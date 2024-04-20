#include <SPI.h>
#include "mcp2515_can.h"

#define SERIAL Serial

const int SPI_CS_PIN = 9;
mcp2515_can CAN(SPI_CS_PIN);

void setup() {
  SERIAL.begin(115200);
  while (!Serial) {};

  while (CAN_OK != CAN.begin(CAN_83K3BPS, MCP_16MHz)) {
    SERIAL.println("CAN BUS Shield init fail");
    delay(1000);
  }
  SERIAL.println("CAN BUS Shield init ok!");
}

typedef struct {
  unsigned long id;
  int len;
  unsigned char data[8];
} frame_t;

frame_t FRAMES[] = {
  // Window operation.
  // id = 0x10, len = 1
  // data = 0b0001   -- activate left window
  //        0b0010   -- activate right window
  {.id=0x10, .len=1, .data={0x30}},
};

unsigned long i = 0;

void printMessage(unsigned long id, byte len, byte* data) {
  SERIAL.print("{.time=");
  SERIAL.print(millis());
  SERIAL.print(", .id=0x");
  SERIAL.print(id, 16);
  SERIAL.print(", .len=");
  SERIAL.print(len);
  SERIAL.print(", .data={");
  for (int i = 0; i < len; ++i) {
    if (i != 0) SERIAL.print(", ");
    SERIAL.print("0x");
    SERIAL.print(data[i], 16);
  }
  SERIAL.print("}},\n");
}

void receive() {
  if (CAN.checkReceive() != CAN_MSGAVAIL) return;
  byte len = 0;
  byte data[8];
  CAN.readMsgBuf(&len, data);
  unsigned long id = CAN.getCanId();
  printMessage(id, len, data);
}

void send() {
  for (int i = 0; i < sizeof(FRAMES) / sizeof(frame_t); i++) {
    CAN.sendMsgBuf(FRAMES[i].id, CAN_STDID, FRAMES[i].len, FRAMES[i].data); 
    SERIAL.print("send ");
    SERIAL.println(i);
  }
}

void loop() {
  receive();
  if (++i % 10000 == 0) send();
}