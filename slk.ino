#include <SPI.h>
#include "mcp2515_can.h"

#define SERIAL Serial

const int SPI_CS_PIN = 9;
mcp2515_can CAN(SPI_CS_PIN);

bool IS_BASELINE_ID[2048];

unsigned long BASELINE_IDS[] = {
    0, 2, 3, 4, 6, 8, 10, 11, 12, 18,
    20, 22, 23, 24, 25, 30, 31, 44, 48, 56,
    88, 112, 144, 154, 156, 158, 178, 241, 384, 396,
    404, 416, 417, 420, 428, 434, 438, 444, 464, 528,
    546, 576, 624, 648, 676, 716, 724, 728, 767, 774,
    818, 992, 993, 1024, 1026, 1027, 1028, 1029, 1031, 1032,
    1033, 1034, 1036, 1037, 1041, 1044, 1045, 1048, 1051, 1052,
    1062, 1890, 1986, 1987, 2012
};

void setupBaseline() {
  for (int i = 0; i < sizeof(BASELINE_IDS) / sizeof(unsigned long); ++i) {
    IS_BASELINE_ID[BASELINE_IDS[i]] = true;
  }
}

void setup() {
  setupBaseline();

  SERIAL.begin(115200);
  while (!Serial) {};

  while (CAN_OK != CAN.begin(CAN_83K3BPS, MCP_16MHz)) {
    SERIAL.println("CAN BUS Shield init fail");
    delay(1000);
  }
  SERIAL.println("CAN BUS Shield init ok!");
}

typedef struct {
  unsigned long time;
  unsigned long id;
  int len;
  unsigned char data[8];
} frame_t;

frame_t FRAMES[] = {
  {.time=0, .id=0x10, .len=1, .data={0x30}},
};

frame_t REPLAY[] = {
  {.time=0, .id=0x10, .len=1, .data={0x30}},
  {.time=100, .id=0x10, .len=1, .data={0x30}},
  {.time=200, .id=0x10, .len=1, .data={0x30}},
  {.time=300, .id=0x10, .len=1, .data={0x30}},
  {.time=400, .id=0x10, .len=1, .data={0x30}},
  {.time=500, .id=0x10, .len=1, .data={0x30}},


  {.time=4028, .id=0x44, .len=4, .data={0x0, 0x0, 0x1, 0x0}},
  {.time=4042, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40}},
  {.time=4048, .id=0x44, .len=4, .data={0x0, 0x1, 0x1, 0x0}},
  {.time=4051, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40}},
  {.time=4062, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40}},
  {.time=4069, .id=0x44, .len=4, .data={0x0, 0x1, 0x1, 0x0}},
  {.time=4088, .id=0x44, .len=4, .data={0x0, 0x1, 0x1, 0x0}},
  {.time=4109, .id=0x44, .len=4, .data={0x0, 0x1, 0x1, 0x0}},
  {.time=4128, .id=0x44, .len=4, .data={0x0, 0x1, 0x1, 0x0}},
  {.time=4149, .id=0x44, .len=4, .data={0x0, 0x1, 0x1, 0x0}},
  {.time=4168, .id=0x44, .len=4, .data={0x0, 0x1, 0x1, 0x0}},
  {.time=4192, .id=0x44, .len=4, .data={0x0, 0x1, 0x1, 0x0}},
  {.time=4208, .id=0x44, .len=4, .data={0x0, 0x1, 0x1, 0x0}},
  {.time=4229, .id=0x44, .len=4, .data={0x0, 0x1, 0x1, 0x0}},
  {.time=4249, .id=0x44, .len=4, .data={0x0, 0x1, 0x1, 0x0}},
  {.time=4269, .id=0x44, .len=4, .data={0x0, 0x1, 0x0, 0x0}},
  {.time=4282, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}},
  {.time=4288, .id=0x44, .len=4, .data={0x0, 0x1, 0x0, 0x0}},
  {.time=4298, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}},
  {.time=4301, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}},
  {.time=4308, .id=0x44, .len=4, .data={0x0, 0x1, 0x0, 0x0}},
  {.time=4313, .id=0x44, .len=4, .data={0x0, 0x0, 0x0, 0x0}},
  {.time=4556, .id=0x44, .len=4, .data={0x0, 0x0, 0x4, 0x0}},
  {.time=4562, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20}},
  {.time=4573, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20}},
  {.time=4577, .id=0x44, .len=4, .data={0x0, 0x1, 0x4, 0x0}},
  {.time=4583, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20}},
  {.time=4596, .id=0x44, .len=4, .data={0x0, 0x1, 0x4, 0x0}},
  {.time=4617, .id=0x44, .len=4, .data={0x0, 0x1, 0x4, 0x0}},
  {.time=4636, .id=0x44, .len=4, .data={0x0, 0x1, 0x4, 0x0}},
  {.time=4657, .id=0x44, .len=4, .data={0x0, 0x1, 0x4, 0x0}},
  {.time=4676, .id=0x44, .len=4, .data={0x0, 0x1, 0x0, 0x0}},
  {.time=4681, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}},
  {.time=4697, .id=0x44, .len=4, .data={0x0, 0x1, 0x0, 0x0}},
  {.time=4707, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}},
  {.time=4709, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}},
  {.time=4716, .id=0x44, .len=4, .data={0x0, 0x1, 0x0, 0x0}},
  {.time=4722, .id=0x44, .len=4, .data={0x0, 0x0, 0x0, 0x0}},
};

void printAsStruct(unsigned long id, byte len, byte* data) {
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


void printSimply(unsigned long id, byte len, byte* data) {
  SERIAL.print(id);
  SERIAL.print(":");
  for (int i = 0; i < len; ++i) {
    SERIAL.print(" ");
    SERIAL.print(data[i], 16);
  }
  SERIAL.print("\n");
}

void receive() {
  if (CAN.checkReceive() != CAN_MSGAVAIL) return;
  byte len = 0;
  byte data[8];
  CAN.readMsgBuf(&len, data);
  unsigned long id = CAN.getCanId();

  if (IS_BASELINE_ID[id]) return;
  
  // printAsStruct(id, len, data);
  printAsStruct(id, len, data);
}

unsigned long REPLAY_INDEX = 0;

void replay() {
  if (REPLAY_INDEX >= sizeof(REPLAY) / sizeof(frame_t)) return;
  if (millis() < REPLAY[REPLAY_INDEX].time) return;

  CAN.sendMsgBuf(REPLAY[REPLAY_INDEX].id, CAN_STDID, REPLAY[REPLAY_INDEX].len, REPLAY[REPLAY_INDEX].data);
  SERIAL.print("replayed ");
  SERIAL.println(REPLAY_INDEX);
  ++REPLAY_INDEX;
}

void send() {
  if (millis() % 100 != 0) return;

  for (int i = 0; i < sizeof(FRAMES) / sizeof(frame_t); i++) {
    CAN.sendMsgBuf(FRAMES[i].id, CAN_STDID, FRAMES[i].len, FRAMES[i].data);
    SERIAL.print("send ");
    SERIAL.println(i);
  }
}

void loop() {
  receive();
  // replay();
  // send();
}