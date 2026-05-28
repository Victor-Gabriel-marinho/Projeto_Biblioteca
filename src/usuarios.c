#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/interface.h"
#include "../include/Users.h"
#include "../include/biblioteca.h"
#include "../include/algoritmos.h"
#include "../include/persistencia.h"

Usuario *usuarios = NULL;
int totalUsuarios = 0;

void AddUsers()
{
    srand(time(NULL));
    char tecla;
    Usuario novoAluno;

    // Função de gerar matricula automaticamente
    gerarID(novoAluno.matricula);
    novoAluno.qtd_emprestimos_ativos = 0;

    printf("=== ADICIONAR USUÁRIO ===\n\n");
    mostrarCursor();

    do
    {

        printf("Digite o nome do usuário: ");
        fgets(novoAluno.nome, MAX_STRING, stdin);
        novoAluno.nome[strcspn(novoAluno.nome, "\n")] = '\0'; // Impedindo que o fgets pegue o Enter que o usuários digitar
        if (strlen(novoAluno.nome) == 0)
        {
            printf("Nome inválido! Tente novamente.\n");
        }

    } while (strlen(novoAluno.nome) == 0);

    do
    {
        printf("Digite o curso do usuário: ");
        fgets(novoAluno.curso, MAX_STRING, stdin);
        novoAluno.curso[strcspn(novoAluno.curso, "\n")] = '\0';

        if (strlen(novoAluno.curso) == 0)
            printf("Curso inválido! Tente novamente.\n");

    } while (strlen(novoAluno.curso) == 0);

    while (1)
    {
        ocultarCursor();
        printf("=== Usuário ===\n");
        printf("Matrícula : %s\n", novoAluno.matricula);
        printf("Nome      : %s\n", novoAluno.nome);
        printf("Curso     : %s\n", novoAluno.curso);
        printf("Empréstimos ativos: %d\n\n", novoAluno.qtd_emprestimos_ativos);
        printf("Pressione Enter para confirmar ou BackSpace para voltar");
        tecla = _getch();

        if (tecla == 8)
        {
            system("cls");
            break;
        }
        else if (tecla == 13)
        {
            FILE *usuarios = fopen("data\\usuarios.dat", "ab");

            if (usuarios == NULL)
            {
                printf("Erro ao abrir o arquivo");
                _getch();
                return;
            }
            // Inserindo novo usuário no arquivo
            fwrite(&novoAluno, sizeof(Usuario), 1, usuarios);
            fclose(usuarios);
            printf("\nUsuário salvo com sucesso!\nPressione qualquer tecla para sair\n");
            _getch();
            system("cls");
            break;
        }
    }
}

void listUsers()
{
    // Percorrendo o arquivo de usuários
    for (int i = 0; i < totalUsuarios; i++)
    {
        printf("=== Usuário %d ===\n", i + 1);
        printf("Matrícula : %s\n", usuarios[i].matricula);
        printf("Nome      : %s\n", usuarios[i].nome);
        printf("Curso     : %s\n", usuarios[i].curso);
        printf("Empréstimos ativos: %d\n\n", usuarios[i].qtd_emprestimos_ativos);
    }
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
    usuarios = CarregarUsuarios(&totalUsuarios);

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

