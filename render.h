//Paul mathai - project 3

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
using namespace std;
//radius in Mm
static float sunRadius = 6.95;
static float mercuryRadius = .02347;
static float venusRadius = .06051;
static float earthRadius = .06378;
static float marsRadius = .03387;
static float jupiterRadius = .714;
static float saturnRadius = .62;
static float uranusRadius = .24;
static float neptuneRadius = .24765;

static float moonRadius = .1;

//distance from sun
static float mercuryDistance = 7;
static float venusDistance = 10;
static float earthDistance = 13;
static float marsDistance = 18;
static float jupitorDistance = 48;
static float saturnDistance = 88;
static float uranusDistance = 188;
static float neptuneDistance = 288;

static float asteroidDistance = 25;


//angles
static float mercAngle = 0;
static float venusAngle = 0;
static float earthAngle = 0;
static float marsAngle = 0;
static float jupitorAngle = 0;
static float saturnAngle = 0;
static float neptuneAngle = 0;
static float uranusAngle = 0;




void drawScene(float blastRadius);

void drawScene2(float blastRadius);

void adjustPlanetsUp(void);
void adjustPlanetsDown(void);
void renderFloor(void);
void imageInit(void);
void fogInit(void);
void superNova(float size);
