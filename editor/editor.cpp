
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>

#include "context.h"
#include "editorUI.h"

#include "libdrawtext/src/drawtext.h"

#include "model/camera.h"
#include "model/entity.h"
#include "model/meshFactory.h"

#include "renderer/canvas.h"
#include "renderer/constants.h"

#include "shared/pixmap.h"

#include "ui/mouseEvent.h"
#include "ui/view/button.h"
#include "ui/view/imageView.h"
#include "ui/view/panel.h"
#include "ui/view/sceneView.h"
#include "ui/view/textView.h"

using namespace editor;

namespace {
    Context* context;
    model::ViewPort viewPort;
    struct dtx_font *font = nullptr;
    EditorUI editorUI;


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
        model::Entity* camera = context->getScene()->getMainCamera();
        float aspect = (float)width / height;
        camera->getComponent<model::Camera>().setPerspective(deg2rad(60.0f / (1.0f / aspect)), aspect, 0.01f, 10.0f);
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

        context->getUI()->addView(&editorUI);
        editorUI.setScene(context->getScene());

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

    // Add a camera
    model::Entity* camera = new model::Entity("camera");
    camera->setTransform(Matrix2Transform(TranslationMatrix(0.2f, 0.2f, 2) * RotationMatrix(deg2rad(60.0f), 0, -1, 0) * RotationMatrix(deg2rad(30.0f), -1, 0, 0)));
    camera->getComponent<model::Camera>().setPerspective(deg2rad(60.0f), 1.0f, 0.01f, 10.0f);
    context->getScene()->getRoot().addChild(camera);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("editor");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(motion);
    reshape(800, 600);

    glutMainLoop();

    return 0; 
}

