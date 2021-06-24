<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * The Netronix embedded controller is a microcontroller found in some
 * e-book पढ़ोers deचिन्हित by the original design manufacturer Netronix, Inc.
 * It contains RTC, battery monitoring, प्रणाली घातer management, and PWM
 * functionality.
 *
 * This driver implements रेजिस्टर access, version detection, and प्रणाली
 * घातer-off/reset.
 *
 * Copyright 2020 Jonathan Neuschथअfer <j.neuschaefer@gmx.net>
 */

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/ntxec.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा NTXEC_REG_VERSION	0x00
#घोषणा NTXEC_REG_POWEROFF	0x50
#घोषणा NTXEC_REG_POWERKEEP	0x70
#घोषणा NTXEC_REG_RESET		0x90

#घोषणा NTXEC_POWEROFF_VALUE	0x0100
#घोषणा NTXEC_POWERKEEP_VALUE	0x0800
#घोषणा NTXEC_RESET_VALUE	0xff00

अटल काष्ठा i2c_client *घातeroff_restart_client;

अटल व्योम ntxec_घातeroff(व्योम)
अणु
	पूर्णांक res;
	u8 buf[3] = अणु NTXEC_REG_POWEROFF पूर्ण;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = घातeroff_restart_client->addr,
			.flags = 0,
			.len = माप(buf),
			.buf = buf,
		पूर्ण,
	पूर्ण;

	put_unaligned_be16(NTXEC_POWEROFF_VALUE, buf + 1);

	res = i2c_transfer(घातeroff_restart_client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (res < 0)
		dev_warn(&घातeroff_restart_client->dev,
			 "Failed to power off (err = %d)\n", res);

	/*
	 * The समय from the रेजिस्टर ग_लिखो until the host CPU is घातered off
	 * has been observed to be about 2.5 to 3 seconds. Sleep दीर्घ enough to
	 * safely aव्योम वापसing from the घातeroff handler.
	 */
	msleep(5000);
पूर्ण

अटल पूर्णांक ntxec_restart(काष्ठा notअगरier_block *nb,
			 अचिन्हित दीर्घ action, व्योम *data)
अणु
	पूर्णांक res;
	u8 buf[3] = अणु NTXEC_REG_RESET पूर्ण;
	/*
	 * NOTE: The lower half of the reset value is not sent, because sending
	 * it causes an I2C error. (The reset handler in the करोwnstream driver
	 * करोes send the full two-byte value, but करोesn't check the result).
	 */
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = घातeroff_restart_client->addr,
			.flags = 0,
			.len = माप(buf) - 1,
			.buf = buf,
		पूर्ण,
	पूर्ण;

	put_unaligned_be16(NTXEC_RESET_VALUE, buf + 1);

	res = i2c_transfer(घातeroff_restart_client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (res < 0)
		dev_warn(&घातeroff_restart_client->dev,
			 "Failed to restart (err = %d)\n", res);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block ntxec_restart_handler = अणु
	.notअगरier_call = ntxec_restart,
	.priority = 128,
पूर्ण;

अटल पूर्णांक regmap_ignore_ग_लिखो(व्योम *context,
			       अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)

अणु
	काष्ठा regmap *regmap = context;

	regmap_ग_लिखो(regmap, reg, val);

	वापस 0;
पूर्ण

अटल पूर्णांक regmap_wrap_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
			    अचिन्हित पूर्णांक *val)
अणु
	काष्ठा regmap *regmap = context;

	वापस regmap_पढ़ो(regmap, reg, val);
पूर्ण

/*
 * Some firmware versions करो not ack written data, add a wrapper. It
 * is used to stack another regmap on top.
 */
अटल स्थिर काष्ठा regmap_config regmap_config_noack = अणु
	.name = "ntxec_noack",
	.reg_bits = 8,
	.val_bits = 16,
	.cache_type = REGCACHE_NONE,
	.reg_ग_लिखो = regmap_ignore_ग_लिखो,
	.reg_पढ़ो = regmap_wrap_पढ़ो
पूर्ण;

अटल स्थिर काष्ठा regmap_config regmap_config = अणु
	.name = "ntxec",
	.reg_bits = 8,
	.val_bits = 16,
	.cache_type = REGCACHE_NONE,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell ntxec_subdev[] = अणु
	अणु .name = "ntxec-rtc" पूर्ण,
	अणु .name = "ntxec-pwm" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell ntxec_subdev_pwm[] = अणु
	अणु .name = "ntxec-pwm" पूर्ण,
पूर्ण;

अटल पूर्णांक ntxec_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ntxec *ec;
	अचिन्हित पूर्णांक version;
	पूर्णांक res;
	स्थिर काष्ठा mfd_cell *subdevs;
	माप_प्रकार n_subdevs;

	ec = devm_kदो_स्मृति(&client->dev, माप(*ec), GFP_KERNEL);
	अगर (!ec)
		वापस -ENOMEM;

	ec->dev = &client->dev;

	ec->regmap = devm_regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(ec->regmap)) अणु
		dev_err(ec->dev, "Failed to set up regmap for device\n");
		वापस PTR_ERR(ec->regmap);
	पूर्ण

	/* Determine the firmware version */
	res = regmap_पढ़ो(ec->regmap, NTXEC_REG_VERSION, &version);
	अगर (res < 0) अणु
		dev_err(ec->dev, "Failed to read firmware version number\n");
		वापस res;
	पूर्ण

	/* Bail out अगर we encounter an unknown firmware version */
	चयन (version) अणु
	हाल NTXEC_VERSION_KOBO_AURA:
		subdevs = ntxec_subdev;
		n_subdevs = ARRAY_SIZE(ntxec_subdev);
		अवरोध;
	हाल NTXEC_VERSION_TOLINO_SHINE2:
		subdevs = ntxec_subdev_pwm;
		n_subdevs = ARRAY_SIZE(ntxec_subdev_pwm);
		/* Another regmap stacked on top of the other */
		ec->regmap = devm_regmap_init(ec->dev, शून्य,
					      ec->regmap,
					      &regmap_config_noack);
		अगर (IS_ERR(ec->regmap))
			वापस PTR_ERR(ec->regmap);
		अवरोध;
	शेष:
		dev_err(ec->dev,
			"Netronix embedded controller version %04x is not supported.\n",
			version);
		वापस -ENODEV;
	पूर्ण

	dev_info(ec->dev,
		 "Netronix embedded controller version %04x detected.\n", version);

	अगर (of_device_is_प्रणाली_घातer_controller(ec->dev->of_node)) अणु
		/*
		 * Set the 'powerkeep' bit. This is necessary on some boards
		 * in order to keep the प्रणाली running.
		 */
		res = regmap_ग_लिखो(ec->regmap, NTXEC_REG_POWERKEEP,
				   NTXEC_POWERKEEP_VALUE);
		अगर (res < 0)
			वापस res;

		अगर (घातeroff_restart_client)
			/*
			 * Another instance of the driver alपढ़ोy took
			 * घातeroff/restart duties.
			 */
			dev_err(ec->dev, "poweroff_restart_client already assigned\n");
		अन्यथा
			घातeroff_restart_client = client;

		अगर (pm_घातer_off)
			/* Another driver alपढ़ोy रेजिस्टरed a घातeroff handler. */
			dev_err(ec->dev, "pm_power_off already assigned\n");
		अन्यथा
			pm_घातer_off = ntxec_घातeroff;

		res = रेजिस्टर_restart_handler(&ntxec_restart_handler);
		अगर (res)
			dev_err(ec->dev,
				"Failed to register restart handler: %d\n", res);
	पूर्ण

	i2c_set_clientdata(client, ec);

	res = devm_mfd_add_devices(ec->dev, PLATFORM_DEVID_NONE,
				   subdevs, n_subdevs, शून्य, 0, शून्य);
	अगर (res)
		dev_err(ec->dev, "Failed to add subdevices: %d\n", res);

	वापस res;
पूर्ण

अटल पूर्णांक ntxec_हटाओ(काष्ठा i2c_client *client)
अणु
	अगर (client == घातeroff_restart_client) अणु
		घातeroff_restart_client = शून्य;
		pm_घातer_off = शून्य;
		unरेजिस्टर_restart_handler(&ntxec_restart_handler);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_ntxec_match_table[] = अणु
	अणु .compatible = "netronix,ntxec", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_ntxec_match_table);

अटल काष्ठा i2c_driver ntxec_driver = अणु
	.driver = अणु
		.name = "ntxec",
		.of_match_table = of_ntxec_match_table,
	पूर्ण,
	.probe_new = ntxec_probe,
	.हटाओ = ntxec_हटाओ,
पूर्ण;
module_i2c_driver(ntxec_driver);

MODULE_AUTHOR("Jonathan Neuschथअfer <j.neuschaefer@gmx.net>");
MODULE_DESCRIPTION("Core driver for Netronix EC");
MODULE_LICENSE("GPL");
