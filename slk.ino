// #include <can-serial.h>
// #include <mcp2515_can.h>
// #include <mcp2515_can_dfs.h>
// #include <mcp2518fd_can.h>
// #include <mcp2518fd_can_dfs.h>
// #include <mcp_can.h>

#include <SPI.h>
// #include "mcp2515_can.h"
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
    delay(1000);
  }
  SERIAL.println("CAN BUS Shield init ok!");

  // CAN.init_Mask(0, 0, 0x07FF); // xffffffff);
  // CAN.init_Mask(1, 0, 0x07FF);

  // CAN.init_Filt(0, 0, 0x0762);
  // CAN.init_Filt(1, 0, 0x0762);
  // CAN.init_Filt(2, 0, 0x0762);
  // CAN.init_Filt(3, 0, 0x0762);
  // CAN.init_Filt(4, 0, 0x0762);
  // CAN.init_Filt(5, 0, 0x0762);

  // pinMode(LED_BUILTIN, OUTPUT);
  // pinMode(5, OUTPUT);
  // SERIAL.println("init done");
}

typedef struct {
  unsigned long id;
  int len;
  unsigned char data[8];
} frame_t;

frame_t FRAMES[] = {
  // {.id=1992, .len=8, .data={0,0,0,0,0,0,0,0}},
  // {.id=1992, .len=8, .data={0,0,0,0,0,0,0,0x40}},
  // {.id=1994, .len=8, .data={0,0,0,0,0,0,0,0}},
  // {.id=1994, .len=8, .data={0,0,0,0,0,0,0,0x40}},
  
    {.id=0x10, .len=1, .data={0x30}},   // left window down   = 0001
//   {.id=0x10, .len=1, .data={0x20}},   // right window down   = 0010


//  { .id=0x10, .len=1, .data={0x30}},   // both windows down  === 0011
//  {.id=0x10, .len=1, .data={0x70}},    // both windows down   == 0111
//  {.id=0x10, .len=1, .data={0xB0}},   // == 1011  // both windows down
  //{.id=0x10, .len=1, .data={0xF0}},   // == 1111, both windows down

//  {.id=0x10, .len=1, .data={0x80}},   // == 0100

// {.id=0x350, .len=2,.data={0x40, 0x1}},
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

unsigned long i = 0;

void loop() {
  // SERIAL.println("on");
  // digitalWrite(5, HIGH); // sets the digital pin 13 on
  // delay(5000);            // waits for a second
  // SERIAL.println("off");
  // digitalWrite(5, LOW);  // sets the digital pin 13 off
  // delay(5000);            // waits for a second

  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    byte len = 0;
    byte buf[8];
    CAN.readMsgBuf(&len, buf);
    unsigned long id = CAN.getCanId();

   // if (id == 11 || id == 16) {
      SERIAL.print(id);
      SERIAL.print(": ");
      for (int i = 0; i < len; i++) {
        SERIAL.print(buf[i], 16);
        SERIAL.print(" ");
      }
      SERIAL.println("");
 //   }
  }

  if (i % 10000 == 0) {
    for (int i = 0; i < sizeof(FRAMES) / sizeof(frame_t); i++) {
      // Remote transmission request (RTR) = 0 (means we're sending a data frame)
      // Identifier extension bit (IDE) = 0 (means we're using an 11 bit identifier)
      CAN.sendMsgBuf(FRAMES[i].id, CAN_STDID, FRAMES[i].len, FRAMES[i].data); 

//      CAN.trySendMsgBuf(FRAMES[i].id, 0, 0, FRAMES[i].len, FRAMES[i].data);
      SERIAL.print("send ");
      SERIAL.println(i);
    }
  }
  ++i;
}