
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

struct arvore{
    int n, fb;

    struct arvore *esquerda;
    struct arvore *direita;
    struct arvore *pai;
};

struct arvore *raiz = NULL;

void menu();
void insere();
void exibir_ordenado(struct arvore*);
void remove_p();
void remover(struct arvore*);
struct arvore* menor_direita(struct arvore*);
struct arvore* buscar(int);
void limpar_arvore(struct arvore*);
int altura(struct arvore*);
struct arvore* balanceia(struct arvore*);
struct arvore* rot_direita(struct arvore*);
struct arvore* rot_esquerda(struct arvore*);

int main(){
    char op[MAX];
    char ins[]="i";
    char remove[]="r";
        scanf("%s", op);
	getchar();
	while (!feof(stdin)){

        if (strcmp(op,ins)==0){
		insere();
	}
        else{
		if (strcmp(op,remove)==0)
                	remove_p();
		else
			printf("Entrada Inválida");
		
	}
	scanf("%s", op);
	}
        exibir_ordenado(raiz);
	limpar_arvore(raiz);
}


void insere(){
    struct arvore *aux1 = NULL, *aux2 = NULL;
    int n;

    scanf("%d", &n);

    if(!raiz){
        raiz = (struct arvore*) malloc(sizeof(struct arvore));

        if(!raiz){
            printf("Erro ao alocar =(\n");
            exit(1);
        }

        raiz->n = n;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
        raiz->pai = NULL;

        raiz->fb = 0;
    }

    else{
        aux1 = raiz;
        aux2 = aux1;

        while(aux2){
            if(n < aux2->n){
                aux2 = aux2->esquerda;

                if(!aux2){
                    aux1->esquerda = (struct arvore*) malloc(sizeof(struct arvore));

                    if(!aux1->esquerda){
                        printf("Erro ao alocar =(\n");
                        exit(1);
                    }

                    aux2 = aux1->esquerda;

                    aux2->esquerda = NULL;
                    aux2->direita = NULL;
                    aux2->pai = aux1;
                    aux2->n = n;
                    break;
                }
                else{
                    aux1 = aux2;
                }
            }

            else{
                aux2 = aux2->direita;

                if(!aux2){
                    aux1->direita = (struct arvore*) malloc(sizeof(struct arvore));

                    if(!aux1->direita){
                        printf("Erro ao alocar =(\n");
                        exit(1);
                    }

                    aux2 = aux1->direita;

                    aux2->esquerda = NULL;
                    aux2->direita = NULL;
                    aux2->pai = aux1;
                    aux2->n = n;
                    break;
                }

                else{
                    aux1 = aux2;
                }
            }
        }
    }
    getchar();

    if(aux2){
        while(aux2){
            aux2->fb = altura(aux2->direita) - altura(aux2->esquerda);

            if(aux2->fb > 1 || aux2->fb < -1){
                aux2 = balanceia(aux2);
            }

            aux2 = aux2->pai;
        }
    }
}

void exibir_ordenado(struct arvore *aux){
    int flag;
    if(!raiz){
        printf("Arvore vazia!");
        return;
    }

    if(aux){
        exibir_ordenado(aux->esquerda);
	flag=altura(aux);
        printf("%d,%d\n", aux->n,flag);
        exibir_ordenado(aux->direita);
    }
}

void remove_p(){
    struct arvore *aux;
    int n;

    scanf("%d", &n);

    aux = buscar(n);

    if(aux){
        remover(aux);
    }

    else{
        printf("O numero nao existe na arvore!\n");
    }
}

void remover(struct arvore *aux){
    struct arvore *aux2, *salva = aux->pai;

    if(aux != raiz){
        if(!aux->esquerda && !aux->direita){
            if(aux->n < aux->pai->n){
                aux->pai->esquerda = NULL;
            }
            else{
                aux->pai->direita = NULL;
            }

            free(aux);
        }

        else if(!aux->direita){
            if(aux->n < aux->pai->n){
                aux->pai->esquerda = aux->esquerda;
            }
            else{
                aux->pai->direita = aux->esquerda;
            }
            aux->esquerda->pai = aux->pai;
            free(aux);
        }

        else if(!aux->esquerda){
            if(aux->n < aux->pai->n){
                aux->pai->esquerda = aux->direita;
            }
            else{
                aux->pai->direita = aux->direita;
            }
            aux->direita->pai = aux->pai;
            free(aux);
        }

        else{
            aux2 = menor_direita(aux->direita);
            aux->n = aux2->n;

            remover(aux2);
        }
    }

    else{
        if(!aux->esquerda && !aux->direita){
            free(aux);
            raiz = NULL;
        }

        else if(!aux->direita){
            aux->esquerda->pai = NULL;
            raiz = aux->esquerda;
            free(aux);
        }

        else if(!aux->esquerda){
            aux->direita->pai = NULL;
            raiz = aux->direita;
            free(aux);
        }

        else{
            aux2 = menor_direita(aux->direita);
            aux->n = aux2->n;

            remover(aux2);
        }
    }

    if(salva){
        while(salva){
            salva->fb = altura(salva->direita) - altura(salva->esquerda);

            if(salva->fb > 1 || salva->fb < -1){
                salva = balanceia(salva);
            }

            salva = salva->pai;
        }
    }
}

struct arvore* menor_direita(struct arvore *aux){
    while(aux->esquerda){
        aux = aux->esquerda;
    }

    return aux;
}

struct arvore* buscar(int n){
    struct arvore *aux;

    aux = raiz;

    while(aux && aux->n != n){
        if(n < aux->n){
            aux = aux->esquerda;
        }

        else{
            aux = aux->direita;
        }
    }

    return aux;
}

void limpar_arvore(struct arvore *aux){
    if(aux->esquerda){
        limpar_arvore(aux->esquerda);
    }

    if(aux->direita){
        limpar_arvore(aux->direita);
    }

    free(aux);
    raiz = NULL;
}


int altura(struct arvore *aux){
    int ae = 0;
    int ad = 0;
    if(!aux){
        return 0;
    }
    ae = altura(aux->esquerda);
    ad = altura(aux->direita);

    return (ae > ad) ? ae + 1: ad + 1;
}


struct arvore* rot_direita(struct arvore *aux){
    struct arvore *esq = aux->esquerda;

    aux->esquerda = esq->direita;
    esq->direita = aux;

    if(aux->esquerda){
        aux->esquerda->pai = aux;
    }

    esq->pai = aux->pai;
    aux->pai = esq;

    if(aux == raiz){
        raiz = esq;
    }

    if(esq->pai){
        if(esq->n < esq->pai->n){
            esq->pai->esquerda = esq;
        }
        else{
            esq->pai->direita = esq;
        }
    }

    esq->fb = altura(esq->direita) - altura(esq->esquerda);
    aux->fb = altura(aux->direita) - altura(aux->esquerda);

    return esq;
}

struct arvore* rot_esquerda(struct arvore *aux){
    struct arvore *dir = aux->direita;

    aux->direita = dir->esquerda;
    dir->esquerda = aux;

    if(aux->direita){
        aux->direita->pai = aux;
    }

    dir->pai = aux->pai;
    aux->pai = dir;

    if(aux == raiz){
        raiz = dir;
    }

    if(dir->pai){
        if(dir->n < dir->pai->n){
            dir->pai->esquerda = dir;
        }
        else{
            dir->pai->direita = dir;
        }
    }

    dir->fb = altura(dir->direita) - altura(dir->esquerda);
    aux->fb = altura(aux->direita) - altura(aux->esquerda);
    return dir;
}

struct arvore* balanceia(struct arvore *aux){
    if(aux->fb < -1){
        if(aux->esquerda->fb > 0){
            aux->esquerda = rot_esquerda(aux->esquerda);
        }

        aux = rot_direita(aux);
    }

    else if(aux->fb > 1){
        if(aux->direita->fb < 0){
            aux->direita = rot_direita(aux->direita);
        }

        aux = rot_esquerda(aux);
    }

    return aux;
}
