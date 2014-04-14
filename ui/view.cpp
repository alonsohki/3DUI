//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        view.cpp
// PURPOUSE:    Base class for the UI views.
//

#include "view.h"

using namespace ui;

View::View()
: mParent(nullptr)
, mPosition(0, 0)
{
}

View::View(int x, int y)
: mParent(nullptr)
, mPosition(x, y)
{
}

View::View(const Vector2i& pos)
: mParent(nullptr)
, mPosition(pos)
{
}

View::~View()
{
}

void View::addView(View* view) {
    assert(view->getParent() == nullptr);

    view->mParent = this;
    mChildren.push_back(view);
}

void View::setPosition(const Vector2i& position) {
    mPosition = position;
}

