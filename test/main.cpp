#include <stdio.h>
#include <salt.h>
int main()
{
	salt::vector<int> a;
	salt::vector<int> b;
	salt::vector<int> c;
	a.resize(100);
	b.resize(100);
	c.resize(100);
	a = b + c;

	return 0;
}
