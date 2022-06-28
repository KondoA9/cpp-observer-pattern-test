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
public:
    using Setter = std::function<void(T& value)>;

private:
    using OnChangeFuncType  = std::function<void(const T& current, const T& previous)>;
    using OnChangeFuncType2 = std::function<void(const T& current)>;
    using OnChangeFuncType3 = std::function<void()>;

    friend class Internal::StateGroup<T>;
    friend class StateFactory;

    std::shared_ptr<T> m_value;

private:
    OnChangeFuncType m_onChange;

public:
    const T& value() const {
        return *m_value;
    }

    void bind(const State<T>& state) {
        // Bind if not in the same group
        if (_stateGroupId() != state._stateGroupId()) {
            const auto previousValue = value();

            Internal::StateGroup<T>::Move(*this, state.getGroup());

            updateValue();
            fireOnChange(value(), previousValue);
        }
    }

    void setOnChange(const OnChangeFuncType& func, bool inherit) {
        setOnChangeImpl(func, inherit);
    }

    void setOnChange(const OnChangeFuncType2& func, bool inherit) {
        setOnChangeImpl(std::bind(func, std::placeholders::_1), inherit);
    }

    void setOnChange(const OnChangeFuncType3& func, bool inherit) {
        setOnChangeImpl(std::bind(func), inherit);
    }

    void setValue(const T& newValue) {
        auto& group = getGroup();
        group.fireOnChangeOfAllStates(newValue, value());
        group.setValue(newValue);
        group.updateValues();
    }

    void setValue(const Setter& setter) {
        const auto prevValue = value();
        auto& group          = getGroup();
        setter(*group.valuePtr());
        group.updateValues();
        group.fireOnChangeOfAllStates(value(), prevValue);
    }

private:
    State(size_t id, size_t groupId) : IState(id, groupId), m_value(getGroup().valuePtr()) {}

    Internal::StateGroup<T>& getGroup() const {
        return static_cast<Internal::StateGroup<T>&>(getGroupInterface());
    }

    void fireOnChange(const T& current, const T& previous) const {
        if (m_onChange) {
            m_onChange(current, previous);
        }
    }

    void updateValue() {
        m_value = getGroup().valuePtr();
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
