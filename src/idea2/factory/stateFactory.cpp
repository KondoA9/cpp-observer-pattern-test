#include "stateFactory.hpp"

#include "storage/stateStorage.hpp"

namespace Internal {
    StateFactory& StateFactory::Instance() {
        static StateFactory instance;
        return instance;
    }

    void StateFactory::StoreState(const std::shared_ptr<Internal::IState>& state) {
        StateStorage::Store(state);
    }
}
