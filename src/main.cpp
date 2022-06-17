#include <iostream>
#include <string>

#include "observer.hpp"
#include "subject.hpp"

class Model : public ISubject {
    std::string m_text = "";

public:
    void setText(const std::string& str) {
        m_text = str;
        notify();
    }

    std::string getText() const {
        return m_text;
    }
};

class UI : public IObserver {
public:
    void update(ISubject* subject) override {
        std::cout << reinterpret_cast<Model*>(subject)->getText() << std::endl;
    }
};

int main() {
    Model model;
    UI ui;

    model.addObserver(&ui);

    model.setText("1");
    model.setText("2");
    model.setText("3");

    return 0;
}
