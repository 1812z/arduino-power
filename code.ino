
#需要修改key SSID password wol的mac地址 其它自己看
#define BLINKER_WIFI
#include <WiFiUdp.h>

#include <WakeOnLan.h>

WiFiUDP UDP;
WakeOnLan WOL(UDP);
#include <Blinker.h>

char auth[] = "key";
// 编写：1812z 博客 1812z.top
char ssid[] = "SSID";
char pswd[] = "password";

void wakeMyPC() {
    const char *MACAddress = "MAC";
  
    WOL.sendMagicPacket(MACAddress); // Send Wake On Lan packet with the above MAC address. Default to port 9.
    // WOL.sendMagicPacket(MACAddress, 7); // Change the port number
}

#define BUTTON_1 "ButtonKey"

BlinkerButton Button2("BUTTON_2");
BlinkerButton Button1("BUTTON_1");
BlinkerText TEXT1("tex-s"); 
BlinkerText TEXT3("powerj"); 

void button2_callback(const String & state)
{
    
    BLINKER_LOG("get button state: ", state);

    if (state == BLINKER_CMD_BUTTON_TAP) {
        BLINKER_LOG("Button tap!");

           wakeMyPC();
    }
    else{
      digitalWrite(LED_BUILTIN, LOW);
     Blinker.delay(1000);
     digitalWrite(LED_BUILTIN, HIGH);
     
    }
    
}    
void button1_callback(const String & state)
{
    digitalWrite(0, !digitalRead(0));
    BLINKER_LOG("get button state: ", state);

    if (state == BLINKER_CMD_BUTTON_TAP) {
        BLINKER_LOG("Button tap!");

        Button1.icon("icon_1");
        Button1.color("#00FF00");
        Button1.text("短按");
        Button1.print();
          Blinker.delay(500); 
            digitalWrite(0, !digitalRead(0));
                  digitalWrite(LED_BUILTIN, LOW);
     Blinker.delay(1000);
     digitalWrite(LED_BUILTIN, HIGH);
     
    }
    else if (state == BLINKER_CMD_BUTTON_PRESSED) {
        BLINKER_LOG("Button pressed!");

        Button1.icon("icon_1");
        Button1.color("#FF0000");
        Button1.text("长按中");
        Button1.print();
              digitalWrite(LED_BUILTIN, LOW);
     Blinker.delay(1000);
     digitalWrite(LED_BUILTIN, HIGH);
    }
    else if (state == BLINKER_CMD_BUTTON_RELEASED) {
        BLINKER_LOG("Button released!");

        Button1.icon("icon_1");
        Button1.color("#FF0000");
        Button1.text("成功长按");
        // Button1.text("Your button name", "describe");
        Button1.print();
              digitalWrite(LED_BUILTIN, LOW);
     Blinker.delay(1000);
     digitalWrite(LED_BUILTIN, HIGH);
     
    }
    else if (state == BLINKER_CMD_ON) {
        BLINKER_LOG("Toggle on!");

        Button1.icon("icon_1");
        Button1.color("#FF0000");
        Button1.text("闭合");
        // Button1.text("Your button name", "describe");
        Button1.print("on");
              digitalWrite(LED_BUILTIN, LOW);
     Blinker.delay(1000);
     digitalWrite(LED_BUILTIN, HIGH);
     
    }
    else if (state == BLINKER_CMD_OFF) {
        BLINKER_LOG("Toggle off!");

        Button1.icon("icon_1");
        Button1.color("#FF0000");
        Button1.text("断开");
        // Button1.text("Your button name", "describe");
        Button1.print("off");
              digitalWrite(LED_BUILTIN, LOW);
     Blinker.delay(1000);
     digitalWrite(LED_BUILTIN, HIGH);
     
    }
    else {
        BLINKER_LOG("Get user setting: ", state);

        Button1.icon("icon_1");
        Button1.color("#FFFFFF");
        Button1.text("?");
        // Button1.text("Your button name", "describe");
        Button1.print();
    }
}

void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);

    Blinker.vibrate();
    
    uint32_t BlinkerTime = millis();
    
    Blinker.print("millis", BlinkerTime);
}

String rts()//计算运行时间
    {
    int rt = Blinker.runTime();
    int r,e,f,s;
    String fh;
    Blinker.delay(100);
    if(rt >= 86400)//天数
    {r = rt / 86400;
     e = rt / 3600 - r*24;
     f = rt / 60 - r*1440 - e*60;
     s = rt - r*86400 - e*3600 - f*60;}
    else if(rt >= 3600)
    {r = 0;
     e = rt / 3600;
     f = rt / 60 - e*60;
     s = rt - e*3600 - f*60;}
    else
    {r = 0;
     e = 0;
     f = rt / 60;
     s = rt - f*60;}
     
    //BLINKER_LOG(r," ",e," ",f," ",s);//输出数据测试
    
    if(f==0 & e==0 & r==0)
    {fh = String("")+ s +"秒";}
    else if(r == 0 & e == 0 )
    {fh = String("")+ f + "分" + s +"秒";}
    else if(r == 0)
    {fh = String("")+ e + "时" + f + "分" + s +"秒"; }
    else
    {fh = String("")+ r + "天" + e + "时" + f + "分" + s +"秒";}

    return(fh);
    }

void heartbeat()//心跳
{
    TEXT1.print(rts());
  
   
}



void setup()
{
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);

    pinMode(0, OUTPUT);
    digitalWrite(0, HIGH);
      pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
     
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);
    Button1.attach(button1_callback);
      Blinker.attachHeartbeat(heartbeat);//附加心跳
      //wol
       WOL.setRepeat(3, 100); // Optional, repeat the packet three times with 100ms between. WARNING delay() is used between send packet function.

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask()); // Optional  => To calculate the broadcast address, otherwise 255.255.255.255 is used (which is denied in some networks).
    Button2.attach(button2_callback); 
}

void loop()
{
   int sensorVal2 = digitalRead(0);
  Serial.println(sensorVal2);
   Blinker.delay(2500); 
  if (sensorVal2 == HIGH) {
   
   TEXT3.print("断开");
  } else {

  TEXT3.print("闭合");
 }
   Blinker.run();
}
  
