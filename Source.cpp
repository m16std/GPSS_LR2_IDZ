#include "Header.h"

int main()
{ 
	cout.precision(3);
	setlocale(LC_ALL, "Russian");

	/*|||||||||||||||||||||||||ВВОДИТЬ||||||||||||||||||||||||||*/
	
	//Нету - 5,6,9,10,13,14,20
	double variant = 15;

	vector<double> a0 = { 1,1,7,8 };
	vector<double> x0 = { 0,1,0,0 };
	vector<double> P0 = { 0.4, 0.42, 0.11, 0.07 };

	vector<double> d1 = { 1,4,3,2,1,0 };
	vector<double> e1 = { 0,1,2,3,4,1 };
	vector<double> k1 = { 1,5,5,5,5,1 };
	vector<double> Y1 = { 1,1,0,0,2,2 };

	/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

	int HandWrite, count3;

	cout << "Вводим значения вручную или берём заготовленные? ";
	cin >> HandWrite;

	if (HandWrite == 1)
	{
		cout << "Введите номер распределения из первого приложения: ";
		cin >> variant;

		cout << "Введите коэффициенты точек и значения вероятности для распределения из второго приложения\n";
		for (int i = 0; i < 4; i++)
		{
			cout << "\nТочка " << i + 1 << ":\n";
			cout << "Коэф. перед 'a' = ";
			cin >> a0[i];
			cout << "Второе слагаемое = ";
			cin >> x0[i];
			cout << "Вероятность = ";
			cin >> P0[i];
		}

		cout << "Введите количество точек из третьего приложения: ";
		cin >> count3;
		cout << "Введите коэффициенты точек и значения вероятности для распределения из третьего приложения\n";
		for (int i = 0; i < count3; i++)
		{
			cout << "\nТочка " << i + 1 << ":";
			cout << "Коэф. перед 'b' = ";
			cin >> d1[i];
			cout << "Коэф. перед 'c' или 'e'= ";
			cin >> e1[i];
			cout << "Делитель = ";
			cin >> k1[i];
			cout << "Значение y = ";
			cin >> Y1[i];
		}
	}

	double Mo1, Mo2, a;

	Mo1 = GetMo1(0, 22, d1, e1, k1, Y1);

	Mo2 = FindMo2(Mo1 / 2.3, variant);

	a = GetP0(a0, x0, P0, Mo1, Mo2);

	PrintP1(0.001, Mo1, 0, 22, d1, e1, k1, Y1);

	cout << "\nMo(P1) = " << Mo1 << "\nMo(P2) = " << Mo2 << "\na = " << a << "\n";

	return 1;
}