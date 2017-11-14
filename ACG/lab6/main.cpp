#include <GL/glut.h>

#define ENABLE_AMBIENT_LIGHT false
#define ROTATE_AMBIENT_LIGHT true

#define ENABLE_POINT_LIGHT true
#define ROTATE_POINT_LIGHT false

#define MOVE_LIGHT false


void display();
void keyInput(int key, int x, int y);
void initPointLight();
void initAmbientLight();

int rotate_x = 0, rotate_y = 0, rotate_z = 0;
float temp = 0;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cube");

    glClearColor (0.3, 0.3, 0.3, 0.0);
    glEnable(GL_LIGHTING);
//    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutSpecialFunc(keyInput);
    glutMainLoop();
    return 0;
}

void keyInput(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 3;

    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 3;

    else if (key == GLUT_KEY_UP)
        rotate_x += 3;

    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 3;
    else if (key == GLUT_KEY_F1)
        rotate_z -= 3;
    else if (key == GLUT_KEY_F2)
        rotate_z += 3;
    else if (key == GLUT_KEY_F3)
        temp -= 0.2;
    else if (key == GLUT_KEY_F4)
        temp += 0.2;

    glutPostRedisplay();
}

void initAmbientLight() {
    float light0_diffuse[] = {1.0, 1.0, 1.0};
    float light0_direction[] = {0.0, 0.0, 1.0f, 0.0};

    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);

}

void initPointLight() {
    GLfloat light1_diffuse[] = {1.0, 1.0, 1.0};
    GLfloat light1_position[] = {temp, 0.0, 1.0, 1.0};

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.9);

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    if (ENABLE_AMBIENT_LIGHT && !ROTATE_AMBIENT_LIGHT) {
        initAmbientLight();
    }
    if (ENABLE_POINT_LIGHT && !ROTATE_POINT_LIGHT) {
        initPointLight();
    }

    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    glRotatef( rotate_z, 0.0, 0.0, 1.0 );
//    glNormal3f(0.0, 0.0, 1.0);
    if (ENABLE_AMBIENT_LIGHT && ROTATE_AMBIENT_LIGHT) {
        initAmbientLight();
    }
    if (ENABLE_POINT_LIGHT && ROTATE_POINT_LIGHT) {
        initPointLight();
    }

    if (MOVE_LIGHT) {
        glLoadIdentity();
    }



    glBegin(GL_QUADS);

    // setting color
    GLfloat color[4] = { 1.f, 0.f, 0.f, 1.f };
    glMaterialfv( GL_FRONT, GL_DIFFUSE, color );

    glVertex3f(  0.3, -0.3f, -0.3f );
    glVertex3f(  0.3,  0.3, -0.3f );
    glVertex3f( -0.3f,  0.3, -0.3f );
    glVertex3f( -0.3f, -0.3f, -0.3f );

    GLfloat color1[4] = { 0.f, 1.f, 0.f, 1.f };
    glMaterialfv( GL_FRONT, GL_DIFFUSE, color1 );

    glVertex3f(  0.3, -0.3f, 0.3 );
    glVertex3f(  0.3,  0.3, 0.3 );
    glVertex3f( -0.3f,  0.3, 0.3 );
    glVertex3f( -0.3f, -0.3f, 0.3 );

    GLfloat color2[4] = { 0.f, 0.f, 1.f, 1.f };
    glMaterialfv( GL_FRONT, GL_DIFFUSE, color2 );

    glVertex3f( 0.3, -0.3f, -0.3f );
    glVertex3f( 0.3,  0.3, -0.3f );
    glVertex3f( 0.3,  0.3,  0.3 );
    glVertex3f( 0.3, -0.3f,  0.3 );

    GLfloat color3[4] = { 1.f, 1.f, 0.f, 1.f };
    glMaterialfv( GL_FRONT, GL_DIFFUSE, color3 );

    glVertex3f( -0.3f, -0.3f,  0.3 );
    glVertex3f( -0.3f,  0.3,  0.3 );
    glVertex3f( -0.3f,  0.3, -0.3f );
    glVertex3f( -0.3f, -0.3f, -0.3f );

    GLfloat color4[4] = { 0.f, 1.f, 1.f, 1.f };
    glMaterialfv( GL_FRONT, GL_DIFFUSE, color4 );

    glVertex3f(  0.3,  0.3,  0.3 );
    glVertex3f(  0.3,  0.3, -0.3f );
    glVertex3f( -0.3f,  0.3, -0.3f );
    glVertex3f( -0.3f,  0.3,  0.3 );

    GLfloat color5[4] = { 1.f, 1.f, 1.f, 1.f };
    glMaterialfv( GL_FRONT, GL_DIFFUSE, color5 );

    glVertex3f(  0.3, -0.3f, -0.3f );
    glVertex3f(  0.3, -0.3f,  0.3 );
    glVertex3f( -0.3f, -0.3f,  0.3 );
    glVertex3f( -0.3f, -0.3f, -0.3f );
    glEnd();

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);

    glFlush();
    glutSwapBuffers();
}

void draw() {

}
