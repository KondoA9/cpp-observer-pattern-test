#pragma once

#include <assert.h>

#include <functional>
#include <thread>

#include "state.hpp"

class Statefull {
    friend class Core;

public:
    virtual ~Statefull() = default;

private:
    static std::thread::id m_MainThreadId;

protected:
    template <typename T>
    const T& _getState(const State<T>& state) const {
        assert(isInMainThread());
        return state.get();
    }

    template <typename T>
    void _setState(State<T>& state, const T& value) {
        assert(isInMainThread());
        state.set(value);
    }

    template <typename T>
    void _effectState(State<T>& state, const std::function<void(T&)>& effect) {
        assert(isInMainThread());
        effect(state.getRef());
    }

    template <typename T>
    void _bindState(State<T>& state, const State<T>& dependent) {
        assert(isInMainThread());
        state.bind(dependent);
    }

private:
    static void Initialize() {
        m_MainThreadId = std::this_thread::get_id();
    }

    bool isInMainThread() const {
        return m_MainThreadId == std::this_thread::get_id();
    }
};

std::thread::id Statefull::m_MainThreadId;
