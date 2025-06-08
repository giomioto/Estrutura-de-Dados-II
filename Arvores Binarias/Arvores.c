/**********************************************************
 *                                                        *
 *        ██    ██ ███████ ███████ ██████  ██████         *
 *        ██    ██   ██    ██      ██   ██ ██   ██        *
 *        ██    ██   ██    █████   ██████  ██████         *
 *        ██    ██   ██    ██      ██      ██   ██        *
 *         ██████    ██    ██      ██      ██   ██        *
 *                                                        *
 *        Estudante: Giovanni Mioto - RA: 2603454         *
 *        Exercício 1 - ED2: Árvores Binárias             *
 *                                                        *
 **********************************************************/

#include <stdio.h>
#include <stdlib.h>

struct tree {
  int info;
  struct tree *left;
  struct tree *right;
};

struct tree *root; /* primeiro nó da arvore */

struct tree *stree (struct tree *root, struct tree *r, int info)
{
  if(!r) {
    r = (struct tree *) malloc(sizeof(struct tree));
    if (!r) {
      printf("Sem memoria\n");
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
  printf("%d ", root->info);
  inorder(root->right);
}

void postorder(struct tree *root)
{
  if(!root) return;
  postorder(root->left);
  postorder(root->right);
  printf("%d ", root->info);
}

void preorder(struct tree *root)
{
  if (!root) return;
  printf("%d ", root->info);
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
  printf("%d\n", r->info);
  print_tree(r->right, l+1);
}

int totalNO(struct tree *root){
    if (root == NULL)
        return 0;
    int alt_esq = totalNO(root->left);
    int alt_dir = totalNO(root->right);
    return(alt_esq + alt_dir + 1);
}

void maiorNumero(struct tree *root){
    if (root->right != NULL) {
        maiorNumero(root->right);
    } else {
        printf("%d\n", root->info);
    }
}

void menorNumero(struct tree *root){
    if (root->left != NULL) {
        menorNumero(root->left);
    } else {
        printf("%d\n", root->info);
    }
}

int quantidadeNos(struct tree *root){
    if (!root)
        return 0;
    int alt_esq = quantidadeNos(root->left);
    int alt_dir = quantidadeNos(root->right);
    return(alt_esq + alt_dir + 1);
}

int somaNos(struct tree *root){
    if (!root)
        return 0;
    int alt_esq = somaNos(root->left);
    int alt_dir = somaNos(root->right);
    return(alt_esq + alt_dir + root->info);
}

void mostrarFilhos(struct tree *root){
    if (root == NULL) {
        printf("A arvore esta vazia\n");
        return;
    }
    if (root->left != NULL) {
        printf("Filho esquerdo: %d\n", root->left->info);
    } else {
        printf("Nao tem filho esquerdo\n");
    }
    if (root->right != NULL) {
        printf("Filho direito: %d\n", root->right->info);
    } else {
        printf("Nao tem filho direito\n");
    }
}

void mostrarFilhosDoNo(struct tree *root, int valor){
    if (!root) {
        printf("A arvore esta vazia\n");
        return;
    }
    if (root->info == valor) {
        mostrarFilhos(root);
        return;
    }
    if (valor < root->info) {
        mostrarFilhosDoNo(root->left, valor);
    } else {
        mostrarFilhosDoNo(root->right, valor);
    }
    printf("Valor %d nao encontrado na arvore\n", valor);
}

void caminhoeProfundidadeNo(struct tree *root, int valor){
  static int profundidade = 0;
  if (!root) {
    printf("A arvore esta vazia ou valor nao encontrado\n");
    return;
  }
  printf("%d - ", root->info);
  if (root->info == valor) {
    printf("\nValor %d encontrado na arvore na profundidade %d\n", valor, profundidade);
    return;
  }
  profundidade++;
  if (valor < root->info) {
    caminhoeProfundidadeNo(root->left, valor);
  } else {
    caminhoeProfundidadeNo(root->right, valor);
  }
  profundidade--;
}

int main()
{
  int num;
  int opcao, valor;
  do {
    system("cls"); // Limpa a tela
    printf("\nMenu:\n");
    printf("1. Preencher a arvore\n");
    printf("2. Exibir em ordem (inorder)\n");
    printf("3. Exibir em pre-ordem (preorder)\n");
    printf("4. Exibir em pos-ordem (postorder)\n");
    printf("5. Exibir arvore formatada\n");
    printf("6. Exibir total de nos\n");
    printf("7. Exibir maior numero da arvore\n");
    printf("8. Exibir menor numero da arvore\n");
    printf("9. Exibir quantidade de nos\n");
    printf("10. Exibir soma dos nos\n");
    printf("11. Mostrar filhos de um no\n");
    printf("12. Mostrar caminho e profundidade de um no\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    fflush(stdin);

    system("cls"); // Limpa a tela antes de executar a opção

    switch (opcao) {
      case 1:
        root = NULL; /* inicializa a árvore */
        printf("Entre com um numero (0 para parar): ");
        scanf("%d", &num);
        fflush(stdin);

        while (num != 0) {
            if (!root) 
               root = stree(root, root, num);
            else stree(root, root, num);

            printf("Entre com um numero (0 para parar): ");
            scanf("%d", &num);
            fflush(stdin);
        }
        break;
      case 2:
        printf("Inorder: ");
        inorder(root);
        printf("\n");
        break;
      case 3:
        printf("Preorder: ");
        preorder(root);
        printf("\n");
        break;
      case 4:
        printf("Postorder: ");
        postorder(root);
        printf("\n");
        break;
      case 5:
        printf("Arvore formatada:\n");
        print_tree(root, 0);
        break;
      case 6:
        printf("Total de nos = %d\n", totalNO(root));
        break;
      case 7:
        printf("Maior numero da arvore: ");
        maiorNumero(root);
        break;
      case 8:
        printf("Menor numero da arvore: ");
        menorNumero(root);
        break;
      case 9:
        printf("Quantidade de nos = %d\n", quantidadeNos(root));
        break;
      case 10:
        printf("Soma dos nos = %d\n", somaNos(root));
        break;
      case 11:
        printf("Digite o valor do no: ");
        scanf("%d", &valor);
        fflush(stdin);
        printf("Filhos do no %d:\n", valor);
        mostrarFilhosDoNo(root, valor);
        break;
      case 12:
        printf("Digite o valor do no: ");
        scanf("%d", &valor);
        fflush(stdin);
        printf("Caminho do no %d: ", valor);
        caminhoeProfundidadeNo(root, valor);
        printf("\n");
        break;
      case 0:
        printf("Saindo...\n");
        break;
      default:
        printf("Opcao invalida! Tente novamente.\n");
    }

    if (opcao != 0) {
      printf("\nPressione qualquer tecla para voltar ao menu...\n");
      getchar();
    }
  } while (opcao != 0);
  return 0;
}
