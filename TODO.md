# Hohe Prio: Simulationsdesign
## Konkrete nächste Schritte
- virtuelle Retina mit Tiefeninformation im Organismus implementieren
- virtuelle Retina in die Visualisierung einbauen

# Basis-Fähigkeiten für grundlegende Aufgaben implementieren
- Steuerung der Bewegung basierend auf Retina - der Organismus läuft auf einen sichtbaren Gegenstand zu

# Mittlere Prio: Code-Optimierungen
- Visualisierung und Simulation zeitmäßig entkoppeln: Welt-Zustand nur alle x Ticks zeichnen lassen

# Niedrige Prio: C++-Code
- baue constexpr ein für compile-time Werte, v.a. in der appconfig und constants Klasse
- Do not pass std::string by value, as it makes an expensive copy. Tip: In most cases, use a std::string_view parameter instead 
- Nutze % Operator für Ganzzahl-Division mit Rest
- Nutze die SDL-Logging-Bibliothek