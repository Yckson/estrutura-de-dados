// ALUNO: WILLIAM GABRIEL YCKSON ARAÚJO BRAGA
// Matrícula: 202300084281


#include <stdio.h>
#include <stdlib.h>


typedef struct no No;

typedef struct listaEncadeada ListaEncadeada;


struct no{
    int valor;
    No *proximo;
};

struct listaEncadeada{
    No *inicio;
    No *fim;
    int tamanho;
};

// CONSTRUIR LISTA ENCADEADA 
int construirListaEncadeada(ListaEncadeada *lista){
    lista->inicio = NULL;
    lista->fim  = NULL;
    lista->tamanho = 0;
    return 0;
}


// CONSTRUIR UM NOVO NÓ
int novoNo(No **ponteiroNo, int valor, No *ponteiroProxNo){
    (*ponteiroNo) = (No*) malloc(sizeof(No));
    (*ponteiroNo)->valor = valor;
    (*ponteiroNo)->proximo = ponteiroProxNo;

    return valor;
}

// ADICIONAR NÓ QUANDO A LISTA ESTIVER VAZIA
int addListaVazia(ListaEncadeada *lista, int valor){
    No *no;
    novoNo(&no, valor, NULL);

    lista->inicio = no;
    lista->fim = no;
    lista->tamanho = 1;

    return valor;
}

// ADICIONAR NÓ EM DETERMINADA POSIÇÃO INFORMADA - SOLICITAÇÃO 5
int addNo(ListaEncadeada *lista, int valor, int pos){
    No *no;
    No *antigoNo = lista->inicio;

    if (pos < 0){
        printf("Posicao Invalida!\n");
        return valor;
    }

    if (lista->tamanho == 0){
        addListaVazia(lista, valor);
        return valor;
    }

    if (pos == 0){
        novoNo(&no, valor, antigoNo);
        lista->inicio = no;
        lista->tamanho++;
        return valor;
    }

    if (pos > lista->tamanho){
        pos = lista->tamanho;
        printf("O elemento sera inserido no final da lista!\n");
    }

    for (int posAtual = 1; posAtual < pos; posAtual++){
        antigoNo = antigoNo->proximo;
    }


    novoNo(&no, valor, antigoNo->proximo);
    antigoNo->proximo = no;

    if (lista->tamanho == pos){
        lista->fim = no;
    }

    lista->tamanho++;

    return valor;
}

// ADICIONAR NÓ NO FINAL DA LISTA
int addNoFinal(ListaEncadeada *lista, int valor){
    addNo(lista, valor, lista->tamanho);
    return valor;
}


// REMOVER NÓ EM DETERMINADA POSIÇÃO PASSADA -> SOLICITAÇÃO 6
int removerNo(ListaEncadeada *lista, int numNo){

    /*
       Fluxo de execução:
       1. Inicializa os ponteiros noAtual e noAnterior com o primeiro nó da lista
       2. Percorre a lista até encontrar o nó desejado
       3. Remove o nó desejado, atualizando os ponteiros e liberando a memória
       4. Atualiza o tamanho da lista
       5. Retorna o número do nó removido
    */


    No *noInicial = lista->inicio;
    No *noAtual;
    No *noAnterior;

    // Verifica se o índice passado é válido
    if(numNo < 0 || numNo >= lista->tamanho){
        printf("Indice invalido!\n");
        return numNo;
    }

    // Verifica se a lista está vazia
    if(lista->tamanho == 0){
        return 0;
    }

    // Remover o primeiro nó
    if(numNo == 0){
        noAtual = noInicial->proximo;
        lista->inicio = noAtual;
        lista->tamanho -= 1;
        free(noInicial);
        return numNo;
    }

    noAtual = noInicial->proximo;
    noAnterior = noInicial;

    for (int numNoAtual = 1; numNoAtual < lista->tamanho-1; numNoAtual++){
        // Remover nó no meio da lista
        if (numNoAtual == numNo){
            noAnterior->proximo = noAtual->proximo;
            free(noAtual);
            lista->tamanho -= 1;
            return numNoAtual;
        }
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }

    // Remover o último nó
    noAnterior->proximo = NULL;
    lista->fim = noAnterior;
    free(noAtual);
    lista->tamanho -= 1;
    return numNo;
}


// REMOVER NÓ NO INÍCIO DA LISTA -> SOLICITAÇÃO 1
int removerNoInicio(ListaEncadeada *lista){
    return removerNo(lista, 0);
}

// REMOVER NÓ NO FINAL DA LISTA -> SOLICITAÇÃO 2
int removerNoFinal(ListaEncadeada *lista){
    return removerNo(lista, lista->tamanho-1);
}

// PESQUISAR INFORMAÇÃO NA LISTA -> SOLICITAÇÃO 4
int busca(ListaEncadeada *lista, int val){
    No *noAtual = lista->inicio;

    for (int pos = 0; pos < lista->tamanho; pos++){
        if(noAtual->valor == val){
            return pos;
        }
        noAtual = noAtual->proximo;
    }

    return -1;
}

int buscaPos(ListaEncadeada *lista, int pos){
    No *noAtual = lista->inicio;

    if (pos < 0 || pos >= lista->tamanho){
        printf("Posicao invalida!\n");
        return -1;
    }

    for (int posAtual = 0; posAtual < lista->tamanho; posAtual++){
        if(posAtual == pos){
            printf("Valor encontrado: %d\n", noAtual->valor);
            return noAtual->valor;
        }
        noAtual = noAtual->proximo;
    }

    printf("Valor nao encontrado!\n");
    return -1;
}

// MOSTRAR LISTA DE FORMA ORGANIZADA (ESTILO ARRAY)
int mostrarLista(ListaEncadeada *lista){

    printf("[ ");

    // Verifica se a lista não está vazia
    if(lista->tamanho > 0){
        // Percorre a lista e imprime os valores
        No *noAtual = lista->inicio;
        for (int pos = 1; pos < lista->tamanho; pos++){
            printf("%d, ", noAtual->valor);
            noAtual = noAtual->proximo;
        }
        printf("%d ", noAtual->valor);
    }

    else{
        // Caso a lista esteja vazia
        printf("LISTA VAZIA ");
    }

    printf("]\n");
    

    return 0;
}


// DESTRUIR LISTA -> SOLICITAÇÃO 3
int limparLista(ListaEncadeada *lista){
    // Remove todos os nós da lista
    while (lista->tamanho > 0){
        removerNo(lista, 0);
    }
    // Constrói uma nova lista com as configurações iniciais
    construirListaEncadeada(lista);

    return 0;
}




int main (){

    ListaEncadeada lista;

    construirListaEncadeada(&lista);
    int opcao;

    do{
        int valor;
        int pos;

        printf("\n 1 - Adicionar no inicio da lista\n");
        printf(" 2 - Adicionar no final da lista\n");
        printf(" 3 - Mostrar lista\n");
        printf(" 4 - Adicionar elemento em determinada posicao\n");
        printf(" 5 - Remover elemento em determinada posicao\n");
        printf(" 6 - Remover elemento no comeco da lista\n");
        printf(" 7 - Remover elemento no final da lista\n");
        printf(" 8 - Buscar elemento na lista\n");
        printf(" 9 - Buscar elemento na lista pela posicao\n");
        printf(" 10 - Remover todos os elementos da lista\n");
        printf(" 11 - Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        printf("\n");

        switch(opcao){
            case 1:
                printf("Digite o valor a ser adicionado: ");
                scanf("%d", &valor);
                addNo(&lista, valor, 0);
                system("pause");
                break;
            case 2:
                printf("Digite o valor a ser adicionado: ");
                scanf("%d", &valor);
                addNoFinal(&lista, valor);
                system("pause");
                break;
            case 3:
                mostrarLista(&lista);
                system("pause");
                break;
            case 4:
                printf("Digite o valor a ser adicionado: ");
                scanf("%d", &valor);
                printf("Digite a posicao a ser adicionada: ");
                scanf("%d", &pos);
                addNo(&lista, valor, pos);
                system("pause");
                break;
            case 5:
                printf("Digite a posicao a ser removida: ");
                scanf("%d", &pos);
                removerNo(&lista, pos);
                system("pause");
                break;
            case 6:
                removerNoInicio(&lista);
                system("pause");
                break;
            case 7:
                removerNoFinal(&lista);
                system("pause");
                break;
            case 8:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                pos = busca(&lista, valor);
                if(pos == -1){
                    printf("Valor nao encontrado!\n");
                }else{
                    printf("Valor encontrado na posicao %d\n", pos);
                }
                system("pause");
                break;

            case 9:
                printf("Digite a posicao a ser buscada: ");
                scanf("%d", &pos);

                valor = buscaPos(&lista, pos);
                system("pause");
                break;
            case 10:
                limparLista(&lista);
                mostrarLista(&lista);
                system("pause");
                break;
            case 11:
                printf("Saindo...\n");
                system("pause");
                break;
            default:
                printf("Opcao invalida!\n");
                system("pause");
        }


    }while(opcao != 11);

    limparLista(&lista);




    



















    return 0;
}