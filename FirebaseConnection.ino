#include <WiFi.h>
#include <FirebaseESP32.h>


#define FIREBASE_HOST "YOUR FIREBASE HOST ID"
#define FIREBASE_AUTH "YOUR FIREBASE AUTHENTICATION KEY"
#define WIFI_SSID "YOUR WIFI NAME"
#define WIFI_PASSWORD "YOUR WIFI PASSWORD"


//Define FirebaseESP32 data object
FirebaseData firebaseData, deep;
FirebaseJson json;

void setup()
{

  Serial.begin(115200);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  //String path = "/data";
  

  Serial.println("------------------------------------");
  Serial.println("Connected...");
  
}

void loop()
{
   
 int Sdata = 55, Gdata;
  delay(100); 
  json.set("/data", Sdata);
  Firebase.updateNode(firebaseData,"Spo2",json);    // UPLOADING DATA TO FIREBASE
  float d = Firebase.getInt(deep, "DHT/interval/value");    // FETCHING DATA FROM DATABASE, STORING THE DATA IN VARIABLE 'deep'
  float schedule = deep.floatData();
  Serial.println(schedule);
  delay(5000);
}
