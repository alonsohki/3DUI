//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        mesh.h
// PURPOUSE:    3D mesh component
//

#pragma once

#include "vertex.h"

namespace model {

struct Mesh {
    enum MeshType {
        TRIANGLES,
    };

            Mesh        ();
            Mesh        ( const Mesh& other );
            ~Mesh       ();

    Mesh&   operator=   (const Mesh& other);

    Vertex*         vertices;
    unsigned int    vertexCount;
    unsigned int*   indices;
    unsigned int    indexCount;
    MeshType        type;
};

}
