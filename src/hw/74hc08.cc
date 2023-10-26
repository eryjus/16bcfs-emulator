//===================================================================================================================
// hw-74hc08.cc -- This file implementes the 74HC08 Quad Two-Input AND Gate IC
//
//      Copyright (c) 2023 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2023-Oct-22  Initial  v0.0.1   Initial Version
//===================================================================================================================


#include "16bcfs.hh"
#include "../moc/hw-74hc08.moc.cc"


//
// -- This is the contructor for the AND Gate IC, which has 14 pins
//    -------------------------------------------------------------
HW_74HC08_t::HW_74HC08_t(void)
{
    pins[A1] = LOW;
    pins[B1] = LOW;
    pins[Y1] = LOW;
    pins[A2] = LOW;
    pins[B2] = LOW;
    pins[Y2] = LOW;
    pins[Y3] = LOW;
    pins[B3] = LOW;
    pins[A3] = LOW;
    pins[Y4] = LOW;
    pins[B4] = LOW;
    pins[A4] = LOW;
}


//
// -- Update the Y1 AND Gates
//    -----------------------
void HW_74HC08_t::UpdateGate1Complete(void)
{
    TriState_t y1 = (pins[A1] == HIGH && pins[B1] == HIGH) ? HIGH : LOW;

    if (y1 != pins[Y1]) {
        pins[Y1] = y1;
        emit Y1Updated(y1);
    }
}


//
// -- Update the Y1 AND Gates
//    -----------------------
void HW_74HC08_t::UpdateGate2Complete(void)
{
    TriState_t y2 = (pins[A2] == HIGH && pins[B2] == HIGH) ? HIGH : LOW;

    if (y2 != pins[Y2]) {
        pins[Y2] = y2;
        emit Y2Updated(y2);
    }
}


//
// -- Update the Y1 AND Gates
//    -----------------------
void HW_74HC08_t::UpdateGate3Complete(void)
{
    TriState_t y3 = (pins[A3] == HIGH && pins[B3] == HIGH) ? HIGH : LOW;

    if (y3 != pins[Y3]) {
        pins[Y3] = y3;
        emit Y3Updated(y3);
    }
}


//
// -- Update the Y1 AND Gates
//    -----------------------
void HW_74HC08_t::UpdateGate4Complete(void)
{
    TriState_t y4 = (pins[A4] == HIGH && pins[B4] == HIGH) ? HIGH : LOW;

    if (y4 != pins[Y4]) {
        pins[Y4] = y4;
        emit Y4Updated(y4);
    }
}


