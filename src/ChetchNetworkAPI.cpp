#include <ChetchNetworkAPI.h>

namespace Chetch{

bool NetworkAPI::trace = false;

int NetworkAPI::registerService(Client& client, const char *networkServiceIP, int networkServicePort, const char *serviceName, int port, int timeout){
    unsigned long started = millis();

    if(trace){
        Serial.print("Attempting to register "); Serial.print(serviceName); Serial.print(":"); Serial.println(port);
        Serial.print("Connecting client to "); Serial.print(networkServiceIP); Serial.print(":"); Serial.println(networkServicePort);
    }

    do{
        client.connect(networkServiceIP, networkServicePort);
        if(!client.connected()){
            if(trace)Serial.println("Failed to connect ...retrying...");
            delay(1000);
        }
    } while (!client.connected() || (timeout > 0 && millis() - started < timeout));

    if(!client.connected()){
        if(trace)Serial.println("Failed to connect!");
        return 0;
    } else {
        if(trace)Serial.println("Client connected!");
    }

    //registration data to send
    char buf[128];
    sprintf(buf, "{\"service_name\": \"%s\",\"endpoint_port\":%d,\"protocols\":\"tcp\"}", serviceName, port);
    int statusCode = 0; //status code of response
        
    do{ 
        if(trace)Serial.println("Sending http request to newtwork service server...");
        //formulate HTTP request
        client.println("PUT /api/service HTTP/1.1");
        client.print("Host: "); client.println(networkServiceIP);
        client.println("Content-Type: application/json");
        client.print("Content-Length: ");
        client.println(strlen(buf));
        client.println();
        client.println(buf);
        client.println();

        //wait for response
        int started = -1;
        while(client.connected() ||  (timeout > 0 && millis() - started < timeout)){
            if(client.available()){
                char c = client.read();
                if(c == ' '){
                    started = 2;
                    continue;
                }
                if(started >= 0){
                    int n = (c - 48) * (started == 2 ? 100 : (started == 1 ? 10 : 1));
                    started--;
                    statusCode += n;
                    if(started < 0){
                        break;
                    }
                }
            } // end available loop
            if(statusCode > 0 && started < 0){
                break;
            }
        } //end while connected

        if(statusCode == 0){
            if(trace)Serial.println("Failed to get status code!");
            delay(1000);
        } else {
            if(trace){
                Serial.print("Received status code: ");
                Serial.println(statusCode);
            }
        }
    } while (statusCode == 0 || (timeout > 0 && millis() - started < timeout));
    
    client.stop();

    return statusCode;
}

} //end namespace