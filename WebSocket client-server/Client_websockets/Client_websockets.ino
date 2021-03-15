  
    
    #include <ESP8266WiFi.h>
    #include <WebSocketsClient.h>
    
    WebSocketsClient webSocket;

    char* ssid = "SSID";
    char* password = "PASSWORD";
    
   
    void setup()
    {
      Serial.begin(115200);
      pinMode(LED_BUILTIN,OUTPUT);
      WiFi.begin(ssid,password);
      
      while(WiFi.status()!=WL_CONNECTED)
      {
        Serial.print(".");
        delay(500);
      }
      Serial.println("");
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
      
      webSocket.begin("192.168.4.1", 81, "/");
      webSocket.onEvent(webSocketEvent);
      // try ever 5000 again if connection has failed
      webSocket.setReconnectInterval(5000);
    }
    
    void loop()
    {
      webSocket.loop();
      if(Serial.available() > 0){
       // char c[] = {(char)Serial.read()};
        String mydata= Serial.readStringUntil('\n');
        webSocket.sendTXT(mydata);
      }
    }
    
    void webSocketEvent(WStype_t type, uint8_t * payload, size_t length){
      if(type == WStype_TEXT){
        // processs any returned data
        
        String str=(char*)payload;
             
        Serial.println(str);
        if(str == "1")digitalWrite(LED_BUILTIN,LOW);
        else digitalWrite(LED_BUILTIN,HIGH);
        
        webSocket.sendTXT("{\"from Client\":\"OK\"}");
      }
      
    }
