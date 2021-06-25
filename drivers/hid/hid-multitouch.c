<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम multitouch panels
 *
 *  Copyright (c) 2010-2012 Stephane Chatty <chatty@enac.fr>
 *  Copyright (c) 2010-2013 Benjamin Tissoires <benjamin.tissoires@gmail.com>
 *  Copyright (c) 2010-2012 Ecole Nationale de l'Aviation Civile, France
 *  Copyright (c) 2012-2013 Red Hat, Inc
 *
 *  This code is partly based on hid-egalax.c:
 *
 *  Copyright (c) 2010 Stephane Chatty <chatty@enac.fr>
 *  Copyright (c) 2010 Henrik Rydberg <rydberg@euromail.se>
 *  Copyright (c) 2010 Canonical, Ltd.
 *
 *  This code is partly based on hid-3m-pct.c:
 *
 *  Copyright (c) 2009-2010 Stephane Chatty <chatty@enac.fr>
 *  Copyright (c) 2010      Henrik Rydberg <rydberg@euromail.se>
 *  Copyright (c) 2010      Canonical, Ltd.
 */

/*
 */

/*
 * This driver is regularly tested thanks to the test suite in hid-tools[1].
 * Please run these regression tests beक्रमe patching this module so that
 * your patch won't अवरोध existing known devices.
 *
 * [1] https://gitlab.मुक्तdesktop.org/libevdev/hid-tools
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>


MODULE_AUTHOR("Stephane Chatty <chatty@enac.fr>");
MODULE_AUTHOR("Benjamin Tissoires <benjamin.tissoires@gmail.com>");
MODULE_DESCRIPTION("HID multitouch panels");
MODULE_LICENSE("GPL");

#समावेश "hid-ids.h"

/* quirks to control the device */
#घोषणा MT_QUIRK_NOT_SEEN_MEANS_UP	BIT(0)
#घोषणा MT_QUIRK_SLOT_IS_CONTACTID	BIT(1)
#घोषणा MT_QUIRK_CYPRESS		BIT(2)
#घोषणा MT_QUIRK_SLOT_IS_CONTACTNUMBER	BIT(3)
#घोषणा MT_QUIRK_ALWAYS_VALID		BIT(4)
#घोषणा MT_QUIRK_VALID_IS_INRANGE	BIT(5)
#घोषणा MT_QUIRK_VALID_IS_CONFIDENCE	BIT(6)
#घोषणा MT_QUIRK_CONFIDENCE		BIT(7)
#घोषणा MT_QUIRK_SLOT_IS_CONTACTID_MINUS_ONE	BIT(8)
#घोषणा MT_QUIRK_NO_AREA		BIT(9)
#घोषणा MT_QUIRK_IGNORE_DUPLICATES	BIT(10)
#घोषणा MT_QUIRK_HOVERING		BIT(11)
#घोषणा MT_QUIRK_CONTACT_CNT_ACCURATE	BIT(12)
#घोषणा MT_QUIRK_FORCE_GET_FEATURE	BIT(13)
#घोषणा MT_QUIRK_FIX_CONST_CONTACT_ID	BIT(14)
#घोषणा MT_QUIRK_TOUCH_SIZE_SCALING	BIT(15)
#घोषणा MT_QUIRK_STICKY_FINGERS		BIT(16)
#घोषणा MT_QUIRK_ASUS_CUSTOM_UP		BIT(17)
#घोषणा MT_QUIRK_WIN8_PTP_BUTTONS	BIT(18)
#घोषणा MT_QUIRK_SEPARATE_APP_REPORT	BIT(19)
#घोषणा MT_QUIRK_FORCE_MULTI_INPUT	BIT(20)
#घोषणा MT_QUIRK_DISABLE_WAKEUP		BIT(21)

#घोषणा MT_INPUTMODE_TOUCHSCREEN	0x02
#घोषणा MT_INPUTMODE_TOUCHPAD		0x03

#घोषणा MT_BUTTONTYPE_CLICKPAD		0

क्रमागत latency_mode अणु
	HID_LATENCY_NORMAL = 0,
	HID_LATENCY_HIGH = 1,
पूर्ण;

#घोषणा MT_IO_FLAGS_RUNNING		0
#घोषणा MT_IO_FLAGS_ACTIVE_SLOTS	1
#घोषणा MT_IO_FLAGS_PENDING_SLOTS	2

अटल स्थिर bool mtrue = true;		/* शेष क्रम true */
अटल स्थिर bool mfalse;		/* शेष क्रम false */
अटल स्थिर __s32 mzero;		/* शेष क्रम 0 */

#घोषणा DEFAULT_TRUE	((व्योम *)&mtrue)
#घोषणा DEFAULT_FALSE	((व्योम *)&mfalse)
#घोषणा DEFAULT_ZERO	((व्योम *)&mzero)

काष्ठा mt_usages अणु
	काष्ठा list_head list;
	__s32 *x, *y, *cx, *cy, *p, *w, *h, *a;
	__s32 *contactid;	/* the device ContactID asचिन्हित to this slot */
	bool *tip_state;	/* is the touch valid? */
	bool *inrange_state;	/* is the finger in proximity of the sensor? */
	bool *confidence_state;	/* is the touch made by a finger? */
पूर्ण;

काष्ठा mt_application अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक application;
	अचिन्हित पूर्णांक report_id;
	काष्ठा list_head mt_usages;	/* mt usages list */

	__s32 quirks;

	__s32 *scanसमय;		/* scanसमय reported */
	__s32 scanसमय_logical_max;	/* max value क्रम raw scanसमय */

	__s32 *raw_cc;			/* contact count in the report */
	पूर्णांक left_button_state;		/* left button state */
	अचिन्हित पूर्णांक mt_flags;		/* flags to pass to input-mt */

	अचिन्हित दीर्घ *pending_palm_slots;	/* slots where we reported palm
						 * and need to release */

	__u8 num_received;	/* how many contacts we received */
	__u8 num_expected;	/* expected last contact index */
	__u8 buttons_count;	/* number of physical buttons per touchpad */
	__u8 touches_by_report;	/* how many touches are present in one report:
				 * 1 means we should use a serial protocol
				 * > 1 means hybrid (multitouch) protocol
				 */

	__s32 dev_समय;		/* the scan समय provided by the device */
	अचिन्हित दीर्घ jअगरfies;	/* the frame's jअगरfies */
	पूर्णांक बारtamp;		/* the बारtamp to be sent */
	पूर्णांक prev_scanसमय;		/* scanसमय reported previously */

	bool have_contact_count;
पूर्ण;

काष्ठा mt_class अणु
	__s32 name;	/* MT_CLS */
	__s32 quirks;
	__s32 sn_move;	/* Signal/noise ratio क्रम move events */
	__s32 sn_width;	/* Signal/noise ratio क्रम width events */
	__s32 sn_height;	/* Signal/noise ratio क्रम height events */
	__s32 sn_pressure;	/* Signal/noise ratio क्रम pressure events */
	__u8 maxcontacts;
	bool is_indirect;	/* true क्रम touchpads */
	bool export_all_inमाला_दो;	/* करो not ignore mouse, keyboards, etc... */
पूर्ण;

काष्ठा mt_report_data अणु
	काष्ठा list_head list;
	काष्ठा hid_report *report;
	काष्ठा mt_application *application;
	bool is_mt_collection;
पूर्ण;

काष्ठा mt_device अणु
	काष्ठा mt_class mtclass;	/* our mt device class */
	काष्ठा समयr_list release_समयr;	/* to release sticky fingers */
	काष्ठा hid_device *hdev;	/* hid_device we're attached to */
	अचिन्हित दीर्घ mt_io_flags;	/* mt flags (MT_IO_FLAGS_*) */
	__u8 inpuपंचांगode_value;	/* InputMode HID feature value */
	__u8 maxcontacts;
	bool is_buttonpad;	/* is this device a button pad? */
	bool serial_maybe;	/* need to check क्रम serial protocol */

	काष्ठा list_head applications;
	काष्ठा list_head reports;
पूर्ण;

अटल व्योम mt_post_parse_शेष_settings(काष्ठा mt_device *td,
					   काष्ठा mt_application *app);
अटल व्योम mt_post_parse(काष्ठा mt_device *td, काष्ठा mt_application *app);

/* classes of device behavior */
#घोषणा MT_CLS_DEFAULT				0x0001

#घोषणा MT_CLS_SERIAL				0x0002
#घोषणा MT_CLS_CONFIDENCE			0x0003
#घोषणा MT_CLS_CONFIDENCE_CONTACT_ID		0x0004
#घोषणा MT_CLS_CONFIDENCE_MINUS_ONE		0x0005
#घोषणा MT_CLS_DUAL_INRANGE_CONTACTID		0x0006
#घोषणा MT_CLS_DUAL_INRANGE_CONTACTNUMBER	0x0007
/* reserved					0x0008 */
#घोषणा MT_CLS_INRANGE_CONTACTNUMBER		0x0009
#घोषणा MT_CLS_NSMU				0x000a
/* reserved					0x0010 */
/* reserved					0x0011 */
#घोषणा MT_CLS_WIN_8				0x0012
#घोषणा MT_CLS_EXPORT_ALL_INPUTS		0x0013
/* reserved					0x0014 */
#घोषणा MT_CLS_WIN_8_FORCE_MULTI_INPUT		0x0015
#घोषणा MT_CLS_WIN_8_DISABLE_WAKEUP		0x0016

/* venकरोr specअगरic classes */
#घोषणा MT_CLS_3M				0x0101
/* reserved					0x0102 */
#घोषणा MT_CLS_EGALAX				0x0103
#घोषणा MT_CLS_EGALAX_SERIAL			0x0104
#घोषणा MT_CLS_TOPSEED				0x0105
#घोषणा MT_CLS_PANASONIC			0x0106
#घोषणा MT_CLS_FLATFROG				0x0107
#घोषणा MT_CLS_GENERALTOUCH_TWOFINGERS		0x0108
#घोषणा MT_CLS_GENERALTOUCH_PWT_TENFINGERS	0x0109
#घोषणा MT_CLS_LG				0x010a
#घोषणा MT_CLS_ASUS				0x010b
#घोषणा MT_CLS_VTL				0x0110
#घोषणा MT_CLS_GOOGLE				0x0111
#घोषणा MT_CLS_RAZER_BLADE_STEALTH		0x0112
#घोषणा MT_CLS_SMART_TECH			0x0113

#घोषणा MT_DEFAULT_MAXCONTACT	10
#घोषणा MT_MAX_MAXCONTACT	250

/*
 * Resync device and local बारtamps after that many microseconds without
 * receiving data.
 */
#घोषणा MAX_TIMESTAMP_INTERVAL	1000000

#घोषणा MT_USB_DEVICE(v, p)	HID_DEVICE(BUS_USB, HID_GROUP_MULTITOUCH, v, p)
#घोषणा MT_BT_DEVICE(v, p)	HID_DEVICE(BUS_BLUETOOTH, HID_GROUP_MULTITOUCH, v, p)

/*
 * these device-dependent functions determine what slot corresponds
 * to a valid contact that was just पढ़ो.
 */

अटल पूर्णांक cypress_compute_slot(काष्ठा mt_application *application,
				काष्ठा mt_usages *slot)
अणु
	अगर (*slot->contactid != 0 || application->num_received == 0)
		वापस *slot->contactid;
	अन्यथा
		वापस -1;
पूर्ण

अटल स्थिर काष्ठा mt_class mt_classes[] = अणु
	अणु .name = MT_CLS_DEFAULT,
		.quirks = MT_QUIRK_ALWAYS_VALID |
			MT_QUIRK_CONTACT_CNT_ACCURATE पूर्ण,
	अणु .name = MT_CLS_NSMU,
		.quirks = MT_QUIRK_NOT_SEEN_MEANS_UP पूर्ण,
	अणु .name = MT_CLS_SERIAL,
		.quirks = MT_QUIRK_ALWAYS_VALIDपूर्ण,
	अणु .name = MT_CLS_CONFIDENCE,
		.quirks = MT_QUIRK_VALID_IS_CONFIDENCE पूर्ण,
	अणु .name = MT_CLS_CONFIDENCE_CONTACT_ID,
		.quirks = MT_QUIRK_VALID_IS_CONFIDENCE |
			MT_QUIRK_SLOT_IS_CONTACTID पूर्ण,
	अणु .name = MT_CLS_CONFIDENCE_MINUS_ONE,
		.quirks = MT_QUIRK_VALID_IS_CONFIDENCE |
			MT_QUIRK_SLOT_IS_CONTACTID_MINUS_ONE पूर्ण,
	अणु .name = MT_CLS_DUAL_INRANGE_CONTACTID,
		.quirks = MT_QUIRK_VALID_IS_INRANGE |
			MT_QUIRK_SLOT_IS_CONTACTID,
		.maxcontacts = 2 पूर्ण,
	अणु .name = MT_CLS_DUAL_INRANGE_CONTACTNUMBER,
		.quirks = MT_QUIRK_VALID_IS_INRANGE |
			MT_QUIRK_SLOT_IS_CONTACTNUMBER,
		.maxcontacts = 2 पूर्ण,
	अणु .name = MT_CLS_INRANGE_CONTACTNUMBER,
		.quirks = MT_QUIRK_VALID_IS_INRANGE |
			MT_QUIRK_SLOT_IS_CONTACTNUMBER पूर्ण,
	अणु .name = MT_CLS_WIN_8,
		.quirks = MT_QUIRK_ALWAYS_VALID |
			MT_QUIRK_IGNORE_DUPLICATES |
			MT_QUIRK_HOVERING |
			MT_QUIRK_CONTACT_CNT_ACCURATE |
			MT_QUIRK_STICKY_FINGERS |
			MT_QUIRK_WIN8_PTP_BUTTONS,
		.export_all_inमाला_दो = true पूर्ण,
	अणु .name = MT_CLS_EXPORT_ALL_INPUTS,
		.quirks = MT_QUIRK_ALWAYS_VALID |
			MT_QUIRK_CONTACT_CNT_ACCURATE,
		.export_all_inमाला_दो = true पूर्ण,
	अणु .name = MT_CLS_WIN_8_FORCE_MULTI_INPUT,
		.quirks = MT_QUIRK_ALWAYS_VALID |
			MT_QUIRK_IGNORE_DUPLICATES |
			MT_QUIRK_HOVERING |
			MT_QUIRK_CONTACT_CNT_ACCURATE |
			MT_QUIRK_STICKY_FINGERS |
			MT_QUIRK_WIN8_PTP_BUTTONS |
			MT_QUIRK_FORCE_MULTI_INPUT,
		.export_all_inमाला_दो = true पूर्ण,
	अणु .name = MT_CLS_WIN_8_DISABLE_WAKEUP,
		.quirks = MT_QUIRK_ALWAYS_VALID |
			MT_QUIRK_IGNORE_DUPLICATES |
			MT_QUIRK_HOVERING |
			MT_QUIRK_CONTACT_CNT_ACCURATE |
			MT_QUIRK_STICKY_FINGERS |
			MT_QUIRK_WIN8_PTP_BUTTONS |
			MT_QUIRK_DISABLE_WAKEUP,
		.export_all_inमाला_दो = true पूर्ण,

	/*
	 * venकरोr specअगरic classes
	 */
	अणु .name = MT_CLS_3M,
		.quirks = MT_QUIRK_VALID_IS_CONFIDENCE |
			MT_QUIRK_SLOT_IS_CONTACTID |
			MT_QUIRK_TOUCH_SIZE_SCALING,
		.sn_move = 2048,
		.sn_width = 128,
		.sn_height = 128,
		.maxcontacts = 60,
	पूर्ण,
	अणु .name = MT_CLS_EGALAX,
		.quirks =  MT_QUIRK_SLOT_IS_CONTACTID |
			MT_QUIRK_VALID_IS_INRANGE,
		.sn_move = 4096,
		.sn_pressure = 32,
	पूर्ण,
	अणु .name = MT_CLS_EGALAX_SERIAL,
		.quirks =  MT_QUIRK_SLOT_IS_CONTACTID |
			MT_QUIRK_ALWAYS_VALID,
		.sn_move = 4096,
		.sn_pressure = 32,
	पूर्ण,
	अणु .name = MT_CLS_TOPSEED,
		.quirks = MT_QUIRK_ALWAYS_VALID,
		.is_indirect = true,
		.maxcontacts = 2,
	पूर्ण,
	अणु .name = MT_CLS_PANASONIC,
		.quirks = MT_QUIRK_NOT_SEEN_MEANS_UP,
		.maxcontacts = 4 पूर्ण,
	अणु .name	= MT_CLS_GENERALTOUCH_TWOFINGERS,
		.quirks	= MT_QUIRK_NOT_SEEN_MEANS_UP |
			MT_QUIRK_VALID_IS_INRANGE |
			MT_QUIRK_SLOT_IS_CONTACTID,
		.maxcontacts = 2
	पूर्ण,
	अणु .name	= MT_CLS_GENERALTOUCH_PWT_TENFINGERS,
		.quirks	= MT_QUIRK_NOT_SEEN_MEANS_UP |
			MT_QUIRK_SLOT_IS_CONTACTID
	पूर्ण,

	अणु .name = MT_CLS_FLATFROG,
		.quirks = MT_QUIRK_NOT_SEEN_MEANS_UP |
			MT_QUIRK_NO_AREA,
		.sn_move = 2048,
		.maxcontacts = 40,
	पूर्ण,
	अणु .name = MT_CLS_LG,
		.quirks = MT_QUIRK_ALWAYS_VALID |
			MT_QUIRK_FIX_CONST_CONTACT_ID |
			MT_QUIRK_IGNORE_DUPLICATES |
			MT_QUIRK_HOVERING |
			MT_QUIRK_CONTACT_CNT_ACCURATE पूर्ण,
	अणु .name = MT_CLS_ASUS,
		.quirks = MT_QUIRK_ALWAYS_VALID |
			MT_QUIRK_CONTACT_CNT_ACCURATE |
			MT_QUIRK_ASUS_CUSTOM_UP पूर्ण,
	अणु .name = MT_CLS_VTL,
		.quirks = MT_QUIRK_ALWAYS_VALID |
			MT_QUIRK_CONTACT_CNT_ACCURATE |
			MT_QUIRK_FORCE_GET_FEATURE,
	पूर्ण,
	अणु .name = MT_CLS_GOOGLE,
		.quirks = MT_QUIRK_ALWAYS_VALID |
			MT_QUIRK_CONTACT_CNT_ACCURATE |
			MT_QUIRK_SLOT_IS_CONTACTID |
			MT_QUIRK_HOVERING
	पूर्ण,
	अणु .name = MT_CLS_RAZER_BLADE_STEALTH,
		.quirks = MT_QUIRK_ALWAYS_VALID |
			MT_QUIRK_IGNORE_DUPLICATES |
			MT_QUIRK_HOVERING |
			MT_QUIRK_CONTACT_CNT_ACCURATE |
			MT_QUIRK_WIN8_PTP_BUTTONS,
	पूर्ण,
	अणु .name = MT_CLS_SMART_TECH,
		.quirks = MT_QUIRK_ALWAYS_VALID |
			MT_QUIRK_IGNORE_DUPLICATES |
			MT_QUIRK_CONTACT_CNT_ACCURATE |
			MT_QUIRK_SEPARATE_APP_REPORT,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल sमाप_प्रकार mt_show_quirks(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा mt_device *td = hid_get_drvdata(hdev);

	वापस प्र_लिखो(buf, "%u\n", td->mtclass.quirks);
पूर्ण

अटल sमाप_प्रकार mt_set_quirks(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा mt_device *td = hid_get_drvdata(hdev);
	काष्ठा mt_application *application;

	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	td->mtclass.quirks = val;

	list_क्रम_each_entry(application, &td->applications, list) अणु
		application->quirks = val;
		अगर (!application->have_contact_count)
			application->quirks &= ~MT_QUIRK_CONTACT_CNT_ACCURATE;
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR(quirks, S_IWUSR | S_IRUGO, mt_show_quirks, mt_set_quirks);

अटल काष्ठा attribute *sysfs_attrs[] = अणु
	&dev_attr_quirks.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group mt_attribute_group = अणु
	.attrs = sysfs_attrs
पूर्ण;

अटल व्योम mt_get_feature(काष्ठा hid_device *hdev, काष्ठा hid_report *report)
अणु
	पूर्णांक ret;
	u32 size = hid_report_len(report);
	u8 *buf;

	/*
	 * Do not fetch the feature report अगर the device has been explicitly
	 * marked as non-capable.
	 */
	अगर (hdev->quirks & HID_QUIRK_NO_INIT_REPORTS)
		वापस;

	buf = hid_alloc_report_buf(report, GFP_KERNEL);
	अगर (!buf)
		वापस;

	ret = hid_hw_raw_request(hdev, report->id, buf, size,
				 HID_FEATURE_REPORT, HID_REQ_GET_REPORT);
	अगर (ret < 0) अणु
		dev_warn(&hdev->dev, "failed to fetch feature %d\n",
			 report->id);
	पूर्ण अन्यथा अणु
		ret = hid_report_raw_event(hdev, HID_FEATURE_REPORT, buf,
					   size, 0);
		अगर (ret)
			dev_warn(&hdev->dev, "failed to report feature\n");
	पूर्ण

	kमुक्त(buf);
पूर्ण

अटल व्योम mt_feature_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage)
अणु
	काष्ठा mt_device *td = hid_get_drvdata(hdev);

	चयन (usage->hid) अणु
	हाल HID_DG_CONTACTMAX:
		mt_get_feature(hdev, field->report);

		td->maxcontacts = field->value[0];
		अगर (!td->maxcontacts &&
		    field->logical_maximum <= MT_MAX_MAXCONTACT)
			td->maxcontacts = field->logical_maximum;
		अगर (td->mtclass.maxcontacts)
			/* check अगर the maxcontacts is given by the class */
			td->maxcontacts = td->mtclass.maxcontacts;

		अवरोध;
	हाल HID_DG_BUTTONTYPE:
		अगर (usage->usage_index >= field->report_count) अणु
			dev_err(&hdev->dev, "HID_DG_BUTTONTYPE out of range\n");
			अवरोध;
		पूर्ण

		mt_get_feature(hdev, field->report);
		अगर (field->value[usage->usage_index] == MT_BUTTONTYPE_CLICKPAD)
			td->is_buttonpad = true;

		अवरोध;
	हाल 0xff0000c5:
		/* Retrieve the Win8 blob once to enable some devices */
		अगर (usage->usage_index == 0)
			mt_get_feature(hdev, field->report);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम set_असल(काष्ठा input_dev *input, अचिन्हित पूर्णांक code,
		काष्ठा hid_field *field, पूर्णांक snratio)
अणु
	पूर्णांक fmin = field->logical_minimum;
	पूर्णांक fmax = field->logical_maximum;
	पूर्णांक fuzz = snratio ? (fmax - fmin) / snratio : 0;
	input_set_असल_params(input, code, fmin, fmax, fuzz, 0);
	input_असल_set_res(input, code, hidinput_calc_असल_res(field, code));
पूर्ण

अटल काष्ठा mt_usages *mt_allocate_usage(काष्ठा hid_device *hdev,
					   काष्ठा mt_application *application)
अणु
	काष्ठा mt_usages *usage;

	usage = devm_kzalloc(&hdev->dev, माप(*usage), GFP_KERNEL);
	अगर (!usage)
		वापस शून्य;

	/* set some शेषs so we करो not need to check क्रम null poपूर्णांकers */
	usage->x = DEFAULT_ZERO;
	usage->y = DEFAULT_ZERO;
	usage->cx = DEFAULT_ZERO;
	usage->cy = DEFAULT_ZERO;
	usage->p = DEFAULT_ZERO;
	usage->w = DEFAULT_ZERO;
	usage->h = DEFAULT_ZERO;
	usage->a = DEFAULT_ZERO;
	usage->contactid = DEFAULT_ZERO;
	usage->tip_state = DEFAULT_FALSE;
	usage->inrange_state = DEFAULT_FALSE;
	usage->confidence_state = DEFAULT_TRUE;

	list_add_tail(&usage->list, &application->mt_usages);

	वापस usage;
पूर्ण

अटल काष्ठा mt_application *mt_allocate_application(काष्ठा mt_device *td,
						      काष्ठा hid_report *report)
अणु
	अचिन्हित पूर्णांक application = report->application;
	काष्ठा mt_application *mt_application;

	mt_application = devm_kzalloc(&td->hdev->dev, माप(*mt_application),
				      GFP_KERNEL);
	अगर (!mt_application)
		वापस शून्य;

	mt_application->application = application;
	INIT_LIST_HEAD(&mt_application->mt_usages);

	अगर (application == HID_DG_TOUCHSCREEN)
		mt_application->mt_flags |= INPUT_MT_सूचीECT;

	/*
	 * Model touchscreens providing buttons as touchpads.
	 */
	अगर (application == HID_DG_TOUCHPAD) अणु
		mt_application->mt_flags |= INPUT_MT_POINTER;
		td->inpuपंचांगode_value = MT_INPUTMODE_TOUCHPAD;
	पूर्ण

	mt_application->scanसमय = DEFAULT_ZERO;
	mt_application->raw_cc = DEFAULT_ZERO;
	mt_application->quirks = td->mtclass.quirks;
	mt_application->report_id = report->id;

	list_add_tail(&mt_application->list, &td->applications);

	वापस mt_application;
पूर्ण

अटल काष्ठा mt_application *mt_find_application(काष्ठा mt_device *td,
						  काष्ठा hid_report *report)
अणु
	अचिन्हित पूर्णांक application = report->application;
	काष्ठा mt_application *पंचांगp, *mt_application = शून्य;

	list_क्रम_each_entry(पंचांगp, &td->applications, list) अणु
		अगर (application == पंचांगp->application) अणु
			अगर (!(td->mtclass.quirks & MT_QUIRK_SEPARATE_APP_REPORT) ||
			    पंचांगp->report_id == report->id) अणु
				mt_application = पंचांगp;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!mt_application)
		mt_application = mt_allocate_application(td, report);

	वापस mt_application;
पूर्ण

अटल काष्ठा mt_report_data *mt_allocate_report_data(काष्ठा mt_device *td,
						      काष्ठा hid_report *report)
अणु
	काष्ठा mt_report_data *rdata;
	काष्ठा hid_field *field;
	पूर्णांक r, n;

	rdata = devm_kzalloc(&td->hdev->dev, माप(*rdata), GFP_KERNEL);
	अगर (!rdata)
		वापस शून्य;

	rdata->report = report;
	rdata->application = mt_find_application(td, report);

	अगर (!rdata->application) अणु
		devm_kमुक्त(&td->hdev->dev, rdata);
		वापस शून्य;
	पूर्ण

	क्रम (r = 0; r < report->maxfield; r++) अणु
		field = report->field[r];

		अगर (!(HID_MAIN_ITEM_VARIABLE & field->flags))
			जारी;

		अगर (field->logical == HID_DG_FINGER || td->hdev->group != HID_GROUP_MULTITOUCH_WIN_8) अणु
			क्रम (n = 0; n < field->report_count; n++) अणु
				अगर (field->usage[n].hid == HID_DG_CONTACTID) अणु
					rdata->is_mt_collection = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	list_add_tail(&rdata->list, &td->reports);

	वापस rdata;
पूर्ण

अटल काष्ठा mt_report_data *mt_find_report_data(काष्ठा mt_device *td,
						  काष्ठा hid_report *report)
अणु
	काष्ठा mt_report_data *पंचांगp, *rdata = शून्य;

	list_क्रम_each_entry(पंचांगp, &td->reports, list) अणु
		अगर (report == पंचांगp->report) अणु
			rdata = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!rdata)
		rdata = mt_allocate_report_data(td, report);

	वापस rdata;
पूर्ण

अटल व्योम mt_store_field(काष्ठा hid_device *hdev,
			   काष्ठा mt_application *application,
			   __s32 *value,
			   माप_प्रकार offset)
अणु
	काष्ठा mt_usages *usage;
	__s32 **target;

	अगर (list_empty(&application->mt_usages))
		usage = mt_allocate_usage(hdev, application);
	अन्यथा
		usage = list_last_entry(&application->mt_usages,
					काष्ठा mt_usages,
					list);

	अगर (!usage)
		वापस;

	target = (__s32 **)((अक्षर *)usage + offset);

	/* the value has alपढ़ोy been filled, create a new slot */
	अगर (*target != DEFAULT_TRUE &&
	    *target != DEFAULT_FALSE &&
	    *target != DEFAULT_ZERO) अणु
		अगर (usage->contactid == DEFAULT_ZERO ||
		    usage->x == DEFAULT_ZERO ||
		    usage->y == DEFAULT_ZERO) अणु
			hid_dbg(hdev,
				"ignoring duplicate usage on incomplete");
			वापस;
		पूर्ण
		usage = mt_allocate_usage(hdev, application);
		अगर (!usage)
			वापस;

		target = (__s32 **)((अक्षर *)usage + offset);
	पूर्ण

	*target = value;
पूर्ण

#घोषणा MT_STORE_FIELD(__name)						\
	mt_store_field(hdev, app,					\
		       &field->value[usage->usage_index],		\
		       दुरत्व(काष्ठा mt_usages, __name))

अटल पूर्णांक mt_touch_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max, काष्ठा mt_application *app)
अणु
	काष्ठा mt_device *td = hid_get_drvdata(hdev);
	काष्ठा mt_class *cls = &td->mtclass;
	पूर्णांक code;
	काष्ठा hid_usage *prev_usage = शून्य;

	/*
	 * Model touchscreens providing buttons as touchpads.
	 */
	अगर (field->application == HID_DG_TOUCHSCREEN &&
	    (usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON) अणु
		app->mt_flags |= INPUT_MT_POINTER;
		td->inpuपंचांगode_value = MT_INPUTMODE_TOUCHPAD;
	पूर्ण

	/* count the buttons on touchpads */
	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON)
		app->buttons_count++;

	अगर (usage->usage_index)
		prev_usage = &field->usage[usage->usage_index - 1];

	चयन (usage->hid & HID_USAGE_PAGE) अणु

	हाल HID_UP_GENDESK:
		चयन (usage->hid) अणु
		हाल HID_GD_X:
			अगर (prev_usage && (prev_usage->hid == usage->hid)) अणु
				code = ABS_MT_TOOL_X;
				MT_STORE_FIELD(cx);
			पूर्ण अन्यथा अणु
				code = ABS_MT_POSITION_X;
				MT_STORE_FIELD(x);
			पूर्ण

			set_असल(hi->input, code, field, cls->sn_move);

			/*
			 * A प्रणाली multi-axis that exports X and Y has a high
			 * chance of being used directly on a surface
			 */
			अगर (field->application == HID_GD_SYSTEM_MULTIAXIS) अणु
				__set_bit(INPUT_PROP_सूचीECT,
					  hi->input->propbit);
				input_set_असल_params(hi->input,
						     ABS_MT_TOOL_TYPE,
						     MT_TOOL_DIAL,
						     MT_TOOL_DIAL, 0, 0);
			पूर्ण

			वापस 1;
		हाल HID_GD_Y:
			अगर (prev_usage && (prev_usage->hid == usage->hid)) अणु
				code = ABS_MT_TOOL_Y;
				MT_STORE_FIELD(cy);
			पूर्ण अन्यथा अणु
				code = ABS_MT_POSITION_Y;
				MT_STORE_FIELD(y);
			पूर्ण

			set_असल(hi->input, code, field, cls->sn_move);

			वापस 1;
		पूर्ण
		वापस 0;

	हाल HID_UP_DIGITIZER:
		चयन (usage->hid) अणु
		हाल HID_DG_INRANGE:
			अगर (app->quirks & MT_QUIRK_HOVERING) अणु
				input_set_असल_params(hi->input,
					ABS_MT_DISTANCE, 0, 1, 0, 0);
			पूर्ण
			MT_STORE_FIELD(inrange_state);
			वापस 1;
		हाल HID_DG_CONFIDENCE:
			अगर ((cls->name == MT_CLS_WIN_8 ||
			     cls->name == MT_CLS_WIN_8_FORCE_MULTI_INPUT ||
			     cls->name == MT_CLS_WIN_8_DISABLE_WAKEUP) &&
				(field->application == HID_DG_TOUCHPAD ||
				 field->application == HID_DG_TOUCHSCREEN))
				app->quirks |= MT_QUIRK_CONFIDENCE;

			अगर (app->quirks & MT_QUIRK_CONFIDENCE)
				input_set_असल_params(hi->input,
						     ABS_MT_TOOL_TYPE,
						     MT_TOOL_FINGER,
						     MT_TOOL_PALM, 0, 0);

			MT_STORE_FIELD(confidence_state);
			वापस 1;
		हाल HID_DG_TIPSWITCH:
			अगर (field->application != HID_GD_SYSTEM_MULTIAXIS)
				input_set_capability(hi->input,
						     EV_KEY, BTN_TOUCH);
			MT_STORE_FIELD(tip_state);
			वापस 1;
		हाल HID_DG_CONTACTID:
			MT_STORE_FIELD(contactid);
			app->touches_by_report++;
			वापस 1;
		हाल HID_DG_WIDTH:
			अगर (!(app->quirks & MT_QUIRK_NO_AREA))
				set_असल(hi->input, ABS_MT_TOUCH_MAJOR, field,
					cls->sn_width);
			MT_STORE_FIELD(w);
			वापस 1;
		हाल HID_DG_HEIGHT:
			अगर (!(app->quirks & MT_QUIRK_NO_AREA)) अणु
				set_असल(hi->input, ABS_MT_TOUCH_MINOR, field,
					cls->sn_height);

				/*
				 * Only set ABS_MT_ORIENTATION अगर it is not
				 * alपढ़ोy set by the HID_DG_AZIMUTH usage.
				 */
				अगर (!test_bit(ABS_MT_ORIENTATION,
						hi->input->असलbit))
					input_set_असल_params(hi->input,
						ABS_MT_ORIENTATION, 0, 1, 0, 0);
			पूर्ण
			MT_STORE_FIELD(h);
			वापस 1;
		हाल HID_DG_TIPPRESSURE:
			set_असल(hi->input, ABS_MT_PRESSURE, field,
				cls->sn_pressure);
			MT_STORE_FIELD(p);
			वापस 1;
		हाल HID_DG_SCANTIME:
			input_set_capability(hi->input, EV_MSC, MSC_TIMESTAMP);
			app->scanसमय = &field->value[usage->usage_index];
			app->scanसमय_logical_max = field->logical_maximum;
			वापस 1;
		हाल HID_DG_CONTACTCOUNT:
			app->have_contact_count = true;
			app->raw_cc = &field->value[usage->usage_index];
			वापस 1;
		हाल HID_DG_AZIMUTH:
			/*
			 * Azimuth has the range of [0, MAX) representing a full
			 * revolution. Set ABS_MT_ORIENTATION to a quarter of
			 * MAX according the definition of ABS_MT_ORIENTATION
			 */
			input_set_असल_params(hi->input, ABS_MT_ORIENTATION,
				-field->logical_maximum / 4,
				field->logical_maximum / 4,
				cls->sn_move ?
				field->logical_maximum / cls->sn_move : 0, 0);
			MT_STORE_FIELD(a);
			वापस 1;
		हाल HID_DG_CONTACTMAX:
			/* contact max are global to the report */
			वापस -1;
		हाल HID_DG_TOUCH:
			/* Legacy devices use TIPSWITCH and not TOUCH.
			 * Let's just ignore this field. */
			वापस -1;
		पूर्ण
		/* let hid-input decide क्रम the others */
		वापस 0;

	हाल HID_UP_BUTTON:
		code = BTN_MOUSE + ((usage->hid - 1) & HID_USAGE);
		/*
		 * MS PTP spec says that बाह्यal buttons left and right have
		 * usages 2 and 3.
		 */
		अगर ((app->quirks & MT_QUIRK_WIN8_PTP_BUTTONS) &&
		    field->application == HID_DG_TOUCHPAD &&
		    (usage->hid & HID_USAGE) > 1)
			code--;

		अगर (field->application == HID_GD_SYSTEM_MULTIAXIS)
			code = BTN_0  + ((usage->hid - 1) & HID_USAGE);

		hid_map_usage(hi, usage, bit, max, EV_KEY, code);
		अगर (!*bit)
			वापस -1;
		input_set_capability(hi->input, EV_KEY, code);
		वापस 1;

	हाल 0xff000000:
		/* we करो not want to map these: no input-oriented meaning */
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_compute_slot(काष्ठा mt_device *td, काष्ठा mt_application *app,
			   काष्ठा mt_usages *slot,
			   काष्ठा input_dev *input)
अणु
	__s32 quirks = app->quirks;

	अगर (quirks & MT_QUIRK_SLOT_IS_CONTACTID)
		वापस *slot->contactid;

	अगर (quirks & MT_QUIRK_CYPRESS)
		वापस cypress_compute_slot(app, slot);

	अगर (quirks & MT_QUIRK_SLOT_IS_CONTACTNUMBER)
		वापस app->num_received;

	अगर (quirks & MT_QUIRK_SLOT_IS_CONTACTID_MINUS_ONE)
		वापस *slot->contactid - 1;

	वापस input_mt_get_slot_by_key(input, *slot->contactid);
पूर्ण

अटल व्योम mt_release_pending_palms(काष्ठा mt_device *td,
				     काष्ठा mt_application *app,
				     काष्ठा input_dev *input)
अणु
	पूर्णांक slotnum;
	bool need_sync = false;

	क्रम_each_set_bit(slotnum, app->pending_palm_slots, td->maxcontacts) अणु
		clear_bit(slotnum, app->pending_palm_slots);

		input_mt_slot(input, slotnum);
		input_mt_report_slot_inactive(input);

		need_sync = true;
	पूर्ण

	अगर (need_sync) अणु
		input_mt_sync_frame(input);
		input_sync(input);
	पूर्ण
पूर्ण

/*
 * this function is called when a whole packet has been received and processed,
 * so that it can decide what to send to the input layer.
 */
अटल व्योम mt_sync_frame(काष्ठा mt_device *td, काष्ठा mt_application *app,
			  काष्ठा input_dev *input)
अणु
	अगर (app->quirks & MT_QUIRK_WIN8_PTP_BUTTONS)
		input_event(input, EV_KEY, BTN_LEFT, app->left_button_state);

	input_mt_sync_frame(input);
	input_event(input, EV_MSC, MSC_TIMESTAMP, app->बारtamp);
	input_sync(input);

	mt_release_pending_palms(td, app, input);

	app->num_received = 0;
	app->left_button_state = 0;

	अगर (test_bit(MT_IO_FLAGS_ACTIVE_SLOTS, &td->mt_io_flags))
		set_bit(MT_IO_FLAGS_PENDING_SLOTS, &td->mt_io_flags);
	अन्यथा
		clear_bit(MT_IO_FLAGS_PENDING_SLOTS, &td->mt_io_flags);
	clear_bit(MT_IO_FLAGS_ACTIVE_SLOTS, &td->mt_io_flags);
पूर्ण

अटल पूर्णांक mt_compute_बारtamp(काष्ठा mt_application *app, __s32 value)
अणु
	दीर्घ delta = value - app->prev_scanसमय;
	अचिन्हित दीर्घ jdelta = jअगरfies_to_usecs(jअगरfies - app->jअगरfies);

	app->jअगरfies = jअगरfies;

	अगर (delta < 0)
		delta += app->scanसमय_logical_max;

	/* HID_DG_SCANTIME is expressed in 100us, we want it in us. */
	delta *= 100;

	अगर (jdelta > MAX_TIMESTAMP_INTERVAL)
		/* No data received क्रम a जबतक, resync the बारtamp. */
		वापस 0;
	अन्यथा
		वापस app->बारtamp + delta;
पूर्ण

अटल पूर्णांक mt_touch_event(काष्ठा hid_device *hid, काष्ठा hid_field *field,
				काष्ठा hid_usage *usage, __s32 value)
अणु
	/* we will handle the hidinput part later, now reमुख्यs hiddev */
	अगर (hid->claimed & HID_CLAIMED_HIDDEV && hid->hiddev_hid_event)
		hid->hiddev_hid_event(hid, field, usage, value);

	वापस 1;
पूर्ण

अटल पूर्णांक mt_process_slot(काष्ठा mt_device *td, काष्ठा input_dev *input,
			    काष्ठा mt_application *app,
			    काष्ठा mt_usages *slot)
अणु
	काष्ठा input_mt *mt = input->mt;
	__s32 quirks = app->quirks;
	bool valid = true;
	bool confidence_state = true;
	bool inrange_state = false;
	पूर्णांक active;
	पूर्णांक slotnum;
	पूर्णांक tool = MT_TOOL_FINGER;

	अगर (!slot)
		वापस -EINVAL;

	अगर ((quirks & MT_QUIRK_CONTACT_CNT_ACCURATE) &&
	    app->num_received >= app->num_expected)
		वापस -EAGAIN;

	अगर (!(quirks & MT_QUIRK_ALWAYS_VALID)) अणु
		अगर (quirks & MT_QUIRK_VALID_IS_INRANGE)
			valid = *slot->inrange_state;
		अगर (quirks & MT_QUIRK_NOT_SEEN_MEANS_UP)
			valid = *slot->tip_state;
		अगर (quirks & MT_QUIRK_VALID_IS_CONFIDENCE)
			valid = *slot->confidence_state;

		अगर (!valid)
			वापस 0;
	पूर्ण

	slotnum = mt_compute_slot(td, app, slot, input);
	अगर (slotnum < 0 || slotnum >= td->maxcontacts)
		वापस 0;

	अगर ((quirks & MT_QUIRK_IGNORE_DUPLICATES) && mt) अणु
		काष्ठा input_mt_slot *i_slot = &mt->slots[slotnum];

		अगर (input_mt_is_active(i_slot) &&
		    input_mt_is_used(mt, i_slot))
			वापस -EAGAIN;
	पूर्ण

	अगर (quirks & MT_QUIRK_CONFIDENCE)
		confidence_state = *slot->confidence_state;

	अगर (quirks & MT_QUIRK_HOVERING)
		inrange_state = *slot->inrange_state;

	active = *slot->tip_state || inrange_state;

	अगर (app->application == HID_GD_SYSTEM_MULTIAXIS)
		tool = MT_TOOL_DIAL;
	अन्यथा अगर (unlikely(!confidence_state)) अणु
		tool = MT_TOOL_PALM;
		अगर (!active && mt &&
		    input_mt_is_active(&mt->slots[slotnum])) अणु
			/*
			 * The non-confidence was reported क्रम
			 * previously valid contact that is also no
			 * दीर्घer valid. We can't simply report
			 * lअगरt-off as userspace will not be aware
			 * of non-confidence, so we need to split
			 * it पूर्णांकo 2 events: active MT_TOOL_PALM
			 * and a separate lअगरtoff.
			 */
			active = true;
			set_bit(slotnum, app->pending_palm_slots);
		पूर्ण
	पूर्ण

	input_mt_slot(input, slotnum);
	input_mt_report_slot_state(input, tool, active);
	अगर (active) अणु
		/* this finger is in proximity of the sensor */
		पूर्णांक wide = (*slot->w > *slot->h);
		पूर्णांक major = max(*slot->w, *slot->h);
		पूर्णांक minor = min(*slot->w, *slot->h);
		पूर्णांक orientation = wide;
		पूर्णांक max_azimuth;
		पूर्णांक azimuth;

		अगर (slot->a != DEFAULT_ZERO) अणु
			/*
			 * Azimuth is counter-घड़ीwise and ranges from [0, MAX)
			 * (a full revolution). Convert it to घड़ीwise ranging
			 * [-MAX/2, MAX/2].
			 *
			 * Note that ABS_MT_ORIENTATION require us to report
			 * the limit of [-MAX/4, MAX/4], but the value can go
			 * out of range to [-MAX/2, MAX/2] to report an upside
			 * करोwn ellipsis.
			 */
			azimuth = *slot->a;
			max_azimuth = input_असल_get_max(input,
							ABS_MT_ORIENTATION);
			अगर (azimuth > max_azimuth * 2)
				azimuth -= max_azimuth * 4;
			orientation = -azimuth;
		पूर्ण

		अगर (quirks & MT_QUIRK_TOUCH_SIZE_SCALING) अणु
			/*
			 * भागided by two to match visual scale of touch
			 * क्रम devices with this quirk
			 */
			major = major >> 1;
			minor = minor >> 1;
		पूर्ण

		input_event(input, EV_ABS, ABS_MT_POSITION_X, *slot->x);
		input_event(input, EV_ABS, ABS_MT_POSITION_Y, *slot->y);
		input_event(input, EV_ABS, ABS_MT_TOOL_X, *slot->cx);
		input_event(input, EV_ABS, ABS_MT_TOOL_Y, *slot->cy);
		input_event(input, EV_ABS, ABS_MT_DISTANCE, !*slot->tip_state);
		input_event(input, EV_ABS, ABS_MT_ORIENTATION, orientation);
		input_event(input, EV_ABS, ABS_MT_PRESSURE, *slot->p);
		input_event(input, EV_ABS, ABS_MT_TOUCH_MAJOR, major);
		input_event(input, EV_ABS, ABS_MT_TOUCH_MINOR, minor);

		set_bit(MT_IO_FLAGS_ACTIVE_SLOTS, &td->mt_io_flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mt_process_mt_event(काष्ठा hid_device *hid,
				काष्ठा mt_application *app,
				काष्ठा hid_field *field,
				काष्ठा hid_usage *usage,
				__s32 value,
				bool first_packet)
अणु
	__s32 quirks = app->quirks;
	काष्ठा input_dev *input = field->hidinput->input;

	अगर (!usage->type || !(hid->claimed & HID_CLAIMED_INPUT))
		वापस;

	अगर (quirks & MT_QUIRK_WIN8_PTP_BUTTONS) अणु

		/*
		 * For Win8 PTP touchpads we should only look at
		 * non finger/touch events in the first_packet of a
		 * (possible) multi-packet frame.
		 */
		अगर (!first_packet)
			वापस;

		/*
		 * For Win8 PTP touchpads we map both the clickpad click
		 * and any "external" left buttons to BTN_LEFT अगर a
		 * device claims to have both we need to report 1 क्रम
		 * BTN_LEFT अगर either is pressed, so we or all values
		 * together and report the result in mt_sync_frame().
		 */
		अगर (usage->type == EV_KEY && usage->code == BTN_LEFT) अणु
			app->left_button_state |= value;
			वापस;
		पूर्ण
	पूर्ण

	input_event(input, usage->type, usage->code, value);
पूर्ण

अटल व्योम mt_touch_report(काष्ठा hid_device *hid,
			    काष्ठा mt_report_data *rdata)
अणु
	काष्ठा mt_device *td = hid_get_drvdata(hid);
	काष्ठा hid_report *report = rdata->report;
	काष्ठा mt_application *app = rdata->application;
	काष्ठा hid_field *field;
	काष्ठा input_dev *input;
	काष्ठा mt_usages *slot;
	bool first_packet;
	अचिन्हित count;
	पूर्णांक r, n;
	पूर्णांक scanसमय = 0;
	पूर्णांक contact_count = -1;

	/* sticky fingers release in progress, पात */
	अगर (test_and_set_bit(MT_IO_FLAGS_RUNNING, &td->mt_io_flags))
		वापस;

	scanसमय = *app->scanसमय;
	app->बारtamp = mt_compute_बारtamp(app, scanसमय);
	अगर (app->raw_cc != DEFAULT_ZERO)
		contact_count = *app->raw_cc;

	/*
	 * Includes multi-packet support where subsequent
	 * packets are sent with zero contactcount.
	 */
	अगर (contact_count >= 0) अणु
		/*
		 * For Win8 PTPs the first packet (td->num_received == 0) may
		 * have a contactcount of 0 अगर there only is a button event.
		 * We द्विगुन check that this is not a continuation packet
		 * of a possible multi-packet frame be checking that the
		 * बारtamp has changed.
		 */
		अगर ((app->quirks & MT_QUIRK_WIN8_PTP_BUTTONS) &&
		    app->num_received == 0 &&
		    app->prev_scanसमय != scanसमय)
			app->num_expected = contact_count;
		/* A non 0 contact count always indicates a first packet */
		अन्यथा अगर (contact_count)
			app->num_expected = contact_count;
	पूर्ण
	app->prev_scanसमय = scanसमय;

	first_packet = app->num_received == 0;

	input = report->field[0]->hidinput->input;

	list_क्रम_each_entry(slot, &app->mt_usages, list) अणु
		अगर (!mt_process_slot(td, input, app, slot))
			app->num_received++;
	पूर्ण

	क्रम (r = 0; r < report->maxfield; r++) अणु
		field = report->field[r];
		count = field->report_count;

		अगर (!(HID_MAIN_ITEM_VARIABLE & field->flags))
			जारी;

		क्रम (n = 0; n < count; n++)
			mt_process_mt_event(hid, app, field,
					    &field->usage[n], field->value[n],
					    first_packet);
	पूर्ण

	अगर (app->num_received >= app->num_expected)
		mt_sync_frame(td, app, input);

	/*
	 * Winकरोws 8 specs says 2 things:
	 * - once a contact has been reported, it has to be reported in each
	 *   subsequent report
	 * - the report rate when fingers are present has to be at least
	 *   the refresh rate of the screen, 60 or 120 Hz
	 *
	 * I पूर्णांकerprete this that the specअगरication क्रमces a report rate of
	 * at least 60 Hz क्रम a touchscreen to be certअगरied.
	 * Which means that अगर we करो not get a report whithin 16 ms, either
	 * something wrong happens, either the touchscreen क्रममाला_लो to send
	 * a release. Taking a reasonable margin allows to हटाओ issues
	 * with USB communication or the load of the machine.
	 *
	 * Given that Win 8 devices are क्रमced to send a release, this will
	 * only affect laggish machines and the ones that have a firmware
	 * defect.
	 */
	अगर (app->quirks & MT_QUIRK_STICKY_FINGERS) अणु
		अगर (test_bit(MT_IO_FLAGS_PENDING_SLOTS, &td->mt_io_flags))
			mod_समयr(&td->release_समयr,
				  jअगरfies + msecs_to_jअगरfies(100));
		अन्यथा
			del_समयr(&td->release_समयr);
	पूर्ण

	clear_bit(MT_IO_FLAGS_RUNNING, &td->mt_io_flags);
पूर्ण

अटल पूर्णांक mt_touch_input_configured(काष्ठा hid_device *hdev,
				     काष्ठा hid_input *hi,
				     काष्ठा mt_application *app)
अणु
	काष्ठा mt_device *td = hid_get_drvdata(hdev);
	काष्ठा mt_class *cls = &td->mtclass;
	काष्ठा input_dev *input = hi->input;
	पूर्णांक ret;

	अगर (!td->maxcontacts)
		td->maxcontacts = MT_DEFAULT_MAXCONTACT;

	mt_post_parse(td, app);
	अगर (td->serial_maybe)
		mt_post_parse_शेष_settings(td, app);

	अगर (cls->is_indirect)
		app->mt_flags |= INPUT_MT_POINTER;

	अगर (app->quirks & MT_QUIRK_NOT_SEEN_MEANS_UP)
		app->mt_flags |= INPUT_MT_DROP_UNUSED;

	/* check क्रम clickpads */
	अगर ((app->mt_flags & INPUT_MT_POINTER) &&
	    (app->buttons_count == 1))
		td->is_buttonpad = true;

	अगर (td->is_buttonpad)
		__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);

	app->pending_palm_slots = devm_kसुस्मृति(&hi->input->dev,
					       BITS_TO_LONGS(td->maxcontacts),
					       माप(दीर्घ),
					       GFP_KERNEL);
	अगर (!app->pending_palm_slots)
		वापस -ENOMEM;

	ret = input_mt_init_slots(input, td->maxcontacts, app->mt_flags);
	अगर (ret)
		वापस ret;

	app->mt_flags = 0;
	वापस 0;
पूर्ण

#घोषणा mt_map_key_clear(c)	hid_map_usage_clear(hi, usage, bit, \
						    max, EV_KEY, (c))
अटल पूर्णांक mt_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा mt_device *td = hid_get_drvdata(hdev);
	काष्ठा mt_application *application;
	काष्ठा mt_report_data *rdata;

	rdata = mt_find_report_data(td, field->report);
	अगर (!rdata) अणु
		hid_err(hdev, "failed to allocate data for report\n");
		वापस 0;
	पूर्ण

	application = rdata->application;

	/*
	 * If mtclass.export_all_inमाला_दो is not set, only map fields from
	 * TouchScreen or TouchPad collections. We need to ignore fields
	 * that beदीर्घ to other collections such as Mouse that might have
	 * the same GenericDesktop usages.
	 */
	अगर (!td->mtclass.export_all_inमाला_दो &&
	    field->application != HID_DG_TOUCHSCREEN &&
	    field->application != HID_DG_PEN &&
	    field->application != HID_DG_TOUCHPAD &&
	    field->application != HID_GD_KEYBOARD &&
	    field->application != HID_GD_SYSTEM_CONTROL &&
	    field->application != HID_CP_CONSUMER_CONTROL &&
	    field->application != HID_GD_WIRELESS_RADIO_CTLS &&
	    field->application != HID_GD_SYSTEM_MULTIAXIS &&
	    !(field->application == HID_VD_ASUS_CUSTOM_MEDIA_KEYS &&
	      application->quirks & MT_QUIRK_ASUS_CUSTOM_UP))
		वापस -1;

	/*
	 * Some Asus keyboard+touchpad devices have the hotkeys defined in the
	 * touchpad report descriptor. We need to treat these as an array to
	 * map usages to input keys.
	 */
	अगर (field->application == HID_VD_ASUS_CUSTOM_MEDIA_KEYS &&
	    application->quirks & MT_QUIRK_ASUS_CUSTOM_UP &&
	    (usage->hid & HID_USAGE_PAGE) == HID_UP_CUSTOM) अणु
		set_bit(EV_REP, hi->input->evbit);
		अगर (field->flags & HID_MAIN_ITEM_VARIABLE)
			field->flags &= ~HID_MAIN_ITEM_VARIABLE;
		चयन (usage->hid & HID_USAGE) अणु
		हाल 0x10: mt_map_key_clear(KEY_BRIGHTNESSDOWN);	अवरोध;
		हाल 0x20: mt_map_key_clear(KEY_BRIGHTNESSUP);		अवरोध;
		हाल 0x35: mt_map_key_clear(KEY_DISPLAY_OFF);		अवरोध;
		हाल 0x6b: mt_map_key_clear(KEY_F21);			अवरोध;
		हाल 0x6c: mt_map_key_clear(KEY_SLEEP);			अवरोध;
		शेष:
			वापस -1;
		पूर्ण
		वापस 1;
	पूर्ण

	अगर (rdata->is_mt_collection)
		वापस mt_touch_input_mapping(hdev, hi, field, usage, bit, max,
					      application);

	/*
	 * some egalax touchscreens have "application == DG_TOUCHSCREEN"
	 * क्रम the stylus. Overग_लिखो the hid_input application
	 */
	अगर (field->physical == HID_DG_STYLUS)
		hi->application = HID_DG_STYLUS;

	/* let hid-core decide क्रम the others */
	वापस 0;
पूर्ण

अटल पूर्णांक mt_input_mapped(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा mt_device *td = hid_get_drvdata(hdev);
	काष्ठा mt_report_data *rdata;

	rdata = mt_find_report_data(td, field->report);
	अगर (rdata && rdata->is_mt_collection) अणु
		/* We own these mappings, tell hid-input to ignore them */
		वापस -1;
	पूर्ण

	/* let hid-core decide क्रम the others */
	वापस 0;
पूर्ण

अटल पूर्णांक mt_event(काष्ठा hid_device *hid, काष्ठा hid_field *field,
				काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा mt_device *td = hid_get_drvdata(hid);
	काष्ठा mt_report_data *rdata;

	rdata = mt_find_report_data(td, field->report);
	अगर (rdata && rdata->is_mt_collection)
		वापस mt_touch_event(hid, field, usage, value);

	वापस 0;
पूर्ण

अटल व्योम mt_report(काष्ठा hid_device *hid, काष्ठा hid_report *report)
अणु
	काष्ठा mt_device *td = hid_get_drvdata(hid);
	काष्ठा hid_field *field = report->field[0];
	काष्ठा mt_report_data *rdata;

	अगर (!(hid->claimed & HID_CLAIMED_INPUT))
		वापस;

	rdata = mt_find_report_data(td, report);
	अगर (rdata && rdata->is_mt_collection)
		वापस mt_touch_report(hid, rdata);

	अगर (field && field->hidinput && field->hidinput->input)
		input_sync(field->hidinput->input);
पूर्ण

अटल bool mt_need_to_apply_feature(काष्ठा hid_device *hdev,
				     काष्ठा hid_field *field,
				     काष्ठा hid_usage *usage,
				     क्रमागत latency_mode latency,
				     bool surface_चयन,
				     bool button_चयन,
				     bool *inpuपंचांगode_found)
अणु
	काष्ठा mt_device *td = hid_get_drvdata(hdev);
	काष्ठा mt_class *cls = &td->mtclass;
	काष्ठा hid_report *report = field->report;
	अचिन्हित पूर्णांक index = usage->usage_index;
	अक्षर *buf;
	u32 report_len;
	पूर्णांक max;

	चयन (usage->hid) अणु
	हाल HID_DG_INPUTMODE:
		/*
		 * Some elan panels wrongly declare 2 input mode features,
		 * and silently ignore when we set the value in the second
		 * field. Skip the second feature and hope क्रम the best.
		 */
		अगर (*inpuपंचांगode_found)
			वापस false;

		अगर (cls->quirks & MT_QUIRK_FORCE_GET_FEATURE) अणु
			report_len = hid_report_len(report);
			buf = hid_alloc_report_buf(report, GFP_KERNEL);
			अगर (!buf) अणु
				hid_err(hdev,
					"failed to allocate buffer for report\n");
				वापस false;
			पूर्ण
			hid_hw_raw_request(hdev, report->id, buf, report_len,
					   HID_FEATURE_REPORT,
					   HID_REQ_GET_REPORT);
			kमुक्त(buf);
		पूर्ण

		field->value[index] = td->inpuपंचांगode_value;
		*inpuपंचांगode_found = true;
		वापस true;

	हाल HID_DG_CONTACTMAX:
		अगर (cls->maxcontacts) अणु
			max = min_t(पूर्णांक, field->logical_maximum,
				    cls->maxcontacts);
			अगर (field->value[index] != max) अणु
				field->value[index] = max;
				वापस true;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल HID_DG_LATENCYMODE:
		field->value[index] = latency;
		वापस true;

	हाल HID_DG_SURFACESWITCH:
		field->value[index] = surface_चयन;
		वापस true;

	हाल HID_DG_BUTTONSWITCH:
		field->value[index] = button_चयन;
		वापस true;
	पूर्ण

	वापस false; /* no need to update the report */
पूर्ण

अटल व्योम mt_set_modes(काष्ठा hid_device *hdev, क्रमागत latency_mode latency,
			 bool surface_चयन, bool button_चयन)
अणु
	काष्ठा hid_report_क्रमागत *rep_क्रमागत;
	काष्ठा hid_report *rep;
	काष्ठा hid_usage *usage;
	पूर्णांक i, j;
	bool update_report;
	bool inpuपंचांगode_found = false;

	rep_क्रमागत = &hdev->report_क्रमागत[HID_FEATURE_REPORT];
	list_क्रम_each_entry(rep, &rep_क्रमागत->report_list, list) अणु
		update_report = false;

		क्रम (i = 0; i < rep->maxfield; i++) अणु
			/* Ignore अगर report count is out of bounds. */
			अगर (rep->field[i]->report_count < 1)
				जारी;

			क्रम (j = 0; j < rep->field[i]->maxusage; j++) अणु
				usage = &rep->field[i]->usage[j];

				अगर (mt_need_to_apply_feature(hdev,
							     rep->field[i],
							     usage,
							     latency,
							     surface_चयन,
							     button_चयन,
							     &inpuपंचांगode_found))
					update_report = true;
			पूर्ण
		पूर्ण

		अगर (update_report)
			hid_hw_request(hdev, rep, HID_REQ_SET_REPORT);
	पूर्ण
पूर्ण

अटल व्योम mt_post_parse_शेष_settings(काष्ठा mt_device *td,
					   काष्ठा mt_application *app)
अणु
	__s32 quirks = app->quirks;

	/* unknown serial device needs special quirks */
	अगर (list_is_singular(&app->mt_usages)) अणु
		quirks |= MT_QUIRK_ALWAYS_VALID;
		quirks &= ~MT_QUIRK_NOT_SEEN_MEANS_UP;
		quirks &= ~MT_QUIRK_VALID_IS_INRANGE;
		quirks &= ~MT_QUIRK_VALID_IS_CONFIDENCE;
		quirks &= ~MT_QUIRK_CONTACT_CNT_ACCURATE;
	पूर्ण

	app->quirks = quirks;
पूर्ण

अटल व्योम mt_post_parse(काष्ठा mt_device *td, काष्ठा mt_application *app)
अणु
	अगर (!app->have_contact_count)
		app->quirks &= ~MT_QUIRK_CONTACT_CNT_ACCURATE;
पूर्ण

अटल पूर्णांक mt_input_configured(काष्ठा hid_device *hdev, काष्ठा hid_input *hi)
अणु
	काष्ठा mt_device *td = hid_get_drvdata(hdev);
	अक्षर *name;
	स्थिर अक्षर *suffix = शून्य;
	काष्ठा mt_report_data *rdata;
	काष्ठा mt_application *mt_application = शून्य;
	काष्ठा hid_report *report;
	पूर्णांक ret;

	list_क्रम_each_entry(report, &hi->reports, hidinput_list) अणु
		rdata = mt_find_report_data(td, report);
		अगर (!rdata) अणु
			hid_err(hdev, "failed to allocate data for report\n");
			वापस -ENOMEM;
		पूर्ण

		mt_application = rdata->application;

		अगर (rdata->is_mt_collection) अणु
			ret = mt_touch_input_configured(hdev, hi,
							mt_application);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	चयन (hi->application) अणु
	हाल HID_GD_KEYBOARD:
	हाल HID_GD_KEYPAD:
	हाल HID_GD_MOUSE:
	हाल HID_DG_TOUCHPAD:
	हाल HID_GD_SYSTEM_CONTROL:
	हाल HID_CP_CONSUMER_CONTROL:
	हाल HID_GD_WIRELESS_RADIO_CTLS:
	हाल HID_GD_SYSTEM_MULTIAXIS:
		/* alपढ़ोy handled by hid core */
		अवरोध;
	हाल HID_DG_TOUCHSCREEN:
		/* we करो not set suffix = "Touchscreen" */
		hi->input->name = hdev->name;
		अवरोध;
	हाल HID_VD_ASUS_CUSTOM_MEDIA_KEYS:
		suffix = "Custom Media Keys";
		अवरोध;
	हाल HID_DG_STYLUS:
		/* क्रमce BTN_STYLUS to allow tablet matching in udev */
		__set_bit(BTN_STYLUS, hi->input->keybit);
		fallthrough;
	हाल HID_DG_PEN:
		suffix = "Stylus";
		अवरोध;
	शेष:
		suffix = "UNKNOWN";
		अवरोध;
	पूर्ण

	अगर (suffix) अणु
		name = devm_kzalloc(&hi->input->dev,
				    म_माप(hdev->name) + म_माप(suffix) + 2,
				    GFP_KERNEL);
		अगर (name) अणु
			प्र_लिखो(name, "%s %s", hdev->name, suffix);
			hi->input->name = name;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mt_fix_स्थिर_field(काष्ठा hid_field *field, अचिन्हित पूर्णांक usage)
अणु
	अगर (field->usage[0].hid != usage ||
	    !(field->flags & HID_MAIN_ITEM_CONSTANT))
		वापस;

	field->flags &= ~HID_MAIN_ITEM_CONSTANT;
	field->flags |= HID_MAIN_ITEM_VARIABLE;
पूर्ण

अटल व्योम mt_fix_स्थिर_fields(काष्ठा hid_device *hdev, अचिन्हित पूर्णांक usage)
अणु
	काष्ठा hid_report *report;
	पूर्णांक i;

	list_क्रम_each_entry(report,
			    &hdev->report_क्रमागत[HID_INPUT_REPORT].report_list,
			    list) अणु

		अगर (!report->maxfield)
			जारी;

		क्रम (i = 0; i < report->maxfield; i++)
			अगर (report->field[i]->maxusage >= 1)
				mt_fix_स्थिर_field(report->field[i], usage);
	पूर्ण
पूर्ण

अटल व्योम mt_release_contacts(काष्ठा hid_device *hid)
अणु
	काष्ठा hid_input *hidinput;
	काष्ठा mt_application *application;
	काष्ठा mt_device *td = hid_get_drvdata(hid);

	list_क्रम_each_entry(hidinput, &hid->inमाला_दो, list) अणु
		काष्ठा input_dev *input_dev = hidinput->input;
		काष्ठा input_mt *mt = input_dev->mt;
		पूर्णांक i;

		अगर (mt) अणु
			क्रम (i = 0; i < mt->num_slots; i++) अणु
				input_mt_slot(input_dev, i);
				input_mt_report_slot_inactive(input_dev);
			पूर्ण
			input_mt_sync_frame(input_dev);
			input_sync(input_dev);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(application, &td->applications, list) अणु
		application->num_received = 0;
	पूर्ण
पूर्ण

अटल व्योम mt_expired_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा mt_device *td = from_समयr(td, t, release_समयr);
	काष्ठा hid_device *hdev = td->hdev;

	/*
	 * An input report came in just beक्रमe we release the sticky fingers,
	 * it will take care of the sticky fingers.
	 */
	अगर (test_and_set_bit(MT_IO_FLAGS_RUNNING, &td->mt_io_flags))
		वापस;
	अगर (test_bit(MT_IO_FLAGS_PENDING_SLOTS, &td->mt_io_flags))
		mt_release_contacts(hdev);
	clear_bit(MT_IO_FLAGS_RUNNING, &td->mt_io_flags);
पूर्ण

अटल पूर्णांक mt_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret, i;
	काष्ठा mt_device *td;
	स्थिर काष्ठा mt_class *mtclass = mt_classes; /* MT_CLS_DEFAULT */

	क्रम (i = 0; mt_classes[i].name ; i++) अणु
		अगर (id->driver_data == mt_classes[i].name) अणु
			mtclass = &(mt_classes[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	td = devm_kzalloc(&hdev->dev, माप(काष्ठा mt_device), GFP_KERNEL);
	अगर (!td) अणु
		dev_err(&hdev->dev, "cannot allocate multitouch data\n");
		वापस -ENOMEM;
	पूर्ण
	td->hdev = hdev;
	td->mtclass = *mtclass;
	td->inpuपंचांगode_value = MT_INPUTMODE_TOUCHSCREEN;
	hid_set_drvdata(hdev, td);

	INIT_LIST_HEAD(&td->applications);
	INIT_LIST_HEAD(&td->reports);

	अगर (id->venकरोr == HID_ANY_ID && id->product == HID_ANY_ID)
		td->serial_maybe = true;

	/* This allows the driver to correctly support devices
	 * that emit events over several HID messages.
	 */
	hdev->quirks |= HID_QUIRK_NO_INPUT_SYNC;

	/*
	 * This allows the driver to handle dअगरferent input sensors
	 * that emits events through dअगरferent applications on the same HID
	 * device.
	 */
	hdev->quirks |= HID_QUIRK_INPUT_PER_APP;

	अगर (id->group != HID_GROUP_MULTITOUCH_WIN_8)
		hdev->quirks |= HID_QUIRK_MULTI_INPUT;

	अगर (mtclass->quirks & MT_QUIRK_FORCE_MULTI_INPUT) अणु
		hdev->quirks &= ~HID_QUIRK_INPUT_PER_APP;
		hdev->quirks |= HID_QUIRK_MULTI_INPUT;
	पूर्ण

	समयr_setup(&td->release_समयr, mt_expired_समयout, 0);

	ret = hid_parse(hdev);
	अगर (ret != 0)
		वापस ret;

	अगर (mtclass->quirks & MT_QUIRK_FIX_CONST_CONTACT_ID)
		mt_fix_स्थिर_fields(hdev, HID_DG_CONTACTID);

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret)
		वापस ret;

	ret = sysfs_create_group(&hdev->dev.kobj, &mt_attribute_group);
	अगर (ret)
		dev_warn(&hdev->dev, "Cannot allocate sysfs group for %s\n",
				hdev->name);

	mt_set_modes(hdev, HID_LATENCY_NORMAL, true, true);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mt_suspend(काष्ठा hid_device *hdev, pm_message_t state)
अणु
	काष्ठा mt_device *td = hid_get_drvdata(hdev);

	/* High latency is desirable क्रम घातer savings during S3/S0ix */
	अगर (td->mtclass.quirks & MT_QUIRK_DISABLE_WAKEUP)
		mt_set_modes(hdev, HID_LATENCY_HIGH, false, false);
	अन्यथा
		mt_set_modes(hdev, HID_LATENCY_HIGH, true, true);

	वापस 0;
पूर्ण

अटल पूर्णांक mt_reset_resume(काष्ठा hid_device *hdev)
अणु
	mt_release_contacts(hdev);
	mt_set_modes(hdev, HID_LATENCY_NORMAL, true, true);
	वापस 0;
पूर्ण

अटल पूर्णांक mt_resume(काष्ठा hid_device *hdev)
अणु
	/* Some Elan legacy devices require SET_IDLE to be set on resume.
	 * It should be safe to send it to other devices too.
	 * Tested on 3M, Stantum, Cypress, Zytronic, eGalax, and Elan panels. */

	hid_hw_idle(hdev, 0, 0, HID_REQ_SET_IDLE);

	mt_set_modes(hdev, HID_LATENCY_NORMAL, true, true);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम mt_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा mt_device *td = hid_get_drvdata(hdev);

	del_समयr_sync(&td->release_समयr);

	sysfs_हटाओ_group(&hdev->dev.kobj, &mt_attribute_group);
	hid_hw_stop(hdev);
पूर्ण

/*
 * This list contains only:
 * - VID/PID of products not working with the शेष multitouch handling
 * - 2 generic rules.
 * So there is no poपूर्णांक in adding here any device with MT_CLS_DEFAULT.
 */
अटल स्थिर काष्ठा hid_device_id mt_devices[] = अणु

	/* 3M panels */
	अणु .driver_data = MT_CLS_3M,
		MT_USB_DEVICE(USB_VENDOR_ID_3M,
			USB_DEVICE_ID_3M1968) पूर्ण,
	अणु .driver_data = MT_CLS_3M,
		MT_USB_DEVICE(USB_VENDOR_ID_3M,
			USB_DEVICE_ID_3M2256) पूर्ण,
	अणु .driver_data = MT_CLS_3M,
		MT_USB_DEVICE(USB_VENDOR_ID_3M,
			USB_DEVICE_ID_3M3266) पूर्ण,

	/* Anton devices */
	अणु .driver_data = MT_CLS_EXPORT_ALL_INPUTS,
		MT_USB_DEVICE(USB_VENDOR_ID_ANTON,
			USB_DEVICE_ID_ANTON_TOUCH_PAD) पूर्ण,

	/* Asus T101HA */
	अणु .driver_data = MT_CLS_WIN_8_DISABLE_WAKEUP,
		HID_DEVICE(BUS_USB, HID_GROUP_MULTITOUCH_WIN_8,
			   USB_VENDOR_ID_ASUSTEK,
			   USB_DEVICE_ID_ASUSTEK_T101HA_KEYBOARD) पूर्ण,

	/* Asus T304UA */
	अणु .driver_data = MT_CLS_ASUS,
		HID_DEVICE(BUS_USB, HID_GROUP_MULTITOUCH_WIN_8,
			USB_VENDOR_ID_ASUSTEK,
			USB_DEVICE_ID_ASUSTEK_T304_KEYBOARD) पूर्ण,

	/* Aपंचांगel panels */
	अणु .driver_data = MT_CLS_SERIAL,
		MT_USB_DEVICE(USB_VENDOR_ID_ATMEL,
			USB_DEVICE_ID_ATMEL_MXT_DIGITIZER) पूर्ण,

	/* Baanto multitouch devices */
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_BAANTO,
			USB_DEVICE_ID_BAANTO_MT_190W2) पूर्ण,

	/* Canकरो panels */
	अणु .driver_data = MT_CLS_DUAL_INRANGE_CONTACTNUMBER,
		MT_USB_DEVICE(USB_VENDOR_ID_CANDO,
			USB_DEVICE_ID_CANDO_MULTI_TOUCH) पूर्ण,
	अणु .driver_data = MT_CLS_DUAL_INRANGE_CONTACTNUMBER,
		MT_USB_DEVICE(USB_VENDOR_ID_CANDO,
			USB_DEVICE_ID_CANDO_MULTI_TOUCH_15_6) पूर्ण,

	/* Chunghwa Telecom touch panels */
	अणु  .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_CHUNGHWAT,
			USB_DEVICE_ID_CHUNGHWAT_MULTITOUCH) पूर्ण,

	/* CJTouch panels */
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_CJTOUCH,
			USB_DEVICE_ID_CJTOUCH_MULTI_TOUCH_0020) पूर्ण,
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_CJTOUCH,
			USB_DEVICE_ID_CJTOUCH_MULTI_TOUCH_0040) पूर्ण,

	/* CVTouch panels */
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_CVTOUCH,
			USB_DEVICE_ID_CVTOUCH_SCREEN) पूर्ण,

	/* eGalax devices (resistive) */
	अणु .driver_data = MT_CLS_EGALAX,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_480D) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_480E) पूर्ण,

	/* eGalax devices (capacitive) */
	अणु .driver_data = MT_CLS_EGALAX_SERIAL,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_7207) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_720C) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX_SERIAL,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_7224) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX_SERIAL,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_722A) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX_SERIAL,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_725E) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX_SERIAL,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_7262) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_726B) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_72A1) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX_SERIAL,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_72AA) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX,
		HID_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_72C4) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX,
		HID_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_72D0) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_72FA) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_7302) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX_SERIAL,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_7349) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX_SERIAL,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_73F7) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX_SERIAL,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_A001) पूर्ण,
	अणु .driver_data = MT_CLS_EGALAX,
		MT_USB_DEVICE(USB_VENDOR_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGALAX_MULTITOUCH_C002) पूर्ण,

	/* Elan devices */
	अणु .driver_data = MT_CLS_WIN_8_FORCE_MULTI_INPUT,
		HID_DEVICE(BUS_I2C, HID_GROUP_MULTITOUCH_WIN_8,
			USB_VENDOR_ID_ELAN, 0x313a) पूर्ण,

	/* Elitegroup panel */
	अणु .driver_data = MT_CLS_SERIAL,
		MT_USB_DEVICE(USB_VENDOR_ID_ELITEGROUP,
			USB_DEVICE_ID_ELITEGROUP_05D8) पूर्ण,

	/* Flatfrog Panels */
	अणु .driver_data = MT_CLS_FLATFROG,
		MT_USB_DEVICE(USB_VENDOR_ID_FLATFROG,
			USB_DEVICE_ID_MULTITOUCH_3200) पूर्ण,

	/* FocalTech Panels */
	अणु .driver_data = MT_CLS_SERIAL,
		MT_USB_DEVICE(USB_VENDOR_ID_CYGNAL,
			USB_DEVICE_ID_FOCALTECH_FTXXXX_MULTITOUCH) पूर्ण,

	/* GeneralTouch panel */
	अणु .driver_data = MT_CLS_GENERALTOUCH_TWOFINGERS,
		MT_USB_DEVICE(USB_VENDOR_ID_GENERAL_TOUCH,
			USB_DEVICE_ID_GENERAL_TOUCH_WIN7_TWOFINGERS) पूर्ण,
	अणु .driver_data = MT_CLS_GENERALTOUCH_PWT_TENFINGERS,
		MT_USB_DEVICE(USB_VENDOR_ID_GENERAL_TOUCH,
			USB_DEVICE_ID_GENERAL_TOUCH_WIN8_PWT_TENFINGERS) पूर्ण,
	अणु .driver_data = MT_CLS_GENERALTOUCH_TWOFINGERS,
		MT_USB_DEVICE(USB_VENDOR_ID_GENERAL_TOUCH,
			USB_DEVICE_ID_GENERAL_TOUCH_WIN8_PIT_0101) पूर्ण,
	अणु .driver_data = MT_CLS_GENERALTOUCH_PWT_TENFINGERS,
		MT_USB_DEVICE(USB_VENDOR_ID_GENERAL_TOUCH,
			USB_DEVICE_ID_GENERAL_TOUCH_WIN8_PIT_0102) पूर्ण,
	अणु .driver_data = MT_CLS_GENERALTOUCH_PWT_TENFINGERS,
		MT_USB_DEVICE(USB_VENDOR_ID_GENERAL_TOUCH,
			USB_DEVICE_ID_GENERAL_TOUCH_WIN8_PIT_0106) पूर्ण,
	अणु .driver_data = MT_CLS_GENERALTOUCH_PWT_TENFINGERS,
		MT_USB_DEVICE(USB_VENDOR_ID_GENERAL_TOUCH,
			USB_DEVICE_ID_GENERAL_TOUCH_WIN8_PIT_010A) पूर्ण,
	अणु .driver_data = MT_CLS_GENERALTOUCH_PWT_TENFINGERS,
		MT_USB_DEVICE(USB_VENDOR_ID_GENERAL_TOUCH,
			USB_DEVICE_ID_GENERAL_TOUCH_WIN8_PIT_E100) पूर्ण,

	/* Gametel game controller */
	अणु .driver_data = MT_CLS_NSMU,
		MT_BT_DEVICE(USB_VENDOR_ID_FRUCTEL,
			USB_DEVICE_ID_GAMETEL_MT_MODE) पूर्ण,

	/* GoodTouch panels */
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_GOODTOUCH,
			USB_DEVICE_ID_GOODTOUCH_000f) पूर्ण,

	/* Hanvon panels */
	अणु .driver_data = MT_CLS_DUAL_INRANGE_CONTACTID,
		MT_USB_DEVICE(USB_VENDOR_ID_HANVON_ALT,
			USB_DEVICE_ID_HANVON_ALT_MULTITOUCH) पूर्ण,

	/* Ilitek dual touch panel */
	अणु  .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_ILITEK,
			USB_DEVICE_ID_ILITEK_MULTITOUCH) पूर्ण,

	/* LG Melfas panel */
	अणु .driver_data = MT_CLS_LG,
		HID_USB_DEVICE(USB_VENDOR_ID_LG,
			USB_DEVICE_ID_LG_MELFAS_MT) पूर्ण,
	अणु .driver_data = MT_CLS_LG,
		HID_DEVICE(BUS_I2C, HID_GROUP_GENERIC,
			USB_VENDOR_ID_LG, I2C_DEVICE_ID_LG_7010) पूर्ण,

	/* Lenovo X1 TAB Gen 2 */
	अणु .driver_data = MT_CLS_WIN_8_FORCE_MULTI_INPUT,
		HID_DEVICE(BUS_USB, HID_GROUP_MULTITOUCH_WIN_8,
			   USB_VENDOR_ID_LENOVO,
			   USB_DEVICE_ID_LENOVO_X1_TAB) पूर्ण,

	/* Lenovo X1 TAB Gen 3 */
	अणु .driver_data = MT_CLS_WIN_8_FORCE_MULTI_INPUT,
		HID_DEVICE(BUS_USB, HID_GROUP_MULTITOUCH_WIN_8,
			   USB_VENDOR_ID_LENOVO,
			   USB_DEVICE_ID_LENOVO_X1_TAB3) पूर्ण,

	/* MosArt panels */
	अणु .driver_data = MT_CLS_CONFIDENCE_MINUS_ONE,
		MT_USB_DEVICE(USB_VENDOR_ID_ASUS,
			USB_DEVICE_ID_ASUS_T91MT)पूर्ण,
	अणु .driver_data = MT_CLS_CONFIDENCE_MINUS_ONE,
		MT_USB_DEVICE(USB_VENDOR_ID_ASUS,
			USB_DEVICE_ID_ASUSTEK_MULTITOUCH_YFO) पूर्ण,
	अणु .driver_data = MT_CLS_CONFIDENCE_MINUS_ONE,
		MT_USB_DEVICE(USB_VENDOR_ID_TURBOX,
			USB_DEVICE_ID_TURBOX_TOUCHSCREEN_MOSART) पूर्ण,

	/* Novatek Panel */
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_NOVATEK,
			USB_DEVICE_ID_NOVATEK_PCT) पूर्ण,

	/* Ntrig Panel */
	अणु .driver_data = MT_CLS_NSMU,
		HID_DEVICE(BUS_I2C, HID_GROUP_MULTITOUCH_WIN_8,
			USB_VENDOR_ID_NTRIG, 0x1b05) पूर्ण,

	/* Panasonic panels */
	अणु .driver_data = MT_CLS_PANASONIC,
		MT_USB_DEVICE(USB_VENDOR_ID_PANASONIC,
			USB_DEVICE_ID_PANABOARD_UBT780) पूर्ण,
	अणु .driver_data = MT_CLS_PANASONIC,
		MT_USB_DEVICE(USB_VENDOR_ID_PANASONIC,
			USB_DEVICE_ID_PANABOARD_UBT880) पूर्ण,

	/* PixArt optical touch screen */
	अणु .driver_data = MT_CLS_INRANGE_CONTACTNUMBER,
		MT_USB_DEVICE(USB_VENDOR_ID_PIXART,
			USB_DEVICE_ID_PIXART_OPTICAL_TOUCH_SCREEN) पूर्ण,
	अणु .driver_data = MT_CLS_INRANGE_CONTACTNUMBER,
		MT_USB_DEVICE(USB_VENDOR_ID_PIXART,
			USB_DEVICE_ID_PIXART_OPTICAL_TOUCH_SCREEN1) पूर्ण,
	अणु .driver_data = MT_CLS_INRANGE_CONTACTNUMBER,
		MT_USB_DEVICE(USB_VENDOR_ID_PIXART,
			USB_DEVICE_ID_PIXART_OPTICAL_TOUCH_SCREEN2) पूर्ण,

	/* PixCir-based panels */
	अणु .driver_data = MT_CLS_DUAL_INRANGE_CONTACTID,
		MT_USB_DEVICE(USB_VENDOR_ID_CANDO,
			USB_DEVICE_ID_CANDO_PIXCIR_MULTI_TOUCH) पूर्ण,

	/* Quanta-based panels */
	अणु .driver_data = MT_CLS_CONFIDENCE_CONTACT_ID,
		MT_USB_DEVICE(USB_VENDOR_ID_QUANTA,
			USB_DEVICE_ID_QUANTA_OPTICAL_TOUCH_3001) पूर्ण,

	/* Razer touchpads */
	अणु .driver_data = MT_CLS_RAZER_BLADE_STEALTH,
		HID_DEVICE(BUS_I2C, HID_GROUP_MULTITOUCH_WIN_8,
			USB_VENDOR_ID_SYNAPTICS, 0x8323) पूर्ण,

	/* Smart Tech panels */
	अणु .driver_data = MT_CLS_SMART_TECH,
		MT_USB_DEVICE(0x0b8c, 0x0092)पूर्ण,

	/* Stantum panels */
	अणु .driver_data = MT_CLS_CONFIDENCE,
		MT_USB_DEVICE(USB_VENDOR_ID_STANTUM_STM,
			USB_DEVICE_ID_MTP_STM)पूर्ण,

	/* Synaptics devices */
	अणु .driver_data = MT_CLS_WIN_8_FORCE_MULTI_INPUT,
		HID_DEVICE(BUS_I2C, HID_GROUP_MULTITOUCH_WIN_8,
			USB_VENDOR_ID_SYNAPTICS, 0xce08) पूर्ण,

	अणु .driver_data = MT_CLS_WIN_8_FORCE_MULTI_INPUT,
		HID_DEVICE(BUS_I2C, HID_GROUP_MULTITOUCH_WIN_8,
			USB_VENDOR_ID_SYNAPTICS, 0xce09) पूर्ण,

	/* TopSeed panels */
	अणु .driver_data = MT_CLS_TOPSEED,
		MT_USB_DEVICE(USB_VENDOR_ID_TOPSEED2,
			USB_DEVICE_ID_TOPSEED2_PERIPAD_701) पूर्ण,

	/* Touch International panels */
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_TOUCH_INTL,
			USB_DEVICE_ID_TOUCH_INTL_MULTI_TOUCH) पूर्ण,

	/* Unitec panels */
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_UNITEC,
			USB_DEVICE_ID_UNITEC_USB_TOUCH_0709) पूर्ण,
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_UNITEC,
			USB_DEVICE_ID_UNITEC_USB_TOUCH_0A19) पूर्ण,

	/* VTL panels */
	अणु .driver_data = MT_CLS_VTL,
		MT_USB_DEVICE(USB_VENDOR_ID_VTL,
			USB_DEVICE_ID_VTL_MULTITOUCH_FF3F) पूर्ण,

	/* Wistron panels */
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_WISTRON,
			USB_DEVICE_ID_WISTRON_OPTICAL_TOUCH) पूर्ण,

	/* XAT */
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_XAT,
			USB_DEVICE_ID_XAT_CSR) पूर्ण,

	/* Xiroku */
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_XIROKU,
			USB_DEVICE_ID_XIROKU_SPX) पूर्ण,
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_XIROKU,
			USB_DEVICE_ID_XIROKU_MPX) पूर्ण,
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_XIROKU,
			USB_DEVICE_ID_XIROKU_CSR) पूर्ण,
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_XIROKU,
			USB_DEVICE_ID_XIROKU_SPX1) पूर्ण,
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_XIROKU,
			USB_DEVICE_ID_XIROKU_MPX1) पूर्ण,
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_XIROKU,
			USB_DEVICE_ID_XIROKU_CSR1) पूर्ण,
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_XIROKU,
			USB_DEVICE_ID_XIROKU_SPX2) पूर्ण,
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_XIROKU,
			USB_DEVICE_ID_XIROKU_MPX2) पूर्ण,
	अणु .driver_data = MT_CLS_NSMU,
		MT_USB_DEVICE(USB_VENDOR_ID_XIROKU,
			USB_DEVICE_ID_XIROKU_CSR2) पूर्ण,

	/* Google MT devices */
	अणु .driver_data = MT_CLS_GOOGLE,
		HID_DEVICE(HID_BUS_ANY, HID_GROUP_ANY, USB_VENDOR_ID_GOOGLE,
			USB_DEVICE_ID_GOOGLE_TOUCH_ROSE) पूर्ण,

	/* Generic MT device */
	अणु HID_DEVICE(HID_BUS_ANY, HID_GROUP_MULTITOUCH, HID_ANY_ID, HID_ANY_ID) पूर्ण,

	/* Generic Win 8 certअगरied MT device */
	अणु  .driver_data = MT_CLS_WIN_8,
		HID_DEVICE(HID_BUS_ANY, HID_GROUP_MULTITOUCH_WIN_8,
			HID_ANY_ID, HID_ANY_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, mt_devices);

अटल स्थिर काष्ठा hid_usage_id mt_grabbed_usages[] = अणु
	अणु HID_ANY_ID, HID_ANY_ID, HID_ANY_ID पूर्ण,
	अणु HID_ANY_ID - 1, HID_ANY_ID - 1, HID_ANY_ID - 1पूर्ण
पूर्ण;

अटल काष्ठा hid_driver mt_driver = अणु
	.name = "hid-multitouch",
	.id_table = mt_devices,
	.probe = mt_probe,
	.हटाओ = mt_हटाओ,
	.input_mapping = mt_input_mapping,
	.input_mapped = mt_input_mapped,
	.input_configured = mt_input_configured,
	.feature_mapping = mt_feature_mapping,
	.usage_table = mt_grabbed_usages,
	.event = mt_event,
	.report = mt_report,
#अगर_घोषित CONFIG_PM
	.suspend = mt_suspend,
	.reset_resume = mt_reset_resume,
	.resume = mt_resume,
#पूर्ण_अगर
पूर्ण;
module_hid_driver(mt_driver);
