#include "state.hpp"
#include "stateFactory.hpp"

int main() {
    State<int>& state1 = StateFactory::Create<int>();
    State<int>& state2 = StateFactory::Create<int>();

    state1.set(0);
    state1.set(1);

    state2.set(0);

    return 0;
}
