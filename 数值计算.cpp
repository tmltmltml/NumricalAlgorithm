#include <iostream>
#include "Evaluation.h"
#include <cstdlib>
using namespace std;

int menu();                                        //ѡ��˵�

int main()
{
	int choice = 0;
	while(choice = menu())
	{
		Evaluation e;
		e.setFlag(choice);                         //����choice ȷ��һ���㷨�����ַ���Steffensen�����ҽط���ţ�ٵ�����)

		if(e.equal_step_width_scan())
			cout << e << endl;
		else
			cout << "there is no answer!" << endl;
	}
	return 0;
}

int menu()
{
	system("cls");
	cout << "please prepare the function:\"fun\",\"fun2\",\"fun3\" " << endl;
	cout << "there are three algorithms to choose:" << endl;
	cout << "1. dichotomy(f(x) = 0)" << endl;
	cout << "2. steffensen(x = f(x))" << endl;
	cout << "3. secant(f(x) = 0)" << endl;
	cout << "4. newton(f(x) = 0)" << endl;
	cout << "0. exit " << endl;
	cout << "input your choose" << endl;
	int n;
	cin >> n;
	system("cls");
	return n;
}

