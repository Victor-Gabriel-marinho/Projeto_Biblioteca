#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include "../include/Users.h"
#include "../include/interface.h"
#include "../include/biblioteca.h"
#include "../include/emprestimos.h"
#include "../include/relatorios.h"
#include "../include/livros.h"
#include "../include/persistencia.h"
#include "../include/emprestimos.h"

Banco db;
Usuario *usuarios = NULL;
int totalUsuarios = 0;
int totalEmprestimos = 0;
Emprestimo *emprestimos = NULL;
int totalLivros = 0;
Livro *livros = NULL;

int main()
{
    usuarios = CarregarUsuarios(&totalUsuarios);
    emprestimos = CarregarEmprestimos(&totalEmprestimos);
    livros = CarregarLivros(&totalLivros);
    // Definindo as opções do Menu principal
    char opcoes[6][30] = {"Gerenciar Usuários", "Gerenciar Livros", "Realizar Empréstimos", "Registrar devolução", "Relatórios", "Sair"};

    while (1)
    {

        int posicaoAtual = criarMenu("MENU PRINCIPAL", opcoes, 6);

        // função para dar espaçamento
        gotoxy(0, 2);

        if (posicaoAtual == 0)
        {
            Users();
        }
        else if (posicaoAtual == 1)
        {
            Livros();
        }
        else if (posicaoAtual == 2)
        {
            emp();
        }
        else if (posicaoAtual == 3)
        {
            regDev();
        }
        else if (posicaoAtual == 4)
        {
            Relatorios();
        }
        else if (posicaoAtual == 5)
        {
            printf("saindo do programa\n");
            break;
        }
        system("cls");
    }

    return 0;
}
