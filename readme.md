# Rosita's adaptive cruise control
## Rosita is my ebike, and she deserves an adaptive cruise control. Let's make it
![rosita's photo](docs/photo_2019-12-22_16-25-09.jpg)

## Pendings
### A list
- Test arduino app
 - Red led when breaking
 - Green led when throttling up
 - lcd distance / throttling rate
- Make a provisory mount
- measure throttle with power and confirm protocol
- implement throttle —probably double hall 48v– emulation
 
### B list
 - Add a laser in case that radar direction is hard to figureout

### C list
 - Go to Chimbarongo and buy a wicker basquet

## Hardware used
 - [OPS243-C FMCW and Doppler Radar Sensor](https://omnipresense.com/product/ops243-c-fmcw-and-doppler-radar-sensor/)
 - [Arduino Mega 2560](https://store.arduino.cc/usa/mega-2560-r3)

## Saferity check list

### On arduino
 - What happen if serial connection to radar is lost?
 - What happen if serial read is not valid?
 - What happen if serial read takes longer than expected?