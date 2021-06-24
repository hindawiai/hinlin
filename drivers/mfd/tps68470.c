<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TPS68470 chip Parent driver
 *
 * Copyright (C) 2017 Intel Corporation
 *
 * Authors:
 *	Rajmohan Mani <rajmohan.mani@पूर्णांकel.com>
 *	Tianshu Qiu <tian.shu.qiu@पूर्णांकel.com>
 *	Jian Xu Zheng <jian.xu.zheng@पूर्णांकel.com>
 *	Yuning Pu <yuning.pu@पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/tps68470.h>
#समावेश <linux/regmap.h>

अटल स्थिर काष्ठा mfd_cell tps68470s[] = अणु
	अणु .name = "tps68470-gpio" पूर्ण,
	अणु .name = "tps68470_pmic_opregion" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tps68470_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = TPS68470_REG_MAX,
पूर्ण;

अटल पूर्णांक tps68470_chip_init(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	अचिन्हित पूर्णांक version;
	पूर्णांक ret;

	/* Force software reset */
	ret = regmap_ग_लिखो(regmap, TPS68470_REG_RESET, TPS68470_REG_RESET_MASK);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(regmap, TPS68470_REG_REVID, &version);
	अगर (ret) अणु
		dev_err(dev, "Failed to read revision register: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_info(dev, "TPS68470 REVID: 0x%x\n", version);

	वापस 0;
पूर्ण

अटल पूर्णांक tps68470_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	regmap = devm_regmap_init_i2c(client, &tps68470_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "devm_regmap_init_i2c Error %ld\n",
			PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	i2c_set_clientdata(client, regmap);

	ret = tps68470_chip_init(dev, regmap);
	अगर (ret < 0) अणु
		dev_err(dev, "TPS68470 Init Error %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE, tps68470s,
			      ARRAY_SIZE(tps68470s), शून्य, 0, शून्य);
	अगर (ret < 0) अणु
		dev_err(dev, "devm_mfd_add_devices failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id tps68470_acpi_ids[] = अणु
	अणु"INT3472"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा i2c_driver tps68470_driver = अणु
	.driver = अणु
		   .name = "tps68470",
		   .acpi_match_table = tps68470_acpi_ids,
	पूर्ण,
	.probe_new = tps68470_probe,
पूर्ण;
builtin_i2c_driver(tps68470_driver);
