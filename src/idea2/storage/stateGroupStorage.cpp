#include "stateGroupStorage.hpp"

#include <stdexcept>

#include "findElement.hpp"
#include "stateGroup/stateGroupInterface.hpp"

StateGroupStorage& StateGroupStorage::Instance() {
    static StateGroupStorage instance;
    return instance;
}

std::shared_ptr<Internal::IStateGroup> StateGroupStorage::Get(size_t id) {
    using StateGroupPtr = std::shared_ptr<Internal::IStateGroup>;

    const auto result = findElement<StateGroupPtr>(
        Instance().m_stateGroups, id, [](const StateGroupPtr& stateGroup) { return stateGroup->stateGroupId(); });

    if (result.has_value()) {
        return Instance().m_stateGroups[result.value()];
    } else {
        throw std::runtime_error("StateGroupStorage::Get(): Unstored state group identifier");
    }
}

void StateGroupStorage::Store(const std::shared_ptr<Internal::IStateGroup>& state) {
    Instance().m_stateGroups.emplace_back(state);
}
