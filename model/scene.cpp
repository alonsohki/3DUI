//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        scene.cpp
// PURPOUSE:    Scene management. For now, just keep the entity tree, but in the
//              future it could hold optimizations for the scene rendering.
//

#include "camera.h"
#include "scene.h"

using namespace model;

Scene::Scene()
: mMainCamera(nullptr)
{
}

Scene::~Scene()
{
}

Entity* Scene::getMainCamera() {
    if (mMainCamera == nullptr) {
        std::vector<Entity*> cameras;
        findEntities<Camera>(&cameras);

        if (cameras.size() > 0) {
            mMainCamera = cameras[0];
        }
    }
    return mMainCamera;
}

Entity* Scene::getCamera(const std::string& id) {
    std::vector<Entity*> cameras;
    findEntities<Camera>(id, &cameras);
    if (cameras.size() > 0) {
        return cameras[0];
    }
    return nullptr;
}

void Scene::setMainCamera(const std::string& id) {
    mMainCamera = getCamera(id);
}

void Scene::forEachEntity(const Entity::ForEachDelegate& delegate)
{
    mRoot.forEach(delegate);
}

void Scene::forEachEntity(const Entity::ForEachLambda& lambda)
{
    mRoot.forEach(lambda);
}
