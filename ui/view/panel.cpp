//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        panel.cpp
// PURPOUSE:    Simple container of multiple views with a gray background.
//

#include "panel.h"

using namespace ui;

Panel::Panel()
{
    setBackground(Color(192, 192, 192, 255));
}

Panel::Panel(int x, int y, int width, int height, const Color& background)
: View(x, y)
{
    setWidth(width);
    setHeight(height);
    setBackground(background);
}

Panel::~Panel()
{
}

void Panel::setBackground(const Color& color) {
    mBackground = color;
}

//--------------------------------------
// Methods inherited from View
void Panel::draw(renderer::Canvas* canvas) {
    const Vector2i& pos = getPosition();

    Recti rect(pos.x(), pos.y(), mDimensions.x() + pos.x(), mDimensions.y() + pos.y());
    canvas->fillRect(rect, mBackground);
}
