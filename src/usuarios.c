#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../include/interface.h"
#include "../include/Users.h"
#include "../include/biblioteca.h"
#include "../include/algoritmos.h"
#include "../include/persistencia.h"

void AddUsers()
{
    srand(time(NULL));
    char tecla;
    Usuario novoAluno;

    // Função de gerar matricula automaticamente
    gerarID(novoAluno.matricula);
    novoAluno.qtd_emprestimos_ativos = 0;

    printf("=== ADICIONAR USUÁRIO ===\n\n");
    mostrarCursor();

    do
    {

        printf("Digite o nome do usuário: ");
        fgets(novoAluno.nome, MAX_STRING, stdin);
        novoAluno.nome[strcspn(novoAluno.nome, "\n")] = '\0'; // Impedindo que o fgets pegue o Enter que o usuários digitar
        if (strlen(novoAluno.nome) == 0 || strcmp(novoAluno.nome, " ") == 0)
        {
            printf("Nome inválido! Tente novamente.\n");
        }

    } while (strlen(novoAluno.nome) == 0 || strcmp(novoAluno.nome, " ") == 0);

    do
    {
        printf("Digite o curso do usuário: ");
        fgets(novoAluno.curso, MAX_STRING, stdin);
        novoAluno.curso[strcspn(novoAluno.curso, "\n")] = '\0';

        if (strlen(novoAluno.curso) == 0 || strcmp(novoAluno.curso, " ") == 0)
            printf("Curso inválido! Tente novamente.\n");

    } while (strlen(novoAluno.curso) == 0 || strcmp(novoAluno.curso, " ") == 0);

    while (1)
    {
        ocultarCursor();
        printf("=== Usuário ===\n");
        printf("Matrícula : %s\n", novoAluno.matricula);
        printf("Nome      : %s\n", novoAluno.nome);
        printf("Curso     : %s\n", novoAluno.curso);
        printf("Empréstimos ativos: %d\n\n", novoAluno.qtd_emprestimos_ativos);
        printf("Pressione Enter para confirmar ou BackSpace para voltar\n");
        tecla = _getch();

        if (tecla == 8)
        {
            system("cls");
            break;
        }
        else if (tecla == 13)
        {

            Usuario *temp = realloc(usuarios, (totalUsuarios + 1) * sizeof(Usuario));
            if (temp == NULL)
            {
                printf("Erro: falha ao alocar memória!\n");
                free(usuarios);
                return;
            }

            usuarios = temp;
            usuarios[totalUsuarios] = novoAluno;
            totalUsuarios++;

            SalvarUsuarios(usuarios, totalUsuarios);

            printf("\nUsuário salvo com sucesso!\nPressione qualquer tecla para sair\n");
            _getch();
            system("cls");
            break;
        }
    }
}

void listUsers()
{

    printf("\t\t\t=== LISTA DE USUÁRIOS ===\n\n");

    // Percorrendo o vetor de usuários
    for (int i = 0; i < totalUsuarios; i += 3)
    {
        int colunas = totalUsuarios - i;
        if (colunas > 3)
            colunas = 3;

        for (int c = 0; c < colunas; c++)
            printf("=== Usuário %d ===\t\t", i + c + 1);
        printf("\n");

        for (int c = 0; c < colunas; c++)
            printf("Matrícula : %-20s", usuarios[i + c].matricula);
        printf("\n");

        for (int c = 0; c < colunas; c++)
            printf("Nome      : %-20s", usuarios[i + c].nome);
        printf("\n");

        for (int c = 0; c < colunas; c++)
            printf("Curso     : %-20s", usuarios[i + c].curso);
        printf("\n");

        for (int c = 0; c < colunas; c++)
            printf("Empréstimos ativos: %-5d\t", usuarios[i + c].qtd_emprestimos_ativos);
        printf("\n\n");
    }
    system("Pause");
}

void RemoverUsuario()
{
    char mat[8];
    char tecla;
    int encontrado = 0;
    Usuario usuarioEncontrado;
    Usuario *NovosUsuarios;
    int i = 0, j = 0;

    mostrarCursor();

    printf("=== REMOVER USUÁRIO ===\n\n");

    printf("Digite a matrícula do usuário que deseja remover: ");
    scanf("%s", mat);

    encontrado = BuscarUsuarioPorMat(&usuarioEncontrado, mat);
    if (encontrado == 0) {
        
        printf("Erro ao buscar usuario.\n");
        system("pause");
        return;
    }


    printf("\nUsuário encontrado:\n");
    printf("Matrícula: %s\n", usuarioEncontrado.matricula);
    printf("Nome: %s\n", usuarioEncontrado.nome);

    printf("\nEsse é o usuário que você quer excluir?\n");
    printf(" Enter     - Sim\n");
    printf(" Backspace - Não\n");

    tecla = _getch();
    if (tecla == 8)
    {
        system("cls");
        return;
    }
    else if (tecla != 13)
    {
        return;
    }

    Usuario *temp = realloc(usuarios, (totalUsuarios - 1) * sizeof(Usuario));

    if (temp == NULL)
    {
        printf("Erro: falha ao alocar memória!\n");
        free(NovosUsuarios);
        return;
    }

    NovosUsuarios = temp;

    for (i = 0; i < totalUsuarios; i++)
    {
        if (strcmp(usuarios[i].matricula, usuarioEncontrado.matricula) != 0)
        {
            NovosUsuarios[j] = usuarios[i];
            j++;
        }
    }
    totalUsuarios--;

    SalvarUsuarios(NovosUsuarios, totalUsuarios);
    usuarios = NovosUsuarios;

    printf("\nUsuário removido com sucesso!\n");
    _getch();
    system("cls");
}

void BuscarUsuarios()
{
    char opcoes[3][30] = {"Buscar por nome", "Buscar por matricula", "Voltar"};

    while (1)
    {
        int posicaoAtual = criarMenu("TELA DE BUSCA", opcoes, 3);

        // Busca por nome
        if (posicaoAtual == 0)
        {
            mostrarCursor();
            char nome[8];
            int result;
            Usuario usuarioEncontrado;

            printf("Digite o nome do usuário: ");
            fgets(nome, 8, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            result = BuscarUsuarioPorNome(&usuarioEncontrado, nome);
            if (result == 0)
            {
                printf("Erro ao buscar usuario.\n");
                system("Pause");
                return;
            }

            printf("=== Usuário ===\n");
            printf("Matrícula : %s\n", usuarioEncontrado.matricula);
            printf("Nome      : %s\n", usuarioEncontrado.nome);
            printf("Curso     : %s\n", usuarioEncontrado.curso);
            printf("Empréstimos ativos: %d\n\n", usuarioEncontrado.qtd_emprestimos_ativos);

            printf("Digite qualquer tecla para voltar\n");
            _getch();
        }

        // Busca por matricula
        else if (posicaoAtual == 1)
        {
            mostrarCursor();

            Usuario usuarioEncontrado;
            char matricula[8];
            int result = 0;

            printf("Digite o nome do usuário: ");
            fgets(matricula, 8, stdin);
            matricula[strcspn(matricula, "\n")] = '\0';

            result = BuscarUsuarioPorMat(&usuarioEncontrado, matricula);
            if (result == 0)
            {
                printf("Erro ao buscar usuario.\n");
                system("pause");
                return;
            }

            printf("=== Usuário ===\n");
            printf("Matrícula : %s\n", usuarioEncontrado.matricula);
            printf("Nome      : %s\n", usuarioEncontrado.nome);
            printf("Curso     : %s\n", usuarioEncontrado.curso);
            printf("Empréstimos ativos: %d\n\n", usuarioEncontrado.qtd_emprestimos_ativos);
            printf("Digite qualquer tecla para voltar\n");
            _getch();
        }
        else if (posicaoAtual == 2)
        {
            system("cls");
            break;
        }
    }
}

void EditarUsuario()
{
    char mat[8];
    char tecla;
    int encontrado = 0;
    Usuario usuarioEncontrado;
    Usuario temp;
    Usuario usuarioEditado;
    mostrarCursor();

    printf("=== EDITAR USUÁRIO ===\n\n");

    printf("Digite a matrícula do usuário que deseja editar: ");
    scanf("%s", mat);

    BuscarUsuarioPorMat(&usuarioEncontrado, mat);
    if (BuscarUsuarioPorMat(&usuarioEncontrado, mat) == 0)
    {
        printf("Erro ao buscar usuario.\n");
        system("pause");
        return;
    }

    ocultarCursor();
    printf("\nUsuário encontrado:\n");
    printf("Matrícula: %s\n", usuarioEncontrado.matricula);
    printf("Nome: %s\n", usuarioEncontrado.nome);
    printf("Curso: %s\n", usuarioEncontrado.curso);

    printf("\nEsse é o usuário que você quer Editar?\n");
    printf(" Enter     - Sim\n");
    printf(" Backspace - Não\n");

    tecla = _getch();
    if (tecla == 8)
    {
        system("cls");
        return;
    }
    else if (tecla != 13)
    {
        return;
    }
    getchar();
    mostrarCursor();
    printf("\nDigite o novo nome\n");
    printf("ou pressione Enter para manter o anterior\n");
    fgets(usuarioEditado.nome, MAX_STRING, stdin);
    usuarioEditado.nome[strcspn(usuarioEditado.nome, "\n")] = '\0';

    printf("\nDigite o novo curso\n");
    printf("ou pressione Enter para manter o anterior\n");
    fgets(usuarioEditado.curso, MAX_STRING, stdin);
    usuarioEditado.curso[strcspn(usuarioEditado.curso, "\n")] = '\0';

    if (strcmp(usuarioEditado.nome, "") == 0 || strcmp(usuarioEditado.nome, " ") == 0)
    {
        strcpy(usuarioEditado.nome, usuarioEncontrado.nome);
    }
    if (strcmp(usuarioEditado.curso, "") == 0 || strcmp(usuarioEditado.curso, " ") == 0)
    {
        strcpy(usuarioEditado.curso, usuarioEncontrado.curso);
    }

    strcpy(usuarioEditado.matricula, usuarioEncontrado.matricula);
    usuarioEditado.qtd_emprestimos_ativos = usuarioEncontrado.qtd_emprestimos_ativos;

    for (int i = 0; i < totalUsuarios; i++)
    {
        if (strcmp(usuarios[i].matricula, usuarioEncontrado.matricula) == 0)
        {
            usuarios[i] = usuarioEditado;
        }
    }

    SalvarUsuarios(usuarios, totalUsuarios);

    printf("\nUsuário editado com sucesso!\n");
    _getch();
    system("cls");
}

void Users()
{

    // Criando opções da tela de gerenciamento de usuários
    char opcoes[6][30] = {"Adicionar Usuário", "Listar Usuários", "Buscar usuário", "Remover Usuário", "Editar usuário", "Voltar"};

    while (1)
    {
        // Função para criar interface
        int posicaoAtual = criarMenu("TELA DE USUÁRIOS", opcoes, 6);

        if (posicaoAtual == 0)
        {
            // Função de adicionar usuários
            AddUsers();
        }
        else if (posicaoAtual == 1)
        {
            // Função de listar usuários
            listUsers();
        }
        else if (posicaoAtual == 2)
        {
            // Função de buscar usuarios por nome ou matricula
            BuscarUsuarios();
        }
        else if (posicaoAtual == 3)
        {
            // Função de remover usuario através da matrícula
            RemoverUsuario();
        }
        else if (posicaoAtual == 4)
        {
            // Função de editar usuario através da matrícula
            EditarUsuario();
        }
        else if (posicaoAtual == 5)
        {
            system("cls");
            break;
        }
        system("cls");
    }
}