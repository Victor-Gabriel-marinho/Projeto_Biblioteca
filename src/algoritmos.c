#include "../include/algoritmos.h"
#include "../include/Users.h"
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

    buffer[MAX_MAT + 1] = '\0';
}

/*busca binaria para encontrar o livro pelo codigo,
retorna o indice do livro no vetor ou -1 se não encontrado*/

int busca_livro(char codigo[8])
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
        if (strcmp(db.livros[meio].codigo, codigo) == 0)
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
    // se o livro não for encontrado, retorna -1
    return -1;
}

// Busca um usuário pelo nome e copia os dados para usuarioEncontrado.
// Se o nome não for encontrado, exibe mensagem de erro.
void BuscarUsuarioPorNome(Usuario *usuarioEncontrado, char nome[8])
{
    int encontrado = 0;

    for (int i = 0; i < totalUsuarios; i++)
    {
        if (strcmp(nome, usuarios[i].nome) == 0)
        {
            *usuarioEncontrado = usuarios[i];
            encontrado = 1;
            break;
        }
    }
    if (encontrado != 1)
    {
        printf("O usuário %s não foi encontrado\n", nome);
        _getch();
    }
}

// Busca um usuário pela matrícula e copia os dados para usuarioEncontrado.
// Se a matrícula não for encontrada, exibe mensagem de erro.
void BuscarUsuarioPorMat(Usuario *usuarioEncontrado, char matricula[8])
{
    int encontrado = 0;
    for (int i = 0; i < totalUsuarios; i++)
    {
        if (strcmp(matricula, usuarios[i].matricula) == 0)
        {
            *usuarioEncontrado = usuarios[i];
            encontrado = 1;
            break;
        }
    }
    if (encontrado != 1)
    {
        printf("O usuário com a matrícula %s não foi encontrado\n", matricula);
        _getch();
    }
}

static void merge_livros(Livro *vet, Livro *tmp, int esq, int meio, int dir)
{
    int i = esq, j = meio + 1, k = esq;

    // Mescla as duas metades ordenadas em um vetor temporário
    while (i <= meio && j <= dir)
    {
        if (vet[i].total_emprestimos >= vet[j].total_emprestimos)
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