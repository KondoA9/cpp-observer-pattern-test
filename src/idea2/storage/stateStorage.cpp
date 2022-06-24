#include "stateStorage.hpp"

#include <stdexcept>

#include "findElement.hpp"
#include "state/stateInterface.hpp"

StateStorage& StateStorage::Instance() {
    static StateStorage instance;
    return instance;
}

StateStorage::StatePtr StateStorage::Get(size_t id) {
    const auto result =
        findElement<StatePtr>(Instance().m_states, id, [](const StatePtr& state) { return state->_stateId(); });

    if (result.has_value()) {
        return Instance().m_states[result.value()];
    } else {
        throw std::runtime_error("StateStorage::Get(): Unstored state identifier");
    }
}

void StateStorage::Store(const StatePtr& state) {
    Instance().m_states.emplace_back(state);
}
