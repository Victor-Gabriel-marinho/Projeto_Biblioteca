#ifndef ALGORITMOS_H
#define ALGORITMOS_H
#include <stdlib.h>
#include "../include/biblioteca.h"

#define MAX_MAT 7

// Definindo funções de utilidades
void gerarID(char *buffer);

/*criando uma void pra fazer as buscas dos livros
ultilizando a busca binaria, sendo um metodo mais pratico*/
int comp_data(char data1[11], char data2[11]);
void pegar_data_hoje(char data[11]);
void ler_data(char data[]);
int busca_livroCodigo(Livro *livroEncontrado, char codigo[8]);
int BuscarLivroPorTitulo(Livro *livroEncontrado, char titulo[MAX_STRING]);
// Funções de busca de usuários
int BuscarUsuarioPorNome(Usuario *usuarioEncontrado, char nome[8]);
int BuscarUsuarioPorMat(Usuario *usuarioEncontrado, char matricula[8]);
int PegarIndiceUsuario(char matricula[8]);
int PegarIndiceLivro(char codigo[8]);
void somar_14_dias(char data[11]);
// Função para ordenar os livros por título usando merge sort
void merge_sort_livros(Livro *saida, int n);

// Função para ordenar os empréstimos por data de retirada usando merge sort
void merge_sort_emprestimos_data(Emprestimo *vet, int n);
void exibir_livros_mais_emprestados(void);

#endif