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

```bash
git clone https://gitlab.gmrv.es/gmrv/scoop.git
mkdir scoop/build && cd scoop/build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
