#include <WiFi.h>

// Buffers for WiFi credentials; fixed size to avoid dynamic allocation and reduce memory fragmentation
char ssid[64];
char password[64];  

// Read a line of input from the serial interface safely into a fixed-size buffer
// Stops at newline or when buffer is full, ensures null-termination
void readLine(char* buffer, size_t maxLen) {
    size_t idx = 0;
    while (idx < maxLen - 1) {
        while (Serial.available() == 0) {}  // Wait for incoming character
        char c = Serial.read();
        if (c == '\n') break;               // Stop at newline
        buffer[idx++] = c;
    }
    buffer[idx] = '\0';                     // Ensure string is properly terminated
}

void setup() {
    Serial.begin(115200);

    // Short delay to ensure host system enumerates USB serial interface
    // Blocking is acceptable here since setup is single-use
    delay(2000);

    Serial.println("Enter SSID: ");
    Serial.flush();  
    readLine(ssid, sizeof(ssid));

    Serial.println("Enter Password: ");
    Serial.flush();
    readLine(password, sizeof(password));

    // Connect to WiFi using provided credentials
    // In production, consider secure storage instead of plain text input
    WiFi.begin(ssid, password);

    // Wait for connection; in a more advanced system, replace blocking with non-blocking check
    while (WiFi.status() != WL_CONNECTED) {
        delay(250);
    }

    Serial.println("Connected.");
}

void loop() {
    // Placeholder for main program logic
}
