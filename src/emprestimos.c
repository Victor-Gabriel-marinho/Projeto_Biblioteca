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

void listEmp_user(char matricula[8], Usuario *pessoa) // Listar o emprestimos de um usuario
{
    int c = 1;
    char today[11];
    BuscarUsuarioPorMat(pessoa, matricula); // Pegar o nome do usuario pela matricula
    printf("Emprestimos de %s: \n", pessoa->nome);
    for (int i = 0; i < totalEmprestimos; i++) // Percorre o vetor de emprestimos que sempre tem tamanho de totalEmprestimos
    {
        if (emprestimos[i].devolvido == 0 && strcmp(emprestimos[i].matricula_usuario, matricula) == 0) // Checa se a matricula registrada no emprestimo é a mesma que a matricula do aluno. Alem disso, checa se devolvido é igual a 0 para o emprestimo ainda estar aberto.
        {
            if (emprestimos[i].devolvido == 0)
            {
                printf("ID: %d\nData do emprestimo: %s\nData prevista de devolucao: %s\n", emprestimos[i].id, emprestimos[i].data_retirada, emprestimos[i].data_prevista);
                pegar_data_hoje(today); // pega a data de hoje para avisar caso esteja atrasado
                if (comp_data(emprestimos[i].data_prevista, today) == -1)
                {
                    printf("O emprestimo está atrasado!");
                }
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
            *posicao_emprestimo = i; // aqui além de checar se determinado emprestimo é de determinado usuario pela matricula, tbm checa a posicao desse emprestimo no vetor emprestimos
            return 1;
        }
    }
    return 0;
}

void listarEmp()
{

    for (int i = 0; i < totalEmprestimos; i++)
    {
        printf("ID - %d\n Matricula livro: %7s, Data de retirada: %10s, Data prevista: %10s\n", emprestimos[i].id, emprestimos[i].matricula_usuario, emprestimos[i].data_retirada, emprestimos[i].data_prevista);
    }
    system("Pause");
}

void regisEmp(Usuario *pessoa, Livro *livro, char data[11])
{
    char data_temp[11];
    Emprestimo novo;                                                                      // criacao da struct do novo emprestimo
    Emprestimo *temp = realloc(emprestimos, (totalEmprestimos + 1) * sizeof(Emprestimo)); // realocação do vetor de emprestimos
    if (temp == NULL)
    {
        printf("Erro: falha ao alocar memória! Emprestimo não foi registrado.\n");
        free(emprestimos);
        return;
    }

    emprestimos = temp;

    strcpy(data_temp, data);        // aqui copia a data enviada pelo usuario numa variavel auxilia
    somar_14_dias(data_temp);       // adiciona 14 dias na variavel auxiliar que contem a data enviada pelo usuario
    novo.id = totalEmprestimos + 1; // a logica dos IDs dos emprestimos é simples: o ID vai começar de 1 e vai se somando 1 a cada emprestimo, dessa forma, alem de evitar que o ID de um emprestimo se repita por outro pelos metodos de randomização, facilita a busca pelo ID

    strcpy(novo.matricula_usuario, pessoa->matricula);
    strcpy(novo.codigo_livro, livro->codigo);
    strcpy(novo.data_retirada, data);
    strcpy(novo.data_prevista, data_temp);
    strcpy(novo.data_devolucao, "ND"); // esses 5 strcpy sao preenchendo a struct do emprestimo novo com as informações enviadas pelo usuario.
    novo.devolvido = 0;
    emprestimos[totalEmprestimos] = novo; // enviando a nova struct para a ultima posicao do vetor de emprestimos
    totalEmprestimos++;

    printf("%d", totalEmprestimos);
    system("pause");

    SalvarEmprestimos(emprestimos, totalEmprestimos); // salvando os emprestimos

    int i = PegarIndiceUsuario(pessoa->matricula);
    int j = PegarIndiceLivro(livro->codigo);

    usuarios[i].qtd_emprestimos_ativos++;
    livros[j].qtd_disponivel--;
    livros[j].total_emprestimos++;

    SalvarUsuarios(usuarios, totalUsuarios);
    SalvarLivros(livros, totalLivros); // Como um emprestimo altera nao so a quantidade de livro disponivel como tambem a quantidade de emprestims de um usuario, precisamos fazer essas alterações em usuarios e livros e depois salvar elas.
}

void regDev()
{ // função pra registrar devoluções
    int posicao_usuario;
    Usuario pessoa;
    int qtd_emprestimo;
    int posicao_emprestimo;
    char matricula_aluno[8];
    char today[11];
    pegar_data_hoje(today);
    Livro livro;
    while (1)
    {

        printf("Qual a matricula do usuario que voce deseja registrar a devolucao? Digite 0 pra voltar: ");
        scanf("%7s", matricula_aluno);
        if (strcmp(matricula_aluno, "0") == 0)
        {
            return;
        }
        else
        {
            if (BuscarUsuarioPorMat(&pessoa, matricula_aluno) == 0)
            {
                printf("Matricula invalida! Digite uma matricula valida.\n");
                system("pause");
                continue;
            }
            else
            {
                int remover;
                if (pessoa.qtd_emprestimos_ativos == 0)
                {
                    printf("O usario não possui emprestimos ativos. Escolha outro\n"); // todo esse começo é so validacao das condicoes para pegar um emprestimo, basicamente verificando se a matricula é valido, e caso seja, buscando o usuario pela matricula para checar se ele de fato tem algum emprestimo.
                    continue;
                }
                printf("O usuario possui %d emprestimos ativos, quais desses voce quer registrar devolucao (Escreva o id de emprestimo)? \n", pessoa.qtd_emprestimos_ativos);
                listEmp_user(matricula_aluno, &pessoa);
                scanf("%d", &remover);

                if (validEmp_user(remover - 1, matricula_aluno, &posicao_emprestimo) == 1) // o valid emp user serve para pegar a posicao do emprestimo selecionado pelo usuario
                {
                    char codigo_temp[8];
                    strcpy(codigo_temp, emprestimos[posicao_emprestimo].codigo_livro); // pegar o codigo do livro para acessar ele
                    busca_livroCodigo(&livro, codigo_temp);
                    emprestimos[posicao_emprestimo].devolvido = 1;
                    strcpy(emprestimos[posicao_emprestimo].data_devolucao, today);
                    int i = PegarIndiceUsuario(pessoa.matricula);
                    int j = PegarIndiceLivro(livro.codigo);
                    usuarios[i].qtd_emprestimos_ativos--;
                    livros[j].qtd_disponivel++; // todas as linhas desde o ultimo comentario foram feitas para localizar o livro e o usuario para poder alterar a quantidade disponivel do livro e a quantidade de emprestimos ativos do usuarios.

                    emprestimos[posicao_emprestimo].devolvido = 1;
                    strcpy(emprestimos[posicao_emprestimo].data_devolucao, today); // aqui é alterando a data de devolução para a data de hoje e trocando o status de devolvido para 1 (devolvido)

                    SalvarUsuarios(usuarios, totalUsuarios);
                    SalvarLivros(livros, totalLivros);
                    SalvarEmprestimos(emprestimos, totalEmprestimos); // Salvando alterações dos vetores
                    printf("Devolucao registrada com sucesso!");
                    return;
                }
                if (validEmp_user(remover, matricula_aluno, &posicao_emprestimo) == 0)
                {
                    printf("O emprestimo selecionado não existe ou não pertence ao usuario selecionado!"); // caso o usuario digite uma opção que nao condiz com um dos emprestimos mostrados
                    continue;
                }
            }
        }
    }
}

void listEmp_atraso()
{ // função pra listar emprestimos em atraso
    char today[11];
    pegar_data_hoje(today); // pega o dia de hoje
    printf("EMPRESTIMOS ATRASADOS: \n");
    for (int i = 0; i < totalEmprestimos; i++)
    {
        if (emprestimos[i].devolvido == 0 && comp_data(emprestimos[i].data_prevista, today) == -1)
        { // percore o vetor emprestimos e caso o livro nao foi entregue (devolvido == 0) e a função comparacao de datas, considerando a data prevista de entrega e o dia de hoje retorne -1 (isso é, a data de hoje for maior que a data prevista de entrega)
            printf("ID: %d\n Matricula:%7s\n Codigo do livro: %7s\nData de Retirada: %11s\n Data prevista: %11s\n", emprestimos[i].id, emprestimos[i].matricula_usuario, emprestimos[i].codigo_livro, emprestimos[i].data_retirada, emprestimos[i].data_prevista);
        }
    }
    system("pause");
}

void addEmp()
{ // função pra adicionar emprestimos
    Usuario pessoa;
    char matricula_aluno[8];
    char codigo[8];
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
            if (pessoa.qtd_emprestimos_ativos == 3) // verificação se o usuario ja tem 3 emprestimos ativos
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
            regisEmp(&pessoa, &livro, data_emp); // aqui so chama a funcao enviando as informações necessarias

            printf("Emprestimo registrado com sucesso!\n");
            system("pause");
            return;
        }
    }
}

void pegar_user()
{
    Usuario pessoa;
    char matricula[8];

    while (1)
    {
        printf("Qual a matricula do usuario vc quer visualizar os emprestimos? Clique 0 para voltar: ");
        scanf("%7s", matricula);
        if (strcmp(matricula, "0") == 0)
        {
            return;
        }
        if (BuscarUsuarioPorMat(&pessoa, matricula) == 0)
        {
            printf("A matricula nao corresponde a nenhum usuario!");
            continue;
        }
        break;
    }
    listEmp_user(matricula, &pessoa);
    system("pause");
}

void emp()
{

    char opcoes[4][30] = {"Registrar emprestimo", "Listar emprestimos de usuario", "Listar emprestimos em atraso", "Voltar"};
    char data[11];

    while (1)
    {
        // Função para criar interface
        int posicaoAtual = criarMenu("TELA DE EMPRESTIMOS", opcoes, 4);

        if (posicaoAtual == 0)
        {
            // Função de adicionar emprestimo
            addEmp();
        }
        else if (posicaoAtual == 1)
        {
            // Função de listar emprestimos atrasados
            pegar_user();
        }
        else if (posicaoAtual == 2)
        {
            // Função de listar emprestimos atrasados
            listEmp_atraso();
        }
        else if (posicaoAtual == 3)
        {
            system("cls");
            break;
        }
        system("cls");
    }
    return;
}
