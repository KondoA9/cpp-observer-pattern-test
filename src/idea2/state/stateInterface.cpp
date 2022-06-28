#include "stateInterface.hpp"

#include "stateGroup/stateGroupInterface.hpp"
#include "storage/stateGroupStorage.hpp"

namespace Internal {
    IStateGroup& IState::getGroupInterface() const {
        return *StateGroupStorage::Get(_stateGroupId()).get();
    }
}
