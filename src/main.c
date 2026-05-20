#include <stdio.h>

int main(){

    int cont = -1; // inicializando com -1 para evitar que pegue lixo de memoria e inicialize com 0, pois não entraria no While.
    while (cont != 0){
    
    printf("Qual ação voce quer fazer? \n 1 - Gerenciar livros \n 2 - Gerenciar usuarios \n 3 - Gerenciar emprestimos ou devolucoes \n 0 - Sair \n");

    printf("Sua opcao: ");
    scanf("%d", cont);
    
    switch(cont){
        case 0:
            break;
        case 1:
            gerenciar_livros(); // Chama a função que vai conter a parte de gerenciamento de livros
        case 2:
            gerenciar_usuario(); // Chama a função que vai conter a parte de gerenciamento de usuario
        case 3:
            gerenciar_emprestimo(); // Chama a função que vai conter a parte de gerenciamento de emprestimo
        default:
        printf("Opcao invalida! \n"); // Quebra o loop pra encerrar o programa
        
    }

}

    return 0;
}
