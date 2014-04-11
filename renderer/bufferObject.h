//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        bufferObject.h
// PURPOUSE:    Data structure to hold buffer objects.
//

#pragma once

namespace renderer {

class BufferObject
{
public:
    enum Type {
        ARRAY_BUFFER,
        ELEMENT_ARRAY_BUFFER,
    };

public:
    virtual         ~BufferObject   () {}

    virtual bool    wrap            (Type type, void* data, unsigned int dataLength) = 0;
    virtual bool    bind            () = 0;
    virtual bool    unbind          () = 0;
};

}
