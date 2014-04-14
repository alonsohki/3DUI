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

#include "math/matrix.h"
#include "meshFactory.h"

using namespace model;


//
//    4 +----------+ 7
//     /|         /|
//    / |        / |
// 0 +----------+ 3|
//   |5 +-------|--+ 6
//   | /        | /
//   |/         |/
// 1 +----------+ 2
//
void MeshFactory::createCube(Mesh* mesh, float edgeSize) {
    mesh->vertexCount = 6 * 4; // 6 faces, 4 vertices
    mesh->vertices = new Vertex[mesh->vertexCount];
    mesh->type = Mesh::TRIANGLES;
    mesh->indexCount = 6 * 2 * 3; // 6 faces, 2 triangles each
    mesh->indices = new unsigned int[mesh->indexCount];

    // Calculate the vertex positions
    Vector3 positions[8];
    int zValues[2] = { 1, -1 };
    int offset = 0;
    float corner = edgeSize * 0.5f;
    for (int z : zValues) {
        positions[0 + offset] = Vector3(-corner, corner,  z * corner);
        positions[1 + offset] = Vector3(-corner, -corner, z * corner);
        positions[2 + offset] = Vector3(corner,  -corner, z * corner);
        positions[3 + offset] = Vector3(corner,  corner,  z * corner);
        offset += 4;
    }

    // Get the face normals
    Vector3 normals[6] = {  Vector3(0, 0, 1),
                            Vector3(1, 0, 0), 
                            Vector3(0, 0, -1), 
                            Vector3(-1, 0, 0), 
                            Vector3(0, 1, 0), 
                            Vector3(0, -1, 0) };

    int faces[] = { 0, 1, 2, 3,     // front
                    3, 2, 6, 7,     // right
                    7, 6, 5, 4,     // back
                    4, 5, 1, 0,     // left
                    4, 0, 3, 7,     // top
                    1, 5, 6, 2 };   // bottom

    int v = 0;
    int i = 0;
    for (int face = 0; face < 6; ++face) {
        int* faceIndices = &faces[face * 4];
        
        mesh->vertices[v + 0].position = positions[faceIndices[0]];
        mesh->vertices[v + 1].position = positions[faceIndices[1]];
        mesh->vertices[v + 2].position = positions[faceIndices[2]];
        mesh->vertices[v + 3].position = positions[faceIndices[3]];

        mesh->vertices[v + 0].uv = Vector2(0.0f, 0.0f);
        mesh->vertices[v + 1].uv = Vector2(0.0f, 1.0f);
        mesh->vertices[v + 2].uv = Vector2(1.0f, 1.0f);
        mesh->vertices[v + 3].uv = Vector2(1.0f, 0.0f);

        for (int j = 0; j < 4; ++j) {
            mesh->vertices[v + j].normal = normals[face];
        }

        mesh->indices[i++] = v + 0;
        mesh->indices[i++] = v + 1;
        mesh->indices[i++] = v + 2;

        mesh->indices[i++] = v + 0;
        mesh->indices[i++] = v + 2;
        mesh->indices[i++] = v + 3;

        v += 4;
    }
}

void MeshFactory::createPlane(Mesh* mesh, float edgeSize) {
    mesh->indexCount = 6;
    mesh->vertexCount = 4;
    mesh->indices = new unsigned int[6];
    mesh->vertices = new Vertex[4];
    mesh->type = Mesh::TRIANGLES;

    float corner = edgeSize * 0.5f;
    mesh->vertices[0].position = Vector3(-corner, corner, 0.0f);
    mesh->vertices[1].position = Vector3(-corner, -corner, 0.0f);
    mesh->vertices[2].position = Vector3(corner, -corner, 0.0f);
    mesh->vertices[3].position = Vector3(corner, corner, 0.0f);

    mesh->vertices[0].normal = Vector3(0, 0, 1);
    mesh->vertices[1].normal = mesh->vertices[0].normal;
    mesh->vertices[2].normal = mesh->vertices[0].normal;
    mesh->vertices[3].normal = mesh->vertices[0].normal;

    mesh->vertices[0].uv = Vector2(0.0f, 0.0f);
    mesh->vertices[1].uv = Vector2(0.0f, 1.0f);
    mesh->vertices[2].uv = Vector2(1.0f, 1.0f);
    mesh->vertices[3].uv = Vector2(1.0f, 0.0f);

    mesh->indices[0] = 0;
    mesh->indices[1] = 1;
    mesh->indices[2] = 2;

    mesh->indices[3] = 0;
    mesh->indices[4] = 2;
    mesh->indices[5] = 3;
}

void MeshFactory::createSphere(Mesh* mesh, float radius, unsigned int slices, unsigned int stacks) {
    mesh->vertexCount = ( slices + 1 ) * ( stacks + 1 );
    mesh->vertices = new Vertex [ mesh->vertexCount ];
    mesh->indexCount = slices * stacks * 6;
    mesh->indices = new unsigned int [ mesh->indexCount ];

    // Sphere is generated laying down, so we transform each generated vertex
    RotationMatrix matRotation(kPi * 0.5f, 1, 0, 0);

    // Use the sphere parametric equation to generate vertices
    for ( unsigned int i = 0; i <= stacks; ++i )
    {
        float vSin = sin ( i * kPi / stacks );
        float vCos = cos ( i * kPi / stacks );

        for ( unsigned int j = 0; j <= slices; ++j )
        {
            float uSin = sin ( j * k2Pi / slices );
            float uCos = cos ( j * k2Pi / slices );

            unsigned int uiCurVertex = j + i * ( slices + 1 );
            Vertex& cur = mesh->vertices [ uiCurVertex ];

            Vector3 vecPosition = Vector3 ( uSin * vSin, uCos * vSin, vCos ) * matRotation;
            cur.position = vecPosition;
            cur.normal = vecPosition;

            // Assume cylindric texture mapping
            cur.uv = Vector2((float)j / slices, (float)i / stacks);
        }
    }

    // Generate indices. Sphere is generated as quads, but we will triangulate them as well.
    unsigned int uiCurIndex = 0;
    unsigned int v1, v2, v3;
    for ( unsigned int i = 0; i < stacks; ++i )
    {
        for ( unsigned int j = 0; j < slices; ++j )
        {
            unsigned int uiRing = i * ( slices + 1 );
            unsigned int uiNextRing = ( i + 1 ) * ( slices + 1 );

            // First triangle
            v1 = j + uiRing;
            v2 = j + uiNextRing;
            v3 = 1 + j + uiNextRing;

            if ( mesh->vertices[ v1 ].position != mesh->vertices[ v2 ].position &&
                 mesh->vertices[ v1 ].position != mesh->vertices[ v3 ].position &&
                 mesh->vertices[ v2 ].position != mesh->vertices[ v3 ].position )
            {
                mesh->indices[ uiCurIndex++ ] = v3;
                mesh->indices[ uiCurIndex++ ] = v2;
                mesh->indices[ uiCurIndex++ ] = v1;
            }

            // Second triangle
            v2 = 1 + j + uiNextRing;
            v3 = 1 + j + uiRing;
            if ( mesh->vertices[ v1 ].position != mesh->vertices[ v2 ].position &&
                 mesh->vertices[ v1 ].position != mesh->vertices[ v3 ].position &&
                 mesh->vertices[ v2 ].position != mesh->vertices[ v3 ].position )
            {
                mesh->indices[ uiCurIndex++ ] = v3;
                mesh->indices[ uiCurIndex++ ] = v2;
                mesh->indices[ uiCurIndex++ ] = v1;
            }
        }
    }
}
