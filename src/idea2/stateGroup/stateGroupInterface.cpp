#include "stateGroupInterface.hpp"

#include "state/stateInterface.hpp"
#include "storage/stateGroupStorage.hpp"
#include "storage/stateStorage.hpp"

void IStateGroup::add(size_t id) {
    const auto state = StateStorage::Get(id);
    state->setGroupId(m_id);
    m_states.emplace_back(state);
}

void IStateGroup::remove(size_t id) {
    for (size_t i = 0; i < m_states.size(); i++) {
        const auto& state = m_states[i];
        if (state->id() == id) {
            m_states.erase(m_states.begin() + i);
            break;
        }
    }

    if (m_states.size() == 0) {
        StateGroupStorage::Release(m_id);
    }
}
