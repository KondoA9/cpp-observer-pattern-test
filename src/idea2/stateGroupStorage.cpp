#include "stateGroupStorage.hpp"

#include "stateGroup.hpp"

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
