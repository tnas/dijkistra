/*
 * io.h
 *
 *  Created on: Oct 13, 2015
 *      Author: erika
 */

#ifndef IO_H_
#define IO_H_

class Grafo;

	Grafo* lerArquivo(int *vertices, int *arestas, char* nomeArquivo);

//	int **cria_matriz(int nlinhas, int ncolunas);
	void libera_matriz(int **matriz, int nlinhas);
	void imprime_matriz(int **matriz, int n);


#endif /* IO_H_ */
