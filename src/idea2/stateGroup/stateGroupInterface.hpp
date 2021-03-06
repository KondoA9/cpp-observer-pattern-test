#pragma once

#include <memory>
#include <vector>

namespace Internal {
    class IState;

    class IStateGroup {
    private:
        const size_t m_id;

    protected:
        std::vector<std::shared_ptr<IState>> m_states;

    public:
        IStateGroup() = delete;

        IStateGroup(const IStateGroup&) = delete;

        IStateGroup& operator=(const IStateGroup&) = delete;

        explicit IStateGroup(size_t id) : m_id(id) {}

        virtual ~IStateGroup() = default;

        void addState(size_t id);

        void removeState(size_t id);

        size_t stateGroupId() const {
            return m_id;
        }
    };
}
