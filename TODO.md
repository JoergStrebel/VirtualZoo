# C++-Code
- baue constexpr ein für compile-time Werte.
- Do not pass std::string by value, as it makes an expensive copy. Tip: In most cases, use a std::string_view parameter instead 

 
# Simulationsdesign
- Event System und Kollisionserkennung. Kollisionserkennung zwischen Organismus und anderen Objekten in der Welt. Diese Erkennung muss in der Welt stattfinden, NICHT in der Visualierung. Die Visualierung malt nur, ist aber ansonsten "dumm".
- Organismus muss auf die eingegangenen Stimuli reagieren und er muss mit einer kette von stimuli zurecht kommen.
- ein Körper  hat Sinneszellen mit einer klaren Reizerfassung un einer klaren Verortung am Körper. Wenn die Sinneszelle feuert, dann weiß das Gehirn, was es mit dem Reiz anfangen soll und wie er weiter zu verabeiten ist.

- Schleife bauen in visualize_gui::load_media(...) um alle Bilder zu laden.
- Schleife bauen in ~visualize_gui um alle Bilder zu löschen.
- Einführung einer transform() Methode in visualize.h, um die Welt auf die Visualisierung abzubilden.

- Den Welt-Zustand an die Visualisierung geben, so dass die Visualisierung aktualisiert werden kann
- gemeinsame Definitionen zwischen Visualisierung und Welt-Zustand einführen
- Visualisierung und Simulation zeitmäßig entkoppeln: Welt-Zustand nur alle x Ticks zeichnen lassen


