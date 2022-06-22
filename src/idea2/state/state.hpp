#pragma once

#include <functional>

#include "../stateGroup/stateGroup.hpp"
#include "../storage/stateGroupStorage.hpp"
#include "stateInterface.hpp"

template <typename T>
class StateGroup;

template <typename T>
class State final : public IState {
    using OnChangeFuncType = std::function<void(const T& current, const T& previous)>;

    friend class StateFactory;

private:
    OnChangeFuncType m_onChange;

public:
    State() = delete;

    const T& value() const {
        const auto group = StateGroupStorage::Get(groupId());
        return std::dynamic_pointer_cast<StateGroup<T>>(group)->value();
    }

    void onChange(const OnChangeFuncType& func) {
        m_onChange = func;
    }

    void setValue(const T& newValue) {
        const auto group = std::dynamic_pointer_cast<StateGroup<T>>(StateGroupStorage::Get(groupId()));
        group->fireOnChange(newValue, value());
        group->setValue(newValue);
    }

    void bindTo(const State& state) {
        // Bind if not in the same group
        if (groupId() != state.groupId()) {
            const auto group = StateGroupStorage::Get(state.groupId());
            setGroupId(group->id());
            group->add(id());
        }
    }

    void fireOnChange(const T& current, const T& previous) {
        if (m_onChange) {
            m_onChange(current, previous);
        }
    }

private:
    explicit State(size_t id) : IState(id) {}
};
