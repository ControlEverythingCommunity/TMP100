// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// TMP100
// This code is designed to work with the TMP100_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Temperature?sku=TMP100_I2CS#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class TMP100
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus Bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, TMP100 I2C address is 0x4F(79)
		I2CDevice device = Bus.getDevice(0x4F);

		// Select configuration register
		// Continuous conversion, comparator mode, 12-bit resolution
		device.write(0x01, (byte)0x60);
		Thread.sleep(500);

		// Read 2 bytes of data
		// temp msb, temp lsb
		byte[] data = new byte[2];
		device.read(0x00, data, 0, 2);

		// Convert the data to 12-bits
		int temp = ((data[0] & 0xFF) * 256 + (data[1] & 0xF0)) / 16;
		if(temp > 2047)
		{
			temp -= 4096;
		}
		double cTemp = temp * 0.0625;
		double fTemp = cTemp * 1.8 + 32;

		// Output data to screen
		System.out.printf("Temperature in Celsius : %.2f C %n", cTemp);
		System.out.printf("Temperature in Fahrenheit : %.2f F %n", fTemp);
	}
}
