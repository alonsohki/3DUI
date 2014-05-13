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
#include "renderer/texture.h"
#include "shared/color.h"

namespace model {

struct Material {
    ~Material()
    {
        delete program;
    }

    std::string         vertexShader;
    std::string         fragmentShader;
    renderer::Program*  program = nullptr;

    Color               diffuse = Color(178, 178, 178, 255);
    Color               ambient = Color(178, 178, 178, 255);
    Color               specular = Color::BLACK;
    Color               emission = Color::BLACK;
    float               shininess = 0.0f;
    bool                shadeless = false;

    renderer::Texture*  texture = nullptr;
    renderer::Texture*  texture1 = nullptr;
    renderer::Texture*  texture2 = nullptr;
};

}
