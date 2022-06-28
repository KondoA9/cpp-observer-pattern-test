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
    using OnChangeFuncType  = std::function<void(const T& current, const T& previous)>;
    using OnChangeFuncType2 = std::function<void(const T& current)>;
    using OnChangeFuncType3 = std::function<void()>;

    friend class Internal::StateGroup<T>;
    friend class StateFactory;

private:
    OnChangeFuncType m_onChange;

public:
    const T& value() const {
        return getGroup().value();
    }

    void bind(const State<T>& state) {
        // Bind if not in the same group
        if (_stateGroupId() != state._stateGroupId()) {
            const auto prevValue = value();
            auto& group          = state.getGroup();
            group.addState(_stateId());
            fireOnChange(value(), prevValue);
        }
    }

    void setOnChange(const OnChangeFuncType& func, bool inherit = false) {
        setOnChangeImpl(func, inherit);
    }

    void setOnChange(const OnChangeFuncType2& func, bool inherit = false) {
        setOnChangeImpl(std::bind(func, std::placeholders::_1), inherit);
    }

    void setOnChange(const OnChangeFuncType3& func, bool inherit = false) {
        setOnChangeImpl(std::bind(func), inherit);
    }

    void setValue(const T& newValue) {
        auto& group = getGroup();
        group.fireOnChangeOfAllStates(newValue, value());
        group.setValue(newValue);
    }

    void setValue(const std::function<void(T& value)>& setter) {
        const auto prevValue = value();
        auto& group          = getGroup();
        setter(group.valueRef());
        group.fireOnChangeOfAllStates(value(), prevValue);
    }

    // ---------------------------------------------------
    // Conversion operator
    // ---------------------------------------------------

    explicit operator const T&() const {
        return value();
    }

    // ---------------------------------------------------
    // Assignment operator
    // ---------------------------------------------------

    State<T>& operator=(const T& _value) {
        setValue(_value);
        return *this;
    }

    // ---------------------------------------------------
    // Comparison operators
    // ---------------------------------------------------

    bool operator==(const State<T>& other) const {
        return value() == other.value();
    }

    bool operator!=(const State<T>& other) const {
        return value() != other.value();
    }

    bool operator<(const State<T>& other) const {
        return value() < other.value();
    }

    bool operator<=(const State<T>& other) const {
        return value() <= other.value();
    }

    bool operator>(const State<T>& other) const {
        return value() > other.value();
    }

    bool operator>=(const State<T>& other) const {
        return value() >= other.value();
    }

    bool operator==(const T& _value) const {
        return value() == _value;
    }

    bool operator!=(const T& _value) const {
        return value() != _value;
    }

    bool operator<(const T& _value) const {
        return value() < _value;
    }

    bool operator<=(const T& _value) const {
        return value() <= _value;
    }

    bool operator>(const T& _value) const {
        return value() > _value;
    }

    bool operator>=(const T& _value) const {
        return value() >= _value;
    }

    friend bool operator==(const T& value, const State<T>& state) {
        return value == state.value();
    }

    friend bool operator!=(const T& value, const State<T>& state) {
        return value != state.value();
    }

    friend bool operator<(const T& value, const State<T>& state) {
        return value < state.value();
    }

    friend bool operator<=(const T& value, const State<T>& state) {
        return value <= state.value();
    }

    friend bool operator>(const T& value, const State<T>& state) {
        return value > state.value();
    }

    friend bool operator>=(const T& value, const State<T>& state) {
        return value >= state.value();
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

    void setOnChangeImpl(const OnChangeFuncType& func, bool inherit) {
        if (inherit && m_onChange) {
            const auto prevOnChange = m_onChange;

            m_onChange = [prevOnChange, func](const T& current, const T& previous) {
                prevOnChange(current, previous);
                func(current, previous);
            };
        } else {
            m_onChange = func;
        }
    }
};
