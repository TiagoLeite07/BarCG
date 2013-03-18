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
	//desenha circulo superior
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			//glColor3f(0.0,1.0,1.0);
			glVertex3f(raio*sin(alpha), altura/2, raio*cos(alpha));
			glVertex3f(raio*sin(alpha+delta), altura/2, raio*cos(alpha+delta));
			glVertex3f(0,altura/2,0);
	}
	//desenha circulo inferior
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			//glColor3f(0.0,1.0,1.0);
			glVertex3f(0,-altura/2,0);
			glVertex3f(raio*sin(alpha+delta), -altura/2, raio*cos(alpha+delta));
			glVertex3f(raio*sin(alpha), -altura/2, raio*cos(alpha));
	}
	//desenha lados do cilindro
	for(alpha = 0; alpha < 2*M_PI; alpha += delta){
			posicaoActual = -altura/2;
			posicaoSeccao = (altura/seccoes)-(altura/2);
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
	glEnd();
		
}

/*void cubo(float altura){
	float x = altura/2;

	glBegin(GL_TRIANGLES);
		glColor3f(1,1,0);
		glVertex3f(-x,x,-x);
		glVertex3f(-x,x,x);
		glVertex3f(x,x,x);
		glVertex3f(x,x,x);
		glVertex3f(x,x,-x);
		glVertex3f(-x,x,-x);

		glColor3f(1,0,0);
		glVertex3f(x,-x,x);
		glVertex3f(-x,-x,x);
		glVertex3f(-x,-x,-x);
		glVertex3f(-x,-x,-x);
		glVertex3f(x,-x,-x);
		glVertex3f(x,-x,x);

		glColor3f(0,1,1);
		glVertex3f(-x,x,x);
		glVertex3f(-x,-x,x);
		glVertex3f(x,-x,x);
		glVertex3f(x,-x,x);
		glVertex3f(x,x,x);
		glVertex3f(-x,x,x);

		glVertex3f(-x,x,x);
		glVertex3f(-x,-x,x);
		glVertex3f(x,-x,x);
		glVertex3f(x,-x,x);
		glVertex3f(x,x,x);
		glVertex3f(-x,x,x);

		glVertex3f(x,x,x);
		glVertex3f(x,-x,x);
		glVertex3f(x,-x,-x);
		glVertex3f(x,-x,-x);
		glVertex3f(x,x,-x);
		glVertex3f(x,x,x);

		glVertex3f(x,x,-x);
		glVertex3f(x,-x,-x);
		glVertex3f(-x,-x,-x);
		glVertex3f(-x,-x,-x);
		glVertex3f(-x,x,-x);
		glVertex3f(x,x,-x);

		glVertex3f(-x,x,-x);
		glVertex3f(-x,-x,-x);
		glVertex3f(-x,-x,x);
		glVertex3f(-x,-x,x);
		glVertex3f(-x,x,x);
		glVertex3f(-x,x,-x);

	glEnd();
}*/

void cubo(float altura){
	float alfa;
	float delta = (2*M_PI)/4;
	float raio = sqrt(pow(altura,2)/2);

	glBegin(GL_TRIANGLES);
	//desenha quadrado superior
	for(alfa = 0; alfa < 2*M_PI; alfa = alfa + 2*delta){
		//glColor3f(1,1,0);
		glVertex3f(raio*sin(alfa),altura/2,raio*cos(alfa));
		glVertex3f(raio*sin(alfa+delta),altura/2,raio*cos(alfa+delta));
		glVertex3f(raio*sin(alfa+2*delta),altura/2,raio*cos(alfa+2*delta));
	}
	//desenha quadrado inferior
	for(alfa = 0; alfa < 2*M_PI; alfa = alfa + 2*delta){
		//glColor3f(1,0,1);
		glVertex3f(raio*sin(alfa+2*delta),-altura/2,raio*cos(alfa+2*delta));
		glVertex3f(raio*sin(alfa+delta),-altura/2,raio*cos(alfa+delta));
		glVertex3f(raio*sin(alfa),-altura/2,raio*cos(alfa));
	}
	//desenha lados do cubo
	for(alfa = 0; alfa < 2*M_PI; alfa += delta){
		//glColor3f(1,0,0);
		glVertex3f(raio*sin(alfa),altura/2,raio*cos(alfa));
		glVertex3f(raio*sin(alfa),-altura/2,raio*cos(alfa));
		glVertex3f(raio*sin(alfa+delta),-altura/2,raio*cos(alfa+delta));

		//glColor3f(0,1,1);
		glVertex3f(raio*sin(alfa),altura/2,raio*cos(alfa));
		glVertex3f(raio*sin(alfa+delta),-altura/2,raio*cos(alfa+delta));
		glVertex3f(raio*sin(alfa+delta),altura/2,raio*cos(alfa+delta));
	}
	glEnd();
}

void esfera(float raio,float seccoes,float lado){
	float alfa;
	float beta = (M_PI/2)/(seccoes/2);
	float anguloBeta;
	float delta = (2*M_PI)/lado;
	
	glBegin(GL_TRIANGLES);
	for(anguloBeta = 0; anguloBeta < (M_PI/2); anguloBeta += beta){
		for(alfa = 0; alfa < 2*M_PI; alfa += delta){
			//glColor3f(1,1,0);
			glVertex3f(raio*cos(anguloBeta+beta)*sin(alfa),raio*sin(anguloBeta+beta),raio*cos(anguloBeta+beta)*cos(alfa));
			glVertex3f(raio*cos(anguloBeta)*sin(alfa),raio*sin(anguloBeta),raio*cos(anguloBeta)*cos(alfa));
			glVertex3f(raio*cos(anguloBeta)*sin(alfa+delta),raio*sin(anguloBeta),raio*cos(anguloBeta)*cos(alfa+delta));
			//glColor3f(0,1,1);
			glVertex3f(raio*cos(anguloBeta+beta)*sin(alfa),raio*sin(anguloBeta+beta),raio*cos(anguloBeta+beta)*cos(alfa));
			glVertex3f(raio*cos(anguloBeta)*sin(alfa+delta),raio*sin(anguloBeta),raio*cos(anguloBeta)*cos(alfa+delta));
			glVertex3f(raio*cos(anguloBeta+beta)*sin(alfa+delta),raio*sin(anguloBeta+beta),raio*cos(anguloBeta+beta)*cos(alfa+delta));
		}
	}

	for(anguloBeta = 0; anguloBeta > -(M_PI/2); anguloBeta -= beta){
		for(alfa = 0;alfa < 2*M_PI; alfa += delta){
			//glColor3f(0,1,0);
			glVertex3f(raio*cos(anguloBeta-beta)*sin(alfa),raio*sin(anguloBeta-beta),raio*cos(anguloBeta-beta)*cos(alfa));
			glVertex3f(raio*cos(anguloBeta)*sin(alfa+delta),raio*sin(anguloBeta),raio*cos(anguloBeta)*cos(alfa+delta));
			glVertex3f(raio*cos(anguloBeta)*sin(alfa),raio*sin(anguloBeta),raio*cos(anguloBeta)*cos(alfa));
			//glColor3f(0,1,1);
			glVertex3f(raio*cos(anguloBeta-beta)*sin(alfa),raio*sin(anguloBeta-beta),raio*cos(anguloBeta-beta)*cos(alfa));
			glVertex3f(raio*cos(anguloBeta-beta)*sin(alfa+delta),raio*sin(anguloBeta-beta),raio*cos(anguloBeta-beta)*cos(alfa+delta));
			glVertex3f(raio*cos(anguloBeta)*sin(alfa+delta),raio*sin(anguloBeta),raio*cos(anguloBeta)*cos(alfa+delta));
		}
	}
	glEnd();
}

void plano (float altura, float comprimento){
	float y = altura;
	float x = comprimento;
	glBegin(GL_TRIANGLES);
	glVertex3f(-x/2,y/2,0);
	glVertex3f(-x/2,-y/2,0);
	glVertex3f(x/2,-y/2,0);
	glVertex3f(x/2,-y/2,0);
	glVertex3f(x/2,y/2,0);
	glVertex3f(-x/2,y/2,0);
	glEnd();
}