//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        util.h
// PURPOUSE:    Shared utilities.
//

#pragma once

namespace {

    // Variable swap: Typical A = B and B = A
    template < typename T >
    inline void swap ( T& a, T& b )
    {
        T temp = a;
        a = b;
        b = temp;
    }

}