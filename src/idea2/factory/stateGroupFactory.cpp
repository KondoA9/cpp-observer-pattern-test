#include "stateGroupFactory.hpp"

#include "storage/stateGroupStorage.hpp"

void StateGroupFactory::StoreGroup(const std::shared_ptr<IStateGroup>& group) {
    StateGroupStorage::Store(group);
}
