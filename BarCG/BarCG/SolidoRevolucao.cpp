#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "SolidoRevolucao.h"

SolidoRevolucao::SolidoRevolucao(){}

SolidoRevolucao::SolidoRevolucao(int lados,std::vector<float>* points){
	solidRevolucao(lados,points);
}

void SolidoRevolucao::desenhaSolidRev() {
    //	Bind e sem‚ntica
	glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
	glVertexPointer(3,GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
	glNormalPointer(GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[2]);
	glTexCoordPointer(2,GL_FLOAT,0,0);
    
    //  Desenhar
	glDrawElements(GL_TRIANGLES, verticeSolidRev ,GL_UNSIGNED_INT, indices);
	//glDrawArrays(GL_TRIANGLES, 0, verticeSolidRev);
}

void SolidoRevolucao::solidRevolucao(int lados, std::vector<float>* pontos){
    float alfa;
	float delta = (2*M_PI)/lados;
    int i=0,nPontos;
	int k = 0;
	int j = 0;
	int h = 0;
	int ni = 0;
	int t = 0;
    float xx1,yy1,xx2,yy2;
	int pontosYY = 0;
    int nPontosTotais=(int)((pontos->size()/2));
	//printf("EXISTE no vector points: %d vertices\n",nPontosTotais);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//calcula quantos triangulos vao ser desenhados
	verticeSolidRev = 0;
	for(nPontos=1; nPontos < nPontosTotais; nPontos++) {
		xx1=pontos->at(h);
        yy1=pontos->at(h+1);
		xx2=pontos->at(h+2);
		yy2=pontos->at(h+3);
		if(xx1==0.0f && xx2 != 0){
			for(int l = 1; l <= lados;l++){
				verticeSolidRev += 3;
			}
		}
		else if(xx1 !=0 && xx2 != 0){
			for(int l = 1; l <= lados;l++){
				verticeSolidRev += 6;
			}
		}
		else if(xx1 != 0 && xx2 == 0){
			for(int l = 1; l <= lados;l++){
				verticeSolidRev += 3;
			}
		}
		h+=2;
	}

	float *vertexB;
	int numeroVertices = nPontosTotais*(lados+1)*3;
	int numeroTexturas = nPontosTotais*(lados+1)*2;
	vertexB = new float[numeroVertices];

	float *normalB;
	normalB = new float[numeroVertices];

	float *texCoord;
	texCoord = new float[numeroTexturas];

	indices = new unsigned int[verticeSolidRev];

	//preenche vetor de vertices----------------------------------------------------------------------
	for (alfa=0; alfa < 2*M_PI; alfa+=delta) {
		for(nPontos=0; nPontos < nPontosTotais; nPontos++) {
			xx1=pontos->at(i);
			yy1=pontos->at(i+1);
			vertexB[k++] = xx1*cos(alfa);
			vertexB[k++] = yy1;
			vertexB[k++] = xx1*sin(alfa);
			//printf("vertexB(%d,%d,%d)=(%f,%f,%f)\n",k-3,k-2,k-1,vertexB[k-3],vertexB[k-2],vertexB[k-1]);
			i+=2;
		}
		i = 0;
	}
	for(nPontos=0; nPontos < nPontosTotais; nPontos++) {
		xx1=pontos->at(i);
		yy1=pontos->at(i+1);
		vertexB[k++] = xx1*cos(0);
		vertexB[k++] = yy1;
		vertexB[k++] = xx1*sin(0);
		//printf("vertexB(%d,%d,%d)=(%f,%f,%f)\n",k-3,k-2,k-1,vertexB[k-3],vertexB[k-2],vertexB[k-1]);
		i+=2;
	}

	i = 0;
	//normais ---------------------------------------------------------------------------------------
	int verticeActual = 0;
	int ladoActual;

	for (ladoActual = 1; ladoActual <= lados+1; ladoActual++) { 
		for(nPontos=0; nPontos < nPontosTotais; nPontos++) {
			xx1 = pontos->at(i);
			yy1 = pontos->at(i+1);
			if(xx1==0.0f && nPontos == 0){
				normalB[ni++] = 0;
				normalB[ni++] = -1;
				normalB[ni++] = 0;
				//printf("normalB(%d,%d,%d)=(%f,%f,%f)\n",ni-3,ni-2,ni-1,normalB[ni-3],normalB[ni-2],normalB[ni-1]);
				verticeActual++;
			}
			else if(xx1==0.0f && nPontos == nPontosTotais-1){
				normalB[ni++] = 0;
				normalB[ni++] = 1;
				normalB[ni++] = 0;
				//printf("normalB(%d,%d,%d)=(%f,%f,%f)\n",ni-3,ni-2,ni-1,normalB[ni-3],normalB[ni-2],normalB[ni-1]);
				verticeActual++;
			}
			else if(xx1==0.0f && nPontos < nPontosTotais-1 && nPontos > 0){
				normalB[ni++] = 1;
				normalB[ni++] = 0;
				normalB[ni++] = 0;
				//printf("normalB(%d,%d,%d)=(%f,%f,%f)\n",ni-3,ni-2,ni-1,normalB[ni-3],normalB[ni-2],normalB[ni-1]);
				verticeActual++;
			}
			else{
				GLfloat p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z,p4x,p4y,p4z;
				GLfloat v12x,v12y,v12z,v34x,v34y,v34z;
				GLfloat nx,ny,nz,norm;

				p3x = vertexB[3*(verticeActual-1)];
				p3y = vertexB[3*(verticeActual-1)+1];
				p3z = vertexB[3*(verticeActual-1)+2];

				if(ladoActual == 1){
					p1x = vertexB[3*(verticeActual+nPontosTotais)];
					p1y = vertexB[3*(verticeActual+nPontosTotais)+1];
					p1z = vertexB[3*(verticeActual+nPontosTotais)+2];

					p2x = vertexB[3*(verticeActual+((lados-1)*nPontosTotais))];
					p2y = vertexB[3*(verticeActual+((lados-1)*nPontosTotais))+1];
					p2z = vertexB[3*(verticeActual+((lados-1)*nPontosTotais))+2];
				}
				else if(ladoActual == lados+1){
					p1x = vertexB[3*(verticeActual-((lados-1)*nPontosTotais))];
					p1y = vertexB[3*(verticeActual-((lados-1)*nPontosTotais))+1];
					p1z = vertexB[3*(verticeActual-((lados-1)*nPontosTotais))+2];

					p2x = vertexB[3*(verticeActual-nPontosTotais)];
					p2y = vertexB[3*(verticeActual-nPontosTotais)+1];
					p2z = vertexB[3*(verticeActual-nPontosTotais)+2];
				}
				else{
					p1x = vertexB[3*(verticeActual+nPontosTotais)];
					p1y = vertexB[3*(verticeActual+nPontosTotais)+1];
					p1z = vertexB[3*(verticeActual+nPontosTotais)+2];

					p2x = vertexB[3*(verticeActual-nPontosTotais)];
					p2y = vertexB[3*(verticeActual-nPontosTotais)+1];
					p2z = vertexB[3*(verticeActual-nPontosTotais)+2];
				}

				p4x = vertexB[3*(verticeActual+1)];
				p4y = vertexB[3*(verticeActual+1)+1];
				p4z = vertexB[3*(verticeActual+1)+2];

				//vetores
				v12x = p2x - p1x;
				v12y = p2y - p1y;
				v12z = p2z - p1z;

				v34x = p4x - p3x;
				v34y = p4y - p3y;
				v34z = p4z - p3z;

				//normal
				nx = (v12y * v34z) - (v12z * v34y);
				ny = (v12z * v34x) - (v12x * v34z);
				nz = (v12x * v34y) - (v12y * v34x);

				//normaliza
				norm = sqrt(nx * nx + ny * ny + nz * nz);

				normalB[ni++] = nx/norm;
				normalB[ni++] = ny/norm;
				normalB[ni++] = nz/norm;
				//printf("normalB(%d,%d,%d)=(%f,%f,%f)\n",ni-3,ni-2,ni-1,normalB[ni-3],normalB[ni-2],normalB[ni-1]);
				verticeActual++;
			}
			i += 2;
		}
		i = 0;
	}

	//coordenadas de textura------------------------------------------------------------------------
	float tex1;
	tex1 = (float) 1/lados;
	//printf("%f\n",tex1);
	float tex2;
	tex2 = (float) 1/(nPontosTotais-1);
	//printf("%f\n",tex2);
	float coords = 0;
	float coordt = 1;
	for (ladoActual = 0; ladoActual <= lados; ladoActual++) {
		for(nPontos=0; nPontos < nPontosTotais; nPontos++) {
			texCoord[t++] = coords;
			texCoord[t++] = coordt;
			//printf("texCoord(%d,%d)=(%f,%f)\n",t-2,t-1,texCoord[t-2],texCoord[t-1]);
			coordt -= tex2;
		}
		coords -= tex1;
		coordt = 1;
	}
	
	//preenche vetor de indices-----------------------------------------------------------------------
	i = 0;
	int ponto =	1;
	int coord1 = 0;
	int coord2 = 1;
	int coord3 = nPontosTotais+1;
	int coord1lado = 0;
	int coord2lado = 1;
	int coord3lado = nPontosTotais+1;
	for (alfa=0; alfa < 2*M_PI; alfa+=delta) {
		for(nPontos=1; nPontos < nPontosTotais; nPontos++) {
			xx1=pontos->at(i);
			yy1=pontos->at(i+1);
			xx2=pontos->at(i+2);
			yy2=pontos->at(i+3);
			if(xx1==0.0f && xx2 != 0){
				indices[j++] = coord1;
				indices[j++] = coord2;
				if(coord2 != ((lados-1)*nPontosTotais)+nPontos){
					indices[j++] = coord3;
				}
				else{
					indices[j++] = coord3;
				}
				coord1++;
				coord2++;
			//printf("Indices[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indices[j-3],indices[j-2],indices[j-1]);
			}
			else if(xx1 !=0 && xx2 != 0){
				indices[j++] = coord1;
				indices[j++] = coord2;
				if(coord2 != ((lados-1)*nPontosTotais)+nPontos){
					indices[j++] = coord3;
				}
				else{
					indices[j++] = coord3;
				}
				//printf("Indices[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indices[j-3],indices[j-2],indices[j-1]);
				if(coord2 != ((lados-1)*nPontosTotais)+nPontos){
					indices[j++] = coord2;
					indices[j++] = coord2+nPontosTotais;
					indices[j++] = coord3;
				}
				else{
					indices[j++] = coord2;
					indices[j++] = coord2+nPontosTotais;
					indices[j++] = coord3;
				}
				//printf("Indices[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indices[j-3],indices[j-2],indices[j-1]);
				coord1++;
				coord2++;
				coord3++;
			}
			else if(xx1 != 0 && xx2 == 0){
				indices[j++] = coord1;
				indices[j++] = coord2;
				if(coord2 != ((lados-1)*nPontosTotais)+nPontos){
					indices[j++] = coord3;
				}
				else{
					indices[j++] = coord3;
				}
				coord1++;
				coord2++;
				coord3++;
				//printf("Indices[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indices[j-3],indices[j-2],indices[j-1]);
			}
			i+=2;
		}
		ponto++;
		coord1lado += nPontosTotais;
		coord2lado += nPontosTotais;
		coord3lado += nPontosTotais;
		coord1 = coord1lado;
		coord2 = coord2lado;
		coord3 = coord3lado;
		i = 0;
	}
	
	// Gerar VBOs
	glGenBuffers(3, buffers);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
	glBufferData(GL_ARRAY_BUFFER,numeroVertices*sizeof(vertexB), vertexB,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
	glBufferData(GL_ARRAY_BUFFER,numeroVertices*sizeof(normalB), normalB,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[2]);
	glBufferData(GL_ARRAY_BUFFER,numeroTexturas*sizeof(texCoord), texCoord,GL_STATIC_DRAW);
}