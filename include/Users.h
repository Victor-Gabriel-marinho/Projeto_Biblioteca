#ifndef USERS_H
#define USERS_H
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "interface.h"

// Definindo funções de usuários
void Users();
void AddUsers();
void RemoverUsuario();
void BuscarPorNome(char nome[100]);
void BuscaPorMat(char matricula[7]);
void BuscarUsuarios();
void listUsers();

#endif