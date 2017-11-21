//
//  Zoom.h
//  FractalCreator
//
//  Created by Rich Beans on 05/09/2017.
//  Copyright © 2017 Rich Beans. All rights reserved.
//

#ifndef Zoom_h
#define Zoom_h

struct Zoom {
    // Bitmap co-ordinates and image scaling / zoom.
    int x{0};
    int y{0};
    double scale{1.0}; // Initial scale is 1.0, meaning full view of the 
    
    Zoom(int x, int y, double scale): x(x), y(y), scale(scale) {};
};


#endif /* Zoom_h */
