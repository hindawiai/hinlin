<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  hp_accel.c - Interface between LIS3LV02DL driver and HP ACPI BIOS
 *
 *  Copyright (C) 2007-2008 Yan Burman
 *  Copyright (C) 2008 Eric Piel
 *  Copyright (C) 2008-2009 Pavel Machek
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/dmi.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/रुको.h>
#समावेश <linux/poll.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/leds.h>
#समावेश <linux/atomic.h>
#समावेश <linux/acpi.h>
#समावेश <linux/i8042.h>
#समावेश <linux/serपन.स>
#समावेश "../../misc/lis3lv02d/lis3lv02d.h"

#घोषणा DRIVER_NAME     "hp_accel"
#घोषणा ACPI_MDPS_CLASS "accelerometer"

/* Delayed LEDs infraकाष्ठाure ------------------------------------ */

/* Special LED class that can defer work */
काष्ठा delayed_led_classdev अणु
	काष्ठा led_classdev led_classdev;
	काष्ठा work_काष्ठा work;
	क्रमागत led_brightness new_brightness;

	अचिन्हित पूर्णांक led;		/* For driver */
	व्योम (*set_brightness)(काष्ठा delayed_led_classdev *data, क्रमागत led_brightness value);
पूर्ण;

अटल अंतरभूत व्योम delayed_set_status_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_led_classdev *data =
			container_of(work, काष्ठा delayed_led_classdev, work);

	data->set_brightness(data, data->new_brightness);
पूर्ण

अटल अंतरभूत व्योम delayed_sysfs_set(काष्ठा led_classdev *led_cdev,
			      क्रमागत led_brightness brightness)
अणु
	काष्ठा delayed_led_classdev *data = container_of(led_cdev,
			     काष्ठा delayed_led_classdev, led_classdev);
	data->new_brightness = brightness;
	schedule_work(&data->work);
पूर्ण

/* HP-specअगरic accelerometer driver ------------------------------------ */

/* e0 25, e0 26, e0 27, e0 28 are scan codes that the accelerometer with acpi id
 * HPQ6000 sends through the keyboard bus */
#घोषणा ACCEL_1 0x25
#घोषणा ACCEL_2 0x26
#घोषणा ACCEL_3 0x27
#घोषणा ACCEL_4 0x28

/* For स्वतःmatic insertion of the module */
अटल स्थिर काष्ठा acpi_device_id lis3lv02d_device_ids[] = अणु
	अणु"HPQ0004", 0पूर्ण, /* HP Mobile Data Protection System PNP */
	अणु"HPQ6000", 0पूर्ण, /* HP Mobile Data Protection System PNP */
	अणु"HPQ6007", 0पूर्ण, /* HP Mobile Data Protection System PNP */
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, lis3lv02d_device_ids);


/**
 * lis3lv02d_acpi_init - ACPI _INI method: initialize the device.
 * @lis3: poपूर्णांकer to the device काष्ठा
 *
 * Returns 0 on success.
 */
अटल पूर्णांक lis3lv02d_acpi_init(काष्ठा lis3lv02d *lis3)
अणु
	काष्ठा acpi_device *dev = lis3->bus_priv;
	अगर (!lis3->init_required)
		वापस 0;

	अगर (acpi_evaluate_object(dev->handle, METHOD_NAME__INI,
				 शून्य, शून्य) != AE_OK)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * lis3lv02d_acpi_पढ़ो - ACPI ALRD method: पढ़ो a रेजिस्टर
 * @lis3: poपूर्णांकer to the device काष्ठा
 * @reg:    the रेजिस्टर to पढ़ो
 * @ret:    result of the operation
 *
 * Returns 0 on success.
 */
अटल पूर्णांक lis3lv02d_acpi_पढ़ो(काष्ठा lis3lv02d *lis3, पूर्णांक reg, u8 *ret)
अणु
	काष्ठा acpi_device *dev = lis3->bus_priv;
	जोड़ acpi_object arg0 = अणु ACPI_TYPE_INTEGER पूर्ण;
	काष्ठा acpi_object_list args = अणु 1, &arg0 पूर्ण;
	अचिन्हित दीर्घ दीर्घ lret;
	acpi_status status;

	arg0.पूर्णांकeger.value = reg;

	status = acpi_evaluate_पूर्णांकeger(dev->handle, "ALRD", &args, &lret);
	अगर (ACPI_FAILURE(status))
		वापस -EINVAL;
	*ret = lret;
	वापस 0;
पूर्ण

/**
 * lis3lv02d_acpi_ग_लिखो - ACPI ALWR method: ग_लिखो to a रेजिस्टर
 * @lis3: poपूर्णांकer to the device काष्ठा
 * @reg:    the रेजिस्टर to ग_लिखो to
 * @val:    the value to ग_लिखो
 *
 * Returns 0 on success.
 */
अटल पूर्णांक lis3lv02d_acpi_ग_लिखो(काष्ठा lis3lv02d *lis3, पूर्णांक reg, u8 val)
अणु
	काष्ठा acpi_device *dev = lis3->bus_priv;
	अचिन्हित दीर्घ दीर्घ ret; /* Not used when writting */
	जोड़ acpi_object in_obj[2];
	काष्ठा acpi_object_list args = अणु 2, in_obj पूर्ण;

	in_obj[0].type          = ACPI_TYPE_INTEGER;
	in_obj[0].पूर्णांकeger.value = reg;
	in_obj[1].type          = ACPI_TYPE_INTEGER;
	in_obj[1].पूर्णांकeger.value = val;

	अगर (acpi_evaluate_पूर्णांकeger(dev->handle, "ALWR", &args, &ret) != AE_OK)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक lis3lv02d_dmi_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	lis3_dev.ac = *((जोड़ axis_conversion *)dmi->driver_data);
	pr_info("hardware type %s found\n", dmi->ident);

	वापस 1;
पूर्ण

/* Represents, क्रम each axis seen by userspace, the corresponding hw axis (+1).
 * If the value is negative, the opposite of the hw value is used. */
#घोषणा DEFINE_CONV(name, x, y, z)			      \
	अटल जोड़ axis_conversion lis3lv02d_axis_##name = \
		अणु .as_array = अणु x, y, z पूर्ण पूर्ण
DEFINE_CONV(normal, 1, 2, 3);
DEFINE_CONV(y_inverted, 1, -2, 3);
DEFINE_CONV(x_inverted, -1, 2, 3);
DEFINE_CONV(x_inverted_usd, -1, 2, -3);
DEFINE_CONV(z_inverted, 1, 2, -3);
DEFINE_CONV(xy_swap, 2, 1, 3);
DEFINE_CONV(xy_rotated_left, -2, 1, 3);
DEFINE_CONV(xy_rotated_left_usd, -2, 1, -3);
DEFINE_CONV(xy_swap_inverted, -2, -1, 3);
DEFINE_CONV(xy_rotated_right, 2, -1, 3);
DEFINE_CONV(xy_swap_yz_inverted, 2, -1, -3);

#घोषणा AXIS_DMI_MATCH(_ident, _name, _axis) अणु		\
	.ident = _ident,				\
	.callback = lis3lv02d_dmi_matched,		\
	.matches = अणु					\
		DMI_MATCH(DMI_PRODUCT_NAME, _name)	\
	पूर्ण,						\
	.driver_data = &lis3lv02d_axis_##_axis		\
पूर्ण

#घोषणा AXIS_DMI_MATCH2(_ident, _class1, _name1,	\
				_class2, _name2,	\
				_axis) अणु		\
	.ident = _ident,				\
	.callback = lis3lv02d_dmi_matched,		\
	.matches = अणु					\
		DMI_MATCH(DMI_##_class1, _name1),	\
		DMI_MATCH(DMI_##_class2, _name2),	\
	पूर्ण,						\
	.driver_data = &lis3lv02d_axis_##_axis		\
पूर्ण
अटल स्थिर काष्ठा dmi_प्रणाली_id lis3lv02d_dmi_ids[] = अणु
	/* product names are truncated to match all kinds of a same model */
	AXIS_DMI_MATCH("NC64x0", "HP Compaq nc64", x_inverted),
	AXIS_DMI_MATCH("NC84x0", "HP Compaq nc84", z_inverted),
	AXIS_DMI_MATCH("NX9420", "HP Compaq nx9420", x_inverted),
	AXIS_DMI_MATCH("NW9440", "HP Compaq nw9440", x_inverted),
	AXIS_DMI_MATCH("NC2510", "HP Compaq 2510", y_inverted),
	AXIS_DMI_MATCH("NC2710", "HP Compaq 2710", xy_swap),
	AXIS_DMI_MATCH("NC8510", "HP Compaq 8510", xy_swap_inverted),
	AXIS_DMI_MATCH("HP2133", "HP 2133", xy_rotated_left),
	AXIS_DMI_MATCH("HP2140", "HP 2140", xy_swap_inverted),
	AXIS_DMI_MATCH("NC653x", "HP Compaq 653", xy_rotated_left_usd),
	AXIS_DMI_MATCH("NC6730b", "HP Compaq 6730b", xy_rotated_left_usd),
	AXIS_DMI_MATCH("NC6730s", "HP Compaq 6730s", xy_swap),
	AXIS_DMI_MATCH("NC651xx", "HP Compaq 651", xy_rotated_right),
	AXIS_DMI_MATCH("NC6710x", "HP Compaq 6710", xy_swap_yz_inverted),
	AXIS_DMI_MATCH("NC6715x", "HP Compaq 6715", y_inverted),
	AXIS_DMI_MATCH("NC693xx", "HP EliteBook 693", xy_rotated_right),
	AXIS_DMI_MATCH("NC693xx", "HP EliteBook 853", xy_swap),
	AXIS_DMI_MATCH("NC854xx", "HP EliteBook 854", y_inverted),
	AXIS_DMI_MATCH("NC273xx", "HP EliteBook 273", y_inverted),
	/* Intel-based HP Pavilion dv5 */
	AXIS_DMI_MATCH2("HPDV5_I",
			PRODUCT_NAME, "HP Pavilion dv5",
			BOARD_NAME, "3603",
			x_inverted),
	/* AMD-based HP Pavilion dv5 */
	AXIS_DMI_MATCH2("HPDV5_A",
			PRODUCT_NAME, "HP Pavilion dv5",
			BOARD_NAME, "3600",
			y_inverted),
	AXIS_DMI_MATCH("DV7", "HP Pavilion dv7", x_inverted),
	AXIS_DMI_MATCH("HP8710", "HP Compaq 8710", y_inverted),
	AXIS_DMI_MATCH("HDX18", "HP HDX 18", x_inverted),
	AXIS_DMI_MATCH("HPB432x", "HP ProBook 432", xy_rotated_left),
	AXIS_DMI_MATCH("HPB440G3", "HP ProBook 440 G3", x_inverted_usd),
	AXIS_DMI_MATCH("HPB440G4", "HP ProBook 440 G4", x_inverted),
	AXIS_DMI_MATCH("HPB442x", "HP ProBook 442", xy_rotated_left),
	AXIS_DMI_MATCH("HPB450G0", "HP ProBook 450 G0", x_inverted),
	AXIS_DMI_MATCH("HPB452x", "HP ProBook 452", y_inverted),
	AXIS_DMI_MATCH("HPB522x", "HP ProBook 522", xy_swap),
	AXIS_DMI_MATCH("HPB532x", "HP ProBook 532", y_inverted),
	AXIS_DMI_MATCH("HPB655x", "HP ProBook 655", xy_swap_inverted),
	AXIS_DMI_MATCH("Mini510x", "HP Mini 510", xy_rotated_left_usd),
	AXIS_DMI_MATCH("HPB63xx", "HP ProBook 63", xy_swap),
	AXIS_DMI_MATCH("HPB64xx", "HP ProBook 64", xy_swap),
	AXIS_DMI_MATCH("HPB64xx", "HP EliteBook 84", xy_swap),
	AXIS_DMI_MATCH("HPB65xx", "HP ProBook 65", x_inverted),
	AXIS_DMI_MATCH("HPZBook15", "HP ZBook 15", x_inverted),
	AXIS_DMI_MATCH("HPZBook17G5", "HP ZBook 17 G5", x_inverted),
	AXIS_DMI_MATCH("HPZBook17", "HP ZBook 17", xy_swap_yz_inverted),
	अणु शून्य, पूर्ण
/* Laptop models without axis info (yet):
 * "NC6910" "HP Compaq 6910"
 * "NC2400" "HP Compaq nc2400"
 * "NX74x0" "HP Compaq nx74"
 * "NX6325" "HP Compaq nx6325"
 * "NC4400" "HP Compaq nc4400"
 */
पूर्ण;

अटल व्योम hpled_set(काष्ठा delayed_led_classdev *led_cdev, क्रमागत led_brightness value)
अणु
	काष्ठा acpi_device *dev = lis3_dev.bus_priv;
	अचिन्हित दीर्घ दीर्घ ret; /* Not used when writing */
	जोड़ acpi_object in_obj[1];
	काष्ठा acpi_object_list args = अणु 1, in_obj पूर्ण;

	in_obj[0].type          = ACPI_TYPE_INTEGER;
	in_obj[0].पूर्णांकeger.value = !!value;

	acpi_evaluate_पूर्णांकeger(dev->handle, "ALED", &args, &ret);
पूर्ण

अटल काष्ठा delayed_led_classdev hpled_led = अणु
	.led_classdev = अणु
		.name			= "hp::hddprotect",
		.शेष_trigger	= "none",
		.brightness_set		= delayed_sysfs_set,
		.flags                  = LED_CORE_SUSPENDRESUME,
	पूर्ण,
	.set_brightness = hpled_set,
पूर्ण;

अटल acpi_status
lis3lv02d_get_resource(काष्ठा acpi_resource *resource, व्योम *context)
अणु
	अगर (resource->type == ACPI_RESOURCE_TYPE_EXTENDED_IRQ) अणु
		काष्ठा acpi_resource_extended_irq *irq;
		u32 *device_irq = context;

		irq = &resource->data.extended_irq;
		*device_irq = irq->पूर्णांकerrupts[0];
	पूर्ण

	वापस AE_OK;
पूर्ण

अटल व्योम lis3lv02d_क्रमागत_resources(काष्ठा acpi_device *device)
अणु
	acpi_status status;

	status = acpi_walk_resources(device->handle, METHOD_NAME__CRS,
					lis3lv02d_get_resource, &lis3_dev.irq);
	अगर (ACPI_FAILURE(status))
		prपूर्णांकk(KERN_DEBUG DRIVER_NAME ": Error getting resources\n");
पूर्ण

अटल bool hp_accel_i8042_filter(अचिन्हित अक्षर data, अचिन्हित अक्षर str,
				  काष्ठा serio *port)
अणु
	अटल bool extended;

	अगर (str & I8042_STR_AUXDATA)
		वापस false;

	अगर (data == 0xe0) अणु
		extended = true;
		वापस true;
	पूर्ण अन्यथा अगर (unlikely(extended)) अणु
		extended = false;

		चयन (data) अणु
		हाल ACCEL_1:
		हाल ACCEL_2:
		हाल ACCEL_3:
		हाल ACCEL_4:
			वापस true;
		शेष:
			serio_पूर्णांकerrupt(port, 0xe0, 0);
			वापस false;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक lis3lv02d_add(काष्ठा acpi_device *device)
अणु
	पूर्णांक ret;

	अगर (!device)
		वापस -EINVAL;

	lis3_dev.bus_priv = device;
	lis3_dev.init = lis3lv02d_acpi_init;
	lis3_dev.पढ़ो = lis3lv02d_acpi_पढ़ो;
	lis3_dev.ग_लिखो = lis3lv02d_acpi_ग_लिखो;
	म_नकल(acpi_device_name(device), DRIVER_NAME);
	म_नकल(acpi_device_class(device), ACPI_MDPS_CLASS);
	device->driver_data = &lis3_dev;

	/* obtain IRQ number of our device from ACPI */
	lis3lv02d_क्रमागत_resources(device);

	/* If possible use a "standard" axes order */
	अगर (lis3_dev.ac.x && lis3_dev.ac.y && lis3_dev.ac.z) अणु
		pr_info("Using custom axes %d,%d,%d\n",
			lis3_dev.ac.x, lis3_dev.ac.y, lis3_dev.ac.z);
	पूर्ण अन्यथा अगर (dmi_check_प्रणाली(lis3lv02d_dmi_ids) == 0) अणु
		pr_info("laptop model unknown, using default axes configuration\n");
		lis3_dev.ac = lis3lv02d_axis_normal;
	पूर्ण

	/* call the core layer करो its init */
	lis3_dev.init_required = true;
	ret = lis3lv02d_init_device(&lis3_dev);
	अगर (ret)
		वापस ret;

	/* filter to हटाओ HPQ6000 accelerometer data
	 * from keyboard bus stream */
	अगर (म_माला(dev_name(&device->dev), "HPQ6000"))
		i8042_install_filter(hp_accel_i8042_filter);

	INIT_WORK(&hpled_led.work, delayed_set_status_worker);
	ret = led_classdev_रेजिस्टर(शून्य, &hpled_led.led_classdev);
	अगर (ret) अणु
		lis3lv02d_joystick_disable(&lis3_dev);
		lis3lv02d_घातeroff(&lis3_dev);
		flush_work(&hpled_led.work);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lis3lv02d_हटाओ(काष्ठा acpi_device *device)
अणु
	अगर (!device)
		वापस -EINVAL;

	i8042_हटाओ_filter(hp_accel_i8042_filter);
	lis3lv02d_joystick_disable(&lis3_dev);
	lis3lv02d_घातeroff(&lis3_dev);

	led_classdev_unरेजिस्टर(&hpled_led.led_classdev);
	flush_work(&hpled_led.work);

	वापस lis3lv02d_हटाओ_fs(&lis3_dev);
पूर्ण


#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक lis3lv02d_suspend(काष्ठा device *dev)
अणु
	/* make sure the device is off when we suspend */
	lis3lv02d_घातeroff(&lis3_dev);
	वापस 0;
पूर्ण

अटल पूर्णांक lis3lv02d_resume(काष्ठा device *dev)
अणु
	lis3_dev.init_required = false;
	lis3lv02d_घातeron(&lis3_dev);
	वापस 0;
पूर्ण

अटल पूर्णांक lis3lv02d_restore(काष्ठा device *dev)
अणु
	lis3_dev.init_required = true;
	lis3lv02d_घातeron(&lis3_dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops hp_accel_pm = अणु
	.suspend = lis3lv02d_suspend,
	.resume = lis3lv02d_resume,
	.मुक्तze = lis3lv02d_suspend,
	.thaw = lis3lv02d_resume,
	.घातeroff = lis3lv02d_suspend,
	.restore = lis3lv02d_restore,
पूर्ण;

#घोषणा HP_ACCEL_PM (&hp_accel_pm)
#अन्यथा
#घोषणा HP_ACCEL_PM शून्य
#पूर्ण_अगर

/* For the HP MDPS aka 3D Driveguard */
अटल काष्ठा acpi_driver lis3lv02d_driver = अणु
	.name  = DRIVER_NAME,
	.class = ACPI_MDPS_CLASS,
	.ids   = lis3lv02d_device_ids,
	.ops = अणु
		.add     = lis3lv02d_add,
		.हटाओ  = lis3lv02d_हटाओ,
	पूर्ण,
	.drv.pm = HP_ACCEL_PM,
पूर्ण;
module_acpi_driver(lis3lv02d_driver);

MODULE_DESCRIPTION("Glue between LIS3LV02Dx and HP ACPI BIOS and support for disk protection LED.");
MODULE_AUTHOR("Yan Burman, Eric Piel, Pavel Machek");
MODULE_LICENSE("GPL");
