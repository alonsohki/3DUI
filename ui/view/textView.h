//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        textView.h
// PURPOUSE:    Text views.
//

#pragma once

#include "shared/color.h"
#include <string>
#include "../view.h"

namespace ui {

class TextView : public View {
public:
                TextView        ();
                TextView        (int x, int y, const std::string& text);
    virtual     ~TextView       ();

    void        setText         (const std::string& text);
    void        setColor        (const Color& color);

    //--------------------------------------
    // Methods inherited from View
    void        draw            (renderer::Canvas* canvas) override;

private:
    Color           mColor;
    std::string     mText;
};

}
