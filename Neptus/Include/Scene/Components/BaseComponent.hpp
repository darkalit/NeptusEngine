#pragma once

#include "Core/API.hpp"

#include <iostream>
#include <string_view>
#include <vector>

namespace Neptus {
namespace Components {
class NP_API BaseComponent {
public:
    BaseComponent() = default;
    BaseComponent(const BaseComponent&) = default;
    virtual ~BaseComponent() = default;

    static std::vector<std::string_view> const& GetRegistry() {
        return s_Registry;
    }
    static std::string_view GetStaticType() {
        return std::string_view{"BaseComponent"};
    }
    virtual std::string_view GetType() const { return GetStaticType(); }

    template <typename T>
    friend bool __AutoRegFunc();

private:
    inline static std::vector<std::string_view> s_Registry = {};
};

template <typename T>
bool __AutoRegFunc() {
    if (T::GetStaticType() != "BaseComponent") {
        BaseComponent::s_Registry.push_back(T::GetStaticType());
    }

    return true;
}

template <typename T>
struct __AutoRegClass {
    inline static const bool __registered = __AutoRegFunc<T>();
};
} // namespace Components
} // namespace Neptus

#define COMPONENT(type)                                                        \
public:                                                                        \
    static std::string_view GetStaticType() {                                  \
        return std::string_view(#type);                                        \
    }                                                                          \
    virtual std::string_view GetType() const override {                        \
        return GetStaticType();                                                \
    }                                                                          \
                                                                               \
private:                                                                       \
    const void* __AutoRegMethod() const {                                      \
        return &__AutoRegClass<type>::__registered;                            \
    }
