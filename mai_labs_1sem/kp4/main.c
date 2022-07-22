#include <stdio.h>
#include <math.h>

double f1(double x) 
{
    return 3.0f * sin(pow(x, 0.5f)) + 0.35f * x - 3.8f;
}

double df1(double x) 
{
    return 3.0f * cos(pow(x, 0.5f)) * 0.5f * pow(x, (-1.0f) * 0.5f) + 0.35f;   
}

double ddf1(double x) 
{
    return (-1.0f) * (3.0f * cos(pow(x, 0.5f)) * 0.25 * pow(x, (-1.0f) * (1.5f)) + 3 * sin(pow(x, 0.5)) * 0.25 * pow(x, (-1.0f)));  
}

double f2(double x) 
{
    return 0.25f * x * x * x + x - 1.2502f;
}

double df2(double x) 
{
    return 0.25f * 3.0f * x * x + 1;
}

double ddf2(double x) 
{
    return 0.25f * 3.0f * 2.0f * x;
}


double dichotomy(double (*f)(double x), double eps, double a, double b) 
{
    while (fabs(a - b) >= eps) {
        if (f(a) * f((a + b) / 2.0f) > 0) {
            a = (a + b) / 2.0f;
        } else {
            b = (a + b) / 2.0f;
        }
    }
    return (a + b) / 2.0f;
}

double iter(double (*f)(double x), double (*df)(double x), double eps, double a, double b) 
{
    int flag = 1;

    for (double x = a; x <= b && flag; x += eps) {
        if (fabs(1 - (df(x) / df((a + b) / 2.0f))) >= 1) {
            flag = 0;
        }
    }

    if (flag) {
        double x0, x1;
        x0 = (a + b) / 2.0f;
        x1 = x0 - (f(x0) / df((a + b) / 2.0f));
        while (fabs(x1 - x0) >= eps) {
            x0 = x1;
            x1 = x0 - (f(x0) / df((a + b) / 2.0f));
        }
        return x1;
    } else {
        return a - 1.0f;
    }

}

double newton(double (*f)(double x), double (*df)(double x), double (*ddf)(double x), double eps, double a, double b) 
{
    int flag = 1;
    for (double x = a; x <= b && flag; x += eps) {
        if (fabs(f(x) * ddf(x)) >= df(x) * df(x)) {
            flag = 0;
        }
    }

    if (flag) {
        double x = b;
        while (fabs(f(x)) >= eps) {
            x = x - f(x) / df(x);
        }
        return x;
    } else {
        return a - 1.0f;
    }
}

int main() {
    double eps, x;
    printf("f1(x) = 3sin(sqrt(x)) + 0.35x - 3.8\nf2(x) = 0.25x^3 + x - 1.2502\n");
    printf("Точность: ");
    scanf("%lf", &eps);
    printf("+-----------------------------+----------+-----------+-----------------------+--------------------------+\n");
	printf("|         Уравнение           | Отрезок  | Метод     | Прибл. значение корня | Прибл. значение функции  |\n");
	printf("+-----------------------------+----------+-----------+-----------------------+--------------------------+\n");
    x = newton(f1, df1, ddf1, eps, 2.0f, 3.0f);
    if (x >= 2.0f) {
		printf("| 3sin(sqrt(x)) + 0.35x - 3.8 | [2, 3]   | Ньютона   | %lf\t             | %lf \t\t|\n", x, f1(x));
	} else {
		printf("| 3sin(sqrt(x)) + 0.35x - 3.8 | [2, 3]   | Ньютона   | Не вычислимо\t     | %lf \t\t|\n", f1(x));
	}
    x = dichotomy(f1, eps, 2.0f, 3.0f);
    if (x >= 2.0f) {
		printf("| 3sin(sqrt(x)) + 0.35x - 3.8 | [2, 3]   | Дихотомии | %lf\t             | %lf \t\t|\n", x, f1(x));
	} else {
		printf("| 3sin(sqrt(x)) + 0.35x - 3.8 | [2, 3]   | Дихотомии | Не вычислимо\t     | %lf \t\t|\n", f1(x));
	}
	x = iter(f1, df1, eps, 2.0f, 3.0f);
	if (x >= 2.0f) {
		printf("| 3sin(sqrt(x)) + 0.35x - 3.8 | [2, 3]   | Итераций  | %lf\t             | %lf \t\t|\n", x, f1(x));
	} else {
		printf("| 3sin(sqrt(x)) + 0.35x - 3.8 | [2, 3]   | Итераций  | Не вычислимо\t     | %lf \t\t|\n", f1(x));
	}
    x = newton(f2, df2, ddf2, eps, 0.0f, 2.0f);
    if (x >= 0.0f) {
		printf("| 0.25x^3 + x - 1.2502        | [0, 2]   | Ньютона   | %lf\t             | %lf \t\t|\n", x, f2(x));
	} else {
		printf("| 0.25x^3 + x - 1.2502        | [0, 2]   | Ньютона   | Не вычислимо\t     | %lf \t\t|\n", f2(x));
	}
    x = dichotomy(f2, eps, 0.0f, 2.0f);
    if (x >= 0.0f) {
		printf("| 0.25x^3 + x - 1.2502        | [0, 2]   | Дихотомии | %lf\t             | %lf \t\t|\n", x, f2(x));
	} else {
		printf("| 0.25x^3 + x - 1.2502        | [0, 2]   | Дихотомии | Не вычислимо\t     | %lf \t\t|\n", f2(x));
	}
    x = iter(f2, df2, eps, 0.0f, 2.0f);a
    if (x >= 0.0f) {
		printf("| 0.25x^3 + x - 1.2502        | [0, 2]   | Итераций  | %lf\t             | %lf \t\t|\n", x, f2(x));
	} else {
		printf("| 0.25x^3 + x - 1.2502        | [0, 2]   | Итераций  | Не вычислимо\t     | %lf \t\t|\n", f2(x));
	}
	printf("+-----------------------------+----------+-----------+-----------------------+--------------------------+\n");
    return 0;
}