#include "../include/algoritmos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para gerar matricula automaticamente
void gerarID(char *buffer)
{
    char caracteres[] = "0123456789";
    for (int i = 0; i < MAX_MAT; i++)
    {
        buffer[i] = caracteres[rand() % (sizeof(caracteres) - 1)];
    }

    buffer[MAX_MAT] = '\0';
}

/*busca binaria para encontrar o livro pelo codigo,
retorna o indice do livro no vetor ou -1 se não encontrado*/

int busca_livro(int codigo)
{
    /* ESQ é o inicio do vetor livros
    dir é o final desse vetor -1
    db.num_livros é a quantidade de livros no Banco*/

    int esq = 0, dir = db.num_livros - 1;
    while (esq <= dir)
    {

        // calcula o índice do elemento do meio do intervalo atual
        int meio = (dir + esq) / 2;

        /*Ele compara o codigo do livro no meio do intervalo com o código
        que está sendo buscado*/
        if (db.livros[meio].codigo == codigo)
        {

            // encontrou o livro, retorna o índice
            return meio;

            // se o código do meio for menor que o procurado
        }
        else if (db.livros[meio].codigo < codigo)
        {

            // o livro procurado está na metade “direita” do intervalo
            esq = meio + 1;

            // Se o código do meio for maior:
        }
        else
        {

            // o livro procurado está na metade “esquerda” do intervalo
            dir = meio - 1;
        }
    }
}