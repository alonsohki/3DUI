//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        entityCreatorView.h
// PURPOUSE:    Widget to create new entities.
//

#pragma once

#include "ui/view/panel.h"

namespace editor {

class EntityCreatorView final : public ui::Panel {
public:
    typedef std::function<void(const std::string&)> OnCreateEntityListener;

public:
                EntityCreatorView           ();
    virtual     ~EntityCreatorView          ();

    void        setOnCreateEntityListener   (const OnCreateEntityListener& listener);


private:
    void        init                        ();

private:
    OnCreateEntityListener  mListener;
};

}