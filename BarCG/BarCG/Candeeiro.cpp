#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include "Primitivas.h"
#include "SolidoRevolucao.h"

void candeeiroTeto(SolidoRevolucao sol){
	float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float mcolor2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//desenha retangulo(base)
	glPushMatrix();
	glScalef(20,1,5);
	glRotatef(45,0,1,0);
	//cubo(1);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor);
	glBindTexture(GL_TEXTURE_2D, 9);
	desenhaCubo();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//desenhas cilindros(lampadas)
	//preparaCilindro(50,18,0.5,50);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor2);
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
	float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float mcolor2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glPushMatrix();
	//glColor3f(1,1,0);
	glRotatef(90,1,0,0);
	glScalef(4,1,4);
	//cilindro(4,1,30,2);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor);
	glBindTexture(GL_TEXTURE_2D, 1);
	cil.desenhaSolidRev();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//desenha 4 pinos
	//glColor3f(1,0.5,1);
	//preparaCilindro(50,1,0.25,50);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor);
	glBindTexture(GL_TEXTURE_2D, 8);
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
	glBindTexture(GL_TEXTURE_2D, 0);

	//desenha esfera(oval)
	//preparaEsfera(50,3.5,50);
	glPushMatrix();
	//glColor3f(0.5,1,1);
	glTranslatef(0,0,1.75);
	glScalef(3.5,3.5,0.875);
	//esfera(3.5,20,20);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor2);
	esf.desenhaSolidRev();
	glPopMatrix();
}