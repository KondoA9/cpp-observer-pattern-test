#include "stateGroupFactory.hpp"

#include "storage/stateGroupStorage.hpp"

StateGroupFactory& StateGroupFactory::Instance() {
    static StateGroupFactory instance;
    return instance;
}

void StateGroupFactory::StoreGroup(const std::shared_ptr<IStateGroup>& group) {
    StateGroupStorage::Store(group);
}
