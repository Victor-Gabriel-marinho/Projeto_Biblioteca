#include <stdio.h>
#include <biblioteca.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./algoritmos.h"

int validacao_codigo(int codigo_livro)
{ // função pra checar se o codigo enviado é válido, retorna 0 (false, não é valido) ou retorna 1(true, é valido)
}
int validacao_matricula(int matricula_aluno)
{ // função pra checar se a matricula enviada é válida, retorna 0 (false, não é valido) ou retorna 1(true, é valido)
}
int validacao_quantidade(int qtd_disponivel)
{ // função pra     checar se tem quantidade disponivel para emprestmo, retorna 0 (false, não tem) ou retorna 1(true, tem)
}
int validacao_usuario(int qtd_usuario)
{ // função pra     checar se o usuario pode pegar mais um emprestimo, retorna 0 (false, não pode) ou retorna 1(true, pode)
}

int emp()
{

    int matricula_aluno; // variavel local da matricula do aluno na execucao atual
    int codigo_livro;    // variavel local de codigo do livro
    int qtd_disponivel;
    int qtd_usuario;

    while (1)
    {

        printf("Qual a matricula do usuario? ");
        scanf("%d ", &matricula_aluno);
        if (validacao_matricula(matricula_aluno) == 0)
        { // Válida se a matricula escrita é valida por meio da função, se for valida ele só continua, se for invalida ele diz que é invalida e volta pro começo do while principal.
            printf("Matricula invalida! Digite uma matricula valida. \n");
            continue;
        }
        printf("Qual o codigo do livro? ");
        scanf("%d", &codigo_livro);
        while (1)
        { // While intermediario pra checar se o codigo escrito é válido, ele fica no loop ate que a função validacao seja verdadeira.
            if (validacao_codigo(codigo_livro) == 0)
            {
                printf("Codigo de livro invalido! Digite um codigo válido de livro. \n");
            }
            else
            {
                break;
            }
        }
    }
    return 0;
}