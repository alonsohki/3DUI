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

#include "../../rendererFactory.h"
#include "opengl3BufferObject.h"
#include "opengl3Canvas.h"
#include "opengl3Impl.h"

using namespace renderer;
using namespace renderer::impl;

RendererImpl* RendererFactory::createRenderer() {
    return new impl::OpenGL3Impl();
}

CanvasImpl* RendererFactory::createCanvas() {
    return new impl::OpenGL3Canvas();
}

BufferObject* RendererFactory::createBufferObject() {
    return new impl::OpenGL3BufferObject();
}
