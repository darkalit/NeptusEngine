#pragma once
#include <cstdint>
#include <memory>

#define NP_STRINGIFY(x) #x;

#define BIT(x) (1 << (x))

namespace Neptus {
template <typename T>
using UniquePtr = std::unique_ptr<T>;

template <typename T, typename... Args>
UniquePtr<T> CreateUniquePtr(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T, typename U>
SharedPtr<T> StaticPointerCast(const SharedPtr<U>& r) {
    return std::static_pointer_cast<T>(r);
}

template <typename T, typename U>
SharedPtr<T> StaticPointerCast(SharedPtr<U>&& r) {
    return std::static_pointer_cast<T>(r);
}

template <typename T, typename U>
SharedPtr<T> DynamicPointerCast(const SharedPtr<U>& r) {
    return std::dynamic_pointer_cast<T>(r);
}

template <typename T, typename U>
SharedPtr<T> DynamicPointerCast(SharedPtr<U>&& r) {
    return std::dynamic_pointer_cast<T>(r);
}

template <typename T, typename... Args>
SharedPtr<T> CreateSharedPtr(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
using WeakPtr = std::weak_ptr<T>;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

// double and float does not guarantee that it will be 64 bits and 32 bits
// respectably but as the only supported currently platform which is 64 bit used
// as the stub for single style
// TODO: Create a true fixed-size floating point type
using f32 = float;
using f64 = double;
} // namespace Neptus
