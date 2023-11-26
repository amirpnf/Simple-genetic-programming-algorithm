#include <stdio.h>
#include <stdlib.h>


int difference(const void* first, const void* second) {
    return *((int*) second) - *((int*) first);
}

int main(int argc, char* argv[]) {
    int array[] = {4, 6, 7, 4, 2, 3};
    qsort(array, 6, sizeof(int), difference);
    for(int i = 0; i < 6; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}