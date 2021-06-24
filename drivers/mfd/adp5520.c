<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Base driver क्रम Analog Devices ADP5520/ADP5501 MFD PMICs
 * LCD Backlight: drivers/video/backlight/adp5520_bl
 * LEDs		: drivers/led/leds-adp5520
 * GPIO		: drivers/gpio/adp5520-gpio (ADP5520 only)
 * Keys		: drivers/input/keyboard/adp5520-keys (ADP5520 only)
 *
 * Copyright 2009 Analog Devices Inc.
 *
 * Author: Michael Hennerich <michael.hennerich@analog.com>
 *
 * Derived from da903x:
 * Copyright (C) 2008 Compulab, Ltd.
 *	Mike Rapoport <mike@compulab.co.il>
 *
 * Copyright (C) 2006-2008 Marvell International Ltd.
 *	Eric Miao <eric.miao@marvell.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>

#समावेश <linux/mfd/adp5520.h>

काष्ठा adp5520_chip अणु
	काष्ठा i2c_client *client;
	काष्ठा device *dev;
	काष्ठा mutex lock;
	काष्ठा blocking_notअगरier_head notअगरier_list;
	पूर्णांक irq;
	अचिन्हित दीर्घ id;
	uपूर्णांक8_t mode;
पूर्ण;

अटल पूर्णांक __adp5520_पढ़ो(काष्ठा i2c_client *client,
				पूर्णांक reg, uपूर्णांक8_t *val)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed reading at 0x%02x\n", reg);
		वापस ret;
	पूर्ण

	*val = (uपूर्णांक8_t)ret;
	वापस 0;
पूर्ण

अटल पूर्णांक __adp5520_ग_लिखो(काष्ठा i2c_client *client,
				 पूर्णांक reg, uपूर्णांक8_t val)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed writing 0x%02x to 0x%02x\n",
				val, reg);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __adp5520_ack_bits(काष्ठा i2c_client *client, पूर्णांक reg,
			      uपूर्णांक8_t bit_mask)
अणु
	काष्ठा adp5520_chip *chip = i2c_get_clientdata(client);
	uपूर्णांक8_t reg_val;
	पूर्णांक ret;

	mutex_lock(&chip->lock);

	ret = __adp5520_पढ़ो(client, reg, &reg_val);

	अगर (!ret) अणु
		reg_val |= bit_mask;
		ret = __adp5520_ग_लिखो(client, reg, reg_val);
	पूर्ण

	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

पूर्णांक adp5520_ग_लिखो(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t val)
अणु
	वापस __adp5520_ग_लिखो(to_i2c_client(dev), reg, val);
पूर्ण
EXPORT_SYMBOL_GPL(adp5520_ग_लिखो);

पूर्णांक adp5520_पढ़ो(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t *val)
अणु
	वापस __adp5520_पढ़ो(to_i2c_client(dev), reg, val);
पूर्ण
EXPORT_SYMBOL_GPL(adp5520_पढ़ो);

पूर्णांक adp5520_set_bits(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t bit_mask)
अणु
	काष्ठा adp5520_chip *chip = dev_get_drvdata(dev);
	uपूर्णांक8_t reg_val;
	पूर्णांक ret;

	mutex_lock(&chip->lock);

	ret = __adp5520_पढ़ो(chip->client, reg, &reg_val);

	अगर (!ret && ((reg_val & bit_mask) != bit_mask)) अणु
		reg_val |= bit_mask;
		ret = __adp5520_ग_लिखो(chip->client, reg, reg_val);
	पूर्ण

	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(adp5520_set_bits);

पूर्णांक adp5520_clr_bits(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t bit_mask)
अणु
	काष्ठा adp5520_chip *chip = dev_get_drvdata(dev);
	uपूर्णांक8_t reg_val;
	पूर्णांक ret;

	mutex_lock(&chip->lock);

	ret = __adp5520_पढ़ो(chip->client, reg, &reg_val);

	अगर (!ret && (reg_val & bit_mask)) अणु
		reg_val &= ~bit_mask;
		ret = __adp5520_ग_लिखो(chip->client, reg, reg_val);
	पूर्ण

	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(adp5520_clr_bits);

पूर्णांक adp5520_रेजिस्टर_notअगरier(काष्ठा device *dev, काष्ठा notअगरier_block *nb,
				अचिन्हित पूर्णांक events)
अणु
	काष्ठा adp5520_chip *chip = dev_get_drvdata(dev);

	अगर (chip->irq) अणु
		adp5520_set_bits(chip->dev, ADP5520_INTERRUPT_ENABLE,
			events & (ADP5520_KP_IEN | ADP5520_KR_IEN |
			ADP5520_OVP_IEN | ADP5520_CMPR_IEN));

		वापस blocking_notअगरier_chain_रेजिस्टर(&chip->notअगरier_list,
			 nb);
	पूर्ण

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(adp5520_रेजिस्टर_notअगरier);

पूर्णांक adp5520_unरेजिस्टर_notअगरier(काष्ठा device *dev, काष्ठा notअगरier_block *nb,
				अचिन्हित पूर्णांक events)
अणु
	काष्ठा adp5520_chip *chip = dev_get_drvdata(dev);

	adp5520_clr_bits(chip->dev, ADP5520_INTERRUPT_ENABLE,
		events & (ADP5520_KP_IEN | ADP5520_KR_IEN |
		ADP5520_OVP_IEN | ADP5520_CMPR_IEN));

	वापस blocking_notअगरier_chain_unरेजिस्टर(&chip->notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(adp5520_unरेजिस्टर_notअगरier);

अटल irqवापस_t adp5520_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा adp5520_chip *chip = data;
	अचिन्हित पूर्णांक events;
	uपूर्णांक8_t reg_val;
	पूर्णांक ret;

	ret = __adp5520_पढ़ो(chip->client, ADP5520_MODE_STATUS, &reg_val);
	अगर (ret)
		जाओ out;

	events =  reg_val & (ADP5520_OVP_INT | ADP5520_CMPR_INT |
		ADP5520_GPI_INT | ADP5520_KR_INT | ADP5520_KP_INT);

	blocking_notअगरier_call_chain(&chip->notअगरier_list, events, शून्य);
	/* ACK, Sticky bits are W1C */
	__adp5520_ack_bits(chip->client, ADP5520_MODE_STATUS, events);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __हटाओ_subdev(काष्ठा device *dev, व्योम *unused)
अणु
	platक्रमm_device_unरेजिस्टर(to_platक्रमm_device(dev));
	वापस 0;
पूर्ण

अटल पूर्णांक adp5520_हटाओ_subdevs(काष्ठा adp5520_chip *chip)
अणु
	वापस device_क्रम_each_child(chip->dev, शून्य, __हटाओ_subdev);
पूर्ण

अटल पूर्णांक adp5520_probe(काष्ठा i2c_client *client,
					स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adp5520_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा platक्रमm_device *pdev;
	काष्ठा adp5520_chip *chip;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
					I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(&client->dev, "SMBUS Word Data not Supported\n");
		वापस -EIO;
	पूर्ण

	अगर (pdata == शून्य) अणु
		dev_err(&client->dev, "missing platform data\n");
		वापस -ENODEV;
	पूर्ण

	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	i2c_set_clientdata(client, chip);
	chip->client = client;

	chip->dev = &client->dev;
	chip->irq = client->irq;
	chip->id = id->driver_data;
	mutex_init(&chip->lock);

	अगर (chip->irq) अणु
		BLOCKING_INIT_NOTIFIER_HEAD(&chip->notअगरier_list);

		ret = request_thपढ़ोed_irq(chip->irq, शून्य, adp5520_irq_thपढ़ो,
				IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				"adp5520", chip);
		अगर (ret) अणु
			dev_err(&client->dev, "failed to request irq %d\n",
					chip->irq);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = adp5520_ग_लिखो(chip->dev, ADP5520_MODE_STATUS, ADP5520_nSTNBY);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to write\n");
		जाओ out_मुक्त_irq;
	पूर्ण

	अगर (pdata->keys) अणु
		pdev = platक्रमm_device_रेजिस्टर_data(chip->dev, "adp5520-keys",
				chip->id, pdata->keys, माप(*pdata->keys));
		अगर (IS_ERR(pdev)) अणु
			ret = PTR_ERR(pdev);
			जाओ out_हटाओ_subdevs;
		पूर्ण
	पूर्ण

	अगर (pdata->gpio) अणु
		pdev = platक्रमm_device_रेजिस्टर_data(chip->dev, "adp5520-gpio",
				chip->id, pdata->gpio, माप(*pdata->gpio));
		अगर (IS_ERR(pdev)) अणु
			ret = PTR_ERR(pdev);
			जाओ out_हटाओ_subdevs;
		पूर्ण
	पूर्ण

	अगर (pdata->leds) अणु
		pdev = platक्रमm_device_रेजिस्टर_data(chip->dev, "adp5520-led",
				chip->id, pdata->leds, माप(*pdata->leds));
		अगर (IS_ERR(pdev)) अणु
			ret = PTR_ERR(pdev);
			जाओ out_हटाओ_subdevs;
		पूर्ण
	पूर्ण

	अगर (pdata->backlight) अणु
		pdev = platक्रमm_device_रेजिस्टर_data(chip->dev,
						"adp5520-backlight",
						chip->id,
						pdata->backlight,
						माप(*pdata->backlight));
		अगर (IS_ERR(pdev)) अणु
			ret = PTR_ERR(pdev);
			जाओ out_हटाओ_subdevs;
		पूर्ण
	पूर्ण

	वापस 0;

out_हटाओ_subdevs:
	adp5520_हटाओ_subdevs(chip);

out_मुक्त_irq:
	अगर (chip->irq)
		मुक्त_irq(chip->irq, chip);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक adp5520_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा adp5520_chip *chip = dev_get_drvdata(&client->dev);

	adp5520_पढ़ो(chip->dev, ADP5520_MODE_STATUS, &chip->mode);
	/* All other bits are W1C */
	chip->mode &= ADP5520_BL_EN | ADP5520_DIM_EN | ADP5520_nSTNBY;
	adp5520_ग_लिखो(chip->dev, ADP5520_MODE_STATUS, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक adp5520_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा adp5520_chip *chip = dev_get_drvdata(&client->dev);

	adp5520_ग_लिखो(chip->dev, ADP5520_MODE_STATUS, chip->mode);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(adp5520_pm, adp5520_suspend, adp5520_resume);

अटल स्थिर काष्ठा i2c_device_id adp5520_id[] = अणु
	अणु "pmic-adp5520", ID_ADP5520 पूर्ण,
	अणु "pmic-adp5501", ID_ADP5501 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver adp5520_driver = अणु
	.driver = अणु
		.name			= "adp5520",
		.pm			= &adp5520_pm,
		.suppress_bind_attrs	= true,
	पूर्ण,
	.probe		= adp5520_probe,
	.id_table	= adp5520_id,
पूर्ण;
builtin_i2c_driver(adp5520_driver);
