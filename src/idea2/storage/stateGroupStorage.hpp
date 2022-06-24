#pragma once

#include <memory>
#include <vector>

namespace Internal {
    class IStateGroup;
}

class StateGroupStorage final {
    using StateGroupPtr = std::shared_ptr<Internal::IStateGroup>;

private:
    std::vector<StateGroupPtr> m_stateGroups;

private:
    StateGroupStorage() = default;

    static StateGroupStorage& Instance();

public:
    static StateGroupPtr Get(size_t id);

    static void Store(const StateGroupPtr& group);
};
