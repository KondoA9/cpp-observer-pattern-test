#pragma once

#include <iostream>
#include <string>

#include "statefull.hpp"

class Model : public Statefull {
    State<int> m_counter             = 1;
    State<std::vector<int>> m_vector = std::vector<int>();

public:
    // ---------------------------------------
    // Get state functions
    // ---------------------------------------

    const State<int>& stateCounter() const {
        return m_counter;
    }

    const State<std::vector<int>>& stateVector() const {
        return m_vector;
    }

    int getCounter() const {
        return m_counter;
    }

    const std::vector<int>& getVector() const {
        return m_vector.get();
    }

    // ---------------------------------------
    // Set state functions
    // ---------------------------------------

    void setCounter(int counter) {
        _setState(m_counter, counter);
        // This is same as following code
        // _effectState<int>(counter, [_counter](int& i) { i = _counter; });
    }

    void setVector(const std::vector<int>& vector) {
        _setState(m_vector, vector);
    }

    void setVectorElement(size_t index, int value) {
        _effectState<std::vector<int>>(m_vector, [index, value](std::vector<int>& v) { v[index] = value; });
    }

    void pushVector(int value) {
        _effectState<std::vector<int>>(m_vector, [value](std::vector<int>& v) { v.push_back(value); });
    }

    void print() const {
        std::cout << "CModel::print()" << std::endl;
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
