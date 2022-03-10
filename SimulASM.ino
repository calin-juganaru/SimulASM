#include "display.h"
#include "memories.h"
#include "keypads.h"
#include "parsing.h"

// =============================================================================

void setup()
{
    delay(2500);
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);

    for (auto address = 0; address < 4; ++address)
    {
        mem_display.shutdown(address, false);
        mem_display.setIntensity(address, 0);
        mem_display.clearDisplay(address);
    }

    reg_display.shutdown(0, false);
    reg_display.setIntensity(0, 0);
    reg_display.clearDisplay(0);

    module.setupDisplay(true, 0);
    wait_button(ENTER);

    // -------------------------------------------------------------------------

    lcd_i2c.init();
    lcd_i2c.backlight();
    lcd_i2c.setCursor(6, 1);
    lcd_i2c.print("SimulASM");
    lcd_i2c.setCursor(16, 3);
    lcd_i2c.print("2022");

    // -------------------------------------------------------------------------

    SR = -1; // 0xFF
}

// =============================================================================

void loop()
{
    for (auto&& keypad: cmd_pads)
    {
        auto key = keypad.getKey();
        if (!key) continue;

        module.setLEDs(key);
        segment_text = get_instruction(key);

        print_segment();
        parse_instruction(key);
        clear_segment();
    }

    call(set_memory_byte, 32);
    call(display_register, 8);
}

// =============================================================================
