#include "stateGroupStorage.hpp"

#include "stateGroup/stateGroupInterface.hpp"

StateGroupStorage& StateGroupStorage::Instance() {
    static StateGroupStorage instance;
    return instance;
}

std::shared_ptr<IStateGroup> StateGroupStorage::Get(size_t id) {
    for (const auto& stateGroup : Instance().m_stateGroups) {
        if (stateGroup->stateGroupId() == id) {
            return stateGroup;
        }
    }

    throw std::exception("StateGroupStorage::Get(): Unstored state group identifier");
}

void StateGroupStorage::Store(const std::shared_ptr<IStateGroup>& state) {
    Instance().m_stateGroups.emplace_back(state);
}
