// A C / C++ programa de algoritmo de caminho de Dijkstra.
// O programa é para grafo representado como uma matriz de adjacência.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <list>

#include "io.h"
#include "Grafo.h"
#include "prim2.h"

using namespace std;
// Programa piloto para testar a funçã

int main() {
    int nVertices, nArestas, fo, i;
    Grafo* g;
    int noInicial;
    float tempo_inicial, tempo_final, tempo_total = 0;
    char* c = "C:/cidades/dmxa1801.stp";
    tempo_total = 0;
    g = lerArquivo(&nVertices, &nArestas, c);
    fprintf(stderr, "O grafo tem %d vertices e %d arestas\n", nVertices, nArestas);
    tempo_final = tempo_inicial = clock();
    fo = primMST(nVertices, g);
    //        fo = primMSTHeap(nVertices, g, 3);
    //        fo = primMSTHeap2(nVertices, g, 3);
    tempo_final = clock(); // / CLOCKS_PER_SEC;
    tempo_total = ((tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;
    printf("funcao objetivo = %d\t  em %.5f\n", fo, tempo_total);
    getchar();
    return 0;
}
