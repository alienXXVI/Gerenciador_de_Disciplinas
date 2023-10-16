#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lotes.h"
#include "sistema.h"

// Insere uma disciplina na lista (arquivo)
// Pré-condição: arq_disciplinas aberto para leitura
// Pós-condição: disciplina inserida no arquivo
void inserir_lote_disciplina(FILE *arq_disciplinas) {
    Disciplina *d = NULL;
    int coddisciplina;
    char *nome;
    int codcurso;
    int serie;

    coddisciplina = atoi(strtok(NULL, ";"));
    nome = strtok(NULL, ";");
    codcurso = atoi(strtok(NULL, ";"));
    serie = atoi(strtok(NULL, ";"));

    d = criar_disciplina(coddisciplina, nome, codcurso, serie);
    inserir_disciplina(arq_disciplinas, d);
    free(d);
}

// Insere um curso na lista (arquivo)
// Pré-condição: arq_cursos aberto para leitura
// Pós-condição: curso inserido no arquivo
void inserir_lote_curso(FILE *arq_cursos) {
    Curso *c = NULL;
    int codigo;
    char *nome;
    char area;

    codigo = atoi(strtok(NULL, ";"));
    nome = strtok(NULL, ";");
    area = *(strtok(NULL, ";"));

    c = criar_curso(codigo, nome, area);
    inserir_curso(arq_cursos, c);
    free(c);
}

// Insere um professor na lista (arquivo)
// Pré-condição: arq_professores aberto para leitura
// Pós-condição: professor inserido no arquivo
void inserir_lote_professor(FILE *arq_professores) {
    CadastroProfessor *cp = NULL;
    int codigo;
    char *nome;

    codigo = atoi(strtok(NULL, ";"));
    nome = strtok(NULL, ";");

    cp = criar_cadastro_professor(codigo, nome);
    inserir_cadastro_professor(arq_professores, cp);
    free(cp);
}

// Insere uma distribuição na lista (arquivo)
// Pré-condição: arq_professores_disciplinas aberto para leitura
// Pós-condição: distribuição inserida no arquivo
void inserir_lote_distribuicao(FILE *arq_professores_disciplinas, FILE *arq_disciplinas) {
    CadastroProfessorDisciplina *cpd = NULL;
    Disciplina *d = NULL;
    int codigo;
    int coddisciplina;
    int codcurso;
    int anoletivo;
    int codprofessor;

    coddisciplina = atoi(strtok(NULL, ";"));
    anoletivo = atoi(strtok(NULL, ";"));
    codprofessor = atoi(strtok(NULL, ";"));
    codigo = gerar_codigo_distribuicao(arq_professores_disciplinas);
    d = buscar_disciplina(arq_disciplinas, coddisciplina);
    codcurso = d->codcurso;

    cpd = criar_cadastro_professor_disciplina(codigo, coddisciplina, anoletivo, codprofessor);
    inserir_cadastro_professor_disciplina(arq_professores_disciplinas, arq_disciplinas, cpd);
    free(cpd);
    free(d);
}

// Lê o arquivo inteiro dado pela string
// Pré-condições: string contendo o nome do arquivo.extensão e arquivos abertos de cada estrutura
// Pós-condições: nenhuma
void ler_arq_txt(char *str, FILE *arq_disciplinas, FILE *arq_cursos, FILE *arq_professores, FILE *arq_professores_disciplinas) {
    FILE *arq_lotes = fopen(str, "r");
    char linha[1024];
    char *c_atual;
    char cadastro; // {Curso, Disciplina, Professor, Ministra}

    if(!arq_lotes) {
        printf("Erro ao abrir arquivo .txt\n");
        return;
    }

    while(fscanf(arq_lotes, "%[^\n]%*c", linha) != EOF) {
        cadastro = *(strtok(linha, ";"));

        switch (cadastro) {
            case 'D': // Curso
                inserir_lote_disciplina(arq_disciplinas);
                break;
            case 'C': // Disciplina
                inserir_lote_curso(arq_cursos);
                break;
            case 'P': // Professor
                inserir_lote_professor(arq_professores);
                break;
            case 'M': // Ministra
                inserir_lote_distribuicao(arq_professores_disciplinas, arq_disciplinas);
                break;

            default:
                break;
        }
    }
    
}