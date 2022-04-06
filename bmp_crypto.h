#ifndef __BMP_CRYPTO__
#define __BMP_CRYPTO__

#include "cryptopp/osrng.h"
#include "cryptopp/hex.h"

#include <string>

/*

*/
class BMPImage
{
public:
    /* Sets
         img_size and img_pixels_size to 0
         image and image_pixels to nullptr
    */
    BMPImage();
    /* Reads the bmp image with the path image_path
       sets the member variables according to the bmp image file
       If an error occures while openning the file or it is not a BMP file
        the member variables are set to the default values
    */
    BMPImage(const std::string& image_path);
    // frees image
    ~BMPImage(); 

    /* setup new image at path image_path, acts like the constructor
        except when an error occures the member variables keep their previous values
    */
    void updateImage(const std::string& image_path);

    /* write bmp image to a file
        if an error occurs while writing the file, an error message will be displayed
    */
    void writeImage(const std::string& out_image_path);

    char* getImg(); // return image_pixels
    uint getImgSize(); // returns img_pixels_size
    /* sets image_pixels, this function does nothing if img is a nullptr,
        and frees img memory, if img is not an allocated memory on the heap an error will occure
    */
    void setImg(char* img);
private:
    
    uint prefix_size; // image prefix size in bytes
    uint img_size; // pixels size in byte
    char* prefix; // The image prefix/info data
    char* image; // Image pixels data
};

/*
*/
class BMPCrypto
{
public:
    /* sets the key to zero  */
    BMPCrypto();
    /* Sets the key used for encryption/decryption, the key can only be up to 16 characters,
        any more will not be used, any less will be replaced by zero vlaues
    */
    BMPCrypto(std::string key);
    
    /* Encrypts the BMP image using the key */
    void encryptBMP(BMPImage& img);
    /* Decrypts the cipher BMP image using the key */
    void decrpytBMP(BMPImage& img);

    /* works like the constructor */
    void setKey(std::string k);
private:
    CryptoPP::SecByteBlock key; // 128bit AES key
};

#endif//__BMP_CRYPTO__