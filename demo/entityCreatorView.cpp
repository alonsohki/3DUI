//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        entityCreatorView.cpp
// PURPOUSE:    Widget to create new entities.
//

#include "entityCreatorView.h"

#include "ui/view/button.h"

using namespace demo;

EntityCreatorView::EntityCreatorView()
{
    init();
}

EntityCreatorView::~EntityCreatorView()
{
}

void EntityCreatorView::setOnCreateEntityListener(const OnCreateEntityListener& listener)
{
    mListener = listener;
}

void EntityCreatorView::init() {
    ui::TextView* title = new ui::TextView(10, 10, "Create new entity");
    title->setColor(Color::BLACK);

    ui::Button* addCube = new ui::Button(10, 40, 70, 30, "+ Cube");
    addCube->setOnClickListener([this](ui::Button* button) {
        if (mListener) {
            mListener("cube");
        }
    });

    ui::Button* addPlane = new ui::Button(90, 40, 70, 30, "+ Plane");
    addPlane->setOnClickListener([this](ui::Button* button) {
        if (mListener) {
            mListener("plane");
        }
    });

    ui::Button* addSphere = new ui::Button(170, 40, 70, 30, "+ Sphere");
    addSphere->setOnClickListener([this](ui::Button* button) {
        if (mListener) {
            mListener("sphere");
        }
    });

    addView(title);
    addView(addCube);
    addView(addPlane);
    addView(addSphere);
}
