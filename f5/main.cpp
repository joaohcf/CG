#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;

float current_angle = 0.0;
float angle = 30.0f;

void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void drawTree(float x, float z){
	int altura_tronco = 3;
	int altura_topo = 8;
	
	//Tronco
	glColor3f(1,.5,0);
	glBegin(GL_TRIANGLES);
		glVertex3f(x, 0, z);
		glVertex3f(x+1, 0, z);
		glVertex3f(x+1, altura_tronco, z);
	glEnd();

	//Topo
	glColor3f(.2,1,.2);
	glBegin(GL_TRIANGLES);
		glVertex3f(x, altura_tronco-1, z);
		glVertex3f(x+2, altura_tronco-1, z);
		glVertex3f(x+2, altura_topo, z);
	glEnd();
}

void drawOutterRing(float radius){

	glColor3f(1,0,0);
	glRotatef(current_angle, 0, 0, 0);
	glTranslatef(radius,0,0);
	glutSolidTeapot(2.0f);

}

void drawInnerRing(float radius){

	glColor3f(0,0,1);
	for(int i = 0; i < 5; i++){
		glRotatef(current_angle,0,0,0);
		glTranslatef(radius,0,0);
		glutSolidTeapot(2.0f);
		current_angle += angle;
	}
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);
	glEnd();
	
	// put code to draw scene in here
	float x, z, r, cx, cz;
	int tree_count = 0;
	int counter = 0;
	r = 30;
	while(tree_count < 1000 && counter < 10000){
		x = rand() / (float)RAND_MAX;
		z = rand() / (float)RAND_MAX;
		cx = x * 200.0f - 100.0f;
		cz = z * 200.0f - 100.0f;
		if( (cx*cx) + (cz*cz) > (r*r) ){
			drawTree(cx, cz);
			tree_count++;
		}
		counter++;
	}

	glColor3f(1,1,1);
	glutSolidTorus(1,2,10,10);

	glTranslatef(0,2,0);
	drawInnerRing(10);
	drawOutterRing(10);	

	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin");
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	spherical2Cartesian();

	printInfo();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
