#include <stdio.h>
#include "sistema.h"

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
            "Codigo do Professor: %d\n\n"
            , cpd->codigo, cpd->coddisciplina, cpd->anoletivo, cpd->codprofessor);
}

int main() {
    Curso *c1 = criar_curso(1, "Ciencia da Computacao", 'E');
    Curso *c2 = criar_curso(2, "Matematica", 'E');
    Curso *c3 = criar_curso(3, "Historia", 'H');

    CadastroProfessor *cp1 = criar_cadastro_professor(1, "Jose de Brito");
    CadastroProfessor *cp2 = criar_cadastro_professor(2, "Maria Silva");

    CadastroProfessorDisciplina *cpd1 = criar_cadastro_professor_disciplina(1, 10, 2023, 1);
    CadastroProfessorDisciplina *cpd2 = criar_cadastro_professor_disciplina(2, 11, 2022, 2);

    FILE *arq_disciplinas = fopen("disciplinas.bin", "w+b");
    FILE *arq_cursos = fopen("cursos.bin", "w+b");
    FILE *arq_professores = fopen("professores.bin", "w+b");
    FILE *arq_professores_disciplinas = fopen("professores_disciplinas.bin", "w+b");


    criar_cabecalho_vazio(arq_cursos);
    inserir_curso(arq_cursos, c1);
    inserir_curso(arq_cursos, c2);
    inserir_curso(arq_cursos, c3);
    imprimir_cursos(arq_cursos);

    Disciplina *d = criar_disciplina(1, "Matematica", 1, 1);
    Disciplina *d2 = criar_disciplina(2, "Ciencia", 4, 1);

    criar_cabecalho_vazio(arq_disciplinas);
    inserir_disciplina(arq_disciplinas, d);
    inserir_disciplina(arq_disciplinas, d2);
    imprimir_disciplinas(arq_disciplinas);
    fclose(arq_disciplinas);
    fclose(arq_cursos);

    criar_cabecalho_vazio(arq_professores);
    inserir_cadastro_professor(arq_professores, cp1);
    inserir_cadastro_professor(arq_professores, cp2);
    imprimir_cadastros_professor(arq_professores);
    fclose(arq_professores);

    criar_cabecalho_vazio(arq_professores_disciplinas);
    inserir_cadastro_professor_disciplina(arq_professores_disciplinas, cpd1);
    inserir_cadastro_professor_disciplina(arq_professores_disciplinas, cpd2);
    imprimir_cadastros_professor_disciplina(arq_professores_disciplinas);
    fclose(arq_professores_disciplinas);

    return 0;
}