#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int vertex;
    struct node* next;
} node;

typedef struct Graph {
    int numVertices;
    node** adjLists;
} Graph;

node* createNode(int v) {
    node* newNode = malloc(sizeof(node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(node*));
   
    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int is_directed) {
    node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    if (!is_directed) {
        newNode = createNode(src);
        newNode->next = graph->adjLists[dest];
        graph->adjLists[dest] = newNode;
    }
}

void printGraph(Graph* graph) {
    int v;
    printf("\nLista de adjacencia\n");
    for (v = 0; v < graph->numVertices; v++) {
        node* temp = graph->adjLists[v];
        printf("\nVertice %d-> ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void vizinhaca(Graph* graph) {
    int v;
    
    printf("\nLista de Vizinhaca\n");
    for (v = 0; v < graph->numVertices; v++) {
        node* temp = graph->adjLists[v];
        printf("Vertice %d:", v);
        while (temp) {
            printf(" %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void grau(Graph* graph, int is_directed) {
 int v, grau[graph->numVertices], grauDirecional[graph->numVertices][2];

    for(int i = 0; i < graph->numVertices; i++){
        for(int j = 0; j < 2; j++){
            grauDirecional[i][j] = 0;
        }
        grau[i] = 0;
    }
    printf("\nLista de Grau\n");
    for (v = 0; v < graph->numVertices; v++) {
        node* temp = graph->adjLists[v];
        while (temp) {
            if(!is_directed){
                grau[v]++;
            }else{
                grauDirecional[v][0]++;
                grauDirecional[temp->vertex][1]++;
            }
            temp = temp->next;
        }
        
    }
    for (v = 0; v < graph->numVertices; v++) {
        node* temp = graph->adjLists[v];
        if (is_directed){
            while (temp) {
                printf("Vertice %d: Entrada: %d; Saida: %d\n", v, grauDirecional[temp->vertex][1], grauDirecional[v][0]);
                temp = temp->next;
            }
        }else{
            printf("Vertice %d: %d\n", v, grau[v]);
        }    
    }
}

Graph* complementGraph(Graph *graph) {
    Graph* complement = createGraph(graph->numVertices);
    
    int v;
    for (v = 0; v < graph->numVertices; v++) {
        node *temp = graph->adjLists[v];
        
        // Criar uma matriz booleana para verificar quais vértices já foram adicionados
        int* addedVertices = (int*)calloc(graph->numVertices, sizeof(int));
        
        while (temp) {
            addedVertices[temp->vertex] = 1;
            temp = temp->next;
        }
        
        int i;
        for (i = 0; i < graph->numVertices; i++) {
            if (i != v && addedVertices[i] == 0) {
                addEdge(complement, v, i, 0);
            }
        }
        
        free(addedVertices);
    }
    

    for (v = 0; v < complement->numVertices; v++) {
        node* temp = complement->adjLists[v];
        printf("\nVertice %d-> ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
    
    
    return complement;
}

int main() {
    int op, vertices, edges, i, src, dest, is_directed;
    printf("-----Lista de Adjacencia-----\n");
    printf("0 - Nao orientado \n");
    printf("1 - Orientado \n");
    printf("Escolha qual tipo do seu grafo: \n");
    scanf("%d", &is_directed);
    printf("Digite o numero de vertices: ");
    scanf("%d", &vertices);
    printf("Digite o numero de arestas: ");
    scanf("%d", &edges);

    Graph* graph = createGraph(vertices);
    Graph* vizinho = createGraph(vertices);
    for (i = 0; i < edges; i++) {
        printf("Entre com a aresta %d origem e destino (exemplo: 1 2): ", i);
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest, is_directed);
        addEdge(vizinho, src, dest, 0);
    }

    do{
        printf("------------------------------\n");
        printf("1- Apresentar a lista resultada do grafo\n");
        printf("2- Apresentar a ordem e o tamanho do grafo\n");
        printf("3- Apresentar a vizinhanca e grau de todos os vertices\n");
        printf("4- Apresentar Complemento\n");
        printf("0- Sair\n");
        printf("Informe a opcao desejada:\n");
        
        scanf("%d", &op);
        switch(op){
            case 1:
                printGraph(graph);
            break;
            case 2:
                //Exibindo o tamanho e ordem do grafo
                printf("------------------------------\n");
                printf("O seu grafo tem ordem %d e tamanho %d. \n", vertices, edges);
                break;
            break;
            case 3:
                //Exibindo os graus e vizinhaca dos vertices
                vizinhaca(vizinho);
                grau(graph, is_directed);
            break;
            case 4:
                complementGraph(graph);
                break;
            case 0:
                
            break;
        }
    }while(op != 0);
    return 0;
}