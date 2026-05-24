#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/interface.h"
#include "../include/Users.h"
#include "../include/biblioteca.h"
#include "../include/algoritmos.h"

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

    printf("Digite o nome do usuário: ");
    fgets(novoAluno.nome, MAX_STRING, stdin);
    // Impedindo que o fgets pegue o Enter que o usuários digitar
    novoAluno.nome[strcspn(novoAluno.nome, "\n")] = '\0';

    printf("Digite o curso do usuário: ");
    fgets(novoAluno.curso, MAX_STRING, stdin);
    novoAluno.curso[strcspn(novoAluno.curso, "\n")] = '\0';

    while (1)
    {
        ocultarCursor();
        printf("=== Usuário ===\n");
        printf("Matrícula : %s\n", novoAluno.matricula);
        printf("Nome      : %s\n", novoAluno.nome);
        printf("Curso     : %s\n", novoAluno.curso);
        printf("Empréstimos ativos: %d\n\n", novoAluno.qtd_emprestimos_ativos);
        printf("Pressione Enter para confirmar ou BackSpace para voltar");
        tecla = _getch();

        if (tecla == 8)
        {
            system("cls");
            break;
        }
        else if (tecla == 13)
        {
            FILE *usuarios = fopen("data\\usuarios.dat", "ab");

            if (usuarios == NULL)
            {
                printf("Erro ao abrir o arquivo");
                _getch();
                return;
            }
            // Inserindo novo usuário no arquivo
            fwrite(&novoAluno, sizeof(Usuario), 1, usuarios);
            fclose(usuarios);
            printf("\nUsuário salvo com sucesso!\nPressione qualquer tecla para sair\n");
            _getch();
            system("cls");
            break;
        }
    }
}

void listUsers()
{
    FILE *f = fopen("data\\usuarios.dat", "rb");

    if (f == NULL)
    {
        printf("Erro ao abrir o arquivo");
        system("Pause");
        return;
    }

    Usuario u;
    int i = 1;

    // Percorrendo o arquivo de usuários
    while (fread(&u, sizeof(Usuario), 1, f) == 1)
    {
        printf("=== Usuário %d ===\n", i++);
        printf("Matrícula : %s\n", u.matricula);
        printf("Nome      : %s\n", u.nome);
        printf("Curso     : %s\n", u.curso);
        printf("Empréstimos ativos: %d\n\n", u.qtd_emprestimos_ativos);
    }
    system("Pause");
    fclose(f);
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
            char nome[100];
            printf("Digite o nome do usuário: ");
            fgets(nome, 100, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            FILE *f = fopen("data\\usuarios.dat", "rb");
            if (f == NULL)
            {
                printf("Erro ao abrir o arquivo\n");
                _getch();
                break;
            }

            Usuario u;
            int encontrado = 0;
            while (fread(&u, sizeof(Usuario), 1, f) == 1)
            {
                if (strcmp(nome, u.nome) == 0)
                {
                    printf("=== Usuário ===\n");
                    printf("Matrícula : %s\n", u.matricula);
                    printf("Nome      : %s\n", u.nome);
                    printf("Curso     : %s\n", u.curso);
                    printf("Empréstimos ativos: %d\n\n", u.qtd_emprestimos_ativos);
                    encontrado = 1;
                }
                if (encontrado == 1)
                {
                    printf("Digite qualquer tecla para voltar\n");
                    _getch();
                    break;
                }
            }
            fclose(f);
            if (encontrado != 1)
                printf("O usuário %s não foi encontrado\n", nome);
        }
        else if (posicaoAtual == 1)
        {
            // Busca por matricula
             mostrarCursor();
            char matricula[100];
            printf("Digite o nome do usuário: ");
            fgets(matricula, 100, stdin);
            matricula[strcspn(matricula, "\n")] = '\0';

            FILE *f = fopen("data\\usuarios.dat", "rb");
            if (f == NULL)
            {
                printf("Erro ao abrir o arquivo\n");
                _getch();
                break;
            }

            Usuario u;
            int encontrado = 0;
            while (fread(&u, sizeof(Usuario), 1, f) == 1)
            {
                if (strcmp(matricula, u.matricula) == 0)
                {
                    printf("=== Usuário ===\n");
                    printf("Matrícula : %s\n", u.matricula);
                    printf("Nome      : %s\n", u.nome);
                    printf("Curso     : %s\n", u.curso);
                    printf("Empréstimos ativos: %d\n\n", u.qtd_emprestimos_ativos);
                    encontrado = 1;
                }
                if (encontrado == 1)
                {
                    printf("Digite qualquer tecla para voltar\n");
                    _getch();
                    break;
                }
            }
            fclose(f);
            if (encontrado != 1)
                printf("O usuário com a matrícula %s não foi encontrado\n", matricula);
        }
        else if (posicaoAtual == 2)
        {
            system("cls");
            break;
        }
    }
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
            BuscarUsuarios();
        }
        else if (posicaoAtual == 3)
        {
            printf("Remover usuário.\n");
        }
        else if (posicaoAtual == 4)
        {
            printf("Editar usuários \n");
        }
        else if (posicaoAtual == 5)
        {
            system("cls");
            break;
        }
        system("cls");
    }
}
