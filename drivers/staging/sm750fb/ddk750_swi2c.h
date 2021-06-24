<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *         Copyright (c) 2007 by Silicon Motion, Inc. (SMI)
 *
 *  swi2c.h --- SM750/SM718 DDK
 *  This file contains the definitions क्रम i2c using software
 *  implementation.
 *
 */

#अगर_अघोषित _SWI2C_H_
#घोषणा _SWI2C_H_

/* Default i2c CLK and Data GPIO. These are the शेष i2c pins */
#घोषणा DEFAULT_I2C_SCL                     30
#घोषणा DEFAULT_I2C_SDA                     31

/*
 * This function initializes the i2c attributes and bus
 *
 * Parameters:
 *      i2cClkGPIO  - The GPIO pin to be used as i2c SCL
 *      i2cDataGPIO - The GPIO pin to be used as i2c SDA
 *
 * Return Value:
 *      -1   - Fail to initialize the i2c
 *       0   - Success
 */
दीर्घ sm750_sw_i2c_init(अचिन्हित अक्षर clk_gpio, अचिन्हित अक्षर data_gpio);

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
अचिन्हित अक्षर sm750_sw_i2c_पढ़ो_reg(अचिन्हित अक्षर addr, अचिन्हित अक्षर reg);

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
			    अचिन्हित अक्षर data);

#पूर्ण_अगर  /* _SWI2C_H_ */
