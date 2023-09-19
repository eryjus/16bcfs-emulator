//===================================================================================================================
// 16bcfs.hh -- 16-Bit Computer From Scratch Emulator header file
//
//      Copyright (c) 2023 - Adam Clark
//      License: Beerware
//
//  This file contains the definitions for the 16-Bit Computer From Scratch.  This file will be included in all
//  source files to import all definitions and function prototypes.
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2023-May-13  Initial  v0.0.1   Initial Version
//===================================================================================================================


#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <ncurses.h>


//
// -- These will help with branch prediction
//    --------------------------------------
#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x)    __builtin_expect(!!(x), 0)



//
// -- create a generic register class from which all other registers will be derived
//    ------------------------------------------------------------------------------
class Register_t {
    Register_t(const Register_t &) = delete;

private:
    int x;
    int y;
    uint16_t value;

public:
    Register_t(int _x, int _y) : x(_x), y(_y), value(0) {};
    virtual ~Register_t() {};

public:
    Register_t &operator=(const Register_t &r) { value = r.value; Draw(); return *this; };
    Register_t &operator=(const uint16_t v) { value = v; Draw(); return *this; }

public:
    inline uint16_t Value(void) const { return value; }

public:
    inline void Inc(void) { value ++; Draw(); }
    inline void Dec(void) { value --; Draw(); }

public:
    void Draw(void);


//
// -- These are placeholders for future development
//    ---------------------------------------------
public:
//    virtual void HandleRisingEdge(void) = 0;
//    virtual void HandleHighLevel(void) = 0;
//    virtual void HandleFallingEdge(void) = 0;
//    virtual void HandleLowLevel(void) = 0;
};



//
// -- create a generic flag class from which all other flags will be derived
//    ----------------------------------------------------------------------
class Flag_t {
    Flag_t(const Flag_t &) = delete;

private:
    int x;
    int y;
    bool value;

public:
    Flag_t(int _x, int _y) : x(_x), y(_y), value(false) {};
    virtual ~Flag_t() {};

public:
    Flag_t &operator=(const Flag_t &f) { value = f.value; Draw(); return *this; };
    Flag_t &operator=(const bool v) { value = v; Draw(); return *this; }
    operator bool() const { return value; }

public:
    inline bool Value(void) const { return value; }

public:
    void Draw(void);
};



//
// -- Define what the CPU looks like
//    ------------------------------
class CPU_t {
    CPU_t(const CPU_t &) = delete;
    CPU_t &operator=(const CPU_t &) = delete;

private:
    static CPU_t *singleton;
    bool irSuppress;
    bool firstInstr;

private:
    CPU_t(void) : r1(6, 7), r2(7,7), pc(20,7), fetch(24,7), instruction(24,56), z(4,52), c(4,56), n(4,60), v(4,64), l(4,68), debug(4,48)  { irSuppress = false; firstInstr = true; UpdateUI(); }

public:
    virtual ~CPU_t() {}

public:
    static inline CPU_t *Get(void) { if (unlikely(!singleton)) singleton = new CPU_t(); return singleton; }

private:
    void PrintBinary(uint16_t v);
    bool ConditionsMet(uint16_t cond);

public:
    void Emulate(void);
    bool Emulate(uint16_t cond, uint16_t opcode);

public:
    void UpdateUI(void);

protected:
    Register_t pc;
    Register_t r1;
    Register_t r2;
    Register_t fetch;
    Register_t instruction;
    Flag_t z;
    Flag_t c;
    Flag_t n;
    Flag_t v;
    Flag_t l;
    Flag_t debug;
};


//
// -- Define the UI Class
//    -------------------
class UI_t {
    UI_t(const UI_t &) = delete;
    UI_t &operator=(const UI_t &) = delete;

public:
    //
    // -- Color mapping
    //    -------------
    enum {
        C_ERROR = 1,
        C_BIT_ON = 2,
        C_BIT_OFF = 3,
        C_TITLE = 4,
        C_LABEL = 5,
        C_SKIPPED = 6,
    };


private:
    static UI_t *singleton;
    WINDOW *hist;

private:
    UI_t(void) { InitUi(); };

public:
    virtual ~UI_t(void) {}

public:
    static inline UI_t *Get(void) { if (unlikely(!singleton)) singleton = new UI_t(); return singleton; }

private:
    void InitUi(void);

public:
    void OutputRegister(int x, int y, uint16_t val);
    void OutputBit(int y, int x, bool b);
    void PaintEmulator(void);
    WINDOW *Hist(void) {return hist; }

public:
    int AppendHistory(const char *fmt, ...) { va_list l; va_start(l,fmt); int rv = vw_printw(hist, fmt, l); va_end(l); return rv; };
    void AppendSkipped(void) { wattrset(hist, COLOR_PAIR(C_SKIPPED)); wprintw(hist, " (condition not met)\n"); wattrset(hist, A_NORMAL); };
};



//
// -- This macro is to help readability in the source code
//    ----------------------------------------------------
#define CPU (CPU_t::Get())
#define UI (UI_t::Get())


//
// -- Memory is not part of the CPU but an external resource on the computer
//    ----------------------------------------------------------------------
extern uint16_t memory[64 * 1024];


//
// -- Functions defined in ui.cc:
//    ---------------------------
inline void Register_t::Draw(void)
{
    UI->OutputRegister(x, y, value);
}


//
// -- Functions defined in ui.cc:
//    ---------------------------
inline void Flag_t::Draw(void)
{
    UI->OutputBit(x, y, value);
}
