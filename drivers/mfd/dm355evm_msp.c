<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dm355evm_msp.c - driver क्रम MSP430 firmware on DM355EVM board
 *
 * Copyright (C) 2008 David Brownell
 */

#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/leds.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/dm355evm_msp.h>


/*
 * The DM355 is a DaVinci chip with video support but no C64+ DSP.  Its
 * EVM board has an MSP430 programmed with firmware क्रम various board
 * support functions.  This driver exposes some of them directly, and
 * supports other drivers (e.g. RTC, input) क्रम more complex access.
 *
 * Because this firmware is entirely board-specअगरic, this file embeds
 * knowledge that would be passed as platक्रमm_data in a generic driver.
 *
 * This driver was tested with firmware revision A4.
 */

#अगर IS_ENABLED(CONFIG_INPUT_DM355EVM)
#घोषणा msp_has_keyboard()	true
#अन्यथा
#घोषणा msp_has_keyboard()	false
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_LEDS_GPIO)
#घोषणा msp_has_leds()		true
#अन्यथा
#घोषणा msp_has_leds()		false
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_RTC_DRV_DM355EVM)
#घोषणा msp_has_rtc()		true
#अन्यथा
#घोषणा msp_has_rtc()		false
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_VIDEO_TVP514X)
#घोषणा msp_has_tvp()		true
#अन्यथा
#घोषणा msp_has_tvp()		false
#पूर्ण_अगर


/*----------------------------------------------------------------------*/

/* REVISIT क्रम paranoia's sake, retry पढ़ोs/ग_लिखोs on error */

अटल काष्ठा i2c_client *msp430;

/**
 * dm355evm_msp_ग_लिखो - Writes a रेजिस्टर in dm355evm_msp
 * @value: the value to be written
 * @reg: रेजिस्टर address
 *
 * Returns result of operation - 0 is success, अन्यथा negative त्रुटि_सं
 */
पूर्णांक dm355evm_msp_ग_लिखो(u8 value, u8 reg)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(msp430, reg, value);
पूर्ण
EXPORT_SYMBOL(dm355evm_msp_ग_लिखो);

/**
 * dm355evm_msp_पढ़ो - Reads a रेजिस्टर from dm355evm_msp
 * @reg: रेजिस्टर address
 *
 * Returns result of operation - value, or negative त्रुटि_सं
 */
पूर्णांक dm355evm_msp_पढ़ो(u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(msp430, reg);
पूर्ण
EXPORT_SYMBOL(dm355evm_msp_पढ़ो);

/*----------------------------------------------------------------------*/

/*
 * Many of the msp430 pins are just used as fixed-direction GPIOs.
 * We could export a few more of them this way, अगर we wanted.
 */
#घोषणा MSP_GPIO(bit, reg)	((DM355EVM_MSP_ ## reg) << 3 | (bit))

अटल स्थिर u8 msp_gpios[] = अणु
	/* eight leds */
	MSP_GPIO(0, LED), MSP_GPIO(1, LED),
	MSP_GPIO(2, LED), MSP_GPIO(3, LED),
	MSP_GPIO(4, LED), MSP_GPIO(5, LED),
	MSP_GPIO(6, LED), MSP_GPIO(7, LED),
	/* SW6 and the NTSC/nPAL jumper */
	MSP_GPIO(0, SWITCH1), MSP_GPIO(1, SWITCH1),
	MSP_GPIO(2, SWITCH1), MSP_GPIO(3, SWITCH1),
	MSP_GPIO(4, SWITCH1),
	/* चयनes on MMC/SD sockets */
	/*
	 * Note: EVMDM355_ECP_VA4.pdf suggests that Bit 2 and 4 should be
	 * checked क्रम card detection. However on the EVM bit 1 and 3 gives
	 * this status, क्रम 0 and 1 instance respectively. The pdf also
	 * suggests that Bit 1 and 3 should be checked क्रम ग_लिखो protection.
	 * However on the EVM bit 2 and 4 gives this status,क्रम 0 and 1
	 * instance respectively.
	 */
	MSP_GPIO(2, SDMMC), MSP_GPIO(1, SDMMC),	/* mmc0 WP, nCD */
	MSP_GPIO(4, SDMMC), MSP_GPIO(3, SDMMC),	/* mmc1 WP, nCD */
पूर्ण;

अटल काष्ठा gpio_led evm_leds[] = अणु
	अणु .name = "dm355evm::ds14",
	  .शेष_trigger = "heartbeat", पूर्ण,
	अणु .name = "dm355evm::ds15",
	  .शेष_trigger = "mmc0", पूर्ण,
	अणु .name = "dm355evm::ds16",
	  /* could also be a CE-ATA drive */
	  .शेष_trigger = "mmc1", पूर्ण,
	अणु .name = "dm355evm::ds17",
	  .शेष_trigger = "nand-disk", पूर्ण,
	अणु .name = "dm355evm::ds18", पूर्ण,
	अणु .name = "dm355evm::ds19", पूर्ण,
	अणु .name = "dm355evm::ds20", पूर्ण,
	अणु .name = "dm355evm::ds21", पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data evm_led_data = अणु
	.num_leds	= ARRAY_SIZE(evm_leds),
	.leds		= evm_leds,
पूर्ण;

अटल काष्ठा gpiod_lookup_table evm_leds_gpio_table = अणु
	.dev_id = "leds-gpio",
	.table = अणु
		/*
		 * These GPIOs are on the dm355evm_msp
		 * GPIO chip at index 0..7
		 */
		GPIO_LOOKUP_IDX("dm355evm_msp", 0, शून्य,
				0, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX("dm355evm_msp", 1, शून्य,
				1, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX("dm355evm_msp", 2, शून्य,
				2, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX("dm355evm_msp", 3, शून्य,
				3, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX("dm355evm_msp", 4, शून्य,
				4, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX("dm355evm_msp", 5, शून्य,
				5, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX("dm355evm_msp", 6, शून्य,
				6, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX("dm355evm_msp", 7, शून्य,
				7, GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा MSP_GPIO_REG(offset)	(msp_gpios[(offset)] >> 3)
#घोषणा MSP_GPIO_MASK(offset)	BIT(msp_gpios[(offset)] & 0x07)

अटल पूर्णांक msp_gpio_in(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	चयन (MSP_GPIO_REG(offset)) अणु
	हाल DM355EVM_MSP_SWITCH1:
	हाल DM355EVM_MSP_SWITCH2:
	हाल DM355EVM_MSP_SDMMC:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल u8 msp_led_cache;

अटल पूर्णांक msp_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	पूर्णांक reg, status;

	reg = MSP_GPIO_REG(offset);
	status = dm355evm_msp_पढ़ो(reg);
	अगर (status < 0)
		वापस status;
	अगर (reg == DM355EVM_MSP_LED)
		msp_led_cache = status;
	वापस !!(status & MSP_GPIO_MASK(offset));
पूर्ण

अटल पूर्णांक msp_gpio_out(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	पूर्णांक mask, bits;

	/* NOTE:  there are some other संकेतs that could be
	 * packaged as output GPIOs, but they aren't as useful
	 * as the LEDs ... so क्रम now we करोn't.
	 */
	अगर (MSP_GPIO_REG(offset) != DM355EVM_MSP_LED)
		वापस -EINVAL;

	mask = MSP_GPIO_MASK(offset);
	bits = msp_led_cache;

	bits &= ~mask;
	अगर (value)
		bits |= mask;
	msp_led_cache = bits;

	वापस dm355evm_msp_ग_लिखो(bits, DM355EVM_MSP_LED);
पूर्ण

अटल व्योम msp_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	msp_gpio_out(chip, offset, value);
पूर्ण

अटल काष्ठा gpio_chip dm355evm_msp_gpio = अणु
	.label			= "dm355evm_msp",
	.owner			= THIS_MODULE,
	.direction_input	= msp_gpio_in,
	.get			= msp_gpio_get,
	.direction_output	= msp_gpio_out,
	.set			= msp_gpio_set,
	.base			= -EINVAL,		/* dynamic assignment */
	.ngpio			= ARRAY_SIZE(msp_gpios),
	.can_sleep		= true,
पूर्ण;

/*----------------------------------------------------------------------*/

अटल काष्ठा device *add_child(काष्ठा i2c_client *client, स्थिर अक्षर *name,
		व्योम *pdata, अचिन्हित pdata_len,
		bool can_wakeup, पूर्णांक irq)
अणु
	काष्ठा platक्रमm_device	*pdev;
	पूर्णांक			status;

	pdev = platक्रमm_device_alloc(name, -1);
	अगर (!pdev)
		वापस ERR_PTR(-ENOMEM);

	device_init_wakeup(&pdev->dev, can_wakeup);
	pdev->dev.parent = &client->dev;

	अगर (pdata) अणु
		status = platक्रमm_device_add_data(pdev, pdata, pdata_len);
		अगर (status < 0) अणु
			dev_dbg(&pdev->dev, "can't add platform_data\n");
			जाओ put_device;
		पूर्ण
	पूर्ण

	अगर (irq) अणु
		काष्ठा resource r = अणु
			.start = irq,
			.flags = IORESOURCE_IRQ,
		पूर्ण;

		status = platक्रमm_device_add_resources(pdev, &r, 1);
		अगर (status < 0) अणु
			dev_dbg(&pdev->dev, "can't add irq\n");
			जाओ put_device;
		पूर्ण
	पूर्ण

	status = platक्रमm_device_add(pdev);
	अगर (status)
		जाओ put_device;

	वापस &pdev->dev;

put_device:
	platक्रमm_device_put(pdev);
	dev_err(&client->dev, "failed to add device %s\n", name);
	वापस ERR_PTR(status);
पूर्ण

अटल पूर्णांक add_children(काष्ठा i2c_client *client)
अणु
	अटल स्थिर काष्ठा अणु
		पूर्णांक offset;
		अक्षर *label;
	पूर्ण config_inमाला_दो[] = अणु
		/* 8 == right after the LEDs */
		अणु 8 + 0, "sw6_1", पूर्ण,
		अणु 8 + 1, "sw6_2", पूर्ण,
		अणु 8 + 2, "sw6_3", पूर्ण,
		अणु 8 + 3, "sw6_4", पूर्ण,
		अणु 8 + 4, "NTSC/nPAL", पूर्ण,
	पूर्ण;

	काष्ठा device	*child;
	पूर्णांक		status;
	पूर्णांक		i;

	/* GPIO-ish stuff */
	dm355evm_msp_gpio.parent = &client->dev;
	status = gpiochip_add_data(&dm355evm_msp_gpio, शून्य);
	अगर (status < 0)
		वापस status;

	/* LED output */
	अगर (msp_has_leds()) अणु
		gpiod_add_lookup_table(&evm_leds_gpio_table);
		/* NOTE:  these are the only fully programmable LEDs
		 * on the board, since GPIO-61/ds22 (and many संकेतs
		 * going to DC7) must be used क्रम AEMIF address lines
		 * unless the top 1 GB of न_अंकD is unused...
		 */
		child = add_child(client, "leds-gpio",
				&evm_led_data, माप(evm_led_data),
				false, 0);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	/* configuration inमाला_दो */
	क्रम (i = 0; i < ARRAY_SIZE(config_inमाला_दो); i++) अणु
		पूर्णांक gpio = dm355evm_msp_gpio.base + config_inमाला_दो[i].offset;

		gpio_request_one(gpio, GPIOF_IN, config_inमाला_दो[i].label);

		/* make it easy क्रम userspace to see these */
		gpio_export(gpio, false);
	पूर्ण

	/* MMC/SD inमाला_दो -- right after the last config input */
	अगर (dev_get_platdata(&client->dev)) अणु
		व्योम (*mmcsd_setup)(अचिन्हित) = dev_get_platdata(&client->dev);

		mmcsd_setup(dm355evm_msp_gpio.base + 8 + 5);
	पूर्ण

	/* RTC is a 32 bit counter, no alarm */
	अगर (msp_has_rtc()) अणु
		child = add_child(client, "rtc-dm355evm",
				शून्य, 0, false, 0);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	/* input from buttons and IR remote (uses the IRQ) */
	अगर (msp_has_keyboard()) अणु
		child = add_child(client, "dm355evm_keys",
				शून्य, 0, true, client->irq);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);
	पूर्ण

	वापस 0;
पूर्ण

/*----------------------------------------------------------------------*/

अटल व्योम dm355evm_command(अचिन्हित command)
अणु
	पूर्णांक status;

	status = dm355evm_msp_ग_लिखो(command, DM355EVM_MSP_COMMAND);
	अगर (status < 0)
		dev_err(&msp430->dev, "command %d failure %d\n",
				command, status);
पूर्ण

अटल व्योम dm355evm_घातer_off(व्योम)
अणु
	dm355evm_command(MSP_COMMAND_POWEROFF);
पूर्ण

अटल पूर्णांक dm355evm_msp_हटाओ(काष्ठा i2c_client *client)
अणु
	pm_घातer_off = शून्य;
	msp430 = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक
dm355evm_msp_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक		status;
	स्थिर अक्षर	*video = msp_has_tvp() ? "TVP5146" : "imager";

	अगर (msp430)
		वापस -EBUSY;
	msp430 = client;

	/* display revision status; द्विगुनs as sanity check */
	status = dm355evm_msp_पढ़ो(DM355EVM_MSP_FIRMREV);
	अगर (status < 0)
		जाओ fail;
	dev_info(&client->dev, "firmware v.%02X, %s as video-in\n",
			status, video);

	/* mux video input:  either tvp5146 or some बाह्यal imager */
	status = dm355evm_msp_ग_लिखो(msp_has_tvp() ? 0 : MSP_VIDEO_IMAGER,
			DM355EVM_MSP_VIDEO_IN);
	अगर (status < 0)
		dev_warn(&client->dev, "error %d muxing %s as video-in\n",
			status, video);

	/* init LED cache, and turn off the LEDs */
	msp_led_cache = 0xff;
	dm355evm_msp_ग_लिखो(msp_led_cache, DM355EVM_MSP_LED);

	/* export capabilities we support */
	status = add_children(client);
	अगर (status < 0)
		जाओ fail;

	/* PM hookup */
	pm_घातer_off = dm355evm_घातer_off;

	वापस 0;

fail:
	/* FIXME हटाओ children ... */
	dm355evm_msp_हटाओ(client);
	वापस status;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id dm355evm_msp_ids[] = अणु
	अणु "dm355evm_msp", 0 पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, dm355evm_msp_ids);

अटल काष्ठा i2c_driver dm355evm_msp_driver = अणु
	.driver.name	= "dm355evm_msp",
	.id_table	= dm355evm_msp_ids,
	.probe		= dm355evm_msp_probe,
	.हटाओ		= dm355evm_msp_हटाओ,
पूर्ण;

अटल पूर्णांक __init dm355evm_msp_init(व्योम)
अणु
	वापस i2c_add_driver(&dm355evm_msp_driver);
पूर्ण
subsys_initcall(dm355evm_msp_init);

अटल व्योम __निकास dm355evm_msp_निकास(व्योम)
अणु
	i2c_del_driver(&dm355evm_msp_driver);
पूर्ण
module_निकास(dm355evm_msp_निकास);

MODULE_DESCRIPTION("Interface to MSP430 firmware on DM355EVM");
MODULE_LICENSE("GPL");
