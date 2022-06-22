#include "factory/stateFactory.hpp"

int main() {
    const auto onChange = [](const int& current, const int& prev) {
        std::cout << "onChange()"
                  << " current=" << current << ", previous=" << prev << std::endl;
    };

    auto& state1 = StateFactory::Create<int>(1);
    auto& state2 = StateFactory::Create<int>(2);
    auto& state3 = StateFactory::Create<int>(3);

    state1.onChange(onChange);
    state2.onChange(onChange);
    state3.onChange(onChange);

    state1.setValue(101);
    state2.setValue(102);

    std::cout << "bind 1 to 2" << std::endl;
    state1.bindTo(state2);

    state1.setValue(5);

    std::cout << "bind 3 to 1 & 2" << std::endl;
    state3.bindTo(state2);

    state1.setValue(6);

    return 0;
}
