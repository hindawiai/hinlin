<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Voltage and current regulation क्रम AD5398 and AD5821
 *
 * Copyright 2010 Analog Devices Inc.
 *
 * Enter bugs at http://blackfin.uclinux.org/
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>

#घोषणा AD5398_CURRENT_EN_MASK	0x8000

काष्ठा ad5398_chip_info अणु
	काष्ठा i2c_client *client;
	पूर्णांक min_uA;
	पूर्णांक max_uA;
	अचिन्हित पूर्णांक current_level;
	अचिन्हित पूर्णांक current_mask;
	अचिन्हित पूर्णांक current_offset;
	काष्ठा regulator_dev *rdev;
पूर्ण;

अटल पूर्णांक ad5398_calc_current(काष्ठा ad5398_chip_info *chip,
	अचिन्हित selector)
अणु
	अचिन्हित range_uA = chip->max_uA - chip->min_uA;

	वापस chip->min_uA + (selector * range_uA / chip->current_level);
पूर्ण

अटल पूर्णांक ad5398_पढ़ो_reg(काष्ठा i2c_client *client, अचिन्हित लघु *data)
अणु
	अचिन्हित लघु val;
	पूर्णांक ret;

	ret = i2c_master_recv(client, (अक्षर *)&val, 2);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "I2C read error\n");
		वापस ret;
	पूर्ण
	*data = be16_to_cpu(val);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5398_ग_लिखो_reg(काष्ठा i2c_client *client, स्थिर अचिन्हित लघु data)
अणु
	अचिन्हित लघु val;
	पूर्णांक ret;

	val = cpu_to_be16(data);
	ret = i2c_master_send(client, (अक्षर *)&val, 2);
	अगर (ret != 2) अणु
		dev_err(&client->dev, "I2C write error\n");
		वापस ret < 0 ? ret : -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad5398_get_current_limit(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा ad5398_chip_info *chip = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *client = chip->client;
	अचिन्हित लघु data;
	पूर्णांक ret;

	ret = ad5398_पढ़ो_reg(client, &data);
	अगर (ret < 0)
		वापस ret;

	ret = (data & chip->current_mask) >> chip->current_offset;

	वापस ad5398_calc_current(chip, ret);
पूर्ण

अटल पूर्णांक ad5398_set_current_limit(काष्ठा regulator_dev *rdev, पूर्णांक min_uA, पूर्णांक max_uA)
अणु
	काष्ठा ad5398_chip_info *chip = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *client = chip->client;
	अचिन्हित range_uA = chip->max_uA - chip->min_uA;
	अचिन्हित selector;
	अचिन्हित लघु data;
	पूर्णांक ret;

	अगर (min_uA < chip->min_uA)
		min_uA = chip->min_uA;
	अगर (max_uA > chip->max_uA)
		max_uA = chip->max_uA;

	अगर (min_uA > chip->max_uA || max_uA < chip->min_uA)
		वापस -EINVAL;

	selector = DIV_ROUND_UP((min_uA - chip->min_uA) * chip->current_level,
				range_uA);
	अगर (ad5398_calc_current(chip, selector) > max_uA)
		वापस -EINVAL;

	dev_dbg(&client->dev, "changing current %duA\n",
		ad5398_calc_current(chip, selector));

	/* पढ़ो chip enable bit */
	ret = ad5398_पढ़ो_reg(client, &data);
	अगर (ret < 0)
		वापस ret;

	/* prepare रेजिस्टर data */
	selector = (selector << chip->current_offset) & chip->current_mask;
	data = (अचिन्हित लघु)selector | (data & AD5398_CURRENT_EN_MASK);

	/* ग_लिखो the new current value back as well as enable bit */
	ret = ad5398_ग_लिखो_reg(client, data);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5398_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा ad5398_chip_info *chip = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *client = chip->client;
	अचिन्हित लघु data;
	पूर्णांक ret;

	ret = ad5398_पढ़ो_reg(client, &data);
	अगर (ret < 0)
		वापस ret;

	अगर (data & AD5398_CURRENT_EN_MASK)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक ad5398_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा ad5398_chip_info *chip = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *client = chip->client;
	अचिन्हित लघु data;
	पूर्णांक ret;

	ret = ad5398_पढ़ो_reg(client, &data);
	अगर (ret < 0)
		वापस ret;

	अगर (data & AD5398_CURRENT_EN_MASK)
		वापस 0;

	data |= AD5398_CURRENT_EN_MASK;

	ret = ad5398_ग_लिखो_reg(client, data);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5398_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा ad5398_chip_info *chip = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *client = chip->client;
	अचिन्हित लघु data;
	पूर्णांक ret;

	ret = ad5398_पढ़ो_reg(client, &data);
	अगर (ret < 0)
		वापस ret;

	अगर (!(data & AD5398_CURRENT_EN_MASK))
		वापस 0;

	data &= ~AD5398_CURRENT_EN_MASK;

	ret = ad5398_ग_लिखो_reg(client, data);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops ad5398_ops = अणु
	.get_current_limit = ad5398_get_current_limit,
	.set_current_limit = ad5398_set_current_limit,
	.enable = ad5398_enable,
	.disable = ad5398_disable,
	.is_enabled = ad5398_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc ad5398_reg = अणु
	.name = "isink",
	.id = 0,
	.ops = &ad5398_ops,
	.type = REGULATOR_CURRENT,
	.owner = THIS_MODULE,
पूर्ण;

काष्ठा ad5398_current_data_क्रमmat अणु
	पूर्णांक current_bits;
	पूर्णांक current_offset;
	पूर्णांक min_uA;
	पूर्णांक max_uA;
पूर्ण;

अटल स्थिर काष्ठा ad5398_current_data_क्रमmat df_10_4_120 = अणु10, 4, 0, 120000पूर्ण;

अटल स्थिर काष्ठा i2c_device_id ad5398_id[] = अणु
	अणु "ad5398", (kernel_uदीर्घ_t)&df_10_4_120 पूर्ण,
	अणु "ad5821", (kernel_uदीर्घ_t)&df_10_4_120 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad5398_id);

अटल पूर्णांक ad5398_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regulator_init_data *init_data = dev_get_platdata(&client->dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा ad5398_chip_info *chip;
	स्थिर काष्ठा ad5398_current_data_क्रमmat *df =
			(काष्ठा ad5398_current_data_क्रमmat *)id->driver_data;

	अगर (!init_data)
		वापस -EINVAL;

	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	config.dev = &client->dev;
	config.init_data = init_data;
	config.driver_data = chip;

	chip->client = client;

	chip->min_uA = df->min_uA;
	chip->max_uA = df->max_uA;
	chip->current_level = 1 << df->current_bits;
	chip->current_offset = df->current_offset;
	chip->current_mask = (chip->current_level - 1) << chip->current_offset;

	chip->rdev = devm_regulator_रेजिस्टर(&client->dev, &ad5398_reg,
					     &config);
	अगर (IS_ERR(chip->rdev)) अणु
		dev_err(&client->dev, "failed to register %s %s\n",
			id->name, ad5398_reg.name);
		वापस PTR_ERR(chip->rdev);
	पूर्ण

	i2c_set_clientdata(client, chip);
	dev_dbg(&client->dev, "%s regulator driver is registered.\n", id->name);
	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver ad5398_driver = अणु
	.probe = ad5398_probe,
	.driver		= अणु
		.name	= "ad5398",
	पूर्ण,
	.id_table	= ad5398_id,
पूर्ण;

अटल पूर्णांक __init ad5398_init(व्योम)
अणु
	वापस i2c_add_driver(&ad5398_driver);
पूर्ण
subsys_initcall(ad5398_init);

अटल व्योम __निकास ad5398_निकास(व्योम)
अणु
	i2c_del_driver(&ad5398_driver);
पूर्ण
module_निकास(ad5398_निकास);

MODULE_DESCRIPTION("AD5398 and AD5821 current regulator driver");
MODULE_AUTHOR("Sonic Zhang");
MODULE_LICENSE("GPL");
