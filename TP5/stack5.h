
struct stack_el{

char *str;	/* String to be printed in show() */
int n;		/* integer to be printed in show() */
struct  stack_el *next  ; /* link to next stack element*/


}stack_el;

struct stack_el *new(int n , char *str);

int push(struct stack_el * el , int my_n , char *my_str);

int pop ( struct stack_el *el);

int stack_size(struct stack_el *el );

int show ( struct stack_el *el);