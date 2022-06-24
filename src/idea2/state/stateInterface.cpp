#include "stateInterface.hpp"

#include "storage/stateGroupStorage.hpp"

namespace Internal {
    std::shared_ptr<IStateGroup> IState::getGroup() const {
        return StateGroupStorage::Get(_stateGroupId());
    }
}
