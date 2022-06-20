#include <functional>
#include <iostream>
#include <memory>
#include <string>

template <typename T>
class State {
    friend class Statefull;

    std::shared_ptr<T> m_value = nullptr;

public:
    State() = delete;

    State(const T& value) : m_value(std::make_shared<T>(value)) {}

    State(T&& value) : m_value(std::make_shared<T>(value)) {}

    ~State() = default;

    const T& get() const {
        return *m_value.get();
    }

    T& get() {
        return *m_value.get();
    }

    void depends(const State& state) {
        m_value = state.m_value;
    }

    void reset() const {
        m_value.reset();
    }

    operator T() const {
        return get();
    }

private:
    void set(const T& value) {
        if (m_value == nullptr) {
            m_value = std::make_shared<T>(value);
        } else {
            *m_value = value;
        }
    }

    State& operator=(const T& value) {
        set(value);
        return *this;
    }

    State& operator=(T&& value) {
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
    template <typename T>
    void setState(State<T>& state, const T& value) {
        // assert(called_in_main_thread);
        // must run in main thread
        state.set(value);
    }

    template <typename T>
    const T& getState(State<T>& state) const {
        // assert(called_in_main_thread);
        // must run in main thread
        return state.get();
    }

    template <typename T>
    T& getState(State<T>& state) {
        // assert(called_in_main_thread);
        // must run in main thread
        return state.get();
    }
};

class CView : public Statefull {
public:
    State<bool> disabled           = false;
    State<int> counter             = 0;
    State<std::vector<int>> vector = std::vector<int>();

    int getCounter() const {
        return counter;
    }

    /*void setValue(int _value) {
        setState(value, _value);
    }*/

    void incremented(const std::function<void(int)>& callback) {
        callback(counter + 1);
    }

    void print() const {
        std::cout << "CView::print()" << std::endl;
        std::cout << "  disabled: " << (disabled ? "true" : "false") << std::endl;
        std::cout << "  counter: " << counter << std::endl;
        {
            std::cout << "  vector: {";
            std::string str = "";
            if (vector.get().size() != 0) {
                for (const auto& v : vector.get()) {
                    str += std::to_string(v) + ", ";
                }
                str.pop_back();
                str.pop_back();
            }
            std::cout << str << "}" << std::endl;
        }
    }
};

class CModel : public Statefull {
public:
    State<int> counter             = 1;
    State<std::vector<int>> vector = std::vector<int>{0, 1, 2};

    int getCounter() const {
        return counter;
    }

    void setCounter(int _counter) {
        setState(counter, _counter);
    }

    void setVectorElement(size_t index, int value) {
        getState(vector)[index] = value;
        setState(vector, vector.get());
    }

    void pushVector(int value) {
        getState(vector).push_back(value);
        setState(vector, vector.get());
    }

    void print() const {
        std::cout << "CModel::print()" << std::endl;
        std::cout << "  counter: " << counter << std::endl;
        {
            std::cout << "  vector: {";
            std::string str = "";
            if (vector.get().size() != 0) {
                for (const auto& v : vector.get()) {
                    str += std::to_string(v) + ", ";
                }
                str.pop_back();
                str.pop_back();
            }
            std::cout << str << "}" << std::endl;
        }
    }
};

class CPage : public Statefull {
    CView view;
    CModel model;

    State<bool> viewDisabled = false;

public:
    void run() {
        // view.value = model.value; compile error
        // model.value = 2; compile error

        // Combine View and Model
        {
            view.counter.depends(model.counter);
            print();
        }

        // Set value from Model
        {
            model.setCounter(2);
            print();

            model.setCounter(3);
            print();
        }

        // Fire event
        {
            view.incremented([this](int i) { model.setCounter(i); });
            print();
        }

        // Combine to page state
        {
            view.disabled.depends(viewDisabled);
            print();

            setState(viewDisabled, true);
            print();
        }

        // vector
        {
            view.vector.depends(model.vector);
            print();

            model.setVectorElement(0, 100);
            print();

            model.pushVector(200);
            print();
        }
    }

private:
    void print() {
        std::cout << "---------------------------" << std::endl;
        view.print();
        model.print();
    }
};

int main() {
    CPage page;

    page.run();

    return 0;
}
