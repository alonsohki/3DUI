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
, mTextView(4, 4, "")
{
    addView(&mTextView);
}

Button::Button(int x, int y, int width, int height, const std::string& text)
: View(x, y)
, mHover(false)
, mTextView(4, 4, "")
{
    addView(&mTextView);

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

void Button::setText(const std::string& text) {
    mTextView.setText(text);
}

//--------------------------------------
// Methods inherited from View
bool Button::onMouseEvent(const MouseEvent& event) {
    const Vector2i& pos = getPosition();
    const Vector2i& dimensions = getDimensions();

    Recti rect(pos.x(), pos.y(), pos.x() + dimensions.x(), pos.y() + dimensions.y());
    mHover = rect.contains(event.position.x(), event.position.y());

    if (mHover && event.state == MouseEvent::UP && mListener) {
        mListener(this);
    }

    return mHover;
}

void Button::draw(renderer::Canvas* canvas) {
    const Vector2i& pos = getPosition();
    const Vector2i& dimensions = getDimensions();
    Recti rect(pos.x(), pos.y(), pos.x() + dimensions.x(), pos.y() + dimensions.y());
    Recti innerRect(rect.left + 2, rect.top + 2, rect.right - 2, rect.bottom - 2);

    canvas->fillRect(rect, mStrokeColor);
    canvas->fillRect(innerRect, mHover ? mHighlightColor : mBackgroundColor);
}
