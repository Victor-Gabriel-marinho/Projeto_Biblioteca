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
#include <ctype.h>
#include "../include/livros.h"

int comp_data(char data1[11], char data2[11])
{
}

void listEmp_user(char matricula[8])
{
    int c = 1;
    for (int i = 0; i < totalEmprestimos; i++)
    {
        if (strcmp(emprestimos[i].matricula_usuario, matricula) == 0)
        {
            printf("Emprestimos de %s: \n", emprestimos[i].matricula_usuario);
            if (emprestimos[i].devolvido == 0)
            {
                printf("%d: \nID: %d\nData do emprestimo: %s\nData prevista de devolucao: %s\n", c, emprestimos[i].id, emprestimos[i].data_retirada, emprestimos[i].data_prevista);
                c++;
            }
        }
    }
}
int validEmp_user(int id, char matricula[8], int *posicao_emprestimo)
{
    for (int i = 0; i < totalEmprestimos; i++)
    {
        if (emprestimos[i].id == id && strcmp(emprestimos[i].matricula_usuario, matricula) == 0)
        {
            *posicao_emprestimo = i;
            return 1;
        }
    }
    return 0;
}
void calcular_data(char data[11])
{
    int dia, mes, ano;

    // pega os valores da string
    sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano);

    // adiciona 14 dias
    dia += 14;

    // ajusta meses
    while (dia > 30)
    {

        dia -= 30;
        mes++;

        if (mes > 12)
        {
            mes = 1;
            ano++;
        }
    }

    // sobrescreve a string original
    sprintf(data, "%02d/%02d/%04d", dia, mes, ano);
}

void ler_data(char data[])
{

    int dia, mes, ano;
    int valida = 0;

    while (valida == 0)
    {

        printf("Digite a data (dd/mm/aaaa): ");
        scanf("%10s", data);

        // verifica tamanho
        if (strlen(data) != 10)
        {
            printf("Data invalida!\n");
            continue;
        }

        // verifica barras
        if (data[2] != '/' || data[5] != '/')
        {
            printf("Data invalida!\n");
            continue;
        }

        // verifica numeros
        int erro = 0;

        for (int i = 0; i < 10; i++)
        {

            if (i == 2 || i == 5)
                continue;

            if (!isdigit(data[i]))
            {
                erro = 1;
                break;
            }
        }

        if (erro)
        {
            printf("Data invalida!\n\n");
            continue;
        }

        // converte
        sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano);

        // verifica dia
        if (dia < 1 || dia > 31)
        {
            printf("Dia invalido!\n\n");
            continue;
        }

        // verifica mes
        if (mes < 1 || mes > 12)
        {
            printf("Mes invalido!\n\n");
            continue;
        }

        valida = 1;
    }
}

void listarEmp()
{

    for (int i = 0; i < totalEmprestimos; i++)
    {
        printf("ID - %d\n", emprestimos[i].id);
    }
    system("Pause");
}

void regisEmp(Usuario *pessoa, Livro *livro, char data[10])
{
    char data_temp[11];
    Emprestimo novo;
    Emprestimo *temp = realloc(emprestimos, (totalEmprestimos + 1) * sizeof(Emprestimo));
    if (temp == NULL)
    {
        printf("Erro: falha ao alocar memória! Emprestimo não foi registrado.\n");
        free(emprestimos);
        return;
    }

    emprestimos = temp;

    strcpy(data_temp, data);
    calcular_data(data_temp);
    novo.id = totalEmprestimos;

    strcpy(novo.matricula_usuario, pessoa->matricula);
    strcpy(novo.codigo_livro, livro->codigo);
    strcpy(novo.data_retirada, data);
    strcpy(novo.data_prevista, data_temp);
    strcpy(novo.data_devolucao, "ND");

    novo.devolvido = 0;
    emprestimos[totalEmprestimos] = novo;
    totalEmprestimos++;
    
    printf("%d",totalEmprestimos);
    system("pause");

    SalvarEmprestimos(emprestimos, totalEmprestimos);

    int i = PegarIndiceUsuario(pessoa->matricula);
    int j = PegarIndiceLivro(livro->codigo);

    usuarios[i].qtd_emprestimos_ativos++;
    livros[j].qtd_disponivel--;

    SalvarUsuarios(usuarios, totalUsuarios);
    SalvarLivros(livros, totalLivros);
}

void regDev()
{ // função pra registrar devoluções
    int posicao_usuario;
    Usuario pessoa;
    int qtd_emprestimo;
    int posicao_emprestimo;
    char matricula_aluno[8];
    Livro livro;
    while (1)
    { // loop central da função

        mostrarCursor();
        printf("Qual a matricula do usuario que voce deseja registrar a devolucao? Digite 0 pra voltar: ");
        scanf("%s", matricula_aluno);
        printf("%d", BuscarUsuarioPorMat(&pessoa, matricula_aluno));
        if (strcmp(matricula_aluno, "0") == 0)
        {
            return;
        }
        else
        {
            if (BuscarUsuarioPorMat(&pessoa, matricula_aluno) == 0)
            {
                printf("Matricula invalida! Digite uma matricula valida.");
                continue;
            }
            else
            {
                int remover;
                if (pessoa.qtd_emprestimos_ativos == 0)
                {
                    printf("O usario não possui emprestimos ativos. Escolha outro");
                    continue;
                }
                printf("O usuario possui %d emprestimos ativos, quais desses voce quer registrar devolucao (Escreva o id de emprestimo)? ", pessoa.qtd_emprestimos_ativos);
                listEmp_user(matricula_aluno);
                scanf("%d", &remover);

                if (validEmp_user(remover, matricula_aluno, &posicao_emprestimo) == 1)
                {
                    char codigo_temp[8];
                    strcpy(codigo_temp, emprestimos[posicao_emprestimo].codigo_livro);
                    busca_livroCodigo(&livro, codigo_temp);
                    for (int i = posicao_emprestimo; i < totalEmprestimos - 1; i++)
                    {
                        emprestimos[i] = emprestimos[i + 1];
                    }
                    totalEmprestimos--;
                    printf("Devolucao registrada com sucesso!");
                    return;
                }
                if (validEmp_user(remover, matricula_aluno, &posicao_emprestimo) == 0)
                {
                    printf("O emprestimo selecionado não existe ou não pertence ao usuario selecionado!");
                    continue;
                }
            }
        }
    }
}

void listEmp_atraso()
{ // função pra listar emprestimos em atraso
}

void addEmp()
{ // função pra adicionar emprestimos
    Usuario pessoa;
    char matricula_aluno[8]; // variavel local da matricula do aluno na execucao atual
    char codigo[8];          // variavel local de codigo do livro
    int qtd_disponivel;
    int qtd_usuario;
    int posicao;
    char data_emp[11];
    Livro livro;

    while (1)
    {
        mostrarCursor();
        printf("Qual a matricula do usuario? Digite 0 para voltar: ");
        scanf("%7s", matricula_aluno);
        if (strcmp(matricula_aluno, "0") == 0)
        {
            return;
        }
        if (BuscarUsuarioPorMat(&pessoa, matricula_aluno) == 0)
        { // Válida se a matricula escrita é valida por meio da função, se for valida ele só continua, se for invalida ele diz que é invalida e volta pro começo do while principal.
            printf("Matricula invalida! Digite uma matricula valida. \n");
            continue;
        }
        else
        {
            printf("%d", pessoa.qtd_emprestimos_ativos);
            if (pessoa.qtd_emprestimos_ativos == 3)
            {
                printf("O usuário já possui 3 emprestimos ativos e não pode registrar um novo. \n");
                system("pause");
                return;
            }
            else
            {
                break;
            }
        }
    }
    while (1)
    { // While pra checar se o codigo escrito é válido, ele fica no loop ate que a função validacao seja verdadeira.
        printf("Qual o codigo do livro? Digite 0 para voltar");
        scanf("%7s", codigo);
        if (strcmp(codigo, "0") == 0)
        {
            return;
        }
        if (busca_livroCodigo(&livro, codigo) == 0)
        {
            printf("Codigo de livro invalido! Digite um codigo válido de livro. \n");
            continue;
        }

        if (livro.qtd_disponivel == 0)
        {
            printf("Não tem estoque disponivel para o livro selecionado. Escolha outro livro.\n");
            continue;
        }
        else
        {
            ler_data(data_emp);
            regisEmp(&pessoa, &livro, data_emp);

            printf("Emprestimo registrado com sucesso!\n");
            system("pause");
            return;
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
            listarEmp();
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