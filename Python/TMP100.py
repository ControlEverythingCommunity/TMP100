# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# TMP100
# This code is designed to work with the TMP100_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Temperature?sku=TMP100_I2CS#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# TMP100 address, 0x4F(79)
# Select configuration register, 0x01(01)
#		0x60(96)	Continuous conversion, comparator mode, 12-bit resolution
bus.write_byte_data(0x4F, 0x01, 0x60)

time.sleep(0.5)

# TMP100 address, 0x4F(79)
# Read data back from 0x00(00), 2 bytes
# temp MSB, temp LSB
data = bus.read_i2c_block_data(0x4F, 0x00, 2)

# Convert the data to 12-bits
temp = (data[0] * 256 + (data[1] & 0xF0)) / 16
if temp > 2047 :
	temp -= 4096
cTemp = temp * 0.0625
fTemp = cTemp * 1.8 + 32

# Output data to screen
print "Temperature in Celsius is : %.2f C" %cTemp
print "Temperature in Fahrenheit is : %.2f F" %fTemp
