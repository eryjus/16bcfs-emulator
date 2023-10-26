//===================================================================================================================
//  hw-computer.hh -- This is the foundation of the computer build -- like a backplane
//
//      Copyright (c) 2023 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2023-Oct-24  Initial  v0.0.1   Reinvisioned initial version
//===================================================================================================================


#pragma once


//
// -- This is the foundation of the computer, as in the backplane or breadboard that everything plugs into
//    ----------------------------------------------------------------------------------------------------
class HW_Computer_t : public QObject {
    Q_OBJECT
    Q_PROPERTY(TriState_t oscillatorState READ GetOscillatorState NOTIFY OscillatorStateChanged)

private:
    QTimer *oscillator;
    TriState_t oscillatorState;
    HW_74HC193_t *clkPhaseCnt;
    HW_74HC138_t *clkPhaseCycler;
    HW_74HC08_t *clkCycles;

public:
    explicit HW_Computer_t(void) {};
    virtual ~HW_Computer_t() {};

public:
    void Initialize(void);
    QTimer *GetOscillator(void) const { return oscillator; }
    HW_74HC193_t *GetClkPhaseCnt(void) const { return clkPhaseCnt; }
    HW_74HC138_t *GetClkPhaseCycler(void) const { return clkPhaseCycler; }
    HW_74HC08_t *GetClkCycles(void) const { return clkCycles; }

    TriState_t GetOscillatorState(void) const { return oscillatorState; }
    void StartTimer(void) { oscillator->start(); }

public slots:
    void ChangeTimerState(void) {
        oscillatorState = (oscillatorState==HIGH?LOW:HIGH);
        emit OscillatorStateChanged(oscillatorState);
    }

signals:
    void OscillatorStateChanged(TriState_t state);

private:
    void Build(void);
};


