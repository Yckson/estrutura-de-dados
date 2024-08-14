#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Definindo as variaveis padrão
int MAX_FILA = 10;
int TEMPO_ATENDIMENTO = 10;


// Definindo as estruturas
typedef struct {
    char nome[50];
    int cod;
    int tempoDeAtendimento;
} Cliente;

typedef struct {
    Cliente *clientes;
    int inicio;
    int fim;
    int tamanho;
} Fila;



// Função para configurar a fila
int configurarFila (Fila *fila){
    fila->clientes = (Cliente *) malloc(MAX_FILA * sizeof(Cliente));
    if (fila->clientes == NULL){
        return 0;
    }
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
    return 1;
}


// Função para verificar se a fila está vazia
int filaVazia(Fila *fila){
    return (fila->inicio == fila->fim && fila->tamanho == 0);
}

// Função para verificar se a fila está cheia
int filaCheia(Fila *fila){
    return fila->tamanho == MAX_FILA;
}


// Função para inserir um cliente na fila
int inserirCliente(Fila *fila, Cliente cliente){
    if (filaCheia(fila)){
        return 0;
    }
    if (filaVazia(fila)){
        fila->inicio = 0;
        fila->fim = 0;
        fila->clientes[fila->fim] = cliente;
        fila->tamanho++;
        return 1;
    }

    if (fila->fim == MAX_FILA - 1){
        fila->fim = -1;
    }
    fila->clientes[fila->fim+1] = cliente;
    fila->fim = (fila->fim + 1) % MAX_FILA;
    fila->tamanho++;

    return 1;
}


// Função para remover um cliente da fila
int removerCliente(Fila *fila, Cliente *cliente){
    if (filaVazia(fila)){
        return 0;
    }
    *cliente = fila->clientes[fila->inicio];

    
    fila->inicio = (fila->inicio + 1) % MAX_FILA;
    fila->tamanho--;

    if (fila->tamanho == 0){
        fila->inicio = 0;
        fila->fim = 0;
    }
    return 1;
}

// Função para criar um cliente
int criarCliente(Cliente *cliente, char nome[], int cod, int tempoDeAtendimento){
    if (cliente == NULL){
        return 0;
    }
    cliente->cod = cod;
    cliente->tempoDeAtendimento = tempoDeAtendimento;
    strcpy(cliente->nome, nome);
    return 1;
}

// Função para imprimir um cliente
void imprimirCliente(Cliente cliente){
    printf("Nome: %s\n", cliente.nome);
    printf("Codigo: %d\n", cliente.cod);
    printf("Tempo de atendimento: %d\n", cliente.tempoDeAtendimento);
}

// Função para imprimir a fila
void imprimirFila(Fila *fila){
    int i = fila->inicio;
    int cont = 1;
    printf("[\n");
    while (cont <= fila->tamanho){
        printf("Cliente %d (%dmin restantes): ", cont, fila->clientes[i].tempoDeAtendimento);
        printf("%s\n", fila->clientes[i].nome);
        i = (i + 1) % MAX_FILA;
        cont++;
    }

    printf("]\n");
}






// Função principal
int main(){

    Fila fila;
    int tempoAtual = 0;
    int qtdInicialClientes = 0;
    char op;

    printf("Digite a quantidade de clientes que o banco aceita: \n");
    scanf("%d", &MAX_FILA);
    printf("Digite o tempo de atendimento do banco: \n");
    scanf("%d", &TEMPO_ATENDIMENTO);

    if (!configurarFila(&fila)){
        printf("Erro ao configurar a fila\n");
        return 1;
    }

    printf("BEM VINDO AO BANCO FILABANK!------------------------------\n");
    printf("Digite a quantidade de clientes iniciais: \n");
    scanf("%d", &qtdInicialClientes);

    printf("Digite as informacoes dos clientes iniciais: \n");
    for (int i = 0; i < qtdInicialClientes; i++){
        
        Cliente cliente;
        char nome[50];
        int tempoDeAtendimento;
        printf("Digite o nome do cliente: \n");
        scanf("%s", nome);
        printf("Digite o tempo de atendimento do cliente: \n");
        scanf("%d", &tempoDeAtendimento);
        if (!criarCliente(&cliente, nome, i, tempoDeAtendimento)){
            printf("Erro ao criar o cliente\n");
            return 1;
        }
        if (!inserirCliente(&fila, cliente)){
            printf("Erro ao inserir o cliente\n");
            return 1;
        }
    }

    do{
        system("cls");
        printf("-----------------------------------------------------TEMPO ATUAL: %dmin\n", tempoAtual);
        printf("Fila de clientes: \n");
        imprimirFila(&fila);
        printf("Digite a opcao desejada: \n");
        printf("A - Atender cliente\n");
        printf("I - Inserir cliente\n");
        printf("E - Encerrar\n");
        scanf(" %c", &op);
        system("cls");

        if (op == 'A' || op == 'a'){
            if (filaVazia(&fila)){
                printf("Nao ha clientes na fila\n");
                system("pause");
                continue;
            }
            Cliente cliente = fila.clientes[fila.inicio];
            printf("Atendendo cliente: \n");
            imprimirCliente(cliente);

            tempoAtual++;
            printf("O tempo se passa... Tempo atual: %d\n", tempoAtual);

            fila.clientes[fila.inicio].tempoDeAtendimento--;
            if (fila.clientes[fila.inicio].tempoDeAtendimento <= 0){
                printf("-----------------------\n");
                removerCliente(&fila, &cliente);
                printf("Cliente atendido e removido da fila com sucesso: \n");
                imprimirCliente(cliente);
            }
            system("pause");

        }else if (op == 'I' || op == 'i'){
            Cliente cliente;
            char nome[50];
            int tempoDeAtendimento;
            printf("Digite o nome do cliente: \n");
            scanf("%s", nome);
            printf("Digite o tempo de atendimento do cliente: \n");
            scanf("%d", &tempoDeAtendimento);
            if (!criarCliente(&cliente, nome, fila.tamanho, tempoDeAtendimento)){
                printf("Erro ao criar o cliente\n");
                system("pause");
                continue;
            }
            if (!inserirCliente(&fila, cliente)){
                printf("Erro ao inserir o cliente\n");
                if (filaCheia(&fila)){
                    printf("Fila cheia!\n");
                }
                system("pause");
                continue;
            }
            qtdInicialClientes++;
        }


    }while (tempoAtual < TEMPO_ATENDIMENTO && !(op == 'E' || op == 'e'));

    system("cls");

    if (tempoAtual >= TEMPO_ATENDIMENTO){
        printf("Tempo de atendimento encerrado!!!\n");
    
    }

    printf("Fila de clientes final: \n");
    imprimirFila(&fila);


    

    free(fila.clientes);

    return 0;
}