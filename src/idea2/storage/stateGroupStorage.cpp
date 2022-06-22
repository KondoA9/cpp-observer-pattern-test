#include "stateGroupStorage.hpp"

#include "stateGroup/stateGroup.hpp"

StateGroupStorage& StateGroupStorage::Instance() {
    static StateGroupStorage instance;
    return instance;
}

std::shared_ptr<IStateGroup> StateGroupStorage::Get(size_t id) {
    for (const auto& stateGroup : Instance().m_stateGroups) {
        if (stateGroup->id() == id) {
            return stateGroup;
        }
    }

    return nullptr;
}

void StateGroupStorage::Store(const std::shared_ptr<IStateGroup>& state) {
    Instance().m_stateGroups.emplace_back(state);
}

void StateGroupStorage::Release(size_t id) {
    for (size_t i = 0; i < Instance().m_stateGroups.size(); i++) {
        auto& stateGroup = Instance().m_stateGroups[i];
        if (stateGroup->id() == id) {
            stateGroup.reset();
            Instance().m_stateGroups.erase(Instance().m_stateGroups.begin() + i);
            break;
        }
    }
}
