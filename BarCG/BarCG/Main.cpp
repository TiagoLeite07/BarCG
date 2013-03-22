#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>
#include "Primitivas.h"
#include <stdio.h>
#include <string.h>

float palpha = 0.0;
float pbeta = 0.0;
float praio = 5.0;

float px = praio*cos(pbeta)*sin(palpha);
float py = praio*sin(pbeta);
float pz = praio*cos(pbeta)*cos(palpha);

bool arrastar;
int arrastax, arrastay;

bool bcubo = false;
bool besfera = false;
bool bcilindro = false;
bool bplano = false;

float alt = 0;
float r = 0;
float l = 0;
float s = 0;
float c = 0;

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

	// p�r instru��es de desenho aqui
	if(bcilindro){
		cilindro(r,alt,l,s);}
	if(bcubo){
		cubo(alt);}
	if(besfera){
		esfera(r,s,l);}
	if(bplano){
		plano(alt,c);}
	// End of frame
	glutSwapBuffers();
}


// escrever fun��o de processamento do teclado
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

//fun��o de processamento do clique do rato
void rato_click(int botao, int estado, int x, int y){
	if(botao == GLUT_LEFT_BUTTON){
		switch(estado){
			case GLUT_DOWN:{
				arrastar = true;
				arrastax = x;
				arrastay = y;
				break;
			}
			case GLUT_UP:{
				arrastar = false;
				break;
			}
		}
	}
}


//fun��o de processamento do movimento do rato
void rato_movimento(int x, int y){
	if(arrastar){
		if(arrastax != x){
			palpha = palpha + 0.03 * ( arrastax < x ? -1 : 1 );
			px = praio*cos(pbeta)*sin(palpha);
			pz = praio*cos(pbeta)*cos(palpha);
		}

		if(arrastay != y){
			pbeta = pbeta + 0.03 * ( arrastay < y ? 1 : -1 );
			if(pbeta > M_PI/2) pbeta = M_PI/2;
			if(pbeta < -M_PI/2) pbeta = -M_PI/2;
			px = praio*cos(pbeta)*sin(palpha);
			py = praio*sin(pbeta);
			pz = praio*cos(pbeta)*cos(palpha);
		}

		arrastax = x;
		arrastay = y;

		//glutPostRedisplay();
	}
}

void menuLinhaComandos(){
	int nargumentos;
	bool solido = false;
	char linha[100],*linha1,comando[10],arg1[10],arg2[10],arg3[10],arg4[10];
	while(!solido){
		printf("Comandos Validos:\n");
		printf("CUBO 'altura'\n");
		printf("CILINDRO 'raio' 'altura' 'nlados' 'nseccoes'\n");
		printf("ESFERA 'raio' 'nlados' 'nseccoes'\n");
		printf("PLANO 'altura' 'comprimento'\n");
		printf("---------------------------\n\n");
		printf("Para trocar de solido fazer 'Botao Direito do Rado'->'NOVO SOLIDO' e voltar a esta linha de comandos\n\n");
		printf("Insira Comando: ");
		linha1 = fgets (linha,100,stdin);
		printf("\n");
		nargumentos = (sscanf(linha, "%s %s %s %s %s %s %s",comando, arg1, arg2, arg3, arg4));
		sscanf(linha, "%s %s %s %s %s %s %s",comando, arg1, arg2, arg3, arg4);

		if (strcmp (comando,"CUBO") == 0){
    			if (nargumentos == 2){
					sscanf(arg1, "%f", &alt);
					solido = true;
					bcubo = true;
					besfera = false;
					bcilindro = false;
					bplano = false;
				}
				else printf("Comando Invalido!\n");
		}
		else if (strcmp (comando,"CILINDRO") == 0){
    			if (nargumentos == 5){
					sscanf(arg1, "%f", &r);
					sscanf(arg2, "%f", &alt);
					sscanf(arg3, "%f", &l);
					sscanf(arg4, "%f", &s);
					solido = true;
					bcubo = false;
					besfera = false;
					bcilindro = true;
					bplano = false;
				}
				else printf("Comando Invalido!\n");
		}
		else if (strcmp (comando,"ESFERA") == 0){
    			if (nargumentos == 4){
					sscanf(arg1, "%f", &r);
					sscanf(arg2, "%f", &l);
					sscanf(arg3, "%f", &s);
					solido = true;
					bcubo = false;
					besfera = true;
					bcilindro = false;
					bplano = false;
				}
				else printf("Comando Invalido!\n");
		}
		else if (strcmp (comando,"PLANO") == 0){
    			if (nargumentos == 3){
					sscanf(arg1, "%f", &alt);
					sscanf(arg2, "%f", &c);
					solido = true;
					bcubo = false;
					besfera = false;
					bcilindro = false;
					bplano = true;
				}
				else printf("Comando Invalido!\n");
		}
		else printf("Comando Invalido!\n\n");
	}
}

// escrever fun��o de processamento do menu
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
		case 7:
			menuLinhaComandos();
			break;
		default:
			break;
	}
	glutPostRedisplay();
}


int main(int argc, char **argv) {
	printf("BarCG - Primitivas\n");
	printf("---------------------------\n\n");
	menuLinhaComandos();
// inicializa��o
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("BarCG");
		
// registo de fun��es
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

// p�r aqui registo da fun��es do teclado e rato
	glutKeyboardFunc(movimento);
	glutMouseFunc(rato_click);
	glutMotionFunc(rato_movimento);

// p�r aqui a cria��o do menu
	glutCreateMenu(menu);
	glutAddMenuEntry("GL_FRONT GL_LINE",1);
	glutAddMenuEntry("GL_BACK GL_LINE",2);
	glutAddMenuEntry("GL_FRONT_AND_BACK GL_LINE",3);
	glutAddMenuEntry("GL_BACK GL_FILL",4);
	glutAddMenuEntry("GL_FRONT GL_FILL",5);
	glutAddMenuEntry("NORMAL",6);
	glutAddMenuEntry("NOVO SOLIDO",7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// entrar no ciclo do GLUT 
	glutMainLoop();

	return 1;
}