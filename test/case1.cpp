#include "core.hpp"
#include "model.hpp"
#include "view.hpp"

class Page : public Statefull {
    View view;
    Model model;

    State<bool> viewDisabled = false;

public:
    void run() {
        // Bind view::counter to model::counter
        {
            view.bindCounter(model.stateCounter());

            model.setCounter(0);
            assert(view.getCounter() == 0 && model.getCounter() == 0);

            model.setCounter(1);
            assert(view.getCounter() == 1 && model.getCounter() == 1);

            // Event
            view.onIncrement([this](int newValue) { model.setCounter(newValue); });
            view.fireIncrement();
            assert(view.getCounter() == 2 && model.getCounter() == 2);

            // Unbind
            view.bindCounter(0);
            assert(view.getCounter() == 0 && model.getCounter() == 2);
        }

        // Bind View::disabled to Page::viewDisabled
        {
            view.bindDisabled(viewDisabled);

            _setState(viewDisabled, true);
            assert(view.isDisabled() && viewDisabled);

            _setState(viewDisabled, false);
            assert(!view.isDisabled() && !viewDisabled);

            // Unbind
            view.bindDisabled(true);
            assert(view.isDisabled() && !viewDisabled);
        }

        // vector
        {
            view.bindVector(model.stateVector());

            model.setVector({0, 1, 2});
            assert(view.getVector() == model.getVector());
            assert(view.getVector() == (std::vector<int>{0, 1, 2}));

            model.setVectorElement(0, 100);
            assert(view.getVector()[0] == 100 && model.getVector()[0] == 100);

            model.pushVector(200);
            assert(view.getVector().size() == 4 && model.getVector().size() == 4);
            assert(view.getVector()[3] == 200 && model.getVector()[3] == 200);
        }
    }
};

int main() {
    Core::Initialize();

    Page page;

    page.run();

    return 0;
}
