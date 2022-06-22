#pragma once

#include <cstddef>

class IState {
    friend class IStateGroup;

private:
    const size_t m_id;
    size_t m_groupId = 0;

public:
    explicit IState(size_t id) : m_id(id) {}

    IState(const IState&) = delete;

    IState& operator=(const IState&) = delete;

    virtual ~IState() = default;

    size_t id() const {
        return m_id;
    }

    size_t groupId() const {
        return m_groupId;
    }

protected:
    void setGroupId(size_t id) {
        m_groupId = id;
    }
};
