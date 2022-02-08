#include <limits>

template<typename Type>
constexpr Type sadd(const Type& a, const Type& b) {
    Type s = a + b;
    if((a<0) && (b<0) && (s > a)){
            s = std::numeric_limits<Type>::min();
    }else if((a>0) && (b>0) && (s < a)){
            s = std::numeric_limits<Type>::max();
    }
    return s;
}

template<typename Type>
constexpr Type ssub(const Type& a, const Type& b){
    Type s = a - b;
    if((a > 0) && (b < 0) && (s < a)){
        s = std::numeric_limits<Type>::max();
    }else if((a < 0) && (b > 0) && (s > a)){
        s = std::numeric_limits<Type>::min();
    }
    return s;
}

template<typename Type>
constexpr Type smul(const Type& _a, const Type& _b){
    int sign = 1;
    Type a = _a;
    Type b = _b;
    if(a < 0){
        sign = -sign;
    }
    if(b < 0){
        sign = -sign;
    }
    Type s = a * b;
    if((a != 0) && (b != (s/a))){
        if(sign < 0){
            s = std::numeric_limits<Type>::min();
        }else {
            s = std::numeric_limits<Type>::max();
        }
    }
    return s;
}

template<typename Type>
class Saturate{
    typedef Saturate<Type> this_t;
    Type _data;
public:
    Saturate():_data(0){}
    Saturate(const Type& d): _data(d){}
    template<typename T>
    explicit operator T(){
        return static_cast<T>(_data);
    }
    constexpr this_t operator+(const this_t& o) const {
        return (this_t) sadd(_data, o._data);
    }
    constexpr this_t operator-(const this_t & o) const {
        return (this_t) ssub(_data, o._data);
    }
    constexpr this_t operator*(const this_t& o) const {
        return (this_t) smul(_data, o._data);
    }
    constexpr this_t operator/(const this_t& o) const {
        return (this_t)(_data / o._data);
    }
};
