#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char titulo[50];
    char genero[20];
    int ano;
} Filme;

void adicionarFilme();
void alterarFilme();
void excluirFilme();
void consultarFilmePorId();
void listarFilmes();

int main() {
    int opcao;

    do {
        printf("\n--- Sistema de Controle de Filmes ---\n");
        printf("1. Adicionar novo filme\n");
        printf("2. Alterar dados de um filme\n");
        printf("3. Excluir filme pelo ID\n");
        printf("4. Consultar informações de um filme pelo ID\n");
        printf("5. Listar todos os filmes cadastrados\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionarFilme(); break;
            case 2: alterarFilme(); break;
            case 3: excluirFilme(); break;
            case 4: consultarFilmePorId(); break;
            case 5: listarFilmes(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

void adicionarFilme() {
    FILE *arquivo = fopen("filmes.dat", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Filme filme;
    printf("Digite o ID do filme: ");
    scanf("%d", &filme.id);
    printf("Digite o título do filme: ");
    getchar();  
    fgets(filme.titulo, sizeof(filme.titulo), stdin);
    filme.titulo[strcspn(filme.titulo, "\n")] = '\0';
    printf("Digite o gênero do filme: ");
    fgets(filme.genero, sizeof(filme.genero), stdin);
    filme.genero[strcspn(filme.genero, "\n")] = '\0';
    printf("Digite o ano de lançamento do filme: ");
    scanf("%d", &filme.ano);

    fwrite(&filme, sizeof(Filme), 1, arquivo);
    fclose(arquivo);
    printf("Filme adicionado com sucesso!\n");
}

void alterarFilme() {
    FILE *arquivo = fopen("filmes.dat", "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int id, encontrado = 0;
    Filme filme;

    printf("Digite o ID do filme a ser alterado: ");
    scanf("%d", &id);

    while (fread(&filme, sizeof(Filme), 1, arquivo)) {
        if (filme.id == id) {
            encontrado = 1;
            printf("Digite o novo título do filme: ");
            getchar();  
            fgets(filme.titulo, sizeof(filme.titulo), stdin);
            filme.titulo[strcspn(filme.titulo, "\n")] = '\0';
            printf("Digite o novo gênero do filme: ");
            fgets(filme.genero, sizeof(filme.genero), stdin);
            filme.genero[strcspn(filme.genero, "\n")] = '\0';
            printf("Digite o novo ano de lançamento: ");
            scanf("%d", &filme.ano);

            fseek(arquivo, -sizeof(Filme), SEEK_CUR);
            fwrite(&filme, sizeof(Filme), 1, arquivo);
            printf("Dados do filme atualizados com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Filme com ID %d não encontrado!\n", id);
    }

    fclose(arquivo);
}

void excluirFilme() {
    FILE *arquivo = fopen("filmes.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int id, encontrado = 0;
    Filme filme;

    printf("Digite o ID do filme a ser excluído: ");
    scanf("%d", &id);

    while (fread(&filme, sizeof(Filme), 1, arquivo)) {
        if (filme.id == id) {
            encontrado = 1;
            printf("Filme excluído com sucesso!\n");
        } else {
            fwrite(&filme, sizeof(Filme), 1, temp);
        }
    }

    if (!encontrado) {
        printf("Filme com ID %d não encontrado!\n", id);
    }

    fclose(arquivo);
    fclose(temp);

    remove("filmes.dat");
    rename("temp.dat", "filmes.dat");
}

void consultarFilmePorId() {
    FILE *arquivo = fopen("filmes.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int id, encontrado = 0;
    Filme filme;

    printf("Digite o ID do filme: ");
    scanf("%d", &id);

    while (fread(&filme, sizeof(Filme), 1, arquivo)) {
        if (filme.id == id) {
            encontrado = 1;
            printf("\nID: %d\n", filme.id);
            printf("Título: %s\n", filme.titulo);
            printf("Gênero: %s\n", filme.genero);
            printf("Ano de Lançamento: %d\n", filme.ano);
            break;
        }
    }

    if (!encontrado) {
        printf("Filme com ID %d não encontrado!\n", id);
    }

    fclose(arquivo);
}

void listarFilmes() {
    FILE *arquivo = fopen("filmes.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Filme filme;
    printf("\n--- Lista de Filmes ---\n");

    while (fread(&filme, sizeof(Filme), 1, arquivo)) {
        printf("\nID: %d\n", filme.id);
        printf("Título: %s\n", filme.titulo);
        printf("Gênero: %s\n", filme.genero);
        printf("Ano de Lançamento: %d\n", filme.ano);
    }

    fclose(arquivo);
}
