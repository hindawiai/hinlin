<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Asus PC WMI hotkey driver
 *
 * Copyright(C) 2010 Intel Corporation.
 * Copyright(C) 2010-2011 Corentin Chary <corentin.अक्षरy@gmail.com>
 *
 * Portions based on wistron_btns.c:
 * Copyright (C) 2005 Miloslav Trmac <mitr@volny.cz>
 * Copyright (C) 2005 Bernhard Rosenkraenzer <bero@arklinux.org>
 * Copyright (C) 2005 Dmitry Torokhov <dtor@mail.ru>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/leds.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/platक्रमm_data/x86/asus-wmi.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/units.h>

#समावेश <acpi/battery.h>
#समावेश <acpi/video.h>

#समावेश "asus-wmi.h"

MODULE_AUTHOR("Corentin Chary <corentin.chary@gmail.com>, "
	      "Yong Wang <yong.y.wang@intel.com>");
MODULE_DESCRIPTION("Asus Generic WMI Driver");
MODULE_LICENSE("GPL");

अटल bool fnlock_शेष = true;
module_param(fnlock_शेष, bool, 0444);

#घोषणा to_asus_wmi_driver(pdrv)					\
	(container_of((pdrv), काष्ठा asus_wmi_driver, platक्रमm_driver))

#घोषणा ASUS_WMI_MGMT_GUID	"97845ED0-4E6D-11DE-8A39-0800200C9A66"

#घोषणा NOTIFY_BRNUP_MIN		0x11
#घोषणा NOTIFY_BRNUP_MAX		0x1f
#घोषणा NOTIFY_BRNDOWN_MIN		0x20
#घोषणा NOTIFY_BRNDOWN_MAX		0x2e
#घोषणा NOTIFY_FNLOCK_TOGGLE		0x4e
#घोषणा NOTIFY_KBD_DOCK_CHANGE		0x75
#घोषणा NOTIFY_KBD_BRTUP		0xc4
#घोषणा NOTIFY_KBD_BRTDWN		0xc5
#घोषणा NOTIFY_KBD_BRTTOGGLE		0xc7
#घोषणा NOTIFY_KBD_FBM			0x99
#घोषणा NOTIFY_KBD_TTP			0xae
#घोषणा NOTIFY_LID_FLIP			0xfa

#घोषणा ASUS_WMI_FNLOCK_BIOS_DISABLED	BIT(0)

#घोषणा ASUS_FAN_DESC			"cpu_fan"
#घोषणा ASUS_FAN_MFUN			0x13
#घोषणा ASUS_FAN_SFUN_READ		0x06
#घोषणा ASUS_FAN_SFUN_WRITE		0x07

/* Based on standard hwmon pwmX_enable values */
#घोषणा ASUS_FAN_CTRL_FULLSPEED		0
#घोषणा ASUS_FAN_CTRL_MANUAL		1
#घोषणा ASUS_FAN_CTRL_AUTO		2

#घोषणा ASUS_FAN_BOOST_MODE_NORMAL		0
#घोषणा ASUS_FAN_BOOST_MODE_OVERBOOST		1
#घोषणा ASUS_FAN_BOOST_MODE_OVERBOOST_MASK	0x01
#घोषणा ASUS_FAN_BOOST_MODE_SILENT		2
#घोषणा ASUS_FAN_BOOST_MODE_SILENT_MASK		0x02
#घोषणा ASUS_FAN_BOOST_MODES_MASK		0x03

#घोषणा ASUS_THROTTLE_THERMAL_POLICY_DEFAULT	0
#घोषणा ASUS_THROTTLE_THERMAL_POLICY_OVERBOOST	1
#घोषणा ASUS_THROTTLE_THERMAL_POLICY_SILENT	2

#घोषणा USB_INTEL_XUSB2PR		0xD0
#घोषणा PCI_DEVICE_ID_INTEL_LYNXPOINT_LP_XHCI	0x9c31

#घोषणा ASUS_ACPI_UID_ASUSWMI		"ASUSWMI"
#घोषणा ASUS_ACPI_UID_ATK		"ATK"

#घोषणा WMI_EVENT_QUEUE_SIZE		0x10
#घोषणा WMI_EVENT_QUEUE_END		0x1
#घोषणा WMI_EVENT_MASK			0xFFFF
/* The WMI hotkey event value is always the same. */
#घोषणा WMI_EVENT_VALUE_ATK		0xFF

#घोषणा WMI_EVENT_MASK			0xFFFF

अटल स्थिर अक्षर * स्थिर ashs_ids[] = अणु "ATK4001", "ATK4002", शून्य पूर्ण;

अटल bool ashs_present(व्योम)
अणु
	पूर्णांक i = 0;
	जबतक (ashs_ids[i]) अणु
		अगर (acpi_dev_found(ashs_ids[i++]))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

काष्ठा bios_args अणु
	u32 arg0;
	u32 arg1;
	u32 arg2; /* At least TUF Gaming series uses 3 dword input buffer. */
	u32 arg4;
	u32 arg5;
पूर्ण __packed;

/*
 * Struct that's used क्रम all methods called via AGFN. Naming is
 * identically to the AML code.
 */
काष्ठा agfn_args अणु
	u16 mfun; /* probably "Multi-function" to be called */
	u16 sfun; /* probably "Sub-function" to be called */
	u16 len;  /* size of the hole काष्ठा, including subfunction fields */
	u8 stas;  /* not used by now */
	u8 err;   /* zero on success */
पूर्ण __packed;

/* काष्ठा used क्रम calling fan पढ़ो and ग_लिखो methods */
काष्ठा agfn_fan_args अणु
	काष्ठा agfn_args agfn;	/* common fields */
	u8 fan;			/* fan number: 0: set स्वतः mode 1: 1st fan */
	u32 speed;		/* पढ़ो: RPM/100 - ग_लिखो: 0-255 */
पूर्ण __packed;

/*
 * <platक्रमm>/    - debugfs root directory
 *   dev_id      - current dev_id
 *   ctrl_param  - current ctrl_param
 *   method_id   - current method_id
 *   devs        - call DEVS(dev_id, ctrl_param) and prपूर्णांक result
 *   dsts        - call DSTS(dev_id)  and prपूर्णांक result
 *   call        - call method_id(dev_id, ctrl_param) and prपूर्णांक result
 */
काष्ठा asus_wmi_debug अणु
	काष्ठा dentry *root;
	u32 method_id;
	u32 dev_id;
	u32 ctrl_param;
पूर्ण;

काष्ठा asus_rfसमाप्त अणु
	काष्ठा asus_wmi *asus;
	काष्ठा rfसमाप्त *rfसमाप्त;
	u32 dev_id;
पूर्ण;

क्रमागत fan_type अणु
	FAN_TYPE_NONE = 0,
	FAN_TYPE_AGFN,		/* deprecated on newer platक्रमms */
	FAN_TYPE_SPEC83,	/* starting in Spec 8.3, use CPU_FAN_CTRL */
पूर्ण;

काष्ठा asus_wmi अणु
	पूर्णांक dsts_id;
	पूर्णांक spec;
	पूर्णांक sfun;
	bool wmi_event_queue;

	काष्ठा input_dev *inputdev;
	काष्ठा backlight_device *backlight_device;
	काष्ठा platक्रमm_device *platक्रमm_device;

	काष्ठा led_classdev wlan_led;
	पूर्णांक wlan_led_wk;
	काष्ठा led_classdev tpd_led;
	पूर्णांक tpd_led_wk;
	काष्ठा led_classdev kbd_led;
	पूर्णांक kbd_led_wk;
	काष्ठा led_classdev lightbar_led;
	पूर्णांक lightbar_led_wk;
	काष्ठा workqueue_काष्ठा *led_workqueue;
	काष्ठा work_काष्ठा tpd_led_work;
	काष्ठा work_काष्ठा wlan_led_work;
	काष्ठा work_काष्ठा lightbar_led_work;

	काष्ठा asus_rfसमाप्त wlan;
	काष्ठा asus_rfसमाप्त bluetooth;
	काष्ठा asus_rfसमाप्त wimax;
	काष्ठा asus_rfसमाप्त wwan3g;
	काष्ठा asus_rfसमाप्त gps;
	काष्ठा asus_rfसमाप्त uwb;

	क्रमागत fan_type fan_type;
	पूर्णांक fan_pwm_mode;
	पूर्णांक agfn_pwm;

	bool fan_boost_mode_available;
	u8 fan_boost_mode_mask;
	u8 fan_boost_mode;

	bool throttle_thermal_policy_available;
	u8 throttle_thermal_policy_mode;

	// The RSOC controls the maximum अक्षरging percentage.
	bool battery_rsoc_available;

	काष्ठा hotplug_slot hotplug_slot;
	काष्ठा mutex hotplug_lock;
	काष्ठा mutex wmi_lock;
	काष्ठा workqueue_काष्ठा *hotplug_workqueue;
	काष्ठा work_काष्ठा hotplug_work;

	bool fnlock_locked;

	काष्ठा asus_wmi_debug debug;

	काष्ठा asus_wmi_driver *driver;
पूर्ण;

/* WMI ************************************************************************/

अटल पूर्णांक asus_wmi_evaluate_method3(u32 method_id,
		u32 arg0, u32 arg1, u32 arg2, u32 *retval)
अणु
	काष्ठा bios_args args = अणु
		.arg0 = arg0,
		.arg1 = arg1,
		.arg2 = arg2,
	पूर्ण;
	काष्ठा acpi_buffer input = अणु (acpi_size) माप(args), &args पूर्ण;
	काष्ठा acpi_buffer output = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	acpi_status status;
	जोड़ acpi_object *obj;
	u32 पंचांगp = 0;

	status = wmi_evaluate_method(ASUS_WMI_MGMT_GUID, 0, method_id,
				     &input, &output);

	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	obj = (जोड़ acpi_object *)output.poपूर्णांकer;
	अगर (obj && obj->type == ACPI_TYPE_INTEGER)
		पंचांगp = (u32) obj->पूर्णांकeger.value;

	अगर (retval)
		*retval = पंचांगp;

	kमुक्त(obj);

	अगर (पंचांगp == ASUS_WMI_UNSUPPORTED_METHOD)
		वापस -ENODEV;

	वापस 0;
पूर्ण

पूर्णांक asus_wmi_evaluate_method(u32 method_id, u32 arg0, u32 arg1, u32 *retval)
अणु
	वापस asus_wmi_evaluate_method3(method_id, arg0, arg1, 0, retval);
पूर्ण
EXPORT_SYMBOL_GPL(asus_wmi_evaluate_method);

अटल पूर्णांक asus_wmi_evaluate_method_agfn(स्थिर काष्ठा acpi_buffer args)
अणु
	काष्ठा acpi_buffer input;
	u64 phys_addr;
	u32 retval;
	u32 status;

	/*
	 * Copy to dma capable address otherwise memory corruption occurs as
	 * bios has to be able to access it.
	 */
	input.poपूर्णांकer = kmemdup(args.poपूर्णांकer, args.length, GFP_DMA | GFP_KERNEL);
	input.length = args.length;
	अगर (!input.poपूर्णांकer)
		वापस -ENOMEM;
	phys_addr = virt_to_phys(input.poपूर्णांकer);

	status = asus_wmi_evaluate_method(ASUS_WMI_METHODID_AGFN,
					phys_addr, 0, &retval);
	अगर (!status)
		स_नकल(args.poपूर्णांकer, input.poपूर्णांकer, args.length);

	kमुक्त(input.poपूर्णांकer);
	अगर (status)
		वापस -ENXIO;

	वापस retval;
पूर्ण

अटल पूर्णांक asus_wmi_get_devstate(काष्ठा asus_wmi *asus, u32 dev_id, u32 *retval)
अणु
	वापस asus_wmi_evaluate_method(asus->dsts_id, dev_id, 0, retval);
पूर्ण

अटल पूर्णांक asus_wmi_set_devstate(u32 dev_id, u32 ctrl_param,
				 u32 *retval)
अणु
	वापस asus_wmi_evaluate_method(ASUS_WMI_METHODID_DEVS, dev_id,
					ctrl_param, retval);
पूर्ण

/* Helper क्रम special devices with magic वापस codes */
अटल पूर्णांक asus_wmi_get_devstate_bits(काष्ठा asus_wmi *asus,
				      u32 dev_id, u32 mask)
अणु
	u32 retval = 0;
	पूर्णांक err;

	err = asus_wmi_get_devstate(asus, dev_id, &retval);
	अगर (err < 0)
		वापस err;

	अगर (!(retval & ASUS_WMI_DSTS_PRESENCE_BIT))
		वापस -ENODEV;

	अगर (mask == ASUS_WMI_DSTS_STATUS_BIT) अणु
		अगर (retval & ASUS_WMI_DSTS_UNKNOWN_BIT)
			वापस -ENODEV;
	पूर्ण

	वापस retval & mask;
पूर्ण

अटल पूर्णांक asus_wmi_get_devstate_simple(काष्ठा asus_wmi *asus, u32 dev_id)
अणु
	वापस asus_wmi_get_devstate_bits(asus, dev_id,
					  ASUS_WMI_DSTS_STATUS_BIT);
पूर्ण

अटल bool asus_wmi_dev_is_present(काष्ठा asus_wmi *asus, u32 dev_id)
अणु
	u32 retval;
	पूर्णांक status = asus_wmi_get_devstate(asus, dev_id, &retval);

	वापस status == 0 && (retval & ASUS_WMI_DSTS_PRESENCE_BIT);
पूर्ण

/* Input **********************************************************************/

अटल पूर्णांक asus_wmi_input_init(काष्ठा asus_wmi *asus)
अणु
	पूर्णांक err, result;

	asus->inputdev = input_allocate_device();
	अगर (!asus->inputdev)
		वापस -ENOMEM;

	asus->inputdev->name = asus->driver->input_name;
	asus->inputdev->phys = asus->driver->input_phys;
	asus->inputdev->id.bustype = BUS_HOST;
	asus->inputdev->dev.parent = &asus->platक्रमm_device->dev;
	set_bit(EV_REP, asus->inputdev->evbit);

	err = sparse_keymap_setup(asus->inputdev, asus->driver->keymap, शून्य);
	अगर (err)
		जाओ err_मुक्त_dev;

	अगर (asus->driver->quirks->use_kbd_करोck_devid) अणु
		result = asus_wmi_get_devstate_simple(asus, ASUS_WMI_DEVID_KBD_DOCK);
		अगर (result >= 0) अणु
			input_set_capability(asus->inputdev, EV_SW, SW_TABLET_MODE);
			input_report_चयन(asus->inputdev, SW_TABLET_MODE, !result);
		पूर्ण अन्यथा अगर (result != -ENODEV) अणु
			pr_err("Error checking for keyboard-dock: %d\n", result);
		पूर्ण
	पूर्ण

	अगर (asus->driver->quirks->use_lid_flip_devid) अणु
		result = asus_wmi_get_devstate_simple(asus, ASUS_WMI_DEVID_LID_FLIP);
		अगर (result < 0)
			asus->driver->quirks->use_lid_flip_devid = 0;
		अगर (result >= 0) अणु
			input_set_capability(asus->inputdev, EV_SW, SW_TABLET_MODE);
			input_report_चयन(asus->inputdev, SW_TABLET_MODE, result);
		पूर्ण अन्यथा अगर (result == -ENODEV) अणु
			pr_err("This device has lid_flip quirk but got ENODEV checking it. This is a bug.");
		पूर्ण अन्यथा अणु
			pr_err("Error checking for lid-flip: %d\n", result);
		पूर्ण
	पूर्ण

	err = input_रेजिस्टर_device(asus->inputdev);
	अगर (err)
		जाओ err_मुक्त_dev;

	वापस 0;

err_मुक्त_dev:
	input_मुक्त_device(asus->inputdev);
	वापस err;
पूर्ण

अटल व्योम asus_wmi_input_निकास(काष्ठा asus_wmi *asus)
अणु
	अगर (asus->inputdev)
		input_unरेजिस्टर_device(asus->inputdev);

	asus->inputdev = शून्य;
पूर्ण

/* Tablet mode ****************************************************************/

अटल व्योम lid_flip_tablet_mode_get_state(काष्ठा asus_wmi *asus)
अणु
	पूर्णांक result = asus_wmi_get_devstate_simple(asus, ASUS_WMI_DEVID_LID_FLIP);

	अगर (result >= 0) अणु
		input_report_चयन(asus->inputdev, SW_TABLET_MODE, result);
		input_sync(asus->inputdev);
	पूर्ण
पूर्ण

/* Battery ********************************************************************/

/* The battery maximum अक्षरging percentage */
अटल पूर्णांक अक्षरge_end_threshold;

अटल sमाप_प्रकार अक्षरge_control_end_threshold_store(काष्ठा device *dev,
						  काष्ठा device_attribute *attr,
						  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक value, ret, rv;

	ret = kstrtouपूर्णांक(buf, 10, &value);
	अगर (ret)
		वापस ret;

	अगर (value < 0 || value > 100)
		वापस -EINVAL;

	ret = asus_wmi_set_devstate(ASUS_WMI_DEVID_RSOC, value, &rv);
	अगर (ret)
		वापस ret;

	अगर (rv != 1)
		वापस -EIO;

	/* There isn't any method in the DSDT to पढ़ो the threshold, so we
	 * save the threshold.
	 */
	अक्षरge_end_threshold = value;
	वापस count;
पूर्ण

अटल sमाप_प्रकार अक्षरge_control_end_threshold_show(काष्ठा device *device,
						 काष्ठा device_attribute *attr,
						 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", अक्षरge_end_threshold);
पूर्ण

अटल DEVICE_ATTR_RW(अक्षरge_control_end_threshold);

अटल पूर्णांक asus_wmi_battery_add(काष्ठा घातer_supply *battery)
अणु
	/* The WMI method करोes not provide a way to specअगरic a battery, so we
	 * just assume it is the first battery.
	 * Note: On some newer ASUS laptops (Zenbook UM431DA), the primary/first
	 * battery is named BATT.
	 */
	अगर (म_भेद(battery->desc->name, "BAT0") != 0 &&
	    म_भेद(battery->desc->name, "BAT1") != 0 &&
	    म_भेद(battery->desc->name, "BATC") != 0 &&
	    म_भेद(battery->desc->name, "BATT") != 0)
		वापस -ENODEV;

	अगर (device_create_file(&battery->dev,
	    &dev_attr_अक्षरge_control_end_threshold))
		वापस -ENODEV;

	/* The अक्षरge threshold is only reset when the प्रणाली is घातer cycled,
	 * and we can't get the current threshold so let set it to 100% when
	 * a battery is added.
	 */
	asus_wmi_set_devstate(ASUS_WMI_DEVID_RSOC, 100, शून्य);
	अक्षरge_end_threshold = 100;

	वापस 0;
पूर्ण

अटल पूर्णांक asus_wmi_battery_हटाओ(काष्ठा घातer_supply *battery)
अणु
	device_हटाओ_file(&battery->dev,
			   &dev_attr_अक्षरge_control_end_threshold);
	वापस 0;
पूर्ण

अटल काष्ठा acpi_battery_hook battery_hook = अणु
	.add_battery = asus_wmi_battery_add,
	.हटाओ_battery = asus_wmi_battery_हटाओ,
	.name = "ASUS Battery Extension",
पूर्ण;

अटल व्योम asus_wmi_battery_init(काष्ठा asus_wmi *asus)
अणु
	asus->battery_rsoc_available = false;
	अगर (asus_wmi_dev_is_present(asus, ASUS_WMI_DEVID_RSOC)) अणु
		asus->battery_rsoc_available = true;
		battery_hook_रेजिस्टर(&battery_hook);
	पूर्ण
पूर्ण

अटल व्योम asus_wmi_battery_निकास(काष्ठा asus_wmi *asus)
अणु
	अगर (asus->battery_rsoc_available)
		battery_hook_unरेजिस्टर(&battery_hook);
पूर्ण

/* LEDs ***********************************************************************/

/*
 * These functions actually update the LED's, and are called from a
 * workqueue. By करोing this as separate work rather than when the LED
 * subप्रणाली asks, we aव्योम messing with the Asus ACPI stuff during a
 * potentially bad समय, such as a समयr पूर्णांकerrupt.
 */
अटल व्योम tpd_led_update(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ctrl_param;
	काष्ठा asus_wmi *asus;

	asus = container_of(work, काष्ठा asus_wmi, tpd_led_work);

	ctrl_param = asus->tpd_led_wk;
	asus_wmi_set_devstate(ASUS_WMI_DEVID_TOUCHPAD_LED, ctrl_param, शून्य);
पूर्ण

अटल व्योम tpd_led_set(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness value)
अणु
	काष्ठा asus_wmi *asus;

	asus = container_of(led_cdev, काष्ठा asus_wmi, tpd_led);

	asus->tpd_led_wk = !!value;
	queue_work(asus->led_workqueue, &asus->tpd_led_work);
पूर्ण

अटल पूर्णांक पढ़ो_tpd_led_state(काष्ठा asus_wmi *asus)
अणु
	वापस asus_wmi_get_devstate_simple(asus, ASUS_WMI_DEVID_TOUCHPAD_LED);
पूर्ण

अटल क्रमागत led_brightness tpd_led_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा asus_wmi *asus;

	asus = container_of(led_cdev, काष्ठा asus_wmi, tpd_led);

	वापस पढ़ो_tpd_led_state(asus);
पूर्ण

अटल व्योम kbd_led_update(काष्ठा asus_wmi *asus)
अणु
	पूर्णांक ctrl_param = 0;

	ctrl_param = 0x80 | (asus->kbd_led_wk & 0x7F);
	asus_wmi_set_devstate(ASUS_WMI_DEVID_KBD_BACKLIGHT, ctrl_param, शून्य);
पूर्ण

अटल पूर्णांक kbd_led_पढ़ो(काष्ठा asus_wmi *asus, पूर्णांक *level, पूर्णांक *env)
अणु
	पूर्णांक retval;

	/*
	 * bits 0-2: level
	 * bit 7: light on/off
	 * bit 8-10: environment (0: dark, 1: normal, 2: light)
	 * bit 17: status unknown
	 */
	retval = asus_wmi_get_devstate_bits(asus, ASUS_WMI_DEVID_KBD_BACKLIGHT,
					    0xFFFF);

	/* Unknown status is considered as off */
	अगर (retval == 0x8000)
		retval = 0;

	अगर (retval < 0)
		वापस retval;

	अगर (level)
		*level = retval & 0x7F;
	अगर (env)
		*env = (retval >> 8) & 0x7F;
	वापस 0;
पूर्ण

अटल व्योम करो_kbd_led_set(काष्ठा led_classdev *led_cdev, पूर्णांक value)
अणु
	काष्ठा asus_wmi *asus;
	पूर्णांक max_level;

	asus = container_of(led_cdev, काष्ठा asus_wmi, kbd_led);
	max_level = asus->kbd_led.max_brightness;

	asus->kbd_led_wk = clamp_val(value, 0, max_level);
	kbd_led_update(asus);
पूर्ण

अटल व्योम kbd_led_set(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness value)
अणु
	/* Prevent disabling keyboard backlight on module unरेजिस्टर */
	अगर (led_cdev->flags & LED_UNREGISTERING)
		वापस;

	करो_kbd_led_set(led_cdev, value);
पूर्ण

अटल व्योम kbd_led_set_by_kbd(काष्ठा asus_wmi *asus, क्रमागत led_brightness value)
अणु
	काष्ठा led_classdev *led_cdev = &asus->kbd_led;

	करो_kbd_led_set(led_cdev, value);
	led_classdev_notअगरy_brightness_hw_changed(led_cdev, asus->kbd_led_wk);
पूर्ण

अटल क्रमागत led_brightness kbd_led_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा asus_wmi *asus;
	पूर्णांक retval, value;

	asus = container_of(led_cdev, काष्ठा asus_wmi, kbd_led);

	retval = kbd_led_पढ़ो(asus, &value, शून्य);
	अगर (retval < 0)
		वापस retval;

	वापस value;
पूर्ण

अटल पूर्णांक wlan_led_unknown_state(काष्ठा asus_wmi *asus)
अणु
	u32 result;

	asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_WIRELESS_LED, &result);

	वापस result & ASUS_WMI_DSTS_UNKNOWN_BIT;
पूर्ण

अटल व्योम wlan_led_update(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ctrl_param;
	काष्ठा asus_wmi *asus;

	asus = container_of(work, काष्ठा asus_wmi, wlan_led_work);

	ctrl_param = asus->wlan_led_wk;
	asus_wmi_set_devstate(ASUS_WMI_DEVID_WIRELESS_LED, ctrl_param, शून्य);
पूर्ण

अटल व्योम wlan_led_set(काष्ठा led_classdev *led_cdev,
			 क्रमागत led_brightness value)
अणु
	काष्ठा asus_wmi *asus;

	asus = container_of(led_cdev, काष्ठा asus_wmi, wlan_led);

	asus->wlan_led_wk = !!value;
	queue_work(asus->led_workqueue, &asus->wlan_led_work);
पूर्ण

अटल क्रमागत led_brightness wlan_led_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा asus_wmi *asus;
	u32 result;

	asus = container_of(led_cdev, काष्ठा asus_wmi, wlan_led);
	asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_WIRELESS_LED, &result);

	वापस result & ASUS_WMI_DSTS_BRIGHTNESS_MASK;
पूर्ण

अटल व्योम lightbar_led_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asus_wmi *asus;
	पूर्णांक ctrl_param;

	asus = container_of(work, काष्ठा asus_wmi, lightbar_led_work);

	ctrl_param = asus->lightbar_led_wk;
	asus_wmi_set_devstate(ASUS_WMI_DEVID_LIGHTBAR, ctrl_param, शून्य);
पूर्ण

अटल व्योम lightbar_led_set(काष्ठा led_classdev *led_cdev,
			     क्रमागत led_brightness value)
अणु
	काष्ठा asus_wmi *asus;

	asus = container_of(led_cdev, काष्ठा asus_wmi, lightbar_led);

	asus->lightbar_led_wk = !!value;
	queue_work(asus->led_workqueue, &asus->lightbar_led_work);
पूर्ण

अटल क्रमागत led_brightness lightbar_led_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा asus_wmi *asus;
	u32 result;

	asus = container_of(led_cdev, काष्ठा asus_wmi, lightbar_led);
	asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_LIGHTBAR, &result);

	वापस result & ASUS_WMI_DSTS_LIGHTBAR_MASK;
पूर्ण

अटल व्योम asus_wmi_led_निकास(काष्ठा asus_wmi *asus)
अणु
	led_classdev_unरेजिस्टर(&asus->kbd_led);
	led_classdev_unरेजिस्टर(&asus->tpd_led);
	led_classdev_unरेजिस्टर(&asus->wlan_led);
	led_classdev_unरेजिस्टर(&asus->lightbar_led);

	अगर (asus->led_workqueue)
		destroy_workqueue(asus->led_workqueue);
पूर्ण

अटल पूर्णांक asus_wmi_led_init(काष्ठा asus_wmi *asus)
अणु
	पूर्णांक rv = 0, led_val;

	asus->led_workqueue = create_singlethपढ़ो_workqueue("led_workqueue");
	अगर (!asus->led_workqueue)
		वापस -ENOMEM;

	अगर (पढ़ो_tpd_led_state(asus) >= 0) अणु
		INIT_WORK(&asus->tpd_led_work, tpd_led_update);

		asus->tpd_led.name = "asus::touchpad";
		asus->tpd_led.brightness_set = tpd_led_set;
		asus->tpd_led.brightness_get = tpd_led_get;
		asus->tpd_led.max_brightness = 1;

		rv = led_classdev_रेजिस्टर(&asus->platक्रमm_device->dev,
					   &asus->tpd_led);
		अगर (rv)
			जाओ error;
	पूर्ण

	अगर (!kbd_led_पढ़ो(asus, &led_val, शून्य)) अणु
		asus->kbd_led_wk = led_val;
		asus->kbd_led.name = "asus::kbd_backlight";
		asus->kbd_led.flags = LED_BRIGHT_HW_CHANGED;
		asus->kbd_led.brightness_set = kbd_led_set;
		asus->kbd_led.brightness_get = kbd_led_get;
		asus->kbd_led.max_brightness = 3;

		rv = led_classdev_रेजिस्टर(&asus->platक्रमm_device->dev,
					   &asus->kbd_led);
		अगर (rv)
			जाओ error;
	पूर्ण

	अगर (asus_wmi_dev_is_present(asus, ASUS_WMI_DEVID_WIRELESS_LED)
			&& (asus->driver->quirks->wapf > 0)) अणु
		INIT_WORK(&asus->wlan_led_work, wlan_led_update);

		asus->wlan_led.name = "asus::wlan";
		asus->wlan_led.brightness_set = wlan_led_set;
		अगर (!wlan_led_unknown_state(asus))
			asus->wlan_led.brightness_get = wlan_led_get;
		asus->wlan_led.flags = LED_CORE_SUSPENDRESUME;
		asus->wlan_led.max_brightness = 1;
		asus->wlan_led.शेष_trigger = "asus-wlan";

		rv = led_classdev_रेजिस्टर(&asus->platक्रमm_device->dev,
					   &asus->wlan_led);
		अगर (rv)
			जाओ error;
	पूर्ण

	अगर (asus_wmi_dev_is_present(asus, ASUS_WMI_DEVID_LIGHTBAR)) अणु
		INIT_WORK(&asus->lightbar_led_work, lightbar_led_update);

		asus->lightbar_led.name = "asus::lightbar";
		asus->lightbar_led.brightness_set = lightbar_led_set;
		asus->lightbar_led.brightness_get = lightbar_led_get;
		asus->lightbar_led.max_brightness = 1;

		rv = led_classdev_रेजिस्टर(&asus->platक्रमm_device->dev,
					   &asus->lightbar_led);
	पूर्ण

error:
	अगर (rv)
		asus_wmi_led_निकास(asus);

	वापस rv;
पूर्ण

/* RF *************************************************************************/

/*
 * PCI hotplug (क्रम wlan rfसमाप्त)
 */
अटल bool asus_wlan_rfसमाप्त_blocked(काष्ठा asus_wmi *asus)
अणु
	पूर्णांक result = asus_wmi_get_devstate_simple(asus, ASUS_WMI_DEVID_WLAN);

	अगर (result < 0)
		वापस false;
	वापस !result;
पूर्ण

अटल व्योम asus_rfसमाप्त_hotplug(काष्ठा asus_wmi *asus)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_bus *bus;
	bool blocked;
	bool असलent;
	u32 l;

	mutex_lock(&asus->wmi_lock);
	blocked = asus_wlan_rfसमाप्त_blocked(asus);
	mutex_unlock(&asus->wmi_lock);

	mutex_lock(&asus->hotplug_lock);
	pci_lock_rescan_हटाओ();

	अगर (asus->wlan.rfसमाप्त)
		rfसमाप्त_set_sw_state(asus->wlan.rfसमाप्त, blocked);

	अगर (asus->hotplug_slot.ops) अणु
		bus = pci_find_bus(0, 1);
		अगर (!bus) अणु
			pr_warn("Unable to find PCI bus 1?\n");
			जाओ out_unlock;
		पूर्ण

		अगर (pci_bus_पढ़ो_config_dword(bus, 0, PCI_VENDOR_ID, &l)) अणु
			pr_err("Unable to read PCI config space?\n");
			जाओ out_unlock;
		पूर्ण
		असलent = (l == 0xffffffff);

		अगर (blocked != असलent) अणु
			pr_warn("BIOS says wireless lan is %s, "
				"but the pci device is %s\n",
				blocked ? "blocked" : "unblocked",
				असलent ? "absent" : "present");
			pr_warn("skipped wireless hotplug as probably "
				"inappropriate for this model\n");
			जाओ out_unlock;
		पूर्ण

		अगर (!blocked) अणु
			dev = pci_get_slot(bus, 0);
			अगर (dev) अणु
				/* Device alपढ़ोy present */
				pci_dev_put(dev);
				जाओ out_unlock;
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
	पूर्ण

out_unlock:
	pci_unlock_rescan_हटाओ();
	mutex_unlock(&asus->hotplug_lock);
पूर्ण

अटल व्योम asus_rfसमाप्त_notअगरy(acpi_handle handle, u32 event, व्योम *data)
अणु
	काष्ठा asus_wmi *asus = data;

	अगर (event != ACPI_NOTIFY_BUS_CHECK)
		वापस;

	/*
	 * We can't call directly asus_rfसमाप्त_hotplug because most
	 * of the समय WMBC is still being executed and not reetrant.
	 * There is currently no way to tell ACPICA that  we want this
	 * method to be serialized, we schedule a asus_rfसमाप्त_hotplug
	 * call later, in a safer context.
	 */
	queue_work(asus->hotplug_workqueue, &asus->hotplug_work);
पूर्ण

अटल पूर्णांक asus_रेजिस्टर_rfसमाप्त_notअगरier(काष्ठा asus_wmi *asus, अक्षर *node)
अणु
	acpi_status status;
	acpi_handle handle;

	status = acpi_get_handle(शून्य, node, &handle);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	status = acpi_install_notअगरy_handler(handle, ACPI_SYSTEM_NOTIFY,
					     asus_rfसमाप्त_notअगरy, asus);
	अगर (ACPI_FAILURE(status))
		pr_warn("Failed to register notify on %s\n", node);

	वापस 0;
पूर्ण

अटल व्योम asus_unरेजिस्टर_rfसमाप्त_notअगरier(काष्ठा asus_wmi *asus, अक्षर *node)
अणु
	acpi_status status = AE_OK;
	acpi_handle handle;

	status = acpi_get_handle(शून्य, node, &handle);
	अगर (ACPI_FAILURE(status))
		वापस;

	status = acpi_हटाओ_notअगरy_handler(handle, ACPI_SYSTEM_NOTIFY,
					    asus_rfसमाप्त_notअगरy);
	अगर (ACPI_FAILURE(status))
		pr_err("Error removing rfkill notify handler %s\n", node);
पूर्ण

अटल पूर्णांक asus_get_adapter_status(काष्ठा hotplug_slot *hotplug_slot,
				   u8 *value)
अणु
	काष्ठा asus_wmi *asus = container_of(hotplug_slot,
					     काष्ठा asus_wmi, hotplug_slot);
	पूर्णांक result = asus_wmi_get_devstate_simple(asus, ASUS_WMI_DEVID_WLAN);

	अगर (result < 0)
		वापस result;

	*value = !!result;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hotplug_slot_ops asus_hotplug_slot_ops = अणु
	.get_adapter_status = asus_get_adapter_status,
	.get_घातer_status = asus_get_adapter_status,
पूर्ण;

अटल व्योम asus_hotplug_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asus_wmi *asus;

	asus = container_of(work, काष्ठा asus_wmi, hotplug_work);
	asus_rfसमाप्त_hotplug(asus);
पूर्ण

अटल पूर्णांक asus_setup_pci_hotplug(काष्ठा asus_wmi *asus)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा pci_bus *bus = pci_find_bus(0, 1);

	अगर (!bus) अणु
		pr_err("Unable to find wifi PCI bus\n");
		वापस -ENODEV;
	पूर्ण

	asus->hotplug_workqueue =
	    create_singlethपढ़ो_workqueue("hotplug_workqueue");
	अगर (!asus->hotplug_workqueue)
		जाओ error_workqueue;

	INIT_WORK(&asus->hotplug_work, asus_hotplug_work);

	asus->hotplug_slot.ops = &asus_hotplug_slot_ops;

	ret = pci_hp_रेजिस्टर(&asus->hotplug_slot, bus, 0, "asus-wifi");
	अगर (ret) अणु
		pr_err("Unable to register hotplug slot - %d\n", ret);
		जाओ error_रेजिस्टर;
	पूर्ण

	वापस 0;

error_रेजिस्टर:
	asus->hotplug_slot.ops = शून्य;
	destroy_workqueue(asus->hotplug_workqueue);
error_workqueue:
	वापस ret;
पूर्ण

/*
 * Rfसमाप्त devices
 */
अटल पूर्णांक asus_rfसमाप्त_set(व्योम *data, bool blocked)
अणु
	काष्ठा asus_rfसमाप्त *priv = data;
	u32 ctrl_param = !blocked;
	u32 dev_id = priv->dev_id;

	/*
	 * If the user bit is set, BIOS can't set and record the wlan status,
	 * it will report the value पढ़ो from id ASUS_WMI_DEVID_WLAN_LED
	 * जबतक we query the wlan status through WMI(ASUS_WMI_DEVID_WLAN).
	 * So, we have to record wlan status in id ASUS_WMI_DEVID_WLAN_LED
	 * जबतक setting the wlan status through WMI.
	 * This is also the behavior that winकरोws app will करो.
	 */
	अगर ((dev_id == ASUS_WMI_DEVID_WLAN) &&
	     priv->asus->driver->wlan_ctrl_by_user)
		dev_id = ASUS_WMI_DEVID_WLAN_LED;

	वापस asus_wmi_set_devstate(dev_id, ctrl_param, शून्य);
पूर्ण

अटल व्योम asus_rfसमाप्त_query(काष्ठा rfसमाप्त *rfसमाप्त, व्योम *data)
अणु
	काष्ठा asus_rfसमाप्त *priv = data;
	पूर्णांक result;

	result = asus_wmi_get_devstate_simple(priv->asus, priv->dev_id);

	अगर (result < 0)
		वापस;

	rfसमाप्त_set_sw_state(priv->rfसमाप्त, !result);
पूर्ण

अटल पूर्णांक asus_rfसमाप्त_wlan_set(व्योम *data, bool blocked)
अणु
	काष्ठा asus_rfसमाप्त *priv = data;
	काष्ठा asus_wmi *asus = priv->asus;
	पूर्णांक ret;

	/*
	 * This handler is enabled only अगर hotplug is enabled.
	 * In this हाल, the asus_wmi_set_devstate() will
	 * trigger a wmi notअगरication and we need to रुको
	 * this call to finish beक्रमe being able to call
	 * any wmi method
	 */
	mutex_lock(&asus->wmi_lock);
	ret = asus_rfसमाप्त_set(data, blocked);
	mutex_unlock(&asus->wmi_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops asus_rfसमाप्त_wlan_ops = अणु
	.set_block = asus_rfसमाप्त_wlan_set,
	.query = asus_rfसमाप्त_query,
पूर्ण;

अटल स्थिर काष्ठा rfसमाप्त_ops asus_rfसमाप्त_ops = अणु
	.set_block = asus_rfसमाप्त_set,
	.query = asus_rfसमाप्त_query,
पूर्ण;

अटल पूर्णांक asus_new_rfसमाप्त(काष्ठा asus_wmi *asus,
			   काष्ठा asus_rfसमाप्त *arfसमाप्त,
			   स्थिर अक्षर *name, क्रमागत rfसमाप्त_type type, पूर्णांक dev_id)
अणु
	पूर्णांक result = asus_wmi_get_devstate_simple(asus, dev_id);
	काष्ठा rfसमाप्त **rfसमाप्त = &arfसमाप्त->rfसमाप्त;

	अगर (result < 0)
		वापस result;

	arfसमाप्त->dev_id = dev_id;
	arfसमाप्त->asus = asus;

	अगर (dev_id == ASUS_WMI_DEVID_WLAN &&
	    asus->driver->quirks->hotplug_wireless)
		*rfसमाप्त = rfसमाप्त_alloc(name, &asus->platक्रमm_device->dev, type,
				       &asus_rfसमाप्त_wlan_ops, arfसमाप्त);
	अन्यथा
		*rfसमाप्त = rfसमाप्त_alloc(name, &asus->platक्रमm_device->dev, type,
				       &asus_rfसमाप्त_ops, arfसमाप्त);

	अगर (!*rfसमाप्त)
		वापस -EINVAL;

	अगर ((dev_id == ASUS_WMI_DEVID_WLAN) &&
			(asus->driver->quirks->wapf > 0))
		rfसमाप्त_set_led_trigger_name(*rfसमाप्त, "asus-wlan");

	rfसमाप्त_init_sw_state(*rfसमाप्त, !result);
	result = rfसमाप्त_रेजिस्टर(*rfसमाप्त);
	अगर (result) अणु
		rfसमाप्त_destroy(*rfसमाप्त);
		*rfसमाप्त = शून्य;
		वापस result;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम asus_wmi_rfसमाप्त_निकास(काष्ठा asus_wmi *asus)
अणु
	अगर (asus->driver->wlan_ctrl_by_user && ashs_present())
		वापस;

	asus_unरेजिस्टर_rfसमाप्त_notअगरier(asus, "\\_SB.PCI0.P0P5");
	asus_unरेजिस्टर_rfसमाप्त_notअगरier(asus, "\\_SB.PCI0.P0P6");
	asus_unरेजिस्टर_rfसमाप्त_notअगरier(asus, "\\_SB.PCI0.P0P7");
	अगर (asus->wlan.rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(asus->wlan.rfसमाप्त);
		rfसमाप्त_destroy(asus->wlan.rfसमाप्त);
		asus->wlan.rfसमाप्त = शून्य;
	पूर्ण
	/*
	 * Refresh pci hotplug in हाल the rfसमाप्त state was changed after
	 * asus_unरेजिस्टर_rfसमाप्त_notअगरier()
	 */
	asus_rfसमाप्त_hotplug(asus);
	अगर (asus->hotplug_slot.ops)
		pci_hp_deरेजिस्टर(&asus->hotplug_slot);
	अगर (asus->hotplug_workqueue)
		destroy_workqueue(asus->hotplug_workqueue);

	अगर (asus->bluetooth.rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(asus->bluetooth.rfसमाप्त);
		rfसमाप्त_destroy(asus->bluetooth.rfसमाप्त);
		asus->bluetooth.rfसमाप्त = शून्य;
	पूर्ण
	अगर (asus->wimax.rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(asus->wimax.rfसमाप्त);
		rfसमाप्त_destroy(asus->wimax.rfसमाप्त);
		asus->wimax.rfसमाप्त = शून्य;
	पूर्ण
	अगर (asus->wwan3g.rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(asus->wwan3g.rfसमाप्त);
		rfसमाप्त_destroy(asus->wwan3g.rfसमाप्त);
		asus->wwan3g.rfसमाप्त = शून्य;
	पूर्ण
	अगर (asus->gps.rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(asus->gps.rfसमाप्त);
		rfसमाप्त_destroy(asus->gps.rfसमाप्त);
		asus->gps.rfसमाप्त = शून्य;
	पूर्ण
	अगर (asus->uwb.rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(asus->uwb.rfसमाप्त);
		rfसमाप्त_destroy(asus->uwb.rfसमाप्त);
		asus->uwb.rfसमाप्त = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक asus_wmi_rfसमाप्त_init(काष्ठा asus_wmi *asus)
अणु
	पूर्णांक result = 0;

	mutex_init(&asus->hotplug_lock);
	mutex_init(&asus->wmi_lock);

	result = asus_new_rfसमाप्त(asus, &asus->wlan, "asus-wlan",
				 RFKILL_TYPE_WLAN, ASUS_WMI_DEVID_WLAN);

	अगर (result && result != -ENODEV)
		जाओ निकास;

	result = asus_new_rfसमाप्त(asus, &asus->bluetooth,
				 "asus-bluetooth", RFKILL_TYPE_BLUETOOTH,
				 ASUS_WMI_DEVID_BLUETOOTH);

	अगर (result && result != -ENODEV)
		जाओ निकास;

	result = asus_new_rfसमाप्त(asus, &asus->wimax, "asus-wimax",
				 RFKILL_TYPE_WIMAX, ASUS_WMI_DEVID_WIMAX);

	अगर (result && result != -ENODEV)
		जाओ निकास;

	result = asus_new_rfसमाप्त(asus, &asus->wwan3g, "asus-wwan3g",
				 RFKILL_TYPE_WWAN, ASUS_WMI_DEVID_WWAN3G);

	अगर (result && result != -ENODEV)
		जाओ निकास;

	result = asus_new_rfसमाप्त(asus, &asus->gps, "asus-gps",
				 RFKILL_TYPE_GPS, ASUS_WMI_DEVID_GPS);

	अगर (result && result != -ENODEV)
		जाओ निकास;

	result = asus_new_rfसमाप्त(asus, &asus->uwb, "asus-uwb",
				 RFKILL_TYPE_UWB, ASUS_WMI_DEVID_UWB);

	अगर (result && result != -ENODEV)
		जाओ निकास;

	अगर (!asus->driver->quirks->hotplug_wireless)
		जाओ निकास;

	result = asus_setup_pci_hotplug(asus);
	/*
	 * If we get -EBUSY then something अन्यथा is handling the PCI hotplug -
	 * करोn't fail in this हाल
	 */
	अगर (result == -EBUSY)
		result = 0;

	asus_रेजिस्टर_rfसमाप्त_notअगरier(asus, "\\_SB.PCI0.P0P5");
	asus_रेजिस्टर_rfसमाप्त_notअगरier(asus, "\\_SB.PCI0.P0P6");
	asus_रेजिस्टर_rfसमाप्त_notअगरier(asus, "\\_SB.PCI0.P0P7");
	/*
	 * Refresh pci hotplug in हाल the rfसमाप्त state was changed during
	 * setup.
	 */
	asus_rfसमाप्त_hotplug(asus);

निकास:
	अगर (result && result != -ENODEV)
		asus_wmi_rfसमाप्त_निकास(asus);

	अगर (result == -ENODEV)
		result = 0;

	वापस result;
पूर्ण

/* Quirks *********************************************************************/

अटल व्योम asus_wmi_set_xusb2pr(काष्ठा asus_wmi *asus)
अणु
	काष्ठा pci_dev *xhci_pdev;
	u32 orig_ports_available;
	u32 ports_available = asus->driver->quirks->xusb2pr;

	xhci_pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
			PCI_DEVICE_ID_INTEL_LYNXPOINT_LP_XHCI,
			शून्य);

	अगर (!xhci_pdev)
		वापस;

	pci_पढ़ो_config_dword(xhci_pdev, USB_INTEL_XUSB2PR,
				&orig_ports_available);

	pci_ग_लिखो_config_dword(xhci_pdev, USB_INTEL_XUSB2PR,
				cpu_to_le32(ports_available));

	pr_info("set USB_INTEL_XUSB2PR old: 0x%04x, new: 0x%04x\n",
			orig_ports_available, ports_available);
पूर्ण

/*
 * Some devices करोnt support or have borcken get_als method
 * but still support set method.
 */
अटल व्योम asus_wmi_set_als(व्योम)
अणु
	asus_wmi_set_devstate(ASUS_WMI_DEVID_ALS_ENABLE, 1, शून्य);
पूर्ण

/* Hwmon device ***************************************************************/

अटल पूर्णांक asus_agfn_fan_speed_पढ़ो(काष्ठा asus_wmi *asus, पूर्णांक fan,
					  पूर्णांक *speed)
अणु
	काष्ठा agfn_fan_args args = अणु
		.agfn.len = माप(args),
		.agfn.mfun = ASUS_FAN_MFUN,
		.agfn.sfun = ASUS_FAN_SFUN_READ,
		.fan = fan,
		.speed = 0,
	पूर्ण;
	काष्ठा acpi_buffer input = अणु (acpi_size) माप(args), &args पूर्ण;
	पूर्णांक status;

	अगर (fan != 1)
		वापस -EINVAL;

	status = asus_wmi_evaluate_method_agfn(input);

	अगर (status || args.agfn.err)
		वापस -ENXIO;

	अगर (speed)
		*speed = args.speed;

	वापस 0;
पूर्ण

अटल पूर्णांक asus_agfn_fan_speed_ग_लिखो(काष्ठा asus_wmi *asus, पूर्णांक fan,
				     पूर्णांक *speed)
अणु
	काष्ठा agfn_fan_args args = अणु
		.agfn.len = माप(args),
		.agfn.mfun = ASUS_FAN_MFUN,
		.agfn.sfun = ASUS_FAN_SFUN_WRITE,
		.fan = fan,
		.speed = speed ?  *speed : 0,
	पूर्ण;
	काष्ठा acpi_buffer input = अणु (acpi_size) माप(args), &args पूर्ण;
	पूर्णांक status;

	/* 1: क्रम setting 1st fan's speed 0: setting स्वतः mode */
	अगर (fan != 1 && fan != 0)
		वापस -EINVAL;

	status = asus_wmi_evaluate_method_agfn(input);

	अगर (status || args.agfn.err)
		वापस -ENXIO;

	अगर (speed && fan == 1)
		asus->agfn_pwm = *speed;

	वापस 0;
पूर्ण

/*
 * Check अगर we can पढ़ो the speed of one fan. If true we assume we can also
 * control it.
 */
अटल bool asus_wmi_has_agfn_fan(काष्ठा asus_wmi *asus)
अणु
	पूर्णांक status;
	पूर्णांक speed;
	u32 value;

	status = asus_agfn_fan_speed_पढ़ो(asus, 1, &speed);
	अगर (status != 0)
		वापस false;

	status = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_FAN_CTRL, &value);
	अगर (status != 0)
		वापस false;

	/*
	 * We need to find a better way, probably using sfun,
	 * bits or spec ...
	 * Currently we disable it अगर:
	 * - ASUS_WMI_UNSUPPORTED_METHOD is वापसed
	 * - reverved bits are non-zero
	 * - sfun and presence bit are not set
	 */
	वापस !(value == ASUS_WMI_UNSUPPORTED_METHOD || value & 0xFFF80000
		 || (!asus->sfun && !(value & ASUS_WMI_DSTS_PRESENCE_BIT)));
पूर्ण

अटल पूर्णांक asus_fan_set_स्वतः(काष्ठा asus_wmi *asus)
अणु
	पूर्णांक status;
	u32 retval;

	चयन (asus->fan_type) अणु
	हाल FAN_TYPE_SPEC83:
		status = asus_wmi_set_devstate(ASUS_WMI_DEVID_CPU_FAN_CTRL,
					       0, &retval);
		अगर (status)
			वापस status;

		अगर (retval != 1)
			वापस -EIO;
		अवरोध;

	हाल FAN_TYPE_AGFN:
		status = asus_agfn_fan_speed_ग_लिखो(asus, 0, शून्य);
		अगर (status)
			वापस -ENXIO;
		अवरोध;

	शेष:
		वापस -ENXIO;
	पूर्ण


	वापस 0;
पूर्ण

अटल sमाप_प्रकार pwm1_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा asus_wmi *asus = dev_get_drvdata(dev);
	पूर्णांक err;
	पूर्णांक value;

	/* If we alपढ़ोy set a value then just वापस it */
	अगर (asus->agfn_pwm >= 0)
		वापस प्र_लिखो(buf, "%d\n", asus->agfn_pwm);

	/*
	 * If we haven't set alपढ़ोy set a value through the AGFN पूर्णांकerface,
	 * we पढ़ो a current value through the (now-deprecated) FAN_CTRL device.
	 */
	err = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_FAN_CTRL, &value);
	अगर (err < 0)
		वापस err;

	value &= 0xFF;

	अगर (value == 1) /* Low Speed */
		value = 85;
	अन्यथा अगर (value == 2)
		value = 170;
	अन्यथा अगर (value == 3)
		value = 255;
	अन्यथा अगर (value) अणु
		pr_err("Unknown fan speed %#x\n", value);
		value = -1;
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार pwm1_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count) अणु
	काष्ठा asus_wmi *asus = dev_get_drvdata(dev);
	पूर्णांक value;
	पूर्णांक state;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 10, &value);
	अगर (ret)
		वापस ret;

	value = clamp(value, 0, 255);

	state = asus_agfn_fan_speed_ग_लिखो(asus, 1, &value);
	अगर (state)
		pr_warn("Setting fan speed failed: %d\n", state);
	अन्यथा
		asus->fan_pwm_mode = ASUS_FAN_CTRL_MANUAL;

	वापस count;
पूर्ण

अटल sमाप_प्रकार fan1_input_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा asus_wmi *asus = dev_get_drvdata(dev);
	पूर्णांक value;
	पूर्णांक ret;

	चयन (asus->fan_type) अणु
	हाल FAN_TYPE_SPEC83:
		ret = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_CPU_FAN_CTRL,
					    &value);
		अगर (ret < 0)
			वापस ret;

		value &= 0xffff;
		अवरोध;

	हाल FAN_TYPE_AGFN:
		/* no speed पढ़ोable on manual mode */
		अगर (asus->fan_pwm_mode == ASUS_FAN_CTRL_MANUAL)
			वापस -ENXIO;

		ret = asus_agfn_fan_speed_पढ़ो(asus, 1, &value);
		अगर (ret) अणु
			pr_warn("reading fan speed failed: %d\n", ret);
			वापस -ENXIO;
		पूर्ण
		अवरोध;

	शेष:
		वापस -ENXIO;
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", value < 0 ? -1 : value*100);
पूर्ण

अटल sमाप_प्रकार pwm1_enable_show(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 अक्षर *buf)
अणु
	काष्ठा asus_wmi *asus = dev_get_drvdata(dev);

	/*
	 * Just पढ़ो back the cached pwm mode.
	 *
	 * For the CPU_FAN device, the spec indicates that we should be
	 * able to पढ़ो the device status and consult bit 19 to see अगर we
	 * are in Full On or Automatic mode. However, this करोes not work
	 * in practice on X532FL at least (the bit is always 0) and there's
	 * also nothing in the DSDT to indicate that this behaviour exists.
	 */
	वापस प्र_लिखो(buf, "%d\n", asus->fan_pwm_mode);
पूर्ण

अटल sमाप_प्रकार pwm1_enable_store(काष्ठा device *dev,
						  काष्ठा device_attribute *attr,
						  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा asus_wmi *asus = dev_get_drvdata(dev);
	पूर्णांक status = 0;
	पूर्णांक state;
	पूर्णांक value;
	पूर्णांक ret;
	u32 retval;

	ret = kstrtouपूर्णांक(buf, 10, &state);
	अगर (ret)
		वापस ret;

	अगर (asus->fan_type == FAN_TYPE_SPEC83) अणु
		चयन (state) अणु /* standard करोcumented hwmon values */
		हाल ASUS_FAN_CTRL_FULLSPEED:
			value = 1;
			अवरोध;
		हाल ASUS_FAN_CTRL_AUTO:
			value = 0;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = asus_wmi_set_devstate(ASUS_WMI_DEVID_CPU_FAN_CTRL,
					    value, &retval);
		अगर (ret)
			वापस ret;

		अगर (retval != 1)
			वापस -EIO;
	पूर्ण अन्यथा अगर (asus->fan_type == FAN_TYPE_AGFN) अणु
		चयन (state) अणु
		हाल ASUS_FAN_CTRL_MANUAL:
			अवरोध;

		हाल ASUS_FAN_CTRL_AUTO:
			status = asus_fan_set_स्वतः(asus);
			अगर (status)
				वापस status;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	asus->fan_pwm_mode = state;
	वापस count;
पूर्ण

अटल sमाप_प्रकार fan1_label_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", ASUS_FAN_DESC);
पूर्ण

अटल sमाप_प्रकार asus_hwmon_temp1(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा asus_wmi *asus = dev_get_drvdata(dev);
	u32 value;
	पूर्णांक err;

	err = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_THERMAL_CTRL, &value);
	अगर (err < 0)
		वापस err;

	वापस प्र_लिखो(buf, "%ld\n",
		       deci_kelvin_to_millicelsius(value & 0xFFFF));
पूर्ण

/* Fan1 */
अटल DEVICE_ATTR_RW(pwm1);
अटल DEVICE_ATTR_RW(pwm1_enable);
अटल DEVICE_ATTR_RO(fan1_input);
अटल DEVICE_ATTR_RO(fan1_label);

/* Temperature */
अटल DEVICE_ATTR(temp1_input, S_IRUGO, asus_hwmon_temp1, शून्य);

अटल काष्ठा attribute *hwmon_attributes[] = अणु
	&dev_attr_pwm1.attr,
	&dev_attr_pwm1_enable.attr,
	&dev_attr_fan1_input.attr,
	&dev_attr_fan1_label.attr,

	&dev_attr_temp1_input.attr,
	शून्य
पूर्ण;

अटल umode_t asus_hwmon_sysfs_is_visible(काष्ठा kobject *kobj,
					  काष्ठा attribute *attr, पूर्णांक idx)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा asus_wmi *asus = dev_get_drvdata(dev->parent);
	u32 value = ASUS_WMI_UNSUPPORTED_METHOD;

	अगर (attr == &dev_attr_pwm1.attr) अणु
		अगर (asus->fan_type != FAN_TYPE_AGFN)
			वापस 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fan1_input.attr
	    || attr == &dev_attr_fan1_label.attr
	    || attr == &dev_attr_pwm1_enable.attr) अणु
		अगर (asus->fan_type == FAN_TYPE_NONE)
			वापस 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_temp1_input.attr) अणु
		पूर्णांक err = asus_wmi_get_devstate(asus,
						ASUS_WMI_DEVID_THERMAL_CTRL,
						&value);

		अगर (err < 0)
			वापस 0; /* can't वापस negative here */

		/*
		 * If the temperature value in deci-Kelvin is near the असलolute
		 * zero temperature, something is clearly wrong
		 */
		अगर (value == 0 || value == 1)
			वापस 0;
	पूर्ण

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group hwmon_attribute_group = अणु
	.is_visible = asus_hwmon_sysfs_is_visible,
	.attrs = hwmon_attributes
पूर्ण;
__ATTRIBUTE_GROUPS(hwmon_attribute);

अटल पूर्णांक asus_wmi_hwmon_init(काष्ठा asus_wmi *asus)
अणु
	काष्ठा device *dev = &asus->platक्रमm_device->dev;
	काष्ठा device *hwmon;

	hwmon = devm_hwmon_device_रेजिस्टर_with_groups(dev, "asus", asus,
			hwmon_attribute_groups);

	अगर (IS_ERR(hwmon)) अणु
		pr_err("Could not register asus hwmon device\n");
		वापस PTR_ERR(hwmon);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक asus_wmi_fan_init(काष्ठा asus_wmi *asus)
अणु
	asus->fan_type = FAN_TYPE_NONE;
	asus->agfn_pwm = -1;

	अगर (asus_wmi_dev_is_present(asus, ASUS_WMI_DEVID_CPU_FAN_CTRL))
		asus->fan_type = FAN_TYPE_SPEC83;
	अन्यथा अगर (asus_wmi_has_agfn_fan(asus))
		asus->fan_type = FAN_TYPE_AGFN;

	अगर (asus->fan_type == FAN_TYPE_NONE)
		वापस -ENODEV;

	asus_fan_set_स्वतः(asus);
	asus->fan_pwm_mode = ASUS_FAN_CTRL_AUTO;
	वापस 0;
पूर्ण

/* Fan mode *******************************************************************/

अटल पूर्णांक fan_boost_mode_check_present(काष्ठा asus_wmi *asus)
अणु
	u32 result;
	पूर्णांक err;

	asus->fan_boost_mode_available = false;

	err = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_FAN_BOOST_MODE,
				    &result);
	अगर (err) अणु
		अगर (err == -ENODEV)
			वापस 0;
		अन्यथा
			वापस err;
	पूर्ण

	अगर ((result & ASUS_WMI_DSTS_PRESENCE_BIT) &&
			(result & ASUS_FAN_BOOST_MODES_MASK)) अणु
		asus->fan_boost_mode_available = true;
		asus->fan_boost_mode_mask = result & ASUS_FAN_BOOST_MODES_MASK;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fan_boost_mode_ग_लिखो(काष्ठा asus_wmi *asus)
अणु
	पूर्णांक err;
	u8 value;
	u32 retval;

	value = asus->fan_boost_mode;

	pr_info("Set fan boost mode: %u\n", value);
	err = asus_wmi_set_devstate(ASUS_WMI_DEVID_FAN_BOOST_MODE, value,
				    &retval);

	sysfs_notअगरy(&asus->platक्रमm_device->dev.kobj, शून्य,
			"fan_boost_mode");

	अगर (err) अणु
		pr_warn("Failed to set fan boost mode: %d\n", err);
		वापस err;
	पूर्ण

	अगर (retval != 1) अणु
		pr_warn("Failed to set fan boost mode (retval): 0x%x\n",
			retval);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fan_boost_mode_चयन_next(काष्ठा asus_wmi *asus)
अणु
	u8 mask = asus->fan_boost_mode_mask;

	अगर (asus->fan_boost_mode == ASUS_FAN_BOOST_MODE_NORMAL) अणु
		अगर (mask & ASUS_FAN_BOOST_MODE_OVERBOOST_MASK)
			asus->fan_boost_mode = ASUS_FAN_BOOST_MODE_OVERBOOST;
		अन्यथा अगर (mask & ASUS_FAN_BOOST_MODE_SILENT_MASK)
			asus->fan_boost_mode = ASUS_FAN_BOOST_MODE_SILENT;
	पूर्ण अन्यथा अगर (asus->fan_boost_mode == ASUS_FAN_BOOST_MODE_OVERBOOST) अणु
		अगर (mask & ASUS_FAN_BOOST_MODE_SILENT_MASK)
			asus->fan_boost_mode = ASUS_FAN_BOOST_MODE_SILENT;
		अन्यथा
			asus->fan_boost_mode = ASUS_FAN_BOOST_MODE_NORMAL;
	पूर्ण अन्यथा अणु
		asus->fan_boost_mode = ASUS_FAN_BOOST_MODE_NORMAL;
	पूर्ण

	वापस fan_boost_mode_ग_लिखो(asus);
पूर्ण

अटल sमाप_प्रकार fan_boost_mode_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा asus_wmi *asus = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", asus->fan_boost_mode);
पूर्ण

अटल sमाप_प्रकार fan_boost_mode_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक result;
	u8 new_mode;
	काष्ठा asus_wmi *asus = dev_get_drvdata(dev);
	u8 mask = asus->fan_boost_mode_mask;

	result = kstrtou8(buf, 10, &new_mode);
	अगर (result < 0) अणु
		pr_warn("Trying to store invalid value\n");
		वापस result;
	पूर्ण

	अगर (new_mode == ASUS_FAN_BOOST_MODE_OVERBOOST) अणु
		अगर (!(mask & ASUS_FAN_BOOST_MODE_OVERBOOST_MASK))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (new_mode == ASUS_FAN_BOOST_MODE_SILENT) अणु
		अगर (!(mask & ASUS_FAN_BOOST_MODE_SILENT_MASK))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (new_mode != ASUS_FAN_BOOST_MODE_NORMAL) अणु
		वापस -EINVAL;
	पूर्ण

	asus->fan_boost_mode = new_mode;
	fan_boost_mode_ग_लिखो(asus);

	वापस count;
पूर्ण

// Fan boost mode: 0 - normal, 1 - overboost, 2 - silent
अटल DEVICE_ATTR_RW(fan_boost_mode);

/* Throttle thermal policy ****************************************************/

अटल पूर्णांक throttle_thermal_policy_check_present(काष्ठा asus_wmi *asus)
अणु
	u32 result;
	पूर्णांक err;

	asus->throttle_thermal_policy_available = false;

	err = asus_wmi_get_devstate(asus,
				    ASUS_WMI_DEVID_THROTTLE_THERMAL_POLICY,
				    &result);
	अगर (err) अणु
		अगर (err == -ENODEV)
			वापस 0;
		वापस err;
	पूर्ण

	अगर (result & ASUS_WMI_DSTS_PRESENCE_BIT)
		asus->throttle_thermal_policy_available = true;

	वापस 0;
पूर्ण

अटल पूर्णांक throttle_thermal_policy_ग_लिखो(काष्ठा asus_wmi *asus)
अणु
	पूर्णांक err;
	u8 value;
	u32 retval;

	value = asus->throttle_thermal_policy_mode;

	err = asus_wmi_set_devstate(ASUS_WMI_DEVID_THROTTLE_THERMAL_POLICY,
				    value, &retval);

	sysfs_notअगरy(&asus->platक्रमm_device->dev.kobj, शून्य,
			"throttle_thermal_policy");

	अगर (err) अणु
		pr_warn("Failed to set throttle thermal policy: %d\n", err);
		वापस err;
	पूर्ण

	अगर (retval != 1) अणु
		pr_warn("Failed to set throttle thermal policy (retval): 0x%x\n",
			retval);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक throttle_thermal_policy_set_शेष(काष्ठा asus_wmi *asus)
अणु
	अगर (!asus->throttle_thermal_policy_available)
		वापस 0;

	asus->throttle_thermal_policy_mode = ASUS_THROTTLE_THERMAL_POLICY_DEFAULT;
	वापस throttle_thermal_policy_ग_लिखो(asus);
पूर्ण

अटल पूर्णांक throttle_thermal_policy_चयन_next(काष्ठा asus_wmi *asus)
अणु
	u8 new_mode = asus->throttle_thermal_policy_mode + 1;

	अगर (new_mode > ASUS_THROTTLE_THERMAL_POLICY_SILENT)
		new_mode = ASUS_THROTTLE_THERMAL_POLICY_DEFAULT;

	asus->throttle_thermal_policy_mode = new_mode;
	वापस throttle_thermal_policy_ग_लिखो(asus);
पूर्ण

अटल sमाप_प्रकार throttle_thermal_policy_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा asus_wmi *asus = dev_get_drvdata(dev);
	u8 mode = asus->throttle_thermal_policy_mode;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", mode);
पूर्ण

अटल sमाप_प्रकार throttle_thermal_policy_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक result;
	u8 new_mode;
	काष्ठा asus_wmi *asus = dev_get_drvdata(dev);

	result = kstrtou8(buf, 10, &new_mode);
	अगर (result < 0)
		वापस result;

	अगर (new_mode > ASUS_THROTTLE_THERMAL_POLICY_SILENT)
		वापस -EINVAL;

	asus->throttle_thermal_policy_mode = new_mode;
	throttle_thermal_policy_ग_लिखो(asus);

	वापस count;
पूर्ण

// Throttle thermal policy: 0 - शेष, 1 - overboost, 2 - silent
अटल DEVICE_ATTR_RW(throttle_thermal_policy);

/* Backlight ******************************************************************/

अटल पूर्णांक पढ़ो_backlight_घातer(काष्ठा asus_wmi *asus)
अणु
	पूर्णांक ret;

	अगर (asus->driver->quirks->store_backlight_घातer)
		ret = !asus->driver->panel_घातer;
	अन्यथा
		ret = asus_wmi_get_devstate_simple(asus,
						   ASUS_WMI_DEVID_BACKLIGHT);

	अगर (ret < 0)
		वापस ret;

	वापस ret ? FB_BLANK_UNBLANK : FB_BLANK_POWERDOWN;
पूर्ण

अटल पूर्णांक पढ़ो_brightness_max(काष्ठा asus_wmi *asus)
अणु
	u32 retval;
	पूर्णांक err;

	err = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_BRIGHTNESS, &retval);
	अगर (err < 0)
		वापस err;

	retval = retval & ASUS_WMI_DSTS_MAX_BRIGTH_MASK;
	retval >>= 8;

	अगर (!retval)
		वापस -ENODEV;

	वापस retval;
पूर्ण

अटल पूर्णांक पढ़ो_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा asus_wmi *asus = bl_get_data(bd);
	u32 retval;
	पूर्णांक err;

	err = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_BRIGHTNESS, &retval);
	अगर (err < 0)
		वापस err;

	वापस retval & ASUS_WMI_DSTS_BRIGHTNESS_MASK;
पूर्ण

अटल u32 get_scalar_command(काष्ठा backlight_device *bd)
अणु
	काष्ठा asus_wmi *asus = bl_get_data(bd);
	u32 ctrl_param = 0;

	अगर ((asus->driver->brightness < bd->props.brightness) ||
	    bd->props.brightness == bd->props.max_brightness)
		ctrl_param = 0x00008001;
	अन्यथा अगर ((asus->driver->brightness > bd->props.brightness) ||
		 bd->props.brightness == 0)
		ctrl_param = 0x00008000;

	asus->driver->brightness = bd->props.brightness;

	वापस ctrl_param;
पूर्ण

अटल पूर्णांक update_bl_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा asus_wmi *asus = bl_get_data(bd);
	u32 ctrl_param;
	पूर्णांक घातer, err = 0;

	घातer = पढ़ो_backlight_घातer(asus);
	अगर (घातer != -ENODEV && bd->props.घातer != घातer) अणु
		ctrl_param = !!(bd->props.घातer == FB_BLANK_UNBLANK);
		err = asus_wmi_set_devstate(ASUS_WMI_DEVID_BACKLIGHT,
					    ctrl_param, शून्य);
		अगर (asus->driver->quirks->store_backlight_घातer)
			asus->driver->panel_घातer = bd->props.घातer;

		/* When using scalar brightness, updating the brightness
		 * will mess with the backlight घातer */
		अगर (asus->driver->quirks->scalar_panel_brightness)
			वापस err;
	पूर्ण

	अगर (asus->driver->quirks->scalar_panel_brightness)
		ctrl_param = get_scalar_command(bd);
	अन्यथा
		ctrl_param = bd->props.brightness;

	err = asus_wmi_set_devstate(ASUS_WMI_DEVID_BRIGHTNESS,
				    ctrl_param, शून्य);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा backlight_ops asus_wmi_bl_ops = अणु
	.get_brightness = पढ़ो_brightness,
	.update_status = update_bl_status,
पूर्ण;

अटल पूर्णांक asus_wmi_backlight_notअगरy(काष्ठा asus_wmi *asus, पूर्णांक code)
अणु
	काष्ठा backlight_device *bd = asus->backlight_device;
	पूर्णांक old = bd->props.brightness;
	पूर्णांक new = old;

	अगर (code >= NOTIFY_BRNUP_MIN && code <= NOTIFY_BRNUP_MAX)
		new = code - NOTIFY_BRNUP_MIN + 1;
	अन्यथा अगर (code >= NOTIFY_BRNDOWN_MIN && code <= NOTIFY_BRNDOWN_MAX)
		new = code - NOTIFY_BRNDOWN_MIN;

	bd->props.brightness = new;
	backlight_update_status(bd);
	backlight_क्रमce_update(bd, BACKLIGHT_UPDATE_HOTKEY);

	वापस old;
पूर्ण

अटल पूर्णांक asus_wmi_backlight_init(काष्ठा asus_wmi *asus)
अणु
	काष्ठा backlight_device *bd;
	काष्ठा backlight_properties props;
	पूर्णांक max;
	पूर्णांक घातer;

	max = पढ़ो_brightness_max(asus);
	अगर (max < 0)
		वापस max;

	घातer = पढ़ो_backlight_घातer(asus);
	अगर (घातer == -ENODEV)
		घातer = FB_BLANK_UNBLANK;
	अन्यथा अगर (घातer < 0)
		वापस घातer;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = max;
	bd = backlight_device_रेजिस्टर(asus->driver->name,
				       &asus->platक्रमm_device->dev, asus,
				       &asus_wmi_bl_ops, &props);
	अगर (IS_ERR(bd)) अणु
		pr_err("Could not register backlight device\n");
		वापस PTR_ERR(bd);
	पूर्ण

	asus->backlight_device = bd;

	अगर (asus->driver->quirks->store_backlight_घातer)
		asus->driver->panel_घातer = घातer;

	bd->props.brightness = पढ़ो_brightness(bd);
	bd->props.घातer = घातer;
	backlight_update_status(bd);

	asus->driver->brightness = bd->props.brightness;

	वापस 0;
पूर्ण

अटल व्योम asus_wmi_backlight_निकास(काष्ठा asus_wmi *asus)
अणु
	backlight_device_unरेजिस्टर(asus->backlight_device);

	asus->backlight_device = शून्य;
पूर्ण

अटल पूर्णांक is_display_toggle(पूर्णांक code)
अणु
	/* display toggle keys */
	अगर ((code >= 0x61 && code <= 0x67) ||
	    (code >= 0x8c && code <= 0x93) ||
	    (code >= 0xa0 && code <= 0xa7) ||
	    (code >= 0xd0 && code <= 0xd5))
		वापस 1;

	वापस 0;
पूर्ण

/* Fn-lock ********************************************************************/

अटल bool asus_wmi_has_fnlock_key(काष्ठा asus_wmi *asus)
अणु
	u32 result;

	asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_FNLOCK, &result);

	वापस (result & ASUS_WMI_DSTS_PRESENCE_BIT) &&
		!(result & ASUS_WMI_FNLOCK_BIOS_DISABLED);
पूर्ण

अटल व्योम asus_wmi_fnlock_update(काष्ठा asus_wmi *asus)
अणु
	पूर्णांक mode = asus->fnlock_locked;

	asus_wmi_set_devstate(ASUS_WMI_DEVID_FNLOCK, mode, शून्य);
पूर्ण

/* WMI events *****************************************************************/

अटल पूर्णांक asus_wmi_get_event_code(u32 value)
अणु
	काष्ठा acpi_buffer response = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;
	पूर्णांक code;

	status = wmi_get_event_data(value, &response);
	अगर (ACPI_FAILURE(status)) अणु
		pr_warn("Failed to get WMI notify code: %s\n",
				acpi_क्रमmat_exception(status));
		वापस -EIO;
	पूर्ण

	obj = (जोड़ acpi_object *)response.poपूर्णांकer;

	अगर (obj && obj->type == ACPI_TYPE_INTEGER)
		code = (पूर्णांक)(obj->पूर्णांकeger.value & WMI_EVENT_MASK);
	अन्यथा
		code = -EIO;

	kमुक्त(obj);
	वापस code;
पूर्ण

अटल व्योम asus_wmi_handle_event_code(पूर्णांक code, काष्ठा asus_wmi *asus)
अणु
	अचिन्हित पूर्णांक key_value = 1;
	bool स्वतःrelease = 1;
	पूर्णांक result, orig_code;

	orig_code = code;

	अगर (asus->driver->key_filter) अणु
		asus->driver->key_filter(asus->driver, &code, &key_value,
					 &स्वतःrelease);
		अगर (code == ASUS_WMI_KEY_IGNORE)
			वापस;
	पूर्ण

	अगर (code >= NOTIFY_BRNUP_MIN && code <= NOTIFY_BRNUP_MAX)
		code = ASUS_WMI_BRN_UP;
	अन्यथा अगर (code >= NOTIFY_BRNDOWN_MIN && code <= NOTIFY_BRNDOWN_MAX)
		code = ASUS_WMI_BRN_DOWN;

	अगर (code == ASUS_WMI_BRN_DOWN || code == ASUS_WMI_BRN_UP) अणु
		अगर (acpi_video_get_backlight_type() == acpi_backlight_venकरोr) अणु
			asus_wmi_backlight_notअगरy(asus, orig_code);
			वापस;
		पूर्ण
	पूर्ण

	अगर (code == NOTIFY_KBD_BRTUP) अणु
		kbd_led_set_by_kbd(asus, asus->kbd_led_wk + 1);
		वापस;
	पूर्ण
	अगर (code == NOTIFY_KBD_BRTDWN) अणु
		kbd_led_set_by_kbd(asus, asus->kbd_led_wk - 1);
		वापस;
	पूर्ण
	अगर (code == NOTIFY_KBD_BRTTOGGLE) अणु
		अगर (asus->kbd_led_wk == asus->kbd_led.max_brightness)
			kbd_led_set_by_kbd(asus, 0);
		अन्यथा
			kbd_led_set_by_kbd(asus, asus->kbd_led_wk + 1);
		वापस;
	पूर्ण

	अगर (code == NOTIFY_FNLOCK_TOGGLE) अणु
		asus->fnlock_locked = !asus->fnlock_locked;
		asus_wmi_fnlock_update(asus);
		वापस;
	पूर्ण

	अगर (asus->driver->quirks->use_kbd_करोck_devid && code == NOTIFY_KBD_DOCK_CHANGE) अणु
		result = asus_wmi_get_devstate_simple(asus,
						      ASUS_WMI_DEVID_KBD_DOCK);
		अगर (result >= 0) अणु
			input_report_चयन(asus->inputdev, SW_TABLET_MODE,
					    !result);
			input_sync(asus->inputdev);
		पूर्ण
		वापस;
	पूर्ण

	अगर (asus->driver->quirks->use_lid_flip_devid && code == NOTIFY_LID_FLIP) अणु
		lid_flip_tablet_mode_get_state(asus);
		वापस;
	पूर्ण

	अगर (asus->fan_boost_mode_available && code == NOTIFY_KBD_FBM) अणु
		fan_boost_mode_चयन_next(asus);
		वापस;
	पूर्ण

	अगर (asus->throttle_thermal_policy_available && code == NOTIFY_KBD_TTP) अणु
		throttle_thermal_policy_चयन_next(asus);
		वापस;
	पूर्ण

	अगर (is_display_toggle(code) && asus->driver->quirks->no_display_toggle)
		वापस;

	अगर (!sparse_keymap_report_event(asus->inputdev, code,
					key_value, स्वतःrelease))
		pr_info("Unknown key %x pressed\n", code);
पूर्ण

अटल व्योम asus_wmi_notअगरy(u32 value, व्योम *context)
अणु
	काष्ठा asus_wmi *asus = context;
	पूर्णांक code;
	पूर्णांक i;

	क्रम (i = 0; i < WMI_EVENT_QUEUE_SIZE + 1; i++) अणु
		code = asus_wmi_get_event_code(value);
		अगर (code < 0) अणु
			pr_warn("Failed to get notify code: %d\n", code);
			वापस;
		पूर्ण

		अगर (code == WMI_EVENT_QUEUE_END || code == WMI_EVENT_MASK)
			वापस;

		asus_wmi_handle_event_code(code, asus);

		/*
		 * Double check that queue is present:
		 * ATK (with queue) uses 0xff, ASUSWMI (without) 0xd2.
		 */
		अगर (!asus->wmi_event_queue || value != WMI_EVENT_VALUE_ATK)
			वापस;
	पूर्ण

	pr_warn("Failed to process event queue, last code: 0x%x\n", code);
पूर्ण

अटल पूर्णांक asus_wmi_notअगरy_queue_flush(काष्ठा asus_wmi *asus)
अणु
	पूर्णांक code;
	पूर्णांक i;

	क्रम (i = 0; i < WMI_EVENT_QUEUE_SIZE + 1; i++) अणु
		code = asus_wmi_get_event_code(WMI_EVENT_VALUE_ATK);
		अगर (code < 0) अणु
			pr_warn("Failed to get event during flush: %d\n", code);
			वापस code;
		पूर्ण

		अगर (code == WMI_EVENT_QUEUE_END || code == WMI_EVENT_MASK)
			वापस 0;
	पूर्ण

	pr_warn("Failed to flush event queue\n");
	वापस -EIO;
पूर्ण

/* Sysfs **********************************************************************/

अटल sमाप_प्रकार store_sys_wmi(काष्ठा asus_wmi *asus, पूर्णांक devid,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 retval;
	पूर्णांक err, value;

	value = asus_wmi_get_devstate_simple(asus, devid);
	अगर (value < 0)
		वापस value;

	err = kstrtoपूर्णांक(buf, 0, &value);
	अगर (err)
		वापस err;

	err = asus_wmi_set_devstate(devid, value, &retval);
	अगर (err < 0)
		वापस err;

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_sys_wmi(काष्ठा asus_wmi *asus, पूर्णांक devid, अक्षर *buf)
अणु
	पूर्णांक value = asus_wmi_get_devstate_simple(asus, devid);

	अगर (value < 0)
		वापस value;

	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

#घोषणा ASUS_WMI_CREATE_DEVICE_ATTR(_name, _mode, _cm)			\
	अटल sमाप_प्रकार show_##_name(काष्ठा device *dev,			\
				    काष्ठा device_attribute *attr,	\
				    अक्षर *buf)				\
	अणु								\
		काष्ठा asus_wmi *asus = dev_get_drvdata(dev);		\
									\
		वापस show_sys_wmi(asus, _cm, buf);			\
	पूर्ण								\
	अटल sमाप_प्रकार store_##_name(काष्ठा device *dev,		\
				     काष्ठा device_attribute *attr,	\
				     स्थिर अक्षर *buf, माप_प्रकार count)	\
	अणु								\
		काष्ठा asus_wmi *asus = dev_get_drvdata(dev);		\
									\
		वापस store_sys_wmi(asus, _cm, buf, count);		\
	पूर्ण								\
	अटल काष्ठा device_attribute dev_attr_##_name = अणु		\
		.attr = अणु						\
			.name = __stringअगरy(_name),			\
			.mode = _mode पूर्ण,				\
		.show   = show_##_name,					\
		.store  = store_##_name,				\
	पूर्ण

ASUS_WMI_CREATE_DEVICE_ATTR(touchpad, 0644, ASUS_WMI_DEVID_TOUCHPAD);
ASUS_WMI_CREATE_DEVICE_ATTR(camera, 0644, ASUS_WMI_DEVID_CAMERA);
ASUS_WMI_CREATE_DEVICE_ATTR(cardr, 0644, ASUS_WMI_DEVID_CARDREADER);
ASUS_WMI_CREATE_DEVICE_ATTR(lid_resume, 0644, ASUS_WMI_DEVID_LID_RESUME);
ASUS_WMI_CREATE_DEVICE_ATTR(als_enable, 0644, ASUS_WMI_DEVID_ALS_ENABLE);

अटल sमाप_प्रकार cpufv_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक value, rv;

	rv = kstrtoपूर्णांक(buf, 0, &value);
	अगर (rv)
		वापस rv;

	अगर (value < 0 || value > 2)
		वापस -EINVAL;

	rv = asus_wmi_evaluate_method(ASUS_WMI_METHODID_CFVS, value, 0, शून्य);
	अगर (rv < 0)
		वापस rv;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_WO(cpufv);

अटल काष्ठा attribute *platक्रमm_attributes[] = अणु
	&dev_attr_cpufv.attr,
	&dev_attr_camera.attr,
	&dev_attr_cardr.attr,
	&dev_attr_touchpad.attr,
	&dev_attr_lid_resume.attr,
	&dev_attr_als_enable.attr,
	&dev_attr_fan_boost_mode.attr,
	&dev_attr_throttle_thermal_policy.attr,
	शून्य
पूर्ण;

अटल umode_t asus_sysfs_is_visible(काष्ठा kobject *kobj,
				    काष्ठा attribute *attr, पूर्णांक idx)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा asus_wmi *asus = dev_get_drvdata(dev);
	bool ok = true;
	पूर्णांक devid = -1;

	अगर (attr == &dev_attr_camera.attr)
		devid = ASUS_WMI_DEVID_CAMERA;
	अन्यथा अगर (attr == &dev_attr_cardr.attr)
		devid = ASUS_WMI_DEVID_CARDREADER;
	अन्यथा अगर (attr == &dev_attr_touchpad.attr)
		devid = ASUS_WMI_DEVID_TOUCHPAD;
	अन्यथा अगर (attr == &dev_attr_lid_resume.attr)
		devid = ASUS_WMI_DEVID_LID_RESUME;
	अन्यथा अगर (attr == &dev_attr_als_enable.attr)
		devid = ASUS_WMI_DEVID_ALS_ENABLE;
	अन्यथा अगर (attr == &dev_attr_fan_boost_mode.attr)
		ok = asus->fan_boost_mode_available;
	अन्यथा अगर (attr == &dev_attr_throttle_thermal_policy.attr)
		ok = asus->throttle_thermal_policy_available;

	अगर (devid != -1)
		ok = !(asus_wmi_get_devstate_simple(asus, devid) < 0);

	वापस ok ? attr->mode : 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group platक्रमm_attribute_group = अणु
	.is_visible = asus_sysfs_is_visible,
	.attrs = platक्रमm_attributes
पूर्ण;

अटल व्योम asus_wmi_sysfs_निकास(काष्ठा platक्रमm_device *device)
अणु
	sysfs_हटाओ_group(&device->dev.kobj, &platक्रमm_attribute_group);
पूर्ण

अटल पूर्णांक asus_wmi_sysfs_init(काष्ठा platक्रमm_device *device)
अणु
	वापस sysfs_create_group(&device->dev.kobj, &platक्रमm_attribute_group);
पूर्ण

/* Platक्रमm device ************************************************************/

अटल पूर्णांक asus_wmi_platक्रमm_init(काष्ठा asus_wmi *asus)
अणु
	काष्ठा device *dev = &asus->platक्रमm_device->dev;
	अक्षर *wmi_uid;
	पूर्णांक rv;

	/* INIT enable hotkeys on some models */
	अगर (!asus_wmi_evaluate_method(ASUS_WMI_METHODID_INIT, 0, 0, &rv))
		pr_info("Initialization: %#x\n", rv);

	/* We करोn't know yet what to करो with this version... */
	अगर (!asus_wmi_evaluate_method(ASUS_WMI_METHODID_SPEC, 0, 0x9, &rv)) अणु
		pr_info("BIOS WMI version: %d.%d\n", rv >> 16, rv & 0xFF);
		asus->spec = rv;
	पूर्ण

	/*
	 * The SFUN method probably allows the original driver to get the list
	 * of features supported by a given model. For now, 0x0100 or 0x0800
	 * bit signअगरies that the laptop is equipped with a Wi-Fi MiniPCI card.
	 * The signअगरicance of others is yet to be found.
	 */
	अगर (!asus_wmi_evaluate_method(ASUS_WMI_METHODID_SFUN, 0, 0, &rv)) अणु
		pr_info("SFUN value: %#x\n", rv);
		asus->sfun = rv;
	पूर्ण

	/*
	 * Eee PC and Notebooks seems to have dअगरferent method_id क्रम DSTS,
	 * but it may also be related to the BIOS's SPEC.
	 * Note, on most Eeepc, there is no way to check अगर a method exist
	 * or note, जबतक on notebooks, they वापसs 0xFFFFFFFE on failure,
	 * but once again, SPEC may probably be used क्रम that kind of things.
	 *
	 * Additionally at least TUF Gaming series laptops वापस nothing क्रम
	 * unknown methods, so the detection in this way is not possible.
	 *
	 * There is strong indication that only ACPI WMI devices that have _UID
	 * equal to "ASUSWMI" use DCTS whereas those with "ATK" use DSTS.
	 */
	wmi_uid = wmi_get_acpi_device_uid(ASUS_WMI_MGMT_GUID);
	अगर (!wmi_uid)
		वापस -ENODEV;

	अगर (!म_भेद(wmi_uid, ASUS_ACPI_UID_ASUSWMI)) अणु
		dev_info(dev, "Detected ASUSWMI, use DCTS\n");
		asus->dsts_id = ASUS_WMI_METHODID_DCTS;
	पूर्ण अन्यथा अणु
		dev_info(dev, "Detected %s, not ASUSWMI, use DSTS\n", wmi_uid);
		asus->dsts_id = ASUS_WMI_METHODID_DSTS;
	पूर्ण

	/*
	 * Some devices can have multiple event codes stored in a queue beक्रमe
	 * the module load अगर it was unloaded पूर्णांकermittently after calling
	 * the INIT method (enables event handling). The WMI notअगरy handler is
	 * expected to retrieve all event codes until a retrieved code equals
	 * queue end marker (One or Ones). Old codes are flushed from the queue
	 * upon module load. Not enabling this when it should be has minimal
	 * visible impact so fall back अगर anything goes wrong.
	 */
	wmi_uid = wmi_get_acpi_device_uid(asus->driver->event_guid);
	अगर (wmi_uid && !म_भेद(wmi_uid, ASUS_ACPI_UID_ATK)) अणु
		dev_info(dev, "Detected ATK, enable event queue\n");

		अगर (!asus_wmi_notअगरy_queue_flush(asus))
			asus->wmi_event_queue = true;
	पूर्ण

	/* CWAP allow to define the behavior of the Fn+F2 key,
	 * this method करोesn't seems to be present on Eee PCs */
	अगर (asus->driver->quirks->wapf >= 0)
		asus_wmi_set_devstate(ASUS_WMI_DEVID_CWAP,
				      asus->driver->quirks->wapf, शून्य);

	वापस 0;
पूर्ण

/* debugfs ********************************************************************/

काष्ठा asus_wmi_debugfs_node अणु
	काष्ठा asus_wmi *asus;
	अक्षर *name;
	पूर्णांक (*show) (काष्ठा seq_file *m, व्योम *data);
पूर्ण;

अटल पूर्णांक show_dsts(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा asus_wmi *asus = m->निजी;
	पूर्णांक err;
	u32 retval = -1;

	err = asus_wmi_get_devstate(asus, asus->debug.dev_id, &retval);
	अगर (err < 0)
		वापस err;

	seq_म_लिखो(m, "DSTS(%#x) = %#x\n", asus->debug.dev_id, retval);

	वापस 0;
पूर्ण

अटल पूर्णांक show_devs(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा asus_wmi *asus = m->निजी;
	पूर्णांक err;
	u32 retval = -1;

	err = asus_wmi_set_devstate(asus->debug.dev_id, asus->debug.ctrl_param,
				    &retval);
	अगर (err < 0)
		वापस err;

	seq_म_लिखो(m, "DEVS(%#x, %#x) = %#x\n", asus->debug.dev_id,
		   asus->debug.ctrl_param, retval);

	वापस 0;
पूर्ण

अटल पूर्णांक show_call(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा asus_wmi *asus = m->निजी;
	काष्ठा bios_args args = अणु
		.arg0 = asus->debug.dev_id,
		.arg1 = asus->debug.ctrl_param,
	पूर्ण;
	काष्ठा acpi_buffer input = अणु (acpi_size) माप(args), &args पूर्ण;
	काष्ठा acpi_buffer output = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;

	status = wmi_evaluate_method(ASUS_WMI_MGMT_GUID,
				     0, asus->debug.method_id,
				     &input, &output);

	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	obj = (जोड़ acpi_object *)output.poपूर्णांकer;
	अगर (obj && obj->type == ACPI_TYPE_INTEGER)
		seq_म_लिखो(m, "%#x(%#x, %#x) = %#x\n", asus->debug.method_id,
			   asus->debug.dev_id, asus->debug.ctrl_param,
			   (u32) obj->पूर्णांकeger.value);
	अन्यथा
		seq_म_लिखो(m, "%#x(%#x, %#x) = t:%d\n", asus->debug.method_id,
			   asus->debug.dev_id, asus->debug.ctrl_param,
			   obj ? obj->type : -1);

	kमुक्त(obj);

	वापस 0;
पूर्ण

अटल काष्ठा asus_wmi_debugfs_node asus_wmi_debug_files[] = अणु
	अणुशून्य, "devs", show_devsपूर्ण,
	अणुशून्य, "dsts", show_dstsपूर्ण,
	अणुशून्य, "call", show_callपूर्ण,
पूर्ण;

अटल पूर्णांक asus_wmi_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा asus_wmi_debugfs_node *node = inode->i_निजी;

	वापस single_खोलो(file, node->show, node->asus);
पूर्ण

अटल स्थिर काष्ठा file_operations asus_wmi_debugfs_io_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = asus_wmi_debugfs_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल व्योम asus_wmi_debugfs_निकास(काष्ठा asus_wmi *asus)
अणु
	debugfs_हटाओ_recursive(asus->debug.root);
पूर्ण

अटल व्योम asus_wmi_debugfs_init(काष्ठा asus_wmi *asus)
अणु
	पूर्णांक i;

	asus->debug.root = debugfs_create_dir(asus->driver->name, शून्य);

	debugfs_create_x32("method_id", S_IRUGO | S_IWUSR, asus->debug.root,
			   &asus->debug.method_id);

	debugfs_create_x32("dev_id", S_IRUGO | S_IWUSR, asus->debug.root,
			   &asus->debug.dev_id);

	debugfs_create_x32("ctrl_param", S_IRUGO | S_IWUSR, asus->debug.root,
			   &asus->debug.ctrl_param);

	क्रम (i = 0; i < ARRAY_SIZE(asus_wmi_debug_files); i++) अणु
		काष्ठा asus_wmi_debugfs_node *node = &asus_wmi_debug_files[i];

		node->asus = asus;
		debugfs_create_file(node->name, S_IFREG | S_IRUGO,
				    asus->debug.root, node,
				    &asus_wmi_debugfs_io_ops);
	पूर्ण
पूर्ण

/* Init / निकास ****************************************************************/

अटल पूर्णांक asus_wmi_add(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_driver *pdrv = to_platक्रमm_driver(pdev->dev.driver);
	काष्ठा asus_wmi_driver *wdrv = to_asus_wmi_driver(pdrv);
	काष्ठा asus_wmi *asus;
	स्थिर अक्षर *chassis_type;
	acpi_status status;
	पूर्णांक err;
	u32 result;

	asus = kzalloc(माप(काष्ठा asus_wmi), GFP_KERNEL);
	अगर (!asus)
		वापस -ENOMEM;

	asus->driver = wdrv;
	asus->platक्रमm_device = pdev;
	wdrv->platक्रमm_device = pdev;
	platक्रमm_set_drvdata(asus->platक्रमm_device, asus);

	अगर (wdrv->detect_quirks)
		wdrv->detect_quirks(asus->driver);

	err = asus_wmi_platक्रमm_init(asus);
	अगर (err)
		जाओ fail_platक्रमm;

	err = fan_boost_mode_check_present(asus);
	अगर (err)
		जाओ fail_fan_boost_mode;

	err = throttle_thermal_policy_check_present(asus);
	अगर (err)
		जाओ fail_throttle_thermal_policy;
	अन्यथा
		throttle_thermal_policy_set_शेष(asus);

	err = asus_wmi_sysfs_init(asus->platक्रमm_device);
	अगर (err)
		जाओ fail_sysfs;

	err = asus_wmi_input_init(asus);
	अगर (err)
		जाओ fail_input;

	err = asus_wmi_fan_init(asus); /* probably no problems on error */

	err = asus_wmi_hwmon_init(asus);
	अगर (err)
		जाओ fail_hwmon;

	err = asus_wmi_led_init(asus);
	अगर (err)
		जाओ fail_leds;

	asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_WLAN, &result);
	अगर (result & (ASUS_WMI_DSTS_PRESENCE_BIT | ASUS_WMI_DSTS_USER_BIT))
		asus->driver->wlan_ctrl_by_user = 1;

	अगर (!(asus->driver->wlan_ctrl_by_user && ashs_present())) अणु
		err = asus_wmi_rfसमाप्त_init(asus);
		अगर (err)
			जाओ fail_rfसमाप्त;
	पूर्ण

	अगर (asus->driver->quirks->wmi_क्रमce_als_set)
		asus_wmi_set_als();

	/* Some Asus desktop boards export an acpi-video backlight पूर्णांकerface,
	   stop this from showing up */
	chassis_type = dmi_get_प्रणाली_info(DMI_CHASSIS_TYPE);
	अगर (chassis_type && !म_भेद(chassis_type, "3"))
		acpi_video_set_dmi_backlight_type(acpi_backlight_venकरोr);

	अगर (asus->driver->quirks->wmi_backlight_घातer)
		acpi_video_set_dmi_backlight_type(acpi_backlight_venकरोr);

	अगर (asus->driver->quirks->wmi_backlight_native)
		acpi_video_set_dmi_backlight_type(acpi_backlight_native);

	अगर (asus->driver->quirks->xusb2pr)
		asus_wmi_set_xusb2pr(asus);

	अगर (acpi_video_get_backlight_type() == acpi_backlight_venकरोr) अणु
		err = asus_wmi_backlight_init(asus);
		अगर (err && err != -ENODEV)
			जाओ fail_backlight;
	पूर्ण अन्यथा अगर (asus->driver->quirks->wmi_backlight_set_devstate)
		err = asus_wmi_set_devstate(ASUS_WMI_DEVID_BACKLIGHT, 2, शून्य);

	अगर (asus_wmi_has_fnlock_key(asus)) अणु
		asus->fnlock_locked = fnlock_शेष;
		asus_wmi_fnlock_update(asus);
	पूर्ण

	status = wmi_install_notअगरy_handler(asus->driver->event_guid,
					    asus_wmi_notअगरy, asus);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Unable to register notify handler - %d\n", status);
		err = -ENODEV;
		जाओ fail_wmi_handler;
	पूर्ण

	asus_wmi_battery_init(asus);

	asus_wmi_debugfs_init(asus);

	वापस 0;

fail_wmi_handler:
	asus_wmi_backlight_निकास(asus);
fail_backlight:
	asus_wmi_rfसमाप्त_निकास(asus);
fail_rfसमाप्त:
	asus_wmi_led_निकास(asus);
fail_leds:
fail_hwmon:
	asus_wmi_input_निकास(asus);
fail_input:
	asus_wmi_sysfs_निकास(asus->platक्रमm_device);
fail_sysfs:
fail_throttle_thermal_policy:
fail_fan_boost_mode:
fail_platक्रमm:
	kमुक्त(asus);
	वापस err;
पूर्ण

अटल पूर्णांक asus_wmi_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा asus_wmi *asus;

	asus = platक्रमm_get_drvdata(device);
	wmi_हटाओ_notअगरy_handler(asus->driver->event_guid);
	asus_wmi_backlight_निकास(asus);
	asus_wmi_input_निकास(asus);
	asus_wmi_led_निकास(asus);
	asus_wmi_rfसमाप्त_निकास(asus);
	asus_wmi_debugfs_निकास(asus);
	asus_wmi_sysfs_निकास(asus->platक्रमm_device);
	asus_fan_set_स्वतः(asus);
	asus_wmi_battery_निकास(asus);

	kमुक्त(asus);
	वापस 0;
पूर्ण

/* Platक्रमm driver - hibernate/resume callbacks *******************************/

अटल पूर्णांक asus_hotk_thaw(काष्ठा device *device)
अणु
	काष्ठा asus_wmi *asus = dev_get_drvdata(device);

	अगर (asus->wlan.rfसमाप्त) अणु
		bool wlan;

		/*
		 * Work around bios bug - acpi _PTS turns off the wireless led
		 * during suspend.  Normally it restores it on resume, but
		 * we should kick it ourselves in हाल hibernation is पातed.
		 */
		wlan = asus_wmi_get_devstate_simple(asus, ASUS_WMI_DEVID_WLAN);
		asus_wmi_set_devstate(ASUS_WMI_DEVID_WLAN, wlan, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक asus_hotk_resume(काष्ठा device *device)
अणु
	काष्ठा asus_wmi *asus = dev_get_drvdata(device);

	अगर (!IS_ERR_OR_शून्य(asus->kbd_led.dev))
		kbd_led_update(asus);

	अगर (asus_wmi_has_fnlock_key(asus))
		asus_wmi_fnlock_update(asus);

	अगर (asus->driver->quirks->use_lid_flip_devid)
		lid_flip_tablet_mode_get_state(asus);

	वापस 0;
पूर्ण

अटल पूर्णांक asus_hotk_restore(काष्ठा device *device)
अणु
	काष्ठा asus_wmi *asus = dev_get_drvdata(device);
	पूर्णांक bl;

	/* Refresh both wlan rfसमाप्त state and pci hotplug */
	अगर (asus->wlan.rfसमाप्त)
		asus_rfसमाप्त_hotplug(asus);

	अगर (asus->bluetooth.rfसमाप्त) अणु
		bl = !asus_wmi_get_devstate_simple(asus,
						   ASUS_WMI_DEVID_BLUETOOTH);
		rfसमाप्त_set_sw_state(asus->bluetooth.rfसमाप्त, bl);
	पूर्ण
	अगर (asus->wimax.rfसमाप्त) अणु
		bl = !asus_wmi_get_devstate_simple(asus, ASUS_WMI_DEVID_WIMAX);
		rfसमाप्त_set_sw_state(asus->wimax.rfसमाप्त, bl);
	पूर्ण
	अगर (asus->wwan3g.rfसमाप्त) अणु
		bl = !asus_wmi_get_devstate_simple(asus, ASUS_WMI_DEVID_WWAN3G);
		rfसमाप्त_set_sw_state(asus->wwan3g.rfसमाप्त, bl);
	पूर्ण
	अगर (asus->gps.rfसमाप्त) अणु
		bl = !asus_wmi_get_devstate_simple(asus, ASUS_WMI_DEVID_GPS);
		rfसमाप्त_set_sw_state(asus->gps.rfसमाप्त, bl);
	पूर्ण
	अगर (asus->uwb.rfसमाप्त) अणु
		bl = !asus_wmi_get_devstate_simple(asus, ASUS_WMI_DEVID_UWB);
		rfसमाप्त_set_sw_state(asus->uwb.rfसमाप्त, bl);
	पूर्ण
	अगर (!IS_ERR_OR_शून्य(asus->kbd_led.dev))
		kbd_led_update(asus);

	अगर (asus_wmi_has_fnlock_key(asus))
		asus_wmi_fnlock_update(asus);

	अगर (asus->driver->quirks->use_lid_flip_devid)
		lid_flip_tablet_mode_get_state(asus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops asus_pm_ops = अणु
	.thaw = asus_hotk_thaw,
	.restore = asus_hotk_restore,
	.resume = asus_hotk_resume,
पूर्ण;

/* Registration ***************************************************************/

अटल पूर्णांक asus_wmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_driver *pdrv = to_platक्रमm_driver(pdev->dev.driver);
	काष्ठा asus_wmi_driver *wdrv = to_asus_wmi_driver(pdrv);
	पूर्णांक ret;

	अगर (!wmi_has_guid(ASUS_WMI_MGMT_GUID)) अणु
		pr_warn("ASUS Management GUID not found\n");
		वापस -ENODEV;
	पूर्ण

	अगर (wdrv->event_guid && !wmi_has_guid(wdrv->event_guid)) अणु
		pr_warn("ASUS Event GUID not found\n");
		वापस -ENODEV;
	पूर्ण

	अगर (wdrv->probe) अणु
		ret = wdrv->probe(pdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस asus_wmi_add(pdev);
पूर्ण

अटल bool used;

पूर्णांक __init_or_module asus_wmi_रेजिस्टर_driver(काष्ठा asus_wmi_driver *driver)
अणु
	काष्ठा platक्रमm_driver *platक्रमm_driver;
	काष्ठा platक्रमm_device *platक्रमm_device;

	अगर (used)
		वापस -EBUSY;

	platक्रमm_driver = &driver->platक्रमm_driver;
	platक्रमm_driver->हटाओ = asus_wmi_हटाओ;
	platक्रमm_driver->driver.owner = driver->owner;
	platक्रमm_driver->driver.name = driver->name;
	platक्रमm_driver->driver.pm = &asus_pm_ops;

	platक्रमm_device = platक्रमm_create_bundle(platक्रमm_driver,
						 asus_wmi_probe,
						 शून्य, 0, शून्य, 0);
	अगर (IS_ERR(platक्रमm_device))
		वापस PTR_ERR(platक्रमm_device);

	used = true;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(asus_wmi_रेजिस्टर_driver);

व्योम asus_wmi_unरेजिस्टर_driver(काष्ठा asus_wmi_driver *driver)
अणु
	platक्रमm_device_unरेजिस्टर(driver->platक्रमm_device);
	platक्रमm_driver_unरेजिस्टर(&driver->platक्रमm_driver);
	used = false;
पूर्ण
EXPORT_SYMBOL_GPL(asus_wmi_unरेजिस्टर_driver);

अटल पूर्णांक __init asus_wmi_init(व्योम)
अणु
	pr_info("ASUS WMI generic driver loaded\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास asus_wmi_निकास(व्योम)
अणु
	pr_info("ASUS WMI generic driver unloaded\n");
पूर्ण

module_init(asus_wmi_init);
module_निकास(asus_wmi_निकास);
