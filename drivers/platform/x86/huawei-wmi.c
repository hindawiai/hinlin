<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Huawei WMI laptop extras driver
 *
 *  Copyright (C) 2018	      Ayman Bagabas <ayman.bagabas@gmail.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/wmi.h>
#समावेश <acpi/battery.h>

/*
 * Huawei WMI GUIDs
 */
#घोषणा HWMI_METHOD_GUID "ABBC0F5B-8EA1-11D1-A000-C90629100000"
#घोषणा HWMI_EVENT_GUID "ABBC0F5C-8EA1-11D1-A000-C90629100000"

/* Legacy GUIDs */
#घोषणा WMI0_EXPENSIVE_GUID "39142400-C6A3-40fa-BADB-8A2652834100"
#घोषणा WMI0_EVENT_GUID "59142400-C6A3-40fa-BADB-8A2652834100"

/* HWMI commands */

क्रमागत अणु
	BATTERY_THRESH_GET		= 0x00001103, /* \GBTT */
	BATTERY_THRESH_SET		= 0x00001003, /* \SBTT */
	FN_LOCK_GET			= 0x00000604, /* \GFRS */
	FN_LOCK_SET			= 0x00000704, /* \SFRS */
	MICMUTE_LED_SET			= 0x00000b04, /* \SMLS */
पूर्ण;

जोड़ hwmi_arg अणु
	u64 cmd;
	u8 args[8];
पूर्ण;

काष्ठा quirk_entry अणु
	bool battery_reset;
	bool ec_micmute;
	bool report_brightness;
पूर्ण;

अटल काष्ठा quirk_entry *quirks;

काष्ठा huawei_wmi_debug अणु
	काष्ठा dentry *root;
	u64 arg;
पूर्ण;

काष्ठा huawei_wmi अणु
	bool battery_available;
	bool fn_lock_available;

	काष्ठा huawei_wmi_debug debug;
	काष्ठा input_dev *idev[2];
	काष्ठा led_classdev cdev;
	काष्ठा device *dev;

	काष्ठा mutex wmi_lock;
पूर्ण;

अटल काष्ठा huawei_wmi *huawei_wmi;

अटल स्थिर काष्ठा key_entry huawei_wmi_keymap[] = अणु
	अणु KE_KEY,    0x281, अणु KEY_BRIGHTNESSDOWN पूर्ण पूर्ण,
	अणु KE_KEY,    0x282, अणु KEY_BRIGHTNESSUP पूर्ण पूर्ण,
	अणु KE_KEY,    0x284, अणु KEY_MUTE पूर्ण पूर्ण,
	अणु KE_KEY,    0x285, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,
	अणु KE_KEY,    0x286, अणु KEY_VOLUMEUP पूर्ण पूर्ण,
	अणु KE_KEY,    0x287, अणु KEY_MICMUTE पूर्ण पूर्ण,
	अणु KE_KEY,    0x289, अणु KEY_WLAN पूर्ण पूर्ण,
	// Huawei |M| key
	अणु KE_KEY,    0x28a, अणु KEY_CONFIG पूर्ण पूर्ण,
	// Keyboard backlit
	अणु KE_IGNORE, 0x293, अणु KEY_KBDILLUMTOGGLE पूर्ण पूर्ण,
	अणु KE_IGNORE, 0x294, अणु KEY_KBDILLUMUP पूर्ण पूर्ण,
	अणु KE_IGNORE, 0x295, अणु KEY_KBDILLUMUP पूर्ण पूर्ण,
	अणु KE_END,	 0 पूर्ण
पूर्ण;

अटल पूर्णांक battery_reset = -1;
अटल पूर्णांक report_brightness = -1;

module_param(battery_reset, bपूर्णांक, 0444);
MODULE_PARM_DESC(battery_reset,
		"Reset battery charge values to (0-0) before disabling it using (0-100)");
module_param(report_brightness, bपूर्णांक, 0444);
MODULE_PARM_DESC(report_brightness,
		"Report brightness keys.");

/* Quirks */

अटल पूर्णांक __init dmi_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	quirks = dmi->driver_data;
	वापस 1;
पूर्ण

अटल काष्ठा quirk_entry quirk_unknown = अणु
पूर्ण;

अटल काष्ठा quirk_entry quirk_battery_reset = अणु
	.battery_reset = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_matebook_x = अणु
	.ec_micmute = true,
	.report_brightness = true,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id huawei_quirks[] = अणु
	अणु
		.callback = dmi_matched,
		.ident = "Huawei MACH-WX9",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HUAWEI"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MACH-WX9"),
		पूर्ण,
		.driver_data = &quirk_battery_reset
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Huawei MateBook X",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HUAWEI"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HUAWEI MateBook X")
		पूर्ण,
		.driver_data = &quirk_matebook_x
	पूर्ण,
	अणु  पूर्ण
पूर्ण;

/* Utils */

अटल पूर्णांक huawei_wmi_call(काष्ठा huawei_wmi *huawei,
			   काष्ठा acpi_buffer *in, काष्ठा acpi_buffer *out)
अणु
	acpi_status status;

	mutex_lock(&huawei->wmi_lock);
	status = wmi_evaluate_method(HWMI_METHOD_GUID, 0, 1, in, out);
	mutex_unlock(&huawei->wmi_lock);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(huawei->dev, "Failed to evaluate wmi method\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/* HWMI takes a 64 bit input and वापसs either a package with 2 buffers, one of
 * 4 bytes and the other of 256 bytes, or one buffer of size 0x104 (260) bytes.
 * The first 4 bytes are ignored, we ignore the first 4 bytes buffer अगर we got a
 * package, or skip the first 4 अगर a buffer of 0x104 is used. The first byte of
 * the reमुख्यing 0x100 sized buffer has the वापस status of every call. In हाल
 * the वापस status is non-zero, we वापस -ENODEV but still copy the वापसed
 * buffer to the given buffer parameter (buf).
 */
अटल पूर्णांक huawei_wmi_cmd(u64 arg, u8 *buf, माप_प्रकार buflen)
अणु
	काष्ठा huawei_wmi *huawei = huawei_wmi;
	काष्ठा acpi_buffer out = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_buffer in;
	जोड़ acpi_object *obj;
	माप_प्रकार len;
	पूर्णांक err, i;

	in.length = माप(arg);
	in.poपूर्णांकer = &arg;

	/* Some models require calling HWMI twice to execute a command. We evaluate
	 * HWMI and अगर we get a non-zero वापस status we evaluate it again.
	 */
	क्रम (i = 0; i < 2; i++) अणु
		err = huawei_wmi_call(huawei, &in, &out);
		अगर (err)
			जाओ fail_cmd;

		obj = out.poपूर्णांकer;
		अगर (!obj) अणु
			err = -EIO;
			जाओ fail_cmd;
		पूर्ण

		चयन (obj->type) अणु
		/* Models that implement both "legacy" and HWMI tend to वापस a 0x104
		 * sized buffer instead of a package of 0x4 and 0x100 buffers.
		 */
		हाल ACPI_TYPE_BUFFER:
			अगर (obj->buffer.length == 0x104) अणु
				// Skip the first 4 bytes.
				obj->buffer.poपूर्णांकer += 4;
				len = 0x100;
			पूर्ण अन्यथा अणु
				dev_err(huawei->dev, "Bad buffer length, got %d\n", obj->buffer.length);
				err = -EIO;
				जाओ fail_cmd;
			पूर्ण

			अवरोध;
		/* HWMI वापसs a package with 2 buffer elements, one of 4 bytes and the
		 * other is 256 bytes.
		 */
		हाल ACPI_TYPE_PACKAGE:
			अगर (obj->package.count != 2) अणु
				dev_err(huawei->dev, "Bad package count, got %d\n", obj->package.count);
				err = -EIO;
				जाओ fail_cmd;
			पूर्ण

			obj = &obj->package.elements[1];
			अगर (obj->type != ACPI_TYPE_BUFFER) अणु
				dev_err(huawei->dev, "Bad package element type, got %d\n", obj->type);
				err = -EIO;
				जाओ fail_cmd;
			पूर्ण
			len = obj->buffer.length;

			अवरोध;
		/* Shouldn't get here! */
		शेष:
			dev_err(huawei->dev, "Unexpected obj type, got: %d\n", obj->type);
			err = -EIO;
			जाओ fail_cmd;
		पूर्ण

		अगर (!*obj->buffer.poपूर्णांकer)
			अवरोध;
	पूर्ण

	err = (*obj->buffer.poपूर्णांकer) ? -ENODEV : 0;

	अगर (buf) अणु
		len = min(buflen, len);
		स_नकल(buf, obj->buffer.poपूर्णांकer, len);
	पूर्ण

fail_cmd:
	kमुक्त(out.poपूर्णांकer);
	वापस err;
पूर्ण

/* LEDs */

अटल पूर्णांक huawei_wmi_micmute_led_set(काष्ठा led_classdev *led_cdev,
		क्रमागत led_brightness brightness)
अणु
	/* This is a workaround until the "legacy" पूर्णांकerface is implemented. */
	अगर (quirks && quirks->ec_micmute) अणु
		अक्षर *acpi_method;
		acpi_handle handle;
		acpi_status status;
		जोड़ acpi_object args[3];
		काष्ठा acpi_object_list arg_list = अणु
			.poपूर्णांकer = args,
			.count = ARRAY_SIZE(args),
		पूर्ण;

		handle = ec_get_handle();
		अगर (!handle)
			वापस -ENODEV;

		args[0].type = args[1].type = args[2].type = ACPI_TYPE_INTEGER;
		args[1].पूर्णांकeger.value = 0x04;

		अगर (acpi_has_method(handle, "SPIN")) अणु
			acpi_method = "SPIN";
			args[0].पूर्णांकeger.value = 0;
			args[2].पूर्णांकeger.value = brightness ? 1 : 0;
		पूर्ण अन्यथा अगर (acpi_has_method(handle, "WPIN")) अणु
			acpi_method = "WPIN";
			args[0].पूर्णांकeger.value = 1;
			args[2].पूर्णांकeger.value = brightness ? 0 : 1;
		पूर्ण अन्यथा अणु
			वापस -ENODEV;
		पूर्ण

		status = acpi_evaluate_object(handle, acpi_method, &arg_list, शून्य);
		अगर (ACPI_FAILURE(status))
			वापस -ENODEV;

		वापस 0;
	पूर्ण अन्यथा अणु
		जोड़ hwmi_arg arg;

		arg.cmd = MICMUTE_LED_SET;
		arg.args[2] = brightness;

		वापस huawei_wmi_cmd(arg.cmd, शून्य, 0);
	पूर्ण
पूर्ण

अटल व्योम huawei_wmi_leds_setup(काष्ठा device *dev)
अणु
	काष्ठा huawei_wmi *huawei = dev_get_drvdata(dev);

	huawei->cdev.name = "platform::micmute";
	huawei->cdev.max_brightness = 1;
	huawei->cdev.brightness_set_blocking = &huawei_wmi_micmute_led_set;
	huawei->cdev.शेष_trigger = "audio-micmute";
	huawei->cdev.brightness = ledtrig_audio_get(LED_AUDIO_MICMUTE);
	huawei->cdev.dev = dev;
	huawei->cdev.flags = LED_CORE_SUSPENDRESUME;

	devm_led_classdev_रेजिस्टर(dev, &huawei->cdev);
पूर्ण

/* Battery protection */

अटल पूर्णांक huawei_wmi_battery_get(पूर्णांक *start, पूर्णांक *end)
अणु
	u8 ret[0x100];
	पूर्णांक err, i;

	err = huawei_wmi_cmd(BATTERY_THRESH_GET, ret, 0x100);
	अगर (err)
		वापस err;

	/* Find the last two non-zero values. Return status is ignored. */
	i = 0xff;
	करो अणु
		अगर (start)
			*start = ret[i-1];
		अगर (end)
			*end = ret[i];
	पूर्ण जबतक (i > 2 && !ret[i--]);

	वापस 0;
पूर्ण

अटल पूर्णांक huawei_wmi_battery_set(पूर्णांक start, पूर्णांक end)
अणु
	जोड़ hwmi_arg arg;
	पूर्णांक err;

	अगर (start < 0 || end < 0 || start > 100 || end > 100)
		वापस -EINVAL;

	arg.cmd = BATTERY_THRESH_SET;
	arg.args[2] = start;
	arg.args[3] = end;

	/* This is an edge हाल were some models turn battery protection
	 * off without changing their thresholds values. We clear the
	 * values beक्रमe turning off protection. Someबार we need a sleep delay to
	 * make sure these values make their way to EC memory.
	 */
	अगर (quirks && quirks->battery_reset && start == 0 && end == 100) अणु
		err = huawei_wmi_battery_set(0, 0);
		अगर (err)
			वापस err;

		msleep(1000);
	पूर्ण

	err = huawei_wmi_cmd(arg.cmd, शून्य, 0);

	वापस err;
पूर्ण

अटल sमाप_प्रकार अक्षरge_control_start_threshold_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक err, start;

	err = huawei_wmi_battery_get(&start, शून्य);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%d\n", start);
पूर्ण

अटल sमाप_प्रकार अक्षरge_control_end_threshold_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक err, end;

	err = huawei_wmi_battery_get(शून्य, &end);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%d\n", end);
पूर्ण

अटल sमाप_प्रकार अक्षरge_control_thresholds_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक err, start, end;

	err = huawei_wmi_battery_get(&start, &end);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%d %d\n", start, end);
पूर्ण

अटल sमाप_प्रकार अक्षरge_control_start_threshold_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक err, start, end;

	err = huawei_wmi_battery_get(शून्य, &end);
	अगर (err)
		वापस err;

	अगर (माला_पूछो(buf, "%d", &start) != 1)
		वापस -EINVAL;

	err = huawei_wmi_battery_set(start, end);
	अगर (err)
		वापस err;

	वापस size;
पूर्ण

अटल sमाप_प्रकार अक्षरge_control_end_threshold_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक err, start, end;

	err = huawei_wmi_battery_get(&start, शून्य);
	अगर (err)
		वापस err;

	अगर (माला_पूछो(buf, "%d", &end) != 1)
		वापस -EINVAL;

	err = huawei_wmi_battery_set(start, end);
	अगर (err)
		वापस err;

	वापस size;
पूर्ण

अटल sमाप_प्रकार अक्षरge_control_thresholds_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक err, start, end;

	अगर (माला_पूछो(buf, "%d %d", &start, &end) != 2)
		वापस -EINVAL;

	err = huawei_wmi_battery_set(start, end);
	अगर (err)
		वापस err;

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(अक्षरge_control_start_threshold);
अटल DEVICE_ATTR_RW(अक्षरge_control_end_threshold);
अटल DEVICE_ATTR_RW(अक्षरge_control_thresholds);

अटल पूर्णांक huawei_wmi_battery_add(काष्ठा घातer_supply *battery)
अणु
	device_create_file(&battery->dev, &dev_attr_अक्षरge_control_start_threshold);
	device_create_file(&battery->dev, &dev_attr_अक्षरge_control_end_threshold);

	वापस 0;
पूर्ण

अटल पूर्णांक huawei_wmi_battery_हटाओ(काष्ठा घातer_supply *battery)
अणु
	device_हटाओ_file(&battery->dev, &dev_attr_अक्षरge_control_start_threshold);
	device_हटाओ_file(&battery->dev, &dev_attr_अक्षरge_control_end_threshold);

	वापस 0;
पूर्ण

अटल काष्ठा acpi_battery_hook huawei_wmi_battery_hook = अणु
	.add_battery = huawei_wmi_battery_add,
	.हटाओ_battery = huawei_wmi_battery_हटाओ,
	.name = "Huawei Battery Extension"
पूर्ण;

अटल व्योम huawei_wmi_battery_setup(काष्ठा device *dev)
अणु
	काष्ठा huawei_wmi *huawei = dev_get_drvdata(dev);

	huawei->battery_available = true;
	अगर (huawei_wmi_battery_get(शून्य, शून्य)) अणु
		huawei->battery_available = false;
		वापस;
	पूर्ण

	battery_hook_रेजिस्टर(&huawei_wmi_battery_hook);
	device_create_file(dev, &dev_attr_अक्षरge_control_thresholds);
पूर्ण

अटल व्योम huawei_wmi_battery_निकास(काष्ठा device *dev)
अणु
	काष्ठा huawei_wmi *huawei = dev_get_drvdata(dev);

	अगर (huawei->battery_available) अणु
		battery_hook_unरेजिस्टर(&huawei_wmi_battery_hook);
		device_हटाओ_file(dev, &dev_attr_अक्षरge_control_thresholds);
	पूर्ण
पूर्ण

/* Fn lock */

अटल पूर्णांक huawei_wmi_fn_lock_get(पूर्णांक *on)
अणु
	u8 ret[0x100] = अणु 0 पूर्ण;
	पूर्णांक err, i;

	err = huawei_wmi_cmd(FN_LOCK_GET, ret, 0x100);
	अगर (err)
		वापस err;

	/* Find the first non-zero value. Return status is ignored. */
	i = 1;
	करो अणु
		अगर (on)
			*on = ret[i] - 1; // -1 undefined, 0 off, 1 on.
	पूर्ण जबतक (i < 0xff && !ret[i++]);

	वापस 0;
पूर्ण

अटल पूर्णांक huawei_wmi_fn_lock_set(पूर्णांक on)
अणु
	जोड़ hwmi_arg arg;

	arg.cmd = FN_LOCK_SET;
	arg.args[2] = on + 1; // 0 undefined, 1 off, 2 on.

	वापस huawei_wmi_cmd(arg.cmd, शून्य, 0);
पूर्ण

अटल sमाप_प्रकार fn_lock_state_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक err, on;

	err = huawei_wmi_fn_lock_get(&on);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%d\n", on);
पूर्ण

अटल sमाप_प्रकार fn_lock_state_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक on, err;

	अगर (kstrtoपूर्णांक(buf, 10, &on) ||
			on < 0 || on > 1)
		वापस -EINVAL;

	err = huawei_wmi_fn_lock_set(on);
	अगर (err)
		वापस err;

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(fn_lock_state);

अटल व्योम huawei_wmi_fn_lock_setup(काष्ठा device *dev)
अणु
	काष्ठा huawei_wmi *huawei = dev_get_drvdata(dev);

	huawei->fn_lock_available = true;
	अगर (huawei_wmi_fn_lock_get(शून्य)) अणु
		huawei->fn_lock_available = false;
		वापस;
	पूर्ण

	device_create_file(dev, &dev_attr_fn_lock_state);
पूर्ण

अटल व्योम huawei_wmi_fn_lock_निकास(काष्ठा device *dev)
अणु
	काष्ठा huawei_wmi *huawei = dev_get_drvdata(dev);

	अगर (huawei->fn_lock_available)
		device_हटाओ_file(dev, &dev_attr_fn_lock_state);
पूर्ण

/* debugfs */

अटल व्योम huawei_wmi_debugfs_call_dump(काष्ठा seq_file *m, व्योम *data,
		जोड़ acpi_object *obj)
अणु
	काष्ठा huawei_wmi *huawei = m->निजी;
	पूर्णांक i;

	चयन (obj->type) अणु
	हाल ACPI_TYPE_INTEGER:
		seq_म_लिखो(m, "0x%llx", obj->पूर्णांकeger.value);
		अवरोध;
	हाल ACPI_TYPE_STRING:
		seq_म_लिखो(m, "\"%.*s\"", obj->string.length, obj->string.poपूर्णांकer);
		अवरोध;
	हाल ACPI_TYPE_BUFFER:
		seq_माला_दो(m, "{");
		क्रम (i = 0; i < obj->buffer.length; i++) अणु
			seq_म_लिखो(m, "0x%02x", obj->buffer.poपूर्णांकer[i]);
			अगर (i < obj->buffer.length - 1)
				seq_माला_दो(m, ",");
		पूर्ण
		seq_माला_दो(m, "}");
		अवरोध;
	हाल ACPI_TYPE_PACKAGE:
		seq_माला_दो(m, "[");
		क्रम (i = 0; i < obj->package.count; i++) अणु
			huawei_wmi_debugfs_call_dump(m, huawei, &obj->package.elements[i]);
			अगर (i < obj->package.count - 1)
				seq_माला_दो(m, ",");
		पूर्ण
		seq_माला_दो(m, "]");
		अवरोध;
	शेष:
		dev_err(huawei->dev, "Unexpected obj type, got %d\n", obj->type);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक huawei_wmi_debugfs_call_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा huawei_wmi *huawei = m->निजी;
	काष्ठा acpi_buffer out = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_buffer in;
	जोड़ acpi_object *obj;
	पूर्णांक err;

	in.length = माप(u64);
	in.poपूर्णांकer = &huawei->debug.arg;

	err = huawei_wmi_call(huawei, &in, &out);
	अगर (err)
		वापस err;

	obj = out.poपूर्णांकer;
	अगर (!obj) अणु
		err = -EIO;
		जाओ fail_debugfs_call;
	पूर्ण

	huawei_wmi_debugfs_call_dump(m, huawei, obj);

fail_debugfs_call:
	kमुक्त(out.poपूर्णांकer);
	वापस err;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(huawei_wmi_debugfs_call);

अटल व्योम huawei_wmi_debugfs_setup(काष्ठा device *dev)
अणु
	काष्ठा huawei_wmi *huawei = dev_get_drvdata(dev);

	huawei->debug.root = debugfs_create_dir("huawei-wmi", शून्य);

	debugfs_create_x64("arg", 0644, huawei->debug.root,
		&huawei->debug.arg);
	debugfs_create_file("call", 0400,
		huawei->debug.root, huawei, &huawei_wmi_debugfs_call_fops);
पूर्ण

अटल व्योम huawei_wmi_debugfs_निकास(काष्ठा device *dev)
अणु
	काष्ठा huawei_wmi *huawei = dev_get_drvdata(dev);

	debugfs_हटाओ_recursive(huawei->debug.root);
पूर्ण

/* Input */

अटल व्योम huawei_wmi_process_key(काष्ठा input_dev *idev, पूर्णांक code)
अणु
	स्थिर काष्ठा key_entry *key;

	/*
	 * WMI0 uses code 0x80 to indicate a hotkey event.
	 * The actual key is fetched from the method WQ00
	 * using WMI0_EXPENSIVE_GUID.
	 */
	अगर (code == 0x80) अणु
		काष्ठा acpi_buffer response = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
		जोड़ acpi_object *obj;
		acpi_status status;

		status = wmi_query_block(WMI0_EXPENSIVE_GUID, 0, &response);
		अगर (ACPI_FAILURE(status))
			वापस;

		obj = (जोड़ acpi_object *)response.poपूर्णांकer;
		अगर (obj && obj->type == ACPI_TYPE_INTEGER)
			code = obj->पूर्णांकeger.value;

		kमुक्त(response.poपूर्णांकer);
	पूर्ण

	key = sparse_keymap_entry_from_scancode(idev, code);
	अगर (!key) अणु
		dev_info(&idev->dev, "Unknown key pressed, code: 0x%04x\n", code);
		वापस;
	पूर्ण

	अगर (quirks && !quirks->report_brightness &&
			(key->sw.code == KEY_BRIGHTNESSDOWN ||
			key->sw.code == KEY_BRIGHTNESSUP))
		वापस;

	sparse_keymap_report_entry(idev, key, 1, true);
पूर्ण

अटल व्योम huawei_wmi_input_notअगरy(u32 value, व्योम *context)
अणु
	काष्ठा input_dev *idev = (काष्ठा input_dev *)context;
	काष्ठा acpi_buffer response = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;

	status = wmi_get_event_data(value, &response);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&idev->dev, "Unable to get event data\n");
		वापस;
	पूर्ण

	obj = (जोड़ acpi_object *)response.poपूर्णांकer;
	अगर (obj && obj->type == ACPI_TYPE_INTEGER)
		huawei_wmi_process_key(idev, obj->पूर्णांकeger.value);
	अन्यथा
		dev_err(&idev->dev, "Bad response type\n");

	kमुक्त(response.poपूर्णांकer);
पूर्ण

अटल पूर्णांक huawei_wmi_input_setup(काष्ठा device *dev,
		स्थिर अक्षर *guid,
		काष्ठा input_dev **idev)
अणु
	*idev = devm_input_allocate_device(dev);
	अगर (!*idev)
		वापस -ENOMEM;

	(*idev)->name = "Huawei WMI hotkeys";
	(*idev)->phys = "wmi/input0";
	(*idev)->id.bustype = BUS_HOST;
	(*idev)->dev.parent = dev;

	वापस sparse_keymap_setup(*idev, huawei_wmi_keymap, शून्य) ||
		input_रेजिस्टर_device(*idev) ||
		wmi_install_notअगरy_handler(guid, huawei_wmi_input_notअगरy,
				*idev);
पूर्ण

अटल व्योम huawei_wmi_input_निकास(काष्ठा device *dev, स्थिर अक्षर *guid)
अणु
	wmi_हटाओ_notअगरy_handler(guid);
पूर्ण

/* Huawei driver */

अटल स्थिर काष्ठा wmi_device_id huawei_wmi_events_id_table[] = अणु
	अणु .guid_string = WMI0_EVENT_GUID पूर्ण,
	अणु .guid_string = HWMI_EVENT_GUID पूर्ण,
	अणु  पूर्ण
पूर्ण;

अटल पूर्णांक huawei_wmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा wmi_device_id *guid = huawei_wmi_events_id_table;
	पूर्णांक err;

	platक्रमm_set_drvdata(pdev, huawei_wmi);
	huawei_wmi->dev = &pdev->dev;

	जबतक (*guid->guid_string) अणु
		काष्ठा input_dev *idev = *huawei_wmi->idev;

		अगर (wmi_has_guid(guid->guid_string)) अणु
			err = huawei_wmi_input_setup(&pdev->dev, guid->guid_string, &idev);
			अगर (err) अणु
				dev_err(&pdev->dev, "Failed to setup input on %s\n", guid->guid_string);
				वापस err;
			पूर्ण
		पूर्ण

		idev++;
		guid++;
	पूर्ण

	अगर (wmi_has_guid(HWMI_METHOD_GUID)) अणु
		mutex_init(&huawei_wmi->wmi_lock);

		huawei_wmi_leds_setup(&pdev->dev);
		huawei_wmi_fn_lock_setup(&pdev->dev);
		huawei_wmi_battery_setup(&pdev->dev);
		huawei_wmi_debugfs_setup(&pdev->dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक huawei_wmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा wmi_device_id *guid = huawei_wmi_events_id_table;

	जबतक (*guid->guid_string) अणु
		अगर (wmi_has_guid(guid->guid_string))
			huawei_wmi_input_निकास(&pdev->dev, guid->guid_string);

		guid++;
	पूर्ण

	अगर (wmi_has_guid(HWMI_METHOD_GUID)) अणु
		huawei_wmi_debugfs_निकास(&pdev->dev);
		huawei_wmi_battery_निकास(&pdev->dev);
		huawei_wmi_fn_lock_निकास(&pdev->dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver huawei_wmi_driver = अणु
	.driver = अणु
		.name = "huawei-wmi",
	पूर्ण,
	.probe = huawei_wmi_probe,
	.हटाओ = huawei_wmi_हटाओ,
पूर्ण;

अटल __init पूर्णांक huawei_wmi_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक err;

	huawei_wmi = kzalloc(माप(काष्ठा huawei_wmi), GFP_KERNEL);
	अगर (!huawei_wmi)
		वापस -ENOMEM;

	quirks = &quirk_unknown;
	dmi_check_प्रणाली(huawei_quirks);
	अगर (battery_reset != -1)
		quirks->battery_reset = battery_reset;
	अगर (report_brightness != -1)
		quirks->report_brightness = report_brightness;

	err = platक्रमm_driver_रेजिस्टर(&huawei_wmi_driver);
	अगर (err)
		जाओ pdrv_err;

	pdev = platक्रमm_device_रेजिस्टर_simple("huawei-wmi", -1, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		err = PTR_ERR(pdev);
		जाओ pdev_err;
	पूर्ण

	वापस 0;

pdev_err:
	platक्रमm_driver_unरेजिस्टर(&huawei_wmi_driver);
pdrv_err:
	kमुक्त(huawei_wmi);
	वापस err;
पूर्ण

अटल __निकास व्योम huawei_wmi_निकास(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(huawei_wmi->dev);

	platक्रमm_device_unरेजिस्टर(pdev);
	platक्रमm_driver_unरेजिस्टर(&huawei_wmi_driver);

	kमुक्त(huawei_wmi);
पूर्ण

module_init(huawei_wmi_init);
module_निकास(huawei_wmi_निकास);

MODULE_ALIAS("wmi:"HWMI_METHOD_GUID);
MODULE_DEVICE_TABLE(wmi, huawei_wmi_events_id_table);
MODULE_AUTHOR("Ayman Bagabas <ayman.bagabas@gmail.com>");
MODULE_DESCRIPTION("Huawei WMI laptop extras driver");
MODULE_LICENSE("GPL v2");
