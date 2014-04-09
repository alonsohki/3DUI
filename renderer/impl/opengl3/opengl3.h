//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        impl/opengl3/opengl3.h
// PURPOUSE:    OpenGL3 implementation.
//

#pragma once

#include "../../rendererPrivate.h"

#if defined(DEBUG)
// This code Copyright (c) Max Rupp
#define eglError( Error, File, Line )\
{\
    fprintf(stderr, "(%s:%u) OpenGL Error: %s\n", File, Line, Error); \
    \
    exit(-1); \
}

#define eglGetError( )\
    switch (glGetError())\
{\
    case GL_INVALID_ENUM:      eglError("GL_INVALID_ENUM", __FILE__, __LINE__); break; \
    case GL_INVALID_VALUE:     eglError("GL_INVALID_VALUE", __FILE__, __LINE__); break; \
    case GL_INVALID_OPERATION: eglError("GL_INVALID_OPERATION", __FILE__, __LINE__); break; \
    case GL_STACK_OVERFLOW:    eglError("GL_STACK_OVERFLOW", __FILE__, __LINE__); break; \
    case GL_STACK_UNDERFLOW:   eglError("GL_STACK_UNDERFLOW", __FILE__, __LINE__); break; \
    case GL_OUT_OF_MEMORY:     eglError("GL_OUT_OF_MEMORY", __FILE__, __LINE__); break; \
    case GL_NO_ERROR:                                              break; \
    default:                                                       break; \
}

// End of (c) Max Rupp code.
#else
#define eglGetError()
#endif

#include "renderer.h"
