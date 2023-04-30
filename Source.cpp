#include "Header.h"

using namespace std;

const int n1 = 4;



double GetMo2(double a, double b, double c, double d, int variant)
{
	if (variant == 1)//A1 A1 a1 a2
		return c * (b - a) / (c + d) + a;

	if (variant == 2)//t p - -
		return a * b;

	if (variant == 3)//i j - -
		return (a + b)/2;

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

	if (variant == 18)//A - - -
		return a;
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
						return GetMo2(a, b, c, d, variant);
					}
				}
			}
		}
	}
}

double GetMo1(double d, double e, vector<double> d1, vector<double> e1, vector<double> k1, vector<double> y1)
{
	double interval, Mo1 = 0;
	for (int i = 0; i < d1.size() - 1; i++)
	{
		interval = (d1[i + 1] * d + e1[i + 1] * e) / k1[i + 1] - (d1[i] * d + e1[i] * e) / k1[i];
		Mo1 += (y1[i] + y1[i + 1]) / 2.0 * interval;
	}
	return Mo1;
}
double GetP1(double x, double d, double e, vector<double> d1, vector<double> e1, vector<double> k1, vector<double> y1)
{
	int left_i = -1;
	for (int i = 0; i < d1.size() - 1; i++)
	{
		if ((d1[i] * d + e1[i] * e) / k1[i] < x && x <  (d1[i + 1] * d + e1[i + 1] * e) / k1[i + 1])
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

	double left_y = y1[left_i], right_y = y1[left_i +1];

	if (left_y == right_y)
		return left_y;

	double interval = (d1[left_i + 1] * d + e1[left_i + 1] * e) / k1[left_i + 1] - (d1[left_i] * d + e1[left_i] * e) / k1[left_i];
		
	double betwen_x_and_left_x = x - (d1[left_i] * d + e1[left_i] * e) / k1[left_i];

	return right_y * betwen_x_and_left_x / interval + left_y * (interval - betwen_x_and_left_x) / interval;
}

void GetP0(double Mo0_a, double Mo0_x, vector<double> a0, vector<double> x0, vector<double> P0, double Mo1, double Mo2)
{
	for (int i = 0; i < a0.size(); i++)
	{
		Mo0_a += a0[i] * P0[i];
		Mo0_x += x0[i] * P0[i];
	}

	double a = 0;
	a = 0.87 / (Mo0_a * (1.0 / Mo1 + 1.0 / Mo2)) - Mo0_x;

	cout << "\na = " << a << "\n\n";

	double P = 0;
	for (int i = 0; i < a0.size(); i++)
	{
		P += P0[i];
		cout << P << ", " << a0[i] * a + x0[i] << "/\n";
	}
}

void PrintP1(double step, double Mo1, double d, double e, vector<double> d1, vector<double> e1, vector<double> k1, vector<double> Y1)
{
	cout << "\n\n";

	double P = 0;
	for (double i = 0; i < 22 + step; i += step)
	{
		if (fmod(i, 1) < step / 2 || fmod(i, 1) > 1 - step / 2)
			cout << i << ", " << P << "/\n";
		P += GetP1(i, 0, 22, d1, e1, k1, Y1) * step / Mo1;
	}

}

int main()
{ 
	cout.precision(3);
	vector<double> a0 = { 1,1,7,8 };
	vector<double> x0 = { 0,1,0,0 };
	vector<double> P0 = { 0.4, 0.42, 0.11, 0.07 };

	vector<double> d1 = { 1,4,3,2,1,0 };
	vector<double> e1 = { 0,1,2,3,4,1 };
	vector<double> k1 = { 1,5,5,5,5,1 };
	vector<double> Y1 = { 1,1,0,0,2,2 };

	double Mo1 = 0;
	double Mo2 = 0;
	double u3 = 0;
	double o3 = 0;
	double A3 = 0;
	
	double Mo0_a = 0;
	double Mo0_x = 0;

	if (a0.size() != x0.size() || d1.size() != e1.size() || e1.size() != k1.size() || k1.size() != Y1.size())
		return 0;

	Mo1 = GetMo1(0, 22, d1, e1, k1, Y1);
	Mo2 = FindMo2(Mo1 / 2.1, 15);

	cout << "Mo1 = " << Mo1 << "\nMo2 = " << Mo2 << "\n";

	GetP0(Mo0_a, Mo0_x, a0, x0, P0, Mo1, Mo2);

	PrintP1(0.001, Mo1, 0, 22, d1, e1, k1, Y1);

	return 1;
}