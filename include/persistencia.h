#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include <stdio.h>
#include <stdlib.h>
#include "persistencia.h"
#include "biblioteca.h"

Usuario *CarregarUsuarios(int *total);
void SalvarUsuarios (Usuario *usuarios, int totalusu);
Emprestimo *CarregarEmprestimos(int *total);
void SalvarEmprestimos(Emprestimo *emprestimos, int totalemp);

Livro *CarregarLivros(int *total);
void SalvarLivros(Livro *livros, int totalLivros);

#endif