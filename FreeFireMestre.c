#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

// Enumeração para critérios de ordenação
typedef enum {
    POR_NOME = 1,
    POR_TIPO,
    POR_PRIORIDADE
} CriterioOrdenacao;

// Estrutura do item
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

// Função para exibir a mochila
void listarItens(Item mochila[], int total) {
    if (total == 0) {
        printf("\n📦 Mochila vazia.\n");
        return;
    }

    printf("\n=== ITENS NA MOCHILA ===\n");
    printf("%-3s | %-20s | %-15s | %-10s | %-10s\n", "N", "Nome", "Tipo", "Qtd", "Prioridade");
    printf("---------------------------------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        printf("%-3d | %-20s | %-15s | %-10d | %-10d\n",
               i + 1, mochila[i].nome, mochila[i].tipo,
               mochila[i].quantidade, mochila[i].prioridade);
    }
}

// Função para ordenar (Insertion Sort)
void ordenarItens(Item mochila[], int total, CriterioOrdenacao criterio, int *comparacoes) {
    *comparacoes = 0;

    for (int i = 1; i < total; i++) {
        Item atual = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++;
            bool cond = false;

            switch (criterio) {
                case POR_NOME:
                    cond = strcmp(mochila[j].nome, atual.nome) > 0;
                    break;
                case POR_TIPO:
                    cond = strcmp(mochila[j].tipo, atual.tipo) > 0;
                    break;
                case POR_PRIORIDADE:
                    cond = mochila[j].prioridade > atual.prioridade;
                    break;
            }

            if (cond) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }
        mochila[j + 1] = atual;
    }
}

// Função para busca binária (somente se ordenado por nome)
int buscaBinaria(Item mochila[], int total, const char *nome, int *comparacoes) {
    int inicio = 0, fim = total - 1;
    *comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(nome, mochila[meio].nome);

        if (cmp == 0) return meio;
        else if (cmp < 0) fim = meio - 1;
        else inicio = meio + 1;
    }
    return -1;
}

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;
    bool ordenadoPorNome = false;

    do {
        printf("\n=== MOCHILA DE SOBREVIVENCIA - NIVEL MESTRE ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Ordenar mochila\n");
        printf("5. Buscar item por nome (busca binaria)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                if (total >= MAX_ITENS) {
                    printf("\n⚠️  Mochila cheia! Nao e possivel adicionar mais itens.\n");
                } else {
                    printf("\nDigite o nome do item: ");
                    fgets(mochila[total].nome, MAX_NOME, stdin);
                    mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0';

                    printf("Digite o tipo do item: ");
                    fgets(mochila[total].tipo, MAX_TIPO, stdin);
                    mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

                    printf("Digite a quantidade: ");
                    scanf("%d", &mochila[total].quantidade);
                    getchar();

                    printf("Digite a prioridade (1 a 5): ");
                    scanf("%d", &mochila[total].prioridade);
                    getchar();

                    if (mochila[total].prioridade < 1 || mochila[total].prioridade > 5)
                        mochila[total].prioridade = 3; // valor padrão

                    total++;
                    ordenadoPorNome = false;
                    printf("\n✅ Item adicionado com sucesso!\n");
                }
                break;

            case 2: {
                if (total == 0) {
                    printf("\n⚠️  Nenhum item para remover.\n");
                    break;
                }

                char nomeRemover[MAX_NOME];
                printf("\nDigite o nome do item que deseja remover: ");
                fgets(nomeRemover, MAX_NOME, stdin);
                nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

                int encontrado = 0;
                for (int i = 0; i < total; i++) {
                    if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                        for (int j = i; j < total - 1; j++) {
                            mochila[j] = mochila[j + 1];
                        }
                        total--;
                        encontrado = 1;
                        ordenadoPorNome = false;
                        printf("\n🗑️  Item removido com sucesso!\n");
                        break;
                    }
                }
                if (!encontrado)
                    printf("\n❌ Item nao encontrado.\n");
                break;
            }

            case 3:
                listarItens(mochila, total);
                break;

            case 4: {
                if (total == 0) {
                    printf("\n⚠️  Nenhum item para ordenar.\n");
                    break;
                }

                int criterio;
                printf("\nEscolha o criterio de ordenacao:\n");
                printf("1. Nome\n");
                printf("2. Tipo\n");
                printf("3. Prioridade\n");
                printf("Opcao: ");
                scanf("%d", &criterio);
                getchar();

                int comparacoes = 0;
                ordenarItens(mochila, total, criterio, &comparacoes);

                if (criterio == POR_NOME) ordenadoPorNome = true;
                else ordenadoPorNome = false;

                printf("\n✅ Mochila ordenada com sucesso!\n");
                printf("🔢 Comparacoes realizadas: %d\n", comparacoes);
                listarItens(mochila, total);
                break;
            }

            case 5: {
                if (!ordenadoPorNome) {
                    printf("\n⚠️  Para usar a busca binaria, a mochila deve estar ordenada por nome!\n");
                    break;
                }

                char nomeBusca[MAX_NOME];
                printf("\nDigite o nome do item para buscar: ");
                fgets(nomeBusca, MAX_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                int comparacoes = 0;
                int pos = buscaBinaria(mochila, total, nomeBusca, &comparacoes);

                if (pos != -1) {
                    printf("\n🔎 Item encontrado!\n");
                    printf("Nome: %s\n", mochila[pos].nome);
                    printf("Tipo: %s\n", mochila[pos].tipo);
                    printf("Quantidade: %d\n", mochila[pos].quantidade);
                    printf("Prioridade: %d\n", mochila[pos].prioridade);
                } else {
                    printf("\n❌ Item nao encontrado na mochila.\n");
                }
                printf("🔢 Comparacoes na busca: %d\n", comparacoes);
                break;
            }

            case 0:
                printf("\n🏆 Parabéns, mestre! Você dominou o Código da Ilha!\n");
                break;

            default:
                printf("\n❗ Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
