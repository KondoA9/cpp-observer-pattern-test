#pragma once

#include <memory>
#include <vector>

#include "stateInterface.hpp"

class StateStorage {
    std::vector<std::shared_ptr<IState>> m_states;

private:
    StateStorage() = default;

    static StateStorage& Instance();

public:
    static std::shared_ptr<IState> Get(size_t id);

    static void Store(const std::shared_ptr<IState>& state);
};
