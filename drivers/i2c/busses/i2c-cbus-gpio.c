<शैली गुरु>
/*
 * CBUS I2C driver क्रम Nokia Internet Tablets.
 *
 * Copyright (C) 2004-2010 Nokia Corporation
 *
 * Based on code written by Juha Yrjथघlथअ, David Weinehall, Mikko Ylinen and
 * Felipe Balbi. Converted to I2C driver by Aaro Koskinen.
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/पन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * Bit counts are derived from Nokia implementation. These should be checked
 * अगर other CBUS implementations appear.
 */
#घोषणा CBUS_ADDR_BITS	3
#घोषणा CBUS_REG_BITS	5

काष्ठा cbus_host अणु
	spinlock_t	lock;		/* host lock */
	काष्ठा device	*dev;
	काष्ठा gpio_desc *clk;
	काष्ठा gpio_desc *dat;
	काष्ठा gpio_desc *sel;
पूर्ण;

/**
 * cbus_send_bit - sends one bit over the bus
 * @host: the host we're using
 * @bit: one bit of inक्रमmation to send
 */
अटल व्योम cbus_send_bit(काष्ठा cbus_host *host, अचिन्हित bit)
अणु
	gpiod_set_value(host->dat, bit ? 1 : 0);
	gpiod_set_value(host->clk, 1);
	gpiod_set_value(host->clk, 0);
पूर्ण

/**
 * cbus_send_data - sends @len amount of data over the bus
 * @host: the host we're using
 * @data: the data to send
 * @len: size of the transfer
 */
अटल व्योम cbus_send_data(काष्ठा cbus_host *host, अचिन्हित data, अचिन्हित len)
अणु
	पूर्णांक i;

	क्रम (i = len; i > 0; i--)
		cbus_send_bit(host, data & (1 << (i - 1)));
पूर्ण

/**
 * cbus_receive_bit - receives one bit from the bus
 * @host: the host we're using
 */
अटल पूर्णांक cbus_receive_bit(काष्ठा cbus_host *host)
अणु
	पूर्णांक ret;

	gpiod_set_value(host->clk, 1);
	ret = gpiod_get_value(host->dat);
	gpiod_set_value(host->clk, 0);
	वापस ret;
पूर्ण

/**
 * cbus_receive_word - receives 16-bit word from the bus
 * @host: the host we're using
 */
अटल पूर्णांक cbus_receive_word(काष्ठा cbus_host *host)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 16; i > 0; i--) अणु
		पूर्णांक bit = cbus_receive_bit(host);

		अगर (bit < 0)
			वापस bit;

		अगर (bit)
			ret |= 1 << (i - 1);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * cbus_transfer - transfers data over the bus
 * @host: the host we're using
 * @rw: पढ़ो/ग_लिखो flag
 * @dev: device address
 * @reg: रेजिस्टर address
 * @data: अगर @rw == I2C_SBUS_WRITE data to send otherwise 0
 */
अटल पूर्णांक cbus_transfer(काष्ठा cbus_host *host, अक्षर rw, अचिन्हित dev,
			 अचिन्हित reg, अचिन्हित data)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* We करोn't want पूर्णांकerrupts disturbing our transfer */
	spin_lock_irqsave(&host->lock, flags);

	/* Reset state and start of transfer, SEL stays करोwn during transfer */
	gpiod_set_value(host->sel, 0);

	/* Set the DAT pin to output */
	gpiod_direction_output(host->dat, 1);

	/* Send the device address */
	cbus_send_data(host, dev, CBUS_ADDR_BITS);

	/* Send the rw flag */
	cbus_send_bit(host, rw == I2C_SMBUS_READ);

	/* Send the रेजिस्टर address */
	cbus_send_data(host, reg, CBUS_REG_BITS);

	अगर (rw == I2C_SMBUS_WRITE) अणु
		cbus_send_data(host, data, 16);
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = gpiod_direction_input(host->dat);
		अगर (ret) अणु
			dev_dbg(host->dev, "failed setting direction\n");
			जाओ out;
		पूर्ण
		gpiod_set_value(host->clk, 1);

		ret = cbus_receive_word(host);
		अगर (ret < 0) अणु
			dev_dbg(host->dev, "failed receiving data\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/* Indicate end of transfer, SEL goes up until next transfer */
	gpiod_set_value(host->sel, 1);
	gpiod_set_value(host->clk, 1);
	gpiod_set_value(host->clk, 0);

out:
	spin_unlock_irqrestore(&host->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक cbus_i2c_smbus_xfer(काष्ठा i2c_adapter	*adapter,
			       u16			addr,
			       अचिन्हित लघु		flags,
			       अक्षर			पढ़ो_ग_लिखो,
			       u8			command,
			       पूर्णांक			size,
			       जोड़ i2c_smbus_data	*data)
अणु
	काष्ठा cbus_host *chost = i2c_get_adapdata(adapter);
	पूर्णांक ret;

	अगर (size != I2C_SMBUS_WORD_DATA)
		वापस -EINVAL;

	ret = cbus_transfer(chost, पढ़ो_ग_लिखो == I2C_SMBUS_READ, addr,
			    command, data->word);
	अगर (ret < 0)
		वापस ret;

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
		data->word = ret;

	वापस 0;
पूर्ण

अटल u32 cbus_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_READ_WORD_DATA | I2C_FUNC_SMBUS_WRITE_WORD_DATA;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm cbus_i2c_algo = अणु
	.smbus_xfer	= cbus_i2c_smbus_xfer,
	.functionality	= cbus_i2c_func,
पूर्ण;

अटल पूर्णांक cbus_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_adapter *adapter = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक cbus_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_adapter *adapter;
	काष्ठा cbus_host *chost;

	adapter = devm_kzalloc(&pdev->dev, माप(काष्ठा i2c_adapter),
			       GFP_KERNEL);
	अगर (!adapter)
		वापस -ENOMEM;

	chost = devm_kzalloc(&pdev->dev, माप(*chost), GFP_KERNEL);
	अगर (!chost)
		वापस -ENOMEM;

	अगर (gpiod_count(&pdev->dev, शून्य) != 3)
		वापस -ENODEV;
	chost->clk = devm_gpiod_get_index(&pdev->dev, शून्य, 0, GPIOD_OUT_LOW);
	अगर (IS_ERR(chost->clk))
		वापस PTR_ERR(chost->clk);
	chost->dat = devm_gpiod_get_index(&pdev->dev, शून्य, 1, GPIOD_IN);
	अगर (IS_ERR(chost->dat))
		वापस PTR_ERR(chost->dat);
	chost->sel = devm_gpiod_get_index(&pdev->dev, शून्य, 2, GPIOD_OUT_HIGH);
	अगर (IS_ERR(chost->sel))
		वापस PTR_ERR(chost->sel);
	gpiod_set_consumer_name(chost->clk, "CBUS clk");
	gpiod_set_consumer_name(chost->dat, "CBUS dat");
	gpiod_set_consumer_name(chost->sel, "CBUS sel");

	adapter->owner		= THIS_MODULE;
	adapter->class		= I2C_CLASS_HWMON;
	adapter->dev.parent	= &pdev->dev;
	adapter->dev.of_node	= pdev->dev.of_node;
	adapter->nr		= pdev->id;
	adapter->समयout	= HZ;
	adapter->algo		= &cbus_i2c_algo;
	strlcpy(adapter->name, "CBUS I2C adapter", माप(adapter->name));

	spin_lock_init(&chost->lock);
	chost->dev = &pdev->dev;

	i2c_set_adapdata(adapter, chost);
	platक्रमm_set_drvdata(pdev, adapter);

	वापस i2c_add_numbered_adapter(adapter);
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id i2c_cbus_dt_ids[] = अणु
	अणु .compatible = "i2c-cbus-gpio", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_cbus_dt_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver cbus_i2c_driver = अणु
	.probe	= cbus_i2c_probe,
	.हटाओ	= cbus_i2c_हटाओ,
	.driver	= अणु
		.name	= "i2c-cbus-gpio",
		.of_match_table = of_match_ptr(i2c_cbus_dt_ids),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(cbus_i2c_driver);

MODULE_ALIAS("platform:i2c-cbus-gpio");
MODULE_DESCRIPTION("CBUS I2C driver");
MODULE_AUTHOR("Juha Yrjथघlथअ");
MODULE_AUTHOR("David Weinehall");
MODULE_AUTHOR("Mikko Ylinen");
MODULE_AUTHOR("Felipe Balbi");
MODULE_AUTHOR("Aaro Koskinen <aaro.koskinen@iki.fi>");
MODULE_LICENSE("GPL");
