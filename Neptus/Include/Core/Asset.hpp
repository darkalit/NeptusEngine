#pragma once

#include "Core/API.hpp"
#include "Core/Base.hpp"
#include "Core/UUID.hpp"

#include <string>

#define ASSET(type)                                                            \
public:                                                                        \
    static AssetType GetStaticAssetType() {                                    \
        return AssetType::type;                                                \
    }                                                                          \
    virtual AssetType GetAssetType() const override {                          \
        return GetStaticAssetType();                                           \
    }                                                                          \
                                                                               \
private:

namespace Neptus {
enum NP_API AssetFlag : u16 {
    NONE = 0,
    MISSING = BIT(0),
    INVALID = BIT(1),
    UNLOADED = BIT(2),
    LOADED = BIT(3),
};

enum class NP_API AssetType : u16 {
    Unknown,
    Shader,
    Texture,
    Model,
    Script,
    System,
    Scene,
};

class NP_API Asset {
public:
    Asset() = default;
    Asset(const Asset&) = delete;
    virtual ~Asset() = default;

    Asset& operator=(const Asset&) = delete;
    virtual bool operator==(const Asset& other) { return m_Id == other.m_Id; }
    virtual bool operator!=(const Asset& other) { return !(*this == other); }

    UUID const& GetID() const { return m_Id; }

    static AssetType GetStaticAssetType() { return AssetType::Unknown; }
    virtual AssetType GetAssetType() const { return AssetType::Unknown; }
    std::string GetAssetPath() const { return m_Filepath; }

    virtual bool IsValid() const {
        return (m_Status & (static_cast<u16>(AssetFlag::INVALID) |
                            static_cast<u16>(AssetFlag::MISSING))) == 0;
    }

protected:
    std::string m_Filepath = {};
    UUID m_Id = {};
    u16 m_Status = AssetFlag::NONE;
};
} // namespace Neptus
