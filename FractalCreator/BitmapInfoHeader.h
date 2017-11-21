//
//  BitmapInfoHeader.h
//  FractalCreator
//
//  Created by Rich Beans on 18/08/2017.
//  Copyright © 2017 Rich Beans. All rights reserved.
//

#ifndef BitmapInfoHeader_h
#define BitmapInfoHeader_h

#include <cstdint> // This header contains the strict 32 bit int data types. Using strict int sizing like this will ensure portability across platforms and systems.

// This is a preprocessor command which wil tell the struct to be packed along 2 byte boundaries.
// This is necessary because otherwise these structs will be created with some padding, the amount of which will vary and will depend on what the compiler thinks is the most efficient way to store the data.
#pragma pack(2)

struct BitmapInfoHeader {
    std::int32_t headerSize{40}; // This is the size of this info header in bytes.
    std::int32_t width;
    std::int32_t height;
    std::int16_t planes{1};
    std::int16_t bitsPerPixel{24};
    std::int32_t compression{0};
    std::int32_t dataSize{0};
    std::int32_t horizontalResolution{2400};
    std::int32_t verticalResolution{2400};
    std::int32_t colors{0};
    std::int32_t importantColors{0};
};

#endif /* BitmapInfoHeader_h */
