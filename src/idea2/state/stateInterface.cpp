#include "stateInterface.hpp"

#include "storage/stateGroupStorage.hpp"
#include "storage/stateStorage.hpp"

namespace Internal {
    void IState::_destroy() const {
        StateStorage::Release(m_id);
    }

    void IState::setGroup(size_t id) {
        m_group = StateGroupStorage::Get(id);
    }
}
