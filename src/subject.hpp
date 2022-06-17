#pragma once

#include <vector>

#include "observer.hpp"

class ISubject {
    std::vector<IObserver*> m_observers;

public:
    virtual ~ISubject() {}

    void addObserver(IObserver* observer) {
        m_observers.emplace_back(observer);
    }

protected:
    void notify() {
        for (auto& observer : m_observers) {
            observer->update(this);
        }
    }
};
