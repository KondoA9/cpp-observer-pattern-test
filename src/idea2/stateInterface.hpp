#pragma once

class IState {
    friend class IStateGroup;

protected:
    const size_t m_id;
    size_t m_groupId = 0;

public:
    IState(size_t id) : m_id(id) {}

    virtual ~IState() = default;

    size_t id() const {
        return m_id;
    }

    size_t groupId() const {
        return m_groupId;
    }

protected:
    virtual void callOnChange() const = 0;
};
