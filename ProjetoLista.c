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
	t_elemento elementos;
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

//função secundaria utilizada na função inserirEncad
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



int inserirEncad(cabecalista * l, int pos, t_elemento dado) {
    t_no * p, * novo;

    // inserção na primeira posicao ou em lista vazia
    if (pos == 0) {
        novo = criaNo();
        
        if (novo == NULL)
            return 0; // erro: memoria insuficiente
            
        novo->elementos = dado;
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
        
    novo->elementos = dado;
    novo->prox = p->prox;
    p->prox = novo;

    return 1;
}



void mostraListaEncad(cabecalista l)
{
	int cnt = 0;
	//função para mostrar a lista encadeada para servir como referencia para a criação da função de mostrar a lista completa
	while(l != NULL) {
		printf("\nDisciplina[%d]: %s\n Nota: %.2f", ++cnt, l->elementos.disciplina,l->elementos.nota);
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


void exibirAlunos(Lista_aluno * aluno){
    int i;
    cabecalista no;

    for(i=0; i<=aluno->n; i++){
        printf("\nAluno %d:\n", i+1);
        printf("RGM: %s\n", aluno->dados[i].RGM);
        no = aluno->dados[i].pt_no;
        mostraListaEncad(no);

        printf("\n");
    }
}


void menu() {
	system("cls");
	printf("Digite a opção desejada:\n");
	printf("0- Encerrar o programa\n");
	printf("1- Incluir um novo elemento na lista\n");
	printf("2- Buscar algum elemento já existente da lista"); 
	printf("\n3- Exibir a lista completa \n4- Remover algum elemento da lista\n");
	printf("5- Exibir os créditos\n");
}

int main() {
	setlocale(LC_ALL,"Portuguese");
	int i=0,pos,t,retorno;
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
		}while (op!='0' && op!='1' && op!='2' && op!='3' && op!='4' && op!='5');
	
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
					sequencial_cont.pt_no=NULL;
					
					printf("Digite o RGM: ");
					scanf("%s",&(sequencial_cont.RGM));
					do{
						fflush(stdin);
						printf("Disciplina:");
						gets(elemento_encad.disciplina);
						printf("Nota:");
						scanf("%f",&elemento_encad.nota);
				
						inserirEncad(&sequencial_cont.pt_no,cont,elemento_encad);
						cont++;
						
						fflush(stdin);
						printf("Mais disciplinas? s/n\n");
						resp = getchar();
						fflush(stdin);
					}while(resp == 's'); 
					inserirOrdenada(&listaAlunos,sequencial_cont);
				}
			getch();
		}
		
		
		else if (op=='2') {
			printf("Digite o RGM do aluno que deseja procurar: ");
			scanf("%s",&buscargm);
			pos=getPosicao(&listaAlunos,buscargm);
			if(pos!=-1) {
				printf("O aluno de RGM %s é o %dº elemento da lista\n",listaAlunos.dados[pos].RGM,pos+1);
				mostraListaEncad(listaAlunos.dados[pos].pt_no);
			}
			else {
				printf("Não existe nenhum aluno cadastrado com esse rgm");
			}
			
			getch();
		}
		
		else if (op=='3') {
			printf("\n\n");
	    	exibirAlunos(&listaAlunos);
	    	getch();
		}
		
		else if(op=='4') {
			printf("Digite o RGM para remover: ");
	    	scanf("%s",&(sequencial_cont.RGM));
	    	retorno=removeAluno(&listaAlunos,sequencial_cont.RGM);
	    	if (retorno==1)
	    	exibirAlunos(&listaAlunos);
	    	else
	    	printf("RGM não registrado");
	    	getch();
		}
		
		else if(op=='5') {
			system("cls");
			printf("Créditos: \n--------------\n");
			printf("Desenvolvedores\n----------------------\n\n");
			printf("Agiel Gomes\n");
			printf("Gabriel de Almeida\n");
			printf("Victor de Almeida\n");
			getch();
		}
	}
	return 0;
    
	
}
