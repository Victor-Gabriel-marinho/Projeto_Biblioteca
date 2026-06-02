#ifndef USERS_H
#define USERS_H
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "interface.h"
#include "biblioteca.h"

extern Usuario *usuarios;
extern int totalUsuarios;

// Definindo funções de usuários
void Users();
void AddUsers();
void RemoverUsuario();
void BuscarUsuarios();
void EditarUsuario();
void listUsers();

#endif