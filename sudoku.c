#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  if (n == NULL) return 0;

    for (int i = 0; i < 9; i++) {
        int marcas_fila[10] = {0};
        for (int j = 0; j < 9; j++) {
            if (n->sudo[i][j] != 0) {
                if (marcas_fila[n->sudo[i][j]] == 1) {
                    return 0;
                }
                marcas_fila[n->sudo[i][j]] = 1;
            }
        }
    }

    for (int j = 0; j < 9; j++) {
        int marcas_columna[10] = {0};
        for (int i = 0; i < 9; i++) {
            if (n->sudo[i][j] != 0) {
                if (marcas_columna[n->sudo[i][j]] == 1) {
                    return 0;
                }
                marcas_columna[n->sudo[i][j]] = 1;
            }
        }
    }

    for (int k = 0; k < 9; k++) {
        int marcas_submatriz[10] = {0};
        for (int p = 0; p < 9; p++){
            int r = 3*(k/3) + (p/3) ;
            int c = 3*(k%3) + (p%3) ;
            if (n->sudo[r][c] != 0) {
                if (marcas_submatriz[n->sudo[r][c]] == 1) {
                    return 0;
                }
                marcas_submatriz[n->sudo[r][c]] = 1;
            }
        }
    }
    return 1;
}


List* get_adj_nodes(Node* n){
    List* lista_adyacentes = createList();
    if (n == NULL) return lista_adyacentes;

    int primera_fila_vacia = -1;
    int primera_columna_vacia = -1;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                primera_fila_vacia = i;
                primera_columna_vacia = j;
                goto casilla_vacia_encontrada_completo;
            }
        }
    }

casilla_vacia_encontrada_completo:
    if (primera_fila_vacia == -1) {
        return lista_adyacentes;
    }

    for (int numero_a_colocar = 1; numero_a_colocar <= 9; numero_a_colocar++) {
        Node* nodo_adyacente = copy(n);
        nodo_adyacente->sudo[primera_fila_vacia][primera_columna_vacia] = numero_a_colocar;
        
        if (is_valid(nodo_adyacente)) {
            pushBack(lista_adyacentes, nodo_adyacente);
        } else {
            free(nodo_adyacente);
        }
    }
    return lista_adyacentes;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/