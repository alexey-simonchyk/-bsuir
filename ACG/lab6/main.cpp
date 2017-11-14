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
void drawConstZ(GLfloat z, float color[]);
void drawConstX(GLfloat x, float color[]);
void drawConstY(GLfloat y, float color[]);

int rotate_x = 0, rotate_y = 0, rotate_z = 0;

float no_mat[4] = {0.0f, 0.0f, 0.0f, 1.0f};
float mat_ambient[4] = {0.7f, 0.7f, 0.7f, 1.0f};
float mat_ambient_color[4] = {0.8f, 0.8f, 0.2f, 1.0f};
float mat_diffuse[4] = {0.1f, 0.5f, 0.8f, 1.0f};
float mat_specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float no_shininess = 0.0f;
float low_shininess = 5.0f;
float high_shininess = 100.0f;
float mat_emission[4] = {0.3f, 0.2f, 0.2f, 0.0f};


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cube");

    glClearColor (0.3, 0.3, 0.3, 0.0);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
//    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
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
    float sp[4] = {1,1,1,1};
    GLfloat light1_position[] = {0.0, 0.0, -1.6, 1.0};

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, sp);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.6);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.6);

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

    if (ENABLE_AMBIENT_LIGHT && ROTATE_AMBIENT_LIGHT) {
        initAmbientLight();
    }
    if (ENABLE_POINT_LIGHT && ROTATE_POINT_LIGHT) {
        initPointLight();
    }

    if (MOVE_LIGHT) {
        glLoadIdentity();
    }



//    float mat_diffuse[4] = {1.0, 1.0, 1.0, 1.0};

    drawConstY(0.5, mat_diffuse);
    drawConstY(-0.5, mat_diffuse);

    drawConstZ(0.5, mat_diffuse);
    drawConstZ(-0.5, mat_diffuse);

    drawConstX(0.5, mat_diffuse);
    drawConstX(-0.5, mat_diffuse);


    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);

    glFlush();
    glutSwapBuffers();
}

void drawConstZ(GLfloat z, float color[]) {
    glBegin(GL_QUADS);
    GLfloat x, y;

    if (z > 0) {
        glNormal3f(0.0, 0.0, 1.0);
    } else {
        glNormal3f(0.0, 0.0, -1.0);
    }

    for (x = -0.5; x < 0.5; x += 0.005)
    {
        for (y = -0.5; y < 0.5; y += 0.005)
        {
            if (z > 0) {
                glNormal3f(0.0, 0.0, 1.0);
            } else {
                glNormal3f(0.0, 0.0, -1.0);
            }
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
            glVertex3f(x, y, z);
            glVertex3f(x, y + 0.005, z);
            glVertex3f(x + 0.005, y + 0.005, z);
            glVertex3f(x + 0.005, y, z);
        }
    }
    glEnd();
}

void drawConstX(GLfloat x, float color[]) {
    glBegin(GL_QUADS);
    GLfloat z, y;

    if (x > 0) {
        glNormal3f(1.0, 0.0, 0.0);
    } else {
        glNormal3f(-1.0, 0.0, 0.0);
    }

    for (z = -0.5; z < 0.5; z += 0.005)
    {
        for (y = -0.5; y < 0.5; y += 0.005)
        {
            if (x > 0) {
                glNormal3f(1.0, 0.0, 0.0);
            } else {
                glNormal3f(-1.0, 0.0, 0.0);
            }
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
            glVertex3f(x, y, z);
            glVertex3f(x, y + 0.005, z);
            glVertex3f(x, y + 0.005, z + 0.005);
            glVertex3f(x, y, z + 0.005);
        }
    }
    glEnd();
}

void drawConstY(GLfloat y, float color[]) {
    glBegin(GL_QUADS);
    GLfloat x, z;

    if (y > 0) {
        glNormal3f(0.0, 1.0, 0.0);
    } else {
        glNormal3f(0.0, -1.0, 0.0);
    }

    for (x = -0.5; x < 0.5; x += 0.005)
    {
        for (z = -0.5; z < 0.5; z += 0.005)
        {
            if (y > 0) {
                glNormal3f(0.0, 1.0, 0.0);
            } else {
                glNormal3f(0.0, -1.0, 0.0);
            }
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
            glVertex3f(x, y, z);
            glVertex3f(x, y , z + 0.005);
            glVertex3f(x + 0.005, y, z + 0.005);
            glVertex3f(x + 0.005, y, z);
        }
    }
    glEnd();
}


