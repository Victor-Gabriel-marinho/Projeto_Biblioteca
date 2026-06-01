#include <stdio.h>
#include "../include/biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/algoritmos.h"
#include "../include/interface.h"

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


void listEmp_user(int matricula){

}

void regisEmp(int matricula_aluno, char codigo[8]){

}

void regDev(){ // função pra registrar devoluções 
    int qtd_emprestimo;
    int matricula_aluno;
    while(1){ // loop central da função 
        printf("Qual a matricula do usuario que voce deseja registrar a devolucao? Digite 0 pra voltar");

        scanf("%d", matricula_aluno);
        if(matricula_aluno == 0){
            return;
        }
        else{
            if(validacao_matricula(matricula_aluno) == 0){
                printf("Matricula invalida! Digite uma matricula valida.");
            }
            else{
                int remover;
                if(qtd_emprestimo == 0){
                    printf("O usario não possui emprestimos ativos. Escolha outro");
                    continue;
                }
                printf("O usuario possui %d emprestimos ativos, quais desses voce quer tirar?");
                listEmp_user(matricula_aluno);
                scanf("%d", &remover);
                if(remover < qtd_emprestimo && remover > qtd_emprestimo){ 
                    printf("O emprestimo selecionado não existe!");
                }

            }
        }
    }
}

void listEmp_atraso(){ // função pra listar emprestimos em atraso

}


void addEmp(){ // função pra adicionar emprestimos

    int matricula_aluno; // variavel local da matricula do aluno na execucao atual
    char codigo[8];      // variavel local de codigo do livro
    int qtd_disponivel;
    int qtd_usuario;

        while (1)
        {
        printf("Qual a matricula do usuario? Digite 0 para voltar");
        scanf("%d ", &matricula_aluno);
        if (matricula_aluno == 0){
            return;
        }
        else{
            if (validacao_matricula(matricula_aluno) == 0)
            { // Válida se a matricula escrita é valida por meio da função, se for valida ele só continua, se for invalida ele diz que é invalida e volta pro começo do while principal.
                printf("Matricula invalida! Digite uma matricula valida. \n");
            
            }
            else{
                if(validacao_usuario == 0){
                    printf("O usuário já possui 3 emprestimos ativos e não pode registrar um novo.");
                    system("pause");
                    return;
                }
            }
        }}
        while (1)
        { // While pra checar se o codigo escrito é válido, ele fica no loop ate que a função validacao seja verdadeira.
        printf("Qual o codigo do livro? ");
        scanf("%7s", codigo);
            if (validacao_codigo(codigo) == 0)
            {
                printf("Codigo de livro invalido! Digite um codigo válido de livro. \n");
            }
            else
            {
                if(validacao_quantidade == 0){
                    printf("Não tem estoque disponivel para o livro selecionado. Escolha outro livro.");
                    system("pause");
                    continue;
                }
                else{
                    printf("Emprestimo registrado com sucesso!");
                    regisEmp(matricula_aluno, codigo);
                    system("pause");
                    return;
                }
                
            }
        }

}

void emp()
{

    
    char opcoes[3][30] = {"Registrar emprestimo", "Listar emprestimos em atraso", "Voltar"};

    while (1)
    {
        // Função para criar interface
        int posicaoAtual = criarMenu("TELA DE EMPRESTIMOS", opcoes, 4);

        if (posicaoAtual == 0)
        {
            // Função de adicionar usuários
            addEmp();
        }
        else if (posicaoAtual == 1)
        {
            // Função de buscar usuarios por nome ou matricula
            listEmp_atraso();
        }
        else if (posicaoAtual == 2)
        {
            system("cls");
            break;
        }
        system("cls");
    }
    return;
}