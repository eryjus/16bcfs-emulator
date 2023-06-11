//===================================================================================================================
// ui.cc -- 16-Bit Computer From Scratch Emulator User Interface functions
//
//      Copyright (c) 2023 - Adam Clark
//      License: Beerware
//
//  This source handles all of the ui painting the emulator screen.
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2023-May-14  Initial  v0.0.1   Initial Version
//===================================================================================================================


#include "16bcfs.hh"


//
// -- Set up some minimums
//    --------------------
#define MIN_ROWS 45
#define MIN_COLS 100



//
// -- The single instance of the UI
//    -----------------------------
UI_t *UI_t::singleton = nullptr;



//
// -- output a bit
//    ------------
void UI_t::OutputBit(int y, int x, bool b)
{
    attrset(A_NORMAL);

    if (b) {
        attrset(A_BOLD | COLOR_PAIR(C_BIT_ON));
        mvaddch(y, x, ACS_DIAMOND);
    } else {
        attrset(COLOR_PAIR(C_BIT_OFF));
        mvaddch(y, x, '.');
    }

    attrset(A_NORMAL);
}


//
// -- Output a register contents
//    --------------------------
void UI_t::OutputRegister(int x, int y, uint16_t val)
{
    OutputBit(x, y +  0, val & 0x8000);
    OutputBit(x, y +  1, val & 0x4000);
    OutputBit(x, y +  2, val & 0x2000);
    OutputBit(x, y +  3, val & 0x1000);
    OutputBit(x, y +  5, val & 0x0800);
    OutputBit(x, y +  6, val & 0x0400);
    OutputBit(x, y +  7, val & 0x0200);
    OutputBit(x, y +  8, val & 0x0100);
    OutputBit(x, y + 10, val & 0x0080);
    OutputBit(x, y + 11, val & 0x0040);
    OutputBit(x, y + 12, val & 0x0020);
    OutputBit(x, y + 13, val & 0x0010);
    OutputBit(x, y + 15, val & 0x0008);
    OutputBit(x, y + 16, val & 0x0004);
    OutputBit(x, y + 17, val & 0x0002);
    OutputBit(x, y + 18, val & 0x0001);
    
    mvprintw(x, y + 20, "%04.4X", val);
}



//
// -- Paint the enture window
//    -----------------------
void UI_t::PaintEmulator(void)
{
    if (COLS < MIN_COLS || LINES < MIN_ROWS) {
        attrset(A_BOLD | COLOR_PAIR(C_ERROR));
        mvprintw(0, 0, "MIN: %d X %d", MIN_COLS, MIN_ROWS);

        attrset(A_NORMAL);
        refresh();

        return; 
    }

    attrset(A_NORMAL);
    attrset(A_BOLD);

    //
    // -- Print the border on the screen
    //    ------------------------------
    border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);


    //
    // -- Now add in all the lines to the screen
    //    --------------------------------------
    mvhline(2, 1, ACS_HLINE, COLS - 2);
    mvhline(5, 1, ACS_HLINE, COLS - 2);
    mvhline(25, 1, ACS_HLINE, COLS - 2);

    mvvline(3, 32, ACS_VLINE, 22);
    mvvline(3, 34, ACS_VLINE, 22);
    mvvline(3, 41, ACS_VLINE, 22);

    
    //
    // -- Now fill in all the interseactions as needed
    //    --------------------------------------------
    mvaddch(2, 0, ACS_LTEE);
    mvaddch(2, COLS - 1, ACS_RTEE);
    mvaddch(2, 32, ACS_TTEE);
    mvaddch(2, 34, ACS_TTEE);
    mvaddch(2, 41, ACS_TTEE);

    mvaddch(5, 0, ACS_LTEE);
    mvaddch(5, COLS - 1, ACS_RTEE);
    mvaddch(5, 32, ACS_PLUS);
    mvaddch(5, 34, ACS_PLUS);
    mvaddch(5, 41, ACS_PLUS);

    mvaddch(25, 0, ACS_LTEE);
    mvaddch(25, COLS - 1, ACS_RTEE);
    mvaddch(25, 32, ACS_BTEE);
    mvaddch(25, 34, ACS_BTEE);
    mvaddch(25, 41, ACS_BTEE);

    mvaddch(2, 50, ACS_TTEE);
    mvaddch(3, 50, ACS_VLINE);
    mvaddch(4, 50, ACS_VLINE);
    mvaddch(5, 50, ACS_BTEE);

    mvaddch(2, 54, ACS_TTEE);
    mvaddch(3, 54, ACS_VLINE);
    mvaddch(4, 54, ACS_VLINE);
    mvaddch(5, 54, ACS_BTEE);

    mvaddch(2, 58, ACS_TTEE);
    mvaddch(3, 58, ACS_VLINE);
    mvaddch(4, 58, ACS_VLINE);
    mvaddch(5, 58, ACS_BTEE);

    mvaddch(2, 62, ACS_TTEE);
    mvaddch(3, 62, ACS_VLINE);
    mvaddch(4, 62, ACS_VLINE);
    mvaddch(5, 62, ACS_BTEE);

    mvaddch(2, 66, ACS_TTEE);
    mvaddch(3, 66, ACS_VLINE);
    mvaddch(4, 66, ACS_VLINE);
    mvaddch(5, 66, ACS_BTEE);

    //
    // -- Now, populate all the screen labels
    //    -----------------------------------

    attrset(A_BOLD | COLOR_PAIR(C_TITLE));
    mvprintw(1, (COLS - 37) / 2, "16-Bit Computer From Scratch Emulator");
    mvprintw(3, 2, "General Purpose Registers");
    mvprintw(4, 2, "  & I/O Ports");
    mvprintw(3, 43, "Flags:");
    attrset(A_NORMAL);


    attrset(A_BOLD | COLOR_PAIR(C_LABEL));
    mvprintw( 3, 33, "L");
    mvprintw( 3, 35, "SMAAAA");
    mvprintw( 4, 33, "t");
    mvprintw( 4, 35, "wnAB12");
    mvprintw( 6, 2, " R1: xxxx xxxx xxxx xxxx");
    mvprintw( 7, 2, " R2: xxxx xxxx xxxx xxxx");
    mvprintw( 8, 2, " R3: xxxx xxxx xxxx xxxx");
    mvprintw( 9, 2, " R4: xxxx xxxx xxxx xxxx");
    mvprintw(10, 2, " R5: xxxx xxxx xxxx xxxx");
    mvprintw(11, 2, " R6: xxxx xxxx xxxx xxxx");
    mvprintw(12, 2, " R7: xxxx xxxx xxxx xxxx");
    mvprintw(13, 2, " R8: xxxx xxxx xxxx xxxx");
    mvprintw(14, 2, " R9: xxxx xxxx xxxx xxxx");
    mvprintw(15, 2, "R10: xxxx xxxx xxxx xxxx");
    mvprintw(16, 2, "R11: xxxx xxxx xxxx xxxx");
    mvprintw(17, 2, "R12: xxxx xxxx xxxx xxxx");
    mvprintw(18, 2, " SP: xxxx xxxx xxxx xxxx");
    mvprintw(19, 2, " RA: xxxx xxxx xxxx xxxx");
    mvprintw(20, 2, " PC: xxxx xxxx xxxx xxxx");
    mvprintw(21, 2, "ISP: xxxx xxxx xxxx xxxx");
    mvprintw(22, 2, "IRA: xxxx xxxx xxxx xxxx");
    mvprintw(23, 2, "IPC: xxxx xxxx xxxx xxxx");
    mvprintw(24, 2, "Fch: xxxx xxxx xxxx xxxx");
    mvprintw(24, 43,"Instruction: ");
    mvprintw(3, 52, "Z");
    mvprintw(3, 56, "C");
    mvprintw(3, 60, "N");
    mvprintw(3, 64, "V");
    mvprintw(4, 52, "x");
    mvprintw(4, 56, "x");
    mvprintw(4, 60, "x");
    mvprintw(4, 64, "x");

    attrset(A_NORMAL);

    refresh();    
}



//
// -- Initialize the UI
//
//    Note that anything after this function is called cannot exit directly as it will leaver the console in an
//    undetermined state
//    ---------------------------------------------------------------------------------------------------------
void UI_t::InitUi(void)
{
    initscr();
    resizeterm(MIN_ROWS, MIN_COLS);
    start_color();
    use_default_colors();
    cbreak();
    raw();
    noecho();
    halfdelay(3);

    curs_set(0);
    init_pair(C_ERROR, COLOR_RED, COLOR_BLACK);
    init_pair(C_BIT_OFF, COLOR_WHITE, COLOR_BLACK);
    init_pair(C_BIT_ON, COLOR_RED, COLOR_BLACK);
    init_pair(C_TITLE, COLOR_BLUE, COLOR_BLACK);
    init_pair(C_LABEL, COLOR_MAGENTA, COLOR_BLACK);

    PaintEmulator();
    hist = newwin(18, COLS - 45, 6, 43);
    if (!hist) fprintf(stderr, "Unable to initialize window!!!\n");
    scrollok(hist, true);
    scrollok(stdscr, false);

    wattrset(hist, A_BOLD | COLOR_PAIR(C_TITLE));
    wprintw(hist, "Welcome to the 16-Bit Computer From Scratch Emulator\n");
    wprintw(hist, "  Press <space> to start; q = exit\n\n");
    wattrset(hist, A_NORMAL);

    wrefresh(hist);
    refresh();
}



