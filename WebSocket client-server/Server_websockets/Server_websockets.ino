    
    
    
    #include <ESP8266WiFi.h>
    #include <WebSocketsServer.h>
    
    WebSocketsServer webSocket = WebSocketsServer(81);
    
    char* ssid = "SSID";
    char* password = "PASSWORD";
    
    void setup()
    {
      Serial.begin(115200);
      Serial.println();
      Serial.print("Configuring access point...");
      /* You can remove the password parameter if you want the AP to be open. */
      WiFi.softAP(ssid, password);
    
      IPAddress myIP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(myIP);
  
      webSocket.begin();
      webSocket.onEvent(webSocketEvent);
    }
    
    void loop()
    {
      webSocket.loop();
      if(Serial.available() > 0){
        String mydata= Serial.readStringUntil('\n');
        webSocket.broadcastTXT(mydata);
      }
    }
    
    void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
      if(type == WStype_TEXT){
        // processs any returned data
        Serial.printf("payload [%u]: %s\n", num, payload);
      } 
    }
