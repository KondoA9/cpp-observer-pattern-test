#include <iostream>
#include <memory>
#include <string>

class State {
    friend class Statefull;

    std::shared_ptr<int> m_value = nullptr;

public:
    State() = delete;

    State(const int& value) : m_value(std::make_shared<int>(value)) {}

    State(int&& value) : m_value(std::make_shared<int>(value)) {}

    ~State() = default;

    int get() const {
        return *m_value.get();
    }

    void combine(const State& state) {
        m_value = state.m_value;
    }

    operator int() const {
        return get();
    }

private:
    void set(const int& value) {
        if (m_value == nullptr) {
            m_value = std::make_shared<int>(value);
        } else {
            *m_value = value;
        }
    }

    State& operator=(const int& value) {
        set(value);
        return *this;
    }

    State& operator=(int&& value) {
        set(value);
        return *this;
    }

    State& operator=(const State& state) {
        combine(state);
        return *this;
    }

    State& operator=(State&& state) {
        combine(state);
        return *this;
    }
};

class Statefull {
protected:
    void setState(State& state, int value) {
        state.set(value);
    }
};

class CView : public Statefull {
public:
    State value = 0;

    void print() const {
        std::cout << "CView::print(): " << value << std::endl;
    }
};

class CModel : public Statefull {
public:
    State value = 1;

    int getValue() const {
        return value;
    }

    void setValue(int _value) {
        setState(value, _value);
    }
};

int main() {
    CView view;
    CModel model;

    view.print();

    // view._value = model.value; compile error
    view.value.combine(model.value);
    view.print();

    // model.value = 2; compile error
    model.setValue(2);
    view.print();

    model.setValue(3);
    view.print();

    return 0;
}
