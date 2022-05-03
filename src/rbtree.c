#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

// typedef struct node_t
// {
//   color_t color;
//   key_t key;
//   struct node_t *parent, *left, *right;
// } node_t;

// typedef struct
// {
//   node_t *root;
//   node_t *nil; // for sentinel
// } rbtree;

rbtree *new_rbtree(void) {
      rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
      // TODO: initialize struct if needed
      return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  if (t->root == NULL)
  {
      node_t *tmp = (node_t *)calloc(1, sizeof(node_t));
      tmp->key = key;
      tmp->color = RBTREE_RED;
      t->root = tmp;
      return tmp; /* code */
  }

  node_t *r = t->root;

  while (r != NULL) {
    if (r->key > key)
    {
      r->left->parent = r;
      r = r->left;
      
    }else
    {
      r->right->parent = r;
      r = r->right;
    }
  }
  r->key = key;
  r->color = RBTREE_RED;
  
  return r;
}

void rotate_left(rbtree * t , node_t *temp){
  node_t *right_child = temp->right;
  temp->right = right_child->left;
  if (temp->right)
  {
    temp->right->parent = temp;
  }
  right_child->parent = temp->parent;
  if (!temp->parent)
  {
    t->root = right_child;
  }else if (temp == temp->parent->left)
  {
    temp->parent->left = right_child;
  }else {
    temp->parent->right = right_child;
  }
  right_child->left = temp;
  temp->parent = right_child;
 
}

void rotate_right(rbtree * t , node_t *temp)
{
  node_t * left_child = temp->left;
  temp->left = left_child->right;
  if (temp->left)
  {
    temp->left->parent = temp;
  }
  left_child->parent = temp->parent;
  if(!temp->parent) {
    t->root = left_child;
  }else if (temp == temp->parent->left){
    temp->parent->left = left_child;
  }else {
    temp->parent->right = left_child;
  }
  left_child->right = temp;
  temp->parent = left_child;
}

void rebuildUncle(){

}

void fixup(rbtree *t, node_t *temp)
{
  node_t * r = t->root;
  while (temp->parent->color = RBTREE_RED)
  {
      if (temp->parent == temp->parent->parent->left) 
      {  //  부모가 할아버지의 왼쪽 자식인 경우
        node_t * uncle = temp->parent->parent->right;
        if (uncle ->color == RBTREE_RED)
        {
          temp->parent->color = RBTREE_BLACK;
          temp->parent = RBTREE_BLACK;
          temp->parent->parent->color = RBTREE_RED;
          temp = temp->parent->parent;
        }else {
          if (temp == temp->parent->right)
          {
            temp = temp->parent;
            rotate_left(t,temp);
          }
          temp->parent->color = RBTREE_BLACK;
          temp->parent->parent->color = RBTREE_RED;
          rotate_right(t,temp->parent->parent);
          
        }
        
      }else { // 부모가 할아버지의 오른쪽 자식인 경우
        node_t * uncle = temp->parent->parent->left;
        if (uncle->color == RBTREE_RED)
        {
          temp->parent->color = RBTREE_BLACK;
          uncle->color = RBTREE_BLACK;
          temp->parent->parent->color = RBTREE_RED;
          temp->parent->parent->color = RBTREE_RED;
          temp =  temp->parent->parent;

        }else {
          if (temp == temp->parent->left)
          {
           temp = temp->parent;
           rotate_right(t,temp);
          }
          temp->parent->color = RBTREE_BLACK;
          temp->parent->parent->color = RBTREE_RED;
          rotate_left(t,temp->parent->parent);
      
        }
        
      }
      t->root->color = RBTREE_BLACK;
  } 
  
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find

  node_t * temp = t->root;
  while(temp != NULL) {
    if(temp->key < key){
        temp = temp->right;
    }else if(temp->key > key) {
        temp = temp->left;
    }else {
      return temp;
    }
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}


// int main() {

//   new_rbtree();
//   printf("hello world \n");
//   rbtree *t = (rbtree *)calloc(1, sizeof(rbtree));
//   node_t *pp = rbtree_insert(t, 102);
//   printf("zzz %p", pp);
// }

