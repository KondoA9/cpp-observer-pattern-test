#pragma once

#include <memory>
#include <vector>

namespace Internal {
    class IState;
}

class StateStorage final {
    using StatePtr = std::shared_ptr<Internal::IState>;

private:
    std::vector<StatePtr> m_states;

private:
    StateStorage() = default;

    static StateStorage& Instance();

public:
    static StatePtr Get(size_t id);

    static void Store(const StatePtr& state);
};
