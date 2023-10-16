#include <stdlib.h>
#include <string.h>
#include "sistema.h"
#include "lotes.h"

// ------------------------------- Arquivo -------------------------------

// Verifica se o cabeçalho (a lista) é vazia
// Entrada: cabeçalho
// Saída: é vazia (1) ou não é vazia (0)
int vazia(Cabecalho *cab) {
    return cab->pos_cabeca == -1;
}

// Cria uma lista (cabeçalho) nova em arquivo, podendo ser de Curso, Disciplina,
// CadastroProfessor ou CadastroProfessorDisciplina
// Pré-condição: arquivo aberto para leitura/escrita
// Pós-condição: arquivo é inicializado com uma lista vazia
void criar_cabecalho_vazio(FILE* arq){
    Cabecalho *cab = (Cabecalho*) malloc(sizeof(Cabecalho));

    cab->pos_cabeca = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;
    escrever_cabecalho(arq, cab);
    free(cab);
}

// Lê o cabeçalho do arquivo contendo as informações da lista
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: retorna o ponteiro para o cabeçalho lido
Cabecalho* ler_cabecalho(FILE *arq) {
    Cabecalho *cab = (Cabecalho*) malloc(sizeof(Cabecalho));
    
    fseek(arq, 0, SEEK_SET); // posiciona no in´ıcio do arquivo
    fread(cab, sizeof(Cabecalho), 1, arq);
    return cab;
}

// Escreve no arquivo o cabeçalho contendo as informações da lista
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: cabeçalho escrito no arquivo
void escrever_cabecalho(FILE *arq, Cabecalho *cab){
    fseek(arq, 0, SEEK_SET); // posiciona no início do arquivo
    fwrite(cab, sizeof(Cabecalho), 1, arq);
}

void imprimir_cabecalho(Cabecalho *cab) {
    printf("---- CABECALHO ----\n");
    printf("Cabeca: %d\n"
            "Topo: %d\n"
            "Livre: %d\n",
        cab->pos_cabeca, cab->pos_topo, cab->pos_livre);
}

// Abre arquivo
// Pré-condição: string contendo o nome do arquivo.extensão
// Pós-condição: retorna arquivo aberto
FILE* open_arq(char* str){
    FILE* arq = fopen(str, "r+b");

    if(arq == NULL){
        arq = fopen(str, "w+b");
        Cabecalho* cab = (Cabecalho*) malloc(sizeof(Cabecalho));
        cab->pos_cabeca = -1;
        cab->pos_livre = -1;
        cab->pos_topo = 0;
        escrever_cabecalho(arq, cab);
        free(cab);
    }
    return arq;
}

// --------------------------- Sistema ---------------------------

// Cria uma Disciplina contendo os dados fornecidos
// Pré-condição: o código fornecido deve ser diferente para o mesmo curso
// Pós-condição: retorna ponteiro para Disciplina
Disciplina* criar_disciplina(int codigo, char *nome, int codcurso, int serie) {
    Disciplina *d = (Disciplina*) malloc(sizeof(Disciplina));

    d->codigo = codigo;
    strcpy(d->nome, nome);
    d->codcurso = codcurso;
    d->serie = serie;
    return d;
}

// Cria um Curso contendo os dados fornecidos
// Pré-condição: o código fornecido deve ser diferente de outro curso,
//      area deve ser 'E' (Exatas), 'H' (Humanas) ou 'B' (Biológicas)
// Pós-condição: retorna ponteiro para Curso
Curso* criar_curso(int codigo, char *nome, char area) {
    Curso *c = (Curso*) malloc(sizeof(Curso));

    c->codigo = codigo;
    strcpy(c->nome, nome);
    c->area = area;
    return c;
}

// Cria um CadastroProfessor contendo os dados fornecidos
// Pré-condição: o código fornecido deve ser diferente de outro professor
// Pós-condição: retorna ponteiro para CadastroProfessor
CadastroProfessor* criar_cadastro_professor(int codigo, char *nome) {
    CadastroProfessor *cp = (CadastroProfessor*) malloc(sizeof(CadastroProfessor));

    cp->codigo = codigo;
    strcpy(cp->nome, nome);
    return cp;
}

// Cria um CadastroProfessorDisciplina contendo os dados fornecidos
// Pré-condição: os códigos fornecidos devem ser válidos
// Pós-condição: retorna ponteiro para CadastroProfessorDisciplina
CadastroProfessorDisciplina* criar_cadastro_professor_disciplina(int codigo, int coddisciplina, int anoletivo, int codprofessor) {
    CadastroProfessorDisciplina *cpd = (CadastroProfessorDisciplina*) malloc(sizeof(CadastroProfessorDisciplina));

    cpd->codigo = codigo;
    cpd->coddisciplina = coddisciplina;
    cpd->anoletivo = anoletivo;
    cpd->codprofessor = codprofessor;
    return cpd;
}

// Insere o nó na lista do arquivo
// Pré-condição: arquivo deve estar aberto para escrita
// Pós-condição: arquivo com novo nó
void inserir_disciplina(FILE *arq, Disciplina *d) {
    Cabecalho *cab = ler_cabecalho(arq);

    d->prox = cab->pos_cabeca;
    cab->pos_cabeca = cab->pos_topo;
    fseek(arq, sizeof(Cabecalho) + sizeof(Disciplina) * cab->pos_topo, SEEK_SET);
    fwrite(d, sizeof(Disciplina), 1, arq);
    cab->pos_topo++;
    escrever_cabecalho(arq, cab);
    free(cab);
    free(d);
}

// Insere o nó na lista do arquivo
// Pré-condição: arquivo deve estar aberto para escrita
// Pós-condição: arquivo com novo nó
void inserir_curso(FILE *arq, Curso *c) {
    Cabecalho *cab = ler_cabecalho(arq);

    c->prox = cab->pos_cabeca;
    cab->pos_cabeca = cab->pos_topo;
    fseek(arq, sizeof(Cabecalho) + sizeof(Curso) * cab->pos_topo, SEEK_SET);
    fwrite(c, sizeof(Curso), 1, arq);
    cab->pos_topo++;
    escrever_cabecalho(arq, cab);
    free(cab);
    free(c);
}

// Insere o nó na lista do arquivo
// Pré-condição: arquivo deve estar aberto para escrita
// Pós-condição: arquivo com novo nó
void inserir_cadastro_professor(FILE *arq, CadastroProfessor *cp) {
    Cabecalho *cab = ler_cabecalho(arq);

    cp->prox = cab->pos_cabeca;
    cab->pos_cabeca = cab->pos_topo;
    fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessor) * cab->pos_topo, SEEK_SET);
    fwrite(cp, sizeof(CadastroProfessor), 1, arq);
    cab->pos_topo++;
    escrever_cabecalho(arq, cab);
    free(cab);
    free(cp);
}

// Insere o nó na lista do arquivo
// Pré-condição: arquivo deve estar aberto para escrita
// Pós-condição: arquivo com novo nó
void inserir_cadastro_professor_disciplina(FILE *arq_professores_disciplinas, FILE *arq_disciplinas, CadastroProfessorDisciplina *cpd) {
    Cabecalho *cab = ler_cabecalho(arq_professores_disciplinas);
    printf("cpd->coddisciplina: %d\n", cpd->coddisciplina);
    Disciplina *d = buscar_disciplina(arq_disciplinas, cpd->coddisciplina);

    cpd->codcurso = d->codcurso;

    cpd->prox = cab->pos_cabeca;
    cab->pos_cabeca = cab->pos_topo;
    fseek(arq_professores_disciplinas, sizeof(Cabecalho) + sizeof(CadastroProfessorDisciplina) * cab->pos_topo, SEEK_SET);
    fwrite(cpd, sizeof(CadastroProfessorDisciplina), 1, arq_professores_disciplinas);
    cab->pos_topo++;
    escrever_cabecalho(arq_professores_disciplinas, cab);
    free(cab);
    free(cpd);
    free(d);
}

// Busca por uma disciplina através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
Disciplina* buscar_disciplina(FILE *arq, int codigo) {
    Cabecalho *cab = ler_cabecalho(arq);
    Disciplina *d = (Disciplina*) malloc(sizeof(Disciplina));

    if(!vazia(cab)) {
        fseek(arq, sizeof(Cabecalho) + sizeof(Disciplina) * cab->pos_cabeca, SEEK_SET);
        fread(d, sizeof(Disciplina), 1, arq);
        while(d->codigo != codigo && d->prox != -1) {
            fseek(arq, sizeof(Cabecalho) + sizeof(Disciplina) * d->prox, SEEK_SET);
            fread(d, sizeof(Disciplina), 1, arq);
        }
        if(d->codigo == codigo) {
            free(cab);
            return d;
        }
    }
    if(vazia(cab))
        printf("Lista vazia.\n");
    else
        printf("Elemento nao encontrado.\n");
    free(cab);
    free(d);
    return NULL;
}

// Busca por um curso através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
Curso* buscar_curso(FILE* arq, int codigo) {
    Cabecalho *cab = ler_cabecalho(arq);
    Curso* c = (Curso*) malloc(sizeof(Curso));

    if(!vazia(cab)) {
        fseek(arq, sizeof(Cabecalho) + sizeof(Curso) * cab->pos_cabeca, SEEK_SET);
        fread(c, sizeof(Curso), 1, arq);
        while(c->codigo != codigo && c->prox != -1) {
            fseek(arq, sizeof(Cabecalho) + sizeof(Curso) * c->prox, SEEK_SET);
            fread(c, sizeof(Curso), 1, arq);
        }
        if(c->codigo == codigo) {
            free(cab);
            return c;
        }
    }
    if(vazia(cab))
        printf("Lista vazia.\n");
    else
        printf("Elemento nao encontrado.\n");
    free(cab);
    free(c);
    return NULL;
}

// Busca por um cadastro de professor através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
CadastroProfessor* buscar_cadastro_professor(FILE* arq, int codigo) {
    Cabecalho *cab = ler_cabecalho(arq);
    CadastroProfessor* cadastro = (CadastroProfessor*) malloc(sizeof(CadastroProfessor));

    if(!vazia(cab)) {
        fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessor) * cab->pos_cabeca, SEEK_SET);
        fread(cadastro, sizeof(CadastroProfessor), 1, arq);
        while(cadastro->codigo != codigo && cadastro->prox != -1) {
            fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessor) * cadastro->prox, SEEK_SET);
            fread(cadastro, sizeof(CadastroProfessor), 1, arq);
        }
        if(cadastro->codigo == codigo) {
            free(cab);
            return cadastro;
        }
    }
    if(vazia(cab))
        printf("Lista vazia.\n");
    else
        printf("Elemento nao encontrado.\n");
    free(cab);
    free(cadastro);
    return NULL;
}

// Busca por um cadastro de distribuição de disciplina através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
CadastroProfessorDisciplina* buscar_cadastro_professor_disciplina(FILE* arq, int codigo) {
    Cabecalho *cab = ler_cabecalho(arq);
    CadastroProfessorDisciplina* cadastro = (CadastroProfessorDisciplina*) malloc(sizeof(CadastroProfessorDisciplina));

    if(!vazia(cab)) {
        fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessorDisciplina) * cab->pos_cabeca, SEEK_SET);
        fread(cadastro, sizeof(CadastroProfessorDisciplina), 1, arq);
        while(cadastro->codigo != codigo && cadastro->prox != -1) {
            fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessorDisciplina) * cadastro->prox, SEEK_SET);
            fread(cadastro, sizeof(CadastroProfessorDisciplina), 1, arq);
        }
        if(cadastro->codigo == codigo) {
            free(cab);
            return cadastro;
        }
    }
    if(vazia(cab))
        printf("Lista vazia.\n");
    else
        printf("Elemento nao encontrado.\n");
    free(cab);
    free(cadastro);
    return NULL;
}

// Imprime a lista de disciplinas
// Pré-condição: arquivo aberto para leitura
// Pós-condição: nenhuma
void imprimir_disciplinas(FILE *arq) {
    Cabecalho *cab = ler_cabecalho(arq);
    Disciplina *d = (Disciplina*) malloc(sizeof(Disciplina));

    if(!vazia(cab)) {
        fseek(arq, sizeof(Cabecalho) + sizeof(Disciplina) * cab->pos_cabeca, SEEK_SET);
        fread(d, sizeof(Disciplina), 1, arq);
        printf("--- DISCIPLINAS ---\n");

        while(d->prox != -1) {
            printf("Codigo: %d\n"
                    "Nome: %s\n"
                    "Codigo do curso: %d\n"
                    "Serie: %d\n"
                    "-------------------\n"
                    , d->codigo, d->nome, d->codcurso, d->serie);
            fseek(arq, sizeof(Cabecalho) + sizeof(Disciplina) * d->prox, SEEK_SET);
            fread(d, sizeof(Disciplina), 1, arq);
        }
        printf("Codigo: %d\n"
                "Nome: %s\n"
                "Codigo do curso: %d\n"
                "Serie: %d\n\n"
                , d->codigo, d->nome, d->codcurso, d->serie);
    }
    free(cab);
    free(d);
}

// Imprime a lista de cursos
// Pré-condição: arquivo aberto para leitura
// Pós-condição: nenhuma
void imprimir_cursos(FILE *arq) {
    Cabecalho *cab = ler_cabecalho(arq);
    Curso *c = (Curso*) malloc(sizeof(Curso));

    if(!vazia(cab)) {
        fseek(arq, sizeof(Cabecalho) + sizeof(Curso) * cab->pos_cabeca, SEEK_SET);
        fread(c, sizeof(Curso), 1, arq);
        printf("------ CURSOS -----\n");

        while(c->prox != -1) {
            printf("Codigo: %d\n"
                    "Nome: %s\n"
                    "Area: %c\n"
                    "-------------------\n"
                    , c->codigo, c->nome, c->area);
            fseek(arq, sizeof(Cabecalho) + sizeof(Curso) * c->prox, SEEK_SET);
            fread(c, sizeof(Curso), 1, arq);
        }
        printf("Codigo: %d\n"
                "Nome: %s\n"
                "Area: %c\n\n"
                , c->codigo, c->nome, c->area);
    }
    free(cab);
    free(c);
}

// Imprime a lista de cadastro de professores
// Pré-condição: arquivo aberto para leitura
// Pós-condição: nenhuma
void imprimir_cadastros_professor(FILE *arq) {
    Cabecalho *cab = ler_cabecalho(arq);
    CadastroProfessor *cp = (CadastroProfessor*) malloc(sizeof(CadastroProfessor));

    if(!vazia(cab)) {
        fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessor) * cab->pos_cabeca, SEEK_SET);
        fread(cp, sizeof(CadastroProfessor), 1, arq);
        printf("--- PROFESSORES ---\n");

        while(cp->prox != -1) {
            printf("Codigo: %d\n"
                    "Nome: %s\n"
                    "-------------------\n"
                    , cp->codigo, cp->nome);
            fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessor) * cp->prox, SEEK_SET);
            fread(cp, sizeof(CadastroProfessor), 1, arq);
        }
        printf("Codigo: %d\n"
                "Nome: %s\n\n"
                , cp->codigo, cp->nome);
    }
    free(cab);
    free(cp);
}

// Imprime a lista de cadastros de distribuições de disciplina
// Pré-condição: arquivo aberto para leitura
// Pós-condição: nenhuma
void imprimir_cadastros_professor_disciplina(FILE *arq) {
    Cabecalho *cab = ler_cabecalho(arq);
    CadastroProfessorDisciplina *cpd = (CadastroProfessorDisciplina*) malloc(sizeof(CadastroProfessorDisciplina));

    if(!vazia(cab)) {
        fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessorDisciplina) * cab->pos_cabeca, SEEK_SET);
        fread(cpd, sizeof(CadastroProfessorDisciplina), 1, arq);
        printf("--- DISTRIBUICAO DE DISCIPLINAS ---\n");

        while(cpd->prox != -1) {
            printf("Codigo: %d\n"
                    "Codigo da Disciplina: %d\n"
                    "Ano Letivo: %d\n"
                    "Codigo do Professor: %d\n"
                    "-----------------------------------\n"
                    , cpd->codigo, cpd->coddisciplina, cpd->anoletivo, cpd->codprofessor);
            fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessorDisciplina) * cpd->prox, SEEK_SET);
            fread(cpd, sizeof(CadastroProfessorDisciplina), 1, arq);
        }
        printf("Codigo: %d\n"
                "Codigo da Disciplina: %d\n"
                "Ano Letivo: %d\n"
                "Codigo do Professor: %d\n\n"
                , cpd->codigo, cpd->coddisciplina, cpd->anoletivo, cpd->codprofessor);
    }
    free(cab);
    free(cpd);
}

// Busca por uma distribuição de disciplina dada uma posição
// Pré-condição: arquivo de professores_disciplinas aberto para leitura
// Pós-condição: nó encontrado é retornado, caso não encontre, retorna NULL
Curso* ler_curso(FILE* arq, int pos) {
    Curso* curso = (Curso*) malloc(sizeof(Curso));

    fseek(arq, sizeof(Cabecalho) + pos * sizeof(Curso), SEEK_SET);
    fread(curso ,sizeof(Curso), 1, arq);
    return curso;
}

// // Imprime a lista de distribuição de disciplinas organizada por cursos
// // Pré-condição: arquivos de distribuição de disciplinas e de cursos abertos para leitura
// // Pós-condição: nenhuma
void imprimir_distribuicao_ordenada(FILE *arq_professores_disciplinas, FILE *arq_cursos) {
    Curso *c = (Curso*) malloc(sizeof(Curso));
    CadastroProfessorDisciplina *cpd = (CadastroProfessorDisciplina*) malloc(sizeof(CadastroProfessorDisciplina));

    Cabecalho *cab_c = ler_cabecalho(arq_cursos);
    Cabecalho *cab_cpd = ler_cabecalho(arq_professores_disciplinas);

    printf("\n--- DISTRIBUICAO DE DISCIPLINAS ORDENADA ---\n");

    fseek(arq_cursos, sizeof(Cabecalho) + sizeof(Curso) * cab_c->pos_cabeca, SEEK_SET);
    fread(c, sizeof(Curso), 1, arq_cursos);

    while(c->prox != -1) {
        printf("\n-> %s <-\n", c->nome);

        fseek(arq_professores_disciplinas, sizeof(Cabecalho) + sizeof(CadastroProfessorDisciplina) * cab_cpd->pos_cabeca, SEEK_SET);
        fread(cpd, sizeof(CadastroProfessorDisciplina), 1, arq_professores_disciplinas);
        
        while(cpd->prox != -1) {
            if(c->codigo == cpd->codcurso) {
                printf("Codigo: %d\n"
                        "Codigo da Disciplina: %d\n"
                        "Ano Letivo: %d\n"
                        "Codigo do Professor: %d\n"
                        "-----------------------------------\n"
                        , cpd->codigo, cpd->coddisciplina, cpd->anoletivo, cpd->codprofessor);
            }
            fseek(arq_professores_disciplinas, sizeof(Cabecalho) + sizeof(CadastroProfessorDisciplina) * cpd->prox, SEEK_SET);
            fread(cpd, sizeof(CadastroProfessorDisciplina), 1, arq_professores_disciplinas);
        }
        fseek(arq_cursos, sizeof(Cabecalho) + sizeof(Curso) * c->prox, SEEK_SET);
        fread(c, sizeof(Curso), 1, arq_cursos);
    }
    printf("\n-> %s <-\n", c->nome);

    fseek(arq_professores_disciplinas, sizeof(Cabecalho) + sizeof(CadastroProfessorDisciplina) * cab_cpd->pos_cabeca, SEEK_SET);
    fread(cpd, sizeof(CadastroProfessorDisciplina), 1, arq_professores_disciplinas);
        
    while(cpd->prox != -1) {
        if(c->codigo == cpd->codcurso) {
            printf("Codigo: %d\n"
                    "Codigo da Disciplina: %d\n"
                    "Ano Letivo: %d\n"
                    "Codigo do Professor: %d\n"
                    "-----------------------------------\n"
                    , cpd->codigo, cpd->coddisciplina, cpd->anoletivo, cpd->codprofessor);
        }
        fseek(arq_professores_disciplinas, sizeof(Cabecalho) + sizeof(CadastroProfessorDisciplina) * cpd->prox, SEEK_SET);
        fread(cpd, sizeof(CadastroProfessorDisciplina), 1, arq_professores_disciplinas);
    }
    printf("Codigo: %d\n"
            "Codigo da Disciplina: %d\n"
            "Ano Letivo: %d\n"
            "Codigo do Professor: %d\n"
            "-----------------------------------\n"
            , cpd->codigo, cpd->coddisciplina, cpd->anoletivo, cpd->codprofessor);

    free(c);
    free(cpd);
    free(cab_c);
    free(cab_cpd);
}

//Escreve um nó em uma determinada posição do arquivo
//Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// pos deve ser uma posição válida do arquivo
//Pós-condição: nó escrito no arquivo
void escrever_cpd(FILE* arq, CadastroProfessorDisciplina *cpd, int pos){
    fseek(arq, sizeof(Cabecalho) + pos * sizeof(cpd), SEEK_SET);
    fwrite(cpd, sizeof(cpd), 1, arq);
}

// Busca por uma distribuição de disciplina dada uma posição
// Pré-condição: arquivo de professores_disciplinas aberto para leitura
// Pós-condição: nó encontrado é retornado, caso não encontre, retorna NULL
CadastroProfessorDisciplina* ler_cpd(FILE* arq, int pos) {
    CadastroProfessorDisciplina* cpd = (CadastroProfessorDisciplina*) malloc(sizeof(CadastroProfessorDisciplina));

    fseek(arq, sizeof(Cabecalho) + pos * sizeof(CadastroProfessorDisciplina), SEEK_SET);
    fread(cpd ,sizeof(CadastroProfessorDisciplina), 1, arq);
    return cpd;
}

// Remove uma distribuição de disciplina dado seu código e seu ano letivo
// Pré-condição: arquivo de professores_disciplinas deve estar aberto para escrita
// Pós-condição: nó removido
void remover_distribuicao_disciplina(FILE *arq, int codigo, int ano_letivo) {
    Cabecalho *cab = ler_cabecalho(arq);
    CadastroProfessorDisciplina *cpd = NULL;
    int pos_aux = cab->pos_cabeca;
    int pos_ant = cab->pos_cabeca;

    while(pos_aux != -1 &&
          ((cpd = ler_cpd(arq, pos_aux)) != NULL) &&
          cpd->codigo != codigo) {
            pos_ant = pos_aux;
            pos_aux = cpd->prox;
            free(cpd);
            cpd = NULL;
        }
    if(pos_aux != -1) { // encontrou o elemento
        printf("\nElemento encontrado\n");
        if(pos_ant == pos_aux) { // remoção na cabeça
            printf("Remove na cabeca\n");
            cab->pos_cabeca = cpd->prox;
            printf("cab->pos_cabeca: %d\n", cab->pos_cabeca);
        }
        else { // remoção no meio
            printf("Remove no meio\n");
            CadastroProfessorDisciplina *ant = ler_cpd(arq, pos_ant);

            printf("pos_ant: %d\n", pos_ant);
            ant->prox = cpd->prox;
            printf("cpd->prox: %d\n", cpd->prox);
            escrever_cpd(arq, ant, pos_ant);
            printf("ant->prox: %d\n", ant->prox);
            free(ant);
        }
        cpd->prox = cab->pos_livre; // torna o nó removido um nó livre
        printf("cab->pos_livre: %d\n", cab->pos_livre);
        cab->pos_livre = pos_aux;
        printf("pos_aux: %d\n", pos_aux);
        escrever_cpd(arq, cpd, pos_aux);
        imprimir_cabecalho(cab);
        escrever_cabecalho(arq, cab);
        free(cpd);
        printf("Removido com sucesso\n");
    }
    free(cab);
}

// Gera um novo código para distribuição de disciplina
// Pré-condição: arquivo de professores_disciplinas aberto para leitura
// Pós-condição: retorna o novo código
int gerar_codigo_distribuicao(FILE *arq) {
        
    Cabecalho *cab = ler_cabecalho(arq);
    CadastroProfessorDisciplina *cpd = (CadastroProfessorDisciplina*) malloc(sizeof(CadastroProfessorDisciplina));
    int maior;

    if(vazia(cab)) {
        free(cab);
        free(cpd);
        return 0;
    }
    
    fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessorDisciplina) * cab->pos_cabeca, SEEK_SET);
    fread(cpd, sizeof(CadastroProfessorDisciplina), 1, arq);
    maior = cpd->codigo;

    while(cpd->prox != -1) {
        fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessorDisciplina) * cpd->prox, SEEK_SET);
        fread(cpd, sizeof(CadastroProfessorDisciplina), 1, arq);
        if(cpd->codigo > maior)
            maior = cpd->codigo;
    }
    free(cab);
    free(cpd);
    return maior+1;
}