<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX25821 PCIe bridge
 *
 *  Copyright (C) 2009 Conexant Systems Inc.
 *  Authors  <shu.lin@conexant.com>, <hiep.huynh@conexant.com>
 */

#समावेश <linux/module.h>
#समावेश "cx25821.h"

/********************* GPIO stuffs *********************/
व्योम cx25821_set_gpiopin_direction(काष्ठा cx25821_dev *dev,
				   पूर्णांक pin_number, पूर्णांक pin_logic_value)
अणु
	पूर्णांक bit = pin_number;
	u32 gpio_oe_reg = GPIO_LO_OE;
	u32 gpio_रेजिस्टर = 0;
	u32 value = 0;

	/* Check क्रम valid pinNumber */
	अगर (pin_number >= 47)
		वापस;

	अगर (pin_number > 31) अणु
		bit = pin_number - 31;
		gpio_oe_reg = GPIO_HI_OE;
	पूर्ण
	/* Here we will make sure that the GPIOs 0 and 1 are output. keep the
	 * rest as is */
	gpio_रेजिस्टर = cx_पढ़ो(gpio_oe_reg);

	अगर (pin_logic_value == 1)
		value = gpio_रेजिस्टर | Set_GPIO_Bit(bit);
	अन्यथा
		value = gpio_रेजिस्टर & Clear_GPIO_Bit(bit);

	cx_ग_लिखो(gpio_oe_reg, value);
पूर्ण
EXPORT_SYMBOL(cx25821_set_gpiopin_direction);

अटल व्योम cx25821_set_gpiopin_logicvalue(काष्ठा cx25821_dev *dev,
					   पूर्णांक pin_number, पूर्णांक pin_logic_value)
अणु
	पूर्णांक bit = pin_number;
	u32 gpio_reg = GPIO_LO;
	u32 value = 0;

	/* Check क्रम valid pinNumber */
	अगर (pin_number >= 47)
		वापस;

	/* change to output direction */
	cx25821_set_gpiopin_direction(dev, pin_number, 0);

	अगर (pin_number > 31) अणु
		bit = pin_number - 31;
		gpio_reg = GPIO_HI;
	पूर्ण

	value = cx_पढ़ो(gpio_reg);

	अगर (pin_logic_value == 0)
		value &= Clear_GPIO_Bit(bit);
	अन्यथा
		value |= Set_GPIO_Bit(bit);

	cx_ग_लिखो(gpio_reg, value);
पूर्ण

व्योम cx25821_gpio_init(काष्ठा cx25821_dev *dev)
अणु
	अगर (dev == शून्य)
		वापस;

	चयन (dev->board) अणु
	हाल CX25821_BOARD_CONEXANT_ATHENA10:
	शेष:
		/* set GPIO 5 to select the path क्रम Medusa/Athena */
		cx25821_set_gpiopin_logicvalue(dev, 5, 1);
		msleep(20);
		अवरोध;
	पूर्ण

पूर्ण
