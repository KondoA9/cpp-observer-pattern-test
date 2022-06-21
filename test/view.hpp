#pragma once

#include <iostream>
#include <string>

#include "statefull.hpp"

class View : public Statefull {
    State<bool> m_disabled           = false;
    State<int> m_counter             = 0;
    State<std::vector<int>> m_vector = std::vector<int>();

    std::function<void(int)> m_onIncrement;

public:
    // ---------------------------------------
    // Get state value functions
    // ---------------------------------------

    int getCounter() const {
        return m_counter;
    }

    bool isDisabled() const {
        return m_disabled;
    }

    const std::vector<int>& getVector() const {
        return m_vector.get();
    }

    // ---------------------------------------
    // Bind state functions
    // ---------------------------------------

    void bindDisabled(const State<bool>& state) {
        _bindState(m_disabled, state);
    }

    void bindCounter(const State<int>& state) {
        _bindState(m_counter, state);
    }

    void bindVector(const State<std::vector<int>>& state) {
        _bindState(m_vector, state);
    }

    void fireIncrement() const {
        m_onIncrement(m_counter + 1);
    }

    void onIncrement(const std::function<void(int)>& callback) {
        m_onIncrement = callback;
    }

    void print() const {
        std::cout << "CView::print()" << std::endl;
        std::cout << "  disabled: " << (m_disabled ? "true" : "false") << std::endl;
        std::cout << "  counter: " << m_counter << std::endl;
        {
            std::cout << "  vector: {";
            std::string str = "";
            if (m_vector.get().size() != 0) {
                for (const auto& v : m_vector.get()) {
                    str += std::to_string(v) + ", ";
                }
                str.pop_back();
                str.pop_back();
            }
            std::cout << str << "}" << std::endl;
        }
    }
};
