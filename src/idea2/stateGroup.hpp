#pragma once

#include <memory>
#include <vector>

#include "state.hpp"
#include "stateGroupInterface.hpp"

template <typename T>
class StateGroup final : public IStateGroup {
    std::vector<State<T>> m_states;
    std::shared_ptr<T> m_value;

public:
    void fire() const override {
        for (const auto& state : m_states) {
            fireOnChange(state);
        }
    }
};
