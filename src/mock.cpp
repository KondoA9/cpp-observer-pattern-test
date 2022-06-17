#include <functional>
#include <iostream>
#include <string>

#include "observer.hpp"
#include "subject.hpp"

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
    bool getEnabled() const {
        return m_enabled;
    }

    std::string getText() const {
        return m_text;
    }

    void setEnabled(bool enabled) {
        m_enabled = enabled;
    }

    void setText(const std::string& text) {
        m_text = text;
    }
};

int main() {
    UIButton button;
    Model model;

    // bind to function
    {
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
