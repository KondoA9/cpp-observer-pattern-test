#pragma once

#include <memory>

#include "../stateGroup/stateGroup.hpp"

class StateGroupFactory {
    size_t m_id = 1;

public:
    template <typename T>
    static IStateGroup& Create(const T& value) {
        const auto group = std::shared_ptr<StateGroup<T>>(new StateGroup<T>(Instance().m_id++, value));
        StateGroupStorage::Store(group);
        return *group.get();
    }

private:
    StateGroupFactory() = default;

    static StateGroupFactory& Instance() {
        static StateGroupFactory instance;
        return instance;
    }
};
