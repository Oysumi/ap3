#include "tree_primitives.h"
#include <stdlib.h>
#include <stdio.h>

/* Restitue un arbre vide */
tree_t cons_empty()
{
  return NULL ;
}

/* Restitue un arbre de racine v et dont les fils sont fg et fd */
tree_t cons(s_base_t v, tree_t fg, tree_t fd)
{
  tree_t t = (tree_t)malloc(sizeof(s_node_t)) ;
  t->val = v ;
  t->fg = fg ;
  t->fd = fd ;
  
  return t ;
}

/* Vrai si et seulement si l'arbre est vide */
int is_empty(tree_t a)
{
  return a==NULL ;
}

/* Restitue la valeur du nœud racine, fonction aussi appelée Racine/root dans 
 * le sujet. 
 * L'arbre a ne doit pas etre pas vide
*/
s_base_t value(tree_t a)
{
  return a->val ;
}

/* Restitue le fils gauche 
 * L'arbre a ne doit pas etre pas vide
 */
tree_t left(tree_t a)
{
  return a->fg ;
}

/* Restitue le fils droit 
 * L'arbre a ne doit pas etre pas vide
*/
tree_t right(tree_t a)
{
  return a->fd ;
}

/* Remplace la valeur de la racine pa par new_value. Version légère avec simple
 * pointeur. 
 * L'arbre a ne doit pas etre pas vide
*/
void change_value(tree_t pa, s_base_t new_value)
{
  pa->val = new_value ;
}

/* Remplace le fils gauche de pa par new_left. Version légère avec simple
 * pointeur. 
 * L'arbre a ne doit pas etre pas vide
*/
void change_left(tree_t pa, tree_t new_left)
{
  tree_t fg = pa->fg ;
  pa->fg = new_left ;
  if (!is_empty(fg)){
    free(fg) ;
  }
}

/* Remplace le fils droit de pa par new_right. Version légère avec simple
 * pointeur. 
 * L'arbre a ne doit pas etre pas vide
*/
void change_right(tree_t pa, tree_t new_right)
{
  tree_t fd = pa->fd ;
  pa->fd = new_right ;
  if (!is_empty(fd)){
    free(fd) ;
  }
}

/* Libère la mémoire allouée pour l'arbre a */
void free_tree(tree_t a)
{
  if (!is_empty(a)){
    free_tree(right(a)) ;
    free_tree(left(a)) ;
    free(a) ;
  }
}

/* Affichage préfixe de l'arbre */
void prefix(tree_t a)
{
  if (!is_empty(a)){
    print(value(a));
    prefix(left(a));
    prefix(right(a));
  }
}

/* Affichage avec mise en forme "graphique" (indentation en fonction de la
 * profondeur) */
void graphical_print(tree_t a, int depth)
{
  if (!is_empty(a)){
    int i ;
    for (i=0; i<depth; i++){
      printf(" ");
    }
    printf("+--");
    print(a->val);
    printf("\n");
    // Appels récursifs sur le fils gauche, en augmentant le décalage
    graphical_print(left(a), depth+3);
    // Appels récursifs sur le fils droit, en augmentant le décalage
    graphical_print(right(a), depth+3);
  }
}

/* Retourne la taille de l'arbre a */
int size(tree_t a)
{
  int res = 0 ;
  
  if (!is_empty(a)){
    res = 1 + size(left(a)) + size(right(a)) ;
  }
  return res ;
}

/* Retourne la hauteur de l'arbre a */
int height(tree_t a)
{
  int res = 0 ;
  
  if (!is_empty(a)){
    int height_fg = height(left(a)) ;
    int height_fd = height(right(a)) ;
    res = 1 + ((height_fg) > (height_fd) ? height_fg : height_fd);
  }
  return res ; 
}

/* Teste l'existence de la donnée v dans l'arbre a */
int exists(tree_t a, s_base_t v)
{
  int res = 0 ;
  
  if (!is_empty(a)){ 
    if (!compare(v, a->val)){ // si la valeur v est égale à la racine (!compare signifie compare = 0)
      res = 1 ;
    } else { // la valeur v ne correspond pas à la racine
      res = exists(left(a), v) ;
      if (!res){ // la valeur v n'est pas dans la feuille gauche
        res = exists(right(a), v) ;
      }
    }
  }
  
  return res ;
}

/* Teste si un arbe est dégéneré (option, non dans le sujet) */
int is_degenerated(tree_t a)
{
  int deg=1;
  if (!is_empty(a)) {
    if (is_empty(left(a))) {
      if (is_empty(right(a))) {
        deg=1;
      } else {
        deg=is_degenerated(right(a));
      }
    } else { 
      if (!is_empty(right(a))) {
        deg=0;
      } else {
        deg=is_degenerated(left(a));
      }
    }
  }
  return deg;
}