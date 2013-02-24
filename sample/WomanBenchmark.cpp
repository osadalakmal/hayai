#include <hayai.hpp>
#include "Woman.hpp"

BENCHMARK_NEW_(Woman, MakeSomeCoffee, 10, 100, true)
{
    Woman::MakeSomeCoffee(10,
                          UnitCup);
}
