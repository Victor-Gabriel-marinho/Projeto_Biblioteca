#include "../include/algoritmos.h"
#include "../include/Users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/livros.h"
#include <time.h>

int comp_data(char data1[11], char data2[11]) // Funçao para comparar duas datas, retorna 1 para data1 > data2, -1 para data2 > data1 e 0 para data1 = data2.
{
    int d1, m1, a1;
    int d2, m2, a2;

    // extrai dia, mês e ano
    sscanf(data1, "%d/%d/%d", &d1, &m1, &a1);
    sscanf(data2, "%d/%d/%d", &d2, &m2, &a2);

    // compara ano
    if (a1 > a2) return 1;
    if (a1 < a2) return -1;

    // compara mês
    if (m1 > m2) return 1;
    if (m1 < m2) return -1;

    // compara dia
    if (d1 > d2) return 1;
    if (d1 < d2) return -1;

    return 0;
}
void pegar_data_hoje(char data[11])
{
    time_t t = time(NULL);
    struct tm *hoje = localtime(&t);

    sprintf(data, "%02d/%02d/%04d",
            hoje->tm_mday,
            hoje->tm_mon + 1,
            hoje->tm_year + 1900);
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


// Função para gerar matricula automaticamente
void gerarID(char *buffer)
{
    char caracteres[] = "0123456789";
    for (int i = 0; i < MAX_MAT; i++)
    {
        buffer[i] = caracteres[rand() % (sizeof(caracteres) - 1)];
    }

    buffer[MAX_MAT + 1] = '\0';
}
void somar_14_dias(char data[11])
{
    int dia, mes, ano;

    // extrai dd/mm/aaaa
    sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano);

    // soma 14 dias
    dia += 14;

    // ajusta dias para meses de 30 dias
    while (dia > 30)
    {
        dia -= 30;
        mes++;
    }

    // ajusta meses para ano de 12 meses
    while (mes > 12)
    {
        mes -= 12;
        ano++;
    }

    // escreve de volta na string
    sprintf(data, "%02d/%02d/%04d", dia, mes, ano);
}
/*busca binaria para encontrar o livro pelo codigo,
retorna o indice do livro no vetor ou -1 se não encontrado*/

int busca_livroCodigo(Livro *livroEncontrado, char codigo[8])
{
    int encontrado = 0;
    for (int i = 0; i < totalLivros; i++)
    {
        if (strcmp(codigo, livros[i].codigo) == 0)
        {
            *livroEncontrado = livros[i];
            encontrado = 1;
            return 1;
        }
    }
    if (encontrado != 1)
    {
        return 0;
    }
}

int BuscarLivroPorTitulo(Livro *livroEncontrado, char titulo[MAX_STRING])
{

    for (int i = 0; titulo[i] != '\0'; i++)
    {
        titulo[i] = tolower(titulo[i]);
    }
    for (int i = 0; i < totalLivros; i++)
    {
        for (int i = 0; livros->titulo[i] != '\0'; i++)
        {
            livros->titulo[i] = tolower(livros->titulo[i]);
        }
        if (strcmp(titulo, livros[i].titulo) == 0)
        {
            *livroEncontrado = livros[i];
            return 1;
        }
    }


        return 0;
    
}


// Busca um usuário pelo nome e copia os dados para usuarioEncontrado.
// Se o nome não for encontrado, exibe mensagem de erro.
int BuscarUsuarioPorNome(Usuario *usuarioEncontrado, char nome[8])
{
    char temp[100];

    for (int i = 0; nome[i] != '\0'; i++)
        nome[i] = tolower(nome[i]);

    for (int i = 0; i < totalUsuarios; i++)
    {
        strcpy(temp, usuarios[i].nome);

        for (int j = 0; temp[j] != '\0'; j++) 
            temp[j] = tolower(temp[j]);

        if (strcmp(nome, temp) == 0)
        {
            *usuarioEncontrado = usuarios[i];
            return 1;
        }
    }

    return 0;
}

// Busca um usuário pela matrícula e copia os dados para usuarioEncontrado.
// Se a matrícula não for encontrada, exibe mensagem de erro.
int BuscarUsuarioPorMat(Usuario *usuarioEncontrado, char matricula[8])
{

    for (int i = 0; i < totalUsuarios; i++)
    {
        if (strcmp(matricula, usuarios[i].matricula) == 0)
        {
            *usuarioEncontrado = usuarios[i];
            return 1;
        }
    }

        return 0;
}
int PegarIndiceUsuario(char matricula[8])
{

    for (int i = 0; i < totalUsuarios; i++)
    {
        if (strcmp(matricula, usuarios[i].matricula) == 0)
        {
            return i;
        }
    }

        return 0;
}

int PegarIndiceLivro(char codigo[8])
{

    for (int i = 0; i < totalLivros; i++)
    {
        if (strcmp(codigo, livros[i].codigo) == 0)
        {
            return i;
        }
    }

        return 0;
}



static void merge_livros(Livro *vet, Livro *tmp, int esq, int meio, int dir)
{
    int i = esq, j = meio + 1, k = esq;

    while (i <= meio && j <= dir)
    {
        // Alterado de >= para <= para ordenar de forma crescente
        if (vet[i].total_emprestimos <= vet[j].total_emprestimos)
            tmp[k++] = vet[i++];
        else
            tmp[k++] = vet[j++];
    }

    // Copia os elementos restantes da metade esquerda, se houver
    while (i <= meio)
        tmp[k++] = vet[i++];

    // Copia os elementos restantes da metade direita, se houver
    while (j <= dir)
        tmp[k++] = vet[j++];

    // Copia o segmento mesclado de volta para o vetor original
    for (i = esq; i <= dir; i++)
        vet[i] = tmp[i];
}

static void merge_sort_livros_rec(Livro *vet, Livro *tmp, int esq, int dir)
{
    // Caso base: um único elemento já está ordenado
    if (esq >= dir)
        return;

    int meio = esq + (dir - esq) / 2;

    // Ordena recursivamente a primeira metade
    merge_sort_livros_rec(vet, tmp, esq, meio);

    // Ordena recursivamente a segunda metade
    merge_sort_livros_rec(vet, tmp, meio + 1, dir);

    // Mescla as duas metades ordenadas
    merge_livros(vet, tmp, esq, meio, dir);
}

void merge_sort_livros(Livro *saida, int n)
{
    if (n <= 0)
        return;

    // Copia os livros do banco para o vetor de saída
    memcpy(saida, db.livros, n * sizeof(Livro));

    Livro tmp[MAX_LIVROS];

    // Inicia a ordenação por merge sort
    merge_sort_livros_rec(saida, tmp, 0, n - 1);
}

static int cmp_data(const char *a, const char *b)
{
    int da, ma, aa, db2, mb, ab;
    sscanf(a, "%d/%d/%d", &da, &ma, &aa);
    sscanf(b, "%d/%d/%d", &db2, &mb, &ab);
    if (aa != ab)
        return aa - ab;
    if (ma != mb)
        return ma - mb;
    return da - db2;
}

static void merge_emp(Emprestimo *vet, Emprestimo *tmp, int esq, int meio, int dir)
{
    int i = esq, j = meio + 1, k = esq;

    // Mescla duas metades ordenadas por data de retirada
    while (i <= meio && j <= dir)
    {
        if (cmp_data(vet[i].data_retirada, vet[j].data_retirada) <= 0)
            tmp[k++] = vet[i++];
        else
            tmp[k++] = vet[j++];
    }

    // Copia o restante da primeira metade
    while (i <= meio)
        tmp[k++] = vet[i++];

    // Copia o restante da segunda metade
    while (j <= dir)
        tmp[k++] = vet[j++];

    // Copia o segmento mesclado de volta para o vetor original
    for (i = esq; i <= dir; i++)
        vet[i] = tmp[i];
}

static void merge_sort_emp_rec(Emprestimo *vet, Emprestimo *tmp, int esq, int dir)
{
    // Caso base: segmento com zero ou um elemento está ordenado
    if (esq >= dir)
        return;

    int meio = esq + (dir - esq) / 2;

    // Ordena recursivamente a primeira metade
    merge_sort_emp_rec(vet, tmp, esq, meio);

    // Ordena recursivamente a segunda metade
    merge_sort_emp_rec(vet, tmp, meio + 1, dir);

    // Mescla as duas metades ordenadas
    merge_emp(vet, tmp, esq, meio, dir);
}

void merge_sort_emprestimos_data(Emprestimo *vet, int n)
{
    if (n <= 1)
        return;

    // Vetor temporário usado para mesclar os segmentos ordenados
    Emprestimo tmp[MAX_EMPRESTIMOS];

    // Ordena os empréstimos por data de retirada
    merge_sort_emp_rec(vet, tmp, 0, n - 1);
}
void exibir_livros_mais_emprestados()
{
    int n = db.num_livros;

    if (n < 0)
    {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    Livro saida[MAX_LIVROS];

    // Ordena os livros por total_emprestimos (decrescente)
    merge_sort_livros(saida, n);

    // Exibe o resultado
    for (int i = 0; i < n; i++)
    {
        printf("%d. %s — %d empréstimos\n",
               i + 1,
               saida[i].titulo,
               saida[i].total_emprestimos);
    }
}