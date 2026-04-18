#pragma once
#include <api/mc/client/gui/GuiData.hpp>
#include <hooks/memory.hpp>

#include <string>

class ClientInstance {
public:
    std::byte pad_4[1368];
    std::unique_ptr<GuiData> mGuiData;
public:
    void* $ctor(
        void* a1,
        void* a2,
        void* a3,
        void* a4,
        void* a5,
        void* a6,
        void* a7,
        void* a8,
        void* a9
    );

    std::string getScreenName() {
        // Virtual index for ClientInstance::getScreenName on current supported Bedrock runtime.
        constexpr size_t get_screen_name_index = 271;
        thread_local std::string screenName = "hud_screen";
        screenName.assign("hud_screen");
        return Selaura::CallVirtual<std::string&, std::string&>(this, get_screen_name_index, screenName);
    }

    bool isDeathScreen() {
        // Avoid extra temporary allocations in per-frame death checks.
        constexpr size_t get_screen_name_index = 271;
        thread_local std::string screenName = "hud_screen";
        screenName.assign("hud_screen");
        return Selaura::CallVirtual<std::string&, std::string&>(this, get_screen_name_index, screenName) == "death_screen";
    }
};
