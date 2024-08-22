# Exponential Smoothing Methods

A simple implementation of some exponential smoothing methods. See more information about these methods
[here](https://otexts.com/fpp2/expsmooth.html).

## Build

We use [conan](https://conan.io/) as package manager. Thus, in order to correctly install all the dependencies
required by the library, you need to specify a `conan_provider.cmake` file. We include one in our project, so
the following lines should be enough to compile the library and its examples.

```shell
mkdir build && cd build
cmake -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=conan_provider.cmake ..
make
```

> [!note]
> Right now we only use `conan` to get the `GTest` suit. Thus, if you either have that already installed on the system
> or you compiled the code with `-DBUILD_TESTING=OFF`, you can safely omit its installation and the use of
> `-DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=conan_provider.cmake`.

## Install

The previous steps are enough to play with the demos and check that dependencies of the library are satisfied. But If
you
want to use our library with an external project, you will need to install it. We provide an installation script
`install.sh`, which should be run directly from the root directory of the library:

```shell
bash install.sh
```

This should create an `install` directory inside the main directory (i.e., `/path/to/library/install`). You can use
the variable [CMAKE_INSTALL_PREFIX](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html) to change
this behaviour. Alternatively, you could execute instead:

```bash
cd build
cmake --build .
cmake --install . --prefix /custom/install/path
```

#### Using library in external project

In the client code (i.e., the external project where you want to use our library) you will need to first find
and link `exponential_smoothing`. For this, in your `CMakeList.txt` add:

```cmake
find_package(exponential_smoothing CONFIG REQUIRED)
target_link_libraries(exec.out PRIVATE exponential_smoothing::exponential_smoothing)
```

When you configure your external application do not forget to include the path to where the library was installed:

```shell
cmake -DCMAKE_PREFIX_PATH="/path/to/library/install"
```

At last, you should be able to include and use our headers in your project as, for example:

```c++
#include <exponential_smoothing/holt_linear_trend.hpp>
```