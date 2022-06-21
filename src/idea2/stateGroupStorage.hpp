#pragma once

#include <memory>
#include <vector>

class IStateGroup;

class StateGroupStorage {
    std::vector<std::shared_ptr<IStateGroup>> m_stateGroups;

private:
    StateGroupStorage() = default;

    static StateGroupStorage& Instance();

public:
    static std::shared_ptr<IStateGroup> Get(size_t id);
};
