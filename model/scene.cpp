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

#include "scene.h"

using namespace model;

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::forEachEntity(const Entity::ForEachDelegate& delegate)
{
    mRoot.forEach(delegate);
}
