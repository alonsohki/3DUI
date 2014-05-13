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

#include "ui.h"
#include "view.h"

using namespace ui;

View::View(UI* ui)
: View()
{
    setUI(ui);
}

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

View::View(int x, int y, int width, int height)
: mParent(nullptr)
, mPosition(x, y)
, mDimensions(width, height)
{
}

View::View(const Vector2i& pos)
: mParent(nullptr)
, mPosition(pos)
{
}

View::~View()
{
    mUI->notifyDeleted(this);
}

void View::addView(View* view) {
    assert(view->getParent() == nullptr);

    view->mParent = this;
    view->setUI(mUI);
    mChildren.push_back(view);
}

void View::removeView(View* view) {
    if (view->getParent() == this) {
        mChildren.erase(std::find(mChildren.begin(), mChildren.end(), view));
        view->mParent = nullptr;
    }
}

void View::removeAllViews() {
    for (auto& child : mChildren) {
        child->mParent = nullptr;
    }
    mChildren.clear();
}

void View::setPosition(const Vector2i& position) {
    mPosition = position;
}

void View::setWidth(int width) {
    mDimensions.x() = width;
}

void View::setHeight(int height) {
    mDimensions.y() = height;
}

void View::setDimensions(const Vector2i& dimensions) {
    mDimensions = dimensions;
}

void View::setUI(UI* ui) {
    mUI = ui;

    for (auto& child : mChildren) {
        child->setUI(mUI);
    }
}
