//paul mathai - cg project 4

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <string.h>
#include "render.h"

using namespace std;

//inits
int windowX = 1280;
int windowY = 800;
//initial position
GLfloat init_y_pos = 5, init_x_pos = 0, init_z_pos = 60;
GLfloat init_y_rot = 0, init_x_rot = 0;
//GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; //set thelight specular to white
//GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0}; //set the light ambient to black
//GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0}; //set the diffuse light to white


int firstClick = 0;

int centerRotation = 0;

GLfloat angle = 0.0;
GLfloat x_position = init_x_pos;
GLfloat y_position = init_y_pos;
GLfloat z_position = init_z_pos;
GLfloat x_rotation = init_x_rot;
GLfloat y_rotation = init_y_rot;

GLfloat drag_x_origin, drag_y_origin;
int dragging = 0;

//frames counter
int frameCount = 0, FPS = 0; 

long previousTime = 0, currentTime = 0;;


//double xdiff = 0, ydiff = 0;
float  lastx = 0, lasty = 0;


bool mouseDown, mouseDisable = false;

//project 4 toggles
bool fogToggle = false;
bool lightingToggle = true;

bool superNovaBOOM = false;
float superNovaSize = 0;


bool diffuse = false;
bool emissive = false;
bool specular = false;

void reset(void){
    //reset position
    x_position = init_x_pos;
    y_position = init_y_pos;
    z_position = init_z_pos;
    //reset rotation
    x_rotation = init_x_rot;
    y_rotation = init_y_rot;

    firstClick = 0;

    superNovaSize = 0;
    superNovaBOOM = false;
}

void init (void) {
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);
//    glEnable(GL_TEXTURE_2D);

    imageInit();
    fogInit();
}



void camera(void){


/*    if(y_rotation > 180)
	y_rotation = 180;
    if(y_rotation < -180)
	y_rotation = -180;
*/
    glRotatef(x_rotation,1,0,0); //angle, x, y, z
    glRotatef(y_rotation,0,1,0);
    glTranslatef(-x_position,-y_position,-z_position);

    if(centerRotation)
        glTranslatef(-x_position,-y_position,-z_position);

//    gluLookAt(-x_position,-y_position,z_position,0,0,0,0,1,0);

}




void light(void){

    //glLightfv(GL_LIGHT0,GL_SPECULAR, whiteSpecularLight);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
    //glLightfv(GL_LIGHT0,GL_DIFFUSE,whiteDiffuseLight);
}

void display (void) {
    glClearColor (0.0,0.0,0.0,1.0);
    
//    glViewport(0,0,windowX,windowY);
    glLoadIdentity();
    //draw main screen
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glLoadIdentity(); 
   
//    light();
    camera();
    if(!superNovaBOOM)
    {
	//draw floor 
	renderFloor();
	//drawthe Scene
	drawScene(0);
    }
    else
    {
	superNovaSize += .01;
	superNova(superNovaSize);
    }



    
    glutSwapBuffers();
}

void reshape (int w, int h) {
  
    printf("reshape called\n");
    windowX = w;
    windowY = h;  

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (45, (GLfloat)w / (GLfloat)h, 1, 1000.0);
    glMatrixMode (GL_MODELVIEW);
 
}

void keyboard (unsigned char key, int x, int y) {
    
    printf("xrotation = %f and yrotation = %f\n", x_rotation,y_rotation);
    printf("x_position = %f and y_position = %f and z_position = %f\n", x_position, y_position, z_position); 
    switch(key){
	//s
	case 's':
	
	    printf("move back\n");
	    GLfloat xrotrad, yrotrad;
	    yrotrad = (y_rotation / 180 * 3.141592654f);
	    xrotrad = (x_rotation / 180 * 3.141592654f); 
//	    if(y_rotation < 180){
		x_position -= GLfloat(sin(yrotrad/2));
		z_position += GLfloat(cos(yrotrad/2)) ;
		y_position += GLfloat(sin(xrotrad/2));
//	    }else{
//		x_position += GLfloat(sin(yrotrad/2));
//		z_position -= GLfloat(cos(yrotrad/2)) ;
//		y_position -= GLfloat(sin(xrotrad/2));
//
//	    }


	    break;
	case 'w':

	    printf("move forward\n");
	    yrotrad = (y_rotation / 180 * 3.141592654f);
	    xrotrad = (x_rotation / 180 * 3.141592654f); 
//	    if(y_rotation < 180){
		x_position += GLfloat(sin(yrotrad/2)) ;
		z_position -= GLfloat(cos(yrotrad/2)) ;
		y_position -= GLfloat(sin(xrotrad/2)) ;
//	    }else{
//		x_position -= GLfloat(sin(yrotrad/2)) ;
//		z_position += GLfloat(cos(yrotrad/2)) ;
//		y_position += GLfloat(sin(xrotrad/2)) ;
//
//	    }
	    break;
	//d 
	case 'd':
	    printf("move right\n");
/*	    y_rotation += 1;
	    if(y_rotation > 360)
		y_rotation -= 360;*/

	    yrotrad = (y_rotation/180 * 3.14159);
	    x_position +=1;// float(cos(yrotrad))*.2;
//	    y_position +=1;// float(sin(yrotrad))*.2;
	    break;


	case 'a':
	    printf("move left\n");
/*	    y_rotation -= 1;
	    if(y_rotation < -360)
		y_rotation += 360;*/
	    yrotrad = (y_rotation/180 * 3.14159);
	    x_position -= float(cos(yrotrad))*.2;
	    y_position -= float(sin(yrotrad))*.2;
	    break;
    	case(32):
	    y_position += 1;
	    break;
	case 'z':
	    printf("move down\n");
	    y_position -= 1;
	    break;
	case('r'):
	    printf("reset\n");
	    reset();
	    break;
	case('l'):

	    lightingToggle = !lightingToggle;


	    if(lightingToggle){
		printf("enabling light\n");
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
	    }
	    else{
		printf("disable lighting\n");
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
	    }
	    break;
	case('f'):

	    //toggle fog
	    fogToggle = !fogToggle;
	    if(fogToggle)
		glEnable(GL_FOG);
	    else
		glDisable(GL_FOG);
	    break;
	case('1'):
	    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	    break;
	case('2'):
	    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	    break;
	case('3'):
	    //toggle center rotation
	    centerRotation ^=1;
	    reset();
	    firstClick = 0;
	    break;
	case('4'):
	    adjustPlanetsDown();
	    break;
	case('5'):
	    adjustPlanetsUp();
	    break;
	case('6'):
	    mouseDisable ^= 1;
	    break;
/*	case('7'):
        if (specular==false)
        {
            specular = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, 
whiteSpecularMaterial);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
        }
        else if (specular==true)
        {
            specular = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blankMaterial);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, 
blankMaterial);
        }
	    break;
	case('8'):
        if (diffuse==false)
        {
            diffuse = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redDiffuseMaterial);
        }
        else if (diffuse==true)
        {
            diffuse = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
        }
	    break;
	case('9'):

        if (emissive==false)
        {
            emissive = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, greenEmissiveMaterial);
        }
        else if (emissive==true)
        {
            emissive = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blankMaterial);
        }
	    break;
*/
	case(27):
	case('q'):
	    exit(0);
	    break;
	default:
	    printf("keypress is %c\n", key);
    }
}

void mouse(int button, int state, int x, int y){
    if(button == 3)
	keyboard('w',1,1);
    if(button == 4)
	keyboard('s',1,1);

    if(button == GLUT_RIGHT_BUTTON){
	superNovaBOOM=true;
    }

    if(button == GLUT_LEFT_BUTTON)// && state == GLUT_DOWN)
    {
	dragging = 1;
        drag_x_origin = x;
        drag_y_origin = y;

    }else{
	dragging = 0;
    }
}

void mouseMotion(int x, int y){
    printf("MOUSE: xrotation = %f and yrotation = %f\n", x_rotation,y_rotation);
    printf("MOUSE x_position = %f and y_position = %f and z_position = %f\n", x_position, y_position, z_position); 
    if(!mouseDisable){ 
	if(dragging){
	    x_rotation += (y - drag_y_origin)*0.3;
	    y_rotation += (x - drag_x_origin)*0.3;
	    drag_x_origin = x;
	    drag_y_origin = y;
     
    

	}
    }
}


void Timer(int extra){
    glutPostRedisplay();
    glutTimerFunc(30,Timer,0);

}



int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (windowX, windowY);
    glutCreateWindow("the first window");
    init();
    glutDisplayFunc (display);
    glutIdleFunc (display);

    glutTimerFunc(0,Timer,0);

    //keyboard functions
    glutKeyboardFunc(keyboard);
    
    //mouse functions
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    adjustPlanetsUp();
    //start in wireframe 
//    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glutReshapeFunc(reshape);
    glutMainLoop ();
    return 0;
}
