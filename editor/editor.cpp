
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>

#include "model/entity.h"
#include "model/meshFactory.h"

int main(int argc, char** argv)
{
    using namespace model;

    Entity entity;
    Mesh& cube = entity.getComponent<Mesh>();
    MeshFactory::createCube(&cube, 1.0f);

	glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (250, 250);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("hello");
    glutMainLoop();
    return 0; 
}

