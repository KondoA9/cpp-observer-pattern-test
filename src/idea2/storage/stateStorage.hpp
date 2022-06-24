#pragma once

#include <memory>
#include <vector>

namespace Internal {
    class IState;
}

class StateStorage final {
    std::vector<std::shared_ptr<Internal::IState>> m_states;

private:
    StateStorage() = default;

    static StateStorage& Instance();

public:
    static std::shared_ptr<Internal::IState> Get(size_t id);

    static void Store(const std::shared_ptr<Internal::IState>& state);
};
