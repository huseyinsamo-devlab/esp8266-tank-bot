# 🚜 ESP8266 Tank Bot

Wi-Fi üzerinden kontrol edilen basit bir **ESP8266 robot tank** projesi.  
HTTP tabanlı komutlarla ileri, geri, sağ, sol ve dur işlemleri yapılabilir.  
L298N veya benzeri motor sürücülerle çalışır.

---

## ⚙️ Özellikler
- ESP8266 üzerinde mini web sunucu (Wi-Fi kontrol)  
- `/move?dir=fwd|back|left|right|stop&spd=0..1023` üzerinden kontrol  
- PWM hız ayarı (0–1023 arası)  
- 10 saniye boyunca komut gelmezse otomatik durdurma (güvenlik)  
- Basit **Python istemcisi** ile bilgisayardan komut gönderme

---

## 🧩 Donanım
| Bileşen | Açıklama |
|----------|-----------|
| **ESP8266 (NodeMCU 1.0)** | Wi-Fi mikrodenetleyici |
| **L298N motor sürücü** | Motor kontrol kartı |
| **2 DC motor + palet** | Tank hareket sistemi |
| **Güç kaynağı** | 7–12 V (motorlar için) |
| **Bağlantı kabloları** | Ortak GND bağlantısı gerekli |

---

## 🔌 Pin Bağlantıları
| Motor Sürücü | ESP8266 Pin | GPIO |
|---------------|-------------|------|
| IN1 | D1 | GPIO5 |
| IN2 | D2 | GPIO4 |
| IN3 | D3 | GPIO0 |
| IN4 | D4 | GPIO2 |
| ENA (sol) | D5 | GPIO14 |
| ENB (sağ) | D6 | GPIO12 |

> Kart ve sürücünün **GND uçlarını mutlaka birleştir.**

---

## 🧠 Kurulum
1. `firmware/esp8266_tank_bot/config.sample.h` dosyasını kopyalayıp `config.h` olarak kaydet.  
   Wi-Fi adını ve şifreni gir:
   ```cpp
   #define WIFI_SSID "YOUR_WIFI"
   #define WIFI_PASS "YOUR_PASSWORD"
