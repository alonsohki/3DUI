//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        impl/opengl3/opengl3BufferObject.cpp
// PURPOUSE:    OpenGL3 buffer objects.
//

#include <gl/glew.h>

#include "opengl3.h"
#include "opengl3BufferObject.h"

using namespace renderer::impl;

OpenGL3BufferObject::OpenGL3BufferObject()
: mHandle(0)
{
}

OpenGL3BufferObject::~OpenGL3BufferObject()
{
    if (mHandle != 0) {
        glDeleteBuffers(1, &mHandle);
        eglGetError();
    }
}

//--------------------------------------------
// Methods inherited from BufferObject
bool OpenGL3BufferObject::wrap(Type type, void* data, unsigned int dataLength) {
    if (mHandle == 0) {
        mType = GL_INVALID_ENUM;
        switch (type) {
        case Type::ARRAY_BUFFER:
            mType = GL_ARRAY_BUFFER;
            break;

        case Type::ELEMENT_ARRAY_BUFFER:
            mType = GL_ELEMENT_ARRAY_BUFFER;
            break;
        }

        if (mType != GL_INVALID_ENUM) {
            glGenBuffers(1, &mHandle);
            eglGetError();

            glBindBuffer(mType, mHandle);
            eglGetError();

            glBufferData(mType, dataLength, data, GL_STATIC_DRAW);
            eglGetError();

            return true;
        }
    }
    return false;
}

bool OpenGL3BufferObject::bind() {
    if (mHandle != 0) {
        glBindBuffer(mType, mHandle);
        return true;
    }
    return false;
}

bool OpenGL3BufferObject::unbind() {
    if (mHandle != 0) {
        glBindBuffer(mType, 0);
        return true;
    }
    return false;
}
