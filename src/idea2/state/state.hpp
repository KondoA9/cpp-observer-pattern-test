#pragma once

#include "../factory/stateFactory.hpp"
#include "stateImpl.hpp"

template <typename T>
class State final {
private:
    Internal::StateImpl<T>& m_state;

public:
    State() = delete;

    State(const State&) = delete;

    State(State&&) = default;

    State& operator=(const State&) = delete;

    State& operator=(State&&) = default;

    explicit State(const T& value = T()) : m_state(Internal::StateFactory::Create<T>(value)) {}

    ~State() {
        m_state._destroy();
    }

    const T& value() const {
        return m_state.value();
    }

    void bind(const State<T>& state) {
        m_state.bind(state.m_state);
    }

    void setOnChange(const std::function<void(const T& current, const T& previous)>& func, bool inherit = false) {
        m_state.setOnChange(func, inherit);
    }

    void setOnChange(const std::function<void(const T& current)>& func, bool inherit = false) {
        m_state.setOnChange(func, inherit);
    }

    void setOnChange(const std::function<void()>& func, bool inherit = false) {
        m_state.setOnChange(func, inherit);
    }

    void setValue(const T& newValue) {
        m_state.setValue(newValue);
    }

    void setValue(const std::function<void(T& value)>& setter) {
        m_state.setValue(setter);
    }

    // ---------------------------------------------------
    // Conversion operator
    // ---------------------------------------------------

    explicit operator const T&() const {
        return m_state.value();
    }

    // ---------------------------------------------------
    // Assignment operator
    // ---------------------------------------------------

    State<T>& operator=(const T& _value) {
        m_state.setValue(_value);
        return *this;
    }

    // ---------------------------------------------------
    // Comparison operators
    // ---------------------------------------------------

    bool operator==(const State<T>& other) const {
        return m_state.value() == other.value();
    }

    bool operator!=(const State<T>& other) const {
        return m_state.value() != other.value();
    }

    bool operator<(const State<T>& other) const {
        return m_state.value() < other.value();
    }

    bool operator<=(const State<T>& other) const {
        return m_state.value() <= other.value();
    }

    bool operator>(const State<T>& other) const {
        return m_state.value() > other.value();
    }

    bool operator>=(const State<T>& other) const {
        return m_state.value() >= other.value();
    }

    bool operator==(const T& _value) const {
        return m_state.value() == _value;
    }

    bool operator!=(const T& _value) const {
        return m_state.value() != _value;
    }

    bool operator<(const T& _value) const {
        return m_state.value() < _value;
    }

    bool operator<=(const T& _value) const {
        return m_state.value() <= _value;
    }

    bool operator>(const T& _value) const {
        return m_state.value() > _value;
    }

    bool operator>=(const T& _value) const {
        return m_state.value() >= _value;
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
};
