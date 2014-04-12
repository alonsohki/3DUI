
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>

#include <chrono>
#include "context.h"
#include "model/camera.h"
#include "model/entity.h"
#include "model/meshFactory.h"

#include "renderer/canvas.h"

using namespace editor;

namespace {
    float xpos = 0.0f;
    Context* context;
    model::ViewPort viewPort;

    void display() {
        using namespace std::chrono;
        auto t0 = high_resolution_clock::now();

        context->getRenderer()->clear();

        context->getRenderer()->renderScene(viewPort, context->getScene());

        renderer::Canvas canvas(context->getRenderer());
        canvas.setRect(Recti(viewPort.x, viewPort.y, viewPort.x + viewPort.width, viewPort.y + viewPort.height));
        canvas.fillRect(Rectf(0.02f, 0.02f, 0.98f, 0.15f), Color::YELLOW);
        canvas.drawText(Vector2(0.0f, 0.5f), "Hello, world!", Color::RED);

        glutSwapBuffers();
        glutPostRedisplay();

        model::Entity* camera = context->getScene()->getMainCamera();
        model::Entity* entity = context->getScene()->findEntity("cube");
        camera->setTransform(Matrix2Transform(TranslationMatrix(xpos, 0, 2 + xpos)));
        entity->setTransform(Matrix2Transform(RotationMatrix(xpos, 0, 1, 1)));
        xpos += 0.001f;
        if (xpos > 2.5f) {
            xpos = -0.5f;
        }

        auto t1 = high_resolution_clock::now();
        milliseconds total_ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
        //printf("FPS: %d\r", 1000 / (int)total_ms.count());
    }

    void reshape(int width, int height) {
        model::Entity* camera = context->getScene()->getMainCamera();
        float aspect = (float)width / height;
        camera->getComponent<model::Camera>().setPerspective(deg2rad(60.0f / (1.0f / aspect)), aspect, 0.01f, 10.0f);
        viewPort.x = 0;
        viewPort.y = 0;
        viewPort.width = width;
        viewPort.height = height;
    }

    void finalize() {
        delete context;
    }
}

#include "shared/pixmap.h"

int main(int argc, char** argv)
{
    Pixmap pix;
    pix.load("pngtest.png");
    pix.savePNG("test.png");

    atexit(finalize);

    context = Context::create();

    // Add a sample cube
    model::Entity* entity = new model::Entity("cube");
    model::MeshFactory::createCube(&entity->getComponent<model::Mesh>(), 1.0f);
    entity->setTransform(Matrix2Transform(TranslationMatrix(0, 0, -5)));
    context->getScene()->getRoot().addChild(entity);

    // Add a camera
    model::Entity* camera = new model::Entity("camera");
    camera->setTransform(Matrix2Transform(TranslationMatrix(0, 0, 2)));
    camera->getComponent<model::Camera>().setPerspective(deg2rad(60.0f), 1.0f, 0.01f, 10.0f);
    context->getScene()->getRoot().addChild(camera);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("editor");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    reshape(800, 600);

    glutMainLoop();

    return 0; 
}

