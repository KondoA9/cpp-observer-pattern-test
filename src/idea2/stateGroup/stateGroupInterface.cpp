#include "stateGroupInterface.hpp"

#include "state/stateInterface.hpp"
#include "storage/stateGroupStorage.hpp"
#include "storage/stateStorage.hpp"

void IStateGroup::add(size_t id) {
    const auto state = StateStorage::Get(id);
    state->setGroupId(m_id);
    m_states.emplace_back(state);
}
