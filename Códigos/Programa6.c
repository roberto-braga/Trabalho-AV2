#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    char estado[30];
    int populacao;
} Cidade;

void incluirCidade();
void alterarCidade();
void excluirCidade();
void consultarCidade();
void listarCidades();

int main() {
    int opcao;

    do {
        printf("\n--- Sistema de Cadastro de Cidades ---\n");
        printf("1. Incluir cidade\n");
        printf("2. Alterar dados de uma cidade\n");
        printf("3. Excluir cidade pelo código\n");
        printf("4. Consultar cidade pelo código\n");
        printf("5. Listar todas as cidades cadastradas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: incluirCidade(); break;
            case 2: alterarCidade(); break;
            case 3: excluirCidade(); break;
            case 4: consultarCidade(); break;
            case 5: listarCidades(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

void incluirCidade() {
    FILE *arquivo = fopen("cidades.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Cidade cidade;
    printf("Digite o código da cidade: ");
    scanf("%d", &cidade.codigo);
    printf("Digite o nome da cidade: ");
    getchar();  
    fgets(cidade.nome, sizeof(cidade.nome), stdin);
    cidade.nome[strcspn(cidade.nome, "\n")] = '\0';
    printf("Digite o estado da cidade: ");
    fgets(cidade.estado, sizeof(cidade.estado), stdin);
    cidade.estado[strcspn(cidade.estado, "\n")] = '\0';
    printf("Digite a população da cidade: ");
    scanf("%d", &cidade.populacao);

    fprintf(arquivo, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
    fclose(arquivo);
    printf("Cidade adicionada com sucesso!\n");
}

void alterarCidade() {
    FILE *arquivo = fopen("cidades.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int codigo, encontrado = 0;
    Cidade cidade;

    printf("Digite o código da cidade a ser alterada: ");
    scanf("%d", &codigo);

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        if (cidade.codigo == codigo) {
            encontrado = 1;
            printf("Digite o novo nome da cidade: ");
            getchar(); 
            fgets(cidade.nome, sizeof(cidade.nome), stdin);
            cidade.nome[strcspn(cidade.nome, "\n")] = '\0';
            printf("Digite o novo estado da cidade: ");
            fgets(cidade.estado, sizeof(cidade.estado), stdin);
            cidade.estado[strcspn(cidade.estado, "\n")] = '\0';
            printf("Digite a nova população da cidade: ");
            scanf("%d", &cidade.populacao);
        }
        fprintf(temp, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
    }

    fclose(arquivo);
    fclose(temp);

    remove("cidades.txt");
    rename("temp.txt", "cidades.txt");

    if (encontrado) {
        printf("Dados da cidade atualizados com sucesso!\n");
    } else {
        printf("Cidade com código %d não encontrada!\n", codigo);
    }
}

void excluirCidade() {
    FILE *arquivo = fopen("cidades.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int codigo, encontrado = 0;
    Cidade cidade;

    printf("Digite o código da cidade a ser excluída: ");
    scanf("%d", &codigo);

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        if (cidade.codigo == codigo) {
            encontrado = 1;
            printf("Cidade excluída com sucesso!\n");
        } else {
            fprintf(temp, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("cidades.txt");
    rename("temp.txt", "cidades.txt");

    if (!encontrado) {
        printf("Cidade com código %d não encontrada!\n", codigo);
    }
}

void consultarCidade() {
    FILE *arquivo = fopen("cidades.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int codigo, encontrado = 0;
    Cidade cidade;

    printf("Digite o código da cidade: ");
    scanf("%d", &codigo);

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        if (cidade.codigo == codigo) {
            encontrado = 1;
            printf("\nCódigo: %d\n", cidade.codigo);
            printf("Nome: %s\n", cidade.nome);
            printf("Estado: %s\n", cidade.estado);
            printf("População: %d\n", cidade.populacao);
            break;
        }
    }

    if (!encontrado) {
        printf("Cidade com código %d não encontrada!\n", codigo);
    }

    fclose(arquivo);
}

void listarCidades() {
    FILE *arquivo = fopen("cidades.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Cidade cidade;
    printf("\n--- Lista de Cidades ---\n");

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        printf("\nCódigo: %d\n", cidade.codigo);
        printf("Nome: %s\n", cidade.nome);
        printf("Estado: %s\n", cidade.estado);
        printf("População: %d\n", cidade.populacao);
    }

    fclose(arquivo);
}
