#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include "../include/interface.h"

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ocultarCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void mostrarCursor () {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// Função para criar as interfaces de escolha
int criarMenu(char *titulo, char opcoes[][30], int totalOpcoes)
{
    // Configura o console para aceitar acentos (UTF-8)
    SetConsoleOutputCP(65001);

    ocultarCursor();
    system("cls");

    int posicaoAtual = 0;
    char tecla;

    while (1)
    {
        // Desenha o menu
        gotoxy(0, 2);
        printf("=== %s ===\n\n", titulo);

        for (int i = 0; i < totalOpcoes; i++)
        {
            if (i == posicaoAtual)
            {
                // Destaca a opção selecionada
                printf("-> [ %s ]\n", opcoes[i]);
            }
            else
            {
                printf("     %s     \n", opcoes[i]);
            }
        }

        // Lê a tecla pressionada
        tecla = _getch();

        // Detecta setas do teclado no Windows
        if (tecla == -32 || tecla == 0)
        {
            tecla = _getch();

            if (tecla == 72)
            { // Seta para CIMA
                posicaoAtual--;
                if (posicaoAtual < 0)
                    posicaoAtual = totalOpcoes - 1;
            }
            else if (tecla == 80)
            { // Seta para BAIXO
                posicaoAtual++;
                if (posicaoAtual >= totalOpcoes)
                    posicaoAtual = 0;
            }
        }
        // Se pressionar ENTER (ASCII 13)
        else if (tecla == 13)
        {
            system("cls"); // Limpa a tela
            return posicaoAtual;
        }
    }
}