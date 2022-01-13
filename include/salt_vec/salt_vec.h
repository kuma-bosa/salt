#ifndef SALT_VEC_H
#define SALT_VEC_H

#include <vector>
#include <arm_sve.h>
namespace salt {
template<typename T>
class vector : public std::vector<T> {
public:
    int a = 0;
    vector<T> operator+ (const vector<T>& src)
    {
        size_t size = std::min(src.size(), this->size());
	for (size_t i = 0; i < size; i += svcntw()) {
	    svbool_t pg = svwhilelt_b32(i, size);
	    svint32_t dst = svadd_x(pg, svld1(pg, src.data() + i), svld1(pg, this->data() + i));
	    svst1(pg, this->data() + i, dst);
	}

	return *this;
    }

//    vector<T> operator= (const vector<T>& src)
 //   {

   // }
};

}

#endif
