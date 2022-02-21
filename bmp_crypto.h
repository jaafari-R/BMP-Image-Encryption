#ifndef __BMP_CRYPTO__
#define __BMP_CRYPTO__

#include <string>

class BMPImage
{
public:
    /* Sets
         img_size and img_pixels_size to 0
         image and image_pixels to nullptr
    */
    BMPImage();
    /* Reads the bmp image with the path image_path
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
    void writeImage(const std::string& out_image_path);

    char* getImgData(); // return image_pixels
    uint getImgSize(); // returns img_size
    void setImgData(char* img); // sets image_pixels
private:
    char* readImageFile(const std::string& image_path);
    
    uint img_size; // image size in bytes
    uint img_pixels_size; // pixels size in byte
    char* image; // The whole image file content
    char* image_pixels; // Image pixels data
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