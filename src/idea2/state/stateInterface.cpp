#include "stateInterface.hpp"

#include "stateGroup/stateGroupInterface.hpp"
#include "storage/stateGroupStorage.hpp"

namespace Internal {
    IState::IState(size_t id, size_t groupId) : m_id(id), m_groupId(groupId) {}

    IStateGroup& IState::getGroupInterface() const {
        return *StateGroupStorage::Get(_stateGroupId()).get();
    }
}
