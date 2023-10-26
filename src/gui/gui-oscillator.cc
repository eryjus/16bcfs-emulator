//===================================================================================================================
//  gui-oscillator.cc -- A label visualizing an oscillator, displaying high and low signals
//
//      Copyright (c) 2023 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2023-Oct-24  Initial  v0.0.1   Reinvisioned initial version
//===================================================================================================================


#include "16bcfs.hh"
#include "gui-oscillator.moc.cc"


//
// -- This is the constructor for the oscillator
//    ------------------------------------------
GUI_Oscillator_t::GUI_Oscillator_t(QWidget *parent) : QLabel(parent), hi("img/clk-hi.png"), lo("img/clk-lo.png")
{
    setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    setPixmap(lo);
}
