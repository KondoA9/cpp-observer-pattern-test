#include <assert.h>

#include "factory/stateFactory.hpp"

int main() {
    State<int>& state   = StateFactory::Create<int>(0);
    State<int>& target1 = StateFactory::Create<int>(0);
    State<int>& target2 = StateFactory::Create<int>(0);

    target1.bind(state);
    target2.bind(state);

    // Get current and previous
    {
        int calledCount = 0;

        const auto func = [&calledCount](const int& current, const int& previous) {
            assert(previous == 0);
            assert(current == 1);
            calledCount++;
        };

        state.setOnChange(func);
        target1.setOnChange(func);
        target2.setOnChange(func);

        state.setValue(1);

        assert(calledCount == 3);
    }

    // Get current
    {
        int calledCount = 0;

        const auto func = [&calledCount](const int& current) {
            assert(current == 2);
            calledCount++;
        };

        state.setOnChange(func);
        target1.setOnChange(func);
        target2.setOnChange(func);

        state.setValue(2);

        assert(calledCount == 3);
    }

    // Get none
    {
        int calledCount = 0;

        const auto func = [&calledCount]() { calledCount++; };

        state.setOnChange(func);
        target1.setOnChange(func);
        target2.setOnChange(func);

        state.setValue(3);

        assert(calledCount == 3);
    }

    // Inherit
    {
        int calledCount1 = 0;
        int calledCount2 = 0;

        const auto func1 = [&calledCount1]() { calledCount1++; };
        const auto func2 = [&calledCount2]() { calledCount2++; };

        state.setOnChange(func1);
        target1.setOnChange(func1);
        target2.setOnChange(func1);

        state.setOnChange(func2, true);
        target1.setOnChange(func2, true);
        target2.setOnChange(func2, true);

        state.setValue(4);

        assert(calledCount1 == 3);
        assert(calledCount2 == 3);

        // Overwrap
        {
            int calledCount3 = 0;

            const auto func3 = [&calledCount3]() { calledCount3++; };

            state.setOnChange(func3);
            target1.setOnChange(func3);
            target2.setOnChange(func3);

            state.setValue(5);

            assert(calledCount1 == 3);
            assert(calledCount2 == 3);
            assert(calledCount3 == 3);
        }
    }

    return 0;
}
