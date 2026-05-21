#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "../include/interface.h"
#include "../include/Users.h"

void Users()
{

    char opcoes[5][30] = {"Adicionar Usuário", "Remover Usuário", "Listar Usuários", "Editar usuário", "Voltar"};
 
    while (1)
    {
        int posicaoAtual = criarMenu("TELA DE USUÁRIOS",opcoes, 5);

            if (posicaoAtual == 0)
            {
                printf("Add usuários");
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