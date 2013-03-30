#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>
#include "Primitivas.h"

void candeeiroTeto(void){
	//desenha retangulo(base)
	int i,j;
	for(j = -2.5; j < 2.5; j++){
		glPushMatrix();
		glColor3f(1,1,0);
		glTranslatef(-9.5,0,j);
		for(i = 0; i < 20; i++){
			glPushMatrix();
			glRotatef(45,0,1,0);
			cubo(1);
			glPopMatrix();
			glTranslatef(1,0,0);
		}
		glPopMatrix();
	}
	//desenhas cilindros(lampadas)
	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(0,0.5,-1);
	glRotatef(90,0,0,1);
	cilindro(0.5,18,20,18);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(0,0.5,1);
	glRotatef(90,0,0,1);
	cilindro(0.5,18,20,18);
	glPopMatrix();
}

void candeeiroParede(void){
	//desenha cilindro base
	glPushMatrix();
	glColor3f(1,1,0);
	glRotatef(90,1,0,0);
	cilindro(4,1,30,2);
	glPopMatrix();

	//desenha 4 pinos
	glColor3f(1,0.5,1);
	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(2,1,2);
	cilindro(0.25,1,20,1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(2,1,-2);
	cilindro(0.25,1,20,1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(-2,1,-2);
	cilindro(0.25,1,20,1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(-2,1,2);
	cilindro(0.25,1,20,1);
	glPopMatrix();

	//desenha esfera(oval)
	glPushMatrix();
	glColor3f(0.5,1,1);
	glTranslatef(0,0,1.75);
	glScalef(1,1,0.25);
	esfera(3.5,20,20);
	glPopMatrix();
}