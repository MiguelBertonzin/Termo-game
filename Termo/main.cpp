/*Estrutura de dados
Atividade: Trabalho M1 TERMO
Alunos: Diego Bourguignon Rangel e Miguel Bertonzin   */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "ListaEncadeada.h" // Utilizando o código da lista encadeada previamente criado

using namespace std;

// Função para converter strings para maiúsculas
string toUpperCase(const string &str) {
    string result = str;
    for (char &c : result) {
        c = toupper(c);
    }
    return result;
}

// Função para ler palavras do arquivo e inserir na lista encadeada
void lerPalavras(LUE<string> &lista, const string &nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    string palavra;
    if (arquivo.is_open()) {
        while (getline(arquivo, palavra)) {
            palavra = toUpperCase(palavra);  // Converte para maiúsculas
            if (palavra.length() == 5) {
                inserirFinalLUE(lista, palavra);
            }
        }
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }
}

// Função para salvar palavras no arquivo
void salvarPalavras(LUE<string> &lista, const string &nomeArquivo) { //abre o arquivo e escreve cada palabra no arquivo em cada linha
    ofstream arquivo(nomeArquivo);
    No<string> *aux = lista.comeco;
    if (arquivo.is_open()) {
        while (aux != NULL) {
            arquivo << aux->info << endl;
            aux = aux->elo;
        }
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo para salvar." << endl;
    }
}

// Função para mostrar o feedback do jogo (verde para correto, amarelo para letra certa no lugar errado)
void mostrarFeedback(const string &palavraSecreta, const string &palpite) {
    for (size_t i = 0; i < palpite.size(); ++i) {                            // Itera por cada letra do palpite
        if (palpite[i] == palavraSecreta[i]) {                               // Verifica se a letra está na posição correta
            cout << "[" << palpite[i] << "] ";                               // Letra correta na posição correta
        } else if (palavraSecreta.find(palpite[i]) != string::npos) {        // Verifica se a letra existe na palavra secreta em outra posição
            cout << "<" << palpite[i] << "> ";                               // Letra correta na posição errada
        } else {
            cout << palpite[i] << " ";                                       // Letra errada
        }
    }
    cout << endl;
}

// Função para selecionar uma palavra aleatória da lista de palavras
string sortearPalavra(LUE<string> &palavras) {
    int tamanho = 0;
    No<string>* aux = palavras.comeco;

    // Conta quantas palavras existem na lista
    while (aux != NULL) {
        tamanho++;
        aux = aux->elo;
    }

    // Sorteia um índice aleatório
    int index = rand() % tamanho;
    aux = palavras.comeco;
    for (int i = 0; i < index; ++i) {
        aux = aux->elo;
    }
    return aux->info;
}

// Função para selecionar palavras aleatórias da lista, garantindo que todas sejam diferentes
void sortearPalavrasDiferentes(LUE<string> &listaPalavras, LUE<string> &palavrasSorteadas, int numPalavras) {
    for (int i = 0; i < numPalavras; ++i) {
        bool palavraUnica = false;
        while (!palavraUnica) {
            string novaPalavra = sortearPalavra(listaPalavras);
            palavraUnica = true;
            // Verifica se a nova palavra já foi sorteada anteriormente
            No<string>* aux = palavrasSorteadas.comeco;
            while (aux != NULL) {
                if (aux->info == novaPalavra) {
                    palavraUnica = false;  // Palavra já existe, sortear novamente
                    break;
                }
                aux = aux->elo;
            }
            if (palavraUnica) {
                inserirFinalLUE(palavrasSorteadas, novaPalavra);  // Adiciona palavra única à lista de sorteadas
            }
        }
    }
}

// Função para iniciar o jogo
void iniciarJogo(LUE<string> &listaPalavras, int numPalavras) {
    LUE<string> listaTentativas;
    inicializarLUE(listaTentativas);

    LUE<string> palavrasSorteadas;
    inicializarLUE(palavrasSorteadas);

    bool palavrasAcertadas[numPalavras] = {false};  // rastrear palavras acertadas

    sortearPalavrasDiferentes(listaPalavras, palavrasSorteadas, numPalavras);  // Agora usando a nova função

    int tentativasMax = 6 + 2 * (numPalavras - 1); // Ajusta número de tentativas conforme o número de palavras
    cout << "Jogo iniciado com " << numPalavras << " palavra(s)!" << endl;
    cout << "Você tem " << tentativasMax << " tentativas." << endl;

    for (int tentativa = 1; tentativa <= tentativasMax; ++tentativa) {
        string palpite;
        cout << "Tentativa " << tentativa << ": ";
        cin >> palpite;
        cout << endl;

        palpite = toUpperCase(palpite); // Converte para maiúsculas
        if (palpite.size() != 5) {
            cout << "A palavra deve ter 5 letras." << endl;
            --tentativa; // Não conta como tentativa válida
            continue;
        }

        inserirFinalLUE(listaTentativas, palpite);

        // Mostra feedback apenas para as palavras que ainda não foram acertadas
        bool acertouTodas = true;  // Verifica se todas as palavras foram acertadas
        No<string>* auxPalavraSorteada = palavrasSorteadas.comeco;
        for (int i = 0; i < numPalavras; ++i) {
            if (!palavrasAcertadas[i] && auxPalavraSorteada != NULL) {
                cout << "Palavra " << i+1 << ": ";
                mostrarFeedback(auxPalavraSorteada->info, palpite);

                // Se o palpite for correto, marca como acertada
                if (auxPalavraSorteada->info == palpite) {
                    palavrasAcertadas[i] = true;
                    cout << "Você acertou a palavra " << i+1 << "!" << endl << endl;
                } else {
                    acertouTodas = false;  // Nem todas as palavras foram acertadas
                }
            }
            auxPalavraSorteada = auxPalavraSorteada->elo;
        }

        // Checa se o jogador acertou todas as palavras
        if (acertouTodas) {
            cout << "Parabéns, você acertou todas as palavras!" << endl;
            break;
        }

        if (tentativa == tentativasMax) {
            cout << "Você esgotou suas tentativas!" << endl;
        }
    }

    cout << "Histórico de tentativas:" << endl;
    mostrarLUE(listaTentativas);
    cout << endl;
    liberarLUE(listaTentativas);
    liberarLUE(palavrasSorteadas);
}


// Menu principal para gerenciamento das palavras e o jogo
void menu(LUE<string> &lista) {
    int opcao;
    string palavra;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Inserir palavra" << endl;
        cout << "2. Remover palavra" << endl;
        cout << "3. Mostrar palavras" << endl;
        cout << "4. Iniciar jogo" << endl;
        cout << "5. Salvar e sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch(opcao) {
            case 1:
                cout << "Digite a palavra: ";
                cin >> palavra;
                palavra = toUpperCase(palavra); // Converte para maiúsculas
                if (palavra.length() != 5) {
                    cout << "A palavra deve ter 5 letras. Palavra não inserida." << endl;
                } else if (pesquisarLUE(lista, palavra)) { // Verifica se já tem na lista
                    cout << "A palavra '" << palavra << "' já está na lista e não será inserida novamente." << endl;
                } else if (inserirFinalLUE(lista, palavra)) {
                    cout << "Palavra '" << palavra << "' inserida com sucesso." << endl;
                } else {
                    cout << "Erro ao inserir a palavra '" << palavra << "'." << endl;
                }
                break;
            case 2:
                cout << "Digite a palavra a remover: ";
                cin >> palavra;
                palavra = toUpperCase(palavra); // Converte para maiúsculas
                if (retirarLUE(lista, palavra)) {
                    cout << "Palavra '" << palavra << "' removida com sucesso." << endl;
                } else {
                    cout << "Palavra '" << palavra << "' não encontrada." << endl;
                }
                break;
            case 3:
                mostrarLUE(lista);
                cout << endl;
                break;
            case 4: {
                int numPalavras;
                cout << "Quantas palavras você quer jogar simultaneamente (1 a 4)? ";
                cin >> numPalavras;

                if (numPalavras < 1 || numPalavras > 4) {
                    cout << "Número inválido de palavras!" << endl;
                } else {
                    iniciarJogo(lista, numPalavras);
                }
                break;
            }
            case 5:
                cout << "Salvando palavras e saindo..." << endl;
                salvarPalavras(lista, "Palavras.txt");
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } while(opcao != 5);
}


int main() {
    setlocale(LC_ALL, "Portuguese");  // Para suportar caracteres especiais
    srand(time(0));  // Inicializa para usar números random

    LUE<string> lista;
    inicializarLUE(lista);

    // Carrega as palavras do arquivo
    lerPalavras(lista, "Palavras.txt");

    // Exibe o menu e manipula as opções
    menu(lista);

    // Libera a memória da lista
    liberarLUE(lista);

    return 0;
}


