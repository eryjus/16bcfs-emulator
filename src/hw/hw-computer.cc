//===================================================================================================================
//  hw-computer.cc -- This is the foundation of the computer build -- like a backplane or breadboard
//
//      Copyright (c) 2023 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2023-Oct-24  Initial  v0.0.1   Reinvisioned initial version
//===================================================================================================================


#include "16bcfs.hh"
#include "hw-computer.moc.cc"


//
// -- Initialize the computer by placing the components and hooking up the wires (signals/slots)
//    ------------------------------------------------------------------------------------------
void HW_Computer_t::Initialize(void)
{
    //
    // -- Place the oscillator
    //    --------------------
    {
        oscillator = new QTimer(this);
        oscillator->setInterval(500);
    }


    //
    // -- here we place a counter for the 4-cycle clock
    //    ---------------------------------------------
    {
        clkPhaseCnt = new HW_74HC193_t;
        clkPhaseCnt->UpdateDown(VCC);
        clkPhaseCnt->UpdateClr(GND);
        clkPhaseCnt->UpdateLoad(VCC);
        clkPhaseCnt->UpdateA(GND);
        clkPhaseCnt->UpdateB(GND);
        clkPhaseCnt->UpdateC(GND);
        clkPhaseCnt->UpdateD(GND);
    }


    //
    // -- here we place a demux for the cycler for the 4-cycle clock
    //    ----------------------------------------------------------
    {
        clkPhaseCycler = new HW_74HC138_t;
        clkPhaseCycler->UpdateG1(VCC);
        clkPhaseCycler->UpdateG2A(GND);
        clkPhaseCycler->UpdateG2B(GND);
        clkPhaseCycler->UpdateC(GND);
    }


    //
    // -- Complete the final 4-cycle clock phasing
    //    ----------------------------------------
    {
        clkCycles = new HW_74HC08_t;
        clkCycles->UpdateA3(GND);
        clkCycles->UpdateB3(GND);
        clkCycles->UpdateA4(GND);
        clkCycles->UpdateB4(GND);
    }

    Build();
}


void HW_Computer_t::Build(void)
{
    // -- wire the oscillator to its state in the computer
    connect(oscillator, &QTimer::timeout, this, &HW_Computer_t::ChangeTimerState);

    // -- connect the inputs of the clock cycle counter
    connect(this, &HW_Computer_t::OscillatorStateChanged, clkPhaseCnt, &HW_74HC193_t::UpdateUp);

    // -- connect the input of the clock cycler
    connect(clkPhaseCnt, &HW_74HC193_t::QaUpdated, clkPhaseCycler, &HW_74HC138_t::UpdateA);
    connect(clkPhaseCnt, &HW_74HC193_t::QbUpdated, clkPhaseCycler, &HW_74HC138_t::UpdateB);
    connect(clkPhaseCnt, &HW_74HC193_t::AllUpdated, clkPhaseCycler, &HW_74HC138_t::UpdatesComplete);

    // -- connect the inputs of the clock phases
    connect(clkPhaseCycler, &HW_74HC138_t::Y1Updated, clkCycles, &HW_74HC08_t::UpdateA1);
    connect(clkPhaseCycler, &HW_74HC138_t::Y2Updated, clkCycles, &HW_74HC08_t::UpdateB1);
    connect(clkPhaseCycler, &HW_74HC138_t::Y2Updated, clkCycles, &HW_74HC08_t::UpdateA2);
    connect(clkPhaseCycler, &HW_74HC138_t::Y3Updated, clkCycles, &HW_74HC08_t::UpdateB2);
    connect(clkPhaseCycler, &HW_74HC138_t::AllUpdated, clkCycles, &HW_74HC08_t::UpdateGate1Complete);
    connect(clkPhaseCycler, &HW_74HC138_t::AllUpdated, clkCycles, &HW_74HC08_t::UpdateGate2Complete);
}
