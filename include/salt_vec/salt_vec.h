#ifndef SALT_VEC_H
#define SALT_VEC_H
#include <vector>
#include <arm_sve.h>

namespace salt {
#ifndef ENABLE_SVE

#define VL_ADD(dst, src0, src1, len)               \
   for (size_t i = 0; i < len; i += svcntw()) {    \
       svbool_t pg =  svwhilelt_b32(i, len);       \
       svint32_t add = svadd_x(pg, svld1(pg, src0 + i), svld1(pg, src1 + i)); \
       svst1(pg, dst + i, add); \
   }               \

#else

#define VL_ADD(dst, src0, src1, len)               \
   for (size_t i = 0; i < len; i += 1) {    \
       dst[i] = src0[i] + src1[i]; \
   }               \

#endif

template<typename T>
class vector : public std::vector<T> {
public:
    vector<T> operator+ (const vector<T>& src)
    {
	auto ret = *this;    
        size_t size = std::min(src.size(), this->size());
	VL_ADD(ret.data(), src.data(), this->data(), size)
	return ret;
    }

    vector<T>& operator+= (const vector<T>& src)
    {
        size_t size = std::min(src.size(), this->size());
        VL_ADD(this->data(), src.data(), this->data(), size)
        return *this;
    }

};

}

#endif
