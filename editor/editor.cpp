
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>

#include "context.h"
#include "model/camera.h"
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

    // Add a camera
    model::Entity* camera = new model::Entity("camera");
    camera->setTransform(Matrix2Transform(LookatMatrix(Vector3(0, 0, -0.25f), Vector3(0.1f, 0, -1), Vector3(0, 1, 0))));
    camera->getComponent<model::Camera>().setPerspective(60.0f, 1.0f, 0.01f, 10.0f);
    context->getScene()->getRoot().addChild(camera);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("editor");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0; 
}

