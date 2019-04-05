Usage (very simple) :

```cpp
// Instance
EventReactor reactor;

// In a callback you can use the event object.
reactor.registerCallback<EventType>([](const EventType& event) {
    // use it here
    doSomething(event.data);
    event.doSomething();
});

// You can make callbacks without parameters
reactor.registerCallback<EventType>([] {
    // do something
});

// Those two callbacks will be fired when the reactor receives this event:
reactor.processEvent(EventType{});

// That's all folks
```
