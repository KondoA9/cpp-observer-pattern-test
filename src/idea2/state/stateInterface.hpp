#pragma once

#include <memory>

namespace Internal {
    class IStateGroup;

    class IState {
        friend class IStateGroup;

    private:
        const size_t m_id;
        size_t m_groupId;

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
        IState(size_t id, size_t groupId) : m_id(id), m_groupId(groupId) {}

        IStateGroup& getGroupInterface() const;

    private:
        void setGroupId(size_t id) {
            m_groupId = id;
        }
    };

}
