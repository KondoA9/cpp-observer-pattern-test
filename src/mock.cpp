#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include "observer.hpp"
#include "subject.hpp"

template <typename T>
class Proxy2 {
    std::shared_ptr<T> m_value = nullptr;

    void setValue(const T& value) {
        if (m_value == nullptr) {
            m_value = std::make_shared<T>(value);
        } else {
            m_value = value;
        }
    }

    const T& getValue() const {
        return m_value;
    }

    T getValue() const {
        return m_value;
    }
};

template <typename T>
class Proxy {
    T m_value;

    std::function<T()> m_func;

public:
    void update() {
        if (m_func) {
            m_value = m_func();
        }
    }

    const T& value() const {
        return m_value;
    }

    Proxy<T>& operator=(const std::function<T()>& func) {
        m_func = func;

        // initialize
        m_value = func();

        return *this;
    }

    operator T() const {
        return m_value;
    }
};

// Observer
class UIButton {
public:
    Proxy<bool> enabled;
    Proxy<std::string> text;

    void print() {
        std::cout << "----------------------------------" << std::endl;
        std::cout << "enabled: " << (enabled ? "true" : "false") << std::endl;
        std::cout << "text: " << text.value() << std::endl;
    }

protected:
    void update() {
        enabled.update();
    }
};

// Subject
class Model {
    bool m_enabled     = false;
    std::string m_text = "initial text";

public:
    const bool& getEnabled() const {
        return m_enabled;
    }

    std::string getText() const {
        return m_text;
    }

    std::string getTextTwice() const {
        return m_text + m_text;
    }

    void setEnabled(bool enabled) {
        m_enabled = enabled;
    }

    void setText(const std::string& text) {
        m_text = text;
    }
};

template <typename T>
class Ref {
    friend class Obs;

    T m_value;
    Obs* m_obs = nullptr;

public:
    Ref(const T& value) : m_value(value) {}

    const T& getValue() const {
        return m_value;
    }

    void setValue(const T& value) {
        m_value = value;
        notify();
    }

    T& operator=(const T& value) {
        setValue(value);
        return *this;
    }

protected:
    void notify() {
        m_obs->update();
    }

private:
    void registerObserver(Obs& obs) {
        m_obs = &obs;
    }
};

class Obs {
public:
    virtual void update() = 0;

protected:
    template <typename T>
    void registerSubject(Ref<T>& ref) {
        ref.registerObserver(*this);
    }
};

class Data {
public:
    Ref<int> m_value = 1;
    int getValue() const {
        return m_value.getValue();
    }

    void setValue(int value) {
        m_value.setValue(value);
    }
};

class UI : public Obs {
private:
    int m_value;
    std::function<int()> func;

public:
    void bind(const std::function<int()>& f, Ref<int>& ref) {
        func = f;
        registerSubject<int>(ref);
    }

    void update() override {
        m_value = func();
    }

    void print() const {
        std::cout << m_value << std::endl;
    }
};

int main() {
    Data data;
    UI ui;

    // ui.bind(std::bind(&Data::getValue, data), data.m_value);
    ui.bind([&data] { return data.getValue(); }, data.m_value);

    data.setValue(1);
    ui.print();
    // data.value.notify() {
    // ui.value = data.getValue() = 1
    // ui.valueTwice = data.getValueTwice() = 2
    // }
    data.setValue(2);
    ui.print();

    data.setValue(3);
    ui.print();

    return 0;
}

int main2() {
    UIButton button;
    Model model;

    // bind to function
    {
        // button.enabled.bind([&model] { return model.getEnabled(); });

        button.enabled = std::bind(&Model::getEnabled, model);
        button.text    = std::bind(&Model::getText, model);

        // false "initial text"
        button.print();

        // true "1"
        model.setEnabled(true);
        model.setText("1");
        button.print();

        // false "hoge"
        model.setEnabled(false);
        model.setText("hoge");
        button.print();
    }

    // bind to variable
    /*{
        bool enabled     = true;
        std::string text = "variable";
        button.enabled   = enabled;
        button.text      = text;
    }*/

    // bind to constant value
    /*{
        button.enabled = false;
        button.text    = "constant text";
    }*/

    // Proxy<T> = bool -> crash
    // button.enabled = false;
    // std::function<void()> func = false;

    return 0;
}
