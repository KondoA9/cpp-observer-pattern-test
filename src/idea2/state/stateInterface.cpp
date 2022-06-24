#include "stateInterface.hpp"

#include "storage/stateGroupStorage.hpp"

namespace Internal {
    IStateGroup& IState::getGroupInterface() const {
        return *StateGroupStorage::Get(_stateGroupId()).get();
    }
}
