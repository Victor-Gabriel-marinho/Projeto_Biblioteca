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
    gerarID(novoAluno.matricula);
    novoAluno.qtd_emprestimos_ativos = 0;

    printf("=== ADICIONAR USUÁRIO ===\n\n");

    mostrarCursor();
    printf("Digite o nome do usuário: ");
    fgets(novoAluno.nome, MAX_STRING, stdin);
    fflush(stdin);
    printf("Digite o curso do usuário: ");
    fgets(novoAluno.curso, MAX_STRING, stdin);
    fflush(stdin);

    while (1)
    {
        ocultarCursor();
        printf("Pressione Enter para confirmar ou BackSpace para voltar");
        tecla = _getch();

        if (tecla == 8)
        {
            system("cls");
            break;
        } else if (tecla == 13) {
            FILE *usuarios = fopen("..\\output\\usuarios.dat", "ab");

            if (usuarios == NULL) {
                printf("Erro ao abrir o arquivo");
                return;
            }
            fwrite(&novoAluno, sizeof(Usuario), 1, usuarios);

            fclose(usuarios);
            printf("");

        }

        system("cls");
    }
}

void Users()
{

    char opcoes[5][30] = {"Adicionar Usuário", "Remover Usuário", "Listar Usuários", "Editar usuário", "Voltar"};

    while (1)
    {
        int posicaoAtual = criarMenu("TELA DE USUÁRIOS", opcoes, 5);

        if (posicaoAtual == 0)
        {
            AddUsers();
        }
        else if (posicaoAtual == 1)
        {
            printf("Remover usuário.\n");
        }
        else if (posicaoAtual == 2)
        {
            printf("Listar usuários \n");
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
