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

#include "editorUI.h"
#include "entityCreatorView.h"

#include "model/meshFactory.h"

using namespace editor;

EditorUI::EditorUI()
: mPanel(nullptr)
{
}

EditorUI::~EditorUI()
{
    delete mPanel;
}

void EditorUI::setScene(model::Scene* scene) {
    if (mPanel == nullptr) {
        createUI();
    }
    mSceneView->setScene(scene);
    mScene = scene;
}

void EditorUI::createUI() {
    mPanel = new ui::Panel(0, 0, 300, 600);
    mSceneView = new ui::SceneView(300, 0, 500, 600, nullptr);

    addView(mPanel);
    addView(mSceneView);

    EntityCreatorView* creator = new EntityCreatorView();
    creator->setOnCreateEntityListener([this](const std::string& entityType) {
        model::Entity* entity = new model::Entity(entityType);
        if (entityType == "cube") {
            model::MeshFactory::createCube(&entity->getComponent<model::Mesh>(), 1.0f);
        }
        else if (entityType == "plane") {
            model::MeshFactory::createPlane(&entity->getComponent<model::Mesh>(), 1.0f);
        }
        else if (entityType == "sphere") {
            model::MeshFactory::createSphere(&entity->getComponent<model::Mesh>(), 1.0f, 30, 30);
        }
        else {
            delete entity;
            entity = nullptr;
        }

        if (entity != nullptr) {
            mScene->getRoot().addChild(entity);
        }
    });

    mPanel->addView(creator);
}

//-----------------------------------------------
// Methods inherited from ui::View
void EditorUI::onLayout(const Recti& rect) {
    mPanel->setHeight(rect.height());
    mSceneView->setHeight(rect.height());
    mSceneView->setWidth(rect.width() - mPanel->getWidth());
}
