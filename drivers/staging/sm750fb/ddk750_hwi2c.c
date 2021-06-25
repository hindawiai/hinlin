<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा USE_HW_I2C
#अगर_घोषित USE_HW_I2C
#समावेश "ddk750_chip.h"
#समावेश "ddk750_reg.h"
#समावेश "ddk750_hwi2c.h"
#समावेश "ddk750_power.h"

#घोषणा MAX_HWI2C_FIFO                  16
#घोषणा HWI2C_WAIT_TIMEOUT              0xF0000

पूर्णांक sm750_hw_i2c_init(अचिन्हित अक्षर bus_speed_mode)
अणु
	अचिन्हित पूर्णांक value;

	/* Enable GPIO 30 & 31 as IIC घड़ी & data */
	value = peek32(GPIO_MUX);

	value |= (GPIO_MUX_30 | GPIO_MUX_31);
	poke32(GPIO_MUX, value);

	/*
	 * Enable Hardware I2C घातer.
	 * TODO: Check अगर we need to enable GPIO घातer?
	 */
	sm750_enable_i2c(1);

	/* Enable the I2C Controller and set the bus speed mode */
	value = peek32(I2C_CTRL) & ~(I2C_CTRL_MODE | I2C_CTRL_EN);
	अगर (bus_speed_mode)
		value |= I2C_CTRL_MODE;
	value |= I2C_CTRL_EN;
	poke32(I2C_CTRL, value);

	वापस 0;
पूर्ण

व्योम sm750_hw_i2c_बंद(व्योम)
अणु
	अचिन्हित पूर्णांक value;

	/* Disable I2C controller */
	value = peek32(I2C_CTRL) & ~I2C_CTRL_EN;
	poke32(I2C_CTRL, value);

	/* Disable I2C Power */
	sm750_enable_i2c(0);

	/* Set GPIO 30 & 31 back as GPIO pins */
	value = peek32(GPIO_MUX);
	value &= ~GPIO_MUX_30;
	value &= ~GPIO_MUX_31;
	poke32(GPIO_MUX, value);
पूर्ण

अटल दीर्घ hw_i2c_रुको_tx_करोne(व्योम)
अणु
	अचिन्हित पूर्णांक समयout;

	/* Wait until the transfer is completed. */
	समयout = HWI2C_WAIT_TIMEOUT;
	जबतक (!(peek32(I2C_STATUS) & I2C_STATUS_TX) && (समयout != 0))
		समयout--;

	अगर (समयout == 0)
		वापस -1;

	वापस 0;
पूर्ण

/*
 *  This function ग_लिखोs data to the i2c slave device रेजिस्टरs.
 *
 *  Parameters:
 *      addr            - i2c Slave device address
 *      length          - Total number of bytes to be written to the device
 *      buf             - The buffer that contains the data to be written to the
 *                     i2c device.
 *
 *  Return Value:
 *      Total number of bytes those are actually written.
 */
अटल अचिन्हित पूर्णांक hw_i2c_ग_लिखो_data(अचिन्हित अक्षर addr,
				      अचिन्हित पूर्णांक length,
				      अचिन्हित अक्षर *buf)
अणु
	अचिन्हित अक्षर count, i;
	अचिन्हित पूर्णांक total_bytes = 0;

	/* Set the Device Address */
	poke32(I2C_SLAVE_ADDRESS, addr & ~0x01);

	/*
	 * Write data.
	 * Note:
	 *      Only 16 byte can be accessed per i2c start inकाष्ठाion.
	 */
	करो अणु
		/*
		 * Reset I2C by writing 0 to I2C_RESET रेजिस्टर to
		 * clear the previous status.
		 */
		poke32(I2C_RESET, 0);

		/* Set the number of bytes to be written */
		अगर (length < MAX_HWI2C_FIFO)
			count = length - 1;
		अन्यथा
			count = MAX_HWI2C_FIFO - 1;
		poke32(I2C_BYTE_COUNT, count);

		/* Move the data to the I2C data रेजिस्टर */
		क्रम (i = 0; i <= count; i++)
			poke32(I2C_DATA0 + i, *buf++);

		/* Start the I2C */
		poke32(I2C_CTRL, peek32(I2C_CTRL) | I2C_CTRL_CTRL);

		/* Wait until the transfer is completed. */
		अगर (hw_i2c_रुको_tx_करोne() != 0)
			अवरोध;

		/* Subtract length */
		length -= (count + 1);

		/* Total byte written */
		total_bytes += (count + 1);

	पूर्ण जबतक (length > 0);

	वापस total_bytes;
पूर्ण

/*
 *  This function पढ़ोs data from the slave device and stores them
 *  in the given buffer
 *
 *  Parameters:
 *      addr            - i2c Slave device address
 *      length          - Total number of bytes to be पढ़ो
 *      buf             - Poपूर्णांकer to a buffer to be filled with the data पढ़ो
 *                     from the slave device. It has to be the same size as the
 *                     length to make sure that it can keep all the data पढ़ो.
 *
 *  Return Value:
 *      Total number of actual bytes पढ़ो from the slave device
 */
अटल अचिन्हित पूर्णांक hw_i2c_पढ़ो_data(अचिन्हित अक्षर addr,
				     अचिन्हित पूर्णांक length,
				     अचिन्हित अक्षर *buf)
अणु
	अचिन्हित अक्षर count, i;
	अचिन्हित पूर्णांक total_bytes = 0;

	/* Set the Device Address */
	poke32(I2C_SLAVE_ADDRESS, addr | 0x01);

	/*
	 * Read data and save them to the buffer.
	 * Note:
	 *      Only 16 byte can be accessed per i2c start inकाष्ठाion.
	 */
	करो अणु
		/*
		 * Reset I2C by writing 0 to I2C_RESET रेजिस्टर to
		 * clear all the status.
		 */
		poke32(I2C_RESET, 0);

		/* Set the number of bytes to be पढ़ो */
		अगर (length <= MAX_HWI2C_FIFO)
			count = length - 1;
		अन्यथा
			count = MAX_HWI2C_FIFO - 1;
		poke32(I2C_BYTE_COUNT, count);

		/* Start the I2C */
		poke32(I2C_CTRL, peek32(I2C_CTRL) | I2C_CTRL_CTRL);

		/* Wait until transaction करोne. */
		अगर (hw_i2c_रुको_tx_करोne() != 0)
			अवरोध;

		/* Save the data to the given buffer */
		क्रम (i = 0; i <= count; i++)
			*buf++ = peek32(I2C_DATA0 + i);

		/* Subtract length by 16 */
		length -= (count + 1);

		/* Number of bytes पढ़ो. */
		total_bytes += (count + 1);

	पूर्ण जबतक (length > 0);

	वापस total_bytes;
पूर्ण

/*
 *  This function पढ़ोs the slave device's रेजिस्टर
 *
 *  Parameters:
 *      deviceAddress   - i2c Slave device address which रेजिस्टर
 *                        to be पढ़ो from
 *      रेजिस्टरIndex   - Slave device's रेजिस्टर to be पढ़ो
 *
 *  Return Value:
 *      Register value
 */
अचिन्हित अक्षर sm750_hw_i2c_पढ़ो_reg(अचिन्हित अक्षर addr, अचिन्हित अक्षर reg)
अणु
	अचिन्हित अक्षर value = 0xFF;

	अगर (hw_i2c_ग_लिखो_data(addr, 1, &reg) == 1)
		hw_i2c_पढ़ो_data(addr, 1, &value);

	वापस value;
पूर्ण

/*
 *  This function ग_लिखोs a value to the slave device's रेजिस्टर
 *
 *  Parameters:
 *      deviceAddress   - i2c Slave device address which रेजिस्टर
 *                        to be written
 *      रेजिस्टरIndex   - Slave device's रेजिस्टर to be written
 *      data            - Data to be written to the रेजिस्टर
 *
 *  Result:
 *          0   - Success
 *         -1   - Fail
 */
पूर्णांक sm750_hw_i2c_ग_लिखो_reg(अचिन्हित अक्षर addr,
			   अचिन्हित अक्षर reg,
			   अचिन्हित अक्षर data)
अणु
	अचिन्हित अक्षर value[2];

	value[0] = reg;
	value[1] = data;
	अगर (hw_i2c_ग_लिखो_data(addr, 2, value) == 2)
		वापस 0;

	वापस -1;
पूर्ण

#पूर्ण_अगर
