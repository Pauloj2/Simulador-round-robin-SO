#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

// Estrutura de nó para representar um processo
struct No {
    string nomeProcesso;
    int tempoChegada;
    int tempoUso;
    int tempoRestante;
    string estado;
    No* proximo;

    No(const string& _nome, int _chegada, int _uso) {
        nomeProcesso = _nome;
        tempoChegada = _chegada;
        tempoUso = _uso;
        tempoRestante = tempoUso;
        estado = "Pronto";
        proximo = NULL;
    }
};

// Estrutura da lista encadeada para adicionar os processos
struct Lista {
    No* primeiro;
    No* ultimo;

    Lista() {
        primeiro = NULL;
        ultimo = NULL;
    }

    // Adiciona um processo ao final da lista
    void adicionar(const string& nome, int chegada, int uso) {
        No* novo = new No(nome, chegada, uso);
        if (ultimo) {
            ultimo->proximo = novo;
        } else {
            primeiro = novo;
        }
        ultimo = novo;
    }

    // Verifica se a lista está vazia
    bool vazia() {
        return primeiro == NULL;
    }

};


int main() {
    Lista lista;
    int qtdProcessos, quantum;

    printf("Informe o numero de processos (maximo 15): ");
    scanf("%d", &qtdProcessos);
    if (qtdProcessos > 15) {
        printf("Numero de processos deve ser no maximo 15.\n");
        return 1;
    }

    printf("Digite o tempo de Quantum: ");
    scanf("%d", &quantum);

    return 0;
}
