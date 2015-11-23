/*
 * Vertice.h
 *
 *  Created on: Oct 1, 2015
 *      Author: erika
 */

#ifndef VERTICE_H_
#define VERTICE_H_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <list>
using namespace std;

class Vertice;
typedef pair<Vertice*,int> aresta;

#define MAX_D 30
#define INFINITO 999999999

class Vertice {
public:
	int numero;
	int distancia;
	int ultimoVertice;
	list<aresta> adj;

	Vertice(int num){ numero = num; distancia = INFINITO; ultimoVertice = -1; }
	virtual ~Vertice(){	};

	void addAresta(Vertice* v, int valor){
		adj.push_front(make_pair(v, valor));
	}
	int valorAresta(Vertice* v){
		list<aresta>::iterator it;
		for( it = adj.begin() ; it != adj.end(); it++ ){
			if( (*it).first == v )
                            return (*it).second;
		}
		return INFINITO;
	}

	void print(){
        printf("%3d \t\t %9d\t%6d\n", numero, distancia, ultimoVertice);
//        printf("%3d \t|\t %9d\t|%6d\n", numero, distancia, ultimoVertice);
	}
};

#endif /* VERTICE_H_ */
