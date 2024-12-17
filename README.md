# Renesas Power Chip Firmware Upgrade Utils

## Directories in This Project

|Directory |Description                          |
|----------|-------------------------------------|
|src       |Program Source                       |
|inc       |Header files                         |
|doc       |Reference documents                  |
|config    |Configuration file of various boards |

## How Config Files Generated
Configuration files(*.hex type) are provided by hardware colleagues. 

When generating the configuration file they need to specify the channel(Configuration ID) to burn,the final effective Configuration ID is based on the hardware design.

## How to Use
isl-uitl i2c-bus slave-addr [file-name]

i2c-bus: 

I2C controller that PMIC attached to    

slave-addr:

Slave address is base on hardware design, it is best to be told in advance by the hardware colleagues.
    
file-name: 

The configuration hex file you want to burn.

## List of PMIC-I2C Topology
|Boards                      |Processor |I2C Bus Number |Slave Address |
|----------------------------|----------|---------------|--------------|
|Pisces                      |SG2042    |0 and 4(2 way) |0x5c          |
|SG2044 EVB v1.1             |SG2044    |0              |0x60          |
|SG2044 EVB v1.0             |SG2044    |0              |0x60          |

## Examples
To query the power chip's device id, reversion id and the NVM slots(remaining number of programming times):

    sudo isl-util 0 0x5c

In addition to the above functions, you want to burn the configuration hex file to power chip(upgrade the chip) :

    sudo isl-util 0 0x5c ISL68127-1v00-0x5C-20240723-pisces.hex
   
