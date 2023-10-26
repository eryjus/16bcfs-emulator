//===================================================================================================================
//  gui-oscillator.hh -- A label visualizing an oscillator, displaying high and low signals
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
// -- This is an oscillator visualization, changing states on a timer signal
//    ----------------------------------------------------------------------
class GUI_Oscillator_t : public QLabel {
    Q_OBJECT

public:
    explicit GUI_Oscillator_t(QWidget *parent = nullptr);
    virtual ~GUI_Oscillator_t() {}

public slots:
    void Change(TriState_t state) { setPixmap(state?hi:lo); }

private:
    QPixmap hi;
    QPixmap lo;
};
