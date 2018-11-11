#ifndef RB_H
#define RB_H

enum cor { VERMELHO, PRETO, DUPLOPRETO };

typedef int tipo_dado;

typedef struct no_bst {
	tipo_dado dado;
	enum cor cor;
	struct no_bst *esq, *dir, *pai;
} no_bst;

typedef no_bst * arvore;

void inicializar(arvore *raiz);
void adicionar (int valor, arvore *raiz);

int altura(arvore raiz);
int maior(int a, int b);
int maior_elemento(arvore raiz);
int menor_elemento(arvore raiz);
void pre_order(arvore raiz);
void pos_order(arvore raiz);
void in_order(arvore raiz);
arvore remover (int valor, arvore* raiz, arvore elemento);
void imprimir_elemento(arvore raiz);
void imprimir(arvore raiz);
enum cor cor(arvore elemento);
void ajustar(arvore *raiz, arvore elemento);
void rotacao_simples_direita(arvore *raiz, arvore pivo);
void rotacao_simples_esquerda(arvore *raiz, arvore pivo);
int eh_raiz(arvore elemento);
int eh_filho_esquerdo(arvore elemento);
int eh_filho_direito(arvore elemento) ;
arvore sobrinho_esq(arvore elemento);
arvore sobrinho_dir(arvore elemento);
arvore irmao(arvore elemento);
arvore tio(arvore elemento);
void remover_auxiliar(arvore* raiz, arvore elemento);
void remover_caso1(arvore elemento);
void remover_caso2(arvore* raiz, arvore elemento);
void remover_caso3(arvore elemento);
void remover_caso4(arvore elemento);
void remover_caso5(arvore* raiz, arvore elemento);
void remover_caso6A(arvore* raiz, arvore elemento);
void remover_caso6B(arvore* raiz, arvore elemento);

#endif
