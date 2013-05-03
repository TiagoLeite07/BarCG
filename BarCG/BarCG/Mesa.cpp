#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "Primitivas.h"
#include "SolidoRevolucao.h"

void mesaQuadrada(void){
	int i;
	float j;
	int a = 0;
	int k;
	float coord[] = {-5,1,-5,-5,1,5,5,1,5,5,1,-5};
	//desenha pernas da mesa
	for(k = 0; k < 4; k++){
		glPushMatrix();
		glTranslatef(coord[a++],coord[a++],coord[a++]);
		glRotatef(45,0,1,0);
		preparaCubo(2);
		for(i = 0; i < 5; i++){
			//cubo(2);
			desenhaSolido();
			glTranslatef(0,2,0);
		}
		glPopMatrix();
	}
	//desenha tabua da mesa
	for(j = -7.5; j < 8.5; j++){
		glPushMatrix();
		glTranslatef(-7.5,10.5,j);
		preparaCubo(1);
		for(i = 0; i < 16; i++){
			glPushMatrix();
			glRotatef(45,0,1,0);
			//cubo(1);
			desenhaSolido();
			glPopMatrix();
			glTranslatef(1,0,0);
		}
		glPopMatrix();
	}
}

void mesaRedonda(void){
	//desenha base da mesa
	preparaCilindro(50,1,4,50);
	glPushMatrix();
	glTranslatef(0,0.5,0);
	//cilindro(4,1,30,1);
	desenhaSolidRev();
	glPopMatrix();
	//desenha perna da mesa
	preparaCilindro(50,16,1,50);
	glPushMatrix();
	glTranslatef(0,9,0);
	//cilindro(1,16,30,16);
	desenhaSolidRev();
	glPopMatrix();
	//desenha tabua da mesa
	preparaCilindro(50,1,8,50);
	glPushMatrix();
	glTranslatef(0,17.5,0);
	//cilindro(8,1,40,1);
	desenhaSolidRev();
	glPopMatrix();
}