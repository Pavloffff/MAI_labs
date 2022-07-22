#include <stdio.h>
#include <math.h>

int fact(int n)
{
    if (n == 0 || n==1)
        return 1;
    else
    {
        return n * fact(n - 1);
    }
}

long double machine_epsilon(void)
{
	long double e = 1.0f;
	while (1.0f + e / 2.0f > 1.0f)
		e /= 2.0f;
	return e;
}

int main()
{
	printf("Введите количество равных разбиений отрезка [a, b]: n = ");
	int n;
	scanf("%d", &n);
	if (n < 1) {
		printf("Введенное значение должно быть больше нуля!\n");
		return 0;
	}
	double e0 = machine_epsilon();
	double d = 1 / (double)n;
	printf("Машинное эпсилон для типа long double: e = %.8e\n", e0);
	printf("+-----------------------------------------------------------------------------------------------------+\n");
	printf("|            Таблица значений ряда Тейлора и стандартной функции для f(x) = exp(pow(x, 2))            |\n");
	printf("+-------+-----------------------------------------+---------------------------------+-----------------+\n");
	printf("|   x   | частичная сумма ряда для exp(pow(x, 2)) |      значение функции f(x)      | число итераций  |\n");
	printf("+-------+-----------------------------------------+---------------------------------+-----------------+\n");
	double x = 0.0;
	for (int i = 0; i <= n; i++) {
		x = d * i;
		double math_func = exp(pow(x, 2));
		double res = 0;
		int n1 = 0;
		double numerator = 1;
		double denominator = 1;
		for(;;n1++)
		{
			double cur = numerator / denominator;
			if(fabs(cur) < e0)
				break;
			res += cur;
			numerator *= x * x;
			denominator *= fact(n1 + 1);
		}
		printf("| %.3f\t|          %.19f          |      %.19f      |        %d        |\n", x, res, math_func, n1);
	}
	printf("+-------+-----------------------------------------+---------------------------------+-----------------+\n");
	return 0;
}
