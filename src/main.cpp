#include <iostream>
#include <string>
#include <vector>

class Observer {
    friend class Subject;

public:
    virtual ~Observer() {}

    virtual void update(Subject* subject) = 0;
};

class Subject {
    std::vector<Observer*> m_observers;

public:
    virtual ~Subject() {}

    void addObserver(Observer* observer) {
        m_observers.emplace_back(observer);
    }

protected:
    void notify() {
        for (auto& observer : m_observers) {
            observer->update(this);
        }
    }
};

class Model : public Subject {
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

class UI : public Observer {
public:
    void update(Subject* subject) override {
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
