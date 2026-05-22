#ifndef INTERFACE_H
#define INTERFACE_H
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// Definindo funções para gerenciar interface
void gotoxy(int x, int y);

void ocultarCursor();

void mostrarCursor();

int criarMenu(char *titulo, char opcoes[][30], int totalOpcoes);

#endif