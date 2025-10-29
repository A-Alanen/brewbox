// ===== File: config.h =====
#ifndef CONFIG_H
#define CONFIG_H

#include <LiquidCrystal.h>
#include <DHT.h>

#define DEFAULT_SET_TEMPERATURE  25    // °C, target temperature
#define DEFAULT_FAN_DURATION     300     // seconds, fan runtime
#define DEFAULT_HEAT_DURATION    300     // seconds, heater runtime
#define DEFAULT_HYSTERESIS       1     // °C, deadband for relay control

#define MENU_ITEMS               4
#define SAFETY_TEMP              50    // °C, overheat cutoff

#define IDLE_TIMEOUT             10000UL  // ms (10 seconds)

#define BUZZER_ON  HIGH
#define BUZZER_OFF LOW
#define BUZZER_DEFAULT_FREQ 1000  // Hz, tonal buzzer default frequency

// ON/OFF states for active LOW relays
#define FAN_ON    LOW
#define FAN_OFF   HIGH
#define HEATER_ON LOW
#define HEATER_OFF HIGH

#define DEFAULT_MENU_INDEX       0

#endif
