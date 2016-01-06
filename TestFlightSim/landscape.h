//
//  landscape.h
//  TestFlightSim
//
//  Created by Matthew Knox on 3/8/15.
//  Copyright (c) 2015 mpknox2. All rights reserved.
//

// Landscape class, representative of the world in which you fly around

#ifndef LANDSCAPE_H_
#define LANDSCAPE_H_

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <cmath>
#include <random>

/* Some Colors  */
static GLfloat bl[] = {0.1, 0.48, 0.91, 1};
static GLfloat g[] = {0.0, 1.0, 0.0, 1.0};
static GLfloat dG[] = {0, 0.45, 0.24, 1};
static GLfloat brn[] = {0.5, 0.5, 0.0, 1.0};
static GLfloat lBrn[] = {0.61, 0.64, 0.3, 1};
static GLfloat gry[] = {0.6, 0.6, 0.6, 1.0};
static GLfloat frstG[] = {0.4, 0.8, 0.5, 1.0};
static GLfloat wh[] = {0.8, 0.23, 0.95, 1};
static GLfloat pnk[] = {1, 0.16, 0.97, 1};

class Landscape {
    int rows;
    int columns;
    double highest;                         // the highest point in the mesh
    std::vector< std::vector<double>  > d;  // the grid of elevations
    int solidId;                            // display list id for solid mesh
    static double unused;
    void generate(int x1, int y1, int x2, int y2, double rug);
    double scale(double x) {return x * (((double)rand()/RAND_MAX) - 0.5);}
    void drawTriangle(int x1, int z1, int x2, int z2, int x3, int z3);
    void vertex(double x, double z);
    void createSolidDisplayList();
    void createWireFrameDisplayList();
public:
    Landscape(int rows, int columns);
    void create(double rug);
    void draw() {glCallList(solidId);}
};

#endif