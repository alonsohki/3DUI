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

#include "model/scene.h"
#include "renderer/renderer.h"

namespace editor {

class Context final {
private:
                            Context         ();

public:
    static Context*         create          ();
                            ~Context        ();
    
    renderer::Renderer*     getRenderer     () const { return mRenderer; }
    model::Scene*           getScene        () const { return mScene; }

private:
    renderer::Renderer*     mRenderer;
    model::Scene*           mScene;
};

}