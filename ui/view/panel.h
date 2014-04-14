//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        panel.h
// PURPOUSE:    Simple container of multiple views with a gray background.
//

#pragma once

#include "../view.h"
#include "shared/color.h"

namespace ui {

class Panel : public View {
public:
                    Panel           ();
                    Panel           (int x, int y, int width, int height, const Color& background = Color(192, 192, 192, 255));
    virtual         ~Panel          ();


    void            setBackground   (const Color& color);
    const Color&    getBackground   () const { return mBackground; }


    //--------------------------------------
    // Methods inherited from View
    void            draw            (renderer::Canvas* canvas) override;


private:
    Color       mBackground;
};

}