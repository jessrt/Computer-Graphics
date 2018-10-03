//Jessica Thomas 
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>


/* 
Here we establish the variables. These variables are used with regard to light position, 
and how light is reflected off certain objects. It also includes the angles and values 
for rotations. These variables contain boolean values as well, for animation control. 
*/

GLfloat pos[] = { -2, 4, 5, 1 },		
amb[] = { 0.3, 0.3, 0.3, 1.0 };			
GLfloat parts_amb_diff[] = { 0.15, 0.15, 0.15, 1.0 };	 
GLfloat extra_amb_diff[] = { 0, 1, 1, 1.0 };	
GLfloat body_amb_diff[] = { 0.4, 0.4, 0.4, 1.0 };
GLfloat rocket_amb_diff[] = { .6, .2, 1, 0 };
GLfloat spe[] = { 0.2, 0.2, 0.2, 1.0 };		
GLfloat theta = 30, theta_1 = 180, dt_1 = .5, dt = .01; 
boolean rotate = false, rotate_1 = false, rotate_2 = false; 

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, body_amb_diff);
	
//The robot is made with the following matrices, from feet to next. 

	glPushMatrix();
	glTranslated(.44, 2, 0);
	glScaled(1, 2.5, 1); 
	glutSolidCube(.4);									//Form body
	glTranslated(0, .2, 0);
	glutSolidCube(.1);									//Form neck
	glPopMatrix();	
	
	glPushMatrix();  
	glTranslated(.4, 1.3, .8); 
	glScaled(1, 3.6, 1); 
	glutSolidCube(.2);									//Form left leg
	glTranslated(0, 0, -1.6);
	glutSolidCube(.2);									//Form right leg
	glTranslated(-.05, -.1, 1.6); 
	glScaled(2, .25, 1); 
	glutSolidCube(.2);									//From left foot
	glTranslated(0, 0, -1.6);
	glutSolidCube(.2);									//Form right foot
	glPopMatrix(); 
	
	glPushMatrix(); 
	glTranslated(.4, 2, .8); 
	glScaled(1, 3, 1); 
	glutSolidCube(.2);									//Form left arm
	glTranslated(0, 0, -1.6);
	glutSolidCube(.2);									//Form right arm
	glPopMatrix();

/*
Here we form the head of the robot, adding the stipulation that if rotate is true, 
the head will rotate. 
*/
	glPushMatrix(); 
	if (rotate) glRotated(theta_1, .44, 2.8, 0);
	glTranslated(.44, 2.8, 0); 
	glScaled(1.2, 1, 1); 
	glutSolidCube(.4);									//Form head
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, parts_amb_diff);
	glTranslated(.1, 0, .2);	
	glutSolidSphere(.025, 68, 68);						//Form eye 
	glTranslated(-.2, 0, 0); 
	glutSolidSphere(.025, 68, 68);						//Form eye
	glScaled(1.4, 1, 1); 
	glTranslated(.07, -.1, 0); 
	glutSolidCube(.05);									//Form mouth
	glPopMatrix();

/*
Here we form the antennae of the robot, adding the stipulation that if rotate_1 is 
true the ball, or sensor, of the robot will begin to rotate around the antennae. 
*/
	glPushMatrix();
	glTranslated(.45, 3, 0);
	glRotated(270, 1, 0, 0);
	glutSolidCone(.1, .5, 48, 48);						//Form antenae
	if (rotate_1) {
		glRotated(theta_1, .45, 1, 6);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rocket_amb_diff);
	}
	glTranslated(0, -1.1, 0); 
	glutSolidSphere(.025, 68, 68);						//Form sensor
	glPopMatrix();

/*
The rocket and thrusters of the rockets are formed. If rotate_2 is true, the rocket's
thrusters will rotate. 
*/
	glPushMatrix();  
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rocket_amb_diff);
	glScaled(2, 1, 1);
	glutSolidSphere(1, 48, 48);							//Form rocket
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, extra_amb_diff);
	if (rotate_2) glRotated(theta_1, 1.5,0, 0); 
	glTranslated(.8, .2, .8); 
	glutSolidCube(.5); 
	glTranslated(0, 0, -1.6);
	glutSolidCube(.5);
	
	glPopMatrix(); 

/*
Here we form planets that automatically rotate around the scene when the program is 
executed. 
*/
	glPushMatrix(); 
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, extra_amb_diff);
	glRotated(theta, 0, -1.5, 5);
	glTranslated(3, 0, -3); 	
	glutSolidSphere(.5, 68, 68);						//Form planet
	glRotated(180, 3, 0, -2); 
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, parts_amb_diff);
	glutSolidTorus(.1, .8, 48, 48);
	glTranslated(-2, -3, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rocket_amb_diff);
	glutSolidSphere(.5, 68, 68);						//Form planet
	
	
	//glTranslated(5, -2, 0);
	//glutSolidSphere(.5, 68, 68); 
	//glutSolidDodecahedron(); 
	glPopMatrix();

	glutSwapBuffers();
}

/*
This function comes into effect when commands are entered for the head and the antennae. 
This function is also used right at the beginning of the program, for the rotating planets. 
*/

void idle(void) {
	theta = (theta < 360) ? theta + dt : dt;
	theta_1 = (theta_1 < 360) ? theta_1 + dt_1 : dt_1;
	glutPostRedisplay();
}
 
//This function designates what happens when certain keys are pressed. 

void key(unsigned char key, int x, int y) {
	if (key == 'q') exit(0);
	if (key == 'o') {
		glTranslated(0, 0, -.1);
		glutPostRedisplay();
	}
	if (key == 'i'){
		glTranslated(0, 0, .1);
		glutPostRedisplay();	
	}
	if (key == 'r') rotate = true; 
	if (key == 's') rotate_1 = true; 
	if (key == 't') rotate_2 = true; 
}

void main(int argc, char** argv) {

//Here we dictate the text to be seen on start up. 

	std::cout << "Hello human. My name is Mr. Robot. Please give me a command: \n\n";
	std::cout << "Press i to zoom in. \nPress o to zoom out. \nPress r to rotate my head. \n";
	std::cout << "Press s to send out my signal. \nPress t to rotate rocket thrusters.\nPress q to exit.";

//Here we establish the initial conditions for the program. 

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Project 3");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55, 1, 2, 8);	

//Control how bright and shiny the view is respectively. 

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe); 
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 60);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

//Position and enable the light. 

	glTranslated(0, -1.3, -5);	
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

//Set functions. 

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(key); 
	glutMainLoop();
}