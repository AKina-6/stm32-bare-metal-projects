#include "app/menu_renderer.h"

/*
 * Adjust these declarations to match the SSD1306 library
 * used in your STM32 project.
 */
extern void SSD1306_Fill(unsigned char color);
extern void SSD1306_GotoXY(unsigned char x, unsigned char y);
extern void SSD1306_Puts(
    const char *text,
    const void *font,
    unsigned char color
);
extern void SSD1306_UpdateScreen(void);
extern const void *Font_7x10;

static void oled_clear(void *context)
{
    (void)context;
    SSD1306_Fill(0U);
}

static void oled_draw_text(
    void *context,
    uint8_t x,
    uint8_t y,
    const char *text,
    bool inverted
) {
    (void)context;
    SSD1306_GotoXY(x, y);
    SSD1306_Puts(
        text,
        Font_7x10,
        inverted ? 0U : 1U
    );
}

static void oled_present(void *context)
{
    (void)context;
    SSD1306_UpdateScreen();
}

menu_display_t ssd1306_menu_display_create(void)
{
    const menu_display_t display = {
        .context = 0,
        .clear = oled_clear,
        .draw_text = oled_draw_text,
        .present = oled_present
    };

    return display;
}
