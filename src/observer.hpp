#pragma once

class IObserver {
    friend class ISubject;

public:
    virtual ~IObserver() {}

    virtual void update(ISubject* subject) = 0;
};
