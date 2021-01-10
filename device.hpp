////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef UDEV_DEVICE_HPP
#define UDEV_DEVICE_HPP

////////////////////////////////////////////////////////////////////////////////
#include <memory>
#include <string>

namespace impl
{

struct udev;
struct udev_device;
struct device_delete { void operator()(udev_device*); };

}

////////////////////////////////////////////////////////////////////////////////
namespace udev
{

class enumerate;
class monitor;
class udev;

////////////////////////////////////////////////////////////////////////////////
enum action { added, removed, other };

////////////////////////////////////////////////////////////////////////////////
// Udev device.
//
// Provides access to udev device attributes. Device instances are returned by
// the enumerate and monitor classes.
//
class device
{
public:
    device() noexcept = default;

    device(const device&) = delete;
    device(device&& rhs) noexcept = default;

    device& operator=(const device&) = delete;
    device& operator=(device&& rhs) noexcept = default;

    bool is_valid() const noexcept { return static_cast<bool>(dev_); }
    explicit operator bool() const noexcept { return is_valid(); }

    device parent() const noexcept;
    device parent(const std::string& subsystem, const std::string& devtype = std::string()) const noexcept;

    std::string subsystem() const noexcept;
    std::string   devtype() const noexcept;
    std::string   syspath() const noexcept;
    std::string   sysname() const noexcept;
    std::string    sysnum() const noexcept;
    std::string   devnode() const noexcept;

    std::string property(const std::string&) const noexcept;
    std::string driver() const noexcept;
    enum action action() const noexcept;
    std::string sysattr(const std::string&) const noexcept;
    bool has_tag(const std::string&) const noexcept;

private:
    std::unique_ptr<impl::udev_device, impl::device_delete> dev_;

    explicit device(impl::udev_device* dev) noexcept : dev_(dev) { }
    device(const udev&, const std::string&);

    friend class enumerate;
    friend class monitor;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
