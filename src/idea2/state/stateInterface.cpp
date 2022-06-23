#include "stateInterface.hpp"

#include "storage/stateGroupStorage.hpp"

std::shared_ptr<IStateGroup> IState::getGroup() const {
    return StateGroupStorage::Get(groupId());
}
