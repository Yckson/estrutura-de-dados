//ALUNO: WILLIAM GABRIEL YCKSON ARAÚJO BRAGA
//MATRÍCULA: 202300084281


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct aluno Aluno;
typedef struct disciplina Disciplina;


struct aluno{

    int matricula;
    char nome[31];
    Aluno *proxAluno;

};

struct disciplina{

    int codigo;
    char nome[31];
    Aluno *alunos;
    int qtdAlunos;
    Disciplina *proxDisciplina;

};

int criarNovoAluno(Aluno **novoAluno, char nome[], int matricula){
    (*novoAluno) = (Aluno*) malloc(sizeof(Aluno));
    if ((*novoAluno) == NULL) {
        printf("Falha na alocacao de memoria!\n");
        return 0;
    }

    (*novoAluno)->matricula = matricula;
    strcpy((*novoAluno)->nome, nome);
    (*novoAluno)->proxAluno = NULL;


    return 1;
}

int criarNovaDisciplina(Disciplina **novaDisciplina, char nome[], int codigo){
    (*novaDisciplina) = (Disciplina*) malloc(sizeof(Disciplina));
    if ((*novaDisciplina) == NULL){
        printf("Falha na alocacao de memoria!\n");
        return 0;
    }

    

    (*novaDisciplina)->codigo = codigo;
    (*novaDisciplina)->alunos = NULL;
    (*novaDisciplina)->qtdAlunos = 0;
    (*novaDisciplina)->proxDisciplina = NULL;
    strcpy((*novaDisciplina)->nome, nome);


    return 1;

}

int adicionarDisciplina(Disciplina **disciplinas, char nome[], int codigo){
    Disciplina *novaDisciplina;
    Disciplina *ultimaDisciplina;

    criarNovaDisciplina(&novaDisciplina, nome, codigo);
    if(novaDisciplina == NULL){
        return 0;
    }



    if ((*disciplinas) == NULL){
        (*disciplinas) = novaDisciplina;
        return 0;
    }

    ultimaDisciplina = (*disciplinas);

    while (ultimaDisciplina->proxDisciplina != NULL){
        ultimaDisciplina = ultimaDisciplina->proxDisciplina;
    }


    ultimaDisciplina->proxDisciplina = novaDisciplina;
    

    return 1;
}


int encontrarDisciplina (Disciplina **disciplinas, int codDisciplina, Disciplina **disciplinaEncontrada){
    Disciplina *disciplinaAtual = (*disciplinas);

    while (disciplinaAtual != NULL) {
        if (disciplinaAtual->codigo == codDisciplina){
            (*disciplinaEncontrada) = disciplinaAtual;
            return 1;
        }
        disciplinaAtual = disciplinaAtual->proxDisciplina;
    }

    return 0;
}

int matricularAluno(char nomeAluno[], int matricula, int codDisciplina, Disciplina **disciplinas){
    Aluno *novoAluno;
    Aluno *ultimoAluno;

    criarNovoAluno(&novoAluno, nomeAluno, matricula);

    if(novoAluno == NULL){
        return 0;
    }

    
    Disciplina *disciplinaEncontrada;
    int encontrou = encontrarDisciplina(&(*disciplinas), codDisciplina, &disciplinaEncontrada);
    if (!encontrou){
        printf("Essa disciplina nao foi encontrada!\n");
        return 0;
    
    }

    ultimoAluno = disciplinaEncontrada->alunos;

    if (ultimoAluno == NULL){
        disciplinaEncontrada->alunos = novoAluno;
        disciplinaEncontrada->qtdAlunos++;
        return 1;
    }

    while (ultimoAluno->proxAluno != NULL) {
        ultimoAluno = ultimoAluno->proxAluno;
    }

    ultimoAluno->proxAluno = novoAluno;
    disciplinaEncontrada->qtdAlunos += 1;
    return 1;
}


int exibirDisciplinas(Disciplina **disciplinas){
    Disciplina *disciplinaAtual = (*disciplinas);

    printf("---------------------------------------------------------------------------------------------\n");
    printf("|Lista de disciplinas cadastradas:\n");

    if(disciplinaAtual == NULL){
        printf("|Nenhuma disciplina cadastrada ainda!\n");
    }
    printf("|\t Codigo: \t\tNome: \t\t\t Qtd alunos cadastrados: \n");

    while (disciplinaAtual != NULL){
        printf("|\t");
        printf("%d\t\t%s\t\t\t\t%d\n", disciplinaAtual->codigo, disciplinaAtual->nome, disciplinaAtual->qtdAlunos);

        disciplinaAtual = disciplinaAtual->proxDisciplina;
    }

    return 1;
}

int exibirAlunos(int codDisciplina, Disciplina **disciplinas){
    Disciplina *disciplinaEncontrada;
    Aluno *alunoAtual;
    int encontrou = encontrarDisciplina(&(*disciplinas), codDisciplina, &disciplinaEncontrada);

    printf("---------------------------------------------------------------------------------------------\n");

    if(!encontrou){
        printf("Nao foi encontrada nenhuma turma com o codigo informado!\n");
        return 0;
    }

    alunoAtual = disciplinaEncontrada->alunos;

    printf("|Lista de alunos da turma de %s:\n", disciplinaEncontrada->nome);
    printf("|\tMatricula:\t\tNome:\n");

    while (alunoAtual != NULL) {
        printf("|\t%d\t\t\t%s\n", alunoAtual->matricula, alunoAtual->nome);
        alunoAtual = alunoAtual->proxAluno;
    }

    return 1;

}

int desmatricularAluno (Disciplina **disciplinas, int matricula, int codDisciplina){
    Disciplina *discipDesmatricula;
    Aluno *penultAluno;
    Aluno *alunoDesmatriculado;

    int encontrou = encontrarDisciplina(&(*disciplinas), codDisciplina,  &discipDesmatricula);

    if (!encontrou){
        printf("|Essa disciplina nao foi encontrada!\n");
        return 0;
    }

    penultAluno = discipDesmatricula->alunos;

    if (penultAluno == NULL) {
        printf("A turma nao possui alunos matriculados!\n");
        return 0;
    }

    if(penultAluno->proxAluno == NULL){
        if (penultAluno->matricula == matricula) {
            printf("O aluno %s de matricula %d foi desmatriculado da disciplina %s (cod: %d)\n", penultAluno->nome, penultAluno->matricula, discipDesmatricula->nome, discipDesmatricula->codigo);
            discipDesmatricula->alunos = NULL;
            discipDesmatricula->qtdAlunos--;
            free(penultAluno);
            return 1;
        }
        printf("Nao foi encontrado nenhum aluno com a matricula %d na turma de %s (cod: %d)!\n", matricula, discipDesmatricula->nome, discipDesmatricula->codigo);
        return 0;
    }

    if(penultAluno->matricula == matricula){
        printf("O aluno %s de matricula %d foi desmatriculado da disciplina %s (cod: %d)\n", penultAluno->nome, penultAluno->matricula, discipDesmatricula->nome, discipDesmatricula->codigo);
        discipDesmatricula->alunos = penultAluno->proxAluno;
        discipDesmatricula->qtdAlunos--;
        free(penultAluno);
        return 1;
    }

    alunoDesmatriculado = penultAluno->proxAluno;


    while(alunoDesmatriculado != NULL){
        if(alunoDesmatriculado->matricula == matricula){
            printf("O aluno %s de matricula %d foi desmatriculado da disciplina %s (cod: %d)\n", alunoDesmatriculado->nome, alunoDesmatriculado->matricula, discipDesmatricula->nome, discipDesmatricula->codigo);
            penultAluno->proxAluno = NULL;
            discipDesmatricula->qtdAlunos--;
            free(alunoDesmatriculado);
            return 1;
        }
        penultAluno = penultAluno->proxAluno;
        alunoDesmatriculado = alunoDesmatriculado->proxAluno;
    }

    printf("Nao foi encontrado nenhum aluno com a matricula %d na turma de %s (cod: %d)!\n", matricula, discipDesmatricula->nome, discipDesmatricula->codigo);
    return 0;


}

int removerTodosAlunos (Disciplina **disciplinas){
    Disciplina *disciplinaAtual = (*disciplinas);
    Aluno *alunoAtual;
    Aluno *alunoProx;

    while (disciplinaAtual != NULL){
        alunoAtual = disciplinaAtual->alunos;

        while (alunoAtual != NULL){
            alunoProx = alunoAtual->proxAluno;
            free(alunoAtual);
            alunoAtual = alunoProx;
            disciplinaAtual->qtdAlunos--;
        }

        disciplinaAtual = disciplinaAtual->proxDisciplina;
    }

    return 1;
}

int removerTodasDisciplinas (Disciplina **disciplinas){
    Disciplina *disciplinaAtual = (*disciplinas);
    Disciplina *disciplinaProx;

    while (disciplinaAtual != NULL){
        disciplinaProx = disciplinaAtual->proxDisciplina;
        free(disciplinaAtual);
        disciplinaAtual = disciplinaProx;
    }

    return 1;
}











int main(){

    Disciplina *disciplinas = NULL;

    int opcao = 0;
    char nomeDisciplina[31];
    int codDisciplina;
    char nomeAluno[31];
    int matricula;

    while (opcao != 6){
        printf("---------------------------------------------------------------------------------------------\n");
        printf("|Escolha uma opcao:\n");
        printf("|1 - Cadastrar disciplina\n");
        printf("|2 - Matricular aluno\n");
        printf("|3 - Desmatricular aluno\n");
        printf("|4 - Exibir disciplinas\n");
        printf("|5 - Exibir alunos de uma disciplina\n");
        printf("|6 - Sair\n");
        printf("---------------------------------------------------------------------------------------------\n");
        printf("|Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                
                system("cls");
                printf("|Digite o nome da disciplina: ");
                scanf(" %[^\n]", nomeDisciplina);
                printf("|Digite o codigo da disciplina: ");
                scanf("%d", &codDisciplina);
                system("cls");
                adicionarDisciplina(&disciplinas, nomeDisciplina, codDisciplina);
                exibirDisciplinas(&disciplinas);
                system("pause");
                break;
            
            case 2: 
                system("cls");
                printf("|Digite o nome do aluno: ");
                scanf(" %[^\n]", nomeAluno);
                printf("|Digite a matricula do aluno: ");
                scanf("%d", &matricula);
                printf("|Digite o codigo da disciplina: ");
                scanf("%d", &codDisciplina);
                system("cls");
                matricularAluno(nomeAluno, matricula, codDisciplina, &disciplinas);
                exibirAlunos(codDisciplina, &disciplinas);
                system("pause");
                break;
            
            case 3: 
                system("cls");
                printf("|Digite a matricula do aluno: ");
                scanf("%d", &matricula);
                printf("|Digite o codigo da disciplina: ");
                scanf("%d", &codDisciplina);

                system("cls");
                desmatricularAluno(&disciplinas, matricula, codDisciplina);
                exibirAlunos(codDisciplina, &disciplinas);
                system("pause");
                break;
            
            case 4: 
                system("cls");
                exibirDisciplinas(&disciplinas);
                system("pause");
                break;
            
            case 5: 
                system("cls");
                printf("|Digite o codigo da disciplina: ");
                scanf("%d", &codDisciplina);
                system("cls");
                exibirAlunos(codDisciplina, &disciplinas);
                system("pause");
                break;
            
            case 6: 
                system("cls");
                printf("|Saindo...\n");
                break;
            
            default: 
                system("cls");
                printf("|Opcao invalida!\n");
                system("pause");

                break;
        }
        system("cls");
    }


    removerTodosAlunos(&disciplinas);
    removerTodasDisciplinas(&disciplinas);

    return 0;
}