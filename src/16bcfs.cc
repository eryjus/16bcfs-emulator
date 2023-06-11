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
    case 0x000:     /* NOP */
        // Do Nothing!

        if (irSuppress) {
            UI->AppendHistory("NOP (IR Suppress)\n");
            irSuppress = false;
        } else if (unlikely(firstInstr)) {
            UI->AppendHistory("NOP (First Instruction)\n");
            firstInstr = false;
        } else {
            UI->AppendHistory("NOP\n");
        }

        break;

    case 0x013:     /* MOV R1,<imm16> */
        UI->AppendHistory("MOV R1,%04.4X\n", CPU->fetch.Value());

        r1 = fetch;
        fetch = 0;
        irSuppress = true;
        break;

    case 0x020:     /* CLC */
        UI->AppendHistory("CLC\n");

        c = false;
        break;

    case 0x030:     /* STC */
        UI->AppendHistory("STC\n");

        c = true;
        break;

    case 0x040:     /* MOV R1,PC */
        UI->AppendHistory("MOV R1,PC\n");

        r1 = pc;
        break;

    case 0xff3:     /* JMP <imm16> */
        UI->AppendHistory("JMP %04.4X\n", CPU->fetch.Value());

        pc = fetch;
        fetch = 0;
        irSuppress = true;
        return false;

    default:
        UI->AppendHistory("Unimplemented OpCode: 0x%x%03.3x\n", cond, opcode);
    }

    return true;
}


//
// -- Start the CPU Emulation
//    -----------------------
void CPU_t::Emulate(void) 
{
    int ch;

    while ((ch = getch()) != ' ' && ch != 'q') {}
    if (ch == 'q') return;

    while (true) {
        // -- right now, the hardware only has 6 address lines hooked up; emulate that here
        if (pc.Value() >= 64) {
            pc = 0;
            CPU->UpdateUI();
        }

        ch = getch();
        if (ch == 'q') return;

        if (ch > 255) {
            mvprintw(26, 3, "Found an upper-byte control code: %d\n", ch);
        }


        instruction = fetch;
        fetch = memory[pc.Value()];
        CPU->UpdateUI();

        uint16_t instr = instruction.Value();
        uint16_t cond = (instr >> 12) & 0xf;
        uint16_t opcode = instr & 0xfff;

        bool inc = Emulate(cond, opcode);
        if (inc) pc.Inc();
        CPU->UpdateUI();
    }
}



//
// -- Update the whole computer contents on screen
//    --------------------------------------------
void CPU_t::UpdateUI(void)
{
    wrefresh(UI->Hist());
    r1.Draw();
    pc.Draw();
    fetch.Draw();
    instruction.Draw();
    c.Draw();
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
    UI;         // first call to UI->Get; for it to be initialiZed
    CPU->Emulate();

    endwin();
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



