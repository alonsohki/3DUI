//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        sceneView.cpp
// PURPOUSE:    View displaying a 3D scene.
//

#include "sceneView.h"

using namespace ui;

SceneView::SceneView()
: mScene(nullptr)
{
}

SceneView::SceneView(int x, int y, int width, int height, model::Scene* scene)
: View(x, y)
{
    setWidth(width);
    setHeight(height);
    setScene(scene);
}

SceneView::~SceneView()
{
}


void SceneView::setScene(model::Scene* scene) {
    mScene = scene;
}


//--------------------------------------
// Methods inherited from View
void SceneView::draw(renderer::Canvas* canvas) {
    const Vector2i& pos = getPosition();
    const Vector2i& dimensions = getDimensions();
    model::ViewPort viewPort(pos.x(), pos.y(), dimensions.x(), dimensions.y());

    renderer::Renderer* renderer = canvas->getRenderer();
    renderer->setEnabled(renderer::BLENDING, false);
    renderer->renderScene(viewPort, mScene);
    renderer->setEnabled(renderer::BLENDING, true);
}
