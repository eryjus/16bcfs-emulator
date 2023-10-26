//===================================================================================================================
// hw-74hc193.cc -- This file implementes the a 74HC193 Up/Down Counter
//
//      Copyright (c) 2023 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2023-Oct-25  Initial  v0.0.1   Initial Version
//===================================================================================================================


#include "16bcfs.hh"
#include "hw-74hc193.moc.cc"


//
// -- This is the contructor for the UP/DOWN cnter, having 16 pins
//    --------------------------------------------------------------
HW_74HC193_t::HW_74HC193_t()
{
    pins[0] = LOW;
    pins[B] = LOW;
    pins[QB] = LOW;
    pins[QA] = LOW;
    pins[DOWN] = LOW;
    pins[UP] = LOW;
    pins[QC] = LOW;
    pins[QD] = LOW;
    pins[D] = LOW;
    pins[C] = LOW;
    pins[LOADb] = LOW;
    pins[COb] = LOW;
    pins[BOb] = LOW;
    pins[CLR] = LOW;
    pins[A] = LOW;

    lastUp = LOW;
    lastDown = LOW;

    cnt = 0;
}


//
// -- Update the outputs
//    ------------------
void HW_74HC193_t::UpdatesComplete(void)
{
    if (pins[UP] == LOW && pins[DOWN] == LOW) {
        qDebug("Invalid state on 74HC193: Both UP and DOWN are LOW at the same time");
    }


    if (pins[CLR] == HIGH) {
        cnt = 0;
        goto updateOut;
    }

    if (pins[LOADb] == LOW) {
        cnt = ((pins[D]==HIGH?1:0) << 3)
                | ((pins[C]==HIGH?1:0) << 2)
                | ((pins[B]==HIGH?1:0) << 1)
                | ((pins[A]==HIGH?1:0) << 0);

        goto updateOut;
    }

    if (lastUp == HIGH && pins[UP] == LOW && cnt == 15) {
        // -- Count Up High-to-Low transition: Set COb low
        pins[COb] = LOW;
        emit CoUpdated(LOW);
    }

    if (lastDown == HIGH && pins[DOWN] == LOW && cnt == 0) {
        // -- Count Up High-to-Low transition: Set BOb low
        pins[BOb] = LOW;
        emit BoUpdated(LOW);
    }

    if (lastUp == LOW && pins[UP] == HIGH) {
        cnt ++;
        pins[COb] = HIGH;
        emit CoUpdated(HIGH);
    }

    if (lastDown == LOW && pins[DOWN] == HIGH) {
        cnt --;
        pins[BOb] = HIGH;
        emit BoUpdated(HIGH);
    }

updateOut:
    cnt &= 0xf;
    lastUp = pins[UP];
    lastDown = pins[DOWN];

    pins[QA] = (cnt&0b0001?HIGH:LOW);
    pins[QB] = (cnt&0b0010?HIGH:LOW);
    pins[QC] = (cnt&0b0100?HIGH:LOW);
    pins[QD] = (cnt&0b1000?HIGH:LOW);

    emit QaUpdated(pins[QA]);
    emit QbUpdated(pins[QB]);
    emit QcUpdated(pins[QC]);
    emit QdUpdated(pins[QD]);

    emit AllUpdated();
}


