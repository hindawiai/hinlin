<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Hanumath Prasad <hanumath.prasad@stericsson.com> क्रम ST-Ericsson
 * Author: Rabin Vincent <rabin.vincent@stericsson.com> क्रम ST-Ericsson
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/tc3589x.h>
#समावेश <linux/err.h>

/*
 * क्रमागत tc3589x_version - indicates the TC3589x version
 */
क्रमागत tc3589x_version अणु
	TC3589X_TC35890,
	TC3589X_TC35892,
	TC3589X_TC35893,
	TC3589X_TC35894,
	TC3589X_TC35895,
	TC3589X_TC35896,
	TC3589X_UNKNOWN,
पूर्ण;

#घोषणा TC3589x_CLKMODE_MODCTL_SLEEP		0x0
#घोषणा TC3589x_CLKMODE_MODCTL_OPERATION	(1 << 0)

/**
 * tc3589x_reg_पढ़ो() - पढ़ो a single TC3589x रेजिस्टर
 * @tc3589x:	Device to पढ़ो from
 * @reg:	Register to पढ़ो
 */
पूर्णांक tc3589x_reg_पढ़ो(काष्ठा tc3589x *tc3589x, u8 reg)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(tc3589x->i2c, reg);
	अगर (ret < 0)
		dev_err(tc3589x->dev, "failed to read reg %#x: %d\n",
			reg, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tc3589x_reg_पढ़ो);

/**
 * tc3589x_reg_ग_लिखो() - ग_लिखो a single TC3589x रेजिस्टर
 * @tc3589x:	Device to ग_लिखो to
 * @reg:	Register to पढ़ो
 * @data:	Value to ग_लिखो
 */
पूर्णांक tc3589x_reg_ग_लिखो(काष्ठा tc3589x *tc3589x, u8 reg, u8 data)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(tc3589x->i2c, reg, data);
	अगर (ret < 0)
		dev_err(tc3589x->dev, "failed to write reg %#x: %d\n",
			reg, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tc3589x_reg_ग_लिखो);

/**
 * tc3589x_block_पढ़ो() - पढ़ो multiple TC3589x रेजिस्टरs
 * @tc3589x:	Device to पढ़ो from
 * @reg:	First रेजिस्टर
 * @length:	Number of रेजिस्टरs
 * @values:	Buffer to ग_लिखो to
 */
पूर्णांक tc3589x_block_पढ़ो(काष्ठा tc3589x *tc3589x, u8 reg, u8 length, u8 *values)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_i2c_block_data(tc3589x->i2c, reg, length, values);
	अगर (ret < 0)
		dev_err(tc3589x->dev, "failed to read regs %#x: %d\n",
			reg, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tc3589x_block_पढ़ो);

/**
 * tc3589x_block_ग_लिखो() - ग_लिखो multiple TC3589x रेजिस्टरs
 * @tc3589x:	Device to ग_लिखो to
 * @reg:	First रेजिस्टर
 * @length:	Number of रेजिस्टरs
 * @values:	Values to ग_लिखो
 */
पूर्णांक tc3589x_block_ग_लिखो(काष्ठा tc3589x *tc3589x, u8 reg, u8 length,
			स्थिर u8 *values)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_i2c_block_data(tc3589x->i2c, reg, length,
					     values);
	अगर (ret < 0)
		dev_err(tc3589x->dev, "failed to write regs %#x: %d\n",
			reg, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tc3589x_block_ग_लिखो);

/**
 * tc3589x_set_bits() - set the value of a bitfield in a TC3589x रेजिस्टर
 * @tc3589x:	Device to ग_लिखो to
 * @reg:	Register to ग_लिखो
 * @mask:	Mask of bits to set
 * @val:	Value to set
 */
पूर्णांक tc3589x_set_bits(काष्ठा tc3589x *tc3589x, u8 reg, u8 mask, u8 val)
अणु
	पूर्णांक ret;

	mutex_lock(&tc3589x->lock);

	ret = tc3589x_reg_पढ़ो(tc3589x, reg);
	अगर (ret < 0)
		जाओ out;

	ret &= ~mask;
	ret |= val;

	ret = tc3589x_reg_ग_लिखो(tc3589x, reg, ret);

out:
	mutex_unlock(&tc3589x->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tc3589x_set_bits);

अटल स्थिर काष्ठा resource gpio_resources[] = अणु
	अणु
		.start	= TC3589x_INT_GPIIRQ,
		.end	= TC3589x_INT_GPIIRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource keypad_resources[] = अणु
	अणु
		.start  = TC3589x_INT_KBसूचीQ,
		.end    = TC3589x_INT_KBसूचीQ,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell tc3589x_dev_gpio[] = अणु
	अणु
		.name		= "tc3589x-gpio",
		.num_resources	= ARRAY_SIZE(gpio_resources),
		.resources	= &gpio_resources[0],
		.of_compatible	= "toshiba,tc3589x-gpio",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell tc3589x_dev_keypad[] = अणु
	अणु
		.name           = "tc3589x-keypad",
		.num_resources  = ARRAY_SIZE(keypad_resources),
		.resources      = &keypad_resources[0],
		.of_compatible	= "toshiba,tc3589x-keypad",
	पूर्ण,
पूर्ण;

अटल irqवापस_t tc3589x_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tc3589x *tc3589x = data;
	पूर्णांक status;

again:
	status = tc3589x_reg_पढ़ो(tc3589x, TC3589x_IRQST);
	अगर (status < 0)
		वापस IRQ_NONE;

	जबतक (status) अणु
		पूर्णांक bit = __ffs(status);
		पूर्णांक virq = irq_create_mapping(tc3589x->करोमुख्य, bit);

		handle_nested_irq(virq);
		status &= ~(1 << bit);
	पूर्ण

	/*
	 * A dummy पढ़ो or ग_लिखो (to any रेजिस्टर) appears to be necessary to
	 * have the last पूर्णांकerrupt clear (क्रम example, GPIO IC ग_लिखो) take
	 * effect. In such a हाल, recheck क्रम any पूर्णांकerrupt which is still
	 * pending.
	 */
	status = tc3589x_reg_पढ़ो(tc3589x, TC3589x_IRQST);
	अगर (status)
		जाओ again;

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tc3589x_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
				irq_hw_number_t hwirq)
अणु
	काष्ठा tc3589x *tc3589x = d->host_data;

	irq_set_chip_data(virq, tc3589x);
	irq_set_chip_and_handler(virq, &dummy_irq_chip,
				handle_edge_irq);
	irq_set_nested_thपढ़ो(virq, 1);
	irq_set_noprobe(virq);

	वापस 0;
पूर्ण

अटल व्योम tc3589x_irq_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq)
अणु
	irq_set_chip_and_handler(virq, शून्य, शून्य);
	irq_set_chip_data(virq, शून्य);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops tc3589x_irq_ops = अणु
	.map    = tc3589x_irq_map,
	.unmap  = tc3589x_irq_unmap,
	.xlate  = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक tc3589x_irq_init(काष्ठा tc3589x *tc3589x, काष्ठा device_node *np)
अणु
	tc3589x->करोमुख्य = irq_करोमुख्य_add_simple(
		np, TC3589x_NR_INTERNAL_IRQS, 0,
		&tc3589x_irq_ops, tc3589x);

	अगर (!tc3589x->करोमुख्य) अणु
		dev_err(tc3589x->dev, "Failed to create irqdomain\n");
		वापस -ENOSYS;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tc3589x_chip_init(काष्ठा tc3589x *tc3589x)
अणु
	पूर्णांक manf, ver, ret;

	manf = tc3589x_reg_पढ़ो(tc3589x, TC3589x_MANFCODE);
	अगर (manf < 0)
		वापस manf;

	ver = tc3589x_reg_पढ़ो(tc3589x, TC3589x_VERSION);
	अगर (ver < 0)
		वापस ver;

	अगर (manf != TC3589x_MANFCODE_MAGIC) अणु
		dev_err(tc3589x->dev, "unknown manufacturer: %#x\n", manf);
		वापस -EINVAL;
	पूर्ण

	dev_info(tc3589x->dev, "manufacturer: %#x, version: %#x\n", manf, ver);

	/*
	 * Put everything except the IRQ module पूर्णांकo reset;
	 * also spare the GPIO module क्रम any pin initialization
	 * करोne during pre-kernel boot
	 */
	ret = tc3589x_reg_ग_लिखो(tc3589x, TC3589x_RSTCTRL,
				TC3589x_RSTCTRL_TIMRST
				| TC3589x_RSTCTRL_ROTRST
				| TC3589x_RSTCTRL_KBDRST);
	अगर (ret < 0)
		वापस ret;

	/* Clear the reset पूर्णांकerrupt. */
	वापस tc3589x_reg_ग_लिखो(tc3589x, TC3589x_RSTINTCLR, 0x1);
पूर्ण

अटल पूर्णांक tc3589x_device_init(काष्ठा tc3589x *tc3589x)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक blocks = tc3589x->pdata->block;

	अगर (blocks & TC3589x_BLOCK_GPIO) अणु
		ret = mfd_add_devices(tc3589x->dev, -1, tc3589x_dev_gpio,
				      ARRAY_SIZE(tc3589x_dev_gpio), शून्य,
				      0, tc3589x->करोमुख्य);
		अगर (ret) अणु
			dev_err(tc3589x->dev, "failed to add gpio child\n");
			वापस ret;
		पूर्ण
		dev_info(tc3589x->dev, "added gpio block\n");
	पूर्ण

	अगर (blocks & TC3589x_BLOCK_KEYPAD) अणु
		ret = mfd_add_devices(tc3589x->dev, -1, tc3589x_dev_keypad,
				      ARRAY_SIZE(tc3589x_dev_keypad), शून्य,
				      0, tc3589x->करोमुख्य);
		अगर (ret) अणु
			dev_err(tc3589x->dev, "failed to keypad child\n");
			वापस ret;
		पूर्ण
		dev_info(tc3589x->dev, "added keypad block\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id tc3589x_match[] = अणु
	/* Legacy compatible string */
	अणु .compatible = "tc3589x", .data = (व्योम *) TC3589X_UNKNOWN पूर्ण,
	अणु .compatible = "toshiba,tc35890", .data = (व्योम *) TC3589X_TC35890 पूर्ण,
	अणु .compatible = "toshiba,tc35892", .data = (व्योम *) TC3589X_TC35892 पूर्ण,
	अणु .compatible = "toshiba,tc35893", .data = (व्योम *) TC3589X_TC35893 पूर्ण,
	अणु .compatible = "toshiba,tc35894", .data = (व्योम *) TC3589X_TC35894 पूर्ण,
	अणु .compatible = "toshiba,tc35895", .data = (व्योम *) TC3589X_TC35895 पूर्ण,
	अणु .compatible = "toshiba,tc35896", .data = (व्योम *) TC3589X_TC35896 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, tc3589x_match);

अटल काष्ठा tc3589x_platक्रमm_data *
tc3589x_of_probe(काष्ठा device *dev, क्रमागत tc3589x_version *version)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा tc3589x_platक्रमm_data *pdata;
	काष्ठा device_node *child;
	स्थिर काष्ठा of_device_id *of_id;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	of_id = of_match_device(tc3589x_match, dev);
	अगर (!of_id)
		वापस ERR_PTR(-ENODEV);
	*version = (क्रमागत tc3589x_version) of_id->data;

	क्रम_each_child_of_node(np, child) अणु
		अगर (of_device_is_compatible(child, "toshiba,tc3589x-gpio"))
			pdata->block |= TC3589x_BLOCK_GPIO;
		अगर (of_device_is_compatible(child, "toshiba,tc3589x-keypad"))
			pdata->block |= TC3589x_BLOCK_KEYPAD;
	पूर्ण

	वापस pdata;
पूर्ण

अटल पूर्णांक tc3589x_probe(काष्ठा i2c_client *i2c,
				   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device_node *np = i2c->dev.of_node;
	काष्ठा tc3589x_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	काष्ठा tc3589x *tc3589x;
	क्रमागत tc3589x_version version;
	पूर्णांक ret;

	अगर (!pdata) अणु
		pdata = tc3589x_of_probe(&i2c->dev, &version);
		अगर (IS_ERR(pdata)) अणु
			dev_err(&i2c->dev, "No platform data or DT found\n");
			वापस PTR_ERR(pdata);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* When not probing from device tree we have this ID */
		version = id->driver_data;
	पूर्ण

	अगर (!i2c_check_functionality(i2c->adapter, I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_I2C_BLOCK))
		वापस -EIO;

	tc3589x = devm_kzalloc(&i2c->dev, माप(काष्ठा tc3589x),
				GFP_KERNEL);
	अगर (!tc3589x)
		वापस -ENOMEM;

	mutex_init(&tc3589x->lock);

	tc3589x->dev = &i2c->dev;
	tc3589x->i2c = i2c;
	tc3589x->pdata = pdata;

	चयन (version) अणु
	हाल TC3589X_TC35893:
	हाल TC3589X_TC35895:
	हाल TC3589X_TC35896:
		tc3589x->num_gpio = 20;
		अवरोध;
	हाल TC3589X_TC35890:
	हाल TC3589X_TC35892:
	हाल TC3589X_TC35894:
	हाल TC3589X_UNKNOWN:
	शेष:
		tc3589x->num_gpio = 24;
		अवरोध;
	पूर्ण

	i2c_set_clientdata(i2c, tc3589x);

	ret = tc3589x_chip_init(tc3589x);
	अगर (ret)
		वापस ret;

	ret = tc3589x_irq_init(tc3589x, np);
	अगर (ret)
		वापस ret;

	ret = request_thपढ़ोed_irq(tc3589x->i2c->irq, शून्य, tc3589x_irq,
				   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				   "tc3589x", tc3589x);
	अगर (ret) अणु
		dev_err(tc3589x->dev, "failed to request IRQ: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = tc3589x_device_init(tc3589x);
	अगर (ret) अणु
		dev_err(tc3589x->dev, "failed to add child devices\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tc3589x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tc3589x *tc3589x = i2c_get_clientdata(client);

	mfd_हटाओ_devices(tc3589x->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tc3589x_suspend(काष्ठा device *dev)
अणु
	काष्ठा tc3589x *tc3589x = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = tc3589x->i2c;
	पूर्णांक ret = 0;

	/* put the प्रणाली to sleep mode */
	अगर (!device_may_wakeup(&client->dev))
		ret = tc3589x_reg_ग_लिखो(tc3589x, TC3589x_CLKMODE,
				TC3589x_CLKMODE_MODCTL_SLEEP);

	वापस ret;
पूर्ण

अटल पूर्णांक tc3589x_resume(काष्ठा device *dev)
अणु
	काष्ठा tc3589x *tc3589x = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = tc3589x->i2c;
	पूर्णांक ret = 0;

	/* enable the प्रणाली पूर्णांकo operation */
	अगर (!device_may_wakeup(&client->dev))
		ret = tc3589x_reg_ग_लिखो(tc3589x, TC3589x_CLKMODE,
				TC3589x_CLKMODE_MODCTL_OPERATION);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tc3589x_dev_pm_ops, tc3589x_suspend, tc3589x_resume);

अटल स्थिर काष्ठा i2c_device_id tc3589x_id[] = अणु
	अणु "tc35890", TC3589X_TC35890 पूर्ण,
	अणु "tc35892", TC3589X_TC35892 पूर्ण,
	अणु "tc35893", TC3589X_TC35893 पूर्ण,
	अणु "tc35894", TC3589X_TC35894 पूर्ण,
	अणु "tc35895", TC3589X_TC35895 पूर्ण,
	अणु "tc35896", TC3589X_TC35896 पूर्ण,
	अणु "tc3589x", TC3589X_UNKNOWN पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tc3589x_id);

अटल काष्ठा i2c_driver tc3589x_driver = अणु
	.driver = अणु
		.name	= "tc3589x",
		.pm	= &tc3589x_dev_pm_ops,
		.of_match_table = of_match_ptr(tc3589x_match),
	पूर्ण,
	.probe		= tc3589x_probe,
	.हटाओ		= tc3589x_हटाओ,
	.id_table	= tc3589x_id,
पूर्ण;

अटल पूर्णांक __init tc3589x_init(व्योम)
अणु
	वापस i2c_add_driver(&tc3589x_driver);
पूर्ण
subsys_initcall(tc3589x_init);

अटल व्योम __निकास tc3589x_निकास(व्योम)
अणु
	i2c_del_driver(&tc3589x_driver);
पूर्ण
module_निकास(tc3589x_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TC3589x MFD core driver");
MODULE_AUTHOR("Hanumath Prasad, Rabin Vincent");
