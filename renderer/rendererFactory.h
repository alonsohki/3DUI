//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        rendererFactory.h
// PURPOUSE:    Private classes for the renderer implementations.
//

#pragma once

#include "bufferObject.h"
#include "canvasImpl.h"
#include "impl/selector.h"
#include "rendererImpl.h"
#include "texture.h"

namespace renderer {

class RendererFactory {
public:
    static RendererImpl*    createRenderer      ();
    static CanvasImpl*      createCanvas        ();
    static BufferObject*    createBufferObject  ();
    static Texture*         createTexture       ();
};

}
