//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        impl/opengl3/opengl3Canvas.cpp
// PURPOUSE:    OpenGL3 Canvas implementation.
//

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>

#include "math/util.h"

#include "model/camera.h"
#include "model/mesh.h"
#include "model/meshFactory.h"

#include "opengl3Canvas.h"

using namespace renderer;
using namespace renderer::impl;

namespace {
    class Factory {
    public:
        static Factory& instance() {
            static Factory sInstance;
            return sInstance;
        }

    public:
        Factory()
        : mMesh(nullptr)
        , mCamera(nullptr)
        {
        }

        ~Factory() {
            delete mMesh;
            delete mCamera;
        }

        model::Mesh* getMesh() {
            if (mMesh == nullptr) {
                mMesh = new model::Mesh();
                model::MeshFactory::createPlane(mMesh, 2.0f);

                // Center the plane on the top-left corner
                for (unsigned int i = 0; i < mMesh->vertexCount; ++i) {
                    mMesh->vertices[i].position.x() += 1.0f;
                    mMesh->vertices[i].position.y() -= 1.0f;
                }
            }
            return mMesh;
        }

        model::Entity* getCamera() {
            if (mCamera == nullptr) {
                mCamera = new model::Entity();
                mCamera->getComponent<model::Camera>().setOrthographic(-1, 1, 1, -1, 1, -1);
            }
            return mCamera;
        }

    private:
        model::Mesh*    mMesh;
        model::Entity*  mCamera;
    };
}

OpenGL3Canvas::OpenGL3Canvas()
{
}

OpenGL3Canvas::~OpenGL3Canvas()
{
}


//-----------------------------------------
// Methods inherited from CanvasImpl
void OpenGL3Canvas::fillRect(Renderer* renderer, const model::ViewPort& viewPort, const Rectf& rect, const Color& color)
{
    model::Material material;
    material.diffuse = color;
    material.shadeless = true;

    Factory& factory = Factory::instance();
    Transform transform = Matrix2Transform(TranslationMatrix(lerp(-1.0f, rect.left, 1.0f), lerp(1.0f, rect.top, -1.0f), 0.0f) * ScalingMatrix(rect.width(), rect.height(), 1.0f));
    renderer->renderMesh(viewPort, factory.getCamera(), factory.getMesh(), &material, transform);
}

void OpenGL3Canvas::drawText(Renderer* renderer, const model::ViewPort& viewPort, const Vector2& position, const std::string& text, const Color& color)
{
}

void OpenGL3Canvas::drawTexture(Renderer* renderer, const model::ViewPort& viewPort, const Rectf& rect, Texture* tex, const Rectf& textureCoordinates)
{
    model::Material material;
    material.diffuse = Color::WHITE;
    material.shadeless = true;
    material.texture = tex;

    Factory& factory = Factory::instance();
    Transform transform = Matrix2Transform(TranslationMatrix(lerp(-1.0f, rect.left, 1.0f), lerp(1.0f, rect.top, -1.0f), 0.0f) * ScalingMatrix(rect.width(), rect.height(), 1.0f));
    renderer->renderMesh(viewPort, factory.getCamera(), factory.getMesh(), &material, transform);
}
