#include "display.h"

class ScrollableTextArea {
public:
    ScrollableTextArea(const String &title = "");

    ScrollableTextArea(
        uint8_t fontSize, int16_t startX, int16_t startY, int32_t width, int32_t height,
        bool drawBorders = true, bool indentWrappedLines = false
    );

    ~ScrollableTextArea();

    void scrollUp();

    void scrollDown();

    void scrollToLine(size_t lineNumber);

    String getLine(size_t lineNumber);
    size_t getMaxLines();

    void addLine(const String &text);

    void clear();

    void fromString(const String &text);

    void fromFile(File file);

    void draw(bool force = false);

    void show(bool force = false);

    uint32_t getMaxVisibleTextLength();

    size_t firstVisibleLine = 0;
    size_t lastVisibleLine = 0;
    /// TODO: Change to std::vector<char *> and alloc to PSRAM if possible
    std::vector<String> linesBuffer;

private:
    bool _redraw = false;
    String _title;
    uint8_t _fontSize = 0;
    int16_t _startX = 0, _startY = 0;
    int32_t _width = 0, _height = 0;
    int32_t _pixelsPerLine = 0;
    size_t _maxVisibleLines = 0;
    uint16_t _maxCharactersPerLine = 0;
    bool _indentWrappedLines = false;

    void setup();

    void update(bool force = false);
};
