/*
 * Grafo.h
 *
 *  Created on: Oct 22, 2015
 *      Author: erika
 */

#ifndef GRAFO_H_
#define GRAFO_H_

#include <stdlib.h>
#include "Vertice.h"

class Grafo {
public:
    Vertice** tabela;
	int nVertices;

	Grafo(int piNVertices){
		int i;
		nVertices = piNVertices;
		tabela = (Vertice**) malloc( nVertices * sizeof(Vertice*) );

	    for (i = 0; i < nVertices; i++){
	    	tabela[i] = new Vertice(i);
	    }
	}

	virtual ~Grafo(){
		int i;
	    for (i = 0; i < nVertices; i++){
	    	delete(tabela[i]);
	    }
	    free(tabela);
	}

	void addAresta(Vertice* v1, Vertice* v2, int valor){
		tabela[v1->numero]->addAresta(v2, valor);
		tabela[v2->numero]->addAresta(v1, valor);
	}
	void addAresta(int v1, int v2, int valor){
		if( tabela[v1] == NULL ){
			fprintf(stderr, "ERROR: Vertice %d nulo no grafo\n\n", v1);
			exit(1);
		}
		if( tabela[v2] == NULL ){
			fprintf(stderr, "ERROR: Vertice %d nulo no grafo\n\n", v2);
			exit(1);
		}
		tabela[v1]->addAresta(tabela[v2], valor);
//		tabela[v2]->addAresta(tabela[v1], valor);
	}
	int valorAresta(int v1, int v2){
		return tabela[v1]->valorAresta(tabela[v2]);
	}
};

#endif /* GRAFO_H_ */
