//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        editorUI.cpp
// PURPOUSE:    UI for the editor.
//

#include "demoUI.h"
#include "entityCreatorView.h"

#include "model/camera.h"
#include "model/meshFactory.h"

using namespace demo;

DemoUI::DemoUI()
: mPanel(nullptr)
{
}

DemoUI::~DemoUI()
{
    delete mPanel;
}

void DemoUI::setContext(Context* context) {
    if (mPanel == nullptr) {
        createUI();
    }
    mSceneView->setScene(context->getScene());
    mContext = context;
}

void DemoUI::createUI() {
    mPanel = new ui::Panel(0, 0, 300, 600);
    mSceneView = new ui::SceneView(300, 0, 500, 600, nullptr);

    addView(mPanel);
    addView(mSceneView);
}

//-----------------------------------------------
// Methods inherited from ui::View
void DemoUI::onLayout(const Recti& rect) {
    mPanel->setHeight(rect.height());
    mSceneView->setHeight(rect.height());
    mSceneView->setWidth(rect.width() - mPanel->getWidth());

    model::Entity* camera = mSceneView->getScene()->getMainCamera();
    float aspect = (float)rect.width() / rect.height();
    camera->getComponent<model::Camera>().setPerspective(deg2rad(60.0f / (1.0f / aspect)), aspect, 0.1f, 30.0f);
}
