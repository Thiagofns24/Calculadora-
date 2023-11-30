#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h> // Adicionado para funções matemáticas

#define STR1 "Por favor, Introduza a operação usando notação polonesa (pós-fixada): "
#define MAX 100

// Definição de estruturas
struct no {
   double elem; // Mudança para suportar números reais
   struct no *prox;
};

struct pilha {
   struct no *topo;
};

// Cabeçalho das funções
void inicializaPilha(struct pilha *P);
short pilhaVazia(struct pilha *P);
void push(struct pilha *P, double elem);
double pop(struct pilha *P);
int dimensaoStr(char *Str);
int caractere(char *Str, int pos);
double calcularOperacao(double n1, double n2, char operador);

int main(void) {
   setlocale(LC_ALL, "Portuguese");
   struct pilha P1;
   inicializaPilha(&P1);

   char str[MAX];
   printf("\n %s", STR1);
   fgets(str, MAX, stdin);
   str[strcspn(str, "\n")] = '\0'; // Remover o caractere de nova linha, se presente

   int dimStr, i;
   double ff;
   dimStr = dimensaoStr(str);

   for (i = 0; i < dimStr; i++) {
       if (str[i] >= '0' && str[i] <= '9') {
           // Lida com números
           double operando = atof(&str[i]);
           while (str[i] >= '0' && str[i] <= '9') {
               i++;
           }
           i--;
           push(&P1, operando);
       } else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
           // Lida com operadores básicos
           double n2 = pop(&P1);
           double n1 = pop(&P1);
           push(&P1, calcularOperacao(n1, n2, str[i]));
       } else if (str[i] == 's' || str[i] == 'c' || str[i] == 't' || str[i] == 'l') {
           // Lida com funções seno, cosseno, tangente e logaritmo
           if (str[i] == 's') {
               double n = pop(&P1);
               push(&P1, sin(n));
           } else if (str[i] == 'c') {
               double n = pop(&P1);
               push(&P1, cos(n));
           } else if (str[i] == 't') {
               double n = pop(&P1);
               push(&P1, tan(n));
           } else if (str[i] == 'l') {
               double n = pop(&P1);
               push(&P1, log(n));
           }
       }
   } // For que percorre a String

   ff = pop(&P1);
   printf("\n\n O resultado da operação é: %.2f\n", ff);

   return 0;
}

void inicializaPilha(struct pilha *P) {
   P->topo = NULL;
}

short pilhaVazia(struct pilha *P) {
   return (P->topo == NULL) ? 1 : 0;
}

void push(struct pilha *P, double elem) {
   struct no *novoNo = (struct no *)malloc(sizeof(struct no));
   novoNo->elem = elem;
   novoNo->prox = P->topo;
   P->topo = novoNo;
}

double pop(struct pilha *P) {
   double x;
   struct no *ptr = P->topo;
   if (pilhaVazia(P)) {
       printf("Erro: Pilha vazia.\n");
       exit(EXIT_FAILURE);
   }
   x = ptr->elem;
   P->topo = ptr->prox;
   free(ptr);
   return x;
}

int dimensaoStr(char *Str) {
   return strlen(Str);
}

double calcularOperacao(double n1, double n2, char operador) {
   switch (operador) {
       case '+':
           return n1 + n2;
       case '-':
           return n1 - n2;
       case '*':
           return n1 * n2;
       case '/':
           if (n2 == 0) {
               printf("Erro: Divisão por zero.\n");
               exit(EXIT_FAILURE);
           }
           return n1 / n2;
       default:
           printf("Erro: Operador não reconhecido.\n");
           exit(EXIT_FAILURE);
   }
}