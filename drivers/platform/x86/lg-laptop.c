<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * lg-laptop.c - LG Gram ACPI features and hotkeys Driver
 *
 * Copyright (C) 2018 Matan Ziv-Av <matan@svgalib.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

#घोषणा LED_DEVICE(_name, max) काष्ठा led_classdev _name = अणु \
	.name           = __stringअगरy(_name),   \
	.max_brightness = max,                  \
	.brightness_set = _name##_set,          \
	.brightness_get = _name##_get,          \
पूर्ण

MODULE_AUTHOR("Matan Ziv-Av");
MODULE_DESCRIPTION("LG WMI Hotkey Driver");
MODULE_LICENSE("GPL");

#घोषणा WMI_EVENT_GUID0	"E4FB94F9-7F2B-4173-AD1A-CD1D95086248"
#घोषणा WMI_EVENT_GUID1	"023B133E-49D1-4E10-B313-698220140DC2"
#घोषणा WMI_EVENT_GUID2	"37BE1AC0-C3F2-4B1F-BFBE-8FDEAF2814D6"
#घोषणा WMI_EVENT_GUID3	"911BAD44-7DF8-4FBB-9319-BABA1C4B293B"
#घोषणा WMI_METHOD_WMAB "C3A72B38-D3EF-42D3-8CBB-D5A57049F66D"
#घोषणा WMI_METHOD_WMBB "2B4F501A-BD3C-4394-8DCF-00A7D2BC8210"
#घोषणा WMI_EVENT_GUID  WMI_EVENT_GUID0

#घोषणा WMAB_METHOD     "\\XINI.WMAB"
#घोषणा WMBB_METHOD     "\\XINI.WMBB"
#घोषणा SB_GGOV_METHOD  "\\_SB.GGOV"
#घोषणा GOV_TLED        0x2020008
#घोषणा WM_GET          1
#घोषणा WM_SET          2
#घोषणा WM_KEY_LIGHT    0x400
#घोषणा WM_TLED         0x404
#घोषणा WM_FN_LOCK      0x407
#घोषणा WM_BATT_LIMIT   0x61
#घोषणा WM_READER_MODE  0xBF
#घोषणा WM_FAN_MODE	0x33
#घोषणा WMBB_USB_CHARGE 0x10B
#घोषणा WMBB_BATT_LIMIT 0x10C

#घोषणा PLATFORM_NAME   "lg-laptop"

MODULE_ALIAS("wmi:" WMI_EVENT_GUID0);
MODULE_ALIAS("wmi:" WMI_EVENT_GUID1);
MODULE_ALIAS("wmi:" WMI_EVENT_GUID2);
MODULE_ALIAS("wmi:" WMI_EVENT_GUID3);
MODULE_ALIAS("wmi:" WMI_METHOD_WMAB);
MODULE_ALIAS("wmi:" WMI_METHOD_WMBB);
MODULE_ALIAS("acpi*:LGEX0815:*");

अटल काष्ठा platक्रमm_device *pf_device;
अटल काष्ठा input_dev *wmi_input_dev;

अटल u32 inited;
#घोषणा INIT_INPUT_WMI_0        0x01
#घोषणा INIT_INPUT_WMI_2        0x02
#घोषणा INIT_INPUT_ACPI         0x04
#घोषणा INIT_SPARSE_KEYMAP      0x80

अटल स्थिर काष्ठा key_entry wmi_keymap[] = अणु
	अणुKE_KEY, 0x70, अणुKEY_F15पूर्ण पूर्ण,	 /* LG control panel (F1) */
	अणुKE_KEY, 0x74, अणुKEY_F13पूर्ण पूर्ण,	 /* Touchpad toggle (F5) */
	अणुKE_KEY, 0xf020000, अणुKEY_F14पूर्ण पूर्ण, /* Read mode (F9) */
	अणुKE_KEY, 0x10000000, अणुKEY_F16पूर्ण पूर्ण,/* Keyboard backlight (F8) - pressing
					  * this key both sends an event and
					  * changes backlight level.
					  */
	अणुKE_KEY, 0x80, अणुKEY_RFKILLपूर्ण पूर्ण,
	अणुKE_END, 0पूर्ण
पूर्ण;

अटल पूर्णांक ggov(u32 arg0)
अणु
	जोड़ acpi_object args[1];
	जोड़ acpi_object *r;
	acpi_status status;
	acpi_handle handle;
	काष्ठा acpi_object_list arg;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	पूर्णांक res;

	args[0].type = ACPI_TYPE_INTEGER;
	args[0].पूर्णांकeger.value = arg0;

	status = acpi_get_handle(शून्य, (acpi_string) SB_GGOV_METHOD, &handle);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Cannot get handle");
		वापस -ENODEV;
	पूर्ण

	arg.count = 1;
	arg.poपूर्णांकer = args;

	status = acpi_evaluate_object(handle, शून्य, &arg, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_err(handle, "GGOV: call failed.\n");
		वापस -EINVAL;
	पूर्ण

	r = buffer.poपूर्णांकer;
	अगर (r->type != ACPI_TYPE_INTEGER) अणु
		kमुक्त(r);
		वापस -EINVAL;
	पूर्ण

	res = r->पूर्णांकeger.value;
	kमुक्त(r);

	वापस res;
पूर्ण

अटल जोड़ acpi_object *lg_wmab(u32 method, u32 arg1, u32 arg2)
अणु
	जोड़ acpi_object args[3];
	acpi_status status;
	acpi_handle handle;
	काष्ठा acpi_object_list arg;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;

	args[0].type = ACPI_TYPE_INTEGER;
	args[0].पूर्णांकeger.value = method;
	args[1].type = ACPI_TYPE_INTEGER;
	args[1].पूर्णांकeger.value = arg1;
	args[2].type = ACPI_TYPE_INTEGER;
	args[2].पूर्णांकeger.value = arg2;

	status = acpi_get_handle(शून्य, (acpi_string) WMAB_METHOD, &handle);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Cannot get handle");
		वापस शून्य;
	पूर्ण

	arg.count = 3;
	arg.poपूर्णांकer = args;

	status = acpi_evaluate_object(handle, शून्य, &arg, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_err(handle, "WMAB: call failed.\n");
		वापस शून्य;
	पूर्ण

	वापस buffer.poपूर्णांकer;
पूर्ण

अटल जोड़ acpi_object *lg_wmbb(u32 method_id, u32 arg1, u32 arg2)
अणु
	जोड़ acpi_object args[3];
	acpi_status status;
	acpi_handle handle;
	काष्ठा acpi_object_list arg;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	u8 buf[32];

	*(u32 *)buf = method_id;
	*(u32 *)(buf + 4) = arg1;
	*(u32 *)(buf + 16) = arg2;
	args[0].type = ACPI_TYPE_INTEGER;
	args[0].पूर्णांकeger.value = 0; /* ignored */
	args[1].type = ACPI_TYPE_INTEGER;
	args[1].पूर्णांकeger.value = 1; /* Must be 1 or 2. Does not matter which */
	args[2].type = ACPI_TYPE_BUFFER;
	args[2].buffer.length = 32;
	args[2].buffer.poपूर्णांकer = buf;

	status = acpi_get_handle(शून्य, (acpi_string)WMBB_METHOD, &handle);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Cannot get handle");
		वापस शून्य;
	पूर्ण

	arg.count = 3;
	arg.poपूर्णांकer = args;

	status = acpi_evaluate_object(handle, शून्य, &arg, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_err(handle, "WMAB: call failed.\n");
		वापस शून्य;
	पूर्ण

	वापस (जोड़ acpi_object *)buffer.poपूर्णांकer;
पूर्ण

अटल व्योम wmi_notअगरy(u32 value, व्योम *context)
अणु
	काष्ठा acpi_buffer response = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;
	दीर्घ data = (दीर्घ)context;

	pr_debug("event guid %li\n", data);
	status = wmi_get_event_data(value, &response);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Bad event status 0x%x\n", status);
		वापस;
	पूर्ण

	obj = (जोड़ acpi_object *)response.poपूर्णांकer;
	अगर (!obj)
		वापस;

	अगर (obj->type == ACPI_TYPE_INTEGER) अणु
		पूर्णांक eventcode = obj->पूर्णांकeger.value;
		काष्ठा key_entry *key;

		key =
		    sparse_keymap_entry_from_scancode(wmi_input_dev, eventcode);
		अगर (key && key->type == KE_KEY)
			sparse_keymap_report_entry(wmi_input_dev, key, 1, true);
	पूर्ण

	pr_debug("Type: %i    Eventcode: 0x%llx\n", obj->type,
		 obj->पूर्णांकeger.value);
	kमुक्त(response.poपूर्णांकer);
पूर्ण

अटल व्योम wmi_input_setup(व्योम)
अणु
	acpi_status status;

	wmi_input_dev = input_allocate_device();
	अगर (wmi_input_dev) अणु
		wmi_input_dev->name = "LG WMI hotkeys";
		wmi_input_dev->phys = "wmi/input0";
		wmi_input_dev->id.bustype = BUS_HOST;

		अगर (sparse_keymap_setup(wmi_input_dev, wmi_keymap, शून्य) ||
		    input_रेजिस्टर_device(wmi_input_dev)) अणु
			pr_info("Cannot initialize input device");
			input_मुक्त_device(wmi_input_dev);
			वापस;
		पूर्ण

		inited |= INIT_SPARSE_KEYMAP;
		status = wmi_install_notअगरy_handler(WMI_EVENT_GUID0, wmi_notअगरy,
						    (व्योम *)0);
		अगर (ACPI_SUCCESS(status))
			inited |= INIT_INPUT_WMI_0;

		status = wmi_install_notअगरy_handler(WMI_EVENT_GUID2, wmi_notअगरy,
						    (व्योम *)2);
		अगर (ACPI_SUCCESS(status))
			inited |= INIT_INPUT_WMI_2;
	पूर्ण अन्यथा अणु
		pr_info("Cannot allocate input device");
	पूर्ण
पूर्ण

अटल व्योम acpi_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा key_entry *key;

	acpi_handle_debug(device->handle, "notify: %d\n", event);
	अगर (inited & INIT_SPARSE_KEYMAP) अणु
		key = sparse_keymap_entry_from_scancode(wmi_input_dev, 0x80);
		अगर (key && key->type == KE_KEY)
			sparse_keymap_report_entry(wmi_input_dev, key, 1, true);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार fan_mode_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	bool value;
	जोड़ acpi_object *r;
	u32 m;
	पूर्णांक ret;

	ret = kstrtobool(buffer, &value);
	अगर (ret)
		वापस ret;

	r = lg_wmab(WM_FAN_MODE, WM_GET, 0);
	अगर (!r)
		वापस -EIO;

	अगर (r->type != ACPI_TYPE_INTEGER) अणु
		kमुक्त(r);
		वापस -EIO;
	पूर्ण

	m = r->पूर्णांकeger.value;
	kमुक्त(r);
	r = lg_wmab(WM_FAN_MODE, WM_SET, (m & 0xffffff0f) | (value << 4));
	kमुक्त(r);
	r = lg_wmab(WM_FAN_MODE, WM_SET, (m & 0xfffffff0) | value);
	kमुक्त(r);

	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_mode_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक status;
	जोड़ acpi_object *r;

	r = lg_wmab(WM_FAN_MODE, WM_GET, 0);
	अगर (!r)
		वापस -EIO;

	अगर (r->type != ACPI_TYPE_INTEGER) अणु
		kमुक्त(r);
		वापस -EIO;
	पूर्ण

	status = r->पूर्णांकeger.value & 0x01;
	kमुक्त(r);

	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", status);
पूर्ण

अटल sमाप_प्रकार usb_अक्षरge_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	bool value;
	जोड़ acpi_object *r;
	पूर्णांक ret;

	ret = kstrtobool(buffer, &value);
	अगर (ret)
		वापस ret;

	r = lg_wmbb(WMBB_USB_CHARGE, WM_SET, value);
	अगर (!r)
		वापस -EIO;

	kमुक्त(r);
	वापस count;
पूर्ण

अटल sमाप_प्रकार usb_अक्षरge_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक status;
	जोड़ acpi_object *r;

	r = lg_wmbb(WMBB_USB_CHARGE, WM_GET, 0);
	अगर (!r)
		वापस -EIO;

	अगर (r->type != ACPI_TYPE_BUFFER) अणु
		kमुक्त(r);
		वापस -EIO;
	पूर्ण

	status = !!r->buffer.poपूर्णांकer[0x10];

	kमुक्त(r);

	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", status);
पूर्ण

अटल sमाप_प्रकार पढ़ोer_mode_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	bool value;
	जोड़ acpi_object *r;
	पूर्णांक ret;

	ret = kstrtobool(buffer, &value);
	अगर (ret)
		वापस ret;

	r = lg_wmab(WM_READER_MODE, WM_SET, value);
	अगर (!r)
		वापस -EIO;

	kमुक्त(r);
	वापस count;
पूर्ण

अटल sमाप_प्रकार पढ़ोer_mode_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक status;
	जोड़ acpi_object *r;

	r = lg_wmab(WM_READER_MODE, WM_GET, 0);
	अगर (!r)
		वापस -EIO;

	अगर (r->type != ACPI_TYPE_INTEGER) अणु
		kमुक्त(r);
		वापस -EIO;
	पूर्ण

	status = !!r->पूर्णांकeger.value;

	kमुक्त(r);

	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", status);
पूर्ण

अटल sमाप_प्रकार fn_lock_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	bool value;
	जोड़ acpi_object *r;
	पूर्णांक ret;

	ret = kstrtobool(buffer, &value);
	अगर (ret)
		वापस ret;

	r = lg_wmab(WM_FN_LOCK, WM_SET, value);
	अगर (!r)
		वापस -EIO;

	kमुक्त(r);
	वापस count;
पूर्ण

अटल sमाप_प्रकार fn_lock_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक status;
	जोड़ acpi_object *r;

	r = lg_wmab(WM_FN_LOCK, WM_GET, 0);
	अगर (!r)
		वापस -EIO;

	अगर (r->type != ACPI_TYPE_BUFFER) अणु
		kमुक्त(r);
		वापस -EIO;
	पूर्ण

	status = !!r->buffer.poपूर्णांकer[0];
	kमुक्त(r);

	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", status);
पूर्ण

अटल sमाप_प्रकार battery_care_limit_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buffer, 10, &value);
	अगर (ret)
		वापस ret;

	अगर (value == 100 || value == 80) अणु
		जोड़ acpi_object *r;

		r = lg_wmab(WM_BATT_LIMIT, WM_SET, value);
		अगर (!r)
			वापस -EIO;

		kमुक्त(r);
		वापस count;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार battery_care_limit_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक status;
	जोड़ acpi_object *r;

	r = lg_wmab(WM_BATT_LIMIT, WM_GET, 0);
	अगर (!r)
		वापस -EIO;

	अगर (r->type != ACPI_TYPE_INTEGER) अणु
		kमुक्त(r);
		वापस -EIO;
	पूर्ण

	status = r->पूर्णांकeger.value;
	kमुक्त(r);
	अगर (status != 80 && status != 100)
		status = 0;

	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", status);
पूर्ण

अटल DEVICE_ATTR_RW(fan_mode);
अटल DEVICE_ATTR_RW(usb_अक्षरge);
अटल DEVICE_ATTR_RW(पढ़ोer_mode);
अटल DEVICE_ATTR_RW(fn_lock);
अटल DEVICE_ATTR_RW(battery_care_limit);

अटल काष्ठा attribute *dev_attributes[] = अणु
	&dev_attr_fan_mode.attr,
	&dev_attr_usb_अक्षरge.attr,
	&dev_attr_पढ़ोer_mode.attr,
	&dev_attr_fn_lock.attr,
	&dev_attr_battery_care_limit.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dev_attribute_group = अणु
	.attrs = dev_attributes,
पूर्ण;

अटल व्योम tpad_led_set(काष्ठा led_classdev *cdev,
			 क्रमागत led_brightness brightness)
अणु
	जोड़ acpi_object *r;

	r = lg_wmab(WM_TLED, WM_SET, brightness > LED_OFF);
	kमुक्त(r);
पूर्ण

अटल क्रमागत led_brightness tpad_led_get(काष्ठा led_classdev *cdev)
अणु
	वापस ggov(GOV_TLED) > 0 ? LED_ON : LED_OFF;
पूर्ण

अटल LED_DEVICE(tpad_led, 1);

अटल व्योम kbd_backlight_set(काष्ठा led_classdev *cdev,
			      क्रमागत led_brightness brightness)
अणु
	u32 val;
	जोड़ acpi_object *r;

	val = 0x22;
	अगर (brightness <= LED_OFF)
		val = 0;
	अगर (brightness >= LED_FULL)
		val = 0x24;
	r = lg_wmab(WM_KEY_LIGHT, WM_SET, val);
	kमुक्त(r);
पूर्ण

अटल क्रमागत led_brightness kbd_backlight_get(काष्ठा led_classdev *cdev)
अणु
	जोड़ acpi_object *r;
	पूर्णांक val;

	r = lg_wmab(WM_KEY_LIGHT, WM_GET, 0);

	अगर (!r)
		वापस LED_OFF;

	अगर (r->type != ACPI_TYPE_BUFFER || r->buffer.poपूर्णांकer[1] != 0x05) अणु
		kमुक्त(r);
		वापस LED_OFF;
	पूर्ण

	चयन (r->buffer.poपूर्णांकer[0] & 0x27) अणु
	हाल 0x24:
		val = LED_FULL;
		अवरोध;
	हाल 0x22:
		val = LED_HALF;
		अवरोध;
	शेष:
		val = LED_OFF;
	पूर्ण

	kमुक्त(r);

	वापस val;
पूर्ण

अटल LED_DEVICE(kbd_backlight, 255);

अटल व्योम wmi_input_destroy(व्योम)
अणु
	अगर (inited & INIT_INPUT_WMI_2)
		wmi_हटाओ_notअगरy_handler(WMI_EVENT_GUID2);

	अगर (inited & INIT_INPUT_WMI_0)
		wmi_हटाओ_notअगरy_handler(WMI_EVENT_GUID0);

	अगर (inited & INIT_SPARSE_KEYMAP)
		input_unरेजिस्टर_device(wmi_input_dev);

	inited &= ~(INIT_INPUT_WMI_0 | INIT_INPUT_WMI_2 | INIT_SPARSE_KEYMAP);
पूर्ण

अटल काष्ठा platक्रमm_driver pf_driver = अणु
	.driver = अणु
		   .name = PLATFORM_NAME,
	पूर्ण
पूर्ण;

अटल पूर्णांक acpi_add(काष्ठा acpi_device *device)
अणु
	पूर्णांक ret;

	अगर (pf_device)
		वापस 0;

	ret = platक्रमm_driver_रेजिस्टर(&pf_driver);
	अगर (ret)
		वापस ret;

	pf_device = platक्रमm_device_रेजिस्टर_simple(PLATFORM_NAME,
						    PLATFORM_DEVID_NONE,
						    शून्य, 0);
	अगर (IS_ERR(pf_device)) अणु
		ret = PTR_ERR(pf_device);
		pf_device = शून्य;
		pr_err("unable to register platform device\n");
		जाओ out_platक्रमm_रेजिस्टरed;
	पूर्ण

	ret = sysfs_create_group(&pf_device->dev.kobj, &dev_attribute_group);
	अगर (ret)
		जाओ out_platक्रमm_device;

	/* LEDs are optional */
	led_classdev_रेजिस्टर(&pf_device->dev, &kbd_backlight);
	led_classdev_रेजिस्टर(&pf_device->dev, &tpad_led);

	wmi_input_setup();

	वापस 0;

out_platक्रमm_device:
	platक्रमm_device_unरेजिस्टर(pf_device);
out_platक्रमm_रेजिस्टरed:
	platक्रमm_driver_unरेजिस्टर(&pf_driver);
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_हटाओ(काष्ठा acpi_device *device)
अणु
	sysfs_हटाओ_group(&pf_device->dev.kobj, &dev_attribute_group);

	led_classdev_unरेजिस्टर(&tpad_led);
	led_classdev_unरेजिस्टर(&kbd_backlight);

	wmi_input_destroy();
	platक्रमm_device_unरेजिस्टर(pf_device);
	pf_device = शून्य;
	platक्रमm_driver_unरेजिस्टर(&pf_driver);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id device_ids[] = अणु
	अणु"LGEX0815", 0पूर्ण,
	अणु"", 0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, device_ids);

अटल काष्ठा acpi_driver acpi_driver = अणु
	.name = "LG Gram Laptop Support",
	.class = "lg-laptop",
	.ids = device_ids,
	.ops = अणु
		.add = acpi_add,
		.हटाओ = acpi_हटाओ,
		.notअगरy = acpi_notअगरy,
		पूर्ण,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init acpi_init(व्योम)
अणु
	पूर्णांक result;

	result = acpi_bus_रेजिस्टर_driver(&acpi_driver);
	अगर (result < 0) अणु
		pr_debug("Error registering driver\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास acpi_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&acpi_driver);
पूर्ण

module_init(acpi_init);
module_निकास(acpi_निकास);
