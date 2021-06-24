<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम pcf857x, pca857x, and pca967x I2C GPIO expanders
 *
 * Copyright (C) 2007 David Brownell
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/pcf857x.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>


अटल स्थिर काष्ठा i2c_device_id pcf857x_id[] = अणु
	अणु "pcf8574", 8 पूर्ण,
	अणु "pcf8574a", 8 पूर्ण,
	अणु "pca8574", 8 पूर्ण,
	अणु "pca9670", 8 पूर्ण,
	अणु "pca9672", 8 पूर्ण,
	अणु "pca9674", 8 पूर्ण,
	अणु "pcf8575", 16 पूर्ण,
	अणु "pca8575", 16 पूर्ण,
	अणु "pca9671", 16 पूर्ण,
	अणु "pca9673", 16 पूर्ण,
	अणु "pca9675", 16 पूर्ण,
	अणु "max7328", 8 पूर्ण,
	अणु "max7329", 8 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pcf857x_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pcf857x_of_table[] = अणु
	अणु .compatible = "nxp,pcf8574" पूर्ण,
	अणु .compatible = "nxp,pcf8574a" पूर्ण,
	अणु .compatible = "nxp,pca8574" पूर्ण,
	अणु .compatible = "nxp,pca9670" पूर्ण,
	अणु .compatible = "nxp,pca9672" पूर्ण,
	अणु .compatible = "nxp,pca9674" पूर्ण,
	अणु .compatible = "nxp,pcf8575" पूर्ण,
	अणु .compatible = "nxp,pca8575" पूर्ण,
	अणु .compatible = "nxp,pca9671" पूर्ण,
	अणु .compatible = "nxp,pca9673" पूर्ण,
	अणु .compatible = "nxp,pca9675" पूर्ण,
	अणु .compatible = "maxim,max7328" पूर्ण,
	अणु .compatible = "maxim,max7329" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcf857x_of_table);
#पूर्ण_अगर

/*
 * The pcf857x, pca857x, and pca967x chips only expose one पढ़ो and one
 * ग_लिखो रेजिस्टर.  Writing a "one" bit (to match the reset state) lets
 * that pin be used as an input; it's not an खोलो-drain model, but acts
 * a bit like one.  This is described as "quasi-bidirectional"; पढ़ो the
 * chip करोcumentation क्रम details.
 *
 * Many other I2C GPIO expander chips (like the pca953x models) have
 * more complex रेजिस्टर models and more conventional circuitry using
 * push/pull drivers.  They often use the same 0x20..0x27 addresses as
 * pcf857x parts, making the "legacy" I2C driver model problematic.
 */
काष्ठा pcf857x अणु
	काष्ठा gpio_chip	chip;
	काष्ठा irq_chip		irqchip;
	काष्ठा i2c_client	*client;
	काष्ठा mutex		lock;		/* protect 'out' */
	अचिन्हित		out;		/* software latch */
	अचिन्हित		status;		/* current status */
	अचिन्हित		irq_enabled;	/* enabled irqs */

	पूर्णांक (*ग_लिखो)(काष्ठा i2c_client *client, अचिन्हित data);
	पूर्णांक (*पढ़ो)(काष्ठा i2c_client *client);
पूर्ण;

/*-------------------------------------------------------------------------*/

/* Talk to 8-bit I/O expander */

अटल पूर्णांक i2c_ग_लिखो_le8(काष्ठा i2c_client *client, अचिन्हित data)
अणु
	वापस i2c_smbus_ग_लिखो_byte(client, data);
पूर्ण

अटल पूर्णांक i2c_पढ़ो_le8(काष्ठा i2c_client *client)
अणु
	वापस (पूर्णांक)i2c_smbus_पढ़ो_byte(client);
पूर्ण

/* Talk to 16-bit I/O expander */

अटल पूर्णांक i2c_ग_लिखो_le16(काष्ठा i2c_client *client, अचिन्हित word)
अणु
	u8 buf[2] = अणु word & 0xff, word >> 8, पूर्ण;
	पूर्णांक status;

	status = i2c_master_send(client, buf, 2);
	वापस (status < 0) ? status : 0;
पूर्ण

अटल पूर्णांक i2c_पढ़ो_le16(काष्ठा i2c_client *client)
अणु
	u8 buf[2];
	पूर्णांक status;

	status = i2c_master_recv(client, buf, 2);
	अगर (status < 0)
		वापस status;
	वापस (buf[1] << 8) | buf[0];
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक pcf857x_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा pcf857x	*gpio = gpiochip_get_data(chip);
	पूर्णांक		status;

	mutex_lock(&gpio->lock);
	gpio->out |= (1 << offset);
	status = gpio->ग_लिखो(gpio->client, gpio->out);
	mutex_unlock(&gpio->lock);

	वापस status;
पूर्ण

अटल पूर्णांक pcf857x_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा pcf857x	*gpio = gpiochip_get_data(chip);
	पूर्णांक		value;

	value = gpio->पढ़ो(gpio->client);
	वापस (value < 0) ? value : !!(value & (1 << offset));
पूर्ण

अटल पूर्णांक pcf857x_output(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा pcf857x	*gpio = gpiochip_get_data(chip);
	अचिन्हित	bit = 1 << offset;
	पूर्णांक		status;

	mutex_lock(&gpio->lock);
	अगर (value)
		gpio->out |= bit;
	अन्यथा
		gpio->out &= ~bit;
	status = gpio->ग_लिखो(gpio->client, gpio->out);
	mutex_unlock(&gpio->lock);

	वापस status;
पूर्ण

अटल व्योम pcf857x_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	pcf857x_output(chip, offset, value);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल irqवापस_t pcf857x_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pcf857x  *gpio = data;
	अचिन्हित दीर्घ change, i, status;

	status = gpio->पढ़ो(gpio->client);

	/*
	 * call the पूर्णांकerrupt handler अगरf gpio is used as
	 * पूर्णांकerrupt source, just to aव्योम bad irqs
	 */
	mutex_lock(&gpio->lock);
	change = (gpio->status ^ status) & gpio->irq_enabled;
	gpio->status = status;
	mutex_unlock(&gpio->lock);

	क्रम_each_set_bit(i, &change, gpio->chip.ngpio)
		handle_nested_irq(irq_find_mapping(gpio->chip.irq.करोमुख्य, i));

	वापस IRQ_HANDLED;
पूर्ण

/*
 * NOP functions
 */
अटल व्योम noop(काष्ठा irq_data *data) अणु पूर्ण

अटल पूर्णांक pcf857x_irq_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	काष्ठा pcf857x *gpio = irq_data_get_irq_chip_data(data);

	वापस irq_set_irq_wake(gpio->client->irq, on);
पूर्ण

अटल व्योम pcf857x_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा pcf857x *gpio = irq_data_get_irq_chip_data(data);

	gpio->irq_enabled |= (1 << data->hwirq);
पूर्ण

अटल व्योम pcf857x_irq_disable(काष्ठा irq_data *data)
अणु
	काष्ठा pcf857x *gpio = irq_data_get_irq_chip_data(data);

	gpio->irq_enabled &= ~(1 << data->hwirq);
पूर्ण

अटल व्योम pcf857x_irq_bus_lock(काष्ठा irq_data *data)
अणु
	काष्ठा pcf857x *gpio = irq_data_get_irq_chip_data(data);

	mutex_lock(&gpio->lock);
पूर्ण

अटल व्योम pcf857x_irq_bus_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा pcf857x *gpio = irq_data_get_irq_chip_data(data);

	mutex_unlock(&gpio->lock);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक pcf857x_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा pcf857x_platक्रमm_data	*pdata = dev_get_platdata(&client->dev);
	काष्ठा device_node		*np = client->dev.of_node;
	काष्ठा pcf857x			*gpio;
	अचिन्हित पूर्णांक			n_latch = 0;
	पूर्णांक				status;

	अगर (IS_ENABLED(CONFIG_OF) && np)
		of_property_पढ़ो_u32(np, "lines-initial-states", &n_latch);
	अन्यथा अगर (pdata)
		n_latch = pdata->n_latch;
	अन्यथा
		dev_dbg(&client->dev, "no platform data\n");

	/* Allocate, initialize, and रेजिस्टर this gpio_chip. */
	gpio = devm_kzalloc(&client->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	mutex_init(&gpio->lock);

	gpio->chip.base			= pdata ? pdata->gpio_base : -1;
	gpio->chip.can_sleep		= true;
	gpio->chip.parent		= &client->dev;
	gpio->chip.owner		= THIS_MODULE;
	gpio->chip.get			= pcf857x_get;
	gpio->chip.set			= pcf857x_set;
	gpio->chip.direction_input	= pcf857x_input;
	gpio->chip.direction_output	= pcf857x_output;
	gpio->chip.ngpio		= id->driver_data;

	/* NOTE:  the OnSemi jlc1562b is also largely compatible with
	 * these parts, notably क्रम output.  It has a low-resolution
	 * DAC instead of pin change IRQs; and its inमाला_दो can be the
	 * result of comparators.
	 */

	/* 8574 addresses are 0x20..0x27; 8574a uses 0x38..0x3f;
	 * 9670, 9672, 9764, and 9764a use quite a variety.
	 *
	 * NOTE: we करोn't distinguish here between *4 and *4a parts.
	 */
	अगर (gpio->chip.ngpio == 8) अणु
		gpio->ग_लिखो	= i2c_ग_लिखो_le8;
		gpio->पढ़ो	= i2c_पढ़ो_le8;

		अगर (!i2c_check_functionality(client->adapter,
				I2C_FUNC_SMBUS_BYTE))
			status = -EIO;

		/* fail अगर there's no chip present */
		अन्यथा
			status = i2c_smbus_पढ़ो_byte(client);

	/* '75/'75c addresses are 0x20..0x27, just like the '74;
	 * the '75c doesn't have a current source pulling high.
	 * 9671, 9673, and 9765 use quite a variety of addresses.
	 *
	 * NOTE: we करोn't distinguish here between '75 and '75c parts.
	 */
	पूर्ण अन्यथा अगर (gpio->chip.ngpio == 16) अणु
		gpio->ग_लिखो	= i2c_ग_लिखो_le16;
		gpio->पढ़ो	= i2c_पढ़ो_le16;

		अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
			status = -EIO;

		/* fail अगर there's no chip present */
		अन्यथा
			status = i2c_पढ़ो_le16(client);

	पूर्ण अन्यथा अणु
		dev_dbg(&client->dev, "unsupported number of gpios\n");
		status = -EINVAL;
	पूर्ण

	अगर (status < 0)
		जाओ fail;

	gpio->chip.label = client->name;

	gpio->client = client;
	i2c_set_clientdata(client, gpio);

	/* NOTE:  these chips have strange "quasi-bidirectional" I/O pins.
	 * We can't actually know whether a pin is configured (a) as output
	 * and driving the संकेत low, or (b) as input and reporting a low
	 * value ... without knowing the last value written since the chip
	 * came out of reset (अगर any).  We can't पढ़ो the latched output.
	 *
	 * In लघु, the only reliable solution क्रम setting up pin direction
	 * is to करो it explicitly.  The setup() method can करो that, but it
	 * may cause transient glitching since it can't know the last value
	 * written (some pins may need to be driven low).
	 *
	 * Using n_latch aव्योमs that trouble.  When left initialized to zero,
	 * our software copy of the "latch" then matches the chip's all-ones
	 * reset state.  Otherwise it flags pins to be driven low.
	 */
	gpio->out = ~n_latch;
	gpio->status = gpio->पढ़ो(gpio->client);

	/* Enable irqchip अगर we have an पूर्णांकerrupt */
	अगर (client->irq) अणु
		काष्ठा gpio_irq_chip *girq;

		gpio->irqchip.name = "pcf857x";
		gpio->irqchip.irq_enable = pcf857x_irq_enable;
		gpio->irqchip.irq_disable = pcf857x_irq_disable;
		gpio->irqchip.irq_ack = noop;
		gpio->irqchip.irq_mask = noop;
		gpio->irqchip.irq_unmask = noop;
		gpio->irqchip.irq_set_wake = pcf857x_irq_set_wake;
		gpio->irqchip.irq_bus_lock = pcf857x_irq_bus_lock;
		gpio->irqchip.irq_bus_sync_unlock = pcf857x_irq_bus_sync_unlock;

		status = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य, pcf857x_irq, IRQF_ONESHOT |
					IRQF_TRIGGER_FALLING | IRQF_SHARED,
					dev_name(&client->dev), gpio);
		अगर (status)
			जाओ fail;

		girq = &gpio->chip.irq;
		girq->chip = &gpio->irqchip;
		/* This will let us handle the parent IRQ in the driver */
		girq->parent_handler = शून्य;
		girq->num_parents = 0;
		girq->parents = शून्य;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_level_irq;
		girq->thपढ़ोed = true;
	पूर्ण

	status = devm_gpiochip_add_data(&client->dev, &gpio->chip, gpio);
	अगर (status < 0)
		जाओ fail;

	/* Let platक्रमm code set up the GPIOs and their users.
	 * Now is the first समय anyone could use them.
	 */
	अगर (pdata && pdata->setup) अणु
		status = pdata->setup(client,
				gpio->chip.base, gpio->chip.ngpio,
				pdata->context);
		अगर (status < 0)
			dev_warn(&client->dev, "setup --> %d\n", status);
	पूर्ण

	dev_info(&client->dev, "probed\n");

	वापस 0;

fail:
	dev_dbg(&client->dev, "probe error %d for '%s'\n", status,
		client->name);

	वापस status;
पूर्ण

अटल पूर्णांक pcf857x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा pcf857x_platक्रमm_data	*pdata = dev_get_platdata(&client->dev);
	काष्ठा pcf857x			*gpio = i2c_get_clientdata(client);
	पूर्णांक				status = 0;

	अगर (pdata && pdata->tearकरोwn) अणु
		status = pdata->tearकरोwn(client,
				gpio->chip.base, gpio->chip.ngpio,
				pdata->context);
		अगर (status < 0) अणु
			dev_err(&client->dev, "%s --> %d\n",
					"teardown", status);
			वापस status;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम pcf857x_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा pcf857x *gpio = i2c_get_clientdata(client);

	/* Drive all the I/O lines high */
	gpio->ग_लिखो(gpio->client, BIT(gpio->chip.ngpio) - 1);
पूर्ण

अटल काष्ठा i2c_driver pcf857x_driver = अणु
	.driver = अणु
		.name	= "pcf857x",
		.of_match_table = of_match_ptr(pcf857x_of_table),
	पूर्ण,
	.probe	= pcf857x_probe,
	.हटाओ	= pcf857x_हटाओ,
	.shutकरोwn = pcf857x_shutकरोwn,
	.id_table = pcf857x_id,
पूर्ण;

अटल पूर्णांक __init pcf857x_init(व्योम)
अणु
	वापस i2c_add_driver(&pcf857x_driver);
पूर्ण
/* रेजिस्टर after i2c postcore initcall and beक्रमe
 * subsys initcalls that may rely on these GPIOs
 */
subsys_initcall(pcf857x_init);

अटल व्योम __निकास pcf857x_निकास(व्योम)
अणु
	i2c_del_driver(&pcf857x_driver);
पूर्ण
module_निकास(pcf857x_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Brownell");
