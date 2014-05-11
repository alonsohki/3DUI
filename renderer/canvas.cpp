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
, mRect(0, 0, 0, 0)
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

void Canvas::setViewport(const model::ViewPort& viewPort) {
    mViewport = viewPort;
}

void Canvas::setRect(const Recti& rect) {
    mRect = rect;
}

const Recti& Canvas::getRect() const {
    return mRect;
}

void Canvas::setRenderer(Renderer* renderer) {
    mRenderer = renderer;
}

void Canvas::fillRect(const Recti& rect, const Color& color) {
    if (init()) {
        mImpl->fillRect(mRenderer, mViewport, Recti(mRect.left + rect.left, mRect.top + rect.top, rect.right, rect.bottom), color);
    }
}

void Canvas::drawText(const Vector2i& position, const std::string& text, const Color& color) {
    if (init()) {
        mImpl->drawText(mRenderer, mViewport, position + Vector2i(mRect.left, mRect.top), text, color);
    }
}

void Canvas::drawImage(const Recti& rect, const Pixmap& pixmap) {
    if (init()) {
        Texture* texture = mRenderer->createTexture();
        if (texture != nullptr) {
            texture->load(pixmap.pixels(), pixmap.width(), pixmap.height(), renderer::Texture::RGBA, false);
            mImpl->drawTexture(mRenderer, mViewport, Recti(mRect.left + rect.left, mRect.top + rect.top, rect.right, rect.bottom), texture, Rectf(0, 0, 1, 1));
            delete texture;
        }
    }
}

void Canvas::drawTexture(const Recti& rect, Texture* texture, const Rectf& textureCoordinates) {
    if (init()) {
        mImpl->drawTexture(mRenderer, mViewport, Recti(mRect.left + rect.left, mRect.top + rect.top, mRect.left + rect.right, mRect.top + rect.bottom), texture, textureCoordinates);
    }
}
