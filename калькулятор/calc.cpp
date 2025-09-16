#define _CRT_SECURE_NO_WARNINGS
#include <stack>
#include <iostream>
#include <string>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <stdio.h>
using namespace std;
struct Leksema
{
	char type;
	double value;
};
void decimal_to_binary(int num) {
	if (num < 0) {
		num = num * -1;
		int binary[32];
		int i = 0;
		int b = 0;
		while (num > 0) {
			binary[i] = num % 2;
			num = num / 2;
			i++;
		}
		for (int j = i - 1; j >= 0; j--) {
			if (binary[j] == 1) {
				binary[j] = 0;
				b += 1;
			}
			else if (binary[j] == 0) {
				binary[j] = 1;
				b += 1;
			}
		}
		for (int i = 0; i < b; i++) {
			if (binary[i] != 0) {
				binary[i] = 0;
			}
			else {
				binary[i] = 1;
				break;
			}
		}
		for (int j = i - 1; j >= 0; j--) {
			printf("%d", binary[j]);
		}
		printf("\n");
	}
	else if (num == 0) {
		printf("0\n");
		return;
	}
	else {
		int binary[32];
		int i = 0;
		while (num > 0) {
			binary[i] = num % 2;
			num = num / 2;
			i++;
		}
		for (int j = i - 1; j >= 0; j--) {
			printf("%d", binary[j]);
		}
		printf("\n");
	}
}
bool Maths(stack <Leksema>& Stack_n, stack <Leksema>& Stack_o, Leksema& item) {
	double a, b, c;
	a = Stack_n.top().value;
	Stack_n.pop();
	switch (Stack_o.top().type) {
	case '+':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = a + b;
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;

	case '-':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = b - a;
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;
	case '*':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = a * b;
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;
	case 's':
		c = sin(a);
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;
	case 'c':
		c = cos(a);
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;
	case 'd': {
		double dec_number = a;
		decimal_to_binary(static_cast<int>(a));
		c = dec_number;
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;
	}
	case 't':
		c = tan(a);
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;
	case 'g':
		c = cos(a) / sin(a);
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;
	case 'e':
		c = exp(a);
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;
	case '^':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = pow(b, a);
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;
	case '/':
		b = Stack_n.top().value;
		if (a == 0) {
			cerr << "\nНа 0 делить нельзя!\n";
			return false;
		}
		else {
			Stack_n.pop();
			c = (b / a);
			item.type = '0';
			item.value = c;
			Stack_n.push(item);
			Stack_o.pop();
			break;
		}
	default:
		cerr << "\n Erorr\n";
		return false;
		break;
	}
	return true;
}

int Parara(char Ch) {
	if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'g' || Ch == 'e')
		return 4;
	if (Ch == '^')
		return 3;
	if (Ch == '+' || Ch == '-')
		return 1;
	if (Ch == '*' || Ch == '/')
		return 2;
	else return 0;
}

void asm_funk() {
	printf("Добро пожаловать в калькулятор!\nРукводство пользователя: просто введите требуемое выражение в строку, все результаты вычислений записываются в файл\nДоступные триганометрические функции (в радианах): sin(x); cos(x); tan(x);ctg(x)\n");
	printf("Длявозведения в степень x впишите ^ x, для извлечения корня степени x впишите ^ (1 / x)\n");
	printf("Для вычисления дополнительного кода из десятичного числа x впишите dob(x)\n");
	printf("Для использования экспоненты впишите e, для вычисления экспоненты от числа x впишите Exp(x)\n");
	printf("Для использования числа Пи впишите p\n");
}
int main() {
	setlocale(LC_ALL, "Rus");
	__asm {
		call asm_funk
	}
	printf(" \n");
	stack <Leksema> Stack_n;
	stack <Leksema> Stack_o;
	Leksema item;
	char Ch;
	double value;
	bool karibo = 1;
	int g = 1;
	while (1) {
		while (52) {
			Ch = cin.peek();
			if (Ch == '\n') {
				break;
			}
			if (Ch == ' ') {
				cin.ignore();
				continue;
			}
			if (Ch == 'p') {
				item.type = '0';
				item.value = acos(-1);
				Stack_n.push(item);
				karibo = 0;
				cin.ignore();
				continue;
			}
			if (Ch == 'e') {
				item.type = '0';
				item.value = exp(1);
				Stack_n.push(item);
				karibo = 0;
				cin.ignore();
				continue;
			}
			if (Ch == 't' || Ch == 's' || Ch == 'c' || Ch == 'e' || Ch == 'd' || Ch == 'E') {
				char lulu[3];
				for (short i = 0; i < 3; i++) {
					Ch = cin.peek();
					lulu[i] = Ch;
					cin.ignore();
				}
				if (lulu[0] == 's' && lulu[1] == 'i' && lulu[2] == 'n') {
					item.type = 's';
					item.value = 0;
					Stack_o.push(item);
					continue;
				}
				if (lulu[0] == 'd' && lulu[1] == 'o' && lulu[2] == 'b') {
					item.type = 'd';
					item.value = 0;
					Stack_o.push(item);

					continue;
				}
				if (lulu[0] == 'c' && lulu[1] == 'o' && lulu[2] == 's')
				{
					item.type = 'c';
					item.value = 0;
					Stack_o.push(item);
					continue;
				}
				if (lulu[0] == 't' && lulu[1] == 'a' && lulu[2] == 'n')
				{
					item.type = 't';
					item.value = 0;
					Stack_o.push(item);
					continue;
				}
				if (lulu[0] == 'c' && lulu[1] == 'a' && lulu[2] == 't')
				{
					item.type = 'g';
					item.value = 0;
					Stack_o.push(item);
					continue;
				}
				if (lulu[0] == 'E' && lulu[1] == 'x' && lulu[2] == 'p')
				{
					item.type = 'e';
					item.value = 0;
					Stack_o.push(item);
					continue;
				}

			}

			if (Ch >= '0' && Ch <= '9' || Ch == '-' && karibo == 1) {
				cin >> value;
				item.type = '0';
				item.value = value;
				Stack_n.push(item);
				karibo = 0;
				continue;
			}
			if (Ch == '+' || Ch == '-' && karibo == 0 || Ch == '*' || Ch == '/' || Ch == '^') {
				if (Stack_o.size() == 0) {
					item.type = Ch;
					item.value = 0;
					Stack_o.push(item);
					cin.ignore();
					continue;
				}
				if (Stack_o.size() != 0 && Parara(Ch) > Parara(Stack_o.top().type)) {
					item.type = Ch;
					item.value = 0;
					Stack_o.push(item);
					cin.ignore();
					continue;
				}
				if (Stack_o.size() != 0 && Parara(Ch) <= Parara(Stack_o.top().type)) {
					if (Maths(Stack_n, Stack_o, item) == false) {
						system("pause");
						return 0;
					}
					continue;
				}
			}
			if (Ch == '(') {
				item.type = Ch;
				item.value = 0;
				Stack_o.push(item);
				cin.ignore();
				continue;
			}
			if (Ch == ')') {
				while (Stack_o.top().type != '(') {
					if (Maths(Stack_n, Stack_o, item) == false) {
						system("pause");
						return 0;
					}
					else continue;

				}
				Stack_o.pop();
				cin.ignore();
				continue;
			}
			else {
				printf("error");
				return 0;
			}
		}
		while (Stack_o.size() != 0) {
			if (Maths(Stack_n, Stack_o, item) == false) {
				system("pause");
				return 0;
			}
			else
				continue;
		}
		printf("Ответ: %lf \n", Stack_n.top().value);
		cin.ignore();
		FILE* fptr;
		fptr = fopen("fileName.txt", "a+");
		fprintf(fptr, "Ответ: %lf", Stack_n.top().value);
		fprintf(fptr, "\n");
		fclose(fptr);
		continue;
	}
}
