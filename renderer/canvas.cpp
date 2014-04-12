//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        canvas.cpp
// PURPOUSE:    Bridge to canvas implementations.
//

#include <algorithm>
#include "canvas.h"
#include "rendererFactory.h"

using namespace renderer;

Canvas::Canvas()
: mImpl(nullptr)
, mRenderer(nullptr)
{
}

Canvas::~Canvas()
{
    delete mImpl;
}

bool Canvas::init() {
    if (mRenderer == nullptr) {
        return false;
    }
    else {
        mRenderer->setEnabled(Constant::CULL_FACE, true);
        mRenderer->setEnabled(Constant::DEPTH_TEST, false);

        if (mImpl == nullptr) {
            mImpl = RendererFactory::createCanvas();
            return mImpl != nullptr;
        }
        else {
            return true;
        }
    }
}

void Canvas::setRect(const Recti& rect) {
    mViewport = model::ViewPort(rect.left, rect.top, rect.width(), rect.height());
}

void Canvas::setRenderer(Renderer* renderer) {
    mRenderer = renderer;
}

void Canvas::fillRect(const Rectf& rect, const Color& color) {
    if (init()) {
        mImpl->fillRect(mRenderer, mViewport, rect, color);
    }
}

void Canvas::drawText(const Vector2& position, const std::string& text, const Color& color) {
    if (init()) {
        mImpl->drawText(mRenderer, mViewport, position, text, color);
    }
}

void Canvas::drawImage(const Rectf& rect, const Pixmap& pixmap) {
    if (init()) {
        Texture* texture = mRenderer->createTexture();
        if (texture != nullptr) {
            texture->load(pixmap.pixels(), pixmap.width(), pixmap.height(), renderer::Texture::RGBA, false);
            mImpl->drawTexture(mRenderer, mViewport, rect, texture, Rectf(0, 0, 1, 1));
            delete texture;
        }
    }
}

void Canvas::drawTexture(const Rectf& rect, Texture* texture, const Rectf& textureCoordinates) {
    if (init()) {
        mImpl->drawTexture(mRenderer, mViewport, rect, texture, textureCoordinates);
    }
}
