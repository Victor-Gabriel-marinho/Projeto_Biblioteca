#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H


extern Emprestimo *emprestimos;
extern int totalEmprestimos;

void emp();
void addEmp();
void listEmp_atraso();
void regDev();
void listarEmp();
void listEmp_user(char matricula[8], Usuario *pessoa);
int validEmp_user(int id, char matricula[8], int *posicao_emprestimo);
void regisEmp(Usuario *pessoa, Livro *livro, char data[10]);



#endif