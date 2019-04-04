#include "stack6.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct stack *init(int size)	// initialize stack. Returns pointer to
{                            //  to initialized stack of desired size
  struct stack *sp = (struct stack*) malloc(sizeof(struct stack));
  if(sp == NULL)
  return NULL;

  sp->size = size;
  sp->top = 0;
  sp->sp = (struct stack_el**) malloc(size * sizeof(struct stack_el));


  return sp;

}


int push(struct stack *sp, struct stack_el *el) // returns 0 if the stack is full, and 1 otherwise
{
  if (sp == NULL || el == NULL)
  return 0;

  if(sp->size == sp->top)
    return 0;

	sp->sp[sp->top] = el;

  sp->top++;

  return 1;



}

struct stack_el *pop(struct stack *sp) // returns NULL if the stack is empty
{
  if ( sp ==NULL || sp->top == 0)
  return NULL;

  struct stack_el *aux;

  sp->top--;

  aux = sp->sp[sp->top];


  return aux;

}

void show(struct stack *sp)
{
  if (sp == NULL || sp->top == 0)
    return;
  int i=0;

  for(i = sp->size - 1; i>-1;i--)
    printf("%s  %d\n", sp->sp[i]->str, sp->sp[i]->n );


}


void f(struct stack *sp)  // frees all data structures allocated
{
  if(sp==NULL)
    return;
  int i=0;

  for(i = sp->size - 1; i>-1;i--){
    free(sp->sp[i]->str);
  }
  free(sp->sp);
  free (sp);
}
