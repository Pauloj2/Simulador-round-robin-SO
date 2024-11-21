#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <queue>  // Incluindo a fila para gerenciar os processos prontos

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

// Função para simular o algoritmo Round-Robin
void roundRobin(Lista& lista, int quantum) {
    int tempoAtual = 0;
    int processosRestantes = 0;
    No* atual = lista.primeiro;

    // Array para registrar a ordem de execução
    string ordemExecucao[1000];
    int execIndex = 0;

    // Conta o número de processos
    while (atual) {
        processosRestantes++;
        atual = atual->proximo;
    }

    printf("************************************\n");
    printf("Simulacao Round-Robin\n");

    // Fila para os processos prontos para execução
    queue<No*> fila;

    // Insere os processos na fila inicial que chegam no tempo 0
    atual = lista.primeiro;
    while (atual && atual->tempoChegada <= tempoAtual) {
        fila.push(atual);
        atual = atual->proximo;
    }

    while (processosRestantes > 0) {
        if (!fila.empty()) {
            No* processo = fila.front();
            fila.pop();

            // Processa o quantum ou até o tempo restante do processo
            int tempoInicio = tempoAtual;
            int tempoProcessado = (processo->tempoRestante < quantum) ? processo->tempoRestante : quantum;
            tempoAtual += tempoProcessado;
            processo->tempoRestante -= tempoProcessado;

            // Registra a execução do processo
            printf("Tempo %d-%d: %s executando\n", tempoInicio, tempoAtual, processo->nomeProcesso.c_str());
            for (int i = 0; i < tempoProcessado; i++) {
                ordemExecucao[execIndex++] = processo->nomeProcesso;
            }

            // Adiciona novos processos que chegaram durante a execução
            while (atual && atual->tempoChegada <= tempoAtual) {
                fila.push(atual);
                atual = atual->proximo;
            }

            // Se o processo ainda não terminou, retorna para o final da fila
            if (processo->tempoRestante > 0) {
                fila.push(processo);
            } else {
                processosRestantes--;
                printf(" -> %s concluido no tempo %d\n", processo->nomeProcesso.c_str(), tempoAtual);
            }
        } else {
            // Incrementa o tempo se nenhum processo está pronto
            tempoAtual++;
            // Adiciona novos processos que chegaram enquanto o tempo avançava
            while (atual && atual->tempoChegada <= tempoAtual) {
                fila.push(atual);
                atual = atual->proximo;
            }
        }
    }

    // Exibe a ordem de execução
    printf("************************************\n");

    printf("\n--- Ordem de Execucao ---\n");
    printf("Tempo Enumerados -> ");
    for (int i = 0; i < execIndex; i++) {
        printf("T%d  ", i);
    }
    printf("\n");
    printf("Nome Do Processo -> ");
    for (int i = 0; i < execIndex; i++) {
        printf("%s  ", ordemExecucao[i].c_str());
    }
    printf("\n--- Fim da Simulacao ---\n");
}

int main() {
    Lista lista;
    int quantProcessos, quantum;
    printf("===================================================\n");
    printf("    ALGORITMO DE ESCALONAMENTO ROUND-ROBIN (RR)   \n");
    printf("===================================================\n\n");

    printf("Qual a quantidade de processos (maximo 15): ");
    scanf("%d", &quantProcessos);
    if (quantProcessos > 15) {
        printf("Numero de processos deve ser no maximo 15.\n");
        return 1;
    }

    printf("Digite o tempo de Quantum: ");
    scanf("%d", &quantum);

    for (int i = 0; i < quantProcessos; i++) {
        char nome[100];
        int chegada, uso;

        printf("\n======= Cadastro do Processo %d ============\n", i + 1);
        printf("Digite o nome do processo: ");
        scanf("%s", nome);
        printf("Digite o tempo de chegada do processo: ");
        scanf("%d", &chegada);
        printf("Digite o tempo de uso do processo na CPU: ");
        scanf("%d", &uso);
        printf("===========================================\n");

        lista.adicionar(string(nome), chegada, uso);
    }

    // Chama a função que ordena os processos por tempo de chegada
    lista.ordenarPorChegada();

    // Chama a função que exibe a lista de processos ordenada
    lista.imprimirLista();

    // Chama a função que Executa a simulação do algoritmo Round-Robin
    roundRobin(lista, quantum);

    return 0;
}
