<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HP WMI hotkeys
 *
 * Copyright (C) 2008 Red Hat <mjg@redhat.com>
 * Copyright (C) 2010, 2011 Anssi Hannula <anssi.hannula@iki.fi>
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
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_profile.h>
#समावेश <linux/acpi.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/माला.स>

MODULE_AUTHOR("Matthew Garrett <mjg59@srcf.ucam.org>");
MODULE_DESCRIPTION("HP laptop WMI hotkeys driver");
MODULE_LICENSE("GPL");

MODULE_ALIAS("wmi:95F24279-4D7B-4334-9387-ACCDC67EF61C");
MODULE_ALIAS("wmi:5FB7F034-2C63-45e9-BE91-3D44E2C707E4");

अटल पूर्णांक enable_tablet_mode_sw = -1;
module_param(enable_tablet_mode_sw, पूर्णांक, 0444);
MODULE_PARM_DESC(enable_tablet_mode_sw, "Enable SW_TABLET_MODE reporting (-1=auto, 0=no, 1=yes)");

#घोषणा HPWMI_EVENT_GUID "95F24279-4D7B-4334-9387-ACCDC67EF61C"
#घोषणा HPWMI_BIOS_GUID "5FB7F034-2C63-45e9-BE91-3D44E2C707E4"

क्रमागत hp_wmi_radio अणु
	HPWMI_WIFI	= 0x0,
	HPWMI_BLUETOOTH	= 0x1,
	HPWMI_WWAN	= 0x2,
	HPWMI_GPS	= 0x3,
पूर्ण;

क्रमागत hp_wmi_event_ids अणु
	HPWMI_DOCK_EVENT		= 0x01,
	HPWMI_PARK_HDD			= 0x02,
	HPWMI_SMART_ADAPTER		= 0x03,
	HPWMI_BEZEL_BUTTON		= 0x04,
	HPWMI_WIRELESS			= 0x05,
	HPWMI_CPU_BATTERY_THROTTLE	= 0x06,
	HPWMI_LOCK_SWITCH		= 0x07,
	HPWMI_LID_SWITCH		= 0x08,
	HPWMI_SCREEN_ROTATION		= 0x09,
	HPWMI_COOLSENSE_SYSTEM_MOBILE	= 0x0A,
	HPWMI_COOLSENSE_SYSTEM_HOT	= 0x0B,
	HPWMI_PROXIMITY_SENSOR		= 0x0C,
	HPWMI_BACKLIT_KB_BRIGHTNESS	= 0x0D,
	HPWMI_PEAKSHIFT_PERIOD		= 0x0F,
	HPWMI_BATTERY_CHARGE_PERIOD	= 0x10,
पूर्ण;

काष्ठा bios_args अणु
	u32 signature;
	u32 command;
	u32 commandtype;
	u32 datasize;
	u8 data[128];
पूर्ण;

क्रमागत hp_wmi_commandtype अणु
	HPWMI_DISPLAY_QUERY		= 0x01,
	HPWMI_HDDTEMP_QUERY		= 0x02,
	HPWMI_ALS_QUERY			= 0x03,
	HPWMI_HARDWARE_QUERY		= 0x04,
	HPWMI_WIRELESS_QUERY		= 0x05,
	HPWMI_BATTERY_QUERY		= 0x07,
	HPWMI_BIOS_QUERY		= 0x09,
	HPWMI_FEATURE_QUERY		= 0x0b,
	HPWMI_HOTKEY_QUERY		= 0x0c,
	HPWMI_FEATURE2_QUERY		= 0x0d,
	HPWMI_WIRELESS2_QUERY		= 0x1b,
	HPWMI_POSTCODEERROR_QUERY	= 0x2a,
	HPWMI_THERMAL_PROखाता_QUERY	= 0x4c,
पूर्ण;

क्रमागत hp_wmi_command अणु
	HPWMI_READ	= 0x01,
	HPWMI_WRITE	= 0x02,
	HPWMI_ODM	= 0x03,
पूर्ण;

क्रमागत hp_wmi_hardware_mask अणु
	HPWMI_DOCK_MASK		= 0x01,
	HPWMI_TABLET_MASK	= 0x04,
पूर्ण;

काष्ठा bios_वापस अणु
	u32 sigpass;
	u32 वापस_code;
पूर्ण;

क्रमागत hp_वापस_value अणु
	HPWMI_RET_WRONG_SIGNATURE	= 0x02,
	HPWMI_RET_UNKNOWN_COMMAND	= 0x03,
	HPWMI_RET_UNKNOWN_CMDTYPE	= 0x04,
	HPWMI_RET_INVALID_PARAMETERS	= 0x05,
पूर्ण;

क्रमागत hp_wireless2_bits अणु
	HPWMI_POWER_STATE	= 0x01,
	HPWMI_POWER_SOFT	= 0x02,
	HPWMI_POWER_BIOS	= 0x04,
	HPWMI_POWER_HARD	= 0x08,
	HPWMI_POWER_FW_OR_HW	= HPWMI_POWER_BIOS | HPWMI_POWER_HARD,
पूर्ण;

क्रमागत hp_thermal_profile अणु
	HP_THERMAL_PROखाता_PERFORMANCE	= 0x00,
	HP_THERMAL_PROखाता_DEFAULT		= 0x01,
	HP_THERMAL_PROखाता_COOL			= 0x02
पूर्ण;

#घोषणा IS_HWBLOCKED(x) ((x & HPWMI_POWER_FW_OR_HW) != HPWMI_POWER_FW_OR_HW)
#घोषणा IS_SWBLOCKED(x) !(x & HPWMI_POWER_SOFT)

काष्ठा bios_rfसमाप्त2_device_state अणु
	u8 radio_type;
	u8 bus_type;
	u16 venकरोr_id;
	u16 product_id;
	u16 subsys_venकरोr_id;
	u16 subsys_product_id;
	u8 rfसमाप्त_id;
	u8 घातer;
	u8 unknown[4];
पूर्ण;

/* 7 devices fit पूर्णांकo the 128 byte buffer */
#घोषणा HPWMI_MAX_RFKILL2_DEVICES	7

काष्ठा bios_rfसमाप्त2_state अणु
	u8 unknown[7];
	u8 count;
	u8 pad[8];
	काष्ठा bios_rfसमाप्त2_device_state device[HPWMI_MAX_RFKILL2_DEVICES];
पूर्ण;

अटल स्थिर काष्ठा key_entry hp_wmi_keymap[] = अणु
	अणु KE_KEY, 0x02,   अणु KEY_BRIGHTNESSUP पूर्ण पूर्ण,
	अणु KE_KEY, 0x03,   अणु KEY_BRIGHTNESSDOWN पूर्ण पूर्ण,
	अणु KE_KEY, 0x20e6, अणु KEY_PROG1 पूर्ण पूर्ण,
	अणु KE_KEY, 0x20e8, अणु KEY_MEDIA पूर्ण पूर्ण,
	अणु KE_KEY, 0x2142, अणु KEY_MEDIA पूर्ण पूर्ण,
	अणु KE_KEY, 0x213b, अणु KEY_INFO पूर्ण पूर्ण,
	अणु KE_KEY, 0x2169, अणु KEY_ROTATE_DISPLAY पूर्ण पूर्ण,
	अणु KE_KEY, 0x216a, अणु KEY_SETUP पूर्ण पूर्ण,
	अणु KE_KEY, 0x231b, अणु KEY_HELP पूर्ण पूर्ण,
	अणु KE_END, 0 पूर्ण
पूर्ण;

अटल काष्ठा input_dev *hp_wmi_input_dev;
अटल काष्ठा platक्रमm_device *hp_wmi_platक्रमm_dev;
अटल काष्ठा platक्रमm_profile_handler platक्रमm_profile_handler;
अटल bool platक्रमm_profile_support;

अटल काष्ठा rfसमाप्त *wअगरi_rfसमाप्त;
अटल काष्ठा rfसमाप्त *bluetooth_rfसमाप्त;
अटल काष्ठा rfसमाप्त *wwan_rfसमाप्त;

काष्ठा rfसमाप्त2_device अणु
	u8 id;
	पूर्णांक num;
	काष्ठा rfसमाप्त *rfसमाप्त;
पूर्ण;

अटल पूर्णांक rfसमाप्त2_count;
अटल काष्ठा rfसमाप्त2_device rfसमाप्त2[HPWMI_MAX_RFKILL2_DEVICES];

/* map output size to the corresponding WMI method id */
अटल अंतरभूत पूर्णांक encode_outsize_क्रम_pvsz(पूर्णांक outsize)
अणु
	अगर (outsize > 4096)
		वापस -EINVAL;
	अगर (outsize > 1024)
		वापस 5;
	अगर (outsize > 128)
		वापस 4;
	अगर (outsize > 4)
		वापस 3;
	अगर (outsize > 0)
		वापस 2;
	वापस 1;
पूर्ण

/*
 * hp_wmi_perक्रमm_query
 *
 * query:	The commandtype (क्रमागत hp_wmi_commandtype)
 * ग_लिखो:	The command (क्रमागत hp_wmi_command)
 * buffer:	Buffer used as input and/or output
 * insize:	Size of input buffer
 * outsize:	Size of output buffer
 *
 * वापसs zero on success
 *         an HP WMI query specअगरic error code (which is positive)
 *         -EINVAL अगर the query was not successful at all
 *         -EINVAL अगर the output buffer size exceeds buffersize
 *
 * Note: The buffersize must at least be the maximum of the input and output
 *       size. E.g. Battery info query is defined to have 1 byte input
 *       and 128 byte output. The caller would करो:
 *       buffer = kzalloc(128, GFP_KERNEL);
 *       ret = hp_wmi_perक्रमm_query(HPWMI_BATTERY_QUERY, HPWMI_READ, buffer, 1, 128)
 */
अटल पूर्णांक hp_wmi_perक्रमm_query(पूर्णांक query, क्रमागत hp_wmi_command command,
				व्योम *buffer, पूर्णांक insize, पूर्णांक outsize)
अणु
	पूर्णांक mid;
	काष्ठा bios_वापस *bios_वापस;
	पूर्णांक actual_outsize;
	जोड़ acpi_object *obj;
	काष्ठा bios_args args = अणु
		.signature = 0x55434553,
		.command = command,
		.commandtype = query,
		.datasize = insize,
		.data = अणु 0 पूर्ण,
	पूर्ण;
	काष्ठा acpi_buffer input = अणु माप(काष्ठा bios_args), &args पूर्ण;
	काष्ठा acpi_buffer output = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	पूर्णांक ret = 0;

	mid = encode_outsize_क्रम_pvsz(outsize);
	अगर (WARN_ON(mid < 0))
		वापस mid;

	अगर (WARN_ON(insize > माप(args.data)))
		वापस -EINVAL;
	स_नकल(&args.data[0], buffer, insize);

	wmi_evaluate_method(HPWMI_BIOS_GUID, 0, mid, &input, &output);

	obj = output.poपूर्णांकer;

	अगर (!obj)
		वापस -EINVAL;

	अगर (obj->type != ACPI_TYPE_BUFFER) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	bios_वापस = (काष्ठा bios_वापस *)obj->buffer.poपूर्णांकer;
	ret = bios_वापस->वापस_code;

	अगर (ret) अणु
		अगर (ret != HPWMI_RET_UNKNOWN_COMMAND &&
		    ret != HPWMI_RET_UNKNOWN_CMDTYPE)
			pr_warn("query 0x%x returned error 0x%x\n", query, ret);
		जाओ out_मुक्त;
	पूर्ण

	/* Ignore output data of zero size */
	अगर (!outsize)
		जाओ out_मुक्त;

	actual_outsize = min(outsize, (पूर्णांक)(obj->buffer.length - माप(*bios_वापस)));
	स_नकल(buffer, obj->buffer.poपूर्णांकer + माप(*bios_वापस), actual_outsize);
	स_रखो(buffer + actual_outsize, 0, outsize - actual_outsize);

out_मुक्त:
	kमुक्त(obj);
	वापस ret;
पूर्ण

अटल पूर्णांक hp_wmi_पढ़ो_पूर्णांक(पूर्णांक query)
अणु
	पूर्णांक val = 0, ret;

	ret = hp_wmi_perक्रमm_query(query, HPWMI_READ, &val,
				   माप(val), माप(val));

	अगर (ret)
		वापस ret < 0 ? ret : -EINVAL;

	वापस val;
पूर्ण

अटल पूर्णांक hp_wmi_hw_state(पूर्णांक mask)
अणु
	पूर्णांक state = hp_wmi_पढ़ो_पूर्णांक(HPWMI_HARDWARE_QUERY);

	अगर (state < 0)
		वापस state;

	वापस !!(state & mask);
पूर्ण

अटल पूर्णांक __init hp_wmi_bios_2008_later(व्योम)
अणु
	पूर्णांक state = 0;
	पूर्णांक ret = hp_wmi_perक्रमm_query(HPWMI_FEATURE_QUERY, HPWMI_READ, &state,
				       माप(state), माप(state));
	अगर (!ret)
		वापस 1;

	वापस (ret == HPWMI_RET_UNKNOWN_CMDTYPE) ? 0 : -ENXIO;
पूर्ण

अटल पूर्णांक __init hp_wmi_bios_2009_later(व्योम)
अणु
	u8 state[128];
	पूर्णांक ret = hp_wmi_perक्रमm_query(HPWMI_FEATURE2_QUERY, HPWMI_READ, &state,
				       माप(state), माप(state));
	अगर (!ret)
		वापस 1;

	वापस (ret == HPWMI_RET_UNKNOWN_CMDTYPE) ? 0 : -ENXIO;
पूर्ण

अटल पूर्णांक __init hp_wmi_enable_hotkeys(व्योम)
अणु
	पूर्णांक value = 0x6e;
	पूर्णांक ret = hp_wmi_perक्रमm_query(HPWMI_BIOS_QUERY, HPWMI_WRITE, &value,
				       माप(value), 0);

	वापस ret <= 0 ? ret : -EINVAL;
पूर्ण

अटल पूर्णांक hp_wmi_set_block(व्योम *data, bool blocked)
अणु
	क्रमागत hp_wmi_radio r = (क्रमागत hp_wmi_radio) data;
	पूर्णांक query = BIT(r + 8) | ((!blocked) << r);
	पूर्णांक ret;

	ret = hp_wmi_perक्रमm_query(HPWMI_WIRELESS_QUERY, HPWMI_WRITE,
				   &query, माप(query), 0);

	वापस ret <= 0 ? ret : -EINVAL;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops hp_wmi_rfसमाप्त_ops = अणु
	.set_block = hp_wmi_set_block,
पूर्ण;

अटल bool hp_wmi_get_sw_state(क्रमागत hp_wmi_radio r)
अणु
	पूर्णांक mask = 0x200 << (r * 8);

	पूर्णांक wireless = hp_wmi_पढ़ो_पूर्णांक(HPWMI_WIRELESS_QUERY);

	/* TBD: Pass error */
	WARN_ONCE(wireless < 0, "error executing HPWMI_WIRELESS_QUERY");

	वापस !(wireless & mask);
पूर्ण

अटल bool hp_wmi_get_hw_state(क्रमागत hp_wmi_radio r)
अणु
	पूर्णांक mask = 0x800 << (r * 8);

	पूर्णांक wireless = hp_wmi_पढ़ो_पूर्णांक(HPWMI_WIRELESS_QUERY);

	/* TBD: Pass error */
	WARN_ONCE(wireless < 0, "error executing HPWMI_WIRELESS_QUERY");

	वापस !(wireless & mask);
पूर्ण

अटल पूर्णांक hp_wmi_rfसमाप्त2_set_block(व्योम *data, bool blocked)
अणु
	पूर्णांक rfसमाप्त_id = (पूर्णांक)(दीर्घ)data;
	अक्षर buffer[4] = अणु 0x01, 0x00, rfसमाप्त_id, !blocked पूर्ण;
	पूर्णांक ret;

	ret = hp_wmi_perक्रमm_query(HPWMI_WIRELESS2_QUERY, HPWMI_WRITE,
				   buffer, माप(buffer), 0);

	वापस ret <= 0 ? ret : -EINVAL;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops hp_wmi_rfसमाप्त2_ops = अणु
	.set_block = hp_wmi_rfसमाप्त2_set_block,
पूर्ण;

अटल पूर्णांक hp_wmi_rfसमाप्त2_refresh(व्योम)
अणु
	काष्ठा bios_rfसमाप्त2_state state;
	पूर्णांक err, i;

	err = hp_wmi_perक्रमm_query(HPWMI_WIRELESS2_QUERY, HPWMI_READ, &state,
				   माप(state), माप(state));
	अगर (err)
		वापस err;

	क्रम (i = 0; i < rfसमाप्त2_count; i++) अणु
		पूर्णांक num = rfसमाप्त2[i].num;
		काष्ठा bios_rfसमाप्त2_device_state *devstate;
		devstate = &state.device[num];

		अगर (num >= state.count ||
		    devstate->rfसमाप्त_id != rfसमाप्त2[i].id) अणु
			pr_warn("power configuration of the wireless devices unexpectedly changed\n");
			जारी;
		पूर्ण

		rfसमाप्त_set_states(rfसमाप्त2[i].rfसमाप्त,
				  IS_SWBLOCKED(devstate->घातer),
				  IS_HWBLOCKED(devstate->घातer));
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार display_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	पूर्णांक value = hp_wmi_पढ़ो_पूर्णांक(HPWMI_DISPLAY_QUERY);
	अगर (value < 0)
		वापस value;
	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार hddtemp_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	पूर्णांक value = hp_wmi_पढ़ो_पूर्णांक(HPWMI_HDDTEMP_QUERY);
	अगर (value < 0)
		वापस value;
	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार als_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	पूर्णांक value = hp_wmi_पढ़ो_पूर्णांक(HPWMI_ALS_QUERY);
	अगर (value < 0)
		वापस value;
	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार करोck_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	पूर्णांक value = hp_wmi_hw_state(HPWMI_DOCK_MASK);
	अगर (value < 0)
		वापस value;
	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार tablet_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक value = hp_wmi_hw_state(HPWMI_TABLET_MASK);
	अगर (value < 0)
		वापस value;
	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार postcode_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	/* Get the POST error code of previous boot failure. */
	पूर्णांक value = hp_wmi_पढ़ो_पूर्णांक(HPWMI_POSTCODEERROR_QUERY);
	अगर (value < 0)
		वापस value;
	वापस प्र_लिखो(buf, "0x%x\n", value);
पूर्ण

अटल sमाप_प्रकार als_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 पंचांगp;
	पूर्णांक ret;

	ret = kstrtou32(buf, 10, &पंचांगp);
	अगर (ret)
		वापस ret;

	ret = hp_wmi_perक्रमm_query(HPWMI_ALS_QUERY, HPWMI_WRITE, &पंचांगp,
				       माप(पंचांगp), माप(पंचांगp));
	अगर (ret)
		वापस ret < 0 ? ret : -EINVAL;

	वापस count;
पूर्ण

अटल sमाप_प्रकार postcode_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 पंचांगp = 1;
	bool clear;
	पूर्णांक ret;

	ret = kstrtobool(buf, &clear);
	अगर (ret)
		वापस ret;

	अगर (clear == false)
		वापस -EINVAL;

	/* Clear the POST error code. It is kept until until cleared. */
	ret = hp_wmi_perक्रमm_query(HPWMI_POSTCODEERROR_QUERY, HPWMI_WRITE, &पंचांगp,
				       माप(पंचांगp), माप(पंचांगp));
	अगर (ret)
		वापस ret < 0 ? ret : -EINVAL;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RO(display);
अटल DEVICE_ATTR_RO(hddtemp);
अटल DEVICE_ATTR_RW(als);
अटल DEVICE_ATTR_RO(करोck);
अटल DEVICE_ATTR_RO(tablet);
अटल DEVICE_ATTR_RW(postcode);

अटल काष्ठा attribute *hp_wmi_attrs[] = अणु
	&dev_attr_display.attr,
	&dev_attr_hddtemp.attr,
	&dev_attr_als.attr,
	&dev_attr_करोck.attr,
	&dev_attr_tablet.attr,
	&dev_attr_postcode.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(hp_wmi);

अटल व्योम hp_wmi_notअगरy(u32 value, व्योम *context)
अणु
	काष्ठा acpi_buffer response = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	u32 event_id, event_data;
	जोड़ acpi_object *obj;
	acpi_status status;
	u32 *location;
	पूर्णांक key_code;

	status = wmi_get_event_data(value, &response);
	अगर (status != AE_OK) अणु
		pr_info("bad event status 0x%x\n", status);
		वापस;
	पूर्ण

	obj = (जोड़ acpi_object *)response.poपूर्णांकer;

	अगर (!obj)
		वापस;
	अगर (obj->type != ACPI_TYPE_BUFFER) अणु
		pr_info("Unknown response received %d\n", obj->type);
		kमुक्त(obj);
		वापस;
	पूर्ण

	/*
	 * Depending on ACPI version the concatenation of id and event data
	 * inside _WED function will result in a 8 or 16 byte buffer.
	 */
	location = (u32 *)obj->buffer.poपूर्णांकer;
	अगर (obj->buffer.length == 8) अणु
		event_id = *location;
		event_data = *(location + 1);
	पूर्ण अन्यथा अगर (obj->buffer.length == 16) अणु
		event_id = *location;
		event_data = *(location + 2);
	पूर्ण अन्यथा अणु
		pr_info("Unknown buffer length %d\n", obj->buffer.length);
		kमुक्त(obj);
		वापस;
	पूर्ण
	kमुक्त(obj);

	चयन (event_id) अणु
	हाल HPWMI_DOCK_EVENT:
		अगर (test_bit(SW_DOCK, hp_wmi_input_dev->swbit))
			input_report_चयन(hp_wmi_input_dev, SW_DOCK,
					    hp_wmi_hw_state(HPWMI_DOCK_MASK));
		अगर (test_bit(SW_TABLET_MODE, hp_wmi_input_dev->swbit))
			input_report_चयन(hp_wmi_input_dev, SW_TABLET_MODE,
					    hp_wmi_hw_state(HPWMI_TABLET_MASK));
		input_sync(hp_wmi_input_dev);
		अवरोध;
	हाल HPWMI_PARK_HDD:
		अवरोध;
	हाल HPWMI_SMART_ADAPTER:
		अवरोध;
	हाल HPWMI_BEZEL_BUTTON:
		key_code = hp_wmi_पढ़ो_पूर्णांक(HPWMI_HOTKEY_QUERY);
		अगर (key_code < 0)
			अवरोध;

		अगर (!sparse_keymap_report_event(hp_wmi_input_dev,
						key_code, 1, true))
			pr_info("Unknown key code - 0x%x\n", key_code);
		अवरोध;
	हाल HPWMI_WIRELESS:
		अगर (rfसमाप्त2_count) अणु
			hp_wmi_rfसमाप्त2_refresh();
			अवरोध;
		पूर्ण

		अगर (wअगरi_rfसमाप्त)
			rfसमाप्त_set_states(wअगरi_rfसमाप्त,
					  hp_wmi_get_sw_state(HPWMI_WIFI),
					  hp_wmi_get_hw_state(HPWMI_WIFI));
		अगर (bluetooth_rfसमाप्त)
			rfसमाप्त_set_states(bluetooth_rfसमाप्त,
					  hp_wmi_get_sw_state(HPWMI_BLUETOOTH),
					  hp_wmi_get_hw_state(HPWMI_BLUETOOTH));
		अगर (wwan_rfसमाप्त)
			rfसमाप्त_set_states(wwan_rfसमाप्त,
					  hp_wmi_get_sw_state(HPWMI_WWAN),
					  hp_wmi_get_hw_state(HPWMI_WWAN));
		अवरोध;
	हाल HPWMI_CPU_BATTERY_THROTTLE:
		pr_info("Unimplemented CPU throttle because of 3 Cell battery event detected\n");
		अवरोध;
	हाल HPWMI_LOCK_SWITCH:
		अवरोध;
	हाल HPWMI_LID_SWITCH:
		अवरोध;
	हाल HPWMI_SCREEN_ROTATION:
		अवरोध;
	हाल HPWMI_COOLSENSE_SYSTEM_MOBILE:
		अवरोध;
	हाल HPWMI_COOLSENSE_SYSTEM_HOT:
		अवरोध;
	हाल HPWMI_PROXIMITY_SENSOR:
		अवरोध;
	हाल HPWMI_BACKLIT_KB_BRIGHTNESS:
		अवरोध;
	हाल HPWMI_PEAKSHIFT_PERIOD:
		अवरोध;
	हाल HPWMI_BATTERY_CHARGE_PERIOD:
		अवरोध;
	शेष:
		pr_info("Unknown event_id - %d - 0x%x\n", event_id, event_data);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक __init hp_wmi_input_setup(व्योम)
अणु
	acpi_status status;
	पूर्णांक err, val;

	hp_wmi_input_dev = input_allocate_device();
	अगर (!hp_wmi_input_dev)
		वापस -ENOMEM;

	hp_wmi_input_dev->name = "HP WMI hotkeys";
	hp_wmi_input_dev->phys = "wmi/input0";
	hp_wmi_input_dev->id.bustype = BUS_HOST;

	__set_bit(EV_SW, hp_wmi_input_dev->evbit);

	/* Dock */
	val = hp_wmi_hw_state(HPWMI_DOCK_MASK);
	अगर (!(val < 0)) अणु
		__set_bit(SW_DOCK, hp_wmi_input_dev->swbit);
		input_report_चयन(hp_wmi_input_dev, SW_DOCK, val);
	पूर्ण

	/* Tablet mode */
	अगर (enable_tablet_mode_sw > 0) अणु
		val = hp_wmi_hw_state(HPWMI_TABLET_MASK);
		अगर (val >= 0) अणु
			__set_bit(SW_TABLET_MODE, hp_wmi_input_dev->swbit);
			input_report_चयन(hp_wmi_input_dev, SW_TABLET_MODE, val);
		पूर्ण
	पूर्ण

	err = sparse_keymap_setup(hp_wmi_input_dev, hp_wmi_keymap, शून्य);
	अगर (err)
		जाओ err_मुक्त_dev;

	/* Set initial hardware state */
	input_sync(hp_wmi_input_dev);

	अगर (!hp_wmi_bios_2009_later() && hp_wmi_bios_2008_later())
		hp_wmi_enable_hotkeys();

	status = wmi_install_notअगरy_handler(HPWMI_EVENT_GUID, hp_wmi_notअगरy, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		err = -EIO;
		जाओ err_मुक्त_dev;
	पूर्ण

	err = input_रेजिस्टर_device(hp_wmi_input_dev);
	अगर (err)
		जाओ err_uninstall_notअगरier;

	वापस 0;

 err_uninstall_notअगरier:
	wmi_हटाओ_notअगरy_handler(HPWMI_EVENT_GUID);
 err_मुक्त_dev:
	input_मुक्त_device(hp_wmi_input_dev);
	वापस err;
पूर्ण

अटल व्योम hp_wmi_input_destroy(व्योम)
अणु
	wmi_हटाओ_notअगरy_handler(HPWMI_EVENT_GUID);
	input_unरेजिस्टर_device(hp_wmi_input_dev);
पूर्ण

अटल पूर्णांक __init hp_wmi_rfसमाप्त_setup(काष्ठा platक्रमm_device *device)
अणु
	पूर्णांक err, wireless;

	wireless = hp_wmi_पढ़ो_पूर्णांक(HPWMI_WIRELESS_QUERY);
	अगर (wireless < 0)
		वापस wireless;

	err = hp_wmi_perक्रमm_query(HPWMI_WIRELESS_QUERY, HPWMI_WRITE, &wireless,
				   माप(wireless), 0);
	अगर (err)
		वापस err;

	अगर (wireless & 0x1) अणु
		wअगरi_rfसमाप्त = rfसमाप्त_alloc("hp-wifi", &device->dev,
					   RFKILL_TYPE_WLAN,
					   &hp_wmi_rfसमाप्त_ops,
					   (व्योम *) HPWMI_WIFI);
		अगर (!wअगरi_rfसमाप्त)
			वापस -ENOMEM;
		rfसमाप्त_init_sw_state(wअगरi_rfसमाप्त,
				     hp_wmi_get_sw_state(HPWMI_WIFI));
		rfसमाप्त_set_hw_state(wअगरi_rfसमाप्त,
				    hp_wmi_get_hw_state(HPWMI_WIFI));
		err = rfसमाप्त_रेजिस्टर(wअगरi_rfसमाप्त);
		अगर (err)
			जाओ रेजिस्टर_wअगरi_error;
	पूर्ण

	अगर (wireless & 0x2) अणु
		bluetooth_rfसमाप्त = rfसमाप्त_alloc("hp-bluetooth", &device->dev,
						RFKILL_TYPE_BLUETOOTH,
						&hp_wmi_rfसमाप्त_ops,
						(व्योम *) HPWMI_BLUETOOTH);
		अगर (!bluetooth_rfसमाप्त) अणु
			err = -ENOMEM;
			जाओ रेजिस्टर_bluetooth_error;
		पूर्ण
		rfसमाप्त_init_sw_state(bluetooth_rfसमाप्त,
				     hp_wmi_get_sw_state(HPWMI_BLUETOOTH));
		rfसमाप्त_set_hw_state(bluetooth_rfसमाप्त,
				    hp_wmi_get_hw_state(HPWMI_BLUETOOTH));
		err = rfसमाप्त_रेजिस्टर(bluetooth_rfसमाप्त);
		अगर (err)
			जाओ रेजिस्टर_bluetooth_error;
	पूर्ण

	अगर (wireless & 0x4) अणु
		wwan_rfसमाप्त = rfसमाप्त_alloc("hp-wwan", &device->dev,
					   RFKILL_TYPE_WWAN,
					   &hp_wmi_rfसमाप्त_ops,
					   (व्योम *) HPWMI_WWAN);
		अगर (!wwan_rfसमाप्त) अणु
			err = -ENOMEM;
			जाओ रेजिस्टर_wwan_error;
		पूर्ण
		rfसमाप्त_init_sw_state(wwan_rfसमाप्त,
				     hp_wmi_get_sw_state(HPWMI_WWAN));
		rfसमाप्त_set_hw_state(wwan_rfसमाप्त,
				    hp_wmi_get_hw_state(HPWMI_WWAN));
		err = rfसमाप्त_रेजिस्टर(wwan_rfसमाप्त);
		अगर (err)
			जाओ रेजिस्टर_wwan_error;
	पूर्ण

	वापस 0;

रेजिस्टर_wwan_error:
	rfसमाप्त_destroy(wwan_rfसमाप्त);
	wwan_rfसमाप्त = शून्य;
	अगर (bluetooth_rfसमाप्त)
		rfसमाप्त_unरेजिस्टर(bluetooth_rfसमाप्त);
रेजिस्टर_bluetooth_error:
	rfसमाप्त_destroy(bluetooth_rfसमाप्त);
	bluetooth_rfसमाप्त = शून्य;
	अगर (wअगरi_rfसमाप्त)
		rfसमाप्त_unरेजिस्टर(wअगरi_rfसमाप्त);
रेजिस्टर_wअगरi_error:
	rfसमाप्त_destroy(wअगरi_rfसमाप्त);
	wअगरi_rfसमाप्त = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक __init hp_wmi_rfसमाप्त2_setup(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा bios_rfसमाप्त2_state state;
	पूर्णांक err, i;

	err = hp_wmi_perक्रमm_query(HPWMI_WIRELESS2_QUERY, HPWMI_READ, &state,
				   माप(state), माप(state));
	अगर (err)
		वापस err < 0 ? err : -EINVAL;

	अगर (state.count > HPWMI_MAX_RFKILL2_DEVICES) अणु
		pr_warn("unable to parse 0x1b query output\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < state.count; i++) अणु
		काष्ठा rfसमाप्त *rfसमाप्त;
		क्रमागत rfसमाप्त_type type;
		अक्षर *name;
		चयन (state.device[i].radio_type) अणु
		हाल HPWMI_WIFI:
			type = RFKILL_TYPE_WLAN;
			name = "hp-wifi";
			अवरोध;
		हाल HPWMI_BLUETOOTH:
			type = RFKILL_TYPE_BLUETOOTH;
			name = "hp-bluetooth";
			अवरोध;
		हाल HPWMI_WWAN:
			type = RFKILL_TYPE_WWAN;
			name = "hp-wwan";
			अवरोध;
		हाल HPWMI_GPS:
			type = RFKILL_TYPE_GPS;
			name = "hp-gps";
			अवरोध;
		शेष:
			pr_warn("unknown device type 0x%x\n",
				state.device[i].radio_type);
			जारी;
		पूर्ण

		अगर (!state.device[i].venकरोr_id) अणु
			pr_warn("zero device %d while %d reported\n",
				i, state.count);
			जारी;
		पूर्ण

		rfसमाप्त = rfसमाप्त_alloc(name, &device->dev, type,
				      &hp_wmi_rfसमाप्त2_ops, (व्योम *)(दीर्घ)i);
		अगर (!rfसमाप्त) अणु
			err = -ENOMEM;
			जाओ fail;
		पूर्ण

		rfसमाप्त2[rfसमाप्त2_count].id = state.device[i].rfसमाप्त_id;
		rfसमाप्त2[rfसमाप्त2_count].num = i;
		rfसमाप्त2[rfसमाप्त2_count].rfसमाप्त = rfसमाप्त;

		rfसमाप्त_init_sw_state(rfसमाप्त,
				     IS_SWBLOCKED(state.device[i].घातer));
		rfसमाप्त_set_hw_state(rfसमाप्त,
				    IS_HWBLOCKED(state.device[i].घातer));

		अगर (!(state.device[i].घातer & HPWMI_POWER_BIOS))
			pr_info("device %s blocked by BIOS\n", name);

		err = rfसमाप्त_रेजिस्टर(rfसमाप्त);
		अगर (err) अणु
			rfसमाप्त_destroy(rfसमाप्त);
			जाओ fail;
		पूर्ण

		rfसमाप्त2_count++;
	पूर्ण

	वापस 0;
fail:
	क्रम (; rfसमाप्त2_count > 0; rfसमाप्त2_count--) अणु
		rfसमाप्त_unरेजिस्टर(rfसमाप्त2[rfसमाप्त2_count - 1].rfसमाप्त);
		rfसमाप्त_destroy(rfसमाप्त2[rfसमाप्त2_count - 1].rfसमाप्त);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक thermal_profile_get(व्योम)
अणु
	वापस hp_wmi_पढ़ो_पूर्णांक(HPWMI_THERMAL_PROखाता_QUERY);
पूर्ण

अटल पूर्णांक thermal_profile_set(पूर्णांक thermal_profile)
अणु
	वापस hp_wmi_perक्रमm_query(HPWMI_THERMAL_PROखाता_QUERY, HPWMI_WRITE, &thermal_profile,
							   माप(thermal_profile), 0);
पूर्ण

अटल पूर्णांक platक्रमm_profile_get(काष्ठा platक्रमm_profile_handler *pprof,
				क्रमागत platक्रमm_profile_option *profile)
अणु
	पूर्णांक tp;

	tp = thermal_profile_get();
	अगर (tp < 0)
		वापस tp;

	चयन (tp) अणु
	हाल HP_THERMAL_PROखाता_PERFORMANCE:
		*profile =  PLATFORM_PROखाता_PERFORMANCE;
		अवरोध;
	हाल HP_THERMAL_PROखाता_DEFAULT:
		*profile =  PLATFORM_PROखाता_BALANCED;
		अवरोध;
	हाल HP_THERMAL_PROखाता_COOL:
		*profile =  PLATFORM_PROखाता_COOL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक platक्रमm_profile_set(काष्ठा platक्रमm_profile_handler *pprof,
				क्रमागत platक्रमm_profile_option profile)
अणु
	पूर्णांक err, tp;

	चयन (profile) अणु
	हाल PLATFORM_PROखाता_PERFORMANCE:
		tp =  HP_THERMAL_PROखाता_PERFORMANCE;
		अवरोध;
	हाल PLATFORM_PROखाता_BALANCED:
		tp =  HP_THERMAL_PROखाता_DEFAULT;
		अवरोध;
	हाल PLATFORM_PROखाता_COOL:
		tp =  HP_THERMAL_PROखाता_COOL;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	err = thermal_profile_set(tp);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक thermal_profile_setup(व्योम)
अणु
	पूर्णांक err, tp;

	tp = thermal_profile_get();
	अगर (tp < 0)
		वापस tp;

	/*
	 * call thermal profile ग_लिखो command to ensure that the firmware correctly
	 * sets the OEM variables क्रम the DPTF
	 */
	err = thermal_profile_set(tp);
	अगर (err)
		वापस err;

	platक्रमm_profile_handler.profile_get = platक्रमm_profile_get,
	platक्रमm_profile_handler.profile_set = platक्रमm_profile_set,

	set_bit(PLATFORM_PROखाता_COOL, platक्रमm_profile_handler.choices);
	set_bit(PLATFORM_PROखाता_BALANCED, platक्रमm_profile_handler.choices);
	set_bit(PLATFORM_PROखाता_PERFORMANCE, platक्रमm_profile_handler.choices);

	err = platक्रमm_profile_रेजिस्टर(&platक्रमm_profile_handler);
	अगर (err)
		वापस err;

	platक्रमm_profile_support = true;

	वापस 0;
पूर्ण

अटल पूर्णांक __init hp_wmi_bios_setup(काष्ठा platक्रमm_device *device)
अणु
	/* clear detected rfसमाप्त devices */
	wअगरi_rfसमाप्त = शून्य;
	bluetooth_rfसमाप्त = शून्य;
	wwan_rfसमाप्त = शून्य;
	rfसमाप्त2_count = 0;

	अगर (hp_wmi_rfसमाप्त_setup(device))
		hp_wmi_rfसमाप्त2_setup(device);

	thermal_profile_setup();

	वापस 0;
पूर्ण

अटल पूर्णांक __निकास hp_wmi_bios_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rfसमाप्त2_count; i++) अणु
		rfसमाप्त_unरेजिस्टर(rfसमाप्त2[i].rfसमाप्त);
		rfसमाप्त_destroy(rfसमाप्त2[i].rfसमाप्त);
	पूर्ण

	अगर (wअगरi_rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(wअगरi_rfसमाप्त);
		rfसमाप्त_destroy(wअगरi_rfसमाप्त);
	पूर्ण
	अगर (bluetooth_rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(bluetooth_rfसमाप्त);
		rfसमाप्त_destroy(bluetooth_rfसमाप्त);
	पूर्ण
	अगर (wwan_rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(wwan_rfसमाप्त);
		rfसमाप्त_destroy(wwan_rfसमाप्त);
	पूर्ण

	अगर (platक्रमm_profile_support)
		platक्रमm_profile_हटाओ();

	वापस 0;
पूर्ण

अटल पूर्णांक hp_wmi_resume_handler(काष्ठा device *device)
अणु
	/*
	 * Hardware state may have changed जबतक suspended, so trigger
	 * input events क्रम the current state. As this is a चयन,
	 * the input layer will only actually pass it on अगर the state
	 * changed.
	 */
	अगर (hp_wmi_input_dev) अणु
		अगर (test_bit(SW_DOCK, hp_wmi_input_dev->swbit))
			input_report_चयन(hp_wmi_input_dev, SW_DOCK,
					    hp_wmi_hw_state(HPWMI_DOCK_MASK));
		अगर (test_bit(SW_TABLET_MODE, hp_wmi_input_dev->swbit))
			input_report_चयन(hp_wmi_input_dev, SW_TABLET_MODE,
					    hp_wmi_hw_state(HPWMI_TABLET_MASK));
		input_sync(hp_wmi_input_dev);
	पूर्ण

	अगर (rfसमाप्त2_count)
		hp_wmi_rfसमाप्त2_refresh();

	अगर (wअगरi_rfसमाप्त)
		rfसमाप्त_set_states(wअगरi_rfसमाप्त,
				  hp_wmi_get_sw_state(HPWMI_WIFI),
				  hp_wmi_get_hw_state(HPWMI_WIFI));
	अगर (bluetooth_rfसमाप्त)
		rfसमाप्त_set_states(bluetooth_rfसमाप्त,
				  hp_wmi_get_sw_state(HPWMI_BLUETOOTH),
				  hp_wmi_get_hw_state(HPWMI_BLUETOOTH));
	अगर (wwan_rfसमाप्त)
		rfसमाप्त_set_states(wwan_rfसमाप्त,
				  hp_wmi_get_sw_state(HPWMI_WWAN),
				  hp_wmi_get_hw_state(HPWMI_WWAN));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops hp_wmi_pm_ops = अणु
	.resume  = hp_wmi_resume_handler,
	.restore  = hp_wmi_resume_handler,
पूर्ण;

अटल काष्ठा platक्रमm_driver hp_wmi_driver = अणु
	.driver = अणु
		.name = "hp-wmi",
		.pm = &hp_wmi_pm_ops,
		.dev_groups = hp_wmi_groups,
	पूर्ण,
	.हटाओ = __निकास_p(hp_wmi_bios_हटाओ),
पूर्ण;

अटल पूर्णांक __init hp_wmi_init(व्योम)
अणु
	पूर्णांक event_capable = wmi_has_guid(HPWMI_EVENT_GUID);
	पूर्णांक bios_capable = wmi_has_guid(HPWMI_BIOS_GUID);
	पूर्णांक err;

	अगर (!bios_capable && !event_capable)
		वापस -ENODEV;

	अगर (event_capable) अणु
		err = hp_wmi_input_setup();
		अगर (err)
			वापस err;
	पूर्ण

	अगर (bios_capable) अणु
		hp_wmi_platक्रमm_dev =
			platक्रमm_device_रेजिस्टर_simple("hp-wmi", -1, शून्य, 0);
		अगर (IS_ERR(hp_wmi_platक्रमm_dev)) अणु
			err = PTR_ERR(hp_wmi_platक्रमm_dev);
			जाओ err_destroy_input;
		पूर्ण

		err = platक्रमm_driver_probe(&hp_wmi_driver, hp_wmi_bios_setup);
		अगर (err)
			जाओ err_unरेजिस्टर_device;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_device:
	platक्रमm_device_unरेजिस्टर(hp_wmi_platक्रमm_dev);
err_destroy_input:
	अगर (event_capable)
		hp_wmi_input_destroy();

	वापस err;
पूर्ण
module_init(hp_wmi_init);

अटल व्योम __निकास hp_wmi_निकास(व्योम)
अणु
	अगर (wmi_has_guid(HPWMI_EVENT_GUID))
		hp_wmi_input_destroy();

	अगर (hp_wmi_platक्रमm_dev) अणु
		platक्रमm_device_unरेजिस्टर(hp_wmi_platक्रमm_dev);
		platक्रमm_driver_unरेजिस्टर(&hp_wmi_driver);
	पूर्ण
पूर्ण
module_निकास(hp_wmi_निकास);
