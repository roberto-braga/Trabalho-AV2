#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matricula;
    char nome[50];
    char curso[30];
    int idade;
} Aluno;

void incluirAluno();
void alterarAluno();
void excluirAluno();
void consultarAluno();
void listarAlunos();

int main() {
    int opcao;

    do {
        printf("\n--- Sistema de Gerenciamento de Alunos ---\n");
        printf("1. Incluir novo aluno\n");
        printf("2. Alterar informações de um aluno\n");
        printf("3. Excluir aluno pelo número de matrícula\n");
        printf("4. Consultar informações de um aluno\n");
        printf("5. Listar todos os alunos cadastrados\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: incluirAluno(); break;
            case 2: alterarAluno(); break;
            case 3: excluirAluno(); break;
            case 4: consultarAluno(); break;
            case 5: listarAlunos(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

void incluirAluno() {
    FILE *arquivo = fopen("alunos.dat", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Aluno aluno;
    printf("Digite o número de matrícula: ");
    scanf("%d", &aluno.matricula);
    printf("Digite o nome do aluno: ");
    getchar();  // Limpar o buffer
    fgets(aluno.nome, sizeof(aluno.nome), stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = '\0';
    printf("Digite o curso do aluno: ");
    fgets(aluno.curso, sizeof(aluno.curso), stdin);
    aluno.curso[strcspn(aluno.curso, "\n")] = '\0';
    printf("Digite a idade do aluno: ");
    scanf("%d", &aluno.idade);

    fwrite(&aluno, sizeof(Aluno), 1, arquivo);
    fclose(arquivo);
    printf("Aluno incluído com sucesso!\n");
}

void alterarAluno() {
    FILE *arquivo = fopen("alunos.dat", "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int matricula, encontrado = 0;
    Aluno aluno;

    printf("Digite o número de matrícula do aluno a ser alterado: ");
    scanf("%d", &matricula);

    while (fread(&aluno, sizeof(Aluno), 1, arquivo)) {
        if (aluno.matricula == matricula) {
            encontrado = 1;
            printf("Digite o novo nome do aluno: ");
            getchar();  // Limpar o buffer
            fgets(aluno.nome, sizeof(aluno.nome), stdin);
            aluno.nome[strcspn(aluno.nome, "\n")] = '\0';
            printf("Digite o novo curso do aluno: ");
            fgets(aluno.curso, sizeof(aluno.curso), stdin);
            aluno.curso[strcspn(aluno.curso, "\n")] = '\0';
            printf("Digite a nova idade do aluno: ");
            scanf("%d", &aluno.idade);

            fseek(arquivo, -sizeof(Aluno), SEEK_CUR);
            fwrite(&aluno, sizeof(Aluno), 1, arquivo);
            printf("Informações do aluno atualizadas com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Aluno com matrícula %d não encontrado!\n", matricula);
    }

    fclose(arquivo);
}

void excluirAluno() {
    FILE *arquivo = fopen("alunos.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int matricula, encontrado = 0;
    Aluno aluno;

    printf("Digite o número de matrícula do aluno a ser excluído: ");
    scanf("%d", &matricula);

    while (fread(&aluno, sizeof(Aluno), 1, arquivo)) {
        if (aluno.matricula == matricula) {
            encontrado = 1;
            printf("Aluno excluído com sucesso!\n");
        } else {
            fwrite(&aluno, sizeof(Aluno), 1, temp);
        }
    }

    if (!encontrado) {
        printf("Aluno com matrícula %d não encontrado!\n", matricula);
    }

    fclose(arquivo);
    fclose(temp);

    remove("alunos.dat");
    rename("temp.dat", "alunos.dat");
}

void consultarAluno() {
    FILE *arquivo = fopen("alunos.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int matricula, encontrado = 0;
    Aluno aluno;

    printf("Digite o número de matrícula do aluno: ");
    scanf("%d", &matricula);

    while (fread(&aluno, sizeof(Aluno), 1, arquivo)) {
        if (aluno.matricula == matricula) {
            encontrado = 1;
            printf("\nMatrícula: %d\n", aluno.matricula);
            printf("Nome: %s\n", aluno.nome);
            printf("Curso: %s\n", aluno.curso);
            printf("Idade: %d\n", aluno.idade);
            break;
        }
    }

    if (!encontrado) {
        printf("Aluno com matrícula %d não encontrado!\n", matricula);
    }

    fclose(arquivo);
}

void listarAlunos() {
    FILE *arquivo = fopen("alunos.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Aluno aluno;
    printf("\n--- Lista de Alunos ---\n");

    while (fread(&aluno, sizeof(Aluno), 1, arquivo)) {
        printf("\nMatrícula: %d\n", aluno.matricula);
        printf("Nome: %s\n", aluno.nome);
        printf("Curso: %s\n", aluno.curso);
        printf("Idade: %d\n", aluno.idade);
    }

    fclose(arquivo);
}
