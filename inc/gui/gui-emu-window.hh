//===================================================================================================================
//  gui-emu-window.hh -- The main Emulation Window -- the graphical application
//
//      Copyright (c) 2023 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2023-Oct-24  Initial  v0.0.1   Reinvisioned initial version
//===================================================================================================================


#pragma once


class GUI_EmulationWindow_t : public QWidget {
    Q_OBJECT

private:
    QGridLayout *grid;
    GUI_Oscillator_t *oscVisual;
    HW_Computer_t *computer;
    GUI_Led_t *led1;
    GUI_Led_t *led2;
    GUI_Led_t *led3;
    GUI_Led_t *led4;

    GUI_Led_t *phaseLed1;
    GUI_Led_t *phaseLed2;

public:
    explicit GUI_EmulationWindow_t(QWidget *parent = nullptr) : QWidget(parent) {};
    virtual ~GUI_EmulationWindow_t() {}

public:
    HW_Computer_t *GetComputer(void) const { return computer; }

protected:
    QGroupBox *CreateOscillatorGroup(void);
    QGroupBox *CreateClockLedGroup(void);

public:
    void Initialize(void);
    void ConnectVisuals(void);
};

