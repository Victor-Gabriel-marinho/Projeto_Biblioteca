#include <stdio.h>
#include <windows.h>
#include <conio.h> 
#include "../include/Users.h"
#include "../include/interface.h"

int main() {
    // Configura o console para aceitar acentos (UTF-8)
    SetConsoleOutputCP(65001);
    
    ocultarCursor();

    // Matriz de strings para as opções
    char opcoes[5][30] = {"Usuários", "Livros", "empréstimos","relatórios","Sair"};
    int totalOpcoes = 5;
    int posicaoAtual = 0;
    char tecla;

    while (1) {
        // Desenha o menu
        gotoxy(0, 2);
        printf("=== MENU PRINCIPAL ===\n\n");

        for (int i = 0; i < totalOpcoes; i++) {
            if (i == posicaoAtual) {
                // Destaca a opção selecionada
                printf("-> [ %s ]\n", opcoes[i]);
            } else {
                printf("     %s     \n", opcoes[i]);
            }
        }

        // Lê a tecla pressionada
        tecla = _getch();

        // Detecta setas do teclado no Windows
        if (tecla == -32 || tecla == 0) {
            tecla = _getch();
            
            if (tecla == 72) { // Seta para CIMA
                posicaoAtual--;
                if (posicaoAtual < 0) posicaoAtual = totalOpcoes - 1;
            }
            else if (tecla == 80) { // Seta para BAIXO
                posicaoAtual++;
                if (posicaoAtual >= totalOpcoes) posicaoAtual = 0;
            }
        }
        // Se pressionar ENTER (ASCII 13)
        else if (tecla == 13) {
            system("cls"); // Limpa a tela
            gotoxy(0, 2);
            
            if (posicaoAtual == 0) {
                Users();
            } else if (posicaoAtual == 1) {
                printf("Livros.\n");
            } else if (posicaoAtual == 2) {
                printf("emprestimos\n");
            } else if (posicaoAtual == 3) {
                printf("relatorios\n");
            }
             else if (posicaoAtual == 4) {
                printf("saindo do programa\n");
                break;
            }
            system("cls");
        }
    }

    return 0;
}
