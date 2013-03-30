#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>
#include "Primitivas.h"

void cadeiraQuadrada(void){
	int i;
	float j;
	int a = 0;
	int k;
	float coord[] = {-3,0.5,-3,-3,0.5,3,3,0.5,3,3,0.5,-3};
	//desenha pernas da mesa
	for(k = 0; k < 4; k++){
		glPushMatrix();
		glTranslatef(coord[a++],coord[a++],coord[a++]);
		glRotatef(45,0,1,0);
		for(i = 0; i < 5; i++){
			cubo(1);
			glTranslatef(0,1,0);
		}
		glPopMatrix();
	}

	//desenha tabua da mesa
	for(j = -3; j <= 3; j++){
		glPushMatrix();
		glTranslatef(-3,5.5,j);
		for(i = 0; i <7; i++){
			glPushMatrix();
			glRotatef(45,0,1,0);
			cubo(1);
			glPopMatrix();
			glTranslatef(1,0,0);
		}
		glPopMatrix();
	}

	for(j = -2.5; j <= 2.5; j+=5){
		glPushMatrix();
		glTranslatef(j,6.5,-3);
		for(i = 1; i <7; i++){
			glPushMatrix();
			glRotatef(45,0,1,0);
			cubo(1);
			glPopMatrix();
			glTranslatef(0,1,0);
		}
		glPopMatrix();
	}

	for(j = -1; j <= 1; j+=1){
		glPushMatrix();
		glTranslatef(j,6.25,-3);
		for(i = 1; i <= 12; i++){
			glPushMatrix();
			glRotatef(45,0,1,0);
			cubo(0.5);
			glPopMatrix();
			glTranslatef(0,0.5,0);
		}
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(-3,12.5,-3);
	for(i = 1; i <=7; i++){
		glPushMatrix();
		glRotatef(45,0,1,0);
		cubo(1);
		glPopMatrix();
		glTranslatef(1,0,0);
	}
	glPopMatrix();
}

void cadeiraRedonda(void){
	//cilindro da parte de baixo
	glPushMatrix();
	glTranslatef(0,0.5,0);
		glColor3f(1,0,0);
	cilindro(2,1,30,1);
	glPopMatrix();
	//cilindro interior que apoia o "taburete"
	glPushMatrix();
	glTranslatef(0,1.5,0);
		glColor3f(0,1,0);
	cilindro(1,1,30,1);
	glPopMatrix();
	//cilindro da parte superior
	glPushMatrix();
	glTranslatef(0,4,0);
		glColor3f(0,0,1);
	cilindro(3,4,30,4);
	glPopMatrix();

}