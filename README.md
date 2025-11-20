# PXL Monopoly Lite

## Beschrijving
PXL Monopoly Lite is een vereenvoudigde variant van Monopoly met een kleiner speelbord en vakken die gerelateerd zijn aan PXL en vakken zoals **C++, Elektronica, PSOC, Raspberry, Spoel, Weerstand, Diode, Triode, Condensator**. Het doel is een volledig objectgeoriënteerd C++ project te demonstreren met correct gebruik van OOP-principes.

---

## Features
- Vereenvoudigd Monopoly-spel
- Koopbare vakken met huur
- Kleine inkomstenbonus per beurt om het spel eerlijk te houden
- Willekeurig speelbord en dobbelsteen

---

## Gebruikte OOP-technieken

| Concept                     | Waar gebruikt / Uitleg |
|------------------------------|-----------------------|
| **Class**                    | `Player`, `Tile`, `Property`, `Game` |
| **Abstract Base Class**      | `Tile` met pure virtual `onLand()` |
| **Encapsulation**            | Alle members van Player en Property zijn `private` en worden via getters/setters of member functions benaderd |
| **Inheritance**              | `Property` erft van `Tile` |
| **Polymorphism**             | `onLand()` wordt virtueel aangeroepen via `Tile*` pointers |
| **Object Composition**       | `Game` bevat een vector van `Players` en een vector van `Tiles` |
| **Virtual Function**         | `Tile::onLand()` |
| **Constructor Forwarding**   | `Property(name, price) : Tile(name)` |
| **Dynamic Memory Management**| `std::unique_ptr` gebruikt voor `Players` en `Tiles` |
| **Const References**         | `const std::string& getName() const` |
| **Randomness**               | `rand()` voor dobbelsteenrol en kans op kopen |
| **Shuffle Board**            | `std::random_shuffle` voor eerlijkere gameplay |

---

## Project Structuur

