//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        entity.cpp
// PURPOUSE:    World entities
//

#include <deque>
#include "entity.h"

using namespace model;

Entity::Entity()
: mParent(nullptr)
, mTransform(IdentityTransform())
, mLocalTransform(IdentityTransform())
{
}

Entity::Entity(const std::string& id)
: Entity()
{
    setID(id);
}

Entity::~Entity()
{
    for (Entity* child : getChildren()) {
        delete child;
    }
}

void Entity::addChild(Entity* entity) {
    assert(entity->getParent() == nullptr);
    entity->mParent = this;
    entity->setTransform(entity->mLocalTransform);
    mChildren.push_back(entity);
}

void Entity::setParent(Entity* parent) {
    parent->addChild(this);
    setTransform(mLocalTransform);
}

bool Entity::forEach(const ForEachDelegate& delegate) {
    for (Entity* entity : getChildren()) {
        if (!entity->forEach(delegate)) {
            return false;
        }
    }
    return delegate(this);
}

void Entity::setTransform(const Transform& transform) {
    mLocalTransform = transform;
    Entity* parent = getParent();
    if (parent != nullptr) {
        mTransform = parent->getTransform() * mLocalTransform;
    }
    else {
        mTransform = mLocalTransform;
    }
}
