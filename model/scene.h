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
                        Scene       ();
    virtual             ~Scene      ();

    const Entity&       getRoot     () const { return mRoot; }
    Entity&             getRoot     () { return mRoot; }

    void                forEachEntity   ( const Entity::ForEachDelegate& delegate );
    void                forEachEntity   ( const Entity::ForEachLambda& lambda );

private:
    Entity      mRoot;
};

}
