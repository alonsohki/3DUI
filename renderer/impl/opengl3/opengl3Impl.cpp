//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        impl/opengl3/opengl3Impl.cpp
// PURPOUSE:    OpenGL3 renderer implementation.
//

#include <Windows.h>
#include <gl/glew.h>
#include <gl/GL.h>

#include "materialFactory.h"
#include "model/camera.h"
#include "model/entity.h"
#include "opengl3.h"
#include "opengl3BufferObject.h"
#include "opengl3Impl.h"
#include "opengl3Texture.h"
#include "opengl3VertexAttrib.h"
#include "program.h"

using namespace renderer;
using namespace renderer::impl;

namespace {
    struct ImplData {
        bool initialized = false;
        OpenGL3BufferObject buffers[2];
        OpenGL3VertexAttrib attribs[3];

        void createFrom(model::Mesh* mesh) {
            if (!initialized) {
                const model::Vertex* v = nullptr;

                buffers[0].wrap(BufferObject::ARRAY_BUFFER, mesh->vertices, sizeof(model::Vertex) * mesh->vertexCount);
                buffers[1].wrap(BufferObject::ELEMENT_ARRAY_BUFFER, mesh->indices, sizeof(unsigned int)* mesh->indexCount);
                attribs[0].set(3, VertexAttrib::FLOAT, false, sizeof(model::Vertex), &buffers[0], (GLchar *)&(v->position));
                attribs[1].set(3, VertexAttrib::FLOAT, true,  sizeof(model::Vertex), &buffers[0], (GLchar *)&(v->normal));
                attribs[2].set(2, VertexAttrib::FLOAT, false, sizeof(model::Vertex), &buffers[0], (GLchar *)&(v->uv));
                initialized = true;
            }
        }

        void bind(Program* program) {
            program->setVertexAttrib("in_Position", &attribs[0]);
            program->setVertexAttrib("in_Normal",   &attribs[1]);
            program->setVertexAttrib("in_TexCoord", &attribs[2]);
            buffers[1].bind();
        }
    };
}

OpenGL3Impl::OpenGL3Impl()
{
    static bool glewInitialized = false;
    if (!glewInitialized) {
        glewInit();
    }
}

OpenGL3Impl::~OpenGL3Impl()
{
}

void OpenGL3Impl::buildMaterial(model::Material* material) {
    if (material != nullptr && material->program == nullptr &&
        material->vertexShader.length() > 0 && material->fragmentShader.length() > 0)
    {
        Program* program = new OpenGL3_Program();
        program->loadVertex(material->vertexShader.c_str());
        program->loadFragment(material->fragmentShader.c_str());
        if (program->link()) {
            material->program = program;
        }
        else {
            delete program;
        }
    }
}

void OpenGL3Impl::clear() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL3Impl::setEnabled(Constant state, bool enabled) {
    GLenum glState = GL_INVALID_ENUM;
    switch (state) {
    case Constant::DEPTH_TEST:
        glState = GL_DEPTH_TEST;
        break;
    case Constant::CULL_FACE:
        glState = GL_CULL_FACE;
        break;
    case Constant::BLENDING:
        glState = GL_BLEND;
        break;
    }

    if (glState != GL_INVALID_ENUM) {
        enabled ? glEnable(glState) : glDisable(glState);

        if (enabled && glState == GL_BLEND) {
            glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        }
    }
}

void OpenGL3Impl::renderMesh(const model::ViewPort& viewPort,
                             model::Entity* cameraEntity,
                             model::Mesh* mesh,
                             model::Material* material,
                             const Transform& transform) {
    Program* program = nullptr;
    model::Material* defaultMaterial = MaterialFactory::getDefault();

    // Make sure we have the render data
    if (mesh->renderData.is_null()) {
        mesh->renderData = ImplData();
    }
    ImplData* data = &mesh->renderData.as<ImplData>();
    data->createFrom(mesh);

    // Let's keep the default material compiled
    buildMaterial(defaultMaterial);

    // Get the camera from the camera entity
    model::Camera* camera = cameraEntity->findComponent<model::Camera>();

    // Resolve the material to use for rendering
    if (material == nullptr) {
        material = defaultMaterial;
    }
    else {
        buildMaterial(material);
    }

    // Resolve the program to use for rendering
    program = material->program;
    if (program == nullptr) {
        program = defaultMaterial->program;
    }

    if (camera != nullptr && material != nullptr && program != nullptr) {
        glViewport(viewPort.x, viewPort.y, viewPort.width, viewPort.height);

        Matrix lookAt = Transform2Matrix(invert(cameraEntity->getTransform()));
        Matrix mat = Transform2Matrix ( transform );
        Matrix matNormals = MatrixForNormals ( mat );
        const Matrix& matProjection = camera->getProjection();
        Matrix matGeometry = matProjection * lookAt * mat;

        program->bind();

        // Set the uniforms
        program->setUniform("un_ProjectionMatrix", matProjection);
        program->setUniform("un_LookatMatrix", lookAt );
        program->setUniform("un_ModelviewMatrix", mat);
        program->setUniform("un_NormalMatrix", matNormals);
        program->setUniform("un_Matrix", matGeometry );
        //program->setUniform("un_ViewVector", m_viewVector );

        GLenum polyType = GL_INVALID_ENUM;
        switch ( mesh->type )
        {
        case model::Mesh::TRIANGLES: polyType = GL_TRIANGLES; break;
            default: break;
        }

        if (polyType != GL_INVALID_ENUM) {
            if (material->texture != nullptr) {
                program->setUniform("un_TextureLevels", 1.0f);
                program->setUniform("un_Sampler0", 0);
            }
            else {
                program->setUniform("un_TextureLevels", 0.0f);
            }

            program->setUniform("un_Material.diffuse",     material->diffuse,    true );
            program->setUniform("un_Material.ambient",     material->ambient,    false);
            program->setUniform("un_Material.specular",    material->specular,   false);
            program->setUniform("un_Material.emission",    material->emission,   false);
            program->setUniform("un_Material.shininess",   material->shininess);
            program->setUniform("un_Material.isShadeless", material->shadeless);

            // For now, hardcode the light values
            program->setUniform("un_Light.diffuse", Color::WHITE, false);
            program->setUniform("un_Light.ambient", Color(10, 20, 25, 255), false);
            program->setUniform("un_Light.specular", Color::WHITE, false);
            program->setUniform("un_Light.position", Vector3(0, 0, 1) );
            program->setUniform("un_Light.direction", Vector3(0.1f, 0, -1) );

            data->bind(program);
            glDrawElements ( polyType, mesh->indexCount, GL_UNSIGNED_INT, 0 );
            eglGetError();
        }

        program->unbind();
    }

    glUseProgram(0);
}

Program* OpenGL3Impl::createProgram() const {
    return new OpenGL3_Program();
}

Texture* OpenGL3Impl::createTexture() const {
    return new OpenGL3Texture();
}
