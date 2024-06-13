/*
   Реализация алгоритма Рутисхаузера. Полная скобочная структура, только
   неотрицательные числа и из операций: + - * /
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG

int isOp(char c) // Проверка на операцию
{
  return (c == '+') || (c == '-') || (c == '*') || (c == '/');
}
int isNum(char c) // Проверка на цифру
{
  return c >= '0' && c <= '9';
}
double doOp(char op, double a, double b) // Выполнить операцию
{
  switch (op) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    return a / b;
  }

  return 0;
}

#define SHIFT(type)                                                            \
  void shift_##type(type arr[], size_t indexFrom, size_t count,                \
                    int shiftSize) {                                           \
    if (count == 0) {                                                          \
      return;                                                                  \
    }                                                                          \
    if (shiftSize >= 0) {                                                      \
      for (size_t i = indexFrom + count - 1; i >= indexFrom; --i) {            \
        arr[i + shiftSize] = arr[i];                                           \
      }                                                                        \
    } else {                                                                   \
      shiftSize *= -1;                                                         \
      for (size_t i = indexFrom; i < indexFrom + count; ++i) {                 \
        arr[i] = arr[i + shiftSize];                                           \
      }                                                                        \
    }                                                                          \
  }

SHIFT(char) // определяет shift_char
SHIFT(double) // определяет shift_double

typedef struct {
  double integerPart;
  double fractionalPart;
} DoubleInParts; // Используется для парсинга чисел с плавающей точкой

double Rutishauser(const char *s) {
  const size_t kStrSize = strlen(s);
  char simpleForm[kStrSize + 1]; // 1 + (2*3) => n+(n*n)
  double nums[kStrSize / 2 +
              2]; // максимум (половина + 1) элементов входной строки -- числа

  size_t cSForm = 0, cNums = 0; // счётчик в simpleForm и в nums
  for (size_t i = 0; i < kStrSize; ++i) {
    if (s[i] == ' ' || s[i] == '\t') {
      continue;
    }
    if (isNum(s[i]) || s[i] == '.') {
      simpleForm[cSForm++] = 'n';
      DoubleInParts buffer = {0, 0};
      double *currentBuffer = &buffer.integerPart;
      while (isNum(s[i]) || s[i] == '.') {
        if (s[i] == '.') {
          currentBuffer = &buffer.fractionalPart;
          ++i;
          continue;
        }

        *currentBuffer = *currentBuffer * 10 + (s[i] - '0');
        ++i;
      }
      while (buffer.fractionalPart >= 1) {
        buffer.fractionalPart /= 10;
      }
      nums[cNums++] = buffer.integerPart + buffer.fractionalPart;
      --i; // Чтобы i после ++i в цикле продолжала указывать на следующий
           // элемент за числом
    } else {
      simpleForm[cSForm++] = s[i];
    }
  }

  simpleForm[cSForm] = 0;
  nums[cNums] = 0;

  cSForm = strlen(simpleForm);
  while (cNums > 1) { // Пока в nums не останется только 1 число
    size_t maxIndex = 0;
    size_t numMaxIndex = 0;

    long long int maxLevel = 0;
    long long int currentLevel = 0;
    long long int currentNumIndex = -1;

    for (size_t i = 0; i < cSForm; ++i) {
      if (simpleForm[i] == '(' || simpleForm[i] == 'n') {
        ++currentLevel;
        if (simpleForm[i] == 'n')
          ++currentNumIndex;
      } else {
        --currentLevel;
      }
      if (currentLevel > maxLevel) {
        maxLevel = currentLevel;
        maxIndex = i;
        numMaxIndex = currentNumIndex;
      }
    }

    double opResult = doOp(simpleForm[maxIndex + 1], nums[numMaxIndex],
                           nums[numMaxIndex + 1]);

    nums[numMaxIndex] = opResult;

    shift_double(nums, numMaxIndex + 1, cNums - (numMaxIndex + 1), -1);
    shift_char(simpleForm, maxIndex - 1, cSForm - (maxIndex + 1), -4);
    simpleForm[maxIndex-1] = 'n';

    --cNums;
    cSForm -= 4; // (n+n) => n За итерацию убирается -- 4 литеры
  }

  return nums[0];
}

#define n 15
int main() {
  const char * s[n] = {
    "",
    "0",
    "1",
    ".1",
    "(.1 - 1)",
    "0.0",
    ".0",
    "(2.0 * 3.0)",
    "(.2 *.3)",
    "(1 + (2 * 3)) /4",
    "(1 + (2 * 3)) /4",
    "(1 + 2) * 4",
    "4 * (1 + 2)",
    "1 + (((1 + 2)/(1 + 2)) * 4)",
    "(((1 + 2)/(1 + 2)) / 4) + 1"
  };

  for(size_t i = 0; i < n; ++i) {
    const char *currentString = s[i];
    double result = Rutishauser(currentString);
    printf(">>>: %s\n<<<: %lf\n\n",currentString, result);
}

  return 0;
}
