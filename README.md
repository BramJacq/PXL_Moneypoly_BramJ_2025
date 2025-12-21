# PXL Moneypoly (Simplefied Monopoly)

## Beschrijving
PXL Monopoly Lite is een vereenvoudigde Monopoly-achtige game met een grafische interface in **Qt**.  
Spelers bewegen over een vast speelbord met vakken zoals **C++ Debugger, Resistor, Capacitor, Transistor, Compiler, ALU, Microcontroller**, enz.  
Het project demonstreert een volledig objectgeoriënteerd C++/Qt-project met correcte toepassing van OOP-principes, moderne C++ technieken en een werkende GUI.

---

## Features
- Grafische Qt GUI met speelbord
- Menselijke speler + bots
- Dobbelsteenmechanisme
- Koopbare eigendommen met huur
- Automatische beurten voor bots
- Spel eindigt wanneer er nog één speler over is of via “End Game”
- Live weergave van spelers en saldo

---

## OOP-concepten en C++ technieken

| Concept | Waar gebruikt / Waarom nuttig |
|--------|-------------------------------|
| **Classes** | `Player`, `Tile`, `Property`, `ConcreteTile`, `Game`, `BoardWidget` zorgen voor duidelijke scheiding van verantwoordelijkheden |
| **Abstract Base Class** | `Tile` met pure virtual `onLand()` maakt polymorfisme mogelijk en dwingt correcte implementatie in afgeleiden |
| **Encapsulation** | Alle member-variabelen zijn `private` en toegankelijk via getters/setters of member functions, wat data-integriteit garandeert |
| **Inheritance** | `Property` en `ConcreteTile` erven van `Tile` om code herbruikbaar en uitbreidbaar te maken |
| **Polymorphism** | Virtuele functie `onLand()` wordt via `Tile*` of `unique_ptr<Tile>` aangeroepen, wat dynamisch gedrag mogelijk maakt |
| **Object Composition** | `Game` bevat vectors van `Player` en `Tile`, wat de structuur modulair en overzichtelijk houdt |
| **Constructors** | Minstens twee default, parameterized en copy constructors aanwezig voor flexibele objectinitialisatie |
| **Destructors** | Virtuele destructors in basisklassen voor veilig geheugenbeheer |
| **Member Initialization Lists** | Alle constructors gebruiken initialisatie van members via colon-syntax |
| **Constructor Forwarding** | `Property(name, price) : Tile(name)` |
| **Const Correctness** | Const getters en const reference parameters waar nodig |
| **Inline Functions** | Kleine getters/setters in headers voor efficiëntie |
| **Templates** | `utils::appendLineToFile<T>()` voor herbruikbare file I/O |
| **Friend Functions** | `operator<<` in `Player` voor makkelijk debuggen en logging |
| **Namespaces** | Alles in `pxl` namespace om naamconflicten te voorkomen |
| **Qt Signals/Slots** | Communicatie tussen `Game` en `BoardWidget` maakt GUI responsief en modulair |
| **Containers** | `std::vector` gebruikt voor spelers en tiles, dynamische uitbreiding van game-objecten |
| **Strings** | `std::string` en `QString` voor tekstuele data |
| **Randomness** | `rand()` voor dobbelsteenrol en kans op aankoop van vakken |
| **Exception Handling & File I/O** | Template helper werpt exceptions bij foutief openen van bestanden |

---

## Build & Run

### Vereisten
- C++17 compatibele compiler
- Qt 5 of Qt 6
- CMake of Qt Creator

### Stappen (Qt Creator)
1. Open het project in Qt Creator.
2. Configureer met een geschikte kit.
3. Build het project.
4. Run de applicatie.

De applicatie start met een speelbord en één menselijke speler plus meerdere bots.  

---

## Waarom dit project nuttig is
- Demonstreert correcte toepassing van **OOP-principes** zoals inheritance, polymorphism en encapsulation  
- Modulaire en uitbreidbare **class structuur**  
- Correct gebruik van **moderne C++ technieken** (smart pointers, const correctness, inline, templates, friend functions)  
- Werkende en onderhoudbare **Qt GUI**  
- Duidelijke scheiding tussen **logica (Game) en interface (BoardWidget)**  
- Volledig compileerbaar en stabiel project


