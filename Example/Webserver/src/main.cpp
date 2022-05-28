#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>

#include "StaticPageData.h"

AsyncWebServer server(80);

#define AP_SSID "ObliCarina"
#define AP_PASS "password"

const char * softAP_ssid= AP_SSID; // SSID of ESP's wifi
const char * softAP_pass= AP_PASS; // Password for ESP's wifi

uint8_t led_val= 0;

void setup(){
  Serial.begin(115200);

  // Initialize led
  pinMode(LED_BUILTIN, OUTPUT); 

  WiFi.softAP(softAP_ssid);
  
  Serial.println(WiFi.localIP());
 
  // Routing requests 
  server.on("/*", HTTP_GET, [](AsyncWebServerRequest *request){
    String tmp= request->url();
  
    digitalWrite(LED_BUILTIN, led_val= !led_val);

    if( tmp == data_index_5d58cbbf_css_path ){
      Serial.println("css file requested");
      request->send_P(200, "text/css;charset=UTF-8", data_index_5d58cbbf_css);
    }
    else if( tmp == data_index_d0368d6e_js_path ){
      Serial.println("javascript file requested");
      request->send_P(200, "text/javascript;charset=UTF-8", data_index_d0368d6e_js);
    }
    // Default redirecting to root "/"
    else{
      Serial.println("Index.html requested"); 
      
      if( tmp != "/" && tmp != "/about" ) // About is another kind of page
        request->redirect("/");
      request->send_P(200, "text/html", data_index_html);
    }
  });
/*
  server.on(data_index_5d58cbbf_css_path, HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("jquery.js requested");
    request->send_P(200, "text/css;charset=UTF-8", data_index_5d58cbbf_css);
  });

  server.on(data_index_d0368d6e_js_path, HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("jquery.js requested");
    request->send_P(200, "text/javascript;charset=UTF-8", data_index_d0368d6e_js);
  });
*/
  /*
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
 */
  server.begin();
}
 
void loop(){
  Serial.println("ciao\n");
}