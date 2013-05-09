#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include "Primitivas.h"
#include "SolidoRevolucao.h"

void candeeiroTeto(SolidoRevolucao sol){
	//desenha retangulo(base)
	glPushMatrix();
	glScalef(20,1,5);
	glRotatef(45,0,1,0);
	//cubo(1);
	desenhaCubo();
	glPopMatrix();

	//desenhas cilindros(lampadas)
	//preparaCilindro(50,18,0.5,50);
	glPushMatrix();
	//glColor3f(1,0,0);
	glTranslatef(0,0.5,-1);
	glRotatef(90,0,0,1);
	glScalef(0.5,18,0.5);
	//cilindro(0.5,18,20,18);
	sol.desenhaSolidRev();
	glPopMatrix();

	glPushMatrix();
	//glColor3f(1,0,0);
	glTranslatef(0,0.5,1);
	glRotatef(90,0,0,1);
	glScalef(0.5,18,0.5);
	//cilindro(0.5,18,20,18);
	sol.desenhaSolidRev();
	glPopMatrix();
}

void candeeiroParede(SolidoRevolucao cil,SolidoRevolucao esf){
	//desenha cilindro base
	//preparaCilindro(50,1,4,50);
	glPushMatrix();
	//glColor3f(1,1,0);
	glRotatef(90,1,0,0);
	glScalef(4,1,4);
	//cilindro(4,1,30,2);
	cil.desenhaSolidRev();
	glPopMatrix();

	//desenha 4 pinos
	//glColor3f(1,0.5,1);
	//preparaCilindro(50,1,0.25,50);
	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(2,1,2);
	glScalef(0.25,1,0.25);
	//cilindro(0.25,1,20,1);
	cil.desenhaSolidRev();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(2,1,-2);
	glScalef(0.25,1,0.25);
	//cilindro(0.25,1,20,1);
	cil.desenhaSolidRev();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(-2,1,-2);
	glScalef(0.25,1,0.25);
	//cilindro(0.25,1,20,1);
	cil.desenhaSolidRev();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(-2,1,2);
	glScalef(0.25,1,0.25);
	//cilindro(0.25,1,20,1);
	cil.desenhaSolidRev();
	glPopMatrix();

	//desenha esfera(oval)
	//preparaEsfera(50,3.5,50);
	glPushMatrix();
	//glColor3f(0.5,1,1);
	glTranslatef(0,0,1.75);
	glScalef(3.5,3.5,0.875);
	//esfera(3.5,20,20);
	esf.desenhaSolidRev();
	glPopMatrix();
}