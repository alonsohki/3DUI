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

namespace {
    struct ImplDataHolder {
        RendererImplData* data;

        ImplDataHolder() : data(nullptr) {}
        ~ImplDataHolder() { delete data; }
    };
}

Renderer::Renderer()
: mImpl(nullptr)
{
}

Renderer::~Renderer()
{
    delete mImpl;
}


void Renderer::renderScene(const model::ViewPort& viewPort, model::Scene* scene) {
    if (init()) {
        model::Entity* cameraEntity = scene->getMainCamera();
        if (cameraEntity != nullptr) {
            scene->forEachEntity([this, cameraEntity, &viewPort](model::Entity* entity) -> bool {
                model::Mesh* mesh = entity->findComponent<model::Mesh>();
                if (mesh != nullptr) {
                    ImplDataHolder& dataHolder = entity->getComponent<ImplDataHolder>();
                    if (dataHolder.data == nullptr) {
                        dataHolder.data = mImpl->createData();
                    }
                    model::Material* material = entity->findComponent<model::Material>();

                    mImpl->renderMesh(viewPort, cameraEntity, mesh, material, entity->getTransform(), dataHolder.data);
                }
                return true;
            });
        }
    }
}

void Renderer::clear() {
    if (init()) {
        mImpl->clear();
    }
}


//------------------------------------------------
// Private utility functions
bool Renderer::init() {
    if (mImpl == nullptr) {
        mImpl = RendererFactory::createInstance();
    }
    return mImpl != nullptr;
}
