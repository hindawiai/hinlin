<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/leds.h>

#समावेश <linux/पन.स>
#समावेश <linux/dmi.h>

#समावेश <linux/i8042.h>

#घोषणा CLEVO_MAIL_LED_OFF		0x0084
#घोषणा CLEVO_MAIL_LED_BLINK_1HZ	0x008A
#घोषणा CLEVO_MAIL_LED_BLINK_0_5HZ	0x0083

MODULE_AUTHOR("Mथँrton Nथऊmeth <nm127@freemail.hu>");
MODULE_DESCRIPTION("Clevo mail LED driver");
MODULE_LICENSE("GPL");

अटल bool nodetect;
module_param_named(nodetect, nodetect, bool, 0);
MODULE_PARM_DESC(nodetect, "Skip DMI hardware detection");

अटल काष्ठा platक्रमm_device *pdev;

अटल पूर्णांक __init clevo_mail_led_dmi_callback(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pr_info("'%s' found\n", id->ident);
	वापस 1;
पूर्ण

/*
 * काष्ठा clevo_mail_led_dmi_table - List of known good models
 *
 * Contains the known good models this driver is compatible with.
 * When adding a new model try to be as strict as possible. This
 * makes it possible to keep the false positives (the model is
 * detected as working, but in reality it is not) as low as
 * possible.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id clevo_mail_led_dmi_table[] __initस्थिर = अणु
	अणु
		.callback = clevo_mail_led_dmi_callback,
		.ident = "Clevo D410J",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "VIA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "K8N800"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "VT8204B")
		पूर्ण
	पूर्ण,
	अणु
		.callback = clevo_mail_led_dmi_callback,
		.ident = "Clevo M5x0N",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "CLEVO Co."),
			DMI_MATCH(DMI_PRODUCT_NAME, "M5x0N")
		पूर्ण
	पूर्ण,
	अणु
		.callback = clevo_mail_led_dmi_callback,
		.ident = "Clevo M5x0V",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "CLEVO Co. "),
			DMI_MATCH(DMI_BOARD_NAME, "M5X0V "),
			DMI_MATCH(DMI_PRODUCT_VERSION, "VT6198")
		पूर्ण
	पूर्ण,
	अणु
		.callback = clevo_mail_led_dmi_callback,
		.ident = "Clevo D400P",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Clevo"),
			DMI_MATCH(DMI_BOARD_NAME, "D400P"),
			DMI_MATCH(DMI_BOARD_VERSION, "Rev.A"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "0106")
		पूर्ण
	पूर्ण,
	अणु
		.callback = clevo_mail_led_dmi_callback,
		.ident = "Clevo D410V",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Clevo, Co."),
			DMI_MATCH(DMI_BOARD_NAME, "D400V/D470V"),
			DMI_MATCH(DMI_BOARD_VERSION, "SS78B"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "Rev. A1")
		पूर्ण
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, clevo_mail_led_dmi_table);

अटल व्योम clevo_mail_led_set(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness value)
अणु
	i8042_lock_chip();

	अगर (value == LED_OFF)
		i8042_command(शून्य, CLEVO_MAIL_LED_OFF);
	अन्यथा अगर (value <= LED_HALF)
		i8042_command(शून्य, CLEVO_MAIL_LED_BLINK_0_5HZ);
	अन्यथा
		i8042_command(शून्य, CLEVO_MAIL_LED_BLINK_1HZ);

	i8042_unlock_chip();

पूर्ण

अटल पूर्णांक clevo_mail_led_blink(काष्ठा led_classdev *led_cdev,
				अचिन्हित दीर्घ *delay_on,
				अचिन्हित दीर्घ *delay_off)
अणु
	पूर्णांक status = -EINVAL;

	i8042_lock_chip();

	अगर (*delay_on == 0 /* ms */ && *delay_off == 0 /* ms */) अणु
		/* Special हाल: the leds subप्रणाली requested us to
		 * chose one user मित्रly blinking of the LED, and
		 * start it. Let's blink the led slowly (0.5Hz).
		 */
		*delay_on = 1000; /* ms */
		*delay_off = 1000; /* ms */
		i8042_command(शून्य, CLEVO_MAIL_LED_BLINK_0_5HZ);
		status = 0;

	पूर्ण अन्यथा अगर (*delay_on == 500 /* ms */ && *delay_off == 500 /* ms */) अणु
		/* blink the led with 1Hz */
		i8042_command(शून्य, CLEVO_MAIL_LED_BLINK_1HZ);
		status = 0;

	पूर्ण अन्यथा अगर (*delay_on == 1000 /* ms */ && *delay_off == 1000 /* ms */) अणु
		/* blink the led with 0.5Hz */
		i8042_command(शून्य, CLEVO_MAIL_LED_BLINK_0_5HZ);
		status = 0;

	पूर्ण अन्यथा अणु
		pr_debug("clevo_mail_led_blink(..., %lu, %lu),"
		       " returning -EINVAL (unsupported)\n",
		       *delay_on, *delay_off);
	पूर्ण

	i8042_unlock_chip();

	वापस status;
पूर्ण

अटल काष्ठा led_classdev clevo_mail_led = अणु
	.name			= "clevo::mail",
	.brightness_set		= clevo_mail_led_set,
	.blink_set		= clevo_mail_led_blink,
	.flags			= LED_CORE_SUSPENDRESUME,
पूर्ण;

अटल पूर्णांक __init clevo_mail_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस led_classdev_रेजिस्टर(&pdev->dev, &clevo_mail_led);
पूर्ण

अटल पूर्णांक clevo_mail_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	led_classdev_unरेजिस्टर(&clevo_mail_led);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver clevo_mail_led_driver = अणु
	.हटाओ		= clevo_mail_led_हटाओ,
	.driver		= अणु
		.name		= KBUILD_MODNAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init clevo_mail_led_init(व्योम)
अणु
	पूर्णांक error = 0;
	पूर्णांक count = 0;

	/* Check with the help of DMI अगर we are running on supported hardware */
	अगर (!nodetect) अणु
		count = dmi_check_प्रणाली(clevo_mail_led_dmi_table);
	पूर्ण अन्यथा अणु
		count = 1;
		pr_err("Skipping DMI detection. "
		       "If the driver works on your hardware please "
		       "report model and the output of dmidecode in tracker "
		       "at http://sourceforge.net/projects/clevo-mailled/\n");
	पूर्ण

	अगर (!count)
		वापस -ENODEV;

	pdev = platक्रमm_device_रेजिस्टर_simple(KBUILD_MODNAME, -1, शून्य, 0);
	अगर (!IS_ERR(pdev)) अणु
		error = platक्रमm_driver_probe(&clevo_mail_led_driver,
					      clevo_mail_led_probe);
		अगर (error) अणु
			pr_err("Can't probe platform driver\n");
			platक्रमm_device_unरेजिस्टर(pdev);
		पूर्ण
	पूर्ण अन्यथा
		error = PTR_ERR(pdev);

	वापस error;
पूर्ण

अटल व्योम __निकास clevo_mail_led_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(pdev);
	platक्रमm_driver_unरेजिस्टर(&clevo_mail_led_driver);

	clevo_mail_led_set(शून्य, LED_OFF);
पूर्ण

module_init(clevo_mail_led_init);
module_निकास(clevo_mail_led_निकास);
