#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "DHeap.h"
#include "Vertice.h"
#include "Grafo.h"

int minKey(int nVertices, int *key, bool mstSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 1; v <= nVertices; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

int somaDistancia(int nVertices, int *key) {
    int total, v;
    total = 0;
    for (v = 1; v <= nVertices; v++) {
        total += key[v];
    }
    return total;
}

int somaDistanciaHeap(int *parent, int nVertices, Grafo *g) {
    int valor = 0;
    int i;
    for (i = 1; i <= nVertices; i++) {
        if (g->valorAresta(i, parent[i]) != INFINITO) {
            valor += g->valorAresta(i, parent[i]);
        }
    }
    return valor;
}

int somaDistanciaHeap2(int nVertices, Grafo *g) {
    int valor = 0;
    int i;
    for (i = 1; i <= nVertices; i++) {
        if (g->valorAresta(g->tabela[i]->numero, g->tabela[i]->ultimoVertice) != INFINITO) {
            valor += g->valorAresta(g->tabela[i]->numero, g->tabela[i]->ultimoVertice);
        }
    }
   return valor;
}

void printMST(int *parent, int nVertices, Grafo *g) {
    //    printf("Pesos das arestas\n");
    int valor = 0;
    int i;
    for (i = 1; i <= nVertices; i++) {
        if (g->valorAresta(i, parent[i]) != INFINITO) {
            printf("%d - %d    %d \n", parent[i], i, g->valorAresta(i, parent[i]));
        }
    }
}

int primMST(int nVertices, Grafo* g) {
    bool mstSet[nVertices + 1]; 
    int *key; 
    key = (int*) malloc(nVertices * sizeof (int));
    int *parent;
    int v, count, i;
    printf("Aqui");
    for (i = 1; i <= nVertices; i++) {
        key[i] = INFINITO;
        mstSet[i] = false;
        
    }
    key[1] = 0;
    parent = (int*) malloc(nVertices * sizeof (int));
    parent[1] = -1;
    
    for (count = 1; count <= nVertices; count++) {
        int u = minKey(nVertices, key, mstSet);
        mstSet[u] = true;
        for (v = 1; v <= nVertices; v++) {
            
            if (mstSet[v] == false && g->valorAresta(u, v) < key[v]) {
                parent[v] = u;
                key[v] = g->valorAresta(u, v);
            }
        }
    }
    printf("Aqui");
    return somaDistancia(nVertices, key);
}

int primMSTHeap(int nVertices, Grafo* g, int nFilhos) {
    DHeap heap(nVertices, nFilhos);
    Vertice *u, *v;
    int i;
    list<aresta>::iterator it;
    bool mstSet[nVertices + 1]; 
    int *parent; 
    g->tabela[1]->distancia = INFINITO;
    g->tabela[1]->ultimoVertice = 0;
    heap.insert(g->tabela[1]);
    for (i = 1; i <= nVertices; i++) {
        mstSet[i] = false;
    }
    parent = (int*) malloc(nVertices * sizeof (int));
    parent[1] = -1;
    printf("aqui");
    while (heap.tamanhoAtual > 0) {
        u = heap.deleteMin();
        mstSet[u->numero] = true;
        for (it = u->adj.begin(); it != u->adj.end(); it++) {
            v = (*it).first;
            if (v->distancia == INFINITO && mstSet[v->numero] == false) {
                v->distancia = g->valorAresta(v->numero, u->numero);
                v->ultimoVertice = u->numero;
                parent[v->numero] = u->numero;
                heap.insert(v);
            } else if (v->distancia > g->valorAresta(v->numero, u->numero) && mstSet[v->numero] == false) {
                v->ultimoVertice = u->numero;
                parent[v->numero] = u->numero;
                heap.decreaseKey(v, g->valorAresta(v->numero, u->numero));
            }
        }
    }
    printf("aqui");
    return somaDistanciaHeap(parent, nVertices, g);
}


int primMSTHeap2(int nVertices, Grafo* g, int nFilhos) {

    DHeap heap(nVertices, nFilhos);
    Vertice *u, *v;
    int i;
    list<aresta>::iterator it;
    bool mstSet[nVertices + 1]; 
    g->tabela[1]->distancia = INFINITO;
    g->tabela[1]->ultimoVertice = 0;
    heap.insert(g->tabela[1]);
    for (i = 1; i <= nVertices; i++) {
        mstSet[i] = false;
    }
    while (heap.tamanhoAtual > 0) {
        u = heap.deleteMin();
        mstSet[u->numero] = true;
        for (it = u->adj.begin(); it != u->adj.end(); it++) {
            v = (*it).first;
            if (v->distancia == INFINITO && mstSet[v->numero] == false) {
                v->distancia = g->valorAresta(v->numero, u->numero);
                v->ultimoVertice = u->numero;
                heap.insert(v);
            } else if (v->distancia > g->valorAresta(v->numero, u->numero) && mstSet[v->numero] == false) {
                v->ultimoVertice = u->numero;
                heap.decreaseKey(v, g->valorAresta(v->numero, u->numero));
            }
        }
    }
    return somaDistanciaHeap2(nVertices, g);
}
