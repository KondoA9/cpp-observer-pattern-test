#pragma once

#include <functional>
#include <iostream>

#include "stateGroupInterface.hpp"
#include "stateGroupStorage.hpp"
#include "stateInterface.hpp"

template <typename T>
class State final : public IState {
    friend class StateFactory;

private:
    std::function<void()> m_onChange = [this] { std::cout << m_id << ": onChange()" << std::endl; };

public:
    State() = delete;

    State(const State&) = delete;

    State& operator=(const State&) = delete;

    void set(const T&) {
        if (m_groupId == 0) {
            if (m_onChange) {
                m_onChange();
            }
        } else {
            const auto group = StateGroupStorage::Get(m_groupId);
            group->fire();
        }
    }

protected:
    void callOnChange() const override {
        if (m_onChange) {
            m_onChange();
        }
    }

private:
    State(size_t id) : IState(id) {}
};
