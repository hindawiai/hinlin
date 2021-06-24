<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Force feedback support क्रम Logitech Gaming Wheels
 *
 *  Including G27, G25, DFP, DFGT, FFEX, Momo, Momo2 &
 *  Speed Force Wireless (WiiWheel)
 *
 *  Copyright (c) 2010 Simon Wood <simon@mungewell.org>
 */

/*
 */


#समावेश <linux/input.h>
#समावेश <linux/usb.h>
#समावेश <linux/hid.h>

#समावेश "usbhid/usbhid.h"
#समावेश "hid-lg.h"
#समावेश "hid-lg4ff.h"
#समावेश "hid-ids.h"

#घोषणा LG4FF_MMODE_IS_MULTIMODE 0
#घोषणा LG4FF_MMODE_SWITCHED 1
#घोषणा LG4FF_MMODE_NOT_MULTIMODE 2

#घोषणा LG4FF_MODE_NATIVE_IDX 0
#घोषणा LG4FF_MODE_DFEX_IDX 1
#घोषणा LG4FF_MODE_DFP_IDX 2
#घोषणा LG4FF_MODE_G25_IDX 3
#घोषणा LG4FF_MODE_DFGT_IDX 4
#घोषणा LG4FF_MODE_G27_IDX 5
#घोषणा LG4FF_MODE_G29_IDX 6
#घोषणा LG4FF_MODE_MAX_IDX 7

#घोषणा LG4FF_MODE_NATIVE BIT(LG4FF_MODE_NATIVE_IDX)
#घोषणा LG4FF_MODE_DFEX BIT(LG4FF_MODE_DFEX_IDX)
#घोषणा LG4FF_MODE_DFP BIT(LG4FF_MODE_DFP_IDX)
#घोषणा LG4FF_MODE_G25 BIT(LG4FF_MODE_G25_IDX)
#घोषणा LG4FF_MODE_DFGT BIT(LG4FF_MODE_DFGT_IDX)
#घोषणा LG4FF_MODE_G27 BIT(LG4FF_MODE_G27_IDX)
#घोषणा LG4FF_MODE_G29 BIT(LG4FF_MODE_G29_IDX)

#घोषणा LG4FF_DFEX_TAG "DF-EX"
#घोषणा LG4FF_DFEX_NAME "Driving Force / Formula EX"
#घोषणा LG4FF_DFP_TAG "DFP"
#घोषणा LG4FF_DFP_NAME "Driving Force Pro"
#घोषणा LG4FF_G25_TAG "G25"
#घोषणा LG4FF_G25_NAME "G25 Racing Wheel"
#घोषणा LG4FF_G27_TAG "G27"
#घोषणा LG4FF_G27_NAME "G27 Racing Wheel"
#घोषणा LG4FF_G29_TAG "G29"
#घोषणा LG4FF_G29_NAME "G29 Racing Wheel"
#घोषणा LG4FF_DFGT_TAG "DFGT"
#घोषणा LG4FF_DFGT_NAME "Driving Force GT"

#घोषणा LG4FF_FFEX_REV_MAJ 0x21
#घोषणा LG4FF_FFEX_REV_MIN 0x00

अटल व्योम lg4ff_set_range_dfp(काष्ठा hid_device *hid, u16 range);
अटल व्योम lg4ff_set_range_g25(काष्ठा hid_device *hid, u16 range);

काष्ठा lg4ff_wheel_data अणु
	स्थिर u32 product_id;
	u16 combine;
	u16 range;
	स्थिर u16 min_range;
	स्थिर u16 max_range;
#अगर_घोषित CONFIG_LEDS_CLASS
	u8  led_state;
	काष्ठा led_classdev *led[5];
#पूर्ण_अगर
	स्थिर u32 alternate_modes;
	स्थिर अक्षर * स्थिर real_tag;
	स्थिर अक्षर * स्थिर real_name;
	स्थिर u16 real_product_id;

	व्योम (*set_range)(काष्ठा hid_device *hid, u16 range);
पूर्ण;

काष्ठा lg4ff_device_entry अणु
	spinlock_t report_lock; /* Protect output HID report */
	काष्ठा hid_report *report;
	काष्ठा lg4ff_wheel_data wdata;
पूर्ण;

अटल स्थिर चिन्हित लघु lg4ff_wheel_effects[] = अणु
	FF_CONSTANT,
	FF_AUTOCENTER,
	-1
पूर्ण;

अटल स्थिर चिन्हित लघु no_wheel_effects[] = अणु
	-1
पूर्ण;

काष्ठा lg4ff_wheel अणु
	स्थिर u32 product_id;
	स्थिर चिन्हित लघु *ff_effects;
	स्थिर u16 min_range;
	स्थिर u16 max_range;
	व्योम (*set_range)(काष्ठा hid_device *hid, u16 range);
पूर्ण;

काष्ठा lg4ff_compat_mode_चयन अणु
	स्थिर u8 cmd_count;	/* Number of commands to send */
	स्थिर u8 cmd[];
पूर्ण;

काष्ठा lg4ff_wheel_ident_info अणु
	स्थिर u32 modes;
	स्थिर u16 mask;
	स्थिर u16 result;
	स्थिर u16 real_product_id;
पूर्ण;

काष्ठा lg4ff_multimode_wheel अणु
	स्थिर u16 product_id;
	स्थिर u32 alternate_modes;
	स्थिर अक्षर *real_tag;
	स्थिर अक्षर *real_name;
पूर्ण;

काष्ठा lg4ff_alternate_mode अणु
	स्थिर u16 product_id;
	स्थिर अक्षर *tag;
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा lg4ff_wheel lg4ff_devices[] = अणु
	अणुUSB_DEVICE_ID_LOGITECH_WINGMAN_FG,  no_wheel_effects,    40, 180, शून्यपूर्ण,
	अणुUSB_DEVICE_ID_LOGITECH_WINGMAN_FFG, lg4ff_wheel_effects, 40, 180, शून्यपूर्ण,
	अणुUSB_DEVICE_ID_LOGITECH_WHEEL,       lg4ff_wheel_effects, 40, 270, शून्यपूर्ण,
	अणुUSB_DEVICE_ID_LOGITECH_MOMO_WHEEL,  lg4ff_wheel_effects, 40, 270, शून्यपूर्ण,
	अणुUSB_DEVICE_ID_LOGITECH_DFP_WHEEL,   lg4ff_wheel_effects, 40, 900, lg4ff_set_range_dfpपूर्ण,
	अणुUSB_DEVICE_ID_LOGITECH_G25_WHEEL,   lg4ff_wheel_effects, 40, 900, lg4ff_set_range_g25पूर्ण,
	अणुUSB_DEVICE_ID_LOGITECH_DFGT_WHEEL,  lg4ff_wheel_effects, 40, 900, lg4ff_set_range_g25पूर्ण,
	अणुUSB_DEVICE_ID_LOGITECH_G27_WHEEL,   lg4ff_wheel_effects, 40, 900, lg4ff_set_range_g25पूर्ण,
	अणुUSB_DEVICE_ID_LOGITECH_G29_WHEEL,   lg4ff_wheel_effects, 40, 900, lg4ff_set_range_g25पूर्ण,
	अणुUSB_DEVICE_ID_LOGITECH_MOMO_WHEEL2, lg4ff_wheel_effects, 40, 270, शून्यपूर्ण,
	अणुUSB_DEVICE_ID_LOGITECH_WII_WHEEL,   lg4ff_wheel_effects, 40, 270, शून्यपूर्ण
पूर्ण;

अटल स्थिर काष्ठा lg4ff_multimode_wheel lg4ff_multimode_wheels[] = अणु
	अणुUSB_DEVICE_ID_LOGITECH_DFP_WHEEL,
	 LG4FF_MODE_NATIVE | LG4FF_MODE_DFP | LG4FF_MODE_DFEX,
	 LG4FF_DFP_TAG, LG4FF_DFP_NAMEपूर्ण,
	अणुUSB_DEVICE_ID_LOGITECH_G25_WHEEL,
	 LG4FF_MODE_NATIVE | LG4FF_MODE_G25 | LG4FF_MODE_DFP | LG4FF_MODE_DFEX,
	 LG4FF_G25_TAG, LG4FF_G25_NAMEपूर्ण,
	अणुUSB_DEVICE_ID_LOGITECH_DFGT_WHEEL,
	 LG4FF_MODE_NATIVE | LG4FF_MODE_DFGT | LG4FF_MODE_DFP | LG4FF_MODE_DFEX,
	 LG4FF_DFGT_TAG, LG4FF_DFGT_NAMEपूर्ण,
	अणुUSB_DEVICE_ID_LOGITECH_G27_WHEEL,
	 LG4FF_MODE_NATIVE | LG4FF_MODE_G27 | LG4FF_MODE_G25 | LG4FF_MODE_DFP | LG4FF_MODE_DFEX,
	 LG4FF_G27_TAG, LG4FF_G27_NAMEपूर्ण,
	अणुUSB_DEVICE_ID_LOGITECH_G29_WHEEL,
	 LG4FF_MODE_NATIVE | LG4FF_MODE_G29 | LG4FF_MODE_G27 | LG4FF_MODE_G25 | LG4FF_MODE_DFGT | LG4FF_MODE_DFP | LG4FF_MODE_DFEX,
	 LG4FF_G29_TAG, LG4FF_G29_NAMEपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा lg4ff_alternate_mode lg4ff_alternate_modes[] = अणु
	[LG4FF_MODE_NATIVE_IDX] = अणु0, "native", ""पूर्ण,
	[LG4FF_MODE_DFEX_IDX] = अणुUSB_DEVICE_ID_LOGITECH_WHEEL, LG4FF_DFEX_TAG, LG4FF_DFEX_NAMEपूर्ण,
	[LG4FF_MODE_DFP_IDX] = अणुUSB_DEVICE_ID_LOGITECH_DFP_WHEEL, LG4FF_DFP_TAG, LG4FF_DFP_NAMEपूर्ण,
	[LG4FF_MODE_G25_IDX] = अणुUSB_DEVICE_ID_LOGITECH_G25_WHEEL, LG4FF_G25_TAG, LG4FF_G25_NAMEपूर्ण,
	[LG4FF_MODE_DFGT_IDX] = अणुUSB_DEVICE_ID_LOGITECH_DFGT_WHEEL, LG4FF_DFGT_TAG, LG4FF_DFGT_NAMEपूर्ण,
	[LG4FF_MODE_G27_IDX] = अणुUSB_DEVICE_ID_LOGITECH_G27_WHEEL, LG4FF_G27_TAG, LG4FF_G27_NAMEपूर्ण,
	[LG4FF_MODE_G29_IDX] = अणुUSB_DEVICE_ID_LOGITECH_G29_WHEEL, LG4FF_G29_TAG, LG4FF_G29_NAMEपूर्ण,
पूर्ण;

/* Multimode wheel identअगरicators */
अटल स्थिर काष्ठा lg4ff_wheel_ident_info lg4ff_dfp_ident_info = अणु
	LG4FF_MODE_DFP | LG4FF_MODE_DFEX,
	0xf000,
	0x1000,
	USB_DEVICE_ID_LOGITECH_DFP_WHEEL
पूर्ण;

अटल स्थिर काष्ठा lg4ff_wheel_ident_info lg4ff_g25_ident_info = अणु
	LG4FF_MODE_G25 | LG4FF_MODE_DFP | LG4FF_MODE_DFEX,
	0xff00,
	0x1200,
	USB_DEVICE_ID_LOGITECH_G25_WHEEL
पूर्ण;

अटल स्थिर काष्ठा lg4ff_wheel_ident_info lg4ff_g27_ident_info = अणु
	LG4FF_MODE_G27 | LG4FF_MODE_G25 | LG4FF_MODE_DFP | LG4FF_MODE_DFEX,
	0xfff0,
	0x1230,
	USB_DEVICE_ID_LOGITECH_G27_WHEEL
पूर्ण;

अटल स्थिर काष्ठा lg4ff_wheel_ident_info lg4ff_dfgt_ident_info = अणु
	LG4FF_MODE_DFGT | LG4FF_MODE_DFP | LG4FF_MODE_DFEX,
	0xff00,
	0x1300,
	USB_DEVICE_ID_LOGITECH_DFGT_WHEEL
पूर्ण;

अटल स्थिर काष्ठा lg4ff_wheel_ident_info lg4ff_g29_ident_info = अणु
	LG4FF_MODE_G29 | LG4FF_MODE_G27 | LG4FF_MODE_G25 | LG4FF_MODE_DFGT | LG4FF_MODE_DFP | LG4FF_MODE_DFEX,
	0xfff8,
	0x1350,
	USB_DEVICE_ID_LOGITECH_G29_WHEEL
पूर्ण;

अटल स्थिर काष्ठा lg4ff_wheel_ident_info lg4ff_g29_ident_info2 = अणु
	LG4FF_MODE_G29 | LG4FF_MODE_G27 | LG4FF_MODE_G25 | LG4FF_MODE_DFGT | LG4FF_MODE_DFP | LG4FF_MODE_DFEX,
	0xff00,
	0x8900,
	USB_DEVICE_ID_LOGITECH_G29_WHEEL
पूर्ण;

/* Multimode wheel identअगरication checklists */
अटल स्थिर काष्ठा lg4ff_wheel_ident_info *lg4ff_मुख्य_checklist[] = अणु
	&lg4ff_g29_ident_info,
	&lg4ff_g29_ident_info2,
	&lg4ff_dfgt_ident_info,
	&lg4ff_g27_ident_info,
	&lg4ff_g25_ident_info,
	&lg4ff_dfp_ident_info
पूर्ण;

/* Compatibility mode चयनing commands */
/* EXT_CMD9 - Understood by G27 and DFGT */
अटल स्थिर काष्ठा lg4ff_compat_mode_चयन lg4ff_mode_चयन_ext09_dfex = अणु
	2,
	अणु0xf8, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Revert mode upon USB reset */
	 0xf8, 0x09, 0x00, 0x01, 0x00, 0x00, 0x00पूर्ण	/* Switch mode to DF-EX with detach */
पूर्ण;

अटल स्थिर काष्ठा lg4ff_compat_mode_चयन lg4ff_mode_चयन_ext09_dfp = अणु
	2,
	अणु0xf8, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Revert mode upon USB reset */
	 0xf8, 0x09, 0x01, 0x01, 0x00, 0x00, 0x00पूर्ण	/* Switch mode to DFP with detach */
पूर्ण;

अटल स्थिर काष्ठा lg4ff_compat_mode_चयन lg4ff_mode_चयन_ext09_g25 = अणु
	2,
	अणु0xf8, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Revert mode upon USB reset */
	 0xf8, 0x09, 0x02, 0x01, 0x00, 0x00, 0x00पूर्ण	/* Switch mode to G25 with detach */
पूर्ण;

अटल स्थिर काष्ठा lg4ff_compat_mode_चयन lg4ff_mode_चयन_ext09_dfgt = अणु
	2,
	अणु0xf8, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Revert mode upon USB reset */
	 0xf8, 0x09, 0x03, 0x01, 0x00, 0x00, 0x00पूर्ण	/* Switch mode to DFGT with detach */
पूर्ण;

अटल स्थिर काष्ठा lg4ff_compat_mode_चयन lg4ff_mode_चयन_ext09_g27 = अणु
	2,
	अणु0xf8, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Revert mode upon USB reset */
	 0xf8, 0x09, 0x04, 0x01, 0x00, 0x00, 0x00पूर्ण	/* Switch mode to G27 with detach */
पूर्ण;

अटल स्थिर काष्ठा lg4ff_compat_mode_चयन lg4ff_mode_चयन_ext09_g29 = अणु
	2,
	अणु0xf8, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Revert mode upon USB reset */
	 0xf8, 0x09, 0x05, 0x01, 0x01, 0x00, 0x00पूर्ण	/* Switch mode to G29 with detach */
पूर्ण;

/* EXT_CMD1 - Understood by DFP, G25, G27 and DFGT */
अटल स्थिर काष्ठा lg4ff_compat_mode_चयन lg4ff_mode_चयन_ext01_dfp = अणु
	1,
	अणु0xf8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण
पूर्ण;

/* EXT_CMD16 - Understood by G25 and G27 */
अटल स्थिर काष्ठा lg4ff_compat_mode_चयन lg4ff_mode_चयन_ext16_g25 = अणु
	1,
	अणु0xf8, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण
पूर्ण;

/* Recalculates X axis value accordingly to currently selected range */
अटल s32 lg4ff_adjust_dfp_x_axis(s32 value, u16 range)
अणु
	u16 max_range;
	s32 new_value;

	अगर (range == 900)
		वापस value;
	अन्यथा अगर (range == 200)
		वापस value;
	अन्यथा अगर (range < 200)
		max_range = 200;
	अन्यथा
		max_range = 900;

	new_value = 8192 + mult_frac(value - 8192, max_range, range);
	अगर (new_value < 0)
		वापस 0;
	अन्यथा अगर (new_value > 16383)
		वापस 16383;
	अन्यथा
		वापस new_value;
पूर्ण

पूर्णांक lg4ff_adjust_input_event(काष्ठा hid_device *hid, काष्ठा hid_field *field,
			     काष्ठा hid_usage *usage, s32 value, काष्ठा lg_drv_data *drv_data)
अणु
	काष्ठा lg4ff_device_entry *entry = drv_data->device_props;
	s32 new_value = 0;

	अगर (!entry) अणु
		hid_err(hid, "Device properties not found");
		वापस 0;
	पूर्ण

	चयन (entry->wdata.product_id) अणु
	हाल USB_DEVICE_ID_LOGITECH_DFP_WHEEL:
		चयन (usage->code) अणु
		हाल ABS_X:
			new_value = lg4ff_adjust_dfp_x_axis(value, entry->wdata.range);
			input_event(field->hidinput->input, usage->type, usage->code, new_value);
			वापस 1;
		शेष:
			वापस 0;
		पूर्ण
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक lg4ff_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
		u8 *rd, पूर्णांक size, काष्ठा lg_drv_data *drv_data)
अणु
	पूर्णांक offset;
	काष्ठा lg4ff_device_entry *entry = drv_data->device_props;

	अगर (!entry)
		वापस 0;

	/* adjust HID report present combined pedals data */
	अगर (entry->wdata.combine) अणु
		चयन (entry->wdata.product_id) अणु
		हाल USB_DEVICE_ID_LOGITECH_WHEEL:
			rd[5] = rd[3];
			rd[6] = 0x7F;
			वापस 1;
		हाल USB_DEVICE_ID_LOGITECH_WINGMAN_FG:
		हाल USB_DEVICE_ID_LOGITECH_WINGMAN_FFG:
		हाल USB_DEVICE_ID_LOGITECH_MOMO_WHEEL:
		हाल USB_DEVICE_ID_LOGITECH_MOMO_WHEEL2:
			rd[4] = rd[3];
			rd[5] = 0x7F;
			वापस 1;
		हाल USB_DEVICE_ID_LOGITECH_DFP_WHEEL:
			rd[5] = rd[4];
			rd[6] = 0x7F;
			वापस 1;
		हाल USB_DEVICE_ID_LOGITECH_G25_WHEEL:
		हाल USB_DEVICE_ID_LOGITECH_G27_WHEEL:
			offset = 5;
			अवरोध;
		हाल USB_DEVICE_ID_LOGITECH_DFGT_WHEEL:
		हाल USB_DEVICE_ID_LOGITECH_G29_WHEEL:
			offset = 6;
			अवरोध;
		हाल USB_DEVICE_ID_LOGITECH_WII_WHEEL:
			offset = 3;
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण

		/* Compute a combined axis when wheel करोes not supply it */
		rd[offset] = (0xFF + rd[offset] - rd[offset+1]) >> 1;
		rd[offset+1] = 0x7F;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lg4ff_init_wheel_data(काष्ठा lg4ff_wheel_data * स्थिर wdata, स्थिर काष्ठा lg4ff_wheel *wheel,
				  स्थिर काष्ठा lg4ff_multimode_wheel *mmode_wheel,
				  स्थिर u16 real_product_id)
अणु
	u32 alternate_modes = 0;
	स्थिर अक्षर *real_tag = शून्य;
	स्थिर अक्षर *real_name = शून्य;

	अगर (mmode_wheel) अणु
		alternate_modes = mmode_wheel->alternate_modes;
		real_tag = mmode_wheel->real_tag;
		real_name = mmode_wheel->real_name;
	पूर्ण

	अणु
		काष्ठा lg4ff_wheel_data t_wdata =  अणु .product_id = wheel->product_id,
						     .real_product_id = real_product_id,
						     .combine = 0,
						     .min_range = wheel->min_range,
						     .max_range = wheel->max_range,
						     .set_range = wheel->set_range,
						     .alternate_modes = alternate_modes,
						     .real_tag = real_tag,
						     .real_name = real_name पूर्ण;

		स_नकल(wdata, &t_wdata, माप(t_wdata));
	पूर्ण
पूर्ण

अटल पूर्णांक lg4ff_play(काष्ठा input_dev *dev, व्योम *data, काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा lg4ff_device_entry *entry;
	काष्ठा lg_drv_data *drv_data;
	अचिन्हित दीर्घ flags;
	s32 *value;
	पूर्णांक x;

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Private driver data not found!\n");
		वापस -EINVAL;
	पूर्ण

	entry = drv_data->device_props;
	अगर (!entry) अणु
		hid_err(hid, "Device properties not found!\n");
		वापस -EINVAL;
	पूर्ण
	value = entry->report->field[0]->value;

#घोषणा CLAMP(x) करो अणु अगर (x < 0) x = 0; अन्यथा अगर (x > 0xff) x = 0xff; पूर्ण जबतक (0)

	चयन (effect->type) अणु
	हाल FF_CONSTANT:
		x = effect->u.ramp.start_level + 0x80;	/* 0x80 is no क्रमce */
		CLAMP(x);

		spin_lock_irqsave(&entry->report_lock, flags);
		अगर (x == 0x80) अणु
			/* De-activate क्रमce in slot-1*/
			value[0] = 0x13;
			value[1] = 0x00;
			value[2] = 0x00;
			value[3] = 0x00;
			value[4] = 0x00;
			value[5] = 0x00;
			value[6] = 0x00;

			hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);
			spin_unlock_irqrestore(&entry->report_lock, flags);
			वापस 0;
		पूर्ण

		value[0] = 0x11;	/* Slot 1 */
		value[1] = 0x08;
		value[2] = x;
		value[3] = 0x80;
		value[4] = 0x00;
		value[5] = 0x00;
		value[6] = 0x00;

		hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);
		spin_unlock_irqrestore(&entry->report_lock, flags);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* Sends शेष स्वतःcentering command compatible with
 * all wheels except Formula Force EX */
अटल व्योम lg4ff_set_स्वतःcenter_शेष(काष्ठा input_dev *dev, u16 magnitude)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	s32 *value;
	u32 expand_a, expand_b;
	काष्ठा lg4ff_device_entry *entry;
	काष्ठा lg_drv_data *drv_data;
	अचिन्हित दीर्घ flags;

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Private driver data not found!\n");
		वापस;
	पूर्ण

	entry = drv_data->device_props;
	अगर (!entry) अणु
		hid_err(hid, "Device properties not found!\n");
		वापस;
	पूर्ण
	value = entry->report->field[0]->value;

	/* De-activate Auto-Center */
	spin_lock_irqsave(&entry->report_lock, flags);
	अगर (magnitude == 0) अणु
		value[0] = 0xf5;
		value[1] = 0x00;
		value[2] = 0x00;
		value[3] = 0x00;
		value[4] = 0x00;
		value[5] = 0x00;
		value[6] = 0x00;

		hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);
		spin_unlock_irqrestore(&entry->report_lock, flags);
		वापस;
	पूर्ण

	अगर (magnitude <= 0xaaaa) अणु
		expand_a = 0x0c * magnitude;
		expand_b = 0x80 * magnitude;
	पूर्ण अन्यथा अणु
		expand_a = (0x0c * 0xaaaa) + 0x06 * (magnitude - 0xaaaa);
		expand_b = (0x80 * 0xaaaa) + 0xff * (magnitude - 0xaaaa);
	पूर्ण

	/* Adjust क्रम non-MOMO wheels */
	चयन (entry->wdata.product_id) अणु
	हाल USB_DEVICE_ID_LOGITECH_MOMO_WHEEL:
	हाल USB_DEVICE_ID_LOGITECH_MOMO_WHEEL2:
		अवरोध;
	शेष:
		expand_a = expand_a >> 1;
		अवरोध;
	पूर्ण

	value[0] = 0xfe;
	value[1] = 0x0d;
	value[2] = expand_a / 0xaaaa;
	value[3] = expand_a / 0xaaaa;
	value[4] = expand_b / 0xaaaa;
	value[5] = 0x00;
	value[6] = 0x00;

	hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);

	/* Activate Auto-Center */
	value[0] = 0x14;
	value[1] = 0x00;
	value[2] = 0x00;
	value[3] = 0x00;
	value[4] = 0x00;
	value[5] = 0x00;
	value[6] = 0x00;

	hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&entry->report_lock, flags);
पूर्ण

/* Sends स्वतःcentering command compatible with Formula Force EX */
अटल व्योम lg4ff_set_स्वतःcenter_ffex(काष्ठा input_dev *dev, u16 magnitude)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा lg4ff_device_entry *entry;
	काष्ठा lg_drv_data *drv_data;
	अचिन्हित दीर्घ flags;
	s32 *value;
	magnitude = magnitude * 90 / 65535;

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Private driver data not found!\n");
		वापस;
	पूर्ण

	entry = drv_data->device_props;
	अगर (!entry) अणु
		hid_err(hid, "Device properties not found!\n");
		वापस;
	पूर्ण
	value = entry->report->field[0]->value;

	spin_lock_irqsave(&entry->report_lock, flags);
	value[0] = 0xfe;
	value[1] = 0x03;
	value[2] = magnitude >> 14;
	value[3] = magnitude >> 14;
	value[4] = magnitude;
	value[5] = 0x00;
	value[6] = 0x00;

	hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&entry->report_lock, flags);
पूर्ण

/* Sends command to set range compatible with G25/G27/Driving Force GT */
अटल व्योम lg4ff_set_range_g25(काष्ठा hid_device *hid, u16 range)
अणु
	काष्ठा lg4ff_device_entry *entry;
	काष्ठा lg_drv_data *drv_data;
	अचिन्हित दीर्घ flags;
	s32 *value;

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Private driver data not found!\n");
		वापस;
	पूर्ण

	entry = drv_data->device_props;
	अगर (!entry) अणु
		hid_err(hid, "Device properties not found!\n");
		वापस;
	पूर्ण
	value = entry->report->field[0]->value;
	dbg_hid("G25/G27/DFGT: setting range to %u\n", range);

	spin_lock_irqsave(&entry->report_lock, flags);
	value[0] = 0xf8;
	value[1] = 0x81;
	value[2] = range & 0x00ff;
	value[3] = (range & 0xff00) >> 8;
	value[4] = 0x00;
	value[5] = 0x00;
	value[6] = 0x00;

	hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&entry->report_lock, flags);
पूर्ण

/* Sends commands to set range compatible with Driving Force Pro wheel */
अटल व्योम lg4ff_set_range_dfp(काष्ठा hid_device *hid, u16 range)
अणु
	काष्ठा lg4ff_device_entry *entry;
	काष्ठा lg_drv_data *drv_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक start_left, start_right, full_range;
	s32 *value;

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Private driver data not found!\n");
		वापस;
	पूर्ण

	entry = drv_data->device_props;
	अगर (!entry) अणु
		hid_err(hid, "Device properties not found!\n");
		वापस;
	पूर्ण
	value = entry->report->field[0]->value;
	dbg_hid("Driving Force Pro: setting range to %u\n", range);

	/* Prepare "coarse" limit command */
	spin_lock_irqsave(&entry->report_lock, flags);
	value[0] = 0xf8;
	value[1] = 0x00;	/* Set later */
	value[2] = 0x00;
	value[3] = 0x00;
	value[4] = 0x00;
	value[5] = 0x00;
	value[6] = 0x00;

	अगर (range > 200) अणु
		value[1] = 0x03;
		full_range = 900;
	पूर्ण अन्यथा अणु
		value[1] = 0x02;
		full_range = 200;
	पूर्ण
	hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);

	/* Prepare "fine" limit command */
	value[0] = 0x81;
	value[1] = 0x0b;
	value[2] = 0x00;
	value[3] = 0x00;
	value[4] = 0x00;
	value[5] = 0x00;
	value[6] = 0x00;

	अगर (range == 200 || range == 900) अणु	/* Do not apply any fine limit */
		hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);
		spin_unlock_irqrestore(&entry->report_lock, flags);
		वापस;
	पूर्ण

	/* Conकाष्ठा fine limit command */
	start_left = (((full_range - range + 1) * 2047) / full_range);
	start_right = 0xfff - start_left;

	value[2] = start_left >> 4;
	value[3] = start_right >> 4;
	value[4] = 0xff;
	value[5] = (start_right & 0xe) << 4 | (start_left & 0xe);
	value[6] = 0xff;

	hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&entry->report_lock, flags);
पूर्ण

अटल स्थिर काष्ठा lg4ff_compat_mode_चयन *lg4ff_get_mode_चयन_command(स्थिर u16 real_product_id, स्थिर u16 target_product_id)
अणु
	चयन (real_product_id) अणु
	हाल USB_DEVICE_ID_LOGITECH_DFP_WHEEL:
		चयन (target_product_id) अणु
		हाल USB_DEVICE_ID_LOGITECH_DFP_WHEEL:
			वापस &lg4ff_mode_चयन_ext01_dfp;
		/* DFP can only be चयनed to its native mode */
		शेष:
			वापस शून्य;
		पूर्ण
		अवरोध;
	हाल USB_DEVICE_ID_LOGITECH_G25_WHEEL:
		चयन (target_product_id) अणु
		हाल USB_DEVICE_ID_LOGITECH_DFP_WHEEL:
			वापस &lg4ff_mode_चयन_ext01_dfp;
		हाल USB_DEVICE_ID_LOGITECH_G25_WHEEL:
			वापस &lg4ff_mode_चयन_ext16_g25;
		/* G25 can only be चयनed to DFP mode or its native mode */
		शेष:
			वापस शून्य;
		पूर्ण
		अवरोध;
	हाल USB_DEVICE_ID_LOGITECH_G27_WHEEL:
		चयन (target_product_id) अणु
		हाल USB_DEVICE_ID_LOGITECH_WHEEL:
			वापस &lg4ff_mode_चयन_ext09_dfex;
		हाल USB_DEVICE_ID_LOGITECH_DFP_WHEEL:
			वापस &lg4ff_mode_चयन_ext09_dfp;
		हाल USB_DEVICE_ID_LOGITECH_G25_WHEEL:
			वापस &lg4ff_mode_चयन_ext09_g25;
		हाल USB_DEVICE_ID_LOGITECH_G27_WHEEL:
			वापस &lg4ff_mode_चयन_ext09_g27;
		/* G27 can only be चयनed to DF-EX, DFP, G25 or its native mode */
		शेष:
			वापस शून्य;
		पूर्ण
		अवरोध;
	हाल USB_DEVICE_ID_LOGITECH_G29_WHEEL:
		चयन (target_product_id) अणु
		हाल USB_DEVICE_ID_LOGITECH_DFP_WHEEL:
			वापस &lg4ff_mode_चयन_ext09_dfp;
		हाल USB_DEVICE_ID_LOGITECH_DFGT_WHEEL:
			वापस &lg4ff_mode_चयन_ext09_dfgt;
		हाल USB_DEVICE_ID_LOGITECH_G25_WHEEL:
			वापस &lg4ff_mode_चयन_ext09_g25;
		हाल USB_DEVICE_ID_LOGITECH_G27_WHEEL:
			वापस &lg4ff_mode_चयन_ext09_g27;
		हाल USB_DEVICE_ID_LOGITECH_G29_WHEEL:
			वापस &lg4ff_mode_चयन_ext09_g29;
		/* G29 can only be चयनed to DF-EX, DFP, DFGT, G25, G27 or its native mode */
		शेष:
			वापस शून्य;
		पूर्ण
		अवरोध;
	हाल USB_DEVICE_ID_LOGITECH_DFGT_WHEEL:
		चयन (target_product_id) अणु
		हाल USB_DEVICE_ID_LOGITECH_WHEEL:
			वापस &lg4ff_mode_चयन_ext09_dfex;
		हाल USB_DEVICE_ID_LOGITECH_DFP_WHEEL:
			वापस &lg4ff_mode_चयन_ext09_dfp;
		हाल USB_DEVICE_ID_LOGITECH_DFGT_WHEEL:
			वापस &lg4ff_mode_चयन_ext09_dfgt;
		/* DFGT can only be चयनed to DF-EX, DFP or its native mode */
		शेष:
			वापस शून्य;
		पूर्ण
		अवरोध;
	/* No other wheels have multiple modes */
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक lg4ff_चयन_compatibility_mode(काष्ठा hid_device *hid, स्थिर काष्ठा lg4ff_compat_mode_चयन *s)
अणु
	काष्ठा lg4ff_device_entry *entry;
	काष्ठा lg_drv_data *drv_data;
	अचिन्हित दीर्घ flags;
	s32 *value;
	u8 i;

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Private driver data not found!\n");
		वापस -EINVAL;
	पूर्ण

	entry = drv_data->device_props;
	अगर (!entry) अणु
		hid_err(hid, "Device properties not found!\n");
		वापस -EINVAL;
	पूर्ण
	value = entry->report->field[0]->value;

	spin_lock_irqsave(&entry->report_lock, flags);
	क्रम (i = 0; i < s->cmd_count; i++) अणु
		u8 j;

		क्रम (j = 0; j < 7; j++)
			value[j] = s->cmd[j + (7*i)];

		hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);
	पूर्ण
	spin_unlock_irqrestore(&entry->report_lock, flags);
	hid_hw_रुको(hid);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार lg4ff_alternate_modes_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा lg4ff_device_entry *entry;
	काष्ठा lg_drv_data *drv_data;
	sमाप_प्रकार count = 0;
	पूर्णांक i;

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Private driver data not found!\n");
		वापस 0;
	पूर्ण

	entry = drv_data->device_props;
	अगर (!entry) अणु
		hid_err(hid, "Device properties not found!\n");
		वापस 0;
	पूर्ण

	अगर (!entry->wdata.real_name) अणु
		hid_err(hid, "NULL pointer to string\n");
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < LG4FF_MODE_MAX_IDX; i++) अणु
		अगर (entry->wdata.alternate_modes & BIT(i)) अणु
			/* Prपूर्णांक tag and full name */
			count += scnम_लिखो(buf + count, PAGE_SIZE - count, "%s: %s",
					   lg4ff_alternate_modes[i].tag,
					   !lg4ff_alternate_modes[i].product_id ? entry->wdata.real_name : lg4ff_alternate_modes[i].name);
			अगर (count >= PAGE_SIZE - 1)
				वापस count;

			/* Mark the currently active mode with an asterisk */
			अगर (lg4ff_alternate_modes[i].product_id == entry->wdata.product_id ||
			    (lg4ff_alternate_modes[i].product_id == 0 && entry->wdata.product_id == entry->wdata.real_product_id))
				count += scnम_लिखो(buf + count, PAGE_SIZE - count, " *\n");
			अन्यथा
				count += scnम_लिखो(buf + count, PAGE_SIZE - count, "\n");

			अगर (count >= PAGE_SIZE - 1)
				वापस count;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार lg4ff_alternate_modes_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा lg4ff_device_entry *entry;
	काष्ठा lg_drv_data *drv_data;
	स्थिर काष्ठा lg4ff_compat_mode_चयन *s;
	u16 target_product_id = 0;
	पूर्णांक i, ret;
	अक्षर *lbuf;

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Private driver data not found!\n");
		वापस -EINVAL;
	पूर्ण

	entry = drv_data->device_props;
	अगर (!entry) अणु
		hid_err(hid, "Device properties not found!\n");
		वापस -EINVAL;
	पूर्ण

	/* Allow \न at the end of the input parameter */
	lbuf = kaप्र_लिखो(GFP_KERNEL, "%s", buf);
	अगर (!lbuf)
		वापस -ENOMEM;

	i = म_माप(lbuf);
	अगर (lbuf[i-1] == '\n') अणु
		अगर (i == 1) अणु
			kमुक्त(lbuf);
			वापस -EINVAL;
		पूर्ण
		lbuf[i-1] = '\0';
	पूर्ण

	क्रम (i = 0; i < LG4FF_MODE_MAX_IDX; i++) अणु
		स्थिर u16 mode_product_id = lg4ff_alternate_modes[i].product_id;
		स्थिर अक्षर *tag = lg4ff_alternate_modes[i].tag;

		अगर (entry->wdata.alternate_modes & BIT(i)) अणु
			अगर (!म_भेद(tag, lbuf)) अणु
				अगर (!mode_product_id)
					target_product_id = entry->wdata.real_product_id;
				अन्यथा
					target_product_id = mode_product_id;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (i == LG4FF_MODE_MAX_IDX) अणु
		hid_info(hid, "Requested mode \"%s\" is not supported by the device\n", lbuf);
		kमुक्त(lbuf);
		वापस -EINVAL;
	पूर्ण
	kमुक्त(lbuf); /* Not needed anymore */

	अगर (target_product_id == entry->wdata.product_id) /* Nothing to करो */
		वापस count;

	/* Automatic चयनing has to be disabled क्रम the चयन to DF-EX mode to work correctly */
	अगर (target_product_id == USB_DEVICE_ID_LOGITECH_WHEEL && !lg4ff_no_स्वतःचयन) अणु
		hid_info(hid, "\"%s\" cannot be switched to \"DF-EX\" mode. Load the \"hid_logitech\" module with \"lg4ff_no_autoswitch=1\" parameter set and try again\n",
			 entry->wdata.real_name);
		वापस -EINVAL;
	पूर्ण

	/* Take care of hardware limitations */
	अगर ((entry->wdata.real_product_id == USB_DEVICE_ID_LOGITECH_DFP_WHEEL || entry->wdata.real_product_id == USB_DEVICE_ID_LOGITECH_G25_WHEEL) &&
	    entry->wdata.product_id > target_product_id) अणु
		hid_info(hid, "\"%s\" cannot be switched back into \"%s\" mode\n", entry->wdata.real_name, lg4ff_alternate_modes[i].name);
		वापस -EINVAL;
	पूर्ण

	s = lg4ff_get_mode_चयन_command(entry->wdata.real_product_id, target_product_id);
	अगर (!s) अणु
		hid_err(hid, "Invalid target product ID %X\n", target_product_id);
		वापस -EINVAL;
	पूर्ण

	ret = lg4ff_चयन_compatibility_mode(hid, s);
	वापस (ret == 0 ? count : ret);
पूर्ण
अटल DEVICE_ATTR(alternate_modes, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH, lg4ff_alternate_modes_show, lg4ff_alternate_modes_store);

अटल sमाप_प्रकार lg4ff_combine_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा lg4ff_device_entry *entry;
	काष्ठा lg_drv_data *drv_data;
	माप_प्रकार count;

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Private driver data not found!\n");
		वापस 0;
	पूर्ण

	entry = drv_data->device_props;
	अगर (!entry) अणु
		hid_err(hid, "Device properties not found!\n");
		वापस 0;
	पूर्ण

	count = scnम_लिखो(buf, PAGE_SIZE, "%u\n", entry->wdata.combine);
	वापस count;
पूर्ण

अटल sमाप_प्रकार lg4ff_combine_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा lg4ff_device_entry *entry;
	काष्ठा lg_drv_data *drv_data;
	u16 combine = simple_म_से_अदीर्घ(buf, शून्य, 10);

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Private driver data not found!\n");
		वापस -EINVAL;
	पूर्ण

	entry = drv_data->device_props;
	अगर (!entry) अणु
		hid_err(hid, "Device properties not found!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (combine > 1)
		combine = 1;

	entry->wdata.combine = combine;
	वापस count;
पूर्ण
अटल DEVICE_ATTR(combine_pedals, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH, lg4ff_combine_show, lg4ff_combine_store);

/* Export the currently set range of the wheel */
अटल sमाप_प्रकार lg4ff_range_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा lg4ff_device_entry *entry;
	काष्ठा lg_drv_data *drv_data;
	माप_प्रकार count;

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Private driver data not found!\n");
		वापस 0;
	पूर्ण

	entry = drv_data->device_props;
	अगर (!entry) अणु
		hid_err(hid, "Device properties not found!\n");
		वापस 0;
	पूर्ण

	count = scnम_लिखो(buf, PAGE_SIZE, "%u\n", entry->wdata.range);
	वापस count;
पूर्ण

/* Set range to user specअगरied value, call appropriate function
 * according to the type of the wheel */
अटल sमाप_प्रकार lg4ff_range_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा lg4ff_device_entry *entry;
	काष्ठा lg_drv_data *drv_data;
	u16 range = simple_म_से_अदीर्घ(buf, शून्य, 10);

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Private driver data not found!\n");
		वापस -EINVAL;
	पूर्ण

	entry = drv_data->device_props;
	अगर (!entry) अणु
		hid_err(hid, "Device properties not found!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (range == 0)
		range = entry->wdata.max_range;

	/* Check अगर the wheel supports range setting
	 * and that the range is within limits क्रम the wheel */
	अगर (entry->wdata.set_range && range >= entry->wdata.min_range && range <= entry->wdata.max_range) अणु
		entry->wdata.set_range(hid, range);
		entry->wdata.range = range;
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR(range, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH, lg4ff_range_show, lg4ff_range_store);

अटल sमाप_प्रकार lg4ff_real_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा lg4ff_device_entry *entry;
	काष्ठा lg_drv_data *drv_data;
	माप_प्रकार count;

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Private driver data not found!\n");
		वापस 0;
	पूर्ण

	entry = drv_data->device_props;
	अगर (!entry) अणु
		hid_err(hid, "Device properties not found!\n");
		वापस 0;
	पूर्ण

	अगर (!entry->wdata.real_tag || !entry->wdata.real_name) अणु
		hid_err(hid, "NULL pointer to string\n");
		वापस 0;
	पूर्ण

	count = scnम_लिखो(buf, PAGE_SIZE, "%s: %s\n", entry->wdata.real_tag, entry->wdata.real_name);
	वापस count;
पूर्ण

अटल sमाप_प्रकार lg4ff_real_id_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	/* Real ID is a पढ़ो-only value */
	वापस -EPERM;
पूर्ण
अटल DEVICE_ATTR(real_id, S_IRUGO, lg4ff_real_id_show, lg4ff_real_id_store);

#अगर_घोषित CONFIG_LEDS_CLASS
अटल व्योम lg4ff_set_leds(काष्ठा hid_device *hid, u8 leds)
अणु
	काष्ठा lg_drv_data *drv_data;
	काष्ठा lg4ff_device_entry *entry;
	अचिन्हित दीर्घ flags;
	s32 *value;

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Private driver data not found!\n");
		वापस;
	पूर्ण

	entry = drv_data->device_props;
	अगर (!entry) अणु
		hid_err(hid, "Device properties not found!\n");
		वापस;
	पूर्ण
	value = entry->report->field[0]->value;

	spin_lock_irqsave(&entry->report_lock, flags);
	value[0] = 0xf8;
	value[1] = 0x12;
	value[2] = leds;
	value[3] = 0x00;
	value[4] = 0x00;
	value[5] = 0x00;
	value[6] = 0x00;
	hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&entry->report_lock, flags);
पूर्ण

अटल व्योम lg4ff_led_set_brightness(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness value)
अणु
	काष्ठा device *dev = led_cdev->dev->parent;
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा lg_drv_data *drv_data = hid_get_drvdata(hid);
	काष्ठा lg4ff_device_entry *entry;
	पूर्णांक i, state = 0;

	अगर (!drv_data) अणु
		hid_err(hid, "Device data not found.");
		वापस;
	पूर्ण

	entry = drv_data->device_props;

	अगर (!entry) अणु
		hid_err(hid, "Device properties not found.");
		वापस;
	पूर्ण

	क्रम (i = 0; i < 5; i++) अणु
		अगर (led_cdev != entry->wdata.led[i])
			जारी;
		state = (entry->wdata.led_state >> i) & 1;
		अगर (value == LED_OFF && state) अणु
			entry->wdata.led_state &= ~(1 << i);
			lg4ff_set_leds(hid, entry->wdata.led_state);
		पूर्ण अन्यथा अगर (value != LED_OFF && !state) अणु
			entry->wdata.led_state |= 1 << i;
			lg4ff_set_leds(hid, entry->wdata.led_state);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत led_brightness lg4ff_led_get_brightness(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा device *dev = led_cdev->dev->parent;
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा lg_drv_data *drv_data = hid_get_drvdata(hid);
	काष्ठा lg4ff_device_entry *entry;
	पूर्णांक i, value = 0;

	अगर (!drv_data) अणु
		hid_err(hid, "Device data not found.");
		वापस LED_OFF;
	पूर्ण

	entry = drv_data->device_props;

	अगर (!entry) अणु
		hid_err(hid, "Device properties not found.");
		वापस LED_OFF;
	पूर्ण

	क्रम (i = 0; i < 5; i++)
		अगर (led_cdev == entry->wdata.led[i]) अणु
			value = (entry->wdata.led_state >> i) & 1;
			अवरोध;
		पूर्ण

	वापस value ? LED_FULL : LED_OFF;
पूर्ण
#पूर्ण_अगर

अटल u16 lg4ff_identअगरy_multimode_wheel(काष्ठा hid_device *hid, स्थिर u16 reported_product_id, स्थिर u16 bcdDevice)
अणु
	u32 current_mode;
	पूर्णांक i;

	/* identअगरy current mode from USB PID */
	क्रम (i = 1; i < ARRAY_SIZE(lg4ff_alternate_modes); i++) अणु
		dbg_hid("Testing whether PID is %X\n", lg4ff_alternate_modes[i].product_id);
		अगर (reported_product_id == lg4ff_alternate_modes[i].product_id)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(lg4ff_alternate_modes))
		वापस 0;

	current_mode = BIT(i);

	क्रम (i = 0; i < ARRAY_SIZE(lg4ff_मुख्य_checklist); i++) अणु
		स्थिर u16 mask = lg4ff_मुख्य_checklist[i]->mask;
		स्थिर u16 result = lg4ff_मुख्य_checklist[i]->result;
		स्थिर u16 real_product_id = lg4ff_मुख्य_checklist[i]->real_product_id;

		अगर ((current_mode & lg4ff_मुख्य_checklist[i]->modes) && \
				(bcdDevice & mask) == result) अणु
			dbg_hid("Found wheel with real PID %X whose reported PID is %X\n", real_product_id, reported_product_id);
			वापस real_product_id;
		पूर्ण
	पूर्ण

	/* No match found. This is either Driving Force or an unknown
	 * wheel model, करो not touch it */
	dbg_hid("Wheel with bcdDevice %X was not recognized as multimode wheel, leaving in its current mode\n", bcdDevice);
	वापस 0;
पूर्ण

अटल पूर्णांक lg4ff_handle_multimode_wheel(काष्ठा hid_device *hid, u16 *real_product_id, स्थिर u16 bcdDevice)
अणु
	स्थिर u16 reported_product_id = hid->product;
	पूर्णांक ret;

	*real_product_id = lg4ff_identअगरy_multimode_wheel(hid, reported_product_id, bcdDevice);
	/* Probed wheel is not a multimode wheel */
	अगर (!*real_product_id) अणु
		*real_product_id = reported_product_id;
		dbg_hid("Wheel is not a multimode wheel\n");
		वापस LG4FF_MMODE_NOT_MULTIMODE;
	पूर्ण

	/* Switch from "Driving Force" mode to native mode स्वतःmatically.
	 * Otherwise keep the wheel in its current mode */
	अगर (reported_product_id == USB_DEVICE_ID_LOGITECH_WHEEL &&
	    reported_product_id != *real_product_id &&
	    !lg4ff_no_स्वतःचयन) अणु
		स्थिर काष्ठा lg4ff_compat_mode_चयन *s = lg4ff_get_mode_चयन_command(*real_product_id, *real_product_id);

		अगर (!s) अणु
			hid_err(hid, "Invalid product id %X\n", *real_product_id);
			वापस LG4FF_MMODE_NOT_MULTIMODE;
		पूर्ण

		ret = lg4ff_चयन_compatibility_mode(hid, s);
		अगर (ret) अणु
			/* Wheel could not have been चयनed to native mode,
			 * leave it in "Driving Force" mode and जारी */
			hid_err(hid, "Unable to switch wheel mode, errno %d\n", ret);
			वापस LG4FF_MMODE_IS_MULTIMODE;
		पूर्ण
		वापस LG4FF_MMODE_SWITCHED;
	पूर्ण

	वापस LG4FF_MMODE_IS_MULTIMODE;
पूर्ण


पूर्णांक lg4ff_init(काष्ठा hid_device *hid)
अणु
	काष्ठा hid_input *hidinput;
	काष्ठा input_dev *dev;
	काष्ठा list_head *report_list = &hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	काष्ठा hid_report *report = list_entry(report_list->next, काष्ठा hid_report, list);
	स्थिर काष्ठा usb_device_descriptor *udesc = &(hid_to_usb_dev(hid)->descriptor);
	स्थिर u16 bcdDevice = le16_to_cpu(udesc->bcdDevice);
	स्थिर काष्ठा lg4ff_multimode_wheel *mmode_wheel = शून्य;
	काष्ठा lg4ff_device_entry *entry;
	काष्ठा lg_drv_data *drv_data;
	पूर्णांक error, i, j;
	पूर्णांक mmode_ret, mmode_idx = -1;
	u16 real_product_id;

	अगर (list_empty(&hid->inमाला_दो)) अणु
		hid_err(hid, "no inputs found\n");
		वापस -ENODEV;
	पूर्ण
	hidinput = list_entry(hid->inमाला_दो.next, काष्ठा hid_input, list);
	dev = hidinput->input;

	/* Check that the report looks ok */
	अगर (!hid_validate_values(hid, HID_OUTPUT_REPORT, 0, 0, 7))
		वापस -1;

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Cannot add device, private driver data not allocated\n");
		वापस -1;
	पूर्ण
	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;
	spin_lock_init(&entry->report_lock);
	entry->report = report;
	drv_data->device_props = entry;

	/* Check अगर a multimode wheel has been connected and
	 * handle it appropriately */
	mmode_ret = lg4ff_handle_multimode_wheel(hid, &real_product_id, bcdDevice);

	/* Wheel has been told to चयन to native mode. There is no poपूर्णांक in going on
	 * with the initialization as the wheel will करो a USB reset when it चयनes mode
	 */
	अगर (mmode_ret == LG4FF_MMODE_SWITCHED)
		वापस 0;
	अन्यथा अगर (mmode_ret < 0) अणु
		hid_err(hid, "Unable to switch device mode during initialization, errno %d\n", mmode_ret);
		error = mmode_ret;
		जाओ err_init;
	पूर्ण

	/* Check what wheel has been connected */
	क्रम (i = 0; i < ARRAY_SIZE(lg4ff_devices); i++) अणु
		अगर (hid->product == lg4ff_devices[i].product_id) अणु
			dbg_hid("Found compatible device, product ID %04X\n", lg4ff_devices[i].product_id);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(lg4ff_devices)) अणु
		hid_err(hid, "This device is flagged to be handled by the lg4ff module but this module does not know how to handle it. "
			     "Please report this as a bug to LKML, Simon Wood <simon@mungewell.org> or "
			     "Michal Maly <madcatxster@devoid-pointer.net>\n");
		error = -1;
		जाओ err_init;
	पूर्ण

	अगर (mmode_ret == LG4FF_MMODE_IS_MULTIMODE) अणु
		क्रम (mmode_idx = 0; mmode_idx < ARRAY_SIZE(lg4ff_multimode_wheels); mmode_idx++) अणु
			अगर (real_product_id == lg4ff_multimode_wheels[mmode_idx].product_id)
				अवरोध;
		पूर्ण

		अगर (mmode_idx == ARRAY_SIZE(lg4ff_multimode_wheels)) अणु
			hid_err(hid, "Device product ID %X is not listed as a multimode wheel", real_product_id);
			error = -1;
			जाओ err_init;
		पूर्ण
	पूर्ण

	/* Set supported क्रमce feedback capabilities */
	क्रम (j = 0; lg4ff_devices[i].ff_effects[j] >= 0; j++)
		set_bit(lg4ff_devices[i].ff_effects[j], dev->ffbit);

	error = input_ff_create_memless(dev, शून्य, lg4ff_play);

	अगर (error)
		जाओ err_init;

	/* Initialize device properties */
	अगर (mmode_ret == LG4FF_MMODE_IS_MULTIMODE) अणु
		BUG_ON(mmode_idx == -1);
		mmode_wheel = &lg4ff_multimode_wheels[mmode_idx];
	पूर्ण
	lg4ff_init_wheel_data(&entry->wdata, &lg4ff_devices[i], mmode_wheel, real_product_id);

	/* Check अगर स्वतःcentering is available and
	 * set the centering क्रमce to zero by शेष */
	अगर (test_bit(FF_AUTOCENTER, dev->ffbit)) अणु
		/* Formula Force EX expects dअगरferent स्वतःcentering command */
		अगर ((bcdDevice >> 8) == LG4FF_FFEX_REV_MAJ &&
		    (bcdDevice & 0xff) == LG4FF_FFEX_REV_MIN)
			dev->ff->set_स्वतःcenter = lg4ff_set_स्वतःcenter_ffex;
		अन्यथा
			dev->ff->set_स्वतःcenter = lg4ff_set_स्वतःcenter_शेष;

		dev->ff->set_स्वतःcenter(dev, 0);
	पूर्ण

	/* Create sysfs पूर्णांकerface */
	error = device_create_file(&hid->dev, &dev_attr_combine_pedals);
	अगर (error)
		hid_warn(hid, "Unable to create sysfs interface for \"combine\", errno %d\n", error);
	error = device_create_file(&hid->dev, &dev_attr_range);
	अगर (error)
		hid_warn(hid, "Unable to create sysfs interface for \"range\", errno %d\n", error);
	अगर (mmode_ret == LG4FF_MMODE_IS_MULTIMODE) अणु
		error = device_create_file(&hid->dev, &dev_attr_real_id);
		अगर (error)
			hid_warn(hid, "Unable to create sysfs interface for \"real_id\", errno %d\n", error);
		error = device_create_file(&hid->dev, &dev_attr_alternate_modes);
		अगर (error)
			hid_warn(hid, "Unable to create sysfs interface for \"alternate_modes\", errno %d\n", error);
	पूर्ण
	dbg_hid("sysfs interface created\n");

	/* Set the maximum range to start with */
	entry->wdata.range = entry->wdata.max_range;
	अगर (entry->wdata.set_range)
		entry->wdata.set_range(hid, entry->wdata.range);

#अगर_घोषित CONFIG_LEDS_CLASS
	/* रेजिस्टर led subप्रणाली - G27/G29 only */
	entry->wdata.led_state = 0;
	क्रम (j = 0; j < 5; j++)
		entry->wdata.led[j] = शून्य;

	अगर (lg4ff_devices[i].product_id == USB_DEVICE_ID_LOGITECH_G27_WHEEL ||
			lg4ff_devices[i].product_id == USB_DEVICE_ID_LOGITECH_G29_WHEEL) अणु
		काष्ठा led_classdev *led;
		माप_प्रकार name_sz;
		अक्षर *name;

		lg4ff_set_leds(hid, 0);

		name_sz = म_माप(dev_name(&hid->dev)) + 8;

		क्रम (j = 0; j < 5; j++) अणु
			led = kzalloc(माप(काष्ठा led_classdev)+name_sz, GFP_KERNEL);
			अगर (!led) अणु
				hid_err(hid, "can't allocate memory for LED %d\n", j);
				जाओ err_leds;
			पूर्ण

			name = (व्योम *)(&led[1]);
			snम_लिखो(name, name_sz, "%s::RPM%d", dev_name(&hid->dev), j+1);
			led->name = name;
			led->brightness = 0;
			led->max_brightness = 1;
			led->brightness_get = lg4ff_led_get_brightness;
			led->brightness_set = lg4ff_led_set_brightness;

			entry->wdata.led[j] = led;
			error = led_classdev_रेजिस्टर(&hid->dev, led);

			अगर (error) अणु
				hid_err(hid, "failed to register LED %d. Aborting.\n", j);
err_leds:
				/* Deरेजिस्टर LEDs (अगर any) */
				क्रम (j = 0; j < 5; j++) अणु
					led = entry->wdata.led[j];
					entry->wdata.led[j] = शून्य;
					अगर (!led)
						जारी;
					led_classdev_unरेजिस्टर(led);
					kमुक्त(led);
				पूर्ण
				जाओ out;	/* Let the driver जारी without LEDs */
			पूर्ण
		पूर्ण
	पूर्ण
out:
#पूर्ण_अगर
	hid_info(hid, "Force feedback support for Logitech Gaming Wheels\n");
	वापस 0;

err_init:
	drv_data->device_props = शून्य;
	kमुक्त(entry);
	वापस error;
पूर्ण

पूर्णांक lg4ff_deinit(काष्ठा hid_device *hid)
अणु
	काष्ठा lg4ff_device_entry *entry;
	काष्ठा lg_drv_data *drv_data;

	drv_data = hid_get_drvdata(hid);
	अगर (!drv_data) अणु
		hid_err(hid, "Error while deinitializing device, no private driver data.\n");
		वापस -1;
	पूर्ण
	entry = drv_data->device_props;
	अगर (!entry)
		जाओ out; /* Nothing more to करो */

	/* Multimode devices will have at least the "MODE_NATIVE" bit set */
	अगर (entry->wdata.alternate_modes) अणु
		device_हटाओ_file(&hid->dev, &dev_attr_real_id);
		device_हटाओ_file(&hid->dev, &dev_attr_alternate_modes);
	पूर्ण

	device_हटाओ_file(&hid->dev, &dev_attr_combine_pedals);
	device_हटाओ_file(&hid->dev, &dev_attr_range);
#अगर_घोषित CONFIG_LEDS_CLASS
	अणु
		पूर्णांक j;
		काष्ठा led_classdev *led;

		/* Deरेजिस्टर LEDs (अगर any) */
		क्रम (j = 0; j < 5; j++) अणु

			led = entry->wdata.led[j];
			entry->wdata.led[j] = शून्य;
			अगर (!led)
				जारी;
			led_classdev_unरेजिस्टर(led);
			kमुक्त(led);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	drv_data->device_props = शून्य;

	kमुक्त(entry);
out:
	dbg_hid("Device successfully unregistered\n");
	वापस 0;
पूर्ण
