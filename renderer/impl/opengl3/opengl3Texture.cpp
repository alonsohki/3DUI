//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        impl/opengl3/opengl3Texture.cpp
// PURPOUSE:    OpenGL3 texture implementation.
//

#include "opengl3.h"
#include "opengl3Texture.h"

using namespace renderer::impl;

OpenGL3Texture::OpenGL3Texture()
: mHandle(0)
{
}

OpenGL3Texture::~OpenGL3Texture()
{
    if (mHandle != 0) {
        glDeleteTextures(1, &mHandle);
        eglGetError();
    }
}


//------------------------------------------
// Methods inherited from Texture
void OpenGL3Texture::load(const void* pixels, unsigned int width, unsigned int height, Format format, bool pixelPerfect) {
    if (mHandle == 0) {
        GLenum glFormat = GL_INVALID_ENUM;
        switch (format) {
        case RGB:
            glFormat = GL_RGB;
            break;
        case RGBA:
            glFormat = GL_RGBA;
            break;
        case LUMINANCE_ALPHA:
            glFormat = GL_LUMINANCE_ALPHA;
            break;
        }

        if (glFormat != GL_INVALID_ENUM) {
            glGenTextures(1, &mHandle);
            eglGetError();

            glBindTexture(GL_TEXTURE_2D, mHandle);
            eglGetError();

            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            eglGetError();

            if (pixelPerfect) {
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            }
            else {
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            }
            eglGetError();

            glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, pixels);
            eglGetError();
        }
    }
}

bool OpenGL3Texture::bind() const {
    if (mHandle != 0) {
        glBindTexture(GL_TEXTURE_2D, mHandle);
        return true;
    }
    return false;
}
