#pragma once

#include <memory>
#include <vector>

#include "../stateGroup/stateGroupInterface.hpp"

class StateGroupStorage {
    size_t m_id = 1;
    std::vector<std::shared_ptr<IStateGroup>> m_stateGroups;

private:
    StateGroupStorage() = default;

    static StateGroupStorage& Instance();

public:
    static std::shared_ptr<IStateGroup> Get(size_t id);

    static void Store(const std::shared_ptr<IStateGroup>& group);

    static void Release(size_t id);
};
