#include "Header.h"

using namespace std;

const int n1 = 4;

vector<double> a1 = { 1,1,7,8 };
vector<double> x1 = { 0,1,0,0 };


vector<double> d2 = { 1,4,3,2,1,0 };
vector<double> e2 = { 0,1,2,3,4,1 };
vector<double> k2 = { 1,5,5,5,5,1 };
vector<double> y2 = { 1,1,0,0,2,2 };

double getMo2(double d, double e, double y)
{
	double interval, Mo2 = 0;
	for (int i = 0; i < d2.size() - 1; i++)
	{
		interval = (d2[i + 1] * d + e2[i + 1] * e) / k2[i + 1] - (d2[i] * d + e2[i] * e) / k2[i];
		Mo2 += (y2[i] + y2[i + 1]) * y / 2 * interval;
	}
	return Mo2;
}

int main()
{ 
	double Mo2 = 0;
	double d0 = 0;
	double e0 = 5;
	double y0 = 1;

	double Mo1_a = 0;
	double Mo1_x = 0;

	if (a1.size() != x1.size() || d2.size() != e2.size() || e2.size() != k2.size() || k2.size() != y2.size())
		return 0;

	for (int i = 0; i < a1.size(); i++)
	{
		Mo1_a += a1[i];
		Mo1_x += x1[i];
	}

	double best = 100, delta;
	
	for (double d = -100; d < 100; d += 0.1)
	{
		for (double e = d + 20.0; e < 100; e += 0.1)
		{
			delta = abs(1.0 - getMo2(e, d, 1));
			if (delta < best)
			{
				best = delta;
				d0 = d;
				e0 = e;
			}

		}
	}
	cout << getMo2(e0, d0, 1);
	cout << "\n" << e0 << "\n" << d0 << "\n";
	return 1;
}