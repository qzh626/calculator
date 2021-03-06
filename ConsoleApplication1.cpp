// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include"pch.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define stackLeagth 100
#define addLength 10
typedef struct stack
{
	int *top;
	int *base;
	int stacksize;
} sqStack;

sqStack initStack(sqStack L)
{
	L.base = (int*)malloc(stackLeagth * sizeof(int));
	if (L.base == NULL) exit(0);
	L.top = L.base;
	L.stacksize = stackLeagth;
	return L;
}

sqStack push(sqStack L, int e)
{
	if (L.base - L.top >= L.stacksize)
	{
		L.base = (int*)realloc(L.base, (stackLeagth + addLength) * sizeof(int));
		if (L.base == NULL) exit(0);
		L.stacksize = stackLeagth + addLength;
		L.top = L.base + stackLeagth;
	}
	*L.top = e;
	L.top++;
	return L;
}

void vist(sqStack L)
{
	int *p = NULL, *q = NULL;
	if (L.base == L.top)
	{
		printf("this is error");
		exit(0);
	}
	for (p = L.base; p < L.top; p++)
		printf("%d ", *p);
	putchar('\n');
}

sqStack madeStack(sqStack L, int n)
{
	int i, e;
	for (i = 0; i < n; i++)
	{
		scanf_s("%d", &e);
		L = push(L, e);
	}
	return L;
}

sqStack pop(sqStack L)
{
	if (L.base == L.top)
	{
		printf("this is erro\n");
		exit(0);
	}
	L.top--;
	return L;
}

sqStack cleanStack(sqStack L)
{
	L.top = L.base;
	return L;
}

int getElement(sqStack L)
{
	int e;
	e = *(L.top - 1);
	return e;
}

int number(char c)
{
	if (c >= '0'&&c <= '9') return 1;
	else return 0;
}

int judgea(char c)
{
	if (c == '(') return 1;
	if (c == '+') return 2;
	if (c == '-') return 2;
	if (c == '*') return 3;
	if (c == '/') return 3;
	if (c == ')') return 4;
	if (c == '#') return 0;
}
int judgeb(char c)
{
	if (c == '#') return 0;
	if (c == '-') return 2;
	if (c == '+') return 2;
	if (c == '*') return 3;
	if (c == '/') return 3;
	if (c == '(') return 4;
	if (c == ')') return 1;
}

char precede(char a, char b)
{
	int A, B;
	if (a == '(' && b == ')') return '=';
	A = judgea(a);
	B = judgeb(b);
	if (A > B) return '>';
	if (A < B) return '<';
	if (A == B) return '>';

}

int operate(int a, char b, int c)
{
	if (b == '+') return a + c;
	if (b == '-') return a - c;
	if (b == '*') return a * c;
	if (b == '/') return a / c;
}

int main()
{
	int flag, i, F;
	char result;//运算结果
	char array[20];
	int a, b;//转换后的运算数
	int k;//临时整数
	sqStack Num, Char;//操作数栈，操作符栈
	char c, f;//输入的字符，运算字符
	Num = initStack(Num);
	Char = initStack(Char);
	Char = push(Char, '#');
	c = getchar();
	while (c != '#' || getElement(Char) != '#')
	{
		flag = 0; i = 0;
		while (number(c)) {
			array[i++] = c;
			flag = 1;
			c = getchar();
		}
		if (flag == 1) {
			array[i] = '\0';
			Num = push(Num, atoi(array));
		}
		if (!number(c)) {
			switch (precede(getElement(Char), c)) {
			case'=': {Char = pop(Char);
				c = getchar();
				break;
			}
			case'<': {
				Char = push(Char, c);
				c = getchar();
				break;
			}
			case'>': {f = getElement(Char);
				Char = pop(Char);
				a = getElement(Num);
				Num = pop(Num);
				b = getElement(Num);
				Num = pop(Num);
				result = operate(b, f, a);
				Num = push(Num, result);
				break;
			}
			}
		}
	}
	vist(Num);
	return 0;
}

