//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        vertex.h
// PURPOUSE:    Vertices
//

#pragma once

#include "math/vector.h"

namespace model {

struct Vertex {
    Vector3 position;
    Vector3 normal;
};

}
