#include <Windows.h>


#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <GL/freeglut.h>


#include <gl/glut.h>


#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280


#define WINDOW_X_OFFSET 100
#define WINDOW_Y_OFFSET 100

#define PLANE_SIZE 20
#define TEXTURE_OFFSET 2

#define MAX_TEXTURE_SIZE 20


//variables

int displayX = 0, displayY = 0;
float occlusion = 1;
int cuts = 12;
GLfloat whiteColor[] = { 1., 1., 1. };
GLfloat blackColor[] = { 0., 0., 0. };


GLubyte floorTexture[MAX_TEXTURE_SIZE][MAX_TEXTURE_SIZE][4];
GLfloat ambient0[] = { 0.1, 0.1, 0.1, 1.0 };



//in elephant there is neded some worke

//Elephant var 
float offcet1 = 1., deg = 270, legLength = 1.7;
float elephantX = 5, elephantY =   offcet1 * .025, elephantZ = 0;
GLfloat elephantColor[] = { .196078 , .6, .8 };
GLfloat elephantColorLighter[] = { .439216 , .858824 , .576471 };

float moveHead = 1, moveTail = 1;
float elephantScale = 3;
float legSwing = 0, headTilt = 0;
float tailDeg = 0;
float hTilt = 0;
float offcet2 = offcet1 * .65;
float handsSize = .20;

// Camera
float camX = 0;
float camY = 5;
float camDist = 40;


// Ball Light
float ballX = 5, ballY = 5, ballZ = 5;
float lightX = ballX, lightY = ballY, lightZ = ballZ;
float degbox = 0;
float toggleLight = 1;


// Lamp
float lampHeight = 7, lampRadius = 0.1;
float lampX = -5, lampY = -legLength, lampZ = 5, lightDeg = 0;
float toggleLamp = 1;
GLfloat lampColor[] = { 1.2, .97, .25, 1 };

// Floor
float floorX = -PLANE_SIZE / 2;
float floorY = -legLength - .5;
float floorZ = -PLANE_SIZE / 2;

// Table and Cair
float tableX = 0, tableY = -7.5, tableZ = -5.;
float chairX = tableX, chairY = tableY + 5. ,chairZ = tableZ +5.;
float tableScale = 1.2;

// Tea Pot
float potdeg = 0;



//needs more work
//Side bar
void renderSideBar()
{


	glViewport(displayX * 2 / 3, 0, displayX / 3, displayY);

	const unsigned char str[] = "\n       help bar      \n\nFor controls use the num pad\nand lowercase letters\n\nPress '0' to exit\n\nElephant control:\nFor movment use (w,s,a,d)\nFor rotation use (q,e)\nTail movment controld by (1)\nHead movment controld by (5)\n\nCamera controld by (i,j,k,l,u,o)\n\nLight position controld by (2,8,4,6,+,-)\nLight on and of (3)\nAmbiant light controld by (z,x)\n\nLamp on and of (7)\n";

	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glColor3fv(whiteColor);


	glRasterPos2f(-.5, .9);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, str);

	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}


//Light
void enableLight()
{


	if (toggleLight)
	{
		GLfloat pos1[] = { ballX, ballY, ballZ, 1 };

		glLightfv(GL_LIGHT0, GL_POSITION, pos1);
	}
	else
	{
		GLfloat pos1[] = { lightX, lightY, lightZ, 1 };
		glLightfv(GL_LIGHT0, GL_POSITION, pos1);
	}

	if (toggleLight)
	{

		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01);
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.2);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2 + .1 * sin(degbox / 70));
		glEnable(GL_LIGHT0);
	}
	else glDisable(GL_LIGHT0);

	if (toggleLamp)
	{
		GLfloat lampCoord[] = { lampX, lampY + lampHeight, lampZ, 1 };
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lampColor);
		glLightfv(GL_LIGHT1, GL_SPECULAR, lampColor);
		glLightfv(GL_LIGHT1, GL_POSITION, lampCoord);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, .01);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, .05);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, .05);
		glLightf(GL_LIGHT1, GL_SHININESS, 158);
		glEnable(GL_LIGHT1);
	}
	else glDisable(GL_LIGHT1);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
}

//Vector multiplire withe const
void vectorXconstant(GLfloat source[], float conatsnt, GLfloat dest[])
{


	for (int i = 0; i < 4; i++)
		dest[i] = source[i] * (conatsnt);
}

//New material function
void newMaterial()
{


	GLfloat _0[] = { 0, 0, 0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, _0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, _0);
	glMaterialf(GL_FRONT, GL_SHININESS, 0);
}

//Sets occlusion
void setOcclusion(GLfloat dff[])
{


	GLfloat amb[4];
	vectorXconstant(dff, occlusion, amb);
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dff);
}

//Sets shiness to object
void setShine(float shine)
{

	glMaterialf(GL_FRONT, GL_SHININESS, shine);
}

//Sets specular lighting component
void setSpecular(GLfloat specular[])
{


	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
}

//Floor 

void renderFloor()
{


	GLfloat matColor[] = { .29, .63, .74, 0 };
	glPushMatrix();

	glTranslatef(floorX, floorY, floorZ);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, PLANE_SIZE, PLANE_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, floorTexture);
	glEnable(GL_TEXTURE_2D);

	newMaterial();
	setOcclusion(matColor);
	setShine(160);
	setSpecular(matColor);
	GLfloat spec[4];
	vectorXconstant(matColor, 0.7, spec);


	for (int counterY = 0; counterY < PLANE_SIZE; counterY++)
		for (int counterX = 0; counterX < PLANE_SIZE; counterX++)
		{
			glNormal3f(0, 1, 0);
			int axisX = counterX * TEXTURE_OFFSET, axisXOffset = axisX + TEXTURE_OFFSET;
			int axisY = counterY * TEXTURE_OFFSET, axisYOffset = axisY + TEXTURE_OFFSET;

			glBegin(GL_TRIANGLES);
			glTexCoord2f((float)axisX / (float)PLANE_SIZE, (float)axisY / (float)PLANE_SIZE); glVertex3f(axisX, 0., axisY);
			glTexCoord2f((float)axisXOffset / (float)PLANE_SIZE, (float)axisY / (float)PLANE_SIZE); glVertex3f(axisXOffset, 0., axisY);
			glTexCoord2f((float)axisX / (float)PLANE_SIZE, (float)axisYOffset / (float)PLANE_SIZE); glVertex3f(axisX, 0., axisYOffset);
			glEnd();

			glBegin(GL_TRIANGLES);
			glTexCoord2f((float)axisX / (float)PLANE_SIZE, (float)axisYOffset / (float)PLANE_SIZE); glVertex3f(axisX, 0., axisYOffset);
			glTexCoord2f((float)axisXOffset / (float)PLANE_SIZE, (float)axisY / (float)PLANE_SIZE); glVertex3f(axisXOffset, 0., axisY);
			glTexCoord2f((float)axisXOffset / (float)PLANE_SIZE, (float)axisYOffset / (float)PLANE_SIZE); glVertex3f(axisXOffset, 0., axisYOffset);
			glEnd();

		}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

//Making texture for floor rendering
void createTexture()
{


	for (int i = 0; i < MAX_TEXTURE_SIZE; i++)
		for (int j = 0; j < MAX_TEXTURE_SIZE; j++)
		{
			float color = 105 * ((i + j) % 5) + 150;

			floorTexture[i][j][0] = (GLubyte)color;
			floorTexture[i][j][1] = (GLubyte)color;
			floorTexture[i][j][2] = (GLubyte)color;
			floorTexture[i][j][3] = 255;
		}
}

//Takes care of head oriantation 
void elephantHeadRotate(float pos[], bool translate)
{

	if (translate) glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(35 * sin(hTilt / 200), 0, 1, 0);
	glRotatef(15 * cos(hTilt / 350), 0, 0, 1);
	if (translate) glTranslatef(-pos[0], -pos[1], -pos[2]);
}

//Renders elephant body
void renderelEphantBody(bool isHead, float hands[], float x, float y, float z, float rad)
{


	glPushMatrix();
	if (isHead)
		elephantHeadRotate(hands, true);
	glTranslatef(x, y, z);
	glutSolidSphere(rad, cuts, cuts);
	glPopMatrix();
}

//All the cones on the elephant 
void renderElephantCone(bool isTail, float dPos[], float x, float y, float z, float rad_1, float rad_2)
{

	glPushMatrix();
	if (!isTail)elephantHeadRotate(dPos, true);
	glTranslatef(x, y, z);
	if (isTail)
	{
		glRotatef(15 * cos(tailDeg / 25), 0, 0, 1);
		glRotatef(45, 0, 0, 1);
		glRotatef(-90, 1, 0, 0);

		if (moveTail)
			tailDeg++;
	}
	else
	{
		glRotatef(-90, 1, 0, 0);
		glRotatef(20, 0, 1, 0);
	}
	glutSolidCone(rad_1, rad_2, cuts, cuts);
	glPopMatrix();
}

//Render sphere for elephant
void renderElephantSphere(bool isHead, float dPos[], float x, float y, float z, float rad)
{


	glPushMatrix();
	if (isHead)
		elephantHeadRotate(dPos, true);
	glTranslatef(x, y, z);
	glutSolidSphere(rad, cuts, cuts);
	glPopMatrix();
}

//Renders the legs of the elephant
void renderElephantLeg(int front, int right)
{


	float lx = elephantX + ((front == 1) ? .2*offcet1 : -1.2*offcet1);
	float lz = elephantZ + .4*offcet1 * ((right == 1) ? 1 : -1);
	float legRadius = offcet1 * .3;

	glPushMatrix();
	glTranslatef(lx, elephantY, lz);
	glRotatef(20 * sin(legSwing / 100) * ((right == 1) ? 1 : -1) * ((front == 1) ? 1 : -1), 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(legRadius, legLength, cuts, cuts);
	glTranslatef(-.05, 0, 0);
	glutSolidCylinder(legRadius / 2., legLength, cuts, cuts);
	glTranslatef(.04, 0, offcet2 + legLength * .6);
	setOcclusion(elephantColorLighter);
	glutSolidSphere(handsSize, cuts, cuts);
	setOcclusion(elephantColor);
	glPopMatrix();
}

//Renders elephant Ears 
void elephantEears(bool isHead, float dPos[], float x, float y, float z, float rad)
{

	glPushMatrix();



	if (isHead)
		elephantHeadRotate(dPos, true);
	glTranslatef(x, y, z);


	glScalef(1, 20, 15);

	setOcclusion(elephantColorLighter);


	glutSolidSphere(rad, cuts , cuts );


	setOcclusion(elephantColor);




	glPopMatrix();
}

//Renders elephant trunk
void elephantTrunk(bool isHead, float dPos[], float x, float y, float z, float rad)
{

	glPushMatrix();
	if (isHead)
		elephantHeadRotate(dPos, true);
	glTranslatef(x, y, z);
	

	glScalef(4, 1, 1);
	setOcclusion(elephantColorLighter);

	glutSolidSphere(rad, cuts, cuts);
	

	setOcclusion(elephantColor);




	glPopMatrix();
}

//Elephant render function
void renderelElephant()
{

	float px2 = elephantX + offcet1 * .6;
	float py2 = elephantY + offcet1 * 1.2;
	float pz2 = elephantZ;
	float dPos[] = { px2, py2, pz2 };

	newMaterial();
	setOcclusion(elephantColor);

	glPushMatrix();
	
	glScalef(elephantScale, elephantScale, elephantScale);
	
	glTranslatef(0, elephantY + offcet1, 0);
	glTranslatef(elephantX, elephantY, elephantZ);
	glRotatef(deg, 0., 1, 0);
	glTranslatef(-elephantX, -elephantY, -elephantZ);


	// Front body
	renderelEphantBody(false, dPos, elephantX - offcet1 * 0.5, elephantY + offcet1 * .1, elephantZ, offcet1*1.2);

	// Head	
	glPushMatrix();
	glTranslatef(px2, py2 - offcet1, pz2);
	elephantHeadRotate(dPos, false);
	glutSolidSphere(offcet2, cuts, cuts);
	glPopMatrix();

	// Ears
	float earOffsetZ = offcet2 * .45;
	float earOffsetY = py2 + offcet2 * .5;

	elephantEears(false, dPos, px2, earOffsetY - offcet1 * 1.3, pz2 + earOffsetZ * 1.8, offcet1 * .05);
	elephantEears(false, dPos, px2, earOffsetY - offcet1 * 1.3, pz2 - earOffsetZ * 1.8, offcet1 * .05);

	// trunk
	float facePlaceX = px2 + offcet1 * 2 / 4;
	elephantTrunk(true, dPos, facePlaceX, py2 - offcet1 / 5 - offcet1, pz2, offcet2 / 2);

	// Eyes
	float eyeOffsetZ = offcet2 * .35;
	float eyeOffsetY = py2 + offcet2 * .2;

	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	renderElephantSphere(true, dPos, facePlaceX, eyeOffsetY - offcet1, pz2 + eyeOffsetZ, offcet2 / 7);
	renderElephantSphere(true, dPos, facePlaceX, eyeOffsetY - offcet1, pz2 - eyeOffsetZ, offcet2 / 7);
	glEnable(GL_LIGHTING);



	float div = .2;
	float offcet3 = offcet1 * (1 - div);

	// Legs
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			renderElephantLeg(i, j);

	// Tail
	setOcclusion(elephantColor);
	renderElephantCone(true, dPos, elephantX - offcet1 - offcet3 / 2, elephantY + offcet1 * 3 / 4, elephantZ, offcet1 * .3 * .7, legLength*.5);

	glPopMatrix();

	if (moveHead)
		hTilt++;
}


//Light cube render 
void renderBall()
{

	if (!toggleLight)
		return;

	glPushMatrix();


	glTranslatef(ballX, ballY, ballZ);
	glRotatef((degbox) / 15., 0., 1, 0);
	glRotatef(sin(degbox / 250)*45., 1, 0, 1);
	glTranslatef(-ballX, -ballY, -ballZ);

	glColor3f(1, 1, 1);
	glTranslatef(ballX, ballY, ballZ);
	glDisable(GL_LIGHTING);
	glutSolidSphere(0.1 + 0.05 * sin(degbox / 70), 6, 6);

	glEnable(GL_LIGHTING);

	glPopMatrix();

	degbox++;

}

//Renders Chair
void renderChair()
{


	glPushMatrix();

	newMaterial();
	GLfloat chairColor[] = { .55, .47 , .14 }; 
	setOcclusion(chairColor);

	glTranslatef(tableX, tableY+7, tableZ);

	glBegin(GL_QUADS);

	//Front
	glNormal3f(0, 0, 1.);
	glVertex3f(-2., -.2, 2.);
	glVertex3f(2., -.2, 2.);
	glVertex3f(2., .2, 2.);
	glVertex3f(-2., .2, 2.);

	//Right
	glNormal3f(1., 0, 0);
	glVertex3f(2., -.2, -2.);
	glVertex3f(2., .2, -2.);
	glVertex3f(2., .2, 2.);
	glVertex3f(2., -.2, 2.);

	//Back
	glNormal3f(0, 0, -1.);
	glVertex3f(-2., -.2, -2.);
	glVertex3f(-2., .2, -2.);
	glVertex3f(2., .2, -2.);
	glVertex3f(2., -.2, -2.);

	//Left
	glNormal3f(-1., 0, 0);
	glVertex3f(-2., -.2, -2.);
	glVertex3f(-2., -.2, 2.);
	glVertex3f(-2., .2, 2.);
	glVertex3f(-2., .2, -2.);

	//top
	glNormal3f(0, 1., 0);

	glVertex3f(2., .2, 2.);
	glVertex3f(-2., .2, 2.);
	glVertex3f(-2., .2, -2.);
	glVertex3f(2., .2, -2.);

	//bottom
	glNormal3f(0, -1., 0);

	glVertex3f(2., -.2, 2.);
	glVertex3f(-2., -.2, 2.);
	glVertex3f(-2., -.2, -2.);
	glVertex3f(2., -.2, -2.);

	//table front leg
	//front
	glNormal3f(0, 0, 1.);

	glVertex3f(1.8, -.2, 1.6);
	glVertex3f(1.4, -.2, 1.6);
	glVertex3f(1.4, -3., 1.6);
	glVertex3f(1.8, -3., 1.6);

	//back
	glNormal3f(0, 0, -1.);

	glVertex3f(1.8, -.2, 1.2);
	glVertex3f(1.4, -.2, 1.2);
	glVertex3f(1.4, -3., 1.2);
	glVertex3f(1.8, -3., 1.2);

	//right
	glNormal3f(1., 0, 0);

	glVertex3f(1.8, -.2, 1.6);
	glVertex3f(1.8, -.2, 1.2);
	glVertex3f(1.8, -3., 1.2);
	glVertex3f(1.8, -3., 1.6);

	//left
	glNormal3f(-1., 0, 0);

	glVertex3f(1.4, -.2, 1.6);
	glVertex3f(1.4, -.2, 1.2);
	glVertex3f(1.4, -3., 1.2);
	glVertex3f(1.4, -3., 1.6);

	//back leg back
	//front
	glNormal3f(0, 0, -1.);

	glVertex3f(1.8, -.2, -1.2);
	glVertex3f(1.4, -.2, -1.2);
	glVertex3f(1.4, -3., -1.2);
	glVertex3f(1.8, -3., -1.2);

	//back
	glNormal3f(0, 0, -1.);

	glVertex3f(1.8, -.2, -1.6);
	glVertex3f(1.4, -.2, -1.6);
	glVertex3f(1.4, -3., -1.6);
	glVertex3f(1.8, -3., -1.6);

	//right
	glNormal3f(1., 0, 0);

	glVertex3f(1.8, -.2, -1.6);
	glVertex3f(1.8, -.2, -1.2);
	glVertex3f(1.8, -3., -1.2);
	glVertex3f(1.8, -3., -1.6);

	//left
	glNormal3f(1., 0, 0);

	glVertex3f(1.4, -.2, -1.6);
	glVertex3f(1.4, -.2, -1.2);
	glVertex3f(1.4, -3., -1.2);
	glVertex3f(1.4, -3., -1.6);

	//leg left front
	glNormal3f(0, 0, 1.);

	glVertex3f(-1.8, -.2, 1.6);
	glVertex3f(-1.4, -.2, 1.6);
	glVertex3f(-1.4, -3., 1.6);
	glVertex3f(-1.8, -3., 1.6);

	//back
	glNormal3f(0, 0, -1.);

	glVertex3f(-1.8, -.2, 1.2);
	glVertex3f(-1.4, -.2, 1.2);
	glVertex3f(-1.4, -3., 1.2);
	glVertex3f(-1.8, -3., 1.2);

	//right
	glNormal3f(1., 0, 0);

	glVertex3f(-1.8, -.2, 1.6);
	glVertex3f(-1.8, -.2, 1.2);
	glVertex3f(-1.8, -3., 1.2);
	glVertex3f(-1.8, -3., 1.6);

	//left
	glNormal3f(-1., 0, 0);

	glVertex3f(-1.4, -.2, 1.6);
	glVertex3f(-1.4, -.2, 1.2);
	glVertex3f(-1.4, -3., 1.2);
	glVertex3f(-1.4, -3., 1.6);

	//left leg back front

	//front
	glNormal3f(0, 0, -1.);

	glVertex3f(-1.8, -.2, -1.2);
	glVertex3f(-1.4, -.2, -1.2);
	glVertex3f(-1.4, -3., -1.2);
	glVertex3f(-1.8, -3., -1.2);

	//back
	glNormal3f(0, 0, -1.);

	glVertex3f(-1.8, -.2, -1.6);
	glVertex3f(-1.4, -.2, -1.6);
	glVertex3f(-1.4, -3., -1.6);
	glVertex3f(-1.8, -3., -1.6);

	//right
	glNormal3f(1., 0, 0);

	glVertex3f(-1.8, -.2, -1.6);
	glVertex3f(-1.8, -.2, -1.2);
	glVertex3f(-1.8, -3., -1.2);
	glVertex3f(-1.8, -3., -1.6);

	//left
	glNormal3f(-1., 0, 0);

	glVertex3f(-1.4, -.2, -1.6);
	glVertex3f(-1.4, -.2, -1.2);
	glVertex3f(-1.4, -3., -1.2);
	glVertex3f(-1.4, -3., -1.6);

	//chair back
	//front
	glColor3f(1, 0, 0);

	glVertex3f(-1.8, .2, -1.8);
	glVertex3f(1.8, .2, -1.8);
	glVertex3f(1.8, 3.5, -1.8);
	glVertex3f(-1.8, 3.5, -1.8);

	//back

	glVertex3f(-1.8, .2, -2.);
	glVertex3f(1.8, .2, -2.);
	glVertex3f(1.8, 3.5, -2.);
	glVertex3f(-1.8, 3.5, -2.);



	glVertex3f(-1.8, .2, -2.);
	glVertex3f(-1.8, 3.5, -2.);
	glVertex3f(-1.8, 3.5, -1.8);
	glVertex3f(-1.8, .2, -1.8);


	glVertex3f(1.8, .2, -2.);
	glVertex3f(1.8, 3.5, -2.);
	glVertex3f(1.8, 3.5, -1.8);
	glVertex3f(1.8, .2, -1.8);

	glVertex3f(-1.8, 3.5, -2.);
	glVertex3f(-1.8, 3.5, -1.8);
	glVertex3f(1.8, 3.5, -1.8);
	glVertex3f(1.8, 3.5, -2.);



	glEnd();

	glPopMatrix();

}

	//Render table
	void renderTable()
{
	glPushMatrix();

	newMaterial();
	GLfloat chairColor[] = { .8, .196078 , .6 };
	setOcclusion(chairColor);

	glScalef(tableScale, tableScale, tableScale);
	glTranslatef(chairX, chairY+3, chairZ);

	glBegin(GL_QUADS);

	//Front
	glNormal3f(0, 0, 1.);
	glVertex3f(-2., -.2, 2.);
	glVertex3f(2., -.2, 2.);
	glVertex3f(2., .2, 2.);
	glVertex3f(-2., .2, 2.);

	//Right
	glNormal3f(1., 0, 0);
	glVertex3f(2., -.2, -2.);
	glVertex3f(2., .2, -2.);
	glVertex3f(2., .2, 2.);
	glVertex3f(2., -.2, 2.);

	//Back
	glNormal3f(0, 0, -1.);
	glVertex3f(-2., -.2, -2.);
	glVertex3f(-2., .2, -2.);
	glVertex3f(2., .2, -2.);
	glVertex3f(2., -.2, -2.);

	//Left
	glNormal3f(-1., 0, 0);
	glVertex3f(-2., -.2, -2.);
	glVertex3f(-2., -.2, 2.);
	glVertex3f(-2., .2, 2.);
	glVertex3f(-2., .2, -2.);

	//top
	glNormal3f(0, 1., 0);

	glVertex3f(2., .2, 2.);
	glVertex3f(-2., .2, 2.);
	glVertex3f(-2., .2, -2.);
	glVertex3f(2., .2, -2.);

	//bottom
	glNormal3f(0, -1., 0);

	glVertex3f(2., -.2, 2.);
	glVertex3f(-2., -.2, 2.);
	glVertex3f(-2., -.2, -2.);
	glVertex3f(2., -.2, -2.);

	//table front leg
	//front
	glNormal3f(0, 0, 1.);

	glVertex3f(1.8, -.2, 1.6);
	glVertex3f(1.4, -.2, 1.6);
	glVertex3f(1.4, -3., 1.6);
	glVertex3f(1.8, -3., 1.6);

	//back
	glNormal3f(0, 0, -1.);

	glVertex3f(1.8, -.2, 1.2);
	glVertex3f(1.4, -.2, 1.2);
	glVertex3f(1.4, -3., 1.2);
	glVertex3f(1.8, -3., 1.2);

	//right
	glNormal3f(1., 0, 0);

	glVertex3f(1.8, -.2, 1.6);
	glVertex3f(1.8, -.2, 1.2);
	glVertex3f(1.8, -3., 1.2);
	glVertex3f(1.8, -3., 1.6);

	//left
	glNormal3f(-1., 0, 0);

	glVertex3f(1.4, -.2, 1.6);
	glVertex3f(1.4, -.2, 1.2);
	glVertex3f(1.4, -3., 1.2);
	glVertex3f(1.4, -3., 1.6);

	//back leg back
	//front
	glNormal3f(0, 0, -1.);

	glVertex3f(1.8, -.2, -1.2);
	glVertex3f(1.4, -.2, -1.2);
	glVertex3f(1.4, -3., -1.2);
	glVertex3f(1.8, -3., -1.2);

	//back
	glNormal3f(0, 0, -1.);

	glVertex3f(1.8, -.2, -1.6);
	glVertex3f(1.4, -.2, -1.6);
	glVertex3f(1.4, -3., -1.6);
	glVertex3f(1.8, -3., -1.6);

	//right
	glNormal3f(1., 0, 0);

	glVertex3f(1.8, -.2, -1.6);
	glVertex3f(1.8, -.2, -1.2);
	glVertex3f(1.8, -3., -1.2);
	glVertex3f(1.8, -3., -1.6);

	//left
	glNormal3f(1., 0, 0);

	glVertex3f(1.4, -.2, -1.6);
	glVertex3f(1.4, -.2, -1.2);
	glVertex3f(1.4, -3., -1.2);
	glVertex3f(1.4, -3., -1.6);

	//leg left front
	glNormal3f(0, 0, 1.);

	glVertex3f(-1.8, -.2, 1.6);
	glVertex3f(-1.4, -.2, 1.6);
	glVertex3f(-1.4, -3., 1.6);
	glVertex3f(-1.8, -3., 1.6);

	//back
	glNormal3f(0, 0, -1.);

	glVertex3f(-1.8, -.2, 1.2);
	glVertex3f(-1.4, -.2, 1.2);
	glVertex3f(-1.4, -3., 1.2);
	glVertex3f(-1.8, -3., 1.2);

	//right
	glNormal3f(1., 0, 0);

	glVertex3f(-1.8, -.2, 1.6);
	glVertex3f(-1.8, -.2, 1.2);
	glVertex3f(-1.8, -3., 1.2);
	glVertex3f(-1.8, -3., 1.6);

	//left
	glNormal3f(-1., 0, 0);

	glVertex3f(-1.4, -.2, 1.6);
	glVertex3f(-1.4, -.2, 1.2);
	glVertex3f(-1.4, -3., 1.2);
	glVertex3f(-1.4, -3., 1.6);

	//left leg back front

	//front
	glNormal3f(0, 0, -1.);

	glVertex3f(-1.8, -.2, -1.2);
	glVertex3f(-1.4, -.2, -1.2);
	glVertex3f(-1.4, -3., -1.2);
	glVertex3f(-1.8, -3., -1.2);

	//back
	glNormal3f(0, 0, -1.);

	glVertex3f(-1.8, -.2, -1.6);
	glVertex3f(-1.4, -.2, -1.6);
	glVertex3f(-1.4, -3., -1.6);
	glVertex3f(-1.8, -3., -1.6);

	//right
	glNormal3f(1., 0, 0);

	glVertex3f(-1.8, -.2, -1.6);
	glVertex3f(-1.8, -.2, -1.2);
	glVertex3f(-1.8, -3., -1.2);
	glVertex3f(-1.8, -3., -1.6);

	//left
	glNormal3f(-1., 0, 0);

	glVertex3f(-1.4, -.2, -1.6);
	glVertex3f(-1.4, -.2, -1.2);
	glVertex3f(-1.4, -3., -1.2);
	glVertex3f(-1.4, -3., -1.6);




	glEnd();

	glPopMatrix();

}

//Renders the lamp
void renderLamp()
{


	glPushMatrix();
	newMaterial();
	GLfloat standColor[] = { .184314, .309804 , .8 };
	setOcclusion(standColor);
	

	// Base
	glTranslatef(lampX, lampY, lampZ);
	glTranslatef(0, -1.3, 0);
	glutSolidCube(1.8);

	// Pole
	glTranslatef(0, lampHeight, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(lampRadius, lampHeight, cuts, cuts);

	glDisable(GL_LIGHTING);
	glColor3fv(lampColor);
	glutSolidSphere(0.5, cuts, cuts);
	glEnable(GL_LIGHTING);
	setOcclusion(elephantColor);

	glPopMatrix();
}

// Renders teapot
void renderTeaPot()
{

	float teaPotScale= 0.05;
	glPushMatrix();
	newMaterial();

	GLfloat greyish[] = { 0.17, 0.18, 0.26 };
	GLfloat teaSpec[] = { 1, 1, 1, 1.0 };

	setOcclusion(greyish);
	glMaterialfv(GL_FRONT, GL_SPECULAR, teaSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, 64);


	glTranslatef(tableX+1,tableY+9,tableZ+4.5);


	glutSolidTeapot(1);

	glPopMatrix();
}

void Display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderSideBar();


	glViewport(0, 0, displayX * 2 / 3, displayY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	gluPerspective(60, (float)(displayX * 2 / 3) / (float)displayY, .1, 100.);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		elephantX + camDist * sin(camX / 10), camY, elephantZ + camDist * cos(camX / 10), // Origin
		elephantX, elephantY, elephantZ, // Look At
		0, 1, 0
	);


	enableLight();
	renderFloor();
	renderelElephant();
	renderBall();
	renderChair();
	renderTable();
	renderLamp();
	renderTeaPot();



	glutSwapBuffers();


}

void resize(int x, int y)
{


	displayX = x;
	displayY = y;
}

// keybord founction
void keys(unsigned char k, int x, int y)
{


	if (k == '0')
		exit(0);

	const int varSize = 11;

	char keys[varSize][2] = {
		{ 'a', 'd' },{ 'w', 's' },{ 'q', 'e' }, // Elephant
		{ 'j', 'l' },{ 'k', 'i' },{ 'u', 'o' }, // Camera
		{ '3', '3' },{ 'z', 'x' }, // Light
		{ '1', '1' },{ '5', '5' }, // Head and tail move
		{ '7', '7' }, // Lamp
	};

	float *vars[varSize] =
	{
		&elephantX, &elephantZ, &deg,
		&camX, &camY, &camDist,
		&toggleLight, &occlusion,
		&moveHead, &moveTail,
		&toggleLamp,
	};

	float interval = .2;


	for (int i = 0; i < sizeof(keys); i++)
		for (int j = 0; j < sizeof(keys[i]); j++)
			if (k == keys[i][j])
			{
				if (k == '1')
					moveTail = !moveTail;
				else if (k == '5')
					moveHead = !moveHead;
				else if (k == '3')
					toggleLight = (toggleLight) ? 0 : 1;
				else if (k == '7')
				{
					float dmp = toggleLamp ? .1 : 1;
					toggleLamp = (toggleLamp) ? 0 : 1;
					lampColor[0] = 1.f  * dmp;
					lampColor[1] = .92f * dmp;
					lampColor[2] = .23f * dmp;
				}
				
				else
				{
					if (k == 'q' || k == 'e') interval *= 20;
					(*vars[i]) += (j == 0) ? (-interval) : interval;
					if (i < 3)
						legSwing += 45;
				}

				return;
			}

			 if ((k == '6'))
			{
				ballX = ballX + 0.1;
				lightX = lightX + 0.1;

			}
			else if (k == '4')
			{
				ballX = ballX - 0.1;
				lightX = lightX - 0.1;
			}
			else if (k == '8')
			{
				ballZ = ballZ - 0.1;
				lightZ = lightZ - 0.1;
			}
			else if (k == '2')
			{
				ballZ = ballZ + 0.1;
				lightZ = lightZ + 0.1;
			}
			else if (k == '-')
			{
				ballY = ballY - 0.1;
				lightY = lightY - 0.1;
			}
			else if (k == '+')
			{
				ballY = ballY + 0.1;
				lightY = lightY + 0.1;
			}
}


void main(int argc, char** argv)
{


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_X_OFFSET, WINDOW_Y_OFFSET);
	glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);
	glutCreateWindow("elephant's rampage");
	glClearColor(0., 0., 0., 0.);
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keys);
	createTexture();
	glutMainLoop();
}