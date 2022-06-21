#pragma once

#include "stateInterface.hpp"

class IStateGroup {
protected:
    /*const*/ size_t m_id;

public:
    virtual ~IStateGroup() = default;

    size_t id() const {
        return m_id;
    }

    virtual void fire() const = 0;

protected:
    void fireOnChange(const IState& state) const {
        state.callOnChange();
    }
};
