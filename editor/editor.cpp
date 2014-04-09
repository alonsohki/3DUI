
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>

#include "context.h"
#include "model/entity.h"
#include "model/meshFactory.h"

using namespace editor;

namespace {
    Context* context;

    void display() {
        context->getRenderer()->clear();
        context->getRenderer()->renderScene(context->getScene());
        glutSwapBuffers();
    }

    void finalize() {
        delete context;
    }
}

int main(int argc, char** argv)
{
    atexit(finalize);

    context = Context::create();

    // Add a sample cube
    model::Entity* entity = new model::Entity();
    model::MeshFactory::createCube(&entity->getComponent<model::Mesh>(), 1.0f);
    context->getScene()->getRoot().addChild(entity);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("editor");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0; 
}

