#include "stateGroupInterface.hpp"

#include "state/stateInterface.hpp"
#include "storage/stateGroupStorage.hpp"
#include "storage/stateStorage.hpp"

namespace Internal {
    void IStateGroup::addState(size_t id) {
        const auto state = StateStorage::Get(id);
        state->setGroup(m_id);
        m_states.emplace_back(state);
    }

    void IStateGroup::removeState(size_t id) {
        for (size_t i = 0; i < m_states.size(); i++) {
            if (m_states[i]->_stateId() == id) {
                m_states.erase(m_states.begin() + i);
                break;
            }
        }

        m_states.shrink_to_fit();

        if (m_states.size() == 0) {
            // Release this
            StateGroupStorage::Release(m_id);
        }
    }
}
