#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>
#include "Primitivas.h"
#include "Mesa.h"
#include "Copo.h"
#include "Candeeiro.h"
#include "Cadeira.h"
#include <stdio.h>
#include <string.h>

float palpha = 0.0;
float pbeta = 0.0;
float praio = 100.0;

float px = praio*cos(pbeta)*sin(palpha);
float py = praio*sin(pbeta);
float pz = praio*cos(pbeta)*cos(palpha);

bool arrastar;
int arrastax, arrastay;

bool bcubo = false;
bool besfera = false;
bool bcilindro = false;
bool bplano = false;
bool bcadeiraQ = false;
bool bcadeiraR = false;
bool bmesaQ = false;
bool bmesaR = false;
bool bcopoR = false;
bool bcopoC = false;
bool bcandeeiroT = false;
bool bcandeeiroP = false;
bool blimites = false;

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

void limitesBar(){
	glPushMatrix();
	glRotatef(-90,1,0,0);
	glColor3f(1,0,0);
	plano(200,200);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,37.5,-100);
	glColor3f(1,0,1);
	plano(75,200);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,37.5,100);
	glRotatef(180,0,1,0);
	glColor3f(1,0,1);
	plano(75,200);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100,37.5,0);
	glRotatef(-90,0,1,0);
	glColor3f(1,0,1);
	plano(75,200);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100,37.5,0);
	glRotatef(90,0,1,0);
	glColor3f(1,0,1);
	plano(75,200);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,75,0);
	glRotatef(90,1,0,0);
	glColor3f(0,1,1);
	plano(200,200);
	glPopMatrix();
}

void teste(){
	glPushMatrix();
	glColor3f(0,1,0);
	glScalef(1.5,1.5,1.5);
	mesaQuadrada();
	glPopMatrix();
	glPushMatrix();
	glScalef(1.5,1.5,1.5);
	glTranslatef(15,0,0);
	mesaRedonda();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3,16.5,0);
	copoCone();
	glTranslatef(6,0,0);
	copoRedondo();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,74,0);
	glRotatef(180,1,0,0);
	glScalef(2,2,2);
	candeeiroTeto();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,40,-99.5);
	candeeiroParede();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0,-12);
	glScalef(1.5,1.5,1.5);
	cadeiraQuadrada();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-14,0,0);
	glScalef(1.5,1.5,1.5);
	cadeiraRedonda();
	glPopMatrix();
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
	if(bcilindro){
		cilindro(r,alt,l,s);
	}
	else if(bcubo){
		cubo(alt);
	}
	else if(besfera){
		esfera(r,s,l);
	}
	else if(bplano){
		plano(alt,c);
	}
	else if(bcadeiraQ){
		cadeiraQuadrada();
	}
	else if(bcadeiraR){
		cadeiraRedonda();
	}
	else if(bcopoR){
		copoRedondo();
	}
	else if(bcopoC){
		copoCone();
	}
	else if(bmesaR){
		mesaRedonda();
	}
	else if(bmesaQ){
		mesaQuadrada();
	}
	else if(bcandeeiroT){
		candeeiroTeto();
	}
	else if(bcandeeiroP){
		candeeiroParede();
	}
	else if(blimites){
		limitesBar();
	}

	//limitesBar();
	//teste();
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
			praio += 1.0;
			px = praio*cos(pbeta)*sin(palpha);
			py = praio*sin(pbeta);
			pz = praio*cos(pbeta)*cos(palpha);
			break;
		case 'x':
			praio -= 1.0;
			px = praio*cos(pbeta)*sin(palpha);
			py = praio*sin(pbeta);
			pz = praio*cos(pbeta)*cos(palpha);
			break;
		default:
			break;
	}
}

//função de processamento do clique do rato
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


//função de processamento do movimento do rato
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
	char linha[100],*linha1,comando[20],arg1[10],arg2[10],arg3[10],arg4[10];
	while(!solido){
		printf("Comandos Validos:\n");
		printf("CUBO 'altura'\n");
		printf("CILINDRO 'raio' 'altura' 'nlados' 'nseccoes'\n");
		printf("ESFERA 'raio' 'nlados' 'nseccoes'\n");
		printf("PLANO 'altura' 'comprimento'\n");
		printf("CADEIRA_QUADRADA\n");
		printf("CADEIRA_REDONDA\n");
		printf("MESA_QUADRADA\n");
		printf("MESA_REDONDA\n");
		printf("COPO_REDONDO\n");
		printf("COPO_CONE\n");
		printf("CANDEEIRO_TETO\n");
		printf("CANDEEIRO_PAREDE\n");
		printf("LIMITES\n");
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
					bcadeiraQ = false;
					bcadeiraR = false;
					bcopoC = false;
					bcopoR = false;
					bcandeeiroP = false;
					bcandeeiroT = false;
					bmesaQ = false;
					bmesaR = false;
					blimites = false;
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
					bcadeiraQ = false;
					bcadeiraR = false;
					bcopoC = false;
					bcopoR = false;
					bcandeeiroP = false;
					bcandeeiroT = false;
					bmesaQ = false;
					bmesaR = false;
					blimites = false;
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
					bcadeiraQ = false;
					bcadeiraR = false;
					bcopoC = false;
					bcopoR = false;
					bcandeeiroP = false;
					bcandeeiroT = false;
					bmesaQ = false;
					bmesaR = false;
					blimites = false;
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
					bcadeiraQ = false;
					bcadeiraR = false;
					bcopoC = false;
					bcopoR = false;
					bcandeeiroP = false;
					bcandeeiroT = false;
					bmesaQ = false;
					bmesaR = false;
					blimites = false;
				}
				else printf("Comando Invalido!\n");
		}
		else if (strcmp (comando,"CADEIRA_QUADRADA") == 0){
    			if (nargumentos == 1){
					solido = true;
					bcubo = false;
					besfera = false;
					bcilindro = false;
					bplano = false;
					bcadeiraQ = true;
					bcadeiraR = false;
					bcopoC = false;
					bcopoR = false;
					bcandeeiroP = false;
					bcandeeiroT = false;
					bmesaQ = false;
					bmesaR = false;
					blimites = false;
				}
				else printf("Comando Invalido!\n");
		}
		else if (strcmp (comando,"CADEIRA_REDONDA") == 0){
    			if (nargumentos == 1){
					solido = true;
					bcubo = false;
					besfera = false;
					bcilindro = false;
					bplano = false;
					bcadeiraQ = false;
					bcadeiraR = true;
					bcopoC = false;
					bcopoR = false;
					bcandeeiroP = false;
					bcandeeiroT = false;
					bmesaQ = false;
					bmesaR = false;
					blimites = false;
				}
				else printf("Comando Invalido!\n");
		}
		else if (strcmp (comando,"COPO_REDONDO") == 0){
    			if (nargumentos == 1){
					solido = true;
					bcubo = false;
					besfera = false;
					bcilindro = false;
					bplano = false;
					bcadeiraQ = false;
					bcadeiraR = false;
					bcopoC = false;
					bcopoR = true;
					bcandeeiroP = false;
					bcandeeiroT = false;
					bmesaQ = false;
					bmesaR = false;
					blimites = false;
				}
				else printf("Comando Invalido!\n");
		}
		else if (strcmp (comando,"COPO_CONE") == 0){
    			if (nargumentos == 1){
					solido = true;
					bcubo = false;
					besfera = false;
					bcilindro = false;
					bplano = false;
					bcadeiraQ = false;
					bcadeiraR = false;
					bcopoC = true;
					bcopoR = false;
					bcandeeiroP = false;
					bcandeeiroT = false;
					bmesaQ = false;
					bmesaR = false;
					blimites = false;
				}
				else printf("Comando Invalido!\n");
		}
		else if (strcmp (comando,"MESA_QUADRADA") == 0){
    			if (nargumentos == 1){
					solido = true;
					bcubo = false;
					besfera = false;
					bcilindro = false;
					bplano = false;
					bcadeiraQ = false;
					bcadeiraR = false;
					bcopoC = false;
					bcopoR = false;
					bcandeeiroP = false;
					bcandeeiroT = false;
					bmesaQ = true;
					bmesaR = false;
					blimites = false;
				}
				else printf("Comando Invalido!\n");
		}
		else if (strcmp (comando,"MESA_REDONDA") == 0){
    			if (nargumentos == 1){
					solido = true;
					bcubo = false;
					besfera = false;
					bcilindro = false;
					bplano = false;
					bcadeiraQ = false;
					bcadeiraR = false;
					bcopoC = false;
					bcopoR = false;
					bcandeeiroP = false;
					bcandeeiroT = false;
					bmesaQ = false;
					bmesaR = true;
					blimites = false;
				}
				else printf("Comando Invalido!\n");
		}
		else if (strcmp (comando,"CANDEEIRO_TETO") == 0){
    			if (nargumentos == 1){
					solido = true;
					bcubo = false;
					besfera = false;
					bcilindro = false;
					bplano = false;
					bcadeiraQ = false;
					bcadeiraR = false;
					bcopoC = false;
					bcopoR = false;
					bcandeeiroP = false;
					bcandeeiroT = true;
					bmesaQ = false;
					bmesaR = false;
					blimites = false;
				}
				else printf("Comando Invalido!\n");
		}
		else if (strcmp (comando,"CANDEEIRO_PAREDE") == 0){
    			if (nargumentos == 1){
					solido = true;
					bcubo = false;
					besfera = false;
					bcilindro = false;
					bplano = false;
					bcadeiraQ = false;
					bcadeiraR = false;
					bcopoC = false;
					bcopoR = false;
					bcandeeiroP = true;
					bcandeeiroT = false;
					bmesaQ = false;
					bmesaR = false;
					blimites = false;
				}
				else printf("Comando Invalido!\n");
		}
		else if (strcmp (comando,"LIMITES") == 0){
    			if (nargumentos == 1){
					solido = true;
					bcubo = false;
					besfera = false;
					bcilindro = false;
					bplano = false;
					bcadeiraQ = false;
					bcadeiraR = false;
					bcopoC = false;
					bcopoR = false;
					bcandeeiroP = false;
					bcandeeiroT = false;
					bmesaQ = false;
					bmesaR = false;
					blimites = true;
				}
				else printf("Comando Invalido!\n");
		}
		else printf("Comando Invalido!\n\n");
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
	printf("MOVIMENTO DA CAMERA:\n");
	printf("Mover Camera -> Rato ou 'a','s','d','w'\n");
	printf("Zoom in -> 'x'\n");
	printf("Zoom out -> 'z'\n");
	printf("---------------------------\n\n");
	menuLinhaComandos();
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
	glutAddMenuEntry("NOVO SOLIDO",7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// entrar no ciclo do GLUT 
	glutMainLoop();

	return 1;
}