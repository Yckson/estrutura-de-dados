#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Aluno{
    char nome[50];
    int matricula;
    float media;
};

typedef struct Aluno Aluno;


void trocarAluno(Aluno* Aluno_A, Aluno* Aluno_B){
    Aluno AlunoTemp = *Aluno_A;
    *Aluno_A = *Aluno_B;
    *Aluno_B = AlunoTemp;
}

void ordenarAlunosPorNome(Aluno* alunos, int numAlunos){
    for(int i = 0; i < numAlunos; i++){
        for(int j = 0; j < numAlunos - 1; j++){
            if(strcmp(alunos[j].nome, alunos[j+1].nome) > 0){
                trocarAluno(&alunos[j], &alunos[j+1]);
            }
        }
    }
}

void ordenarAlunosPorMedia(Aluno* alunos, int numAlunos){
    for(int i = 0; i < numAlunos; i++){
        for(int j = 0; j < numAlunos - 1; j++){
            if(alunos[j].media < alunos[j+1].media){
                trocarAluno(&alunos[j], &alunos[j+1]);
            }
        }
    }
}

void mostrarAlunos(Aluno* alunos, int numAlunos){
    for(int i = 0; i < numAlunos; i++){
        printf("Aluno %d:\n", i+1);
        printf("\tNome: %s\n", alunos[i].nome);
        printf("\tMatricula: %d\n", alunos[i].matricula);
        printf("\tMedia: %.2f\n", alunos[i].media);
        printf("\n");
    }
}


int main(){

    Aluno* alunos = 0;
    int numAlunos = 0;
    int opcao = 0;

    printf("Digite o numero de alunos: ");
    scanf("%d", &numAlunos);

    alunos = (Aluno*) calloc(numAlunos, sizeof(Aluno));

    if(alunos == 0){
        printf("Erro ao alocar memoria\n");
        return 1;
    }

    for(int i = 0; i < numAlunos; i++){
        printf("Digite o nome do aluno %d: ", i+1);
        scanf(" %[^\n]", alunos[i].nome);
        printf("Digite a matricula do aluno %d: ", i+1);
        scanf("%d", &alunos[i].matricula);
        printf("Digite a media do aluno %d: ", i+1);
        scanf("%f", &alunos[i].media);
        printf("\n");
    }

    while(1){
        printf("Digite a opcao desejada:\n");
        printf("1 - Listar alunos em ordem alfabetica\n");
        printf("2 - Listar alunos em ordem de classificacao (media)\n");
        printf("3 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Alunos em ordem alfabetica (A --> Z): \n");
                ordenarAlunosPorNome(alunos, numAlunos);
                mostrarAlunos(alunos, numAlunos);
                break;
            
            case 2:
                printf("Alunos em ordem de classificacao (Maior Media --> Menor Media): \n");
                ordenarAlunosPorMedia(alunos, numAlunos);
                mostrarAlunos(alunos, numAlunos);
                break;

            case 3:
                opcao = 0;
                break;
            
            default:
                printf("Opcao invalida\n");
                break;
        }
        
        if(opcao == 0){
            printf("Saindo...\n");
            break;
        }
    }

    free(alunos);

    
    return 0;
}