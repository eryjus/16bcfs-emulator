//===================================================================================================================
//  16bcfs.hh -- This is the singular header file to include for the entire project
//
//      Copyright (c) 2023 - Adam Clark
//      License: Beerware
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2023-Oct-24  Initial  v0.0.1   Reinvisioned initial version
//===================================================================================================================


//
// -- c/c++ standard include files here
//    ---------------------------------
typedef enum {
    LOW = 0,
    GND = 0,
    HIGH = 1,
    VCC = 1,
    Z = -1,
} TriState_t;


//
// -- Qt6 include files here
//    ----------------------
#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QtGui/QPalette>
#include <QtGui/QPicture>
#include <QtGui/QPixmap>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>


//
// --  forward declaration of all classes
//     ----------------------------------
class HW_Computer_t;
class HW_74HC08_t;
class HW_74HC138_t;
class HW_74HC193_t;
class GUI_EmulationWindow_t;
class GUI_Application_t;
class GUI_Led_t;
class GUI_Oscillator_t;



//
// -- project speific include files here
//    ----------------------------------
#include "hw/hw-computer.hh"
#include "hw/hw-74hc08.hh"
#include "hw/hw-74hc138.hh"
#include "hw/hw-74hc193.hh"
#include "gui/gui-emu-window.hh"
#include "gui/gui-application.hh"
#include "gui/gui-led.hh"
#include "gui/gui-oscillator.hh"


