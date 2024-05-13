#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Atleta {
    char nome[50];
    int idade;
    float peso;
};


typedef struct Atleta Atleta;

int main (){

    char nomeAtleta[50];
    int idadeAtleta = 0;
    float pesoAtleta = 0.0;
    float somaPesos = 0.0;
    int qtdMenorIdade = 0;

    int qtdAtletas = 0;

    printf("Digite a quantidade de atletas: ");
    scanf("%d", &qtdAtletas);

    Atleta *atletas = (Atleta *) calloc(qtdAtletas, sizeof(Atleta));

    if (atletas == NULL) {
        printf("Memoria nao alocada corretamente! Finalizando o programa...\n");
        return 1;
    }

    for (int i = 0; i < qtdAtletas; i++) {
        fflush(stdin);
        printf("Digite o nome do atleta %d: ", i+1);
        fgets(nomeAtleta, 50, stdin);
        fflush(stdin);
        printf("Digite a idade do atleta %d: ", i+1);
        scanf(" %d", &idadeAtleta);
        printf("Digite o peso do atleta %d: ", i+1);
        scanf(" %f", &pesoAtleta);
        printf("\n");

        strcpy(atletas[i].nome, nomeAtleta);
        atletas[i].idade = idadeAtleta;
        atletas[i].peso = pesoAtleta;
    }

    printf("\n\n================LISTAGEM DOS ATLETAS CADASTRADOS================\n\n");
    for (int i = 0; i < qtdAtletas; i++) {
        printf("Atleta %d:\n", i+1);
        printf("\tNome: %s", atletas[i].nome);
        printf("\tIdade: %d\n", atletas[i].idade);
        printf("\tPeso: %.2f\n", atletas[i].peso);
        printf("\n");

        somaPesos += atletas[i].peso;
        if (atletas[i].idade < 18) {
            qtdMenorIdade++;
        }


    }

    printf("\n\n================RESULTADOS================\n\n");
    printf("Media de pesos dos atletas: %.2f\n", somaPesos/qtdAtletas);
    printf("Quantidade de atletas com idade inferior a 18 anos: %d\n", qtdMenorIdade);

    free(atletas);



    return 0;
}