

# libfpreal: fixed point real numbers in C++

libfpreal is a fixed point real numbers library in C++. It utilizes int128 data type, if it is available by the compiler, otherwise it falls back to long long. 

**Supported platforms**

Any *nix platform with GNU Make installed and a C++ compiler with support equal or above the C++98 standard will do the job.

**How to compile and install**

Just type make in the top level source directory. Makefiles are written with a g++ compatible compiler in mind. CC, CXX, CFLAGS, CXXFAGS, CPPFLAGS, LD environment variables are supported.

Make will produce libfpreal.a, libfpreal.so and the binaries for the examples, a simple benchmark and the tests for the C language binding.

make install will install the libraries and the header files under /usr/local

make clean will wipe out and object or executable binaries produced.

**How to use libfpreal in your projects**

You have to link over libfpreal.so or libfpreal.a 

**How to use libfpreal in your programs**

libfpreal is very easy to use. Better take a look in the examples/basic.cpp file. 

The basic type is fprealN_t where N is the number of the digits after the decimal point. 

For example:

**fpreal2_t A;**

declares a fixed point real number with two digits after the decimal point. 

You can assign values to A in many ways, strings included. All the following assignments are valid:

**fpreal2_t A, B = 12.12, C (13.13), D ("2342.1192");**

You can even assign values from strings. For example:

**fpreal2 E;**

**E="98.9981";**

is valid. 

There are overload operators for **=,+,-,*,/,++,--,*=,/= and comparisons**.

Two member functions **getString()** and **getDouble()** are also available.

Assignments and operations throw exceptions for strings containing invalid numbers and overflow/underflow. 

You must include fprealxx.h. C language bindings are also available in fpreal.h.

**Limitations**

The maximum supported number of digits after the decimal points, is 9. The range depends on the native type used, int128 or long long, and the number of digits after the decimal point.

**License**

[GPL v3](https://www.gnu.org/licenses/gpl-3.0.en.html)

**Contact**

Lucas Tsatiris: lucast70@hotmail.com















