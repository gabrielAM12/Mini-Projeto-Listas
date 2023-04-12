#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX 60


//estruturas:

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

//funções para lista sequencial:

//criação da lista sequencial
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

//procura atraves da posição na lista sequencial (possivelmente desnecessário)
t_conteudo * getAluno(Lista_aluno * aluno, int pos) {
	if ((pos > aluno->n) || (pos < 0))
		return NULL;
		
	return &(aluno->dados[pos]);
}

//procura atraves do rgm do aluno na lista sequencial
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

int inserirOrdenada (Lista_aluno * aluno, t_conteudo dado) {
	int pos;
	
    if (isCheia(aluno))
        return 0;

	if (isVazia(aluno))
		pos = 0;
	else
	    pos = getPosicaoInsercaoOrdenada(aluno, dado.RGM);
	
	inserirPos (aluno, pos, dado);	

    return 1;
}


//funções para lista encadeada:


t_no * criaNo() {
    t_no * no = (t_no *) malloc(sizeof(t_no));

    if (no)
        no->prox = NULL;

    return no;
}


int encadVazia(cabecalista l) {
    return (l == NULL);
}

int encadTamanho(cabecalista l) {
    int n = 0;
    
    while (l != NULL) {
        n++;
        l = l->prox;
    }
    return n;
}

t_no * getNo(cabecalista l, int pos) {
    // Retorna 0 se posicao invalida. Do contrario, retorna o elemento
    int n = 0;

    if (pos < 0)
        return 0; // erro: posicao invalida

    while (l != NULL) {
        if (n == pos)
            return l;
            
        n++;
        l = l->prox;
    }
    return 0; // erro: posicao invalida
}

//nao ira precisar
t_elemento * getElemento(cabecalista l, int pos)
{
    t_no * no = getNo(l, pos);
    
    if (no != NULL)
        return &(no->dados);
    else
        return NULL;
}

int inserirEncad(cabecalista * l, int pos, t_elemento dado) {
    t_no * p, * novo;

    // inserção na primeira posicao ou em lista vazia
    if (pos == 0) {
        novo = criaNo();
        
        if (novo == NULL)
            return 0; // erro: memoria insuficiente
            
        novo->dados = dado;
        novo->prox = *l;
        
        *l = novo;
        
        return 1;
    }
    // insercao apos a primeira posicao em lista nao vazia
    p = getNo(*l, pos - 1);
    if (p == NULL)
         return 0; // erro: posicao invalida 
         
    novo = criaNo();
    if (novo == NULL)
        return 0; // erro: memoria insuficiente
        
    novo->dados = dado;
    novo->prox = p->prox;
    p->prox = novo;

    return 1;
}


int removerEncad(cabecalista * l, int pos) {
    t_no * anterior,  * aux;
    
    if (encadVazia(*l) || pos < 0)
		return 0; // erro: lista vazia ou posição inválida
    
    if (pos == 0) { // remocao da primeira posicao em lista nao vazia
        aux = *l;
        *l = aux->prox;
    } else { // remocao em qualquer posicao
        anterior = getNo(*l, pos-1);
        if (anterior == NULL)
            return 0; // erro: posicao invalida
            
        aux = anterior->prox;
        if (aux == NULL)
            return 0; // erro: posicao invalida
            
        anterior->prox = aux->prox;
    }
    free(aux);
    
    return 1;
}




//Essa função será desenvolvida depois de terminar a lista encadeada:



void mostraListaEncad(cabecalista l)
{
	int cnt = 0;
	//função para mostrar a lista encadeada para servir como referencia para a criação da função de mostrar a lista completa
	while(l != NULL) {
		printf("Elemento [%d] tem [%s]\n", ++cnt, l->dados.disciplina);
		l = l->prox;
	}
	
	if(!cnt)
		printf("Lista vazia\n");
}

void	mostrar(Lista_aluno * aluno){
	
	int i;
	
	printf("Minha lista de Alunos\n");
	for(i = 0; i <= aluno->n; i++) {
		printf("RGM: %s\t", aluno->dados[i].RGM);
	}
}


int main() {
	setlocale(LC_ALL,"Portuguese");
	
}
