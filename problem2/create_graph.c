#include "define.h"

struct Node* newAdjNode(int vertex, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;

    return newNode;
}

//struct Graph* createGraph(int V, int dest, int src, int weight, int n) {
struct Graph* createGraph(const char* FILENAME) {
    FILE *fp;
    int i = 0;

    fp = fopen(FILENAME, "r");
    int line_idx = 0;
    int edge_idx = 0;
    int dest, src, weight;
    int line_count = 0;

    fscanf(fp, "%d", &i);

    int vertex_num = i;
    printf("vertex num is %d\n", i);

    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = vertex_num;
    graph->llist = (struct LList*)malloc(vertex_num*sizeof(struct LList));

    // initialize each adjacency list as empty by making head null
    for (i=0; i<vertex_num; i++) {
        graph->llist[i].head = NULL;   //foo->bar = (*foo).bar where foo is address of struct and *foo is the content of the struct
    }

    while(!feof(fp)) {
        fscanf(fp, "%d", &i);
        if (line_idx == 0) {
            dest = i;
            line_idx++;
        }
        else if (line_idx == 1) {
            src = i;
            line_idx++;
        }
        else if (line_idx == 2) {
            weight = i;
            line_idx = 0;
            edge_idx++;

            struct Node* newNode = newAdjNode(dest, weight);
            // point next new node to the current head
            newNode->next = graph->llist[src].head;
            // point the head to the new node
            graph->llist[src].head = newNode;

            // since graph is undirected, add an edge from dest to src also
            newNode = newAdjNode(src, weight);
            newNode->next = graph->llist[dest].head;
            graph->llist[dest].head = newNode;

        }
    }
    return graph;
}


struct Graph* printGraph(const char* FILENAME) {
    
    int v;

    struct Graph* graph = createGraph(FILENAME);

    for (v=0; v<graph->V; v++) {
        struct Node* pVertex = graph->llist[v].head;
/*        printf("\n Adjacency list of vertext %d\n head ", v);
        while(pVertex) {
            printf("-> %d, weight: %d\n", pVertex->vertex, pVertex->weight);
            pVertex = pVertex->next;
        }*/

    }
    return graph;
}


void my_func_1(unsigned int dummy_1)
{
    printf("Hello from my function 1 ... ");

    unsigned int i, j;
    for (i=0; i<dummy_1; i++)
        j = (unsigned int) rand();

    printf("after %u iterations the random value is %d\n", dummy_1, j);
}
