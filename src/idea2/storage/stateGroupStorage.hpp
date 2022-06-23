#pragma once

#include <memory>
#include <vector>

#include "../stateGroup/stateGroupInterface.hpp"

class StateGroupStorage final {
    std::vector<std::shared_ptr<IStateGroup>> m_stateGroups;

private:
    StateGroupStorage() = default;

    static StateGroupStorage& Instance();

public:
    static std::shared_ptr<IStateGroup> Get(size_t id);

    static void Store(const std::shared_ptr<IStateGroup>& group);
};
