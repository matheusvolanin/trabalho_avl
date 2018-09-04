struct No{
       int data;
       struct No *sae;
       struct No *sad;
       int n;
       int h;
       int i;
       int fb;
};
typedef struct No no;

//Prototipos
no *criar(int);
no *inserir(no *, no *,int *);
void imprimir(no *);
no *deletar(no *,int);
no *balancearDeletar(no *,no *,no *,no *);
no *pesquisar(no *,int);
void preordem(no *);
void ordem(no *);
void posordem(no *);
int altura(no *);
int calcfb(no *);
no *rot_dir(no *);
no *rot_esq(no *);
no *rot_esq_dir(no *);
no *rot_dir_esq(no *t);
void atualizar(no *, no *);
