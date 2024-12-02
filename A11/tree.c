#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

struct tree_node* find(const char* name, struct tree_node* root){
  if(root == NULL){
    return NULL;
  }else if(strcmp(name, root->data.name) < 0){
    return(find(name, root->left));
  }else if(strcmp(name, root->data.name) > 0){
    return(find(name, root->right));
  }else{
    return root;
  }
}

struct tree_node* insert(const char* name, struct tree_node* root){
  if( root == NULL ){
    root = (struct tree_node*)malloc(sizeof(struct tree_node));
    strcpy(root->data.name, name);
    root->left = NULL;
    root->right = NULL;
  }else{
    if( strcmp(name, root->data.name) < 0 ){
      root->left = insert( name, root->left );
      }
    if( strcmp(name, root->data.name) > 0 ){
      root->right = insert( name, root->right );
      }
  }
  return root;
}

void clear(struct tree_node* root){
  if (root == NULL) {
    return; 
  }
  clear(root->left);
  clear(root->right);
  free(root);
}

int depth = 0;

void print(struct tree_node* root){
  if ( root == NULL ){
    return;
  }
  printf("%s\n", root->data.name);
  depth++;
  if(root->left != NULL){
    for(int i = 0; i < depth; i++){
      printf(" ");
    }
    printf("l:");
    print(root->left);
  }
  if(root->right != NULL){
    for(int i = 0; i < depth; i++){
      printf(" ");
    }
    printf("r:");
    print(root->right);
  }
}

void printSorted(struct tree_node* root){
  if ( root == NULL ){
    return;
  }
  printSorted(root->left);
  printf("%s\n", root->data.name);
  printSorted(root->right);
}
