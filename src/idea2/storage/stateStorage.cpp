#include "stateStorage.hpp"

#include <stdexcept>

#include "state/stateInterface.hpp"

StateStorage& StateStorage::Instance() {
    static StateStorage instance;
    return instance;
}

std::shared_ptr<IState> StateStorage::Get(size_t id) {
    for (const auto& state : Instance().m_states) {
        if (state->_stateId() == id) {
            return state;
        }
    }

    throw std::runtime_error("StateStorage::Get(): Unstored state identifier");
}

void StateStorage::Store(const std::shared_ptr<IState>& state) {
    Instance().m_states.emplace_back(state);
}
