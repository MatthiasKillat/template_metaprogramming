#include <iostream>

#include "cond_check.hpp"

//some condition of interest that depends on T and can depend on other args
//(here X, but more Y, Z, ,,, would be possible in the general case
template <typename T, typename X>
using IntegralAndNotX = Boolean<
    std::is_integral<T>::value &&
    !std::is_same<T, X>::value>;

template <typename T>
using MyCond = IntegralAndNotX<T, bool>;

template <typename T, typename Cond = MyCond<T>>
struct DependsOnCond
{
    static void print()
    {
        std::cout << "default" << std::endl;
    }
};

//positive case specialization
template <typename T>
struct DependsOnCond<T, True>
{
    static void print()
    {
        std::cout << "true" << std::endl;
    }

    //add whatever is needed in the positive case
};

//negative case specialization
template <typename T>
struct DependsOnCond<T, False>
{
    static void print()
    {
        std::cout << "false" << std::endl;
    }

    //add whatever is needed in the negative case
};

struct Foo
{
};

int main(int argc, char **argv)
{

    auto result = Eval<True>::value();
    std::cout << result << " " << Eval<True>::type() << std::endl;

    result = Eval<False>::value();
    std::cout << result << " " << Eval<False>::type() << std::endl;

    result = Eval<MyCond<int>>::value();
    std::cout << result << " " << Eval<MyCond<int>>::type() << std::endl;

    DependsOnCond<int>::print();
    DependsOnCond<bool>::print();
    DependsOnCond<double>::print();
    DependsOnCond<Foo>::print();

    return 0;
}
