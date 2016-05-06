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
        if(index == 0){
            array[index] = array[index + 1] + 1;
        }
        else{
            array[index] = array[index - 1] - 1;
        }
    }
    return array;
}

int* getRandomSubArrayLocal(int* array, int gamma, int n){
    int index = (int)(rand() % (n - gamma));
    return &array[index];
}

int* getRandomSubArrayFile();

float calcAlphaSortedness(int* sub_array, int gamma){
    int i;
    int num_unsorted = 0;
    for(i = 0; i < gamma - 1; i++){
        if(sub_array[i] > sub_array[i+1]){
            num_unsorted++;
        }
    }
    return (1.0 * (gamma - num_unsorted)) / gamma;
}

int main(int argc, char* argv[]){
    time_t t;
    int i;
    srand((unsigned int) time(&t));

    if(argc != 6){
        printf("Usage is %s array_size alpha beta gamma array_alpha\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    float alpha = atof(argv[2]);
    int beta = atoi(argv[3]);
    int gamma = atoi(argv[4]);
    float alpha_prime = atof(argv[5]);

    int* array = genAlphaSortedArray(alpha_prime, n);

    float total_alpha = 0;
    for(i = 0; i < beta; i++){
        int* sub_array = getRandomSubArrayLocal(array, gamma, n);
        total_alpha += calcAlphaSortedness(sub_array, gamma);
    }
    float approx_alpha = total_alpha / beta;
    if(approx_alpha >= alpha){
        printf("True\n");
    }
    else{
        printf("False\n");
    }

    free(array);
    return 0;
}