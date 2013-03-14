#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>

void cilindro(float raio, float altura, int nlados, float seccoes){
	float delta;
	float alpha;
	float posicaoActual;
	float posicaoSeccao;
	float alturaSeccao;
	delta = (2*M_PI)/nlados;
	glBegin(GL_TRIANGLES);
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			glColor3f(0.0,1.0,1.0);
			glVertex3f(raio*sin(alpha), altura/2, raio*cos(alpha));
			glVertex3f(raio*sin(alpha+delta), altura/2, raio*cos(alpha+delta));
			glVertex3f(0,altura/2,0);
	}

	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			glColor3f(0.0,1.0,1.0);
			glVertex3f(0,-altura/2,0);
			glVertex3f(raio*sin(alpha+delta), -altura/2, raio*cos(alpha+delta));
			glVertex3f(raio*sin(alpha), -altura/2, raio*cos(alpha));
	}

	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			posicaoActual = -altura/2;
			posicaoSeccao = (altura/seccoes)-(altura/2);
			alturaSeccao = altura/seccoes;
			for(float i = 1; i <= seccoes; i++){
				glColor3f(1.0,0.0,0.0);
				glVertex3f(raio*sin(alpha), posicaoSeccao, raio*cos(alpha));
				glVertex3f(raio*sin(alpha), posicaoActual, raio*cos(alpha));
				glVertex3f(raio*sin(alpha+delta), posicaoActual, raio*cos(alpha+delta));

				glColor3f(0.0,1.0,0.0);
				glVertex3f(raio*sin(alpha+delta), posicaoActual, raio*cos(alpha+delta));
				glVertex3f(raio*sin(alpha+delta), posicaoSeccao, raio*cos(alpha+delta));
				glVertex3f(raio*sin(alpha), posicaoSeccao, raio*cos(alpha));
				posicaoActual = posicaoSeccao;
				posicaoSeccao += alturaSeccao;
			}
	}
	glEnd();
		
}