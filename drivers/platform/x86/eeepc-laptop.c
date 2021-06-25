<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  eeepc-laptop.c - Asus Eee PC extras
 *
 *  Based on asus_acpi.c as patched क्रम the Eee PC by Asus:
 *  ftp://ftp.asus.com/pub/ASUS/EeePC/701/ASUS_ACPI_071126.rar
 *  Based on eee.c from eeepc-linux
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/backlight.h>
#समावेश <linux/fb.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/leds.h>
#समावेश <linux/dmi.h>
#समावेश <acpi/video.h>

#घोषणा EEEPC_LAPTOP_VERSION	"0.1"
#घोषणा EEEPC_LAPTOP_NAME	"Eee PC Hotkey Driver"
#घोषणा EEEPC_LAPTOP_खाता	"eeepc"

#घोषणा EEEPC_ACPI_CLASS	"hotkey"
#घोषणा EEEPC_ACPI_DEVICE_NAME	"Hotkey"
#घोषणा EEEPC_ACPI_HID		"ASUS010"

MODULE_AUTHOR("Corentin Chary, Eric Cooper");
MODULE_DESCRIPTION(EEEPC_LAPTOP_NAME);
MODULE_LICENSE("GPL");

अटल bool hotplug_disabled;

module_param(hotplug_disabled, bool, 0444);
MODULE_PARM_DESC(hotplug_disabled,
		 "Disable hotplug for wireless device. "
		 "If your laptop need that, please report to "
		 "acpi4asus-user@lists.sourceforge.net.");

/*
 * Definitions क्रम Asus EeePC
 */
#घोषणा NOTIFY_BRN_MIN	0x20
#घोषणा NOTIFY_BRN_MAX	0x2f

क्रमागत अणु
	DISABLE_ASL_WLAN = 0x0001,
	DISABLE_ASL_BLUETOOTH = 0x0002,
	DISABLE_ASL_IRDA = 0x0004,
	DISABLE_ASL_CAMERA = 0x0008,
	DISABLE_ASL_TV = 0x0010,
	DISABLE_ASL_GPS = 0x0020,
	DISABLE_ASL_DISPLAYSWITCH = 0x0040,
	DISABLE_ASL_MODEM = 0x0080,
	DISABLE_ASL_CARDREADER = 0x0100,
	DISABLE_ASL_3G = 0x0200,
	DISABLE_ASL_WIMAX = 0x0400,
	DISABLE_ASL_HWCF = 0x0800
पूर्ण;

क्रमागत अणु
	CM_ASL_WLAN = 0,
	CM_ASL_BLUETOOTH,
	CM_ASL_IRDA,
	CM_ASL_1394,
	CM_ASL_CAMERA,
	CM_ASL_TV,
	CM_ASL_GPS,
	CM_ASL_DVDROM,
	CM_ASL_DISPLAYSWITCH,
	CM_ASL_PANELBRIGHT,
	CM_ASL_BIOSFLASH,
	CM_ASL_ACPIFLASH,
	CM_ASL_CPUFV,
	CM_ASL_CPUTEMPERATURE,
	CM_ASL_FANCPU,
	CM_ASL_FANCHASSIS,
	CM_ASL_USBPORT1,
	CM_ASL_USBPORT2,
	CM_ASL_USBPORT3,
	CM_ASL_MODEM,
	CM_ASL_CARDREADER,
	CM_ASL_3G,
	CM_ASL_WIMAX,
	CM_ASL_HWCF,
	CM_ASL_LID,
	CM_ASL_TYPE,
	CM_ASL_PANELPOWER,	/*P901*/
	CM_ASL_TPD
पूर्ण;

अटल स्थिर अक्षर *cm_getv[] = अणु
	"WLDG", "BTHG", शून्य, शून्य,
	"CAMG", शून्य, शून्य, शून्य,
	शून्य, "PBLG", शून्य, शून्य,
	"CFVG", शून्य, शून्य, शून्य,
	"USBG", शून्य, शून्य, "MODG",
	"CRDG", "M3GG", "WIMG", "HWCF",
	"LIDG",	"TYPE", "PBPG",	"TPDG"
पूर्ण;

अटल स्थिर अक्षर *cm_setv[] = अणु
	"WLDS", "BTHS", शून्य, शून्य,
	"CAMS", शून्य, शून्य, शून्य,
	"SDSP", "PBLS", "HDPS", शून्य,
	"CFVS", शून्य, शून्य, शून्य,
	"USBG", शून्य, शून्य, "MODS",
	"CRDS", "M3GS", "WIMS", शून्य,
	शून्य, शून्य, "PBPS", "TPDS"
पूर्ण;

अटल स्थिर काष्ठा key_entry eeepc_keymap[] = अणु
	अणु KE_KEY, 0x10, अणु KEY_WLAN पूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणु KEY_WLAN पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणु KEY_PROG1 पूर्ण पूर्ण,
	अणु KE_KEY, 0x13, अणु KEY_MUTE पूर्ण पूर्ण,
	अणु KE_KEY, 0x14, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,
	अणु KE_KEY, 0x15, अणु KEY_VOLUMEUP पूर्ण पूर्ण,
	अणु KE_KEY, 0x16, अणु KEY_DISPLAY_OFF पूर्ण पूर्ण,
	अणु KE_KEY, 0x1a, अणु KEY_COFFEE पूर्ण पूर्ण,
	अणु KE_KEY, 0x1b, अणु KEY_ZOOM पूर्ण पूर्ण,
	अणु KE_KEY, 0x1c, अणु KEY_PROG2 पूर्ण पूर्ण,
	अणु KE_KEY, 0x1d, अणु KEY_PROG3 पूर्ण पूर्ण,
	अणु KE_KEY, NOTIFY_BRN_MIN, अणु KEY_BRIGHTNESSDOWN पूर्ण पूर्ण,
	अणु KE_KEY, NOTIFY_BRN_MAX, अणु KEY_BRIGHTNESSUP पूर्ण पूर्ण,
	अणु KE_KEY, 0x30, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण,
	अणु KE_KEY, 0x32, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण,
	अणु KE_KEY, 0x37, अणु KEY_F13 पूर्ण पूर्ण, /* Disable Touchpad */
	अणु KE_KEY, 0x38, अणु KEY_F14 पूर्ण पूर्ण,
	अणु KE_IGNORE, 0x50, अणु KEY_RESERVED पूर्ण पूर्ण, /* AC plugged */
	अणु KE_IGNORE, 0x51, अणु KEY_RESERVED पूर्ण पूर्ण, /* AC unplugged */
	अणु KE_END, 0 पूर्ण,
पूर्ण;

/*
 * This is the मुख्य काष्ठाure, we can use it to store useful inक्रमmation
 */
काष्ठा eeepc_laptop अणु
	acpi_handle handle;		/* the handle of the acpi device */
	u32 cm_supported;		/* the control methods supported
					   by this BIOS */
	bool cpufv_disabled;
	bool hotplug_disabled;
	u16 event_count[128];		/* count क्रम each event */

	काष्ठा platक्रमm_device *platक्रमm_device;
	काष्ठा acpi_device *device;		/* the device we are in */
	काष्ठा backlight_device *backlight_device;

	काष्ठा input_dev *inputdev;

	काष्ठा rfसमाप्त *wlan_rfसमाप्त;
	काष्ठा rfसमाप्त *bluetooth_rfसमाप्त;
	काष्ठा rfसमाप्त *wwan3g_rfसमाप्त;
	काष्ठा rfसमाप्त *wimax_rfसमाप्त;

	काष्ठा hotplug_slot hotplug_slot;
	काष्ठा mutex hotplug_lock;

	काष्ठा led_classdev tpd_led;
	पूर्णांक tpd_led_wk;
	काष्ठा workqueue_काष्ठा *led_workqueue;
	काष्ठा work_काष्ठा tpd_led_work;
पूर्ण;

/*
 * ACPI Helpers
 */
अटल पूर्णांक ग_लिखो_acpi_पूर्णांक(acpi_handle handle, स्थिर अक्षर *method, पूर्णांक val)
अणु
	acpi_status status;

	status = acpi_execute_simple_method(handle, (अक्षर *)method, val);

	वापस (status == AE_OK ? 0 : -1);
पूर्ण

अटल पूर्णांक पढ़ो_acpi_पूर्णांक(acpi_handle handle, स्थिर अक्षर *method, पूर्णांक *val)
अणु
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ result;

	status = acpi_evaluate_पूर्णांकeger(handle, (अक्षर *)method, शून्य, &result);
	अगर (ACPI_FAILURE(status)) अणु
		*val = -1;
		वापस -1;
	पूर्ण अन्यथा अणु
		*val = result;
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक set_acpi(काष्ठा eeepc_laptop *eeepc, पूर्णांक cm, पूर्णांक value)
अणु
	स्थिर अक्षर *method = cm_setv[cm];

	अगर (method == शून्य)
		वापस -ENODEV;
	अगर ((eeepc->cm_supported & (0x1 << cm)) == 0)
		वापस -ENODEV;

	अगर (ग_लिखो_acpi_पूर्णांक(eeepc->handle, method, value))
		pr_warn("Error writing %s\n", method);
	वापस 0;
पूर्ण

अटल पूर्णांक get_acpi(काष्ठा eeepc_laptop *eeepc, पूर्णांक cm)
अणु
	स्थिर अक्षर *method = cm_getv[cm];
	पूर्णांक value;

	अगर (method == शून्य)
		वापस -ENODEV;
	अगर ((eeepc->cm_supported & (0x1 << cm)) == 0)
		वापस -ENODEV;

	अगर (पढ़ो_acpi_पूर्णांक(eeepc->handle, method, &value))
		pr_warn("Error reading %s\n", method);
	वापस value;
पूर्ण

अटल पूर्णांक acpi_setter_handle(काष्ठा eeepc_laptop *eeepc, पूर्णांक cm,
			      acpi_handle *handle)
अणु
	स्थिर अक्षर *method = cm_setv[cm];
	acpi_status status;

	अगर (method == शून्य)
		वापस -ENODEV;
	अगर ((eeepc->cm_supported & (0x1 << cm)) == 0)
		वापस -ENODEV;

	status = acpi_get_handle(eeepc->handle, (अक्षर *)method,
				 handle);
	अगर (status != AE_OK) अणु
		pr_warn("Error finding %s\n", method);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * Sys helpers
 */
अटल पूर्णांक parse_arg(स्थिर अक्षर *buf, पूर्णांक *val)
अणु
	अगर (माला_पूछो(buf, "%i", val) != 1)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार store_sys_acpi(काष्ठा device *dev, पूर्णांक cm,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा eeepc_laptop *eeepc = dev_get_drvdata(dev);
	पूर्णांक rv, value;

	rv = parse_arg(buf, &value);
	अगर (rv < 0)
		वापस rv;
	rv = set_acpi(eeepc, cm, value);
	अगर (rv < 0)
		वापस -EIO;
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_sys_acpi(काष्ठा device *dev, पूर्णांक cm, अक्षर *buf)
अणु
	काष्ठा eeepc_laptop *eeepc = dev_get_drvdata(dev);
	पूर्णांक value = get_acpi(eeepc, cm);

	अगर (value < 0)
		वापस -EIO;
	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

#घोषणा EEEPC_ACPI_SHOW_FUNC(_name, _cm)				\
	अटल sमाप_प्रकार _name##_show(काष्ठा device *dev,			\
				    काष्ठा device_attribute *attr,	\
				    अक्षर *buf)				\
	अणु								\
		वापस show_sys_acpi(dev, _cm, buf);			\
	पूर्ण

#घोषणा EEEPC_ACPI_STORE_FUNC(_name, _cm)				\
	अटल sमाप_प्रकार _name##_store(काष्ठा device *dev,		\
				     काष्ठा device_attribute *attr,	\
				     स्थिर अक्षर *buf, माप_प्रकार count)	\
	अणु								\
		वापस store_sys_acpi(dev, _cm, buf, count);		\
	पूर्ण

#घोषणा EEEPC_CREATE_DEVICE_ATTR_RW(_name, _cm)				\
	EEEPC_ACPI_SHOW_FUNC(_name, _cm)				\
	EEEPC_ACPI_STORE_FUNC(_name, _cm)				\
	अटल DEVICE_ATTR_RW(_name)

#घोषणा EEEPC_CREATE_DEVICE_ATTR_WO(_name, _cm)				\
	EEEPC_ACPI_STORE_FUNC(_name, _cm)				\
	अटल DEVICE_ATTR_WO(_name)

EEEPC_CREATE_DEVICE_ATTR_RW(camera, CM_ASL_CAMERA);
EEEPC_CREATE_DEVICE_ATTR_RW(cardr, CM_ASL_CARDREADER);
EEEPC_CREATE_DEVICE_ATTR_WO(disp, CM_ASL_DISPLAYSWITCH);

काष्ठा eeepc_cpufv अणु
	पूर्णांक num;
	पूर्णांक cur;
पूर्ण;

अटल पूर्णांक get_cpufv(काष्ठा eeepc_laptop *eeepc, काष्ठा eeepc_cpufv *c)
अणु
	c->cur = get_acpi(eeepc, CM_ASL_CPUFV);
	अगर (c->cur < 0)
		वापस -ENODEV;

	c->num = (c->cur >> 8) & 0xff;
	c->cur &= 0xff;
	अगर (c->num == 0 || c->num > 12)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार available_cpufv_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा eeepc_laptop *eeepc = dev_get_drvdata(dev);
	काष्ठा eeepc_cpufv c;
	पूर्णांक i;
	sमाप_प्रकार len = 0;

	अगर (get_cpufv(eeepc, &c))
		वापस -ENODEV;
	क्रम (i = 0; i < c.num; i++)
		len += प्र_लिखो(buf + len, "%d ", i);
	len += प्र_लिखो(buf + len, "\n");
	वापस len;
पूर्ण

अटल sमाप_प्रकार cpufv_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा eeepc_laptop *eeepc = dev_get_drvdata(dev);
	काष्ठा eeepc_cpufv c;

	अगर (get_cpufv(eeepc, &c))
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%#x\n", (c.num << 8) | c.cur);
पूर्ण

अटल sमाप_प्रकार cpufv_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा eeepc_laptop *eeepc = dev_get_drvdata(dev);
	काष्ठा eeepc_cpufv c;
	पूर्णांक rv, value;

	अगर (eeepc->cpufv_disabled)
		वापस -EPERM;
	अगर (get_cpufv(eeepc, &c))
		वापस -ENODEV;
	rv = parse_arg(buf, &value);
	अगर (rv < 0)
		वापस rv;
	अगर (value < 0 || value >= c.num)
		वापस -EINVAL;
	rv = set_acpi(eeepc, CM_ASL_CPUFV, value);
	अगर (rv)
		वापस rv;
	वापस count;
पूर्ण

अटल sमाप_प्रकार cpufv_disabled_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा eeepc_laptop *eeepc = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", eeepc->cpufv_disabled);
पूर्ण

अटल sमाप_प्रकार cpufv_disabled_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा eeepc_laptop *eeepc = dev_get_drvdata(dev);
	पूर्णांक rv, value;

	rv = parse_arg(buf, &value);
	अगर (rv < 0)
		वापस rv;

	चयन (value) अणु
	हाल 0:
		अगर (eeepc->cpufv_disabled)
			pr_warn("cpufv enabled (not officially supported on this model)\n");
		eeepc->cpufv_disabled = false;
		वापस count;
	हाल 1:
		वापस -EPERM;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण


अटल DEVICE_ATTR_RW(cpufv);
अटल DEVICE_ATTR_RO(available_cpufv);
अटल DEVICE_ATTR_RW(cpufv_disabled);

अटल काष्ठा attribute *platक्रमm_attributes[] = अणु
	&dev_attr_camera.attr,
	&dev_attr_cardr.attr,
	&dev_attr_disp.attr,
	&dev_attr_cpufv.attr,
	&dev_attr_available_cpufv.attr,
	&dev_attr_cpufv_disabled.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group platक्रमm_attribute_group = अणु
	.attrs = platक्रमm_attributes
पूर्ण;

अटल पूर्णांक eeepc_platक्रमm_init(काष्ठा eeepc_laptop *eeepc)
अणु
	पूर्णांक result;

	eeepc->platक्रमm_device = platक्रमm_device_alloc(EEEPC_LAPTOP_खाता, -1);
	अगर (!eeepc->platक्रमm_device)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(eeepc->platक्रमm_device, eeepc);

	result = platक्रमm_device_add(eeepc->platक्रमm_device);
	अगर (result)
		जाओ fail_platक्रमm_device;

	result = sysfs_create_group(&eeepc->platक्रमm_device->dev.kobj,
				    &platक्रमm_attribute_group);
	अगर (result)
		जाओ fail_sysfs;
	वापस 0;

fail_sysfs:
	platक्रमm_device_del(eeepc->platक्रमm_device);
fail_platक्रमm_device:
	platक्रमm_device_put(eeepc->platक्रमm_device);
	वापस result;
पूर्ण

अटल व्योम eeepc_platक्रमm_निकास(काष्ठा eeepc_laptop *eeepc)
अणु
	sysfs_हटाओ_group(&eeepc->platक्रमm_device->dev.kobj,
			   &platक्रमm_attribute_group);
	platक्रमm_device_unरेजिस्टर(eeepc->platक्रमm_device);
पूर्ण

/*
 * LEDs
 */
/*
 * These functions actually update the LED's, and are called from a
 * workqueue. By करोing this as separate work rather than when the LED
 * subप्रणाली asks, we aव्योम messing with the Asus ACPI stuff during a
 * potentially bad समय, such as a समयr पूर्णांकerrupt.
 */
अटल व्योम tpd_led_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा eeepc_laptop *eeepc;

	eeepc = container_of(work, काष्ठा eeepc_laptop, tpd_led_work);

	set_acpi(eeepc, CM_ASL_TPD, eeepc->tpd_led_wk);
पूर्ण

अटल व्योम tpd_led_set(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness value)
अणु
	काष्ठा eeepc_laptop *eeepc;

	eeepc = container_of(led_cdev, काष्ठा eeepc_laptop, tpd_led);

	eeepc->tpd_led_wk = (value > 0) ? 1 : 0;
	queue_work(eeepc->led_workqueue, &eeepc->tpd_led_work);
पूर्ण

अटल क्रमागत led_brightness tpd_led_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा eeepc_laptop *eeepc;

	eeepc = container_of(led_cdev, काष्ठा eeepc_laptop, tpd_led);

	वापस get_acpi(eeepc, CM_ASL_TPD);
पूर्ण

अटल पूर्णांक eeepc_led_init(काष्ठा eeepc_laptop *eeepc)
अणु
	पूर्णांक rv;

	अगर (get_acpi(eeepc, CM_ASL_TPD) == -ENODEV)
		वापस 0;

	eeepc->led_workqueue = create_singlethपढ़ो_workqueue("led_workqueue");
	अगर (!eeepc->led_workqueue)
		वापस -ENOMEM;
	INIT_WORK(&eeepc->tpd_led_work, tpd_led_update);

	eeepc->tpd_led.name = "eeepc::touchpad";
	eeepc->tpd_led.brightness_set = tpd_led_set;
	अगर (get_acpi(eeepc, CM_ASL_TPD) >= 0) /* अगर method is available */
		eeepc->tpd_led.brightness_get = tpd_led_get;
	eeepc->tpd_led.max_brightness = 1;

	rv = led_classdev_रेजिस्टर(&eeepc->platक्रमm_device->dev,
				   &eeepc->tpd_led);
	अगर (rv) अणु
		destroy_workqueue(eeepc->led_workqueue);
		वापस rv;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम eeepc_led_निकास(काष्ठा eeepc_laptop *eeepc)
अणु
	led_classdev_unरेजिस्टर(&eeepc->tpd_led);
	अगर (eeepc->led_workqueue)
		destroy_workqueue(eeepc->led_workqueue);
पूर्ण

/*
 * PCI hotplug (क्रम wlan rfसमाप्त)
 */
अटल bool eeepc_wlan_rfसमाप्त_blocked(काष्ठा eeepc_laptop *eeepc)
अणु
	अगर (get_acpi(eeepc, CM_ASL_WLAN) == 1)
		वापस false;
	वापस true;
पूर्ण

अटल व्योम eeepc_rfसमाप्त_hotplug(काष्ठा eeepc_laptop *eeepc, acpi_handle handle)
अणु
	काष्ठा pci_dev *port;
	काष्ठा pci_dev *dev;
	काष्ठा pci_bus *bus;
	bool blocked = eeepc_wlan_rfसमाप्त_blocked(eeepc);
	bool असलent;
	u32 l;

	अगर (eeepc->wlan_rfसमाप्त)
		rfसमाप्त_set_sw_state(eeepc->wlan_rfसमाप्त, blocked);

	mutex_lock(&eeepc->hotplug_lock);
	pci_lock_rescan_हटाओ();

	अगर (!eeepc->hotplug_slot.ops)
		जाओ out_unlock;

	port = acpi_get_pci_dev(handle);
	अगर (!port) अणु
		pr_warn("Unable to find port\n");
		जाओ out_unlock;
	पूर्ण

	bus = port->subordinate;

	अगर (!bus) अणु
		pr_warn("Unable to find PCI bus 1?\n");
		जाओ out_put_dev;
	पूर्ण

	अगर (pci_bus_पढ़ो_config_dword(bus, 0, PCI_VENDOR_ID, &l)) अणु
		pr_err("Unable to read PCI config space?\n");
		जाओ out_put_dev;
	पूर्ण

	असलent = (l == 0xffffffff);

	अगर (blocked != असलent) अणु
		pr_warn("BIOS says wireless lan is %s, but the pci device is %s\n",
			blocked ? "blocked" : "unblocked",
			असलent ? "absent" : "present");
		pr_warn("skipped wireless hotplug as probably inappropriate for this model\n");
		जाओ out_put_dev;
	पूर्ण

	अगर (!blocked) अणु
		dev = pci_get_slot(bus, 0);
		अगर (dev) अणु
			/* Device alपढ़ोy present */
			pci_dev_put(dev);
			जाओ out_put_dev;
		पूर्ण
		dev = pci_scan_single_device(bus, 0);
		अगर (dev) अणु
			pci_bus_assign_resources(bus);
			pci_bus_add_device(dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev = pci_get_slot(bus, 0);
		अगर (dev) अणु
			pci_stop_and_हटाओ_bus_device(dev);
			pci_dev_put(dev);
		पूर्ण
	पूर्ण
out_put_dev:
	pci_dev_put(port);

out_unlock:
	pci_unlock_rescan_हटाओ();
	mutex_unlock(&eeepc->hotplug_lock);
पूर्ण

अटल व्योम eeepc_rfसमाप्त_hotplug_update(काष्ठा eeepc_laptop *eeepc, अक्षर *node)
अणु
	acpi_status status = AE_OK;
	acpi_handle handle;

	status = acpi_get_handle(शून्य, node, &handle);

	अगर (ACPI_SUCCESS(status))
		eeepc_rfसमाप्त_hotplug(eeepc, handle);
पूर्ण

अटल व्योम eeepc_rfसमाप्त_notअगरy(acpi_handle handle, u32 event, व्योम *data)
अणु
	काष्ठा eeepc_laptop *eeepc = data;

	अगर (event != ACPI_NOTIFY_BUS_CHECK)
		वापस;

	eeepc_rfसमाप्त_hotplug(eeepc, handle);
पूर्ण

अटल पूर्णांक eeepc_रेजिस्टर_rfसमाप्त_notअगरier(काष्ठा eeepc_laptop *eeepc,
					  अक्षर *node)
अणु
	acpi_status status;
	acpi_handle handle;

	status = acpi_get_handle(शून्य, node, &handle);

	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	status = acpi_install_notअगरy_handler(handle,
					     ACPI_SYSTEM_NOTIFY,
					     eeepc_rfसमाप्त_notअगरy,
					     eeepc);
	अगर (ACPI_FAILURE(status))
		pr_warn("Failed to register notify on %s\n", node);

	/*
	 * Refresh pci hotplug in हाल the rfसमाप्त state was
	 * changed during setup.
	 */
	eeepc_rfसमाप्त_hotplug(eeepc, handle);
	वापस 0;
पूर्ण

अटल व्योम eeepc_unरेजिस्टर_rfसमाप्त_notअगरier(काष्ठा eeepc_laptop *eeepc,
					     अक्षर *node)
अणु
	acpi_status status = AE_OK;
	acpi_handle handle;

	status = acpi_get_handle(शून्य, node, &handle);

	अगर (ACPI_FAILURE(status))
		वापस;

	status = acpi_हटाओ_notअगरy_handler(handle,
					     ACPI_SYSTEM_NOTIFY,
					     eeepc_rfसमाप्त_notअगरy);
	अगर (ACPI_FAILURE(status))
		pr_err("Error removing rfkill notify handler %s\n",
			node);
		/*
		 * Refresh pci hotplug in हाल the rfसमाप्त
		 * state was changed after
		 * eeepc_unरेजिस्टर_rfसमाप्त_notअगरier()
		 */
	eeepc_rfसमाप्त_hotplug(eeepc, handle);
पूर्ण

अटल पूर्णांक eeepc_get_adapter_status(काष्ठा hotplug_slot *hotplug_slot,
				    u8 *value)
अणु
	काष्ठा eeepc_laptop *eeepc;
	पूर्णांक val;

	eeepc = container_of(hotplug_slot, काष्ठा eeepc_laptop, hotplug_slot);
	val = get_acpi(eeepc, CM_ASL_WLAN);

	अगर (val == 1 || val == 0)
		*value = val;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hotplug_slot_ops eeepc_hotplug_slot_ops = अणु
	.get_adapter_status = eeepc_get_adapter_status,
	.get_घातer_status = eeepc_get_adapter_status,
पूर्ण;

अटल पूर्णांक eeepc_setup_pci_hotplug(काष्ठा eeepc_laptop *eeepc)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा pci_bus *bus = pci_find_bus(0, 1);

	अगर (!bus) अणु
		pr_err("Unable to find wifi PCI bus\n");
		वापस -ENODEV;
	पूर्ण

	eeepc->hotplug_slot.ops = &eeepc_hotplug_slot_ops;

	ret = pci_hp_रेजिस्टर(&eeepc->hotplug_slot, bus, 0, "eeepc-wifi");
	अगर (ret) अणु
		pr_err("Unable to register hotplug slot - %d\n", ret);
		जाओ error_रेजिस्टर;
	पूर्ण

	वापस 0;

error_रेजिस्टर:
	eeepc->hotplug_slot.ops = शून्य;
	वापस ret;
पूर्ण

/*
 * Rfसमाप्त devices
 */
अटल पूर्णांक eeepc_rfसमाप्त_set(व्योम *data, bool blocked)
अणु
	acpi_handle handle = data;

	वापस ग_लिखो_acpi_पूर्णांक(handle, शून्य, !blocked);
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops eeepc_rfसमाप्त_ops = अणु
	.set_block = eeepc_rfसमाप्त_set,
पूर्ण;

अटल पूर्णांक eeepc_new_rfसमाप्त(काष्ठा eeepc_laptop *eeepc,
			    काष्ठा rfसमाप्त **rfसमाप्त,
			    स्थिर अक्षर *name,
			    क्रमागत rfसमाप्त_type type, पूर्णांक cm)
अणु
	acpi_handle handle;
	पूर्णांक result;

	result = acpi_setter_handle(eeepc, cm, &handle);
	अगर (result < 0)
		वापस result;

	*rfसमाप्त = rfसमाप्त_alloc(name, &eeepc->platक्रमm_device->dev, type,
			       &eeepc_rfसमाप्त_ops, handle);

	अगर (!*rfसमाप्त)
		वापस -EINVAL;

	rfसमाप्त_init_sw_state(*rfसमाप्त, get_acpi(eeepc, cm) != 1);
	result = rfसमाप्त_रेजिस्टर(*rfसमाप्त);
	अगर (result) अणु
		rfसमाप्त_destroy(*rfसमाप्त);
		*rfसमाप्त = शून्य;
		वापस result;
	पूर्ण
	वापस 0;
पूर्ण

अटल अक्षर EEEPC_RFKILL_NODE_1[] = "\\_SB.PCI0.P0P5";
अटल अक्षर EEEPC_RFKILL_NODE_2[] = "\\_SB.PCI0.P0P6";
अटल अक्षर EEEPC_RFKILL_NODE_3[] = "\\_SB.PCI0.P0P7";

अटल व्योम eeepc_rfसमाप्त_निकास(काष्ठा eeepc_laptop *eeepc)
अणु
	eeepc_unरेजिस्टर_rfसमाप्त_notअगरier(eeepc, EEEPC_RFKILL_NODE_1);
	eeepc_unरेजिस्टर_rfसमाप्त_notअगरier(eeepc, EEEPC_RFKILL_NODE_2);
	eeepc_unरेजिस्टर_rfसमाप्त_notअगरier(eeepc, EEEPC_RFKILL_NODE_3);
	अगर (eeepc->wlan_rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(eeepc->wlan_rfसमाप्त);
		rfसमाप्त_destroy(eeepc->wlan_rfसमाप्त);
		eeepc->wlan_rfसमाप्त = शून्य;
	पूर्ण

	अगर (eeepc->hotplug_slot.ops)
		pci_hp_deरेजिस्टर(&eeepc->hotplug_slot);

	अगर (eeepc->bluetooth_rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(eeepc->bluetooth_rfसमाप्त);
		rfसमाप्त_destroy(eeepc->bluetooth_rfसमाप्त);
		eeepc->bluetooth_rfसमाप्त = शून्य;
	पूर्ण
	अगर (eeepc->wwan3g_rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(eeepc->wwan3g_rfसमाप्त);
		rfसमाप्त_destroy(eeepc->wwan3g_rfसमाप्त);
		eeepc->wwan3g_rfसमाप्त = शून्य;
	पूर्ण
	अगर (eeepc->wimax_rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(eeepc->wimax_rfसमाप्त);
		rfसमाप्त_destroy(eeepc->wimax_rfसमाप्त);
		eeepc->wimax_rfसमाप्त = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक eeepc_rfसमाप्त_init(काष्ठा eeepc_laptop *eeepc)
अणु
	पूर्णांक result = 0;

	mutex_init(&eeepc->hotplug_lock);

	result = eeepc_new_rfसमाप्त(eeepc, &eeepc->wlan_rfसमाप्त,
				  "eeepc-wlan", RFKILL_TYPE_WLAN,
				  CM_ASL_WLAN);

	अगर (result && result != -ENODEV)
		जाओ निकास;

	result = eeepc_new_rfसमाप्त(eeepc, &eeepc->bluetooth_rfसमाप्त,
				  "eeepc-bluetooth", RFKILL_TYPE_BLUETOOTH,
				  CM_ASL_BLUETOOTH);

	अगर (result && result != -ENODEV)
		जाओ निकास;

	result = eeepc_new_rfसमाप्त(eeepc, &eeepc->wwan3g_rfसमाप्त,
				  "eeepc-wwan3g", RFKILL_TYPE_WWAN,
				  CM_ASL_3G);

	अगर (result && result != -ENODEV)
		जाओ निकास;

	result = eeepc_new_rfसमाप्त(eeepc, &eeepc->wimax_rfसमाप्त,
				  "eeepc-wimax", RFKILL_TYPE_WIMAX,
				  CM_ASL_WIMAX);

	अगर (result && result != -ENODEV)
		जाओ निकास;

	अगर (eeepc->hotplug_disabled)
		वापस 0;

	result = eeepc_setup_pci_hotplug(eeepc);
	/*
	 * If we get -EBUSY then something अन्यथा is handling the PCI hotplug -
	 * करोn't fail in this हाल
	 */
	अगर (result == -EBUSY)
		result = 0;

	eeepc_रेजिस्टर_rfसमाप्त_notअगरier(eeepc, EEEPC_RFKILL_NODE_1);
	eeepc_रेजिस्टर_rfसमाप्त_notअगरier(eeepc, EEEPC_RFKILL_NODE_2);
	eeepc_रेजिस्टर_rfसमाप्त_notअगरier(eeepc, EEEPC_RFKILL_NODE_3);

निकास:
	अगर (result && result != -ENODEV)
		eeepc_rfसमाप्त_निकास(eeepc);
	वापस result;
पूर्ण

/*
 * Platक्रमm driver - hibernate/resume callbacks
 */
अटल पूर्णांक eeepc_hotk_thaw(काष्ठा device *device)
अणु
	काष्ठा eeepc_laptop *eeepc = dev_get_drvdata(device);

	अगर (eeepc->wlan_rfसमाप्त) अणु
		पूर्णांक wlan;

		/*
		 * Work around bios bug - acpi _PTS turns off the wireless led
		 * during suspend.  Normally it restores it on resume, but
		 * we should kick it ourselves in हाल hibernation is पातed.
		 */
		wlan = get_acpi(eeepc, CM_ASL_WLAN);
		अगर (wlan >= 0)
			set_acpi(eeepc, CM_ASL_WLAN, wlan);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक eeepc_hotk_restore(काष्ठा device *device)
अणु
	काष्ठा eeepc_laptop *eeepc = dev_get_drvdata(device);

	/* Refresh both wlan rfसमाप्त state and pci hotplug */
	अगर (eeepc->wlan_rfसमाप्त) अणु
		eeepc_rfसमाप्त_hotplug_update(eeepc, EEEPC_RFKILL_NODE_1);
		eeepc_rfसमाप्त_hotplug_update(eeepc, EEEPC_RFKILL_NODE_2);
		eeepc_rfसमाप्त_hotplug_update(eeepc, EEEPC_RFKILL_NODE_3);
	पूर्ण

	अगर (eeepc->bluetooth_rfसमाप्त)
		rfसमाप्त_set_sw_state(eeepc->bluetooth_rfसमाप्त,
				    get_acpi(eeepc, CM_ASL_BLUETOOTH) != 1);
	अगर (eeepc->wwan3g_rfसमाप्त)
		rfसमाप्त_set_sw_state(eeepc->wwan3g_rfसमाप्त,
				    get_acpi(eeepc, CM_ASL_3G) != 1);
	अगर (eeepc->wimax_rfसमाप्त)
		rfसमाप्त_set_sw_state(eeepc->wimax_rfसमाप्त,
				    get_acpi(eeepc, CM_ASL_WIMAX) != 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops eeepc_pm_ops = अणु
	.thaw = eeepc_hotk_thaw,
	.restore = eeepc_hotk_restore,
पूर्ण;

अटल काष्ठा platक्रमm_driver platक्रमm_driver = अणु
	.driver = अणु
		.name = EEEPC_LAPTOP_खाता,
		.pm = &eeepc_pm_ops,
	पूर्ण
पूर्ण;

/*
 * Hwmon device
 */

#घोषणा EEEPC_EC_SC00      0x61
#घोषणा EEEPC_EC_FAN_PWM   (EEEPC_EC_SC00 + 2) /* Fan PWM duty cycle (%) */
#घोषणा EEEPC_EC_FAN_HRPM  (EEEPC_EC_SC00 + 5) /* High byte, fan speed (RPM) */
#घोषणा EEEPC_EC_FAN_LRPM  (EEEPC_EC_SC00 + 6) /* Low byte, fan speed (RPM) */

#घोषणा EEEPC_EC_SFB0      0xD0
#घोषणा EEEPC_EC_FAN_CTRL  (EEEPC_EC_SFB0 + 3) /* Byte containing SF25  */

अटल अंतरभूत पूर्णांक eeepc_pwm_to_lmsensors(पूर्णांक value)
अणु
	वापस value * 255 / 100;
पूर्ण

अटल अंतरभूत पूर्णांक eeepc_lmsensors_to_pwm(पूर्णांक value)
अणु
	value = clamp_val(value, 0, 255);
	वापस value * 100 / 255;
पूर्ण

अटल पूर्णांक eeepc_get_fan_pwm(व्योम)
अणु
	u8 value = 0;

	ec_पढ़ो(EEEPC_EC_FAN_PWM, &value);
	वापस eeepc_pwm_to_lmsensors(value);
पूर्ण

अटल व्योम eeepc_set_fan_pwm(पूर्णांक value)
अणु
	value = eeepc_lmsensors_to_pwm(value);
	ec_ग_लिखो(EEEPC_EC_FAN_PWM, value);
पूर्ण

अटल पूर्णांक eeepc_get_fan_rpm(व्योम)
अणु
	u8 high = 0;
	u8 low = 0;

	ec_पढ़ो(EEEPC_EC_FAN_HRPM, &high);
	ec_पढ़ो(EEEPC_EC_FAN_LRPM, &low);
	वापस high << 8 | low;
पूर्ण

#घोषणा EEEPC_EC_FAN_CTRL_BIT	0x02
#घोषणा EEEPC_FAN_CTRL_MANUAL	1
#घोषणा EEEPC_FAN_CTRL_AUTO	2

अटल पूर्णांक eeepc_get_fan_ctrl(व्योम)
अणु
	u8 value = 0;

	ec_पढ़ो(EEEPC_EC_FAN_CTRL, &value);
	अगर (value & EEEPC_EC_FAN_CTRL_BIT)
		वापस EEEPC_FAN_CTRL_MANUAL;
	अन्यथा
		वापस EEEPC_FAN_CTRL_AUTO;
पूर्ण

अटल व्योम eeepc_set_fan_ctrl(पूर्णांक manual)
अणु
	u8 value = 0;

	ec_पढ़ो(EEEPC_EC_FAN_CTRL, &value);
	अगर (manual == EEEPC_FAN_CTRL_MANUAL)
		value |= EEEPC_EC_FAN_CTRL_BIT;
	अन्यथा
		value &= ~EEEPC_EC_FAN_CTRL_BIT;
	ec_ग_लिखो(EEEPC_EC_FAN_CTRL, value);
पूर्ण

अटल sमाप_प्रकार store_sys_hwmon(व्योम (*set)(पूर्णांक), स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rv, value;

	rv = parse_arg(buf, &value);
	अगर (rv < 0)
		वापस rv;
	set(value);
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_sys_hwmon(पूर्णांक (*get)(व्योम), अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", get());
पूर्ण

#घोषणा EEEPC_SENSOR_SHOW_FUNC(_name, _get)				\
	अटल sमाप_प्रकार _name##_show(काष्ठा device *dev,			\
				    काष्ठा device_attribute *attr,	\
				    अक्षर *buf)				\
	अणु								\
		वापस show_sys_hwmon(_get, buf);			\
	पूर्ण

#घोषणा EEEPC_SENSOR_STORE_FUNC(_name, _set)				\
	अटल sमाप_प्रकार _name##_store(काष्ठा device *dev,		\
				     काष्ठा device_attribute *attr,	\
				     स्थिर अक्षर *buf, माप_प्रकार count)	\
	अणु								\
		वापस store_sys_hwmon(_set, buf, count);		\
	पूर्ण

#घोषणा EEEPC_CREATE_SENSOR_ATTR_RW(_name, _get, _set)			\
	EEEPC_SENSOR_SHOW_FUNC(_name, _get)				\
	EEEPC_SENSOR_STORE_FUNC(_name, _set)				\
	अटल DEVICE_ATTR_RW(_name)

#घोषणा EEEPC_CREATE_SENSOR_ATTR_RO(_name, _get)			\
	EEEPC_SENSOR_SHOW_FUNC(_name, _get)				\
	अटल DEVICE_ATTR_RO(_name)

EEEPC_CREATE_SENSOR_ATTR_RO(fan1_input, eeepc_get_fan_rpm);
EEEPC_CREATE_SENSOR_ATTR_RW(pwm1, eeepc_get_fan_pwm,
			    eeepc_set_fan_pwm);
EEEPC_CREATE_SENSOR_ATTR_RW(pwm1_enable, eeepc_get_fan_ctrl,
			    eeepc_set_fan_ctrl);

अटल काष्ठा attribute *hwmon_attrs[] = अणु
	&dev_attr_pwm1.attr,
	&dev_attr_fan1_input.attr,
	&dev_attr_pwm1_enable.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(hwmon);

अटल पूर्णांक eeepc_hwmon_init(काष्ठा eeepc_laptop *eeepc)
अणु
	काष्ठा device *dev = &eeepc->platक्रमm_device->dev;
	काष्ठा device *hwmon;

	hwmon = devm_hwmon_device_रेजिस्टर_with_groups(dev, "eeepc", शून्य,
						       hwmon_groups);
	अगर (IS_ERR(hwmon)) अणु
		pr_err("Could not register eeepc hwmon device\n");
		वापस PTR_ERR(hwmon);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Backlight device
 */
अटल पूर्णांक पढ़ो_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा eeepc_laptop *eeepc = bl_get_data(bd);

	वापस get_acpi(eeepc, CM_ASL_PANELBRIGHT);
पूर्ण

अटल पूर्णांक set_brightness(काष्ठा backlight_device *bd, पूर्णांक value)
अणु
	काष्ठा eeepc_laptop *eeepc = bl_get_data(bd);

	वापस set_acpi(eeepc, CM_ASL_PANELBRIGHT, value);
पूर्ण

अटल पूर्णांक update_bl_status(काष्ठा backlight_device *bd)
अणु
	वापस set_brightness(bd, bd->props.brightness);
पूर्ण

अटल स्थिर काष्ठा backlight_ops eeepcbl_ops = अणु
	.get_brightness = पढ़ो_brightness,
	.update_status = update_bl_status,
पूर्ण;

अटल पूर्णांक eeepc_backlight_notअगरy(काष्ठा eeepc_laptop *eeepc)
अणु
	काष्ठा backlight_device *bd = eeepc->backlight_device;
	पूर्णांक old = bd->props.brightness;

	backlight_क्रमce_update(bd, BACKLIGHT_UPDATE_HOTKEY);

	वापस old;
पूर्ण

अटल पूर्णांक eeepc_backlight_init(काष्ठा eeepc_laptop *eeepc)
अणु
	काष्ठा backlight_properties props;
	काष्ठा backlight_device *bd;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = 15;
	bd = backlight_device_रेजिस्टर(EEEPC_LAPTOP_खाता,
				       &eeepc->platक्रमm_device->dev, eeepc,
				       &eeepcbl_ops, &props);
	अगर (IS_ERR(bd)) अणु
		pr_err("Could not register eeepc backlight device\n");
		eeepc->backlight_device = शून्य;
		वापस PTR_ERR(bd);
	पूर्ण
	eeepc->backlight_device = bd;
	bd->props.brightness = पढ़ो_brightness(bd);
	bd->props.घातer = FB_BLANK_UNBLANK;
	backlight_update_status(bd);
	वापस 0;
पूर्ण

अटल व्योम eeepc_backlight_निकास(काष्ठा eeepc_laptop *eeepc)
अणु
	backlight_device_unरेजिस्टर(eeepc->backlight_device);
	eeepc->backlight_device = शून्य;
पूर्ण


/*
 * Input device (i.e. hotkeys)
 */
अटल पूर्णांक eeepc_input_init(काष्ठा eeepc_laptop *eeepc)
अणु
	काष्ठा input_dev *input;
	पूर्णांक error;

	input = input_allocate_device();
	अगर (!input)
		वापस -ENOMEM;

	input->name = "Asus EeePC extra buttons";
	input->phys = EEEPC_LAPTOP_खाता "/input0";
	input->id.bustype = BUS_HOST;
	input->dev.parent = &eeepc->platक्रमm_device->dev;

	error = sparse_keymap_setup(input, eeepc_keymap, शून्य);
	अगर (error) अणु
		pr_err("Unable to setup input device keymap\n");
		जाओ err_मुक्त_dev;
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		pr_err("Unable to register input device\n");
		जाओ err_मुक्त_dev;
	पूर्ण

	eeepc->inputdev = input;
	वापस 0;

err_मुक्त_dev:
	input_मुक्त_device(input);
	वापस error;
पूर्ण

अटल व्योम eeepc_input_निकास(काष्ठा eeepc_laptop *eeepc)
अणु
	अगर (eeepc->inputdev)
		input_unरेजिस्टर_device(eeepc->inputdev);
	eeepc->inputdev = शून्य;
पूर्ण

/*
 * ACPI driver
 */
अटल व्योम eeepc_input_notअगरy(काष्ठा eeepc_laptop *eeepc, पूर्णांक event)
अणु
	अगर (!eeepc->inputdev)
		वापस;
	अगर (!sparse_keymap_report_event(eeepc->inputdev, event, 1, true))
		pr_info("Unknown key %x pressed\n", event);
पूर्ण

अटल व्योम eeepc_acpi_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा eeepc_laptop *eeepc = acpi_driver_data(device);
	पूर्णांक old_brightness, new_brightness;
	u16 count;

	अगर (event > ACPI_MAX_SYS_NOTIFY)
		वापस;
	count = eeepc->event_count[event % 128]++;
	acpi_bus_generate_netlink_event(device->pnp.device_class,
					dev_name(&device->dev), event,
					count);

	/* Brightness events are special */
	अगर (event < NOTIFY_BRN_MIN || event > NOTIFY_BRN_MAX) अणु
		eeepc_input_notअगरy(eeepc, event);
		वापस;
	पूर्ण

	/* Ignore them completely अगर the acpi video driver is used */
	अगर (!eeepc->backlight_device)
		वापस;

	/* Update the backlight device. */
	old_brightness = eeepc_backlight_notअगरy(eeepc);

	/* Convert event to keypress (obsolescent hack) */
	new_brightness = event - NOTIFY_BRN_MIN;

	अगर (new_brightness < old_brightness) अणु
		event = NOTIFY_BRN_MIN; /* brightness करोwn */
	पूर्ण अन्यथा अगर (new_brightness > old_brightness) अणु
		event = NOTIFY_BRN_MAX; /* brightness up */
	पूर्ण अन्यथा अणु
		/*
		 * no change in brightness - alपढ़ोy at min/max,
		 * event will be desired value (or अन्यथा ignored)
		 */
	पूर्ण
	eeepc_input_notअगरy(eeepc, event);
पूर्ण

अटल व्योम eeepc_dmi_check(काष्ठा eeepc_laptop *eeepc)
अणु
	स्थिर अक्षर *model;

	model = dmi_get_प्रणाली_info(DMI_PRODUCT_NAME);
	अगर (!model)
		वापस;

	/*
	 * Blacklist क्रम setting cpufv (cpu speed).
	 *
	 * EeePC 4G ("701") implements CFVS, but it is not supported
	 * by the pre-installed OS, and the original option to change it
	 * in the BIOS setup screen was हटाओd in later versions.
	 *
	 * Judging by the lack of "Super Hybrid Engine" on Asus product pages,
	 * this applies to all "701" models (4G/4G Surf/2G Surf).
	 *
	 * So Asus made a deliberate decision not to support it on this model.
	 * We have several reports that using it can cause the प्रणाली to hang
	 *
	 * The hang has also been reported on a "702" (Model name "8G"?).
	 *
	 * We aव्योम dmi_check_प्रणाली() / dmi_match(), because they use
	 * substring matching.  We करोn't want to affect the "701SD"
	 * and "701SDX" models, because they करो support S.H.E.
	 */
	अगर (म_भेद(model, "701") == 0 || म_भेद(model, "702") == 0) अणु
		eeepc->cpufv_disabled = true;
		pr_info("model %s does not officially support setting cpu speed\n",
			model);
		pr_info("cpufv disabled to avoid instability\n");
	पूर्ण

	/*
	 * Blacklist क्रम wlan hotplug
	 *
	 * Eeepc 1005HA करोesn't work like others models and don't need the
	 * hotplug code. In fact, current hotplug code seems to unplug another
	 * device...
	 */
	अगर (म_भेद(model, "1005HA") == 0 || म_भेद(model, "1201N") == 0 ||
	    म_भेद(model, "1005PE") == 0) अणु
		eeepc->hotplug_disabled = true;
		pr_info("wlan hotplug disabled\n");
	पूर्ण
पूर्ण

अटल व्योम cmsg_quirk(काष्ठा eeepc_laptop *eeepc, पूर्णांक cm, स्थिर अक्षर *name)
अणु
	पूर्णांक dummy;

	/* Some BIOSes करो not report cm although it is available.
	   Check अगर cm_getv[cm] works and, अगर yes, assume cm should be set. */
	अगर (!(eeepc->cm_supported & (1 << cm))
	    && !पढ़ो_acpi_पूर्णांक(eeepc->handle, cm_getv[cm], &dummy)) अणु
		pr_info("%s (%x) not reported by BIOS, enabling anyway\n",
			name, 1 << cm);
		eeepc->cm_supported |= 1 << cm;
	पूर्ण
पूर्ण

अटल व्योम cmsg_quirks(काष्ठा eeepc_laptop *eeepc)
अणु
	cmsg_quirk(eeepc, CM_ASL_LID, "LID");
	cmsg_quirk(eeepc, CM_ASL_TYPE, "TYPE");
	cmsg_quirk(eeepc, CM_ASL_PANELPOWER, "PANELPOWER");
	cmsg_quirk(eeepc, CM_ASL_TPD, "TPD");
पूर्ण

अटल पूर्णांक eeepc_acpi_init(काष्ठा eeepc_laptop *eeepc)
अणु
	अचिन्हित पूर्णांक init_flags;
	पूर्णांक result;

	result = acpi_bus_get_status(eeepc->device);
	अगर (result)
		वापस result;
	अगर (!eeepc->device->status.present) अणु
		pr_err("Hotkey device not present, aborting\n");
		वापस -ENODEV;
	पूर्ण

	init_flags = DISABLE_ASL_WLAN | DISABLE_ASL_DISPLAYSWITCH;
	pr_notice("Hotkey init flags 0x%x\n", init_flags);

	अगर (ग_लिखो_acpi_पूर्णांक(eeepc->handle, "INIT", init_flags)) अणु
		pr_err("Hotkey initialization failed\n");
		वापस -ENODEV;
	पूर्ण

	/* get control methods supported */
	अगर (पढ़ो_acpi_पूर्णांक(eeepc->handle, "CMSG", &eeepc->cm_supported)) अणु
		pr_err("Get control methods supported failed\n");
		वापस -ENODEV;
	पूर्ण
	cmsg_quirks(eeepc);
	pr_info("Get control methods supported: 0x%x\n", eeepc->cm_supported);

	वापस 0;
पूर्ण

अटल व्योम eeepc_enable_camera(काष्ठा eeepc_laptop *eeepc)
अणु
	/*
	 * If the following call to set_acpi() fails, it's because there's no
	 * camera so we can ignore the error.
	 */
	अगर (get_acpi(eeepc, CM_ASL_CAMERA) == 0)
		set_acpi(eeepc, CM_ASL_CAMERA, 1);
पूर्ण

अटल bool eeepc_device_present;

अटल पूर्णांक eeepc_acpi_add(काष्ठा acpi_device *device)
अणु
	काष्ठा eeepc_laptop *eeepc;
	पूर्णांक result;

	pr_notice(EEEPC_LAPTOP_NAME "\n");
	eeepc = kzalloc(माप(काष्ठा eeepc_laptop), GFP_KERNEL);
	अगर (!eeepc)
		वापस -ENOMEM;
	eeepc->handle = device->handle;
	म_नकल(acpi_device_name(device), EEEPC_ACPI_DEVICE_NAME);
	म_नकल(acpi_device_class(device), EEEPC_ACPI_CLASS);
	device->driver_data = eeepc;
	eeepc->device = device;

	eeepc->hotplug_disabled = hotplug_disabled;

	eeepc_dmi_check(eeepc);

	result = eeepc_acpi_init(eeepc);
	अगर (result)
		जाओ fail_platक्रमm;
	eeepc_enable_camera(eeepc);

	/*
	 * Register the platक्रमm device first.  It is used as a parent क्रम the
	 * sub-devices below.
	 *
	 * Note that अगर there are multiple instances of this ACPI device it
	 * will bail out, because the platक्रमm device is रेजिस्टरed with a
	 * fixed name.  Of course it करोesn't make sense to have more than one,
	 * and machine-specअगरic scripts find the fixed name convenient.  But
	 * It's also good क्रम us to exclude multiple instances because both
	 * our hwmon and our wlan rfसमाप्त subdevice use global ACPI objects
	 * (the EC and the wlan PCI slot respectively).
	 */
	result = eeepc_platक्रमm_init(eeepc);
	अगर (result)
		जाओ fail_platक्रमm;

	अगर (acpi_video_get_backlight_type() == acpi_backlight_venकरोr) अणु
		result = eeepc_backlight_init(eeepc);
		अगर (result)
			जाओ fail_backlight;
	पूर्ण

	result = eeepc_input_init(eeepc);
	अगर (result)
		जाओ fail_input;

	result = eeepc_hwmon_init(eeepc);
	अगर (result)
		जाओ fail_hwmon;

	result = eeepc_led_init(eeepc);
	अगर (result)
		जाओ fail_led;

	result = eeepc_rfसमाप्त_init(eeepc);
	अगर (result)
		जाओ fail_rfसमाप्त;

	eeepc_device_present = true;
	वापस 0;

fail_rfसमाप्त:
	eeepc_led_निकास(eeepc);
fail_led:
fail_hwmon:
	eeepc_input_निकास(eeepc);
fail_input:
	eeepc_backlight_निकास(eeepc);
fail_backlight:
	eeepc_platक्रमm_निकास(eeepc);
fail_platक्रमm:
	kमुक्त(eeepc);

	वापस result;
पूर्ण

अटल पूर्णांक eeepc_acpi_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा eeepc_laptop *eeepc = acpi_driver_data(device);

	eeepc_backlight_निकास(eeepc);
	eeepc_rfसमाप्त_निकास(eeepc);
	eeepc_input_निकास(eeepc);
	eeepc_led_निकास(eeepc);
	eeepc_platक्रमm_निकास(eeepc);

	kमुक्त(eeepc);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा acpi_device_id eeepc_device_ids[] = अणु
	अणुEEEPC_ACPI_HID, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, eeepc_device_ids);

अटल काष्ठा acpi_driver eeepc_acpi_driver = अणु
	.name = EEEPC_LAPTOP_NAME,
	.class = EEEPC_ACPI_CLASS,
	.owner = THIS_MODULE,
	.ids = eeepc_device_ids,
	.flags = ACPI_DRIVER_ALL_NOTIFY_EVENTS,
	.ops = अणु
		.add = eeepc_acpi_add,
		.हटाओ = eeepc_acpi_हटाओ,
		.notअगरy = eeepc_acpi_notअगरy,
	पूर्ण,
पूर्ण;


अटल पूर्णांक __init eeepc_laptop_init(व्योम)
अणु
	पूर्णांक result;

	result = platक्रमm_driver_रेजिस्टर(&platक्रमm_driver);
	अगर (result < 0)
		वापस result;

	result = acpi_bus_रेजिस्टर_driver(&eeepc_acpi_driver);
	अगर (result < 0)
		जाओ fail_acpi_driver;

	अगर (!eeepc_device_present) अणु
		result = -ENODEV;
		जाओ fail_no_device;
	पूर्ण

	वापस 0;

fail_no_device:
	acpi_bus_unरेजिस्टर_driver(&eeepc_acpi_driver);
fail_acpi_driver:
	platक्रमm_driver_unरेजिस्टर(&platक्रमm_driver);
	वापस result;
पूर्ण

अटल व्योम __निकास eeepc_laptop_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&eeepc_acpi_driver);
	platक्रमm_driver_unरेजिस्टर(&platक्रमm_driver);
पूर्ण

module_init(eeepc_laptop_init);
module_निकास(eeepc_laptop_निकास);
