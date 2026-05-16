# ARCADE DMX Controller - ESP32-S2 Mini

Полная реализация коммерческого пульта управления световыми приборами LIGHTSHOW.SU "ARCADE" на одном микроконтроллере **ESP32-S2 Mini**.

## 🎯 Основные функции

- ✅ **DMX512 Control** - управление 5 группами по 1024 канала
- ✅ **TFT 2.8"/3.2" Touch UI** - сенсорный графический интерфейс
- ✅ **10 Static Scenes** - предзаписанные статические сцены
- ✅ **6+ Dynamic Programs** - динамические программы для дискотек
- ✅ **BPM Speed Controller** - контроль скорости эффектов
- ✅ **Show Recording** - запись и воспроизведение световых шоу
- ✅ **Web Editor** - онлайн редактор на локальной сети
- ✅ **5 Hot Keys** - физические кнопки для быстрого доступа
- ✅ **SPIFFS Storage** - сохранение программ и конфигурации

## 📋 Требуемое оборудование

### Микроконтроллер
- **ESP32-S2 Mini** (240 MHz, 4MB Flash, 2MB PSRAM)

### Дисплей и сенсор
- **TFT ILI9341** 2.8" или 3.2" (320×240 или 320×480)
- **Резистивный сенсор XPT2046** по SPI

### DMX-интерфейс
- **MAX485** или **SP485** трансивер TTL↔DMX512
- **Разъем XLR-3 или Mini-XLR** для DMX-выхода

### Периферия
- **4-5 тактовых кнопок** (GPIO pull-up/down)
- **USB Type-C** питание (5V, ≥1A)

## 🔌 Подключение на ESP32-S2 Mini

```
TFT ILI9341 (SPI1):
  CS   → GPIO34 (D5)
  DC   → GPIO35 (D6)
  MOSI → GPIO32 (SPI1_D7)
  MISO → GPIO37 (SPI1_D4)
  CLK  → GPIO36 (SPI1_CLK)
  RST  → GPIO33 (D9)

XPT2046 Touch (SPI2):
  CS   → GPIO39 (D7)
  MOSI → GPIO11 (SPI2_D0)
  MISO → GPIO9  (SPI2_D1)
  CLK  → GPIO10 (SPI2_CLK)
  IRQ  → GPIO40 (D8) [опционально]

MAX485 DMX:
  DI   → GPIO4  (UART1_TX)
  RE   → GND (читать всегда выключен)
  DE   → GPIO5  (Направление)
  A/B  → XLR pins

Кнопки (GPIO pull-up к 3.3V):
  SCENE_1  → GPIO13
  SCENE_2  → GPIO14
  SCENE_3  → GPIO38
  SCENE_4  → GPIO41
  SCENE_5  → GPIO42
```

## 📂 Структура проекта

```
arcade-dmx-controller/
├── firmware/
│   ├── platformio.ini              # конфигурация PlatformIO
│   ├── src/
│   │   ├── main.cpp                # точка входа
│   │   ├── config.h                # константы и конфигурация
│   │   ├── display/
│   │   │   └── tft_display.h       # управление TFT
│   │   ├── dmx/
│   │   │   └── dmx512.h            # протокол DMX512
│   │   ├── ui/
│   │   │   └── buttons.h           # физические кнопки
│   │   ├── effects/
│   │   │   ├── scene.h             # сцены (статические)
│   │   │   └── program.h           # программы (динамические)
│   │   ├── storage/
│   │   │   └── spiffs.h            # работа с SPIFFS
│   │   └── webserver/
│   │       └── web_server.h        # REST API
│   └── .gitignore
├── web-editor/
│   └── index.html                  # веб-редактор
├── docs/
│   ├── INSTALLATION.md             # установка и компиляция
│   └── API.md                      # описание REST API
└── README.md
```

## 🚀 Быстрый старт

### 1. Установка зависимостей
```bash
pip install platformio
```

### 2. Клонирование репозитория
```bash
git clone https://github.com/shedafoxlis/arcade-dmx-controller.git
cd arcade-dmx-controller/firmware
```

### 3. Конфигурация
Отредактировать `src/config.h` под вашу аппаратуру (если нужно)

### 4. Компиляция и загрузка
```bash
# Собрать проект
platformio run

# Загрузить на ESP32-S2 Mini
platformio run --target upload

# Просмотр логов
platformio device monitor --baud 115200
```

### 5. Веб-интерфейс
После загрузки открыть браузер:
```
http://192.168.1.XXX/
```
(IP адрес будет выведен в серийный порт)

## 📡 Работа с DMX

### Стандартная раскладка каналов (на группу)

```
Группа 1:   LED PAR / Wash (ch 0-101)
Группа 2:   Spot/Moving Head (ch 102-203)
Группа 3:   LED Bar / Линеар (ch 204-305)
Группа 4:   Лазеры / Спецэффекты (ch 306-407)
Группа 5:   Система дыма / Прочее (ch 408-509)
```

Полностью настраивается в конфигурации!

## 🎨 Встроенные эффекты

### Статические сцены (10 шт)
1. **Red** - Красная
2. **Green** - Зелёная
3. **Blue** - Синяя
4. **White** - Белая
5. **Cyan** - Голубая
6. **Magenta** - Магента
7. **Yellow** - Жёлтая
8. **Orange** - Оранжевая
9. **Purple** - Фиолетовая
10. **Blackout** - Темнота

### Динамические программы (6 базовых)
1. **Rainbow Chase** - радуга, движущийся паттерн
2. **Pulse** - пульсирование яркости
3. **Strobe** - стробоскоп белый
4. **Rainbow Strobe** - цветной стробоскоп
5. **DJ Mix** - быстрая смена цветов под BPM
6. **Slow Color Fade** - медленная смена цветов

Скорость всех программ контролируется **BPM энкодером** (30-240 BPM)

## 🔧 REST API

### Основные endpoints

```
GET  /api/status              - статус пульта
POST /api/scene?id=0          - запустить сцену
POST /api/program?group=0&id=2 - запустить программу в группе
POST /api/dmx?ch=0&val=255    - установить значение канала
POST /api/record/start        - начать запись шоу
POST /api/record/stop         - остановить запись
POST /api/record/play?id=0    - воспроизвести шоу
```

Полное описание API: [docs/API.md](docs/API.md)

## 🛠️ Разработка

### Добавление новой программы (эффекта)

1. Добавить в `enum EffectType` в `src/effects/program.h`
2. Реализовать логику в `updateEffect()`
3. Добавить в массив `programs[]`

### Добавление новой сцены

1. Добавить в массив `scenes[]` в `src/effects/scene.h`
2. Определить RGB значения для каждой группы

### Кастомизация дисплея

Используется библиотека **TFT_eSPI**. Отредактировать:
- `User_Setup.h` в `~/.platformio/packages/framework-arduinoespressif32/`

## 📚 Документация

- [INSTALLATION.md](docs/INSTALLATION.md) - подробная установка и настройка
- [API.md](docs/API.md) - полное описание REST API

## 🐛 Известные ограничения (v0.1.0)

- Рекордер работает в памяти (max ~10KB лога событий)
- Веб-UI базовый (можно расширить)
- X/Y-сенсорная поверхность в планах
- Требуется оптимизация памяти для полного функционала

## 🔮 Планы развития

- [ ] Сенсорный X/Y XY-джойстик на экране
- [ ] Библиотека 100+ программируемых эффектов
- [ ] MIDI-вход для синхронизации
- [ ] SD карта для хранения шоу
- [ ] Встроенная синхронизация звука
- [ ] Веб-редактор программ

## 📜 Лицензия

MIT License - свободное использование в коммерческих и личных проектах

## 🤝 Поддержка

Вопросы и issues: [GitHub Issues](https://github.com/shedafoxlis/arcade-dmx-controller/issues)

---

**Статус**: 🔨 В разработке  
**Последнее обновление**: 2026-05-16  
**Версия прошивки**: 0.1.0 (alpha)
