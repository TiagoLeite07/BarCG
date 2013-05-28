#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "Primitivas.h"
#include "SolidoRevolucao.h"

void mesaQuadrada(void){
	int a = 0;
	int k;
	float coord[] = {-5,5,-5,-5,5,5,5,5,5,5,5,-5};
	//desenha pernas da mesa
	float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor);
	glBindTexture(GL_TEXTURE_2D, 1);
	for(k = 0; k < 4; k++){
		glPushMatrix();
		glTranslatef(coord[a++],coord[a++],coord[a++]);
		glRotatef(45,0,1,0);
		glScalef(2,10,2);
		desenhaCubo();
		glPopMatrix();
	}
	//desenha tabua da mesa
	glPushMatrix();
	glTranslatef(0,10.5,0);
	glRotatef(45,0,1,0);
	glScalef(16,1,16);
	desenhaCubo();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void mesaRedonda(SolidoRevolucao sol){
	float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor);
	glBindTexture(GL_TEXTURE_2D, 6);
	//desenha base da mesa
	//preparaCilindro(50,1,4,50);
	glPushMatrix();
	glTranslatef(0,0.5,0);
	glScalef(4,1,4);
	//cilindro(4,1,30,1);
	sol.desenhaSolidRev();
	glPopMatrix();

	//desenha perna da mesa
	//preparaCilindro(50,16,1,50);
	glPushMatrix();
	glTranslatef(0,9,0);
	glScalef(1,16,1);
	//cilindro(1,16,30,16);
	sol.desenhaSolidRev();
	glPopMatrix();

	//desenha tabua da mesa
	//preparaCilindro(50,1,8,50);
	glPushMatrix();
	glTranslatef(0,17.5,0);
	glScalef(8,1,8);
	//cilindro(8,1,40,1);
	sol.desenhaSolidRev();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}