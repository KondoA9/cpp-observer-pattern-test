#include <assert.h>

#include "statewrap/statewrap.hpp"

class InputField {
private:
    // --------------------------------------------
    // States should be private or protected
    // --------------------------------------------

    StateWrap<bool> m_isEnabled   = StateWrap<bool>(true);
    StateWrap<std::string> m_text = StateWrap<std::string>("");

public:
    // --------------------------------------------
    // UI should have methods to bind states
    // --------------------------------------------

    void bindText(const StateWrap<std::string>& state) {
        m_text.bind(state);
    }

    void bindEnabled(const StateWrap<bool>& state) {
        m_isEnabled.bind(state);
    }

    // --------------------------------------------
    // UI should have methods to get states
    // --------------------------------------------

    const StateWrap<std::string>& getText() const {
        return m_text;
    }

    const StateWrap<bool>& isEnabled() const {
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
    StateWrap<std::string> m_text = StateWrap<std::string>("");

public:
    void bindText(const StateWrap<std::string>& state) {
        m_text.bind(state);
    }

    const StateWrap<std::string>& getText() const {
        return m_text;
    }
};

class ToggleButton {
private:
    StateWrap<bool>& m_isToggled = StateWrap<bool>(true);

public:
    void bindToggled(const StateWrap<bool>& state) {
        m_isToggled.bind(state);
    }

    const StateWrap<bool>& isToggled() const {
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

    StateWrap<std::string> m_text      = StateWrap<std::string>("");
    StateWrap<std::string> m_textTwice = StateWrap<std::string>("");

public:
    Model() {
        // m_textTwice depends on m_text
        m_text.setOnChange([this](const std::string& current) { m_textTwice = current + current; });
    }

    // --------------------------------------------
    // Model should have methods to get states
    // --------------------------------------------

    const StateWrap<std::string>& getText() const {
        return m_text;
    }

    const StateWrap<std::string>& getTextTwice() const {
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
