#include "bmp_crypto.h"

#include <fstream>

/* -=-=-=-=-=-=-=-=- BMPImage -=-=-=-=-=-=-=-=- */

BMPImage::BMPImage()
{
    prefix = "";
    image = "";
}

BMPImage::BMPImage(const std::string& image_path)
{
    updateImage(image_path);
}

// TODO
void BMPImage::writeImage(const std::string& out_image_path)
{

}

// TODO check file type
void BMPImage::updateImage(const std::string& image_path)
{
    int pixels_offest; // image pixels offset, end of image info
    std::string img = readImageFile(image_path);
    // check image type 

    // set img data
    pixels_offest = img[10] + img[11] * 256 + img[12] * 256*256 + img[13] * 256*256*256;
    prefix = img.substr(0, pixels_offest);
    image = img.substr(pixels_offest, img.size() - pixels_offest);
}

// TODO do error checking
std::string BMPImage::readImageFile(const std::string& image_path)
{
    char* img;
    int file_length;
    std::ifstream iimg(image_path);

    // check for error

    // get length of file:
    iimg.seekg (0, iimg.end);
    file_length = iimg.tellg();
    iimg.seekg (0, iimg.beg);

    // read and return file
    iimg.read(img, file_length);
    return static_cast<std::string>(img);
}

void BMPImage::setImg(std::string img)
{
    image = img;
}
