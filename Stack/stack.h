#include <stdio.h>
#ifndef _STACK_H
#define _STACK_H
#endif
#define ERROR 1
#define OK 0
#define SIZE 200

typedef struct {
	int data[SIZE];
	int top;	
};

void init(stack *) ;
int push(stack * , int) ;
int pop(stack *) ;
int top(stack *, int *) ;
int isEmpty(stack *) ;
int isFull(stack *) ; // For finite size

void init(stack *s){
	s->top=-1; // (*s).top=-1;
}

int isFull(stack *s)
{
	return (s->top==SIZE-1);
} 

int isEmpty(stack *s){
	return (s->top==-1);
}

int push(stack *s, int n)
{
	if (isFull(s))
	{
		printf("Stack is Full\n");
		return ERROR;
	}
	s->data[++(s->top)]=n;
	return OK;
}

int pop(stack *s)
{
	if (isEmpty(s))
	{
		printf("Stack is Empty\n");
		return ERROR;
	}
	s->top--;
	return OK;
}

int top(stack *s, int *val)
{
	if (isEmpty(s))
	{
		printf("Stack is Empty\n");
		return ERROR;
	}
	*val=s->data[s->top];
	return OK;
}
