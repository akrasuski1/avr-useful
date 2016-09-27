# Bootloader

Just a proof of concept that dynamic loading of code is possible on AVRs.

Code can be built using the usual makefile of mine - just remember to add:
```
BOOT=0x7e00
LD_FLAGS+=-Wl,--section-start=boot=$(BOOT)
```
