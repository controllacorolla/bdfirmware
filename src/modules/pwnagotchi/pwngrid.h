/*
Thanks to thoses developers for their projects:
* @7h30th3r0n3 : https://github.com/7h30th3r0n3/Evil-M5Core2 and https://github.com/7h30th3r0n3/PwnGridSpam
* @viniciusbo : https://github.com/viniciusbo/m5-palnagotchi
* @sduenasg : https://github.com/sduenasg/pio_palnagotchi

Thanks to @bmorcelli for his help doing a better code.
*/
#if !defined(LITE_VERSION)
#include "ArduinoJson.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include <Arduino.h>
#include <vector>

typedef struct {
    int epoch = 0;
    String face;
    String grid_version;
    String identity;
    String name;
    int pwnd_run = 0;
    int pwnd_tot = 0;
    String session_id;
    int timestamp = 0;
    int uptime = 0;
    String version;
    signed int rssi = 0;
    unsigned long last_ping = 0;
    bool gone = false;
} pwngrid_peer;

void initPwngrid();
esp_err_t pwngridAdvertise(uint8_t channel, const String &face);
std::vector<pwngrid_peer> getPwngridPeers();
uint8_t getPwngridRunTotalPeers();
uint8_t getPwngridTotalPeers();
String getPwngridLastFriendName();
signed int getPwngridClosestRssi();
void checkPwngridGoneFriends();
void clearPwngridPeers();
#endif
