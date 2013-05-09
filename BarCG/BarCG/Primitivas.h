#include "SolidoRevolucao.h"

void desenhaPlano();
void desenhaCubo();
void cilindro(float raio, float altura, int nlados, float seccoes);
void cubo(float altura);
void esfera(float raio,float seccoes,float lado);
void plano (float altura, float comprimento);
std::vector<float> preparaEsfera(float raio, int seccoes);
std::vector<float> preparaCilindro(float altura, float raio, int seccoes);
void preparaCubo(float altura);
void preparaPlano (float altura, float comprimento);