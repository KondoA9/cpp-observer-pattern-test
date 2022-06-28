#pragma once

#include <memory>

#include "../factory/stateGroupFactory.hpp"
#include "../state/stateImpl.hpp"
#include "../stateGroup/stateGroupInterface.hpp"

namespace Internal {
    class StateFactory final {
    private:
        size_t m_id = 1;

    public:
        template <typename T>
        static StateImpl<T>& Create(const T& value = T()) {
            auto& stateGroup = Internal::StateGroupFactory::Create<T>(value);
            const auto state =
                std::shared_ptr<StateImpl<T>>(new StateImpl<T>(Instance().m_id++, stateGroup.stateGroupId()));

            StoreState(state);
            stateGroup.addState(state->_stateId());

            return *state.get();
        }

    private:
        StateFactory() = default;

        static StateFactory& Instance();

        static void StoreState(const std::shared_ptr<Internal::IState>& state);
    };
}
