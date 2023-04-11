#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX 60

typedef struct elemento{
	char disciplina[50];
	float nota;
}t_elemento;

typedef struct no{
	t_elemento dados;
	struct no *prox;
}t_no;

typedef t_no * cabecalista;

typedef struct conteudo{
	cabecalista pt_no;
	char RGM [8];
}t_conteudo;

typedef struct aluno{
	t_conteudo dados[MAX];
	int n;
}Lista_aluno;



Lista_aluno criar() {
	Lista_aluno aluno;
	
	aluno.n = -1;
	
	return aluno;
}


int	isVazia(Lista_aluno * aluno){
	return (aluno->n == -1);
}

int	isCheia (Lista_aluno * aluno) {
	return (aluno->n == (MAX -1));
}

int	getQuantidade(Lista_aluno * aluno) {
	return (aluno->n + 1);
}

t_conteudo * getAluno(Lista_aluno * aluno, int pos) {
	if ((pos > aluno->n) || (pos < 0))
		return NULL;
		
	return &(aluno->dados[pos]);
}

int getPosicao(Lista_aluno * aluno, char RGM[]) {
	int	i;
	
	for (i = 0; i <= aluno->n; i++) {
		if (strcmp(aluno->dados[i].RGM, RGM) == 0)
			return i;
	}
			
	return -1;
}

int deslocaDireita(Lista_aluno * aluno, int pos) {
    int i;

    for (i = aluno->n + 1; i>pos; i--)
        aluno->dados[i] = aluno->dados[i-1];
}

int inserirPos (Lista_aluno * aluno, int pos, t_conteudo conteudo) {
    if (isCheia(aluno) || (pos > aluno->n + 1) || (pos < 0))
        return 0;

    deslocaDireita(aluno, pos);
    aluno->dados[pos] = conteudo;
    (aluno->n)++;
    return 1;
}

int deslocaEsquerda(Lista_aluno * aluno, int pos) {
    int i;

    for (i = pos; i < aluno->n ; i++)
        aluno->dados[i] = aluno->dados[i+1];
}

int removePos(Lista_aluno * aluno, int pos) {
    if ((pos > aluno->n) || (pos < 0))
        return 0;

    deslocaEsquerda(aluno, pos);
    (aluno->n)--;
    
    return 1;
}

int getPosicaoInsercaoOrdenada(Lista_aluno * aluno, char RGM[]) {
    int i;
    
    for (i = 0; i <= aluno->n; i++) {
        if (strcmp(aluno->dados[i].RGM, RGM) > 0)
            return i;
    }

    // inserir na última posição
    return i;
}

int main() {
	setlocale(LC_ALL,"Portuguese");
	
	Lista_aluno lista = criar();
	
	// fazer função ExibeLista()
    printf("Lista de alunos:\n");
    for (int i = 0; i <= lista.n; i++) {
        printf("Aluno %d - RGM: %s\n", i+1, lista.dados[i].RGM);
    }

    char rgm[8];
    printf("Digite o RGM do aluno a ser removido: ");
    scanf("%s", rgm);

	// fazer função removeAluno(), que chama removePos caso encontre o aluno para remover
    int pos = getPosicao(&lista, rgm);
    if (pos == -1) {
        printf("Aluno não encontrado\n");
    } else {
        removePos(&lista, pos);
        printf("Aluno removido com sucesso\n");
    }

    return 0;
	
}
