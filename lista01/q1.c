#include <stdio.h>
#include <stdlib.h>


int main (){

    int qtdNumeros = 0;
    int *numeros = 0;
    int achouMultiplo = 0;
    int soma = 0;

    printf("Digite a quantidade de numeros: ");
    scanf("%d", &qtdNumeros);

    numeros = (int *) malloc(qtdNumeros * sizeof(int));

    if (numeros == NULL){
        printf("Memoria nao alocada corretamente! Finalizando o programa...");
        return 1;
    }


    for (int i = 0; i < qtdNumeros; i++){
        printf("Digite o %d numero: ", i+1);
        scanf("%d", &numeros[i]);
        soma += numeros[i];
    }

    printf("Os numeros multiplos de 6 que foram digitados sao: ");
    for (int i = 0; i < qtdNumeros; i++){
        if (numeros[i] % 6 == 0){
            printf("%d ", numeros[i]);
            achouMultiplo = 1;
        }
    }

    if (!achouMultiplo){
        printf("Nenhum numero é multiplo de 6.");
    }

    printf("\nA media aritmetica dos numeros digitados e: %.2f", ((float) soma / qtdNumeros));
    free(numeros);


    return 0;
}