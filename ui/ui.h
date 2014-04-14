//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        ui.h
// PURPOUSE:    UI subsystem.
//

#pragma once

#include "mouseEvent.h"
#include "renderer/canvas.h"
#include "view.h"

namespace ui {

class UI final {
    friend class View;

public:
                UI              ();
                ~UI             ();

    void        addView         (View* view);
    View*       getRoot         () { return &mViewRoot; }

    void        draw            (renderer::Canvas* canvas);
    void        onMouseEvent    (const MouseEvent& event);

private:
    void        notifyDeleted   (View* view);
    void        drawView        (renderer::Canvas* canvas, View* view, const Recti& rect);
    View*       handleMouse     (const MouseEvent& event, View* view);

private:
    View    mViewRoot;
    View*   mMouseOwner;
};

}
