//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        rendererPrivate.h
// PURPOUSE:    Private classes for the renderer implementations.
//

#pragma once

#include "constants.h"
#include "math/transform.h"
#include "model/entity.h"
#include "model/material.h"
#include "model/mesh.h"
#include "model/viewPort.h"
#include "program.h"
#include "texture.h"

namespace renderer {

//-------------------------------------------
// Interface for renderer implementations
class RendererImpl {
public:
    virtual                     ~RendererImpl       () {}

    virtual void                buildMaterial       (model::Material* material) = 0;

    virtual void                clear               () = 0;
    virtual void                setEnabled          (Constant state, bool enabled) = 0;
    virtual void                renderMesh          ( const model::ViewPort& viewPort,
                                                      model::Entity* camera,
                                                      model::Mesh* mesh,
                                                      model::Material* material,
                                                      const Transform& transform ) = 0;
    virtual Program*            createProgram       () const = 0;
    virtual Texture*            createTexture       () const = 0;
};

}
