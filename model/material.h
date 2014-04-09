//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        material.h
// PURPOUSE:    Material component
//

#pragma once

#include "renderer/program.h"

namespace model {

struct Material {
    Material() : program(nullptr)
    {
    }
    ~Material()
    {
        delete program;
    }

    std::string         vertexShader;
    std::string         fragmentShader;
    renderer::Program*  program;
};

}
