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
#include "shared/pixmap.h"
#include "texture.h"

namespace renderer {

class Canvas {
public:
                    Canvas          ();
                    Canvas          (Renderer* renderer) : Canvas() { setRenderer(renderer); }
    virtual         ~Canvas         ();

    void            setRenderer     (Renderer* renderer);
    Renderer*       getRenderer     () const { return mRenderer; }
    void            setViewport     (const model::ViewPort& viewPort);
    void            setRect         (const Recti& rect);
    const Recti&    getRect         () const;

    void            fillRect        (const Recti& rect, const Color& color);
    void            drawText        (const Vector2i& position, const std::string& text, const Color& color = Color::WHITE);
    void            drawImage       (const Recti& rect, const Pixmap& image);
    void            drawTexture     (const Recti& rect, Texture* texture, const Rectf& textureCoordinates);

private:
    bool            init            ();

private:
    Renderer*           mRenderer;
    CanvasImpl*         mImpl;
    model::ViewPort     mViewport;
    Recti               mRect;
};

}
