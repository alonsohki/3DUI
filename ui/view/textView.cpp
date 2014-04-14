//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        textView.cpp
// PURPOUSE:    Text views.
//

#include "textView.h"

using namespace ui;

TextView::TextView()
: mColor(Color::WHITE)
{
}

TextView::TextView(int x, int y, const std::string& text)
: View(x, y)
, mColor(Color::WHITE)
{
    setText(text);
}

TextView::~TextView()
{
}

void TextView::setText(const std::string& text) {
    mText = text;
}

void TextView::setColor(const Color& color) {
    mColor = color;
}


//--------------------------------------
// Methods inherited from View
void TextView::draw(renderer::Canvas* canvas) {
    canvas->drawText(getPosition(), mText, mColor);
}
