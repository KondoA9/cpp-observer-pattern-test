#include "stateGroupStorage.hpp"

#include <stdexcept>

#include "findElement.hpp"
#include "stateGroup/stateGroupInterface.hpp"

StateGroupStorage& StateGroupStorage::Instance() {
    static StateGroupStorage instance;
    return instance;
}

StateGroupStorage::StateGroupPtr StateGroupStorage::Get(size_t id) {
    const auto result = findElement<StateGroupPtr>(
        Instance().m_stateGroups, id, [](const StateGroupPtr& stateGroup) { return stateGroup->stateGroupId(); });

    if (result.has_value()) {
        return Instance().m_stateGroups[result.value()];
    } else {
        throw std::runtime_error("StateGroupStorage::Get(): Unstored state group identifier");
    }
}

void StateGroupStorage::Store(const StateGroupPtr& state) {
    Instance().m_stateGroups.emplace_back(state);
}
