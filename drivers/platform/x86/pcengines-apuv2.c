<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 * PC-Engines APUv2/APUv3 board platक्रमm driver
 * क्रम GPIO buttons and LEDs
 *
 * Copyright (C) 2018 metux IT consult
 * Author: Enrico Weigelt <info@metux.net>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/dmi.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_data/gpio/gpio-amd-fch.h>

/*
 * NOTE: this driver only supports APUv2/3 - not APUv1, as this one
 * has completely dअगरferent रेजिस्टर layouts.
 */

/* Register mappings */
#घोषणा APU2_GPIO_REG_LED1		AMD_FCH_GPIO_REG_GPIO57
#घोषणा APU2_GPIO_REG_LED2		AMD_FCH_GPIO_REG_GPIO58
#घोषणा APU2_GPIO_REG_LED3		AMD_FCH_GPIO_REG_GPIO59_DEVSLP1
#घोषणा APU2_GPIO_REG_MODESW		AMD_FCH_GPIO_REG_GPIO32_GE1
#घोषणा APU2_GPIO_REG_SIMSWAP		AMD_FCH_GPIO_REG_GPIO33_GE2
#घोषणा APU2_GPIO_REG_MPCIE2		AMD_FCH_GPIO_REG_GPIO55_DEVSLP0
#घोषणा APU2_GPIO_REG_MPCIE3		AMD_FCH_GPIO_REG_GPIO51

/* Order in which the GPIO lines are defined in the रेजिस्टर list */
#घोषणा APU2_GPIO_LINE_LED1		0
#घोषणा APU2_GPIO_LINE_LED2		1
#घोषणा APU2_GPIO_LINE_LED3		2
#घोषणा APU2_GPIO_LINE_MODESW		3
#घोषणा APU2_GPIO_LINE_SIMSWAP		4
#घोषणा APU2_GPIO_LINE_MPCIE2		5
#घोषणा APU2_GPIO_LINE_MPCIE3		6

/* GPIO device */

अटल पूर्णांक apu2_gpio_regs[] = अणु
	[APU2_GPIO_LINE_LED1]		= APU2_GPIO_REG_LED1,
	[APU2_GPIO_LINE_LED2]		= APU2_GPIO_REG_LED2,
	[APU2_GPIO_LINE_LED3]		= APU2_GPIO_REG_LED3,
	[APU2_GPIO_LINE_MODESW]		= APU2_GPIO_REG_MODESW,
	[APU2_GPIO_LINE_SIMSWAP]	= APU2_GPIO_REG_SIMSWAP,
	[APU2_GPIO_LINE_MPCIE2]		= APU2_GPIO_REG_MPCIE2,
	[APU2_GPIO_LINE_MPCIE3]		= APU2_GPIO_REG_MPCIE3,
पूर्ण;

अटल स्थिर अक्षर * स्थिर apu2_gpio_names[] = अणु
	[APU2_GPIO_LINE_LED1]		= "front-led1",
	[APU2_GPIO_LINE_LED2]		= "front-led2",
	[APU2_GPIO_LINE_LED3]		= "front-led3",
	[APU2_GPIO_LINE_MODESW]		= "front-button",
	[APU2_GPIO_LINE_SIMSWAP]	= "simswap",
	[APU2_GPIO_LINE_MPCIE2]		= "mpcie2_reset",
	[APU2_GPIO_LINE_MPCIE3]		= "mpcie3_reset",
पूर्ण;

अटल स्थिर काष्ठा amd_fch_gpio_pdata board_apu2 = अणु
	.gpio_num	= ARRAY_SIZE(apu2_gpio_regs),
	.gpio_reg	= apu2_gpio_regs,
	.gpio_names	= apu2_gpio_names,
पूर्ण;

/* GPIO LEDs device */

अटल स्थिर काष्ठा gpio_led apu2_leds[] = अणु
	अणु .name = "apu:green:1" पूर्ण,
	अणु .name = "apu:green:2" पूर्ण,
	अणु .name = "apu:green:3" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_led_platक्रमm_data apu2_leds_pdata = अणु
	.num_leds	= ARRAY_SIZE(apu2_leds),
	.leds		= apu2_leds,
पूर्ण;

अटल काष्ठा gpiod_lookup_table gpios_led_table = अणु
	.dev_id = "leds-gpio",
	.table = अणु
		GPIO_LOOKUP_IDX(AMD_FCH_GPIO_DRIVER_NAME, APU2_GPIO_LINE_LED1,
				शून्य, 0, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX(AMD_FCH_GPIO_DRIVER_NAME, APU2_GPIO_LINE_LED2,
				शून्य, 1, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX(AMD_FCH_GPIO_DRIVER_NAME, APU2_GPIO_LINE_LED3,
				शून्य, 2, GPIO_ACTIVE_LOW),
	पूर्ण
पूर्ण;

/* GPIO keyboard device */

अटल काष्ठा gpio_keys_button apu2_keys_buttons[] = अणु
	अणु
		.code			= KEY_RESTART,
		.active_low		= 1,
		.desc			= "front button",
		.type			= EV_KEY,
		.debounce_पूर्णांकerval	= 10,
		.value			= 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_platक्रमm_data apu2_keys_pdata = अणु
	.buttons	= apu2_keys_buttons,
	.nbuttons	= ARRAY_SIZE(apu2_keys_buttons),
	.poll_पूर्णांकerval	= 100,
	.rep		= 0,
	.name		= "apu2-keys",
पूर्ण;

अटल काष्ठा gpiod_lookup_table gpios_key_table = अणु
	.dev_id = "gpio-keys-polled",
	.table = अणु
		GPIO_LOOKUP_IDX(AMD_FCH_GPIO_DRIVER_NAME, APU2_GPIO_LINE_MODESW,
				शून्य, 0, GPIO_ACTIVE_LOW),
	पूर्ण
पूर्ण;

/* Board setup */

/* Note: matching works on string prefix, so "apu2" must come beक्रमe "apu" */
अटल स्थिर काष्ठा dmi_प्रणाली_id apu_gpio_dmi_table[] __initस्थिर = अणु

	/* APU2 w/ legacy BIOS < 4.0.8 */
	अणु
		.ident		= "apu2",
		.matches	= अणु
			DMI_MATCH(DMI_SYS_VENDOR, "PC Engines"),
			DMI_MATCH(DMI_BOARD_NAME, "APU2")
		पूर्ण,
		.driver_data	= (व्योम *)&board_apu2,
	पूर्ण,
	/* APU2 w/ legacy BIOS >= 4.0.8 */
	अणु
		.ident		= "apu2",
		.matches	= अणु
			DMI_MATCH(DMI_SYS_VENDOR, "PC Engines"),
			DMI_MATCH(DMI_BOARD_NAME, "apu2")
		पूर्ण,
		.driver_data	= (व्योम *)&board_apu2,
	पूर्ण,
	/* APU2 w/ मुख्यline BIOS */
	अणु
		.ident		= "apu2",
		.matches	= अणु
			DMI_MATCH(DMI_SYS_VENDOR, "PC Engines"),
			DMI_MATCH(DMI_BOARD_NAME, "PC Engines apu2")
		पूर्ण,
		.driver_data	= (व्योम *)&board_apu2,
	पूर्ण,

	/* APU3 w/ legacy BIOS < 4.0.8 */
	अणु
		.ident		= "apu3",
		.matches	= अणु
			DMI_MATCH(DMI_SYS_VENDOR, "PC Engines"),
			DMI_MATCH(DMI_BOARD_NAME, "APU3")
		पूर्ण,
		.driver_data = (व्योम *)&board_apu2,
	पूर्ण,
	/* APU3 w/ legacy BIOS >= 4.0.8 */
	अणु
		.ident       = "apu3",
		.matches     = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "PC Engines"),
			DMI_MATCH(DMI_BOARD_NAME, "apu3")
		पूर्ण,
		.driver_data = (व्योम *)&board_apu2,
	पूर्ण,
	/* APU3 w/ मुख्यline BIOS */
	अणु
		.ident       = "apu3",
		.matches     = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "PC Engines"),
			DMI_MATCH(DMI_BOARD_NAME, "PC Engines apu3")
		पूर्ण,
		.driver_data = (व्योम *)&board_apu2,
	पूर्ण,
	/* APU4 w/ legacy BIOS < 4.0.8 */
	अणु
		.ident        = "apu4",
		.matches    = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "PC Engines"),
			DMI_MATCH(DMI_BOARD_NAME, "APU4")
		पूर्ण,
		.driver_data = (व्योम *)&board_apu2,
	पूर्ण,
	/* APU4 w/ legacy BIOS >= 4.0.8 */
	अणु
		.ident       = "apu4",
		.matches     = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "PC Engines"),
			DMI_MATCH(DMI_BOARD_NAME, "apu4")
		पूर्ण,
		.driver_data = (व्योम *)&board_apu2,
	पूर्ण,
	/* APU4 w/ मुख्यline BIOS */
	अणु
		.ident       = "apu4",
		.matches     = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "PC Engines"),
			DMI_MATCH(DMI_BOARD_NAME, "PC Engines apu4")
		पूर्ण,
		.driver_data = (व्योम *)&board_apu2,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device *apu_gpio_pdev;
अटल काष्ठा platक्रमm_device *apu_leds_pdev;
अटल काष्ठा platक्रमm_device *apu_keys_pdev;

अटल काष्ठा platक्रमm_device * __init apu_create_pdev(
	स्थिर अक्षर *name,
	स्थिर व्योम *pdata,
	माप_प्रकार sz)
अणु
	काष्ठा platक्रमm_device *pdev;

	pdev = platक्रमm_device_रेजिस्टर_resndata(शून्य,
		name,
		PLATFORM_DEVID_NONE,
		शून्य,
		0,
		pdata,
		sz);

	अगर (IS_ERR(pdev))
		pr_err("failed registering %s: %ld\n", name, PTR_ERR(pdev));

	वापस pdev;
पूर्ण

अटल पूर्णांक __init apu_board_init(व्योम)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *id;

	id = dmi_first_match(apu_gpio_dmi_table);
	अगर (!id) अणु
		pr_err("failed to detect APU board via DMI\n");
		वापस -ENODEV;
	पूर्ण

	gpiod_add_lookup_table(&gpios_led_table);
	gpiod_add_lookup_table(&gpios_key_table);

	apu_gpio_pdev = apu_create_pdev(
		AMD_FCH_GPIO_DRIVER_NAME,
		id->driver_data,
		माप(काष्ठा amd_fch_gpio_pdata));

	apu_leds_pdev = apu_create_pdev(
		"leds-gpio",
		&apu2_leds_pdata,
		माप(apu2_leds_pdata));

	apu_keys_pdev = apu_create_pdev(
		"gpio-keys-polled",
		&apu2_keys_pdata,
		माप(apu2_keys_pdata));

	वापस 0;
पूर्ण

अटल व्योम __निकास apu_board_निकास(व्योम)
अणु
	gpiod_हटाओ_lookup_table(&gpios_led_table);
	gpiod_हटाओ_lookup_table(&gpios_key_table);

	platक्रमm_device_unरेजिस्टर(apu_keys_pdev);
	platक्रमm_device_unरेजिस्टर(apu_leds_pdev);
	platक्रमm_device_unरेजिस्टर(apu_gpio_pdev);
पूर्ण

module_init(apu_board_init);
module_निकास(apu_board_निकास);

MODULE_AUTHOR("Enrico Weigelt, metux IT consult <info@metux.net>");
MODULE_DESCRIPTION("PC Engines APUv2/APUv3 board GPIO/LEDs/keys driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(dmi, apu_gpio_dmi_table);
MODULE_ALIAS("platform:pcengines-apuv2");
MODULE_SOFTDEP("pre: platform:" AMD_FCH_GPIO_DRIVER_NAME " platform:leds-gpio platform:gpio_keys_polled");
