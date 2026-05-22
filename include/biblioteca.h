#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./algoritmos.h"

#define MAX_LIVROS 500
#define MAX_USUARIOS 500
#define MAX_EMPRESTIMOS 2000
#define MAX_STRING 100
#define MAX_EMPRESTIMOS_USUARIO 3
#define PRAZO_DEVOLUCAO 14


typedef struct
{
    int codigo;
    char titulo[MAX_STRING];
    char autor[MAX_STRING];
    int ano;
    char genero[MAX_STRING];
    int qtd_total;
    int qtd_disponivel;
    int total_emprestimos;
} Livro;

typedef struct
{
    char matricula[MAX_MAT];
    char nome[MAX_STRING];
    char curso[MAX_STRING];
    int qtd_emprestimos_ativos;
} Usuario;

typedef struct
{
    int id;
    int matricula_usuario;
    int codigo_livro;
    char data_retirada[11];
    char data_prevista[11];
    char data_devolucao[11];
    int devolvido;
} Emprestimo;

#endif