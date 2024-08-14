#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file q1.c
 * @brief Esse arquivo contém a aplicação da fila em array solicitada.
 *
 * O programa consiste em simular um banco, onde o usuário pode adicionar clientes à fila e atendê-los.
 * O usuário pode adicionar clientes iniciais e atendê-los, ou adicionar clientes durante o atendimento.
 * O programa encerra o atendimento após um tempo determinado.
 * 
 * O programa foi desenvolvido como atividade da disciplina de Estrutura de Dados.
 * 
 * @date 2024-08-14
 */

/**
 * @brief Tamanho máximo da fila de clientes.
 */
int MAX_FILA = 10;

/**
 * @brief Tempo padrão de atendimento para cada cliente (em minutos).
 */
int TEMPO_ATENDIMENTO = 10;

/**
 * @brief Estrutura que representa um cliente no sistema.
 */
typedef struct {
    char nome[50];             /**< Nome do cliente. */
    int cod;                   /**< Código de identificação do cliente. */
    int tempoDeAtendimento;     /**< Tempo necessário para atender o cliente (em minutos). */
} Cliente;

/**
 * @brief Estrutura que representa uma fila de clientes.
 */
typedef struct {
    Cliente *clientes;          /**< Array dinâmico de clientes. */
    int inicio;                 /**< Índice do início da fila. */
    int fim;                    /**< Índice do final da fila. */
    int tamanho;                /**< Quantidade de clientes na fila. */
} Fila;

/**
 * @brief Inicializa a fila com o tamanho máximo especificado.
 *
 * Aloca memória para a fila e inicializa os índices de início, fim e tamanho.
 *
 * @param fila Ponteiro para a fila que será inicializada.
 * @return 1 se a fila for configurada com sucesso, 0 caso contrário.
 */
int configurarFila(Fila *fila) {
    fila->clientes = (Cliente *)malloc(MAX_FILA * sizeof(Cliente));
    if (fila->clientes == NULL) {
        return 0;
    }
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
    return 1;
}

/**
 * @brief Verifica se a fila está vazia.
 *
 * @param fila Ponteiro para a fila.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int filaVazia(Fila *fila) {
    return (fila->inicio == fila->fim && fila->tamanho == 0);
}

/**
 * @brief Verifica se a fila está cheia.
 *
 * @param fila Ponteiro para a fila.
 * @return 1 se a fila estiver cheia, 0 caso contrário.
 */
int filaCheia(Fila *fila) {
    return fila->tamanho == MAX_FILA;
}

/**
 * @brief Insere um cliente na fila.
 *
 * Se a fila não estiver cheia, o cliente é adicionado ao final da fila.
 *
 * @param fila Ponteiro para a fila.
 * @param cliente Cliente a ser inserido na fila.
 * @return 1 se o cliente for inserido com sucesso, 0 se a fila estiver cheia.
 */
int inserirCliente(Fila *fila, Cliente cliente) {
    if (filaCheia(fila)) {
        return 0;
    }
    if (filaVazia(fila)) {
        fila->inicio = 0;
        fila->fim = 0;
        fila->clientes[fila->fim] = cliente;
        fila->tamanho++;
        return 1;
    }

    if (fila->fim == MAX_FILA - 1) {
        fila->fim = -1;
    }
    fila->clientes[fila->fim + 1] = cliente;
    fila->fim = (fila->fim + 1) % MAX_FILA;
    fila->tamanho++;

    return 1;
}

/**
 * @brief Remove um cliente da fila.
 *
 * O cliente no início da fila é removido e o próximo cliente, se houver, ocupa seu lugar.
 *
 * @param fila Ponteiro para a fila.
 * @param cliente Ponteiro para o cliente removido.
 * @return 1 se o cliente for removido com sucesso, 0 se a fila estiver vazia.
 */
int removerCliente(Fila *fila, Cliente *cliente) {
    if (filaVazia(fila)) {
        return 0;
    }
    *cliente = fila->clientes[fila->inicio];

    fila->inicio = (fila->inicio + 1) % MAX_FILA;
    fila->tamanho--;

    if (fila->tamanho == 0) {
        fila->inicio = 0;
        fila->fim = 0;
    }
    return 1;
}

/**
 * @brief Cria um cliente com as informações fornecidas.
 *
 * @param cliente Ponteiro para o cliente que será criado.
 * @param nome Nome do cliente.
 * @param cod Código de identificação do cliente.
 * @param tempoDeAtendimento Tempo necessário para atender o cliente (em minutos).
 * @return 1 se o cliente for criado com sucesso, 0 caso contrário.
 */
int criarCliente(Cliente *cliente, char nome[], int cod, int tempoDeAtendimento) {
    if (cliente == NULL) {
        return 0;
    }
    cliente->cod = cod;
    cliente->tempoDeAtendimento = tempoDeAtendimento;
    strcpy(cliente->nome, nome);
    return 1;
}

/**
 * @brief Imprime as informações de um cliente.
 *
 * @param cliente O cliente cujas informações serão impressas.
 */
void imprimirCliente(Cliente cliente) {
    printf("Nome: %s\n", cliente.nome);
    printf("Codigo: %d\n", cliente.cod);
    printf("Tempo de atendimento: %d\n", cliente.tempoDeAtendimento);
}

/**
 * @brief Imprime a fila de clientes.
 *
 * Exibe a lista de clientes na fila, mostrando o tempo de atendimento restante para cada cliente.
 *
 * @param fila Ponteiro para a fila.
 */
void imprimirFila(Fila *fila) {
    int i = fila->inicio;
    int cont = 1;
    printf("[\n");
    while (cont <= fila->tamanho) {
        printf("Cliente %d (%dmin restantes): ", cont, fila->clientes[i].tempoDeAtendimento);
        printf("%s\n", fila->clientes[i].nome);
        i = (i + 1) % MAX_FILA;
        cont++;
    }

    printf("]\n");
}

/**
 * @brief Função principal do programa.
 *
 * O programa inicializa a fila, solicita a entrada do usuário e simula o atendimento dos clientes.
 *
 * @return 0 se o programa for executado com sucesso, 1 caso contrário.
 */
int main() {
    Fila fila;
    int tempoAtual = 0;
    int qtdInicialClientes = 0;
    char op;

    printf("Digite a quantidade de clientes que o banco aceita: \n");
    scanf("%d", &MAX_FILA);
    printf("Digite o tempo de atendimento do banco: \n");
    scanf("%d", &TEMPO_ATENDIMENTO);

    if (!configurarFila(&fila)) {
        printf("Erro ao configurar a fila\n");
        return 1;
    }

    printf("BEM VINDO AO BANCO FILABANK!------------------------------\n");
    printf("Digite a quantidade de clientes iniciais: \n");
    scanf("%d", &qtdInicialClientes);

    printf("Digite as informacoes dos clientes iniciais: \n");
    for (int i = 0; i < qtdInicialClientes; i++) {
        Cliente cliente;
        char nome[50];
        int tempoDeAtendimento;
        printf("Digite o nome do cliente: \n");
        scanf("%s", nome);
        printf("Digite o tempo de atendimento do cliente: \n");
        scanf("%d", &tempoDeAtendimento);
        if (!criarCliente(&cliente, nome, i, tempoDeAtendimento)) {
            printf("Erro ao criar o cliente\n");
            return 1;
        }
        if (!inserirCliente(&fila, cliente)) {
            printf("Erro ao inserir o cliente\n");
            return 1;
        }
    }

    do {
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

        if (op == 'A' || op == 'a') {
            if (filaVazia(&fila)) {
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
            if (fila.clientes[fila.inicio].tempoDeAtendimento <= 0) {
                printf("-----------------------\n");
                removerCliente(&fila, &cliente);
                printf("Cliente atendido e removido da fila com sucesso: \n");
                imprimirCliente(cliente);
            }
            system("pause");

        } else if (op == 'I' || op == 'i') {
            Cliente cliente;
            char nome[50];
            int tempoDeAtendimento;
            printf("Digite o nome do cliente: \n");
            scanf("%s", nome);
            printf("Digite o tempo de atendimento do cliente: \n");
            scanf("%d", &tempoDeAtendimento);
            if (!criarCliente(&cliente, nome, fila.tamanho, tempoDeAtendimento)) {
                printf("Erro ao criar o cliente\n");
                system("pause");
                continue;
            }
            if (!inserirCliente(&fila, cliente)) {
                printf("Erro ao inserir o cliente\n");
                if (filaCheia(&fila)) {
                    printf("Fila cheia!\n");
                }
                system("pause");
                continue;
            }
            qtdInicialClientes++;
        }

    } while (tempoAtual < TEMPO_ATENDIMENTO && !(op == 'E' || op == 'e'));

    system("cls");

    if (tempoAtual >= TEMPO_ATENDIMENTO) {
        printf("Tempo de atendimento encerrado!!!\n");
    }

    printf("Fila de clientes final: \n");
    imprimirFila(&fila);

    free(fila.clientes);

    return 0;
}
