#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "code.h"

#define NB_OCT 32

extern float fitness_key(Bitkey* key);
extern void enter_the_matrix(Bitkey* k);

void crossover(const Bitkey parent1, const Bitkey parent2, const Bitkey parent3, Bitkey *child) {
    int res = 0;
    for(int i = 0; i < NB_OCT; ++i) {
        res = parent1.values[i] + parent2.values[i] + parent3.values[i];
        if(res <= 1) {
            child->values[i] = 0;
            continue;
        }
        child->values[i] = 1;
    }
}

void print_bitkey(const Bitkey key) {
    for (int i = 0; i < NB_OCT; i++) {
        printf("%d ", key.values[i]);
    }
    printf("\n");
}

void generate_random_key(Bitkey* key) {
    for(int i = 0; i < NB_OCT; i++) {
        key->values[i] = rand() % 2;
    }
}

int compare_keys(const void* first, const void* second) {
    float fitness_diff = fitness_key((Bitkey*)first) - fitness_key((Bitkey*)second);
    return (int)(fitness_diff);
}

void sort_key_array(Bitkey* keys, int size) {
    qsort(keys, size, sizeof(Bitkey), compare_keys);
}

void generate_key_generation(Bitkey* B, int d) {
    if (d == 0) {
        generate_random_key(B);
        return;
    }

    Bitkey array[8];
    for (int i = 0; i < 8; ++i) {
        generate_random_key(&array[i]);  // Generate a random key at each level
        generate_key_generation(&array[i], d - 1);
    }

    // Sort the array of keys
    qsort(array, 8, sizeof(Bitkey), compare_keys);

    // Perform crossover on the first three keys
    crossover(array[0], array[1], array[2], B);
    print_bitkey(*B);
}


int main(int argc, char* argv[]) {

    srand(time(NULL));
    Bitkey B;
    Bitkey key1 = {{1, 1, 0, 1, 0, 0, 1, 0}};
    Bitkey key2 = {{1, 0, 1, 1, 0, 1, 1, 0}};
    Bitkey key3 = {{1, 0, 1, 1, 0, 0, 1, 1}};
    //Bitkey B;
    /*for(int i = 0; i < 3; ++i) {
        print_bitkey(array[i]);
        printf("\n");
    }
    printf("-----------\n");*/
    //crossover(key1, key2, key3, &child);
    /*for(int i = 0; i < 5; ++i) {
        generate_random_key(&child);
        print_bitkey(child);
    }*/
    generate_key_generation(&B, 7);
    enter_the_matrix(&B);
    /*sort_key_array(array, 3);
    for(int i = 0; i < 3; ++i) {
        print_bitkey(array[i]);
        printf("\n");
    }*/
    return 0;
}