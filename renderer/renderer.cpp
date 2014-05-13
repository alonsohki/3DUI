//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        renderer.cpp
// PURPOUSE:    Renderer interface
//

#include "renderer.h"
#include "rendererFactory.h"

using namespace renderer;

Renderer::Renderer()
: mImpl(nullptr)
{
}

Renderer::~Renderer()
{
    delete mImpl;
}

void Renderer::buildMaterial(model::Material* material) {
    if (init()) {
        mImpl->buildMaterial(material);
    }
}

Texture* Renderer::createTexture() {
    if (init()) {
        return mImpl->createTexture();
    }
    return nullptr;
}

VertexAttrib* Renderer::createVertexAttrib() {
    if (init()) {
        return mImpl->createVertexAttrib();
    }
    return nullptr;
}

void Renderer::renderScene(const model::ViewPort& viewPort, model::Scene* scene) {
    if (init()) {
        model::Entity* cameraEntity = scene->getMainCamera();
        if (cameraEntity != nullptr) {
            mImpl->setEnabled(CULL_FACE, true);
            mImpl->setEnabled(DEPTH_TEST, true);

            scene->forEachEntity([this, cameraEntity, &viewPort](model::Entity* entity) -> bool {
                model::Mesh* mesh = entity->findComponent<model::Mesh>();
                if (mesh != nullptr) {
                    model::Material* material = entity->findComponent<model::Material>();

                    mImpl->renderMesh(viewPort, cameraEntity, mesh, material, entity->getTransform());
                }
                return true;
            });
        }
    }
}

void Renderer::renderMesh(const model::ViewPort& viewPort, model::Entity* camera, model::Mesh* mesh, model::Material* material, const Transform& transform) {
    if (init()) {
        mImpl->renderMesh(viewPort, camera, mesh, material, transform);
    }
}

void Renderer::clear() {
    if (init()) {
        mImpl->clear();
    }
}

void Renderer::setEnabled(Constant state, bool enabled) {
    if (init()) {
        mImpl->setEnabled(state, enabled);
    }
}

model::Entity* Renderer::pick(const model::ViewPort& viewPort, model::Scene* scene, const Vector2i& position) {
    model::Entity* pickedEntity = nullptr;

    if (init()) {
        model::Entity* cameraEntity = scene->getMainCamera();
        if (cameraEntity != nullptr) {
            mImpl->setEnabled(CULL_FACE, true);
            mImpl->setEnabled(DEPTH_TEST, true);

            std::vector<model::Entity*> entities;
            Pick pick;
            mImpl->beginPicking(viewPort, position);
            scene->forEachEntity([this, cameraEntity, &viewPort, &entities](model::Entity* entity) -> bool {
                model::Mesh* mesh = entity->findComponent<model::Mesh>();
                if (mesh != nullptr) {
                    entities.push_back(entity);
                    mImpl->renderForPicking(viewPort, cameraEntity, mesh, entity->getTransform(), entities.size());
                }
                return true;
            });
            mImpl->endPicking(&pick);
        }
    }

    return pickedEntity;
}


//------------------------------------------------
// Private utility functions
bool Renderer::init() {
    if (mImpl == nullptr) {
        mImpl = RendererFactory::createRenderer();
    }
    return mImpl != nullptr;
}
