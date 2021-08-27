#include "define.h"

#include <sys/time.h>
#include <sys/resource.h>


int main(int argc, char *argv[])
{
    //argc[0]: executable file name
    //argc[1]: input filename
    //arcv[2]: destination node
    //argc[3]: format 0/1 for linked list and binary heap

    clock_t my_time;

    const char* filename = argv[1];

    char format = *argv[4];

    int i = 0;

    // initialize the random number generator
    srand((int)time(NULL));
    printf("\n");
    

    struct Edge input[] = {
        {0,1,4}, {0,7,8}, {1,2,8}, {1,7,11}, {2,3,7}, {2,8,2}, {2,5,4}, {3,4,9},
        {3,5,14}, {4,5,10}, {5,6,2}, {6,7,1}, {6,8,6}, {7,8,7}
    };


    printf("CLOCKS PER SEC is %u\n\n", (unsigned int)CLOCKS_PER_SEC);

    unsigned int dummy_1 = (unsigned int) rand() % (1 << 25);
    my_time = clock();
    struct Graph* graph = printGraph(filename);
    my_time = clock() - my_time;
    printf ("It took %f seconds for printGraph to complete.\n",
            ((float)my_time)/CLOCKS_PER_SEC);
    printf("\n");

    int start_vertex = rand() % graph->V; // generate a random number from 0 to num of vertex
    //int start_vertex = 20;

    char *d;
    long arg_d = strtol(argv[3], &d, 10);
    int dest_node = arg_d;

    char *s;
    long arg_s = strtol(argv[2], &s, 10);
    int src_node = arg_s;

    unsigned int dummy_2 = (unsigned int) rand() % (1 << 25);
    my_time = clock();
    if (format == '0') {
        dijkstra_shortest_path(graph, src_node, dest_node);
        printf("format is Linked List\n");
        printf("source node is %d, destination node is %d\n", src_node, dest_node);
    }else {
        dijkstra_shortest_path_heap(graph, src_node, dest_node);
        printf("format is Binary Heap\n");
        printf("source node is %d, destination node is %d\n", src_node, dest_node);
    }
    my_time = clock() - my_time;
    printf ("It took %f seconds for dijkstra_shortest_path to complete.\n",
            ((float)my_time)/CLOCKS_PER_SEC);
    printf("\n");


    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Memory usage: %ld KB\n", usage.ru_maxrss);

    return 0;
}
