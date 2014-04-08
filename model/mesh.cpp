//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        mesh.cpp
// PURPOUSE:    3D mesh component
//

#include "mesh.h"

using namespace model;

Mesh::Mesh()
: vertices(nullptr)
, indices(nullptr)
, indexCount(0)
, type(TRIANGLES)
{
}

Mesh::Mesh(const Mesh& other)
: vertices(nullptr)
, indices(nullptr)
{
    operator=(other);
}

Mesh::~Mesh()
{
    if (vertices != nullptr) {
        delete[] vertices;
    }
    if (indices != nullptr) {
        delete[] indices;
    }
}

Mesh& Mesh::operator=(const Mesh& other) {
    if (this != &other) {
        if (vertices != nullptr) {
            delete[] vertices;
        }
        if (indices != nullptr) {
            delete[] indices;
        }

        this->vertexCount = other.vertexCount;
        this->vertices = new Vertex[other.vertexCount];
        memcpy(this->vertices, other.vertices, sizeof(Vertex) * other.vertexCount);

        this->indexCount = other.indexCount;
        this->indices = new unsigned int[other.indexCount];
        memcpy(this->indices, other.indices, sizeof(unsigned int) * other.indexCount);

        this->type = other.type;
    }
    return *this;
}
