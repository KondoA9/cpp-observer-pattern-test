#pragma once

#include <functional>

#include "../stateGroup/stateGroup.hpp"
#include "stateInterface.hpp"

namespace Internal {
    template <typename T>
    class StateGroup;
}

template <typename T>
class State final : public Internal::IState {
    using OnChangeFuncType = std::function<void(const T& current, const T& previous)>;

    friend class Internal::StateGroup<T>;
    friend class StateFactory;

private:
    OnChangeFuncType m_onChange;

public:
    const T& value() const {
        return getGroup().value();
    }

    void bind(const State& state) {
        // Bind if not in the same group
        if (_stateGroupId() != state._stateGroupId()) {
            auto& group = state.getGroup();
            group.addState(_stateId());
        }
    }

    void setOnChange(const OnChangeFuncType& func) {
        m_onChange = func;
    }

    void setValue(const T& newValue) {
        auto& group = getGroup();
        group.fireOnChangeOfAllStates(newValue, value());
        group.setValue(newValue);
    }

    operator const T&() const& {
        return value();
    }

    operator const T&&() const&& {
        return value();
    }

    bool operator==(const State<T>& other) const {
        return value() == other.value();
    }

    bool operator!=(const State<T>& other) const {
        return value() != other.value();
    }

    bool operator==(const T& val) const {
        return value() == val;
    }

    bool operator!=(const T& val) const {
        return value() != val;
    }

private:
    using Internal::IState::IState;

    Internal::StateGroup<T>& getGroup() const {
        return static_cast<Internal::StateGroup<T>&>(getGroupInterface());
    }

    void fireOnChange(const T& current, const T& previous) const {
        if (m_onChange) {
            m_onChange(current, previous);
        }
    }
};

template <typename T>
bool operator==(const T& value, const State<T>& state) {
    return value == state.value();
}

template <typename T>
bool operator!=(const T& value, const State<T>& state) {
    return value != state.value();
}
