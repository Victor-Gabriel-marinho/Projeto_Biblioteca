#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "../include/interface.h"
#include "../include/Users.h"

typedef struct
{
    char matricula[20];
    char nome[50];
    char Curso[50];

} UsersDTO;

void Users()
{

    SetConsoleOutputCP(65001);
    ocultarCursor();
    system("cls");

    char options[5][30] = {"Adicionar Usuário", "Remover Usuário", "Listar Usuários", "Editar usuário", "Voltar"};
    int totalOptions = 5;
    int currentPosition = 0;
    char key;

    while (1)
    {
        gotoxy(0, 2);
        printf("=== TELA DE USUÁRIOS ===\n");

        for (int i = 0; i < totalOptions; i++)
        {
            if (i == currentPosition)
            {
                printf("-> [ %s ]\n", options[i]);
            }
            else
            {
                printf("     %s     \n", options[i]);
            }
        }

        key = _getch();

        if (key == -32 || key == 0)
        {
            key = _getch();

            if (key == 72)
            { // Seta para CIMA
                    currentPosition--;
                if (currentPosition < 0)
                    currentPosition = totalOptions - 1;
            }
            else if (key == 80)
            { // Seta para BAIXO
                    currentPosition++;
                if (currentPosition >= totalOptions)
                    currentPosition = 0;
            }
        }

        // Se pressionar ENTER (ASCII 13)
        else if (key == 13)
        {
            system("cls"); // Limpa a tela
            gotoxy(0, 2);

            if (currentPosition == 0)
            {
                printf("Add usuários");
            }
            else if (currentPosition == 1)
            {
                printf("Remover usuário.\n");
            }
            else if (currentPosition == 2)
            {
                printf("Listar usuários \n");
            }
            else if (currentPosition == 3)
            {
                printf("Editar usuários \n");
            }
            else if (currentPosition == 4)
            {
                system("cls");
                break;
            }
            system("cls");
        }
    }
}