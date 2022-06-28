#pragma once

#include <memory>

#include "../state/stateImpl.hpp"
#include "stateGroupInterface.hpp"

namespace Internal {
    template <typename T>
    class StateImpl;

    template <typename T>
    class StateGroup final : public IStateGroup {
        friend class StateGroupFactory;

    private:
        std::shared_ptr<T> m_value = nullptr;

    public:
        const std::shared_ptr<T>& valuePtr() const {
            return m_value;
        }

        const T& value() const {
            return *m_value.get();
        }

        static void Move(const StateImpl<T>& state, StateGroup<T>& to) {
            const auto stateId = state._stateId();

            // Remove from current group
            state.getGroupInterface().removeState(stateId);

            // Add to new group
            to.addState(stateId);
        }

        void setValue(const T& value) {
            *m_value = value;
        }

        void fireOnChangeOfAllStates(const T& current, const T& previous) const {
            for (const auto& state : m_states) {
                static_cast<StateImpl<T>&>(*state.get()).fireOnChange(current, previous);
            }
        }

        void updateValues() {
            for (const auto& state : m_states) {
                static_cast<StateImpl<T>&>(*state.get()).updateValue();
            }
        }

    private:
        StateGroup(size_t id, const T& value) : IStateGroup(id), m_value(std::make_shared<T>(value)) {}
    };
}
