#include "bmp_crypto.h"

#include <fstream>
#include <iostream>

/* -=-=-=-=-=-=-=-=- BMPImage -=-=-=-=-=-=-=-=- */

BMPImage::BMPImage()
{
    img_size = 0;
    img_pixels_size = 0;
    image = nullptr;
    image = nullptr;
}

BMPImage::BMPImage(const std::string& image_path)
{
    img_size = 0;
    img_pixels_size = 0;
    image = nullptr;
    image = nullptr;
    updateImage(image_path);
}

BMPImage::~BMPImage()
{
    if(img_size)
        delete image;
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

    std::cout << img_size;
    oimg.write(image, img_size);
    oimg.close();
}

void BMPImage::updateImage(const std::string& image_path)
{
    uint pixels_offest = 0; // image pixels offset, end of image info
    char* img = readImageFile(image_path);
    if(!img)
        return;

    // the position at which the image pixel data starts
    pixels_offest = static_cast<uint>(img[10]) + static_cast<uint>(img[11]) * 256 + static_cast<uint>(img[12]) *256*256 + static_cast<uint>(img[13] *256*256*256);

    // free memory if occupied
    if(img_pixels_size)
    {
        delete image;
        image = nullptr;
        image_pixels = nullptr;
        img_pixels_size = 0;
    }

    // set img data
    image = img;
    image_pixels = img + pixels_offest;
    img_pixels_size = img_size - pixels_offest;
}

char* BMPImage::readImageFile(const std::string& image_path)
{
    char* img = nullptr;
    int file_length;
    std::ifstream iimg(image_path);

    // check for error
    if(iimg.fail())
    {
        printf("An error occured while trying to open the BMP file.\n");
        iimg.close();
        return nullptr;
    }
    
    // get length of file:
    iimg.seekg (0, iimg.end);
    file_length = iimg.tellg();
    iimg.seekg (0, iimg.beg);
    img = new char[file_length];

    // read file
    iimg.read(img, file_length);
    iimg.close();

    // check file type 
    if(img[0] != 'B' || img[1] != 'M')
    {
        std::cout << "The file: " << image_path << " is not a BMP image.\n";
        delete img;
        return nullptr;
    }
    img_size = file_length;
    return img;
}

char* BMPImage::getImgData() {return image_pixels;}
uint BMPImage::getImgSize() {return img_size;}

void BMPImage::setImgData(char* img)
{
    delete image;
    image = img;
    image_pixels = image + (img_size - img_pixels_size);
}
