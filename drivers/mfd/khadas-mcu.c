<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Khadas System control Microcontroller
 *
 * Copyright (C) 2020 BayLibre SAS
 *
 * Author(s): Neil Armstrong <narmstrong@baylibre.com>
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/khadas-mcu.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

अटल bool khadas_mcu_reg_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg >= KHADAS_MCU_USER_DATA_0_REG &&
	    reg < KHADAS_MCU_PWR_OFF_CMD_REG)
		वापस true;

	चयन (reg) अणु
	हाल KHADAS_MCU_PWR_OFF_CMD_REG:
	हाल KHADAS_MCU_PASSWD_START_REG:
	हाल KHADAS_MCU_CHECK_VEN_PASSWD_REG:
	हाल KHADAS_MCU_CHECK_USER_PASSWD_REG:
	हाल KHADAS_MCU_WOL_INIT_START_REG:
	हाल KHADAS_MCU_CMD_FAN_STATUS_CTRL_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool khadas_mcu_reg_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल KHADAS_MCU_PASSWD_VEN_0_REG:
	हाल KHADAS_MCU_PASSWD_VEN_1_REG:
	हाल KHADAS_MCU_PASSWD_VEN_2_REG:
	हाल KHADAS_MCU_PASSWD_VEN_3_REG:
	हाल KHADAS_MCU_PASSWD_VEN_4_REG:
	हाल KHADAS_MCU_PASSWD_VEN_5_REG:
	हाल KHADAS_MCU_MAC_0_REG:
	हाल KHADAS_MCU_MAC_1_REG:
	हाल KHADAS_MCU_MAC_2_REG:
	हाल KHADAS_MCU_MAC_3_REG:
	हाल KHADAS_MCU_MAC_4_REG:
	हाल KHADAS_MCU_MAC_5_REG:
	हाल KHADAS_MCU_USID_0_REG:
	हाल KHADAS_MCU_USID_1_REG:
	हाल KHADAS_MCU_USID_2_REG:
	हाल KHADAS_MCU_USID_3_REG:
	हाल KHADAS_MCU_USID_4_REG:
	हाल KHADAS_MCU_USID_5_REG:
	हाल KHADAS_MCU_VERSION_0_REG:
	हाल KHADAS_MCU_VERSION_1_REG:
	हाल KHADAS_MCU_DEVICE_NO_0_REG:
	हाल KHADAS_MCU_DEVICE_NO_1_REG:
	हाल KHADAS_MCU_FACTORY_TEST_REG:
	हाल KHADAS_MCU_SHUTDOWN_NORMAL_STATUS_REG:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config khadas_mcu_regmap_config = अणु
	.reg_bits	= 8,
	.reg_stride	= 1,
	.val_bits	= 8,
	.max_रेजिस्टर	= KHADAS_MCU_CMD_FAN_STATUS_CTRL_REG,
	.अस्थिर_reg	= khadas_mcu_reg_अस्थिर,
	.ग_लिखोable_reg	= khadas_mcu_reg_ग_लिखोable,
	.cache_type	= REGCACHE_RBTREE,
पूर्ण;

अटल काष्ठा mfd_cell khadas_mcu_fan_cells[] = अणु
	/* VIM1/2 Rev13+ and VIM3 only */
	अणु .name = "khadas-mcu-fan-ctrl", पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell khadas_mcu_cells[] = अणु
	अणु .name = "khadas-mcu-user-mem", पूर्ण,
पूर्ण;

अटल पूर्णांक khadas_mcu_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा khadas_mcu *ddata;
	पूर्णांक ret;

	ddata = devm_kzalloc(dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	i2c_set_clientdata(client, ddata);

	ddata->dev = dev;

	ddata->regmap = devm_regmap_init_i2c(client, &khadas_mcu_regmap_config);
	अगर (IS_ERR(ddata->regmap)) अणु
		ret = PTR_ERR(ddata->regmap);
		dev_err(dev, "Failed to allocate register map: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE,
				   khadas_mcu_cells,
				   ARRAY_SIZE(khadas_mcu_cells),
				   शून्य, 0, शून्य);
	अगर (ret)
		वापस ret;

	अगर (of_find_property(dev->of_node, "#cooling-cells", शून्य))
		वापस devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE,
					    khadas_mcu_fan_cells,
					    ARRAY_SIZE(khadas_mcu_fan_cells),
					    शून्य, 0, शून्य);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id khadas_mcu_of_match[] = अणु
	अणु .compatible = "khadas,mcu", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, khadas_mcu_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver khadas_mcu_driver = अणु
	.driver = अणु
		.name = "khadas-mcu-core",
		.of_match_table = of_match_ptr(khadas_mcu_of_match),
	पूर्ण,
	.probe = khadas_mcu_probe,
पूर्ण;
module_i2c_driver(khadas_mcu_driver);

MODULE_DESCRIPTION("Khadas MCU core driver");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_LICENSE("GPL v2");
