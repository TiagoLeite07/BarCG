#ifndef _SolidoRevolucao_H_
#define _SolidoRevolucao_H_

#include <vector>

class SolidoRevolucao{
private:
	int verticeSolidRev;
	unsigned int *indices;
	GLuint buffers[3];
public:
	void desenhaSolidRev();
	void solidRevolucao(int lados, std::vector<float>* pontos);
	SolidoRevolucao(int lados,std::vector<float>* points);
	SolidoRevolucao();
};
//void desenhaSolidRev();
//void solidRevolucao(int lados, std::vector<float>* pontos);

#endif