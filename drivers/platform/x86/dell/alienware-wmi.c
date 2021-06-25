<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Alienware AlienFX control
 *
 * Copyright (C) 2014 Dell Inc <Dell.Client.Kernel@dell.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/leds.h>

#घोषणा LEGACY_CONTROL_GUID		"A90597CE-A997-11DA-B012-B622A1EF5492"
#घोषणा LEGACY_POWER_CONTROL_GUID	"A80593CE-A997-11DA-B012-B622A1EF5492"
#घोषणा WMAX_CONTROL_GUID		"A70591CE-A997-11DA-B012-B622A1EF5492"

#घोषणा WMAX_METHOD_HDMI_SOURCE		0x1
#घोषणा WMAX_METHOD_HDMI_STATUS		0x2
#घोषणा WMAX_METHOD_BRIGHTNESS		0x3
#घोषणा WMAX_METHOD_ZONE_CONTROL	0x4
#घोषणा WMAX_METHOD_HDMI_CABLE		0x5
#घोषणा WMAX_METHOD_AMPLIFIER_CABLE	0x6
#घोषणा WMAX_METHOD_DEEP_SLEEP_CONTROL	0x0B
#घोषणा WMAX_METHOD_DEEP_SLEEP_STATUS	0x0C

MODULE_AUTHOR("Mario Limonciello <mario.limonciello@outlook.com>");
MODULE_DESCRIPTION("Alienware special feature control");
MODULE_LICENSE("GPL");
MODULE_ALIAS("wmi:" LEGACY_CONTROL_GUID);
MODULE_ALIAS("wmi:" WMAX_CONTROL_GUID);

क्रमागत INTERFACE_FLAGS अणु
	LEGACY,
	WMAX,
पूर्ण;

क्रमागत LEGACY_CONTROL_STATES अणु
	LEGACY_RUNNING = 1,
	LEGACY_BOOTING = 0,
	LEGACY_SUSPEND = 3,
पूर्ण;

क्रमागत WMAX_CONTROL_STATES अणु
	WMAX_RUNNING = 0xFF,
	WMAX_BOOTING = 0,
	WMAX_SUSPEND = 3,
पूर्ण;

काष्ठा quirk_entry अणु
	u8 num_zones;
	u8 hdmi_mux;
	u8 amplअगरier;
	u8 deepslp;
पूर्ण;

अटल काष्ठा quirk_entry *quirks;


अटल काष्ठा quirk_entry quirk_inspiron5675 = अणु
	.num_zones = 2,
	.hdmi_mux = 0,
	.amplअगरier = 0,
	.deepslp = 0,
पूर्ण;

अटल काष्ठा quirk_entry quirk_unknown = अणु
	.num_zones = 2,
	.hdmi_mux = 0,
	.amplअगरier = 0,
	.deepslp = 0,
पूर्ण;

अटल काष्ठा quirk_entry quirk_x51_r1_r2 = अणु
	.num_zones = 3,
	.hdmi_mux = 0,
	.amplअगरier = 0,
	.deepslp = 0,
पूर्ण;

अटल काष्ठा quirk_entry quirk_x51_r3 = अणु
	.num_zones = 4,
	.hdmi_mux = 0,
	.amplअगरier = 1,
	.deepslp = 0,
पूर्ण;

अटल काष्ठा quirk_entry quirk_यंत्र100 = अणु
	.num_zones = 2,
	.hdmi_mux = 1,
	.amplअगरier = 0,
	.deepslp = 0,
पूर्ण;

अटल काष्ठा quirk_entry quirk_यंत्र200 = अणु
	.num_zones = 2,
	.hdmi_mux = 1,
	.amplअगरier = 0,
	.deepslp = 1,
पूर्ण;

अटल काष्ठा quirk_entry quirk_यंत्र201 = अणु
	.num_zones = 2,
	.hdmi_mux = 1,
	.amplअगरier = 1,
	.deepslp = 1,
पूर्ण;

अटल पूर्णांक __init dmi_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	quirks = dmi->driver_data;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id alienware_quirks[] __initस्थिर = अणु
	अणु
	 .callback = dmi_matched,
	 .ident = "Alienware X51 R3",
	 .matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Alienware"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "Alienware X51 R3"),
		     पूर्ण,
	 .driver_data = &quirk_x51_r3,
	 पूर्ण,
	अणु
	 .callback = dmi_matched,
	 .ident = "Alienware X51 R2",
	 .matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Alienware"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "Alienware X51 R2"),
		     पूर्ण,
	 .driver_data = &quirk_x51_r1_r2,
	 पूर्ण,
	अणु
	 .callback = dmi_matched,
	 .ident = "Alienware X51 R1",
	 .matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Alienware"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "Alienware X51"),
		     पूर्ण,
	 .driver_data = &quirk_x51_r1_r2,
	 पूर्ण,
	अणु
	 .callback = dmi_matched,
	 .ident = "Alienware ASM100",
	 .matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Alienware"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "ASM100"),
		     पूर्ण,
	 .driver_data = &quirk_यंत्र100,
	 पूर्ण,
	अणु
	 .callback = dmi_matched,
	 .ident = "Alienware ASM200",
	 .matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Alienware"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "ASM200"),
		     पूर्ण,
	 .driver_data = &quirk_यंत्र200,
	 पूर्ण,
	अणु
	 .callback = dmi_matched,
	 .ident = "Alienware ASM201",
	 .matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Alienware"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "ASM201"),
		     पूर्ण,
	 .driver_data = &quirk_यंत्र201,
	 पूर्ण,
	 अणु
	 .callback = dmi_matched,
	 .ident = "Dell Inc. Inspiron 5675",
	 .matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		     DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 5675"),
		     पूर्ण,
	 .driver_data = &quirk_inspiron5675,
	 पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा color_platक्रमm अणु
	u8 blue;
	u8 green;
	u8 red;
पूर्ण __packed;

काष्ठा platक्रमm_zone अणु
	u8 location;
	काष्ठा device_attribute *attr;
	काष्ठा color_platक्रमm colors;
पूर्ण;

काष्ठा wmax_brightness_args अणु
	u32 led_mask;
	u32 percentage;
पूर्ण;

काष्ठा wmax_basic_args अणु
	u8 arg;
पूर्ण;

काष्ठा legacy_led_args अणु
	काष्ठा color_platक्रमm colors;
	u8 brightness;
	u8 state;
पूर्ण __packed;

काष्ठा wmax_led_args अणु
	u32 led_mask;
	काष्ठा color_platक्रमm colors;
	u8 state;
पूर्ण __packed;

अटल काष्ठा platक्रमm_device *platक्रमm_device;
अटल काष्ठा device_attribute *zone_dev_attrs;
अटल काष्ठा attribute **zone_attrs;
अटल काष्ठा platक्रमm_zone *zone_data;

अटल काष्ठा platक्रमm_driver platक्रमm_driver = अणु
	.driver = अणु
		   .name = "alienware-wmi",
		   पूर्ण
पूर्ण;

अटल काष्ठा attribute_group zone_attribute_group = अणु
	.name = "rgb_zones",
पूर्ण;

अटल u8 पूर्णांकerface;
अटल u8 lighting_control_state;
अटल u8 global_brightness;

/*
 * Helpers used क्रम zone control
 */
अटल पूर्णांक parse_rgb(स्थिर अक्षर *buf, काष्ठा platक्रमm_zone *zone)
अणु
	दीर्घ अचिन्हित पूर्णांक rgb;
	पूर्णांक ret;
	जोड़ color_जोड़ अणु
		काष्ठा color_platक्रमm cp;
		पूर्णांक package;
	पूर्ण repackager;

	ret = kम_से_अदीर्घ(buf, 16, &rgb);
	अगर (ret)
		वापस ret;

	/* RGB triplet notation is 24-bit hexadecimal */
	अगर (rgb > 0xFFFFFF)
		वापस -EINVAL;

	repackager.package = rgb & 0x0f0f0f0f;
	pr_debug("alienware-wmi: r: %d g:%d b: %d\n",
		 repackager.cp.red, repackager.cp.green, repackager.cp.blue);
	zone->colors = repackager.cp;
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_zone *match_zone(काष्ठा device_attribute *attr)
अणु
	u8 zone;

	क्रम (zone = 0; zone < quirks->num_zones; zone++) अणु
		अगर ((काष्ठा device_attribute *)zone_data[zone].attr == attr) अणु
			pr_debug("alienware-wmi: matched zone location: %d\n",
				 zone_data[zone].location);
			वापस &zone_data[zone];
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Inभागidual RGB zone control
 */
अटल पूर्णांक alienware_update_led(काष्ठा platक्रमm_zone *zone)
अणु
	पूर्णांक method_id;
	acpi_status status;
	अक्षर *guid;
	काष्ठा acpi_buffer input;
	काष्ठा legacy_led_args legacy_args;
	काष्ठा wmax_led_args wmax_basic_args;
	अगर (पूर्णांकerface == WMAX) अणु
		wmax_basic_args.led_mask = 1 << zone->location;
		wmax_basic_args.colors = zone->colors;
		wmax_basic_args.state = lighting_control_state;
		guid = WMAX_CONTROL_GUID;
		method_id = WMAX_METHOD_ZONE_CONTROL;

		input.length = (acpi_size) माप(wmax_basic_args);
		input.poपूर्णांकer = &wmax_basic_args;
	पूर्ण अन्यथा अणु
		legacy_args.colors = zone->colors;
		legacy_args.brightness = global_brightness;
		legacy_args.state = 0;
		अगर (lighting_control_state == LEGACY_BOOTING ||
		    lighting_control_state == LEGACY_SUSPEND) अणु
			guid = LEGACY_POWER_CONTROL_GUID;
			legacy_args.state = lighting_control_state;
		पूर्ण अन्यथा
			guid = LEGACY_CONTROL_GUID;
		method_id = zone->location + 1;

		input.length = (acpi_size) माप(legacy_args);
		input.poपूर्णांकer = &legacy_args;
	पूर्ण
	pr_debug("alienware-wmi: guid %s method %d\n", guid, method_id);

	status = wmi_evaluate_method(guid, 0, method_id, &input, शून्य);
	अगर (ACPI_FAILURE(status))
		pr_err("alienware-wmi: zone set failure: %u\n", status);
	वापस ACPI_FAILURE(status);
पूर्ण

अटल sमाप_प्रकार zone_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा platक्रमm_zone *target_zone;
	target_zone = match_zone(attr);
	अगर (target_zone == शून्य)
		वापस प्र_लिखो(buf, "red: -1, green: -1, blue: -1\n");
	वापस प्र_लिखो(buf, "red: %d, green: %d, blue: %d\n",
		       target_zone->colors.red,
		       target_zone->colors.green, target_zone->colors.blue);

पूर्ण

अटल sमाप_प्रकार zone_set(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा platक्रमm_zone *target_zone;
	पूर्णांक ret;
	target_zone = match_zone(attr);
	अगर (target_zone == शून्य) अणु
		pr_err("alienware-wmi: invalid target zone\n");
		वापस 1;
	पूर्ण
	ret = parse_rgb(buf, target_zone);
	अगर (ret)
		वापस ret;
	ret = alienware_update_led(target_zone);
	वापस ret ? ret : count;
पूर्ण

/*
 * LED Brightness (Global)
 */
अटल पूर्णांक wmax_brightness(पूर्णांक brightness)
अणु
	acpi_status status;
	काष्ठा acpi_buffer input;
	काष्ठा wmax_brightness_args args = अणु
		.led_mask = 0xFF,
		.percentage = brightness,
	पूर्ण;
	input.length = (acpi_size) माप(args);
	input.poपूर्णांकer = &args;
	status = wmi_evaluate_method(WMAX_CONTROL_GUID, 0,
				     WMAX_METHOD_BRIGHTNESS, &input, शून्य);
	अगर (ACPI_FAILURE(status))
		pr_err("alienware-wmi: brightness set failure: %u\n", status);
	वापस ACPI_FAILURE(status);
पूर्ण

अटल व्योम global_led_set(काष्ठा led_classdev *led_cdev,
			   क्रमागत led_brightness brightness)
अणु
	पूर्णांक ret;
	global_brightness = brightness;
	अगर (पूर्णांकerface == WMAX)
		ret = wmax_brightness(brightness);
	अन्यथा
		ret = alienware_update_led(&zone_data[0]);
	अगर (ret)
		pr_err("LED brightness update failed\n");
पूर्ण

अटल क्रमागत led_brightness global_led_get(काष्ठा led_classdev *led_cdev)
अणु
	वापस global_brightness;
पूर्ण

अटल काष्ठा led_classdev global_led = अणु
	.brightness_set = global_led_set,
	.brightness_get = global_led_get,
	.name = "alienware::global_brightness",
पूर्ण;

/*
 * Lighting control state device attribute (Global)
 */
अटल sमाप_प्रकार show_control_state(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अगर (lighting_control_state == LEGACY_BOOTING)
		वापस scnम_लिखो(buf, PAGE_SIZE, "[booting] running suspend\n");
	अन्यथा अगर (lighting_control_state == LEGACY_SUSPEND)
		वापस scnम_लिखो(buf, PAGE_SIZE, "booting running [suspend]\n");
	वापस scnम_लिखो(buf, PAGE_SIZE, "booting [running] suspend\n");
पूर्ण

अटल sमाप_प्रकार store_control_state(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	दीर्घ अचिन्हित पूर्णांक val;
	अगर (म_भेद(buf, "booting\n") == 0)
		val = LEGACY_BOOTING;
	अन्यथा अगर (म_भेद(buf, "suspend\n") == 0)
		val = LEGACY_SUSPEND;
	अन्यथा अगर (पूर्णांकerface == LEGACY)
		val = LEGACY_RUNNING;
	अन्यथा
		val = WMAX_RUNNING;
	lighting_control_state = val;
	pr_debug("alienware-wmi: updated control state to %d\n",
		 lighting_control_state);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(lighting_control_state, 0644, show_control_state,
		   store_control_state);

अटल पूर्णांक alienware_zone_init(काष्ठा platक्रमm_device *dev)
अणु
	u8 zone;
	अक्षर buffer[10];
	अक्षर *name;

	अगर (पूर्णांकerface == WMAX) अणु
		lighting_control_state = WMAX_RUNNING;
	पूर्ण अन्यथा अगर (पूर्णांकerface == LEGACY) अणु
		lighting_control_state = LEGACY_RUNNING;
	पूर्ण
	global_led.max_brightness = 0x0F;
	global_brightness = global_led.max_brightness;

	/*
	 *      - zone_dev_attrs num_zones + 1 is क्रम inभागidual zones and then
	 *        null terminated
	 *      - zone_attrs num_zones + 2 is क्रम all attrs in zone_dev_attrs +
	 *        the lighting control + null terminated
	 *      - zone_data num_zones is क्रम the distinct zones
	 */
	zone_dev_attrs =
	    kसुस्मृति(quirks->num_zones + 1, माप(काष्ठा device_attribute),
		    GFP_KERNEL);
	अगर (!zone_dev_attrs)
		वापस -ENOMEM;

	zone_attrs =
	    kसुस्मृति(quirks->num_zones + 2, माप(काष्ठा attribute *),
		    GFP_KERNEL);
	अगर (!zone_attrs)
		वापस -ENOMEM;

	zone_data =
	    kसुस्मृति(quirks->num_zones, माप(काष्ठा platक्रमm_zone),
		    GFP_KERNEL);
	अगर (!zone_data)
		वापस -ENOMEM;

	क्रम (zone = 0; zone < quirks->num_zones; zone++) अणु
		प्र_लिखो(buffer, "zone%02hhX", zone);
		name = kstrdup(buffer, GFP_KERNEL);
		अगर (name == शून्य)
			वापस 1;
		sysfs_attr_init(&zone_dev_attrs[zone].attr);
		zone_dev_attrs[zone].attr.name = name;
		zone_dev_attrs[zone].attr.mode = 0644;
		zone_dev_attrs[zone].show = zone_show;
		zone_dev_attrs[zone].store = zone_set;
		zone_data[zone].location = zone;
		zone_attrs[zone] = &zone_dev_attrs[zone].attr;
		zone_data[zone].attr = &zone_dev_attrs[zone];
	पूर्ण
	zone_attrs[quirks->num_zones] = &dev_attr_lighting_control_state.attr;
	zone_attribute_group.attrs = zone_attrs;

	led_classdev_रेजिस्टर(&dev->dev, &global_led);

	वापस sysfs_create_group(&dev->dev.kobj, &zone_attribute_group);
पूर्ण

अटल व्योम alienware_zone_निकास(काष्ठा platक्रमm_device *dev)
अणु
	u8 zone;

	sysfs_हटाओ_group(&dev->dev.kobj, &zone_attribute_group);
	led_classdev_unरेजिस्टर(&global_led);
	अगर (zone_dev_attrs) अणु
		क्रम (zone = 0; zone < quirks->num_zones; zone++)
			kमुक्त(zone_dev_attrs[zone].attr.name);
	पूर्ण
	kमुक्त(zone_dev_attrs);
	kमुक्त(zone_data);
	kमुक्त(zone_attrs);
पूर्ण

अटल acpi_status alienware_wmax_command(काष्ठा wmax_basic_args *in_args,
					  u32 command, पूर्णांक *out_data)
अणु
	acpi_status status;
	जोड़ acpi_object *obj;
	काष्ठा acpi_buffer input;
	काष्ठा acpi_buffer output;

	input.length = (acpi_size) माप(*in_args);
	input.poपूर्णांकer = in_args;
	अगर (out_data) अणु
		output.length = ACPI_ALLOCATE_BUFFER;
		output.poपूर्णांकer = शून्य;
		status = wmi_evaluate_method(WMAX_CONTROL_GUID, 0,
					     command, &input, &output);
		अगर (ACPI_SUCCESS(status)) अणु
			obj = (जोड़ acpi_object *)output.poपूर्णांकer;
			अगर (obj && obj->type == ACPI_TYPE_INTEGER)
				*out_data = (u32)obj->पूर्णांकeger.value;
		पूर्ण
		kमुक्त(output.poपूर्णांकer);
	पूर्ण अन्यथा अणु
		status = wmi_evaluate_method(WMAX_CONTROL_GUID, 0,
					     command, &input, शून्य);
	पूर्ण
	वापस status;
पूर्ण

/*
 *	The HDMI mux sysfs node indicates the status of the HDMI input mux.
 *	It can toggle between standard प्रणाली GPU output and HDMI input.
 */
अटल sमाप_प्रकार show_hdmi_cable(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	acpi_status status;
	u32 out_data;
	काष्ठा wmax_basic_args in_args = अणु
		.arg = 0,
	पूर्ण;
	status =
	    alienware_wmax_command(&in_args, WMAX_METHOD_HDMI_CABLE,
				   (u32 *) &out_data);
	अगर (ACPI_SUCCESS(status)) अणु
		अगर (out_data == 0)
			वापस scnम_लिखो(buf, PAGE_SIZE,
					 "[unconnected] connected unknown\n");
		अन्यथा अगर (out_data == 1)
			वापस scnम_लिखो(buf, PAGE_SIZE,
					 "unconnected [connected] unknown\n");
	पूर्ण
	pr_err("alienware-wmi: unknown HDMI cable status: %d\n", status);
	वापस scnम_लिखो(buf, PAGE_SIZE, "unconnected connected [unknown]\n");
पूर्ण

अटल sमाप_प्रकार show_hdmi_source(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	acpi_status status;
	u32 out_data;
	काष्ठा wmax_basic_args in_args = अणु
		.arg = 0,
	पूर्ण;
	status =
	    alienware_wmax_command(&in_args, WMAX_METHOD_HDMI_STATUS,
				   (u32 *) &out_data);

	अगर (ACPI_SUCCESS(status)) अणु
		अगर (out_data == 1)
			वापस scnम_लिखो(buf, PAGE_SIZE,
					 "[input] gpu unknown\n");
		अन्यथा अगर (out_data == 2)
			वापस scnम_लिखो(buf, PAGE_SIZE,
					 "input [gpu] unknown\n");
	पूर्ण
	pr_err("alienware-wmi: unknown HDMI source status: %u\n", status);
	वापस scnम_लिखो(buf, PAGE_SIZE, "input gpu [unknown]\n");
पूर्ण

अटल sमाप_प्रकार toggle_hdmi_source(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	acpi_status status;
	काष्ठा wmax_basic_args args;
	अगर (म_भेद(buf, "gpu\n") == 0)
		args.arg = 1;
	अन्यथा अगर (म_भेद(buf, "input\n") == 0)
		args.arg = 2;
	अन्यथा
		args.arg = 3;
	pr_debug("alienware-wmi: setting hdmi to %d : %s", args.arg, buf);

	status = alienware_wmax_command(&args, WMAX_METHOD_HDMI_SOURCE, शून्य);

	अगर (ACPI_FAILURE(status))
		pr_err("alienware-wmi: HDMI toggle failed: results: %u\n",
		       status);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(cable, S_IRUGO, show_hdmi_cable, शून्य);
अटल DEVICE_ATTR(source, S_IRUGO | S_IWUSR, show_hdmi_source,
		   toggle_hdmi_source);

अटल काष्ठा attribute *hdmi_attrs[] = अणु
	&dev_attr_cable.attr,
	&dev_attr_source.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hdmi_attribute_group = अणु
	.name = "hdmi",
	.attrs = hdmi_attrs,
पूर्ण;

अटल व्योम हटाओ_hdmi(काष्ठा platक्रमm_device *dev)
अणु
	अगर (quirks->hdmi_mux > 0)
		sysfs_हटाओ_group(&dev->dev.kobj, &hdmi_attribute_group);
पूर्ण

अटल पूर्णांक create_hdmi(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret;

	ret = sysfs_create_group(&dev->dev.kobj, &hdmi_attribute_group);
	अगर (ret)
		हटाओ_hdmi(dev);
	वापस ret;
पूर्ण

/*
 * Alienware GFX amplअगरier support
 * - Currently supports पढ़ोing cable status
 * - Leaving expansion room to possibly support करोck/unकरोck events later
 */
अटल sमाप_प्रकार show_amplअगरier_status(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	acpi_status status;
	u32 out_data;
	काष्ठा wmax_basic_args in_args = अणु
		.arg = 0,
	पूर्ण;
	status =
	    alienware_wmax_command(&in_args, WMAX_METHOD_AMPLIFIER_CABLE,
				   (u32 *) &out_data);
	अगर (ACPI_SUCCESS(status)) अणु
		अगर (out_data == 0)
			वापस scnम_लिखो(buf, PAGE_SIZE,
					 "[unconnected] connected unknown\n");
		अन्यथा अगर (out_data == 1)
			वापस scnम_लिखो(buf, PAGE_SIZE,
					 "unconnected [connected] unknown\n");
	पूर्ण
	pr_err("alienware-wmi: unknown amplifier cable status: %d\n", status);
	वापस scnम_लिखो(buf, PAGE_SIZE, "unconnected connected [unknown]\n");
पूर्ण

अटल DEVICE_ATTR(status, S_IRUGO, show_amplअगरier_status, शून्य);

अटल काष्ठा attribute *amplअगरier_attrs[] = अणु
	&dev_attr_status.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group amplअगरier_attribute_group = अणु
	.name = "amplifier",
	.attrs = amplअगरier_attrs,
पूर्ण;

अटल व्योम हटाओ_amplअगरier(काष्ठा platक्रमm_device *dev)
अणु
	अगर (quirks->amplअगरier > 0)
		sysfs_हटाओ_group(&dev->dev.kobj, &amplअगरier_attribute_group);
पूर्ण

अटल पूर्णांक create_amplअगरier(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret;

	ret = sysfs_create_group(&dev->dev.kobj, &amplअगरier_attribute_group);
	अगर (ret)
		हटाओ_amplअगरier(dev);
	वापस ret;
पूर्ण

/*
 * Deep Sleep Control support
 * - Modअगरies BIOS setting क्रम deep sleep control allowing extra wakeup events
 */
अटल sमाप_प्रकार show_deepsleep_status(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	acpi_status status;
	u32 out_data;
	काष्ठा wmax_basic_args in_args = अणु
		.arg = 0,
	पूर्ण;
	status = alienware_wmax_command(&in_args, WMAX_METHOD_DEEP_SLEEP_STATUS,
					(u32 *) &out_data);
	अगर (ACPI_SUCCESS(status)) अणु
		अगर (out_data == 0)
			वापस scnम_लिखो(buf, PAGE_SIZE,
					 "[disabled] s5 s5_s4\n");
		अन्यथा अगर (out_data == 1)
			वापस scnम_लिखो(buf, PAGE_SIZE,
					 "disabled [s5] s5_s4\n");
		अन्यथा अगर (out_data == 2)
			वापस scnम_लिखो(buf, PAGE_SIZE,
					 "disabled s5 [s5_s4]\n");
	पूर्ण
	pr_err("alienware-wmi: unknown deep sleep status: %d\n", status);
	वापस scnम_लिखो(buf, PAGE_SIZE, "disabled s5 s5_s4 [unknown]\n");
पूर्ण

अटल sमाप_प्रकार toggle_deepsleep(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	acpi_status status;
	काष्ठा wmax_basic_args args;

	अगर (म_भेद(buf, "disabled\n") == 0)
		args.arg = 0;
	अन्यथा अगर (म_भेद(buf, "s5\n") == 0)
		args.arg = 1;
	अन्यथा
		args.arg = 2;
	pr_debug("alienware-wmi: setting deep sleep to %d : %s", args.arg, buf);

	status = alienware_wmax_command(&args, WMAX_METHOD_DEEP_SLEEP_CONTROL,
					शून्य);

	अगर (ACPI_FAILURE(status))
		pr_err("alienware-wmi: deep sleep control failed: results: %u\n",
			status);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(deepsleep, S_IRUGO | S_IWUSR, show_deepsleep_status, toggle_deepsleep);

अटल काष्ठा attribute *deepsleep_attrs[] = अणु
	&dev_attr_deepsleep.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group deepsleep_attribute_group = अणु
	.name = "deepsleep",
	.attrs = deepsleep_attrs,
पूर्ण;

अटल व्योम हटाओ_deepsleep(काष्ठा platक्रमm_device *dev)
अणु
	अगर (quirks->deepslp > 0)
		sysfs_हटाओ_group(&dev->dev.kobj, &deepsleep_attribute_group);
पूर्ण

अटल पूर्णांक create_deepsleep(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret;

	ret = sysfs_create_group(&dev->dev.kobj, &deepsleep_attribute_group);
	अगर (ret)
		हटाओ_deepsleep(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक __init alienware_wmi_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (wmi_has_guid(LEGACY_CONTROL_GUID))
		पूर्णांकerface = LEGACY;
	अन्यथा अगर (wmi_has_guid(WMAX_CONTROL_GUID))
		पूर्णांकerface = WMAX;
	अन्यथा अणु
		pr_warn("alienware-wmi: No known WMI GUID found\n");
		वापस -ENODEV;
	पूर्ण

	dmi_check_प्रणाली(alienware_quirks);
	अगर (quirks == शून्य)
		quirks = &quirk_unknown;

	ret = platक्रमm_driver_रेजिस्टर(&platक्रमm_driver);
	अगर (ret)
		जाओ fail_platक्रमm_driver;
	platक्रमm_device = platक्रमm_device_alloc("alienware-wmi", -1);
	अगर (!platक्रमm_device) अणु
		ret = -ENOMEM;
		जाओ fail_platक्रमm_device1;
	पूर्ण
	ret = platक्रमm_device_add(platक्रमm_device);
	अगर (ret)
		जाओ fail_platक्रमm_device2;

	अगर (quirks->hdmi_mux > 0) अणु
		ret = create_hdmi(platक्रमm_device);
		अगर (ret)
			जाओ fail_prep_hdmi;
	पूर्ण

	अगर (quirks->amplअगरier > 0) अणु
		ret = create_amplअगरier(platक्रमm_device);
		अगर (ret)
			जाओ fail_prep_amplअगरier;
	पूर्ण

	अगर (quirks->deepslp > 0) अणु
		ret = create_deepsleep(platक्रमm_device);
		अगर (ret)
			जाओ fail_prep_deepsleep;
	पूर्ण

	ret = alienware_zone_init(platक्रमm_device);
	अगर (ret)
		जाओ fail_prep_zones;

	वापस 0;

fail_prep_zones:
	alienware_zone_निकास(platक्रमm_device);
fail_prep_deepsleep:
fail_prep_amplअगरier:
fail_prep_hdmi:
	platक्रमm_device_del(platक्रमm_device);
fail_platक्रमm_device2:
	platक्रमm_device_put(platक्रमm_device);
fail_platक्रमm_device1:
	platक्रमm_driver_unरेजिस्टर(&platक्रमm_driver);
fail_platक्रमm_driver:
	वापस ret;
पूर्ण

module_init(alienware_wmi_init);

अटल व्योम __निकास alienware_wmi_निकास(व्योम)
अणु
	अगर (platक्रमm_device) अणु
		alienware_zone_निकास(platक्रमm_device);
		हटाओ_hdmi(platक्रमm_device);
		platक्रमm_device_unरेजिस्टर(platक्रमm_device);
		platक्रमm_driver_unरेजिस्टर(&platक्रमm_driver);
	पूर्ण
पूर्ण

module_निकास(alienware_wmi_निकास);
