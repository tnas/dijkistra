/*
 * DHeap.cpp
 *
 *  Created on: Oct 1, 2015
 *      Author: erika
 */
#include <stdlib.h>
#include <stdio.h>

#include "Vertice.h"
#include "DHeap.h"

DHeap::DHeap(int capacidade, int numFilhos) {
    int i;
    tamanhoAtual = 0;
    d = numFilhos;
    tamanhoMaximo = capacidade + 1;
    vetor = (Vertice**) malloc((capacidade + 1) * sizeof (Vertice*));
    for (i = 0; i < capacidade + 1; i++) vetor[i] = NULL;
}

DHeap::~DHeap() {
    free(vetor);
}

void DHeap::insert(Vertice* vertice) {
    if (estaCheio()) {
        fprintf(stderr, "ERROR: vetor Out of Bounds\n");
        return;
    }
    int posicao = tamanhoAtual;
    tamanhoAtual++;
    vetor[posicao] = vertice;
    percolateUp(posicao);
}

Vertice* DHeap::deleteMin() {
    if (estaVazio()) {
        fprintf(stderr, "ERROR: vetor Underflow\n");
        return NULL;
    }
    return Delete(0);
}

void DHeap::decreaseKey(Vertice* vertice, int distanciaVertice) {
    int posHeap = -1;
    int i;
    for (i = 0; i < tamanhoAtual; i++) {
        if (vetor[i]->numero == vertice->numero) {
            posHeap = i;
            break;
        }
    }
    vertice->distancia = distanciaVertice;
    percolateUp(posHeap);
}

bool DHeap::estaVazio() {
    return tamanhoAtual == 0;
}

bool DHeap::estaCheio() {
    return tamanhoAtual == tamanhoMaximo;
}

void DHeap::Esvazia() {
    tamanhoAtual = 0;
}

int DHeap::ObtemPai(int i) {
    return (i - 1) / d;
}

int DHeap::ObtemFilhoOrdemK(int i, int k) {
    return d * i + k;
}

Vertice* DHeap::Delete(int posicao) {
    if (estaVazio()) {
        fprintf(stderr, "ERROR: vetor Underflow\n");
        return 0;
    }
    Vertice* chaveItem = vetor[posicao];
    vetor[posicao] = vetor[tamanhoAtual - 1];
    tamanhoAtual--;
    percolateDown(posicao);
    return chaveItem;
}

int DHeap::menorFilho(int posicao) {
    int melhorFilho = ObtemFilhoOrdemK(posicao, 1);
    int k = 2;
    int filhocandidato = ObtemFilhoOrdemK(posicao, k);
    while ((k <= d) && (filhocandidato < tamanhoAtual)) {
        if (vetor[filhocandidato]->distancia < vetor[melhorFilho]->distancia)
            melhorFilho = filhocandidato;
        k++;
        filhocandidato = ObtemFilhoOrdemK(posicao, k);
    }
    return melhorFilho;
}

void DHeap::percolateDown(int posicao) {
    int filho;
    Vertice* tmp = vetor[posicao];
    for (; ObtemFilhoOrdemK(posicao, 1) < tamanhoAtual; posicao = filho) {
        filho = menorFilho(posicao);
        if (vetor[filho]->distancia < tmp->distancia)
            vetor[posicao] = vetor[filho];
        else
            break;
    }
    vetor[posicao] = tmp;
}

void DHeap::percolateUp(int posicao) {
    Vertice* tmp = vetor[posicao];
    for (; posicao > 0 && tmp->distancia < vetor[ObtemPai(posicao)]->distancia; posicao = ObtemPai(posicao))
        vetor[posicao] = vetor[ ObtemPai(posicao) ];
    vetor[posicao] = tmp;
}

void DHeap::printHeap() {
    printf("\nHeap:\n");
    for (int i = 0; i < tamanhoAtual; i++)
        printf("%3d: %3d\n", vetor[i]->numero, vetor[i]->distancia);
    printf("\n\n");
}

