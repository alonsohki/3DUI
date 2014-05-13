//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        materialView.cpp
// PURPOUSE:    View that is rendered using a given material.
//

#include "materialView.h"

using namespace ui;

MaterialView::MaterialView()
{
}

MaterialView::MaterialView(int x, int y, int width, int height)
: View(x, y, width, height)
{
}

MaterialView::~MaterialView() {
}

void MaterialView::setMaterial(model::Material* material) {
    mMaterial = material;
}


//--------------------------------------
// Methods inherited from View
void MaterialView::draw(renderer::Canvas* canvas) {
    const Vector2i& pos = getPosition();
    const Vector2i& dim = getDimensions();
    Recti rect(pos.x(), pos.y(), pos.x() + dim.x(), pos.y() + dim.y());
    canvas->fillRect(rect, mMaterial);
}
