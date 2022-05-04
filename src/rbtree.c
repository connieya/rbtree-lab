#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

node_t *new_node_t(key_t key)
{
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  new_node->key = key;
  new_node->color = RBTREE_RED;
  return new_node;
}

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *nilNode = (node_t *)calloc(1, sizeof(node_t));
  nilNode->color = RBTREE_BLACK;
  p->nil = nilNode;
  p->root = nilNode;
  p->root->parent = nilNode;
  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  free(t);
}

void rotate_right(rbtree *t, node_t *temp)
{
  node_t *left_child = temp->left;
  temp->left = left_child->right;
  if (left_child->right != t->nil)
  {
    left_child->right->parent = temp;
  }
  left_child->parent = temp->parent;
  if (temp->parent == t->nil)
  {
    t->root = left_child;
  }
  else if (temp == temp->parent->left)
  {
    temp->parent->left = left_child;
  }
  else
  {
    temp->parent->right = left_child;
  }
  left_child->right = temp;
  temp->parent = left_child;
}

void rotate_left(rbtree *t, node_t *temp)
{
  node_t *right_child = temp->right;
  temp->right = right_child->left;
  if (right_child->left != t->nil)
  {
    right_child->left->parent = temp;
  }
  right_child->parent = temp->parent;

  if (temp->parent == t->nil)
  {
    t->root = right_child;
  }
  else if (temp == temp->parent->left)
  {
    temp->parent->left = right_child;
  }
  else
  {
    temp->parent->right = right_child;
  }
  right_child->left = temp;
  temp->parent = right_child;
}

void rb_insert_fixup(rbtree *t, node_t *x)
{
  while (x->parent->color == RBTREE_RED)
  {
    if (x->parent == x->parent->parent->left)
    { //  부모가 할아버지의 왼쪽 자식인 경우
      node_t *uncle = x->parent->parent->right;
      if (uncle->color == RBTREE_RED)
      {
        x->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        x->parent->parent->color = RBTREE_RED;
        x = x->parent->parent;
      }
      else
      {
        if (x == x->parent->right)
        {
          x = x->parent;
          rotate_left(t, x);
        }
        x->parent->color = RBTREE_BLACK;
        x->parent->parent->color = RBTREE_RED;
        rotate_right(t, x->parent->parent);
      }
    }
    else
    { // 부모가 할아버지의 오른쪽 자식인 경우
      node_t *uncle = x->parent->parent->left;
      if (uncle->color == RBTREE_RED)
      {
        x->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        x->parent->parent->color = RBTREE_RED;
        x = x->parent->parent;
      }
      else
      {
        if (x == x->parent->left)
        {
          x = x->parent;
          rotate_right(t, x);
        }
        x->parent->color = RBTREE_BLACK;
        x->parent->parent->color = RBTREE_RED;
        rotate_left(t, x->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // TODO: implement insert
  node_t *temp = (node_t *)calloc(1, sizeof(node_t));
  node_t *target = t->root;
  node_t *y = t->nil;

  while (target != t->nil)
  {
    y = target;
    if (target->key > key)
    {
      target = target->left;
    }
    else
    {
      target = target->right;
    }
  }

  temp->parent = y;
  if (y == t->nil)
  {
    t->root = temp;
  }
  else if (key < y->key)
  {
    y->left = temp;
  }
  else
  {
    y->right = temp;
  }
  temp->left = t->nil;
  temp->right = t->nil;
  temp->key = key;
  temp->color = RBTREE_RED;
  rb_insert_fixup(t, temp);

  return temp;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  node_t *temp = t->root;
  while (temp != t->nil)
  {
    if (temp->key < key)
    {
      temp = temp->right;
    }
    else if (temp->key > key)
    {
      temp = temp->left;
    }
    else
    {
      return temp;
    }
  }

  return NULL;
}

node_t *rbtree_min(const rbtree *t)
{
  // TODO: implement find
  node_t *node = t->root;
  while (node->left != t->nil)
  {
    node = node->left;
  }

  return node;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  node_t *node = t->root;
  while (node->right != t->nil)
  {
    node = node->right;
  }

  return node;
}

node_t *node_min(rbtree *t, node_t *x)
{
  node_t *temp = x;
  while (temp->left != t->nil)
  {
    temp = temp->left;
  }
  return temp;
}

void rb_transplant(rbtree *t, node_t *u, node_t *v)
{
  if (u->parent == t->nil)
  {
    t->root = v;
  }
  else if (u == u->parent->left)
  {
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

void rb_erase_fixup(rbtree *t, node_t *temp)
{
  // TODO: implement erase 
  while (temp != t->root && temp->color == RBTREE_BLACK)
  {
    if (temp == temp->parent->left)
    {
      node_t * sibling = temp->parent->right;
      if (sibling->color == RBTREE_RED)
      {
        sibling->color = RBTREE_BLACK;
        temp->parent->color = RBTREE_RED;
        rotate_left(t, temp->parent);
        sibling = temp->parent->right;
      }
      
      if (sibling->left->color == RBTREE_BLACK && sibling->right->color == RBTREE_BLACK)
      {
        sibling->color = RBTREE_RED;
        temp = temp->parent;
      }
      else
      {
      
        if (sibling->right->color == RBTREE_BLACK)
        {
          sibling->left->color = RBTREE_BLACK;
          sibling->color = RBTREE_RED;
          rotate_right(t, sibling);
          sibling = temp->parent->right;
        }
        
        sibling->color = temp->parent->color;
        temp->parent->color = RBTREE_BLACK;
        sibling->right->color = RBTREE_BLACK;
        rotate_left(t, temp->parent);
        temp = t->root;
      }
    }
   
    else
    {
      node_t *sibling = temp->parent->left;
     
      if (sibling->color == RBTREE_RED)
      {
        sibling->color = RBTREE_BLACK;
        temp->parent->color = RBTREE_RED;
        rotate_right(t, temp->parent);
        sibling = temp->parent->left;
      }
    
      if (sibling->right->color == RBTREE_BLACK && sibling->left->color == RBTREE_BLACK)
      {
        sibling->color = RBTREE_RED;
        temp = temp->parent;
      }
      else
      {
       
        if (sibling->left->color == RBTREE_BLACK)
        {
          sibling->right->color = RBTREE_BLACK;
          sibling->color = RBTREE_RED;
          rotate_left(t, sibling);
          sibling = temp->parent->left;
        }
        
        sibling->color = temp->parent->color;
        temp->parent->color = RBTREE_BLACK;
        sibling->left->color = RBTREE_BLACK;
        rotate_right(t, temp->parent);
        temp = t->root;
      }
    }
  }
  temp->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *z)
{
  // TODO: implement erase
  node_t *y = z;
  node_t *x = t->nil;

  color_t original_color = y->color;

  if (z->left == t->nil)
  {
    x = z->right;
    rb_transplant(t, z, z->right);
  }
  else if (z->right == t->nil)
  {
    x = z->left;
    rb_transplant(t, z, z->left);
  }
  else
  {
    y = node_min(t, z->right);
    original_color = y->color;
    x = y->right;
    if (y->parent == z)
    {
      x->parent = z;
    }
    else
    {
      rb_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    rb_transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }

  if (original_color == RBTREE_BLACK)
  {
    // rb_erase_fixup(t, x);
  }
  free(z);

  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
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
