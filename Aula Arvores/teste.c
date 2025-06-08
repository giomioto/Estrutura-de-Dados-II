#include <stdio.h>
#include <stdlib.h>

struct tree {
  char info;
  struct tree *left;
  struct tree *right;
};

struct tree *root; /* primeiro n� da �rvore */

struct tree *stree (struct tree *root, struct tree *r, char info)
{
  if(!r) {
    r = (struct tree *) malloc(sizeof(struct tree));
    if (!r) {
      printf("Sem mem�ria\n");
      system("PAUSE");
      exit (0);
    }
    r->left = NULL;
    r->right = NULL;
    r->info = info;
    if (!root) 
       return r; /* primeira entrada */
    if (info < root->info) 
       root->left = r;
    else root->right = r;
    return r;
  }
  if (info < r->info)
     stree(r, r->left, info);
  else stree(r, r->right, info);
}

void inorder (struct tree *root)
{
  if (!root) return;
  inorder(root->left);
  printf("%c ", root->info);
  inorder(root->right);
}

void postorder(struct tree *root)
{
  if(!root) return;
  postorder(root->left);
  postorder(root->right);
  printf("%c ", root->info);
}

void preorder(struct tree *root)
{
  if (!root) return;
  printf("%c ", root->info);
  preorder(root->left);
  preorder(root->right);
}


void print_tree(struct tree *r, int l)
{
  int i;
  if(r==NULL) return;
  print_tree(r->left, l+1);
  for(i=0; i<l; i++)
     printf("    ");
  printf("%c\n", r->info);
  print_tree(r->right, l+1);
}

int totalNO(struct tree *raiz){
    if (raiz == NULL)
        return 0;
    int alt_esq = totalNO(raiz->left);
    int alt_dir = totalNO(raiz->right);
    return(alt_esq + alt_dir + 1);
}

int main()
{
  char s;
  root = NULL; /* inicializa a árvore */

  printf("Entre com um caractere (espaço para parar): ");
  scanf("%c", &s);
  fflush(stdin);

  while (s != ' ') {
      if (!root) 
         root = stree(root, root, s);
      else stree(root, root, s);

      printf("Entre com um caractere (espaco para parar): ");
      scanf("%c", &s);
      fflush(stdin);
  }

  inorder(root);
  printf("\n");

  preorder(root);
  printf("\n");

  postorder(root);
  printf("\n\n");

  print_tree(root, 0);
  printf("Total de nos = %d\n", totalNO(root));

  system("PAUSE");
  return 0;
}
