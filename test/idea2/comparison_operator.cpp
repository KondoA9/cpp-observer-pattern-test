#include <assert.h>

#include "state/state.hpp"

int main() {
    auto value1 = State<int>(1);
    auto value2 = State<int>(2);

    assert(value1 == value1);
    assert(value1 == value1.value());
    assert(value1.value() == value1);

    assert(value1 != value2);
    assert(value1 != value2.value());
    assert(value1.value() != value2);

    assert(value1 < value2);
    assert(value1 < value2.value());
    assert(value1.value() < value2);

    assert(value1 <= value2);
    assert(value1 <= value2.value());
    assert(value1.value() <= value2);

    assert(value2 > value1);
    assert(value2 > value1.value());
    assert(value2.value() > value1);

    assert(value2 >= value1);
    assert(value2 >= value1.value());
    assert(value2.value() >= value1);

    return 0;
}
