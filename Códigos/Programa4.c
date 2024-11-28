#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char modelo[50];
    char placa[10];
    int ano;
} Veiculo;

void adicionarVeiculo();
void alterarVeiculo();
void excluirVeiculo();
void consultarVeiculoPorPlaca();
void listarVeiculos();

int main() {
    int opcao;

    do {
        printf("\n--- Sistema de Registro de Veículos ---\n");
        printf("1. Adicionar novo veículo\n");
        printf("2. Alterar dados de um veículo\n");
        printf("3. Excluir veículo pelo ID\n");
        printf("4. Consultar informações de um veículo pela placa\n");
        printf("5. Listar todos os veículos cadastrados\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionarVeiculo(); break;
            case 2: alterarVeiculo(); break;
            case 3: excluirVeiculo(); break;
            case 4: consultarVeiculoPorPlaca(); break;
            case 5: listarVeiculos(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

void adicionarVeiculo() {
    FILE *arquivo = fopen("veiculos.dat", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Veiculo veiculo;
    printf("Digite o ID do veículo: ");
    scanf("%d", &veiculo.id);
    printf("Digite o modelo do veículo: ");
    getchar(); 
    fgets(veiculo.modelo, sizeof(veiculo.modelo), stdin);
    veiculo.modelo[strcspn(veiculo.modelo, "\n")] = '\0';
    printf("Digite a placa do veículo: ");
    fgets(veiculo.placa, sizeof(veiculo.placa), stdin);
    veiculo.placa[strcspn(veiculo.placa, "\n")] = '\0';
    printf("Digite o ano de fabricação do veículo: ");
    scanf("%d", &veiculo.ano);

    fwrite(&veiculo, sizeof(Veiculo), 1, arquivo);
    fclose(arquivo);
    printf("Veículo adicionado com sucesso!\n");
}

void alterarVeiculo() {
    FILE *arquivo = fopen("veiculos.dat", "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int id, encontrado = 0;
    Veiculo veiculo;

    printf("Digite o ID do veículo a ser alterado: ");
    scanf("%d", &id);

    while (fread(&veiculo, sizeof(Veiculo), 1, arquivo)) {
        if (veiculo.id == id) {
            encontrado = 1;
            printf("Digite o novo modelo do veículo: ");
            getchar();  
            fgets(veiculo.modelo, sizeof(veiculo.modelo), stdin);
            veiculo.modelo[strcspn(veiculo.modelo, "\n")] = '\0';
            printf("Digite a nova placa do veículo: ");
            fgets(veiculo.placa, sizeof(veiculo.placa), stdin);
            veiculo.placa[strcspn(veiculo.placa, "\n")] = '\0';
            printf("Digite o novo ano de fabricação do veículo: ");
            scanf("%d", &veiculo.ano);

            fseek(arquivo, -sizeof(Veiculo), SEEK_CUR);
            fwrite(&veiculo, sizeof(Veiculo), 1, arquivo);
            printf("Dados do veículo atualizados com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Veículo com ID %d não encontrado!\n", id);
    }

    fclose(arquivo);
}

void excluirVeiculo() {
    FILE *arquivo = fopen("veiculos.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int id, encontrado = 0;
    Veiculo veiculo;

    printf("Digite o ID do veículo a ser excluído: ");
    scanf("%d", &id);

    while (fread(&veiculo, sizeof(Veiculo), 1, arquivo)) {
        if (veiculo.id == id) {
            encontrado = 1;
            printf("Veículo excluído com sucesso!\n");
        } else {
            fwrite(&veiculo, sizeof(Veiculo), 1, temp);
        }
    }

    if (!encontrado) {
        printf("Veículo com ID %d não encontrado!\n", id);
    }

    fclose(arquivo);
    fclose(temp);

    remove("veiculos.dat");
    rename("temp.dat", "veiculos.dat");
}

void consultarVeiculoPorPlaca() {
    FILE *arquivo = fopen("veiculos.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char placa[10];
    int encontrado = 0;
    Veiculo veiculo;

    printf("Digite a placa do veículo: ");
    getchar(); 
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0';

    while (fread(&veiculo, sizeof(Veiculo), 1, arquivo)) {
        if (strcmp(veiculo.placa, placa) == 0) {
            encontrado = 1;
            printf("\nID: %d\n", veiculo.id);
            printf("Modelo: %s\n", veiculo.modelo);
            printf("Placa: %s\n", veiculo.placa);
            printf("Ano de Fabricação: %d\n", veiculo.ano);
            break;
        }
    }

    if (!encontrado) {
        printf("Veículo com placa %s não encontrado!\n", placa);
    }

    fclose(arquivo);
}

void listarVeiculos() {
    FILE *arquivo = fopen("veiculos.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Veiculo veiculo;
    printf("\n--- Lista de Veículos ---\n");

    while (fread(&veiculo, sizeof(Veiculo), 1, arquivo)) {
        printf("\nID: %d\n", veiculo.id);
        printf("Modelo: %s\n", veiculo.modelo);
        printf("Placa: %s\n", veiculo.placa);
        printf("Ano de Fabricação: %d\n", veiculo.ano);
    }

    fclose(arquivo);
}
