<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Acer Iconia Tab A500 Embedded Controller Driver
 *
 * Copyright 2020 GRATE-driver project
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>

#घोषणा A500_EC_I2C_ERR_TIMEOUT		500
#घोषणा A500_EC_POWER_CMD_TIMEOUT	1000

/*
 * Controller's firmware expects specअगरic command opcodes to be used क्रम the
 * corresponding रेजिस्टरs. Unsupported commands are skipped by the firmware.
 */
#घोषणा CMD_SHUTDOWN			0x0
#घोषणा CMD_WARM_REBOOT			0x0
#घोषणा CMD_COLD_REBOOT			0x1

क्रमागत अणु
	REG_CURRENT_NOW = 0x03,
	REG_SHUTDOWN = 0x52,
	REG_WARM_REBOOT = 0x54,
	REG_COLD_REBOOT = 0x55,
पूर्ण;

अटल काष्ठा i2c_client *a500_ec_client_pm_off;

अटल पूर्णांक a500_ec_पढ़ो(व्योम *context, स्थिर व्योम *reg_buf, माप_प्रकार reg_size,
			व्योम *val_buf, माप_प्रकार val_sizel)
अणु
	काष्ठा i2c_client *client = context;
	अचिन्हित पूर्णांक reg, retries = 5;
	u16 *ret_val = val_buf;
	s32 ret = 0;

	reg = *(u8 *)reg_buf;

	जबतक (retries-- > 0) अणु
		ret = i2c_smbus_पढ़ो_word_data(client, reg);
		अगर (ret >= 0)
			अवरोध;

		msleep(A500_EC_I2C_ERR_TIMEOUT);
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(&client->dev, "read 0x%x failed: %d\n", reg, ret);
		वापस ret;
	पूर्ण

	*ret_val = ret;

	अगर (reg == REG_CURRENT_NOW)
		fsleep(10000);

	वापस 0;
पूर्ण

अटल पूर्णांक a500_ec_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = context;
	अचिन्हित पूर्णांक reg, val, retries = 5;
	s32 ret = 0;

	reg = *(u8  *)(data + 0);
	val = *(u16 *)(data + 1);

	जबतक (retries-- > 0) अणु
		ret = i2c_smbus_ग_लिखो_word_data(client, reg, val);
		अगर (ret >= 0)
			अवरोध;

		msleep(A500_EC_I2C_ERR_TIMEOUT);
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(&client->dev, "write 0x%x failed: %d\n", reg, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config a500_ec_regmap_config = अणु
	.name = "KB930",
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = 0xff,
पूर्ण;

अटल स्थिर काष्ठा regmap_bus a500_ec_regmap_bus = अणु
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_NATIVE,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_LITTLE,
	.ग_लिखो = a500_ec_ग_लिखो,
	.पढ़ो = a500_ec_पढ़ो,
	.max_raw_पढ़ो = 2,
पूर्ण;

अटल व्योम a500_ec_घातeroff(व्योम)
अणु
	i2c_smbus_ग_लिखो_word_data(a500_ec_client_pm_off,
				  REG_SHUTDOWN, CMD_SHUTDOWN);

	mdelay(A500_EC_POWER_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक a500_ec_restart_notअगरy(काष्ठा notअगरier_block *this,
				  अचिन्हित दीर्घ reboot_mode, व्योम *data)
अणु
	अगर (reboot_mode == REBOOT_WARM)
		i2c_smbus_ग_लिखो_word_data(a500_ec_client_pm_off,
					  REG_WARM_REBOOT, CMD_WARM_REBOOT);
	अन्यथा
		i2c_smbus_ग_लिखो_word_data(a500_ec_client_pm_off,
					  REG_COLD_REBOOT, CMD_COLD_REBOOT);

	mdelay(A500_EC_POWER_CMD_TIMEOUT);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block a500_ec_restart_handler = अणु
	.notअगरier_call = a500_ec_restart_notअगरy,
	.priority = 200,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell a500_ec_cells[] = अणु
	अणु .name = "acer-a500-iconia-battery", पूर्ण,
	अणु .name = "acer-a500-iconia-leds", पूर्ण,
पूर्ण;

अटल पूर्णांक a500_ec_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा regmap *regmap;
	पूर्णांक err;

	regmap = devm_regmap_init(&client->dev, &a500_ec_regmap_bus,
				  client, &a500_ec_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	err = devm_mfd_add_devices(&client->dev, PLATFORM_DEVID_AUTO,
				   a500_ec_cells, ARRAY_SIZE(a500_ec_cells),
				   शून्य, 0, शून्य);
	अगर (err) अणु
		dev_err(&client->dev, "failed to add sub-devices: %d\n", err);
		वापस err;
	पूर्ण

	अगर (of_device_is_प्रणाली_घातer_controller(client->dev.of_node)) अणु
		a500_ec_client_pm_off = client;

		err = रेजिस्टर_restart_handler(&a500_ec_restart_handler);
		अगर (err)
			वापस err;

		अगर (!pm_घातer_off)
			pm_घातer_off = a500_ec_घातeroff;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक a500_ec_हटाओ(काष्ठा i2c_client *client)
अणु
	अगर (of_device_is_प्रणाली_घातer_controller(client->dev.of_node)) अणु
		अगर (pm_घातer_off == a500_ec_घातeroff)
			pm_घातer_off = शून्य;

		unरेजिस्टर_restart_handler(&a500_ec_restart_handler);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id a500_ec_match[] = अणु
	अणु .compatible = "acer,a500-iconia-ec" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, a500_ec_match);

अटल काष्ठा i2c_driver a500_ec_driver = अणु
	.driver = अणु
		.name = "acer-a500-embedded-controller",
		.of_match_table = a500_ec_match,
	पूर्ण,
	.probe_new = a500_ec_probe,
	.हटाओ = a500_ec_हटाओ,
पूर्ण;
module_i2c_driver(a500_ec_driver);

MODULE_DESCRIPTION("Acer Iconia Tab A500 Embedded Controller driver");
MODULE_AUTHOR("Dmitry Osipenko <digetx@gmail.com>");
MODULE_LICENSE("GPL");
