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

frame_t REPLAY[] = {
  {.time=0, .id=0x10, .len=1, .data={0x30}},
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

void record() {
  if (CAN.checkReceive() != CAN_MSGAVAIL) return;
  byte len = 0;
  byte data[8];
  CAN.readMsgBuf(&len, data);
  unsigned long id = CAN.getCanId();

  if (IS_BASELINE_ID[id]) return;
  
  // printSimply(id, len, data);
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
