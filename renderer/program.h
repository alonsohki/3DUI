//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        program.h
// PURPOUSE:    Graphics rendering proram.
//

#pragma once

#include "math/matrix.h"
#include "math/vector.h"
#include "shared/color.h"
#include <string>
#include "vertexAttrib.h"

namespace renderer {

class Program {
public:
    enum DefaultAttributeIndex
    {
        POSITION = 0,
        NORMAL = 1,
        TEX2D = 2,
    };

public:
    virtual             ~Program        () {}

    virtual bool        loadVertex      (const char* source) = 0;
    virtual bool        loadFragment    (const char* source) = 0;
    virtual bool        link            () = 0;

    virtual bool        bind            () = 0;
    virtual bool        unbind          () = 0;

    virtual bool        setVertexAttrib (const std::string& name, VertexAttrib* attrib) = 0;

    virtual bool        setUniform      (const std::string& name, bool value) = 0;
    virtual bool        setUniform      (const std::string& name, float value) = 0;
    virtual bool        setUniform      (const std::string& name, int value) = 0;
    virtual bool        setUniform      (const std::string& name, const Vector2& vec) = 0;
    virtual bool        setUniform      (const std::string& name, const Vector3& vec) = 0;
    virtual bool        setUniform      (const std::string& name, const Matrix& mat) = 0;
    virtual bool        setUniform      (const std::string& name, const Matrix* mat, unsigned int count) = 0;
    virtual bool        setUniform      (const std::string& name, const Color& col, bool includeAlpha) = 0;
    virtual bool        setUniform      (const std::string& name, float* values, unsigned int count) = 0;
};

}

