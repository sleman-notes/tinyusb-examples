# Tinyusb Examples

This repo will use TinyUSB v0.21.0 and STM32F411 (Blackpill Weact).

## Concepts

The most important concepts about USB are:

- **Host and device:** the PC is generally the host and is in charge of
everything, the device only responds.

- **Enumeration:** when you plug the device in the cable, the PC asks "who are
you?" and the device answers with descriptors.

- **Descriptors:** byte tables that describe the device, like:
    - VID/PID (vendor and product IDs)
    - How many interfaces it has
    - Which class each interface belongs to
    - Which endpoints it uses
    
**Note:** with tinyusb the descriptors are written with the help of ready-made
*macros.

- **Endpoints:** the data "channels", Endpoint - is the control endpoint (used
for enumeration), the others are numbered and have a direction:
    - IN (device to PC, e.g. 0x81)
    - OUT (PC to device, e.g. 0x02)

- **Classes:** standardized protocols that the operation system already
understands, without custom drivers. A virtual serial port is the **CDC-ACM**
class. It uses two interfaces: a control interface with a notification endpoint,
and a data interface with one IN and one OUT endpoint. Tinyusb generates all of
this with a single macro. Windows 10+, Linux and macOS support CDC natively, so
the board shows up as COMx or /dev/ttyACM0, with no driver installation.

## The TinyUSB

TinyUSB's architecture is simple. Every USB interrupt only queues an event, the
actual processing happens outside the interrupt, inside a function called
"tud_task()" that you call from your main loop. This makes the library safe and
predictable.

You have to provide:

1. tusb_config.h: tells TinyUSB which microcontroller, which OS (can be none),
and which classes to enable.
2. usb_descriptors.c: the descriptors and the callback functions that return
them.
3. Integration: hardware setup (clock, pins), tusb_init() at startup, tud_task()
in the loop, and forwarding the USB interupt.
4. Your application: using the "tud_cdc_*" API for write and read for example.

Callbacks in TinyUSB are **not registered**. You simply implement functions with
the prescribed names and the stack calls them automatically. Naming convention:
"tud_" for device, "tuh_" for host. If you forget a mandatory callback, you will
get an undefined reference as linker error.

## Why the USB needs exactly 48 MHz

The USB cable has no clock wire. It carries only two data wires, so the device
has to figure out the timing by itself. The trick is to look at the line much
faster than the data arrives, the USB hardware checks it **four times per bit**.
That way it always finds the middle of the bit, which is where the signal is
most stable and safest to read. Full speed USB sends 12 million bits per second,
and four looks per bit gives 4 x 12 = 48 MHz, so from there comes the number.
Also it's important to note that the spec of USB says that a devive should have
only 0.25% of error.

## References

- [TinyUSB a simple Tutorial](https://www.pschatzmann.ch/home/2021/02/19/tinyusb-a-simple-tutorial/)
- [TinyUSB - Getting Started](https://docs.tinyusb.org/en/latest/getting_started.html)
- [TinyUSB - Repository](https://github.com/hathach/tinyusb)
    - /examples/device/cdc_msc/src/tusb_config.h
    - /hw/bsp/stm32f4
