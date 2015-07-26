#include "render.h"
#include <SOIL/SOIL.h>


int floorSize = 50;
int floorLevel = -15;

int red = 1;
int green = 1;

//color
GLfloat yellowEmissiveMaterial[] = {1,1,0};
GLfloat redEmissiveMaterial[] = {1,0,0};
GLfloat blueEmissiveMaterial[] = {0,0,1};
GLfloat greenEmissiveMaterial[] = {0,1,0};
GLfloat orangeEmissiveMaterial[] = {.75,.25,0};
GLfloat whiteEmissiveMaterial[] = {1,1,1};
GLfloat juptierColor[] = {.8,.15,.0};
GLfloat saturnColor[] = {.9,.3,.0};


//textures
GLuint earthTexture;
GLuint marsTexture;
GLuint asteroidTexture;
GLuint grassTexture;
GLuint spaceTexture;

//sun settings
GLfloat sunPosition[] = {0,0,0};
GLfloat sundiffuse[] = {1,1,0,1};
GLfloat sunAmbient[] = {1,1,0,1};

//fog values
GLfloat fogDensity = .1;
GLfloat fogColor[4] = {.5,.5,.5,.5};


//GLfloat specular


void imageInit(){

     marsTexture = SOIL_load_OGL_texture(
        "assets/mars_texture.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );


//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    if( 0 == marsTexture )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result());
    }

    //glBindTexture(GL_TEXTURE_2D, marsTexture);

    earthTexture = SOIL_load_OGL_texture(
        "assets/earth_texture.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
	SOIL_FLAG_MIPMAPS
        
    );



    if( 0 == earthTexture )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result());
    }
    



     asteroidTexture = SOIL_load_OGL_texture(
        "assets/asteroid_texture.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );   


    grassTexture = SOIL_load_OGL_texture(
	"assets/grass_texture.jpg",
	SOIL_LOAD_AUTO,
	SOIL_CREATE_NEW_ID,
	SOIL_FLAG_INVERT_Y
    );

    spaceTexture = SOIL_load_OGL_texture(
	"assets/space_texture.jpg",
	SOIL_LOAD_AUTO,
	SOIL_CREATE_NEW_ID,
	SOIL_FLAG_INVERT_Y
    );



    printf("all images found\n");


}


void fogInit(void){
    glFogi(GL_FOG_MODE,GL_LINEAR);
    glFogfv(GL_FOG_COLOR,fogColor);
    glFogf(GL_FOG_DENSITY, fogDensity);
    glHint(GL_FOG_HINT,GL_NICEST);

}


void renderFloor(void){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,grassTexture);

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glBegin(GL_QUADS);
    glColor3f(0,.5,0);
    glTexCoord3f(-floorSize,floorLevel,floorSize);
    glVertex3f(-floorSize,	floorLevel,	floorSize); // The bottom left corner

    glTexCoord3f(-floorSize, floorLevel, -floorSize); 
    glVertex3f(-floorSize,	floorLevel,	-floorSize); // The top left corner

    glTexCoord3f(floorSize,floorLevel,	-floorSize);    
    glVertex3f(floorSize,	floorLevel,	-floorSize); // The top right corner
    
    glTexCoord3f(floorSize,floorLevel,floorSize);
    glVertex3f(floorSize,	floorLevel,	floorSize); // The bottom right corner
    
    glColor3f(1,1,1);
    glEnd(); 
    
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);
    

}

void drawScene(float blastRadius){


    //draw the Sun
    if(blastRadius < sunRadius){
	glColor3f(1,1,0);
//	glLightfv(GL_LIGHT0,GL_AMBIENT,sunAmbient);
	glLightfv(GL_LIGHT0,GL_POSITION,sunPosition);	
//	glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION, .8f);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,yellowEmissiveMaterial);
	glutSolidSphere(sunRadius,100,100);

    }
    //draw a planet

    glLightf(GL_FRONT_AND_BACK,GL_SHININESS,128);
    
    //mercury
    if(blastRadius < mercuryDistance-mercuryRadius){
	glPushMatrix();
	
	glTranslatef(mercuryDistance * sin(mercAngle),0 ,mercuryDistance * cos(mercAngle));
	glColor3f(1,0,0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,redEmissiveMaterial);
//	glColorMaterial(GL_FRONT_AND_BACK,GL_EMISSION);
	glutSolidSphere(mercuryRadius,25,25);
	glPopMatrix();
    }

    //venus
    if(blastRadius < venusDistance-venusRadius){
	glPushMatrix();
	glTranslatef(venusDistance * sin(venusAngle),0,venusDistance * cos(venusAngle));
	glColor3f(.8,.2,0);
	//how light interacts with model
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,orangeEmissiveMaterial);
//	glColorMaterial(GL_FRONT_AND_BACK,GL_EMISSION);
	glutSolidSphere(venusRadius,25,25);
	glPopMatrix();
    }

    //earth
    if(blastRadius < earthDistance-earthRadius){
	glPushMatrix();
	glTranslatef(earthDistance*sin(earthAngle),0,earthDistance * cos(earthAngle));
	glColor3f(0,0,1);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blueEmissiveMaterial);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, earthTexture);
	GLfloat earthPosition[] = {earthDistance*sin(earthAngle),0,earthDistance * cos(earthAngle)};
	glLightfv(GL_LIGHT1,GL_AMBIENT_AND_DIFFUSE,earthPosition);
	
	glutSolidSphere(earthRadius,25,25);	
	
	glDisable(GL_TEXTURE_2D);
	//create the moon
	glPushMatrix();
	    glTranslatef((earthRadius + earthRadius*.25)*sin(mercAngle+25),0,(earthRadius + earthRadius*.25)*cos(mercAngle+25));
	    glColor3f(.9,.9,.9);
//	    glColorMaterial(GL_FRONT_AND_BACK, whiteEmissiv
	    glutSolidSphere(earthRadius/10,24,25);
	    glPopMatrix();
	glPopMatrix();
    }

    //mars
    if(blastRadius < marsDistance-marsRadius){
	glPushMatrix();
	glTranslatef(marsDistance * sin(marsAngle),0,marsDistance * cos(marsAngle));
	glColor3f(1,0,0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,redEmissiveMaterial);
	glutSolidSphere(marsRadius,25,25);
	//moon 1
	glPushMatrix();

	glTranslatef((marsRadius + (marsRadius*.25))*sin(marsAngle+25),0,(marsRadius + (marsRadius*.25))*cos(marsAngle+25));
	glColor3f(.9,.9,.9);
	glutSolidSphere(marsRadius/10,24,25);
	glPopMatrix();	
	//moon 2
	glPushMatrix();
	glTranslatef((marsRadius + (marsRadius*.25))*sin(mercuryRadius+25),(marsRadius + (marsRadius*.25))*cos(mercuryRadius+25),0);
	glColor3f(.9,.9,.9);
	glutSolidSphere(marsRadius/10,24,25);
	glPopMatrix();

	glPopMatrix();
    }

    //asteroid belt
    if(blastRadius < asteroidDistance){

	glEnable(GL_TEXTURE_2D);
	glColor3f(.5,.2,.1);
	for(int circle = 0; circle <= 360; circle+= 36)
	{
	    glPushMatrix();	    
	    glTranslatef(asteroidDistance*cos(circle),0,asteroidDistance*sin(circle));
	     
	    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,yellowEmissiveMaterial);
	    glBindTexture(GL_TEXTURE_2D, earthTexture);

	    glutSolidTeapot(1.5);
	    glPopMatrix();


	}
    
	glDisable(GL_TEXTURE_2D);
 

    }



    //jupiter
    if(blastRadius < jupitorDistance-jupiterRadius){
	glPushMatrix();
	glTranslatef(jupitorDistance * sin(jupitorAngle),0,jupitorDistance * cos(jupitorAngle));
	glColor3f(.8,.15,0);

	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,juptierColor);
	glutSolidSphere(jupiterRadius,25,25);
	//moon 1 
	glPushMatrix();
	    glTranslatef((jupiterRadius +jupiterRadius*.25)*sin(mercAngle),(jupiterRadius + jupiterRadius*.25)*cos(mercAngle),0);
	    glColor3f(1,1,0);
	    glutSolidSphere(jupiterRadius/15,10,14);
	    glPopMatrix();
	//moon 2
	glPushMatrix();
	    glTranslatef(((jupiterRadius + jupiterRadius*.5)*sin(mercAngle)),0,(jupiterRadius + jupiterRadius*.5)*cos(mercAngle));
	    glColor3f(1,1,0);
	    glutSolidSphere(jupiterRadius/15,10,8);
	    glPopMatrix();
	glPopMatrix();

    }

    //saturn
    if(blastRadius < saturnDistance-saturnRadius){

	glPushMatrix();
	glTranslatef(saturnDistance*sin(saturnAngle), 0, saturnDistance*cos(saturnAngle));
	glColor3f(.9,.3,0);
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,saturnColor);	
	glutSolidSphere(saturnRadius,25,25);
	glPopMatrix();
    }

    //uranus
    if(blastRadius < uranusDistance-uranusRadius){
	glPushMatrix();
	glTranslatef(uranusDistance * sin(uranusAngle),0,uranusDistance * cos(uranusAngle));
	glColor3f(0,0,.8);
	glutSolidSphere(uranusRadius,25,25);
	glPopMatrix();
    }
    
    //neptune
    if(blastRadius < neptuneDistance-neptuneRadius){
	glPushMatrix();
	glTranslatef(neptuneDistance * sin(neptuneAngle),0,neptuneDistance * cos(neptuneAngle));
	glColor3f(0,0,.4);
	glutSolidSphere(neptuneRadius, 24,24);
	glPopMatrix();
    }

    mercAngle += .005;
    venusAngle += .001;
    earthAngle += .0008;
    marsAngle += .0005;
    jupitorAngle += .0004;
    saturnAngle += .0003;
    uranusAngle += .0002;
    neptuneAngle += .0001;

}

void superNova(float size){
    glPushMatrix();
    glDisable(GL_FOG);
    float blastRadius = 2+size+.05;
    drawScene(blastRadius);
    glColor3f(.8,0,0);
    glRotatef(90,1,0,0);
    glutSolidTorus(2,2+size+.05,25,25);
    glRotatef(-90,1,0,0); 
    glPopMatrix();

}


void adjustPlanetsUp(void){

sunRadius = 5;
mercuryRadius = .02347 * 10;
venusRadius = .06051 * 10;
earthRadius = .06378 * 10;
marsRadius = .03387 * 10;
jupiterRadius = .514 * 10;
saturnRadius = .42 * 10;
uranusRadius = .24 * 10;
neptuneRadius = .24765 * 10;



}

void adjustPlanetsDown(void){

sunRadius = 6.95;
mercuryRadius = .02347;
venusRadius = .06051;
earthRadius = .06378;
marsRadius = .03387;
jupiterRadius = .714;
saturnRadius = .62;
uranusRadius = .24;
neptuneRadius = .24765;


}
