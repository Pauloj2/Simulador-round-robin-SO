#include <stdio.h>
#include <stdlib.h>
#include <string>

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

    // Ordena os processos por tempo de chegada para ser executado da forma correta
    void ordenarPorChegada() {
        if (vazia() || !primeiro->proximo) return;

        No* ordenada = NULL; // Lista auxiliar para manter os nós ordenados
        No* atual = primeiro;

        while (atual != NULL) {
            No* proximo = atual->proximo; // Armazena o próximo nó
            if (!ordenada || atual->tempoChegada < ordenada->tempoChegada) {
                atual->proximo = ordenada;
                ordenada = atual;
            } else {
                No* aux = ordenada;
                while (aux->proximo && aux->proximo->tempoChegada <= atual->tempoChegada) {
                    aux = aux->proximo;
                }
                atual->proximo = aux->proximo;
                aux->proximo = atual;
            }
            atual = proximo;
        }

        // Atualiza o ponteiro da lista para a nova lista ordenada
        primeiro = ordenada;
        // Atualiza o ponteiro "ultimo"
        ultimo = primeiro;
        while (ultimo && ultimo->proximo) {
            ultimo = ultimo->proximo;
        }
    }

    // Exibe os processos na lista
    void imprimirLista() {
        No* atual = primeiro;
        printf("\n");
        printf("------------------------------------------");
        printf("\nProcessos ordenados por tempo de chegada\n");
        printf("------------------------------------------\n");
        while (atual != NULL) {
            printf("Processo %s: chegada=%d, duracao=%d\n",
                   atual->nomeProcesso.c_str(), atual->tempoChegada, atual->tempoUso);
            atual = atual->proximo;
        }
        printf("------------------------------------------");
        printf("\n\n");
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
