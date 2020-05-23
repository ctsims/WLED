#ifndef WLED_FCN_DECLARE_H
#define WLED_FCN_DECLARE_H
#include <Arduino.h>
#include "src/dependencies/espalexa/EspalexaDevice.h"
#include "src/dependencies/e131/ESPAsyncE131.h"

/*
 * All globally accessible functions are declared here
 */

//alexa.cpp
void onAlexaChange(EspalexaDevice* dev);
void alexaInit();
void handleAlexa();
void onAlexaChange(EspalexaDevice* dev);

//blynk.cpp
void initBlynk(const char* auth);
void handleBlynk();
void updateBlynk();

//button.cpp
void shortPressAction();
void handleButton();
void handleIO();

//colors.cpp
void colorFromUint32(uint32_t in, bool secondary = false);
void colorFromUint24(uint32_t in, bool secondary = false);
void relativeChangeWhite(int8_t amount, byte lowerBoundary = 0);
void colorHStoRGB(uint16_t hue, byte sat, byte* rgb); //hue, sat to rgb
void colorCTtoRGB(uint16_t mired, byte* rgb); //white spectrum to rgb

void colorXYtoRGB(float x, float y, byte* rgb); // only defined if huesync disabled TODO
void colorRGBtoXY(byte* rgb, float* xy); // only defined if huesync disabled TODO

void colorFromDecOrHexString(byte* rgb, char* in);
void colorRGBtoRGBW(byte* rgb); //rgb to rgbw (http://codewelt.com/rgbw). (RGBW_MODE_LEGACY)

//dmx.cpp
void initDMX();
void handleDMX();

//e131.cpp
void handleE131Packet(e131_packet_t* p, IPAddress clientIP, bool isArtnet);

//file.cpp
bool handleFileRead(AsyncWebServerRequest*, String path);

//hue.cpp
void handleHue();
void reconnectHue();
void onHueError(void* arg, AsyncClient* client, int8_t error);
void onHueConnect(void* arg, AsyncClient* client);
void sendHuePoll();
void onHueData(void* arg, AsyncClient* client, void *data, size_t len);

//ir.cpp
bool decodeIRCustom(uint32_t code);
void relativeChange(byte* property, int8_t amount, byte lowerBoundary = 0, byte higherBoundary = 0xFF);
void changeEffectSpeed(int8_t amount);
void changeEffectIntensity(int8_t amount);
void decodeIR(uint32_t code);
void decodeIR24(uint32_t code);
void decodeIR24OLD(uint32_t code);
void decodeIR24CT(uint32_t code);
void decodeIR40(uint32_t code);
void decodeIR44(uint32_t code);
void decodeIR21(uint32_t code);
void decodeIR6(uint32_t code);

void initIR();
void handleIR();

//json.cpp
#include "ESPAsyncWebServer.h"
#include "src/dependencies/json/ArduinoJson-v6.h"
#include "src/dependencies/json/AsyncJson-v6.h"
#include "FX.h"

void deserializeSegment(JsonObject elem, byte it);
bool deserializeState(JsonObject root);
void serializeSegment(JsonObject& root, WS2812FX::Segment& seg, byte id);
void serializeState(JsonObject root);
void serializeInfo(JsonObject root);
void serveJson(AsyncWebServerRequest* request);
void serveLiveLeds(AsyncWebServerRequest* request);

//led.cpp
void setValuesFromMainSeg();
void resetTimebase();
void toggleOnOff();
void setAllLeds();
void setLedsStandard(bool justColors = false);
bool colorChanged();
void colorUpdated(int callMode);
void updateInterfaces(uint8_t callMode);
void handleTransitions();
void handleNightlight();

//mqtt.cpp
bool initMqtt();
void publishMqtt();

//ntp.cpp
void handleNetworkTime();
void sendNTPPacket();
bool checkNTPResponse();    
void updateLocalTime();
void getTimeString(char* out);
bool checkCountdown();
void setCountdown();
byte weekdayMondayFirst();
void checkTimers();

//overlay.cpp
void initCronixie();
void handleOverlays();
void handleOverlayDraw();
void _overlayAnalogCountdown();
void _overlayAnalogClock();

byte getSameCodeLength(char code, int index, char const cronixieDisplay[]);
void setCronixie();
void _overlayCronixie();    
void _drawOverlayCronixie();

//set.cpp
void _setRandomColor(bool _sec,bool fromButton=false);
bool isAsterisksOnly(const char* str, byte maxLen);
void handleSettingsSet(AsyncWebServerRequest *request, byte subPage);
bool handleSet(AsyncWebServerRequest *request, const String& req);
int getNumVal(const String* req, uint16_t pos);
bool updateVal(const String* req, const char* key, byte* val, byte minv=0, byte maxv=255);

//udp.cpp
void notify(byte callMode, bool followUp=false);
void realtimeLock(uint32_t timeoutMs, byte md = REALTIME_MODE_GENERIC);
void handleNotifications();
void setRealtimePixel(uint16_t i, byte r, byte g, byte b, byte w);

//usermod.cpp
void userSetup();
void userConnected();
void userLoop();

//wled_eeprom.cpp
void commit();
void clearEEPROM();
void writeStringToEEPROM(uint16_t pos, char* str, uint16_t len);
void readStringFromEEPROM(uint16_t pos, char* str, uint16_t len);
void saveSettingsToEEPROM();
void loadSettingsFromEEPROM(bool first);
void savedToPresets();
bool applyPreset(byte index, bool loadBri = true);
void savePreset(byte index, bool persist = true);
void loadMacro(byte index, char* m);
void applyMacro(byte index);
void saveMacro(byte index, String mc, bool persist = true); //only commit on single save, not in settings

//wled_serial.cpp
void handleSerial();

//wled_server.cpp
bool isIp(String str);
bool captivePortal(AsyncWebServerRequest *request);
void initServer();
void serveIndexOrWelcome(AsyncWebServerRequest *request);
void serveIndex(AsyncWebServerRequest* request);
String msgProcessor(const String& var);
void serveMessage(AsyncWebServerRequest* request, uint16_t code, String headl, String subl="", byte optionT=255);
String settingsProcessor(const String& var);
String dmxProcessor(const String& var);
void serveSettings(AsyncWebServerRequest* request);

//xml.cpp
char* XML_response(AsyncWebServerRequest *request, char* dest = nullptr);
char* URL_response(AsyncWebServerRequest *request);
void sappend(char stype, const char* key, int val);
void sappends(char stype, const char* key, char* val);
void getSettingsJS(byte subPage, char* dest);

#endif