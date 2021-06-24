<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2012 Robert Gerlach <khnz@gmx.de>
 * Copyright (C) 2005-2006 Jan Rychter <jan@rychter.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>

#घोषणा MODULENAME "fujitsu-tablet"

#घोषणा ACPI_FUJITSU_CLASS "fujitsu"

#घोषणा INVERT_TABLET_MODE_BIT      0x01
#घोषणा INVERT_DOCK_STATE_BIT       0x02
#घोषणा FORCE_TABLET_MODE_IF_UNDOCK 0x04

#घोषणा KEYMAP_LEN 16

अटल स्थिर काष्ठा acpi_device_id fujitsu_ids[] = अणु
	अणु .id = "FUJ02BD" पूर्ण,
	अणु .id = "FUJ02BF" पूर्ण,
	अणु .id = "" पूर्ण
पूर्ण;

काष्ठा fujitsu_config अणु
	अचिन्हित लघु keymap[KEYMAP_LEN];
	अचिन्हित पूर्णांक quirks;
पूर्ण;

अटल अचिन्हित लघु keymap_Lअगरebook_Tseries[KEYMAP_LEN] __initdata = अणु
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_SCROLLDOWN,
	KEY_SCROLLUP,
	KEY_ROTATE_DISPLAY,
	KEY_LEFTCTRL,
	KEY_BRIGHTNESSUP,
	KEY_BRIGHTNESSDOWN,
	KEY_BRIGHTNESS_ZERO,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_LEFTALT
पूर्ण;

अटल अचिन्हित लघु keymap_Lअगरebook_T901[KEYMAP_LEN] __initdata = अणु
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_SCROLLDOWN,
	KEY_SCROLLUP,
	KEY_CYCLEWINDOWS,
	KEY_LEFTCTRL,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_LEFTMETA
पूर्ण;

अटल अचिन्हित लघु keymap_Lअगरebook_T902[KEYMAP_LEN] __initdata = अणु
	KEY_RESERVED,
	KEY_VOLUMEDOWN,
	KEY_VOLUMEUP,
	KEY_CYCLEWINDOWS,
	KEY_PROG1,
	KEY_PROG2,
	KEY_LEFTMETA,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
पूर्ण;

अटल अचिन्हित लघु keymap_Lअगरebook_U810[KEYMAP_LEN] __initdata = अणु
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_PROG1,
	KEY_PROG2,
	KEY_ROTATE_DISPLAY,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_UP,
	KEY_DOWN,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_LEFTCTRL,
	KEY_LEFTALT
पूर्ण;

अटल अचिन्हित लघु keymap_Stylistic_Tseries[KEYMAP_LEN] __initdata = अणु
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_PRINT,
	KEY_BACKSPACE,
	KEY_SPACE,
	KEY_ENTER,
	KEY_BRIGHTNESSUP,
	KEY_BRIGHTNESSDOWN,
	KEY_DOWN,
	KEY_UP,
	KEY_SCROLLUP,
	KEY_SCROLLDOWN,
	KEY_LEFTCTRL,
	KEY_LEFTALT
पूर्ण;

अटल अचिन्हित लघु keymap_Stylistic_ST5xxx[KEYMAP_LEN] __initdata = अणु
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_MAIL,
	KEY_ROTATE_DISPLAY,
	KEY_ESC,
	KEY_ENTER,
	KEY_BRIGHTNESSUP,
	KEY_BRIGHTNESSDOWN,
	KEY_DOWN,
	KEY_UP,
	KEY_SCROLLUP,
	KEY_SCROLLDOWN,
	KEY_LEFTCTRL,
	KEY_LEFTALT
पूर्ण;

अटल काष्ठा अणु
	काष्ठा input_dev *idev;
	काष्ठा fujitsu_config config;
	अचिन्हित दीर्घ prev_keymask;

	अक्षर phys[21];

	पूर्णांक irq;
	पूर्णांक io_base;
	पूर्णांक io_length;
पूर्ण fujitsu;

अटल u8 fujitsu_ack(व्योम)
अणु
	वापस inb(fujitsu.io_base + 2);
पूर्ण

अटल u8 fujitsu_status(व्योम)
अणु
	वापस inb(fujitsu.io_base + 6);
पूर्ण

अटल u8 fujitsu_पढ़ो_रेजिस्टर(स्थिर u8 addr)
अणु
	outb(addr, fujitsu.io_base);
	वापस inb(fujitsu.io_base + 4);
पूर्ण

अटल व्योम fujitsu_send_state(व्योम)
अणु
	पूर्णांक state;
	पूर्णांक करोck, tablet_mode;

	state = fujitsu_पढ़ो_रेजिस्टर(0xdd);

	करोck = state & 0x02;
	अगर (fujitsu.config.quirks & INVERT_DOCK_STATE_BIT)
		करोck = !करोck;

	अगर ((fujitsu.config.quirks & FORCE_TABLET_MODE_IF_UNDOCK) && (!करोck)) अणु
		tablet_mode = 1;
	पूर्ण अन्यथाअणु
		tablet_mode = state & 0x01;
		अगर (fujitsu.config.quirks & INVERT_TABLET_MODE_BIT)
			tablet_mode = !tablet_mode;
	पूर्ण

	input_report_चयन(fujitsu.idev, SW_DOCK, करोck);
	input_report_चयन(fujitsu.idev, SW_TABLET_MODE, tablet_mode);
	input_sync(fujitsu.idev);
पूर्ण

अटल व्योम fujitsu_reset(व्योम)
अणु
	पूर्णांक समयout = 50;

	fujitsu_ack();

	जबतक ((fujitsu_status() & 0x02) && (--समयout))
		msleep(20);

	fujitsu_send_state();
पूर्ण

अटल पूर्णांक input_fujitsu_setup(काष्ठा device *parent, स्थिर अक्षर *name,
			       स्थिर अक्षर *phys)
अणु
	काष्ठा input_dev *idev;
	पूर्णांक error;
	पूर्णांक i;

	idev = input_allocate_device();
	अगर (!idev)
		वापस -ENOMEM;

	idev->dev.parent = parent;
	idev->phys = phys;
	idev->name = name;
	idev->id.bustype = BUS_HOST;
	idev->id.venकरोr  = 0x1734;	/* Fujitsu Siemens Computer GmbH */
	idev->id.product = 0x0001;
	idev->id.version = 0x0101;

	idev->keycode = fujitsu.config.keymap;
	idev->keycodesize = माप(fujitsu.config.keymap[0]);
	idev->keycodemax = ARRAY_SIZE(fujitsu.config.keymap);

	__set_bit(EV_REP, idev->evbit);

	क्रम (i = 0; i < ARRAY_SIZE(fujitsu.config.keymap); i++)
		अगर (fujitsu.config.keymap[i])
			input_set_capability(idev, EV_KEY, fujitsu.config.keymap[i]);

	input_set_capability(idev, EV_MSC, MSC_SCAN);

	input_set_capability(idev, EV_SW, SW_DOCK);
	input_set_capability(idev, EV_SW, SW_TABLET_MODE);

	error = input_रेजिस्टर_device(idev);
	अगर (error) अणु
		input_मुक्त_device(idev);
		वापस error;
	पूर्ण

	fujitsu.idev = idev;
	वापस 0;
पूर्ण

अटल व्योम input_fujitsu_हटाओ(व्योम)
अणु
	input_unरेजिस्टर_device(fujitsu.idev);
पूर्ण

अटल irqवापस_t fujitsu_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ keymask, changed;
	अचिन्हित पूर्णांक keycode;
	पूर्णांक pressed;
	पूर्णांक i;

	अगर (unlikely(!(fujitsu_status() & 0x01)))
		वापस IRQ_NONE;

	fujitsu_send_state();

	keymask  = fujitsu_पढ़ो_रेजिस्टर(0xde);
	keymask |= fujitsu_पढ़ो_रेजिस्टर(0xdf) << 8;
	keymask ^= 0xffff;

	changed = keymask ^ fujitsu.prev_keymask;
	अगर (changed) अणु
		fujitsu.prev_keymask = keymask;

		क्रम_each_set_bit(i, &changed, KEYMAP_LEN) अणु
			keycode = fujitsu.config.keymap[i];
			pressed = keymask & changed & BIT(i);

			अगर (pressed)
				input_event(fujitsu.idev, EV_MSC, MSC_SCAN, i);

			input_report_key(fujitsu.idev, keycode, pressed);
			input_sync(fujitsu.idev);
		पूर्ण
	पूर्ण

	fujitsu_ack();
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __init fujitsu_dmi_common(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	pr_info("%s\n", dmi->ident);
	स_नकल(fujitsu.config.keymap, dmi->driver_data,
			माप(fujitsu.config.keymap));
पूर्ण

अटल पूर्णांक __init fujitsu_dmi_lअगरebook(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	fujitsu_dmi_common(dmi);
	fujitsu.config.quirks |= INVERT_TABLET_MODE_BIT;
	वापस 1;
पूर्ण

अटल पूर्णांक __init fujitsu_dmi_stylistic(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	fujitsu_dmi_common(dmi);
	fujitsu.config.quirks |= FORCE_TABLET_MODE_IF_UNDOCK;
	fujitsu.config.quirks |= INVERT_DOCK_STATE_BIT;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id dmi_ids[] __initस्थिर = अणु
	अणु
		.callback = fujitsu_dmi_lअगरebook,
		.ident = "Fujitsu Lifebook T901",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LifeBook T901")
		पूर्ण,
		.driver_data = keymap_Lअगरebook_T901
	पूर्ण,
	अणु
		.callback = fujitsu_dmi_lअगरebook,
		.ident = "Fujitsu Lifebook T901",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK T901")
		पूर्ण,
		.driver_data = keymap_Lअगरebook_T901
	पूर्ण,
	अणु
		.callback = fujitsu_dmi_lअगरebook,
		.ident = "Fujitsu Lifebook T902",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK T902")
		पूर्ण,
		.driver_data = keymap_Lअगरebook_T902
	पूर्ण,
	अणु
		.callback = fujitsu_dmi_lअगरebook,
		.ident = "Fujitsu Siemens P/T Series",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK")
		पूर्ण,
		.driver_data = keymap_Lअगरebook_Tseries
	पूर्ण,
	अणु
		.callback = fujitsu_dmi_lअगरebook,
		.ident = "Fujitsu Lifebook T Series",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LifeBook T")
		पूर्ण,
		.driver_data = keymap_Lअगरebook_Tseries
	पूर्ण,
	अणु
		.callback = fujitsu_dmi_stylistic,
		.ident = "Fujitsu Siemens Stylistic T Series",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Stylistic T")
		पूर्ण,
		.driver_data = keymap_Stylistic_Tseries
	पूर्ण,
	अणु
		.callback = fujitsu_dmi_lअगरebook,
		.ident = "Fujitsu LifeBook U810",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LifeBook U810")
		पूर्ण,
		.driver_data = keymap_Lअगरebook_U810
	पूर्ण,
	अणु
		.callback = fujitsu_dmi_stylistic,
		.ident = "Fujitsu Siemens Stylistic ST5xxx Series",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "STYLISTIC ST5")
		पूर्ण,
		.driver_data = keymap_Stylistic_ST5xxx
	पूर्ण,
	अणु
		.callback = fujitsu_dmi_stylistic,
		.ident = "Fujitsu Siemens Stylistic ST5xxx Series",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Stylistic ST5")
		पूर्ण,
		.driver_data = keymap_Stylistic_ST5xxx
	पूर्ण,
	अणु
		.callback = fujitsu_dmi_lअगरebook,
		.ident = "Unknown (using defaults)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, ""),
			DMI_MATCH(DMI_PRODUCT_NAME, "")
		पूर्ण,
		.driver_data = keymap_Lअगरebook_Tseries
	पूर्ण,
	अणु शून्य पूर्ण
पूर्ण;

अटल acpi_status fujitsu_walk_resources(काष्ठा acpi_resource *res, व्योम *data)
अणु
	चयन (res->type) अणु
	हाल ACPI_RESOURCE_TYPE_IRQ:
		fujitsu.irq = res->data.irq.पूर्णांकerrupts[0];
		वापस AE_OK;

	हाल ACPI_RESOURCE_TYPE_IO:
		fujitsu.io_base = res->data.io.minimum;
		fujitsu.io_length = res->data.io.address_length;
		वापस AE_OK;

	हाल ACPI_RESOURCE_TYPE_END_TAG:
		अगर (fujitsu.irq && fujitsu.io_base)
			वापस AE_OK;
		अन्यथा
			वापस AE_NOT_FOUND;

	शेष:
		वापस AE_ERROR;
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_fujitsu_add(काष्ठा acpi_device *adev)
अणु
	acpi_status status;
	पूर्णांक error;

	अगर (!adev)
		वापस -EINVAL;

	status = acpi_walk_resources(adev->handle, METHOD_NAME__CRS,
			fujitsu_walk_resources, शून्य);
	अगर (ACPI_FAILURE(status) || !fujitsu.irq || !fujitsu.io_base)
		वापस -ENODEV;

	प्र_लिखो(acpi_device_name(adev), "Fujitsu %s", acpi_device_hid(adev));
	प्र_लिखो(acpi_device_class(adev), "%s", ACPI_FUJITSU_CLASS);

	snम_लिखो(fujitsu.phys, माप(fujitsu.phys),
			"%s/input0", acpi_device_hid(adev));

	error = input_fujitsu_setup(&adev->dev,
		acpi_device_name(adev), fujitsu.phys);
	अगर (error)
		वापस error;

	अगर (!request_region(fujitsu.io_base, fujitsu.io_length, MODULENAME)) अणु
		input_fujitsu_हटाओ();
		वापस -EBUSY;
	पूर्ण

	fujitsu_reset();

	error = request_irq(fujitsu.irq, fujitsu_पूर्णांकerrupt,
			IRQF_SHARED, MODULENAME, fujitsu_पूर्णांकerrupt);
	अगर (error) अणु
		release_region(fujitsu.io_base, fujitsu.io_length);
		input_fujitsu_हटाओ();
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_fujitsu_हटाओ(काष्ठा acpi_device *adev)
अणु
	मुक्त_irq(fujitsu.irq, fujitsu_पूर्णांकerrupt);
	release_region(fujitsu.io_base, fujitsu.io_length);
	input_fujitsu_हटाओ();
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acpi_fujitsu_resume(काष्ठा device *dev)
अणु
	fujitsu_reset();
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(acpi_fujitsu_pm, शून्य, acpi_fujitsu_resume);

अटल काष्ठा acpi_driver acpi_fujitsu_driver = अणु
	.name  = MODULENAME,
	.class = "hotkey",
	.ids   = fujitsu_ids,
	.ops   = अणु
		.add    = acpi_fujitsu_add,
		.हटाओ	= acpi_fujitsu_हटाओ,
	पूर्ण,
	.drv.pm = &acpi_fujitsu_pm,
पूर्ण;

अटल पूर्णांक __init fujitsu_module_init(व्योम)
अणु
	पूर्णांक error;

	dmi_check_प्रणाली(dmi_ids);

	error = acpi_bus_रेजिस्टर_driver(&acpi_fujitsu_driver);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल व्योम __निकास fujitsu_module_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&acpi_fujitsu_driver);
पूर्ण

module_init(fujitsu_module_init);
module_निकास(fujitsu_module_निकास);

MODULE_AUTHOR("Robert Gerlach <khnz@gmx.de>");
MODULE_DESCRIPTION("Fujitsu tablet pc extras driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("2.5");

MODULE_DEVICE_TABLE(acpi, fujitsu_ids);
