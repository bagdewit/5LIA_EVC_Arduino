#include "Iflush.h"
#include "Common.h"
#include "definitions.cpp"

void iFlush::execute(){
    INFO_FLUSH("FLUSH QUEUE IN PROGRESS");
    
    while (!queue.isEmpty ())
    {
      pQueueInstruction pQnext = queue.peek();
      delete  pQnext.pInstr; // delete the Instruction Object
      
      queue.pop ();
    }

    // TODO: MEMORY LEAK!
};
