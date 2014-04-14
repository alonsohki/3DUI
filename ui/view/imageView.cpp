//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        imageView.cpp
// PURPOUSE:    Image views.
//

#include "imageView.h"

using namespace ui;

ImageView::ImageView()
: mTexture(nullptr)
{
}

ImageView::ImageView(int x, int y, const Pixmap& image)
: View(x, y)
, mTexture(nullptr)
{
    setImage(image);
}

ImageView::~ImageView()
{
    delete mTexture;
}

void ImageView::setImage(const Pixmap& image) {
    delete mTexture;
    mTexture = nullptr;

    mImage = image;
}



//--------------------------------------
// Methods inherited from View
void ImageView::draw(renderer::Canvas* canvas) {
    if (mTexture == nullptr) {
        mTexture = canvas->getRenderer()->createTexture();
        mTexture->load(mImage.pixels(), mImage.width(), mImage.height(), renderer::Texture::RGBA, false);
    }

    const Vector2i& pos = getPosition();
    Recti rect(pos.x(), pos.y(), pos.x() + mImage.width(), pos.y() + mImage.height());
    canvas->drawTexture(rect, mTexture, Rectf(0, 0, 1, 1));
}
