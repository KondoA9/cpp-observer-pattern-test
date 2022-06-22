#include "stateStorage.hpp"

#include "state/stateInterface.hpp"

StateStorage& StateStorage::Instance() {
    static StateStorage instance;
    return instance;
}

std::shared_ptr<IState> StateStorage::Get(size_t id) {
    for (const auto& state : Instance().m_states) {
        if (state->id() == id) {
            return state;
        }
    }

    return nullptr;
}

void StateStorage::Store(const std::shared_ptr<IState>& state) {
    Instance().m_states.emplace_back(state);
}
