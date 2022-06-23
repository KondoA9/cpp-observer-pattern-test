#pragma once

#include <cstddef>
#include <memory>

class IState {
    friend class IStateGroup;

private:
    const size_t m_id;
    size_t m_groupId = 0;

public:
    IState() = delete;

    IState(const IState&) = delete;

    IState& operator=(const IState&) = delete;

    virtual ~IState() = default;

    size_t _stateId() const {
        return m_id;
    }

    size_t _stateGroupId() const {
        return m_groupId;
    }

protected:
    explicit IState(size_t id) : m_id(id) {}

    std::shared_ptr<IStateGroup> getGroup() const;

private:
    void setGroupId(size_t id) {
        m_groupId = id;
    }
};
