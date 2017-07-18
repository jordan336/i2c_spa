## I/O Simple Platform Abstraction Library
### Jordan Ebel

This library provides an abstraction layer for I2C and SPI
operations.  This library compiles to a different static 
library for each supported platform.  A project can link 
with different versions of this static library to function 
on different platforms, without changing source code.


Currently supported platforms:

- Linux

