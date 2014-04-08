//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        entity.h
// PURPOUSE:    World entities
//

#pragma once

#include "math/transform.h"
#include "shared/any.h"
#include "shared/FastDelegate.h"
#include <vector>

namespace model {

class Entity {
public:
    typedef fastdelegate::FastDelegate<void (Entity*)> ForEachDelegate;
    typedef std::vector<Entity*> EntityVector;
    typedef std::vector<Any> ComponentVector;

public:
                        Entity          ();
    virtual             ~Entity         ();

    const Transform&    getTransform    () const { return mTransform; }
    Transform&          getTransform    () { return mTransform; }
    void                setTransform    ( const Transform& transform ) { mTransform = transform; }

    void                addChild        ( Entity* entity );
    void                setParent       ( Entity* parent );
    const EntityVector& getChildren     ()  const { return mChildren; }
    Entity*             getParent       () const { return mParent; }

    void                forEach         ( const ForEachDelegate& delegate );


    //-------------------------------------------------------------------
    // Component management
public:
    template<typename T>
    T&                  getComponent()
    {
        T* component = findComponent<T>();
        if (!component) {
            component = createComponent<T>();
        }
        return *component;
    }

    template<typename T>
    T*                  findComponent()
    {
        for (Any current : mComponents) {
            if (current.is<T>()) {
                return &current.as<T>();
            }
        }
        return nullptr;
    }

private:
    template<typename T>
    T*                  createComponent()
    {
        mComponents.push_back(T());
        return &mComponents.back().as<T>();
    }



private:
    Transform           mTransform;
    Entity*             mParent;
    EntityVector        mChildren;
    ComponentVector     mComponents;
};

}
