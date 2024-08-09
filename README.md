# Holt-Winter's

A simple implementation of the Holt-Winter's exponential smoothing method. See more information about the method
[here](https://otexts.com/fpp2/expsmooth.html).

## Build

We use [conan](https://conan.io/) as package manager. Thus, in order to correctly install all the dependencies
required by the library, you need to specify a `conan_provider.cmake` file. We include one in our project, so
the following two lines should be enough to compile the library and its examples.

```shell
mkdir build && cd build
cmake -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=conan_provider.cmake ..
make