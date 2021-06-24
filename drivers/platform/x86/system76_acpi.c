<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * System76 ACPI Driver
 *
 * Copyright (C) 2019 System76
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/types.h>

काष्ठा प्रणाली76_data अणु
	काष्ठा acpi_device *acpi_dev;
	काष्ठा led_classdev ap_led;
	काष्ठा led_classdev kb_led;
	क्रमागत led_brightness kb_brightness;
	क्रमागत led_brightness kb_toggle_brightness;
	पूर्णांक kb_color;
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id device_ids[] = अणु
	अणु"17761776", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, device_ids);

// Array of keyboard LED brightness levels
अटल स्थिर क्रमागत led_brightness kb_levels[] = अणु
	48,
	72,
	96,
	144,
	192,
	255
पूर्ण;

// Array of keyboard LED colors in 24-bit RGB क्रमmat
अटल स्थिर पूर्णांक kb_colors[] = अणु
	0xFFFFFF,
	0x0000FF,
	0xFF0000,
	0xFF00FF,
	0x00FF00,
	0x00FFFF,
	0xFFFF00
पूर्ण;

// Get a System76 ACPI device value by name
अटल पूर्णांक प्रणाली76_get(काष्ठा प्रणाली76_data *data, अक्षर *method)
अणु
	acpi_handle handle;
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ ret = 0;

	handle = acpi_device_handle(data->acpi_dev);
	status = acpi_evaluate_पूर्णांकeger(handle, method, शून्य, &ret);
	अगर (ACPI_SUCCESS(status))
		वापस (पूर्णांक)ret;
	अन्यथा
		वापस -1;
पूर्ण

// Set a System76 ACPI device value by name
अटल पूर्णांक प्रणाली76_set(काष्ठा प्रणाली76_data *data, अक्षर *method, पूर्णांक value)
अणु
	जोड़ acpi_object obj;
	काष्ठा acpi_object_list obj_list;
	acpi_handle handle;
	acpi_status status;

	obj.type = ACPI_TYPE_INTEGER;
	obj.पूर्णांकeger.value = value;
	obj_list.count = 1;
	obj_list.poपूर्णांकer = &obj;
	handle = acpi_device_handle(data->acpi_dev);
	status = acpi_evaluate_object(handle, method, &obj_list, शून्य);
	अगर (ACPI_SUCCESS(status))
		वापस 0;
	अन्यथा
		वापस -1;
पूर्ण

// Get the airplane mode LED brightness
अटल क्रमागत led_brightness ap_led_get(काष्ठा led_classdev *led)
अणु
	काष्ठा प्रणाली76_data *data;
	पूर्णांक value;

	data = container_of(led, काष्ठा प्रणाली76_data, ap_led);
	value = प्रणाली76_get(data, "GAPL");
	अगर (value > 0)
		वापस (क्रमागत led_brightness)value;
	अन्यथा
		वापस LED_OFF;
पूर्ण

// Set the airplane mode LED brightness
अटल पूर्णांक ap_led_set(काष्ठा led_classdev *led, क्रमागत led_brightness value)
अणु
	काष्ठा प्रणाली76_data *data;

	data = container_of(led, काष्ठा प्रणाली76_data, ap_led);
	वापस प्रणाली76_set(data, "SAPL", value == LED_OFF ? 0 : 1);
पूर्ण

// Get the last set keyboard LED brightness
अटल क्रमागत led_brightness kb_led_get(काष्ठा led_classdev *led)
अणु
	काष्ठा प्रणाली76_data *data;

	data = container_of(led, काष्ठा प्रणाली76_data, kb_led);
	वापस data->kb_brightness;
पूर्ण

// Set the keyboard LED brightness
अटल पूर्णांक kb_led_set(काष्ठा led_classdev *led, क्रमागत led_brightness value)
अणु
	काष्ठा प्रणाली76_data *data;

	data = container_of(led, काष्ठा प्रणाली76_data, kb_led);
	data->kb_brightness = value;
	वापस प्रणाली76_set(data, "SKBL", (पूर्णांक)data->kb_brightness);
पूर्ण

// Get the last set keyboard LED color
अटल sमाप_प्रकार kb_led_color_show(
	काष्ठा device *dev,
	काष्ठा device_attribute *dev_attr,
	अक्षर *buf)
अणु
	काष्ठा led_classdev *led;
	काष्ठा प्रणाली76_data *data;

	led = (काष्ठा led_classdev *)dev->driver_data;
	data = container_of(led, काष्ठा प्रणाली76_data, kb_led);
	वापस प्र_लिखो(buf, "%06X\n", data->kb_color);
पूर्ण

// Set the keyboard LED color
अटल sमाप_प्रकार kb_led_color_store(
	काष्ठा device *dev,
	काष्ठा device_attribute *dev_attr,
	स्थिर अक्षर *buf,
	माप_प्रकार size)
अणु
	काष्ठा led_classdev *led;
	काष्ठा प्रणाली76_data *data;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	led = (काष्ठा led_classdev *)dev->driver_data;
	data = container_of(led, काष्ठा प्रणाली76_data, kb_led);
	ret = kstrtouपूर्णांक(buf, 16, &val);
	अगर (ret)
		वापस ret;
	अगर (val > 0xFFFFFF)
		वापस -EINVAL;
	data->kb_color = (पूर्णांक)val;
	प्रणाली76_set(data, "SKBC", data->kb_color);

	वापस size;
पूर्ण

अटल स्थिर काष्ठा device_attribute kb_led_color_dev_attr = अणु
	.attr = अणु
		.name = "color",
		.mode = 0644,
	पूर्ण,
	.show = kb_led_color_show,
	.store = kb_led_color_store,
पूर्ण;

// Notअगरy that the keyboard LED was changed by hardware
अटल व्योम kb_led_notअगरy(काष्ठा प्रणाली76_data *data)
अणु
	led_classdev_notअगरy_brightness_hw_changed(
		&data->kb_led,
		data->kb_brightness
	);
पूर्ण

// Read keyboard LED brightness as set by hardware
अटल व्योम kb_led_hotkey_hardware(काष्ठा प्रणाली76_data *data)
अणु
	पूर्णांक value;

	value = प्रणाली76_get(data, "GKBL");
	अगर (value < 0)
		वापस;
	data->kb_brightness = value;
	kb_led_notअगरy(data);
पूर्ण

// Toggle the keyboard LED
अटल व्योम kb_led_hotkey_toggle(काष्ठा प्रणाली76_data *data)
अणु
	अगर (data->kb_brightness > 0) अणु
		data->kb_toggle_brightness = data->kb_brightness;
		kb_led_set(&data->kb_led, 0);
	पूर्ण अन्यथा अणु
		kb_led_set(&data->kb_led, data->kb_toggle_brightness);
	पूर्ण
	kb_led_notअगरy(data);
पूर्ण

// Decrease the keyboard LED brightness
अटल व्योम kb_led_hotkey_करोwn(काष्ठा प्रणाली76_data *data)
अणु
	पूर्णांक i;

	अगर (data->kb_brightness > 0) अणु
		क्रम (i = ARRAY_SIZE(kb_levels); i > 0; i--) अणु
			अगर (kb_levels[i - 1] < data->kb_brightness) अणु
				kb_led_set(&data->kb_led, kb_levels[i - 1]);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		kb_led_set(&data->kb_led, data->kb_toggle_brightness);
	पूर्ण
	kb_led_notअगरy(data);
पूर्ण

// Increase the keyboard LED brightness
अटल व्योम kb_led_hotkey_up(काष्ठा प्रणाली76_data *data)
अणु
	पूर्णांक i;

	अगर (data->kb_brightness > 0) अणु
		क्रम (i = 0; i < ARRAY_SIZE(kb_levels); i++) अणु
			अगर (kb_levels[i] > data->kb_brightness) अणु
				kb_led_set(&data->kb_led, kb_levels[i]);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		kb_led_set(&data->kb_led, data->kb_toggle_brightness);
	पूर्ण
	kb_led_notअगरy(data);
पूर्ण

// Cycle the keyboard LED color
अटल व्योम kb_led_hotkey_color(काष्ठा प्रणाली76_data *data)
अणु
	पूर्णांक i;

	अगर (data->kb_color < 0)
		वापस;
	अगर (data->kb_brightness > 0) अणु
		क्रम (i = 0; i < ARRAY_SIZE(kb_colors); i++) अणु
			अगर (kb_colors[i] == data->kb_color)
				अवरोध;
		पूर्ण
		i += 1;
		अगर (i >= ARRAY_SIZE(kb_colors))
			i = 0;
		data->kb_color = kb_colors[i];
		प्रणाली76_set(data, "SKBC", data->kb_color);
	पूर्ण अन्यथा अणु
		kb_led_set(&data->kb_led, data->kb_toggle_brightness);
	पूर्ण
	kb_led_notअगरy(data);
पूर्ण

// Handle ACPI notअगरication
अटल व्योम प्रणाली76_notअगरy(काष्ठा acpi_device *acpi_dev, u32 event)
अणु
	काष्ठा प्रणाली76_data *data;

	data = acpi_driver_data(acpi_dev);
	चयन (event) अणु
	हाल 0x80:
		kb_led_hotkey_hardware(data);
		अवरोध;
	हाल 0x81:
		kb_led_hotkey_toggle(data);
		अवरोध;
	हाल 0x82:
		kb_led_hotkey_करोwn(data);
		अवरोध;
	हाल 0x83:
		kb_led_hotkey_up(data);
		अवरोध;
	हाल 0x84:
		kb_led_hotkey_color(data);
		अवरोध;
	पूर्ण
पूर्ण

// Add a System76 ACPI device
अटल पूर्णांक प्रणाली76_add(काष्ठा acpi_device *acpi_dev)
अणु
	काष्ठा प्रणाली76_data *data;
	पूर्णांक err;

	data = devm_kzalloc(&acpi_dev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	acpi_dev->driver_data = data;
	data->acpi_dev = acpi_dev;

	err = प्रणाली76_get(data, "INIT");
	अगर (err)
		वापस err;
	data->ap_led.name = "system76_acpi::airplane";
	data->ap_led.flags = LED_CORE_SUSPENDRESUME;
	data->ap_led.brightness_get = ap_led_get;
	data->ap_led.brightness_set_blocking = ap_led_set;
	data->ap_led.max_brightness = 1;
	data->ap_led.शेष_trigger = "rfkill-none";
	err = devm_led_classdev_रेजिस्टर(&acpi_dev->dev, &data->ap_led);
	अगर (err)
		वापस err;

	data->kb_led.name = "system76_acpi::kbd_backlight";
	data->kb_led.flags = LED_BRIGHT_HW_CHANGED | LED_CORE_SUSPENDRESUME;
	data->kb_led.brightness_get = kb_led_get;
	data->kb_led.brightness_set_blocking = kb_led_set;
	अगर (acpi_has_method(acpi_device_handle(data->acpi_dev), "SKBC")) अणु
		data->kb_led.max_brightness = 255;
		data->kb_toggle_brightness = 72;
		data->kb_color = 0xffffff;
		प्रणाली76_set(data, "SKBC", data->kb_color);
	पूर्ण अन्यथा अणु
		data->kb_led.max_brightness = 5;
		data->kb_color = -1;
	पूर्ण
	err = devm_led_classdev_रेजिस्टर(&acpi_dev->dev, &data->kb_led);
	अगर (err)
		वापस err;

	अगर (data->kb_color >= 0) अणु
		err = device_create_file(
			data->kb_led.dev,
			&kb_led_color_dev_attr
		);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

// Remove a System76 ACPI device
अटल पूर्णांक प्रणाली76_हटाओ(काष्ठा acpi_device *acpi_dev)
अणु
	काष्ठा प्रणाली76_data *data;

	data = acpi_driver_data(acpi_dev);
	अगर (data->kb_color >= 0)
		device_हटाओ_file(data->kb_led.dev, &kb_led_color_dev_attr);

	devm_led_classdev_unरेजिस्टर(&acpi_dev->dev, &data->ap_led);

	devm_led_classdev_unरेजिस्टर(&acpi_dev->dev, &data->kb_led);

	प्रणाली76_get(data, "FINI");

	वापस 0;
पूर्ण

अटल काष्ठा acpi_driver प्रणाली76_driver = अणु
	.name = "System76 ACPI Driver",
	.class = "hotkey",
	.ids = device_ids,
	.ops = अणु
		.add = प्रणाली76_add,
		.हटाओ = प्रणाली76_हटाओ,
		.notअगरy = प्रणाली76_notअगरy,
	पूर्ण,
पूर्ण;
module_acpi_driver(प्रणाली76_driver);

MODULE_DESCRIPTION("System76 ACPI Driver");
MODULE_AUTHOR("Jeremy Soller <jeremy@system76.com>");
MODULE_LICENSE("GPL");
