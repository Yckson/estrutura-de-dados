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

int construirListaEncadeada(ListaEncadeada *lista){
    lista->inicio = NULL;
    lista->fim  = NULL;
    lista->tamanho = 0;
    return 0;
}

int novoNo(No **ponteiroNo, int valor, No *ponteiroProxNo){
    (*ponteiroNo) = (No*) malloc(sizeof(No));
    (*ponteiroNo)->valor = valor;
    (*ponteiroNo)->proximo = ponteiroProxNo;

    return valor;
}

int addListaVazia(ListaEncadeada *lista, int valor){
    No *no;
    novoNo(&no, valor, NULL);

    lista->inicio = no;
    lista->fim = no;
    lista->tamanho = 1;

    return valor;
}

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

int addNoFinal(ListaEncadeada *lista, int valor){
    addNo(lista, valor, lista->tamanho);
    return valor;
}

int removerNo(ListaEncadeada *lista, int numNo){
    No *noInicial = lista->inicio;
    No *noAtual;
    No *noAnterior;

    if(numNo < 0 || numNo >= lista->tamanho){
        printf("Indice invalido!\n");
        return numNo;
    }

    if(lista->tamanho == 0){
        return 0;
    }

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


        if (numNoAtual == numNo){
            noAnterior->proximo = noAtual->proximo;
            free(noAtual);
            lista->tamanho -= 1;
            return numNoAtual;
        }

        noAnterior = noAtual;
        noAtual = noAtual->proximo;

    }

    noAnterior->proximo = NULL;
    lista->fim = noAnterior;
    free(noAtual);
    lista->tamanho -= 1;
    return numNo;
}


int mostrarLista(ListaEncadeada *lista){

    printf("[ ");

    if(lista->tamanho > 0){
        No *noAtual = lista->inicio;
        for (int pos = 1; pos < lista->tamanho; pos++){
            printf("%d, ", noAtual->valor);
            noAtual = noAtual->proximo;
        }
        printf("%d ", noAtual->valor);
    }

    else{
        printf("LISTA VAZIA ");
    }

    printf("]\n");
    

    return 0;
}

int limparLista(ListaEncadeada *lista){
    while (lista->tamanho > 0){
        removerNo(lista, 0);
    }

    construirListaEncadeada(lista);

    return 0;
}




int main (){

    int valor = 5;
    int valor2 = 10;
    int valor3 = 22;
    int valor4 = 11;

    ListaEncadeada lista;
    construirListaEncadeada(&lista);

    addNo(&lista, valor, 0);
    addNo(&lista, valor2, 4);
    addNoFinal(&lista, valor3);
    addNo(&lista, valor4, 1);

    mostrarLista(&lista);
    



    printf("Primeiro valor da lista: %d\n", lista.inicio->valor);
    printf("Ultimo valor da lista: %d\n", lista.fim->valor);

    removerNo(&lista, 2);

    mostrarLista(&lista);

    printf("Primeiro valor da lista: %d\n", lista.inicio->valor);
    printf("Ultimo valor da lista: %d\n", lista.fim->valor);

    removerNo(&lista, 0);
    mostrarLista(&lista);

    printf("Primeiro valor da lista: %d\n", lista.inicio->valor);
    printf("Ultimo valor da lista: %d\n", lista.fim->valor);

    removerNo(&lista, 10);
    mostrarLista(&lista);

    printf("Primeiro valor da lista: %d\n", lista.inicio->valor);
    printf("Ultimo valor da lista: %d\n", lista.fim->valor);
    

    limparLista(&lista);
    mostrarLista(&lista);




    



















    return 0;
}