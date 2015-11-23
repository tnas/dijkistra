/*
 * File:   main.cpp
 * Author: Robson
 *
 * Created on 9 de Outubro de 2015, 00:30
 */

#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "Grafo.h"

Grafo* lerArquivo(int *vertices, int *arestas, char* nomeArquivo) {
    int i, j, v1, v2, peso;
    FILE *arq;
    char c;
    int nArestas = 0;
    Grafo* g;

    arq = fopen(nomeArquivo, "r");
    if (!arq) {
        fprintf(stderr, "Erro ao abrir o arquivo '%s'.\n", nomeArquivo);
        exit(0);
    }
    //leitura dos vertices (a,b) - passagem para a funÃ§Ã£o Inserir_Aresta.
    fscanf(arq, "%d %d\n", vertices, arestas);
    g = new Grafo(*vertices + 1);

    for (i = 0; i < *arestas; i++) {
        fscanf(arq, "%c %d %d %d\n", &c, &v1, &v2, &peso);
        g->addAresta(v1, v2, peso);
        nArestas++;
        g->addAresta(v2, v1, peso);
        nArestas++;
    }
    *arestas = nArestas;
    fclose(arq);
    return g;
}


