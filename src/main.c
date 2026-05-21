#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "../include/Users.h"
#include "../include/interface.h"

int main()
{

    // Matriz de strings para as opções
    char opcoes[5][30] = {"Usuários", "Livros", "empréstimos", "relatórios", "Sair"};

    while (1)
    {

        int posicaoAtual = criarMenu("MENU PRINCIPAL", opcoes, 5);

        gotoxy(0, 2);

        if (posicaoAtual == 0)
        {
            Users();
        }
        else if (posicaoAtual == 1)
        {
            printf("Livros.\n");
        }
        else if (posicaoAtual == 2)
        {
            printf("emprestimos\n");
        }
        else if (posicaoAtual == 3)
        {
            printf("relatorios\n");
        }
        else if (posicaoAtual == 4)
        {
            printf("saindo do programa\n");
            break;
        }
        system("cls");
    }

    return 0;
}
