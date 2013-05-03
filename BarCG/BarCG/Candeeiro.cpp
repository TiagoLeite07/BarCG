#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include "Primitivas.h"
#include "SolidoRevolucao.h"

void candeeiroTeto(void){
	//desenha retangulo(base)
	int i,j;
	preparaCubo(1);
	for(j = -2.5; j < 2.5; j++){
		glPushMatrix();
		//glColor3f(1,1,0);
		glTranslatef(-9.5,0,j);
		for(i = 0; i < 20; i++){
			glPushMatrix();
			glRotatef(45,0,1,0);
			//cubo(1);
			desenhaSolido();
			glPopMatrix();
			glTranslatef(1,0,0);
		}
		glPopMatrix();
	}
	//desenhas cilindros(lampadas)
	preparaCilindro(50,18,0.5,50);
	glPushMatrix();
	//glColor3f(1,0,0);
	glTranslatef(0,0.5,-1);
	glRotatef(90,0,0,1);
	//cilindro(0.5,18,20,18);
	desenhaSolidRev();
	glPopMatrix();

	glPushMatrix();
	//glColor3f(1,0,0);
	glTranslatef(0,0.5,1);
	glRotatef(90,0,0,1);
	//cilindro(0.5,18,20,18);
	desenhaSolidRev();
	glPopMatrix();
}

void candeeiroParede(void){
	//desenha cilindro base
	preparaCilindro(50,1,4,50);
	glPushMatrix();
	//glColor3f(1,1,0);
	glRotatef(90,1,0,0);
	//cilindro(4,1,30,2);
	desenhaSolidRev();
	glPopMatrix();

	//desenha 4 pinos
	//glColor3f(1,0.5,1);
	preparaCilindro(50,1,0.25,50);
	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(2,1,2);
	//cilindro(0.25,1,20,1);
	desenhaSolidRev();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(2,1,-2);
	//cilindro(0.25,1,20,1);
	desenhaSolidRev();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(-2,1,-2);
	//cilindro(0.25,1,20,1);
	desenhaSolidRev();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(-2,1,2);
	//cilindro(0.25,1,20,1);
	desenhaSolidRev();
	glPopMatrix();

	//desenha esfera(oval)
	preparaEsfera(50,3.5,50);
	glPushMatrix();
	//glColor3f(0.5,1,1);
	glTranslatef(0,0,1.75);
	glScalef(1,1,0.25);
	//esfera(3.5,20,20);
	desenhaSolidRev();
	glPopMatrix();
}