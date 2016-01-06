//
//  fly.cpp
//  TestFlightSim
//
//  Created by Matthew Knox on 3/8/15.
//  Copyright (c) 2015 mpknox2. All rights reserved.
//
//
// The Main entrance for the Flight Simulator

#include "glew.h"
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "cockpit.h"
#include "landscape.h"
#include <iostream>

// A landscape to fly around
Landscape landscape(800, 800);

static const double angle = 0.08;

void newLandscape() {
    static double rug = ((double)rand()) / RAND_MAX;
    landscape.create(rug);
}

static const unsigned char NEW_LANDSCAPE_KEY = 'r';
static const unsigned char HARD_RIGHT_KEY = '/';
static const unsigned char HARD_LEFT_KEY = '.';

static Ship theShip(Point(60, 40, 220));

/** camera representation */
static Cockpit cockpit(theShip);

void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case NEW_LANDSCAPE_KEY: newLandscape();
            break;
        case HARD_RIGHT_KEY:    theShip.yaw(-2*angle);
            break;
        case HARD_LEFT_KEY:     theShip.yaw(2*angle);
            break;
        case  27:               exit(0);
            break;
    }
}

void specialKeyboard(int k, int x, int y)
{
    switch (k)
    {
        case GLUT_KEY_UP:       theShip.pitch(-angle);
            break;
        case GLUT_KEY_DOWN:     theShip.pitch(angle);
            break;
        case GLUT_KEY_RIGHT:    theShip.roll(-angle);
            break;
        case GLUT_KEY_LEFT:     theShip.roll(angle);
            break;
    }
    
}

// OpenGL display() function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    landscape.draw();
    cockpit.draw();
    glFlush();
    glutSwapBuffers();
}

// OpenGL timer() call-back function
void timer(int v)
{
    theShip.fly();
    Point eye(theShip.getPosition());
    Point at(theShip.getPosition() + theShip.getDirection());
    Vector up(theShip.getVertical());
    glLoadIdentity();
    gluLookAt(eye.x, eye.y, eye.z, at.x, at.y, at.z, up.i, up.j, up.k);
    glutPostRedisplay();
    glutTimerFunc(1000/30, timer, v);
}

// OpenGL reshape() call-back function
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 0.05, 300.0);
    glMatrixMode(GL_MODELVIEW);
}

// init(): GLUT initialization
void init()
{
    srand(9903);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    newLandscape();
    cockpit.create();
    GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat dark[] = { 0.2, 0.15, 0.2, 1.0 };
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat direction[] = { 0.2, 1.0, 0.5, 0.0 };
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, dark);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, black);
    glLightfv(GL_LIGHT0, GL_POSITION, direction);
    
    // Let there be light!
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

// Writes some trivial help text to the console.
void writeHelpToConsole()
{
    std::cout << "left/right arrow keys = roll left / right\n";
    std::cout << "up/down arrow keys - pitch down / up\n";
    std::cout << "r - generate a new landscape\n";
}

// main(): Initialize GLUT and enter the GLUT event loop.
int main(int argc, char** argv) {
    writeHelpToConsole();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(780, 500);
    glutCreateWindow("Flight Simulator");
    glutReshapeFunc(reshape);
    glutTimerFunc(100, timer, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    init();
    glutMainLoop();
}
