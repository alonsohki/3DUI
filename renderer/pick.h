//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        pick.h
// PURPOUSE:    Result of performing a picking operation.
//

#pragma once

namespace renderer {
    struct Pick
    {
        struct Hit {
            ~Hit() {
                delete[] names;
            }

            float z1;
            float z2;
            unsigned int* names = nullptr;
            unsigned int nameCount;
        };

        ~Pick() {
            delete[] hits;
        }

        int hitCount;
        Hit* hits = nullptr;
    };
}
