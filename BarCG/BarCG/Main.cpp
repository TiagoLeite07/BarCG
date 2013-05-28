#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>
#include <math.h>
#include "Primitivas.h"
#include "Mesa.h"
#include "Copo.h"
#include "Candeeiro.h"
#include "Cadeira.h"
#include "SolidoRevolucao.h"
#include <stdio.h>
#include <string.h>

float angle = 0;
float px = 75;
float py = 50;
float pz = 75;
float lx = 0;
float ly = 0; 
float lz = -1;
float deltaMove = 0;
float deltaUp = 0;
float deltaAngle = 0;

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

unsigned int texID;

SolidoRevolucao cil;
SolidoRevolucao esf;
SolidoRevolucao copoR;
SolidoRevolucao copoC;

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

void balcao(){
	float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor);
	glBindTexture(GL_TEXTURE_2D, 8);
	glPushMatrix();
	glTranslatef(0,13.5,0);
	glScalef(60,27,12);
	glRotatef(45,0,1,0);
	desenhaCubo();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(36,13.5,-14);
	glScalef(12,27,40);
	glRotatef(45,0,1,0);
	desenhaCubo();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-36,13.5,-4);
	glScalef(12,27,20);
	glRotatef(45,0,1,0);
	desenhaCubo();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-36,26.5,-24);
	glScalef(12,1,20);
	glRotatef(45,0,1,0);
	desenhaCubo();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void prateleira(){
	float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor);
	glBindTexture(GL_TEXTURE_2D, 8);
	glPushMatrix();
	glTranslatef(0,0.5,0);
	glScalef(60,1,8);
	glRotatef(45,0,1,0);
	desenhaCubo();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void limitesBar(){
	float i,j;
	glPushMatrix();
	glRotatef(-90,1,0,0);
	glScalef(20,20,1);
	glBindTexture(GL_TEXTURE_2D, 2);
	for(i = -4.5; i <= 4.5; i++){
		for(j = -4.5; j <= 4.5; j++){
			glPushMatrix();
			glTranslatef(i,j,0);
			desenhaPlano();
			glPopMatrix();
		}
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 4);
	glPushMatrix();
	glTranslatef(0,37.5,-100);
	glScalef(200,75,1);
	desenhaPlano();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,37.5,100);
	glRotatef(180,0,1,0);
	glScalef(200,75,1);
	desenhaPlano();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100,37.5,0);
	glRotatef(-90,0,1,0);
	glScalef(200,75,1);
	desenhaPlano();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100,37.5,0);
	glRotatef(90,0,1,0);
	glScalef(200,75,1);
	desenhaPlano();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

	glPushMatrix();
	glTranslatef(0,75,0);
	glRotatef(90,1,0,0);
	glScalef(200,200,1);
	glBindTexture(GL_TEXTURE_2D, 5);
	desenhaPlano();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

void orientacao(float ang) {
	lx = sin(ang);
	lz = -cos(ang);
}

void mover(float i) {
	px = px + i*(lx)*0.1;
	py = py + i*(ly)*0.1;
	pz = pz + i*(lz)*0.1;
}

void lookup(float i) {
	ly += 0.01*i;
}

void renderScene(void) {

	if (deltaMove)
		mover(deltaMove);
	if (deltaUp)
		lookup(deltaUp);
	if (deltaAngle) {
		angle += deltaAngle;
		orientacao(angle);
	}

	float pos1[4] = {0.0, 74, -30, 0.0};
	float pos2[4] = {0.0, 74.0, 30, 0.0};
	float pos3[4] = {0.0, 50, 99.5, 0.0};
	float pos4[4] = {99.5, 50, 0.0, 0.0};
	float pos5[4] = {-99.5, 50, 0.0, 0.0};
	GLfloat amb[3] = {0.4, 0.4, 0.4};
	GLfloat diff[3] = {0.6, 0.6, 0.6};
	GLfloat specular[4] = {1.0, 1.0, 1.0 , 1.0};

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, pos1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glLightfv(GL_LIGHT1, GL_POSITION, pos2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

	glLightfv(GL_LIGHT2, GL_POSITION, pos3);
	glLightfv(GL_LIGHT2, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);

	glLightfv(GL_LIGHT3, GL_POSITION, pos4);
	glLightfv(GL_LIGHT3, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular);

	glLightfv(GL_LIGHT4, GL_POSITION, pos5);
	glLightfv(GL_LIGHT4, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT4, GL_SPECULAR, specular);
	gluLookAt(px, py, pz, 
		      px + lx,py + ly,pz + lz,
			  0.0f,1.0f,0.0f);

	// pôr instruções de desenho aqui
	/*if(bcilindro){
		//cilindro(r,alt,l,s);
		glScalef(r,alt,r);
		cil.desenhaSolidRev();
	}
	else if(bcubo){
		//cubo(alt);
		glScalef(alt,alt,alt);
		desenhaCubo();
	}
	else if(besfera){
		//esfera(r,s,l);
		glScalef(r,r,r);
		esf.desenhaSolidRev();
	}
	else if(bplano){
		//plano(alt,c);
		glScalef(c,alt,1);
		desenhaPlano();
	}
	else if(bcadeiraQ){
		//cadeiraQuadrada();
		cadeiraQuadrada();
	}
	else if(bcadeiraR){
		//cadeiraRedonda();
		cadeiraRedonda(cil);
	}
	else if(bcopoR){
		//copoRedondo();
		copoR.desenhaSolidRev();
	}
	else if(bcopoC){
		//copoCone();
		copoC.desenhaSolidRev();
	}
	else if(bmesaR){
		//mesaRedonda();
		mesaRedonda(cil);
	}
	else if(bmesaQ){
		//mesaQuadrada();
		mesaQuadrada();
	}
	else if(bcandeeiroT){
		//candeeiroTeto();
		candeeiroTeto(cil);
	}
	else if(bcandeeiroP){
		//candeeiroParede();
		candeeiroParede(cil,esf);
	}
	else if(blimites){
		//limitesBar();
		limitesBar();
	}*/
	float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	limitesBar();

	//balcao
	glPushMatrix();
	glTranslatef(0,0,-66);
	balcao();
	glPopMatrix();

	//prateleiras
	glPushMatrix();
	glTranslatef(12,35,-96);
	prateleira();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-12,45,-96);
	prateleira();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(12,55,-96);
	prateleira();
	glPopMatrix();

	//candeeiros teto
	glPushMatrix();
	glTranslatef(0,74,-30);
	glRotatef(180,1,0,0);
	glScalef(2,2,2);
	candeeiroTeto(cil);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,74,30);
	glRotatef(180,1,0,0);
	glScalef(2,2,2);
	candeeiroTeto(cil);
	glPopMatrix();

	//candeeiros parede
	glPushMatrix();
	glTranslatef(0,50,99.5);
	glRotatef(180,0,1,0);
	candeeiroParede(cil,esf);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(99.5,50,0);
	glRotatef(-90,0,1,0);
	candeeiroParede(cil,esf);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-99.5,50,0);
	glRotatef(90,0,1,0);
	candeeiroParede(cil,esf);
	glPopMatrix();

	//mesas redondas
	float coord[] = {-40,0,-60,60,0,70,-40,0,70,60,0,-60};
	int k,i = 0;
	for(k = 0; k < 4; k++){
		glPushMatrix();
		glTranslatef(coord[i++],coord[i++],coord[i++]);
		glScalef(1.5,1.5,1.5);
		mesaRedonda(cil);
		glPopMatrix();
	}


	//mesas quadradas
	float coord2[] = {10,0,-60,60,0,10,10,0,70,-15,0,0};
	i = 0;
	for(k = 0; k < 4; k++){
		glPushMatrix();
		glTranslatef(coord2[i++],coord2[i++],coord2[i++]);
		glScalef(1.5,1.5,1.5);
		mesaQuadrada();
		glPopMatrix();
	}

	//cadeiras redondas
	float coord3[] = {10,0,-80,10,0,-45,10,0,85,-30,0,0};
	i = 0;
	for(k = 0; k < 4; k++){
		glPushMatrix();
		glTranslatef(coord3[i++],coord3[i++],coord3[i++]);
		glScalef(1.5,1.5,1.5);
		cadeiraRedonda(cil);
		glPopMatrix();
	}

	//cadeiras quadradas
	float coord4[] = {60,0,-10,10,0,55,-15,0,-15,60,0,20,-15,0,15,0,0,0,45,0,10};
	i = 0;
	for(k = 0; k < 3; k++){
		glPushMatrix();
		glTranslatef(coord4[i++],coord4[i++],coord4[i++]);
		glRotatef(90,0,1,0);
		glScalef(1.5,1.5,1.5);
		cadeiraQuadrada();
		glPopMatrix();
	}
	for(k = 0; k < 2; k++){
		glPushMatrix();
		glTranslatef(coord4[i++],coord4[i++],coord4[i++]);
		glRotatef(-90,0,1,0);
		glScalef(1.5,1.5,1.5);
		cadeiraQuadrada();
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(coord4[i++],coord4[i++],coord4[i++]);
	glRotatef(180,0,1,0);
	glScalef(1.5,1.5,1.5);
	cadeiraQuadrada();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(coord4[i++],coord4[i++],coord4[i++]);
	glScalef(1.5,1.5,1.5);
	cadeiraQuadrada();
	glPopMatrix();

	//copos cone
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, 7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor);
	float coord5[] = {-96,36,12,-96,36,17,-96,36,7,-96,36,22,-96,36,2,-96,36,27,-96,36,-3,-96,36,32,-96,36,-8,-42,27,-61,64,27,75,60,27,73,15,16.5,-62,63,16.5,10};
	i = 0;
	for(k = 0; k < 14; k++){
		glPushMatrix();
		glTranslatef(coord5[i++],coord5[i++],coord5[i++]);
		copoC.desenhaSolidRev();
		glPopMatrix();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);

	//copos redondos
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, 7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor);
	float coord6[] = {-96,46,-12,-96,46,-17,-96,46,-7,-96,46,-22,-96,46,-2,-96,46,-27,-96,46,3,-96,46,-32,-96,46,8,11,16.5,-61,64,16.5,13,60,16.5,10,10,16.5,70};
	i = 0;
	for(k = 0; k < 13; k++){
		glPushMatrix();
		glTranslatef(coord6[i++],coord6[i++],coord6[i++]);
		copoR.desenhaSolidRev();
		glPopMatrix();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);

	// End of frame
	glutSwapBuffers();
}

void movimentoCamera(int key, int x1, int y1) {

	switch (key) {
		case GLUT_KEY_LEFT: 
			deltaAngle = -0.01f;
			break;
		case GLUT_KEY_RIGHT : 
			deltaAngle = 0.01f;
			break;
		case GLUT_KEY_UP : 
			deltaUp = 1.0;
			break;
		case GLUT_KEY_DOWN : 
			deltaUp = -1.0;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void movimentoCameraPara(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT: 
		case GLUT_KEY_RIGHT : 
			deltaAngle = 0.0;
			break;
		case GLUT_KEY_UP : 
		case GLUT_KEY_DOWN : 
			deltaUp = 0;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

// escrever função de processamento do teclado
void movimentoDeslocar(unsigned char tecla, int x, int y){
	switch(tecla){
		case 'w' : deltaMove = 4.0;break;
		case 's' : deltaMove = -4.0;break;
		default:
			break;
	}
	glutPostRedisplay();
}

void movimentoDeslocarPara(unsigned char tecla, int x, int y){
	switch(tecla){
		case 'w' : 
		case 's' : deltaMove = 0;break;
		default:
			break;
	}
	glutPostRedisplay();
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
			
		}

		if(arrastay != y){
			
		}

		arrastax = x;
		arrastay = y;

		glutPostRedisplay();
	}
}

/*void menuLinhaComandos(){
	int nargumentos;
	bool solido = false;
	char linha[100],*linha1,comando[20],arg1[10],arg2[10],arg3[10],arg4[10];
	while(!solido){
		printf("Comandos Validos:\n");
		printf("CUBO 'altura'\n");
		printf("CILINDRO 'raio' 'altura'\n");
		printf("ESFERA 'raio'\n");
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
    			if (nargumentos == 3){
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
    			if (nargumentos == 2){
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
}*/

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
			glEnable(GL_LIGHT0);
			break;
		case 8:
			glEnable(GL_LIGHT1);
			break;
		case 9:
			glEnable(GL_LIGHT2);
			break;
		case 10:
			glEnable(GL_LIGHT3);
			break;
		case 11:
			glEnable(GL_LIGHT4);
			break;
		case 12:
			glDisable(GL_LIGHT0);
			break;
		case 13:
			glDisable(GL_LIGHT1);
			break;
		case 14:
			glDisable(GL_LIGHT2);
			break;
		case 15:
			glDisable(GL_LIGHT3);
			break;
		case 16:
			glDisable(GL_LIGHT4);
			break;
		case 17:
			glEnable(GL_TEXTURE_2D);
			break;
		case 18:
			glDisable(GL_TEXTURE_2D);
			break;
		//case 19:
			//menuLinhaComandos();
			//break;
		default:
			break;
	}
	glutPostRedisplay();
}

void init() {
	ilInit();
	unsigned int t[9], tw, th;
	unsigned char *texData;
	ilGenImages(9,t);

	ilBindImage(t[0]);
	ilLoadImage((ILstring)"../Wood3.jpg");
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();
	glGenTextures(1,&texID); // unsigned int texID - variavel global;
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	ilBindImage(t[1]);
	ilLoadImage((ILstring)"../Wood1.jpg");
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();
	glGenTextures(1,&texID); // unsigned int texID - variavel global;
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	ilBindImage(t[2]);
	ilLoadImage((ILstring)"../Wood1_M.jpg");
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();
	glGenTextures(1,&texID); // unsigned int texID - variavel global;
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	ilBindImage(t[3]);
	ilLoadImage((ILstring)"../11.jpg");
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();
	glGenTextures(1,&texID); // unsigned int texID - variavel global;
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	ilBindImage(t[4]);
	ilLoadImage((ILstring)"../Tiles1.jpg");
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();
	glGenTextures(1,&texID); // unsigned int texID - variavel global;
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	ilBindImage(t[5]);
	ilLoadImage((ILstring)"../MetalBare2.jpg");
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();
	glGenTextures(1,&texID); // unsigned int texID - variavel global;
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	ilBindImage(t[6]);
	ilLoadImage((ILstring)"../copo.png");
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();
	glGenTextures(1,&texID); // unsigned int texID - variavel global;
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	ilBindImage(t[7]);
	ilLoadImage((ILstring)"../Wood2.jpg");
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();
	glGenTextures(1,&texID); // unsigned int texID - variavel global;
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	ilBindImage(t[8]);
	ilLoadImage((ILstring)"../Fiberglass.jpg");
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();
	glGenTextures(1,&texID); // unsigned int texID - variavel global;
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);


// alguns settings para OpenGL
	glEnable(GL_TEXTURE_2D);
}

int main(int argc, char **argv) {
	/*printf("BarCG - Primitivas\n");
	printf("---------------------------\n\n");
	printf("MOVIMENTO DA CAMERA:\n");
	printf("Mover Camera -> Rato ou 'a','s','d','w'\n");
	printf("Zoom in -> 'x'\n");
	printf("Zoom out -> 'z'\n");
	printf("---------------------------\n\n");
	menuLinhaComandos();*/
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

	glewInit();
	init();

// pôr aqui registo da funções do teclado e rato
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(movimentoDeslocar);
	glutKeyboardUpFunc(movimentoDeslocarPara);
	glutMouseFunc(rato_click);
	glutMotionFunc(rato_movimento);
	glutSpecialFunc(movimentoCamera);
	glutSpecialUpFunc(movimentoCameraPara);

// pôr aqui a criação do menu
	glutCreateMenu(menu);
	glutAddMenuEntry("GL_FRONT GL_LINE",1);
	glutAddMenuEntry("GL_BACK GL_LINE",2);
	glutAddMenuEntry("GL_FRONT_AND_BACK GL_LINE",3);
	glutAddMenuEntry("GL_BACK GL_FILL",4);
	glutAddMenuEntry("GL_FRONT GL_FILL",5);
	glutAddMenuEntry("NORMAL",6);
	glutAddMenuEntry("LIGAR LUZ_1",7);
	glutAddMenuEntry("LIGAR LUZ_2",8);
	glutAddMenuEntry("LIGAR LUZ_3",9);
	glutAddMenuEntry("LIGAR LUZ_4",10);
	glutAddMenuEntry("LIGAR LUZ_5",11);
	glutAddMenuEntry("DELIGAR LUZ_1",12);
	glutAddMenuEntry("DELIGAR LUZ_2",13);
	glutAddMenuEntry("DELIGAR LUZ_3",14);
	glutAddMenuEntry("DELIGAR LUZ_4",15);
	glutAddMenuEntry("DELIGAR LUZ_5",16);
	glutAddMenuEntry("LIGAR TEXTURAS",17);
	glutAddMenuEntry("DESLIGAR TEXTURAS",18);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

// inicialização da luz
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);


	preparaCubo(1);
	preparaPlano(1,1);
	std::vector<float> pontos;
	pontos = preparaCilindro(1,1,50);
	cil = SolidoRevolucao (50,&pontos);
	std::vector<float> pontos2;
	pontos2 = preparaEsfera(1,50);
	esf = SolidoRevolucao (50,&pontos2);
	std::vector<float> pontos3;
	pontos3 = preparaCopoRedondo();
	copoR = SolidoRevolucao (50,&pontos3);
	std::vector<float> pontos4;
	pontos4 = preparaCopoCone();
	copoC = SolidoRevolucao (50,&pontos4);

// entrar no ciclo do GLUT 
	glutMainLoop();

	return 1;
}