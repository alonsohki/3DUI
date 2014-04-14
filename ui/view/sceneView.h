//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        sceneView.h
// PURPOUSE:    View displaying a 3D scene.
//

#pragma once

#include "../view.h"
#include "model/scene.h"

namespace ui {

class SceneView : public View {
public:
    typedef std::function<void(SceneView* view, model::Entity* entity)> OnPickListener;

public:
                SceneView       ();
                SceneView       (int x, int y, int width, int height, model::Scene* scene);
    virtual     ~SceneView      ();

    void        setScene        (model::Scene* scene);

    //--------------------------------------
    // Methods inherited from View
    void        draw            (renderer::Canvas* canvas) override;

private:
    model::Scene*   mScene;
    OnPickListener  mListener;
};

}
