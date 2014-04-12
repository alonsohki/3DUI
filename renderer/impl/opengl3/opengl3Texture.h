//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        impl/opengl3/opengl3Texture.h
// PURPOUSE:    OpenGL3 texture implementation.
//

#pragma once

#include <Windows.h>
#include <gl/GL.h>

#include "../../texture.h"

namespace renderer {
namespace impl {

class OpenGL3Texture : public Texture
{
public:
                OpenGL3Texture      ();
    virtual     ~OpenGL3Texture     ();

    //------------------------------------------
    // Methods inherited from Texture
public:
    void        load                (const void* pixels, unsigned int width, unsigned int height, Format format, bool pixelPerfect) override;
    bool        bind                () const override;


private:
    GLuint      mHandle;
};

}
}
