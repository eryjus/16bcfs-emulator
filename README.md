# 16-Bit Computer From Scratch -- Emulator

This is the source code that supports my *16-Bit Computer From Scratch* project.  This project in particular is an emulator for the 16-Bit Computer.


---

## Videos

I am documenting my 16-Bit Computer build in video form.  You can find the entire playlist [here](https://www.youtube.com/playlist?list=PLUF7WfBe0k3g9wpTtg41QP3jl5y8T1aGV).


---

## License

See [LICENSE.md](LICENSE.md).


---

## Build System

I use `tup` as my primary build system.  I usually will wrap `tup` in `make` commands.  You can find `tup` [here](https://gittup.org/tup/).  I simply find `tup` to more reliable detect changed sources with less work.


---

## EEPROM Programmer

I do not have a commercial EEPROM programmer.  I use the TommyPROM programmer.  You can find all the relevant information on TommyPROM [here](https://tomnisbet.github.io/TommyPROM/).  In Linux, I use `minicom` as the interface.  Hint: use `sudo minicom -s` to set up the defaults.



---

## TODO:
- [x] Label the instruction and fetch registers
- [x] Disasemble the current instruciton
- [x] Label the rest of the registers
- [x] Create a window for scrolling the instruction executed
- [x] Encapsulate the UI in a class
- [x] Change input to timeout
- [x] Change exit key to 'q'
- [x] Trap Ctrl-C and terminal resize
- [ ] Change Emulator to halt when sized improperly
- [ ] Change the location of the sections based on the size of the window; alternatively, set the size of the emulator to be fixed
- [ ] Center the terminal size error message in the window; paint the background red


