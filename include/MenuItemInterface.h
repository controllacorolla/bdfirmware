#ifndef __MENU_ITEM_INTERFACE_H__
#define __MENU_ITEM_INTERFACE_H__

#include "core/display.h"
#include <globals.h>

class MenuItemInterface {
public:
    virtual ~MenuItemInterface() = default;
    virtual void optionsMenu(void) = 0;
    virtual void drawIcon(float scale = 1) = 0;
    virtual void drawIconImg() {
        drawImg(
            *bruceConfig.themeFS(),
            bruceConfig.getThemeItemImg(themePath()),  // const String& - no heap alloc
            0,
            imgCenterY,
            true,
            bruceConfig.theme.gifDuration,
            false
        );
    }
    virtual bool hasTheme() = 0;
    virtual const String& themePath() = 0;

    bool checkTheme() { return hasTheme() && themePath().length() > 0; }
    String getName() const { return String(_name); }

    void draw(float scale = 1) {
        if (rotation != bruceConfigPins.rotation) resetCoordinates();
        if (!checkTheme()) {
            tft.fillRect(0, 27, tftWidth, tftHeight - 27, bruceConfig.bgColor);
            drawIcon(scale);
            drawArrows(scale);
            drawTitle(scale);
        } else {
            if (bruceConfig.theme.label)
                drawTitle(scale); // If using .GIF, labels are draw after complete, which takes some time
            drawIconImg();
            if (bruceConfig.theme.label) drawTitle(scale); // Makes sure to draw over the image
        }
        drawStatusBar();
    }

    void drawArrows(float scale = 1) {
        tft.fillRect(arrowAreaX, iconAreaY, arrowAreaW, iconAreaH, bruceConfig.bgColor);
        tft.fillRect(
            tftWidth - arrowAreaX - arrowAreaW, iconAreaY, arrowAreaW, iconAreaH, bruceConfig.bgColor
        );

        int arrowSize = scale * 10;
        int lineWidth = scale * 2.5;
        if (lineWidth < 2) lineWidth = 2;

        int arrowX = BORDER_PAD_X + 1.5 * arrowSize;
        int arrowY = iconCenterY + 1.5 * arrowSize;
        uint16_t arrowColor = getColorVariation(bruceConfig.priColor, 6, -1);

        // Left Arrow
        tft.drawWideLine(
            arrowX, arrowY,
            arrowX + arrowSize, arrowY + arrowSize,
            lineWidth, arrowColor, bruceConfig.bgColor
        );
        tft.drawWideLine(
            arrowX, arrowY,
            arrowX + arrowSize, arrowY - arrowSize,
            lineWidth, arrowColor, bruceConfig.bgColor
        );

        // Right Arrow
        tft.drawWideLine(
            tftWidth - arrowX, arrowY,
            tftWidth - arrowX - arrowSize, arrowY + arrowSize,
            lineWidth, arrowColor, bruceConfig.bgColor
        );
        tft.drawWideLine(
            tftWidth - arrowX, arrowY,
            tftWidth - arrowX - arrowSize, arrowY - arrowSize,
            lineWidth, arrowColor, bruceConfig.bgColor
        );
    }

    void drawTitle(float scale = 1) {
        int titleY = iconCenterY + iconAreaH / 2 + FG;

        tft.setTextSize(FM);
        tft.drawPixel(0, 0, 0);
        tft.fillRect(arrowAreaX, titleY - 3, tftWidth - 2 * arrowAreaX, LH * FM + 6, bruceConfig.bgColor);
        int nchars = (tftWidth - 16) / (LW * FM);
        String name = getName().substring(0, nchars);
        int textW = name.length() * FM * LW;
        int pillW = textW + 16;
        int pillX = iconCenterX - pillW / 2;
        tft.fillRoundRect(pillX, titleY - 3, pillW, LH * FM + 6, 4,
                          getColorVariation(bruceConfig.priColor, 25, -1));
        tft.setTextColor(bruceConfig.priColor, getColorVariation(bruceConfig.priColor, 25, -1));
        tft.drawCentreString(name, iconCenterX, titleY, 1);
        tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
    }

protected:
    const char *_name = "";
    uint8_t rotation = ROTATION;

    int iconAreaH =
        ((tftHeight - 2 * BORDER_PAD_Y) % 2 == 0 ? tftHeight - 2 * BORDER_PAD_Y
                                                 : tftHeight - 2 * BORDER_PAD_Y + 1);
    int iconAreaW = iconAreaH;

    int iconCenterX = tftWidth / 2;
    int iconCenterY = tftHeight / 2;
    int imgCenterY = 13;

    int iconAreaX = iconCenterX - iconAreaW / 2;
    int iconAreaY = iconCenterY - iconAreaH / 2;

    int arrowAreaX = BORDER_PAD_X;
    int arrowAreaW = iconAreaX - arrowAreaX;

    MenuItemInterface(const char *name) : _name(name) {}

    void clearIconArea(void) {
        tft.fillRect(iconAreaX, iconAreaY, iconAreaW, iconAreaH, bruceConfig.bgColor);
    }
    void clearImgArea(void) { tft.fillRect(7, 27, tftWidth - 14, tftHeight - 34, bruceConfig.bgColor); }
    void resetCoordinates(void) {
        // Recalculate Center and ared due to portrait/landscape changings
        if (tftWidth > tftHeight) {
            iconAreaH =
                ((tftHeight - 2 * BORDER_PAD_Y) % 2 == 0 ? tftHeight - 2 * BORDER_PAD_Y
                                                         : tftHeight - 2 * BORDER_PAD_Y + 1);
        } else {
            iconAreaH =
                ((tftWidth - 2 * BORDER_PAD_Y) % 2 == 0 ? tftWidth - 2 * BORDER_PAD_Y
                                                        : tftWidth - 2 * BORDER_PAD_Y + 1);
        }

        iconAreaW = iconAreaH;

        iconCenterX = tftWidth / 2;
        iconCenterY = tftHeight / 2;

        iconAreaX = iconCenterX - iconAreaW / 2;
        iconAreaY = iconCenterY - iconAreaH / 2;

        arrowAreaX = BORDER_PAD_X;
        arrowAreaW = iconAreaX - arrowAreaX;

        rotation = bruceConfigPins.rotation;
    }

private:
};

#endif // __MENU_ITEM_INTERFACE_H__
