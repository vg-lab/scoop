# scoop - Simple color palettes and mappers


## Introduction

scoop is a library for color palettes and color mappers based on QColor

## Dependencies

* Required dependencies:
    * Qt5 (for QColor)

* Optional dependencies:
    * Boost: for unit tests

## Building

scoop has been succesfully built and used on Ubuntu 14.04, Mac OSX
Yosemite and Windows 7/8 Visual Studio 2013 Win64. The following steps should be
enough to build it just with the required dependencies.

~~~~~~
git clone --recursive https://gitlab.gmrv.es/gmrv/scoop.git
mkdir scoop/build && cd scoop/build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
~~~~~~


## Testing

After building scoop, you can run some examples in bin directory.
For example, to manually run a simple test that creates a sequential 
color map, use the command:
~~~~~~~~~~~~~
./bin/scoopSequentialColorMap 
~~~~~~~~~~~~~

## Documentation

You can access the online API documentation generated from the source 
(using [Doxygen](http://doxygen.org/) ) in 
https://gmrvvis.github.io/doc/scoop/
