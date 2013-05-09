#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>
#include <math.h>
#include <vector>
#include "SolidoRevolucao.h"

const int n=3;

int verticePlano;
unsigned int *indicesPlano;
GLuint buffersPlano[n];

int verticeCubo;
unsigned int *indicesCubo;
GLuint buffersCubo[n];

void desenhaPlano() {
    
    //	Bind e sem‚ntica
	glBindBuffer(GL_ARRAY_BUFFER,buffersPlano[0]);
	glVertexPointer(3,GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,buffersPlano[1]);
	glNormalPointer(GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,buffersPlano[2]);
	glTexCoordPointer(2,GL_FLOAT,0,0);
    
    //  Desenhar
	glDrawElements(GL_TRIANGLES, verticePlano ,GL_UNSIGNED_INT, indicesPlano);
	//glDrawArrays(GL_TRIANGLES, 0, verticeCilindro);
}

void desenhaCubo() {
    
    //	Bind e sem‚ntica
	glBindBuffer(GL_ARRAY_BUFFER,buffersCubo[0]);
	glVertexPointer(3,GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,buffersCubo[1]);
	glNormalPointer(GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,buffersCubo[2]);
	glTexCoordPointer(2,GL_FLOAT,0,0);
    
    //  Desenhar
	glDrawElements(GL_TRIANGLES, verticeCubo ,GL_UNSIGNED_INT, indicesCubo);
	//glDrawArrays(GL_TRIANGLES, 0, verticeCilindro);
}

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

//-----------------------------------VBO's-----------------------------------------------------

std::vector<float> preparaEsfera(float raio, int seccoes){
	std::vector<float> points;
	float seccoesF = (float) seccoes;
	float alfa;
	float beta = (M_PI/2)/(seccoesF/2);
	for(alfa = 0; alfa <= M_PI; alfa+=beta){
		points.push_back(-raio*sin(alfa));
		points.push_back(-raio*cos(alfa));
	}
	points.push_back(0);
	points.push_back(raio);
	return points;

}

std::vector<float> preparaCilindro(float altura, float raio, int seccoes){
	std::vector<float> points;
	float alturaSeccao = altura/seccoes;
	float alturaActual = alturaSeccao-(altura/2);

	points.push_back(0);
	points.push_back(-altura/2);
	points.push_back(raio);
	points.push_back(-altura/2);
	for(int i = 0; i<seccoes-1;i++){
		points.push_back(raio);
		points.push_back(alturaActual);
		alturaActual += alturaSeccao;
	}
	points.push_back(raio);
	points.push_back(altura/2);
	points.push_back(0);
	points.push_back(altura/2);
	return points;
}

void preparaCubo(float altura){
	verticeCubo = 36;
	float *vertexB;
	vertexB = new float[72];
	indicesCubo = new unsigned int[verticeCubo];
	float *normalB;
	normalB = new float[72];
	float *texCoord;
	texCoord = new float[48];
	float raio = sqrt(pow(altura,2)/2);
	float alfa;
	float delta = (2*M_PI)/4;
	int i = 0;
	int j = 0;
	int ni = 0;
	int t = 0;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	GLfloat v1x,v1y,v1z,v2x,v2y,v2z;
	GLfloat nx,ny,nz,norm;
	for(alfa = 0; alfa < 2*M_PI; alfa += delta){
		vertexB[i++] = raio*cos(alfa);
		vertexB[i++] = altura/2;
		vertexB[i++] = raio*sin(alfa);
		//printf("vertexB(%d,%d,%d)=(%f,%f,%f)\n",i-3,i-2,i-1,vertexB[i-3],vertexB[i-2],vertexB[i-1]);

		normalB[ni++] = 0;
		normalB[ni++] = 1;
		normalB[ni++] = 0;
	}

	for(alfa = 0; alfa < 2*M_PI; alfa += delta){
		vertexB[i++] = raio*cos(alfa);
		vertexB[i++] = altura/2;
		vertexB[i++] = raio*sin(alfa);
		//printf("vertexB(%d,%d,%d)=(%f,%f,%f)\n",i-3,i-2,i-1,vertexB[i-3],vertexB[i-2],vertexB[i-1]);
		vertexB[i++] = raio*cos(alfa+delta);
		vertexB[i++] = altura/2;
		vertexB[i++] = raio*sin(alfa+delta);
		//printf("vertexB(%d,%d,%d)=(%f,%f,%f)\n",i-3,i-2,i-1,vertexB[i-3],vertexB[i-2],vertexB[i-1]);
		vertexB[i++] = raio*cos(alfa+delta);
		vertexB[i++] = -altura/2;
		vertexB[i++] = raio*sin(alfa+delta);
		//printf("vertexB(%d,%d,%d)=(%f,%f,%f)\n",i-3,i-2,i-1,vertexB[i-3],vertexB[i-2],vertexB[i-1]);
		vertexB[i++] = raio*cos(alfa);
		vertexB[i++] = -altura/2;
		vertexB[i++] = raio*sin(alfa);
		//printf("vertexB(%d,%d,%d)=(%f,%f,%f)\n",i-3,i-2,i-1,vertexB[i-3],vertexB[i-2],vertexB[i-1]);

		v1x = cos(alfa);
		v1y = 0;
		v1z = sin(alfa);
		v2x = cos(alfa+delta);
		v2y = 0;
		v2z = sin(alfa+delta);
		nx = v1x+v2x;
		ny = v1y+v2y;
		nz = v1z+v2z;
		norm = sqrt(nx * nx + ny * ny + nz * nz);
		normalB[ni++] = nx/norm;
		normalB[ni++] = ny/norm;
		normalB[ni++] = nz/norm;
		normalB[ni++] = nx/norm;
		normalB[ni++] = ny/norm;
		normalB[ni++] = nz/norm;
		normalB[ni++] = nx/norm;
		normalB[ni++] = ny/norm;
		normalB[ni++] = nz/norm;
		normalB[ni++] = nx/norm;
		normalB[ni++] = ny/norm;
		normalB[ni++] = nz/norm;
	}

	for(alfa = 0; alfa < 2*M_PI; alfa += delta){
		vertexB[i++] = raio*cos(alfa);
		vertexB[i++] = -altura/2;
		vertexB[i++] = raio*sin(alfa);
		//printf("vertexB(%d,%d,%d)=(%f,%f,%f)\n",i-3,i-2,i-1,vertexB[i-3],vertexB[i-2],vertexB[i-1]);

		normalB[ni++] = 0;
		normalB[ni++] = -1;
		normalB[ni++] = 0;
	}

	texCoord[t++] = 1;
	texCoord[t++] = 0;
	texCoord[t++] = 1;
	texCoord[t++] = 1;
	texCoord[t++] = 0;
	texCoord[t++] = 1;
	texCoord[t++] = 0;
	texCoord[t++] = 0;

	texCoord[t++] = 1;
	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 1;
	texCoord[t++] = 1;
	texCoord[t++] = 1;

	texCoord[t++] = 1;
	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 1;
	texCoord[t++] = 1;
	texCoord[t++] = 1;

	texCoord[t++] = 1;
	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 1;
	texCoord[t++] = 1;
	texCoord[t++] = 1;

	texCoord[t++] = 1;
	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 1;
	texCoord[t++] = 1;
	texCoord[t++] = 1;

	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 1;
	texCoord[t++] = 1;
	texCoord[t++] = 1;
	texCoord[t++] = 1;
	texCoord[t++] = 0;

	//pontos::
	//		3,13,16
	//2,9,12		0,4,17
	//		1,5,8
	//		14,19,23
	//10,15,22		7,18,20
	//		6,11,21

	//face superior
	indicesCubo[j++] = 0;
	indicesCubo[j++] = 3;
	indicesCubo[j++] = 2;
	//printf("indicesSolido[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indicesSolido[j-3],indicesSolido[j-2],indicesSolido[j-1]);
	indicesCubo[j++] = 0;
	indicesCubo[j++] = 2;
	indicesCubo[j++] = 1;
	//printf("indicesSolido[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indicesSolido[j-3],indicesSolido[j-2],indicesSolido[j-1]);

	//lados
	indicesCubo[j++] = 4;
	indicesCubo[j++] = 5;
	indicesCubo[j++] = 6;
	//printf("indicesSolido[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indicesSolido[j-3],indicesSolido[j-2],indicesSolido[j-1]);
	indicesCubo[j++] = 4;
	indicesCubo[j++] = 6;
	indicesCubo[j++] = 7;
	//printf("indicesSolido[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indicesSolido[j-3],indicesSolido[j-2],indicesSolido[j-1]);
	indicesCubo[j++] = 8;
	indicesCubo[j++] = 9;
	indicesCubo[j++] = 10;
	//printf("indicesSolido[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indicesSolido[j-3],indicesSolido[j-2],indicesSolido[j-1]);
	indicesCubo[j++] = 8;
	indicesCubo[j++] = 10;
	indicesCubo[j++] = 11;
	//printf("indicesSolido[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indicesSolido[j-3],indicesSolido[j-2],indicesSolido[j-1]);
	indicesCubo[j++] = 12;
	indicesCubo[j++] = 13;
	indicesCubo[j++] = 14;
	//printf("indicesSolido[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indicesSolido[j-3],indicesSolido[j-2],indicesSolido[j-1]);
	indicesCubo[j++] = 12;
	indicesCubo[j++] = 14;
	indicesCubo[j++] = 15;
	//printf("indicesSolido[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indicesSolido[j-3],indicesSolido[j-2],indicesSolido[j-1]);
	indicesCubo[j++] = 16;
	indicesCubo[j++] = 17;
	indicesCubo[j++] = 18;
	//printf("indicesSolido[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indicesSolido[j-3],indicesSolido[j-2],indicesSolido[j-1]);
	indicesCubo[j++] = 16;
	indicesCubo[j++] = 18;
	indicesCubo[j++] = 19;
	//printf("indicesSolido[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indicesSolido[j-3],indicesSolido[j-2],indicesSolido[j-1]);

	//face inferior
	indicesCubo[j++] = 20;
	indicesCubo[j++] = 22;
	indicesCubo[j++] = 23;
	//printf("indicesSolido[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indicesSolido[j-3],indicesSolido[j-2],indicesSolido[j-1]);
	indicesCubo[j++] = 20;
	indicesCubo[j++] = 21;
	indicesCubo[j++] = 22;
	//printf("indicesSolido[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indicesSolido[j-3],indicesSolido[j-2],indicesSolido[j-1]);

	glGenBuffers(n, buffersCubo);
	glBindBuffer(GL_ARRAY_BUFFER,buffersCubo[0]);
	glBufferData(GL_ARRAY_BUFFER,72*sizeof(vertexB), vertexB,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,buffersCubo[1]);
	glBufferData(GL_ARRAY_BUFFER,72*sizeof(normalB), normalB,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,buffersCubo[2]);
	glBufferData(GL_ARRAY_BUFFER,48*sizeof(texCoord), texCoord,GL_STATIC_DRAW);
}

void preparaPlano (float altura, float comprimento){
	verticePlano = 6;
	float *vertexB;
	vertexB = new float[12];
	indicesPlano = new unsigned int[verticePlano];
	float *normalB;
	normalB = new float[12];
	float *texCoord;
	texCoord = new float[8];
	int i = 0;
	int j = 0;
	int k = 0;
	int t = 0;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	vertexB[i++] = -altura/2;
	vertexB[i++] = comprimento/2;
	vertexB[i++] = 0;
	vertexB[i++] = -altura/2;
	vertexB[i++] = -comprimento/2;
	vertexB[i++] = 0;
	vertexB[i++] = altura/2;
	vertexB[i++] = -comprimento/2;
	vertexB[i++] = 0;
	vertexB[i++] = altura/2;
	vertexB[i++] = comprimento/2;
	vertexB[i++] = 0;

	normalB[k++] = 0;
	normalB[k++] = 0;
	normalB[k++] = 1;
	normalB[k++] = 0;
	normalB[k++] = 0;
	normalB[k++] = 1;
	normalB[k++] = 0;
	normalB[k++] = 0;
	normalB[k++] = 1;
	normalB[k++] = 0;
	normalB[k++] = 0;
	normalB[k++] = 1;

	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 0;
	texCoord[t++] = 1;
	texCoord[t++] = 1;
	texCoord[t++] = 1;
	texCoord[t++] = 1;
	texCoord[t++] = 0;

	indicesPlano[j++] = 0;
	indicesPlano[j++] = 1;
	indicesPlano[j++] = 2;
	indicesPlano[j++] = 2;
	indicesPlano[j++] = 3;
	indicesPlano[j++] = 0;

	glGenBuffers(n, buffersPlano);
	glBindBuffer(GL_ARRAY_BUFFER,buffersPlano[0]);
	glBufferData(GL_ARRAY_BUFFER,12*sizeof(vertexB), vertexB,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,buffersPlano[1]);
	glBufferData(GL_ARRAY_BUFFER,12*sizeof(normalB), normalB,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,buffersPlano[2]);
	glBufferData(GL_ARRAY_BUFFER,8*sizeof(texCoord), texCoord,GL_STATIC_DRAW);
}