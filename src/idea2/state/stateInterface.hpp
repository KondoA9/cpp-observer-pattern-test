#pragma once

#include <memory>

#include "../stateGroup/stateGroupInterface.hpp"

namespace Internal {
    class IStateGroup;

    class IState {
        friend class IStateGroup;

    private:
        const size_t m_id;

        std::shared_ptr<IStateGroup> m_group;

    public:
        IState() = delete;

        IState(const IState&) = delete;

        IState& operator=(const IState&) = delete;

        virtual ~IState() = default;

        void _destroy() const;

        size_t _stateId() const {
            return m_id;
        }

        size_t _stateGroupId() const {
            return m_group->stateGroupId();
        }

    protected:
        IState(size_t id, size_t groupId) : m_id(id) {
            setGroup(groupId);
        }

        IStateGroup& getGroupInterface() const {
            return *m_group;
        }

    private:
        void setGroup(size_t id);
    };
}
