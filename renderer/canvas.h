//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        canvas.h
// PURPOUSE:    Bridge to canvas implementations.
//

#pragma once

#include "canvasImpl.h"
#include "math/rect.h"
#include "renderer.h"
#include "shared/color.h"

namespace renderer {

class Canvas {
public:
                Canvas      ();
                Canvas      (Renderer* renderer) : Canvas() { setRenderer(renderer); }
    virtual     ~Canvas     ();

    void        setRenderer (Renderer* renderer);
    void        setRect     (const Recti& rect);

    void        fillRect    (const Rectf& rect, const Color& color);
    void        drawText    (const Vector2& position, const std::string& text, const Color& color = Color::WHITE);

private:
    bool        init        ();

private:
    Renderer*           mRenderer;
    CanvasImpl*         mImpl;
    model::ViewPort     mViewport;
};

}
