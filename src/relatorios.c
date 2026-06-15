/* ============================================================================
   SISTEMA DE RELATÓRIOS - BIBLIOTECA
   ============================================================================
   Módulo responsável por gerar relatórios sobre livros, empréstimos e
   históricos de usuários, exibindo dados na tela e salvando em arquivos.
   ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "../include/biblioteca.h"
#include "../include/algoritmos.h"
#include "../include/interface.h"
#include "../include/Users.h"
#include "../include/livros.h"
#include "../include/emprestimos.h"
#include "../include/relatorios.h"

/*
   FUNÇÕES AUXILIARES INTERNAS (Helpers)

   Funções privadas que oferecem suporte às operações principais de
   geração de relatórios, como abertura de arquivos, formatação de tela
   e manipulação de cursor.
   */

/* abrirArquivoRelatorio()
   - Cria o diretório "relatorios/" se não existir
   - Abre um arquivo para escrita dentro deste diretório
   - Retorna o ponteiro FILE para escrita, ou NULL se falhar */
static FILE *abrirArquivoRelatorio(const char *nomeArquivo)
{
    _mkdir("relatorios");

    char caminho[256];
    snprintf(caminho, sizeof(caminho), "relatorios/%s", nomeArquivo);

    FILE *arq = fopen(caminho, "w");
    return arq;
}

/* linha()
   - Posiciona o cursor na linha y, coluna 2
   - Imprime uma sequência horizontal de hífens (-)
   - Cria divisores visuais nas tabelas dos relatórios */
static void linha(int y, int largura)
{
    gotoxy(2, y);
    for (int i = 0; i < largura; i++)
        printf("-");
}

/* aguardarTecla()
   - Exibe mensagem de rodapé: "Pressione qualquer tecla para voltar..."
   - Mostra o cursor antes de aguardar
   - Aguarda entrada do usuário com _getch()
   - Oculta o cursor novamente após o pressionamento */
static void aguardarTecla(int y)
{
    gotoxy(2, y);
    printf("Pressione qualquer tecla para voltar...");
    mostrarCursor();
    _getch();
    ocultarCursor();
}

/* cabecalhoTela()
   - Configura a página de código para UTF-8
   - Oculta o cursor do terminal
   - Limpa a tela
   - Exibe um título centralizado formatado com "===" */
static void cabecalhoTela(const char *titulo)
{
    SetConsoleOutputCP(65001);
    ocultarCursor();
    system("cls");
    gotoxy(0, 2);
    printf("=== %s ===\n\n", titulo);
}

/*
   RELATÓRIO 1: LIVROS MAIS EMPRESTADOS

   Exibe e salva em arquivo uma lista de todos os livros ordenados por
   quantidade de empréstimos, em ordem decrescente. Mostra código, título,
   autor e total de empréstimos de cada obra.
    */
void relatorioLivrosMaisEmprestados()
{
    cabecalhoTela("RELATORIO: LIVROS MAIS EMPRESTADOS");

    /* Verifica se há livros cadastrados no sistema */
    if (totalLivros == 0)
    {
        gotoxy(2, 5);
        printf("Nenhum livro cadastrado.");
        aguardarTecla(7);
        return;
    }

    /* Cria cópia dos livros e ordena por quantidade de empréstimos */
    Livro ordenados[MAX_LIVROS];
    merge_sort_livros(ordenados, totalLivros);

    /* Exibe cabeçalho da tabela na tela */
    const int COL = 2, Y0 = 5;
    gotoxy(COL, Y0);
    printf("%-4s %-7s %-35s %-25s %s", "POS", "CODIGO", "TITULO", "AUTOR", "EMP.");
    linha(Y0 + 1, 80);

    /* Abre arquivo para salvar o relatório */
    FILE *arq = abrirArquivoRelatorio("livros_mais_emprestados.txt");
    if (arq)
        fprintf(arq, "%-4s %-7s %-35s %-25s %s\n%-*s\n",
                "POS", "CODIGO", "TITULO", "AUTOR", "EMP.", 80, "");

    /* Itera sobre todos os livros e exibe dados formatados */
    for (int i = 0; i < totalLivros; i++)
    {
        gotoxy(COL, Y0 + 2 + i);
        printf("%-4d %-7s %-35.35s %-25.25s %d",
               i + 1,
               ordenados[i].codigo,
               ordenados[i].titulo,
               ordenados[i].autor,
               ordenados[i].total_emprestimos);

        /* Escreve a mesma linha no arquivo */
        if (arq)
            fprintf(arq, "%-4d %-7s %-35.35s %-25.25s %d\n",
                    i + 1,
                    ordenados[i].codigo,
                    ordenados[i].titulo,
                    ordenados[i].autor,
                    ordenados[i].total_emprestimos);
    }

    /* Fecha o arquivo (não exibe caminho de salvamento) */
    int rodape = Y0 + 2 + totalLivros + 1;
    if (arq)
    {
        fclose(arq);
    }
    aguardarTecla(rodape);
}

static int diasAtraso(const char *previsto, const char *hoje)
{
    int dp, mp, ap, dh, mh, ah;
    sscanf(previsto, "%d/%d/%d", &dp, &mp, &ap);
    sscanf(hoje, "%d/%d/%d", &dh, &mh, &ah);

    // Converte ambas as datas para "dias totais" usando fórmula simples
    long dias_prev = ap * 365L + mp * 30L + dp;
    long dias_hoje = ah * 365L + mh * 30L + dh;

    return (int)(dias_hoje - dias_prev);
}

/*
   RELATÓRIO 2: EMPRÉSTIMOS EM ATRASO

   Exibe e salva em arquivo uma lista de empréstimos não devolvidos que
   ultrapassaram a data prevista de devolução. Mostra ID, matrícula,
   nome do usuário, título do livro, data de retirada e data prevista.
    */
void relatorioEmprestimosAtraso()
{
    cabecalhoTela("RELATORIO: EMPRESTIMOS EM ATRASO");

    char hoje[11];
    pegar_data_hoje(hoje);

    gotoxy(2, 5);
    printf("Data de referencia: %s", hoje);

    const int COL = 2, Y0 = 7;
    gotoxy(COL, Y0);
    printf("%-4s %-8s %-25s %-30s %s",
           "ID", "MAT.", "USUARIO", "LIVRO", "ATRASO");
    linha(Y0 + 1, 75);

    FILE *arq = abrirArquivoRelatorio("emprestimos_em_atraso.txt");
    if (arq)
        fprintf(arq, "Data de referencia: %s\n\n%-4s %-8s %-25s %-30s %s\n%-*s\n",
                hoje, "ID", "MAT.", "USUARIO", "LIVRO", "ATRASO", 75, "");

    int achou = 0, linha_atual = Y0 + 2;
    for (int i = 0; i < totalEmprestimos; i++)
    {
        Emprestimo *e = &emprestimos[i];
        if (e->devolvido != 0 || comp_data(e->data_prevista, hoje) != -1)
            continue;

        Usuario *u = NULL;
        Livro *l = NULL;
        for (int j = 0; j < totalUsuarios; j++)
            if (strcmp(usuarios[j].matricula, e->matricula_usuario) == 0)
            {
                u = &usuarios[j];
                break;
            }
        for (int j = 0; j < totalLivros; j++)
            if (strcmp(livros[j].codigo, e->codigo_livro) == 0)
            {
                l = &livros[j];
                break;
            }

        int dias = diasAtraso(e->data_prevista, hoje);
        char atraso_str[20];
        snprintf(atraso_str, sizeof(atraso_str), "%d dia%s", dias, dias == 1 ? "" : "s");

        gotoxy(COL, linha_atual);
        printf("%-4d %-8s %-25.25s %-30.30s %s",
               e->id,
               e->matricula_usuario,
               u ? u->nome : "(removido)",
               l ? l->titulo : "(removido)",
               atraso_str);

        if (arq)
            fprintf(arq, "%-4d %-8s %-25.25s %-30.30s %s\n",
                    e->id, e->matricula_usuario,
                    u ? u->nome : "(removido)",
                    l ? l->titulo : "(removido)",
                    atraso_str);

        linha_atual++;
        achou = 1;
    }

    if (!achou)
    {
        gotoxy(COL, linha_atual);
        printf("Nenhum emprestimo em atraso.");
        if (arq)
            fprintf(arq, "Nenhum emprestimo em atraso.\n");
        linha_atual++;
    }

    linha_atual++;
    if (arq)
    {
        fclose(arq);
    }
    aguardarTecla(linha_atual);
}

/*
   RELATÓRIO 3: ACERVO DISPONÍVEL

   Exibe e salva em arquivo uma lista de todos os livros que possuem
   quantidade disponível maior que zero. Mostra código, título, autor
   e proporção de quantidade disponível por total.
    */
void relatorioAcervoDisponivel()
{
    cabecalhoTela("RELATORIO: ACERVO DISPONIVEL");

    /* Exibe cabeçalho da tabela na tela */
    const int COL = 2, Y0 = 5;
    gotoxy(COL, Y0);
    printf("%-7s %-35s %-25s %s", "CODIGO", "TITULO", "AUTOR", "DISP/TOTAL");
    linha(Y0 + 1, 80);

    /* Abre arquivo para armazenar o relatório */
    FILE *arq = abrirArquivoRelatorio("acervo_disponivel.txt");
    if (arq)
        fprintf(arq, "%-7s %-35s %-25s %s\n%-*s\n",
                "CODIGO", "TITULO", "AUTOR", "DISP/TOTAL", 80, "");

    /* Percorre todos os livros filtrando apenas os disponíveis */
    int achou = 0, linha_atual = Y0 + 2;
    for (int i = 0; i < totalLivros; i++)
    {
        /* Ignora livros com quantidade disponível zerada */
        if (livros[i].qtd_disponivel <= 0)
            continue;

        /* Exibe informações do livro disponível na tela */
        gotoxy(COL, linha_atual);
        printf("%-7s %-35.35s %-25.25s %d/%d",
               livros[i].codigo,
               livros[i].titulo,
               livros[i].autor,
               livros[i].qtd_disponivel,
               livros[i].qtd_total);

        /* Escreve a mesma linha no arquivo */
        if (arq)
            fprintf(arq, "%-7s %-35.35s %-25.25s %d/%d\n",
                    livros[i].codigo, livros[i].titulo, livros[i].autor,
                    livros[i].qtd_disponivel, livros[i].qtd_total);

        linha_atual++;
        achou = 1;
    }

    /* Se nenhum livro estiver disponível, exibe mensagem correspondente */
    if (!achou)
    {
        gotoxy(COL, linha_atual);
        printf("Nenhum livro disponivel no momento.");
        if (arq)
            fprintf(arq, "Nenhum livro disponivel.\n");
        linha_atual++;
    }

    /* Fecha o arquivo (não exibe caminho de salvamento) */
    linha_atual++;
    if (arq)
    {
        fclose(arq);
    }
    aguardarTecla(linha_atual);
}

/*
   RELATÓRIO 4: HISTÓRICO DE EMPRÉSTIMOS DE UM USUÁRIO

   Exibe e salva em arquivo o histórico completo de empréstimos de um
   usuário específico, mostrando todos os empréstimos realizados com
   datas e status atual (devolvido, atrasado ou em aberto).
 */
void relatorioHistoricoUsuario()
{
    cabecalhoTela("RELATORIO: HISTORICO DE USUARIO");

    /* Solicita a matrícula do usuário cuja história será consultada */
    char matricula[8];
    gotoxy(2, 5);
    printf("Matricula do usuario: ");
    mostrarCursor();
    scanf("%7s", matricula);
    ocultarCursor();

    /* Busca o usuário pelo número de matrícula */
    Usuario pessoa;
    if (BuscarUsuarioPorMat(&pessoa, matricula) == 0)
    {
        gotoxy(2, 7);
        printf("[!] Usuario nao encontrado.");
        aguardarTecla(9);
        return;
    }

    /* Aloca espaço para armazenar os empréstimos do usuário */
    Emprestimo *hist = NULL;
    if (totalEmprestimos > 0)
        hist = malloc(totalEmprestimos * sizeof(Emprestimo));

    /* Filtra apenas os empréstimos realizados por este usuário */
    int n = 0;
    for (int i = 0; i < totalEmprestimos; i++)
        if (strcmp(emprestimos[i].matricula_usuario, matricula) == 0)
            hist[n++] = emprestimos[i];

    /* Ordena os empréstimos por data de retirada */
    merge_sort_emprestimos_data(hist, n);

    /* Exibe informações do usuário consultado */
    const int COL = 2;
    int y = 7;
    gotoxy(COL, y++);
    printf("Usuario : %s", pessoa.nome);
    gotoxy(COL, y++);
    printf("Matricula: %s  |  Curso: %s", pessoa.matricula, pessoa.curso);
    gotoxy(COL, y++);
    printf("Total de emprestimos: %d", n);
    y++;

    /* Abre arquivo para armazenar o histórico */
    FILE *arq = abrirArquivoRelatorio("historico_usuario.txt");
    if (arq)
        fprintf(arq, "Usuario: %s (Mat. %s) | Curso: %s\nTotal de emprestimos: %d\n\n",
                pessoa.nome, pessoa.matricula, pessoa.curso, n);

    /* Se o usuário não possui empréstimos, exibe mensagem informativa */
    if (n == 0)
    {
        gotoxy(COL, y);
        printf("Nenhum emprestimo registrado para este usuario.");
        if (arq)
            fprintf(arq, "Nenhum emprestimo registrado.\n");
        y++;
    }
    else
    {
        /* Exibe cabeçalho da tabela de empréstimos */
        gotoxy(COL, y);
        printf("\n%-5s %-34s %-10s %-10s %-10s %-10s\n",
               "ID", "LIVRO", "RETIRADA", "PREVISTO", "DEVOLVIDO", "STATUS");
        y++;

        gotoxy(COL, y);
        for (int i = 0; i < 90; i++)
            printf("-");
        y++;

        if (arq)
            fprintf(arq, "\n%-5s %-34s %-10s %-10s %-10s %-10s\n%-*s\n",
                    "ID", "LIVRO", "RETIRADA", "PREVISTO", "DEVOLVIDO", "STATUS", 90, "");

        /* Obtém a data de referência (hoje) para verificar atrasos */
        char hoje[11];
        pegar_data_hoje(hoje);

        /* Percorre todos os empréstimos do usuário */
        for (int i = 0; i < n; i++)
        {
            Emprestimo *e = &hist[i];

            /* Busca o título do livro emprestado */
            Livro *l = NULL;
            for (int j = 0; j < totalLivros; j++)
                if (strcmp(livros[j].codigo, e->codigo_livro) == 0)
                {
                    l = &livros[j];
                    break;
                }

            /* Determina o status atual do empréstimo */
            const char *status;
            if (e->devolvido)
                status = "DEVOLVIDO";
            else if (comp_data(e->data_prevista, hoje) == -1)
                status = "ATRASADO";
            else
                status = "EM ABERTO";

            /* Exibe informações do empréstimo na tela */
            gotoxy(COL, y);
            printf("\n%-5d %-34.34s %-10s %-10s %-10s %-10s\n",
                   e->id,
                   l ? l->titulo : "(removido)",
                   e->data_retirada,
                   e->data_prevista,
                   e->devolvido ? e->data_devolucao : "-",
                   status);

            /* Escreve a mesma linha no arquivo */
            if (arq)

                fprintf(arq, "\n%-5d %-34.34s %-10s %-10s %-10s %-10s\n",
                        e->id,
                        l ? l->titulo : "(removido)",
                        e->data_retirada,
                        e->data_prevista,
                        e->devolvido ? e->data_devolucao : "-",
                        status);
            y++;
        }
    }

    /* Libera a memória alocada para o histórico */
    free(hist);
    y++;

    /* Fecha o arquivo (não exibe caminho de salvamento) */
    if (arq)
    {
        fclose(arq);
    }
    aguardarTecla(y);
}

/*
   MENU PRINCIPAL DE RELATÓRIOS

   Gerencia a navegação entre os diferentes tipos de relatórios disponíveis.
   Exibe opções ao usuário e executa o relatório selecionado em loop até
   que o usuário escolha voltar ao menu anterior.
   */
void Relatorios()
{
    /* Define as opções de menu disponíveis para o usuário */
    char opcoes[5][30] = {
        "Livros mais emprestados",
        "Emprestimos em atraso",
        "Acervo disponivel",
        "Historico de usuario",
        "Voltar"};

    /* Loop do menu - continua até o usuário escolher voltar */
    while (1)
    {
        /* Exibe o menu interativo e captura a escolha do usuário */
        int posicaoAtual = criarMenu("TELA DE RELATORIOS", opcoes, 5);

        /* Executa a função correspondente à opção selecionada */
        switch (posicaoAtual)
        {
        case 0:
            relatorioLivrosMaisEmprestados();
            break;
        case 1:
            relatorioEmprestimosAtraso();
            break;
        case 2:
            relatorioAcervoDisponivel();
            break;
        case 3:
            relatorioHistoricoUsuario();
            break;
        case 4:
            /* Usuário escolheu voltar: limpa tela e retorna */
            system("cls");
            return;
        }
        system("cls");
    }
}