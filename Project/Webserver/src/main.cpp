#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

#include "assetsPath.h"

AsyncWebServer server(80);

#define AP_SSID "ObliCarina"
#define AP_PASS "password"

const char * softAP_ssid= AP_SSID; // SSID of ESP's wifi
const char * softAP_pass= AP_PASS; // Password for ESP's wifi

uint8_t led_val= 0;

void setup(){
  // Initialize serial baudrate
  Serial.begin(115200);

  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Initialize led
  pinMode(LED_BUILTIN, OUTPUT); 

  WiFi.softAP(softAP_ssid, softAP_pass);
  
  Serial.println(WiFi.localIP());
 
  // Routing all requests 
  server.on("/*", HTTP_GET, [](AsyncWebServerRequest *request){
    String tmp= request->url();
  
    digitalWrite(LED_BUILTIN, led_val= !led_val);

    if( tmp == INDEX_CSS_PATH ){
      Serial.println("css file requested");
      request->send(SPIFFS, INDEX_CSS_PATH, "text/css;charset=UTF-8");
    }
    else if( tmp == INDEX_JS_PATH ){
      Serial.println("javascript file requested");
      request->send(SPIFFS, INDEX_JS_PATH, "text/javascript;charset=UTF-8");
    }
    else if( tmp == LOGO_SVG_PATH ){
      Serial.println("svg file requested");
      request->send(SPIFFS, LOGO_SVG_PATH, "image/svg+xml");
    }
    else if( tmp == FAVICON_ICO_PATH ){
      Serial.println("favicon file requested");
      request->send(SPIFFS, FAVICON_ICO_PATH, "image/ico");
    }
    // Default redirecting to root "/"
    else{
      Serial.println("Index.html requested"); 
      if( tmp != "/" && tmp != "/about" && tmp != "/obli" ) // "about" and "obli" are other kind of pages and they don't have to be redircted to "/"
        request->redirect("/");
      request->send(SPIFFS, INDEX_HTML_PATH, "text/html");
    }
  });

  server.begin();
}
 
void loop(){
  
}