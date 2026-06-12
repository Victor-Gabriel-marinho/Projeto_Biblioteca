#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "../include/interface.h"
#include "../include/biblioteca.h"

extern Livro *livros;
extern int totalLivros;

void AddLivros();
void EditLivros();
void ListLivros();
void BuscarCodigoDoLivro();
void RemoveLivros();
void BuscarPorNomeDoLivro();
void Livros();
