#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "../include/Users.h"
#include "../include/interface.h"

int main()
{

    // Definindo as opções do Menu principal
    char opcoes[6][30] = {"Gerenciar Usuários", "Gerenciar Livros", "Realizar Empréstimos", "Registrar devolução", "Relatórios" , "Sair"};

    while (1)
    {

        int posicaoAtual = criarMenu("MENU PRINCIPAL", opcoes, 6);

        // função para dar espaçamento
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
            printf("Devolução\n");
        }
        else if (posicaoAtual == 3)
        {
            printf("relatorios\n");
        }
        else if (posicaoAtual == 5)
        {
            printf("saindo do programa\n");
            break;
        }
        system("cls");
    }

    return 0;
}
