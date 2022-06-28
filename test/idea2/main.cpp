#include <assert.h>

#include <string>

#include "state/state.hpp"

class InputField {
private:
    // --------------------------------------------
    // States should be private or protected
    // --------------------------------------------

    State<bool> m_isEnabled   = State<bool>(true);
    State<std::string> m_text = State<std::string>("");

public:
    // --------------------------------------------
    // UI should have methods to bind states
    // --------------------------------------------

    void bindText(const State<std::string>& state) {
        m_text.bind(state);
    }

    void bindEnabled(const State<bool>& state) {
        m_isEnabled.bind(state);
    }

    // --------------------------------------------
    // UI should have methods to get states
    // --------------------------------------------

    const State<std::string>& getText() const {
        return m_text;
    }

    const State<bool>& isEnabled() const {
        return m_isEnabled;
    }

    // --------------------------------------------
    // Other methods
    // --------------------------------------------

    void input(const std::string& str) {
        if (m_isEnabled) {
            m_text = m_text.value() + str;
        }
    }
};

class Text {
private:
    State<std::string> m_text = State<std::string>("");

public:
    void bindText(const State<std::string>& state) {
        m_text.bind(state);
    }

    const State<std::string>& getText() const {
        return m_text;
    }
};

class ToggleButton {
private:
    State<bool> m_isToggled = State<bool>(true);

public:
    void bindToggled(const State<bool>& state) {
        m_isToggled.bind(state);
    }

    const State<bool>& isToggled() const {
        return m_isToggled;
    }

    void toggle() {
        m_isToggled = !m_isToggled;
    }
};

class Model {
private:
    // --------------------------------------------
    // States should be private or protected
    // --------------------------------------------

    State<std::string> m_text      = State<std::string>("");
    State<std::string> m_textTwice = State<std::string>("");

public:
    Model() {
        // m_textTwice depends on m_text
        m_text.setOnChange([this](const std::string& current) { m_textTwice = current + current; });
    }

    // --------------------------------------------
    // Model should have methods to get states
    // --------------------------------------------

    const State<std::string>& getText() const {
        return m_text;
    }

    const State<std::string>& getTextTwice() const {
        return m_textTwice;
    }
};

class Page {
private:
    // UI
    ToggleButton ui_toggleButton;
    InputField ui_inputField;
    Text ui_twiceText;

    // Logic
    Model m_model;

public:
    void run() {
        // Binding
        {
            // Enable / Disable input field by the toggle button
            ui_inputField.bindEnabled(ui_toggleButton.isToggled());

            // Input Model::text by the input field
            ui_inputField.bindText(m_model.getText());

            ui_twiceText.bindText(m_model.getTextTwice());
        }

        assert(m_model.getText() == "" && ui_inputField.getText() == "");

        // Disable input field
        {
            ui_toggleButton.toggle();

            ui_inputField.input("dummy");
            assert(m_model.getText() == "" && ui_inputField.getText() == "");
        }

        // Input text
        {
            ui_toggleButton.toggle();

            ui_inputField.input("hello");
            assert(m_model.getText() == "hello" && ui_inputField.getText() == "hello");
            assert(m_model.getTextTwice() == "hellohello" && ui_twiceText.getText() == "hellohello");
        }
    }
};

int main() {
    Page page;

    page.run();

    return 0;
}
