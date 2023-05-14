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
    uint16_t value;

public:
    Register_t(void) : value(0) {};
    virtual ~Register_t() {};

public:
    Register_t &operator=(const Register_t &r) { value = r.value; return *this; };
    Register_t &operator=(const uint16_t v) { value = v; return *this; }

public:
    inline uint16_t Value(void) const { return value; }
    inline void Value(uint16_t v) { value = v; }

public:
    inline void Inc(void) { value ++; }
    inline void Dec(void) { value --; }


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
// -- Define what the CPU looks like
//    ------------------------------
class CPU_t {
    CPU_t(const CPU_t &) = delete;
    CPU_t &operator=(const CPU_t &) = delete;

private:
    static CPU_t *singleton;

private:
    CPU_t(void) {}

public:
    virtual ~CPU_t() {}

public:
    static inline CPU_t *Get(void) { if (unlikely(!singleton)) singleton = new CPU_t(); return singleton; }

private:
    void PrintBinary(uint16_t v);

public:
    void Emulate(void);
    bool Emulate(uint16_t cond, uint16_t opcode);

protected:
    Register_t pc;
    Register_t r1;
    Register_t fetch;
    Register_t instruction;
    bool c;
};



//
// -- Memory is not part of the CPU but an external resource on the computer
//    ----------------------------------------------------------------------
extern uint16_t memory[64 * 1024];


