//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        renderer.h
// PURPOUSE:    Renderer interface
//

#pragma once

#include "constants.h"
#include "math/transform.h"
#include "model/mesh.h"
#include "model/scene.h"
#include "model/viewPort.h"
#include "rendererImpl.h"
#include "texture.h"

namespace renderer {

class Renderer {
public:
                    Renderer            ();
                    ~Renderer           ();

    Texture*        createTexture       ();
    VertexAttrib*   createVertexAttrib  ();
    void            buildMaterial       (model::Material* material);

    void            renderScene         (const model::ViewPort& viewPort, model::Scene* scene);
    void            renderMesh          (const model::ViewPort& viewPort, model::Entity* camera, model::Mesh* mesh, model::Material* material, const Transform& transform);
    void            clear               ();

    model::Entity*  pick                (const model::ViewPort& viewPort, model::Scene* scene, const Vector2i& position);

    void            setEnabled          (Constant state, bool enabled);

    //------------------------------------------------
    // Private utility functions
private:
    bool            init                ();

private:
    RendererImpl*   mImpl;
};

}

