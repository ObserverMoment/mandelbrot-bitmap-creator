//
//  ZoomList.h
//  FractalCreator
//
//  Created by Rich Beans on 05/09/2017.
//  Copyright © 2017 Rich Beans. All rights reserved.
//

#ifndef ZoomList_h
#define ZoomList_h

#include <vector>
#include <utility>
#include "Zoom.h"

class ZoomList {
private:
    // These will track the current / latest position and zoom depth of the image on the screen.
    double m_xCenter{0};
    double m_yCenter{0};
    double m_Scale{0};
    
    // Main window size
    int m_width{0};
    int m_height{0};
    std::vector<Zoom> zooms;
public:
    ZoomList(int width, int height): m_width(width), m_height(height) { m_Scale = 2.0/height; };
    void addZoom(const Zoom& zoom) {
        zooms.push_back(zoom);
        
        // Every tiime that you add a new zoom object (struct) to the list you need to update the variables which track the current zoom amount and position.
        // Convert the zoom objects bitmap co-ordinates to fractal cordinates with zero in the centre.
        m_xCenter += (zoom.x - m_width/2) * m_Scale;
        m_yCenter += (zoom.y - m_height/2) * m_Scale;
        
        // Once you have used the previous overall scale amount you can update it with the new zoom objects scale.
        m_Scale *= zoom.scale;
        
//        std::cout << m_xCenter << ", " << m_yCenter << ", " << m_Scale << std::endl;
        
    };
    std::pair<double,double> doZoom(int x, int y) {
        
        double fractalX = (x - m_width/2 - (m_width - m_height)) * m_Scale + m_xCenter;
        double fractalY = (y - m_height/2) * m_Scale + m_yCenter;
        
        return std::pair<double, double>(fractalX,fractalY);
    };
};

#endif /* ZoomList_h */
