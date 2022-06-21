#pragma once

#include <memory>

template <typename T>
class State final {
    friend class Statefull;

    std::shared_ptr<T> m_value = nullptr;

public:
    State() = delete;

    State(const T& value) : m_value(std::make_shared<T>(value)) {}

    State(T&& value) : m_value(std::make_shared<T>(value)) {}

    ~State() = default;

    const T& get() const& {
        return *m_value.get();
    }

    const T&& get() const&& {
        return *m_value.get();
    }

    void reset() const {
        m_value.reset();
    }

    void reset(const T& value) const {
        m_value.reset(value);
    }

    operator const T&() const& {
        return get();
    }

    operator const T&&() const&& {
        return get();
    }

private:
    T& getRef() & {
        return *m_value.get();
    }

    void set(const T& value) {
        if (m_value == nullptr) {
            m_value = std::make_shared<T>(value);
        } else {
            *m_value = value;
        }
    }

    void bind(const State& state) {
        m_value = state.m_value;
    }

    State& operator=(const T& value) {
        set(value);
        return *this;
    }

    State& operator=(T&& value) {
        set(value);
        return *this;
    }

    State& operator=(const State& state) {
        combine(state);
        return *this;
    }

    State& operator=(State&& state) {
        combine(state);
        return *this;
    }
};
