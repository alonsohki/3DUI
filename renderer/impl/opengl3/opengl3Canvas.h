//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        impl/opengl3/opengl3Canvas.h
// PURPOUSE:    OpenGL3 Canvas implementation.
//

#pragma once

#include "../../canvas.h"
#include "../../renderer.h"

namespace renderer {
namespace impl {

class OpenGL3Canvas : public CanvasImpl {
public:
                OpenGL3Canvas       ();
    virtual     ~OpenGL3Canvas      ();


    //-----------------------------------------
    // Methods inherited from CanvasImpl
    void        fillRect            (Renderer* renderer, const model::ViewPort& viewPort, const Recti& rect, model::Material* material) override;
    void        drawText            (Renderer* renderer, const model::ViewPort& viewPort, const Vector2i& position, const std::string& text, const Color& color) override;
    void        drawTexture         (Renderer* renderer, const model::ViewPort& viewPort, const Recti& rect, Texture* texture, const Rectf& textureCoordinates) override;
};

}
}
