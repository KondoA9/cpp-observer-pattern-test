#pragma once

#include <functional>

#include "../stateGroup/stateGroup.hpp"
#include "stateInterface.hpp"

template <typename T>
class StateGroup;

template <typename T>
class State final : public IState {
    using OnChangeFuncType = std::function<void(const T& current, const T& previous)>;

    friend class StateGroup<T>;
    friend class StateFactory;

private:
    OnChangeFuncType m_onChange;

public:
    State() = delete;

    const T& value() const {
        return std::dynamic_pointer_cast<StateGroup<T>>(getGroup())->value();
    }

    void bindTo(const State& state) {
        // Bind if not in the same group
        if (groupId() != state.groupId()) {
            const auto group = state.getGroup();
            group->add(id());
        }
    }

    void setOnChange(const OnChangeFuncType& func) {
        m_onChange = func;
    }

    void setValue(const T& newValue) {
        const auto group = std::dynamic_pointer_cast<StateGroup<T>>(getGroup());
        group->fireOnChange(newValue, value());
        group->setValue(newValue);
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
    explicit State(size_t id) : IState(id) {}

    void fireOnChange(const T& current, const T& previous) {
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
