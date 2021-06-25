<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C driver क्रम Marvell 88PM80x
 *
 * Copyright (C) 2012 Marvell International Ltd.
 * Haojian Zhuang <haojian.zhuang@marvell.com>
 * Joseph(Yossi) Hanin <yhanin@marvell.com>
 * Qiao Zhou <zhouqiao@marvell.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/88pm80x.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/err.h>

/* 88pm80x chips have same definition क्रम chip id रेजिस्टर. */
#घोषणा PM80X_CHIP_ID			(0x00)
#घोषणा PM80X_CHIP_ID_NUM(x)		(((x) >> 5) & 0x7)
#घोषणा PM80X_CHIP_ID_REVISION(x)	((x) & 0x1F)

काष्ठा pm80x_chip_mapping अणु
	अचिन्हित पूर्णांक	id;
	पूर्णांक		type;
पूर्ण;

अटल काष्ठा pm80x_chip_mapping chip_mapping[] = अणु
	/* 88PM800 chip id number */
	अणु0x3,	CHIP_PM800पूर्ण,
	/* 88PM805 chip id number */
	अणु0x0,	CHIP_PM805पूर्ण,
	/* 88PM860 chip id number */
	अणु0x4,	CHIP_PM860पूर्ण,
पूर्ण;

/*
 * workaround: some रेजिस्टरs needed by pm805 are defined in pm800, so
 * need to use this global variable to मुख्यtain the relation between
 * pm800 and pm805. would हटाओ it after HW chip fixes the issue.
 */
अटल काष्ठा pm80x_chip *g_pm80x_chip;

स्थिर काष्ठा regmap_config pm80x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;
EXPORT_SYMBOL_GPL(pm80x_regmap_config);


पूर्णांक pm80x_init(काष्ठा i2c_client *client)
अणु
	काष्ठा pm80x_chip *chip;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक val;
	पूर्णांक i, ret = 0;

	chip =
	    devm_kzalloc(&client->dev, माप(काष्ठा pm80x_chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	map = devm_regmap_init_i2c(client, &pm80x_regmap_config);
	अगर (IS_ERR(map)) अणु
		ret = PTR_ERR(map);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	chip->client = client;
	chip->regmap = map;

	chip->irq = client->irq;

	chip->dev = &client->dev;
	dev_set_drvdata(chip->dev, chip);
	i2c_set_clientdata(chip->client, chip);

	ret = regmap_पढ़ो(chip->regmap, PM80X_CHIP_ID, &val);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to read CHIP ID: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(chip_mapping); i++) अणु
		अगर (chip_mapping[i].id == PM80X_CHIP_ID_NUM(val)) अणु
			chip->type = chip_mapping[i].type;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(chip_mapping)) अणु
		dev_err(chip->dev,
			"Failed to detect Marvell 88PM800:ChipID[0x%x]\n", val);
		वापस -EINVAL;
	पूर्ण

	device_init_wakeup(&client->dev, 1);

	/*
	 * workaround: set g_pm80x_chip to the first probed chip. अगर the
	 * second chip is probed, just poपूर्णांक to the companion to each
	 * other so that pm805 can access those specअगरic रेजिस्टर. would
	 * हटाओ it after HW chip fixes the issue.
	 */
	अगर (!g_pm80x_chip)
		g_pm80x_chip = chip;
	अन्यथा अणु
		chip->companion = g_pm80x_chip->client;
		g_pm80x_chip->companion = chip->client;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm80x_init);

पूर्णांक pm80x_deinit(व्योम)
अणु
	/*
	 * workaround: clear the dependency between pm800 and pm805.
	 * would हटाओ it after HW chip fixes the issue.
	 */
	अगर (g_pm80x_chip->companion)
		g_pm80x_chip->companion = शून्य;
	अन्यथा
		g_pm80x_chip = शून्य;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm80x_deinit);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pm80x_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा pm80x_chip *chip = i2c_get_clientdata(client);

	अगर (chip && chip->wu_flag)
		अगर (device_may_wakeup(chip->dev))
			enable_irq_wake(chip->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक pm80x_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा pm80x_chip *chip = i2c_get_clientdata(client);

	अगर (chip && chip->wu_flag)
		अगर (device_may_wakeup(chip->dev))
			disable_irq_wake(chip->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

SIMPLE_DEV_PM_OPS(pm80x_pm_ops, pm80x_suspend, pm80x_resume);
EXPORT_SYMBOL_GPL(pm80x_pm_ops);

MODULE_DESCRIPTION("I2C Driver for Marvell 88PM80x");
MODULE_AUTHOR("Qiao Zhou <zhouqiao@marvell.com>");
MODULE_LICENSE("GPL");
