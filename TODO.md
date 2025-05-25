# Hohe Prio: Simulationsdesign
## Konkrete nächste Schritte
- Schreibe Unit-Tests für World::create_visual_impression() und für die Projection-Erzeugung
- Methoden im Organismus_Manager schreiben, die die Rectangles auf die Retina abbilden
- virtuelle Retina mit Tiefeninformation im Organismus implementieren
- Logik im Organismus einbauen, die eine einfache Mustererkennung macht
- virtuelle Retina in die Visualisierung (Hauptfenster) einbauen

# Basis-Fähigkeiten für grundlegende Aufgaben implementieren
- Steuerung der Bewegung basierend auf Retina - der Organismus läuft auf einen sichtbaren Gegenstand zu

# Mittlere Prio: Code-Optimierungen
- Visualisierung und Simulation zeitmäßig entkoppeln: Welt-Zustand nur alle x Ticks zeichnen lassen

# Niedrige Prio: C++-Code
- nutze % Operator für Ganzzahl-Division mit Rest
- nutze die SDL-Logging-Bibliothek
- benutze static_cast<...>(), um die Compiler-Warnungen bezüglich numerischer Umwandlungen loszuwerden
- nutze immer value initialization {} anstelle von default. Beispiel: int x; vs. int x{};
- schau mal, wo ich unique_ptr() nutzen kann
- ersetze std::vector mit std::array wo möglich aus Performance-Gründen, z.B. bei C-style sensorarray mit `std::array<sensor, 8>`
- verschiebe die Kollisionserkennung von world.h nach organism_manager.h
- prüfe und implementiere die Regel von 3 oder 5 (https://en.cppreference.com/w/cpp/language/rule_of_three)

# Später
- Analysiere, wo constexpr möglich sind und baue constexpr ein für compile-time Werte und reine Funktionen, v.a. in der appconfig und constants Klasse



