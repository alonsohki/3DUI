//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        impl/opengl3/program.cpp
// PURPOUSE:    Graphics rendering proram for OpenGL3
//

#include <gl/glew.h>
#include "opengl3.h"
#include "program.h"

using namespace renderer::impl;

namespace {
    GLuint& handle(void* p) {
        return *(GLuint *)p;
    }

    bool attachShader(GLuint program, const char* shaderSource, GLenum type) {
        GLuint handle = glCreateShader(type);
        eglGetError();

        const GLchar* source = static_cast < const GLchar* > ( shaderSource );
        glShaderSource(handle, 1, &source, 0);
        eglGetError();

        glCompileShader(handle);
        eglGetError();

        GLint status;
        glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
        eglGetError();

        if (status == GL_TRUE) {
            glAttachShader ( program, handle );
            eglGetError();
        
            return true;
        }
        else {
            GLint length;
            char* error;
            glGetShaderiv ( handle, GL_INFO_LOG_LENGTH, &length );
            error = new char[length + 1];
            glGetShaderInfoLog ( handle, length + 1, &length, error );

            fprintf(stderr, "Error compiling a shader: %s\n", error);

            delete[] error;
            glDeleteShader(handle);

            return false;
        }
    }
}

OpenGL3_Program::OpenGL3_Program()
: mInitialized(false)
, mLinked(false)
{
    mHandle = new GLuint;
}

OpenGL3_Program::~OpenGL3_Program()
{
    if (mInitialized) {
        // Detach all the attached shaders
        GLint numShaders;
        glGetProgramiv(handle(mHandle), GL_ATTACHED_SHADERS, &numShaders);
        eglGetError();

        if (numShaders > 0 && numShaders < 3) {
            GLuint* shaders = new GLuint[numShaders];
            glGetAttachedShaders(handle(mHandle), numShaders, 0, shaders);
            eglGetError();

            for (int i = 0; i < numShaders; ++i)
            {
                glDetachShader(handle(mHandle), shaders[i]);
                eglGetError();
            }
            delete[] shaders;
        }

        glDeleteProgram(handle(mHandle));
        eglGetError();
    }

    delete mHandle;
}

bool OpenGL3_Program::init() {
    if (!mInitialized) {
        handle(mHandle) = glCreateProgram();
        eglGetError();
        mInitialized = true;
    }
    return mInitialized;
}


//--------------------------------------
// Methods inherited from Program
bool OpenGL3_Program::loadVertex(const char* source) {
    return init() && attachShader(handle(mHandle), source, GL_VERTEX_SHADER);
}

bool OpenGL3_Program::loadFragment (const char* source) {
    return init() && attachShader(handle(mHandle), source, GL_FRAGMENT_SHADER);
}

bool OpenGL3_Program::link () {
    if (!init()) {
        return false;
    }
    else {
        glBindAttribLocation ( handle(mHandle), POSITION, "in_Position" );
        eglGetError();
        glBindAttribLocation ( handle(mHandle), NORMAL, "in_Normal" );
        eglGetError();
        glBindAttribLocation ( handle(mHandle), TEX2D, "in_TexCoord" );
        eglGetError();

        glLinkProgram ( handle(mHandle) );
        eglGetError();

        GLint linked;
        glGetProgramiv ( handle(mHandle), GL_LINK_STATUS, &linked );
        eglGetError();

        mLinked = linked == GL_TRUE;

        if (!mLinked) {
            GLint length;
            char* error;
            glGetProgramiv ( handle(mHandle), GL_INFO_LOG_LENGTH, &length );
            error = new char[length + 1];
            glGetProgramInfoLog ( handle(mHandle), length + 1, &length, error );

            fprintf(stderr, "Error linking a GLSL program: %s\n", error);

            delete[] error;
        }
        return mLinked;
    }
}

bool OpenGL3_Program::use () {
    if (mLinked) {
        glUseProgram ( handle(mHandle) );
        eglGetError();
        return true;
    }
    return false;
}



bool OpenGL3_Program::setUniform (const std::string& name, bool value) {
    GLint loc = glGetUniformLocation ( handle(mHandle), name.c_str() );
    eglGetError();
    if ( loc == -1 )
        return false;
    glUniform1i ( loc, value );
    eglGetError();
    return true;
}

bool OpenGL3_Program::setUniform (const std::string& name, float value) {
    GLint loc = glGetUniformLocation ( handle(mHandle), name.c_str() );
    eglGetError();
    if ( loc == -1 )
        return false;
    glUniform1f ( loc, value );
    eglGetError();
    return true;
}

bool OpenGL3_Program::setUniform (const std::string& name, int value) {
    GLint loc = glGetUniformLocation ( handle(mHandle), name.c_str() );
    eglGetError();
    if ( loc == -1 )
        return false;
    glUniform1i ( loc, value );
    eglGetError();
    return true;
}

bool OpenGL3_Program::setUniform (const std::string& name, const Vector2& vec) {
    GLint loc = glGetUniformLocation ( handle(mHandle), name.c_str() );
    eglGetError();
    if ( loc == -1 )
        return false;
    glUniform2fv ( loc, 1, vec.vector() );
    eglGetError();
    return true;
}

bool OpenGL3_Program::setUniform (const std::string& name, const Vector3& vec) {
    GLint loc = glGetUniformLocation ( handle(mHandle), name.c_str() );
    eglGetError();
    if ( loc == -1 )
        return false;
    glUniform3fv ( loc, 1, vec.vector() );
    eglGetError();
    return true;
}

bool OpenGL3_Program::setUniform (const std::string& name, const Matrix& mat) {
    GLint loc = glGetUniformLocation ( handle(mHandle), name.c_str() );
    eglGetError();
    if ( loc == -1 )
        return false;
    glUniformMatrix4fv ( loc, 1, GL_FALSE, mat.vector() );
    eglGetError();
    return true;
}

bool OpenGL3_Program::setUniform (const std::string& name, const Matrix* mat, unsigned int count) {
    GLint loc = glGetUniformLocation ( handle(mHandle), name.c_str() );
    eglGetError();
    if ( loc == -1 )
        return false;
    glUniformMatrix4fv ( loc, count, GL_FALSE, mat->vector() );
    eglGetError();
    return true;
}

bool OpenGL3_Program::setUniform(const std::string& name, const Color& col, bool includeAlpha)
{
    GLint loc = glGetUniformLocation ( handle(mHandle), name.c_str() );
    eglGetError();
    if ( loc == -1 )
        return false;
    
    float values [ 4 ];
    values[0] = col.r() / 255.0f;
    values[1] = col.g() / 255.0f;
    values[2] = col.b() / 255.0f;
    values[3] = col.a() / 255.0f;
    
    if ( includeAlpha )
        glUniform4fv ( loc, 1, &values[0] );
    else
        glUniform3fv ( loc, 1, &values[0] );
    eglGetError();
    return true;
}

bool OpenGL3_Program::setUniform (const std::string& name, float* values, unsigned int count) {
    GLint loc = glGetUniformLocation ( handle(mHandle), name.c_str() );
    eglGetError();
    if ( loc == -1 )
        return false;
    glUniform1fv ( loc, count, values );
    eglGetError();
    return true;
}
