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

#include "math/transform.h"
#include "model/entity.h"
#include "model/material.h"
#include "model/mesh.h"
#include "program.h"

namespace renderer {

//-------------------------------------------
// Interface for renderer implementations
class RendererImplData {
public:
    virtual         ~RendererImplData   () {}
};

class RendererImpl {
public:
    virtual                     ~RendererImpl       () {}

    virtual void                clear               () = 0;
    virtual void                renderMesh          ( model::Entity* camera, model::Mesh* mesh, model::Material* material, const Transform& transform, RendererImplData* data ) = 0;
    virtual RendererImplData*   createData          () const = 0;
    virtual Program*            createProgram       () const = 0;
};

}
