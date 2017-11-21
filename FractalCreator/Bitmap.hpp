//
//  Bitmap.hpp
//  FractalCreator
//
//  Created by Rich Beans on 18/08/2017.
//  Copyright © 2017 Rich Beans. All rights reserved.
//

#ifndef Bitmap_hpp
#define Bitmap_hpp

#include <stdio.h>
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>

#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

class Bitmap {
private:
    int m_width{0};
    int m_height{0};
    // A smart pointer to an array of uint8_t ints - initialized to nullptr.
    std::unique_ptr<uint8_t[]> m_pPixelMem{nullptr};
public:
    Bitmap(int width, int height);
    
    // Method to write to file. Will return true if successful and false otherwise.
    bool writeToFile(std::string filename);
    
    // This method will set a single picel within the bitmap file.
    // At location x,y and with uint8_t RGB values for each.
    void setPixel(int x, int y, std::uint8_t red, std::uint8_t green, std::uint8_t blue);
    
};

#endif /* Bitmap_hpp */
