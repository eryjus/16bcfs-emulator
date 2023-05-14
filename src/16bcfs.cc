//===================================================================================================================
// 16bcfs.cc -- 16-Bit Computer From Scratch Emulator main entry point with globals
//
//      Copyright (c) 2023 - Adam Clark
//      License: Beerware
//
//  This source file is the main entry point for the emulator.  It also contains all the global variables used
//  in this program.
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2023-May-13  Initial  v0.0.1   Initial Version
//===================================================================================================================


#include "16bcfs.hh"


//
// -- This macro is to help readability in the source code
//    ----------------------------------------------------
#define CPU (CPU_t::Get())


//
// -- Print a value as a binary Number
//    --------------------------------
void CPU_t::PrintBinary(uint16_t v)
{
    printf("%c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c\n",
        v & 0x8000 ? '1' : '0',
        v & 0x4000 ? '1' : '0',
        v & 0x2000 ? '1' : '0',
        v & 0x1000 ? '1' : '0',
        v & 0x0800 ? '1' : '0',
        v & 0x0400 ? '1' : '0',
        v & 0x0200 ? '1' : '0',
        v & 0x0100 ? '1' : '0',
        v & 0x0080 ? '1' : '0',
        v & 0x0040 ? '1' : '0',
        v & 0x0020 ? '1' : '0',
        v & 0x0010 ? '1' : '0',
        v & 0x0008 ? '1' : '0',
        v & 0x0004 ? '1' : '0',
        v & 0x0002 ? '1' : '0',
        v & 0x0001 ? '1' : '0'
    );
}


//
// -- Emulate a single instruction
//    ----------------------------
bool CPU_t::Emulate(uint16_t cond, uint16_t opcode)
{
    switch(opcode) {
    case 0x000:
        // Do Nothing!
        printf("NOP\n");
        break;

    case 0x013:
        r1 = fetch;
        fetch = 0;

        printf("MOV R1,<imm16>\n\tR1 = ");
        PrintBinary(r1.Value());
        break;

    case 0x020:
        c = false;

        printf("CLC\n");
        break;

    case 0x030:
        c = true;

        printf("STC\n");
        break;

    case 0x040:
        r1 = pc;

        printf("MOV R1,PC\n\tR1 = ");
        PrintBinary(r1.Value());
        break;

    case 0xff3:
        pc = fetch;
        fetch = 0;

        printf("JMP <imm16>\tPC = \n");
        PrintBinary(pc.Value());
        return false;

    default:
        fprintf(stderr, "Unimplemented OpCode: 0x%x%x\n", cond, opcode);
    }

    return true;
}


//
// -- Start the CPU Emulation
//    -----------------------
void CPU_t::Emulate(void) 
{
    while (true) {
        instruction = fetch;
        fetch = memory[pc.Value()];

        uint16_t instr = instruction.Value();
        uint16_t cond = (instr >> 12) & 0xf;
        uint16_t opcode = instr & 0xfff;

        bool inc = Emulate(cond, opcode);
        if (inc) pc.Inc();

        usleep(500000);
    }
}





//===================================================================================================================
//===================================================================================================================
//===================================================================================================================


//
// -- Read the program binary
//    -----------------------
void ReadProgram(const char *f)
{
    FILE *fp = fopen(f, "r");
    if (!fp) {
        fprintf(stderr, "Invalid Program Binary\n");
        exit(EXIT_FAILURE);
    }

    fread(memory, sizeof(uint16_t), 64 * 1024, fp);
    fclose(fp);

    for (int i = 0; i < 64 * 1024; i ++) {
        memory[i] = ((memory[i] >> 8) & 0xff) | ((memory[i] & 0xff) << 8);
    }
}


//
// -- Main Entry Point
//    ----------------
int main(int argc, char *argv[]) 
{
    ReadProgram(argv[1]);
    CPU->Emulate();

    return EXIT_SUCCESS;
}



//===================================================================================================================
//===================================================================================================================
//===================================================================================================================



//
// -- Global variables not to be access directly are placed at the bottom of this source file
//    =======================================================================================


//
// -- This is the singleton CPU_t instance.  Access this through `CPU_t::get();`
//    --------------------------------------------------------------------------
CPU_t *CPU_t::singleton = nullptr;


//
// -- This is the memory definition
//    -----------------------------
uint16_t memory[64 * 1024];



