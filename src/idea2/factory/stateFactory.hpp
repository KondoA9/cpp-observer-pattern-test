#pragma once

#include <memory>

#include "../factory/stateGroupFactory.hpp"
#include "../state/state.hpp"
#include "../stateGroup/stateGroupInterface.hpp"
#include "../storage/stateStorage.hpp"

class StateFactory {
    size_t m_id = 1;

public:
    template <typename T>
    static State<T>& Create(const T& value = T()) {
        const auto state = std::shared_ptr<State<T>>(new State<T>(Instance().m_id++));
        StateStorage::Store(state);

        IStateGroup& stateGroup = StateGroupFactory::Create<T>(value);
        stateGroup.add(state->stateId());

        return *state.get();
    }

private:
    StateFactory() = default;

    static StateFactory& Instance() {
        static StateFactory instance;
        return instance;
    }
};
