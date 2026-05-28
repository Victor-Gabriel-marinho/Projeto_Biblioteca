#include <stdio.h>
#include <biblioteca.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./algoritmos.h"

int validacao_codigo(char codigo[8])
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

void addEmp(){
    
    int matricula_aluno; // variavel local da matricula do aluno na execucao atual
    char codigo[8];      // variavel local de codigo do livro
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
        scanf("%7s", codigo);
        while (1)
        { // While intermediario pra checar se o codigo escrito é válido, ele fica no loop ate que a função validacao seja verdadeira.
            if (validacao_codigo(codigo) == 0)
            {
                printf("Codigo de livro invalido! Digite um codigo válido de livro. \n");
            }
            else
            {
                break;
            }
        }
    }

}

void emp()
{

    
    char opcoes[4][30] = {"Registrar emprestimo", "Registrar devolução", "Listar emprestimos em atraso", "Voltar"};

    while (1)
    {
        // Função para criar interface
        int posicaoAtual = criarMenu("TELA DE USUÁRIOS", opcoes, 6);

        if (posicaoAtual == 0)
        {
            // Função de adicionar usuários
            AddUsers();
        }
        else if (posicaoAtual == 1)
        {
            // Função de listar usuários
            listUsers();
        }
        else if (posicaoAtual == 2)
        {
            // Função de buscar usuarios por nome ou matricula
            BuscarUsuarios();
        }
        else if (posicaoAtual == 3)
        {
            // Função de remover usuario através da matrícula
            RemoverUsuario();
        }
        else if (posicaoAtual == 4)
        {
            // Função de editar usuario através da matrícula
            EditarUsuario();
        }
        else if (posicaoAtual == 5)
        {
            system("cls");
            break;
        }
        system("cls");
    }
    return 0;
}