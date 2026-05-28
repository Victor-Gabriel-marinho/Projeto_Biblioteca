#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/interface.h"
#include "../include/livros.h"
#include "../include/biblioteca.h"
#include "../include/algoritmos.h"
#include "../include/persistencia.h"
#include <string.h>

void AddLivros()
{
    srand(time(NULL));
    char tecla;
    Livro novoLivro;

    // Função de gerar o codigo do livro automaticamente
    gerarID(novoLivro.codigo);
    novoLivro.qtd_disponivel = 0;

    printf("=== ADICIONAR LIVRO ===\n\n");
    mostrarCursor();

    do
    {

        printf("Digite o título do livro: ");
        fgets(novoLivro.titulo, MAX_STRING, stdin);
        novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = '\0'; // Impedindo que o fgets pegue o Enter que o usuários digitar
        if (strlen(novoLivro.titulo) == 0)
        {
            printf("Título inválido! Tente novamente.\n");
        }

    } while (strlen(novoLivro.titulo) == 0);

    do
    {
        printf("Digite o nome do autor: ");
        fgets(novoLivro.autor, MAX_STRING, stdin);
        novoLivro.autor[strcspn(novoLivro.autor, "\n")] = '\0';

        if (strlen(novoLivro.autor) == 0)
            printf("Autor inválido! Tente novamente.\n");

    } while (strlen(novoLivro.autor) == 0);

    {
        char ano_str[MAX_STRING];
        int ano_valido = 0;

        do
        {
            printf("Digite o ano do livro: ");
            fgets(ano_str, MAX_STRING, stdin);
            ano_str[strcspn(ano_str, "\n")] = '\0';

            if (strlen(ano_str) == 0)
            {
                printf("Ano inválido! Tente novamente.\n");
            }
            else
            {
                char *endptr;
                long ano_convertido = strtol(ano_str, &endptr, 10);

                if (*endptr != '\0' || ano_convertido <= 0)
                {
                    printf("Ano inválido! Tente novamente.\n");
                }
                else
                {
                    novoLivro.ano = (size_t)ano_convertido;
                    ano_valido = 1;
                }
            }
        } while (!ano_valido);
    }

    do
    {
        printf("Digite o gênero do livro: ");
        fgets(novoLivro.genero, MAX_STRING, stdin);
        novoLivro.genero[strcspn(novoLivro.genero, "\n")] = '\0';

        if (strlen(novoLivro.genero) == 0)
            printf("Gênero inválido! Tente novamente.\n");
    } while (strlen(novoLivro.genero) == 0);

    while (1)
    {
        ocultarCursor();
        printf("=== Livro ===\n");
        printf("Código    : %s\n", novoLivro.codigo);
        printf("Título    : %s\n", novoLivro.titulo);
        printf("Autor     : %s\n", novoLivro.autor);
        printf("Ano       : %zu\n", novoLivro.ano);
        printf("Gênero    : %s\n", novoLivro.genero);
        printf("Disponível: %d\n\n", novoLivro.qtd_disponivel);
        printf("Pressione Enter para confirmar ou BackSpace para voltar");
        tecla = _getch();

        if (tecla == 8)
        {
            system("cls");
            break;
        }
        else if (tecla == 13)
        {
            FILE *livros = fopen("data\\livros.dat", "ab");

            if (livros == NULL)
            {
                printf("Erro ao abrir o arquivo");
                _getch();
                return;
            }
            fwrite(&novoLivro, sizeof(Livro), 1, livros);
            fclose(livros);
            printf("\nLivro salvo com sucesso!\nPressione qualquer tecla para sair\n");
            _getch();
            system("cls");
            break;
        }
    }
}

void ListLivros()
{
    FILE *arquivo = fopen("data\\livros.dat", "rb");
    if (arquivo == NULL)
    {
        printf("Não foi possível abrir o arquivo de livros.\n");
        _getch();
        return;
    }

    Livro livro;
    int contador = 0;

    while (fread(&livro, sizeof(Livro), 1, arquivo) == 1)
    {
        contador++;
        printf("=== Livro %d ===\n", contador);
        printf("Código    : %s\n", livro.codigo);
        printf("Título    : %s\n", livro.titulo);
        printf("Autor     : %s\n", livro.autor);
        printf("Ano       : %d\n", livro.ano);
        printf("Gênero    : %s\n", livro.genero);
        printf("Quantidade total     : %d\n", livro.qtd_total);
        printf("Quantidade disponível: %d\n", livro.qtd_disponivel);
        printf("Total de empréstimos : %d\n\n", livro.total_emprestimos);
    }

    if (contador == 0)
    {
        printf("Nenhum livro encontrado.\n");
    }

    fclose(arquivo);
    system("Pause");
}

void RemoverUsuario()
{
    char mat[8];
    char tecla;
    int encontrado = 0;
    Usuario usuarioEncontrado;
    Usuario temp;
    mostrarCursor();

    printf("=== REMOVER USUÁRIO ===\n\n");

    printf("Digite a matrícula do usuário que deseja remover: ");
    scanf("%s", mat);

    FILE *a = fopen("data\\usuarios.dat", "rb");
    if (a == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fread(&usuarioEncontrado, sizeof(Usuario), 1, a) == 1)
    {
        if (strcmp(usuarioEncontrado.matricula, mat) == 0)
        {
            encontrado = 1;
            break;
        }
    }
    fclose(a);

    if (encontrado != 1)
    {
        printf("Usuário com matrícula '%s' não encontrado.\n", mat);
        _getch();
        return;
    }

    printf("\nUsuário encontrado:\n");
    printf("Matrícula: %s\n", usuarioEncontrado.matricula);
    printf("Nome: %s\n", usuarioEncontrado.nome);

    printf("\nEsse é o usuário que você quer excluir?\n");
    printf(" Enter     - Sim\n");
    printf(" Backspace - Não\n");

    tecla = _getch();
    if (tecla == 8)
    {

        system("cls");
        return;
    }
    else if (tecla != 13)
    {
        return;
    }

    FILE *original = fopen("data\\usuarios.dat", "rb");
    FILE *temporario = fopen("data\\usuarios_temp.dat", "wb");

    if (original == NULL || temporario == NULL)
    {
        printf("Erro ao abrir arquivos para remoção.\n");
        return;
    }

    while (fread(&temp, sizeof(Usuario), 1, original))
    {
        // Copia todos EXCETO o que tem a matrícula informada
        if (strcmp(temp.matricula, mat) != 0)
        {
            fwrite(&temp, sizeof(Usuario), 1, temporario);
        }
    }

    fclose(original);
    fclose(temporario);

    // Substitui o original pelo temporário
    remove("data\\usuarios.dat");
    rename("data\\usuarios_temp.dat", "data\\usuarios.dat");

    printf("\nUsuário removido com sucesso!\n");
    _getch();
    system("cls");
}

void BuscarPorNome(char nome[100])
{
    FILE *f = fopen("data\\usuarios.dat", "rb");
    if (f == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        _getch();
        return;
    }

    Usuario u;
    int encontrado = 0;
    while (fread(&u, sizeof(Usuario), 1, f) == 1)
    {
        if (strcmp(nome, u.nome) == 0)
        {
            printf("=== Usuário ===\n");
            printf("Matrícula : %s\n", u.matricula);
            printf("Nome      : %s\n", u.nome);
            printf("Curso     : %s\n", u.curso);
            printf("Empréstimos ativos: %d\n\n", u.qtd_emprestimos_ativos);
            encontrado = 1;
            printf("Digite qualquer tecla para voltar\n");
            _getch();
            break;
        }
    }
    fclose(f);
    if (encontrado != 1)
    {
        printf("O usuário %s não foi encontrado\n", nome);
        _getch();
    }
}

void BuscaPorMat(char matricula[7])
{
    FILE *f = fopen("data\\usuarios.dat", "rb");
    if (f == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        _getch();
        return;
    }

    Usuario u;
    int encontrado = 0;
    while (fread(&u, sizeof(Usuario), 1, f) == 1)
    {
        if (strcmp(matricula, u.matricula) == 0)
        {
            printf("=== Usuário ===\n");
            printf("Matrícula : %s\n", u.matricula);
            printf("Nome      : %s\n", u.nome);
            printf("Curso     : %s\n", u.curso);
            printf("Empréstimos ativos: %d\n\n", u.qtd_emprestimos_ativos);
            encontrado = 1;
            printf("Digite qualquer tecla para voltar\n");
            _getch();
            break;
        }
    }
    fclose(f);
    if (encontrado != 1)
    {
        printf("O usuário com a matrícula %s não foi encontrado\n", matricula);
        _getch();
    }
}

void BuscarUsuarios()
{
    char opcoes[3][30] = {"Buscar por nome", "Buscar por matricula", "Voltar"};

    while (1)
    {
        int posicaoAtual = criarMenu("TELA DE BUSCA", opcoes, 3);

        // Busca por nome
        if (posicaoAtual == 0)
        {
            mostrarCursor();
            char nome[100];
            printf("Digite o nome do usuário: ");
            fgets(nome, 100, stdin);
            nome[strcspn(nome, "\n")] = '\0';
            BuscarPorNome(nome);
        }
        else if (posicaoAtual == 1)
        {
            // Busca por matricula
            mostrarCursor();
            char matricula[100];
            printf("Digite o nome do usuário: ");
            fgets(matricula, 100, stdin);
            matricula[strcspn(matricula, "\n")] = '\0';
            BuscaPorMat(matricula);
        }
        else if (posicaoAtual == 2)
        {
            system("cls");
            break;
        }
    }
}

void EditarUsuario()
{
    char mat[8];
    char tecla;
    int encontrado = 0;
    Usuario usuarioEncontrado;
    Usuario temp;
    Usuario usuarioEditado;
    mostrarCursor();

    printf("=== EDITAR USUÁRIO ===\n\n");

    printf("Digite a matrícula do usuário que deseja editar: ");
    scanf("%s", mat);

    FILE *a = fopen("data\\usuarios.dat", "rb");
    if (a == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fread(&usuarioEncontrado, sizeof(Usuario), 1, a) == 1)
    {
        if (strcmp(usuarioEncontrado.matricula, mat) == 0)
        {
            encontrado = 1;
            break;
        }
    }
    fclose(a);

    if (encontrado != 1)
    {
        printf("Usuário com matrícula '%s' não encontrado.\n", mat);
        _getch();
        return;
    }
    ocultarCursor();
    printf("\nUsuário encontrado:\n");
    printf("Matrícula: %s\n", usuarioEncontrado.matricula);
    printf("Nome: %s\n", usuarioEncontrado.nome);
    printf("Curso: %s\n", usuarioEncontrado.curso);

    printf("\nEsse é o usuário que você quer Editar?\n");
    printf(" Enter     - Sim\n");
    printf(" Backspace - Não\n");

    tecla = _getch();
    if (tecla == 8)
    {
        system("cls");
        return;
    }
    else if (tecla != 13)
    {
        return;
    }
    getchar();
    mostrarCursor();
    printf("\nDigite o novo nome\n");
    printf("ou pressione Enter para manter o anterior\n");
    fgets(usuarioEditado.nome, MAX_STRING, stdin);
    usuarioEditado.nome[strcspn(usuarioEditado.nome, "\n")] = '\0';

    printf("\nDigite o novo curso\n");
    printf("ou pressione Enter para manter o anterior\n");
    fgets(usuarioEditado.curso, MAX_STRING, stdin);
    usuarioEditado.nome[strcspn(usuarioEditado.nome, "\n")] = '\0';

    if (strlen(usuarioEditado.nome) == 1)
    {
        strcpy(usuarioEditado.nome, usuarioEncontrado.nome);
    }
    if (strlen(usuarioEditado.curso) == 1)
    {
        strcpy(usuarioEditado.curso, usuarioEncontrado.curso);
    }

    strcpy(usuarioEditado.matricula, usuarioEncontrado.matricula);
    usuarioEditado.qtd_emprestimos_ativos = usuarioEncontrado.qtd_emprestimos_ativos;

    FILE *original = fopen("data\\usuarios.dat", "rb");
    FILE *temporario = fopen("data\\usuarios_temp.dat", "wb");

    if (original == NULL || temporario == NULL)
    {
        printf("Erro ao abrir arquivos para remoção.\n");
        return;
    }

    while (fread(&temp, sizeof(Usuario), 1, original))
    {
        if (strcmp(temp.matricula, usuarioEncontrado.matricula) == 0)
        {

            // Se a matrícula for igual ao encontrado ele escreve o novo usuário
            fwrite(&usuarioEditado, sizeof(Usuario), 1, temporario);
        }
        else
        {

            // Se for diferente ele escreve oque ja tinha
            fwrite(&temp, sizeof(Usuario), 1, temporario);
        }
    }
    fcloseall();

    remove("data\\usuarios.dat");
    rename("data\\usuarios_temp.dat", "data\\usuarios.dat");

    printf("\nUsuário editado com sucesso!\n");
    _getch();
    system("cls");
}

void Users()
{

    // Criando opções da tela de gerenciamento de usuários
    char opcoes[6][30] = {"Adicionar Usuário", "Listar Usuários", "Buscar usuário", "Remover Usuário", "Editar usuário", "Voltar"};

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
}