# libudev++: Udev Library for C++

The `libudev++` library is a C++ wrapper for
[libudev](https://www.freedesktop.org/software/systemd/man/libudev.html).
It enables one to enumerate, monitor and introspect devices on the local system.

## Installation

### Prerequisites

* libudev (provided by [systemd](https://www.freedesktop.org/wiki/Software/systemd/))

### Binary

Debian/Ubuntu/etc:

```console
$ ver=1.0
$ url=https://github.com/dimitry-ishenko-cpp/libudevpp/releases/download/v${ver}
$ wget ${url}/libudev++_${ver}_amd64.deb
$ sudo apt install ./libudev++_${ver}_amd64.deb
```

Install the development package, if you are planning to develop applications with `libudev++`:

```console
$ wget ${url}/libudev++-dev_${ver}_amd64.deb
$ sudo apt install ./libudev++-dev_${ver}_amd64.deb
```

RaspberryPi:

```console
$ ver=1.0
$ url=https://github.com/dimitry-ishenko-cpp/libudevpp/releases/download/v${ver}
$ wget ${url}/libudev++_${ver}_armhf.deb
$ sudo apt install ./libudev++_${ver}_armhf.deb
```

Install the development package, if you are planning to develop applications with `libudev++`:

```console
$ wget ${url}/libudev++-dev_${ver}_armhf.deb
$ sudo apt install ./libudev++-dev_${ver}_armhf.deb
```

### From source

Stable version (requires [CMake](https://cmake.org/) >= 3.1):

```console
$ ver=1.0
$ wget https://github.com/dimitry-ishenko-cpp/libudevpp/archive/v${ver}.tar.gz
$ tar xzf v${ver}.tar.gz
$ mkdir libudevpp-${ver}/build
$ cd libudevpp-${ver}/build
$ cmake ..
$ make
$ sudo make install
```

Latest master (requires [git](https://git-scm.com/) and [CMake](https://cmake.org/) >= 3.1):

```console
$ git clone https://github.com/dimitry-ishenko-cpp/libudevpp.git
$ mkdir libudevpp/build
$ cd libudevpp/build
$ cmake ..
$ make
$ sudo make install
```

## Developing with libudev++

To develop with `libudev++` simply add `#include <udev++.hpp>` to your program
and `-ludev++` to your linker. Following are a few examples demonstrating its
capabilities:

Example #1:

```cpp
auto ctx = udev::udev::instance();

udev::enumerate enumerate{ ctx };
enumerate.match_subsystem("block");

auto devices = enumerate.get();
for(auto const& device : devices)
{
    using namespace std;

    if(device.type() == "partition" && device.property("ID_BUS") == "ata")
    {
        cout << "Found hard disk" << endl
             << "Path: " << device.syspath() << endl
             << "Node: " << device.devnode() << endl
             << "  FS: " << device.property("ID_FS_TYPE") << endl
             << "Name: " << device.sysname() << endl
             << "   #: " << device.sysnum () << endl;
        cout << endl;
    }
}
```

Example #2:
```cpp
auto ctx = udev::udev::instance();

udev::monitor monitor{ ctx };
monitor.match_device("block");

for(;;)
{
    using namespace std::chrono_literals;
    using namespace std;

    if(auto device = monitor.try_get_for(30s))
    {
        switch(device.action())
        {
        case udev::added:
            if(device.type() == "partition" && device.property("ID_BUS") == "usb")
            {
                cout << "USB drive plugged in" << endl
                     << "Path: " << device.syspath() << endl
                     << "Node: " << device.devnode() << endl
                     << "  FS: " << device.property("ID_FS_TYPE") << endl
                     << "Name: " << device.sysname() << endl
                     << "   #: " << device.sysnum () << endl;
                cout << endl;
            }
            break;

        case udev::removed:
            if(device.type() == "partition" && device.property("ID_BUS") == "usb")
            {
                cout << "USB drive " << device.devnode() << " unplugged" << endl;
                cout << endl;
            }
            break;
        }
    }
    else
    {
        cout << "Nothing seems to be happening" << endl;
        break;
    }
}
```

## Authors

* **Dimitry Ishenko** - dimitry (dot) ishenko (at) (gee) mail (dot) com

## License

This project is distributed under the GNU GPL license. See the
[LICENSE.md](LICENSE.md) file for details.

## Acknowledgments
