## I2C, Simple / Platform-Agnostic Library
### Jordan Ebel

This library provides platform-agnostic support for I2C
operations.  This library compiles to a different static 
library for each supported platform.  A project can link 
with different versions of this static library to function 
on different platforms, without changing source code.


Currently supported platforms:

- Linux

