//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        button.h
// PURPOUSE:    Clickable buttons
//

#pragma once

#include "../view.h"
#include <string>

namespace ui {

class Button : public View {
public:
    typedef std::function<void(Button*)> OnClickListener;

public:
                    Button              ();
                    Button              (int x, int y, int width, int height, const std::string& text);
    virtual         ~Button             ();

    void            setOnClickListener  (const OnClickListener& listener);

    void            setWidth            (int width);
    void            setHeight           (int height);
    void            setText             (const std::string& text);

    //--------------------------------------
    // Methods inherited from View
    bool            onMouseEvent        (const MouseEvent& event) override;
    void            draw                (renderer::Canvas* canvas) override;

private:
    Vector2i            mDimensions;
    std::string         mText;
    OnClickListener     mListener;
    Color               mStrokeColor = Color::BLACK;
    Color               mBackgroundColor = Color(128, 128, 128, 255);
    Color               mHighlightColor = Color(180, 180, 180, 255);
    bool                mHover;
};

}
