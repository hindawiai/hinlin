<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Input driver क्रम slidebars on some Lenovo IdeaPad laptops
 *
 * Copyright (C) 2013 Andrey Moiseev <o2g.org.ru@gmail.com>
 *
 * Reverse-engineered from Lenovo SlideNav software (SBarHook.dll).
 *
 * Trademarks are the property of their respective owners.
 */

/*
 * Currently tested and works on:
 *	Lenovo IdeaPad Y550
 *	Lenovo IdeaPad Y550P
 *
 * Other models can be added easily. To test,
 * load with 'force' parameter set 'true'.
 *
 * LEDs blinking and input mode are managed via sysfs,
 * (hex, अचिन्हित byte value):
 * /sys/devices/platक्रमm/ideapad_slidebar/slidebar_mode
 *
 * The value is in byte range, however, I only figured out
 * how bits 0b10011001 work. Some other bits, probably,
 * are meaningfull too.
 *
 * Possible states:
 *
 * STD_INT, ONMOV_INT, OFF_INT, LAST_POLL, OFF_POLL
 *
 * Meaning:
 *           released      touched
 * STD       'heartbeat'   lights follow the finger
 * ONMOV     no lights     lights follow the finger
 * LAST      at last pos   lights follow the finger
 * OFF       no lights     no lights
 *
 * INT       all input events are generated, पूर्णांकerrupts are used
 * POLL      no input events by शेष, to get them,
 *	     send 0b10000000 (पढ़ो below)
 *
 * Commands: ग_लिखो
 *
 * All      |  0b01001 -> STD_INT
 * possible |  0b10001 -> ONMOV_INT
 * states   |  0b01000 -> OFF_INT
 *
 *                      |  0b0 -> LAST_POLL
 * STD_INT or ONMOV_INT |
 *                      |  0b1 -> STD_INT
 *
 *                      |  0b0 -> OFF_POLL
 * OFF_INT or OFF_POLL  |
 *                      |  0b1 -> OFF_INT
 *
 * Any state |   0b10000000 ->  अगर the slidebar has updated data,
 *				produce one input event (last position),
 *				चयन to respective POLL mode
 *				(like 0x0), अगर not in POLL mode yet.
 *
 * Get current state: पढ़ो
 *
 * masked by 0x11 पढ़ो value means:
 *
 * 0x00   LAST
 * 0x01   STD
 * 0x10   OFF
 * 0x11   ONMOV
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/dmi.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/i8042.h>
#समावेश <linux/serपन.स>

#घोषणा IDEAPAD_BASE	0xff29

अटल bool क्रमce;
module_param(क्रमce, bool, 0);
MODULE_PARM_DESC(क्रमce, "Force driver load, ignore DMI data");

अटल DEFINE_SPINLOCK(io_lock);

अटल काष्ठा input_dev *slidebar_input_dev;
अटल काष्ठा platक्रमm_device *slidebar_platक्रमm_dev;

अटल u8 slidebar_pos_get(व्योम)
अणु
	u8 res;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&io_lock, flags);
	outb(0xf4, 0xff29);
	outb(0xbf, 0xff2a);
	res = inb(0xff2b);
	spin_unlock_irqrestore(&io_lock, flags);

	वापस res;
पूर्ण

अटल u8 slidebar_mode_get(व्योम)
अणु
	u8 res;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&io_lock, flags);
	outb(0xf7, 0xff29);
	outb(0x8b, 0xff2a);
	res = inb(0xff2b);
	spin_unlock_irqrestore(&io_lock, flags);

	वापस res;
पूर्ण

अटल व्योम slidebar_mode_set(u8 mode)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&io_lock, flags);
	outb(0xf7, 0xff29);
	outb(0x8b, 0xff2a);
	outb(mode, 0xff2b);
	spin_unlock_irqrestore(&io_lock, flags);
पूर्ण

अटल bool slidebar_i8042_filter(अचिन्हित अक्षर data, अचिन्हित अक्षर str,
				  काष्ठा serio *port)
अणु
	अटल bool extended = false;

	/* We are only पूर्णांकerested in data coming क्रमm KBC port */
	अगर (str & I8042_STR_AUXDATA)
		वापस false;

	/* Scancodes: e03b on move, e0bb on release. */
	अगर (data == 0xe0) अणु
		extended = true;
		वापस true;
	पूर्ण

	अगर (!extended)
		वापस false;

	extended = false;

	अगर (likely((data & 0x7f) != 0x3b)) अणु
		serio_पूर्णांकerrupt(port, 0xe0, 0);
		वापस false;
	पूर्ण

	अगर (data & 0x80) अणु
		input_report_key(slidebar_input_dev, BTN_TOUCH, 0);
	पूर्ण अन्यथा अणु
		input_report_key(slidebar_input_dev, BTN_TOUCH, 1);
		input_report_असल(slidebar_input_dev, ABS_X, slidebar_pos_get());
	पूर्ण
	input_sync(slidebar_input_dev);

	वापस true;
पूर्ण

अटल sमाप_प्रकार show_slidebar_mode(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%x\n", slidebar_mode_get());
पूर्ण

अटल sमाप_प्रकार store_slidebar_mode(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u8 mode;
	पूर्णांक error;

	error = kstrtou8(buf, 0, &mode);
	अगर (error)
		वापस error;

	slidebar_mode_set(mode);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(slidebar_mode, S_IWUSR | S_IRUGO,
		   show_slidebar_mode, store_slidebar_mode);

अटल काष्ठा attribute *ideapad_attrs[] = अणु
	&dev_attr_slidebar_mode.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group ideapad_attr_group = अणु
	.attrs = ideapad_attrs
पूर्ण;

अटल स्थिर काष्ठा attribute_group *ideapad_attr_groups[] = अणु
	&ideapad_attr_group,
	शून्य
पूर्ण;

अटल पूर्णांक __init ideapad_probe(काष्ठा platक्रमm_device* pdev)
अणु
	पूर्णांक err;

	अगर (!request_region(IDEAPAD_BASE, 3, "ideapad_slidebar")) अणु
		dev_err(&pdev->dev, "IO ports are busy\n");
		वापस -EBUSY;
	पूर्ण

	slidebar_input_dev = input_allocate_device();
	अगर (!slidebar_input_dev) अणु
		dev_err(&pdev->dev, "Failed to allocate input device\n");
		err = -ENOMEM;
		जाओ err_release_ports;
	पूर्ण

	slidebar_input_dev->name = "IdeaPad Slidebar";
	slidebar_input_dev->id.bustype = BUS_HOST;
	slidebar_input_dev->dev.parent = &pdev->dev;
	input_set_capability(slidebar_input_dev, EV_KEY, BTN_TOUCH);
	input_set_capability(slidebar_input_dev, EV_ABS, ABS_X);
	input_set_असल_params(slidebar_input_dev, ABS_X, 0, 0xff, 0, 0);

	err = i8042_install_filter(slidebar_i8042_filter);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"Failed to install i8042 filter: %d\n", err);
		जाओ err_मुक्त_dev;
	पूर्ण

	err = input_रेजिस्टर_device(slidebar_input_dev);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"Failed to register input device: %d\n", err);
		जाओ err_हटाओ_filter;
	पूर्ण

	वापस 0;

err_हटाओ_filter:
	i8042_हटाओ_filter(slidebar_i8042_filter);
err_मुक्त_dev:
	input_मुक्त_device(slidebar_input_dev);
err_release_ports:
	release_region(IDEAPAD_BASE, 3);
	वापस err;
पूर्ण

अटल पूर्णांक ideapad_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	i8042_हटाओ_filter(slidebar_i8042_filter);
	input_unरेजिस्टर_device(slidebar_input_dev);
	release_region(IDEAPAD_BASE, 3);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver slidebar_drv = अणु
	.driver = अणु
		.name = "ideapad_slidebar",
	पूर्ण,
	.हटाओ = ideapad_हटाओ,
पूर्ण;

अटल पूर्णांक __init ideapad_dmi_check(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pr_info("Laptop model '%s'\n", id->ident);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id ideapad_dmi[] __initस्थिर = अणु
	अणु
		.ident = "Lenovo IdeaPad Y550",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "20017"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "Lenovo IdeaPad Y550")
		पूर्ण,
		.callback = ideapad_dmi_check
	पूर्ण,
	अणु
		.ident = "Lenovo IdeaPad Y550P",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "20035"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "Lenovo IdeaPad Y550P")
		पूर्ण,
		.callback = ideapad_dmi_check
	पूर्ण,
	अणु शून्य, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, ideapad_dmi);

अटल पूर्णांक __init slidebar_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!क्रमce && !dmi_check_प्रणाली(ideapad_dmi)) अणु
		pr_err("DMI does not match\n");
		वापस -ENODEV;
	पूर्ण

	slidebar_platक्रमm_dev = platक्रमm_device_alloc("ideapad_slidebar", -1);
	अगर (!slidebar_platक्रमm_dev) अणु
		pr_err("Not enough memory\n");
		वापस -ENOMEM;
	पूर्ण

	slidebar_platक्रमm_dev->dev.groups = ideapad_attr_groups;

	err = platक्रमm_device_add(slidebar_platक्रमm_dev);
	अगर (err) अणु
		pr_err("Failed to register platform device\n");
		जाओ err_मुक्त_dev;
	पूर्ण

	err = platक्रमm_driver_probe(&slidebar_drv, ideapad_probe);
	अगर (err) अणु
		pr_err("Failed to register platform driver\n");
		जाओ err_delete_dev;
	पूर्ण

	वापस 0;

err_delete_dev:
	platक्रमm_device_del(slidebar_platक्रमm_dev);
err_मुक्त_dev:
	platक्रमm_device_put(slidebar_platक्रमm_dev);
	वापस err;
पूर्ण

अटल व्योम __निकास slidebar_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(slidebar_platक्रमm_dev);
	platक्रमm_driver_unरेजिस्टर(&slidebar_drv);
पूर्ण

module_init(slidebar_init);
module_निकास(slidebar_निकास);

MODULE_AUTHOR("Andrey Moiseev <o2g.org.ru@gmail.com>");
MODULE_DESCRIPTION("Slidebar input support for some Lenovo IdeaPad laptops");
MODULE_LICENSE("GPL");
