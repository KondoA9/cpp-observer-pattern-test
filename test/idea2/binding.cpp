#include <assert.h>

#include <string>

#include "factory/stateFactory.hpp"

template <typename T>
void Validate(const State<T>& state, const State<T>& target1, const State<T>& target2, const T& value) {
    const bool isEqualToValue = state == value;
    const bool isSame         = state == target1 && state == target2;

    assert(isEqualToValue);
    assert(isSame);
}

int main() {
    // State<int>
    {
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
    }

    // std::string
    {
        State<std::string>& state   = StateFactory::Create<std::string>("");
        State<std::string>& target1 = StateFactory::Create<std::string>("");
        State<std::string>& target2 = StateFactory::Create<std::string>("");

        // Value is the same when bind
        target1.bind(state);
        target2.bind(state);
        Validate(state, target1, target2, std::string(""));

        // Set value to the specific value
        {
            state.setValue("a");
            Validate(state, target1, target2, std::string("a"));

            target1.setValue("b");
            Validate(state, target1, target2, std::string("b"));

            target2.setValue("c");
            Validate(state, target1, target2, std::string("c"));
        }

        // Set value by the function
        {
            state.setValue([](std::string& str) { str += "d"; });
            Validate(state, target1, target2, std::string("cd"));

            target1.setValue([](std::string& str) { str += "e"; });
            Validate(state, target1, target2, std::string("cde"));

            target2.setValue([](std::string& str) { str += "f"; });
            Validate(state, target1, target2, std::string("cdef"));
        }
    }

    return 0;
}
