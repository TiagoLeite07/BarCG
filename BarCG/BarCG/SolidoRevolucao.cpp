#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <vector>

int verticeSolidRev;
unsigned int *indices;
const int n=2;
GLuint buffers[n];

void desenhaSolidRev() {
    
    //	Bind e sem‚ntica
	glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
	glVertexPointer(3,GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
	glNormalPointer(GL_FLOAT,0,0);
    
    //  Desenhar
	glDrawElements(GL_TRIANGLES, verticeSolidRev ,GL_UNSIGNED_INT, indices);
	//glDrawArrays(GL_TRIANGLES, 0, verticeSolidRev);
}

void solidRevolucao(int lados, std::vector<float>* pontos){
    float alfa;
	float delta = (2*M_PI)/lados;
    int i=0,nPontos;
	int k = 0;
	int j = 0;
	int h = 0;
	int ni = 0;
    float xx1,yy1,xx2,yy2;
	int pontosYY = 0;
    int nPontosTotais=(int)((pontos->size()/2));
	//printf("EXISTE no vector points: %d vertices\n",nPontosTotais);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	//calcula quantos pontos estao no eixo yy
	for(nPontos=0; nPontos < nPontosTotais*2; nPontos+=2) {
		if(pontos->at(nPontos) == 0){
			pontosYY++;
		}
	}

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
	int numeroVertices = (((nPontosTotais-pontosYY)*lados)+pontosYY)*3;
	vertexB = new float[numeroVertices];

	float *normalB;
	normalB = new float[numeroVertices];

	indices = new unsigned int[verticeSolidRev];

	//preenche vetor de vertices----------------------------------------------------------------------
	for(nPontos=0; nPontos < nPontosTotais; nPontos++) {
		xx1=pontos->at(i);
        yy1=pontos->at(i+1);
		if(xx1==0.0f){
			vertexB[k++] = xx1;
			vertexB[k++] = yy1;
			vertexB[k++] = 0;
			//printf("vertexB(%d,%d,%d)=(%f,%f,%f)\n",k-3,k-2,k-1,vertexB[k-3],vertexB[k-2],vertexB[k-1]);
		}
		else{
			for (alfa=0; alfa < 2*M_PI; alfa+=delta) {
				vertexB[k++] = xx1*cos(alfa);
				vertexB[k++] = yy1;
				vertexB[k++] = xx1*sin(alfa);

				//printf("vertexB(%d,%d,%d)=(%f,%f,%f) alfa:%f \n",k-3,k-2,k-1,vertexB[k-3],vertexB[k-2],vertexB[k-1],alfa);
			}
		}
		i+=2;
	}

	int passou = 1;
	//normais ----------------------------------------------------------------------------------------
	i = 0;
	int verticeActual = 0;
	for(nPontos=0; nPontos < nPontosTotais; nPontos++) {
		xx1 = pontos->at(i);
		yy1 = pontos->at(i+1);
		if(xx1==0.0f && nPontos == 0){
			normalB[ni++] = 0;
			normalB[ni++] = -1;
			normalB[ni++] = 0;
			//printf("normalB(%d,%d,%d)=(%f,%f,%f)\n",ni-3,ni-2,ni-1,normalB[ni-3],normalB[ni-2],normalB[ni-1]);
			//printf("PassouINICIO: %d\n",passou);
			verticeActual++;
			passou++;
		}
		else if(xx1==0.0f && nPontos == nPontosTotais-1){
			normalB[ni++] = 0;
			normalB[ni++] = 1;
			normalB[ni++] = 0;
			//printf("normalB(%d,%d,%d)=(%f,%f,%f)\n",ni-3,ni-2,ni-1,normalB[ni-3],normalB[ni-2],normalB[ni-1]);
			verticeActual++;
			//printf("PassouFIM: %d\n",passou);
			passou++;
		}
		else if(xx1==0.0f && nPontos < nPontosTotais-1){
			normalB[ni++] = 1;
			normalB[ni++] = 0;
			normalB[ni++] = 0;
			//printf("normalB(%d,%d,%d)=(%f,%f,%f)\n",ni-3,ni-2,ni-1,normalB[ni-3],normalB[ni-2],normalB[ni-1]);
			//printf("PassouINICIO: %d\n",passou);
			verticeActual++;
			passou++;
		}
		else{
			GLfloat p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z,p4x,p4y,p4z;
			GLfloat v12x,v12y,v12z,v34x,v34y,v34z;
			GLfloat nx,ny,nz,norm;

			for (alfa=0; alfa < 2*M_PI; alfa+=delta) {
				if(verticeActual-lados <= 0){
					p3x = vertexB[0];
					p3y = vertexB[1];
					p3z = vertexB[2];

				}
				else {
					p3x = vertexB[3*(verticeActual-lados)];
					p3y = vertexB[3*(verticeActual-lados)+1];
					p3z = vertexB[3*(verticeActual-lados)+2];
				}

				if(alfa == 0){
					p1x = vertexB[3*(verticeActual+1)];
					p1y = vertexB[3*(verticeActual+1)+1];
					p1z = vertexB[3*(verticeActual+1)+2];

					p2x = vertexB[3*(verticeActual+(lados-1))];
					p2y = vertexB[3*(verticeActual+(lados-1))+1];
					p2z = vertexB[3*(verticeActual+(lados-1))+2];
				}
				else if(alfa == (lados-1)*delta){
					p1x = vertexB[3*(verticeActual-(lados-1))];
					p1y = vertexB[3*(verticeActual-(lados-1))+1];
					p1z = vertexB[3*(verticeActual-(lados-1))+2];

					p2x = vertexB[3*(verticeActual-1)];
					p2y = vertexB[3*(verticeActual-1)+1];
					p2z = vertexB[3*(verticeActual-1)+2];
				}
				else{
					p1x = vertexB[3*(verticeActual+1)];
					p1y = vertexB[3*(verticeActual+1)+1];
					p1z = vertexB[3*(verticeActual+1)+2];

					p2x = vertexB[3*(verticeActual-1)];
					p2y = vertexB[3*(verticeActual-1)+1];
					p2z = vertexB[3*(verticeActual-1)+2];
				}

				if(verticeActual == numeroVertices/3){
					p4x = vertexB[3*verticeActual];
					p4y = vertexB[3*(verticeActual)+1];
					p4z = vertexB[3*(verticeActual)+2];
				}
				else{
					p4x = vertexB[3*(verticeActual+lados)];
					p4y = vertexB[3*(verticeActual+lados)+1];
					p4z = vertexB[3*(verticeActual+lados)+2];
				}

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
				//printf("PassouMEIO: %d\n",passou);
				passou++;
			}
		}
		i+=2;
	}



	//preenche vetor de indices-----------------------------------------------------------------------
	i = 0;
	int ponto =	1;
	for(nPontos=1; nPontos < nPontosTotais; nPontos++) {
		xx1=pontos->at(i);
        yy1=pontos->at(i+1);
		xx2=pontos->at(i+2);
        yy2=pontos->at(i+3);
		if(xx1==0.0f && xx2 != 0){
			int pontoAux = ponto-1;
			for(int l = 1; l <= lados;l++){
				indices[j++] = pontoAux;;
				indices[j++] = ponto++;
				if(l != lados){
					indices[j++] = ponto;
				}
				else{
					indices[j++] = pontoAux+1;
				}
				//printf("Indices[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indices[j-3],indices[j-2],indices[j-1]);
			}
		}
		else if(xx1 !=0 && xx2 != 0){
			int ponto1 = ponto-lados;
			int ponto2 = ponto;
			int ponto3 = ponto-lados+1;
			int ponto4 = ponto2;
			for(int l = 1; l <= lados;l++){
				indices[j++] = ponto1++;
				indices[j++] = ponto2++;
				if(l != lados){
					indices[j++]=ponto1;
				}
				else{
					indices[j++]=ponto-lados;
				}
				//printf("Indices[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indices[j-3],indices[j-2],indices[j-1]);
				if(l != lados){
					indices[j++] = ponto4++;
					indices[j++] = ponto4;
					indices[j++] = ponto3++;
				}
				else{
					indices[j++] = ponto4++;
					indices[j++] = ponto;
					indices[j++] = ponto-lados;
				}
				//printf("Indices[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indices[j-3],indices[j-2],indices[j-1]);
			}
			ponto+=lados;
		}
		else if(xx1 != 0 && xx2 == 0){
			int aux = ponto-lados;
			for(int l = 1; l <= lados;l++){
				indices[j++] = aux++;
				indices[j++] = ponto;
				if(l != lados){
					indices[j++] = aux;
				}
				else{
					indices[j++] = ponto-lados;
				}
				//printf("Indices[%d|%d|%d] : %d %d %d\n",j-3,j-2,j-1,indices[j-3],indices[j-2],indices[j-1]);
			}
			ponto++;
		}
		i+=2;
	}

	
	// Gerar VBOs
	glGenBuffers(n, buffers);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
	glBufferData(GL_ARRAY_BUFFER,numeroVertices*sizeof(vertexB), vertexB,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
	glBufferData(GL_ARRAY_BUFFER,numeroVertices*sizeof(normalB), normalB,GL_STATIC_DRAW);
}