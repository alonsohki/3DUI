//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        rect.h
// PURPOUSE:    Rectangles.
//

#pragma once

template<class T>
struct Rect {
    Rect() {}
    Rect(const T& left_, const T& top_, const T& right_, const T& bottom_)
    : left(left_), top(top_), right(right_), bottom(bottom_)
    {}

    T left;
    T top;
    T right;
    T bottom;

    T width() const {
        return right - left;
    }

    T height() const {
        return bottom - top;
    }

    bool contains(const T& x, const T& y) const {
        return x >= left && x <= right && y >= top && y <= bottom;
    }
};

typedef Rect<float> Rectf;
typedef Rect<int> Recti;
