#include <stdio.h>
#include "../include/biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/algoritmos.h"
#include "../include/interface.h"
#include "../include/Users.h"
#include "../include/persistencia.h"
#include "../include/emprestimos.h"

int validacao_codigo(char codigo[8])
{ // função pra checar se o codigo enviado é válido, retorna 0 (false, não é valido) ou retorna 1(true, é valido)
}
int validacao_quantidade(int qtd_disponivel)
{ // função pra     checar se tem quantidade disponivel para emprestmo, retorna 0 (false, não tem) ou retorna 1(true, tem)
}
int validacao_usuario(int qtd_usuario)
{ // função pra     checar se o usuario pode pegar mais um emprestimo, retorna 0 (false, não pode) ou retorna 1(true, pode)
}


void listEmp_user(char matricula[8]){
    int c = 1;
    for(int i = 0; i < totalEmprestimos; i++){
        if(strcmp(emprestimos[i].matricula_usuario, matricula) == 0){
            printf("Emprestimos de %s: \n", emprestimos[i].matricula_usuario);
            if(emprestimos[i].devolvido ==0){
            printf("%d: \nID: %d\nData do emprestimo: %s\nData prevista de devolucao: %s\n", c, emprestimos[i].id, emprestimos[i].data_retirada, emprestimos[i].data_prevista);
            c++;
            }
        }
    }
}
int validEmp_user(int id, char matricula[8], int *posicao_emprestimo){
    for(int i = 0; i < totalEmprestimos; i++){
        if(emprestimos[i].id == id && strcmp(emprestimos[i].matricula_usuario, matricula) == 0){
            *posicao_emprestimo = i;
            return 1;
        }
    }
    return 0;
}

void regisEmp(Usuario *pessoa, Livro *livro, Emprestimo *emprestimos){
    Emprestimo *temp = realloc(emprestimos, (totalEmprestimos + 1) * sizeof(Emprestimo));
            if (temp == NULL)
            {
                printf("Erro: falha ao alocar memória! Emprestimo não foi registrado.\n");
                free(emprestimos);
                return;
            }
            emprestimos = temp;
            //Emprestimo novo = {gerarID};
            //emprestimos[totalEmprestimos] = {}
}

void regDev(){ // função pra registrar devoluções 
    int posicao_usuario;
    Usuario pessoa;
    int qtd_emprestimo;
    int posicao_emprestimo;
    char matricula_aluno[8];
    while(1){ // loop central da função 

        mostrarCursor();
        printf("Qual a matricula do usuario que voce deseja registrar a devolucao? Digite 0 pra voltar: ");
        scanf("%s", matricula_aluno);
        printf("%d",BuscarUsuarioPorMat(&pessoa, matricula_aluno));
        if(strcmp(matricula_aluno, "0") == 0){
            return;
        }
        else{
            if(BuscarUsuarioPorMat(&pessoa, matricula_aluno) == 0){
                printf("Matricula invalida! Digite uma matricula valida.");
                continue;
            }
            else{
                int remover;
                if(pessoa.qtd_emprestimos_ativos == 0){
                    printf("O usario não possui emprestimos ativos. Escolha outro");
                    continue;
                }
                printf("O usuario possui %d emprestimos ativos, quais desses voce quer registrar devolucao (Escreva o id de emprestimo)? ", pessoa.qtd_emprestimos_ativos);
                listEmp_user(matricula_aluno);
                scanf("%d", &remover);
                if(validEmp_user(remover, matricula_aluno, &posicao_emprestimo) == 1){
                    
                    for(int i = posicao_emprestimo; i < totalEmprestimos -1; i++){
                        emprestimos[i] = emprestimos[i+1];
                    }
                    totalEmprestimos--;
                    printf("Devolucao registrada com sucesso!");
                    return;
                }
                if(validEmp_user(remover, matricula_aluno, &posicao_emprestimo) == 0){ 
                    printf("O emprestimo selecionado não existe ou não pertence ao usuario selecionado!");
                }

            }
        }
    }
}

void listEmp_atraso(){ // função pra listar emprestimos em atraso

}


void addEmp(){ // função pra adicionar emprestimos
    Usuario pessoa;
    char matricula_aluno[8]; // variavel local da matricula do aluno na execucao atual
    char codigo[8];      // variavel local de codigo do livro
    int qtd_disponivel;
    int qtd_usuario;
    int posicao;
    Livro *livro;

        while (1)
        {
            mostrarCursor();
        printf("Qual a matricula do usuario? Digite 0 para voltar: ");
        fgets(matricula_aluno, 8, stdin);

        if (strcmp(matricula_aluno, "0\n") == 0){
            return;
        }
        else{
            matricula_aluno[strlen(matricula_aluno)-1]= '\n';
            if (BuscarUsuarioPorMat(&pessoa, matricula_aluno) == 0)
            { // Válida se a matricula escrita é valida por meio da função, se for valida ele só continua, se for invalida ele diz que é invalida e volta pro começo do while principal.
                printf("Matricula invalida! Digite uma matricula valida. \n");
                continue;
            }
            else{
                if(pessoa.qtd_emprestimos_ativos == 3){
                    printf("O usuário já possui 3 emprestimos ativos e não pode registrar um novo.\n");
                    system("pause");
                    return;
                }
            }
        }}
        while (1)
        { // While pra checar se o codigo escrito é válido, ele fica no loop ate que a função validacao seja verdadeira.
        printf("Qual o codigo do livro? Digite 0 para volta\n");
        scanf("%s", codigo);
        if(codigo == 0){
            return;
        }
            if(busca_livroCodigo(livro, codigo) == 0)
            {
                printf("Codigo de livro invalido! Digite um codigo válido de livro. \n");
                system("pause");
                continue;
            }
            else
            {
                if(livro->qtd_disponivel == 0){
                    printf("Não tem estoque disponivel para o livro selecionado. Escolha outro livro.\n");
                    system("pause");
                    continue;
                }
                else{
                    printf("Emprestimo registrado com sucesso!\n");
                    regisEmp(&pessoa, livro, emprestimos);
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
        int posicaoAtual = criarMenu("TELA DE EMPRESTIMOS", opcoes, 3);

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