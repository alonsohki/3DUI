//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        impl/opengl3/renderer.cpp
// PURPOUSE:    OpenGL3 renderer implementation.
//

#include <Windows.h>
#include <gl/glew.h>
#include <gl/GL.h>

#include "../../rendererFactory.h"
#include "materialFactory.h"
#include "opengl3.h"
#include "program.h"


using namespace renderer;
using namespace renderer::impl;

namespace {
    struct ImplData : public RendererImplData {
        ImplData() : initialized(false) {}
        ~ImplData() {
            if (initialized) {
                glDeleteBuffers(2, buffers);
            }
        }

        bool initialized;
        GLuint buffers [ 2 ];

        void createFrom(model::Mesh* mesh) {
            glGenBuffers(2, buffers);

            glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
            eglGetError();
            glBufferData(GL_ARRAY_BUFFER, sizeof(model::Vertex) * mesh->vertexCount, mesh->vertices, GL_STATIC_DRAW);
            eglGetError();

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
            eglGetError();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->indexCount, mesh->indices, GL_STATIC_DRAW);
            eglGetError();

            initialized = true;
        }

        void bind() {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
        }
    };
}

RendererImpl* RendererFactory::createInstance() {
    return new impl::OpenGL3Impl();
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

void OpenGL3Impl::clear() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL3Impl::renderMesh(model::Mesh* mesh, model::Material* material, const Transform& transform, RendererImplData* data_) {
    ImplData* data = static_cast<ImplData*>(data_);
    if (data != nullptr && data->initialized == false) {
        data->createFrom(mesh);
    }

    if (material == nullptr) {
        material = MaterialFactory::getDefault();
    }
    if (material != nullptr && material->program == nullptr) {
        Program* program = createProgram();
        program->loadVertex(material->vertexShader.c_str());
        program->loadFragment(material->fragmentShader.c_str());
        if (program->link()) {
            material->program = program;
        }
        else {
            delete program;
        }
    }

    if (material != nullptr && material->program != nullptr) {
        material->program->use();

        Matrix lookAt = IdentityMatrix();
        Matrix mat = Transform2Matrix ( transform );
        Matrix matNormals = MatrixForNormals ( mat );
        Matrix matGeometry = IdentityMatrix() * lookAt * mat;

        data->bind();

        const model::Vertex* v = 0;
        glVertexAttribPointer ( OpenGL3_Program::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(model::Vertex), (GLchar *)&(v->position) );
        eglGetError();
        glVertexAttribPointer ( OpenGL3_Program::NORMAL, 3, GL_FLOAT, GL_TRUE, sizeof(model::Vertex), (GLchar *)&(v->normal) );
        eglGetError();
        glVertexAttribPointer ( OpenGL3_Program::TEX2D, 2, GL_FLOAT, GL_FALSE, sizeof(model::Vertex), (GLchar *)&(v->uv) );
        eglGetError();
        glEnableVertexAttribArray ( OpenGL3_Program::POSITION );
        eglGetError();
        glEnableVertexAttribArray ( OpenGL3_Program::NORMAL );
        eglGetError();
        glEnableVertexAttribArray ( OpenGL3_Program::TEX2D );
        eglGetError();

        // Set the uniforms
        //material->program->setUniform("un_ProjectionMatrix", m_matProjection );
        material->program->setUniform("un_LookatMatrix", lookAt );
        material->program->setUniform("un_ModelviewMatrix", mat);
        material->program->setUniform("un_NormalMatrix", matNormals);
        material->program->setUniform("un_Matrix", matGeometry );
        //material->program->setUniform("un_ViewVector", m_viewVector );

        GLenum polyType = GL_INVALID_ENUM;
        switch ( mesh->type )
        {
        case model::Mesh::TRIANGLES: polyType = GL_TRIANGLES; break;
            default: break;
        }

        if (polyType != GL_INVALID_ENUM) {
            glDrawElements ( polyType, mesh->indexCount, GL_UNSIGNED_INT, 0 );
            eglGetError();
        }
    }

    glUseProgram(0);
}


RendererImplData* OpenGL3Impl::createData() const {
    return new ImplData();
}

Program* OpenGL3Impl::createProgram() const {
    return new OpenGL3_Program();
}
