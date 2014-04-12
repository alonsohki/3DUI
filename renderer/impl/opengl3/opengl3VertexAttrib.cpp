//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        impl/opengl3/opengl3VertexAttrib.cpp
// PURPOUSE:    OpenGL3 vertex attributes.
//

#include <gl/glew.h>
#include "opengl3.h"
#include "opengl3VertexAttrib.h"

using namespace renderer;
using namespace renderer::impl;

OpenGL3VertexAttrib::OpenGL3VertexAttrib()
: mBuffer(nullptr)
, mData(nullptr)
{
}

OpenGL3VertexAttrib::~OpenGL3VertexAttrib()
{
}


void OpenGL3VertexAttrib::set(unsigned int elementCount, Type type, bool normalize, unsigned int stride, BufferObject* bo, const char* offset)
{
    mElementCount = elementCount;
    mNormalize = normalize;
    mStride = stride;
    mBuffer = bo;
    mOffset = offset;
    mData = nullptr;

    switch (type) {
    case FLOAT:
        mType = GL_FLOAT;
        break;
    }
}

void OpenGL3VertexAttrib::set(unsigned int elementCount, Type type, bool normalize, unsigned int stride, const void* data)
{
    mElementCount = elementCount;
    mNormalize = normalize;
    mStride = stride;
    mBuffer = nullptr;
    mOffset = nullptr;
    mData = data;

    switch (type) {
    case FLOAT:
        mType = GL_FLOAT;
        break;
    }
}

bool OpenGL3VertexAttrib::enable(unsigned int index)
{
    if (mBuffer != nullptr) {
        mBuffer->bind();
        glVertexAttribPointer(index, mElementCount, mType, mNormalize ? GL_TRUE : GL_FALSE, mStride, mOffset);
        eglGetError();
    }
    else {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        eglGetError();
        glVertexAttribPointer(index, mElementCount, mType, mNormalize ? GL_TRUE : GL_FALSE, mStride, mData);
        eglGetError();
    }

    glEnableVertexAttribArray(index);
    eglGetError();
    return true;
}

bool OpenGL3VertexAttrib::disable(unsigned int index)
{
    glDisableVertexAttribArray(index);
    eglGetError();

    return true;
}
