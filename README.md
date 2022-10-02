# ESP32 Data Viewer

## requirement
the software you need to run this system. install the app below on your PC/server
- mosquitto
- node-red
- xampp

## SETUP
### Run Mosquitto
first change the configuration of mosquitto on your mosquitto folder with opening the configuration files named
_mosquitto.conf_ to this :
> listener 1883
> allow_anonymous true

open the command prompt then type :

```bash
cd \path to mosquitto folder\
mosquitto -c mosquitto.conf -v
```

### Make database
1. Run apache module and Mysql module
2. open phpmyadmin
3. select import
4. choose sensor_tab1.sql
5. press import

### Run node-red
open cmd and type :

```bash
node-red
```
if you not configure the node-red yet :
1. copy all the text inside node-red-conf.txt
2. go to : localhost:1880
3. select import
4. paste the text
5. deploy


### Setup Main Device / Forwarder
1. open the progam code of the main device
2. fill the SSID and Password wifi
3. fill the ip server
4. upload the code

## RUN THE SYSTEM
### turn on the sensor node
turn on the sensor node by plug the device cable to power source (ex : computer USB, power adapter)

### turn on the main device / forwarder
1. turn on the sensor node by plug the device cable to power source (ex : computer USB, power adapter)
2. the device will run normally if its connected to WiFi and MQTT as you can see at the serial monitor
### MQTT webviewer
1. copy your ip server
2. go to : "youripserver":1880/ui  (ex: 192.168.144.33:1880/ui )
### Webserver viewer
1. copy the ip of the main device 
2. open browser and type/paste the ip of main device/forwarder


