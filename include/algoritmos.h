#ifndef ALGORITMOS_H
#define ALGORITMOS_H
#include <stdlib.h>
#include "../include/biblioteca.h"

#define MAX_MAT 7

// Definindo funções de utilidades
void gerarID(char *buffer);

/*criando uma void pra fazer as buscas dos livros
ultilizando a busca binaria, sendo um metodo mais pratico*/
void busca_livro(int codigo);

// Função para ordenar os livros por título usando merge sort
void merge_sort_livros(Livro *saida, int n);

// Função para ordenar os empréstimos por data de retirada usando merge sort
void merge_sort_emprestimos_data(Emprestimo *vet, int n);

#endif