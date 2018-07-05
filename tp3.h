#include <stdio.h>
#include <stdlib.h>

#define nline printf("\n")
#define RODADAS "rodadas.txt"
#define ALOCACAO "alocacao.txt"
#define writeMode "w+"

/**  Begin Declaring Structs **/

struct Grafo
{
    int V; // numero de vertices
    struct Lista* lista;
};

struct Lista
{
    struct Node *head; // ponteiro pra cabeca da lista (topo)
};

struct Node
{
	unsigned int vertice;
    int updateRound;
    struct Node* next;
};

/**************************************************/


 /**            Funcoes                **/

struct Node* novoNode(unsigned int vertice);
struct Grafo* criaGrafo(unsigned int V);
void destroiGrafo (struct Grafo* grafo);
void acrescentaAresta(struct Grafo* grafo, unsigned int A, unsigned int B);
void inicializaVetor(int * vetor, int tamanho, int valor);
struct Grafo* lerEntradaCriarGrafo() ;
void printGraph(struct Grafo* g);
void GreedySolve(struct Grafo* grafo);
void printAnswer(int * result, int N);
