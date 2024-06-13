/* ���������� ��������� ������-����������. �� ���� ������ ����� �����, ��
 * ��������: + - * */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

DEF_STACK(op, char)
DEF_STACK(num, double)

bool isOp(char c) {
  return (c == '+') || (c == '-') || (c == '*') || (c == '+') || (c == '(') ||
         (c == ')');
}

bool isDigit(char c) { return ((c >= '0') && (c <= '9')); }

double
doOp(char op, double b,
     double a) { // �������� �������� � �������� ������� � ���� ��������� �����
  printf("%lf %c %lf\n", a, op, b);
  switch (op) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    return a / b;
  default:
    printf("Error(function: doOp): Unknown operator.\n");
    exit(1);
  }
}

/*
        ������� ��������:

              | $ | ( | + | - | * | / | ) |
        ------|---|---|---|---|---|---|---|
        �:| $ | 6 | 1 | 1 | 1 | 1 | 1 | 5 |
          | ( | 5 | 1 | 1 | 1 | 1 | 1 | 3 |
          | + | 4 | 1 | 2 | 2 | 1 | 1 | 4 |
          | - | 4 | 1 | 2 | 2 | 1 | 1 | 4 |
          | * | 4 | 1 | 4 | 4 | 2 | 2 | 4 |
          | / | 4 | 1 | 4 | 4 | 2 | 2 | 4 |
*/
void scanNumber(char *c, int *buff, int sign, char *cPrev) {
  *cPrev = *c;
  while (isDigit((*c = getchar()))) {
    *buff = (*buff * 10) + *c - '0';
    *cPrev = *c;
  }
  *buff *= sign;
}

void choose_function(char *c, char *cPrev, Stack_op *T, Stack_num *E);

void f1(char *c, Stack_op *T, char *cPrev) {
  Stack_op_push(T, *c);
  *cPrev = *c;
  *c = getchar();
}

void f2(char *c, Stack_op *T, Stack_num *E, char *cPrev) {
  char op = *Stack_op_top(T);
  Stack_op_pop(T);

  double a = *Stack_num_top(E);
  Stack_num_pop(E);
  double b = *Stack_num_top(E);
  Stack_num_pop(E);

  double result = doOp(op, a, b);

  Stack_num_push(E, result);
  Stack_op_push(T, *c);

  *cPrev = *c;
  *c = getchar();
}

void f3(char *c, Stack_op *T, char *cPrev) {
  Stack_op_pop(T);

  *cPrev = *c;
  *c = getchar();
}

void f4(char *c, Stack_op *T, Stack_num *E, char *cPrev) {
  char op = *Stack_op_top(T);
  Stack_op_pop(T);

  double a = *Stack_num_top(E);
  Stack_num_pop(E);
  double b = *Stack_num_top(E);
  Stack_num_pop(E);

  double result = doOp(op, a, b);

  Stack_num_push(E, result);

  choose_function(c, cPrev, T, E);
}

void f5() {
  printf("Error in f5!\n");
  exit(1);
};

void f6(char *c) { *c = EOF; }

void choose_function(char *c, char *cPrev, Stack_op *T, Stack_num *E) {
  char topOP = (Stack_op_empty(T) ? '$' : *Stack_op_top(T));
  if (*c == '$') {
    switch (topOP) {
    case '$':
      f6(c);
      break;
    case '(':
      f5();
      break;
    case '+':
    case '-':
    case '*':
    case '/':
      f4(c, T, E, cPrev);
      break;
    }
  } else if (*c == '(') {
    f1(c, T, cPrev);
  } else if (*c == '+' || *c == '-') {
    switch (topOP) {
    case '$':
    case '(':
      f1(c, T, cPrev);
      break;
    case '+':
    case '-':
      f2(c, T, E, cPrev);
      break;
    case '*':
    case '/':
      f4(c, T, E, cPrev);
      break;
    }
  } else if (*c == '*' || *c == '/') {
    switch (topOP) {
    case '$':
    case '(':
    case '+':
    case '-':
      f1(c, T, cPrev);
      break;
    case '*':
    case '/':
      f2(c, T, E, cPrev);
      break;
    }
  } else if (*c == ')') {
    switch (topOP) {
    case '$':
      f5();
      break;
    case '(':
      f3(c, T, cPrev);
      break;
    case '+':
    case '-':
    case '*':
    case '/':
      f4(c, T, E, cPrev);
      break;
    }
  }
}
// ��� ��������
double BauerZamelson() {
  char c = getchar(), cPrev = '\0'; // � cPrev ��������� ���������� ������ ���
                                    // ����������� �������� ������
  int sign = 1; // ���� �����
  Stack_num *E = Stack_num_create();
  Stack_op *T = Stack_op_create();
  while (c != EOF && c != '\n') { // ���� �� ����� �� �����
    if (c == ' ' || c == '\t') { // ������� � ��������� ����������
      c = getchar();
      continue;
    }
    if (isDigit(c)) { // ���� ���������� ����� - ��������� ��� ���������
      int buff = c - '0';
      scanNumber(&c, &buff, sign, &cPrev);
      Stack_num_push(E, buff);
      sign = 1;
    } else if (c == '-' &&
               (isOp(cPrev) || cPrev == '\0')) { // ���� ������� �����
      sign = -1;
      c = getchar();
      continue;
    } else {
      choose_function(&c, &cPrev, T, E);
    }
  }
  c = '$';
  choose_function(&c, &cPrev, T, E);

  double result = *Stack_num_top(E);
  Stack_op_destroy(T);
  Stack_num_destroy(E);
  return result;
}

int main() {
  printf("Result: %lf\n", BauerZamelson());
  return 0;
}
