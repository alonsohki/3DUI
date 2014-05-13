//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        materialView.h
// PURPOUSE:    View that is rendered using a given material.
//

#pragma once

#include "../view.h"
#include "model/material.h"

namespace ui {

class MaterialView : public View {
public:
                            MaterialView    ();
                            MaterialView    (int x, int y, int width, int height);
    virtual                 ~MaterialView   ();

    void                    setMaterial     (model::Material* material);
    model::Material*        getMaterial     () const { return mMaterial; }


    //--------------------------------------
    // Methods inherited from View
    void                    draw            (renderer::Canvas* canvas) override;



private:
    model::Material*        mMaterial;
};

}
