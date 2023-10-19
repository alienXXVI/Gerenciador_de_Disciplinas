#ifndef MENU
#define MENU

#include "sistema.h"

void menu_principal(FILE *arq_cursos, FILE *arq_disciplinas, FILE *arq_professores, FILE *arq_professores_disciplinas);

void cadastrar(FILE *arq_cursos, FILE *arq_disciplinas, FILE *arq_professores, FILE *arq_professores_disciplinas);

void cadastrar_curso(FILE *arq_cursos);

void cadastrar_disciplina(FILE *arq_disciplinas);

void cadastrar_professor(FILE* arq_professores);

void cadastrar_distribuicao(FILE *arq_professores_disciplinas, FILE *arq_disciplinas);

void imprimir(FILE *arq_cursos, FILE *arq_disciplinas, FILE *arq_professores, FILE *arq_professores_disciplinas);

void remover(FILE *arq_professores_disciplinas);

void carregar_lote(FILE *arq_cursos, FILE *arq_disciplinas, FILE *arq_professores, FILE *arq_professores_disciplinas);

#endif