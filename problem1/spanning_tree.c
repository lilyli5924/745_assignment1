#include "define.h"

struct minVertex* newMinVertex(int v, int distance) {
    struct minVertex* minVertexNode = (struct minVertex*)malloc(sizeof(struct minVertex));
    minVertexNode->vertex = v;
    minVertexNode->distance = distance;

    return minVertexNode;
}

struct VertexSet* createVertexSet(int size) {
    struct VertexSet* minVertexSet = (struct VertexSet*)malloc(sizeof(struct VertexSet));
    minVertexSet->current_size = 0;
    minVertexSet->size = size;
    minVertexSet->list = (struct minVertex**)malloc(size * sizeof(struct minVertex*));

    return minVertexSet;
}

int isEmpty(struct VertexSet* vertexSet) {
    if (vertexSet->current_size == 0) {
        return 1;
    }
    else {
        return -1;
    }
}

struct Index isInVertexSet(struct VertexSet* vertexSet, int v) {
    
    struct Index check;
    // Position will always less than size if v is in this set
    for (int i=0; i<vertexSet->current_size; i++) {
        if (vertexSet->list[i]->vertex == v) {
            check.success = 1;
            check.index = i;
            return check;
        }
    }
    check.success = -1;
    check.index = __INT_MAX__;
    return check;
}

int isIn_heap(int *map, int v) {
    
    if (map[v] != -1) {
        return 1;
    }

    return 0;
}

struct minVertex* extract(struct VertexSet* vertexSet) {
    
    struct minVertex* root = (struct minVertex*)malloc(sizeof(struct minVertex));
    int flag = 0;
    int temp = 0;
    int extract_idx = 0;

    root->distance = __INT_MAX__;
    root->vertex = __INT_MAX__;

    // Find the vertex with minimum distance
    for (int i=0; i<vertexSet->current_size; i++) {
        if (vertexSet->list[i]->distance < root->distance) {
            root = vertexSet->list[i];
            extract_idx = i;
        }
    }
    for (int j=extract_idx; j<vertexSet->current_size; j++) {
        struct minVertex* next_node = vertexSet->list[j+1];
        vertexSet->list[j] = next_node;
    }

    vertexSet->current_size--;

    return root;
}

void heapifyDown(struct VertexSet* vertexSet, int idx_in, int *map) {
    int smallest = idx_in;      // always extract at index 0
    int left = 2 * idx_in + 1;  // left child = 2 * 0 + 1 = 1
    int right = 2 * idx_in + 2; // right child = 2 * 0 + 2 = 2

    if (left < vertexSet->current_size && vertexSet->list[left]->distance < vertexSet->list[smallest]->distance) {
        // if the distance of the first vertex > left child's distance
        smallest = left;
    }
    
    if (right < vertexSet->current_size && vertexSet->list[right]->distance < vertexSet->list[smallest]->distance) {
        // if the distance of the first vertex > right child's distance
        smallest = right;
    }

    if (smallest != idx_in) {
        // Swap the two vertice
        struct minVertex* temp_vertex = vertexSet->list[idx_in];
        vertexSet->list[idx_in] = vertexSet->list[smallest];
        vertexSet->list[smallest] = temp_vertex;

        // Update the index in map too
        map[vertexSet->list[smallest]->vertex] = smallest;
        map[vertexSet->list[idx_in]->vertex] = idx_in;

        // Recursive
        heapifyDown(vertexSet, idx_in, map);
    }
}

struct minVertex* extract_minimum(struct VertexSet* vertexSet, int* map) {
    
    struct minVertex* root = vertexSet->list[0];
    struct minVertex* last_vertex = vertexSet->list[vertexSet->current_size-1];

    vertexSet->list[0] = last_vertex;

    // Update the map array
    map[root->vertex] = -1;
    map[last_vertex->vertex] = 0;   // map[vertex last] will now have its new index = 0

    vertexSet->current_size--;

    if (vertexSet->current_size > 1) {
        heapifyDown(vertexSet, 0, map);
    }

    return root;
}

void printMST(int array[], int n, int weight) {
    for (int i=0; i<n; i++) {
        if (array[i] != -1)
            printf("%d - %d\n", array[i], i);
    }
    printf("Total weight is %d\n", weight);
}

void decreaseDist(struct VertexSet* vertexSet, int *map, int v, int distance) {

    int i = map[v];
    vertexSet->list[i]->distance = distance;
}

void min_spanning_tree(struct Graph* graph, int start_vertex) {
    int vertex_num = graph->V;
    int MST_result[vertex_num];   // store the MST result
    int distance[vertex_num];     // store the distance for vertices
    int MST_weight = 0;

    printf("Size of Vertice is %d\n", vertex_num);
    
    struct VertexSet* newVertexSet = createVertexSet(vertex_num);

    // Adding all other vertices to the set V except the chosen root
    for (int i=0; i<vertex_num; i++) {
        MST_result[i] = -1;
        if (i != start_vertex) {
            distance[i] = __INT_MAX__;
            newVertexSet->list[i] = newMinVertex(i, distance[i]);
        }   
        else {
            // set the distance of the root to be 0
            distance[i] = 0;
            newVertexSet->list[i] = newMinVertex(i, distance[i]);
        }    
    }


    // initially the size of the newVertexSet is vertex_num
    newVertexSet->current_size = vertex_num;

    while(isEmpty(newVertexSet) != 1) {
        // Extract the vertex with minimum value
        struct minVertex* current_node = extract(newVertexSet);
        int u = current_node->vertex;
        MST_weight = MST_weight + current_node->distance;

        // Traverse through all adjacent vertices of u and update distance
        // Obtain the available linked list for u as current_vertex
        struct Node* connect_vertice = graph->llist[u].head;
        
        while(connect_vertice) {
            int v = connect_vertice->vertex;

            struct Index check = isInVertexSet(newVertexSet, v);
            if (check.success == 1 && connect_vertice->weight < distance[v]) {
                distance[v] = connect_vertice->weight;
                MST_result[v] = u;
                newVertexSet->list[check.index]->distance = distance[v];
            }
            connect_vertice = connect_vertice->next;
        }
    } // end of while loop

    printMST(MST_result, vertex_num, MST_weight);

}

void min_spanning_tree_heap(struct Graph* graph, int start_vertex) {
    int vertex_num = graph->V;
    int MST_result[vertex_num];   // store the MST result
    int distance[vertex_num];     // store the distance for vertices
    int MST_weight = 0;

    printf("Size of Vertice is %d\n", vertex_num);

    int *map = (int*)malloc(vertex_num * sizeof(int));
    
    struct VertexSet* newVertexSet = createVertexSet(vertex_num);

    // Adding all other vertices to the set V except the chosen root
    for (int i=0; i<vertex_num; i++) {
        MST_result[i] = -1;
        if (i < start_vertex) {
            distance[i] = __INT_MAX__;
            newVertexSet->list[i+1] = newMinVertex(i, distance[i]);
            map[i] = i+1;
        }
        else if (i > start_vertex) {
            distance[i] = __INT_MAX__;
            newVertexSet->list[i] = newMinVertex(i, distance[i]);
            map[i] = i;
        }
        else {
            distance[start_vertex] = 0;
            newVertexSet->list[0] = newMinVertex(start_vertex, distance[start_vertex]);
            map[start_vertex] = 0;
        }       
    }

    // initially the size of the newVertexSet is vertex_num
    newVertexSet->current_size = vertex_num;

    while(isEmpty(newVertexSet) != 1) {
        // Extract the vertex with minimum value
        struct minVertex* current_node = extract_minimum(newVertexSet, map);
        int u = current_node->vertex;
        MST_weight = MST_weight + current_node->distance;

        // Traverse through all adjacent vertices of u and update distance
        // Obtain the available linked list for u as current_vertex
        struct Node* connect_vertice = graph->llist[u].head;
        
        while(connect_vertice) {
            int v = connect_vertice->vertex;

            if (isIn_heap(map,v) == 1 && connect_vertice->weight < distance[v]) {
                distance[v] = connect_vertice->weight;
                MST_result[v] = u;
                decreaseDist(newVertexSet, map, v, distance[v]);
            }
            connect_vertice = connect_vertice->next;
        }

        // Re-arrange array to make smallest to the top
        for (int i=newVertexSet->current_size/2-1; i>=0; i--) {
            heapifyDown(newVertexSet, i, map);
        }
    } // end of while loop

    printMST(MST_result, vertex_num, MST_weight);

}



void my_func_2(unsigned int dummy_2)
{
    printf("Hello from my function 2 ... ");

    unsigned int i, j;
    for (i=0; i<dummy_2; i++)
        j = (unsigned int) rand();

    printf("after %u iterations the random value is %d\n", dummy_2, j);
}
