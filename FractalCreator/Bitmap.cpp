//
//  Bitmap.cpp
//  FractalCreator
//
//  Created by Rich Beans on 18/08/2017.
//  Copyright © 2017 Rich Beans. All rights reserved.
//

#include "Bitmap.hpp"

Bitmap::Bitmap(int width, int height):
    m_width(width),
    m_height(height),
    // The amount of memory required will be the width and the height in pixels (total pixels) multiplied by the space needed per pixel - which in this case is 3 x uint8_t (one for each colour).
    // The {} syntax after the uint8_t array constructor will set all the memory to zero.
    m_pPixelMem(new uint8_t[width*height*3]{}) {};

bool Bitmap::writeToFile(std::string filename) {
    
    // First create the two header objects.
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    
    double dataSize = m_width * m_height * 3;
    
    // Then fill the uninitialized data in the headers now that we know how big the file is going to be. The total number of bytes is the size of both headers + the size of the data (which is 3 bytes per pixel for width * height pixels). DataOffset is where the actual data starts - i.e. after the headers.
    fileHeader.filesize = sizeof(fileHeader) + sizeof(infoHeader) + (dataSize);
    fileHeader.dataOffset = sizeof(fileHeader) + sizeof(infoHeader);
    
    infoHeader.width = m_width;
    infoHeader.height = m_height;
    
    // Open the stream and check it is open.
    std::ofstream fileStream;
    fileStream.open(filename, std::ios::out | std::ios::binary);
    if (!fileStream) { return false; };
    
    // Write the fileheader, infoheader and the data. All must be cast to a char*, as this is the pointer type that the ofstream object requires. For the fileHeader and infoHeader you have to go to the data using the & and then cast what is there to a char*.
    fileStream.write((char*)&fileHeader, sizeof(fileHeader));
    fileStream.write((char*)&infoHeader, sizeof(infoHeader));
    // As the data is actually a unique_ptr, which you cannot cast, you have to use the inique_ptr's .get() function to first return a raw 'normal' pointer, then cast the result of this to a char*. You cannot re-cast a unique_ptr by default.
    fileStream.write((char*)m_pPixelMem.get(), dataSize);
    
    fileStream.close();
    
    if (!fileStream) { return false; };
    
    std::cout << "Written To File" << std::endl;
    
    return true;
};

void Bitmap::setPixel(int x, int y, std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
    // First you want to get a new pointer to the block of image pixel data. You must use the .get() function of the unique_ptr object so you ca re-cast it as the type of pointer that you need (in this case a uint8_t.)
    uint8_t* pPixelData = m_pPixelMem.get();
    // Use pointer arithmetic to get to the correct pixel. Remember that there are three bytes per pixel so you must multiply everything by three.
    pPixelData += ((y * m_width) + x) * 3;
    
    // Bmp files are little endian, so the largest bit goes last instead of first. This means that instead of being RGB in the pixel data you actually need to describe BGR values.
    pPixelData[0] = blue;
    pPixelData[1] = green;
    pPixelData[2] = red;
    
    // You could also access these bytes as follows by incrementing the pointer and then using the dereference operator to get at the value at its location.
//    *pPixelData = blue;
//    pPixelData += 1;
//    *pPixelData = green;
//    pPixelData += 1;
//    *pPixelData = red;
};





