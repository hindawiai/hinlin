<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम controlling LEDs क्रम cameras connected to the Intel atomisp2
 * The मुख्य purpose of this driver is to turn off LEDs which are on at boot.
 *
 * Copyright (C) 2020 Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/dmi.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>

/* This must be leds-gpio as the leds-gpio driver binds to the name */
#घोषणा DEV_NAME		"leds-gpio"

अटल स्थिर काष्ठा gpio_led atomisp2_leds[] = अणु
	अणु
		.name = "atomisp2::camera",
		.शेष_state  = LEDS_GPIO_DEFSTATE_OFF,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_led_platक्रमm_data atomisp2_leds_pdata = अणु
	.num_leds	= ARRAY_SIZE(atomisp2_leds),
	.leds		= atomisp2_leds,
पूर्ण;

अटल काष्ठा gpiod_lookup_table asus_t100ta_lookup = अणु
	.dev_id = DEV_NAME,
	.table = अणु
		GPIO_LOOKUP_IDX("INT33FC:02", 8, शून्य, 0, GPIO_ACTIVE_HIGH),
		अणु पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा gpiod_lookup_table asus_t100chi_lookup = अणु
	.dev_id = DEV_NAME,
	.table = अणु
		GPIO_LOOKUP_IDX("INT33FC:01", 24, शून्य, 0, GPIO_ACTIVE_HIGH),
		अणु पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id atomisp2_led_प्रणालीs[] __initस्थिर = अणु
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "T100TA"),
		पूर्ण,
		.driver_data = &asus_t100ta_lookup,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "T200TA"),
		पूर्ण,
		.driver_data = &asus_t100ta_lookup,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "T100CHI"),
		पूर्ण,
		.driver_data = &asus_t100chi_lookup,
	पूर्ण,
	अणुपूर्ण /* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(dmi, atomisp2_led_प्रणालीs);

अटल काष्ठा gpiod_lookup_table *gpio_lookup;
अटल काष्ठा platक्रमm_device *pdev;

अटल पूर्णांक __init atomisp2_led_init(व्योम)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *प्रणाली;

	प्रणाली = dmi_first_match(atomisp2_led_प्रणालीs);
	अगर (!प्रणाली)
		वापस -ENODEV;

	gpio_lookup = प्रणाली->driver_data;
	gpiod_add_lookup_table(gpio_lookup);

	pdev = platक्रमm_device_रेजिस्टर_resndata(शून्य,
						 DEV_NAME, PLATFORM_DEVID_NONE,
						 शून्य, 0, &atomisp2_leds_pdata,
						 माप(atomisp2_leds_pdata));
	अगर (IS_ERR(pdev))
		gpiod_हटाओ_lookup_table(gpio_lookup);

	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण

अटल व्योम __निकास atomisp2_led_cleanup(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(pdev);
	gpiod_हटाओ_lookup_table(gpio_lookup);
पूर्ण

module_init(atomisp2_led_init);
module_निकास(atomisp2_led_cleanup);

/*
 * The ACPI INIT method from Asus WMI's code on the T100TA and T200TA turns the
 * LED on (without the WMI पूर्णांकerface allowing further control over the LED).
 * Ensure we are loaded after asus-nb-wmi so that we turn the LED off again.
 */
MODULE_SOFTDEP("pre: asus_nb_wmi");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com");
MODULE_DESCRIPTION("Intel atomisp2 camera LED driver");
MODULE_LICENSE("GPL");
