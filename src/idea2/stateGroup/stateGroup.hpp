#pragma once

#include <memory>

#include "../state/state.hpp"
#include "stateGroupInterface.hpp"

namespace Internal {
    template <typename T>
    class StateGroup final : public IStateGroup {
        friend class State<T>;
        friend class StateGroupFactory;

    private:
        std::shared_ptr<T> m_value = nullptr;

    public:
        const T& value() const {
            return *m_value.get();
        }

        void setValue(const T& value) {
            *m_value = value;
        }

    private:
        StateGroup(size_t id, const T& value) : IStateGroup(id), m_value(std::make_shared<T>(value)) {}

        void fireOnChangeOfAllStates(const T& current, const T& previous) const {
            for (const auto& state : m_states) {
                static_cast<State<T>&>(*state.get()).fireOnChange(current, previous);
            }
        }
    };
}
