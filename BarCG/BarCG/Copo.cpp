#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>
#include "Primitivas.h"

void copoRedondo(){
	float delta;
	float alpha;
	float posicaoActual;
	float posicaoSeccao;
	float alturaSeccao;
	float nlados = 30;
	float altura = 2;
	float raio = 1;
	float seccoes = 4;
	delta = (2*M_PI)/nlados;
	glBegin(GL_TRIANGLES);
	//desenha anel
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			glColor3f(0.0,1.0,1.0);
			glVertex3f((raio)*sin(alpha), altura, (raio)*cos(alpha));
			glVertex3f((raio)*sin(alpha+delta), altura, (raio)*cos(alpha+delta));
			glVertex3f((raio-(raio/8))*sin(alpha+delta), altura, (raio-(raio/8))*cos(alpha+delta));
			glVertex3f((raio-(raio/8))*sin(alpha+delta), altura, (raio-(raio/8))*cos(alpha+delta));
			glVertex3f((raio-(raio/8))*sin(alpha), altura, (raio-(raio/8))*cos(alpha));
			glVertex3f((raio)*sin(alpha), altura, (raio)*cos(alpha));

	}
	//desenha circulo interior
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			glColor3f(1.0,1.0,1.0);
			glVertex3f((raio-(raio/8))*sin(alpha), ((altura/4)), (raio-(raio/8))*cos(alpha));
			glVertex3f((raio-(raio/8))*sin(alpha+delta), ((altura/4)), (raio-(raio/8))*cos(alpha+delta));
			glVertex3f(0,((altura/4)),0);
	}
	//desenha circulo exterior
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			glColor3f(1.0,0.0,1.0);
			glVertex3f(0,0,0);
			glVertex3f(raio*sin(alpha+delta), 0, raio*cos(alpha+delta));
			glVertex3f(raio*sin(alpha), 0, raio*cos(alpha));
	}
	//desenha lados do cilindro exterior
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			posicaoActual = 0;
			posicaoSeccao = (altura/seccoes);
			alturaSeccao = altura/seccoes;
			for(float i = 1; i <= seccoes; i++){
				//glColor3f(1.0,0.0,0.0);
				glVertex3f(raio*sin(alpha), posicaoSeccao, raio*cos(alpha));
				glVertex3f(raio*sin(alpha), posicaoActual, raio*cos(alpha));
				glVertex3f(raio*sin(alpha+delta), posicaoActual, raio*cos(alpha+delta));

				//glColor3f(0.0,1.0,0.0);
				glVertex3f(raio*sin(alpha+delta), posicaoActual, raio*cos(alpha+delta));
				glVertex3f(raio*sin(alpha+delta), posicaoSeccao, raio*cos(alpha+delta));
				glVertex3f(raio*sin(alpha), posicaoSeccao, raio*cos(alpha));
				posicaoActual = posicaoSeccao;
				posicaoSeccao += alturaSeccao;
			}
	}
	//desenha lados do cilindro interior
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			posicaoActual = (altura/4);
			posicaoSeccao = (altura/seccoes);
			alturaSeccao = altura/seccoes;
			for(float i = 1; i <= seccoes; i++){
				//glColor3f(1.0,0.0,0.0);
				glVertex3f((raio-(raio/8))*sin(alpha+delta), posicaoActual, (raio-(raio/8))*cos(alpha+delta));
				glVertex3f((raio-(raio/8))*sin(alpha), posicaoActual, (raio-(raio/8))*cos(alpha));
				glVertex3f((raio-(raio/8))*sin(alpha), posicaoSeccao, (raio-(raio/8))*cos(alpha));

				//glColor3f(0.0,1.0,0.0);
				glVertex3f((raio-(raio/8))*sin(alpha), posicaoSeccao, (raio-(raio/8))*cos(alpha));
				glVertex3f((raio-(raio/8))*sin(alpha+delta), posicaoSeccao, (raio-(raio/8))*cos(alpha+delta));
				glVertex3f((raio-(raio/8))*sin(alpha+delta), posicaoActual, (raio-(raio/8))*cos(alpha+delta));
				posicaoActual = posicaoSeccao;
				posicaoSeccao += alturaSeccao;
			}
	}
	glEnd();
}

void copoCone(){
	float delta;
	float alpha;
	float posicaoActual;
	float posicaoSeccao;
	float alturaSeccao;
	float nlados = 30;
	float altura = 1.5;
	float alturaBase = 0.125;
	float alturaPega = 1;
	float raio = 1.5;
	float seccoes = 1;
	delta = (2*M_PI)/nlados;
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glTranslatef(0,alturaBase/2,0);
	cilindro(raio*0.4,alturaBase,20,1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,alturaPega/2+alturaBase,0);
	cilindro(raio*0.05,alturaPega,20,5);
	glPopMatrix();
	glBegin(GL_TRIANGLES);
	//desenha circulo interior
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			glColor3f(1.0,1.0,1.0);
			glVertex3f((raio-(raio/8))*0.05*sin(alpha), alturaBase+alturaPega+altura/8, (raio-(raio/8))*0.05*cos(alpha));
			glVertex3f((raio-(raio/8))*0.05*sin(alpha+delta), alturaBase+alturaPega+altura/8, (raio-(raio/8))*0.05*cos(alpha+delta));
			glVertex3f(0,alturaBase+alturaPega+altura/8,0);
	}
	//desenha anel
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			glColor3f(0.0,1.0,1.0);
			glVertex3f((raio)*sin(alpha), alturaBase+alturaPega+altura, (raio)*cos(alpha));
			glVertex3f((raio)*sin(alpha+delta), alturaBase+alturaPega+altura, (raio)*cos(alpha+delta));
			glVertex3f((raio-(raio/8))*sin(alpha+delta), alturaBase+alturaPega+altura, (raio-(raio/8))*cos(alpha+delta));
			glVertex3f((raio-(raio/8))*sin(alpha+delta), alturaBase+alturaPega+altura, (raio-(raio/8))*cos(alpha+delta));
			glVertex3f((raio-(raio/8))*sin(alpha), alturaBase+alturaPega+altura, (raio-(raio/8))*cos(alpha));
			glVertex3f((raio)*sin(alpha), alturaBase+alturaPega+altura, (raio)*cos(alpha));

	}
	//desenha lados do cone exterior
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			posicaoActual = alturaBase+alturaPega;
			posicaoSeccao = alturaBase+alturaPega+altura;
			alturaSeccao = altura;
			for(float i = 1; i <= seccoes; i++){
				glColor3f(1.0,1.0,1.0);
				glVertex3f(raio*sin(alpha), posicaoSeccao, raio*cos(alpha));
				glVertex3f(raio*0.05*sin(alpha), posicaoActual, raio*0.05*cos(alpha));
				glVertex3f(raio*0.05*sin(alpha+delta), posicaoActual, raio*0.05*cos(alpha+delta));

				//glColor3f(0.0,1.0,0.0);
				glVertex3f(raio*0.05*sin(alpha+delta), posicaoActual, raio*0.05*cos(alpha+delta));
				glVertex3f(raio*sin(alpha+delta), posicaoSeccao, raio*cos(alpha+delta));
				glVertex3f(raio*sin(alpha), posicaoSeccao, raio*cos(alpha));
				posicaoActual = posicaoSeccao;
				posicaoSeccao += alturaSeccao;
			}
	}
	//desenha lados do cone interior
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			posicaoActual = alturaBase+alturaPega+altura/8;
			posicaoSeccao = alturaBase+alturaPega+altura;
			alturaSeccao = altura;
			for(float i = 1; i <= seccoes; i++){
				glColor3f(1.0,1.0,1.0);
				glVertex3f((raio-(raio/8))*0.05*sin(alpha+delta), posicaoActual, (raio-(raio/8))*0.05*cos(alpha+delta));
				glVertex3f((raio-(raio/8))*0.05*sin(alpha), posicaoActual, (raio-(raio/8))*0.05*cos(alpha));
				glVertex3f((raio-(raio/8))*sin(alpha), posicaoSeccao, (raio-(raio/8))*cos(alpha));

				//glColor3f(0.0,1.0,0.0);
				glVertex3f((raio-(raio/8))*sin(alpha), posicaoSeccao, (raio-(raio/8))*cos(alpha));
				glVertex3f((raio-(raio/8))*sin(alpha+delta), posicaoSeccao, (raio-(raio/8))*cos(alpha+delta));
				glVertex3f((raio-(raio/8))*0.05*sin(alpha+delta), posicaoActual, (raio-(raio/8))*0.05*cos(alpha+delta));
				posicaoActual = posicaoSeccao;
				posicaoSeccao += alturaSeccao;
			}
	}
	glEnd();
}