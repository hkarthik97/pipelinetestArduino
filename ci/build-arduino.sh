#!/bin/bash
# Exit immediately if a command exits with a non-zero status.
set -e
# Enable the globstar shell option
shopt -s globstar
# Make sure we are inside the github workspace
cd $GITHUB_WORKSPACE
# Create directories
mkdir $HOME/Arduino
mkdir $HOME/Arduino/libraries
# Install Arduino IDE
export PATH=$PATH:$GITHUB_WORKSPACE/bin
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
arduino-cli config init
arduino-cli core update-index
# Install Arduino AVR core
arduino-cli core install arduino:avr
/opt/arduino/arduino --pref "boardsmanager.additional.urls=http://arduino.esp8266.com/stable/package_esp8266com_index.json" --save-prefs
/opt/arduino/arduino --install-boards esp8266:esp8266 --save-prefs
# Link Arduino library
ln -s $GITHUB_WORKSPACE $HOME/Arduino/libraries/CI_Test_Library
# Compile all *.ino files for the Arduino Uno
for f in **/*.ino ; do
    /opt/arduino/arduino -v --verify --board esp8266:esp8266:nodemcu $f
done