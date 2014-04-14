//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        button.cpp
// PURPOUSE:    Clickable buttons
//

#include "button.h"

using namespace ui;

Button::Button()
: mHover(false)
{
}

Button::Button(int x, int y, int width, int height, const std::string& text)
: View(x, y)
, mHover(false)
{
    setWidth(width);
    setHeight(height);
    setText(text);
}

Button::~Button()
{
}

void Button::setOnClickListener(const OnClickListener& listener) {
    mListener = listener;
}

void Button::setWidth(int width) {
    mDimensions.x() = width;
}

void Button::setHeight(int height) {
    mDimensions.y() = height;
}

void Button::setText(const std::string& text) {
    mText = text;
}

//--------------------------------------
// Methods inherited from View
bool Button::onMouseEvent(const MouseEvent& event) {
    const Vector2i& pos = getPosition();
    Recti rect(pos.x(), pos.y(), pos.x() + mDimensions.x(), pos.y() + mDimensions.y());
    mHover = rect.contains(event.position.x(), event.position.y());

    if (mHover && event.state == MouseEvent::UP && mListener) {
        mListener(this);
    }

    return mHover;
}

void Button::draw(renderer::Canvas* canvas) {
    const Vector2i& pos = getPosition();
    Recti rect(pos.x(), pos.y(), pos.x() + mDimensions.x(), pos.y() + mDimensions.y());
    Recti innerRect(rect.left + 2, rect.top + 2, rect.right - 2, rect.bottom - 2);

    canvas->fillRect(rect, mStrokeColor);
    canvas->fillRect(innerRect, mHover ? mHighlightColor : mBackgroundColor);
    canvas->drawText(Vector2i(pos.x() + 4, pos.y() + 4), mText, Color::WHITE);
}
