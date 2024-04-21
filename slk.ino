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

typedef struct {
  unsigned long time;
  unsigned long id;
  int len;
  unsigned char data[8];
} frame_t;

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

frame_t REPLAY[] = {
  {.time=6323, .id=0x350, .len=1, .data={0x40}},
  {.time=6342, .id=0x350, .len=1, .data={0x40}},
  {.time=6363, .id=0x350, .len=1, .data={0x40}},
  {.time=6383, .id=0x350, .len=1, .data={0x40}},
  {.time=6406, .id=0x350, .len=1, .data={0x40}},
  {.time=6422, .id=0x350, .len=1, .data={0x40}},
  {.time=6443, .id=0x350, .len=1, .data={0x40}},
  {.time=6462, .id=0x350, .len=1, .data={0x40}},
  {.time=6482, .id=0x350, .len=1, .data={0x40}},
  {.time=6505, .id=0x350, .len=1, .data={0x40}},
  {.time=6523, .id=0x350, .len=1, .data={0x40}},
  {.time=6545, .id=0x350, .len=1, .data={0x40}},
  {.time=6562, .id=0x350, .len=1, .data={0x40}},
  {.time=6583, .id=0x350, .len=1, .data={0x40}},
  {.time=6605, .id=0x350, .len=1, .data={0x40}},
  {.time=6623, .id=0x350, .len=1, .data={0x40}},
  {.time=6643, .id=0x350, .len=1, .data={0x40}},
  {.time=6663, .id=0x350, .len=1, .data={0x40}},
  {.time=6682, .id=0x350, .len=1, .data={0x40}},
  {.time=6705, .id=0x350, .len=1, .data={0x40}},
  {.time=6722, .id=0x350, .len=1, .data={0x40}},
  {.time=6744, .id=0x350, .len=1, .data={0x40}},
  {.time=6762, .id=0x350, .len=1, .data={0x40}},
  {.time=6782, .id=0x350, .len=1, .data={0x40}},
  {.time=6805, .id=0x350, .len=1, .data={0x40}},
  {.time=6823, .id=0x350, .len=1, .data={0x40}},
  {.time=6844, .id=0x350, .len=1, .data={0x40}},
  {.time=6864, .id=0x350, .len=1, .data={0x40}},
  {.time=6882, .id=0x350, .len=1, .data={0x40}},
  {.time=6904, .id=0x350, .len=1, .data={0x40}},
  {.time=6923, .id=0x350, .len=1, .data={0x40}},
  {.time=6943, .id=0x350, .len=1, .data={0x40}},
  {.time=6963, .id=0x350, .len=1, .data={0x40}},
  {.time=6982, .id=0x350, .len=1, .data={0x40}},
  {.time=7006, .id=0x350, .len=1, .data={0x40}},
  {.time=7023, .id=0x350, .len=1, .data={0x40}},
  {.time=7044, .id=0x350, .len=1, .data={0x40}},
  {.time=7063, .id=0x350, .len=1, .data={0x40}},
  {.time=7083, .id=0x350, .len=1, .data={0x40}},
  {.time=7104, .id=0x350, .len=1, .data={0x40}},
  {.time=7122, .id=0x350, .len=1, .data={0x40}},
  {.time=7142, .id=0x10, .len=1, .data={0x10}},
  {.time=7144, .id=0x350, .len=1, .data={0x40}},
  {.time=7158, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40}},
  {.time=7161, .id=0x10, .len=1, .data={0x10}},
  {.time=7164, .id=0x350, .len=1, .data={0x40}},
  {.time=7169, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40}},
  {.time=7178, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40}},
  {.time=7183, .id=0x350, .len=1, .data={0x40}},
  {.time=7203, .id=0x10, .len=1, .data={0x10}},
  {.time=7205, .id=0x350, .len=1, .data={0x40}},
  {.time=7222, .id=0x10, .len=1, .data={0x30}},
  {.time=7223, .id=0x350, .len=1, .data={0x40}},
  {.time=7235, .id=0x7CA, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40}},
  {.time=7242, .id=0x10, .len=1, .data={0x30}},
  {.time=7244, .id=0x350, .len=1, .data={0x40}},
  {.time=7245, .id=0x7CA, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40}},
  {.time=7262, .id=0x10, .len=1, .data={0x30}},
  {.time=7264, .id=0x7CA, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40}},
  {.time=7268, .id=0x350, .len=1, .data={0x40}},
  {.time=7281, .id=0x10, .len=1, .data={0x30}},
  {.time=7282, .id=0x350, .len=1, .data={0x40}},
  {.time=7305, .id=0x10, .len=1, .data={0xB0}},
  {.time=7306, .id=0x350, .len=1, .data={0x40}},
  {.time=7321, .id=0x10, .len=1, .data={0xB0}},
  {.time=7322, .id=0x350, .len=1, .data={0x40}},
  {.time=7342, .id=0x10, .len=1, .data={0xB0}},
  {.time=7344, .id=0x350, .len=1, .data={0x40}},
  {.time=7362, .id=0x10, .len=1, .data={0xB0}},
  {.time=7363, .id=0x350, .len=1, .data={0x40}},
  {.time=7382, .id=0x10, .len=1, .data={0xF0}},
  {.time=7383, .id=0x350, .len=1, .data={0x40}},
  {.time=7404, .id=0x10, .len=1, .data={0xF0}},
  {.time=7405, .id=0x350, .len=1, .data={0x40}},
  {.time=7421, .id=0x10, .len=1, .data={0xF0}},
  {.time=7422, .id=0x350, .len=1, .data={0x40}},
  {.time=7442, .id=0x10, .len=1, .data={0xF0}},
  {.time=7444, .id=0x350, .len=1, .data={0x40}},
  {.time=7461, .id=0x10, .len=1, .data={0xF0}},
  {.time=7462, .id=0x350, .len=1, .data={0x40}},
  {.time=7481, .id=0x10, .len=1, .data={0xF0}},
  {.time=7483, .id=0x350, .len=1, .data={0x40}},
  {.time=7504, .id=0x10, .len=1, .data={0xF0}},
  {.time=7505, .id=0x350, .len=1, .data={0x40}},
  {.time=7522, .id=0x10, .len=1, .data={0xF0}},
  {.time=7523, .id=0x350, .len=1, .data={0x40}},
  {.time=7542, .id=0x10, .len=1, .data={0xF0}},
  {.time=7544, .id=0x350, .len=1, .data={0x40}},
  {.time=7561, .id=0x10, .len=1, .data={0xF0}},
  {.time=7564, .id=0x350, .len=1, .data={0x40}},
  {.time=7581, .id=0x10, .len=1, .data={0xF0}},
  {.time=7582, .id=0x350, .len=1, .data={0x40}},
  {.time=7603, .id=0x10, .len=1, .data={0xF0}},
  {.time=7605, .id=0x350, .len=1, .data={0x40}},
  {.time=7621, .id=0x10, .len=1, .data={0xF0}},
  {.time=7622, .id=0x350, .len=1, .data={0x40}},
  {.time=7642, .id=0x10, .len=1, .data={0xF0}},
  {.time=7644, .id=0x350, .len=1, .data={0x40}},
  {.time=7662, .id=0x10, .len=1, .data={0xF0}},
  {.time=7663, .id=0x350, .len=1, .data={0x40}},
  {.time=7682, .id=0x10, .len=1, .data={0xF0}},
  {.time=7683, .id=0x350, .len=1, .data={0x40}},
  {.time=7688, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}},
  {.time=7698, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}},
  {.time=7703, .id=0x10, .len=1, .data={0xF0}},
  {.time=7705, .id=0x350, .len=1, .data={0x40}},
  {.time=7708, .id=0x7C8, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}},
  {.time=7721, .id=0x10, .len=1, .data={0xF0}},
  {.time=7723, .id=0x350, .len=1, .data={0x40}},
  {.time=7742, .id=0x10, .len=1, .data={0xF0}},
  {.time=7744, .id=0x350, .len=1, .data={0x40}},
  {.time=7761, .id=0x10, .len=1, .data={0xF0}},
  {.time=7762, .id=0x350, .len=1, .data={0x40}},
  {.time=7781, .id=0x10, .len=1, .data={0xF0}},
  {.time=7782, .id=0x350, .len=1, .data={0x40}},
  {.time=7804, .id=0x10, .len=1, .data={0xF0}},
  {.time=7805, .id=0x350, .len=1, .data={0x40}},
  {.time=7808, .id=0x7CA, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}},
  {.time=7815, .id=0x7CA, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}},
  {.time=7821, .id=0x10, .len=1, .data={0xF0}},
  {.time=7825, .id=0x350, .len=1, .data={0x40}},
  {.time=7829, .id=0x7CA, .len=8, .data={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}},
  {.time=7841, .id=0x10, .len=1, .data={0xF0}},
  {.time=7843, .id=0x350, .len=1, .data={0x40}},
  {.time=7861, .id=0x10, .len=1, .data={0xF0}},
  {.time=7864, .id=0x350, .len=1, .data={0x40}},
  {.time=7881, .id=0x10, .len=1, .data={0xF0}},
  {.time=7882, .id=0x350, .len=1, .data={0x40}},
  {.time=7904, .id=0x10, .len=1, .data={0xF0}},
  {.time=7905, .id=0x350, .len=1, .data={0x40}},
  {.time=7921, .id=0x10, .len=1, .data={0xF0}},
  {.time=7923, .id=0x350, .len=1, .data={0x40}},
  {.time=7942, .id=0x10, .len=1, .data={0xF0}},
  {.time=7944, .id=0x350, .len=1, .data={0x40}},
  {.time=7961, .id=0x10, .len=1, .data={0xF0}},
  {.time=7962, .id=0x350, .len=1, .data={0x40}},
  {.time=7981, .id=0x10, .len=1, .data={0xF0}},
  {.time=7983, .id=0x350, .len=1, .data={0x40}},
  {.time=8003, .id=0x10, .len=1, .data={0xF0}},
  {.time=8004, .id=0x350, .len=1, .data={0x40}},
  {.time=8022, .id=0x10, .len=1, .data={0xF0}},
  {.time=8023, .id=0x350, .len=1, .data={0x40}},
  {.time=8041, .id=0x10, .len=1, .data={0xF0}},
  {.time=8044, .id=0x350, .len=1, .data={0x40}},
  {.time=8061, .id=0x10, .len=1, .data={0xF0}},
  {.time=8064, .id=0x350, .len=1, .data={0x40}},
  {.time=8081, .id=0x10, .len=1, .data={0xF0}},
  {.time=8082, .id=0x350, .len=1, .data={0x40}},
  {.time=8103, .id=0x10, .len=1, .data={0xF0}},
  {.time=8104, .id=0x350, .len=1, .data={0x40}},
  {.time=8121, .id=0x10, .len=1, .data={0xF0}},
  {.time=8122, .id=0x350, .len=1, .data={0x40}},
  {.time=8141, .id=0x10, .len=1, .data={0xF0}},
  {.time=8143, .id=0x350, .len=1, .data={0x40}},
  {.time=8161, .id=0x10, .len=1, .data={0xF0}},
  {.time=8164, .id=0x350, .len=1, .data={0x40}},
  {.time=8180, .id=0x10, .len=1, .data={0xF0}},
  {.time=8183, .id=0x350, .len=1, .data={0x40}},
  {.time=8204, .id=0x10, .len=1, .data={0xF0}},
  {.time=8206, .id=0x350, .len=1, .data={0x40}},
  {.time=8220, .id=0x10, .len=1, .data={0xF0}},
  {.time=8222, .id=0x350, .len=1, .data={0x40}},
  {.time=8242, .id=0x10, .len=1, .data={0xF0}},
  {.time=8244, .id=0x350, .len=1, .data={0x40}},
  {.time=8261, .id=0x10, .len=1, .data={0xF0}},
  {.time=8262, .id=0x350, .len=1, .data={0x40}},
  {.time=8281, .id=0x10, .len=1, .data={0xF0}},
  {.time=8284, .id=0x350, .len=1, .data={0x40}},
  {.time=8303, .id=0x10, .len=1, .data={0xF0}},
  {.time=8305, .id=0x350, .len=1, .data={0x40}},
  {.time=8321, .id=0x10, .len=1, .data={0xF0}},
  {.time=8323, .id=0x350, .len=1, .data={0x40}},
  {.time=8341, .id=0x10, .len=1, .data={0xF0}},
  {.time=8344, .id=0x350, .len=1, .data={0x40}},
  {.time=8360, .id=0x10, .len=1, .data={0xF0}},
  {.time=8364, .id=0x350, .len=1, .data={0x40}},
  {.time=8380, .id=0x10, .len=1, .data={0xF0}},
  {.time=8382, .id=0x350, .len=1, .data={0x40}},
  {.time=8403, .id=0x10, .len=1, .data={0xF0}},
  {.time=8404, .id=0x350, .len=1, .data={0x40}},
  {.time=8420, .id=0x10, .len=1, .data={0xF0}},
  {.time=8422, .id=0x350, .len=1, .data={0x40}},
  {.time=8441, .id=0x10, .len=1, .data={0xF0}},
  {.time=8443, .id=0x350, .len=1, .data={0x40}},
  {.time=8460, .id=0x10, .len=1, .data={0xF0}},
  {.time=8462, .id=0x350, .len=1, .data={0x40}},
  {.time=8480, .id=0x10, .len=1, .data={0xF0}},
  {.time=8482, .id=0x350, .len=1, .data={0x40}},
  {.time=8503, .id=0x10, .len=1, .data={0xF0}},
  {.time=8504, .id=0x350, .len=1, .data={0x40}},
  {.time=8521, .id=0x10, .len=1, .data={0xF0}},
  {.time=8522, .id=0x350, .len=1, .data={0x40}},
  {.time=8541, .id=0x10, .len=1, .data={0xF0}},
  {.time=8543, .id=0x350, .len=1, .data={0x40}},
  {.time=8560, .id=0x10, .len=1, .data={0xF0}},
  {.time=8562, .id=0x350, .len=1, .data={0x40}},
  {.time=8581, .id=0x10, .len=1, .data={0xF0}},
  {.time=8584, .id=0x350, .len=1, .data={0x40}},
  {.time=8603, .id=0x10, .len=1, .data={0xF0}},
  {.time=8604, .id=0x350, .len=1, .data={0x40}},
  {.time=8621, .id=0x10, .len=1, .data={0xF0}},
  {.time=8623, .id=0x350, .len=1, .data={0x40}},
  {.time=8641, .id=0x10, .len=1, .data={0xF0}},
  {.time=8643, .id=0x350, .len=1, .data={0x40}},
  {.time=8660, .id=0x10, .len=1, .data={0xF0}},
  {.time=8663, .id=0x350, .len=1, .data={0x40}},
  {.time=8680, .id=0x10, .len=1, .data={0xF0}},
  {.time=8682, .id=0x350, .len=1, .data={0x40}},
  {.time=8702, .id=0x10, .len=1, .data={0xF0}},
  {.time=8704, .id=0x350, .len=1, .data={0x40}},
  {.time=8720, .id=0x10, .len=1, .data={0xF0}},
  {.time=8722, .id=0x350, .len=1, .data={0x40}},
  {.time=8740, .id=0x10, .len=1, .data={0xF0}},
  {.time=8742, .id=0x350, .len=1, .data={0x40}},
  {.time=8760, .id=0x10, .len=1, .data={0xF0}},
  {.time=8762, .id=0x350, .len=1, .data={0x40}},
  {.time=8780, .id=0x10, .len=1, .data={0xF0}},
  {.time=8782, .id=0x350, .len=1, .data={0x40}},
  {.time=8803, .id=0x10, .len=1, .data={0xF0}},
  {.time=8804, .id=0x350, .len=1, .data={0x40}},
  {.time=8820, .id=0x10, .len=1, .data={0xF0}},
  {.time=8822, .id=0x350, .len=1, .data={0x40}},
  {.time=8841, .id=0x10, .len=1, .data={0xF0}},
  {.time=8843, .id=0x350, .len=1, .data={0x40}},
  {.time=8861, .id=0x10, .len=1, .data={0xF0}},
  {.time=8862, .id=0x350, .len=1, .data={0x40}},
  {.time=8880, .id=0x10, .len=1, .data={0xF0}},
  {.time=8882, .id=0x350, .len=1, .data={0x40}},
  {.time=8903, .id=0x10, .len=1, .data={0xF0}},
  {.time=8903, .id=0x350, .len=1, .data={0x40}},
  {.time=8920, .id=0x10, .len=1, .data={0xF0}},
  {.time=8923, .id=0x350, .len=1, .data={0x40}},
  {.time=8940, .id=0x10, .len=1, .data={0xF0}},
  {.time=8942, .id=0x350, .len=1, .data={0x40}},
  {.time=8960, .id=0x10, .len=1, .data={0xF0}},
  {.time=8963, .id=0x350, .len=1, .data={0x40}},
  {.time=8980, .id=0x10, .len=1, .data={0xF0}},
  {.time=8982, .id=0x350, .len=1, .data={0x40}},
  {.time=9003, .id=0x10, .len=1, .data={0xF0}},
  {.time=9004, .id=0x350, .len=1, .data={0x40}},
  {.time=9021, .id=0x10, .len=1, .data={0xF0}},
  {.time=9023, .id=0x350, .len=1, .data={0x40}},
  {.time=9040, .id=0x10, .len=1, .data={0xF0}},
  {.time=9042, .id=0x350, .len=1, .data={0x40}},
  {.time=9060, .id=0x10, .len=1, .data={0xF0}},
  {.time=9062, .id=0x350, .len=1, .data={0x40}},
  {.time=9081, .id=0x10, .len=1, .data={0xF0}},
  {.time=9082, .id=0x350, .len=1, .data={0x40}},
  {.time=9103, .id=0x10, .len=1, .data={0xF0}},
  {.time=9103, .id=0x350, .len=1, .data={0x40}},
  {.time=9119, .id=0x10, .len=1, .data={0xF0}},
  {.time=9122, .id=0x350, .len=1, .data={0x40}},
  {.time=9140, .id=0x10, .len=1, .data={0xF0}},
  {.time=9142, .id=0x350, .len=1, .data={0x40}},
  {.time=9159, .id=0x10, .len=1, .data={0xF0}},
  {.time=9162, .id=0x350, .len=1, .data={0x40}},
  {.time=9181, .id=0x10, .len=1, .data={0xF0}},
  {.time=9183, .id=0x350, .len=1, .data={0x40}},
  {.time=9202, .id=0x10, .len=1, .data={0xF0}},
  {.time=9204, .id=0x350, .len=1, .data={0x40}},
  {.time=9220, .id=0x10, .len=1, .data={0xF0}},
  {.time=9223, .id=0x350, .len=1, .data={0x40}},
  {.time=9240, .id=0x10, .len=1, .data={0xF0}},
  {.time=9243, .id=0x350, .len=1, .data={0x40}},
  {.time=9261, .id=0x10, .len=1, .data={0xF0}},
  {.time=9263, .id=0x350, .len=1, .data={0x40}},
  {.time=9281, .id=0x10, .len=1, .data={0xF0}},
  {.time=9283, .id=0x350, .len=1, .data={0x40}},
  {.time=9300, .id=0x10, .len=1, .data={0xF0}},
  {.time=9304, .id=0x350, .len=1, .data={0x40}},
  {.time=9319, .id=0x10, .len=1, .data={0xF0}},
  {.time=9322, .id=0x350, .len=1, .data={0x40}},
  {.time=9339, .id=0x10, .len=1, .data={0xF0}},
  {.time=9342, .id=0x350, .len=1, .data={0x40}},
  {.time=9359, .id=0x10, .len=1, .data={0xF0}},
  {.time=9362, .id=0x350, .len=1, .data={0x40}},
  {.time=9379, .id=0x10, .len=1, .data={0xF0}},
  {.time=9382, .id=0x350, .len=1, .data={0x40}},
  {.time=9402, .id=0x10, .len=1, .data={0xF0}},
  {.time=9403, .id=0x350, .len=1, .data={0x40}},
  {.time=9419, .id=0x10, .len=1, .data={0xF0}},
  {.time=9422, .id=0x350, .len=1, .data={0x40}},
  {.time=9440, .id=0x10, .len=1, .data={0xF0}},
  {.time=9442, .id=0x350, .len=1, .data={0x40}},
  {.time=9459, .id=0x10, .len=1, .data={0xF0}},
  {.time=9463, .id=0x350, .len=1, .data={0x40}},
  {.time=9480, .id=0x10, .len=1, .data={0xF0}},
  {.time=9482, .id=0x350, .len=1, .data={0x40}},
  {.time=9502, .id=0x10, .len=1, .data={0xF0}},
  {.time=9503, .id=0x350, .len=1, .data={0x40}},
  {.time=9520, .id=0x10, .len=1, .data={0xF0}},
  {.time=9522, .id=0x350, .len=1, .data={0x40}},
  {.time=9539, .id=0x10, .len=1, .data={0xF0}},
  {.time=9542, .id=0x350, .len=1, .data={0x40}},
  {.time=9559, .id=0x10, .len=1, .data={0x30}},
  {.time=9563, .id=0x350, .len=1, .data={0x40}},
  {.time=9579, .id=0x10, .len=1, .data={0x30}},
  {.time=9582, .id=0x350, .len=1, .data={0x40}},
  {.time=9602, .id=0x10, .len=1, .data={0x30}},
  {.time=9603, .id=0x350, .len=1, .data={0x40}},
  {.time=9619, .id=0x10, .len=1, .data={0x30}},
  {.time=9622, .id=0x350, .len=1, .data={0x40}},
  {.time=9639, .id=0x10, .len=1, .data={0x30}},
  {.time=9643, .id=0x350, .len=1, .data={0x40}},
  {.time=9659, .id=0x10, .len=1, .data={0x30}},
  {.time=9662, .id=0x350, .len=1, .data={0x40}},
  {.time=9679, .id=0x10, .len=1, .data={0x30}},
  {.time=9683, .id=0x350, .len=1, .data={0x40}},
  {.time=9700, .id=0x10, .len=1, .data={0x30}},
  {.time=9703, .id=0x350, .len=1, .data={0x40}},
  {.time=9719, .id=0x10, .len=1, .data={0x30}},
  {.time=9722, .id=0x350, .len=1, .data={0x40}},
  {.time=9739, .id=0x10, .len=1, .data={0x30}},
  {.time=9742, .id=0x350, .len=1, .data={0x40}},
  {.time=9759, .id=0x10, .len=1, .data={0x30}},
  {.time=9762, .id=0x350, .len=1, .data={0x40}},
  {.time=9779, .id=0x10, .len=1, .data={0x30}},
  {.time=9782, .id=0x350, .len=1, .data={0x40}},
  {.time=9801, .id=0x10, .len=1, .data={0x30}},
  {.time=9802, .id=0x350, .len=1, .data={0x40}},
  {.time=9819, .id=0x10, .len=1, .data={0x30}},
  {.time=9822, .id=0x350, .len=1, .data={0x40}},
  {.time=9839, .id=0x10, .len=1, .data={0x30}},
  {.time=9842, .id=0x350, .len=1, .data={0x40}},
  {.time=9860, .id=0x10, .len=1, .data={0x30}},
  {.time=9862, .id=0x350, .len=1, .data={0x40}},
  {.time=9879, .id=0x10, .len=1, .data={0x30}},
  {.time=9882, .id=0x350, .len=1, .data={0x40}},
  {.time=9902, .id=0x10, .len=1, .data={0x30}},
  {.time=9904, .id=0x350, .len=1, .data={0x40}},
  {.time=9919, .id=0x10, .len=1, .data={0x30}},
  {.time=9922, .id=0x350, .len=1, .data={0x40}},
  {.time=9938, .id=0x10, .len=1, .data={0x30}},
  {.time=9943, .id=0x350, .len=1, .data={0x40}},
  {.time=9959, .id=0x10, .len=1, .data={0x30}},
  {.time=9962, .id=0x350, .len=1, .data={0x40}},
  {.time=9978, .id=0x10, .len=1, .data={0x30}},
  {.time=9982, .id=0x350, .len=1, .data={0x40}},
  {.time=10001, .id=0x10, .len=1, .data={0x30}},
  {.time=10002, .id=0x350, .len=1, .data={0x40}},
  {.time=10019, .id=0x10, .len=1, .data={0x30}},
  {.time=10022, .id=0x350, .len=1, .data={0x40}},
  {.time=10039, .id=0x10, .len=1, .data={0x30}},
  {.time=10042, .id=0x350, .len=1, .data={0x40}},
  {.time=10058, .id=0x10, .len=1, .data={0x30}},
  {.time=10062, .id=0x350, .len=1, .data={0x40}},
  {.time=10079, .id=0x10, .len=1, .data={0x30}},
  {.time=10082, .id=0x350, .len=1, .data={0x40}},
  {.time=10101, .id=0x10, .len=1, .data={0x30}},
  {.time=10102, .id=0x350, .len=1, .data={0x40}},
  {.time=10119, .id=0x10, .len=1, .data={0x30}},
  {.time=10123, .id=0x350, .len=1, .data={0x40}},
  {.time=10138, .id=0x10, .len=1, .data={0x30}},
  {.time=10142, .id=0x350, .len=1, .data={0x40}},
  {.time=10159, .id=0x10, .len=1, .data={0x30}},
  {.time=10162, .id=0x350, .len=1, .data={0x40}},
  {.time=10178, .id=0x10, .len=1, .data={0x30}},
  {.time=10182, .id=0x350, .len=1, .data={0x40}},
  {.time=10201, .id=0x10, .len=1, .data={0x30}},
  {.time=10204, .id=0x350, .len=1, .data={0x40}},
  {.time=10219, .id=0x10, .len=1, .data={0x30}},
  {.time=10222, .id=0x350, .len=1, .data={0x40}},
  {.time=10238, .id=0x10, .len=1, .data={0x30}},
  {.time=10243, .id=0x350, .len=1, .data={0x40}},
  {.time=10259, .id=0x10, .len=1, .data={0x30}},
  {.time=10262, .id=0x350, .len=1, .data={0x40}},
  {.time=10278, .id=0x10, .len=1, .data={0x30}},
  {.time=10283, .id=0x350, .len=1, .data={0x40}},
  {.time=10301, .id=0x10, .len=1, .data={0x30}},
  {.time=10303, .id=0x350, .len=1, .data={0x40}},
  {.time=10318, .id=0x10, .len=1, .data={0x30}},
  {.time=10322, .id=0x350, .len=1, .data={0x40}},
  {.time=10338, .id=0x10, .len=1, .data={0x30}},
  {.time=10343, .id=0x350, .len=1, .data={0x40}},
  {.time=10358, .id=0x10, .len=1, .data={0x30}},
  {.time=10362, .id=0x350, .len=1, .data={0x40}},
  {.time=10378, .id=0x10, .len=1, .data={0x30}},
  {.time=10382, .id=0x350, .len=1, .data={0x40}},
  {.time=10401, .id=0x10, .len=1, .data={0x30}},
  {.time=10402, .id=0x350, .len=1, .data={0x40}},
  {.time=10418, .id=0x10, .len=1, .data={0x30}},
  {.time=10422, .id=0x350, .len=1, .data={0x40}},
  {.time=10438, .id=0x10, .len=1, .data={0x30}},
  {.time=10442, .id=0x350, .len=1, .data={0x40}},
  {.time=10458, .id=0x10, .len=1, .data={0x30}},
  {.time=10462, .id=0x350, .len=1, .data={0x40}},
  {.time=10478, .id=0x10, .len=1, .data={0x30}},
  {.time=10482, .id=0x350, .len=1, .data={0x40}},
  {.time=10501, .id=0x10, .len=1, .data={0x30}},
  {.time=10502, .id=0x350, .len=1, .data={0x40}},
  {.time=10519, .id=0x10, .len=1, .data={0x30}},
  {.time=10522, .id=0x350, .len=1, .data={0x40}},
  {.time=10539, .id=0x10, .len=1, .data={0x30}},
  {.time=10542, .id=0x350, .len=1, .data={0x40}},
  {.time=10558, .id=0x10, .len=1, .data={0x30}},
  {.time=10563, .id=0x350, .len=1, .data={0x40}},
  {.time=10578, .id=0x10, .len=1, .data={0x30}},
  {.time=10583, .id=0x350, .len=1, .data={0x40}},
  {.time=10601, .id=0x10, .len=1, .data={0x30}},
  {.time=10602, .id=0x350, .len=1, .data={0x40}},
  {.time=10618, .id=0x10, .len=1, .data={0x30}},
  {.time=10622, .id=0x350, .len=1, .data={0x40}},
  {.time=10638, .id=0x10, .len=1, .data={0x30}},
  {.time=10642, .id=0x350, .len=1, .data={0x40}},
  {.time=10658, .id=0x10, .len=1, .data={0x30}},
  {.time=10662, .id=0x350, .len=1, .data={0x40}},
  {.time=10678, .id=0x10, .len=1, .data={0x30}},
  {.time=10682, .id=0x350, .len=1, .data={0x40}},
  {.time=10700, .id=0x10, .len=1, .data={0x30}},
  {.time=10702, .id=0x350, .len=1, .data={0x40}},
  {.time=10718, .id=0x10, .len=1, .data={0x30}},
  {.time=10722, .id=0x350, .len=1, .data={0x40}},
  {.time=10738, .id=0x10, .len=1, .data={0x30}},
  {.time=10742, .id=0x350, .len=1, .data={0x40}},
  {.time=10758, .id=0x10, .len=1, .data={0x30}},
  {.time=10762, .id=0x350, .len=1, .data={0x40}},
  {.time=10779, .id=0x10, .len=1, .data={0x30}},
  {.time=10783, .id=0x350, .len=1, .data={0x40}},
  {.time=10801, .id=0x10, .len=1, .data={0x30}},
  {.time=10802, .id=0x350, .len=1, .data={0x40}},
  {.time=10818, .id=0x10, .len=1, .data={0x30}},
  {.time=10822, .id=0x350, .len=1, .data={0x40}},
  {.time=10838, .id=0x10, .len=1, .data={0x30}},
  {.time=10842, .id=0x350, .len=1, .data={0x40}},
  {.time=10859, .id=0x10, .len=1, .data={0x30}},
};

unsigned long REPLAY_INDEX = 0;

void replay() {
  if (REPLAY_INDEX >= sizeof(REPLAY) / sizeof(frame_t)) return;
  if (millis() < REPLAY[REPLAY_INDEX].time) return;

  CAN.sendMsgBuf(REPLAY[REPLAY_INDEX].id, CAN_STDID, REPLAY[REPLAY_INDEX].len, REPLAY[REPLAY_INDEX].data);
  SERIAL.print("replayed ");
  SERIAL.println(REPLAY_INDEX);
  ++REPLAY_INDEX;
}

frame_t FRAMES[] = {
  {.time=0, .id=0x350, .len=1, .data={0x40}},
};

unsigned long LAST_SENT = 0;

void send() {
  // send every 20 ms
  if (millis() - LAST_SENT < 20) return;
  LAST_SENT = millis();

  for (int i = 0; i < sizeof(FRAMES) / sizeof(frame_t); i++) {
    CAN.sendMsgBuf(FRAMES[i].id, CAN_STDID, FRAMES[i].len, FRAMES[i].data);
    SERIAL.print("send ");
    SERIAL.println(millis());
  }
}

void setup() {
  // setupBaseline();

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
  // replay();
  send();
}