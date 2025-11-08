#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

// Estrutura que representa um item da mochila
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n=== MOCHILA DE SOBREVIVENCIA ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                if (total >= MAX_ITENS) {
                    printf("\n⚠️  Mochila cheia! Nao e possivel adicionar mais itens.\n");
                } else {
                    printf("\nDigite o nome do item: ");
                    fgets(mochila[total].nome, MAX_NOME, stdin);
                    mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0'; // Remove \n

                    printf("Digite o tipo do item: ");
                    fgets(mochila[total].tipo, MAX_TIPO, stdin);
                    mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

                    printf("Digite a quantidade: ");
                    scanf("%d", &mochila[total].quantidade);
                    getchar();

                    total++;
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
                        printf("\n🗑️  Item removido com sucesso!\n");
                        break;
                    }
                }
                if (!encontrado)
                    printf("\n❌ Item nao encontrado.\n");
                break;
            }

            case 3:
                if (total == 0) {
                    printf("\n📦 Mochila vazia.\n");
                } else {
                    printf("\n=== ITENS NA MOCHILA ===\n");
                    printf("%-3s | %-20s | %-15s | %-10s\n", "N", "Nome", "Tipo", "Qtd");
                    printf("------------------------------------------------------\n");
                    for (int i = 0; i < total; i++) {
                        printf("%-3d | %-20s | %-15s | %-10d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
                    }
                }
                break;

            case 0:
                printf("\n🏝️  Saindo da ilha... Boa sorte, sobrevivente!\n");
                break;

            default:
                printf("\n❗ Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
