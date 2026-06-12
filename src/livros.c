#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/interface.h"
#include "../include/biblioteca.h"
#include "../include/algoritmos.h"
#include "../include/persistencia.h"
#include "../include/livros.h"
#include <string.h>

void AddLivros()
{
    srand(time(NULL));
    char tecla;
    Livro novoLivro;

    gerarID(novoLivro.codigo);
    novoLivro.qtd_disponivel = 0;

    printf("=== ADICIONAR LIVRO ===\n\n");
    mostrarCursor(); 

    do
    {
        printf("Digite o título do livro: ");
        fgets(novoLivro.titulo, MAX_STRING, stdin);
        novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = '\0';
        if (strlen(novoLivro.titulo) == 0)
        {
            printf("Título inválido! Tente novamente.\n");
        }
    } while (strlen(novoLivro.titulo) == 0 || strcmp(novoLivro.titulo, " ") == 0);

    do
    {
        printf("Digite o nome do autor: ");
        fgets(novoLivro.autor, MAX_STRING, stdin);
        novoLivro.autor[strcspn(novoLivro.autor, "\n")] = '\0';
        if (strlen(novoLivro.autor) == 0)
        {
            printf("Autor inválido! Tente novamente.\n");
        }
    } while (strlen(novoLivro.autor) == 0 || strcmp(novoLivro.autor, " ") == 0);

 do
    {
        printf("Digite o gênero do livro: ");
        fgets(novoLivro.genero, MAX_STRING, stdin);
        novoLivro.genero[strcspn(novoLivro.genero, "\n")] = '\0';
        
        if (strlen(novoLivro.genero) == 0)
        {
            printf("Gênero inválido! Tente novamente.\n");
        }
    } while (strlen(novoLivro.genero) == 0 || strcmp(novoLivro.genero, " ") == 0);

    {
        int ano = 0;
        int ano_valido = 0;

        do
        {
            printf("Digite o ano do livro: ");
            scanf("%d", &novoLivro.ano);  
            if (novoLivro.ano == 0)
            {
                printf("Ano inválido! Tente novamente.\n");
            }
            else
            {
                ano_valido = 1;
            }
        } while (!ano_valido && getchar() != '\n');
    }

    {   
        int qtd_total = 0;
        int qtd_valida = 0;

        do
        {
            printf("Digite a quantidade total de exemplares do livro: ");
            scanf("%d", &novoLivro.qtd_total);   
            if (novoLivro.qtd_total == 0)
            {
                printf("Quantidade inválida! Tente novamente.\n");
            }
            else
            {
                qtd_valida = 1;
                novoLivro.qtd_disponivel = novoLivro.qtd_total;
            }
        } while (!qtd_valida);
    }

    while (1)
    {
        ocultarCursor();
        printf("=== Livro ===\n");
        printf("Código    : %s\n", novoLivro.codigo);
        printf("Título    : %s\n", novoLivro.titulo);
        printf("Autor     : %s\n", novoLivro.autor);
        printf("Ano       : %zu\n", novoLivro.ano);
        printf("Gênero    : %s\n", novoLivro.genero);
        printf("Disponível: %d\n\n", novoLivro.qtd_total);
        printf("Pressione Enter para confirmar ou BackSpace para voltar");
        tecla = _getch();

        if (tecla == 8)
        {
            system("cls");
            break;
        }
        else if (tecla == 13)
        {
           
            Livro *temp = realloc(livros, (totalLivros + 1) * sizeof(Livro));
            if (temp == NULL)
            {
                printf("Erro: falha ao alocar memória!\n");
                free(livros);
                return;
            }

            livros = temp;
            livros[totalLivros] = novoLivro;
            totalLivros++;

            SalvarLivros(livros, totalLivros);   
            printf("\nLivro salvo com sucesso!\nPressione qualquer tecla para sair\n");
            _getch();
            system("cls");
            break;
        }
    }
}
void listLivros()
{
    printf("\n============================== LISTA DE LIVROS ==============================\n\n");

    for (int i = 0; i < totalLivros; i += 1)
    {
        int colunas = totalLivros - i;
        if (colunas > 1)
            colunas = 1;

        // Cabeçalho
            printf("=== Livro %d ===\t\t", i + 1);
        printf("\n");

        // Código
            printf("Codigo: %-40.40s", livros[i].codigo);
        printf("\n");

        // Título
            printf("Titulo: %-50.50s", livros[i].titulo);
        printf("\n");

        // Autor
            printf("Autor : %-50.50s", livros[i].autor);
        printf("\n");

        // Ano
            printf("Ano   : %-40d", livros[i].ano);
        printf("\n");

        // Gênero
            printf("Genero: %-50.50s", livros[i].genero);
        printf("\n");

        // Quantidade total
            printf("Total : %-50d", livros[i].qtd_total);
        printf("\n");

        // Quantidade disponível
            printf("Disp. : %-50d", livros[i].qtd_disponivel);
        printf("\n\n");
    }

    system("pause");
}

 void RemoverLivro()
{
    char cod[8];
    char tecla;
    int encontrado = 0;
    int pos = -1;
    Livro livroEncontrado;

    mostrarCursor();

    printf("=== REMOVER LIVRO ===\n\n");

    printf("Digite o código do livro que deseja remover: ");
    scanf("%7s", cod);

    encontrado = busca_livroCodigo(&livroEncontrado, cod);

    if (encontrado == 0)
    {
        printf("\nLivro com o código %s não encontrado!\n", cod);
        _getch();
        return;
    }

    printf("\nLivro encontrado:\n");
    printf("Código: %s\n", livroEncontrado.codigo);
    printf("Título: %s\n", livroEncontrado.titulo);

    printf("\nEsse é o livro que você quer excluir?\n");
    printf("Enter     - Sim\n");
    printf("Backspace - Não\n");

    tecla = _getch();

    if (tecla == 8) // Backspace
    {
        system("cls");
        return;
    }

    if (tecla != 13) // Enter
    {
        return;
    }

    /* Procura a posição do livro no vetor */
    for (int i = 0; i < totalLivros; i++)
    {
        if (strcmp(livros[i].codigo, cod) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("\nErro ao localizar o livro no vetor!\n");
        _getch();
        return;
    }

    /* Desloca os elementos uma posição para a esquerda */
    for (int i = pos; i < totalLivros - 1; i++)
    {
        livros[i] = livros[i + 1];
    }

    totalLivros--;

    /* Redimensiona o vetor */
    if (totalLivros > 0)
    {
        Livro *temp = realloc(livros, totalLivros * sizeof(Livro));

        if (temp != NULL)
        {
            livros = temp;
        }
    }
    else
    {
        free(livros);
        livros = NULL;
    }

    SalvarLivros(livros, totalLivros);

    printf("\nLivro removido com sucesso!\n");

    _getch();
    system("cls");
}

void BuscarLivro()
{
    char opcoes[3][30] = {"Buscar por nome", "Buscar por código", "Voltar"};

    while (1)
    {
        int posicaoAtual = criarMenu("TELA DE BUSCA", opcoes, 3);

        // Busca por nome
        if (posicaoAtual == 0)
        {
            mostrarCursor();
            char titulo[MAX_STRING];
            int result;
            Livro livroEncontrado;

            printf("Digite o título do livro: ");
            fgets(titulo, MAX_STRING, stdin);
            titulo[strcspn(titulo, "\n")] = '\0';

            result = BuscarLivroPorTitulo(&livroEncontrado, titulo);
          if (result == 0)
        {
            printf("Livro não encontrado!\n");
            _getch();
            continue;
           }

            printf("=== Livro ===\n");
            printf("Código : %s\n", livroEncontrado.codigo);
            printf("Título : %s\n", livroEncontrado.titulo);
            printf("Autor  : %s\n", livroEncontrado.autor);
            printf("Gênero : %s\n", livroEncontrado.genero);
            printf("Ano    : %d\n", livroEncontrado.ano);
         printf("Disponível: %d\n", livroEncontrado.qtd_disponivel);
         printf("Acervo total: %d\n", livroEncontrado.qtd_total);
        

            printf("Digite qualquer tecla para voltar\n");
            _getch();
        }

        // Busca por código
        else if (posicaoAtual == 1)
        {
            mostrarCursor();

            Livro livroEncontrado;
            char codigo[8];
            int result = 0;

            printf("Digite o código do livro: ");
            fgets(codigo, 8, stdin);
            codigo[strcspn(codigo, "\n")] = '\0';

            result = busca_livroCodigo(&livroEncontrado, codigo);
           if (result == 0)
           {
            printf("Livro não encontrado!\n");
            _getch();
            continue;
        }

            printf("=== Livro ===\n");
            printf("Código : %s\n", livroEncontrado.codigo);
            printf("Título : %s\n", livroEncontrado.titulo);
            printf("Autor  : %s\n", livroEncontrado.autor);
            printf("Gênero : %s\n", livroEncontrado.genero);
            printf("Ano    : %d\n", livroEncontrado.ano);
            printf("Disponível: %d\n", livroEncontrado.qtd_disponivel);
            printf("Acervo total: %d\n", livroEncontrado.qtd_total);
            printf("Digite qualquer tecla para voltar\n");
            _getch();
        }
        else if (posicaoAtual == 2)
        {
            system("cls");
            break;
        }
    }
}
// void EditarUsuario()
// {
//     char mat[8];
//     char tecla;
//     int encontrado = 0;
//     Usuario usuarioEncontrado;
//     Usuario temp;
//     Usuario usuarioEditado;
//     mostrarCursor();

//     printf("=== EDITAR USUÁRIO ===\n\n");

//     printf("Digite a matrícula do usuário que deseja editar: ");
//     scanf("%s", mat);

//     FILE *a = fopen("data\\usuarios.dat", "rb");
//     if (a == NULL)
//     {
//         printf("Erro ao abrir o arquivo.\n");
//         return;
//     }

//     while (fread(&usuarioEncontrado, sizeof(Usuario), 1, a) == 1)
//     {
//         if (strcmp(usuarioEncontrado.matricula, mat) == 0)
//         {
//             encontrado = 1;
//             break;
//         }
//     }
//     fclose(a);

//     if (encontrado != 1)
//     {
//         printf("Usuário com matrícula '%s' não encontrado.\n", mat);
//         _getch();
//         return;
//     }
//     ocultarCursor();
//     printf("\nUsuário encontrado:\n");
//     printf("Matrícula: %s\n", usuarioEncontrado.matricula);
//     printf("Nome: %s\n", usuarioEncontrado.nome);
//     printf("Curso: %s\n", usuarioEncontrado.curso);

//     printf("\nEsse é o usuário que você quer Editar?\n");
//     printf(" Enter     - Sim\n");
//     printf(" Backspace - Não\n");

//     tecla = _getch();
//     if (tecla == 8)
//     {
//         system("cls");
//         return;
//     }
//     else if (tecla != 13)
//     {
//         return;
//     }
//     getchar();
//     mostrarCursor();
//     printf("\nDigite o novo nome\n");
//     printf("ou pressione Enter para manter o anterior\n");
//     fgets(usuarioEditado.nome, MAX_STRING, stdin);
//     usuarioEditado.nome[strcspn(usuarioEditado.nome, "\n")] = '\0';

//     printf("\nDigite o novo curso\n");
//     printf("ou pressione Enter para manter o anterior\n");
//     fgets(usuarioEditado.curso, MAX_STRING, stdin);
//     usuarioEditado.nome[strcspn(usuarioEditado.nome, "\n")] = '\0';

//     if (strlen(usuarioEditado.nome) == 1)
//     {
//         strcpy(usuarioEditado.nome, usuarioEncontrado.nome);
//     }
//     if (strlen(usuarioEditado.curso) == 1)
//     {
//         strcpy(usuarioEditado.curso, usuarioEncontrado.curso);
//     }

//     strcpy(usuarioEditado.matricula, usuarioEncontrado.matricula);
//     usuarioEditado.qtd_emprestimos_ativos = usuarioEncontrado.qtd_emprestimos_ativos;

//     FILE *original = fopen("data\\usuarios.dat", "rb");
//     FILE *temporario = fopen("data\\usuarios_temp.dat", "wb");

//     if (original == NULL || temporario == NULL)
//     {
//         printf("Erro ao abrir arquivos para remoção.\n");
//         return;
//     }

//     while (fread(&temp, sizeof(Usuario), 1, original))
//     {
//         if (strcmp(temp.matricula, usuarioEncontrado.matricula) == 0)
//         {

//             // Se a matrícula for igual ao encontrado ele escreve o novo usuário
//             fwrite(&usuarioEditado, sizeof(Usuario), 1, temporario);
//         }
//         else
//         {

//             // Se for diferente ele escreve oque ja tinha
//             fwrite(&temp, sizeof(Usuario), 1, temporario);
//         }
//     }
//     fcloseall();

//     remove("data\\usuarios.dat");
//     rename("data\\usuarios_temp.dat", "data\\usuarios.dat");

//     printf("\nUsuário editado com sucesso!\n");
//     _getch();
//     system("cls");
// }

void Livros()
{

    // Criando opções da tela de gerenciamento de livros
    char opcoes[6][30] = {"Adicionar Livro", "Listar Livros", "Buscar Livro", "Remover Livro", "Editar Livro", "Voltar"};

    while (1)
    {
        // Função para criar interface
        int posicaoAtual = criarMenu("TELA DE LIVROS", opcoes, 6);

        if (posicaoAtual == 0)
        {
            // Função de adicionar livros
           AddLivros(); 
        }
        else if (posicaoAtual == 1)
        {
            // Função de listar livros
            listLivros();
            
        }
        else if (posicaoAtual == 2)
        {
            // Função de buscar livros por código
            BuscarLivro();
        }
        else if (posicaoAtual == 3)
        {
            // Função de remover usuario através da matrícula
            RemoverLivro();
        }
        else if (posicaoAtual == 4)
        {
            // Função de editar usuario através da matrícula
            
        }
        else if (posicaoAtual == 5)
        {
            system("cls");
            break;
        }
        system("cls");
    }
}