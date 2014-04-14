//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        imageView.h
// PURPOUSE:    Image views.
//

#pragma once

#include "../view.h"
#include "renderer/texture.h"
#include "shared/pixmap.h"

namespace ui {

class ImageView : public View {
public:
                    ImageView       ();
                    ImageView       (int x, int y, const Pixmap& pixmap);
    virtual         ~ImageView      ();

    void            setImage        (const Pixmap& pixmap);


    //--------------------------------------
    // Methods inherited from View
    void            draw            (renderer::Canvas* canvas) override;


private:
    Pixmap              mImage;
    renderer::Texture*  mTexture;
};

}
