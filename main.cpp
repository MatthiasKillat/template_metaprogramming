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

    static void ifCondIsTrueOnly()
    {
        std::cout << "true only" << std::endl;
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

    static void ifCondIsFalseOnly()
    {
        std::cout << "false only" << std::endl;
    }

    //add whatever is needed in the negative case
};

template <typename T, typename Cond = TrueOrFail<MyCond<T>>>
struct DoesNotCompileIfCondIsFalse
{
    static void print()
    {
        std::cout << "default - true" << std::endl;
    }
    //the false instantiation should lead to a compiler error
};

struct Foo
{
};

int main(int argc, char **argv)
{

    std::cout << "value = " << Eval<True>::value() << " type() = " << Eval<True>::type() << std::endl;

    std::cout << "value = " << Eval<False>::value() << " type() = " << Eval<False>::type() << std::endl;

    std::cout << "value = " << Eval<MyCond<int>>::value() << " type() = " << Eval<MyCond<int>>::type() << std::endl;

    DependsOnCond<int>::print();
    DependsOnCond<bool>::print();
    DependsOnCond<double>::print();
    DependsOnCond<Foo>::print();

    DependsOnCond<int>::ifCondIsTrueOnly();
    //DependsOnCond<int>::ifCondIsFalseOnly();
    //DependsOnCond<Foo>::ifCondIsTrueOnly();
    DependsOnCond<Foo>::ifCondIsFalseOnly();

    //condition is true ... ok
    DoesNotCompileIfCondIsFalse<int>::print();

    //condition is false ... this does not compile, as intended
    //DoesNotCompileIfCondIsFalse<bool>::print();

    return 0;
}
