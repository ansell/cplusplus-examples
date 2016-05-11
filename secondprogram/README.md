Overall structure roughly following the tutorial (with completely different implementation) at:

https://cmake.org/cmake-tutorial/

Includes GPL-3 code from https://github.com/jay/CSV

Installation instructions
=========================

To install run the following command

    cmake . && cmake . && make clean install

The artifacts will be accessible in the target subdirectory

Running tests
=============

To run tests execute the following command

    cmake . && cmake . && make && ctest .

Generate packages
=================

To generate packages for distribution execute the following command:

    cmake -DCMAKE_BUILD_TYPE=Release . && cmake -DCMAKE_BUILD_TYPE=Release . && make clean install && ctest . && cpack --config CPackConfig.cmake

To generate source packages for distribution execute the following command:

    cmake . && cmake . && make clean install && ctest . && cpack --config CPackSourceConfig.cmake
