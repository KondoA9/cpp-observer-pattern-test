#pragma once

#include <functional>
#include <memory>

template <typename T>
class State final {
    friend class Statefull;

    std::shared_ptr<T> m_value = nullptr;
    std::function<void(const T&, const T&)> m_onChange;

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

    void onChange(const std::function<void(const T& newValue, const T& oldValue)>& func, bool inherit = false) {
        if (inherit && m_onChange) {
            const auto inherited = m_onChange;
            m_onChange           = [this, inherited, func](const T& newValue, const T& oldValue) {
                inherited(newValue, oldValue);
                func(newValue, oldValue);
            };
        } else {
            m_onChange = func;
        }
    }

    operator const T&() const& {
        return get();
    }

    operator const T&&() const&& {
        return get();
    }

    const T* const operator->() const {
        return m_value.get();
    }

private:
    T& getRef() & {
        return *m_value.get();
    }

    void set(const T& value) {
        fireChange(value);

        if (m_value == nullptr) {
            m_value = std::make_shared<T>(value);
        } else {
            *m_value = value;
        }
    }

    void bind(const State& state) {
        fireChange(state.get());

        m_value = state.m_value;
    }

    void fireChange(const T& newValue) {
        const T& oldValue = m_value == nullptr ? newValue : get();

        if (m_onChange) {
            m_onChange(newValue, oldValue);
        }
    }

    State& operator=(const T& value) {
        set(value);
        return *this;
    }

    State& operator=(T&& value) {
        set(value);
        return *this;
    }
};
