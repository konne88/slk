#include <SPI.h>
#include "mcp2515_can.h"

#define SERIAL Serial

const int SPI_CS_PIN = 9;
mcp2515_can CAN(SPI_CS_PIN);

#define START_MILLIS 2000  // Start button push repeating after 1s
#define END_MILLIS 10000  // End button push repeating after 10s

// #define REPEAT_MILLIS 10000  // Repeat a button push for 30s
#define DELAY_MILLIS 20      // Delay between button push indicator signals is 20ms.

#define ROOF_CAN_ID 0x350
#define ROOF_OPEN_COMMAND 0x40
#define ROOF_CLOSE_COMMAND 0x80

bool isKnownCommand(byte command) {
  return command == ROOF_OPEN_COMMAND || command == ROOF_CLOSE_COMMAND;
}

unsigned long mostRecentRoofButtonPushMillis = 0;
byte mostRecentRoofButtonPushData = 0;

void receive() {
  if (CAN.checkReceive() != CAN_MSGAVAIL) return;
  byte len = 0;
  byte data[8];
  CAN.readMsgBuf(&len, data);
  unsigned long id = CAN.getCanId();

  if (id != ROOF_CAN_ID) return;
  if (len != 1) return;

  byte command = data[0];
  if (!isKnownCommand(command)) return;

  mostRecentRoofButtonPushMillis = millis();
  mostRecentRoofButtonPushData = command;
  SERIAL.print("Roof button was pushed: 0x");
  SERIAL.println(command, 16);
}

unsigned long lastSent = 0;

void send() {
  unsigned long now = millis();

  byte command = mostRecentRoofButtonPushData;
  if (!isKnownCommand(command)) return;
  unsigned long millisSinceButtonPush = now - mostRecentRoofButtonPushMillis;
  if (millisSinceButtonPush < START_MILLIS) return;
  if (millisSinceButtonPush > END_MILLIS) return;
  if (now - lastSent < DELAY_MILLIS) return;

  CAN.sendMsgBuf(ROOF_CAN_ID, CAN_STDID, 1, {command});
  lastSent = now;

  SERIAL.print("sent: 0x");
  SERIAL.print(command, 16);
  SERIAL.print(" at ");
  SERIAL.println(now);
}

typedef struct {
  unsigned long time;
  unsigned long id;
  int len;
  unsigned char data[8];
} frame_t;

frame_t FRAMES[] = {
  {.time=0, .id=0x350, .len=1, .data={0x40}},
};

void alwaysSendOpen() {
  // unsigned long now = millis();
  // if (now - lastSent < DELAY_MILLIS) return;
  // CAN.sendMsgBuf(ROOF_CAN_ID, CAN_STDID, 1, {ROOF_OPEN_COMMAND});
  // lastSent = now;
  // SERIAL.println("sending open");


    // send every 20 ms
  if (millis() - lastSent < 20) return;
  lastSent = millis();

  for (int i = 0; i < sizeof(FRAMES) / sizeof(frame_t); i++) {
    CAN.sendMsgBuf(FRAMES[i].id, CAN_STDID, FRAMES[i].len, FRAMES[i].data);
    SERIAL.print("send ");
    SERIAL.println(millis());
  }
}

void setup() {
  SERIAL.begin(115200);
  while (!Serial) {};

  while (CAN_OK != CAN.begin(CAN_83K3BPS, MCP_16MHz)) {
    SERIAL.println("CAN BUS Shield init fail");
    delay(1000);
  }
  SERIAL.println("CAN BUS Shield init ok!");
}

void loop() {
  // receive();
//  send();
  alwaysSendOpen();
}