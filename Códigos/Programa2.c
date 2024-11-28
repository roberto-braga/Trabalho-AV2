#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    char cargo[30];
    int salario;
} Funcionario;

void cadastrarFuncionario();
void alterarFuncionario();
void excluirFuncionario();
void consultarFuncionario();
void listarFuncionarios();

int main() {
    int opcao;

    do {
        printf("\n--- Sistema de Cadastro de Funcionários ---\n");
        printf("1. Cadastrar novo funcionário\n");
        printf("2. Alterar dados de um funcionário\n");
        printf("3. Excluir funcionário pelo ID\n");
        printf("4. Consultar informações de um funcionário\n");
        printf("5. Listar todos os funcionários cadastrados\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarFuncionario(); break;
            case 2: alterarFuncionario(); break;
            case 3: excluirFuncionario(); break;
            case 4: consultarFuncionario(); break;
            case 5: listarFuncionarios(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

void cadastrarFuncionario() {
    FILE *arquivo = fopen("funcionarios.dat", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Funcionario funcionario;
    printf("Digite o ID do funcionário: ");
    scanf("%d", &funcionario.id);
    printf("Digite o nome do funcionário: ");
    getchar(); 
    fgets(funcionario.nome, sizeof(funcionario.nome), stdin);
    funcionario.nome[strcspn(funcionario.nome, "\n")] = '\0';
    printf("Digite o cargo do funcionário: ");
    fgets(funcionario.cargo, sizeof(funcionario.cargo), stdin);
    funcionario.cargo[strcspn(funcionario.cargo, "\n")] = '\0';
    printf("Digite o salário do funcionário (em reais): ");
    scanf("%d", &funcionario.salario);

    fwrite(&funcionario, sizeof(Funcionario), 1, arquivo);
    fclose(arquivo);
    printf("Funcionário cadastrado com sucesso!\n");
}

void alterarFuncionario() {
    FILE *arquivo = fopen("funcionarios.dat", "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int id, encontrado = 0;
    Funcionario funcionario;

    printf("Digite o ID do funcionário a ser alterado: ");
    scanf("%d", &id);

    while (fread(&funcionario, sizeof(Funcionario), 1, arquivo)) {
        if (funcionario.id == id) {
            encontrado = 1;
            printf("Digite o novo cargo do funcionário: ");
            getchar();  
            fgets(funcionario.cargo, sizeof(funcionario.cargo), stdin);
            funcionario.cargo[strcspn(funcionario.cargo, "\n")] = '\0';
            printf("Digite o novo salário do funcionário (em reais): ");
            scanf("%d", &funcionario.salario);

            fseek(arquivo, -sizeof(Funcionario), SEEK_CUR);
            fwrite(&funcionario, sizeof(Funcionario), 1, arquivo);
            printf("Dados do funcionário atualizados com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Funcionário com ID %d não encontrado!\n", id);
    }

    fclose(arquivo);
}

void excluirFuncionario() {
    FILE *arquivo = fopen("funcionarios.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int id, encontrado = 0;
    Funcionario funcionario;

    printf("Digite o ID do funcionário a ser excluído: ");
    scanf("%d", &id);

    while (fread(&funcionario, sizeof(Funcionario), 1, arquivo)) {
        if (funcionario.id == id) {
            encontrado = 1;
            printf("Funcionário excluído com sucesso!\n");
        } else {
            fwrite(&funcionario, sizeof(Funcionario), 1, temp);
        }
    }

    if (!encontrado) {
        printf("Funcionário com ID %d não encontrado!\n", id);
    }

    fclose(arquivo);
    fclose(temp);

    remove("funcionarios.dat");
    rename("temp.dat", "funcionarios.dat");
}

void consultarFuncionario() {
    FILE *arquivo = fopen("funcionarios.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int id, encontrado = 0;
    Funcionario funcionario;

    printf("Digite o ID do funcionário: ");
    scanf("%d", &id);

    while (fread(&funcionario, sizeof(Funcionario), 1, arquivo)) {
        if (funcionario.id == id) {
            encontrado = 1;
            printf("\nID: %d\n", funcionario.id);
            printf("Nome: %s\n", funcionario.nome);
            printf("Cargo: %s\n", funcionario.cargo);
            printf("Salário: R$%d\n", funcionario.salario);
            break;
        }
    }

    if (!encontrado) {
        printf("Funcionário com ID %d não encontrado!\n", id);
    }

    fclose(arquivo);
}

void listarFuncionarios() {
    FILE *arquivo = fopen("funcionarios.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Funcionario funcionario;
    printf("\n--- Lista de Funcionários ---\n");

    while (fread(&funcionario, sizeof(Funcionario), 1, arquivo)) {
        printf("\nID: %d\n", funcionario.id);
        printf("Nome: %s\n", funcionario.nome);
        printf("Cargo: %s\n", funcionario.cargo);
        printf("Salário: R$%d\n", funcionario.salario);
    }

    fclose(arquivo);
}
