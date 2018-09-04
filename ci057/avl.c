#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

/*
* Retorna Ponteiro par no da arvore
*/
no *criar(int data){
   no *t = (no*)malloc(sizeof(no));

   t->data = data;
   t->sad = 0;
   t->sae = 0;
   t->n = 1;
   t->h = 0;
   t->i = 0;
   t->fb = 0;
   return t;
}//fim metodo criar

/*
* Insere no na arvore a partir da raiz
*/
no *inserir(no *raiz, no *n,int *dados){
     no *a;
     a = raiz;
     no *d; //no mais jovem que pode ser desbalanceado
     no *fd; //pai de d
     d = fd = raiz;
     int eSae = 1; //1 - d é sae : 0 - d e sad

     /* Insere No */
     while(1){
              dados[0]++;
              if(n->data == a->data)
                         return raiz;
              if(n->data < a->data){
                         if(a->sae == 0){
                                   a->sae = n;
                                   n->i = (2*a->i)+1;
                                   n->h = a->h +1;
                                   n->n = a->n + 1;
                                   break;
                         }//fim if
                         else{                
                                   if(a->sae->fb > 0){
                                                 fd = a;
                                                 d = a->sae;
                                                 eSae = 1;
                                   }//fim if                                            
                                   a = a->sae;                                                                      
                         }//fim else
              }//fim if
              else{
                         if(a->sad == 0){
                                   a->sad = n;
                                   n->i = (2*a->i)+2;
                                   n->h = a->h +1;
                                   n->n = a->n + 1;
                                   break;
                         }//fim if
                         else{
                                  if(a->sad->fb < 0){
                                                fd = a;
                                                d = a->sad;
                                                eSae = 0;
                                  }//fim if
                                  a = a->sad;
                         }//fim else
              }//fim else
     }//fim while
     
     
     /* Atualiza FBs a partir de d */
     no *t = d;
     while(t != n){
            t->fb = calcfb(t);
            if(n->data < t->data)
                       t = t->sae;
            else if(n->data > t->data)
                       t = t->sad;
     }//fim while
     
     if(d->fb > 1){
                   if(d->sae->fb > 0){
                         if(d == raiz){
                              raiz = rot_dir(d);
                              dados[1]++;
                         }//fim if
                         else
                             if(eSae){
                                     fd->sae = rot_dir(d);
                                     dados[1]++;
                             }//fim if
                             else{
                                     fd->sad = rot_dir(d);
                                     dados[1]++;
                             }//fim else
                   }//fim if
                   else if(d->sae->fb < 0){
                        if(d == raiz){
                             raiz = rot_esq_dir(d);
                             dados[1] += 2;
                        }//fim if
                        else
                            if(eSae){
                                    fd->sae = rot_esq_dir(d);
                                    dados[1] += 2;
                            }//fim if
                            else{
                                    fd->sad = rot_esq_dir(d);
                                    dados[1] += 2;
                            }//fim else
                   }//fim else if                   
     }//fim if
     else if(d->fb < -1){
                   if(d->sad->fb < 0){
                         if(d == raiz){
                              raiz = rot_esq(d); 
                              dados[1]++;
                         }//fim if
                         else
                             if(eSae){
                                     fd->sae = rot_esq(d);
                                     dados[1]++;
                             }//fim if
                             else{
                                     fd->sad = rot_esq(d);
                                     dados[1]++;
                             }//fim else
                   }//fim if
                   else if(d->sad->fb > 0){
                        if(d == raiz){
                             raiz = rot_dir_esq(d);
                             dados[1] += 2;
                        }//fim if
                        else
                            if(eSae){
                                    fd->sae = rot_dir_esq(d);
                                    dados[1] += 2;
                            }//fim if
                            else{
                                    fd->sad = rot_dir_esq(d);
                                    dados[1] += 2;
                            }//fim else
                   }//fim else if
     }//fim else if           
          
     return raiz;
}//fim metodo inserir

/*
* Imprime a arvore
*/
void imprimir(no *n){
     if(n != 0){
         printf("<");
         printf("%d",n->data);
         imprimir(n->sae);
         imprimir(n->sad);
         printf(">");
     }//fim if
}//fim metodo imprimir

/*
* Deleta no da arvore
*/
no *deletar(no *raiz,int chave){
     no *paiDeletar = raiz;
     no *noDeletar = raiz;
     int eSae = 1;
     no *paiSucessor;
     no *sucessor;
     
     //Verifica existencia
     if(pesquisar(raiz,chave) == 0)
                          return raiz;
                          
     //Localiza no pai e a ser deletado
     while(noDeletar->data != chave){
           paiDeletar = noDeletar;
           if(chave < noDeletar->data){
                    eSae = 1;
                    noDeletar = noDeletar->sae;
           }//fim if
           else if(chave > noDeletar->data){
                eSae = 0;
                noDeletar = noDeletar->sad;
           }//fim else if
     }//fim while 
     //Deleta no sem filhos
     if(noDeletar->sae == 0 && noDeletar->sad == 0){
             if(noDeletar != raiz){
                 if(eSae)
                         paiDeletar->sae = 0;
                 else
                         paiDeletar->sad = 0;
             }//fim if
     }//fim if
     //Deleta com filho esquerdo
     else if(noDeletar->sae != 0 && noDeletar->sad == 0){
             if(noDeletar == raiz){
                      raiz = noDeletar->sae;
                      paiDeletar = raiz;
             }//fim if
             else if(eSae)
                     paiDeletar->sae = noDeletar->sae;
             else
                     paiDeletar->sad = noDeletar->sae;
             noDeletar->sae->h = noDeletar->h;
             noDeletar->sae->n = noDeletar->n; 
             noDeletar->sae->i = noDeletar->i;                    
     }//fim else if
     //Deleta com filho direito
     else if(noDeletar->sae == 0 && noDeletar->sad != 0){             
             if(noDeletar == raiz){
                          raiz = noDeletar->sad;             
                          paiDeletar = raiz;
             }//fim if
             else if(eSae)
                  paiDeletar->sae = noDeletar->sad;
             else
                 paiDeletar->sad = noDeletar->sad;
                
             noDeletar->sad->h = noDeletar->h;
             noDeletar->sad->n = noDeletar->n; 
             noDeletar->sad->i = noDeletar->i;
             
     }//fim else if
     //Deleta com filho esquerdo e direito
     else{
          paiSucessor = noDeletar;
          sucessor = noDeletar;
          no *atualSucessor = noDeletar->sad;
          
          while(atualSucessor != 0){
             paiSucessor = sucessor;
             sucessor = atualSucessor;
             atualSucessor = atualSucessor->sae;
          }//fim while          
          sucessor->sae = noDeletar->sae;
          
          if(sucessor != noDeletar->sad){
                      paiSucessor->sae = sucessor->sad;
                      sucessor->sad = noDeletar->sad;
          }//fim if
          sucessor->n = noDeletar->n;
          sucessor->h = noDeletar->h;
          sucessor->i = noDeletar->i;
          
          if(noDeletar == raiz){
                  raiz = sucessor;
                  paiDeletar = raiz;
          }//fim if
          else if(eSae)
                  paiDeletar->sae = sucessor;
          else
                  paiDeletar->sad = sucessor;
     }//fim else        
     
     atualizar(raiz,paiDeletar);
     raiz = balancearDeletar(raiz,raiz,raiz,paiDeletar);
     
     return raiz;     
}//fim metodo deletar

/*
* Balanceia Depois de deletar
*/
no *balancearDeletar(no *raiz,no *fd,no *d,no *n){ 
   if(d != n){
        if(n->data < d->data){
                   balancearDeletar(raiz,d,d->sae,n);
        }//fim if
        else if(n->data > d->data){
                   balancearDeletar(raiz,d,d->sad,n);
        }//fim else if     
   }//fim if
   
   d->fb = calcfb(d);
   if(d == raiz){
        if(raiz->fb > 1){
                    if(raiz->sae->fb >= 0)
                                     raiz = rot_dir(d);
                    else if(raiz->sae->fb < 0)
                                     raiz = rot_esq_dir(d);        
        }//fim if
        else if(raiz->fb < -1){
                    if(raiz->sad->fb <= 0)
                                     raiz = rot_esq(d);
                    else if(raiz->sad->fb > 0)
                                     raiz = rot_dir_esq(d);
        }//fim else if
   }//fim if
   else if(d->fb > 1){
        if(d->sae->fb >= 0){
                      if(fd->sae == d)
                                 fd->sae = rot_dir(d);
                      else if(fd->sad == d)
                                 fd->sad = rot_dir(d);
        }//fim if   
        else if(d->sae->fb <= 0){
                      if(fd->sae == d)
                                 fd->sae = rot_esq_dir(d);
                      else if(fd->sad == d)
                                 fd->sad = rot_esq_dir(d);
        }//fim else if
   }//fim else if
   else if(d->fb < -1){
        if(d->sad->fb < 0){
                      if(fd->sae == d)
                                 fd->sae = rot_esq(d);
                      else if(fd->sad == d)
                                 fd->sad = rot_esq(d);
        }//fim if
        else if(d->sad->fb > 0){
                      if(fd->sae == d)
                                 fd->sae = rot_dir_esq(d);
                      else if(fd->sad == d)
                                 fd->sad = rot_dir_esq(d);
        }//fim else if
   }//fim else if
   
   return raiz;
}//fim metodo balancearDeletar

/*
* Retorna no da arvore especificado pela chave
*/
no *pesquisar(no *raiz,int chave){
   no *t = raiz;     
   while(raiz != 0){
              if(raiz->data == chave)
                       return raiz;
              else if(chave < raiz->data)
                       raiz = raiz->sae;
              else
                       raiz = raiz->sad;
   }//fim while
   return 0;
}//fim metodo pesquisar

/*
* Percurso em pré-ordem
*/
void preordem(no *raiz){
     if(raiz != 0){
             printf("%d ",raiz->data);
             preordem(raiz->sae);
             preordem(raiz->sad);
     }//fim if
}//fim metodo preordem

/*
* Percurso em ordem
*/
void ordem(no *raiz){
     if(raiz != 0){             
             ordem(raiz->sae);
             printf("%d,%d",raiz->data,altura(raiz));
             ordem(raiz->sad);
     }//fim if
}//fim metodo ordem

/*
* Percurso em pos-ordem
*/
void posordem(no *raiz){
     if(raiz != 0){
             posordem(raiz->sae);
             posordem(raiz->sad);
             printf("%d ",raiz->data);
     }//fim if
}//fim metodo posordem

/*
* retorna valor da altura do no
*/
int altura(no *n){
     int asae,asad;
     if(n == 0)
          return -1;
     else{
          asae = altura(n->sae);
          asad = altura(n->sad);
          if(asae < asad)
                  return asad + 1;
          else
                  return asae + 1;
     }//fim else
}//fim metodo altura

/*
* calcula fator de balanceamento do no
*/
int calcfb(no *n){
    return altura(n->sae) - altura(n->sad);
}//fim metodo calcfb

/*
* Rotação Simples a Direita
*/
no *rot_dir(no *t){
   no *u;
   u = t->sae;
   t->sae = u->sad;
   u->sad = t;
   t->fb = 0;
   
   u->n = t->n;
   u->h = t->h;
   u->i = t->i;
   u->fb = calcfb(u);  
   
   return u;
}//fim metodo rot_dir

/*
* Rotação Simples a Esquerda
*/
no *rot_esq(no *t){
   no *u;
   u = t->sad;
   t->sad = u->sae;
   u->sae = t;
   t->fb = 0;

   u->n = t->n;
   u->h = t->h;
   u->i = t->i;
   u->fb = calcfb(u);

   return u;
}//fim metodo rot_esq


/*
* Rotação Dupla ED
*/
no *rot_esq_dir(no *t){
   no *u,*v;
   u = t->sae;
   v = u->sad;
   u->sad = v->sae;
   v->sae = u;
   t->sae = v->sad;
   v->sad = t;
   if(v->fb == -1)
            t->fb = 1;
   else
            t->fb = 0;
   if(v->fb == 1)
            u->fb = -1;
   else
            u->fb = 0;
   v->n = t->n;
   v->h = t->h;
   v->i = t->i;
   v->fb = calcfb(v); 
   return v;
}//fim metodo rot_esq_dir


/*
* Rotaçao Dupla DE
*/
no *rot_dir_esq(no *t){
   no *u,*v;
   u = t->sad;
   v = u->sae;
   u->sae = v->sad;
   v->sad = u;
   t->sad = v->sae;
   v->sae = t;
   if(v->fb == 1)
            t->fb = -1;
   else
            t->fb = 0;
   if(v->fb == -1)
            u->fb = 1;
   else
            u->fb = 0;
            
   v->n = t->n;
   v->h = t->h;
   v->i = t->i;
   v->fb = calcfb(v); 
            
   return v;
}//fim metodo rot_dir_esq

/*
* Atualiza Informaçoes dos nos das arvores
*/
void atualizar(no *p, no *n){
     if(n != 0){
         if(p == n);
         else{
              n->i = (2*p->i)+1;
              n->h = p->h +1;
              n->n = p->n + 1;
              n->fb = calcfb(n);
         }//fim else
         atualizar(n,n->sae);
         atualizar(n,n->sad);
     }//fim if
}//fim metodo atualizar

int main(int argc, char **argv)
{
	no *raiz;
	char buffer[1];
	char insere[]= "i";
	int chave;
	FILE *arq;

	arq=fopen(argv[1],"r");
	if (arq==NULL){
		printf("%s\n", argv[1]);
		return 1;
	}

	fgets (buffer, sizeof(buffer), arq);
	if (strcmp(buffer, "i") != 0||strcmp (buffer, "r ") != 0)
		printf("operação inválida %s\n", argv[1]);
	fscanf (arq, "%d", &chave);
	printf ("%d", chave);
	if (strcmp (buffer, "i") == 0)

		raiz=inserir (raiz,chave,1);
	else
		deletar (raiz,chave);
	ordem (raiz);
	return 0;
}
