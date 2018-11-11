#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

void inicializar(arvore *raiz) {
	*raiz = NULL;
}

void adicionar (int valor, arvore *raiz) {
	arvore posicao, pai, novo;
	posicao = *raiz;
	pai = NULL;

	/*navega na árvore até encontrar a posição vaga apropriada para o elemento,
		nesta "descida" é necessário manter o ponteiro para o pai, pois após encontrar
		a posição vaga (NULL) não será possível encontrar o pai com o ponteiro posicao->pai */
	while(posicao != NULL) {
			pai = posicao;
			if(valor > posicao->dado)
					posicao = posicao->dir;
			else
					posicao = posicao->esq;
	}

	novo = (arvore) malloc(sizeof(struct no_bst));
	novo->dado = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;

	if(eh_raiz(novo))
			*raiz = novo;
	else {
		if(valor > pai->dado)
			pai->dir = novo;
		else
			pai->esq = novo;
	}

	ajustar(raiz, novo);
}


void ajustar(arvore *raiz, arvore elemento){

	while(cor(elemento->pai) == VERMELHO && elemento->cor == VERMELHO) {
			//caso 1: Cor do tio é vermelha, desce o preto do avô
			if(cor(tio(elemento)) == VERMELHO) {
				tio(elemento)->cor = PRETO;
				elemento->pai->cor = PRETO;
				elemento->pai->pai->cor = VERMELHO;
				//Continua a verificação a partir do avô, que mudou para vermelho e pode ter
				//gerado uma sequência vermelho-vermelho
				elemento = elemento->pai->pai;
				continue;
			}
			//caso 2a: rotação simples direita
			if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
					rotacao_simples_direita(raiz, elemento->pai->pai);
					irmao(elemento)->cor = VERMELHO;
					elemento->pai->cor = PRETO;
					continue;
			}
			//caso 2b: rotação simples esquerda
			if(eh_filho_direito(elemento) && eh_filho_direito(elemento->pai)) {
					rotacao_simples_esquerda(raiz, elemento->pai->pai);
					irmao(elemento)->cor = VERMELHO;
					elemento->pai->cor = PRETO;
					continue;
			}
			//caso 3a: rotação dupla direita
			if (eh_filho_direito(elemento) && eh_filho_esquerdo(elemento->pai)) {
					rotacao_simples_esquerda(raiz, elemento->pai);
					rotacao_simples_direita(raiz, elemento->pai);
					elemento->cor = PRETO;
					elemento->esq->cor = VERMELHO;
					elemento->dir->cor = VERMELHO;
					continue;
			}

			//caso 3b: rotação dupla esquerda
			if (eh_filho_esquerdo(elemento) && eh_filho_direito(elemento->pai)) {
					rotacao_simples_direita(raiz, elemento->pai);
					rotacao_simples_esquerda(raiz, elemento->pai);
					elemento->cor = PRETO;
					elemento->esq->cor = VERMELHO;
					elemento->dir->cor = VERMELHO;
					continue;
			}
	}

	(*raiz)->cor = PRETO;
}

void rotacao_simples_direita(arvore *raiz, arvore pivo){
			arvore fe;
			fe = pivo->esq;

			int posicao_pivo_esq = eh_filho_esquerdo(pivo);

			//Atualização dos ponteiros
			pivo->esq = fe->dir;
			fe->dir = pivo;

			fe->pai = pivo->pai;
			pivo->pai = fe;

			if(pivo->esq != NULL)
				pivo->esq->pai = pivo;

			if(eh_raiz(fe))
				*raiz = fe;
			else {
					if(posicao_pivo_esq)
							fe->pai->esq = fe;
					else
							fe->pai->dir = fe;
			}
}

void rotacao_simples_esquerda(arvore *raiz, arvore pivo){
			arvore fd;
			fd = pivo->dir;

			int posicao_pivo_dir = eh_filho_direito(pivo);

			//Atualização dos ponteiros
			pivo->dir = fd->esq;
			fd->esq = pivo;

			fd->pai = pivo->pai;
			pivo->pai = fd;

			if(pivo->dir != NULL)
				pivo->dir->pai = pivo;

			if(eh_raiz(fd))
				*raiz = fd;
			else {
					if(posicao_pivo_dir)
							fd->pai->dir = fd;
					else
							fd->pai->esq = fd;
			}
}

enum cor cor(arvore elemento) {
	enum cor c;
	if(elemento == NULL || elemento->cor == PRETO)
		c = PRETO;
	else
		c = VERMELHO;
	return c;
}

int eh_raiz(arvore elemento) {
	return (elemento->pai == NULL);
}

int eh_filho_esquerdo(arvore elemento) {
	return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

int eh_filho_direito(arvore elemento) {
	return (elemento->pai != NULL && elemento == elemento->pai->dir);
}

arvore tio(arvore elemento) {
	return irmao(elemento->pai);
}

arvore irmao(arvore elemento) {
	if(eh_filho_esquerdo(elemento))
		return elemento->pai->dir;
	else
		return elemento->pai->esq;
}

arvore sobrinho_esq(arvore elemento){
	return irmao(elemento)->esq;
}

arvore sobrinho_dir(arvore elemento){
	return irmao(elemento)->dir;
}

void imprimir(arvore raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}


int altura(arvore raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}

int maior_elemento(arvore raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->dir);
}

int menor_elemento(arvore raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return menor_elemento(raiz->esq);
}

void pre_order(arvore raiz) {
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
}

void pos_order(arvore raiz) {
	if(raiz != NULL) {
		pos_order(raiz->esq);
		pos_order(raiz->dir);
		imprimir_elemento(raiz);
	}
}

void in_order(arvore raiz) {
	if(raiz != NULL) {
		in_order(raiz->esq);
		imprimir_elemento(raiz);
		in_order(raiz->dir);
	}
}

void imprimir_elemento(arvore raiz) {
	if(cor(raiz) == PRETO)
		printf("\x1b[30m[%d]\x1b[0m", raiz->dado);
	else
		printf("\x1b[31m[%d]\x1b[0m", raiz->dado);
}

arvore remover (int valor, arvore* raiz) {
	int v = valor;
	arvore aux = NULL;
	arvore elemento = (*raiz);

	while(elemento != NULL){

		if(elemento->dado == v) {

			if(elemento->esq == NULL && elemento->dir == NULL && elemento->cor == PRETO) {
				arvore duploPreto = (arvore) malloc(sizeof(arvore));
				duploPreto->cor = DUPLOPRETO;
			  duploPreto->pai = elemento->pai;

				if(eh_filho_direito(elemento)){
					elemento->pai->dir = duploPreto;
				}else{
					elemento->pai->esq = duploPreto;
				}

				free(elemento);
				remover_auxiliar(raiz, duploPreto);
				break;
			}

			if(elemento->esq == NULL && elemento->dir == NULL && elemento->cor == VERMELHO) {
				if(eh_filho_esquerdo(elemento)){
					elemento->pai->esq = NULL;
					elemento = NULL;
					break;
				}else{
					elemento->pai->dir = NULL;
					elemento = NULL;
					break;
				}
			}

			if(elemento->esq == NULL) {
				aux = elemento;
				elemento = elemento->dir;
				if(eh_filho_direito(aux)){
					aux->pai->dir = elemento;
				}else{
					aux->pai->esq = elemento;
				}
				free(elemento->dir);
				break;
			}

			if(elemento->dir == NULL) {
				aux = elemento;
				elemento = elemento->esq;
				if(eh_filho_direito(aux)){
					aux->pai->dir = elemento;
				}else{
					aux->pai->esq = elemento;
				}
				free(elemento->esq);
				break;
			}

			elemento->dado = maior_elemento(elemento->esq);
			v = elemento->dado;
			elemento = elemento->esq;
			continue;
		}
		if(v > elemento->dado) {
				elemento = elemento->dir;
				continue;
		} else {
				elemento = elemento->esq;
				continue;
		}
	}
	return (*raiz);
}

void remover_auxiliar(arvore* raiz, arvore elemento){
	int flag = 1;

	while(flag){

		if (eh_raiz(elemento)) {
			remover_caso1(elemento);
			flag = 0;
			continue;
		}

		if(elemento->pai->cor == PRETO && cor(irmao(elemento)) == VERMELHO && cor(sobrinho_esq(elemento)) == PRETO
				&& cor(sobrinho_esq(elemento)) == PRETO){

			remover_caso2(raiz, elemento);
		}

		if(elemento->pai->cor == PRETO && cor(irmao(elemento)) == PRETO && cor(sobrinho_dir(elemento)) == PRETO
				&& cor(sobrinho_esq(elemento)) == PRETO){

					remover_caso3(elemento);
					arvore aux = elemento;
					elemento = elemento->pai;
					if(eh_filho_direito(aux)){
						aux->pai->dir = aux->dir;
					}else{
						aux->pai->esq = aux->esq;
					}
					aux = NULL;
		}

		if(elemento->pai->cor == VERMELHO && cor(irmao(elemento)) == PRETO && cor(sobrinho_dir(elemento)) == PRETO
				&& cor(sobrinho_esq(elemento)) == PRETO){

			remover_caso4(elemento);
			flag = 0;
			continue;
		}

		if(cor(irmao(elemento)) == PRETO && cor(sobrinho_dir(elemento)) == PRETO && cor(sobrinho_esq(elemento)) == VERMELHO){
			remover_caso5(raiz, elemento);
		}else if(cor(irmao(elemento)) == PRETO && cor(sobrinho_dir(elemento)) == VERMELHO && cor(sobrinho_esq(elemento)) == PRETO){
			remover_caso5(raiz, elemento);
		}

		if (cor(irmao(elemento)) == PRETO && cor(sobrinho_dir(elemento)) == VERMELHO) {
			remover_caso6A(raiz, elemento);
			flag = 0;
			continue;
		} else if (cor(irmao(elemento)) == PRETO && cor(sobrinho_esq(elemento)) == VERMELHO) {
			remover_caso6B(raiz, elemento);
			flag = 0;
			continue;
		}
	}

	ajustar(raiz, elemento->pai);
}

void remover_caso1(arvore elemento){
	elemento = NULL;
}

void remover_caso2(arvore* raiz, arvore elemento){
	if(eh_filho_esquerdo(elemento)){
		rotacao_simples_esquerda(raiz, elemento->pai);
	}else{
		rotacao_simples_direita(raiz, elemento->pai);
	}
	elemento->pai->cor = VERMELHO;
	elemento->pai->pai->cor = PRETO;
}

void remover_caso3(arvore elemento){
	elemento->cor = PRETO;
	elemento->pai->cor = DUPLOPRETO;
	irmao(elemento)->cor = VERMELHO;
}

void remover_caso4(arvore elemento){
	elemento->pai->cor = PRETO;
	irmao(elemento)->cor = VERMELHO;
	if (eh_filho_direito(elemento)) {
		elemento->pai->dir = NULL;
	}else{
		elemento->pai->esq = NULL;
	}
	elemento = NULL;
}

void remover_caso5(arvore* raiz, arvore elemento){
	if(eh_filho_esquerdo(elemento)){
		rotacao_simples_direita(raiz, irmao(elemento));
		irmao(elemento)->cor = PRETO;
		irmao(elemento)->dir->cor = VERMELHO;
	}else{
		rotacao_simples_esquerda(raiz, irmao(elemento));
		irmao(elemento)->cor = PRETO;
		irmao(elemento)->esq->cor = VERMELHO;
	}
}

void remover_caso6A(arvore* raiz, arvore elemento){
	rotacao_simples_esquerda(raiz, elemento->pai);
	elemento->pai->pai->cor = elemento->pai->cor;
	elemento->pai->cor = PRETO;
	tio(elemento)->cor = PRETO;
	elemento->pai->esq = NULL;
	elemento = NULL;
}

void remover_caso6B(arvore* raiz, arvore elemento){
	rotacao_simples_direita(raiz, elemento->pai);
	elemento->pai->pai->cor = elemento->pai->cor;
	elemento->pai->cor = PRETO;
	tio(elemento)->cor = PRETO;
	elemento->pai->dir = NULL;
	elemento = NULL;
}
