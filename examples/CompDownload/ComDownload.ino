#include "NexDownload.h"
NexDownload nex_download("nex.tft",10,115200);
void setup() {
  // put your setup code here, to run once:
    nex_download.startDownload();
}

void loop() {
  // put your main code here, to run repeatedly:
}
