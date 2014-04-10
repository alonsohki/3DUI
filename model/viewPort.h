//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        viewPort.h
// PURPOUSE:    Viewport specification.
//

#pragma once

namespace model {

struct ViewPort {
    ViewPort() {}
    ViewPort(const int& x_, const int& y_, const int& width_, const int& height_)
    : x(x_), y(y_), width(width_), height(height_)
    {}

    int x;
    int y;
    int width;
    int height;
};

}
