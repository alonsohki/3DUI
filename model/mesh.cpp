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
, vertexCount(0)
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
            vertices = nullptr;
        }
        if (indices != nullptr) {
            delete[] indices;
            indices = nullptr;
        }

        if (other.vertexCount > 0) {
            this->vertexCount = other.vertexCount;
            this->vertices = new Vertex[other.vertexCount];
            memcpy(this->vertices, other.vertices, sizeof(Vertex)* other.vertexCount);
        }
        else {
            this->vertexCount = 0;
        }

        if (other.indexCount > 0) {
            this->indexCount = other.indexCount;
            this->indices = new unsigned int[other.indexCount];
            memcpy(this->indices, other.indices, sizeof(unsigned int)* other.indexCount);
        }
        else {
            this->indexCount = 0;
        }

        this->type = other.type;
    }
    return *this;
}
