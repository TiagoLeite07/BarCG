#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>
#include "Primitivas.h"

float palpha = 0.0;
float pbeta = 0.0;
float praio = 5.0;

float px = praio*cos(pbeta)*sin(palpha);
float py = praio*sin(pbeta);
float pz = praio*cos(pbeta)*cos(palpha);

bool arrastar;
int arrastax, arrastay;

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


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(px,py,pz, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	// pôr instruções de desenho aqui
	//cilindro(2,2,50,16);
	//cubo(1);
	//esfera(1,20,20);
	plano(1,2);
	// End of frame
	glutSwapBuffers();
}


// escrever função de processamento do teclado
void movimento(unsigned char tecla, int x, int y){
	switch(tecla){
		case 'd':
			palpha += 0.1;
			px = praio*cos(pbeta)*sin(palpha);
			pz = praio*cos(pbeta)*cos(palpha);
			break;
		case 'a':
			palpha -= 0.1;
			px = praio*cos(pbeta)*sin(palpha);
			pz = praio*cos(pbeta)*cos(palpha);
			break;
		case 'w': 
			pbeta += 0.1;
			if(pbeta > M_PI/2) pbeta = M_PI/2;
			px = praio*cos(pbeta)*sin(palpha);
			py = praio*sin(pbeta);
			pz = praio*cos(pbeta)*cos(palpha);
			break;
		case 's':
			pbeta -= 0.1;
			if(pbeta < -M_PI/2) pbeta = -M_PI/2;
			px = praio*cos(pbeta)*sin(palpha);
			py = praio*sin(pbeta);
			pz = praio*cos(pbeta)*cos(palpha);
			break;
		case 'z': 
			praio += 0.1;
			px = praio*cos(pbeta)*sin(palpha);
			py = praio*sin(pbeta);
			pz = praio*cos(pbeta)*cos(palpha);
			break;
		case 'x':
			praio -= 0.1;
			px = praio*cos(pbeta)*sin(palpha);
			py = praio*sin(pbeta);
			pz = praio*cos(pbeta)*cos(palpha);
			break;
		default:
			break;
	}
}

//função de processamento do clique do rato
void rato_click(int botao, int estado, int x, int y)
{
	if(botao == GLUT_LEFT_BUTTON)
	{
		switch(estado)
		{
		case GLUT_DOWN:
			{
				arrastar = true;
				arrastax = x;
				arrastay = y;
				break;
			}
		case GLUT_UP:
			{
				arrastar = false;
				break;
			}
		}
	}
}

//função de processamento do movimento do rato
void rato_movimento(int x, int y)
{
	if(arrastar)
	{
		if(arrastax != x) {
			palpha = palpha + 0.03 * ( arrastax < x ? -1 : 1 );
			px = praio*cos(pbeta)*sin(palpha);
			pz = praio*cos(pbeta)*cos(palpha);}

		if(arrastay != y) {
			pbeta = pbeta + 0.03 * ( arrastay < y ? 1 : -1 );
			if(pbeta > M_PI/2) pbeta = M_PI/2;
			if(pbeta < -M_PI/2) pbeta = -M_PI/2;
			px = praio*cos(pbeta)*sin(palpha);
			py = praio*sin(pbeta);
			pz = praio*cos(pbeta)*cos(palpha);}

		arrastax = x;
		arrastay = y;

		glutPostRedisplay();
	}
}


// escrever função de processamento do menu
void menu(int id_op){
	switch (id_op){
		case 1:
			glDisable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT,GL_LINE);
			break;
		case 2:
			glDisable(GL_CULL_FACE);
			glPolygonMode(GL_BACK,GL_LINE);
			break;
		case 3:
			glDisable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			break;
		case 4:
			glDisable(GL_CULL_FACE);
			glPolygonMode(GL_BACK,GL_FILL);
			break;
		case 5:
			glDisable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT,GL_FILL);
			break;
		case 6:
			glEnable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}



int main(int argc, char **argv) {

// inicialização
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("BarCG");
		

// registo de funções 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

// pôr aqui registo da funções do teclado e rato
	glutKeyboardFunc(movimento);
	glutMouseFunc(rato_click);
	glutMotionFunc(rato_movimento);

// pôr aqui a criação do menu
	glutCreateMenu(menu);
	glutAddMenuEntry("GL_FRONT GL_LINE",1);
	glutAddMenuEntry("GL_BACK GL_LINE",2);
	glutAddMenuEntry("GL_FRONT_AND_BACK GL_LINE",3);
	glutAddMenuEntry("GL_BACK GL_FILL",4);
	glutAddMenuEntry("GL_FRONT GL_FILL",5);
	glutAddMenuEntry("NORMAL",6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// entrar no ciclo do GLUT 
	glutMainLoop();
	
	return 1;
}