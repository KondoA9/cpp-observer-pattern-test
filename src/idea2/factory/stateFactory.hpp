#pragma once

#include <memory>

#include "../factory/stateGroupFactory.hpp"
#include "../state/state.hpp"
#include "../stateGroup/stateGroupInterface.hpp"

class StateFactory final {
private:
    size_t m_id = 1;

public:
    template <typename T>
    static State<T>& Create(const T& value = T()) {
        const auto state = std::shared_ptr<State<T>>(new State<T>(Instance().m_id++));
        StoreState(state);

        IStateGroup& stateGroup = StateGroupFactory::Create<T>(value);
        stateGroup.add(state->_stateId());

        return *state.get();
    }

private:
    StateFactory() = default;

    static StateFactory& Instance();

    static void StoreState(const std::shared_ptr<IState>& state);
};
