#include "NexVar.h"

NexVar nex_sel0  = NexVar(0, 1, "sel0");

int sel0;

NexTouch *nexListenList[] = 
{
   
    NULL
};


void setup() {
  
  dbSerial.begin(9600);
  nexInit();
     
  dbSerial.println("setup done");

}

void loop() {
  
   delay(500);
   
   uint32_t number = 0;
   nex_sel0.getValue(&number);
   
   sel0 = number;
   
   dbSerial.println(sel0);
   
   
   nexLoop(nexListenList);

}
