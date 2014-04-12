//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        scene.h
// PURPOUSE:    Scene management. For now, just keep the entity tree, but in the
//              future it could hold optimizations for the scene rendering.
//

#pragma once

#include "entity.h"

namespace model {

class Scene {
public:
                            Scene           ();
    virtual                 ~Scene          ();

    Entity*                 getMainCamera   ();
    void                    setMainCamera   (const std::string& id);
    Entity*                 getCamera       (const std::string& id);

    const Entity&           getRoot         () const { return mRoot; }
    Entity&                 getRoot         () { return mRoot; }

    void                    forEachEntity   ( const Entity::ForEachDelegate& delegate );

    Entity*                 findEntity(const std::string& id)
    {
        Entity* ret = nullptr;
        forEachEntity([&ret, &id] (Entity* entity) -> bool {
            if (entity->getID() == id) {
                ret = entity;
                return false;
            }
            return true;
        });
        return ret;
    }

    template<class T>
    void                    findEntities(std::vector<Entity*>* out)
    {
        return findEntities<T>("", out);
    }

    template<class T>
    void                    findEntities    (const std::string& id, std::vector<Entity*>* out)
    {
        if (id == "") {
            forEachEntity([out] (Entity* entity) -> bool {
                if (entity->findComponent<T>() != nullptr) {
                    out->push_back(entity);
                }
                return true;
            });
        }
        else {
            forEachEntity([out, &id](Entity* entity) -> bool {
                if (entity->getID() == id && entity->findComponent<T>() != nullptr) {
                    out->push_back(entity);
                }
                return true;
            });
        }
    }

private:
    Entity      mRoot;
    Entity*     mMainCamera;
};

}
