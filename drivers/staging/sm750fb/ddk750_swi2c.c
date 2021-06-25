<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *         Copyright (c) 2007 by Silicon Motion, Inc. (SMI)
 *
 *  swi2c.c --- SM750/SM718 DDK
 *  This file contains the source code क्रम I2C using software
 *  implementation.
 */

#समावेश "ddk750_chip.h"
#समावेश "ddk750_reg.h"
#समावेश "ddk750_swi2c.h"
#समावेश "ddk750_power.h"

/*
 * I2C Software Master Driver:
 * ===========================
 * Each i2c cycle is split पूर्णांकo 4 sections. Each of these section marks
 * a poपूर्णांक in समय where the SCL or SDA may be changed.
 *
 * 1 Cycle == |  Section I. |  Section 2. |  Section 3. |  Section 4. |
 *            +-------------+-------------+-------------+-------------+
 *            | SCL set LOW |SCL no change| SCL set HIGH|SCL no change|
 *
 *                                          ____________ _____________
 * SCL == XXXX _____________ ____________ /
 *
 * I.e. the SCL may only be changed in section 1. and section 3. जबतक
 * the SDA may only be changed in section 2. and section 4. The table
 * below gives the changes क्रम these 2 lines in the varios sections.
 *
 * Section changes Table:
 * ======================
 * blank = no change, L = set bit LOW, H = set bit HIGH
 *
 *                                | 1.| 2.| 3.| 4.|
 *                 ---------------+---+---+---+---+
 *                 Tx Start   SDA |   | H |   | L |
 *                            SCL | L |   | H |   |
 *                 ---------------+---+---+---+---+
 *                 Tx Stop    SDA |   | L |   | H |
 *                            SCL | L |   | H |   |
 *                 ---------------+---+---+---+---+
 *                 Tx bit H   SDA |   | H |   |   |
 *                            SCL | L |   | H |   |
 *                 ---------------+---+---+---+---+
 *                 Tx bit L   SDA |   | L |   |   |
 *                            SCL | L |   | H |   |
 *                 ---------------+---+---+---+---+
 *
 */

/* GPIO pins used क्रम this I2C. It ranges from 0 to 63. */
अटल अचिन्हित अक्षर sw_i2c_clk_gpio = DEFAULT_I2C_SCL;
अटल अचिन्हित अक्षर sw_i2c_data_gpio = DEFAULT_I2C_SDA;

/*
 *  Below is the variable declaration क्रम the GPIO pin रेजिस्टर usage
 *  क्रम the i2c Clock and i2c Data.
 *
 *  Note:
 *      Notice that the GPIO usage क्रम the i2c घड़ी and i2c Data are
 *      separated. This is to make this code flexible enough when
 *      two separate GPIO pins क्रम the घड़ी and data are located
 *      in two dअगरferent GPIO रेजिस्टर set (worst हाल).
 */

/* i2c Clock GPIO Register usage */
अटल अचिन्हित दीर्घ sw_i2c_clk_gpio_mux_reg = GPIO_MUX;
अटल अचिन्हित दीर्घ sw_i2c_clk_gpio_data_reg = GPIO_DATA;
अटल अचिन्हित दीर्घ sw_i2c_clk_gpio_data_dir_reg = GPIO_DATA_सूचीECTION;

/* i2c Data GPIO Register usage */
अटल अचिन्हित दीर्घ sw_i2c_data_gpio_mux_reg = GPIO_MUX;
अटल अचिन्हित दीर्घ sw_i2c_data_gpio_data_reg = GPIO_DATA;
अटल अचिन्हित दीर्घ sw_i2c_data_gpio_data_dir_reg = GPIO_DATA_सूचीECTION;

/*
 *  This function माला_दो a delay between command
 */
अटल व्योम sw_i2c_रुको(व्योम)
अणु
	/* find a bug:
	 * peekIO method works well beक्रमe suspend/resume
	 * but after suspend, peekIO(0x3ce,0x61) & 0x10
	 * always be non-zero,which makes the जबतक loop
	 * never finish.
	 * use non-ultimate क्रम loop below is safe
	 */

    /* Change रुको algorithm to use PCI bus घड़ी,
     * it's more reliable than counter loop ..
     * ग_लिखो 0x61 to 0x3ce and पढ़ो from 0x3cf
     */
	पूर्णांक i, पंचांगp;

	क्रम (i = 0; i < 600; i++) अणु
		पंचांगp = i;
		पंचांगp += i;
	पूर्ण
पूर्ण

/*
 *  This function set/reset the SCL GPIO pin
 *
 *  Parameters:
 *      value    - Bit value to set to the SCL or SDA (0 = low, 1 = high)
 *
 *  Notes:
 *      When setting SCL to high, just set the GPIO as input where the pull up
 *      resistor will pull the संकेत up. Do not use software to pull up the
 *      संकेत because the i2c will fail when other device try to drive the
 *      संकेत due to SM50x will drive the संकेत to always high.
 */
अटल व्योम sw_i2c_scl(अचिन्हित अक्षर value)
अणु
	अचिन्हित दीर्घ gpio_data;
	अचिन्हित दीर्घ gpio_dir;

	gpio_dir = peek32(sw_i2c_clk_gpio_data_dir_reg);
	अगर (value) अणु    /* High */
		/*
		 * Set direction as input. This will स्वतःmatically
		 * pull the संकेत up.
		 */
		gpio_dir &= ~(1 << sw_i2c_clk_gpio);
		poke32(sw_i2c_clk_gpio_data_dir_reg, gpio_dir);
	पूर्ण अन्यथा अणु        /* Low */
		/* Set the संकेत करोwn */
		gpio_data = peek32(sw_i2c_clk_gpio_data_reg);
		gpio_data &= ~(1 << sw_i2c_clk_gpio);
		poke32(sw_i2c_clk_gpio_data_reg, gpio_data);

		/* Set direction as output */
		gpio_dir |= (1 << sw_i2c_clk_gpio);
		poke32(sw_i2c_clk_gpio_data_dir_reg, gpio_dir);
	पूर्ण
पूर्ण

/*
 *  This function set/reset the SDA GPIO pin
 *
 *  Parameters:
 *      value    - Bit value to set to the SCL or SDA (0 = low, 1 = high)
 *
 *  Notes:
 *      When setting SCL to high, just set the GPIO as input where the pull up
 *      resistor will pull the संकेत up. Do not use software to pull up the
 *      संकेत because the i2c will fail when other device try to drive the
 *      संकेत due to SM50x will drive the संकेत to always high.
 */
अटल व्योम sw_i2c_sda(अचिन्हित अक्षर value)
अणु
	अचिन्हित दीर्घ gpio_data;
	अचिन्हित दीर्घ gpio_dir;

	gpio_dir = peek32(sw_i2c_data_gpio_data_dir_reg);
	अगर (value) अणु    /* High */
		/*
		 * Set direction as input. This will स्वतःmatically
		 * pull the संकेत up.
		 */
		gpio_dir &= ~(1 << sw_i2c_data_gpio);
		poke32(sw_i2c_data_gpio_data_dir_reg, gpio_dir);
	पूर्ण अन्यथा अणु        /* Low */
		/* Set the संकेत करोwn */
		gpio_data = peek32(sw_i2c_data_gpio_data_reg);
		gpio_data &= ~(1 << sw_i2c_data_gpio);
		poke32(sw_i2c_data_gpio_data_reg, gpio_data);

		/* Set direction as output */
		gpio_dir |= (1 << sw_i2c_data_gpio);
		poke32(sw_i2c_data_gpio_data_dir_reg, gpio_dir);
	पूर्ण
पूर्ण

/*
 *  This function पढ़ो the data from the SDA GPIO pin
 *
 *  Return Value:
 *      The SDA data bit sent by the Slave
 */
अटल अचिन्हित अक्षर sw_i2c_पढ़ो_sda(व्योम)
अणु
	अचिन्हित दीर्घ gpio_dir;
	अचिन्हित दीर्घ gpio_data;
	अचिन्हित दीर्घ dir_mask = 1 << sw_i2c_data_gpio;

	/* Make sure that the direction is input (High) */
	gpio_dir = peek32(sw_i2c_data_gpio_data_dir_reg);
	अगर ((gpio_dir & dir_mask) != ~dir_mask) अणु
		gpio_dir &= ~(1 << sw_i2c_data_gpio);
		poke32(sw_i2c_data_gpio_data_dir_reg, gpio_dir);
	पूर्ण

	/* Now पढ़ो the SDA line */
	gpio_data = peek32(sw_i2c_data_gpio_data_reg);
	अगर (gpio_data & (1 << sw_i2c_data_gpio))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/*
 *  This function sends ACK संकेत
 */
अटल व्योम sw_i2c_ack(व्योम)
अणु
	वापस;  /* Single byte पढ़ो is ok without it. */
पूर्ण

/*
 *  This function sends the start command to the slave device
 */
अटल व्योम sw_i2c_start(व्योम)
अणु
	/* Start I2C */
	sw_i2c_sda(1);
	sw_i2c_scl(1);
	sw_i2c_sda(0);
पूर्ण

/*
 *  This function sends the stop command to the slave device
 */
अटल व्योम sw_i2c_stop(व्योम)
अणु
	/* Stop the I2C */
	sw_i2c_scl(1);
	sw_i2c_sda(0);
	sw_i2c_sda(1);
पूर्ण

/*
 *  This function ग_लिखोs one byte to the slave device
 *
 *  Parameters:
 *      data    - Data to be ग_लिखो to the slave device
 *
 *  Return Value:
 *       0   - Success
 *      -1   - Fail to ग_लिखो byte
 */
अटल दीर्घ sw_i2c_ग_लिखो_byte(अचिन्हित अक्षर data)
अणु
	अचिन्हित अक्षर value = data;
	पूर्णांक i;

	/* Sending the data bit by bit */
	क्रम (i = 0; i < 8; i++) अणु
		/* Set SCL to low */
		sw_i2c_scl(0);

		/* Send data bit */
		अगर ((value & 0x80) != 0)
			sw_i2c_sda(1);
		अन्यथा
			sw_i2c_sda(0);

		sw_i2c_रुको();

		/* Toggle clk line to one */
		sw_i2c_scl(1);
		sw_i2c_रुको();

		/* Shअगरt byte to be sent */
		value = value << 1;
	पूर्ण

	/* Set the SCL Low and SDA High (prepare to get input) */
	sw_i2c_scl(0);
	sw_i2c_sda(1);

	/* Set the SCL High क्रम ack */
	sw_i2c_रुको();
	sw_i2c_scl(1);
	sw_i2c_रुको();

	/* Read SDA, until SDA==0 */
	क्रम (i = 0; i < 0xff; i++) अणु
		अगर (!sw_i2c_पढ़ो_sda())
			अवरोध;

		sw_i2c_scl(0);
		sw_i2c_रुको();
		sw_i2c_scl(1);
		sw_i2c_रुको();
	पूर्ण

	/* Set the SCL Low and SDA High */
	sw_i2c_scl(0);
	sw_i2c_sda(1);

	अगर (i < 0xff)
		वापस 0;
	अन्यथा
		वापस -1;
पूर्ण

/*
 *  This function पढ़ोs one byte from the slave device
 *
 *  Parameters:
 *      ack    - Flag to indicate either to send the acknowledge
 *            message to the slave device or not
 *
 *  Return Value:
 *      One byte data पढ़ो from the Slave device
 */
अटल अचिन्हित अक्षर sw_i2c_पढ़ो_byte(अचिन्हित अक्षर ack)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर data = 0;

	क्रम (i = 7; i >= 0; i--) अणु
		/* Set the SCL to Low and SDA to High (Input) */
		sw_i2c_scl(0);
		sw_i2c_sda(1);
		sw_i2c_रुको();

		/* Set the SCL High */
		sw_i2c_scl(1);
		sw_i2c_रुको();

		/* Read data bits from SDA */
		data |= (sw_i2c_पढ़ो_sda() << i);
	पूर्ण

	अगर (ack)
		sw_i2c_ack();

	/* Set the SCL Low and SDA High */
	sw_i2c_scl(0);
	sw_i2c_sda(1);

	वापस data;
पूर्ण

/*
 * This function initializes GPIO port क्रम SW I2C communication.
 *
 * Parameters:
 *      clk_gpio      - The GPIO pin to be used as i2c SCL
 *      data_gpio     - The GPIO pin to be used as i2c SDA
 *
 * Return Value:
 *      -1   - Fail to initialize the i2c
 *       0   - Success
 */
अटल दीर्घ sm750le_i2c_init(अचिन्हित अक्षर clk_gpio, अचिन्हित अक्षर data_gpio)
अणु
	पूर्णांक i;

	/* Initialize the GPIO pin क्रम the i2c Clock Register */
	sw_i2c_clk_gpio_data_reg = GPIO_DATA_SM750LE;
	sw_i2c_clk_gpio_data_dir_reg = GPIO_DATA_सूचीECTION_SM750LE;

	/* Initialize the Clock GPIO Offset */
	sw_i2c_clk_gpio = clk_gpio;

	/* Initialize the GPIO pin क्रम the i2c Data Register */
	sw_i2c_data_gpio_data_reg = GPIO_DATA_SM750LE;
	sw_i2c_data_gpio_data_dir_reg = GPIO_DATA_सूचीECTION_SM750LE;

	/* Initialize the Data GPIO Offset */
	sw_i2c_data_gpio = data_gpio;

	/* Note that SM750LE करोn't have GPIO MUX and घातer is always on */

	/* Clear the i2c lines. */
	क्रम (i = 0; i < 9; i++)
		sw_i2c_stop();

	वापस 0;
पूर्ण

/*
 * This function initializes the i2c attributes and bus
 *
 * Parameters:
 *      clk_gpio      - The GPIO pin to be used as i2c SCL
 *      data_gpio     - The GPIO pin to be used as i2c SDA
 *
 * Return Value:
 *      -1   - Fail to initialize the i2c
 *       0   - Success
 */
दीर्घ sm750_sw_i2c_init(अचिन्हित अक्षर clk_gpio, अचिन्हित अक्षर data_gpio)
अणु
	पूर्णांक i;

	/*
	 * Return 0 अगर the GPIO pins to be used is out of range. The
	 * range is only from [0..63]
	 */
	अगर ((clk_gpio > 31) || (data_gpio > 31))
		वापस -1;

	अगर (sm750_get_chip_type() == SM750LE)
		वापस sm750le_i2c_init(clk_gpio, data_gpio);

	/* Initialize the GPIO pin क्रम the i2c Clock Register */
	sw_i2c_clk_gpio_mux_reg = GPIO_MUX;
	sw_i2c_clk_gpio_data_reg = GPIO_DATA;
	sw_i2c_clk_gpio_data_dir_reg = GPIO_DATA_सूचीECTION;

	/* Initialize the Clock GPIO Offset */
	sw_i2c_clk_gpio = clk_gpio;

	/* Initialize the GPIO pin क्रम the i2c Data Register */
	sw_i2c_data_gpio_mux_reg = GPIO_MUX;
	sw_i2c_data_gpio_data_reg = GPIO_DATA;
	sw_i2c_data_gpio_data_dir_reg = GPIO_DATA_सूचीECTION;

	/* Initialize the Data GPIO Offset */
	sw_i2c_data_gpio = data_gpio;

	/* Enable the GPIO pins क्रम the i2c Clock and Data (GPIO MUX) */
	poke32(sw_i2c_clk_gpio_mux_reg,
	       peek32(sw_i2c_clk_gpio_mux_reg) & ~(1 << sw_i2c_clk_gpio));
	poke32(sw_i2c_data_gpio_mux_reg,
	       peek32(sw_i2c_data_gpio_mux_reg) & ~(1 << sw_i2c_data_gpio));

	/* Enable GPIO घातer */
	sm750_enable_gpio(1);

	/* Clear the i2c lines. */
	क्रम (i = 0; i < 9; i++)
		sw_i2c_stop();

	वापस 0;
पूर्ण

/*
 *  This function पढ़ोs the slave device's रेजिस्टर
 *
 *  Parameters:
 *      addr   - i2c Slave device address which रेजिस्टर
 *                        to be पढ़ो from
 *      reg    - Slave device's रेजिस्टर to be पढ़ो
 *
 *  Return Value:
 *      Register value
 */
अचिन्हित अक्षर sm750_sw_i2c_पढ़ो_reg(अचिन्हित अक्षर addr, अचिन्हित अक्षर reg)
अणु
	अचिन्हित अक्षर data;

	/* Send the Start संकेत */
	sw_i2c_start();

	/* Send the device address */
	sw_i2c_ग_लिखो_byte(addr);

	/* Send the रेजिस्टर index */
	sw_i2c_ग_लिखो_byte(reg);

	/* Get the bus again and get the data from the device पढ़ो address */
	sw_i2c_start();
	sw_i2c_ग_लिखो_byte(addr + 1);
	data = sw_i2c_पढ़ो_byte(1);

	/* Stop swI2C and release the bus */
	sw_i2c_stop();

	वापस data;
पूर्ण

/*
 *  This function ग_लिखोs a value to the slave device's रेजिस्टर
 *
 *  Parameters:
 *      addr            - i2c Slave device address which रेजिस्टर
 *                        to be written
 *      reg             - Slave device's रेजिस्टर to be written
 *      data            - Data to be written to the रेजिस्टर
 *
 *  Result:
 *          0   - Success
 *         -1   - Fail
 */
दीर्घ sm750_sw_i2c_ग_लिखो_reg(अचिन्हित अक्षर addr,
			    अचिन्हित अक्षर reg,
			    अचिन्हित अक्षर data)
अणु
	दीर्घ ret = 0;

	/* Send the Start संकेत */
	sw_i2c_start();

	/* Send the device address and पढ़ो the data. All should वापस success
	 * in order क्रम the writing processed to be successful
	 */
	अगर ((sw_i2c_ग_लिखो_byte(addr) != 0) ||
	    (sw_i2c_ग_लिखो_byte(reg) != 0) ||
	    (sw_i2c_ग_लिखो_byte(data) != 0)) अणु
		ret = -1;
	पूर्ण

	/* Stop i2c and release the bus */
	sw_i2c_stop();

	वापस ret;
पूर्ण
