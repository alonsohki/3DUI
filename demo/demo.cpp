
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>

#include "context.h"
#include "demoUI.h"

#include "libdrawtext/src/drawtext.h"

#include "model/camera.h"
#include "model/entity.h"
#include "model/meshFactory.h"

#include "renderer/canvas.h"
#include "renderer/constants.h"

#include "shared/pixmap.h"

#include "ui/mouseEvent.h"

using namespace demo;

namespace {
    Context* context;
    model::ViewPort viewPort;
    struct dtx_font *font = nullptr;
    DemoUI UI;


    void display() {
        context->getRenderer()->clear();

        renderer::Canvas canvas(context->getRenderer());
        canvas.setViewport(viewPort);
        canvas.setRect(Recti(viewPort.x, viewPort.y, viewPort.x + viewPort.width, viewPort.y + viewPort.height));
        context->getUI()->draw(&canvas);

        glutSwapBuffers();
        glutPostRedisplay();
    }

    void reshape(int width, int height) {
        viewPort.x = 0;
        viewPort.y = 0;
        viewPort.width = width;
        viewPort.height = height;
    }

    void mouse(int button, int state, int x, int y) {
        ui::MouseEvent event;
        switch (button) {
        case GLUT_LEFT_BUTTON:
            event.button = ui::MouseEvent::LEFT;
            break;
        case GLUT_MIDDLE_BUTTON:
            event.button = ui::MouseEvent::MIDDLE;
            break;
        case GLUT_RIGHT_BUTTON:
            event.button = ui::MouseEvent::RIGHT;
            break;
        default:
            return;
        }

        switch (state) {
        case GLUT_UP:
            event.state = ui::MouseEvent::UP;
            break;
        case GLUT_DOWN:
            event.state = ui::MouseEvent::DOWN;
            break;
        default:
            return;
        }

        event.position.x() = x;
        event.position.y() = y;

        context->getUI()->onMouseEvent(event);
    }

    void motion(int x, int y) {
        ui::MouseEvent event;
        event.position.x() = x;
        event.position.y() = y;
        event.state = ui::MouseEvent::MOVE;

        context->getUI()->onMouseEvent(event);
    }

    void finalize() {
        delete context;
    }

    bool createUI(ui::UI* ui) {
        if(!(font = dtx_open_font("tahoma.ttf", 14))) {
		    fprintf(stderr, "failed to open font\n");
		    return false;
	    }
        dtx_use_font(font, 14);

        context->getUI()->addView(&UI);
        UI.setContext(context);

        return true;
    }
}


int main(int argc, char** argv)
{
    atexit(finalize);

    context = Context::create();
    if (!createUI(context->getUI())) {
        return EXIT_FAILURE;
    }

    // Add a camera to the scene
    model::Entity* camera = new model::Entity("camera");
    camera->setTransform(Matrix2Transform(TranslationMatrix(0.2f, 0.2f, 2) * RotationMatrix(deg2rad(60.0f), 0, -1, 0) * RotationMatrix(deg2rad(30.0f), -1, 0, 0)));
    camera->getComponent<model::Camera>();
    context->getScene()->getRoot().addChild(camera);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("demo");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(motion);
    reshape(800, 600);

    glutMainLoop();

    return 0; 
}

