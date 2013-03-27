#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>
#include "Primitivas.h"

void copoRedondo(void){
	float delta;
	float alpha;
	float posicaoActual;
	float posicaoSeccao;
	float alturaSeccao;

	float nlados = 30;
	float altura = 2;
	float raio = 1;
	float seccoes = 1;

	delta = (2*M_PI)/nlados;
	glBegin(GL_TRIANGLES);
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			//desenha anel 
			glColor3f(0.0,1.0,1.0);
			glVertex3f((raio)*sin(alpha), altura, (raio)*cos(alpha));
			glVertex3f((raio)*sin(alpha+delta), altura, (raio)*cos(alpha+delta));
			glVertex3f((raio-(raio/8))*sin(alpha+delta), altura, (raio-(raio/8))*cos(alpha+delta));
			glVertex3f((raio-(raio/8))*sin(alpha+delta), altura, (raio-(raio/8))*cos(alpha+delta));
			glVertex3f((raio-(raio/8))*sin(alpha), altura, (raio-(raio/8))*cos(alpha));
			glVertex3f((raio)*sin(alpha), altura, (raio)*cos(alpha));

			//desenha circulo interior do copo
			glColor3f(1.0,1.0,1.0);
			glVertex3f((raio-(raio/8))*sin(alpha), ((altura/4)), (raio-(raio/8))*cos(alpha));
			glVertex3f((raio-(raio/8))*sin(alpha+delta), ((altura/4)), (raio-(raio/8))*cos(alpha+delta));
			glVertex3f(0,((altura/4)),0);

			//desenha circulo exterior do copo
			glColor3f(1.0,0.0,1.0);
			glVertex3f(0,0,0);
			glVertex3f(raio*sin(alpha+delta), 0, raio*cos(alpha+delta));
			glVertex3f(raio*sin(alpha), 0, raio*cos(alpha));

	}

	//desenha lados do copo exterior
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

	//desenha lados do copo interior
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

void copoCone(void){
	float delta;
	float alpha;
	float posicaoActual;
	float posicaoSeccao;
	float alturaSeccao;
	float raioSeccao;
	float raioActual;
	float raioProximo;

	float nlados = 30;
	float altura = 1.5;
	float alturaBase = 0.125;
	float alturaPega = 1;
	float raio = 1.5;
	float seccoes = 4;

	delta = (2*M_PI)/nlados;

	//desenha base do copo
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glTranslatef(0,alturaBase/2,0);
	cilindro(raio*0.4,alturaBase,20,1);
	glPopMatrix();
	//desenha pega do copo
	glPushMatrix();
	glTranslatef(0,alturaPega/2+alturaBase,0);
	cilindro(raio*0.05,alturaPega,20,4);
	glPopMatrix();

	glBegin(GL_TRIANGLES);
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			//desenha circulo interior do copo
			glColor3f(1.0,1.0,1.0);
			glVertex3f((raio-(raio/8))*0.05*sin(alpha), alturaBase+alturaPega+altura/8, (raio-(raio/8))*0.05*cos(alpha));
			glVertex3f((raio-(raio/8))*0.05*sin(alpha+delta), alturaBase+alturaPega+altura/8, (raio-(raio/8))*0.05*cos(alpha+delta));
			glVertex3f(0,alturaBase+alturaPega+altura/8,0);

			//desenha anel
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
			posicaoSeccao = alturaBase+alturaPega+(altura/seccoes);
			alturaSeccao = altura/seccoes;
			raioSeccao = (raio-(raio*0.05))/seccoes;
			raioActual = raio*0.05;
			raioProximo = raioActual+raioSeccao;
			for(float i = 1; i <= seccoes; i++){
				glColor3f(1.0,1.0,1.0);
				glVertex3f(raioProximo*sin(alpha), posicaoSeccao, raioProximo*cos(alpha));
				glVertex3f(raioActual*sin(alpha), posicaoActual, raioActual*cos(alpha));
				glVertex3f(raioActual*sin(alpha+delta), posicaoActual, raioActual*cos(alpha+delta));

				//glColor3f(0.0,1.0,0.0);
				glVertex3f(raioActual*sin(alpha+delta), posicaoActual, raioActual*cos(alpha+delta));
				glVertex3f(raioProximo*sin(alpha+delta), posicaoSeccao, raioProximo*cos(alpha+delta));
				glVertex3f(raioProximo*sin(alpha), posicaoSeccao, raioProximo*cos(alpha));
				posicaoActual = posicaoSeccao;
				posicaoSeccao += alturaSeccao;
				raioActual = raioProximo;
				raioProximo += raioSeccao;
			}
	}

	//desenha lados do cone interior
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			posicaoActual = alturaBase+alturaPega+altura/8;
			posicaoSeccao = alturaBase+alturaPega+altura/8+((altura-(altura/8))/seccoes);
			alturaSeccao = ((altura-(altura/8))/seccoes);
			raioSeccao = ((raio-(raio/8))-((raio-(raio/8))*0.05))/seccoes;
			raioActual = (raio-(raio/8))*0.05;
			raioProximo = raioActual+raioSeccao;
			for(float i = 1; i <= seccoes; i++){
				glColor3f(1.0,1.0,1.0);
				glVertex3f(raioActual*sin(alpha+delta), posicaoActual, raioActual*cos(alpha+delta));
				glVertex3f(raioActual*sin(alpha), posicaoActual, raioActual*cos(alpha));
				glVertex3f(raioProximo*sin(alpha), posicaoSeccao, raioProximo*cos(alpha));

				//glColor3f(0.0,1.0,0.0);
				glVertex3f(raioProximo*sin(alpha), posicaoSeccao, raioProximo*cos(alpha));
				glVertex3f(raioProximo*sin(alpha+delta), posicaoSeccao, raioProximo*cos(alpha+delta));
				glVertex3f(raioActual*sin(alpha+delta), posicaoActual, raioActual*cos(alpha+delta));
				posicaoActual = posicaoSeccao;
				posicaoSeccao += alturaSeccao;
				raioActual = raioProximo;
				raioProximo += raioSeccao;
			}
	}
	glEnd();
}