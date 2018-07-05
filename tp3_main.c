#include "tp3.h"



int main () {

	// Algoritmo Guloso

	int N; // numero de servidores
	int M; // numero de conexoes
	int S1, S2; // conexao entre servidores

	scanf("%d", &N);
	struct Grafo* grafo = criaGrafo(N);

	scanf("%d", &M);
	int i;
	for (i = 0; i < M; i++) {
		scanf("%d %d", &S1, &S2);
		acrescentaAresta(grafo, S1, S2);
	}

	//printGraph(grafo);
	//nline;
	
	GreedySolve(grafo);

	return 0;
}
