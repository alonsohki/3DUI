//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        impl/opengl3/òpengl3VertexAttrib.h
// PURPOUSE:    OpenGL3 vertex attributes.
//

#pragma once

#include "../../vertexAttrib.h"

namespace renderer {
namespace impl {

class OpenGL3VertexAttrib : public VertexAttrib {
public:
                        OpenGL3VertexAttrib     ();
    virtual             ~OpenGL3VertexAttrib    ();

    //--------------------------------------------
    // Methods inherited from VertexAttrib
public:
    void                set                     (unsigned int elementCount, Type type, bool normalize, unsigned int stride,
                                                 BufferObject* bo, const char* offset) override;
    void                set                     (unsigned int elementCount, Type type, bool normalize, unsigned int stride,
                                                 const void* data) override;

    bool                enable                  (unsigned int index) override;
    bool                disable                 (unsigned int index) override;

private:
    BufferObject*   mBuffer;
    const void*     mData;
    const char*     mOffset;
    unsigned int    mElementCount;
    GLenum          mType;
    bool            mNormalize;
    unsigned int    mStride;
};

}
}
