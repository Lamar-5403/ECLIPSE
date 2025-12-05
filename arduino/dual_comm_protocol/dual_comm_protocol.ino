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
    if (c == '\n') break;  // Stop at newline
    buffer[idx++] = c;
  }
  buffer[idx] = '\0';  // Ensure string is properly terminated
}

// Message type architecture
typedef enum {
    MSG_ARM              = 0x01,
    MSG_DISARM           = 0x02,
    MSG_STATUS_REQUEST   = 0x03,
    MSG_STATUS_RESPONSE  = 0x04,
    MSG_ERROR            = 0x05,
    MSG_HEARTBEAT        = 0x06
} msg_type_t;


// Structure of frame for payload transport
typedef struct __attribute__((packed)) {
  uint8_t start;
  uint8_t type;
  uint8_t len;
  uint8_t payload[256];  // Fixed length, traversed to len;
  uint16_t crc;
} frame_t;

// Enum for finite state machine for parsing 
enum State {
  WAIT_START,
  READ_TYPE,
  READ_LEN,
  READ_PAYLOAD,
  READ_CRC
};

// FSM Enum for system
typedef enum {
  SYS_SAFE,
  SYS_ARMING,
  SYS_ARMED,
  SYS_DISARMED,
  SYS_LOCKOUT
} system_state_t;





















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

  // Wait for connection
  unsigned long startTime = millis();
  unsigned long lastCheck = 0;

  while (WiFi.status() != WL_CONNECTED) {

    unsigned long now = millis();

    if (now - startTime >= 10000) {
      Serial.println("Could not connect to network.");
      exit(1);
    } else if (now - lastCheck >= 250) {
      lastCheck = now;
      Serial.println(WiFi.status());
    }
  }

  Serial.println("Connected.");
}

void loop() {
  // Placeholder for main program logic
}
