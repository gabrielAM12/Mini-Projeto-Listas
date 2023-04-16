#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

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
	char RGM [9];
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

int removeAluno(Lista_aluno * aluno,char RGM[]) {
	int posicao, i;
	posicao = getPosicao(aluno, RGM);

        if (posicao != -1) {
            removePos(aluno, posicao);
            return 1;
        }
    return 0;
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



void exibirAlunos(Lista_aluno lista) {
    printf("Lista de alunos:\n");
    int i;
    for (i = 0; i <= lista.n; i++) {
        printf("Aluno %d - RGM: %s\n", i+1, lista.dados[i].RGM);
    }
}

void menu() {
	system("cls");
	printf("Digite a opção desejada:\n1- Incluir um novo elemento na lista\n");
	printf("2- Buscar algum elemento já existente da lista"); 
	printf("\n3- Exibir a lista completa \n4- Remover algum elemento da lista\n0- Encerrar o programa\n");
}

int main() {
	setlocale(LC_ALL,"Portuguese");
	int i=0,pos;
	int qtde=0,totalA=0;
	char op;
	char buscargm[9];
	int sair=0;
	
	
	cabecalista mlista = NULL;
	
	t_conteudo sequencial_cont;
	t_elemento elemento_encad;
	t_no * mno;
	Lista_aluno listaAlunos = criar();
	
	
	while (sair==0) {
		menu();
		
		do{
			op = getch();
		}while (op!='0' && op!='1' && op!='2' && op!='3' && op!='4');
	
		if (op=='0') {
			sair=1;
		}
		
		
		
		else if (op=='1') {
			char resp = 's';
			printf("Digite a quantidade de alunos que serão cadastrados:");
			scanf("%d",&qtde);
			totalA+=qtde;
				for(;i<totalA;i++) {
					int cont=0;
					
					printf("Digite o RGM: ");
					scanf("%s",&(sequencial_cont.RGM));
					inserirOrdenada(&listaAlunos,sequencial_cont);
					do{
						fflush(stdin);
						printf("Disciplina:");
						gets(elemento_encad.disciplina);
						printf("Nota:");
						scanf("%f",&elemento_encad.nota);
				
						//inserirPos (&myLista, pos, cont);
						inserirEncad(&listaAlunos.dados[i].pt_no,cont,elemento_encad);
						cont++;
						
						fflush(stdin);
						printf("Mais disciplinas? s/n\n");
						resp = getchar();
						fflush(stdin);
					}while(resp == 's'); 
				}
			getch();
		}
		
		
		else if (op=='2') {
			printf("Digite o RGM do aluno que deseja procurar: ");
			scanf("%s",&buscargm);
			pos=getPosicao(&listaAlunos,buscargm);
			if(pos!=-1) {
				printf("O aluno de RGM %s é o %dº elemento da lista",listaAlunos.dados[pos].RGM,pos+1);
			}
			else {
				printf("Não existe nenhum aluno cadastrado com esse rgm");
			}
			
			getch();
		}
		
		else if (op=='3') {
			printf("\n\n");
	    	exibirAlunos(listaAlunos);
	    	getch();
		}
		
		else if(op=='4') {
			printf("Digite o RGM para remover: ");
	    	scanf("%s",&(sequencial_cont.RGM));
	    	removeAluno(&listaAlunos,sequencial_cont.RGM);
	    	getch();
		}
	}
	
	
	
	
	
	
    
	return 0;
    
	
}
