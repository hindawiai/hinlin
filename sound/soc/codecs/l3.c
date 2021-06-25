<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * L3 code
 *
 *  Copyright (C) 2008, Christian Pellegrin <chripell@evolware.org>
 *
 * based on:
 *
 * L3 bus algorithm module.
 *
 *  Copyright (C) 2001 Russell King, All Rights Reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpपन.स>

#समावेश <sound/l3.h>

/*
 * Send one byte of data to the chip.  Data is latched पूर्णांकo the chip on
 * the rising edge of the घड़ी.
 */
अटल व्योम sendbyte(काष्ठा l3_pins *adap, अचिन्हित पूर्णांक byte)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		adap->setclk(adap, 0);
		udelay(adap->data_hold);
		adap->setdat(adap, byte & 1);
		udelay(adap->data_setup);
		adap->setclk(adap, 1);
		udelay(adap->घड़ी_high);
		byte >>= 1;
	पूर्ण
पूर्ण

/*
 * Send a set of bytes to the chip.  We need to pulse the MODE line
 * between each byte, but never at the start nor at the end of the
 * transfer.
 */
अटल व्योम sendbytes(काष्ठा l3_pins *adap, स्थिर u8 *buf,
		      पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		अगर (i) अणु
			udelay(adap->mode_hold);
			adap->seपंचांगode(adap, 0);
			udelay(adap->mode);
		पूर्ण
		adap->seपंचांगode(adap, 1);
		udelay(adap->mode_setup);
		sendbyte(adap, buf[i]);
	पूर्ण
पूर्ण

पूर्णांक l3_ग_लिखो(काष्ठा l3_pins *adap, u8 addr, u8 *data, पूर्णांक len)
अणु
	adap->setclk(adap, 1);
	adap->setdat(adap, 1);
	adap->seपंचांगode(adap, 1);
	udelay(adap->mode);

	adap->seपंचांगode(adap, 0);
	udelay(adap->mode_setup);
	sendbyte(adap, addr);
	udelay(adap->mode_hold);

	sendbytes(adap, data, len);

	adap->setclk(adap, 1);
	adap->setdat(adap, 1);
	adap->seपंचांगode(adap, 0);

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(l3_ग_लिखो);


अटल व्योम l3_set_clk(काष्ठा l3_pins *adap, पूर्णांक val)
अणु
	gpio_set_value(adap->gpio_clk, val);
पूर्ण

अटल व्योम l3_set_data(काष्ठा l3_pins *adap, पूर्णांक val)
अणु
	gpio_set_value(adap->gpio_data, val);
पूर्ण

अटल व्योम l3_set_mode(काष्ठा l3_pins *adap, पूर्णांक val)
अणु
	gpio_set_value(adap->gpio_mode, val);
पूर्ण

पूर्णांक l3_set_gpio_ops(काष्ठा device *dev, काष्ठा l3_pins *adap)
अणु
	पूर्णांक ret;

	अगर (!adap->use_gpios)
		वापस -EINVAL;

	ret = devm_gpio_request_one(dev, adap->gpio_data,
				GPIOF_OUT_INIT_LOW, "l3_data");
	अगर (ret < 0)
		वापस ret;
	adap->setdat = l3_set_data;

	ret = devm_gpio_request_one(dev, adap->gpio_clk,
				GPIOF_OUT_INIT_LOW, "l3_clk");
	अगर (ret < 0)
		वापस ret;
	adap->setclk = l3_set_clk;

	ret = devm_gpio_request_one(dev, adap->gpio_mode,
				GPIOF_OUT_INIT_LOW, "l3_mode");
	अगर (ret < 0)
		वापस ret;
	adap->seपंचांगode = l3_set_mode;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(l3_set_gpio_ops);

MODULE_DESCRIPTION("L3 bit-banging driver");
MODULE_AUTHOR("Christian Pellegrin <chripell@evolware.org>");
MODULE_LICENSE("GPL");
