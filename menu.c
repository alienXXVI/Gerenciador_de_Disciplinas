#include <stdio.h>
#include "menu.h"
#include "lotes.h"

void menu_principal(FILE *arq_cursos, FILE *arq_disciplinas, FILE *arq_professores, FILE *arq_professores_disciplinas) {
    int i = -1;

    while(i != 5) {
        printf("\n1 - Fazer um cadastro\n"
                "2 - Fazer uma impressao\n"
                "3 - Remover cadastro de distribuicao de disciplina\n"
                "4 - Carregar arquivo em lote\n"
                "5 - Finalizar o programa\n"
                "> ");

        scanf("%d%*c", &i);
        if(i == 1)
            cadastrar(arq_cursos, arq_disciplinas, arq_professores, arq_professores_disciplinas);
        if(i == 2)
            imprimir(arq_cursos, arq_disciplinas, arq_professores, arq_professores_disciplinas);
        if(i == 3)
            remover(arq_professores_disciplinas);
        if(i == 4)
            carregar_lote(arq_cursos, arq_disciplinas, arq_professores, arq_professores_disciplinas);
        if(i != 1 && i != 2 && i != 3 && i != 4 && i != 5)
            printf("(Digito invalido)\n");
    }
}

void cadastrar(FILE *arq_cursos, FILE *arq_disciplinas, FILE *arq_professores, FILE *arq_professores_disciplinas) {
    int i = -1;

    while (i != 5)
    {
        printf("\n1 - Cadastrar curso\n"
               "2 - Cadastrar disciplina\n"
               "3 - Cadastrar professor\n"
               "4 - Cadastrar distribuicao de disciplina\n"
               "5 - Voltar\n"
               "> ");
        scanf("%d%*c", &i);

        if(i == 1)
            cadastrar_curso(arq_cursos);
        if(i == 2)
            cadastrar_disciplina(arq_disciplinas);
        if(i == 3)
            cadastrar_professor(arq_professores);
        if(i == 4)
            cadastrar_distribuicao(arq_professores_disciplinas, arq_disciplinas);
        if(i != 1 && i != 2 && i != 3 && i != 4 && i != 5)
            printf("(Digito invalido)\n");
    }
    
}

void cadastrar_curso(FILE *arq_cursos) {
    Curso *c = NULL;
    int codigo;
    char nome[100];
    char area;

    printf("\nDigite o codigo do curso\n"
           "> ");
    scanf("%d%*c", &codigo);

    printf("Digite o nome do curso\n"
           "> ");
    scanf("%s%*c", &nome);

    printf("Digite a area do curso\n"
           "> ");
    scanf("%c%*c", &area);

    c = criar_curso(codigo, nome, area);
    inserir_curso(arq_cursos, c);
    printf("(Curso inserido)\n");
}

void cadastrar_disciplina(FILE *arq_disciplinas) {
    Disciplina *d = NULL;
    int codigo;
    char nome[100];
    int codcurso;
    int serie;

    printf("\nDigite o codigo da disciplina\n"
           "> ");
    scanf("%d%*c", &codigo);

    printf("Digite o nome da disciplina\n"
           "> ");
    scanf("%s%*c", &nome);

    printf("Digite o codigo do curso da disciplina\n"
           "> ");
    scanf("%d%*c", &codcurso);

    printf("Digite a serie da disciplina\n"
           "> ");
    scanf("%d%*c", &serie);

    d = criar_disciplina(codigo, nome, codcurso, serie);
    inserir_disciplina(arq_disciplinas, d);
    printf("(Disciplina inserida)\n");
}

void cadastrar_professor(FILE* arq_professores) {
    CadastroProfessor *cp = NULL;
    int codigo;
    char nome[1000];

    printf("\nDigite o codigo do professor\n"
           "> ");
    scanf("%d%*c", &codigo);

    printf("Digite o nome do professor\n"
           "> ");
    scanf("%s%*c", &nome);

    cp = criar_cadastro_professor(codigo, nome);
    inserir_cadastro_professor(arq_professores, cp);
    printf("(Professor inserido)\n");
}

void cadastrar_distribuicao(FILE *arq_professores_disciplinas, FILE *arq_disciplinas) {
    CadastroProfessorDisciplina *cpd = NULL;
    int codigo;
    int coddisciplina;
    int anoletivo;
    int codprofessor;

    printf("\nDigite o codigo\n"
           "> ");
    scanf("%d%*c", &codigo);

    printf("Digite o codigo da disciplina\n"
           "> ");
    scanf("%d%*c", &coddisciplina);

    printf("Digite o ano letivo\n"
           "> ");
    scanf("%d%*c", &anoletivo);

    printf("Digite o codigo do professor\n"
           "> ");
    scanf("%d%*c", &codprofessor);

    cpd = criar_cadastro_professor_disciplina(codigo, coddisciplina, anoletivo, codprofessor);
    inserir_cadastro_professor_disciplina(arq_professores_disciplinas, arq_disciplinas, cpd);
    printf("(Distribuicao inserida)\n");
}

void imprimir(FILE *arq_cursos, FILE *arq_disciplinas, FILE *arq_professores, FILE *arq_professores_disciplinas) {
    int i = -1;

    while(i != 5) {
        printf("\n1 - Imprimir cursos\n"
               "2 - Imprimir disciplinas\n"
               "3 - Imprimir professores\n"
               "4 - Imprimir distribuicoes de disciplinas\n"
               "5 - Voltar\n"
               "> ");
        scanf("%d%*c", &i);

        if(i == 1)
            imprimir_cursos(arq_cursos);
        if(i == 2)
            imprimir_disciplinas(arq_disciplinas);
        if(i == 3)
            imprimir_cadastros_professor(arq_professores);
        if(i == 4)
            imprimir_distribuicao_ordenada(arq_professores_disciplinas, arq_cursos);
        if(i != 1 && i != 2 && i != 3 && i != 4 && i != 5)
            printf("(Digito invalido)\n");
    }
}

void remover(FILE *arq_professores_disciplinas) {
    int codigo;
    int anoletivo;

    printf("\nDigite o codigo da distribuicao de disciplina\n"
           "> ");
    scanf("%d%*c", &codigo);

    printf("Digite o ano letivo\n"
           "> ");
    scanf("%d%*c", &anoletivo);

    remover_distribuicao_disciplina(arq_professores_disciplinas, codigo, anoletivo);
    printf("(Distribuicao removida)\n");
}

void carregar_lote(FILE *arq_cursos, FILE *arq_disciplinas, FILE *arq_professores, FILE *arq_professores_disciplinas) {
    char arquivo[100];

    printf("\nDigite o nome do arquivo\n"
           "> ");
    scanf("%s%*c", &arquivo);

    ler_arq_txt(arquivo, arq_disciplinas,  arq_cursos, arq_professores, arq_professores_disciplinas);
    printf("Arquivo lido\n");
}