# Cidia Rust Cheat

**Cidia Rust Cheat** is a powerful external cheat for the game *Rust*, featuring aimbot, ESP, and a wide range of game-breaking enhancements. Built for stealth and performance with driver-level bypass and ImGui overlay support.

---

## 🚀 Features

### 🎯 Aimbot
- Smooth aim assist
- In-FOV targeting
- Distance-based locking
- FastBow, Instant Eoka, LongHand support
- Bone targeting with hitbox override

### 🧠 ESP (Visuals)
- Player and NPC ESP
- Health and active item display
- Sleeper and dead player detection
- Trace lines to targets
- Raid object/structure ESP

### 🔫 Weapon Mods
- No recoil (pitch, yaw, spread control)
- No sway
- Instant shooting weapons (bows, Eoka)
- Bullet drop and drag control
- Custom projectile velocity & gravity
- Automatic fire toggle
- Reload time tweak
- Bullet thickness modification

### 🌍 World Hacks
- World-to-screen calculations
- Set admin time and ambient lighting
- Day/night light intensity override
- Underwater vision toggle
- Layer/culling bypass

### 🧠 Player Logic
- Detect NPCs, dead, and sleeping players
- Modify movement states (jump, land, fall)
- Ground angle override
- View manipulation and eye control
- Belt container management

### 🔐 Bypass & Anti-Cheat
- Kernel driver initialization and bypass
- Spoofed WinAPI functions
- Console window hiding
- HWID and return spoofing
- Hidden file/module loading
- Token-based auth system
- Hidden folder creation

### 🖥️ Overlay & UI
- ImGui-based cheat menu
- Toggleable interface
- Custom color editor
- Hotkeys and menu configuration

### 🌐 Misc
- URL reading and JSON config support
- Multi-threaded system (render, raid, trace)
- Internal debug log system
- Auth system with encrypted session

---

## 📁 Project Structure

```
Cidia Rust Cheat/
│
├── Aimbot.cpp/.h
├── BasePlayer.cpp/.h
├── BaseProjectile.cpp/.h
├── CheatFunction.cpp/.h
├── overlay.cpp/.h
├── auth.h / encryption
├── kernel/driver loader
├── ImGui / JSON / Filesystem includes
└── Cidia Rust Cheat.cpp (main)
```

---

## 📦 Requirements

- Visual Studio 2022+
- Windows 10/11 (Admin rights required)
- Git + GitHub
- Driver loader for kernel access

---

## ⚠️ Disclaimer

> **For educational and reverse engineering purposes only.**  
> Using this on live servers may violate EULA/TOS and result in bans.  
> Use at your own risk.

---

## 🔗 Credits

- ImGui – for the in-game UI
- nlohmann/json – config support
- Custom kernel driver and bypass logic by MasterDream

