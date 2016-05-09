#include <stdio.h>
#include <stdlib.h>

int* genAlphaSortedArray(float alpha, int n){
    int i;
    int* array = calloc(n, sizeof(int));
    for(i = 0; i < n; i++){
        array[i] = i;
    }
    int num_replace = (int)((1 - alpha) * n);
    for(i = 0; i < num_replace; i++){
        int index = (int)(rand() % n);
        if(array[index] == n + 1){
            i--;
            continue;
        }
        array[index] = n + 1;
    }
    return array;
}

int* getRandomSubArrayLocal(int* array, int gamma, int n){
    int index = (int)(rand() % (n - gamma));
    return &array[index];
}

float calcAlphaSortedness(int* sub_array, int gamma, int n){
    (void)n;
    int i;
    int num_unsorted = 0;
    for(i = 0; i < gamma - 1; i++){
        if(sub_array[i] >= sub_array[i + 1]){
            num_unsorted++;
        }
    }
    return (1.0 * (gamma - num_unsorted)) / gamma;
}

int main(int argc, char* argv[]){
    time_t t;
    int i, rep;
    srand((unsigned int) time(&t));

    if(argc != 7){
        printf("Usage is %s array_size alpha beta gamma array_alpha num_repetitions\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    float alpha = atof(argv[2]);
    int beta = atoi(argv[3]);
    int gamma = atoi(argv[4]);
    float alpha_prime = atof(argv[5]);
    int num_repetitions = atoi(argv[6]);

    int* array = genAlphaSortedArray(alpha_prime, n);
    int successes = 0;
    for(rep = 0; rep < num_repetitions; rep++){
        float total_alpha = 0;
        for(i = 0; i < beta; i++){
            int* sub_array = getRandomSubArrayLocal(array, gamma, n);
            total_alpha += calcAlphaSortedness(sub_array, gamma, n);
        }
        float approx_alpha = total_alpha / beta;
        if(approx_alpha >= alpha){
            successes += 1;
        }
    }
    
    printf("Succeeded %d out of %d times (%4f)\n", successes, num_repetitions, (1.0 * successes) / num_repetitions);

    free(array);
    return 0;
}