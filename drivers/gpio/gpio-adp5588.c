<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GPIO Chip driver क्रम Analog Devices
 * ADP5588/ADP5587 I/O Expander and QWERTY Keypad Controller
 *
 * Copyright 2009-2010 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/of_device.h>

#समावेश <linux/platक्रमm_data/adp5588.h>

#घोषणा DRV_NAME	"adp5588-gpio"

/*
 * Early pre 4.0 Silicon required to delay पढ़ोout by at least 25ms,
 * since the Event Counter Register updated 25ms after the पूर्णांकerrupt
 * निश्चितed.
 */
#घोषणा WA_DELAYED_READOUT_REVID(rev)	((rev) < 4)

काष्ठा adp5588_gpio अणु
	काष्ठा i2c_client *client;
	काष्ठा gpio_chip gpio_chip;
	काष्ठा mutex lock;	/* protect cached dir, dat_out */
	/* protect serialized access to the पूर्णांकerrupt controller bus */
	काष्ठा mutex irq_lock;
	uपूर्णांक8_t dat_out[3];
	uपूर्णांक8_t dir[3];
	uपूर्णांक8_t पूर्णांक_lvl_low[3];
	uपूर्णांक8_t पूर्णांक_lvl_high[3];
	uपूर्णांक8_t पूर्णांक_en[3];
	uपूर्णांक8_t irq_mask[3];
	uपूर्णांक8_t पूर्णांक_input_en[3];
पूर्ण;

अटल पूर्णांक adp5588_gpio_पढ़ो(काष्ठा i2c_client *client, u8 reg)
अणु
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(client, reg);

	अगर (ret < 0)
		dev_err(&client->dev, "Read Error\n");

	वापस ret;
पूर्ण

अटल पूर्णांक adp5588_gpio_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 val)
अणु
	पूर्णांक ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);

	अगर (ret < 0)
		dev_err(&client->dev, "Write Error\n");

	वापस ret;
पूर्ण

अटल पूर्णांक adp5588_gpio_get_value(काष्ठा gpio_chip *chip, अचिन्हित off)
अणु
	काष्ठा adp5588_gpio *dev = gpiochip_get_data(chip);
	अचिन्हित bank = ADP5588_BANK(off);
	अचिन्हित bit = ADP5588_BIT(off);
	पूर्णांक val;

	mutex_lock(&dev->lock);

	अगर (dev->dir[bank] & bit)
		val = dev->dat_out[bank];
	अन्यथा
		val = adp5588_gpio_पढ़ो(dev->client, GPIO_DAT_STAT1 + bank);

	mutex_unlock(&dev->lock);

	वापस !!(val & bit);
पूर्ण

अटल व्योम adp5588_gpio_set_value(काष्ठा gpio_chip *chip,
				   अचिन्हित off, पूर्णांक val)
अणु
	अचिन्हित bank, bit;
	काष्ठा adp5588_gpio *dev = gpiochip_get_data(chip);

	bank = ADP5588_BANK(off);
	bit = ADP5588_BIT(off);

	mutex_lock(&dev->lock);
	अगर (val)
		dev->dat_out[bank] |= bit;
	अन्यथा
		dev->dat_out[bank] &= ~bit;

	adp5588_gpio_ग_लिखो(dev->client, GPIO_DAT_OUT1 + bank,
			   dev->dat_out[bank]);
	mutex_unlock(&dev->lock);
पूर्ण

अटल पूर्णांक adp5588_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित off)
अणु
	पूर्णांक ret;
	अचिन्हित bank;
	काष्ठा adp5588_gpio *dev = gpiochip_get_data(chip);

	bank = ADP5588_BANK(off);

	mutex_lock(&dev->lock);
	dev->dir[bank] &= ~ADP5588_BIT(off);
	ret = adp5588_gpio_ग_लिखो(dev->client, GPIO_सूची1 + bank, dev->dir[bank]);
	mutex_unlock(&dev->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक adp5588_gpio_direction_output(काष्ठा gpio_chip *chip,
					 अचिन्हित off, पूर्णांक val)
अणु
	पूर्णांक ret;
	अचिन्हित bank, bit;
	काष्ठा adp5588_gpio *dev = gpiochip_get_data(chip);

	bank = ADP5588_BANK(off);
	bit = ADP5588_BIT(off);

	mutex_lock(&dev->lock);
	dev->dir[bank] |= bit;

	अगर (val)
		dev->dat_out[bank] |= bit;
	अन्यथा
		dev->dat_out[bank] &= ~bit;

	ret = adp5588_gpio_ग_लिखो(dev->client, GPIO_DAT_OUT1 + bank,
				 dev->dat_out[bank]);
	ret |= adp5588_gpio_ग_लिखो(dev->client, GPIO_सूची1 + bank,
				 dev->dir[bank]);
	mutex_unlock(&dev->lock);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_GPIO_ADP5588_IRQ

अटल व्योम adp5588_irq_bus_lock(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा adp5588_gpio *dev = gpiochip_get_data(gc);

	mutex_lock(&dev->irq_lock);
पूर्ण

 /*
  * genirq core code can issue chip->mask/unmask from atomic context.
  * This करोesn't work क्रम slow busses where an access needs to sleep.
  * bus_sync_unlock() is thereक्रमe called outside the atomic context,
  * syncs the current irq mask state with the slow बाह्यal controller
  * and unlocks the bus.
  */

अटल व्योम adp5588_irq_bus_sync_unlock(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा adp5588_gpio *dev = gpiochip_get_data(gc);
	पूर्णांक i;

	क्रम (i = 0; i <= ADP5588_BANK(ADP5588_MAXGPIO); i++) अणु
		अगर (dev->पूर्णांक_input_en[i]) अणु
			mutex_lock(&dev->lock);
			dev->dir[i] &= ~dev->पूर्णांक_input_en[i];
			dev->पूर्णांक_input_en[i] = 0;
			adp5588_gpio_ग_लिखो(dev->client, GPIO_सूची1 + i,
					   dev->dir[i]);
			mutex_unlock(&dev->lock);
		पूर्ण

		अगर (dev->पूर्णांक_en[i] ^ dev->irq_mask[i]) अणु
			dev->पूर्णांक_en[i] = dev->irq_mask[i];
			adp5588_gpio_ग_लिखो(dev->client, GPI_EM1 + i,
					   dev->पूर्णांक_en[i]);
		पूर्ण
	पूर्ण

	mutex_unlock(&dev->irq_lock);
पूर्ण

अटल व्योम adp5588_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा adp5588_gpio *dev = gpiochip_get_data(gc);

	dev->irq_mask[ADP5588_BANK(d->hwirq)] &= ~ADP5588_BIT(d->hwirq);
पूर्ण

अटल व्योम adp5588_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा adp5588_gpio *dev = gpiochip_get_data(gc);

	dev->irq_mask[ADP5588_BANK(d->hwirq)] |= ADP5588_BIT(d->hwirq);
पूर्ण

अटल पूर्णांक adp5588_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा adp5588_gpio *dev = gpiochip_get_data(gc);
	uपूर्णांक16_t gpio = d->hwirq;
	अचिन्हित bank, bit;

	bank = ADP5588_BANK(gpio);
	bit = ADP5588_BIT(gpio);

	dev->पूर्णांक_lvl_low[bank] &= ~bit;
	dev->पूर्णांक_lvl_high[bank] &= ~bit;

	अगर (type & IRQ_TYPE_EDGE_BOTH || type & IRQ_TYPE_LEVEL_HIGH)
		dev->पूर्णांक_lvl_high[bank] |= bit;

	अगर (type & IRQ_TYPE_EDGE_BOTH || type & IRQ_TYPE_LEVEL_LOW)
		dev->पूर्णांक_lvl_low[bank] |= bit;

	dev->पूर्णांक_input_en[bank] |= bit;

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip adp5588_irq_chip = अणु
	.name			= "adp5588",
	.irq_mask		= adp5588_irq_mask,
	.irq_unmask		= adp5588_irq_unmask,
	.irq_bus_lock		= adp5588_irq_bus_lock,
	.irq_bus_sync_unlock	= adp5588_irq_bus_sync_unlock,
	.irq_set_type		= adp5588_irq_set_type,
पूर्ण;

अटल irqवापस_t adp5588_irq_handler(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा adp5588_gpio *dev = devid;
	पूर्णांक status = adp5588_gpio_पढ़ो(dev->client, INT_STAT);

	अगर (status & ADP5588_KE_INT) अणु
		पूर्णांक ev_cnt = adp5588_gpio_पढ़ो(dev->client, KEY_LCK_EC_STAT);

		अगर (ev_cnt > 0) अणु
			पूर्णांक i;

			क्रम (i = 0; i < (ev_cnt & ADP5588_KEC); i++) अणु
				पूर्णांक key = adp5588_gpio_पढ़ो(dev->client,
							    Key_EVENTA + i);
				/* GPIN events begin at 97,
				 * bit 7 indicates logic level
				 */
				पूर्णांक gpio = (key & 0x7f) - 97;
				पूर्णांक lvl = key & (1 << 7);
				पूर्णांक bank = ADP5588_BANK(gpio);
				पूर्णांक bit = ADP5588_BIT(gpio);

				अगर ((lvl && dev->पूर्णांक_lvl_high[bank] & bit) ||
				    (!lvl && dev->पूर्णांक_lvl_low[bank] & bit))
					handle_nested_irq(irq_find_mapping(
					      dev->gpio_chip.irq.करोमुख्य, gpio));
			पूर्ण
		पूर्ण
	पूर्ण

	adp5588_gpio_ग_लिखो(dev->client, INT_STAT, status); /* Status is W1C */

	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक adp5588_irq_init_hw(काष्ठा gpio_chip *gc)
अणु
	काष्ठा adp5588_gpio *dev = gpiochip_get_data(gc);
	/* Enable IRQs after रेजिस्टरing chip */
	adp5588_gpio_ग_लिखो(dev->client, CFG,
			   ADP5588_AUTO_INC | ADP5588_INT_CFG | ADP5588_KE_IEN);

	वापस 0;
पूर्ण

अटल पूर्णांक adp5588_irq_setup(काष्ठा adp5588_gpio *dev)
अणु
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	काष्ठा adp5588_gpio_platक्रमm_data *pdata =
			dev_get_platdata(&client->dev);
	काष्ठा gpio_irq_chip *girq;

	adp5588_gpio_ग_लिखो(client, CFG, ADP5588_AUTO_INC);
	adp5588_gpio_ग_लिखो(client, INT_STAT, -1); /* status is W1C */

	mutex_init(&dev->irq_lock);

	ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य, adp5588_irq_handler, IRQF_ONESHOT
					| IRQF_TRIGGER_FALLING | IRQF_SHARED,
					dev_name(&client->dev), dev);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to request irq %d\n",
			client->irq);
		वापस ret;
	पूर्ण

	/* This will be रेजिस्टरed in the call to devm_gpiochip_add_data() */
	girq = &dev->gpio_chip.irq;
	girq->chip = &adp5588_irq_chip;
	/* This will let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->first = pdata ? pdata->irq_base : 0;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_simple_irq;
	girq->init_hw = adp5588_irq_init_hw;
	girq->thपढ़ोed = true;

	वापस 0;
पूर्ण

#अन्यथा
अटल पूर्णांक adp5588_irq_setup(काष्ठा adp5588_gpio *dev)
अणु
	काष्ठा i2c_client *client = dev->client;
	dev_warn(&client->dev, "interrupt support not compiled in\n");

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_GPIO_ADP5588_IRQ */

अटल पूर्णांक adp5588_gpio_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा adp5588_gpio_platक्रमm_data *pdata =
			dev_get_platdata(&client->dev);
	काष्ठा adp5588_gpio *dev;
	काष्ठा gpio_chip *gc;
	पूर्णांक ret, i, revid;
	अचिन्हित पूर्णांक pullup_dis_mask = 0;

	अगर (!i2c_check_functionality(client->adapter,
					I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(&client->dev, "SMBUS Byte Data not Supported\n");
		वापस -EIO;
	पूर्ण

	dev = devm_kzalloc(&client->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->client = client;

	gc = &dev->gpio_chip;
	gc->direction_input = adp5588_gpio_direction_input;
	gc->direction_output = adp5588_gpio_direction_output;
	gc->get = adp5588_gpio_get_value;
	gc->set = adp5588_gpio_set_value;
	gc->can_sleep = true;
	gc->base = -1;
	gc->parent = &client->dev;

	अगर (pdata) अणु
		gc->base = pdata->gpio_start;
		gc->names = pdata->names;
		pullup_dis_mask = pdata->pullup_dis_mask;
	पूर्ण

	gc->ngpio = ADP5588_MAXGPIO;
	gc->label = client->name;
	gc->owner = THIS_MODULE;

	mutex_init(&dev->lock);

	ret = adp5588_gpio_पढ़ो(dev->client, DEV_ID);
	अगर (ret < 0)
		वापस ret;

	revid = ret & ADP5588_DEVICE_ID_MASK;

	क्रम (i = 0, ret = 0; i <= ADP5588_BANK(ADP5588_MAXGPIO); i++) अणु
		dev->dat_out[i] = adp5588_gpio_पढ़ो(client, GPIO_DAT_OUT1 + i);
		dev->dir[i] = adp5588_gpio_पढ़ो(client, GPIO_सूची1 + i);
		ret |= adp5588_gpio_ग_लिखो(client, KP_GPIO1 + i, 0);
		ret |= adp5588_gpio_ग_लिखो(client, GPIO_PULL1 + i,
				(pullup_dis_mask >> (8 * i)) & 0xFF);
		ret |= adp5588_gpio_ग_लिखो(client, GPIO_INT_EN1 + i, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (client->irq) अणु
		अगर (WA_DELAYED_READOUT_REVID(revid)) अणु
			dev_warn(&client->dev, "GPIO int not supported\n");
		पूर्ण अन्यथा अणु
			ret = adp5588_irq_setup(dev);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_gpiochip_add_data(&client->dev, &dev->gpio_chip, dev);
	अगर (ret)
		वापस ret;

	अगर (pdata && pdata->setup) अणु
		ret = pdata->setup(client, gc->base, gc->ngpio, pdata->context);
		अगर (ret < 0)
			dev_warn(&client->dev, "setup failed, %d\n", ret);
	पूर्ण

	i2c_set_clientdata(client, dev);

	वापस 0;
पूर्ण

अटल पूर्णांक adp5588_gpio_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा adp5588_gpio_platक्रमm_data *pdata =
			dev_get_platdata(&client->dev);
	काष्ठा adp5588_gpio *dev = i2c_get_clientdata(client);
	पूर्णांक ret;

	अगर (pdata && pdata->tearकरोwn) अणु
		ret = pdata->tearकरोwn(client,
				      dev->gpio_chip.base, dev->gpio_chip.ngpio,
				      pdata->context);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "teardown failed %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (dev->client->irq)
		मुक्त_irq(dev->client->irq, dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adp5588_gpio_id[] = अणु
	अणुDRV_NAME, 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adp5588_gpio_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id adp5588_gpio_of_id[] = अणु
	अणु .compatible = "adi," DRV_NAME, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adp5588_gpio_of_id);
#पूर्ण_अगर

अटल काष्ठा i2c_driver adp5588_gpio_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(adp5588_gpio_of_id),
	पूर्ण,
	.probe_new = adp5588_gpio_probe,
	.हटाओ = adp5588_gpio_हटाओ,
	.id_table = adp5588_gpio_id,
पूर्ण;

module_i2c_driver(adp5588_gpio_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("GPIO ADP5588 Driver");
MODULE_LICENSE("GPL");
