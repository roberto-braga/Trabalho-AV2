#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char titulo[50];
    char autor[50];
    int ano;
} Livro;

void adicionarLivro();
void alterarLivro();
void excluirLivro();
void consultarLivro();
void listarLivros();

int main() {
    int opcao;

    do {
        printf("\n--- Gerenciamento de Livros ---\n");
        printf("1. Adicionar novo livro ao catálogo\n");
        printf("2. Alterar dados de um livro\n");
        printf("3. Excluir livro pelo código\n");
        printf("4. Consultar informações de um livro\n");
        printf("5. Listar todos os livros cadastrados\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionarLivro(); break;
            case 2: alterarLivro(); break;
            case 3: excluirLivro(); break;
            case 4: consultarLivro(); break;
            case 5: listarLivros(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

void adicionarLivro() {
    FILE *arquivo = fopen("livros.dat", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Livro livro;
    printf("Digite o código do livro: ");
    scanf("%d", &livro.codigo);
    printf("Digite o título do livro: ");
    getchar();  // Limpar o buffer
    fgets(livro.titulo, sizeof(livro.titulo), stdin);
    livro.titulo[strcspn(livro.titulo, "\n")] = '\0';
    printf("Digite o nome do autor: ");
    fgets(livro.autor, sizeof(livro.autor), stdin);
    livro.autor[strcspn(livro.autor, "\n")] = '\0';
    printf("Digite o ano de publicação: ");
    scanf("%d", &livro.ano);

    fwrite(&livro, sizeof(Livro), 1, arquivo);
    fclose(arquivo);
    printf("Livro adicionado com sucesso!\n");
}

// Função para alterar os dados de um livro
void alterarLivro() {
    FILE *arquivo = fopen("livros.dat", "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int codigo, encontrado = 0;
    Livro livro;

    printf("Digite o código do livro a ser alterado: ");
    scanf("%d", &codigo);

    while (fread(&livro, sizeof(Livro), 1, arquivo)) {
        if (livro.codigo == codigo) {
            encontrado = 1;
            printf("Digite o novo título do livro: ");
            getchar(); 
            fgets(livro.titulo, sizeof(livro.titulo), stdin);
            livro.titulo[strcspn(livro.titulo, "\n")] = '\0';
            printf("Digite o novo autor do livro: ");
            fgets(livro.autor, sizeof(livro.autor), stdin);
            livro.autor[strcspn(livro.autor, "\n")] = '\0';
            printf("Digite o novo ano de publicação: ");
            scanf("%d", &livro.ano);

            fseek(arquivo, -sizeof(Livro), SEEK_CUR);
            fwrite(&livro, sizeof(Livro), 1, arquivo);
            printf("Dados do livro atualizados com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Livro com código %d não encontrado!\n", codigo);
    }

    fclose(arquivo);
}

void excluirLivro() {
    FILE *arquivo = fopen("livros.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int codigo, encontrado = 0;
    Livro livro;

    printf("Digite o código do livro a ser excluído: ");
    scanf("%d", &codigo);

    while (fread(&livro, sizeof(Livro), 1, arquivo)) {
        if (livro.codigo == codigo) {
            encontrado = 1;
            printf("Livro excluído com sucesso!\n");
        } else {
            fwrite(&livro, sizeof(Livro), 1, temp);
        }
    }

    if (!encontrado) {
        printf("Livro com código %d não encontrado!\n", codigo);
    }

    fclose(arquivo);
    fclose(temp);

    remove("livros.dat");
    rename("temp.dat", "livros.dat");
}

void consultarLivro() {
    FILE *arquivo = fopen("livros.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int codigo, encontrado = 0;
    Livro livro;

    printf("Digite o código do livro: ");
    scanf("%d", &codigo);

    while (fread(&livro, sizeof(Livro), 1, arquivo)) {
        if (livro.codigo == codigo) {
            encontrado = 1;
            printf("\nCódigo: %d\n", livro.codigo);
            printf("Título: %s\n", livro.titulo);
            printf("Autor: %s\n", livro.autor);
            printf("Ano de Publicação: %d\n", livro.ano);
            break;
        }
    }

    if (!encontrado) {
        printf("Livro com código %d não encontrado!\n", codigo);
    }

    fclose(arquivo);
}

void listarLivros() {
    FILE *arquivo = fopen("livros.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Livro livro;
    printf("\n--- Lista de Livros ---\n");

    while (fread(&livro, sizeof(Livro), 1, arquivo)) {
        printf("\nCódigo: %d\n", livro.codigo);
        printf("Título: %s\n", livro.titulo);
        printf("Autor: %s\n", livro.autor);
        printf("Ano de Publicação: %d\n", livro.ano);
    }

    fclose(arquivo);
}
