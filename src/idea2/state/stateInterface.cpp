#include "stateInterface.hpp"

#include "stateGroup/stateGroupInterface.hpp"
#include "storage/stateGroupStorage.hpp"
#include "storage/stateStorage.hpp"

namespace Internal {
    void IState::_destroy() const {
        StateStorage::Release(m_id);
    }

    IStateGroup& IState::getGroupInterface() const {
        return *StateGroupStorage::Get(_stateGroupId()).get();
    }
}
