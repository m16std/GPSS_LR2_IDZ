#include <cmath>
#include <cstring>
#include <vector>
#include <cwchar>
#include <iostream>
#include <Vector>
#include <Math.h>

using namespace std;

double GetMo2(double a, double b, double c, double d, int variant)
{
	if (variant == 1)//A1 A1 a1 a2
		return c * (b - a) / (c + d) + a;

	if (variant == 2)//t p - -
		return a * b;

	if (variant == 3)//i j - -
		return (a + b) / 2;

	if (variant == 4)//B A - -
		return a + b;

	if (variant == 7)//a b A -
		return a * b + c;

	if (variant == 8)//p - - -
		return (1 - a) / a;

	if (variant == 11)//A - - -
		return a;

	if (variant == 12)//A - - -
		return a;

	if (variant == 15)//u o A -
		return exp(a + pow(b, 2) / 2.0) + c;

	if (variant == 16)//s p - -
		return a * (1 - b) / b;

	if (variant == 17)//u - - -
		return a;

	if (variant == 18)//b A - -
		return (a * b) / (a - 1);

	if (variant == 19)//a b A -
		return b / (a - 1) + c;

	if (variant == 21)//A - - -
		return a;

	if (variant == 22)//a b c -
		return (a + b + c) / 3;

	if (variant == 23)//a b - -
		return (a + b) / 2;

	if (variant == 24)//a b A -
		return b / a * tgamma(1 / a) + c;
}

void PrintP2(double a, double b, double c, double d, int variant)
{
	if (variant == 1)//A1 A1 a1 a2
		cout << "BETA(1, " << a << ", " << b << ", " << c << ", " << d << ")";

	if (variant == 2)//t p - -
		cout << "BINORMAN(1, " << a << ", " << b << ")";

	if (variant == 3)//i j - -
		cout << "DUNIFORM(1, " << a << ", " << b << ")";

	if (variant == 4)//B A - -
		cout << "EXPONENTIAL(1, " << b << ", " << a << ")";

	if (variant == 7)//a b A -
		cout << "GAMMA(1, " << c << ", " << b << ", " << c << ")";

	if (variant == 8)//p - - -
		cout << "GEOMETRIC(1, " << a << ")";

	if (variant == 11)//A - - -
		cout << "LAPLACE(1, " << a << ", 1)";

	if (variant == 12)//A - - -
		cout << "LOGISTIC(1, " << a << ", 1)";

	if (variant == 15)//u o A -
		cout << "LOGNORMAL(1, " << c << ", " << a << ", " << b << ")";

	if (variant == 16)//s p - -
		cout << "NEGBINOM(1, " << a << ", " << b << ")";

	if (variant == 17)//u - - -
		cout << "NORMAL(1, " << a << ", 1)";

	if (variant == 18)//b A - -
		cout << "PARETO(1, " << b << ", " << a << ")";

	if (variant == 19)//a b A -
		cout << "PEARSON5(1, " << c << ", " << b << ", " << a << ")";

	if (variant == 21)//A - - -
		cout << "POISSON(1, " << a << ")";

	if (variant == 22)//a b c -
		cout << "TRIANGULAR(1, 10" << a << ", " << b << ", " << c << ")";

	if (variant == 23)//a b - -
		cout << "UNIFORM(1, " << a << ", " << b << ")";

	if (variant == 24)//a b A -
		cout << "WEIBULL(1, " << c << ", " << b << ", " << a << ")";

	cout << "\n\n";
}

double FindMo2(double x, int variant)
{
	double best = 100, delta, u3, o3, A3;
	for (double d = 0; d < 100; d += 0.1)
	{
		for (double c = 0; c < 100; c += 0.1)
		{
			for (double b = 0; b < 100; b += 0.1)
			{
				for (double a = 0; a < 100; a += 0.1)
				{

					delta = abs(x - GetMo2(a, b, c, d, variant));
					if (delta < 0.1)
					{
						PrintP2(a, b, c, d, variant);
						return GetMo2(a, b, c, d, variant);
					}
				}
			}
		}
	}
}

double GetS1(double d, double e, vector<double> d1, vector<double> e1, vector<double> k1, vector<double> y1)
{
	double interval, S1 = 0;
	for (int i = 0; i < d1.size() - 1; i++)
	{
		interval = (d1[i + 1] * d + e1[i + 1] * e) / k1[i + 1] - (d1[i] * d + e1[i] * e) / k1[i];
		S1 += (y1[i] + y1[i + 1]) / 2.0 * interval;
	}
	return S1;
}

double GetP1(double x, double d, double e, vector<double> d1, vector<double> e1, vector<double> k1, vector<double> y1)
{
	int left_i = -1;
	for (int i = 0; i < d1.size() - 1; i++)
	{
		if ((d1[i] * d + e1[i] * e) / k1[i] < x && x < (d1[i + 1] * d + e1[i + 1] * e) / k1[i + 1])
		{
			left_i = i;
			continue;
		}
		if (x == (d1[i] * d + e1[i] * e) / k1[i])
		{
			return y1[i];
		}
		if (x == (d1[i + 1] * d + e1[i + 1] * e) / k1[i + 1])
		{
			return y1[i + 1];
		}
	}


	if (x < (d1[0] * d + e1[0] * e) / k1[0])
	{
		return 0;
	}

	if (x > (d1[d1.size() - 1] * d + e1[d1.size() - 1] * e) / k1[d1.size() - 1])
	{
		return 0;
	}

	double left_y = y1[left_i], right_y = y1[left_i + 1];

	if (left_y == right_y)
		return left_y;

	double interval = (d1[left_i + 1] * d + e1[left_i + 1] * e) / k1[left_i + 1] - (d1[left_i] * d + e1[left_i] * e) / k1[left_i];

	double betwen_x_and_left_x = x - (d1[left_i] * d + e1[left_i] * e) / k1[left_i];

	return right_y * betwen_x_and_left_x / interval + left_y * (interval - betwen_x_and_left_x) / interval;
}

double GetP0(vector<double> a0, vector<double> x0, vector<double> P0, double Mo1, double Mo2)
{
	double Mo0_a = 0, Mo0_x = 0;

	for (int i = 0; i < a0.size(); i++)
	{
		Mo0_a += a0[i] * P0[i];
		Mo0_x += x0[i] * P0[i];
	}

	double a, Mo0;
	Mo0 = 0.87 / (1.0 / Mo1 + 1.0 / Mo2);
	a = (Mo0 - Mo0_x)/ Mo0_a;

	//cout << "a = " << a << "\n\n";

	double P = 0;
	for (int i = 0; i < a0.size(); i++)
	{
		P += P0[i];
		cout << P << ", " << a0[i] * a + x0[i] << "/\n";
	}

	return a;
}

void PrintP1(double S1, double d, double e, vector<double> d1, vector<double> e1, vector<double> k1, vector<double> Y1)
{
	cout << "\n";

	double P = 0, step = 0.001;
	for (double i = d; i < e + step; i += step)
	{
		if (fmod(i, 1) < step / 2 || fmod(i, 1) > 1 - step / 2)
			cout << i << ", " << P << "/\n";
		P += GetP1(i, d, e, d1, e1, k1, Y1) * step / S1;
	}

}

double GetMo1(double S1, double d, double e, vector<double> d1, vector<double> e1, vector<double> k1, vector<double> Y1)
{
	cout << "\n";

	double P = 0, step = 0.001, Mo1 = 0, best = 100;
	for (double i = d; i < e + step; i += step)
	{
		P += GetP1(i, d, e, d1, e1, k1, Y1) * step / S1;
		if (abs(P - 0.5) < best)
		{
			best = abs(P - 0.5);
			Mo1 = i;
		}
	}
	return Mo1;
}
