#include <assert.h>

#include "factory/stateFactory.hpp"

void Validate(const State<int>& state, const State<int>& target1, const State<int>& target2, int value) {
    const bool isEqualToValue = state == value;
    const bool isSame         = state == target1 && state == target2;

    assert(isEqualToValue);
    assert(isSame);
}

int main() {
    State<int>& state   = StateFactory::Create<int>(1);
    State<int>& target1 = StateFactory::Create<int>(2);
    State<int>& target2 = StateFactory::Create<int>(3);

    // Value is the same when bind
    target1.bind(state);
    target2.bind(state);
    Validate(state, target1, target2, 1);

    // Set value to the specific value
    {
        state.setValue(2);
        Validate(state, target1, target2, 2);

        target1.setValue(3);
        Validate(state, target1, target2, 3);

        target2.setValue(4);
        Validate(state, target1, target2, 4);
    }

    // Set value by the function
    {
        state.setValue([](int& value) { value++; });
        Validate(state, target1, target2, 5);

        target1.setValue([](int& value) { value++; });
        Validate(state, target1, target2, 6);

        target2.setValue([](int& value) { value++; });
        Validate(state, target1, target2, 7);
    }

    return 0;
}
