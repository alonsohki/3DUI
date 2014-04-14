//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        context.h
// PURPOUSE:    Class to hold the editor context.
//

#pragma once

#include "model/scene.h"
#include "renderer/renderer.h"
#include "ui/ui.h"

namespace editor {

class Context final {
private:
                            Context         ();

public:
    static Context*         create          ();
                            ~Context        ();
    
    renderer::Renderer*     getRenderer     () const { return mRenderer; }
    model::Scene*           getScene        () const { return mScene; }
    ui::UI*                 getUI           () const { return mUI; }

private:
    renderer::Renderer*     mRenderer;
    model::Scene*           mScene;
    ui::UI*                 mUI;
};

}