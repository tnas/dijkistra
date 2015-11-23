/*
 * Dijkstra.h
 *
 *  Created on: Oct 13, 2015
 *      Author: erika
 */

#ifndef PRIM2_H_
#define PRIM2_H_

class Grafo;

int primMST(int nVertices, Grafo* g);
int primMSTHeap(int nVertices, Grafo* g, int nFilhos);
int primMSTHeap2(int nVertices, Grafo* g, int nFilhos);
#endif 
