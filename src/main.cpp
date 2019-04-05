#include <iostream>
#include <any>

#include "EventReactor.hpp"

struct Event1 {
    const int x, y;
    constexpr Event1(int xx, int yy) noexcept
        : x{xx}, y{yy}
    {}
};

struct Event2 {};

struct Object {
    void sayHi() const { std::cout << "object says hello.\n"; }
    struct Event {};
};


int main()
{
    EventReactor reactor;
    Object obj;

    reactor.registerCallback<Event1>([](Event1 ev) {
        std::cout << "Event1: " << ev.x << ", " << ev.y << "\n";
    });

    reactor.registerCallback<Event1>([](Event1 ev) {
        std::cout << "Event1: " << ev.x << ", " << ev.y << "\n";
    });

    reactor.registerCallback<Event2>([]() {
        std::cout << "Event2 without data.\n";
    });

    reactor.registerCallback<const Object&>([](const Object& o) {
        o.sayHi();
    });

    Event1 ev1{0,1};
    Event2 ev2;

    reactor.processEvent(std::move(ev1));
    reactor.processEvent(ev2);
    reactor.processEvent(ev1);
    reactor.processEvent(Event1{3,3});
    reactor.processEvent(Event2{});
    reactor.processEvent(obj);
}
