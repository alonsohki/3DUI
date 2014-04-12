//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        texture.h
// PURPOUSE:    Texture interface.
//

#pragma once

namespace renderer {

class Texture {
public:
    enum Format {
        RGB,
        RGBA,
        LUMINANCE_ALPHA,
    };
public:
    virtual             ~Texture    () {}

    virtual void        load        (const void* pixels, unsigned int width, unsigned int height, Format format, bool pixelPerfect = false) = 0;
    virtual bool        bind        () const = 0;
};

}
