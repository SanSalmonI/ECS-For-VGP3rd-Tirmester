# ECS Battle Simulator

A console C++ program demonstrating a basic Entity-Component-System (ECS) pattern through a turn-based, type-matchup card battle game (structurally similar to Pokémon type effectiveness). All logic lives in a single file, `ECS.cpp`.

## What it does

- **Entities** are physical objects (e.g. "Diamond," "Car," "Taser") with HP and a list of **Components**, where each component is one of 8 elemental types: Rock, Metal, Fire, Electric, Organic, Plastic, Conceptual, Light.
- Type matchups follow a rock-paper-scissors-style chart: each type has strengths (1.5x damage) and weaknesses (0.5x damage) against specific other types, checked in `System::calculateDamage`.
- **Actors** ("Kaleb," "Salmon," "Ibi," and the player) hold an inventory of entities/items.
- At startup, three enemy Actors are auto-assigned a random subset of the pre-built entity pool (`assignEnemyItems`).
- The player enters a name, chooses how many items (1–5) to bring into battle, names each item, and each gets a random HP (5–9) and a random elemental component.
- **Battle**: the player picks a card from their inventory each turn to fight a random card from Enemy 1's inventory. `System::update` runs a full HP-depletion loop between the two chosen items, applying type-based damage until one (or both) reach 0 HP. The loser's item is removed from their inventory (or both, on a tie).
- The battle continues until either the player's or Enemy 1's inventory is empty, then prints a win/loss message.

## Known quirks / incomplete parts (per in-code comments)

- Only the battle against **Enemy 1** is implemented — Enemy 2 and Enemy 3 are assigned items at startup but there's no battle loop for them yet (marked "unused feature" in `main`).
- No bounds-checking on the player's card choice input — selecting a number outside the inventory's range will error.
- There's a noted bug where items don't always get destroyed/removed correctly and can stay at negative HP.
- Uses `conio.h` and `system("CLS")`, so it's Windows-only as written.

## Project Structure

- `ECS.cpp` — all source code (Component, Entity, EntityManager, Actor, System classes, and `main`).
- `ECS_VGP131.vcxproj` and `Project21.vcxproj` — two separate Visual Studio project files that both build `ECS.cpp` (the repo has a top-level `Project21.sln`; the duplication looks like a leftover from renaming/re-creating the project — worth cleaning up).
- `x64/Debug/`, `Project21/x64/`, `ECS_VGP131/x64/`, `.vs/` — build artifacts and IDE cache checked into the repo; these aren't source and could be removed / gitignored.

## Running

Open `Project21.sln` in Visual Studio (Windows) and build/run.
