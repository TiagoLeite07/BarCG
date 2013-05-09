#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include "Primitivas.h"
#include "SolidoRevolucao.h"

void cadeiraQuadrada(void){
	int i;
	float j;
	int a = 0;
	int k;
	float coord[] = {-3,2.5,-3,-3,2.5,3,3,2.5,3,3,2.5,-3};
	//desenha pernas da cadeira
	for(k = 0; k < 4; k++){
		glPushMatrix();
		glTranslatef(coord[a++],coord[a++],coord[a++]);
		glRotatef(45,0,1,0);
		glScalef(1,5,1);
		desenhaCubo();
		glPopMatrix();
	}

	//desenha tabua da cadeira
	glPushMatrix();
	glTranslatef(0,5.5,0);
	glRotatef(45,0,1,0);
	glScalef(7,1,7);
	//cubo(1);
	desenhaCubo();
	glPopMatrix();

	for(j = -2.5; j <= 2.5; j+=5){
		glPushMatrix();
		glTranslatef(j,9.0,-3);
		glRotatef(45,0,1,0);
		glScalef(1,6,1);
		//cubo(1);
		desenhaCubo();
		glPopMatrix();
	}

	
	for(j = -1; j <= 1; j+=1){
		glPushMatrix();
		glTranslatef(j,9.0,-3);
		glRotatef(45,0,1,0);
		glScalef(0.5,6,0.5);
		desenhaCubo();
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(0,12.5,-3);
	glScalef(7,1,1);
	glRotatef(45,0,1,0);
	desenhaCubo();
	glPopMatrix();
}

void cadeiraRedonda(SolidoRevolucao sol){
	//cilindro da parte de baixo
	//preparaCilindro(50,1,2,50);
	glPushMatrix();
	glTranslatef(0,0.5,0);
	glScalef(2,1,2);
		//glColor3f(1,0,0);
	//cilindro(2,1,30,1);
	sol.desenhaSolidRev();
	glPopMatrix();

	//cilindro interior que apoia o "taburete"
	//preparaCilindro(50,1,1,50);
	glPushMatrix();
	glTranslatef(0,1.5,0);
		//glColor3f(0,1,0);
	//cilindro(1,1,30,1);
	sol.desenhaSolidRev();
	glPopMatrix();
	//preparaCilindro(50,4,3,50);

	//cilindro da parte superior
	glPushMatrix();
	glTranslatef(0,4,0);
	glScalef(3,4,3);
		//glColor3f(0,0,1);
	//cilindro(3,4,30,4);
	sol.desenhaSolidRev();
	glPopMatrix();

}