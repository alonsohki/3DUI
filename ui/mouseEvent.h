//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        mouseEvent.h
// PURPOUSE:    Hold data relating a mouse event.
//

#pragma once

#include "math/vector.h"

namespace ui {

struct MouseEvent {
    enum Button {
        LEFT,
        MIDDLE,
        RIGHT
    };

    enum State {
        DOWN,
        MOVE,
        UP
    };

    Button      button;
    State       state;
    Vector2i    position;
};

}
