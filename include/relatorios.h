#ifndef RELATORIOS_H
#define RELATORIOS_H

#include "biblioteca.h"

// Tela principal do módulo de relatórios (chamada pelo menu principal)
void Relatorios();

// Relatórios individuais
void relatorioLivrosMaisEmprestados();
static int diasAtraso(const char *previsto, const char *hoje);
void relatorioEmprestimosAtraso();
void relatorioAcervoDisponivel();
void relatorioHistoricoUsuario();

#endif