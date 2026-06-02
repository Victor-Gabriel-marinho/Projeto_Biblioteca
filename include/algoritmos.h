#ifndef ALGORITMOS_H
#define ALGORITMOS_H
#include <stdlib.h>
#include "../include/biblioteca.h"

#define MAX_MAT 7

// Definindo funções de utilidades
void gerarID(char *buffer);

/*criando uma void pra fazer as buscas dos livros
ultilizando a busca binaria, sendo um metodo mais pratico*/
int busca_livro(char codigo[8]);

// Funções de busca de usuários
int BuscarUsuarioPorNome(Usuario *usuarioEncontrado,char nome[8]);
int BuscarUsuarioPorMat(Usuario *usuarioEncontrado,char matricula[8]);

// Função para ordenar os livros por título usando merge sort
void merge_sort_livros(Livro *saida, int n);

// Função para ordenar os empréstimos por data de retirada usando merge sort
void merge_sort_emprestimos_data(Emprestimo *vet, int n);

#endif