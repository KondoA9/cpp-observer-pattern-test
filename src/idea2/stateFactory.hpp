#pragma once

#include "state.hpp"
#include "stateStorage.hpp"

class StateFactory {
    size_t m_id = 1;

private:
    StateFactory() = default;

    static StateFactory& Instance() {
        static StateFactory instance;
        return instance;
    }

public:
    template <typename T>
    static State<T>& Create() {
        auto state = std::shared_ptr<State<T>>(new State<T>(Instance().m_id++));
        StateStorage::Store(state);
        return *state.get();
    }
};
