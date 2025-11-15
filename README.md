# Układ do pomiaru refleksu na dzień otwarty CEZ 13 grudnia 2024 r.
<a href="https://www.tiktok.com/@cezstalowawola/video/7448272293739924758" target="_blank">tiktok</a>
![schemat](https://github.com/gcygan2/reflex/blob/main/schemat.png)  
[esp32](https://botland.com.pl/moduly-wifi-i-bt-esp32/8893-esp32-wifi-bt-42-platforma-z-modulem-esp-wroom-32-zgodny-z-esp32-devkit-5904422337438.html)

Instalacja obsługi ESP32 w Arduino IDE

Otwórz Arduino IDE.

Wejdź w Plik → Preferencje.

W polu „Dodatkowe adresy URL menedżera płytek” dodaj:

Kod
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
Kliknij OK.

Dodanie płytek ESP32

Wejdź w Narzędzia → Płytka → Menedżer płytek.

Wyszukaj ESP32 by Espressif Systems i kliknij Instaluj.

Wybór odpowiedniej płytki

Po instalacji wejdź w Narzędzia → Płytka → ESP32 Arduino.

Wybierz DOIT ESP32 DEVKIT V1 – to jest właściwa opcja dla Twojej płytki ESP32 Devkit V1.

Konfiguracja portu i upload

Podłącz płytkę przez USB.

Wybierz odpowiedni port w Narzędzia → Port.

Wgraj przykładowy program (np. „Blink”).

Jeśli pojawią się problemy z wgrywaniem, czasem trzeba nacisnąć przycisk BOOT podczas rozpoczynania uploadu, a następnie puścić go, gdy IDE zacznie przesyłać kod.
