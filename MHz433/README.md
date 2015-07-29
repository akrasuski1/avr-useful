Recently I bought a pair of cheap 433MHz modules - FS1000A and XY-MK-5V. They are known for being hard to work with -
in Arduino, there exists a special library called VirtualWire that everyone seems to use, as otherwise modules are
barely usable. I took a look into its source code, but then I noticed my use case is different - I don't need to
send digital data, getting corrupted even via one bad bit. No, I wanted to create a remote control for my future
robots, so all I really needed was sending analog data from joystick or two. So I created this library. It uses
similar mechanism as other real life RC controllers, but it's more suited for those particular chips (the 
automatic gain control was quite annoying when it was getting everywhere). Feel free to use it.
