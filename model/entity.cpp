//
// Copyright � 2014 - Alberto Alonso
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
{
}

Entity::~Entity()
{
}

void Entity::addChild(Entity* entity) {
    assert(entity->getParent() == nullptr);
    entity->mParent = this;
    mChildren.push_back(entity);
}

void Entity::setParent(Entity* parent) {
    return parent->addChild(this);
}

void Entity::forEach(const ForEachDelegate& delegate) {
    for (Entity* entity : getChildren()) {
        entity->forEach(delegate);
    }
    delegate(this);
}
