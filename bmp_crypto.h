#ifndef __BMP_CRYPTO__
#define __BMP_CRYPTO__

#include <string>

class BMPImage
{
public:
    BMPImage();
    /* Reads the bmp image with the path image_path
       If the path is invalid or the file is not a BMP file:
            prefix and image are set to ""
    */
    BMPImage(const std::string& image_path);

    /* Use a new image at path image_path, acts like the constructor*/
    void updateImage(const std::string& image_path);
    void writeImage(const std::string& out_image_path);

    std::string getImg();
    void setImg(std::string img);
private:
    std::string readImageFile(const std::string& image_path);
    
    std::string prefix; // Image information
    std::string image;  // Image pixels data
};


class BMPCrypto
{
public:
    BMPCrypto();
    // BMPCrypto(key); // sets the key
    
    /* Encrypts the bmp image pixels using the key */
    void encryptBMP();
    /* Decrypts the bmp image pixels using the key*/
    void decrpytBMP();

private:
    // key
};

#endif//__BMP_CRYPTO__