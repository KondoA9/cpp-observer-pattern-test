#include <assert.h>

#include <iostream>

#include "factory/stateFactory.hpp"

class View {
private:
    State<bool>& m_toggleButtonState = StateFactory::Create<bool>(true);
    State<std::string>& m_inputText  = StateFactory::Create<std::string>("placeholder");

public:
    View() {
        m_toggleButtonState.setOnChange(
            [](auto current, auto) { std::cout << "View: toggle is " << (current ? "true" : "false") << std::endl; });
    }

    bool getToggleState() const {
        return m_toggleButtonState.value();
    }

    std::string getInputText() const {
        return m_inputText.value();
    }

    void bindToggleState(const State<bool>& state) {
        m_toggleButtonState.bind(state);
    }

    void bintInputField(const State<std::string>& state) {
        m_inputText.bind(state);
    }

    void toggle() {
        m_toggleButtonState.setValue(!m_toggleButtonState.value());
    }

    void input(const std::string& str) {
        m_inputText.setValue(m_inputText.value() + str);
    }
};

class Model {
private:
    State<bool>& m_Enabled     = StateFactory::Create<bool>(false);
    State<std::string>& m_text = StateFactory::Create<std::string>("");
    State<int>& m_intValue     = StateFactory::Create<int>(0);

public:
    Model() {
        m_Enabled.setOnChange([](auto current, auto) {
            std::cout << "Model: m_enabled is " << (current ? "enabled" : "disabled") << std::endl;
        });
        m_text.setOnChange([](auto current, auto) { std::cout << "Model: text is " << current << std::endl; });
    }

    const State<bool>& stateEnabled() const {
        return m_Enabled;
    }

    const State<std::string>& stateText() const {
        return m_text;
    }

    const State<int>& stateIntValue() const {
        return m_intValue;
    }
};

class ViewController {
private:
    View m_view;
    Model m_model;

    State<int>& m_intValue = StateFactory::Create<int>(1);

public:
    void run() {
        m_view.bindToggleState(m_model.stateEnabled());
        m_view.bintInputField(m_model.stateText());
        assert(m_model.stateEnabled() == false && m_view.getToggleState() == m_model.stateEnabled());

        m_view.toggle();
        assert(m_model.stateEnabled() == true && m_view.getToggleState() == m_model.stateEnabled());

        m_view.toggle();
        assert(m_model.stateEnabled() == false && m_view.getToggleState() == m_model.stateEnabled());

        m_view.input("a");
        assert(m_model.stateText() == "a" && m_view.getInputText() == m_model.stateText());

        m_view.input("bcd");
        assert(m_model.stateText() == "abcd" && m_view.getInputText() == m_model.stateText());

        assert(m_intValue != m_model.stateIntValue());
        assert(m_intValue > m_model.stateIntValue());

        assert(m_model.stateIntValue() != m_intValue);
        assert(m_model.stateIntValue() < m_intValue);

        m_intValue.bind(m_model.stateIntValue());
        assert(m_intValue == m_model.stateIntValue());

        m_intValue.setValue([](int& state) {
            state = 3;
            std::cout << "effect: set value to 3" << std::endl;
        });
        assert(m_intValue == 3 && m_intValue == m_model.stateIntValue());
    }
};

int main() {
    ViewController vc;

    vc.run();

    return 0;
}
