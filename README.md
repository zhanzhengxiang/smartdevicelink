GENIVI SmartDeviceLink
======================
forked from http://git.projects.genivi.org/smartdevicelink.git

How to build the android app
======================
Install adt from http://developer.android.com/sdk/index.html

Launch the eclipse

Install Android 2.2 sdk

Import projects from SDL_Android

If you see two projects on the project pane, you've done it.

Connect android phone.

Compile all projects.

Run SmartDeviceLinkTester


How to build the head unit app
======================
Ubuntu linux is recommended

apt-get install build-essential libssl-dev cmake libbluetooth-dev chromium-browser

cd SDL_Core

cmake .

make

If you see the chromium browser and a warning message, it works.

###How to enable the log
Append "-DDEBUG_ON -DDEBUG_MB_ON" to CMAKE_CXX_FLAGS in SDL_Core/CMakeList.txt

Repeate above procedure

Logs are diffused to 3 ways - stdout, SmartDeviceLinkCore.log, and SmartDeivceLinkCoreWarn.log

How to test via WIFI
======================
### Starting the head unit app.
cd SDL_Core/src/appMain

./smartDeviceLinkCore

### Starting the android app.
Click SmartDeviceLinkTester

You'll see 'Please select properties' dialogue.

(If you don't see, click menu and Exit. and run it again.)

Check WIFI

Type the IP address of the box that runs the head unit app.

Type '12345' on Port.

Click OK

### How to check
If they are linked, the android app plays the music.


How to test via BlueTooth
======================
### Starting the head unit app.
cd SDL_Core/src/appMain

./smartDeviceLinkCore

### Starting the android app.
Click SmartDeviceLinkTester

You'll see 'Please select properties' dialogue.

(If you don't see, click menu and Exit. and run it again.)

Check Bluetooth

Click OK

### Paring and Connection
Pair the phone and the box.

Let them stay connected.(They are easily disconnected)

### How to check
If they are linked, the android app plays the music.

How to play Stitcher via BlueTooth
======================
### Starting the head unit app.
cd SDL_Core/src/appMain

./smartDeviceLinkCore

Click 'i' button at the bottom.

### Starting Stitcher.
Click Stitcher.

### Paring and Connection
Pair the phone and the box.

Let them stay connected.(They are easily disconnected)

### How to check
The browser at the head unit adds 'Stitcher' button.
Click the 'Stitcher' button and control the Stitcher.
