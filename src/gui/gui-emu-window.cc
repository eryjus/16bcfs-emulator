//===================================================================================================================
//  gui-emu-window.cc -- The main Emulation Window -- the graphical application
//
//      Copyright (c) 2023 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2023-Oct-24  Initial  v0.0.1   Reinvisioned initial version
//===================================================================================================================


#include "16bcfs.hh"
#include "gui-emu-window.moc.cc"


//
// -- Create the group box which will contain the square wave oscillator
//    ------------------------------------------------------------------
QGroupBox *GUI_EmulationWindow_t::CreateOscillatorGroup(void)
{
    QGroupBox *group = new QGroupBox(tr("Sq Wave"));

    oscVisual = new GUI_Oscillator_t;
    oscVisual->setObjectName("Oscillator");

    QVBoxLayout *oscVLayout = new QVBoxLayout;
    oscVLayout->setObjectName("Oscillator Vert Layout");
    oscVLayout->setContentsMargins(0, 0, 0, 0);
    group->setLayout(oscVLayout);

    group->setObjectName("Oscillator Group Box");
    group->setAlignment(Qt::AlignHCenter);
    group->setMaximumHeight(60);
    group->setMaximumWidth(50);

    oscVLayout->addWidget(oscVisual);
    group->setLayout(oscVLayout);

    return group;
}


//
// -- Create the group box which will contain the Clock LEDs
//    ------------------------------------------------------
QGroupBox *GUI_EmulationWindow_t::CreateClockLedGroup(void)
{
    QGroupBox *group = new QGroupBox(tr("Clk LEDs"));


    group->setObjectName("Clock LED Pretty Box");
    group->setAlignment(Qt::AlignHCenter);
    group->setMaximumHeight(60);
    group->setMaximumWidth(50);

    QHBoxLayout *clkLedHLayout1 = new QHBoxLayout();
    clkLedHLayout1->setAlignment(Qt::AlignHCenter);
    clkLedHLayout1->setContentsMargins(0, 0, 0, 0);
    clkLedHLayout1->setSpacing(2);

    led1 = new GUI_Led_t(GUI_Led_t::OnWhenLow);
    led1->setObjectName("LED1");
    clkLedHLayout1->addWidget(led1);

    led2 = new GUI_Led_t(GUI_Led_t::OnWhenLow);
    led2->setObjectName("LED2");
    clkLedHLayout1->addWidget(led2);

    led3 = new GUI_Led_t(GUI_Led_t::OnWhenLow);
    led3->setObjectName("LED3");
    clkLedHLayout1->addWidget(led3);

    led4 = new GUI_Led_t(GUI_Led_t::OnWhenLow);
    led4->setObjectName("LED4");
    clkLedHLayout1->addWidget(led4);


    QHBoxLayout *clkLedHLayout2 = new QHBoxLayout();
    clkLedHLayout2->setAlignment(Qt::AlignHCenter);
    clkLedHLayout2->setContentsMargins(0, 0, 0, 0);
    clkLedHLayout2->setSpacing(2);

    phaseLed1 = new GUI_Led_t(GUI_Led_t::OnWhenHigh, Qt::blue);
    phaseLed1->setObjectName("Phased Clock Major");
    clkLedHLayout2->addWidget(phaseLed1);

    phaseLed2 = new GUI_Led_t(GUI_Led_t::OnWhenHigh, Qt::blue);
    phaseLed2->setObjectName("Phased Clock Minor");
    clkLedHLayout2->addWidget(phaseLed2);


    QVBoxLayout *clkLedVLayout = new QVBoxLayout;
    clkLedVLayout->setAlignment(Qt::AlignHCenter);
    clkLedVLayout->setContentsMargins(0, 0, 0, 0);
    clkLedVLayout->addLayout(clkLedHLayout1);
    clkLedVLayout->addLayout(clkLedHLayout2);

    group->setLayout(clkLedVLayout);

    return group;
}


//
// -- Initialize the main application window for all the widgets
//    ----------------------------------------------------------
void GUI_EmulationWindow_t::Initialize(void)
{
    grid = new QGridLayout;
    grid->setContentsMargins(0, 0, 0, 0);
    grid->addWidget(CreateOscillatorGroup(), 19, 39);
    grid->addWidget(CreateClockLedGroup(), 19, 38);

    setLayout(grid);

    setWindowTitle(tr("16bcfs Emulator"));
    show();


    //
    // -- Finally, set up the computer hardware
    //    -------------------------------------
    computer = new HW_Computer_t();
    computer->Initialize();

    ConnectVisuals();
}


//
// -- Connect up all the wires for the visual elements of the computer
//    ----------------------------------------------------------------
void GUI_EmulationWindow_t::ConnectVisuals(void)
{
    // -- wire the oscillator state in the computer to its visual representation on the screen
    connect(computer, &HW_Computer_t::OscillatorStateChanged, oscVisual, &GUI_Oscillator_t::Change);

    // -- wire up the demux to the LEDs
    connect(computer->GetClkPhaseCycler(), &HW_74HC138_t::Y0Updated, led1, &GUI_Led_t::ChangeState);
    connect(computer->GetClkPhaseCycler(), &HW_74HC138_t::Y1Updated, led2, &GUI_Led_t::ChangeState);
    connect(computer->GetClkPhaseCycler(), &HW_74HC138_t::Y2Updated, led3, &GUI_Led_t::ChangeState);
    connect(computer->GetClkPhaseCycler(), &HW_74HC138_t::Y3Updated, led4, &GUI_Led_t::ChangeState);

    // -- wire up the AND gate to handle the Major/Minor clock phasing
    connect(computer->GetClkCycles(), &HW_74HC08_t::Y1Updated, phaseLed1, &GUI_Led_t::ChangeState);
    connect(computer->GetClkCycles(), &HW_74HC08_t::Y2Updated, phaseLed2, &GUI_Led_t::ChangeState);
}

