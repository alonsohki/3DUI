//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        meshFactory.h
// PURPOUSE:    3D mesh generator
//

#pragma once

#include "mesh.h"

namespace model {

class MeshFactory {
public:
    static void     createCube      ( Mesh* into, float edgeSize );
};

}