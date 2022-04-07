// #include "cryptopp/cryptlib.h"
#include "cryptopp/modes.h"
// #include "cryptopp/rijndael.h"
// #include "cryptopp/files.h"

#include <fstream>
#include <iostream>
#include <cstring> // for memcpy

#include "bmp_crypto.h"

/* -=-=-=-=-=-=-=-=- BMPImage -=-=-=-=-=-=-=-=- */

BMPImage::BMPImage()
{
    prefix_size = 0;
    img_size = 0;
    prefix = nullptr;
    image = nullptr;
}

BMPImage::BMPImage(const std::string& image_path)
{
    prefix_size = 0;
    img_size = 0;
    prefix = nullptr;
    image = nullptr;
    updateImage(image_path);
}

BMPImage::~BMPImage()
{
    if(img_size)
    {
        delete prefix;
        delete image;
    }
}

void BMPImage::writeImage(const std::string& out_image_path)
{
    std::ofstream oimg(out_image_path);
    
    // check for error
    if(oimg.fail())
    {
        printf("An Error have occured while trying to open an output file.\n");
        return;
    }

    oimg.write(prefix, prefix_size);
    oimg.write(image, img_size);
    oimg.close();
}

void BMPImage::updateImage(const std::string& image_path)
{
    uint pixels_offest = 0; // image pixels offset, end of image info
    size_t file_length = 0; // size of prefix + pixels in bytes
    size_t offset = 0;
    int p256 = 1; // used to read an int, a byte at a time

    // ---- read image file ---- //
    std::ifstream iimg(image_path);

    // check for error
    if(iimg.fail())
    {
        printf("An error occured while trying to open the BMP file.\n");
        iimg.close();
        return;
    }

    // get file length
    iimg.seekg (0, iimg.end);
    file_length = iimg.tellg();
    iimg.seekg (0, iimg.beg);


    // ---- confirm file type and set prefix_size and image_size ---- //
    // check file size, this is done to make sure no error occur when reading image_size or checking image type
    if(file_length < 14)
    {
        printf("The file input is not a BMP file.\n");
        iimg.close();
        return;
    }

    // check file type
    if(iimg.get() != 'B' || iimg.get() != 'M') // check first 2 letters in the file
    {
        std::cout << "The file: " << image_path << " is not a BMP image.\n";
        iimg.close();
        return;
    }   

    // read offset to image size(the position at which image pixels start)
    iimg.seekg(10);
    for(int i = 0; i < 4; ++i)
    {
        uint* c;
        offset += static_cast<uint>(iimg.get()) * p256;
        p256 *= 256;
    }

    // chekc if file is valid, based on offset read
    if(file_length < offset)
    {
        printf("The file input is not a BMP file.\n");
        iimg.close();
        return;
    }

    // ---- read image and prefix ---- //
    // reinitialize image
    delete image;
    delete prefix;
    prefix = nullptr;
    image = nullptr;
    prefix_size = offset;
    img_size = file_length - offset;

    // read prefix and image
    iimg.seekg (0, iimg.beg);
    
    prefix = new char[prefix_size];
    iimg.read(prefix, prefix_size);

    image = new char[img_size];
    iimg.read(image, img_size);
}

char* BMPImage::getImg() {return image;}
uint BMPImage::getImgSize() {return img_size;}

void BMPImage::setImg(char* img)
{
    if(!img)
        return;
    std::memcpy(image, img, img_size);
}

/* -=-=-=-=-=-=-=-=- BMPCrypto -=-=-=-=-=-=-=-=- */

BMPCrypto::BMPCrypto()
{
    key = CryptoPP::SecByteBlock(CryptoPP::AES::DEFAULT_KEYLENGTH);
    for(size_t i = 0; i < 16; ++i)
        key[i] = 0;
}

BMPCrypto::BMPCrypto(std::string k)
{
    key = CryptoPP::SecByteBlock(CryptoPP::AES::DEFAULT_KEYLENGTH);
    setKey(k);
}

void BMPCrypto::setKey(std::string k)
{
    uint8_t key_size = k.size();
    uint8_t i;

    if(key_size >= 15)
        for(i = 0; i < 16; ++i)
            key[i] = k[i];
    else
    {
        key = CryptoPP::SecByteBlock(CryptoPP::AES::DEFAULT_KEYLENGTH);
        for(i = 0; i < key_size; ++i)
            key[i] = k[i];
    }
}

void BMPCrypto::encryptBMP(BMPImage& img)
{
    if(!img.getImgSize())
        return;

    char* oimg = new char[img.getImgSize()];
    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE); // iv is 0 by default

    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption enc(key, key.size(), iv);
    enc.ProcessData(reinterpret_cast<byte*>(oimg), reinterpret_cast<byte*>(img.getImg()), img.getImgSize());// set up encryption parameters
    
    img.setImg(oimg);
    delete oimg;
}

void BMPCrypto::decrpytBMP(BMPImage& img)
{
    if(!img.getImgSize())
        return;

    char* oimg = new char[img.getImgSize()];

    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE); // iv is 0 by default
    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption dec(key, key.size(), iv); // set up decryption parameters
    // decrypt image
    dec.ProcessData(reinterpret_cast<byte*>(oimg), reinterpret_cast<byte*>(img.getImg()), img.getImgSize());

    img.setImg(oimg);
    delete oimg;
}