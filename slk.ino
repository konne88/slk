#include <SPI.h>
#include "mcp2515_can.h"

#define SERIAL Serial

const int SPI_CS_PIN = 9;
mcp2515_can CAN(SPI_CS_PIN);

#define START_MILLIS 1000   // Start button push repeating after 1s
#define END_MILLIS 30000    // End button push repeating after 30s
#define DELAY_MILLIS 20     // Delay between button push indicator signals is 20ms.

#define ROOF_CAN_ID 0x350
#define ROOF_OPEN_COMMAND 0x40
#define ROOF_CLOSE_COMMAND 0x80

bool isKnownCommand(byte command) {
  return command == ROOF_OPEN_COMMAND || command == ROOF_CLOSE_COMMAND;
}

unsigned long millisSince(unsigned long time) {
  return millis() - time;
}

unsigned long lastButtonPushMillis = 0;
byte lastButtonPushCommand = 0;

void receive() {
  if (CAN.checkReceive() != CAN_MSGAVAIL) return;
  byte len = 0;
  byte data[8];
  CAN.readMsgBuf(&len, data);
  unsigned long id = CAN.getCanId();

  if (id != ROOF_CAN_ID || len != 1) return;
  byte command = data[0];
  if (!isKnownCommand(command)) return;

  lastButtonPushMillis = millis();
  lastButtonPushCommand = command;
  SERIAL.print("Roof button was pushed: 0x");
  SERIAL.println(command, 16);
}

unsigned long lastSent = 0;

void send() {
  byte command = lastButtonPushCommand;
  if (!isKnownCommand(command)) return;
  if (millisSince(lastButtonPushMillis) < START_MILLIS) return;
  if (millisSince(lastButtonPushMillis) > END_MILLIS) return;
  if (millisSince(lastSent) < DELAY_MILLIS) return;

  CAN.sendMsgBuf(ROOF_CAN_ID, CAN_STDID, 1, &command);
  lastSent = millis();

  SERIAL.print("sent: 0x");
  SERIAL.print(command, 16);
  SERIAL.print(" at ");
  SERIAL.println(lastSent);
}

void setup() {
  SERIAL.begin(115200);
  while (!Serial) {};

  while (CAN_OK != CAN.begin(CAN_83K3BPS, MCP_16MHz)) {
    SERIAL.println("CAN BUS Shield init fail");
    delay(1000);
  }
  SERIAL.println("Setup ok");
}

void loop() {
  receive();
  send();
}