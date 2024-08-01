#include <stdio.h>




int main () {

    int vetor[10] = {1,2,3,4,5,6,7,8,9,10};
    int n = 10;
    int aux = 0;

    for (int x = 0; x < n-1; x++) {
        for (int y = 1; y < n; y++){
            if (vetor[x] > vetor[y]){
                aux = vetor[x];
                vetor[x] = vetor[y];
                vetor[y] = aux;
            }
        }
    }

    return 0;
}
