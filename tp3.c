// Trabalho Pratico '3' de Algoritmos e Estrutura de Dados III
// Nome: Alvaro Augusto Alves de Carvalho
// Matricula: 2015430231
#include "tp3.h"



 //funcao para criar um node de uma lista
struct Node* novoNode(unsigned int vertice) {
    struct Node* newNode =
    (struct Node*) malloc(sizeof(struct Node));
    newNode->vertice = vertice;
    newNode->next = NULL;
    return newNode;
}

 // funcao para criar um Grafo de V vertices
struct Grafo* criaGrafo(unsigned int V) {

    struct Grafo* graph = (struct Grafo*) malloc(sizeof(struct Grafo));
    graph->V = V;

    // alocar memoria para um array de V listas encadeadas
    graph->lista = (struct Lista*) malloc((V+1) * sizeof(struct Lista));

    // inicializa cada lista como vazia
    unsigned int i;
    for (i=0;i<V;i++) {
		graph->lista[i].head = NULL;
    }

    return graph; // retorna grafo vazio de V v�rtices
}

/**
 * Desaloca a memoria e destroi um grafo
 *
 **/
void destroiGrafo (struct Grafo* grafo) {
	if (grafo) {
		if(grafo->lista) {
			int i;
			for (i=0;i<grafo->V;i++) {
				struct Node* navegador = grafo->lista[i].head;

				while(navegador) {
					struct Node* temp = navegador;
					navegador = navegador->next;
					free(temp);
				}
				free(navegador);
			}

			free(grafo->lista);
		}
		free(grafo);
	}
}


 /**
 * Adiciona uma aresta a um grafo nao direcionado
 *
 **/

void acrescentaAresta(struct Grafo* grafo, unsigned int A, unsigned int B) {

	// adiciona um Node no inicio da lista de A
    struct Node* newNode = novoNode(B);
    newNode->next = grafo->lista[A].head;
    grafo->lista[A].head = newNode;

    // para grafo nao direcionado: faz o mesmo de B para A
    newNode = novoNode(A);
    newNode->next = grafo->lista[B].head;
    grafo->lista[B].head = newNode;

}

/**
 * Algoritmo de busca em profundidade (Depth First Search)
 * Disponivel nos repositorios do DCC da UFMG
 **/

void DFS(unsigned int i, unsigned int * visited, struct Grafo* grafo) {

	struct Node* navegador = grafo->lista[i].head;

    visited[i] = 1;

    while(navegador!=NULL) {
        i = navegador->vertice;
        if (!visited[i])
            DFS(i, visited, grafo);

        navegador = navegador->next;
    }
}

/**
 * Inicializa um vetor de tamanho 'tamanho' para o valor informado.
 * Se o valor informado for <0, inicializa cada elemento com o indice
 **/
void inicializaVetor(int * vetor, int tamanho, int valor) {
	int i;
	for (i=0;i<tamanho;i++) {
		vetor[i] = (valor < 0) ? i : valor;
	}
}

/**
 * Checa adjacencia de servidores para verificar se o servidor em questao pode
 * ser ativo no round definido
 * @param vertice => servidor em questao
 * @param updateRound => o round de atualizacao a ser verificado
 * @return 1 caso verdadeiro, 0 caso falso
 */
int checkServerAdjacency(struct Grafo * grafo, int updateRound, unsigned int vertice) {
    struct Node* navegador = grafo->lista[vertice].head;
    while (navegador!=NULL) {
        if (navegador->updateRound == updateRound) {
            return 0;
        }
        navegador = navegador->next;
    }
    return 1;
}

	struct Grafo* lerEntradaCriarGrafo() {
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

    return grafo;

}

void printGraph(struct Grafo* g) {
	int N = g->V;
	int i;
	printf("Num Vertices: %d\n", N);
	for (i=1;i<=N;i++) {
		struct Node* navegador = g->lista[i].head;
		printf("Iteracao %d\n",i);
		while(navegador!=NULL) {
			printf("Vertice: %d -> %d\n", i, navegador->vertice);
			navegador = navegador->next;
		}
	}
}

/**
 * Algoritmo guloso para colorir um dado grafo
 * O algoritmo primeiro colore o primeiro vertice, depois passa vertice a vertice colorindo utilizando a menor cor possivel
 * as cores na verdade sao um array de 0 a N, onde N eh o numero de vertices.
 * Para cada Vertice, o algoritmo checa todos os seus adjacentes e verifica se algum ja foi colorido. Se sim, marca aquela cor como indisponivel
 * posteriormente, colore o vertice em questao com a menor cor possivel que estiver disponivel.
 */
void GreedySolve(struct Grafo* grafo) {

	int N = grafo->V;
	int i;
	int result[N+1]; // array de cores
	result[1] = 1; // primeira cor para o primeiro vertice

	for (i = 2;i<=N;i++) {
		result[i] = -1; // todos os vertices remanescentes nao tem cor inicialmente
	}

	int available[N+1];
	inicializaVetor(available, N+1, 1); // booleano que lista as cores disponiveis

	int u;
	// atribuir cores aos proximos V-1 vertices (ou servidores)
	for(u = 2; u<=N;u++) {

		// atribuir como assigned todos os vertices adjacentes
		struct Node* navegador = grafo->lista[u].head;
		while (navegador!=NULL) {
			if(result[navegador->vertice] != -1) {
				available[result[navegador->vertice]] = 0; // cor indisponivel
			}
			navegador = navegador->next;
		}
		int color;
		for (color = 1; color <= N; color++) {
			if (available[color] == 1)
				break;
		}
		result[u] = color;
		navegador = grafo->lista[u].head;
		while (navegador!=NULL) {
			if(result[navegador->vertice] != -1) {
				available[result[navegador->vertice]] = 1; // reinicia os valores para a proxima iteracao
			}
			navegador = navegador->next;
		}
		free(navegador);
	}
	
	printAnswer(result, N);
	
	destroiGrafo(grafo);

}

/**
 * Imprime as respostas encontradas nos arquivos conforme enunciado
 * o numero de rodadas deve ser impresso no arquivo "rodadas.txt"
 * e a configuracao de alocacao dos servidores no arquivo "alocacao.txt"
 */
void printAnswer(int * result, int N) {

	FILE * rodadas = fopen(RODADAS, writeMode);
	FILE * alocacao = fopen(ALOCACAO, writeMode);
	
	if (!rodadas || !alocacao) {
		printf("Erro ao abrir arquivos de saida\n");
		return;
	}
	
	int numRodadas = 0;
	int i;
	for (i = 1; i <=N; i++) {
		if (numRodadas < result[i]) {
			numRodadas = result[i];
		}
		//printf("Vertice: %d\n", grafo->lista[i].head->vertice);
		fprintf(alocacao, "%d %d\n", i, result[i]);
	}
	
	fprintf(rodadas,"%d\n", numRodadas);
	
	fclose(rodadas);
	fclose(alocacao);

}

