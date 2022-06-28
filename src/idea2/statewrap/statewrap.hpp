#pragma once

#include "../factory/stateFactory.hpp"
#include "../state/state.hpp"

template <typename T>
class StateWrap final {
private:
    State<T>& m_state;

public:
    StateWrap() = delete;

    StateWrap(const StateWrap&) = delete;

    StateWrap& operator=(const StateWrap&) = delete;

    explicit StateWrap(const T& value = T()) : m_state(StateFactory::Create<T>(value)) {}

    ~StateWrap() {
        m_state._destroy();
    }

    const T& value() const {
        return m_state.value();
    }

    void bind(const StateWrap<T>& state) {
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

    StateWrap<T>& operator=(const T& _value) {
        m_state.setValue(_value);
        return *this;
    }

    // ---------------------------------------------------
    // Comparison operators
    // ---------------------------------------------------

    bool operator==(const StateWrap<T>& other) const {
        return m_state.value() == other.value();
    }

    bool operator!=(const StateWrap<T>& other) const {
        return m_state.value() != other.value();
    }

    bool operator<(const StateWrap<T>& other) const {
        return m_state.value() < other.value();
    }

    bool operator<=(const StateWrap<T>& other) const {
        return m_state.value() <= other.value();
    }

    bool operator>(const StateWrap<T>& other) const {
        return m_state.value() > other.value();
    }

    bool operator>=(const StateWrap<T>& other) const {
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

    friend bool operator==(const T& value, const StateWrap<T>& state) {
        return value == state.value();
    }

    friend bool operator!=(const T& value, const StateWrap<T>& state) {
        return value != state.value();
    }

    friend bool operator<(const T& value, const StateWrap<T>& state) {
        return value < state.value();
    }

    friend bool operator<=(const T& value, const StateWrap<T>& state) {
        return value <= state.value();
    }

    friend bool operator>(const T& value, const StateWrap<T>& state) {
        return value > state.value();
    }

    friend bool operator>=(const T& value, const StateWrap<T>& state) {
        return value >= state.value();
    }
};
