A reactor is a design pattern for synchronous event handling, that allows
event handlers to be associated with sets of events.

## Proposal ##
Design an general purposee reactor framework that can be used with a wide
variety of event sources, such as:

  * Timers
    * Operating system
      * Network
      * File system
      * Signals?
    * Input devices
      * Keyboard
      * Mouse
      * Touch
  * Sensors
    * Accelerometer
    * Proximity
    * Light
    * Moisture
    * Gyroscope
    * etc...

The particular data associated with each event should be specific to the
device.

The event system should be "pluggable", meaning that a programmer should
configure the sets of events being received by the application.

Ease of use is a must. Subclassing event handlers is not necessarily the best
design for a reactive event handling system.

## Considerations ##
Can a single reactor be designed to accommodate all of these devices in a
single framework? Do we need different reactors to handle events from different
sources?

Should the library have a single reactor or allow multiple reactors? What are
the thread safety considerations of this style of program?

Almost every event will have its own design considerations. For example, what
is the best way to indicate a pressed key? Using letters may not be appropriate
if a different keyboard layout is in use. What kind of information should be
associated with timer events? What kinds of file system events should be
supported?

## Links ##

ACE Reactor
libevent
SDML
cppnetlib