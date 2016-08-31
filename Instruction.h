#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "Common.h"


class Instruction { // abstract base class
    public:
        static  bool           isDriveInstruction      (instrTypesEnum instrType);
        static  bool           isFlushInstruction      (instrTypesEnum instrType);
        static  bool           isMeeInstruction        (instrTypesEnum instrType);
        static bool            isObjectInstruction     (instrTypesEnum instrType);
        static  instrTypesEnum getInstrType            (char instructionString[]);
        static  Instruction    *parseInstruction       (char instructionString[]);
        char                   getId                   (void);
        Instruction             (void);
        void           doExecute               (void);
        void           test                     ();
    protected:
        char _id;
        virtual void           execute                 () =0 ; // pure virutal function, no definition
                void           done                    (void);
        char           obtainId                (char* iString);

        instrTypesEnum _instrType;
        // time created etc
};

#endif
