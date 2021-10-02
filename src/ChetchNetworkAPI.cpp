#include <ChetchNetworkAPI.h>
#include <ESP8266WiFi.h>

namespace Chetch{

bool NetworkAPI::trace = false;

bool NetworkAPI::registerService(const char *networkServiceURL, const char *serviceName, int port, int timeout){
    HTTPClient http;  //Declare an object of class HTTPClient
    bool success = false;
    unsigned long started = millis();
    do{
        if(trace){
            Serial.print("Registering this device @: ");
            Serial.println(networkServiceURL);
        }
        http.begin(networkServiceURL);  //Open connection and Specify request destination
        http.addHeader("Content-Type", "application/json"); //api expects JSON

        //manually create a JSON string and PUT to the API
        char buf[128];
        sprintf(buf, "{\"service_name\": \"%s\",\"endpoint_port\":%d,\"protocols\":\"tcp\"}", serviceName, port);
        int httpCode = http.PUT(buf);   //Send the request

        if(trace){
            Serial.print("Return code: ");
            Serial.println(httpCode);
        }

        //check if successful and close (if not successful, wait a bit and try again)
        success = httpCode == HTTP_CODE_OK;
        http.end();   //Close connection
        if(!success){
            if(trace){
                Serial.print("Failed to register service: return code ");
                Serial.println(httpCode);
            }
            if(timeout > 0 && (millis() - started > timeout)){
                break;
            } else {
                delay(2000);
            }
        }
    
    } while (!success);

    return success;
}

} //end namespace