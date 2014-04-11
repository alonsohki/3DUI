//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        impl/opengl3/opengl3BufferObject.h
// PURPOUSE:    OpenGL3 buffer objects.
//

#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include "../../bufferObject.h"

namespace renderer {
namespace impl {

class OpenGL3BufferObject : public BufferObject {
public:
                OpenGL3BufferObject     ();
    virtual     ~OpenGL3BufferObject    ();

    //--------------------------------------------
    // Methods inherited from BufferObject
public:
    bool        wrap                    (Type type, void* data, unsigned int dataLength) override;
    bool        bind                    () override;
    bool        unbind                  () override;

private:
    GLuint      mHandle;
    GLenum      mType;
};

}
}
