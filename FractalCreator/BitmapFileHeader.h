//
//  BitmapFileHeader.h
//  FractalCreator
//
//  Created by Rich Beans on 18/08/2017.
//  Copyright © 2017 Rich Beans. All rights reserved.
//

#ifndef BitmapFileHeader_h
#define BitmapFileHeader_h

#include <cstdint> // This header contains the strict 32 bit int data types. Using strict int sizing like this will ensure portability across platforms and systems.

// This is a preprocessor command which wil tell the struct to be packed along 2 byte boundaries.
// This is necessary because otherwise these structs will be created with some padding, the amount of which will vary and will depend on what the compiler thinks is the most efficient way to store the data.
#pragma pack(2)

// All the data elements in this struct are divisible exactly by 2 bytes so there will be no padding. This is necessary when creating a file header like this as it must be exactly as specified / required.
struct BitmapFileHeader {
    char header[2]{'B', 'M'}; // Describes the filetype, for use internally and by programs trying to read the file.
    std::int32_t filesize; // The total size of the file.
    std::int32_t reserved{0};
    std::int32_t dataOffset; // The amount of space taken before the start of the actual file data.
};


#endif /* BitmapFileHeader_h */
