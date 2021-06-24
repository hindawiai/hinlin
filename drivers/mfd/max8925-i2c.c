<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C driver क्रम Maxim MAX8925
 *
 * Copyright (C) 2009 Marvell International Ltd.
 *	Haojian Zhuang <haojian.zhuang@marvell.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/max8925.h>
#समावेश <linux/slab.h>

#घोषणा RTC_I2C_ADDR		0x68
#घोषणा ADC_I2C_ADDR		0x47

अटल अंतरभूत पूर्णांक max8925_पढ़ो_device(काष्ठा i2c_client *i2c,
				      पूर्णांक reg, पूर्णांक bytes, व्योम *dest)
अणु
	पूर्णांक ret;

	अगर (bytes > 1)
		ret = i2c_smbus_पढ़ो_i2c_block_data(i2c, reg, bytes, dest);
	अन्यथा अणु
		ret = i2c_smbus_पढ़ो_byte_data(i2c, reg);
		अगर (ret < 0)
			वापस ret;
		*(अचिन्हित अक्षर *)dest = (अचिन्हित अक्षर)ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक max8925_ग_लिखो_device(काष्ठा i2c_client *i2c,
				       पूर्णांक reg, पूर्णांक bytes, व्योम *src)
अणु
	अचिन्हित अक्षर buf[9];
	पूर्णांक ret;

	buf[0] = (अचिन्हित अक्षर)reg;
	स_नकल(&buf[1], src, bytes);

	ret = i2c_master_send(i2c, buf, bytes + 1);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

पूर्णांक max8925_reg_पढ़ो(काष्ठा i2c_client *i2c, पूर्णांक reg)
अणु
	काष्ठा max8925_chip *chip = i2c_get_clientdata(i2c);
	अचिन्हित अक्षर data = 0;
	पूर्णांक ret;

	mutex_lock(&chip->io_lock);
	ret = max8925_पढ़ो_device(i2c, reg, 1, &data);
	mutex_unlock(&chip->io_lock);

	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस (पूर्णांक)data;
पूर्ण
EXPORT_SYMBOL(max8925_reg_पढ़ो);

पूर्णांक max8925_reg_ग_लिखो(काष्ठा i2c_client *i2c, पूर्णांक reg,
		अचिन्हित अक्षर data)
अणु
	काष्ठा max8925_chip *chip = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	mutex_lock(&chip->io_lock);
	ret = max8925_ग_लिखो_device(i2c, reg, 1, &data);
	mutex_unlock(&chip->io_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(max8925_reg_ग_लिखो);

पूर्णांक max8925_bulk_पढ़ो(काष्ठा i2c_client *i2c, पूर्णांक reg,
		पूर्णांक count, अचिन्हित अक्षर *buf)
अणु
	काष्ठा max8925_chip *chip = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	mutex_lock(&chip->io_lock);
	ret = max8925_पढ़ो_device(i2c, reg, count, buf);
	mutex_unlock(&chip->io_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(max8925_bulk_पढ़ो);

पूर्णांक max8925_bulk_ग_लिखो(काष्ठा i2c_client *i2c, पूर्णांक reg,
		पूर्णांक count, अचिन्हित अक्षर *buf)
अणु
	काष्ठा max8925_chip *chip = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	mutex_lock(&chip->io_lock);
	ret = max8925_ग_लिखो_device(i2c, reg, count, buf);
	mutex_unlock(&chip->io_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(max8925_bulk_ग_लिखो);

पूर्णांक max8925_set_bits(काष्ठा i2c_client *i2c, पूर्णांक reg,
		अचिन्हित अक्षर mask, अचिन्हित अक्षर data)
अणु
	काष्ठा max8925_chip *chip = i2c_get_clientdata(i2c);
	अचिन्हित अक्षर value;
	पूर्णांक ret;

	mutex_lock(&chip->io_lock);
	ret = max8925_पढ़ो_device(i2c, reg, 1, &value);
	अगर (ret < 0)
		जाओ out;
	value &= ~mask;
	value |= data;
	ret = max8925_ग_लिखो_device(i2c, reg, 1, &value);
out:
	mutex_unlock(&chip->io_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(max8925_set_bits);


अटल स्थिर काष्ठा i2c_device_id max8925_id_table[] = अणु
	अणु "max8925", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक max8925_dt_init(काष्ठा device_node *np, काष्ठा device *dev,
			   काष्ठा max8925_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "maxim,tsc-irq", &pdata->tsc_irq);
	अगर (ret) अणु
		dev_err(dev, "Not found maxim,tsc-irq property\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max8925_probe(काष्ठा i2c_client *client,
				   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max8925_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा max8925_chip *chip;
	काष्ठा device_node *node = client->dev.of_node;

	अगर (node && !pdata) अणु
		/* parse DT to get platक्रमm data */
		pdata = devm_kzalloc(&client->dev,
				     माप(काष्ठा max8925_platक्रमm_data),
				     GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;

		अगर (max8925_dt_init(node, &client->dev, pdata))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (!pdata) अणु
		pr_info("%s: platform data is missing\n", __func__);
		वापस -EINVAL;
	पूर्ण

	chip = devm_kzalloc(&client->dev,
			    माप(काष्ठा max8925_chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;
	chip->i2c = client;
	chip->dev = &client->dev;
	i2c_set_clientdata(client, chip);
	dev_set_drvdata(chip->dev, chip);
	mutex_init(&chip->io_lock);

	chip->rtc = i2c_new_dummy_device(chip->i2c->adapter, RTC_I2C_ADDR);
	अगर (IS_ERR(chip->rtc)) अणु
		dev_err(chip->dev, "Failed to allocate I2C device for RTC\n");
		वापस PTR_ERR(chip->rtc);
	पूर्ण
	i2c_set_clientdata(chip->rtc, chip);

	chip->adc = i2c_new_dummy_device(chip->i2c->adapter, ADC_I2C_ADDR);
	अगर (IS_ERR(chip->adc)) अणु
		dev_err(chip->dev, "Failed to allocate I2C device for ADC\n");
		i2c_unरेजिस्टर_device(chip->rtc);
		वापस PTR_ERR(chip->adc);
	पूर्ण
	i2c_set_clientdata(chip->adc, chip);

	device_init_wakeup(&client->dev, 1);

	max8925_device_init(chip, pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक max8925_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा max8925_chip *chip = i2c_get_clientdata(client);

	max8925_device_निकास(chip);
	i2c_unरेजिस्टर_device(chip->adc);
	i2c_unरेजिस्टर_device(chip->rtc);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक max8925_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा max8925_chip *chip = i2c_get_clientdata(client);

	अगर (device_may_wakeup(dev) && chip->wakeup_flag)
		enable_irq_wake(chip->core_irq);
	वापस 0;
पूर्ण

अटल पूर्णांक max8925_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा max8925_chip *chip = i2c_get_clientdata(client);

	अगर (device_may_wakeup(dev) && chip->wakeup_flag)
		disable_irq_wake(chip->core_irq);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(max8925_pm_ops, max8925_suspend, max8925_resume);

अटल स्थिर काष्ठा of_device_id max8925_dt_ids[] = अणु
	अणु .compatible = "maxim,max8925", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा i2c_driver max8925_driver = अणु
	.driver	= अणु
		.name	= "max8925",
		.pm     = &max8925_pm_ops,
		.of_match_table = max8925_dt_ids,
	पूर्ण,
	.probe		= max8925_probe,
	.हटाओ		= max8925_हटाओ,
	.id_table	= max8925_id_table,
पूर्ण;

अटल पूर्णांक __init max8925_i2c_init(व्योम)
अणु
	पूर्णांक ret;

	ret = i2c_add_driver(&max8925_driver);
	अगर (ret != 0)
		pr_err("Failed to register MAX8925 I2C driver: %d\n", ret);

	वापस ret;
पूर्ण
subsys_initcall(max8925_i2c_init);
