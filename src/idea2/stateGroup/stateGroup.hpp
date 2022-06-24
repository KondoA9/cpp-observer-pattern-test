#pragma once

#include <memory>
#include <vector>

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
        StateGroup() = delete;

        const T& value() const {
            return *m_value.get();
        }

        void setValue(const T& value) {
            *m_value = value;
        }

    private:
        StateGroup(size_t id, const T& value) : IStateGroup(id), m_value(std::make_shared<T>(value)) {}

        void fireOnChange(const T& current, const T& previous) {
            for (auto& state : m_states) {
                std::dynamic_pointer_cast<State<T>>(state)->fireOnChange(current, previous);
            }
        }
    };
}
