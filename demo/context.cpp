//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        context.cpp
// PURPOUSE:    Class to hold the editor context.
//

#include "context.h"

using namespace demo;

Context::Context()
: mRenderer(nullptr)
, mScene(nullptr)
, mUI(nullptr)
{
}

Context::~Context()
{
    delete mScene;
    delete mRenderer;
    delete mUI;
}

Context* Context::create() {
    Context* context = new Context();
    context->mRenderer = new renderer::Renderer();
    context->mScene = new model::Scene();
    context->mUI = new ui::UI();
    return context;
}
