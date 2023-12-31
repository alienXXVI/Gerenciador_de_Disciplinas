#include <stdio.h>
#include "sistema.h"
#include "lotes.h"
#include "menu.h"

void imprimir_curso(Curso *c) {
    if(c == NULL) {
        printf("Estrutura vazia.\n");
        return;
    }
    printf("****** CURSO ********\n");
    printf("Codigo: %d\n"
            "Nome: %s\n"
            "Area: %c\n\n"
            , c->codigo, c->nome, c->area);
}

void imprimir_disciplina(Disciplina *d) {
    if(d == NULL) {
        printf("Estrutura vazia.\n");
        return;
    }
    printf("******** DISCIPLINA *********\n");
    printf("Codigo: %d\n"
            "Nome: %s\n"
            "Codigo do Curso: %d\n"
            "Serie: %d\n\n"
            , d->codigo, d->nome, d->codcurso, d->serie);
}

void imprimir_professor(CadastroProfessor *cp) {
    if(cp == NULL) {
        printf("Estrutura vazia.\n");
        return;
    }
    printf("******** PROFESSOR *********\n");
    printf("Codigo: %d\n"
            "Nome: %s\n\n"
            , cp->codigo, cp->nome);
}

void imprimir_distribuicao_disciplina(CadastroProfessorDisciplina *cpd) {
    if(cpd == NULL) {
        printf("Estrutura vazia.\n");
        return;
    }
    printf("******** DISTRIBUICAO DE DISCIPLINA *********\n");
    printf("Codigo: %d\n"
            "Codigo da Disciplina: %d\n"
            "Ano Letivo: %d\n"
            "Codigo do Professor: %d\n"
            "Codigo do Curso: %d\n\n"
            , cpd->codigo, cpd->coddisciplina, cpd->anoletivo, cpd->codprofessor, cpd->codcurso);
}

void resetar() {
    FILE *arq_disciplinas = fopen("disciplinas.bin", "w+b");
    FILE *arq_cursos = fopen("cursos.bin", "w+b");
    FILE *arq_professores = fopen("professores.bin", "w+b");
    FILE *arq_professores_disciplinas = fopen("professores_disciplinas.bin", "w+b");

    criar_cabecalho_vazio(arq_disciplinas);
    criar_cabecalho_vazio(arq_cursos);
    criar_cabecalho_vazio(arq_professores);
    criar_cabecalho_vazio(arq_professores_disciplinas);

    fclose(arq_disciplinas);
    fclose(arq_cursos);
    fclose(arq_professores);
    fclose(arq_professores_disciplinas);
}

int main() {
    FILE *arq_cursos = open_arq("cursos.bin");
    FILE *arq_disciplinas = open_arq("disciplinas.bin");
    FILE *arq_professores = open_arq("professores.bin");
    FILE *arq_professores_disciplinas = open_arq("professores_disciplinas.bin");

    menu_principal(arq_cursos, arq_disciplinas, arq_professores, arq_professores_disciplinas);
    fclose(arq_cursos);
    fclose(arq_disciplinas);
    fclose(arq_professores);
    fclose(arq_professores_disciplinas);

    // resetar();
    
    return 0;
}