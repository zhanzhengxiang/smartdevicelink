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
###Compiling for PC-easy way
Ubuntu linux is recommended

./configure

(If it is the first time to run configure, ./confgure --env)

make -C build -j4

###Compiling for PC-custom way
Ubuntu linux is recommended

apt-get install build-essential libssl-dev cmake libbluetooth-dev chromium-browser

cd SDL_Core

mkdir build

cd build

cmake ..

make -j4

cd ..

If you see the chromium browser and a warning message, it works.


###Cross-compiling via Poky toolchain
Ubuntu linux is recommended

####Download poky toolchain from following site
64bit linux

http://downloads.yoctoproject.org/releases/yocto/yocto-1.5.1/toolchain/x86_64/poky-eglibc-x86_64-core-image-sato-armv7a-vfp-neon-toolchain-1.5.1.sh

####32bit linux

http://downloads.yoctoproject.org/releases/yocto/yocto-1.5.1/toolchain/i686/poky-eglibc-i686-core-image-sato-armv7a-vfp-neon-toolchain-1.5.1.sh

./configure poky

(If it is the first time to run configure, ./confgure imx6 --env)

make -C build -j4

###Cross-compiling for iMX6
Ubuntu linux is recommended

you need a root file system and a cross tool chain for iMX6

./configure imx6

(If it is the first time to run configure, ./confgure imx6 --env)

make -C build -j4

###How to enable the log
Append "-DDEBUG_ON -DDEBUG_MB_ON" to CMAKE_CXX_FLAGS in SDL_Core/CMakeList.txt

Repeate above procedure

Logs are diffused to 3 ways - stdout, SmartDeviceLinkCore.log, and SmartDeivceLinkCoreWarn.log

How to test via WIFI
======================
### Starting the head unit app.
cd SDL_Core/build/src/appMain

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
cd SDL_Core/build/src/appMain

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
### Paring and Connection
Pair the phone and the box.

### Starting Stitcher.
Take an android phone.

Goto Google play store and download Stitcher.

Start Stitcher.

### Starting the android app.
Click SmartDeviceLinkTester

You'll see 'Please select properties' dialogue.

(If you don't see, click menu and Exit. and run it again.)

Check Bluetooth

Click OK

Click the menu button

Click startProxy

Click Allow button on the dialogue box

### Starting the head unit app.
cd SDL_Core/build/src/appMain

./smartDeviceLinkCore

Click 'i' button at the bottom.

Click 'Change Devices' button.

Wait until you see a phone item on the screen

Click the phone item

Click 'Stitcher-'

### How to check
The browser at the head unit adds 'Stitcher' button.
Click the 'Stitcher' button and control the Stitcher.
