#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LIVROS 500
#define MAX_USUARIOS 500
#define MAX_EMPRESTIMOS 20000
#define MAX_STRING 100
#define MAX_EMPRESTIMOS_USUARIO 3
#define PRAZO_DEVOLUCAO 14

// struct dos livros
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

// struct dos usuarios
typedef struct
{
    int matricula;
    char nome[MAX_STRING];
    char curso[MAX_STRING];
    int qtd_emprestimos_ativos;
} Usuario;

// struct dos emprestimos
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

/*Essa struct é a base de dados, onde tem os vetores de livros, usuarios e emprestimos,
alem de variaveis pra contar quantos tem de cada um*/
typedef struct
{
    Livro livros[MAX_LIVROS];

    // Variável para contar quantos livros estão cadastrados
    int num_livros;

    Usuario usuarios[MAX_USUARIOS];

    // Variável para contar quantos usuários estão cadastrados
    int num_usuarios;

    Emprestimo emprestimos[MAX_EMPRESTIMOS];

    // Variável para contar quantos empréstimos estão registrados
    int num_emprestimos;
} Banco;

// Variável global do banco de dados
extern Banco db;

#endif