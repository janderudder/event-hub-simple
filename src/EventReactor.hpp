#pragma once
#include <any>
#include <functional>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>


class EventReactor
{
    using Callback = std::function<void(std::any)>;

    std::unordered_multimap<std::type_index, Callback> mTypeCallbackMap;


public:
    template <typename Event>
    void registerCallback(std::function<void(Event)> fun)
    {
        mTypeCallbackMap.emplace(std::type_index(typeid(Event)), [fun](std::any event) {
            std::invoke(fun, std::any_cast<Event>(event));
        });
    }

    template <typename Event>
    void registerCallback(std::function<void()> fun)
    {
        mTypeCallbackMap.emplace(std::type_index(typeid(Event)), [fun](std::any) {
            std::invoke(fun);
        });
    }

    template <typename Event>
    void processEvent(Event&& event)
    {
        const auto range = mTypeCallbackMap.equal_range(std::type_index(typeid(Event)));
        for (auto it = range.first; it != range.second; it=std::next(it)) {
            std::invoke(it->second, std::forward<Event>(event));
        }
    }
};
