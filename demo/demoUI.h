//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        editorUI.h
// PURPOUSE:    UI for the editor.
//

#pragma once

#include "context.h"

#include "ui/view.h"
#include "ui/view/panel.h"
#include "ui/view/sceneView.h"

namespace demo {

class DemoUI final : public ui::View {
public:
                DemoUI      ();
    virtual     ~DemoUI     ();

    void        setContext  (Context* context);


    //-----------------------------------------------
    // Methods inherited from ui::View
    void        onLayout    (const Recti& rect) override;

private:
    void        createUI    ();

private:
    ui::Panel*      mPanel;
    ui::SceneView*  mSceneView;
    Context*        mContext;
};

}
