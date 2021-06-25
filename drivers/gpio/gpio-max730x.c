<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * Copyright (C) 2006 Juergen Beisert, Pengutronix
 * Copyright (C) 2008 Guennadi Liakhovetski, Pengutronix
 * Copyright (C) 2009 Wolfram Sang, Pengutronix
 *
 * The Maxim MAX7300/1 device is an I2C/SPI driven GPIO expander. There are
 * 28 GPIOs. 8 of them can trigger an पूर्णांकerrupt. See datasheet क्रम more
 * details
 * Note:
 * - DIN must be stable at the rising edge of घड़ी.
 * - when writing:
 *   - always घड़ी in 16 घड़ीs at once
 *   - at DIN: D15 first, D0 last
 *   - D0..D7 = databyte, D8..D14 = commandbyte
 *   - D15 = low -> ग_लिखो command
 * - when पढ़ोing
 *   - always घड़ी in 16 घड़ीs at once
 *   - at DIN: D15 first, D0 last
 *   - D0..D7 = dummy, D8..D14 = रेजिस्टर address
 *   - D15 = high -> पढ़ो command
 *   - उठाओ CS and निश्चित it again
 *   - always घड़ी in 16 घड़ीs at once
 *   - at DOUT: D15 first, D0 last
 *   - D0..D7 contains the data from the first cycle
 *
 * The driver exports a standard gpiochip पूर्णांकerface
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spi/max7301.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/slab.h>

/*
 * Pin configurations, see MAX7301 datasheet page 6
 */
#घोषणा PIN_CONFIG_MASK 0x03
#घोषणा PIN_CONFIG_IN_PULLUP 0x03
#घोषणा PIN_CONFIG_IN_WO_PULLUP 0x02
#घोषणा PIN_CONFIG_OUT 0x01

#घोषणा PIN_NUMBER 28

अटल पूर्णांक max7301_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा max7301 *ts = container_of(chip, काष्ठा max7301, chip);
	u8 *config;
	u8 offset_bits, pin_config;
	पूर्णांक ret;

	/* First 4 pins are unused in the controller */
	offset += 4;
	offset_bits = (offset & 3) << 1;

	config = &ts->port_config[offset >> 2];

	अगर (ts->input_pullup_active & BIT(offset))
		pin_config = PIN_CONFIG_IN_PULLUP;
	अन्यथा
		pin_config = PIN_CONFIG_IN_WO_PULLUP;

	mutex_lock(&ts->lock);

	*config = (*config & ~(PIN_CONFIG_MASK << offset_bits))
			   | (pin_config << offset_bits);

	ret = ts->ग_लिखो(ts->dev, 0x08 + (offset >> 2), *config);

	mutex_unlock(&ts->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक __max7301_set(काष्ठा max7301 *ts, अचिन्हित offset, पूर्णांक value)
अणु
	अगर (value) अणु
		ts->out_level |= 1 << offset;
		वापस ts->ग_लिखो(ts->dev, 0x20 + offset, 0x01);
	पूर्ण अन्यथा अणु
		ts->out_level &= ~(1 << offset);
		वापस ts->ग_लिखो(ts->dev, 0x20 + offset, 0x00);
	पूर्ण
पूर्ण

अटल पूर्णांक max7301_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
				    पूर्णांक value)
अणु
	काष्ठा max7301 *ts = container_of(chip, काष्ठा max7301, chip);
	u8 *config;
	u8 offset_bits;
	पूर्णांक ret;

	/* First 4 pins are unused in the controller */
	offset += 4;
	offset_bits = (offset & 3) << 1;

	config = &ts->port_config[offset >> 2];

	mutex_lock(&ts->lock);

	*config = (*config & ~(PIN_CONFIG_MASK << offset_bits))
			   | (PIN_CONFIG_OUT << offset_bits);

	ret = __max7301_set(ts, offset, value);

	अगर (!ret)
		ret = ts->ग_लिखो(ts->dev, 0x08 + (offset >> 2), *config);

	mutex_unlock(&ts->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक max7301_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा max7301 *ts = gpiochip_get_data(chip);
	पूर्णांक config, level = -EINVAL;

	/* First 4 pins are unused in the controller */
	offset += 4;

	mutex_lock(&ts->lock);

	config = (ts->port_config[offset >> 2] >> ((offset & 3) << 1))
			& PIN_CONFIG_MASK;

	चयन (config) अणु
	हाल PIN_CONFIG_OUT:
		/* Output: वापस cached level */
		level =  !!(ts->out_level & (1 << offset));
		अवरोध;
	हाल PIN_CONFIG_IN_WO_PULLUP:
	हाल PIN_CONFIG_IN_PULLUP:
		/* Input: पढ़ो out */
		level = ts->पढ़ो(ts->dev, 0x20 + offset) & 0x01;
	पूर्ण
	mutex_unlock(&ts->lock);

	वापस level;
पूर्ण

अटल व्योम max7301_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा max7301 *ts = gpiochip_get_data(chip);

	/* First 4 pins are unused in the controller */
	offset += 4;

	mutex_lock(&ts->lock);

	__max7301_set(ts, offset, value);

	mutex_unlock(&ts->lock);
पूर्ण

पूर्णांक __max730x_probe(काष्ठा max7301 *ts)
अणु
	काष्ठा device *dev = ts->dev;
	काष्ठा max7301_platक्रमm_data *pdata;
	पूर्णांक i, ret;

	pdata = dev_get_platdata(dev);

	mutex_init(&ts->lock);
	dev_set_drvdata(dev, ts);

	/* Power up the chip and disable IRQ output */
	ts->ग_लिखो(dev, 0x04, 0x01);

	अगर (pdata) अणु
		ts->input_pullup_active = pdata->input_pullup_active;
		ts->chip.base = pdata->base;
	पूर्ण अन्यथा अणु
		ts->chip.base = -1;
	पूर्ण
	ts->chip.label = dev->driver->name;

	ts->chip.direction_input = max7301_direction_input;
	ts->chip.get = max7301_get;
	ts->chip.direction_output = max7301_direction_output;
	ts->chip.set = max7301_set;

	ts->chip.ngpio = PIN_NUMBER;
	ts->chip.can_sleep = true;
	ts->chip.parent = dev;
	ts->chip.owner = THIS_MODULE;

	/*
	 * initialize pullups according to platक्रमm data and cache the
	 * रेजिस्टर values क्रम later use.
	 */
	क्रम (i = 1; i < 8; i++) अणु
		पूर्णांक j;
		/*
		 * initialize port_config with "0xAA", which means
		 * input with पूर्णांकernal pullup disabled. This is needed
		 * to aव्योम writing zeros (in the inner क्रम loop),
		 * which is not allowed according to the datasheet.
		 */
		ts->port_config[i] = 0xAA;
		क्रम (j = 0; j < 4; j++) अणु
			पूर्णांक offset = (i - 1) * 4 + j;
			ret = max7301_direction_input(&ts->chip, offset);
			अगर (ret)
				जाओ निकास_destroy;
		पूर्ण
	पूर्ण

	ret = gpiochip_add_data(&ts->chip, ts);
	अगर (!ret)
		वापस ret;

निकास_destroy:
	mutex_destroy(&ts->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__max730x_probe);

पूर्णांक __max730x_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा max7301 *ts = dev_get_drvdata(dev);

	अगर (ts == शून्य)
		वापस -ENODEV;

	/* Power करोwn the chip and disable IRQ output */
	ts->ग_लिखो(dev, 0x04, 0x00);
	gpiochip_हटाओ(&ts->chip);
	mutex_destroy(&ts->lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__max730x_हटाओ);

MODULE_AUTHOR("Juergen Beisert, Wolfram Sang");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MAX730x GPIO-Expanders, generic parts");
