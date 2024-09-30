#ifndef LISTAENCADEADA_H_INCLUDED
#define LISTAENCADEADA_H_INCLUDED
#include <iostream>
using namespace std;

template <typename T>
struct No{
    T info;
    No <T> *elo = NULL;
};

template <typename T>
struct LUE{
    No <T> *comeco = NULL;
    No <T> *fim = NULL;
};

// Operações da LUE
template <typename T>
void inicializarLUE( LUE <T> &lista ){
    lista.comeco = NULL;
    lista.fim = NULL;
}

template <typename T>
bool inserirFinalLUE( LUE <T> &lista, T valor ){
    No <T> *novo = new No <T>;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->elo = NULL;

    if( lista.comeco == NULL ){ // Caso 1 - lista vazia
        lista.comeco = novo;
        lista.fim = novo;
    }
    else{   // Caso 2 - Inserir no final
        lista.fim->elo = novo;
        lista.fim = novo;
    }
    return true;
}

template <typename T>
bool inserirLUE(LUE <T> &lista, T valor){
    No <T> *novo = new No <T>;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->elo = NULL;

    if( lista.comeco == NULL ){ // Caso A
        lista.comeco = novo;
        lista.fim = novo;
    }
    else if( valor < lista.comeco->info ){ // Caso B
        novo->elo = lista.comeco;
        lista.comeco = novo;
    }
    else if( valor > lista.fim->info ){ // Caso C
        lista.fim->elo = novo;
        lista.fim = novo;
    }
    else{ // Caso D
        No <T> *aux = lista.comeco;
        while( aux != NULL ){
            No <T> *prox = aux->elo;
            if( aux->info < valor && valor < prox->info ){
                novo->elo = prox;
                aux->elo = novo;
                break;
            }
            aux = aux->elo;
        }
    }
    return true;
}

template <typename T>
bool retirarLUE( LUE <T> &lista, T valor ){
    if( lista.comeco == NULL ) return false;
    No <T> *aux, *ant;

    if( valor == lista.comeco->info ){ // Caso a ou b
        aux = lista.comeco;
        if( aux->elo == NULL ){ // Caso a
            lista.comeco = NULL;
            lista.fim = NULL;
        }
        else{ // Caso b
            lista.comeco = aux->elo;
        }
    }
    else{ // Casos c e d
        ant = NULL;
        aux = lista.comeco;
        while( aux != NULL ){
            if( aux->info == valor ){
                if( valor == lista.fim->info ){ // Caso c
                    ant->elo = NULL;
                    lista.fim = ant;
                }
                else{ // Caso d
                    ant->elo = aux->elo;
                }
                break;
            }
            ant = aux;
            aux = aux->elo;
        }
        if( aux == NULL ) return false;
    }
    delete aux;
    return true;
}

template <typename T>
void mostrarLUE(LUE <T> lista){
    No <T> *aux = lista.comeco;
    while( aux != NULL ){
        cout << aux->info << " ";
        aux = aux->elo; // Avança para o próximo no
    }
}

template <typename T>
void liberarLUE(LUE <T> &lista){
    No <T> *temp, *aux = lista.comeco;
    while( aux != NULL ){
        temp = aux;
        aux = aux->elo;
        delete temp;
    }
    lista.comeco = lista.fim = NULL;
}

// Retornar true se o valor for encontrado ou false se não estiver na lista
template <typename T>
bool pesquisarLUE(LUE <T> lista, T valor){
    No <T> *aux = lista.comeco;
    while( aux != NULL ){
        if( aux->info == valor ) return true;
        aux = aux->elo;
    }
    return false;
}




#endif // LISTAENCADEADA_H_INCLUDED
