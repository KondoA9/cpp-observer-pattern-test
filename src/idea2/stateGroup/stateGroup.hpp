#pragma once

#include <memory>

#include "../state/state.hpp"
#include "stateGroupInterface.hpp"

template <typename T>
class State;

namespace Internal {
    template <typename T>
    class StateGroup final : public IStateGroup {
        friend class StateGroupFactory;

    private:
        std::shared_ptr<T> m_value = nullptr;

    public:
        T& valueRef() const {
            return *m_value.get();
        }

        const T& value() const {
            return *m_value.get();
        }

        void setValue(const T& value) {
            *m_value = value;
        }

        void fireOnChangeOfAllStates(const T& current, const T& previous) const {
            for (const auto& state : m_states) {
                static_cast<State<T>&>(*state.get()).fireOnChange(current, previous);
            }
        }

        void updateValues() {
            for (const auto& state : m_states) {
                static_cast<State<T>&>(*state.get()).updateValue();
            }
        }

    private:
        StateGroup(size_t id, const T& value) : IStateGroup(id), m_value(std::make_shared<T>(value)) {}
    };
}
