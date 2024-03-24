#include <SPI.h>
#include "mcp2515_can.h"

/*SAMD core*/
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
#define SERIAL SerialUSB
#else
#define SERIAL Serial
#endif

const int SPI_CS_PIN = 9;
mcp2515_can CAN(SPI_CS_PIN);  // Set CS pin

void setup() {
  SERIAL.begin(115200);
  // SERIAL.begin(9600);

  while (!Serial) {};

  // The only thing I see is 1A4

  while (CAN_OK != CAN.begin(CAN_83K3BPS, MCP_16MHz)) {  // init can bus : baudrate = 500k
    SERIAL.println("CAN BUS Shield init fail");
    SERIAL.println("Init CAN BUS Shield again");
    delay(100);
  }
  //  SERIAL.print(speed);
  SERIAL.println("CAN BUS Shield init ok!");

  CAN.init_Mask(0, 0, 0x07FF); // xffffffff);
  CAN.init_Mask(1, 0, 0x07FF);

  CAN.init_Filt(0, 0, 0x0762);
  CAN.init_Filt(1, 0, 0x0762);
  CAN.init_Filt(2, 0, 0x0762);
  CAN.init_Filt(3, 0, 0x0762);
  CAN.init_Filt(4, 0, 0x0762);
  CAN.init_Filt(5, 0, 0x0762);

  // pinMode(LED_BUILTIN, OUTPUT);
}

typedef struct {
  unsigned long id;
  int len;
  unsigned char data[8];
} frame_t;

frame_t FRAMES[] = {
 {.id=0x10, .len=2,.data={0x30, 0x1}},
 {.id=0x350, .len=2,.data={0x40, 0x1}},
};

/*
  // ======= push unlock key fob

  // 0: 0 0 FF 0 0 0
  { .id = 0, .len = 6, .data = { 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0 } },

  // 22: 77
  // 22: 78
  // (already below)

  // 4: 0 0 1 0 0 FF 0
  // 4: 0 4 1 0 0 FF 0
  // 4: 1 0 1 0 0 FF 0

  { .id = 4, .len = 7, .data = { 0x0, 0x0, 0x1, 0x0, 0x0, 0xFF, 0x0 } },
  { .id = 4, .len = 7, .data = { 0x0, 0x4, 0x1, 0x0, 0x0, 0xFF, 0x0 } },
  { .id = 4, .len = 7, .data = { 0x1, 0x0, 0x1, 0x0, 0x0, 0xFF, 0x0 } },

  // ======= push open-the-roof button on the inside

  //      0:                        F    0    60    58    B2    39
  { .id = 0, .len = 6, .data = { 0x0F, 0x0, 0x6B, 0x5F, 0xB2, 0x39 } },

  //      4:                      0    0    1    F    0    60    58
  { .id = 4, .len = 7, .data = { 0x0, 0x0, 0x1, 0xF, 0x0, 0x6B, 0x5F } },
  //      4:                      0    4    1    F    0    60    58
  { .id = 4, .len = 7, .data = { 0x0, 0x4, 0x1, 0xF, 0x0, 0x6C, 0x60 } },

  { .id = 22, .len = 1, .data = { 0x73 } },
  { .id = 22, .len = 1, .data = { 0x74 } },
  { .id = 22, .len = 1, .data = { 0x75 } },
  { .id = 22, .len = 1, .data = { 0x76 } },
  // 22:                            77             (happened in both)
  { .id = 22, .len = 1, .data = { 0x77 } },
  { .id = 22, .len = 1, .data = { 0x78 } },

  // 512: 0 C 0 0 0 0 FB E0
  // 520: 0 20 0 0 0 14 0 0
  // 520: 0 20 0 1 0 74 0 0
  // 520: 0 20 0 2 0 50 0 0
  { .id = 520, .len = 8, .data = { 0x0, 0x20, 0x0, 0x7, 0x2, 0x18, 0x0, 0x0 } },

  //      1023:                       3B    38    72 64 7 FF FF 8A
  //      1023:                       3B    38    72 64 8 FF FF 8A
  { .id = 1023, .len = 8, .data = { 0x3B, 0x38, 0x75, 0x64, 0x3A, 0xFF, 0xFF, 0x8A } },
  { .id = 1023, .len = 8, .data = { 0x3B, 0x38, 0x75, 0x64, 0x3A, 0xFF, 0xFF, 0xFF } },
  { .id = 1023, .len = 8, .data = { 0x3B, 0x38, 0x75, 0x64, 0x3B, 0xFF, 0xFF, 0x8A } },
};
*/

// unsigned long i = 0;

void loop() {
  // if (i % 100000 == 0) {
  //   int speed = i / 100000;

  // }
  // ++i;

  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    byte len = 0;
    byte buf[8];

    // read data,  len: data length, buf: data buf
    // SERIAL.println("checkReceive");
    CAN.readMsgBuf(&len, buf);

    unsigned long id = CAN.getCanId();
    SERIAL.print(id);
    SERIAL.print(": ");

    // print the data
    for (int i = 0; i < len; i++) {
      SERIAL.print(buf[i], 16);
      SERIAL.print(" ");
    }
    SERIAL.println("");
  }

  // for (int i = 0; i < sizeof(FRAMES) / sizeof(frame_t); i++) {
  //   CAN.sendMsgBuf(FRAMES[i].id, 0, FRAMES[i].len, FRAMES[i].data);
  // }
  // SERIAL.println("send");
  // delay(100);  // send data per 100ms
}