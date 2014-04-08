//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        impl/opengl3.cpp
// PURPOUSE:    OpenGL3 renderer implementation.
//

#include <Windows.h>
#include <gl/GL.h>
#include "opengl3.h"
#include "../rendererFactory.h"

using namespace renderer;
using namespace renderer::impl;

namespace {
    struct ImplData : public RendererImplData {
        
    };
}

RendererImpl* RendererFactory::createInstance() {
    return new impl::OpenGL3Impl();
}

OpenGL3Impl::OpenGL3Impl()
{
}

OpenGL3Impl::~OpenGL3Impl()
{
}

void OpenGL3Impl::clear() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL3Impl::renderMesh(model::Mesh* mesh, const Transform& transform, RendererImplData* data) {
    printf("Rendering mesh: %p\n", mesh);
}


RendererImplData*  OpenGL3Impl::createData() const {
    return new ImplData();
}
