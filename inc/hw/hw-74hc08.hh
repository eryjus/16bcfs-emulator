//===================================================================================================================
// hw-74hc08.hh -- This header file defines a 74HC08 Quad Two-Input AND Gate IC
//
//      Copyright (c) 2023 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2023-Oct-23  Initial  v0.0.1   Initial Version
//===================================================================================================================


#pragma once


//
// -- This class implements a 74HC08 AND Gate IC
//    ------------------------------------------
class HW_74HC08_t : public QObject {
    Q_OBJECT

public:
    enum {A1 = 1,
        B1 = 2,
        Y1 = 3,
        A2 = 4,
        B2 = 5,
        Y2 = 6,
        Y3 = 8,
        B3 = 9,
        A3 = 10,
        Y4 = 11,
        B4 = 12,
        A4 = 13,
    };

private:
    TriState_t pins[14+1];


public:
    HW_74HC08_t(void);
    virtual ~HW_74HC08_t() {};

public slots:
    void UpdateA1(TriState_t state) { pins[A1] = state; }
    void UpdateB1(TriState_t state) { pins[B1] = state; }
    void UpdateA2(TriState_t state) { pins[A2] = state; }
    void UpdateB2(TriState_t state) { pins[B2] = state; }
    void UpdateA3(TriState_t state) { pins[A3] = state; }
    void UpdateB3(TriState_t state) { pins[B3] = state; }
    void UpdateA4(TriState_t state) { pins[A4] = state; }
    void UpdateB4(TriState_t state) { pins[B4] = state; }

    void UpdateGate1Complete(void);
    void UpdateGate2Complete(void);
    void UpdateGate3Complete(void);
    void UpdateGate4Complete(void);

    void UpdatesComplete(void) {
        UpdateGate1Complete();
        UpdateGate2Complete();
        UpdateGate3Complete();
        UpdateGate4Complete();
    }


signals:
    void Y1Updated(TriState_t state);
    void Y2Updated(TriState_t state);
    void Y3Updated(TriState_t state);
    void Y4Updated(TriState_t state);
    void AllUpdated(void);
};



