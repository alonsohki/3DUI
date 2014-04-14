//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        impl/opengl3/opengl3Impl.h
// PURPOUSE:    OpenGL3 renderer implementation.
//

#pragma once

#include <Windows.h>
#include <gl/GL.h>

#include "../../rendererImpl.h"
#include "program.h"

namespace renderer {
namespace impl {

class OpenGL3Impl : public RendererImpl {
public:
                        OpenGL3Impl         ();
    virtual             ~OpenGL3Impl        ();

    //-------------------------------------------------
    // Methods inherited from RendererImpl
    void                buildMaterial       (model::Material* material) override;
    void                clear               () override;
    void                setEnabled          (Constant state, bool enabled) override;
    void                renderMesh          (const model::ViewPort& viewPort,
                                             model::Entity* camera,
                                             model::Mesh* mesh,
                                             model::Material* material,
                                             const Transform& transform ) override;
    void                beginPicking        (const model::ViewPort& viewPort, const Vector2i& position) override;
    void                renderForPicking    (const model::ViewPort& viewPort,
                                             model::Entity* camera,
                                             model::Mesh* mesh,
                                             const Transform& transform,
                                             unsigned int name) override;
    void                endPicking          (Pick* result) override;

    Program*            createProgram       () const override;
    Texture*            createTexture       () const override;

private:
    bool    mPicking;
    Matrix  mPickingMatrix;
    GLuint  mPickingBuffer[512];
};

}
}
