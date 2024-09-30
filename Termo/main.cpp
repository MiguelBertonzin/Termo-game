/*Estrutura de dados
Atividade: Trabalho M1 TERMO
Alunos: Diego Bourguignon Rangel e Miguel Bertonzin   */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "ListaEncadeada.h" // Utilizando o c�digo da lista encadeada previamente criado

using namespace std;

// Fun��o para converter strings para mai�sculas
string toUpperCase(const string &str) {
    string result = str;
    for (char &c : result) {
        c = toupper(c);
    }
    return result;
}

// Fun��o para ler palavras do arquivo e inserir na lista encadeada
void lerPalavras(LUE<string> &lista, const string &nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    string palavra;
    if (arquivo.is_open()) {
        while (getline(arquivo, palavra)) {
            palavra = toUpperCase(palavra);  // Converte para mai�sculas
            if (palavra.length() == 5) {
                inserirFinalLUE(lista, palavra);
            }
        }
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }
}

// Fun��o para salvar palavras no arquivo
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

// Fun��o para mostrar o feedback do jogo (verde para correto, amarelo para letra certa no lugar errado)
void mostrarFeedback(const string &palavraSecreta, const string &palpite) {
    for (size_t i = 0; i < palpite.size(); ++i) {                            // Itera por cada letra do palpite
        if (palpite[i] == palavraSecreta[i]) {                               // Verifica se a letra est� na posi��o correta
            cout << "[" << palpite[i] << "] ";                               // Letra correta na posi��o correta
        } else if (palavraSecreta.find(palpite[i]) != string::npos) {        // Verifica se a letra existe na palavra secreta em outra posi��o
            cout << "<" << palpite[i] << "> ";                               // Letra correta na posi��o errada
        } else {
            cout << palpite[i] << " ";                                       // Letra errada
        }
    }
    cout << endl;
}

// Fun��o para selecionar uma palavra aleat�ria da lista de palavras
string sortearPalavra(LUE<string> &palavras) {
    int tamanho = 0;
    No<string>* aux = palavras.comeco;

    // Conta quantas palavras existem na lista
    while (aux != NULL) {
        tamanho++;
        aux = aux->elo;
    }

    // Sorteia um �ndice aleat�rio
    int index = rand() % tamanho;
    aux = palavras.comeco;
    for (int i = 0; i < index; ++i) {
        aux = aux->elo;
    }
    return aux->info;
}

// Fun��o para selecionar palavras aleat�rias da lista, garantindo que todas sejam diferentes
void sortearPalavrasDiferentes(LUE<string> &listaPalavras, LUE<string> &palavrasSorteadas, int numPalavras) {
    for (int i = 0; i < numPalavras; ++i) {
        bool palavraUnica = false;
        while (!palavraUnica) {
            string novaPalavra = sortearPalavra(listaPalavras);
            palavraUnica = true;
            // Verifica se a nova palavra j� foi sorteada anteriormente
            No<string>* aux = palavrasSorteadas.comeco;
            while (aux != NULL) {
                if (aux->info == novaPalavra) {
                    palavraUnica = false;  // Palavra j� existe, sortear novamente
                    break;
                }
                aux = aux->elo;
            }
            if (palavraUnica) {
                inserirFinalLUE(palavrasSorteadas, novaPalavra);  // Adiciona palavra �nica � lista de sorteadas
            }
        }
    }
}

// Fun��o para iniciar o jogo
void iniciarJogo(LUE<string> &listaPalavras, int numPalavras) {
    LUE<string> listaTentativas;
    inicializarLUE(listaTentativas);

    LUE<string> palavrasSorteadas;
    inicializarLUE(palavrasSorteadas);

    bool palavrasAcertadas[numPalavras] = {false};  // rastrear palavras acertadas

    sortearPalavrasDiferentes(listaPalavras, palavrasSorteadas, numPalavras);  // Agora usando a nova fun��o

    int tentativasMax = 6 + 2 * (numPalavras - 1); // Ajusta n�mero de tentativas conforme o n�mero de palavras
    cout << "Jogo iniciado com " << numPalavras << " palavra(s)!" << endl;
    cout << "Voc� tem " << tentativasMax << " tentativas." << endl;

    for (int tentativa = 1; tentativa <= tentativasMax; ++tentativa) {
        string palpite;
        cout << "Tentativa " << tentativa << ": ";
        cin >> palpite;
        cout << endl;

        palpite = toUpperCase(palpite); // Converte para mai�sculas
        if (palpite.size() != 5) {
            cout << "A palavra deve ter 5 letras." << endl;
            --tentativa; // N�o conta como tentativa v�lida
            continue;
        }

        inserirFinalLUE(listaTentativas, palpite);

        // Mostra feedback apenas para as palavras que ainda n�o foram acertadas
        bool acertouTodas = true;  // Verifica se todas as palavras foram acertadas
        No<string>* auxPalavraSorteada = palavrasSorteadas.comeco;
        for (int i = 0; i < numPalavras; ++i) {
            if (!palavrasAcertadas[i] && auxPalavraSorteada != NULL) {
                cout << "Palavra " << i+1 << ": ";
                mostrarFeedback(auxPalavraSorteada->info, palpite);

                // Se o palpite for correto, marca como acertada
                if (auxPalavraSorteada->info == palpite) {
                    palavrasAcertadas[i] = true;
                    cout << "Voc� acertou a palavra " << i+1 << "!" << endl << endl;
                } else {
                    acertouTodas = false;  // Nem todas as palavras foram acertadas
                }
            }
            auxPalavraSorteada = auxPalavraSorteada->elo;
        }

        // Checa se o jogador acertou todas as palavras
        if (acertouTodas) {
            cout << "Parab�ns, voc� acertou todas as palavras!" << endl;
            break;
        }

        if (tentativa == tentativasMax) {
            cout << "Voc� esgotou suas tentativas!" << endl;
        }
    }

    cout << "Hist�rico de tentativas:" << endl;
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
                palavra = toUpperCase(palavra); // Converte para mai�sculas
                if (palavra.length() != 5) {
                    cout << "A palavra deve ter 5 letras. Palavra n�o inserida." << endl;
                } else if (pesquisarLUE(lista, palavra)) { // Verifica se j� tem na lista
                    cout << "A palavra '" << palavra << "' j� est� na lista e n�o ser� inserida novamente." << endl;
                } else if (inserirFinalLUE(lista, palavra)) {
                    cout << "Palavra '" << palavra << "' inserida com sucesso." << endl;
                } else {
                    cout << "Erro ao inserir a palavra '" << palavra << "'." << endl;
                }
                break;
            case 2:
                cout << "Digite a palavra a remover: ";
                cin >> palavra;
                palavra = toUpperCase(palavra); // Converte para mai�sculas
                if (retirarLUE(lista, palavra)) {
                    cout << "Palavra '" << palavra << "' removida com sucesso." << endl;
                } else {
                    cout << "Palavra '" << palavra << "' n�o encontrada." << endl;
                }
                break;
            case 3:
                mostrarLUE(lista);
                cout << endl;
                break;
            case 4: {
                int numPalavras;
                cout << "Quantas palavras voc� quer jogar simultaneamente (1 a 4)? ";
                cin >> numPalavras;

                if (numPalavras < 1 || numPalavras > 4) {
                    cout << "N�mero inv�lido de palavras!" << endl;
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
                cout << "Op��o inv�lida!" << endl;
        }
    } while(opcao != 5);
}


int main() {
    setlocale(LC_ALL, "Portuguese");  // Para suportar caracteres especiais
    srand(time(0));  // Inicializa para usar n�meros random

    LUE<string> lista;
    inicializarLUE(lista);

    // Carrega as palavras do arquivo
    lerPalavras(lista, "Palavras.txt");

    // Exibe o menu e manipula as op��es
    menu(lista);

    // Libera a mem�ria da lista
    liberarLUE(lista);

    return 0;
}


