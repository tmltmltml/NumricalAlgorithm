#include <cmath>                                     //mathematica lib

double fun2(double x)
{
	x = -0.5 - 2 * pow(x, 3) + 4 * pow(x, 2);
	return x;
}

//eg:

//x = f(x);
//x = (x * x - 4) / 3;
//x = sqrt(sin(x) + 1) / 3;


//C++              math
//exp(x)           e ^ x;
//pow(x, *)        x ^ *;
//cos(x)           cosx;
//sin(x)           sinx;
//acos(x)          arccosx;
//asin(x)          arcsinx;
//atan(x)          arctanx;
//fabs(x)          |x|;
//log(x)           lnx;
//log10(x)         lgx;
//sqrt(x)          x ^ (1 / 2);