#include "stateStorage.hpp"

#include <stdexcept>

#include "findElement.hpp"
#include "state/stateInterface.hpp"

StateStorage& StateStorage::Instance() {
    static StateStorage instance;
    return instance;
}

std::shared_ptr<Internal::IState> StateStorage::Get(size_t id) {
    using StatePtr = std::shared_ptr<Internal::IState>;

    const auto result =
        findElement<StatePtr>(Instance().m_states, id, [](const StatePtr& state) { return state->_stateId(); });

    if (result.has_value()) {
        return Instance().m_states[result.value()];
    } else {
        throw std::runtime_error("StateStorage::Get(): Unstored state identifier");
    }
}

void StateStorage::Store(const std::shared_ptr<Internal::IState>& state) {
    Instance().m_states.emplace_back(state);
}
