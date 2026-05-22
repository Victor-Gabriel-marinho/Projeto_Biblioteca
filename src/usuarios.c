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
    int i = 0;

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

void Users()
{
    // Criando opções da tela de gerenciamento de usuários
    char opcoes[5][30] = {"Adicionar Usuário", "Listar Usuários", "Remover Usuário", "Editar usuário", "Voltar"};

    while (1)
    {
        // Função para criar interface
        int posicaoAtual = criarMenu("TELA DE USUÁRIOS", opcoes, 5);

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
            printf("Remover usuário.\n");
        }
        else if (posicaoAtual == 3)
        {
            printf("Editar usuários \n");
        }
        else if (posicaoAtual == 4)
        {
            system("cls");
            break;
        }
        system("cls");
    }
}
