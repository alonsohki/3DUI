// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        vertexAttrib.h
// PURPOUSE:    Vertex attributes.
//

#pragma once

#include "bufferObject.h"
#include <string>

namespace renderer {

class VertexAttrib {
public:
    enum Type {
        FLOAT,
    };

public:
    virtual                     ~VertexAttrib   () {}

    virtual void                set         (unsigned int elementCount, Type type, bool normalize, unsigned int stride,
                                             BufferObject* bo, const char* offset) = 0;
    virtual void                set         (unsigned int elementCount, Type type, bool normalize, unsigned int stride,
                                             const void* data) = 0;

    virtual bool                enable      (unsigned int index) = 0;
    virtual bool                disable     (unsigned int index) = 0;
};

}
