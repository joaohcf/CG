#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

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


void drawCylinder(float radius, float height, int slices) {

	float alpha = 0;
	float angle = 360/slices;

	// put code to draw cylinder in here
	for(int slice = 1; slice <= slices; slice++){
		
		float px = radius * sin(alpha);
		float pz = radius * cos(alpha);

		glBegin(GL_TRIANGLES);

			//Base
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(px, 0, pz);
			glVertex3f(0, 0, 0);
			glVertex3f(radius*sin(alpha+angle), 0, radius*cos(alpha+angle));
			
			//Topo
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(px, height, pz);
			glVertex3f(0, height, 0);
			glVertex3f(radius*sin(alpha+angle), height, radius*cos(alpha+angle));

			//Lateral
			//glColor3f(0.0, 0.0, 1.0);
			//glVertex3f(px,0,pz);
			//glVertex3f(px+radius*sin(alpha+angle),0,pz+radius*cos(alpha+angle));
			//glVertex3f(px,height,pz);

			//glVertex3f(px,height,pz);
			//glVertex3f(px+radius*sin(alpha+angle),height,pz+radius*cos(alpha+angle));
			//glVertex3f(px+radius*sin(alpha+angle),0,pz+radius*cos(alpha+angle));
			
		glEnd();

		alpha += angle;
	}
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	drawCylinder(1,2,10);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here

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
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
