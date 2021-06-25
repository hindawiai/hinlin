<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Keyboard backlight LED driver क्रम ChromeOS
//
// Copyright (C) 2012 Google, Inc.

#समावेश <linux/acpi.h>
#समावेश <linux/leds.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/* Keyboard LED ACPI Device must be defined in firmware */
#घोषणा ACPI_KEYBOARD_BACKLIGHT_DEVICE	"\\_SB.KBLT"
#घोषणा ACPI_KEYBOARD_BACKLIGHT_READ	ACPI_KEYBOARD_BACKLIGHT_DEVICE ".KBQC"
#घोषणा ACPI_KEYBOARD_BACKLIGHT_WRITE	ACPI_KEYBOARD_BACKLIGHT_DEVICE ".KBCM"

#घोषणा ACPI_KEYBOARD_BACKLIGHT_MAX		100

अटल व्योम keyboard_led_set_brightness(काष्ठा led_classdev *cdev,
					क्रमागत led_brightness brightness)
अणु
	जोड़ acpi_object param;
	काष्ठा acpi_object_list input;
	acpi_status status;

	param.type = ACPI_TYPE_INTEGER;
	param.पूर्णांकeger.value = brightness;
	input.count = 1;
	input.poपूर्णांकer = &param;

	status = acpi_evaluate_object(शून्य, ACPI_KEYBOARD_BACKLIGHT_WRITE,
				      &input, शून्य);
	अगर (ACPI_FAILURE(status))
		dev_err(cdev->dev, "Error setting keyboard LED value: %d\n",
			status);
पूर्ण

अटल क्रमागत led_brightness
keyboard_led_get_brightness(काष्ठा led_classdev *cdev)
अणु
	अचिन्हित दीर्घ दीर्घ brightness;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(शून्य, ACPI_KEYBOARD_BACKLIGHT_READ,
				       शून्य, &brightness);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(cdev->dev, "Error getting keyboard LED value: %d\n",
			status);
		वापस -EIO;
	पूर्ण

	वापस brightness;
पूर्ण

अटल पूर्णांक keyboard_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा led_classdev *cdev;
	acpi_handle handle;
	acpi_status status;
	पूर्णांक error;

	/* Look क्रम the keyboard LED ACPI Device */
	status = acpi_get_handle(ACPI_ROOT_OBJECT,
				 ACPI_KEYBOARD_BACKLIGHT_DEVICE,
				 &handle);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&pdev->dev, "Unable to find ACPI device %s: %d\n",
			ACPI_KEYBOARD_BACKLIGHT_DEVICE, status);
		वापस -ENXIO;
	पूर्ण

	cdev = devm_kzalloc(&pdev->dev, माप(*cdev), GFP_KERNEL);
	अगर (!cdev)
		वापस -ENOMEM;

	cdev->name = "chromeos::kbd_backlight";
	cdev->max_brightness = ACPI_KEYBOARD_BACKLIGHT_MAX;
	cdev->flags |= LED_CORE_SUSPENDRESUME;
	cdev->brightness_set = keyboard_led_set_brightness;
	cdev->brightness_get = keyboard_led_get_brightness;

	error = devm_led_classdev_रेजिस्टर(&pdev->dev, cdev);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id keyboard_led_id[] = अणु
	अणु "GOOG0002", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, keyboard_led_id);

अटल काष्ठा platक्रमm_driver keyboard_led_driver = अणु
	.driver		= अणु
		.name	= "chromeos-keyboard-leds",
		.acpi_match_table = ACPI_PTR(keyboard_led_id),
	पूर्ण,
	.probe		= keyboard_led_probe,
पूर्ण;
module_platक्रमm_driver(keyboard_led_driver);

MODULE_AUTHOR("Simon Que <sque@chromium.org>");
MODULE_DESCRIPTION("ChromeOS Keyboard backlight LED Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:chromeos-keyboard-leds");
