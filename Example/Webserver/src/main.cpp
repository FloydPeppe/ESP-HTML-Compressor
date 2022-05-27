#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>

#include "HtmlData.h"

AsyncWebServer server(80);

char AP_SSID[]= "ObliCarina";          // SSID of ESP's wifi
char AP_PASS[]= "password";             // Password for ESP's wifi
 
void setup(){
  Serial.begin(115200);

  WiFi.softAP(AP_SSID);
  
  Serial.println(WiFi.localIP());
 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Index.html requested");
    request->send_P(200, "text/html", data_index_html);
  });
  
  server.on(data_bootstrap_min_css_path, HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("jquery.js requested");
    request->send_P(200, "text/css;charset=UTF-8", data_bootstrap_min_css);
  });

  server.on(data_script_js_path, HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("script.js requested");
    request->send_P(200, "text/javascript", data_script_js);
  });


  server.on(data_bootstrap_min_js_path, HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("bootstrap_min.js requested");
    request->send_P(200, "text/javascript", data_bootstrap_min_js);
  });

  server.on(data_style_css_path, HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("style.css requested");
    request->send_P(200, "text/css;charset=UTF-8", data_style_css);
  });
 
  server.begin();
}
 
void loop(){
  Serial.println("ciao\n");
}