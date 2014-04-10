//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        materialFactory.cpp
// PURPOUSE:    Material factory
//

#include "materialFactory.h"

using namespace renderer::impl;

model::Material* MaterialFactory::getDefault() {
    static bool initialized = false;
    static model::Material mat;

    if (!initialized) {
        mat.vertexShader = R"(
            attribute vec2 in_TexCoord;
            attribute vec3 in_Position;
            attribute vec3 in_Normal;

            uniform mat4 un_Matrix;
            uniform mat4 un_ProjectionMatrix;
            uniform mat4 un_LookatMatrix;
            uniform mat4 un_ModelviewMatrix;

            uniform mat4 un_NormalMatrix;

            varying vec3 ex_Normal;
            varying vec2 ex_TexCoord;

            void main(void)
            {
                vec4 in_Position4 = vec4 ( in_Position, 1.0 );
                vec4 in_Normal4 = vec4 ( in_Normal, 0.0 );

                gl_Position = un_Matrix * in_Position4;
                ex_Normal = (un_NormalMatrix * in_Normal4).xyz;

                normalize(ex_Normal);

                ex_TexCoord = in_TexCoord;
            }
        )";

        mat.fragmentShader = R"(
            varying vec3 ex_Normal;
            varying vec2 ex_TexCoord;
            uniform mat4 un_LookatMatrix;
            uniform vec3 un_ViewVector;
            uniform float un_TextureLevels;
            uniform sampler2D un_Sampler0;

            void main(void)
            {
                float diffuseFactor = max(-dot(ex_Normal, vec3(1.0, 0.0, 0.1)), 0.0);
                vec4 pixel = vec4(diffuseFactor, diffuseFactor + 0.05, diffuseFactor, 1.0);

                if (un_TextureLevels > 0.0) {
                    pixel *= texture2D ( un_Sampler0, ex_TexCoord );
                }

                gl_FragColor = pixel;
            }
        )";

        initialized = true;
    }

    return &mat;
}