#include "define.h"

#include <sys/time.h>
#include <sys/resource.h>


int main(int argc, char *argv[])
{
    //argc[0]: executable file name
    //argc[1]: input filename
    //argc[2]: format 0/1 for linked list and binary heap

    clock_t my_time;

    const char* filename = argv[1];

    char format = *argv[2];

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

    unsigned int dummy_2 = (unsigned int) rand() % (1 << 25);
    my_time = clock();
    if (format == '0') {
        min_spanning_tree(graph, start_vertex);
        printf("format is Linked List\n");
        printf("Random generated number is %d\n", start_vertex);
    }else {
        min_spanning_tree_heap(graph, start_vertex);
        printf("format is Binary Heap\n");
        printf("Random generated number is %d\n", start_vertex);
    }
    my_time = clock() - my_time;
    printf ("It took %f seconds for min_spanning_tree to complete.\n",
            ((float)my_time)/CLOCKS_PER_SEC);
    printf("\n");

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Memory usage: %ld KB\n", usage.ru_maxrss);

    return 0;
}
