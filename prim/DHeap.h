/*
 * DHeap.h
 *
 *  Created on: Oct 1, 2015
 *      Author: erika
 */

#ifndef DHEAP_H_
#define DHEAP_H_

class Vertice;
class DHeap {
public:
    int d;
    int tamanhoAtual;
    int tamanhoMaximo;
    Vertice **vetor;

	DHeap(int capacidade, int numFilhos);
	virtual ~DHeap();

	void insert(Vertice* v);
	Vertice* deleteMin();
	void decreaseKey(Vertice* vertice, int distanciaVertice);

private:
	bool estaVazio();
	bool estaCheio();
	void Esvazia();
	int ObtemPai(int i);
	int ObtemFilhoOrdemK(int i, int k);

	Vertice* Delete(int posicao);
	void percolateDown(int posicao);
	int menorFilho(int posicao);
	void percolateUp(int posicao);
	void printHeap();
};

#endif /* DHEAP_H_ */

