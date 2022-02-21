#ifndef __BMP_CRYPTO__
#define __BMP_CRYPTO__

class BMPImage
{
public:
    BMPImage();
    /* Reads the bmp image with the path image_path
       If the path is invalid or the file is not a BMP file:
            image_width and image_length are set to 0,
            prefix and image are set to ""
    */
    BMPImage(std::string image_path);

    /* Use a new image at path image_path, acts like the constructor*/
    void updateImage(std::string image_path);
private:
    void readImageFile();
    void readImagePrefix();
    void readPixels();
    
    short image_width;  // Image width
    short image_length; // Image length 
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