//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        util.h
// PURPOUSE:    Renderer utilities.
//

#pragma once

#include "renderer.h"
#include "shared/pixmap.h"
#include "texture.h"

namespace renderer {

class Util {
public:
    static Texture* pixmap2Texture(Renderer* renderer, const Pixmap& pix) {
        Texture* tex = renderer->createTexture();
        tex->load(pix.pixels(), pix.width(), pix.height(), Texture::Format::RGBA, false);
        return tex;
    }
};

}
