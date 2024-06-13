#include "../Stack/stack.h"
#include <stdio.h>
#include "queue.h"
#include <stdlib.h>


typedef struct {
	Stack innerStack; // Очередь, которая хранит данные на стеке
} QueueOnStack;

void queueOnStack_Create(QueueOnStack * queueOnStack) {
	Create(&queueOnStack->innerStack);
}

void queueOnStack_Pop_1(QueueOnStack * queueOnStack) {
	Stack additionalStack; // Создать дополнительный стек
	Create(&additionalStack);

	while (!Empty(&queueOnStack->innerStack)) {// Перелить входную "очередь" в дополнительный стек
		Push(&additionalStack, Top(&queueOnStack->innerStack));
		Pop(&queueOnStack->innerStack);
	}

	Pop(&additionalStack);// Убрать первый элемент перелитой очереди "очереди"

	while (!Empty(&additionalStack)) {// Перелить дополнительный стек в входную "очередь"
		Push(&queueOnStack->innerStack, Top(&additionalStack));
		Pop(&additionalStack);
	}
}

void queueOnStack_Pop_2(QueueOnStack * queueOnStack) {
	if (Empty(&queueOnStack->innerStack)) { // Если "очередь" пуста -- просто 
		// вернуться. Нечего удалять.
		return;
	}

	int temp = Top(&queueOnStack->innerStack); // Снять элемент с вершины
	Pop(&queueOnStack->innerStack);

	queueOnStack_Pop_2(queueOnStack);// Рекурсия

	if (Empty(&queueOnStack->innerStack)) { // Если мы сняли послединый элемент,
		return; // класть его обратно не надо.
	}
	Push(&queueOnStack->innerStack, temp);//Положить снятый элемент назад
}


void queueOnStack_Push(QueueOnStack * queueOnStack, int value) {
	Push(&queueOnStack->innerStack, value); // Просто кладём элемент на вершины
}

void queueOnStack_Print(QueueOnStack * queueOnStack) {
	printf("QUEUE_ON_STACK: [ ");
	int i = queueOnStack->innerStack.size;
	for (Item * item = queueOnStack->innerStack.head; i > 0; item = item->next, i--) {
		printf("%d ", item->data);
	}
	printf("]\n");
}

int main() {
	const int size = 16;

	QueueOnStack * qOnStack = (QueueOnStack *)malloc(sizeof(QueueOnStack));
	Queue * queue = (Queue *)malloc(sizeof(Queue));

	queueOnStack_Create(qOnStack);
	Create(queue);

	for (int i = 0; i < size; i++) {
		int value = rand() % 100;

		queueOnStack_Push(qOnStack, value);
		Push(queue, value);
	}

	queueOnStack_Print(qOnStack);
	Print(queue);

	for (int i = 0; i < size / 2; i++) {
		queueOnStack_Pop_1(qOnStack);
		Pop(queue);
	}

	queueOnStack_Print(qOnStack);
	Print(queue);

	return 0;
}

