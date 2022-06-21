/*********************************************************************************
*  
*                    MINI PROJETO - ESTRUTURA DE DADOS I 
*                    Professor: Walace Bonfim
*                    DESCRIPTION :
*       
*	            Projeto criado em grupo para finalização do primeiro
*               Ciclo de Estrutura de Dados I, com isso fizemos uma 
*          arvóre binaria de busca, Baseada nos criterios pedidos no slide. 
*
* Autores: Gabriel Rodrigues, Farney Filho, Davi Carneiro, Bianca Schiochet 
*
*                   Data de inicio: 15 de jun de 2022.
*                   Data da finalização: 19 de jun de 2022.
*
**********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#ifdef WIN32

void gotoxy(int coluna, int linha){
    COORD point;
    point.X = coluna;
    point.Y = linha;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}
#else
void gotoxy(int x, int y){
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}
#endif

// Tipo base dos elementos da arvore
typedef struct elementos {
	char rgm[100] ;
    //char nome[100];
} t_elemento;

typedef struct no {
	struct no * esq;
	t_elemento dado;
	struct no * dir;
} t_no;

typedef t_no* t_arvore;



// Exibe arvore
void exibir(t_arvore arvore);

// Busca
t_no * busca(t_arvore tree, t_elemento dado);

// Pesquisa
void pesquisar(t_elemento dado, t_arvore tree);

// Busca Pai
t_no * buscaSetPai(t_arvore tree, t_elemento dado, t_no ** pai);

// Remover
int remover (t_arvore *tree, t_elemento item);

// ExibirposOrdem
void exibirPosOrdem(t_arvore tree);

// ExibirinOrdem
void exibirInOrdem(t_arvore tree);

// ExibirpreOrdem
void exibirPreOrdem(t_arvore tree);

// Exibir Graficamente
void exibirGraficamente(t_arvore tree, int col, int lin, int desloc);

// Criar no
t_no * criar ();

// Comparar
int compara(t_elemento dado, t_elemento item);

// Inserir
int inserir (t_arvore *tree, t_elemento item);

// Menu
int menu();

// Ler Arquivo
void lerArquivo(t_arvore* arvore);

// Apagar
void apagar();

// Esvaziar
void esvaziar(t_arvore *tree);


int main() {
	
	FILE *arquivo = NULL;
	t_arvore arvore = NULL;
	int pegaOpc = 0;
	int pOpcSair; 
	char str[100];
	int numeroConvertido[100];
	t_elemento dado;
	lerArquivo(&arvore);
	
	do{
		
		pegaOpc = menu();
			
		switch(pegaOpc){
			
			case 1:
				do{
                    system("cls");
					printf("Digite o rgm que voce deseja inserir na arvore: ");
					scanf("%s", dado.rgm);
					
					inserir(&arvore, dado);
					printf("digite 0 para sair ou qualquer outro valor para inserir na arvore: ");
					scanf("%d", &pOpcSair);
					system("cls");
					
				}while(pOpcSair != 0);
				
				break;
				
			case 2:
                system("cls");
				printf("informe o dado que voce deseja remover da arvore: ");
				scanf("%s",dado.rgm);
				remover(&arvore, dado);
				break;
			
				
			case 3:
                system("cls");
				printf("Informe o dado que voce deseja pesquisar: ");
				scanf("%s",&dado.rgm);
				pesquisar(dado, arvore);
				break;
				
			
			case 4:
                system("cls");
				esvaziar(&arvore);
				break;
				
			case 5:
                system("cls");
				exibir(arvore);
				break;
		}
		
	}while(pegaOpc != 0);

	return 0;
}

/* funcoes */

t_no * buscaSetPai(t_arvore tree, t_elemento dado, t_no ** pai) {

    if (tree == NULL) {
        *pai = NULL;
        return NULL;
    }
    if (compara(tree->dado, dado)==0)
        return tree;

    if (compara(tree->dado, dado)>0) {
        *pai = tree;
        return buscaSetPai(tree->esq, dado, pai);
    }
    else {
        *pai = tree;
        return buscaSetPai(tree->dir, dado, pai);
    }
}

int remover (t_arvore *tree, t_elemento item){
    t_no *no, 
         *pai, 
         *sub, 
         *paiSuce, 
         *suce; 
    no = *tree;
    pai=NULL;
    no = buscaSetPai(*tree, item, &pai);
    if (no==NULL){	
    	printf("conteudo nao existe na arvore ");
        return 0; 
		}
    if (no->esq == NULL)
        sub = no->dir;
    else
    {
        if (no->dir == NULL)
            sub = no->esq;
        else { 
             paiSuce=no;
             sub = no->dir;
             suce = sub->esq; 
             while (suce != NULL) {
                   paiSuce = sub;
                   sub = suce;
                   suce = sub->esq;
             }
             if (paiSuce != no) {
                paiSuce->esq = sub->dir;
                sub->dir = no->dir;
             }
             sub->esq = no->esq;
        }
    }
    if (pai == NULL) 
        *tree = sub;
    else
        if (no == pai->esq)
            pai->esq = sub;
        else
            pai->dir = sub;
    free(no); 
    return 1; 
}

t_no * busca(t_arvore tree, t_elemento dado) {

    if (tree == NULL) 
        return NULL;
    if (compara(tree->dado, dado)==0)
        return tree;

    if (compara(tree->dado, dado)>0)
        return busca(tree->esq, dado);
    else
        return busca(tree->dir, dado);
}


void pesquisar(t_elemento dado, t_arvore tree) {
	t_no *retorno;
	
	retorno = busca(tree, dado);
	
	if(retorno == NULL){
		printf("Conteudo nao existe na arvore: \n");
		
	}
	
	else{
		printf("tudo bem o conteudo %s existe na arvore\n", dado.rgm);
	}
}

t_no * criar () {
	t_no * no = (t_no*) malloc(sizeof(t_no));

	if (no)
	no->esq = no->dir = NULL;

	return no;
}

int compara(t_elemento dado1, t_elemento dado2){
	return (strcmp(dado1.rgm, dado2.rgm));
}

int inserir (t_arvore *tree, t_elemento item) {
	int ok;
	if (*tree == NULL) {
		*tree = criar();
		if (*tree == NULL)
		return 0;
		(*tree)->dado = item;
		return 1;
		}
		
	if (compara((*tree)->dado, item)<0)
		ok = inserir (&((*tree)->dir), item);
	else
		if (compara((*tree)->dado, item)>0)
			ok = inserir (&((*tree)->esq), item);
	else
		ok = 0;
	return ok;
}


void esvaziar(t_arvore *tree) {
    if (*tree == NULL)
        return;
    esvaziar(&(*tree)->esq);
    esvaziar(&(*tree)->dir);
    free(*tree);
    *tree = NULL;
}


int menu(){
	int opc = 0 ;

    printf("\n\t------------------------------------------");
    printf("\n\t          ARVORE BINARIA - ABB            ");
    printf("\n\t------------------------------------------");
    printf("                                              ");
    printf("\n\t          1. Inserir                      ");
    printf("\n\t          2. Remover No                   ");
    printf("\n\t          3. Pesquisar                    ");
    printf("\n\t          4. Esvaziar a Arvore            ");
    printf("\n\t          5. Exibir a Arvore              ");
    printf("\n\t          0. Sair                         ");
    printf("                                              ");
    printf("\n\t     ESCOLHA ALGUMA DAS OPCOES            ");
    printf("\n\t------------------------------------------");
    printf("\n\t    Disciplina: Estrutura de Dados I      ");
    printf("\n\t    Professor: Walace Bonfim              ");
    printf("\n\t    Alunos: Gabriel Rodrigues             ");
    printf("\n\t    Farney Filho, Bianca Schiochet        ");
    printf("\n\t    Davi Carneiro                         ");
    printf("\n\t------------------------------------------");
	scanf("%d", &opc);
	system("cls");
	
	return opc;
 


   
}

void exibirGraficamente(t_arvore tree, int col, int lin, int desloc) {
    if (tree == NULL)
        return;
    gotoxy(col,lin);
    printf("%s",tree->dado.rgm);
    if (tree->esq != NULL)
        exibirGraficamente(tree->esq,col-desloc,lin+2,desloc/2+1);
    if (tree->dir != NULL)
        exibirGraficamente(tree->dir,col+desloc,lin+2,desloc/2+1);
}


void exibirInOrdem(t_arvore tree) {
    if (tree!=NULL) {
        exibirInOrdem(tree->esq);
        printf("%s ", tree->dado.rgm);
        exibirInOrdem(tree->dir);
    }
}

void exibirPreOrdem(t_arvore tree) {
    if (tree!=NULL) {
        printf("%s ", tree->dado.rgm);
        exibirPreOrdem(tree->esq);
        exibirPreOrdem(tree->dir);
    }
}


void exibirPosOrdem(t_arvore tree) {
    if (tree!=NULL) {
        exibirPosOrdem(tree->esq);
        exibirPosOrdem(tree->dir);
        printf("%s ", tree->dado.rgm);
    }
}

void exibir(t_arvore arvore) {
	
	printf("Exibicao em ordem: ");
	exibirPreOrdem(arvore);
	printf("\n\n");
	printf("Exibicao pos ordem: ");
	exibirPosOrdem(arvore);
	printf("\n\n");
	printf("Exibicao in ordem: ");
	exibirInOrdem(arvore);
	printf("\n\n");
	printf("Pressione enter ...");
	system("cls");
	printf("Exibicao grafica\n");
	exibirGraficamente(arvore, 10, 10, 3);
	printf("\n\n");
	system("cls");

}

void lerArquivo(t_arvore* arvore) {
	t_elemento elemento;
	char url[]="rgm.txt";
	char ch;
	int i=0;
	FILE *arq;
	arq = fopen(url, "r");
	if(arq == NULL){
		printf("Erro, nao conseguimos abrir o arquivo.\n");
	} else {
		while( (ch=fgetc(arq))!= EOF ){
			if(ch == ';'){	
				elemento.rgm[i] = '\0';
				inserir(arvore, elemento);
				i=0;		
			} else {
				elemento.rgm[i] = ch;
				i++;	
			}
			
		}
	}	
	
	fclose(arq);
}