#include <stdio.h>
#include <salt.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>

using namespace std::chrono;
template <typename T>
static inline void Rnd(T &v, int ub = 100000)
{
    for (auto &ele : v) {
	ele = rand() % ub;
    }
}

static inline void ShowImpl(std::string name)
{
    std::cout << "show " << name << std::endl;
}

template <typename T>
static inline void ShowImpl(std::string name, salt::vector<T> &v)
{
    ShowImpl(name);
    for (auto &ele : v) {
	 std::cout << ele << ", ";
    }
    std::cout << std::endl;
}

#define SHOW(v)                        \
    ShowImpl(#v, v);                    \

#define SHOW_ACTION(action)            \
    ShowImpl(std::string(#action) + " action");       \


#define PWATCH(action)                  \
{   	                                      \
    SHOW_ACTION(action);                      \	
    auto begin = high_resolution_clock::now();\
    action;\
    auto end = high_resolution_clock::now();  \
    auto elapsed_time = duration_cast<nanoseconds>(end - begin);\
    std::cout << (float)(elapsed_time.count())/1000.0 << "ms" << std::endl;\
}	\

template <typename T>
class Vector : public std::vector<T> {
	public:
Vector operator+ (const Vector &src) 
{
    auto ret = *this;
    for(size_t i = 0; i < ret.size(); i++) {
	ret[i] += src[i];
    }
    return ret;
}
void operator+= (const Vector &src) 
{
    for(size_t i = 0; i < (*this).size(); i++) {
	(*this)[i] += src[i];
    }
}
};

template <typename T>
void TestSuite(size_t size, int ub)
{
        T a;
        T b;
        T c;
        a.resize(size);
        Rnd(a, ub);
        b.resize(size);
        Rnd(b, ub);
        c.resize(size);
        Rnd(c, ub);
        //SHOW(a);
        //SHOW(b);
        //SHOW(c);
        PWATCH(a = b + c);
        //SHOW(a);
        //SHOW(b);
        //SHOW(c);
        PWATCH(a += b);
        //SHOW(a);
}


int main(int argc, char** argv)
{
	int testTime = std::atoi(argv[1]);
	TestSuite<salt::vector<int>>(testTime, 10);
        TestSuite<Vector<int>>(testTime, 10);
	return 0;
}
