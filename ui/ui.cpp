//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        ui.cpp
// PURPOUSE:    UI subsystem.
//

#include "ui.h"

using namespace ui;

UI::UI()
: mMouseOwner(nullptr)
{
}

UI::~UI()
{
}

void UI::addView(View* view) {
    mViewRoot.addView(view);
}

void UI::draw(renderer::Canvas* canvas) {
    Recti rootRect = canvas->getRect();
    drawView(canvas, &mViewRoot, rootRect);
    canvas->setRect(rootRect);
}

void UI::drawView(renderer::Canvas* canvas, View* view, const Recti& rect) {
    canvas->setRect(rect);
    view->onLayout(rect);
    view->draw(canvas);

    const Vector2i& pos = view->getPosition();
    Recti childrenRect(rect.left + pos.x(), rect.top + pos.y(), rect.right + pos.x(), rect.top + pos.y());

    View::ViewVector& children = view->getChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        View* child = *iter;
        drawView(canvas, child, childrenRect);
    }
}

void UI::onMouseEvent(const MouseEvent& event) {
    if (mMouseOwner == nullptr) {
        mMouseOwner = &mViewRoot;
    }

    View* newOwner = handleMouse(event, mMouseOwner);
    if (newOwner == nullptr && mMouseOwner != &mViewRoot) {
        mMouseOwner = handleMouse(event, &mViewRoot);
    }
    else {
        mMouseOwner = newOwner;
    }
}

View* UI::handleMouse(const MouseEvent& event, View* view) {
    View::ViewVector& children = view->getChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        View* handler = handleMouse(event, *iter);
        if (handler != nullptr) {
            return handler;
        }
    }

    return view->onMouseEvent(event) ? view : nullptr;
}

void UI::notifyDeleted(View* view) {
    if (view == mMouseOwner) {
        mMouseOwner = nullptr;
    }
}
