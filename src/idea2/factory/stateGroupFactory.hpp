#pragma once

#include <memory>

#include "../stateGroup/stateGroup.hpp"

namespace Internal {
    class StateGroupFactory final {
    private:
        size_t m_id = 1;

    public:
        template <typename T>
        static IStateGroup& Create(const T& value) {
            const auto group = std::shared_ptr<StateGroup<T>>(new StateGroup<T>(Instance().m_id++, value));
            StoreGroup(group);
            return *group.get();
        }

    private:
        StateGroupFactory() = default;

        static StateGroupFactory& Instance();

        static void StoreGroup(const std::shared_ptr<IStateGroup>& group);
    };

}
