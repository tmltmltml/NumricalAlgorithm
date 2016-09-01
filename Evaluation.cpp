#include <iostream>
#include <vector>
#include <cmath>
#include "Evaluation.h"
#include <fstream>
#include <string>
using namespace std;
const double min = 1e-7;
//--------------------------------------------------------------------------------------------
istream& operator >>(istream &in, Evaluation &e)
{
	in >> e.a >> e.b >> e.err;
	return in;
}

ostream& operator <<(ostream &out,const Evaluation &e)
{
	out << "[" << e.a << "," << e.b << "]" << '\t'  << e.err << endl;
	for(size_t i = 0; i != e.vd.size(); ++i)
	{
		out << e.vd[i] << ' ';
		if((i + 1) % 5 == 0)
			out << endl;
	}
	return out;
}
//------------------------------------------------------------------------------------------------

double Evaluation::getA()
{
	return a;
}

double Evaluation::getB()
{
	return b;
}

double Evaluation::getErr()
{
	return err;
}
//--------------------------------------------------------------------------------------------------
void Evaluation::setFlag(int n)
{
	flag = n;
	if(flag == 4)
		p1 = fun3;
	else
		p1 = 0;
	if(flag == 2)
		p = fun2;
	else 
		p = fun;
}
//-------------------------------------------------------------------------------------------------
double Evaluation::getValue(double x)                                                    //获得x对应的函数值，f(x) 或f(x) - x;
{
	if(flag == 2)
		return p(x) - x;
	else
		return p(x);
}
//--------------------------------------------------------------------------------------------------
bool Evaluation::equal_step_width_scan()                                                     //等步长扫描
{
	double t1 = a;                                                                          //set left and right end points
	while(t1 <= b)
	{
		double t2 = (t1 + step_width)>b? b: (t1 + step_width);
		if(getValue(t1) * getValue(t2) <= 0)                                                  
			switch(flag)
		{
			case 1:
				vd.push_back(dicho(t1, t2));
				break;
			case 2:
				vd.push_back(steffensen(t1));
				break;
			case 3:
				vd.push_back(secant(t1, t2));
				break;
			default:
				vd.push_back(newton(t1));
				break;
		}
		if(fabs(getValue(t1)) < err)
			t1 += err;
		else if(fabs(getValue(t2)) < err)
			t1 = t2 + err;
		else
			t1 += step_width;
	}
	if(vd.empty())
		flag = -1;                                                       //这里控制flag 
	return !vd.empty();
}

double Evaluation::dicho(double a, double b)                             //f(x) = 0;
{
	if(fabs(getValue(a)) < err)
		return a;
	if(fabs(getValue(b)) < err)
		return b;
	double c = (a + b) / 2;
	while(fabs(b - a) > err || fabs(getValue(c)) > err)
	{
		if(getValue(a) * getValue(c) < 0)                                               //< 0 or <=0?
			b = c;
		else
			a = c;
		c = (a + b) / 2;
	}
	return c;
}


double Evaluation::steffensen(double xn)                                    //x = f(x)
{
	int L = 0, N;
	cout << "[" << xn << "," << xn + step_width << "]" << endl;
	cout << "input the max times: " << endl;
	cin >> N;
	double xn1 = xn, temp = xn;
	while(fabs(xn1 - xn) > err || fabs(getValue(xn1)) > err)
	{
		++L;
		xn = xn1;
		double yn = p(xn);
		double zn = p(yn);
		if(L > N || fabs(zn - 2 * yn + xn) < ::min)
		{
			cerr << "[" << temp << "," << temp + step_width << "]" << "Steffensen can't be used" << endl;
			cout << "use secant algorithm temporarily" << endl;
			return secant(temp, temp + step_width);
		}
		xn1 = xn - (pow((yn - xn), 2) / (zn - 2 * yn + xn));		
	}
	return xn1;
}

double Evaluation::secant(double x0, double x1)                               //f(x) = 0
{
	double x2 = x1;
	while(fabs(getValue(x1)) > err || fabs(x1 - x0) > err)
	{
		x2 = x1 - p(x1) * (x1 - x0) / (p(x1) - p(x0));
		x0 = x1;
		x1 = x2;
	}
	return x2;
}

double Evaluation::newton(double x0)
{
	int flag = 1;
	double x1 = x0 - p(x0) / p1(x0);
	if(fabs(p1(x0)) > ::min && flag)
	{
		while(fabs(x1 - x0) > err || fabs(getValue(x1) - getValue(x0)) > err)
		{
			x0 = x1;
			if(fabs(p1(x0)) < ::min)
			{
				flag = 0;
				break;
			}
			x1 = x0 - p(x0) / p1(x0);
		}
	}
	if(!flag || fabs(p1(x0)) < ::min)
	{
		cerr << "[" << x0 << "," << x0 + step_width << "]" << "newton algorithm can't be used" << endl;
		cout << "use secant temporarily" << endl;
		return secant(x0, x0 + step_width);
	}
	return x1;
}

//-------------------------------------------------------------------
void Evaluation::write_to_file()
{
	ofstream outfile;
	outfile.open("Evaluation.txt", ios::out | ios::app);
	outfile << endl;

	ifstream infile("fun.cpp");
	string str;
	getline(infile, str);
	while(str != "{")
			getline(infile, str);
	getline(infile, str);
	while(str != "}")
	{
		outfile << str << endl;
		getline(infile, str);
	}
	infile.close();
	outfile << "[" << a << "," << b << "]" << '\t' << err << endl;
	switch(flag)
	{
	case 1:
		outfile << "Dichotomy Algorithm" << endl;
		break;
	case 2:
		outfile << "Steffensen Algorithm" << endl;
		break;
	case 3:
		outfile << "Secant Algorithm" << endl;
		break;
	default:
		outfile << "Newton Algorithm" << endl;
		break;
	}
	if(flag != -1)
		for(size_t i = 0; i != vd.size(); ++i)
		{
			outfile << vd[i] << ' ';
			if((i + 1) % 5 == 0)
				outfile << endl;
		}
	else
		outfile << "there is no answer!" << endl;
	outfile << endl;
	outfile.close();
}
//-------------------------------------------------------------------
Evaluation::~Evaluation()
{
	char y = 'n';
	cout << "do you want to write the answers to a file?(input y / n)" << endl;
	cin >> y;
	if(y == 'y')
		write_to_file();
}