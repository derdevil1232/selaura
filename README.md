<h1 align="center">
Selaura Client
</h1>
<p align="center">
 <a href="https://selauraclient.com/discord" target="_blank">Discord</a>
 •
 <a href="https://selauraclient.com/" target="_blank">Website</a>
 •
 <a href="https://docs.selauraclient.com/" target="_blank">Scripting Documentation</a>
</p>

This repository contains the full source code for Selaura Client. Selaura Client is a mod that aims to improve user experience of Minecraft: Bedrock Edition.

## 🔌 Runtime event example: auto-respawn

Selaura runtime now emits a `PlayerDeathEvent` when the local client transitions onto the death screen.

- The event is posted from the existing `ScreenView::setupAndRender` hook path.
- Emission is one-shot per death-screen entry (it does not fire every frame while dead).
- A sample auto-respawn flow is shown in `test/main.cpp`, which subscribes to `PlayerDeathEvent` and triggers respawn input after a short delay.

Current assumption:
- The sample auto-respawn behavior runs on the game/client hook thread and sends the respawn input only while `death_screen` is still active.

## 🖥️ Compatibility
Selaura Client aims to support:
- Windows 10/11 (64-bit Only)
- Android 9+ (ARM64 Only)
- Any device supporting [mcpelauncher-linux](https://github.com/minecraft-linux/mcpelauncher-manifest)

## ✨ Open Source Technologies Used
- [fmtlib/fmt](https://github.com/fmtlib/fmt)
- [skypjack/entt](https://github.com/skypjack/entt)
- [foonathan/type_safe](https://github.com/foonathan/type_safe)
- [BasedInc/libhat](https://github.com/BasedInc/libhat)
- [Neargye/magic_enum](https://github.com/Neargye/magic_enum)
- [g-truc/glm](https://github.com/g-truc/glm)
- [ocornut/imgui](https://github.com/ocornut/imgui)

## 📈 Star History
[![Star History Chart](https://api.star-history.com/svg?repos=selauraclient/client&type=Date)](https://www.star-history.com/#selauraclient/client&Date)

## 📄 License
Selaura Client currently falls under the [GPL-3.0 License](LICENSE). Feel free to use this code as a fork in your own project. Thank you!
