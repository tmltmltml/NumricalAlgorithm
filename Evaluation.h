#ifndef HEADER_NUMALGORITHM
#define HEADER_NUMALGORITHM

#include <iostream>
#include <vector>
#include "fun.h"
#include "fun2.h"
#include "fun3.h"
#include <fstream>
using namespace std;

class Evaluation
{
	double a, b, step_width, err;
	vector<double> vd;
	int flag;
	double (*p)(double);
	double (*p1)(double);                                           //p函数的导数
public:
	Evaluation()
	{
		cout << "input left end point, right end point, and the degree of accuracy(scientific notation):" << endl;
		cin >> a >> b >> err;
		step_width = (b - a) * 5 * err;
		flag = 0;
	}
	friend istream& operator >>(istream &, Evaluation &);
	friend ostream& operator <<(ostream &, const Evaluation &);	
	double getA();                                                     //以下三个函数便于以后修改类结构使用，现在暂无用
	double getB();
	double getErr();
	double getValue(double);                                           //返回函数值，对于f(x) = 0返回f(x), x = f(x) 返回f(x) - x;
	void setFlag(int);                                                 //确定p,p1的指向                                                  
	bool equal_step_width_scan();                                      //等步长扫描，每扫描到一个区间调用要求的算法
	double dicho(double ,double);                                      //二分法求解
	double steffensen(double);                                         //Steffensen法求解
	double secant(double, double);                                     //弦截法求解
	double newton(double);                                             //牛顿迭代法求解
	void write_to_file();                                              //将答案写到文件中
	~Evaluation();
};
istream& operator >>(istream &, Evaluation &);
ostream& operator <<(ostream &, const Evaluation &);

#endif
