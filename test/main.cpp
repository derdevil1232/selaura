#pragma once
#include <Windows.h>
#include <print>
#include <chrono>

#include <api/imports.hpp>
#include <../src/runtime.hpp>

#include <event/events.hpp>
#include <api/helpers/mcuirc.hpp>
#include <api/mc/client/renderer/MeshHelpers.hpp>

#include "selaura_imgui.hpp"

BOOL APIENTRY DllMain(HINSTANCE, DWORD, LPVOID) {
    return TRUE;
}

namespace {
    constexpr auto kAutoRespawnDelay = std::chrono::milliseconds(500);

    // These callbacks run on the game hook thread in this runtime path.
    bool gRespawnPending = false;
    std::chrono::steady_clock::time_point gRespawnAt = {};
    Selaura::Runtime* gRuntime = nullptr;

    void TriggerRespawnInput() {
        INPUT inputs[2]{};

        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = VK_RETURN;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = VK_RETURN;
        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

        const UINT sent = SendInput(2, inputs, sizeof(INPUT));
        if (sent != 2) {
            std::println("[Selaura AutoRespawn] Failed to send respawn input.");
        }
    }
}

void OnPlayerDeath(Selaura::PlayerDeathEvent&) {
    gRespawnPending = true;
    gRespawnAt = std::chrono::steady_clock::now() + kAutoRespawnDelay;
}

void AfterUI(Selaura::SetupAndRenderEvent<Selaura::EventPhase::Post>& ev) {
    if (gRespawnPending && std::chrono::steady_clock::now() >= gRespawnAt) {
        if (gRuntime != nullptr &&
            gRuntime->mClientCtx->mClientInstance != nullptr &&
            gRuntime->mClientCtx->mClientInstance->isDeathScreen()) {
            TriggerRespawnInput();
        }

        gRespawnPending = false;
    }

    static bool state = false;
    if (!state) {
        SelauraImGui::Init(ev.mCtx, ev.mCtx->mScreenContext);
        state = true;
    }

    SelauraImGui::NewFrame();
    ImGui::NewFrame();

    ImGui::GetForegroundDrawList()->AddRectFilled({0, 0}, {100, 100}, ImColor(255, 0, 0));

    ImGui::EndFrame();
    ImGui::Render();
    SelauraImGui::RenderDrawData(ImGui::GetDrawData());
}

SELAURA_API void SelauraPluginInit(Selaura::Runtime* pRuntime) {
    gRuntime = pRuntime;
    pRuntime->mEventManager->subscribe(&OnPlayerDeath);
    pRuntime->mEventManager->subscribe(&AfterUI);
}
