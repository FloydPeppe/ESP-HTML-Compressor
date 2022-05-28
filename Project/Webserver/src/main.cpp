#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

AsyncWebServer server(80);

#define AP_SSID "ObliCarina"
#define AP_PASS "password"

const char * softAP_ssid= AP_SSID; // SSID of ESP's wifi
const char * softAP_pass= AP_PASS; // Password for ESP's wifi

const char* index_css_path= "/assets/index.css";
const char* index_js_path= "/assets/index.js";
const char* favicon_path= "/assets/favicon.ico";
const char* svg_path= "/assets/react_logo.svg";
const char* index_html_path= "/index.html";

uint8_t led_val= 0;

void setup(){
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

    if( tmp == index_css_path ){
      Serial.println("css file requested");
      request->send(SPIFFS, index_css_path, "text/css;charset=UTF-8");
    }
    else if( tmp == index_js_path ){
      Serial.println("javascript file requested");
      request->send(SPIFFS, index_js_path, "text/javascript;charset=UTF-8");
    }
    else if( tmp == svg_path ){
      Serial.println("svg file requested");
      request->send(SPIFFS, svg_path, "image/svg+xml");
    }
    else if( tmp == favicon_path ){
      Serial.println("favicon file requested");
      request->send(SPIFFS, favicon_path, "image/ico");
    }
    // Default redirecting to root "/"
    else{
      Serial.println("Index.html requested"); 
      
      if( tmp != "/" && tmp != "/about" && tmp != "/obli" ) // About is another kind of page
        request->redirect("/");
      request->send(SPIFFS, index_html_path, "text/html");
    }
  });

  server.begin();
}
 
void loop(){
  Serial.println("ciao\n");
}