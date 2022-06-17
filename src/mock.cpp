#include <functional>
#include <string>

class UIButton {
public:
    bool enabled;
    std::string text;

public:
    void update();
};

class Model {
    bool m_enabled     = false;
    std::string m_text = "";

public:
    bool getEnabled() const {
        return m_enabled;
    }

    std::string getText() const {
        return m_text;
    }
};

int main() {
    UIButton button;
    Model model;

    auto method    = &Model::getEnabled;
    auto& instance = model;

    auto f = std::bind(method, instance);

    f();

    button.enabled = model.getEnabled();
    button.text    = model.getText();

    return 0;
}
