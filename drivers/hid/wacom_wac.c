<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/input/tablet/wacom_wac.c
 *
 *  USB Wacom tablet support - Wacom specअगरic code
 */

/*
 */

#समावेश "wacom_wac.h"
#समावेश "wacom.h"
#समावेश <linux/input/mt.h>

/* resolution क्रम penabled devices */
#घोषणा WACOM_PL_RES		20
#घोषणा WACOM_PENPRTN_RES	40
#घोषणा WACOM_VOLITO_RES	50
#घोषणा WACOM_GRAPHIRE_RES	80
#घोषणा WACOM_INTUOS_RES	100
#घोषणा WACOM_INTUOS3_RES	200

/* Newer Cपूर्णांकiq and DTU have an offset between tablet and screen areas */
#घोषणा WACOM_DTU_OFFSET	200
#घोषणा WACOM_CINTIQ_OFFSET	400

/*
 * Scale factor relating reported contact size to logical contact area.
 * 2^14/pi is a good approximation on Intuos5 and 3rd-gen Bamboo
 */
#घोषणा WACOM_CONTACT_AREA_SCALE 2607

अटल bool touch_arbitration = 1;
module_param(touch_arbitration, bool, 0644);
MODULE_PARM_DESC(touch_arbitration, " on (Y) off (N)");

अटल व्योम wacom_report_numbered_buttons(काष्ठा input_dev *input_dev,
				पूर्णांक button_count, पूर्णांक mask);

अटल पूर्णांक wacom_numbered_button_to_key(पूर्णांक n);

अटल व्योम wacom_update_led(काष्ठा wacom *wacom, पूर्णांक button_count, पूर्णांक mask,
			     पूर्णांक group);
/*
 * Percent of battery capacity क्रम Graphire.
 * 8th value means AC online and show 100% capacity.
 */
अटल अचिन्हित लघु batcap_gr[8] = अणु 1, 15, 25, 35, 50, 70, 100, 100 पूर्ण;

/*
 * Percent of battery capacity क्रम Intuos4 WL, AC has a separate bit.
 */
अटल अचिन्हित लघु batcap_i4[8] = अणु 1, 15, 30, 45, 60, 70, 85, 100 पूर्ण;

अटल व्योम __wacom_notअगरy_battery(काष्ठा wacom_battery *battery,
				   पूर्णांक bat_status, पूर्णांक bat_capacity,
				   bool bat_अक्षरging, bool bat_connected,
				   bool ps_connected)
अणु
	bool changed = battery->bat_status       != bat_status    ||
		       battery->battery_capacity != bat_capacity  ||
		       battery->bat_अक्षरging     != bat_अक्षरging  ||
		       battery->bat_connected    != bat_connected ||
		       battery->ps_connected     != ps_connected;

	अगर (changed) अणु
		battery->bat_status = bat_status;
		battery->battery_capacity = bat_capacity;
		battery->bat_अक्षरging = bat_अक्षरging;
		battery->bat_connected = bat_connected;
		battery->ps_connected = ps_connected;

		अगर (battery->battery)
			घातer_supply_changed(battery->battery);
	पूर्ण
पूर्ण

अटल व्योम wacom_notअगरy_battery(काष्ठा wacom_wac *wacom_wac,
	पूर्णांक bat_status, पूर्णांक bat_capacity, bool bat_अक्षरging,
	bool bat_connected, bool ps_connected)
अणु
	काष्ठा wacom *wacom = container_of(wacom_wac, काष्ठा wacom, wacom_wac);

	__wacom_notअगरy_battery(&wacom->battery, bat_status, bat_capacity,
			       bat_अक्षरging, bat_connected, ps_connected);
पूर्ण

अटल पूर्णांक wacom_penpartner_irq(काष्ठा wacom_wac *wacom)
अणु
	अचिन्हित अक्षर *data = wacom->data;
	काष्ठा input_dev *input = wacom->pen_input;

	चयन (data[0]) अणु
	हाल 1:
		अगर (data[5] & 0x80) अणु
			wacom->tool[0] = (data[5] & 0x20) ? BTN_TOOL_RUBBER : BTN_TOOL_PEN;
			wacom->id[0] = (data[5] & 0x20) ? ERASER_DEVICE_ID : STYLUS_DEVICE_ID;
			input_report_key(input, wacom->tool[0], 1);
			input_report_असल(input, ABS_MISC, wacom->id[0]); /* report tool id */
			input_report_असल(input, ABS_X, get_unaligned_le16(&data[1]));
			input_report_असल(input, ABS_Y, get_unaligned_le16(&data[3]));
			input_report_असल(input, ABS_PRESSURE, (चिन्हित अक्षर)data[6] + 127);
			input_report_key(input, BTN_TOUCH, ((चिन्हित अक्षर)data[6] > -127));
			input_report_key(input, BTN_STYLUS, (data[5] & 0x40));
		पूर्ण अन्यथा अणु
			input_report_key(input, wacom->tool[0], 0);
			input_report_असल(input, ABS_MISC, 0); /* report tool id */
			input_report_असल(input, ABS_PRESSURE, -1);
			input_report_key(input, BTN_TOUCH, 0);
		पूर्ण
		अवरोध;

	हाल 2:
		input_report_key(input, BTN_TOOL_PEN, 1);
		input_report_असल(input, ABS_MISC, STYLUS_DEVICE_ID); /* report tool id */
		input_report_असल(input, ABS_X, get_unaligned_le16(&data[1]));
		input_report_असल(input, ABS_Y, get_unaligned_le16(&data[3]));
		input_report_असल(input, ABS_PRESSURE, (चिन्हित अक्षर)data[6] + 127);
		input_report_key(input, BTN_TOUCH, ((चिन्हित अक्षर)data[6] > -80) && !(data[5] & 0x20));
		input_report_key(input, BTN_STYLUS, (data[5] & 0x40));
		अवरोध;

	शेष:
		dev_dbg(input->dev.parent,
			"%s: received unknown report #%d\n", __func__, data[0]);
		वापस 0;
        पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक wacom_pl_irq(काष्ठा wacom_wac *wacom)
अणु
	काष्ठा wacom_features *features = &wacom->features;
	अचिन्हित अक्षर *data = wacom->data;
	काष्ठा input_dev *input = wacom->pen_input;
	पूर्णांक prox, pressure;

	अगर (data[0] != WACOM_REPORT_PENABLED) अणु
		dev_dbg(input->dev.parent,
			"%s: received unknown report #%d\n", __func__, data[0]);
		वापस 0;
	पूर्ण

	prox = data[1] & 0x40;

	अगर (!wacom->id[0]) अणु
		अगर ((data[0] & 0x10) || (data[4] & 0x20)) अणु
			wacom->tool[0] = BTN_TOOL_RUBBER;
			wacom->id[0] = ERASER_DEVICE_ID;
		पूर्ण
		अन्यथा अणु
			wacom->tool[0] = BTN_TOOL_PEN;
			wacom->id[0] = STYLUS_DEVICE_ID;
		पूर्ण
	पूर्ण

	/* If the eraser is in prox, STYLUS2 is always set. If we
	 * mis-detected the type and notice that STYLUS2 isn't set
	 * then क्रमce the eraser out of prox and let the pen in.
	 */
	अगर (wacom->tool[0] == BTN_TOOL_RUBBER && !(data[4] & 0x20)) अणु
		input_report_key(input, BTN_TOOL_RUBBER, 0);
		input_report_असल(input, ABS_MISC, 0);
		input_sync(input);
		wacom->tool[0] = BTN_TOOL_PEN;
		wacom->id[0] = STYLUS_DEVICE_ID;
	पूर्ण

	अगर (prox) अणु
		pressure = (चिन्हित अक्षर)((data[7] << 1) | ((data[4] >> 2) & 1));
		अगर (features->pressure_max > 255)
			pressure = (pressure << 1) | ((data[4] >> 6) & 1);
		pressure += (features->pressure_max + 1) / 2;

		input_report_असल(input, ABS_X, data[3] | (data[2] << 7) | ((data[1] & 0x03) << 14));
		input_report_असल(input, ABS_Y, data[6] | (data[5] << 7) | ((data[4] & 0x03) << 14));
		input_report_असल(input, ABS_PRESSURE, pressure);

		input_report_key(input, BTN_TOUCH, data[4] & 0x08);
		input_report_key(input, BTN_STYLUS, data[4] & 0x10);
		/* Only allow the stylus2 button to be reported क्रम the pen tool. */
		input_report_key(input, BTN_STYLUS2, (wacom->tool[0] == BTN_TOOL_PEN) && (data[4] & 0x20));
	पूर्ण

	अगर (!prox)
		wacom->id[0] = 0;
	input_report_key(input, wacom->tool[0], prox);
	input_report_असल(input, ABS_MISC, wacom->id[0]);
	वापस 1;
पूर्ण

अटल पूर्णांक wacom_ptu_irq(काष्ठा wacom_wac *wacom)
अणु
	अचिन्हित अक्षर *data = wacom->data;
	काष्ठा input_dev *input = wacom->pen_input;

	अगर (data[0] != WACOM_REPORT_PENABLED) अणु
		dev_dbg(input->dev.parent,
			"%s: received unknown report #%d\n", __func__, data[0]);
		वापस 0;
	पूर्ण

	अगर (data[1] & 0x04) अणु
		input_report_key(input, BTN_TOOL_RUBBER, data[1] & 0x20);
		input_report_key(input, BTN_TOUCH, data[1] & 0x08);
		wacom->id[0] = ERASER_DEVICE_ID;
	पूर्ण अन्यथा अणु
		input_report_key(input, BTN_TOOL_PEN, data[1] & 0x20);
		input_report_key(input, BTN_TOUCH, data[1] & 0x01);
		wacom->id[0] = STYLUS_DEVICE_ID;
	पूर्ण
	input_report_असल(input, ABS_MISC, wacom->id[0]); /* report tool id */
	input_report_असल(input, ABS_X, le16_to_cpup((__le16 *)&data[2]));
	input_report_असल(input, ABS_Y, le16_to_cpup((__le16 *)&data[4]));
	input_report_असल(input, ABS_PRESSURE, le16_to_cpup((__le16 *)&data[6]));
	input_report_key(input, BTN_STYLUS, data[1] & 0x02);
	input_report_key(input, BTN_STYLUS2, data[1] & 0x10);
	वापस 1;
पूर्ण

अटल पूर्णांक wacom_dtu_irq(काष्ठा wacom_wac *wacom)
अणु
	अचिन्हित अक्षर *data = wacom->data;
	काष्ठा input_dev *input = wacom->pen_input;
	पूर्णांक prox = data[1] & 0x20;

	dev_dbg(input->dev.parent,
		"%s: received report #%d", __func__, data[0]);

	अगर (prox) अणु
		/* Going पूर्णांकo proximity select tool */
		wacom->tool[0] = (data[1] & 0x0c) ? BTN_TOOL_RUBBER : BTN_TOOL_PEN;
		अगर (wacom->tool[0] == BTN_TOOL_PEN)
			wacom->id[0] = STYLUS_DEVICE_ID;
		अन्यथा
			wacom->id[0] = ERASER_DEVICE_ID;
	पूर्ण
	input_report_key(input, BTN_STYLUS, data[1] & 0x02);
	input_report_key(input, BTN_STYLUS2, data[1] & 0x10);
	input_report_असल(input, ABS_X, le16_to_cpup((__le16 *)&data[2]));
	input_report_असल(input, ABS_Y, le16_to_cpup((__le16 *)&data[4]));
	input_report_असल(input, ABS_PRESSURE, ((data[7] & 0x01) << 8) | data[6]);
	input_report_key(input, BTN_TOUCH, data[1] & 0x05);
	अगर (!prox) /* out-prox */
		wacom->id[0] = 0;
	input_report_key(input, wacom->tool[0], prox);
	input_report_असल(input, ABS_MISC, wacom->id[0]);
	वापस 1;
पूर्ण

अटल पूर्णांक wacom_dtus_irq(काष्ठा wacom_wac *wacom)
अणु
	अचिन्हित अक्षर *data = wacom->data;
	काष्ठा input_dev *input = wacom->pen_input;
	अचिन्हित लघु prox, pressure = 0;

	अगर (data[0] != WACOM_REPORT_DTUS && data[0] != WACOM_REPORT_DTUSPAD) अणु
		dev_dbg(input->dev.parent,
			"%s: received unknown report #%d", __func__, data[0]);
		वापस 0;
	पूर्ण अन्यथा अगर (data[0] == WACOM_REPORT_DTUSPAD) अणु
		input = wacom->pad_input;
		input_report_key(input, BTN_0, (data[1] & 0x01));
		input_report_key(input, BTN_1, (data[1] & 0x02));
		input_report_key(input, BTN_2, (data[1] & 0x04));
		input_report_key(input, BTN_3, (data[1] & 0x08));
		input_report_असल(input, ABS_MISC,
				 data[1] & 0x0f ? PAD_DEVICE_ID : 0);
		वापस 1;
	पूर्ण अन्यथा अणु
		prox = data[1] & 0x80;
		अगर (prox) अणु
			चयन ((data[1] >> 3) & 3) अणु
			हाल 1: /* Rubber */
				wacom->tool[0] = BTN_TOOL_RUBBER;
				wacom->id[0] = ERASER_DEVICE_ID;
				अवरोध;

			हाल 2: /* Pen */
				wacom->tool[0] = BTN_TOOL_PEN;
				wacom->id[0] = STYLUS_DEVICE_ID;
				अवरोध;
			पूर्ण
		पूर्ण

		input_report_key(input, BTN_STYLUS, data[1] & 0x20);
		input_report_key(input, BTN_STYLUS2, data[1] & 0x40);
		input_report_असल(input, ABS_X, get_unaligned_be16(&data[3]));
		input_report_असल(input, ABS_Y, get_unaligned_be16(&data[5]));
		pressure = ((data[1] & 0x03) << 8) | (data[2] & 0xff);
		input_report_असल(input, ABS_PRESSURE, pressure);
		input_report_key(input, BTN_TOUCH, pressure > 10);

		अगर (!prox) /* out-prox */
			wacom->id[0] = 0;
		input_report_key(input, wacom->tool[0], prox);
		input_report_असल(input, ABS_MISC, wacom->id[0]);
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक wacom_graphire_irq(काष्ठा wacom_wac *wacom)
अणु
	काष्ठा wacom_features *features = &wacom->features;
	अचिन्हित अक्षर *data = wacom->data;
	काष्ठा input_dev *input = wacom->pen_input;
	काष्ठा input_dev *pad_input = wacom->pad_input;
	पूर्णांक battery_capacity, ps_connected;
	पूर्णांक prox;
	पूर्णांक rw = 0;
	पूर्णांक retval = 0;

	अगर (features->type == GRAPHIRE_BT) अणु
		अगर (data[0] != WACOM_REPORT_PENABLED_BT) अणु
			dev_dbg(input->dev.parent,
				"%s: received unknown report #%d\n", __func__,
				data[0]);
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अगर (data[0] != WACOM_REPORT_PENABLED) अणु
		dev_dbg(input->dev.parent,
			"%s: received unknown report #%d\n", __func__, data[0]);
		जाओ निकास;
	पूर्ण

	prox = data[1] & 0x80;
	अगर (prox || wacom->id[0]) अणु
		अगर (prox) अणु
			चयन ((data[1] >> 5) & 3) अणु

			हाल 0:	/* Pen */
				wacom->tool[0] = BTN_TOOL_PEN;
				wacom->id[0] = STYLUS_DEVICE_ID;
				अवरोध;

			हाल 1: /* Rubber */
				wacom->tool[0] = BTN_TOOL_RUBBER;
				wacom->id[0] = ERASER_DEVICE_ID;
				अवरोध;

			हाल 2: /* Mouse with wheel */
				input_report_key(input, BTN_MIDDLE, data[1] & 0x04);
				fallthrough;

			हाल 3: /* Mouse without wheel */
				wacom->tool[0] = BTN_TOOL_MOUSE;
				wacom->id[0] = CURSOR_DEVICE_ID;
				अवरोध;
			पूर्ण
		पूर्ण
		input_report_असल(input, ABS_X, le16_to_cpup((__le16 *)&data[2]));
		input_report_असल(input, ABS_Y, le16_to_cpup((__le16 *)&data[4]));
		अगर (wacom->tool[0] != BTN_TOOL_MOUSE) अणु
			अगर (features->type == GRAPHIRE_BT)
				input_report_असल(input, ABS_PRESSURE, data[6] |
					(((__u16) (data[1] & 0x08)) << 5));
			अन्यथा
				input_report_असल(input, ABS_PRESSURE, data[6] |
					((data[7] & 0x03) << 8));
			input_report_key(input, BTN_TOUCH, data[1] & 0x01);
			input_report_key(input, BTN_STYLUS, data[1] & 0x02);
			input_report_key(input, BTN_STYLUS2, data[1] & 0x04);
		पूर्ण अन्यथा अणु
			input_report_key(input, BTN_LEFT, data[1] & 0x01);
			input_report_key(input, BTN_RIGHT, data[1] & 0x02);
			अगर (features->type == WACOM_G4 ||
					features->type == WACOM_MO) अणु
				input_report_असल(input, ABS_DISTANCE, data[6] & 0x3f);
				rw = (data[7] & 0x04) - (data[7] & 0x03);
			पूर्ण अन्यथा अगर (features->type == GRAPHIRE_BT) अणु
				/* Compute distance between mouse and tablet */
				rw = 44 - (data[6] >> 2);
				rw = clamp_val(rw, 0, 31);
				input_report_असल(input, ABS_DISTANCE, rw);
				अगर (((data[1] >> 5) & 3) == 2) अणु
					/* Mouse with wheel */
					input_report_key(input, BTN_MIDDLE,
							data[1] & 0x04);
					rw = (data[6] & 0x01) ? -1 :
						(data[6] & 0x02) ? 1 : 0;
				पूर्ण अन्यथा अणु
					rw = 0;
				पूर्ण
			पूर्ण अन्यथा अणु
				input_report_असल(input, ABS_DISTANCE, data[7] & 0x3f);
				rw = -(चिन्हित अक्षर)data[6];
			पूर्ण
			input_report_rel(input, REL_WHEEL, rw);
		पूर्ण

		अगर (!prox)
			wacom->id[0] = 0;
		input_report_असल(input, ABS_MISC, wacom->id[0]); /* report tool id */
		input_report_key(input, wacom->tool[0], prox);
		input_sync(input); /* sync last event */
	पूर्ण

	/* send pad data */
	चयन (features->type) अणु
	हाल WACOM_G4:
		prox = data[7] & 0xf8;
		अगर (prox || wacom->id[1]) अणु
			wacom->id[1] = PAD_DEVICE_ID;
			input_report_key(pad_input, BTN_BACK, (data[7] & 0x40));
			input_report_key(pad_input, BTN_FORWARD, (data[7] & 0x80));
			rw = ((data[7] & 0x18) >> 3) - ((data[7] & 0x20) >> 3);
			input_report_rel(pad_input, REL_WHEEL, rw);
			अगर (!prox)
				wacom->id[1] = 0;
			input_report_असल(pad_input, ABS_MISC, wacom->id[1]);
			retval = 1;
		पूर्ण
		अवरोध;

	हाल WACOM_MO:
		prox = (data[7] & 0xf8) || data[8];
		अगर (prox || wacom->id[1]) अणु
			wacom->id[1] = PAD_DEVICE_ID;
			input_report_key(pad_input, BTN_BACK, (data[7] & 0x08));
			input_report_key(pad_input, BTN_LEFT, (data[7] & 0x20));
			input_report_key(pad_input, BTN_FORWARD, (data[7] & 0x10));
			input_report_key(pad_input, BTN_RIGHT, (data[7] & 0x40));
			input_report_असल(pad_input, ABS_WHEEL, (data[8] & 0x7f));
			अगर (!prox)
				wacom->id[1] = 0;
			input_report_असल(pad_input, ABS_MISC, wacom->id[1]);
			retval = 1;
		पूर्ण
		अवरोध;
	हाल GRAPHIRE_BT:
		prox = data[7] & 0x03;
		अगर (prox || wacom->id[1]) अणु
			wacom->id[1] = PAD_DEVICE_ID;
			input_report_key(pad_input, BTN_0, (data[7] & 0x02));
			input_report_key(pad_input, BTN_1, (data[7] & 0x01));
			अगर (!prox)
				wacom->id[1] = 0;
			input_report_असल(pad_input, ABS_MISC, wacom->id[1]);
			retval = 1;
		पूर्ण
		अवरोध;
	पूर्ण

	/* Store current battery capacity and घातer supply state */
	अगर (features->type == GRAPHIRE_BT) अणु
		rw = (data[7] >> 2 & 0x07);
		battery_capacity = batcap_gr[rw];
		ps_connected = rw == 7;
		wacom_notअगरy_battery(wacom, WACOM_POWER_SUPPLY_STATUS_AUTO,
				     battery_capacity, ps_connected, 1,
				     ps_connected);
	पूर्ण
निकास:
	वापस retval;
पूर्ण

अटल व्योम wacom_पूर्णांकuos_schedule_prox_event(काष्ठा wacom_wac *wacom_wac)
अणु
	काष्ठा wacom *wacom = container_of(wacom_wac, काष्ठा wacom, wacom_wac);
	काष्ठा wacom_features *features = &wacom_wac->features;
	काष्ठा hid_report *r;
	काष्ठा hid_report_क्रमागत *re;

	re = &(wacom->hdev->report_क्रमागत[HID_FEATURE_REPORT]);
	अगर (features->type == INTUOSHT2)
		r = re->report_id_hash[WACOM_REPORT_INTUOSHT2_ID];
	अन्यथा
		r = re->report_id_hash[WACOM_REPORT_INTUOS_ID1];
	अगर (r) अणु
		hid_hw_request(wacom->hdev, r, HID_REQ_GET_REPORT);
	पूर्ण
पूर्ण

अटल पूर्णांक wacom_पूर्णांकuos_pad(काष्ठा wacom_wac *wacom)
अणु
	काष्ठा wacom_features *features = &wacom->features;
	अचिन्हित अक्षर *data = wacom->data;
	काष्ठा input_dev *input = wacom->pad_input;
	पूर्णांक i;
	पूर्णांक buttons = 0, nbuttons = features->numbered_buttons;
	पूर्णांक keys = 0, nkeys = 0;
	पूर्णांक ring1 = 0, ring2 = 0;
	पूर्णांक strip1 = 0, strip2 = 0;
	bool prox = false;
	bool wrench = false, keyboard = false, mute_touch = false, menu = false,
	     info = false;

	/* pad packets. Works as a second tool and is always in prox */
	अगर (!(data[0] == WACOM_REPORT_INTUOSPAD || data[0] == WACOM_REPORT_INTUOS5PAD ||
	      data[0] == WACOM_REPORT_CINTIQPAD))
		वापस 0;

	अगर (features->type >= INTUOS4S && features->type <= INTUOS4L) अणु
		buttons = (data[3] << 1) | (data[2] & 0x01);
		ring1 = data[1];
	पूर्ण अन्यथा अगर (features->type == DTK) अणु
		buttons = data[6];
	पूर्ण अन्यथा अगर (features->type == WACOM_13HD) अणु
		buttons = (data[4] << 1) | (data[3] & 0x01);
	पूर्ण अन्यथा अगर (features->type == WACOM_24HD) अणु
		buttons = (data[8] << 8) | data[6];
		ring1 = data[1];
		ring2 = data[2];

		/*
		 * Three "buttons" are available on the 24HD which are
		 * physically implemented as a touchstrip. Each button
		 * is approximately 3 bits wide with a 2 bit spacing.
		 * The raw touchstrip bits are stored at:
		 *    ((data[3] & 0x1f) << 8) | data[4])
		 */
		nkeys = 3;
		keys = ((data[3] & 0x1C) ? 1<<2 : 0) |
		       ((data[4] & 0xE0) ? 1<<1 : 0) |
		       ((data[4] & 0x07) ? 1<<0 : 0);
		keyboard = !!(data[4] & 0xE0);
		info = !!(data[3] & 0x1C);

		अगर (features->oPid) अणु
			mute_touch = !!(data[4] & 0x07);
			अगर (mute_touch)
				wacom->shared->is_touch_on =
					!wacom->shared->is_touch_on;
		पूर्ण अन्यथा अणु
			wrench = !!(data[4] & 0x07);
		पूर्ण
	पूर्ण अन्यथा अगर (features->type == WACOM_27QHD) अणु
		nkeys = 3;
		keys = data[2] & 0x07;

		wrench = !!(data[2] & 0x01);
		keyboard = !!(data[2] & 0x02);

		अगर (features->oPid) अणु
			mute_touch = !!(data[2] & 0x04);
			अगर (mute_touch)
				wacom->shared->is_touch_on =
					!wacom->shared->is_touch_on;
		पूर्ण अन्यथा अणु
			menu = !!(data[2] & 0x04);
		पूर्ण
		input_report_असल(input, ABS_X, be16_to_cpup((__be16 *)&data[4]));
		input_report_असल(input, ABS_Y, be16_to_cpup((__be16 *)&data[6]));
		input_report_असल(input, ABS_Z, be16_to_cpup((__be16 *)&data[8]));
	पूर्ण अन्यथा अगर (features->type == CINTIQ_HYBRID) अणु
		/*
		 * Do not send hardware buttons under Android. They
		 * are alपढ़ोy sent to the प्रणाली through GPIO (and
		 * have dअगरferent meaning).
		 *
		 * d-pad right  -> data[4] & 0x10
		 * d-pad up     -> data[4] & 0x20
		 * d-pad left   -> data[4] & 0x40
		 * d-pad करोwn   -> data[4] & 0x80
		 * d-pad center -> data[3] & 0x01
		 */
		buttons = (data[4] << 1) | (data[3] & 0x01);
	पूर्ण अन्यथा अगर (features->type == CINTIQ_COMPANION_2) अणु
		/* d-pad right  -> data[2] & 0x10
		 * d-pad up     -> data[2] & 0x20
		 * d-pad left   -> data[2] & 0x40
		 * d-pad करोwn   -> data[2] & 0x80
		 * d-pad center -> data[1] & 0x01
		 */
		buttons = ((data[2] >> 4) << 7) |
		          ((data[1] & 0x04) << 4) |
		          ((data[2] & 0x0F) << 2) |
		          (data[1] & 0x03);
	पूर्ण अन्यथा अगर (features->type >= INTUOS5S && features->type <= INTUOSPL) अणु
		/*
		 * ExpressKeys on Intuos5/Intuos Pro have a capacitive sensor in
		 * addition to the mechanical चयन. Switch data is
		 * stored in data[4], capacitive data in data[5].
		 *
		 * Touch ring mode चयन (data[3]) has no capacitive sensor
		 */
		buttons = (data[4] << 1) | (data[3] & 0x01);
		ring1 = data[2];
	पूर्ण अन्यथा अणु
		अगर (features->type == WACOM_21UX2 || features->type == WACOM_22HD) अणु
			buttons = (data[8] << 10) | ((data[7] & 0x01) << 9) |
			          (data[6] << 1) | (data[5] & 0x01);

			अगर (features->type == WACOM_22HD) अणु
				nkeys = 3;
				keys = data[9] & 0x07;

				info = !!(data[9] & 0x01);
				wrench = !!(data[9] & 0x02);
			पूर्ण
		पूर्ण अन्यथा अणु
			buttons = ((data[6] & 0x10) << 5)  |
			          ((data[5] & 0x10) << 4)  |
			          ((data[6] & 0x0F) << 4)  |
			          (data[5] & 0x0F);
		पूर्ण
		strip1 = ((data[1] & 0x1f) << 8) | data[2];
		strip2 = ((data[3] & 0x1f) << 8) | data[4];
	पूर्ण

	prox = (buttons & ~(~0U << nbuttons)) | (keys & ~(~0U << nkeys)) |
	       (ring1 & 0x80) | (ring2 & 0x80) | strip1 | strip2;

	wacom_report_numbered_buttons(input, nbuttons, buttons);

	क्रम (i = 0; i < nkeys; i++)
		input_report_key(input, KEY_PROG1 + i, keys & (1 << i));

	input_report_key(input, KEY_BUTTONCONFIG, wrench);
	input_report_key(input, KEY_ONSCREEN_KEYBOARD, keyboard);
	input_report_key(input, KEY_CONTROLPANEL, menu);
	input_report_key(input, KEY_INFO, info);

	अगर (wacom->shared && wacom->shared->touch_input) अणु
		input_report_चयन(wacom->shared->touch_input,
				    SW_MUTE_DEVICE,
				    !wacom->shared->is_touch_on);
		input_sync(wacom->shared->touch_input);
	पूर्ण

	input_report_असल(input, ABS_RX, strip1);
	input_report_असल(input, ABS_RY, strip2);

	input_report_असल(input, ABS_WHEEL,    (ring1 & 0x80) ? (ring1 & 0x7f) : 0);
	input_report_असल(input, ABS_THROTTLE, (ring2 & 0x80) ? (ring2 & 0x7f) : 0);

	input_report_key(input, wacom->tool[1], prox ? 1 : 0);
	input_report_असल(input, ABS_MISC, prox ? PAD_DEVICE_ID : 0);

	input_event(input, EV_MSC, MSC_SERIAL, 0xffffffff);

	वापस 1;
पूर्ण

अटल पूर्णांक wacom_पूर्णांकuos_id_mangle(पूर्णांक tool_id)
अणु
	वापस (tool_id & ~0xFFF) << 4 | (tool_id & 0xFFF);
पूर्ण

अटल पूर्णांक wacom_पूर्णांकuos_get_tool_type(पूर्णांक tool_id)
अणु
	पूर्णांक tool_type;

	चयन (tool_id) अणु
	हाल 0x812: /* Inking pen */
	हाल 0x801: /* Intuos3 Inking pen */
	हाल 0x12802: /* Intuos4/5 Inking Pen */
	हाल 0x012:
		tool_type = BTN_TOOL_PENCIL;
		अवरोध;

	हाल 0x822: /* Pen */
	हाल 0x842:
	हाल 0x852:
	हाल 0x823: /* Intuos3 Grip Pen */
	हाल 0x813: /* Intuos3 Classic Pen */
	हाल 0x885: /* Intuos3 Marker Pen */
	हाल 0x802: /* Intuos4/5 13HD/24HD General Pen */
	हाल 0x804: /* Intuos4/5 13HD/24HD Marker Pen */
	हाल 0x8e2: /* IntuosHT2 pen */
	हाल 0x022:
	हाल 0x10804: /* Intuos4/5 13HD/24HD Art Pen */
	हाल 0x10842: /* MobileStudio Pro Pro Pen slim */
	हाल 0x14802: /* Intuos4/5 13HD/24HD Classic Pen */
	हाल 0x16802: /* Cपूर्णांकiq 13HD Pro Pen */
	हाल 0x18802: /* DTH2242 Pen */
	हाल 0x10802: /* Intuos4/5 13HD/24HD General Pen */
		tool_type = BTN_TOOL_PEN;
		अवरोध;

	हाल 0x832: /* Stroke pen */
	हाल 0x032:
		tool_type = BTN_TOOL_BRUSH;
		अवरोध;

	हाल 0x007: /* Mouse 4D and 2D */
	हाल 0x09c:
	हाल 0x094:
	हाल 0x017: /* Intuos3 2D Mouse */
	हाल 0x806: /* Intuos4 Mouse */
		tool_type = BTN_TOOL_MOUSE;
		अवरोध;

	हाल 0x096: /* Lens cursor */
	हाल 0x097: /* Intuos3 Lens cursor */
	हाल 0x006: /* Intuos4 Lens cursor */
		tool_type = BTN_TOOL_LENS;
		अवरोध;

	हाल 0x82a: /* Eraser */
	हाल 0x84a:
	हाल 0x85a:
	हाल 0x91a:
	हाल 0xd1a:
	हाल 0x0fa:
	हाल 0x82b: /* Intuos3 Grip Pen Eraser */
	हाल 0x81b: /* Intuos3 Classic Pen Eraser */
	हाल 0x91b: /* Intuos3 Airbrush Eraser */
	हाल 0x80c: /* Intuos4/5 13HD/24HD Marker Pen Eraser */
	हाल 0x80a: /* Intuos4/5 13HD/24HD General Pen Eraser */
	हाल 0x90a: /* Intuos4/5 13HD/24HD Airbrush Eraser */
	हाल 0x1480a: /* Intuos4/5 13HD/24HD Classic Pen Eraser */
	हाल 0x1090a: /* Intuos4/5 13HD/24HD Airbrush Eraser */
	हाल 0x1080c: /* Intuos4/5 13HD/24HD Art Pen Eraser */
	हाल 0x1084a: /* MobileStudio Pro Pro Pen slim Eraser */
	हाल 0x1680a: /* Cपूर्णांकiq 13HD Pro Pen Eraser */
	हाल 0x1880a: /* DTH2242 Eraser */
	हाल 0x1080a: /* Intuos4/5 13HD/24HD General Pen Eraser */
		tool_type = BTN_TOOL_RUBBER;
		अवरोध;

	हाल 0xd12:
	हाल 0x912:
	हाल 0x112:
	हाल 0x913: /* Intuos3 Airbrush */
	हाल 0x902: /* Intuos4/5 13HD/24HD Airbrush */
	हाल 0x10902: /* Intuos4/5 13HD/24HD Airbrush */
		tool_type = BTN_TOOL_AIRBRUSH;
		अवरोध;

	शेष: /* Unknown tool */
		tool_type = BTN_TOOL_PEN;
		अवरोध;
	पूर्ण
	वापस tool_type;
पूर्ण

अटल व्योम wacom_निकास_report(काष्ठा wacom_wac *wacom)
अणु
	काष्ठा input_dev *input = wacom->pen_input;
	काष्ठा wacom_features *features = &wacom->features;
	अचिन्हित अक्षर *data = wacom->data;
	पूर्णांक idx = (features->type == INTUOS) ? (data[1] & 0x01) : 0;

	/*
	 * Reset all states otherwise we lose the initial states
	 * when in-prox next समय
	 */
	input_report_असल(input, ABS_X, 0);
	input_report_असल(input, ABS_Y, 0);
	input_report_असल(input, ABS_DISTANCE, 0);
	input_report_असल(input, ABS_TILT_X, 0);
	input_report_असल(input, ABS_TILT_Y, 0);
	अगर (wacom->tool[idx] >= BTN_TOOL_MOUSE) अणु
		input_report_key(input, BTN_LEFT, 0);
		input_report_key(input, BTN_MIDDLE, 0);
		input_report_key(input, BTN_RIGHT, 0);
		input_report_key(input, BTN_SIDE, 0);
		input_report_key(input, BTN_EXTRA, 0);
		input_report_असल(input, ABS_THROTTLE, 0);
		input_report_असल(input, ABS_RZ, 0);
	पूर्ण अन्यथा अणु
		input_report_असल(input, ABS_PRESSURE, 0);
		input_report_key(input, BTN_STYLUS, 0);
		input_report_key(input, BTN_STYLUS2, 0);
		input_report_key(input, BTN_TOUCH, 0);
		input_report_असल(input, ABS_WHEEL, 0);
		अगर (features->type >= INTUOS3S)
			input_report_असल(input, ABS_Z, 0);
	पूर्ण
	input_report_key(input, wacom->tool[idx], 0);
	input_report_असल(input, ABS_MISC, 0); /* reset tool id */
	input_event(input, EV_MSC, MSC_SERIAL, wacom->serial[idx]);
	wacom->id[idx] = 0;
पूर्ण

अटल पूर्णांक wacom_पूर्णांकuos_inout(काष्ठा wacom_wac *wacom)
अणु
	काष्ठा wacom_features *features = &wacom->features;
	अचिन्हित अक्षर *data = wacom->data;
	काष्ठा input_dev *input = wacom->pen_input;
	पूर्णांक idx = (features->type == INTUOS) ? (data[1] & 0x01) : 0;

	अगर (!(((data[1] & 0xfc) == 0xc0) ||  /* in prox */
	    ((data[1] & 0xfe) == 0x20) ||    /* in range */
	    ((data[1] & 0xfe) == 0x80)))     /* out prox */
		वापस 0;

	/* Enter report */
	अगर ((data[1] & 0xfc) == 0xc0) अणु
		/* serial number of the tool */
		wacom->serial[idx] = ((data[3] & 0x0f) << 28) +
			(data[4] << 20) + (data[5] << 12) +
			(data[6] << 4) + (data[7] >> 4);

		wacom->id[idx] = (data[2] << 4) | (data[3] >> 4) |
		     ((data[7] & 0x0f) << 16) | ((data[8] & 0xf0) << 8);

		wacom->tool[idx] = wacom_पूर्णांकuos_get_tool_type(wacom->id[idx]);

		wacom->shared->stylus_in_proximity = true;
		वापस 1;
	पूर्ण

	/* in Range */
	अगर ((data[1] & 0xfe) == 0x20) अणु
		अगर (features->type != INTUOSHT2)
			wacom->shared->stylus_in_proximity = true;

		/* in Range जबतक निकासing */
		अगर (wacom->reporting_data) अणु
			input_report_key(input, BTN_TOUCH, 0);
			input_report_असल(input, ABS_PRESSURE, 0);
			input_report_असल(input, ABS_DISTANCE, wacom->features.distance_max);
			वापस 2;
		पूर्ण
		वापस 1;
	पूर्ण

	/* Exit report */
	अगर ((data[1] & 0xfe) == 0x80) अणु
		wacom->shared->stylus_in_proximity = false;
		wacom->reporting_data = false;

		/* करोn't report exit if we don't know the ID */
		अगर (!wacom->id[idx])
			वापस 1;

		wacom_निकास_report(wacom);
		वापस 2;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत bool report_touch_events(काष्ठा wacom_wac *wacom)
अणु
	वापस (touch_arbitration ? !wacom->shared->stylus_in_proximity : 1);
पूर्ण

अटल अंतरभूत bool delay_pen_events(काष्ठा wacom_wac *wacom)
अणु
	वापस (wacom->shared->touch_करोwn && touch_arbitration);
पूर्ण

अटल पूर्णांक wacom_पूर्णांकuos_general(काष्ठा wacom_wac *wacom)
अणु
	काष्ठा wacom_features *features = &wacom->features;
	अचिन्हित अक्षर *data = wacom->data;
	काष्ठा input_dev *input = wacom->pen_input;
	पूर्णांक idx = (features->type == INTUOS) ? (data[1] & 0x01) : 0;
	अचिन्हित अक्षर type = (data[1] >> 1) & 0x0F;
	अचिन्हित पूर्णांक x, y, distance, t;

	अगर (data[0] != WACOM_REPORT_PENABLED && data[0] != WACOM_REPORT_CINTIQ &&
		data[0] != WACOM_REPORT_INTUOS_PEN)
		वापस 0;

	अगर (delay_pen_events(wacom))
		वापस 1;

	/* करोn't report events if we don't know the tool ID */
	अगर (!wacom->id[idx]) अणु
		/* but reschedule a पढ़ो of the current tool */
		wacom_पूर्णांकuos_schedule_prox_event(wacom);
		वापस 1;
	पूर्ण

	/*
	 * करोn't report events क्रम invalid data
	 */
	/* older I4 styli करोn't work with new Cपूर्णांकiqs */
	अगर ((!((wacom->id[idx] >> 16) & 0x01) &&
			(features->type == WACOM_21UX2)) ||
	    /* Only large Intuos support Lense Cursor */
	    (wacom->tool[idx] == BTN_TOOL_LENS &&
		(features->type == INTUOS3 ||
		 features->type == INTUOS3S ||
		 features->type == INTUOS4 ||
		 features->type == INTUOS4S ||
		 features->type == INTUOS5 ||
		 features->type == INTUOS5S ||
		 features->type == INTUOSPM ||
		 features->type == INTUOSPS)) ||
	   /* Cपूर्णांकiq करोesn't send data when RDY bit isn't set */
	   (features->type == CINTIQ && !(data[1] & 0x40)))
		वापस 1;

	x = (be16_to_cpup((__be16 *)&data[2]) << 1) | ((data[9] >> 1) & 1);
	y = (be16_to_cpup((__be16 *)&data[4]) << 1) | (data[9] & 1);
	distance = data[9] >> 2;
	अगर (features->type < INTUOS3S) अणु
		x >>= 1;
		y >>= 1;
		distance >>= 1;
	पूर्ण
	अगर (features->type == INTUOSHT2)
		distance = features->distance_max - distance;
	input_report_असल(input, ABS_X, x);
	input_report_असल(input, ABS_Y, y);
	input_report_असल(input, ABS_DISTANCE, distance);

	चयन (type) अणु
	हाल 0x00:
	हाल 0x01:
	हाल 0x02:
	हाल 0x03:
		/* general pen packet */
		t = (data[6] << 3) | ((data[7] & 0xC0) >> 5) | (data[1] & 1);
		अगर (features->pressure_max < 2047)
			t >>= 1;
		input_report_असल(input, ABS_PRESSURE, t);
		अगर (features->type != INTUOSHT2) अणु
		    input_report_असल(input, ABS_TILT_X,
				 (((data[7] << 1) & 0x7e) | (data[8] >> 7)) - 64);
		    input_report_असल(input, ABS_TILT_Y, (data[8] & 0x7f) - 64);
		पूर्ण
		input_report_key(input, BTN_STYLUS, data[1] & 2);
		input_report_key(input, BTN_STYLUS2, data[1] & 4);
		input_report_key(input, BTN_TOUCH, t > 10);
		अवरोध;

	हाल 0x0a:
		/* airbrush second packet */
		input_report_असल(input, ABS_WHEEL,
				(data[6] << 2) | ((data[7] >> 6) & 3));
		input_report_असल(input, ABS_TILT_X,
				 (((data[7] << 1) & 0x7e) | (data[8] >> 7)) - 64);
		input_report_असल(input, ABS_TILT_Y, (data[8] & 0x7f) - 64);
		अवरोध;

	हाल 0x05:
		/* Rotation packet */
		अगर (features->type >= INTUOS3S) अणु
			/* I3 marker pen rotation */
			t = (data[6] << 3) | ((data[7] >> 5) & 7);
			t = (data[7] & 0x20) ? ((t > 900) ? ((t-1) / 2 - 1350) :
				((t-1) / 2 + 450)) : (450 - t / 2) ;
			input_report_असल(input, ABS_Z, t);
		पूर्ण अन्यथा अणु
			/* 4D mouse 2nd packet */
			t = (data[6] << 3) | ((data[7] >> 5) & 7);
			input_report_असल(input, ABS_RZ, (data[7] & 0x20) ?
				((t - 1) / 2) : -t / 2);
		पूर्ण
		अवरोध;

	हाल 0x04:
		/* 4D mouse 1st packet */
		input_report_key(input, BTN_LEFT,   data[8] & 0x01);
		input_report_key(input, BTN_MIDDLE, data[8] & 0x02);
		input_report_key(input, BTN_RIGHT,  data[8] & 0x04);

		input_report_key(input, BTN_SIDE,   data[8] & 0x20);
		input_report_key(input, BTN_EXTRA,  data[8] & 0x10);
		t = (data[6] << 2) | ((data[7] >> 6) & 3);
		input_report_असल(input, ABS_THROTTLE, (data[8] & 0x08) ? -t : t);
		अवरोध;

	हाल 0x06:
		/* I4 mouse */
		input_report_key(input, BTN_LEFT,   data[6] & 0x01);
		input_report_key(input, BTN_MIDDLE, data[6] & 0x02);
		input_report_key(input, BTN_RIGHT,  data[6] & 0x04);
		input_report_rel(input, REL_WHEEL, ((data[7] & 0x80) >> 7)
				 - ((data[7] & 0x40) >> 6));
		input_report_key(input, BTN_SIDE,   data[6] & 0x08);
		input_report_key(input, BTN_EXTRA,  data[6] & 0x10);

		input_report_असल(input, ABS_TILT_X,
			(((data[7] << 1) & 0x7e) | (data[8] >> 7)) - 64);
		input_report_असल(input, ABS_TILT_Y, (data[8] & 0x7f) - 64);
		अवरोध;

	हाल 0x08:
		अगर (wacom->tool[idx] == BTN_TOOL_MOUSE) अणु
			/* 2D mouse packet */
			input_report_key(input, BTN_LEFT,   data[8] & 0x04);
			input_report_key(input, BTN_MIDDLE, data[8] & 0x08);
			input_report_key(input, BTN_RIGHT,  data[8] & 0x10);
			input_report_rel(input, REL_WHEEL, (data[8] & 0x01)
					 - ((data[8] & 0x02) >> 1));

			/* I3 2D mouse side buttons */
			अगर (features->type >= INTUOS3S && features->type <= INTUOS3L) अणु
				input_report_key(input, BTN_SIDE,   data[8] & 0x40);
				input_report_key(input, BTN_EXTRA,  data[8] & 0x20);
			पूर्ण
		पूर्ण
		अन्यथा अगर (wacom->tool[idx] == BTN_TOOL_LENS) अणु
			/* Lens cursor packets */
			input_report_key(input, BTN_LEFT,   data[8] & 0x01);
			input_report_key(input, BTN_MIDDLE, data[8] & 0x02);
			input_report_key(input, BTN_RIGHT,  data[8] & 0x04);
			input_report_key(input, BTN_SIDE,   data[8] & 0x10);
			input_report_key(input, BTN_EXTRA,  data[8] & 0x08);
		पूर्ण
		अवरोध;

	हाल 0x07:
	हाल 0x09:
	हाल 0x0b:
	हाल 0x0c:
	हाल 0x0d:
	हाल 0x0e:
	हाल 0x0f:
		/* unhandled */
		अवरोध;
	पूर्ण

	input_report_असल(input, ABS_MISC,
			 wacom_पूर्णांकuos_id_mangle(wacom->id[idx])); /* report tool id */
	input_report_key(input, wacom->tool[idx], 1);
	input_event(input, EV_MSC, MSC_SERIAL, wacom->serial[idx]);
	wacom->reporting_data = true;
	वापस 2;
पूर्ण

अटल पूर्णांक wacom_पूर्णांकuos_irq(काष्ठा wacom_wac *wacom)
अणु
	अचिन्हित अक्षर *data = wacom->data;
	काष्ठा input_dev *input = wacom->pen_input;
	पूर्णांक result;

	अगर (data[0] != WACOM_REPORT_PENABLED &&
	    data[0] != WACOM_REPORT_INTUOS_ID1 &&
	    data[0] != WACOM_REPORT_INTUOS_ID2 &&
	    data[0] != WACOM_REPORT_INTUOSPAD &&
	    data[0] != WACOM_REPORT_INTUOS_PEN &&
	    data[0] != WACOM_REPORT_CINTIQ &&
	    data[0] != WACOM_REPORT_CINTIQPAD &&
	    data[0] != WACOM_REPORT_INTUOS5PAD) अणु
		dev_dbg(input->dev.parent,
			"%s: received unknown report #%d\n", __func__, data[0]);
                वापस 0;
	पूर्ण

	/* process pad events */
	result = wacom_पूर्णांकuos_pad(wacom);
	अगर (result)
		वापस result;

	/* process in/out prox events */
	result = wacom_पूर्णांकuos_inout(wacom);
	अगर (result)
		वापस result - 1;

	/* process general packets */
	result = wacom_पूर्णांकuos_general(wacom);
	अगर (result)
		वापस result - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक wacom_remote_irq(काष्ठा wacom_wac *wacom_wac, माप_प्रकार len)
अणु
	अचिन्हित अक्षर *data = wacom_wac->data;
	काष्ठा input_dev *input;
	काष्ठा wacom *wacom = container_of(wacom_wac, काष्ठा wacom, wacom_wac);
	काष्ठा wacom_remote *remote = wacom->remote;
	पूर्णांक bat_अक्षरging, bat_percent, touch_ring_mode;
	__u32 serial;
	पूर्णांक i, index = -1;
	अचिन्हित दीर्घ flags;

	अगर (data[0] != WACOM_REPORT_REMOTE) अणु
		hid_dbg(wacom->hdev, "%s: received unknown report #%d",
			__func__, data[0]);
		वापस 0;
	पूर्ण

	serial = data[3] + (data[4] << 8) + (data[5] << 16);
	wacom_wac->id[0] = PAD_DEVICE_ID;

	spin_lock_irqsave(&remote->remote_lock, flags);

	क्रम (i = 0; i < WACOM_MAX_REMOTES; i++) अणु
		अगर (remote->remotes[i].serial == serial) अणु
			index = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (index < 0 || !remote->remotes[index].रेजिस्टरed)
		जाओ out;

	input = remote->remotes[index].input;

	input_report_key(input, BTN_0, (data[9] & 0x01));
	input_report_key(input, BTN_1, (data[9] & 0x02));
	input_report_key(input, BTN_2, (data[9] & 0x04));
	input_report_key(input, BTN_3, (data[9] & 0x08));
	input_report_key(input, BTN_4, (data[9] & 0x10));
	input_report_key(input, BTN_5, (data[9] & 0x20));
	input_report_key(input, BTN_6, (data[9] & 0x40));
	input_report_key(input, BTN_7, (data[9] & 0x80));

	input_report_key(input, BTN_8, (data[10] & 0x01));
	input_report_key(input, BTN_9, (data[10] & 0x02));
	input_report_key(input, BTN_A, (data[10] & 0x04));
	input_report_key(input, BTN_B, (data[10] & 0x08));
	input_report_key(input, BTN_C, (data[10] & 0x10));
	input_report_key(input, BTN_X, (data[10] & 0x20));
	input_report_key(input, BTN_Y, (data[10] & 0x40));
	input_report_key(input, BTN_Z, (data[10] & 0x80));

	input_report_key(input, BTN_BASE, (data[11] & 0x01));
	input_report_key(input, BTN_BASE2, (data[11] & 0x02));

	अगर (data[12] & 0x80)
		input_report_असल(input, ABS_WHEEL, (data[12] & 0x7f) - 1);
	अन्यथा
		input_report_असल(input, ABS_WHEEL, 0);

	bat_percent = data[7] & 0x7f;
	bat_अक्षरging = !!(data[7] & 0x80);

	अगर (data[9] | data[10] | (data[11] & 0x03) | data[12])
		input_report_असल(input, ABS_MISC, PAD_DEVICE_ID);
	अन्यथा
		input_report_असल(input, ABS_MISC, 0);

	input_event(input, EV_MSC, MSC_SERIAL, serial);

	input_sync(input);

	/*Which mode select (LED light) is currently on?*/
	touch_ring_mode = (data[11] & 0xC0) >> 6;

	क्रम (i = 0; i < WACOM_MAX_REMOTES; i++) अणु
		अगर (remote->remotes[i].serial == serial)
			wacom->led.groups[i].select = touch_ring_mode;
	पूर्ण

	__wacom_notअगरy_battery(&remote->remotes[index].battery,
				WACOM_POWER_SUPPLY_STATUS_AUTO, bat_percent,
				bat_अक्षरging, 1, bat_अक्षरging);

out:
	spin_unlock_irqrestore(&remote->remote_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम wacom_remote_status_irq(काष्ठा wacom_wac *wacom_wac, माप_प्रकार len)
अणु
	काष्ठा wacom *wacom = container_of(wacom_wac, काष्ठा wacom, wacom_wac);
	अचिन्हित अक्षर *data = wacom_wac->data;
	काष्ठा wacom_remote *remote = wacom->remote;
	काष्ठा wacom_remote_data remote_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, ret;

	अगर (data[0] != WACOM_REPORT_DEVICE_LIST)
		वापस;

	स_रखो(&remote_data, 0, माप(काष्ठा wacom_remote_data));

	क्रम (i = 0; i < WACOM_MAX_REMOTES; i++) अणु
		पूर्णांक j = i * 6;
		पूर्णांक serial = (data[j+6] << 16) + (data[j+5] << 8) + data[j+4];
		bool connected = data[j+2];

		remote_data.remote[i].serial = serial;
		remote_data.remote[i].connected = connected;
	पूर्ण

	spin_lock_irqsave(&remote->remote_lock, flags);

	ret = kfअगरo_in(&remote->remote_fअगरo, &remote_data, माप(remote_data));
	अगर (ret != माप(remote_data)) अणु
		spin_unlock_irqrestore(&remote->remote_lock, flags);
		hid_err(wacom->hdev, "Can't queue Remote status event.\n");
		वापस;
	पूर्ण

	spin_unlock_irqrestore(&remote->remote_lock, flags);

	wacom_schedule_work(wacom_wac, WACOM_WORKER_REMOTE);
पूर्ण

अटल पूर्णांक पूर्णांक_dist(पूर्णांक x1, पूर्णांक y1, पूर्णांक x2, पूर्णांक y2)
अणु
	पूर्णांक x = x2 - x1;
	पूर्णांक y = y2 - y1;

	वापस पूर्णांक_वर्ग_मूल(x*x + y*y);
पूर्ण

अटल व्योम wacom_पूर्णांकuos_bt_process_data(काष्ठा wacom_wac *wacom,
		अचिन्हित अक्षर *data)
अणु
	स_नकल(wacom->data, data, 10);
	wacom_पूर्णांकuos_irq(wacom);

	input_sync(wacom->pen_input);
	अगर (wacom->pad_input)
		input_sync(wacom->pad_input);
पूर्ण

अटल पूर्णांक wacom_पूर्णांकuos_bt_irq(काष्ठा wacom_wac *wacom, माप_प्रकार len)
अणु
	अचिन्हित अक्षर data[WACOM_PKGLEN_MAX];
	पूर्णांक i = 1;
	अचिन्हित घातer_raw, battery_capacity, bat_अक्षरging, ps_connected;

	स_नकल(data, wacom->data, len);

	चयन (data[0]) अणु
	हाल 0x04:
		wacom_पूर्णांकuos_bt_process_data(wacom, data + i);
		i += 10;
		fallthrough;
	हाल 0x03:
		wacom_पूर्णांकuos_bt_process_data(wacom, data + i);
		i += 10;
		wacom_पूर्णांकuos_bt_process_data(wacom, data + i);
		i += 10;
		घातer_raw = data[i];
		bat_अक्षरging = (घातer_raw & 0x08) ? 1 : 0;
		ps_connected = (घातer_raw & 0x10) ? 1 : 0;
		battery_capacity = batcap_i4[घातer_raw & 0x07];
		wacom_notअगरy_battery(wacom, WACOM_POWER_SUPPLY_STATUS_AUTO,
				     battery_capacity, bat_अक्षरging,
				     battery_capacity || bat_अक्षरging,
				     ps_connected);
		अवरोध;
	शेष:
		dev_dbg(wacom->pen_input->dev.parent,
				"Unknown report: %d,%d size:%zu\n",
				data[0], data[1], len);
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wacom_wac_finger_count_touches(काष्ठा wacom_wac *wacom)
अणु
	काष्ठा input_dev *input = wacom->touch_input;
	अचिन्हित touch_max = wacom->features.touch_max;
	पूर्णांक count = 0;
	पूर्णांक i;

	अगर (!touch_max)
		वापस 0;

	अगर (touch_max == 1)
		वापस test_bit(BTN_TOUCH, input->key) &&
			report_touch_events(wacom);

	क्रम (i = 0; i < input->mt->num_slots; i++) अणु
		काष्ठा input_mt_slot *ps = &input->mt->slots[i];
		पूर्णांक id = input_mt_get_value(ps, ABS_MT_TRACKING_ID);
		अगर (id >= 0)
			count++;
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम wacom_पूर्णांकuos_pro2_bt_pen(काष्ठा wacom_wac *wacom)
अणु
	पूर्णांक pen_frame_len, pen_frames;

	काष्ठा input_dev *pen_input = wacom->pen_input;
	अचिन्हित अक्षर *data = wacom->data;
	पूर्णांक i;

	अगर (wacom->features.type == INTUOSP2_BT ||
	    wacom->features.type == INTUOSP2S_BT) अणु
		wacom->serial[0] = get_unaligned_le64(&data[99]);
		wacom->id[0]     = get_unaligned_le16(&data[107]);
		pen_frame_len = 14;
		pen_frames = 7;
	पूर्ण अन्यथा अणु
		wacom->serial[0] = get_unaligned_le64(&data[33]);
		wacom->id[0]     = get_unaligned_le16(&data[41]);
		pen_frame_len = 8;
		pen_frames = 4;
	पूर्ण

	अगर (wacom->serial[0] >> 52 == 1) अणु
		/* Add back in missing bits of ID क्रम non-USI pens */
		wacom->id[0] |= (wacom->serial[0] >> 32) & 0xFFFFF;
	पूर्ण

	क्रम (i = 0; i < pen_frames; i++) अणु
		अचिन्हित अक्षर *frame = &data[i*pen_frame_len + 1];
		bool valid = frame[0] & 0x80;
		bool prox = frame[0] & 0x40;
		bool range = frame[0] & 0x20;
		bool invert = frame[0] & 0x10;

		अगर (!valid)
			जारी;

		अगर (!prox) अणु
			wacom->shared->stylus_in_proximity = false;
			wacom_निकास_report(wacom);
			input_sync(pen_input);

			wacom->tool[0] = 0;
			wacom->id[0] = 0;
			wacom->serial[0] = 0;
			वापस;
		पूर्ण

		अगर (range) अणु
			अगर (!wacom->tool[0]) अणु /* first in range */
				/* Going पूर्णांकo range select tool */
				अगर (invert)
					wacom->tool[0] = BTN_TOOL_RUBBER;
				अन्यथा अगर (wacom->id[0])
					wacom->tool[0] = wacom_पूर्णांकuos_get_tool_type(wacom->id[0]);
				अन्यथा
					wacom->tool[0] = BTN_TOOL_PEN;
			पूर्ण

			input_report_असल(pen_input, ABS_X, get_unaligned_le16(&frame[1]));
			input_report_असल(pen_input, ABS_Y, get_unaligned_le16(&frame[3]));

			अगर (wacom->features.type == INTUOSP2_BT ||
			    wacom->features.type == INTUOSP2S_BT) अणु
				/* Fix rotation alignment: userspace expects zero at left */
				पूर्णांक16_t rotation =
					(पूर्णांक16_t)get_unaligned_le16(&frame[9]);
				rotation += 1800/4;

				अगर (rotation > 899)
					rotation -= 1800;

				input_report_असल(pen_input, ABS_TILT_X,
						 (अक्षर)frame[7]);
				input_report_असल(pen_input, ABS_TILT_Y,
						 (अक्षर)frame[8]);
				input_report_असल(pen_input, ABS_Z, rotation);
				input_report_असल(pen_input, ABS_WHEEL,
						 get_unaligned_le16(&frame[11]));
			पूर्ण
		पूर्ण
		अगर (wacom->tool[0]) अणु
			input_report_असल(pen_input, ABS_PRESSURE, get_unaligned_le16(&frame[5]));
			अगर (wacom->features.type == INTUOSP2_BT ||
			    wacom->features.type == INTUOSP2S_BT) अणु
				input_report_असल(pen_input, ABS_DISTANCE,
						 range ? frame[13] : wacom->features.distance_max);
			पूर्ण अन्यथा अणु
				input_report_असल(pen_input, ABS_DISTANCE,
						 range ? frame[7] : wacom->features.distance_max);
			पूर्ण

			input_report_key(pen_input, BTN_TOUCH, frame[0] & 0x09);
			input_report_key(pen_input, BTN_STYLUS, frame[0] & 0x02);
			input_report_key(pen_input, BTN_STYLUS2, frame[0] & 0x04);

			input_report_key(pen_input, wacom->tool[0], prox);
			input_event(pen_input, EV_MSC, MSC_SERIAL, wacom->serial[0]);
			input_report_असल(pen_input, ABS_MISC,
					 wacom_पूर्णांकuos_id_mangle(wacom->id[0])); /* report tool id */
		पूर्ण

		wacom->shared->stylus_in_proximity = prox;

		input_sync(pen_input);
	पूर्ण
पूर्ण

अटल व्योम wacom_पूर्णांकuos_pro2_bt_touch(काष्ठा wacom_wac *wacom)
अणु
	स्थिर पूर्णांक finger_touch_len = 8;
	स्थिर पूर्णांक finger_frames = 4;
	स्थिर पूर्णांक finger_frame_len = 43;

	काष्ठा input_dev *touch_input = wacom->touch_input;
	अचिन्हित अक्षर *data = wacom->data;
	पूर्णांक num_contacts_left = 5;
	पूर्णांक i, j;

	क्रम (i = 0; i < finger_frames; i++) अणु
		अचिन्हित अक्षर *frame = &data[i*finger_frame_len + 109];
		पूर्णांक current_num_contacts = frame[0] & 0x7F;
		पूर्णांक contacts_to_send;

		अगर (!(frame[0] & 0x80))
			जारी;

		/*
		 * First packet resets the counter since only the first
		 * packet in series will have non-zero current_num_contacts.
		 */
		अगर (current_num_contacts)
			wacom->num_contacts_left = current_num_contacts;

		contacts_to_send = min(num_contacts_left, wacom->num_contacts_left);

		क्रम (j = 0; j < contacts_to_send; j++) अणु
			अचिन्हित अक्षर *touch = &frame[j*finger_touch_len + 1];
			पूर्णांक slot = input_mt_get_slot_by_key(touch_input, touch[0]);
			पूर्णांक x = get_unaligned_le16(&touch[2]);
			पूर्णांक y = get_unaligned_le16(&touch[4]);
			पूर्णांक w = touch[6] * input_असल_get_res(touch_input, ABS_MT_POSITION_X);
			पूर्णांक h = touch[7] * input_असल_get_res(touch_input, ABS_MT_POSITION_Y);

			अगर (slot < 0)
				जारी;

			input_mt_slot(touch_input, slot);
			input_mt_report_slot_state(touch_input, MT_TOOL_FINGER, touch[1] & 0x01);
			input_report_असल(touch_input, ABS_MT_POSITION_X, x);
			input_report_असल(touch_input, ABS_MT_POSITION_Y, y);
			input_report_असल(touch_input, ABS_MT_TOUCH_MAJOR, max(w, h));
			input_report_असल(touch_input, ABS_MT_TOUCH_MINOR, min(w, h));
			input_report_असल(touch_input, ABS_MT_ORIENTATION, w > h);
		पूर्ण

		input_mt_sync_frame(touch_input);

		wacom->num_contacts_left -= contacts_to_send;
		अगर (wacom->num_contacts_left <= 0) अणु
			wacom->num_contacts_left = 0;
			wacom->shared->touch_करोwn = wacom_wac_finger_count_touches(wacom);
			input_sync(touch_input);
		पूर्ण
	पूर्ण

	अगर (wacom->num_contacts_left == 0) अणु
		// Be careful that we करोn't accidentally call input_sync with
		// only a partial set of fingers of processed
		input_report_चयन(touch_input, SW_MUTE_DEVICE, !(data[281] >> 7));
		input_sync(touch_input);
	पूर्ण

पूर्ण

अटल व्योम wacom_पूर्णांकuos_pro2_bt_pad(काष्ठा wacom_wac *wacom)
अणु
	काष्ठा input_dev *pad_input = wacom->pad_input;
	अचिन्हित अक्षर *data = wacom->data;
	पूर्णांक nbuttons = wacom->features.numbered_buttons;

	पूर्णांक expresskeys = data[282];
	पूर्णांक center = (data[281] & 0x40) >> 6;
	पूर्णांक ring = data[285] & 0x7F;
	bool ringstatus = data[285] & 0x80;
	bool prox = expresskeys || center || ringstatus;

	/* Fix touchring data: userspace expects 0 at left and increasing घड़ीwise */
	ring = 71 - ring;
	ring += 3*72/16;
	अगर (ring > 71)
		ring -= 72;

	wacom_report_numbered_buttons(pad_input, nbuttons,
                                      expresskeys | (center << (nbuttons - 1)));

	input_report_असल(pad_input, ABS_WHEEL, ringstatus ? ring : 0);

	input_report_key(pad_input, wacom->tool[1], prox ? 1 : 0);
	input_report_असल(pad_input, ABS_MISC, prox ? PAD_DEVICE_ID : 0);
	input_event(pad_input, EV_MSC, MSC_SERIAL, 0xffffffff);

	input_sync(pad_input);
पूर्ण

अटल व्योम wacom_पूर्णांकuos_pro2_bt_battery(काष्ठा wacom_wac *wacom)
अणु
	अचिन्हित अक्षर *data = wacom->data;

	bool chg = data[284] & 0x80;
	पूर्णांक battery_status = data[284] & 0x7F;

	wacom_notअगरy_battery(wacom, WACOM_POWER_SUPPLY_STATUS_AUTO,
			     battery_status, chg, 1, chg);
पूर्ण

अटल व्योम wacom_पूर्णांकuos_gen3_bt_pad(काष्ठा wacom_wac *wacom)
अणु
	काष्ठा input_dev *pad_input = wacom->pad_input;
	अचिन्हित अक्षर *data = wacom->data;

	पूर्णांक buttons = data[44];

	wacom_report_numbered_buttons(pad_input, 4, buttons);

	input_report_key(pad_input, wacom->tool[1], buttons ? 1 : 0);
	input_report_असल(pad_input, ABS_MISC, buttons ? PAD_DEVICE_ID : 0);
	input_event(pad_input, EV_MSC, MSC_SERIAL, 0xffffffff);

	input_sync(pad_input);
पूर्ण

अटल व्योम wacom_पूर्णांकuos_gen3_bt_battery(काष्ठा wacom_wac *wacom)
अणु
	अचिन्हित अक्षर *data = wacom->data;

	bool chg = data[45] & 0x80;
	पूर्णांक battery_status = data[45] & 0x7F;

	wacom_notअगरy_battery(wacom, WACOM_POWER_SUPPLY_STATUS_AUTO,
			     battery_status, chg, 1, chg);
पूर्ण

अटल पूर्णांक wacom_पूर्णांकuos_pro2_bt_irq(काष्ठा wacom_wac *wacom, माप_प्रकार len)
अणु
	अचिन्हित अक्षर *data = wacom->data;

	अगर (data[0] != 0x80 && data[0] != 0x81) अणु
		dev_dbg(wacom->pen_input->dev.parent,
			"%s: received unknown report #%d\n", __func__, data[0]);
		वापस 0;
	पूर्ण

	wacom_पूर्णांकuos_pro2_bt_pen(wacom);
	अगर (wacom->features.type == INTUOSP2_BT ||
	    wacom->features.type == INTUOSP2S_BT) अणु
		wacom_पूर्णांकuos_pro2_bt_touch(wacom);
		wacom_पूर्णांकuos_pro2_bt_pad(wacom);
		wacom_पूर्णांकuos_pro2_bt_battery(wacom);
	पूर्ण अन्यथा अणु
		wacom_पूर्णांकuos_gen3_bt_pad(wacom);
		wacom_पूर्णांकuos_gen3_bt_battery(wacom);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wacom_24hdt_irq(काष्ठा wacom_wac *wacom)
अणु
	काष्ठा input_dev *input = wacom->touch_input;
	अचिन्हित अक्षर *data = wacom->data;
	पूर्णांक i;
	पूर्णांक current_num_contacts = data[61];
	पूर्णांक contacts_to_send = 0;
	पूर्णांक num_contacts_left = 4; /* maximum contacts per packet */
	पूर्णांक byte_per_packet = WACOM_BYTES_PER_24HDT_PACKET;
	पूर्णांक y_offset = 2;

	अगर (wacom->shared->has_mute_touch_चयन &&
	    !wacom->shared->is_touch_on) अणु
		अगर (!wacom->shared->touch_करोwn)
			वापस 0;
	पूर्ण

	अगर (wacom->features.type == WACOM_27QHDT) अणु
		current_num_contacts = data[63];
		num_contacts_left = 10;
		byte_per_packet = WACOM_BYTES_PER_QHDTHID_PACKET;
		y_offset = 0;
	पूर्ण

	/*
	 * First packet resets the counter since only the first
	 * packet in series will have non-zero current_num_contacts.
	 */
	अगर (current_num_contacts)
		wacom->num_contacts_left = current_num_contacts;

	contacts_to_send = min(num_contacts_left, wacom->num_contacts_left);

	क्रम (i = 0; i < contacts_to_send; i++) अणु
		पूर्णांक offset = (byte_per_packet * i) + 1;
		bool touch = (data[offset] & 0x1) && report_touch_events(wacom);
		पूर्णांक slot = input_mt_get_slot_by_key(input, data[offset + 1]);

		अगर (slot < 0)
			जारी;
		input_mt_slot(input, slot);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, touch);

		अगर (touch) अणु
			पूर्णांक t_x = get_unaligned_le16(&data[offset + 2]);
			पूर्णांक t_y = get_unaligned_le16(&data[offset + 4 + y_offset]);

			input_report_असल(input, ABS_MT_POSITION_X, t_x);
			input_report_असल(input, ABS_MT_POSITION_Y, t_y);

			अगर (wacom->features.type != WACOM_27QHDT) अणु
				पूर्णांक c_x = get_unaligned_le16(&data[offset + 4]);
				पूर्णांक c_y = get_unaligned_le16(&data[offset + 8]);
				पूर्णांक w = get_unaligned_le16(&data[offset + 10]);
				पूर्णांक h = get_unaligned_le16(&data[offset + 12]);

				input_report_असल(input, ABS_MT_TOUCH_MAJOR, min(w,h));
				input_report_असल(input, ABS_MT_WIDTH_MAJOR,
						 min(w, h) + पूर्णांक_dist(t_x, t_y, c_x, c_y));
				input_report_असल(input, ABS_MT_WIDTH_MINOR, min(w, h));
				input_report_असल(input, ABS_MT_ORIENTATION, w > h);
			पूर्ण
		पूर्ण
	पूर्ण
	input_mt_sync_frame(input);

	wacom->num_contacts_left -= contacts_to_send;
	अगर (wacom->num_contacts_left <= 0) अणु
		wacom->num_contacts_left = 0;
		wacom->shared->touch_करोwn = wacom_wac_finger_count_touches(wacom);
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक wacom_mt_touch(काष्ठा wacom_wac *wacom)
अणु
	काष्ठा input_dev *input = wacom->touch_input;
	अचिन्हित अक्षर *data = wacom->data;
	पूर्णांक i;
	पूर्णांक current_num_contacts = data[2];
	पूर्णांक contacts_to_send = 0;
	पूर्णांक x_offset = 0;

	/* MTTPC करोes not support Height and Width */
	अगर (wacom->features.type == MTTPC || wacom->features.type == MTTPC_B)
		x_offset = -4;

	/*
	 * First packet resets the counter since only the first
	 * packet in series will have non-zero current_num_contacts.
	 */
	अगर (current_num_contacts)
		wacom->num_contacts_left = current_num_contacts;

	/* There are at most 5 contacts per packet */
	contacts_to_send = min(5, wacom->num_contacts_left);

	क्रम (i = 0; i < contacts_to_send; i++) अणु
		पूर्णांक offset = (WACOM_BYTES_PER_MT_PACKET + x_offset) * i + 3;
		bool touch = (data[offset] & 0x1) && report_touch_events(wacom);
		पूर्णांक id = get_unaligned_le16(&data[offset + 1]);
		पूर्णांक slot = input_mt_get_slot_by_key(input, id);

		अगर (slot < 0)
			जारी;

		input_mt_slot(input, slot);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, touch);
		अगर (touch) अणु
			पूर्णांक x = get_unaligned_le16(&data[offset + x_offset + 7]);
			पूर्णांक y = get_unaligned_le16(&data[offset + x_offset + 9]);
			input_report_असल(input, ABS_MT_POSITION_X, x);
			input_report_असल(input, ABS_MT_POSITION_Y, y);
		पूर्ण
	पूर्ण
	input_mt_sync_frame(input);

	wacom->num_contacts_left -= contacts_to_send;
	अगर (wacom->num_contacts_left <= 0) अणु
		wacom->num_contacts_left = 0;
		wacom->shared->touch_करोwn = wacom_wac_finger_count_touches(wacom);
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक wacom_tpc_mt_touch(काष्ठा wacom_wac *wacom)
अणु
	काष्ठा input_dev *input = wacom->touch_input;
	अचिन्हित अक्षर *data = wacom->data;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांक p = data[1] & (1 << i);
		bool touch = p && report_touch_events(wacom);

		input_mt_slot(input, i);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, touch);
		अगर (touch) अणु
			पूर्णांक x = le16_to_cpup((__le16 *)&data[i * 2 + 2]) & 0x7fff;
			पूर्णांक y = le16_to_cpup((__le16 *)&data[i * 2 + 6]) & 0x7fff;

			input_report_असल(input, ABS_MT_POSITION_X, x);
			input_report_असल(input, ABS_MT_POSITION_Y, y);
		पूर्ण
	पूर्ण
	input_mt_sync_frame(input);

	/* keep touch state क्रम pen event */
	wacom->shared->touch_करोwn = wacom_wac_finger_count_touches(wacom);

	वापस 1;
पूर्ण

अटल पूर्णांक wacom_tpc_single_touch(काष्ठा wacom_wac *wacom, माप_प्रकार len)
अणु
	अचिन्हित अक्षर *data = wacom->data;
	काष्ठा input_dev *input = wacom->touch_input;
	bool prox = report_touch_events(wacom);
	पूर्णांक x = 0, y = 0;

	अगर (wacom->features.touch_max > 1 || len > WACOM_PKGLEN_TPC2FG)
		वापस 0;

	अगर (len == WACOM_PKGLEN_TPC1FG) अणु
		prox = prox && (data[0] & 0x01);
		x = get_unaligned_le16(&data[1]);
		y = get_unaligned_le16(&data[3]);
	पूर्ण अन्यथा अगर (len == WACOM_PKGLEN_TPC1FG_B) अणु
		prox = prox && (data[2] & 0x01);
		x = get_unaligned_le16(&data[3]);
		y = get_unaligned_le16(&data[5]);
	पूर्ण अन्यथा अणु
		prox = prox && (data[1] & 0x01);
		x = le16_to_cpup((__le16 *)&data[2]);
		y = le16_to_cpup((__le16 *)&data[4]);
	पूर्ण

	अगर (prox) अणु
		input_report_असल(input, ABS_X, x);
		input_report_असल(input, ABS_Y, y);
	पूर्ण
	input_report_key(input, BTN_TOUCH, prox);

	/* keep touch state क्रम pen events */
	wacom->shared->touch_करोwn = prox;

	वापस 1;
पूर्ण

अटल पूर्णांक wacom_tpc_pen(काष्ठा wacom_wac *wacom)
अणु
	अचिन्हित अक्षर *data = wacom->data;
	काष्ठा input_dev *input = wacom->pen_input;
	bool prox = data[1] & 0x20;

	अगर (!wacom->shared->stylus_in_proximity) /* first in prox */
		/* Going पूर्णांकo proximity select tool */
		wacom->tool[0] = (data[1] & 0x0c) ? BTN_TOOL_RUBBER : BTN_TOOL_PEN;

	/* keep pen state क्रम touch events */
	wacom->shared->stylus_in_proximity = prox;

	/* send pen events only when touch is up or क्रमced out
	 * or touch arbitration is off
	 */
	अगर (!delay_pen_events(wacom)) अणु
		input_report_key(input, BTN_STYLUS, data[1] & 0x02);
		input_report_key(input, BTN_STYLUS2, data[1] & 0x10);
		input_report_असल(input, ABS_X, le16_to_cpup((__le16 *)&data[2]));
		input_report_असल(input, ABS_Y, le16_to_cpup((__le16 *)&data[4]));
		input_report_असल(input, ABS_PRESSURE, ((data[7] & 0x07) << 8) | data[6]);
		input_report_key(input, BTN_TOUCH, data[1] & 0x05);
		input_report_key(input, wacom->tool[0], prox);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wacom_tpc_irq(काष्ठा wacom_wac *wacom, माप_प्रकार len)
अणु
	अचिन्हित अक्षर *data = wacom->data;

	अगर (wacom->pen_input) अणु
		dev_dbg(wacom->pen_input->dev.parent,
			"%s: received report #%d\n", __func__, data[0]);

		अगर (len == WACOM_PKGLEN_PENABLED ||
		    data[0] == WACOM_REPORT_PENABLED)
			वापस wacom_tpc_pen(wacom);
	पूर्ण
	अन्यथा अगर (wacom->touch_input) अणु
		dev_dbg(wacom->touch_input->dev.parent,
			"%s: received report #%d\n", __func__, data[0]);

		चयन (len) अणु
		हाल WACOM_PKGLEN_TPC1FG:
			वापस wacom_tpc_single_touch(wacom, len);

		हाल WACOM_PKGLEN_TPC2FG:
			वापस wacom_tpc_mt_touch(wacom);

		शेष:
			चयन (data[0]) अणु
			हाल WACOM_REPORT_TPC1FG:
			हाल WACOM_REPORT_TPCHID:
			हाल WACOM_REPORT_TPCST:
			हाल WACOM_REPORT_TPC1FGE:
				वापस wacom_tpc_single_touch(wacom, len);

			हाल WACOM_REPORT_TPCMT:
			हाल WACOM_REPORT_TPCMT2:
				वापस wacom_mt_touch(wacom);

			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wacom_offset_rotation(काष्ठा input_dev *input, काष्ठा hid_usage *usage,
				 पूर्णांक value, पूर्णांक num, पूर्णांक denom)
अणु
	काष्ठा input_असलinfo *असल = &input->असलinfo[usage->code];
	पूर्णांक range = (असल->maximum - असल->minimum + 1);

	value += num*range/denom;
	अगर (value > असल->maximum)
		value -= range;
	अन्यथा अगर (value < असल->minimum)
		value += range;
	वापस value;
पूर्ण

पूर्णांक wacom_equivalent_usage(पूर्णांक usage)
अणु
	अगर ((usage & HID_USAGE_PAGE) == WACOM_HID_UP_WACOMDIGITIZER) अणु
		पूर्णांक subpage = (usage & 0xFF00) << 8;
		पूर्णांक subusage = (usage & 0xFF);

		अगर (subpage == WACOM_HID_SP_PAD ||
		    subpage == WACOM_HID_SP_BUTTON ||
		    subpage == WACOM_HID_SP_DIGITIZER ||
		    subpage == WACOM_HID_SP_DIGITIZERINFO ||
		    usage == WACOM_HID_WD_SENSE ||
		    usage == WACOM_HID_WD_SERIALHI ||
		    usage == WACOM_HID_WD_TOOLTYPE ||
		    usage == WACOM_HID_WD_DISTANCE ||
		    usage == WACOM_HID_WD_TOUCHSTRIP ||
		    usage == WACOM_HID_WD_TOUCHSTRIP2 ||
		    usage == WACOM_HID_WD_TOUCHRING ||
		    usage == WACOM_HID_WD_TOUCHRINGSTATUS ||
		    usage == WACOM_HID_WD_REPORT_VALID) अणु
			वापस usage;
		पूर्ण

		अगर (subpage == HID_UP_UNDEFINED)
			subpage = HID_UP_DIGITIZER;

		वापस subpage | subusage;
	पूर्ण

	अगर ((usage & HID_USAGE_PAGE) == WACOM_HID_UP_WACOMTOUCH) अणु
		पूर्णांक subpage = (usage & 0xFF00) << 8;
		पूर्णांक subusage = (usage & 0xFF);

		अगर (usage == WACOM_HID_WT_REPORT_VALID)
			वापस usage;

		अगर (subpage == HID_UP_UNDEFINED)
			subpage = WACOM_HID_SP_DIGITIZER;

		वापस subpage | subusage;
	पूर्ण

	वापस usage;
पूर्ण

अटल व्योम wacom_map_usage(काष्ठा input_dev *input, काष्ठा hid_usage *usage,
		काष्ठा hid_field *field, __u8 type, __u16 code, पूर्णांक fuzz)
अणु
	काष्ठा wacom *wacom = input_get_drvdata(input);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा wacom_features *features = &wacom_wac->features;
	पूर्णांक fmin = field->logical_minimum;
	पूर्णांक fmax = field->logical_maximum;
	अचिन्हित पूर्णांक equivalent_usage = wacom_equivalent_usage(usage->hid);
	पूर्णांक resolution_code = code;

	अगर (equivalent_usage == HID_DG_TWIST) अणु
		resolution_code = ABS_RZ;
	पूर्ण

	अगर (equivalent_usage == HID_GD_X) अणु
		fmin += features->offset_left;
		fmax -= features->offset_right;
	पूर्ण
	अगर (equivalent_usage == HID_GD_Y) अणु
		fmin += features->offset_top;
		fmax -= features->offset_bottom;
	पूर्ण

	usage->type = type;
	usage->code = code;

	चयन (type) अणु
	हाल EV_ABS:
		input_set_असल_params(input, code, fmin, fmax, fuzz, 0);
		input_असल_set_res(input, code,
				  hidinput_calc_असल_res(field, resolution_code));
		अवरोध;
	हाल EV_KEY:
	हाल EV_MSC:
	हाल EV_SW:
		input_set_capability(input, type, code);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम wacom_wac_battery_usage_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा wacom_features *features = &wacom_wac->features;
	अचिन्हित equivalent_usage = wacom_equivalent_usage(usage->hid);

	चयन (equivalent_usage) अणु
	हाल HID_DG_BATTERYSTRENGTH:
	हाल WACOM_HID_WD_BATTERY_LEVEL:
	हाल WACOM_HID_WD_BATTERY_CHARGING:
		features->quirks |= WACOM_QUIRK_BATTERY;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम wacom_wac_battery_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	अचिन्हित equivalent_usage = wacom_equivalent_usage(usage->hid);

	चयन (equivalent_usage) अणु
	हाल HID_DG_BATTERYSTRENGTH:
		अगर (value == 0) अणु
			wacom_wac->hid_data.bat_status = POWER_SUPPLY_STATUS_UNKNOWN;
		पूर्ण
		अन्यथा अणु
			value = value * 100 / (field->logical_maximum - field->logical_minimum);
			wacom_wac->hid_data.battery_capacity = value;
			wacom_wac->hid_data.bat_connected = 1;
			wacom_wac->hid_data.bat_status = WACOM_POWER_SUPPLY_STATUS_AUTO;
		पूर्ण
		अवरोध;
	हाल WACOM_HID_WD_BATTERY_LEVEL:
		value = value * 100 / (field->logical_maximum - field->logical_minimum);
		wacom_wac->hid_data.battery_capacity = value;
		wacom_wac->hid_data.bat_connected = 1;
		wacom_wac->hid_data.bat_status = WACOM_POWER_SUPPLY_STATUS_AUTO;
		अवरोध;
	हाल WACOM_HID_WD_BATTERY_CHARGING:
		wacom_wac->hid_data.bat_अक्षरging = value;
		wacom_wac->hid_data.ps_connected = value;
		wacom_wac->hid_data.bat_connected = 1;
		wacom_wac->hid_data.bat_status = WACOM_POWER_SUPPLY_STATUS_AUTO;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम wacom_wac_battery_pre_report(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report)
अणु
	वापस;
पूर्ण

अटल व्योम wacom_wac_battery_report(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा wacom_features *features = &wacom_wac->features;

	अगर (features->quirks & WACOM_QUIRK_BATTERY) अणु
		पूर्णांक status = wacom_wac->hid_data.bat_status;
		पूर्णांक capacity = wacom_wac->hid_data.battery_capacity;
		bool अक्षरging = wacom_wac->hid_data.bat_अक्षरging;
		bool connected = wacom_wac->hid_data.bat_connected;
		bool घातered = wacom_wac->hid_data.ps_connected;

		wacom_notअगरy_battery(wacom_wac, status, capacity, अक्षरging,
				     connected, घातered);
	पूर्ण
पूर्ण

अटल व्योम wacom_wac_pad_usage_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा wacom_features *features = &wacom_wac->features;
	काष्ठा input_dev *input = wacom_wac->pad_input;
	अचिन्हित equivalent_usage = wacom_equivalent_usage(usage->hid);

	चयन (equivalent_usage) अणु
	हाल WACOM_HID_WD_ACCELEROMETER_X:
		__set_bit(INPUT_PROP_ACCELEROMETER, input->propbit);
		wacom_map_usage(input, usage, field, EV_ABS, ABS_X, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		अवरोध;
	हाल WACOM_HID_WD_ACCELEROMETER_Y:
		__set_bit(INPUT_PROP_ACCELEROMETER, input->propbit);
		wacom_map_usage(input, usage, field, EV_ABS, ABS_Y, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		अवरोध;
	हाल WACOM_HID_WD_ACCELEROMETER_Z:
		__set_bit(INPUT_PROP_ACCELEROMETER, input->propbit);
		wacom_map_usage(input, usage, field, EV_ABS, ABS_Z, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		अवरोध;
	हाल WACOM_HID_WD_BUTTONCENTER:
	हाल WACOM_HID_WD_BUTTONHOME:
	हाल WACOM_HID_WD_BUTTONUP:
	हाल WACOM_HID_WD_BUTTONDOWN:
	हाल WACOM_HID_WD_BUTTONLEFT:
	हाल WACOM_HID_WD_BUTTONRIGHT:
		wacom_map_usage(input, usage, field, EV_KEY,
				wacom_numbered_button_to_key(features->numbered_buttons),
				0);
		features->numbered_buttons++;
		features->device_type |= WACOM_DEVICETYPE_PAD;
		अवरोध;
	हाल WACOM_HID_WD_TOUCHONOFF:
	हाल WACOM_HID_WD_MUTE_DEVICE:
		/*
		 * This usage, which is used to mute touch events, comes
		 * from the pad packet, but is reported on the touch
		 * पूर्णांकerface. Because the touch पूर्णांकerface may not have
		 * been created yet, we cannot call wacom_map_usage(). In
		 * order to process this usage when we receive it, we set
		 * the usage type and code directly.
		 */
		wacom_wac->has_mute_touch_चयन = true;
		usage->type = EV_SW;
		usage->code = SW_MUTE_DEVICE;
		features->device_type |= WACOM_DEVICETYPE_PAD;
		अवरोध;
	हाल WACOM_HID_WD_TOUCHSTRIP:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_RX, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		अवरोध;
	हाल WACOM_HID_WD_TOUCHSTRIP2:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_RY, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		अवरोध;
	हाल WACOM_HID_WD_TOUCHRING:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_WHEEL, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		अवरोध;
	हाल WACOM_HID_WD_TOUCHRINGSTATUS:
		/*
		 * Only set up type/code association. Completely mapping
		 * this usage may overग_लिखो the axis resolution and range.
		 */
		usage->type = EV_ABS;
		usage->code = ABS_WHEEL;
		set_bit(EV_ABS, input->evbit);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		अवरोध;
	हाल WACOM_HID_WD_BUTTONCONFIG:
		wacom_map_usage(input, usage, field, EV_KEY, KEY_BUTTONCONFIG, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		अवरोध;
	हाल WACOM_HID_WD_ONSCREEN_KEYBOARD:
		wacom_map_usage(input, usage, field, EV_KEY, KEY_ONSCREEN_KEYBOARD, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		अवरोध;
	हाल WACOM_HID_WD_CONTROLPANEL:
		wacom_map_usage(input, usage, field, EV_KEY, KEY_CONTROLPANEL, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		अवरोध;
	हाल WACOM_HID_WD_MODE_CHANGE:
		/* करो not overग_लिखो previous data */
		अगर (!wacom_wac->has_mode_change) अणु
			wacom_wac->has_mode_change = true;
			wacom_wac->is_direct_mode = true;
		पूर्ण
		features->device_type |= WACOM_DEVICETYPE_PAD;
		अवरोध;
	पूर्ण

	चयन (equivalent_usage & 0xfffffff0) अणु
	हाल WACOM_HID_WD_EXPRESSKEY00:
		wacom_map_usage(input, usage, field, EV_KEY,
				wacom_numbered_button_to_key(features->numbered_buttons),
				0);
		features->numbered_buttons++;
		features->device_type |= WACOM_DEVICETYPE_PAD;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम wacom_wac_pad_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा input_dev *input = wacom_wac->pad_input;
	काष्ठा wacom_features *features = &wacom_wac->features;
	अचिन्हित equivalent_usage = wacom_equivalent_usage(usage->hid);
	पूर्णांक i;
	bool करो_report = false;

	/*
	 * Aव्योम reporting this event and setting inrange_state अगर this usage
	 * hasn't been mapped.
	 */
	अगर (!usage->type && equivalent_usage != WACOM_HID_WD_MODE_CHANGE)
		वापस;

	अगर (wacom_equivalent_usage(field->physical) == HID_DG_TABLETFUNCTIONKEY) अणु
		अगर (usage->hid != WACOM_HID_WD_TOUCHRING)
			wacom_wac->hid_data.inrange_state |= value;
	पूर्ण

	चयन (equivalent_usage) अणु
	हाल WACOM_HID_WD_TOUCHRING:
		/*
		 * Userspace expects touchrings to increase in value with
		 * घड़ीwise gestures and have their zero poपूर्णांक at the
		 * tablet's left. HID events "should" be घड़ीwise-
		 * increasing and zero at top, though the MobileStudio
		 * Pro and 2nd-gen Intuos Pro करोn't करो this...
		 */
		अगर (hdev->venकरोr == 0x56a &&
		    (hdev->product == 0x34d || hdev->product == 0x34e ||  /* MobileStudio Pro */
		     hdev->product == 0x357 || hdev->product == 0x358 ||  /* Intuos Pro 2 */
		     hdev->product == 0x392 ||				  /* Intuos Pro 2 */
		     hdev->product == 0x398 || hdev->product == 0x399 ||  /* MobileStudio Pro */
		     hdev->product == 0x3AA)) अणु				  /* MobileStudio Pro */
			value = (field->logical_maximum - value);

			अगर (hdev->product == 0x357 || hdev->product == 0x358 ||
			    hdev->product == 0x392)
				value = wacom_offset_rotation(input, usage, value, 3, 16);
			अन्यथा अगर (hdev->product == 0x34d || hdev->product == 0x34e ||
				 hdev->product == 0x398 || hdev->product == 0x399 ||
				 hdev->product == 0x3AA)
				value = wacom_offset_rotation(input, usage, value, 1, 2);
		पूर्ण
		अन्यथा अणु
			value = wacom_offset_rotation(input, usage, value, 1, 4);
		पूर्ण
		करो_report = true;
		अवरोध;
	हाल WACOM_HID_WD_TOUCHRINGSTATUS:
		अगर (!value)
			input_event(input, usage->type, usage->code, 0);
		अवरोध;

	हाल WACOM_HID_WD_MUTE_DEVICE:
	हाल WACOM_HID_WD_TOUCHONOFF:
		अगर (wacom_wac->shared->touch_input) अणु
			bool *is_touch_on = &wacom_wac->shared->is_touch_on;

			अगर (equivalent_usage == WACOM_HID_WD_MUTE_DEVICE && value)
				*is_touch_on = !(*is_touch_on);
			अन्यथा अगर (equivalent_usage == WACOM_HID_WD_TOUCHONOFF)
				*is_touch_on = value;

			input_report_चयन(wacom_wac->shared->touch_input,
					    SW_MUTE_DEVICE, !(*is_touch_on));
			input_sync(wacom_wac->shared->touch_input);
		पूर्ण
		अवरोध;

	हाल WACOM_HID_WD_MODE_CHANGE:
		अगर (wacom_wac->is_direct_mode != value) अणु
			wacom_wac->is_direct_mode = value;
			wacom_schedule_work(&wacom->wacom_wac, WACOM_WORKER_MODE_CHANGE);
		पूर्ण
		अवरोध;

	हाल WACOM_HID_WD_BUTTONCENTER:
		क्रम (i = 0; i < wacom->led.count; i++)
			wacom_update_led(wacom, features->numbered_buttons,
					 value, i);
		fallthrough;
	शेष:
		करो_report = true;
		अवरोध;
	पूर्ण

	अगर (करो_report) अणु
		input_event(input, usage->type, usage->code, value);
		अगर (value)
			wacom_wac->hid_data.pad_input_event_flag = true;
	पूर्ण
पूर्ण

अटल व्योम wacom_wac_pad_pre_report(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;

	wacom_wac->hid_data.inrange_state = 0;
पूर्ण

अटल व्योम wacom_wac_pad_report(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, काष्ठा hid_field *field)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा input_dev *input = wacom_wac->pad_input;
	bool active = wacom_wac->hid_data.inrange_state != 0;

	/* report prox क्रम expresskey events */
	अगर (wacom_wac->hid_data.pad_input_event_flag) अणु
		input_event(input, EV_ABS, ABS_MISC, active ? PAD_DEVICE_ID : 0);
		input_sync(input);
		अगर (!active)
			wacom_wac->hid_data.pad_input_event_flag = false;
	पूर्ण
पूर्ण

अटल व्योम wacom_set_barrel_चयन3_usage(काष्ठा wacom_wac *wacom_wac)
अणु
	काष्ठा input_dev *input = wacom_wac->pen_input;
	काष्ठा wacom_features *features = &wacom_wac->features;

	अगर (!(features->quirks & WACOM_QUIRK_AESPEN) &&
	    wacom_wac->hid_data.barrelचयन &&
	    wacom_wac->hid_data.barrelचयन2 &&
	    wacom_wac->hid_data.serialhi)
		input_set_capability(input, EV_KEY, BTN_STYLUS3);
पूर्ण

अटल व्योम wacom_wac_pen_usage_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा wacom_features *features = &wacom_wac->features;
	काष्ठा input_dev *input = wacom_wac->pen_input;
	अचिन्हित equivalent_usage = wacom_equivalent_usage(usage->hid);

	चयन (equivalent_usage) अणु
	हाल HID_GD_X:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_X, 4);
		अवरोध;
	हाल HID_GD_Y:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_Y, 4);
		अवरोध;
	हाल WACOM_HID_WD_DISTANCE:
	हाल HID_GD_Z:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_DISTANCE, 0);
		अवरोध;
	हाल HID_DG_TIPPRESSURE:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_PRESSURE, 0);
		अवरोध;
	हाल HID_DG_INRANGE:
		wacom_map_usage(input, usage, field, EV_KEY, BTN_TOOL_PEN, 0);
		अवरोध;
	हाल HID_DG_INVERT:
		wacom_map_usage(input, usage, field, EV_KEY,
				BTN_TOOL_RUBBER, 0);
		अवरोध;
	हाल HID_DG_TILT_X:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_TILT_X, 0);
		अवरोध;
	हाल HID_DG_TILT_Y:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_TILT_Y, 0);
		अवरोध;
	हाल HID_DG_TWIST:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_Z, 0);
		अवरोध;
	हाल HID_DG_ERASER:
		input_set_capability(input, EV_KEY, BTN_TOOL_RUBBER);
		wacom_map_usage(input, usage, field, EV_KEY, BTN_TOUCH, 0);
		अवरोध;
	हाल HID_DG_TIPSWITCH:
		input_set_capability(input, EV_KEY, BTN_TOOL_PEN);
		wacom_map_usage(input, usage, field, EV_KEY, BTN_TOUCH, 0);
		अवरोध;
	हाल HID_DG_BARRELSWITCH:
		wacom_wac->hid_data.barrelचयन = true;
		wacom_set_barrel_चयन3_usage(wacom_wac);
		wacom_map_usage(input, usage, field, EV_KEY, BTN_STYLUS, 0);
		अवरोध;
	हाल HID_DG_BARRELSWITCH2:
		wacom_wac->hid_data.barrelचयन2 = true;
		wacom_set_barrel_चयन3_usage(wacom_wac);
		wacom_map_usage(input, usage, field, EV_KEY, BTN_STYLUS2, 0);
		अवरोध;
	हाल HID_DG_TOOLSERIALNUMBER:
		features->quirks |= WACOM_QUIRK_TOOLSERIAL;
		wacom_map_usage(input, usage, field, EV_MSC, MSC_SERIAL, 0);
		अवरोध;
	हाल WACOM_HID_WD_SENSE:
		features->quirks |= WACOM_QUIRK_SENSE;
		wacom_map_usage(input, usage, field, EV_KEY, BTN_TOOL_PEN, 0);
		अवरोध;
	हाल WACOM_HID_WD_SERIALHI:
		wacom_wac->hid_data.serialhi = true;
		wacom_set_barrel_चयन3_usage(wacom_wac);
		wacom_map_usage(input, usage, field, EV_ABS, ABS_MISC, 0);
		अवरोध;
	हाल WACOM_HID_WD_FINGERWHEEL:
		input_set_capability(input, EV_KEY, BTN_TOOL_AIRBRUSH);
		wacom_map_usage(input, usage, field, EV_ABS, ABS_WHEEL, 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम wacom_wac_pen_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा wacom_features *features = &wacom_wac->features;
	काष्ठा input_dev *input = wacom_wac->pen_input;
	अचिन्हित equivalent_usage = wacom_equivalent_usage(usage->hid);

	अगर (wacom_wac->is_invalid_bt_frame)
		वापस;

	चयन (equivalent_usage) अणु
	हाल HID_GD_Z:
		/*
		 * HID_GD_Z "should increase as the control's position is
		 * moved from high to low", जबतक ABS_DISTANCE instead
		 * increases in value as the tool moves from low to high.
		 */
		value = field->logical_maximum - value;
		अवरोध;
	हाल HID_DG_INRANGE:
		wacom_wac->hid_data.inrange_state = value;
		अगर (!(features->quirks & WACOM_QUIRK_SENSE))
			wacom_wac->hid_data.sense_state = value;
		वापस;
	हाल HID_DG_INVERT:
		wacom_wac->hid_data.invert_state = value;
		वापस;
	हाल HID_DG_ERASER:
	हाल HID_DG_TIPSWITCH:
		wacom_wac->hid_data.tipचयन |= value;
		वापस;
	हाल HID_DG_BARRELSWITCH:
		wacom_wac->hid_data.barrelचयन = value;
		वापस;
	हाल HID_DG_BARRELSWITCH2:
		wacom_wac->hid_data.barrelचयन2 = value;
		वापस;
	हाल HID_DG_TOOLSERIALNUMBER:
		अगर (value) अणु
			wacom_wac->serial[0] = (wacom_wac->serial[0] & ~0xFFFFFFFFULL);
			wacom_wac->serial[0] |= wacom_s32tou(value, field->report_size);
		पूर्ण
		वापस;
	हाल HID_DG_TWIST:
		/*
		 * Userspace expects pen twist to have its zero poपूर्णांक when
		 * the buttons/finger is on the tablet's left. HID values
		 * are zero when buttons are toward the top.
		 */
		value = wacom_offset_rotation(input, usage, value, 1, 4);
		अवरोध;
	हाल WACOM_HID_WD_SENSE:
		wacom_wac->hid_data.sense_state = value;
		वापस;
	हाल WACOM_HID_WD_SERIALHI:
		अगर (value) अणु
			__u32 raw_value = wacom_s32tou(value, field->report_size);

			wacom_wac->serial[0] = (wacom_wac->serial[0] & 0xFFFFFFFF);
			wacom_wac->serial[0] |= ((__u64)raw_value) << 32;
			/*
			 * Non-USI EMR devices may contain additional tool type
			 * inक्रमmation here. See WACOM_HID_WD_TOOLTYPE हाल क्रम
			 * more details.
			 */
			अगर (value >> 20 == 1) अणु
				wacom_wac->id[0] |= raw_value & 0xFFFFF;
			पूर्ण
		पूर्ण
		वापस;
	हाल WACOM_HID_WD_TOOLTYPE:
		/*
		 * Some devices (MobileStudio Pro, and possibly later
		 * devices as well) करो not वापस the complete tool
		 * type in their WACOM_HID_WD_TOOLTYPE usage. Use a
		 * bitwise OR so the complete value can be built
		 * up over समय :(
		 */
		wacom_wac->id[0] |= wacom_s32tou(value, field->report_size);
		वापस;
	हाल WACOM_HID_WD_OFFSETLEFT:
		अगर (features->offset_left && value != features->offset_left)
			hid_warn(hdev, "%s: overriding existing left offset "
				 "%d -> %d\n", __func__, value,
				 features->offset_left);
		features->offset_left = value;
		वापस;
	हाल WACOM_HID_WD_OFFSETRIGHT:
		अगर (features->offset_right && value != features->offset_right)
			hid_warn(hdev, "%s: overriding existing right offset "
				 "%d -> %d\n", __func__, value,
				 features->offset_right);
		features->offset_right = value;
		वापस;
	हाल WACOM_HID_WD_OFFSETTOP:
		अगर (features->offset_top && value != features->offset_top)
			hid_warn(hdev, "%s: overriding existing top offset "
				 "%d -> %d\n", __func__, value,
				 features->offset_top);
		features->offset_top = value;
		वापस;
	हाल WACOM_HID_WD_OFFSETBOTTOM:
		अगर (features->offset_bottom && value != features->offset_bottom)
			hid_warn(hdev, "%s: overriding existing bottom offset "
				 "%d -> %d\n", __func__, value,
				 features->offset_bottom);
		features->offset_bottom = value;
		वापस;
	हाल WACOM_HID_WD_REPORT_VALID:
		wacom_wac->is_invalid_bt_frame = !value;
		वापस;
	पूर्ण

	/* send pen events only when touch is up or क्रमced out
	 * or touch arbitration is off
	 */
	अगर (!usage->type || delay_pen_events(wacom_wac))
		वापस;

	/* send pen events only when the pen is in range */
	अगर (wacom_wac->hid_data.inrange_state)
		input_event(input, usage->type, usage->code, value);
	अन्यथा अगर (wacom_wac->shared->stylus_in_proximity && !wacom_wac->hid_data.sense_state)
		input_event(input, usage->type, usage->code, 0);
पूर्ण

अटल व्योम wacom_wac_pen_pre_report(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;

	wacom_wac->is_invalid_bt_frame = false;
	वापस;
पूर्ण

अटल व्योम wacom_wac_pen_report(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा input_dev *input = wacom_wac->pen_input;
	bool range = wacom_wac->hid_data.inrange_state;
	bool sense = wacom_wac->hid_data.sense_state;

	अगर (wacom_wac->is_invalid_bt_frame)
		वापस;

	अगर (!wacom_wac->tool[0] && range) अणु /* first in range */
		/* Going पूर्णांकo range select tool */
		अगर (wacom_wac->hid_data.invert_state)
			wacom_wac->tool[0] = BTN_TOOL_RUBBER;
		अन्यथा अगर (wacom_wac->id[0])
			wacom_wac->tool[0] = wacom_पूर्णांकuos_get_tool_type(wacom_wac->id[0]);
		अन्यथा
			wacom_wac->tool[0] = BTN_TOOL_PEN;
	पूर्ण

	/* keep pen state क्रम touch events */
	wacom_wac->shared->stylus_in_proximity = sense;

	अगर (!delay_pen_events(wacom_wac) && wacom_wac->tool[0]) अणु
		पूर्णांक id = wacom_wac->id[0];
		पूर्णांक sw_state = wacom_wac->hid_data.barrelचयन |
			       (wacom_wac->hid_data.barrelचयन2 << 1);

		input_report_key(input, BTN_STYLUS, sw_state == 1);
		input_report_key(input, BTN_STYLUS2, sw_state == 2);
		input_report_key(input, BTN_STYLUS3, sw_state == 3);

		/*
		 * Non-USI EMR tools should have their IDs mangled to
		 * match the legacy behavior of wacom_पूर्णांकuos_general
		 */
		अगर (wacom_wac->serial[0] >> 52 == 1)
			id = wacom_पूर्णांकuos_id_mangle(id);

		/*
		 * To ensure compatibility with xf86-input-wacom, we should
		 * report the BTN_TOOL_* event prior to the ABS_MISC or
		 * MSC_SERIAL events.
		 */
		input_report_key(input, BTN_TOUCH,
				wacom_wac->hid_data.tipचयन);
		input_report_key(input, wacom_wac->tool[0], sense);
		अगर (wacom_wac->serial[0]) अणु
			input_event(input, EV_MSC, MSC_SERIAL, wacom_wac->serial[0]);
			input_report_असल(input, ABS_MISC, sense ? id : 0);
		पूर्ण

		wacom_wac->hid_data.tipचयन = false;

		input_sync(input);
	पूर्ण

	अगर (!sense) अणु
		wacom_wac->tool[0] = 0;
		wacom_wac->id[0] = 0;
		wacom_wac->serial[0] = 0;
	पूर्ण
पूर्ण

अटल व्योम wacom_wac_finger_usage_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा input_dev *input = wacom_wac->touch_input;
	अचिन्हित touch_max = wacom_wac->features.touch_max;
	अचिन्हित equivalent_usage = wacom_equivalent_usage(usage->hid);

	चयन (equivalent_usage) अणु
	हाल HID_GD_X:
		अगर (touch_max == 1)
			wacom_map_usage(input, usage, field, EV_ABS, ABS_X, 4);
		अन्यथा
			wacom_map_usage(input, usage, field, EV_ABS,
					ABS_MT_POSITION_X, 4);
		अवरोध;
	हाल HID_GD_Y:
		अगर (touch_max == 1)
			wacom_map_usage(input, usage, field, EV_ABS, ABS_Y, 4);
		अन्यथा
			wacom_map_usage(input, usage, field, EV_ABS,
					ABS_MT_POSITION_Y, 4);
		अवरोध;
	हाल HID_DG_WIDTH:
	हाल HID_DG_HEIGHT:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_MT_TOUCH_MAJOR, 0);
		wacom_map_usage(input, usage, field, EV_ABS, ABS_MT_TOUCH_MINOR, 0);
		input_set_असल_params(input, ABS_MT_ORIENTATION, 0, 1, 0, 0);
		अवरोध;
	हाल HID_DG_TIPSWITCH:
		wacom_map_usage(input, usage, field, EV_KEY, BTN_TOUCH, 0);
		अवरोध;
	हाल HID_DG_CONTACTCOUNT:
		wacom_wac->hid_data.cc_report = field->report->id;
		wacom_wac->hid_data.cc_index = field->index;
		wacom_wac->hid_data.cc_value_index = usage->usage_index;
		अवरोध;
	हाल HID_DG_CONTACTID:
		अगर ((field->logical_maximum - field->logical_minimum) < touch_max) अणु
			/*
			 * The HID descriptor क्रम G11 sensors leaves logical
			 * maximum set to '1' despite it being a multitouch
			 * device. Override to a sensible number.
			 */
			field->logical_maximum = 255;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम wacom_wac_finger_slot(काष्ठा wacom_wac *wacom_wac,
		काष्ठा input_dev *input)
अणु
	काष्ठा hid_data *hid_data = &wacom_wac->hid_data;
	bool mt = wacom_wac->features.touch_max > 1;
	bool prox = hid_data->tipचयन &&
		    report_touch_events(wacom_wac);

	अगर (wacom_wac->shared->has_mute_touch_चयन &&
	    !wacom_wac->shared->is_touch_on) अणु
		अगर (!wacom_wac->shared->touch_करोwn)
			वापस;
		prox = false;
	पूर्ण

	wacom_wac->hid_data.num_received++;
	अगर (wacom_wac->hid_data.num_received > wacom_wac->hid_data.num_expected)
		वापस;

	अगर (mt) अणु
		पूर्णांक slot;

		slot = input_mt_get_slot_by_key(input, hid_data->id);
		input_mt_slot(input, slot);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, prox);
	पूर्ण
	अन्यथा अणु
		input_report_key(input, BTN_TOUCH, prox);
	पूर्ण

	अगर (prox) अणु
		input_report_असल(input, mt ? ABS_MT_POSITION_X : ABS_X,
				 hid_data->x);
		input_report_असल(input, mt ? ABS_MT_POSITION_Y : ABS_Y,
				 hid_data->y);

		अगर (test_bit(ABS_MT_TOUCH_MAJOR, input->असलbit)) अणु
			input_report_असल(input, ABS_MT_TOUCH_MAJOR, max(hid_data->width, hid_data->height));
			input_report_असल(input, ABS_MT_TOUCH_MINOR, min(hid_data->width, hid_data->height));
			अगर (hid_data->width != hid_data->height)
				input_report_असल(input, ABS_MT_ORIENTATION, hid_data->width <= hid_data->height ? 0 : 1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम wacom_wac_finger_event(काष्ठा hid_device *hdev,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	अचिन्हित equivalent_usage = wacom_equivalent_usage(usage->hid);
	काष्ठा wacom_features *features = &wacom->wacom_wac.features;

	अगर (wacom_wac->is_invalid_bt_frame)
		वापस;

	चयन (equivalent_usage) अणु
	हाल HID_GD_X:
		wacom_wac->hid_data.x = value;
		अवरोध;
	हाल HID_GD_Y:
		wacom_wac->hid_data.y = value;
		अवरोध;
	हाल HID_DG_WIDTH:
		wacom_wac->hid_data.width = value;
		अवरोध;
	हाल HID_DG_HEIGHT:
		wacom_wac->hid_data.height = value;
		अवरोध;
	हाल HID_DG_CONTACTID:
		wacom_wac->hid_data.id = value;
		अवरोध;
	हाल HID_DG_TIPSWITCH:
		wacom_wac->hid_data.tipचयन = value;
		अवरोध;
	हाल WACOM_HID_WT_REPORT_VALID:
		wacom_wac->is_invalid_bt_frame = !value;
		वापस;
	हाल HID_DG_CONTACTMAX:
		अगर (!features->touch_max) अणु
			features->touch_max = value;
		पूर्ण अन्यथा अणु
			hid_warn(hdev, "%s: ignoring attempt to overwrite non-zero touch_max "
				 "%d -> %d\n", __func__, features->touch_max, value);
		पूर्ण
		वापस;
	पूर्ण

	अगर (usage->usage_index + 1 == field->report_count) अणु
		अगर (equivalent_usage == wacom_wac->hid_data.last_slot_field)
			wacom_wac_finger_slot(wacom_wac, wacom_wac->touch_input);
	पूर्ण
पूर्ण

अटल व्योम wacom_wac_finger_pre_report(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा hid_data* hid_data = &wacom_wac->hid_data;
	पूर्णांक i;

	wacom_wac->is_invalid_bt_frame = false;

	क्रम (i = 0; i < report->maxfield; i++) अणु
		काष्ठा hid_field *field = report->field[i];
		पूर्णांक j;

		क्रम (j = 0; j < field->maxusage; j++) अणु
			काष्ठा hid_usage *usage = &field->usage[j];
			अचिन्हित पूर्णांक equivalent_usage =
				wacom_equivalent_usage(usage->hid);

			चयन (equivalent_usage) अणु
			हाल HID_GD_X:
			हाल HID_GD_Y:
			हाल HID_DG_WIDTH:
			हाल HID_DG_HEIGHT:
			हाल HID_DG_CONTACTID:
			हाल HID_DG_INRANGE:
			हाल HID_DG_INVERT:
			हाल HID_DG_TIPSWITCH:
				hid_data->last_slot_field = equivalent_usage;
				अवरोध;
			हाल HID_DG_CONTACTCOUNT:
				hid_data->cc_report = report->id;
				hid_data->cc_index = i;
				hid_data->cc_value_index = j;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (hid_data->cc_report != 0 &&
	    hid_data->cc_index >= 0) अणु
		काष्ठा hid_field *field = report->field[hid_data->cc_index];
		पूर्णांक value = field->value[hid_data->cc_value_index];
		अगर (value)
			hid_data->num_expected = value;
	पूर्ण
	अन्यथा अणु
		hid_data->num_expected = wacom_wac->features.touch_max;
	पूर्ण
पूर्ण

अटल व्योम wacom_wac_finger_report(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा input_dev *input = wacom_wac->touch_input;
	अचिन्हित touch_max = wacom_wac->features.touch_max;

	/* If more packets of data are expected, give us a chance to
	 * process them rather than immediately syncing a partial
	 * update.
	 */
	अगर (wacom_wac->hid_data.num_received < wacom_wac->hid_data.num_expected)
		वापस;

	अगर (touch_max > 1)
		input_mt_sync_frame(input);

	input_sync(input);
	wacom_wac->hid_data.num_received = 0;

	/* keep touch state क्रम pen event */
	wacom_wac->shared->touch_करोwn = wacom_wac_finger_count_touches(wacom_wac);
पूर्ण

व्योम wacom_wac_usage_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा wacom_features *features = &wacom_wac->features;

	अगर (WACOM_सूचीECT_DEVICE(field))
		features->device_type |= WACOM_DEVICETYPE_सूचीECT;

	/* usage tests must precede field tests */
	अगर (WACOM_BATTERY_USAGE(usage))
		wacom_wac_battery_usage_mapping(hdev, field, usage);
	अन्यथा अगर (WACOM_PAD_FIELD(field))
		wacom_wac_pad_usage_mapping(hdev, field, usage);
	अन्यथा अगर (WACOM_PEN_FIELD(field))
		wacom_wac_pen_usage_mapping(hdev, field, usage);
	अन्यथा अगर (WACOM_FINGER_FIELD(field))
		wacom_wac_finger_usage_mapping(hdev, field, usage);
पूर्ण

व्योम wacom_wac_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);

	अगर (wacom->wacom_wac.features.type != HID_GENERIC)
		वापस;

	अगर (value > field->logical_maximum || value < field->logical_minimum)
		वापस;

	/* usage tests must precede field tests */
	अगर (WACOM_BATTERY_USAGE(usage))
		wacom_wac_battery_event(hdev, field, usage, value);
	अन्यथा अगर (WACOM_PAD_FIELD(field) && wacom->wacom_wac.pad_input)
		wacom_wac_pad_event(hdev, field, usage, value);
	अन्यथा अगर (WACOM_PEN_FIELD(field) && wacom->wacom_wac.pen_input)
		wacom_wac_pen_event(hdev, field, usage, value);
	अन्यथा अगर (WACOM_FINGER_FIELD(field) && wacom->wacom_wac.touch_input)
		wacom_wac_finger_event(hdev, field, usage, value);
पूर्ण

अटल व्योम wacom_report_events(काष्ठा hid_device *hdev,
				काष्ठा hid_report *report, पूर्णांक collection_index,
				पूर्णांक field_index)
अणु
	पूर्णांक r;

	क्रम (r = field_index; r < report->maxfield; r++) अणु
		काष्ठा hid_field *field;
		अचिन्हित count, n;

		field = report->field[r];
		count = field->report_count;

		अगर (!(HID_MAIN_ITEM_VARIABLE & field->flags))
			जारी;

		क्रम (n = 0 ; n < count; n++) अणु
			अगर (field->usage[n].collection_index == collection_index)
				wacom_wac_event(hdev, field, &field->usage[n],
						field->value[n]);
			अन्यथा
				वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक wacom_wac_collection(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
			 पूर्णांक collection_index, काष्ठा hid_field *field,
			 पूर्णांक field_index)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);

	wacom_report_events(hdev, report, collection_index, field_index);

	/*
	 * Non-input reports may be sent prior to the device being
	 * completely initialized. Since only their events need
	 * to be processed, निकास after 'wacom_report_events' has
	 * been called to prevent potential crashes in the report-
	 * processing functions.
	 */
	अगर (report->type != HID_INPUT_REPORT)
		वापस -1;

	अगर (WACOM_PAD_FIELD(field))
		वापस 0;
	अन्यथा अगर (WACOM_PEN_FIELD(field) && wacom->wacom_wac.pen_input)
		wacom_wac_pen_report(hdev, report);
	अन्यथा अगर (WACOM_FINGER_FIELD(field) && wacom->wacom_wac.touch_input)
		wacom_wac_finger_report(hdev, report);

	वापस 0;
पूर्ण

व्योम wacom_wac_report(काष्ठा hid_device *hdev, काष्ठा hid_report *report)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा hid_field *field;
	bool pad_in_hid_field = false, pen_in_hid_field = false,
		finger_in_hid_field = false, true_pad = false;
	पूर्णांक r;
	पूर्णांक prev_collection = -1;

	अगर (wacom_wac->features.type != HID_GENERIC)
		वापस;

	क्रम (r = 0; r < report->maxfield; r++) अणु
		field = report->field[r];

		अगर (WACOM_PAD_FIELD(field))
			pad_in_hid_field = true;
		अगर (WACOM_PEN_FIELD(field))
			pen_in_hid_field = true;
		अगर (WACOM_FINGER_FIELD(field))
			finger_in_hid_field = true;
		अगर (wacom_equivalent_usage(field->physical) == HID_DG_TABLETFUNCTIONKEY)
			true_pad = true;
	पूर्ण

	wacom_wac_battery_pre_report(hdev, report);

	अगर (pad_in_hid_field && wacom->wacom_wac.pad_input)
		wacom_wac_pad_pre_report(hdev, report);
	अगर (pen_in_hid_field && wacom->wacom_wac.pen_input)
		wacom_wac_pen_pre_report(hdev, report);
	अगर (finger_in_hid_field && wacom->wacom_wac.touch_input)
		wacom_wac_finger_pre_report(hdev, report);

	क्रम (r = 0; r < report->maxfield; r++) अणु
		field = report->field[r];

		अगर (field->usage[0].collection_index != prev_collection) अणु
			अगर (wacom_wac_collection(hdev, report,
				field->usage[0].collection_index, field, r) < 0)
				वापस;
			prev_collection = field->usage[0].collection_index;
		पूर्ण
	पूर्ण

	wacom_wac_battery_report(hdev, report);

	अगर (true_pad && wacom->wacom_wac.pad_input)
		wacom_wac_pad_report(hdev, report, field);
पूर्ण

अटल पूर्णांक wacom_bpt_touch(काष्ठा wacom_wac *wacom)
अणु
	काष्ठा wacom_features *features = &wacom->features;
	काष्ठा input_dev *input = wacom->touch_input;
	काष्ठा input_dev *pad_input = wacom->pad_input;
	अचिन्हित अक्षर *data = wacom->data;
	पूर्णांक i;

	अगर (data[0] != 0x02)
	    वापस 0;

	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांक offset = (data[1] & 0x80) ? (8 * i) : (9 * i);
		bool touch = report_touch_events(wacom)
			   && (data[offset + 3] & 0x80);

		input_mt_slot(input, i);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, touch);
		अगर (touch) अणु
			पूर्णांक x = get_unaligned_be16(&data[offset + 3]) & 0x7ff;
			पूर्णांक y = get_unaligned_be16(&data[offset + 5]) & 0x7ff;
			अगर (features->quirks & WACOM_QUIRK_BBTOUCH_LOWRES) अणु
				x <<= 5;
				y <<= 5;
			पूर्ण
			input_report_असल(input, ABS_MT_POSITION_X, x);
			input_report_असल(input, ABS_MT_POSITION_Y, y);
		पूर्ण
	पूर्ण

	input_mt_sync_frame(input);

	input_report_key(pad_input, BTN_LEFT, (data[1] & 0x08) != 0);
	input_report_key(pad_input, BTN_FORWARD, (data[1] & 0x04) != 0);
	input_report_key(pad_input, BTN_BACK, (data[1] & 0x02) != 0);
	input_report_key(pad_input, BTN_RIGHT, (data[1] & 0x01) != 0);
	wacom->shared->touch_करोwn = wacom_wac_finger_count_touches(wacom);

	वापस 1;
पूर्ण

अटल व्योम wacom_bpt3_touch_msg(काष्ठा wacom_wac *wacom, अचिन्हित अक्षर *data)
अणु
	काष्ठा wacom_features *features = &wacom->features;
	काष्ठा input_dev *input = wacom->touch_input;
	bool touch = data[1] & 0x80;
	पूर्णांक slot = input_mt_get_slot_by_key(input, data[0]);

	अगर (slot < 0)
		वापस;

	touch = touch && report_touch_events(wacom);

	input_mt_slot(input, slot);
	input_mt_report_slot_state(input, MT_TOOL_FINGER, touch);

	अगर (touch) अणु
		पूर्णांक x = (data[2] << 4) | (data[4] >> 4);
		पूर्णांक y = (data[3] << 4) | (data[4] & 0x0f);
		पूर्णांक width, height;

		अगर (features->type >= INTUOSPS && features->type <= INTUOSHT2) अणु
			width  = data[5] * 100;
			height = data[6] * 100;
		पूर्ण अन्यथा अणु
			/*
			 * "a" is a scaled-करोwn area which we assume is
			 * roughly circular and which can be described as:
			 * a=(pi*r^2)/C.
			 */
			पूर्णांक a = data[5];
			पूर्णांक x_res = input_असल_get_res(input, ABS_MT_POSITION_X);
			पूर्णांक y_res = input_असल_get_res(input, ABS_MT_POSITION_Y);
			width = 2 * पूर्णांक_वर्ग_मूल(a * WACOM_CONTACT_AREA_SCALE);
			height = width * y_res / x_res;
		पूर्ण

		input_report_असल(input, ABS_MT_POSITION_X, x);
		input_report_असल(input, ABS_MT_POSITION_Y, y);
		input_report_असल(input, ABS_MT_TOUCH_MAJOR, width);
		input_report_असल(input, ABS_MT_TOUCH_MINOR, height);
	पूर्ण
पूर्ण

अटल व्योम wacom_bpt3_button_msg(काष्ठा wacom_wac *wacom, अचिन्हित अक्षर *data)
अणु
	काष्ठा input_dev *input = wacom->pad_input;
	काष्ठा wacom_features *features = &wacom->features;

	अगर (features->type == INTUOSHT || features->type == INTUOSHT2) अणु
		input_report_key(input, BTN_LEFT, (data[1] & 0x02) != 0);
		input_report_key(input, BTN_BACK, (data[1] & 0x08) != 0);
	पूर्ण अन्यथा अणु
		input_report_key(input, BTN_BACK, (data[1] & 0x02) != 0);
		input_report_key(input, BTN_LEFT, (data[1] & 0x08) != 0);
	पूर्ण
	input_report_key(input, BTN_FORWARD, (data[1] & 0x04) != 0);
	input_report_key(input, BTN_RIGHT, (data[1] & 0x01) != 0);
पूर्ण

अटल पूर्णांक wacom_bpt3_touch(काष्ठा wacom_wac *wacom)
अणु
	अचिन्हित अक्षर *data = wacom->data;
	पूर्णांक count = data[1] & 0x07;
	पूर्णांक  touch_changed = 0, i;

	अगर (data[0] != 0x02)
	    वापस 0;

	/* data has up to 7 fixed sized 8-byte messages starting at data[2] */
	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक offset = (8 * i) + 2;
		पूर्णांक msg_id = data[offset];

		अगर (msg_id >= 2 && msg_id <= 17) अणु
			wacom_bpt3_touch_msg(wacom, data + offset);
			touch_changed++;
		पूर्ण अन्यथा अगर (msg_id == 128)
			wacom_bpt3_button_msg(wacom, data + offset);

	पूर्ण

	/* only update touch अगर we actually have a touchpad and touch data changed */
	अगर (wacom->touch_input && touch_changed) अणु
		input_mt_sync_frame(wacom->touch_input);
		wacom->shared->touch_करोwn = wacom_wac_finger_count_touches(wacom);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक wacom_bpt_pen(काष्ठा wacom_wac *wacom)
अणु
	काष्ठा wacom_features *features = &wacom->features;
	काष्ठा input_dev *input = wacom->pen_input;
	अचिन्हित अक्षर *data = wacom->data;
	पूर्णांक x = 0, y = 0, p = 0, d = 0;
	bool pen = false, btn1 = false, btn2 = false;
	bool range, prox, rdy;

	अगर (data[0] != WACOM_REPORT_PENABLED)
	    वापस 0;

	range = (data[1] & 0x80) == 0x80;
	prox = (data[1] & 0x40) == 0x40;
	rdy = (data[1] & 0x20) == 0x20;

	wacom->shared->stylus_in_proximity = range;
	अगर (delay_pen_events(wacom))
		वापस 0;

	अगर (rdy) अणु
		p = le16_to_cpup((__le16 *)&data[6]);
		pen = data[1] & 0x01;
		btn1 = data[1] & 0x02;
		btn2 = data[1] & 0x04;
	पूर्ण
	अगर (prox) अणु
		x = le16_to_cpup((__le16 *)&data[2]);
		y = le16_to_cpup((__le16 *)&data[4]);

		अगर (data[1] & 0x08) अणु
			wacom->tool[0] = BTN_TOOL_RUBBER;
			wacom->id[0] = ERASER_DEVICE_ID;
		पूर्ण अन्यथा अणु
			wacom->tool[0] = BTN_TOOL_PEN;
			wacom->id[0] = STYLUS_DEVICE_ID;
		पूर्ण
		wacom->reporting_data = true;
	पूर्ण
	अगर (range) अणु
		/*
		 * Convert distance from out prox to distance from tablet.
		 * distance will be greater than distance_max once
		 * touching and applying pressure; करो not report negative
		 * distance.
		 */
		अगर (data[8] <= features->distance_max)
			d = features->distance_max - data[8];
	पूर्ण अन्यथा अणु
		wacom->id[0] = 0;
	पूर्ण

	अगर (wacom->reporting_data) अणु
		input_report_key(input, BTN_TOUCH, pen);
		input_report_key(input, BTN_STYLUS, btn1);
		input_report_key(input, BTN_STYLUS2, btn2);

		अगर (prox || !range) अणु
			input_report_असल(input, ABS_X, x);
			input_report_असल(input, ABS_Y, y);
		पूर्ण
		input_report_असल(input, ABS_PRESSURE, p);
		input_report_असल(input, ABS_DISTANCE, d);

		input_report_key(input, wacom->tool[0], range); /* PEN or RUBBER */
		input_report_असल(input, ABS_MISC, wacom->id[0]); /* TOOL ID */
	पूर्ण

	अगर (!range) अणु
		wacom->reporting_data = false;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक wacom_bpt_irq(काष्ठा wacom_wac *wacom, माप_प्रकार len)
अणु
	काष्ठा wacom_features *features = &wacom->features;

	अगर ((features->type == INTUOSHT2) &&
	    (features->device_type & WACOM_DEVICETYPE_PEN))
		वापस wacom_पूर्णांकuos_irq(wacom);
	अन्यथा अगर (len == WACOM_PKGLEN_BBTOUCH)
		वापस wacom_bpt_touch(wacom);
	अन्यथा अगर (len == WACOM_PKGLEN_BBTOUCH3)
		वापस wacom_bpt3_touch(wacom);
	अन्यथा अगर (len == WACOM_PKGLEN_BBFUN || len == WACOM_PKGLEN_BBPEN)
		वापस wacom_bpt_pen(wacom);

	वापस 0;
पूर्ण

अटल व्योम wacom_bamboo_pad_pen_event(काष्ठा wacom_wac *wacom,
		अचिन्हित अक्षर *data)
अणु
	अचिन्हित अक्षर prefix;

	/*
	 * We need to reroute the event from the debug पूर्णांकerface to the
	 * pen पूर्णांकerface.
	 * We need to add the report ID to the actual pen report, so we
	 * temporary overग_लिखो the first byte to prevent having to kzalloc/kमुक्त
	 * and स_नकल the report.
	 */
	prefix = data[0];
	data[0] = WACOM_REPORT_BPAD_PEN;

	/*
	 * actually reroute the event.
	 * No need to check अगर wacom->shared->pen is valid, hid_input_report()
	 * will check क्रम us.
	 */
	hid_input_report(wacom->shared->pen, HID_INPUT_REPORT, data,
			 WACOM_PKGLEN_PENABLED, 1);

	data[0] = prefix;
पूर्ण

अटल पूर्णांक wacom_bamboo_pad_touch_event(काष्ठा wacom_wac *wacom,
		अचिन्हित अक्षर *data)
अणु
	काष्ठा input_dev *input = wacom->touch_input;
	अचिन्हित अक्षर *finger_data, prefix;
	अचिन्हित id;
	पूर्णांक x, y;
	bool valid;

	prefix = data[0];

	क्रम (id = 0; id < wacom->features.touch_max; id++) अणु
		valid = !!(prefix & BIT(id)) &&
			report_touch_events(wacom);

		input_mt_slot(input, id);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, valid);

		अगर (!valid)
			जारी;

		finger_data = data + 1 + id * 3;
		x = finger_data[0] | ((finger_data[1] & 0x0f) << 8);
		y = (finger_data[2] << 4) | (finger_data[1] >> 4);

		input_report_असल(input, ABS_MT_POSITION_X, x);
		input_report_असल(input, ABS_MT_POSITION_Y, y);
	पूर्ण

	input_mt_sync_frame(input);

	input_report_key(input, BTN_LEFT, prefix & 0x40);
	input_report_key(input, BTN_RIGHT, prefix & 0x80);

	/* keep touch state क्रम pen event */
	wacom->shared->touch_करोwn = !!prefix && report_touch_events(wacom);

	वापस 1;
पूर्ण

अटल पूर्णांक wacom_bamboo_pad_irq(काष्ठा wacom_wac *wacom, माप_प्रकार len)
अणु
	अचिन्हित अक्षर *data = wacom->data;

	अगर (!((len == WACOM_PKGLEN_BPAD_TOUCH) ||
	      (len == WACOM_PKGLEN_BPAD_TOUCH_USB)) ||
	    (data[0] != WACOM_REPORT_BPAD_TOUCH))
		वापस 0;

	अगर (data[1] & 0x01)
		wacom_bamboo_pad_pen_event(wacom, &data[1]);

	अगर (data[1] & 0x02)
		वापस wacom_bamboo_pad_touch_event(wacom, &data[9]);

	वापस 0;
पूर्ण

अटल पूर्णांक wacom_wireless_irq(काष्ठा wacom_wac *wacom, माप_प्रकार len)
अणु
	अचिन्हित अक्षर *data = wacom->data;
	पूर्णांक connected;

	अगर (len != WACOM_PKGLEN_WIRELESS || data[0] != WACOM_REPORT_WL)
		वापस 0;

	connected = data[1] & 0x01;
	अगर (connected) अणु
		पूर्णांक pid, battery, अक्षरging;

		अगर ((wacom->shared->type == INTUOSHT ||
		    wacom->shared->type == INTUOSHT2) &&
		    wacom->shared->touch_input &&
		    wacom->shared->touch_max) अणु
			input_report_चयन(wacom->shared->touch_input,
					SW_MUTE_DEVICE, data[5] & 0x40);
			input_sync(wacom->shared->touch_input);
		पूर्ण

		pid = get_unaligned_be16(&data[6]);
		battery = (data[5] & 0x3f) * 100 / 31;
		अक्षरging = !!(data[5] & 0x80);
		अगर (wacom->pid != pid) अणु
			wacom->pid = pid;
			wacom_schedule_work(wacom, WACOM_WORKER_WIRELESS);
		पूर्ण

		wacom_notअगरy_battery(wacom, WACOM_POWER_SUPPLY_STATUS_AUTO,
				     battery, अक्षरging, 1, 0);

	पूर्ण अन्यथा अगर (wacom->pid != 0) अणु
		/* disconnected जबतक previously connected */
		wacom->pid = 0;
		wacom_schedule_work(wacom, WACOM_WORKER_WIRELESS);
		wacom_notअगरy_battery(wacom, POWER_SUPPLY_STATUS_UNKNOWN, 0, 0, 0, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wacom_status_irq(काष्ठा wacom_wac *wacom_wac, माप_प्रकार len)
अणु
	काष्ठा wacom *wacom = container_of(wacom_wac, काष्ठा wacom, wacom_wac);
	काष्ठा wacom_features *features = &wacom_wac->features;
	अचिन्हित अक्षर *data = wacom_wac->data;

	अगर (data[0] != WACOM_REPORT_USB)
		वापस 0;

	अगर ((features->type == INTUOSHT ||
	    features->type == INTUOSHT2) &&
	    wacom_wac->shared->touch_input &&
	    features->touch_max) अणु
		input_report_चयन(wacom_wac->shared->touch_input,
				    SW_MUTE_DEVICE, data[8] & 0x40);
		input_sync(wacom_wac->shared->touch_input);
	पूर्ण

	अगर (data[9] & 0x02) अणु /* wireless module is attached */
		पूर्णांक battery = (data[8] & 0x3f) * 100 / 31;
		bool अक्षरging = !!(data[8] & 0x80);

		wacom_notअगरy_battery(wacom_wac, WACOM_POWER_SUPPLY_STATUS_AUTO,
				     battery, अक्षरging, battery || अक्षरging, 1);

		अगर (!wacom->battery.battery &&
		    !(features->quirks & WACOM_QUIRK_BATTERY)) अणु
			features->quirks |= WACOM_QUIRK_BATTERY;
			wacom_schedule_work(wacom_wac, WACOM_WORKER_BATTERY);
		पूर्ण
	पूर्ण
	अन्यथा अगर ((features->quirks & WACOM_QUIRK_BATTERY) &&
		 wacom->battery.battery) अणु
		features->quirks &= ~WACOM_QUIRK_BATTERY;
		wacom_schedule_work(wacom_wac, WACOM_WORKER_BATTERY);
		wacom_notअगरy_battery(wacom_wac, POWER_SUPPLY_STATUS_UNKNOWN, 0, 0, 0, 0);
	पूर्ण
	वापस 0;
पूर्ण

व्योम wacom_wac_irq(काष्ठा wacom_wac *wacom_wac, माप_प्रकार len)
अणु
	bool sync;

	चयन (wacom_wac->features.type) अणु
	हाल PENPARTNER:
		sync = wacom_penpartner_irq(wacom_wac);
		अवरोध;

	हाल PL:
		sync = wacom_pl_irq(wacom_wac);
		अवरोध;

	हाल WACOM_G4:
	हाल GRAPHIRE:
	हाल GRAPHIRE_BT:
	हाल WACOM_MO:
		sync = wacom_graphire_irq(wacom_wac);
		अवरोध;

	हाल PTU:
		sync = wacom_ptu_irq(wacom_wac);
		अवरोध;

	हाल DTU:
		sync = wacom_dtu_irq(wacom_wac);
		अवरोध;

	हाल DTUS:
	हाल DTUSX:
		sync = wacom_dtus_irq(wacom_wac);
		अवरोध;

	हाल INTUOS:
	हाल INTUOS3S:
	हाल INTUOS3:
	हाल INTUOS3L:
	हाल INTUOS4S:
	हाल INTUOS4:
	हाल INTUOS4L:
	हाल CINTIQ:
	हाल WACOM_BEE:
	हाल WACOM_13HD:
	हाल WACOM_21UX2:
	हाल WACOM_22HD:
	हाल WACOM_24HD:
	हाल WACOM_27QHD:
	हाल DTK:
	हाल CINTIQ_HYBRID:
	हाल CINTIQ_COMPANION_2:
		sync = wacom_पूर्णांकuos_irq(wacom_wac);
		अवरोध;

	हाल INTUOS4WL:
		sync = wacom_पूर्णांकuos_bt_irq(wacom_wac, len);
		अवरोध;

	हाल WACOM_24HDT:
	हाल WACOM_27QHDT:
		sync = wacom_24hdt_irq(wacom_wac);
		अवरोध;

	हाल INTUOS5S:
	हाल INTUOS5:
	हाल INTUOS5L:
	हाल INTUOSPS:
	हाल INTUOSPM:
	हाल INTUOSPL:
		अगर (len == WACOM_PKGLEN_BBTOUCH3)
			sync = wacom_bpt3_touch(wacom_wac);
		अन्यथा अगर (wacom_wac->data[0] == WACOM_REPORT_USB)
			sync = wacom_status_irq(wacom_wac, len);
		अन्यथा
			sync = wacom_पूर्णांकuos_irq(wacom_wac);
		अवरोध;

	हाल INTUOSP2_BT:
	हाल INTUOSP2S_BT:
	हाल INTUOSHT3_BT:
		sync = wacom_पूर्णांकuos_pro2_bt_irq(wacom_wac, len);
		अवरोध;

	हाल TABLETPC:
	हाल TABLETPCE:
	हाल TABLETPC2FG:
	हाल MTSCREEN:
	हाल MTTPC:
	हाल MTTPC_B:
		sync = wacom_tpc_irq(wacom_wac, len);
		अवरोध;

	हाल BAMBOO_PT:
	हाल BAMBOO_PEN:
	हाल BAMBOO_TOUCH:
	हाल INTUOSHT:
	हाल INTUOSHT2:
		अगर (wacom_wac->data[0] == WACOM_REPORT_USB)
			sync = wacom_status_irq(wacom_wac, len);
		अन्यथा
			sync = wacom_bpt_irq(wacom_wac, len);
		अवरोध;

	हाल BAMBOO_PAD:
		sync = wacom_bamboo_pad_irq(wacom_wac, len);
		अवरोध;

	हाल WIRELESS:
		sync = wacom_wireless_irq(wacom_wac, len);
		अवरोध;

	हाल REMOTE:
		sync = false;
		अगर (wacom_wac->data[0] == WACOM_REPORT_DEVICE_LIST)
			wacom_remote_status_irq(wacom_wac, len);
		अन्यथा
			sync = wacom_remote_irq(wacom_wac, len);
		अवरोध;

	शेष:
		sync = false;
		अवरोध;
	पूर्ण

	अगर (sync) अणु
		अगर (wacom_wac->pen_input)
			input_sync(wacom_wac->pen_input);
		अगर (wacom_wac->touch_input)
			input_sync(wacom_wac->touch_input);
		अगर (wacom_wac->pad_input)
			input_sync(wacom_wac->pad_input);
	पूर्ण
पूर्ण

अटल व्योम wacom_setup_basic_pro_pen(काष्ठा wacom_wac *wacom_wac)
अणु
	काष्ठा input_dev *input_dev = wacom_wac->pen_input;

	input_set_capability(input_dev, EV_MSC, MSC_SERIAL);

	__set_bit(BTN_TOOL_PEN, input_dev->keybit);
	__set_bit(BTN_STYLUS, input_dev->keybit);
	__set_bit(BTN_STYLUS2, input_dev->keybit);

	input_set_असल_params(input_dev, ABS_DISTANCE,
			     0, wacom_wac->features.distance_max, wacom_wac->features.distance_fuzz, 0);
पूर्ण

अटल व्योम wacom_setup_cपूर्णांकiq(काष्ठा wacom_wac *wacom_wac)
अणु
	काष्ठा input_dev *input_dev = wacom_wac->pen_input;
	काष्ठा wacom_features *features = &wacom_wac->features;

	wacom_setup_basic_pro_pen(wacom_wac);

	__set_bit(BTN_TOOL_RUBBER, input_dev->keybit);
	__set_bit(BTN_TOOL_BRUSH, input_dev->keybit);
	__set_bit(BTN_TOOL_PENCIL, input_dev->keybit);
	__set_bit(BTN_TOOL_AIRBRUSH, input_dev->keybit);

	input_set_असल_params(input_dev, ABS_WHEEL, 0, 1023, 0, 0);
	input_set_असल_params(input_dev, ABS_TILT_X, -64, 63, features->tilt_fuzz, 0);
	input_असल_set_res(input_dev, ABS_TILT_X, 57);
	input_set_असल_params(input_dev, ABS_TILT_Y, -64, 63, features->tilt_fuzz, 0);
	input_असल_set_res(input_dev, ABS_TILT_Y, 57);
पूर्ण

अटल व्योम wacom_setup_पूर्णांकuos(काष्ठा wacom_wac *wacom_wac)
अणु
	काष्ठा input_dev *input_dev = wacom_wac->pen_input;

	input_set_capability(input_dev, EV_REL, REL_WHEEL);

	wacom_setup_cपूर्णांकiq(wacom_wac);

	__set_bit(BTN_LEFT, input_dev->keybit);
	__set_bit(BTN_RIGHT, input_dev->keybit);
	__set_bit(BTN_MIDDLE, input_dev->keybit);
	__set_bit(BTN_SIDE, input_dev->keybit);
	__set_bit(BTN_EXTRA, input_dev->keybit);
	__set_bit(BTN_TOOL_MOUSE, input_dev->keybit);
	__set_bit(BTN_TOOL_LENS, input_dev->keybit);

	input_set_असल_params(input_dev, ABS_RZ, -900, 899, 0, 0);
	input_असल_set_res(input_dev, ABS_RZ, 287);
	input_set_असल_params(input_dev, ABS_THROTTLE, -1023, 1023, 0, 0);
पूर्ण

व्योम wacom_setup_device_quirks(काष्ठा wacom *wacom)
अणु
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा wacom_features *features = &wacom->wacom_wac.features;

	/* The pen and pad share the same पूर्णांकerface on most devices */
	अगर (features->type == GRAPHIRE_BT || features->type == WACOM_G4 ||
	    features->type == DTUS ||
	    (features->type >= INTUOS3S && features->type <= WACOM_MO)) अणु
		अगर (features->device_type & WACOM_DEVICETYPE_PEN)
			features->device_type |= WACOM_DEVICETYPE_PAD;
	पूर्ण

	/* touch device found but size is not defined. use शेष */
	अगर (features->device_type & WACOM_DEVICETYPE_TOUCH && !features->x_max) अणु
		features->x_max = 1023;
		features->y_max = 1023;
	पूर्ण

	/*
	 * Intuos5/Pro and Bamboo 3rd gen have no useful data about its
	 * touch पूर्णांकerface in its HID descriptor. If this is the touch
	 * पूर्णांकerface (PacketSize of WACOM_PKGLEN_BBTOUCH3), override the
	 * tablet values.
	 */
	अगर ((features->type >= INTUOS5S && features->type <= INTUOSPL) ||
		(features->type >= INTUOSHT && features->type <= BAMBOO_PT)) अणु
		अगर (features->pktlen == WACOM_PKGLEN_BBTOUCH3) अणु
			अगर (features->touch_max)
				features->device_type |= WACOM_DEVICETYPE_TOUCH;
			अगर (features->type >= INTUOSHT && features->type <= BAMBOO_PT)
				features->device_type |= WACOM_DEVICETYPE_PAD;

			अगर (features->type == INTUOSHT2) अणु
				features->x_max = features->x_max / 10;
				features->y_max = features->y_max / 10;
			पूर्ण
			अन्यथा अणु
				features->x_max = 4096;
				features->y_max = 4096;
			पूर्ण
		पूर्ण
		अन्यथा अगर (features->pktlen == WACOM_PKGLEN_BBTOUCH) अणु
			features->device_type |= WACOM_DEVICETYPE_PAD;
		पूर्ण
	पूर्ण

	/*
	 * Hack क्रम the Bamboo One:
	 * the device presents a PAD/Touch पूर्णांकerface as most Bamboos and even
	 * sends ghosts PAD data on it. However, later, we must disable this
	 * ghost पूर्णांकerface, and we can not detect it unless we set it here
	 * to WACOM_DEVICETYPE_PAD or WACOM_DEVICETYPE_TOUCH.
	 */
	अगर (features->type == BAMBOO_PEN &&
	    features->pktlen == WACOM_PKGLEN_BBTOUCH3)
		features->device_type |= WACOM_DEVICETYPE_PAD;

	/*
	 * Raw Wacom-mode pen and touch events both come from पूर्णांकerface
	 * 0, whose HID descriptor has an application usage of 0xFF0D
	 * (i.e., WACOM_HID_WD_DIGITIZER). We route pen packets back
	 * out through the HID_GENERIC device created क्रम पूर्णांकerface 1,
	 * so reग_लिखो this one to be of type WACOM_DEVICETYPE_TOUCH.
	 */
	अगर (features->type == BAMBOO_PAD)
		features->device_type = WACOM_DEVICETYPE_TOUCH;

	अगर (features->type == REMOTE)
		features->device_type = WACOM_DEVICETYPE_PAD;

	अगर (features->type == INTUOSP2_BT ||
	    features->type == INTUOSP2S_BT) अणु
		features->device_type |= WACOM_DEVICETYPE_PEN |
					 WACOM_DEVICETYPE_PAD |
					 WACOM_DEVICETYPE_TOUCH;
		features->quirks |= WACOM_QUIRK_BATTERY;
	पूर्ण

	अगर (features->type == INTUOSHT3_BT) अणु
		features->device_type |= WACOM_DEVICETYPE_PEN |
					 WACOM_DEVICETYPE_PAD;
		features->quirks |= WACOM_QUIRK_BATTERY;
	पूर्ण

	चयन (features->type) अणु
	हाल PL:
	हाल DTU:
	हाल DTUS:
	हाल DTUSX:
	हाल WACOM_21UX2:
	हाल WACOM_22HD:
	हाल DTK:
	हाल WACOM_24HD:
	हाल WACOM_27QHD:
	हाल CINTIQ_HYBRID:
	हाल CINTIQ_COMPANION_2:
	हाल CINTIQ:
	हाल WACOM_BEE:
	हाल WACOM_13HD:
	हाल WACOM_24HDT:
	हाल WACOM_27QHDT:
	हाल TABLETPC:
	हाल TABLETPCE:
	हाल TABLETPC2FG:
	हाल MTSCREEN:
	हाल MTTPC:
	हाल MTTPC_B:
		features->device_type |= WACOM_DEVICETYPE_सूचीECT;
		अवरोध;
	पूर्ण

	अगर (wacom->hdev->bus == BUS_BLUETOOTH)
		features->quirks |= WACOM_QUIRK_BATTERY;

	/* quirk क्रम bamboo touch with 2 low res touches */
	अगर ((features->type == BAMBOO_PT || features->type == BAMBOO_TOUCH) &&
	    features->pktlen == WACOM_PKGLEN_BBTOUCH) अणु
		features->x_max <<= 5;
		features->y_max <<= 5;
		features->x_fuzz <<= 5;
		features->y_fuzz <<= 5;
		features->quirks |= WACOM_QUIRK_BBTOUCH_LOWRES;
	पूर्ण

	अगर (features->type == WIRELESS) अणु
		अगर (features->device_type == WACOM_DEVICETYPE_WL_MONITOR) अणु
			features->quirks |= WACOM_QUIRK_BATTERY;
		पूर्ण
	पूर्ण

	अगर (features->type == REMOTE)
		features->device_type |= WACOM_DEVICETYPE_WL_MONITOR;

	/* HID descriptor क्रम DTK-2451 / DTH-2452 claims to report lots
	 * of things it shouldn't. Lets fix up the damage...
	 */
	अगर (wacom->hdev->product == 0x382 || wacom->hdev->product == 0x37d) अणु
		features->quirks &= ~WACOM_QUIRK_TOOLSERIAL;
		__clear_bit(BTN_TOOL_BRUSH, wacom_wac->pen_input->keybit);
		__clear_bit(BTN_TOOL_PENCIL, wacom_wac->pen_input->keybit);
		__clear_bit(BTN_TOOL_AIRBRUSH, wacom_wac->pen_input->keybit);
		__clear_bit(ABS_Z, wacom_wac->pen_input->असलbit);
		__clear_bit(ABS_DISTANCE, wacom_wac->pen_input->असलbit);
		__clear_bit(ABS_TILT_X, wacom_wac->pen_input->असलbit);
		__clear_bit(ABS_TILT_Y, wacom_wac->pen_input->असलbit);
		__clear_bit(ABS_WHEEL, wacom_wac->pen_input->असलbit);
		__clear_bit(ABS_MISC, wacom_wac->pen_input->असलbit);
		__clear_bit(MSC_SERIAL, wacom_wac->pen_input->mscbit);
		__clear_bit(EV_MSC, wacom_wac->pen_input->evbit);
	पूर्ण
पूर्ण

पूर्णांक wacom_setup_pen_input_capabilities(काष्ठा input_dev *input_dev,
				   काष्ठा wacom_wac *wacom_wac)
अणु
	काष्ठा wacom_features *features = &wacom_wac->features;

	अगर (!(features->device_type & WACOM_DEVICETYPE_PEN))
		वापस -ENODEV;

	अगर (features->device_type & WACOM_DEVICETYPE_सूचीECT)
		__set_bit(INPUT_PROP_सूचीECT, input_dev->propbit);
	अन्यथा
		__set_bit(INPUT_PROP_POINTER, input_dev->propbit);

	अगर (features->type == HID_GENERIC)
		/* setup has alपढ़ोy been करोne */
		वापस 0;

	input_dev->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	__set_bit(BTN_TOUCH, input_dev->keybit);
	__set_bit(ABS_MISC, input_dev->असलbit);

	input_set_असल_params(input_dev, ABS_X, 0 + features->offset_left,
			     features->x_max - features->offset_right,
			     features->x_fuzz, 0);
	input_set_असल_params(input_dev, ABS_Y, 0 + features->offset_top,
			     features->y_max - features->offset_bottom,
			     features->y_fuzz, 0);
	input_set_असल_params(input_dev, ABS_PRESSURE, 0,
		features->pressure_max, features->pressure_fuzz, 0);

	/* penabled devices have fixed resolution क्रम each model */
	input_असल_set_res(input_dev, ABS_X, features->x_resolution);
	input_असल_set_res(input_dev, ABS_Y, features->y_resolution);

	चयन (features->type) अणु
	हाल GRAPHIRE_BT:
		__clear_bit(ABS_MISC, input_dev->असलbit);
		fallthrough;

	हाल WACOM_MO:
	हाल WACOM_G4:
		input_set_असल_params(input_dev, ABS_DISTANCE, 0,
					      features->distance_max,
					      features->distance_fuzz, 0);
		fallthrough;

	हाल GRAPHIRE:
		input_set_capability(input_dev, EV_REL, REL_WHEEL);

		__set_bit(BTN_LEFT, input_dev->keybit);
		__set_bit(BTN_RIGHT, input_dev->keybit);
		__set_bit(BTN_MIDDLE, input_dev->keybit);

		__set_bit(BTN_TOOL_RUBBER, input_dev->keybit);
		__set_bit(BTN_TOOL_PEN, input_dev->keybit);
		__set_bit(BTN_TOOL_MOUSE, input_dev->keybit);
		__set_bit(BTN_STYLUS, input_dev->keybit);
		__set_bit(BTN_STYLUS2, input_dev->keybit);
		अवरोध;

	हाल WACOM_27QHD:
	हाल WACOM_24HD:
	हाल DTK:
	हाल WACOM_22HD:
	हाल WACOM_21UX2:
	हाल WACOM_BEE:
	हाल CINTIQ:
	हाल WACOM_13HD:
	हाल CINTIQ_HYBRID:
	हाल CINTIQ_COMPANION_2:
		input_set_असल_params(input_dev, ABS_Z, -900, 899, 0, 0);
		input_असल_set_res(input_dev, ABS_Z, 287);
		wacom_setup_cपूर्णांकiq(wacom_wac);
		अवरोध;

	हाल INTUOS3:
	हाल INTUOS3L:
	हाल INTUOS3S:
	हाल INTUOS4:
	हाल INTUOS4WL:
	हाल INTUOS4L:
	हाल INTUOS4S:
		input_set_असल_params(input_dev, ABS_Z, -900, 899, 0, 0);
		input_असल_set_res(input_dev, ABS_Z, 287);
		fallthrough;

	हाल INTUOS:
		wacom_setup_पूर्णांकuos(wacom_wac);
		अवरोध;

	हाल INTUOS5:
	हाल INTUOS5L:
	हाल INTUOSPM:
	हाल INTUOSPL:
	हाल INTUOS5S:
	हाल INTUOSPS:
	हाल INTUOSP2_BT:
	हाल INTUOSP2S_BT:
		input_set_असल_params(input_dev, ABS_DISTANCE, 0,
				      features->distance_max,
				      features->distance_fuzz, 0);

		input_set_असल_params(input_dev, ABS_Z, -900, 899, 0, 0);
		input_असल_set_res(input_dev, ABS_Z, 287);

		wacom_setup_पूर्णांकuos(wacom_wac);
		अवरोध;

	हाल WACOM_24HDT:
	हाल WACOM_27QHDT:
	हाल MTSCREEN:
	हाल MTTPC:
	हाल MTTPC_B:
	हाल TABLETPC2FG:
	हाल TABLETPC:
	हाल TABLETPCE:
		__clear_bit(ABS_MISC, input_dev->असलbit);
		fallthrough;

	हाल DTUS:
	हाल DTUSX:
	हाल PL:
	हाल DTU:
		__set_bit(BTN_TOOL_PEN, input_dev->keybit);
		__set_bit(BTN_TOOL_RUBBER, input_dev->keybit);
		__set_bit(BTN_STYLUS, input_dev->keybit);
		__set_bit(BTN_STYLUS2, input_dev->keybit);
		अवरोध;

	हाल PTU:
		__set_bit(BTN_STYLUS2, input_dev->keybit);
		fallthrough;

	हाल PENPARTNER:
		__set_bit(BTN_TOOL_PEN, input_dev->keybit);
		__set_bit(BTN_TOOL_RUBBER, input_dev->keybit);
		__set_bit(BTN_STYLUS, input_dev->keybit);
		अवरोध;

	हाल INTUOSHT:
	हाल BAMBOO_PT:
	हाल BAMBOO_PEN:
	हाल INTUOSHT2:
	हाल INTUOSHT3_BT:
		अगर (features->type == INTUOSHT2 ||
		    features->type == INTUOSHT3_BT) अणु
			wacom_setup_basic_pro_pen(wacom_wac);
		पूर्ण अन्यथा अणु
			__clear_bit(ABS_MISC, input_dev->असलbit);
			__set_bit(BTN_TOOL_PEN, input_dev->keybit);
			__set_bit(BTN_TOOL_RUBBER, input_dev->keybit);
			__set_bit(BTN_STYLUS, input_dev->keybit);
			__set_bit(BTN_STYLUS2, input_dev->keybit);
			input_set_असल_params(input_dev, ABS_DISTANCE, 0,
				      features->distance_max,
				      features->distance_fuzz, 0);
		पूर्ण
		अवरोध;
	हाल BAMBOO_PAD:
		__clear_bit(ABS_MISC, input_dev->असलbit);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक wacom_setup_touch_input_capabilities(काष्ठा input_dev *input_dev,
					 काष्ठा wacom_wac *wacom_wac)
अणु
	काष्ठा wacom_features *features = &wacom_wac->features;

	अगर (!(features->device_type & WACOM_DEVICETYPE_TOUCH))
		वापस -ENODEV;

	अगर (features->device_type & WACOM_DEVICETYPE_सूचीECT)
		__set_bit(INPUT_PROP_सूचीECT, input_dev->propbit);
	अन्यथा
		__set_bit(INPUT_PROP_POINTER, input_dev->propbit);

	अगर (features->type == HID_GENERIC)
		/* setup has alपढ़ोy been करोne */
		वापस 0;

	input_dev->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	__set_bit(BTN_TOUCH, input_dev->keybit);

	अगर (features->touch_max == 1) अणु
		input_set_असल_params(input_dev, ABS_X, 0,
			features->x_max, features->x_fuzz, 0);
		input_set_असल_params(input_dev, ABS_Y, 0,
			features->y_max, features->y_fuzz, 0);
		input_असल_set_res(input_dev, ABS_X,
				  features->x_resolution);
		input_असल_set_res(input_dev, ABS_Y,
				  features->y_resolution);
	पूर्ण
	अन्यथा अगर (features->touch_max > 1) अणु
		input_set_असल_params(input_dev, ABS_MT_POSITION_X, 0,
			features->x_max, features->x_fuzz, 0);
		input_set_असल_params(input_dev, ABS_MT_POSITION_Y, 0,
			features->y_max, features->y_fuzz, 0);
		input_असल_set_res(input_dev, ABS_MT_POSITION_X,
				  features->x_resolution);
		input_असल_set_res(input_dev, ABS_MT_POSITION_Y,
				  features->y_resolution);
	पूर्ण

	चयन (features->type) अणु
	हाल INTUOSP2_BT:
	हाल INTUOSP2S_BT:
		input_dev->evbit[0] |= BIT_MASK(EV_SW);
		__set_bit(SW_MUTE_DEVICE, input_dev->swbit);

		अगर (wacom_wac->shared->touch->product == 0x361) अणु
			input_set_असल_params(input_dev, ABS_MT_POSITION_X,
					     0, 12440, 4, 0);
			input_set_असल_params(input_dev, ABS_MT_POSITION_Y,
					     0, 8640, 4, 0);
		पूर्ण
		अन्यथा अगर (wacom_wac->shared->touch->product == 0x360) अणु
			input_set_असल_params(input_dev, ABS_MT_POSITION_X,
					     0, 8960, 4, 0);
			input_set_असल_params(input_dev, ABS_MT_POSITION_Y,
					     0, 5920, 4, 0);
		पूर्ण
		अन्यथा अगर (wacom_wac->shared->touch->product == 0x393) अणु
			input_set_असल_params(input_dev, ABS_MT_POSITION_X,
					     0, 6400, 4, 0);
			input_set_असल_params(input_dev, ABS_MT_POSITION_Y,
					     0, 4000, 4, 0);
		पूर्ण
		input_असल_set_res(input_dev, ABS_MT_POSITION_X, 40);
		input_असल_set_res(input_dev, ABS_MT_POSITION_Y, 40);

		fallthrough;

	हाल INTUOS5:
	हाल INTUOS5L:
	हाल INTUOSPM:
	हाल INTUOSPL:
	हाल INTUOS5S:
	हाल INTUOSPS:
		input_set_असल_params(input_dev, ABS_MT_TOUCH_MAJOR, 0, features->x_max, 0, 0);
		input_set_असल_params(input_dev, ABS_MT_TOUCH_MINOR, 0, features->y_max, 0, 0);
		input_mt_init_slots(input_dev, features->touch_max, INPUT_MT_POINTER);
		अवरोध;

	हाल WACOM_24HDT:
		input_set_असल_params(input_dev, ABS_MT_TOUCH_MAJOR, 0, features->x_max, 0, 0);
		input_set_असल_params(input_dev, ABS_MT_WIDTH_MAJOR, 0, features->x_max, 0, 0);
		input_set_असल_params(input_dev, ABS_MT_WIDTH_MINOR, 0, features->y_max, 0, 0);
		input_set_असल_params(input_dev, ABS_MT_ORIENTATION, 0, 1, 0, 0);
		fallthrough;

	हाल WACOM_27QHDT:
		अगर (wacom_wac->shared->touch->product == 0x32C ||
		    wacom_wac->shared->touch->product == 0xF6) अणु
			input_dev->evbit[0] |= BIT_MASK(EV_SW);
			__set_bit(SW_MUTE_DEVICE, input_dev->swbit);
			wacom_wac->shared->has_mute_touch_चयन = true;
		पूर्ण
		fallthrough;

	हाल MTSCREEN:
	हाल MTTPC:
	हाल MTTPC_B:
	हाल TABLETPC2FG:
		input_mt_init_slots(input_dev, features->touch_max, INPUT_MT_सूचीECT);
		fallthrough;

	हाल TABLETPC:
	हाल TABLETPCE:
		अवरोध;

	हाल INTUOSHT:
	हाल INTUOSHT2:
		input_dev->evbit[0] |= BIT_MASK(EV_SW);
		__set_bit(SW_MUTE_DEVICE, input_dev->swbit);
		fallthrough;

	हाल BAMBOO_PT:
	हाल BAMBOO_TOUCH:
		अगर (features->pktlen == WACOM_PKGLEN_BBTOUCH3) अणु
			input_set_असल_params(input_dev,
				     ABS_MT_TOUCH_MAJOR,
				     0, features->x_max, 0, 0);
			input_set_असल_params(input_dev,
				     ABS_MT_TOUCH_MINOR,
				     0, features->y_max, 0, 0);
		पूर्ण
		input_mt_init_slots(input_dev, features->touch_max, INPUT_MT_POINTER);
		अवरोध;

	हाल BAMBOO_PAD:
		input_mt_init_slots(input_dev, features->touch_max,
				    INPUT_MT_POINTER);
		__set_bit(BTN_LEFT, input_dev->keybit);
		__set_bit(BTN_RIGHT, input_dev->keybit);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wacom_numbered_button_to_key(पूर्णांक n)
अणु
	अगर (n < 10)
		वापस BTN_0 + n;
	अन्यथा अगर (n < 16)
		वापस BTN_A + (n-10);
	अन्यथा अगर (n < 18)
		वापस BTN_BASE + (n-16);
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम wacom_setup_numbered_buttons(काष्ठा input_dev *input_dev,
				पूर्णांक button_count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < button_count; i++) अणु
		पूर्णांक key = wacom_numbered_button_to_key(i);

		अगर (key)
			__set_bit(key, input_dev->keybit);
	पूर्ण
पूर्ण

अटल व्योम wacom_24hd_update_leds(काष्ठा wacom *wacom, पूर्णांक mask, पूर्णांक group)
अणु
	काष्ठा wacom_led *led;
	पूर्णांक i;
	bool updated = false;

	/*
	 * 24HD has LED group 1 to the left and LED group 0 to the right.
	 * So group 0 matches the second half of the buttons and thus the mask
	 * needs to be shअगरted.
	 */
	अगर (group == 0)
		mask >>= 8;

	क्रम (i = 0; i < 3; i++) अणु
		led = wacom_led_find(wacom, group, i);
		अगर (!led) अणु
			hid_err(wacom->hdev, "can't find LED %d in group %d\n",
				i, group);
			जारी;
		पूर्ण
		अगर (!updated && mask & BIT(i)) अणु
			led->held = true;
			led_trigger_event(&led->trigger, LED_FULL);
		पूर्ण अन्यथा अणु
			led->held = false;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool wacom_is_led_toggled(काष्ठा wacom *wacom, पूर्णांक button_count,
				 पूर्णांक mask, पूर्णांक group)
अणु
	पूर्णांक group_button;

	/*
	 * 21UX2 has LED group 1 to the left and LED group 0
	 * to the right. We need to reverse the group to match this
	 * historical behavior.
	 */
	अगर (wacom->wacom_wac.features.type == WACOM_21UX2)
		group = 1 - group;

	group_button = group * (button_count/wacom->led.count);

	अगर (wacom->wacom_wac.features.type == INTUOSP2_BT)
		group_button = 8;

	वापस mask & (1 << group_button);
पूर्ण

अटल व्योम wacom_update_led(काष्ठा wacom *wacom, पूर्णांक button_count, पूर्णांक mask,
			     पूर्णांक group)
अणु
	काष्ठा wacom_led *led, *next_led;
	पूर्णांक cur;
	bool pressed;

	अगर (wacom->wacom_wac.features.type == WACOM_24HD)
		वापस wacom_24hd_update_leds(wacom, mask, group);

	pressed = wacom_is_led_toggled(wacom, button_count, mask, group);
	cur = wacom->led.groups[group].select;

	led = wacom_led_find(wacom, group, cur);
	अगर (!led) अणु
		hid_err(wacom->hdev, "can't find current LED %d in group %d\n",
			cur, group);
		वापस;
	पूर्ण

	अगर (!pressed) अणु
		led->held = false;
		वापस;
	पूर्ण

	अगर (led->held && pressed)
		वापस;

	next_led = wacom_led_next(wacom, led);
	अगर (!next_led) अणु
		hid_err(wacom->hdev, "can't find next LED in group %d\n",
			group);
		वापस;
	पूर्ण
	अगर (next_led == led)
		वापस;

	next_led->held = true;
	led_trigger_event(&next_led->trigger,
			  wacom_leds_brightness_get(next_led));
पूर्ण

अटल व्योम wacom_report_numbered_buttons(काष्ठा input_dev *input_dev,
				पूर्णांक button_count, पूर्णांक mask)
अणु
	काष्ठा wacom *wacom = input_get_drvdata(input_dev);
	पूर्णांक i;

	क्रम (i = 0; i < wacom->led.count; i++)
		wacom_update_led(wacom,  button_count, mask, i);

	क्रम (i = 0; i < button_count; i++) अणु
		पूर्णांक key = wacom_numbered_button_to_key(i);

		अगर (key)
			input_report_key(input_dev, key, mask & (1 << i));
	पूर्ण
पूर्ण

पूर्णांक wacom_setup_pad_input_capabilities(काष्ठा input_dev *input_dev,
				   काष्ठा wacom_wac *wacom_wac)
अणु
	काष्ठा wacom_features *features = &wacom_wac->features;

	अगर ((features->type == HID_GENERIC) && features->numbered_buttons > 0)
		features->device_type |= WACOM_DEVICETYPE_PAD;

	अगर (!(features->device_type & WACOM_DEVICETYPE_PAD))
		वापस -ENODEV;

	अगर (features->type == REMOTE && input_dev == wacom_wac->pad_input)
		वापस -ENODEV;

	input_dev->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	/* kept क्रम making legacy xf86-input-wacom working with the wheels */
	__set_bit(ABS_MISC, input_dev->असलbit);

	/* kept क्रम making legacy xf86-input-wacom accepting the pad */
	अगर (!(input_dev->असलinfo && (input_dev->असलinfo[ABS_X].minimum ||
	      input_dev->असलinfo[ABS_X].maximum)))
		input_set_असल_params(input_dev, ABS_X, 0, 1, 0, 0);
	अगर (!(input_dev->असलinfo && (input_dev->असलinfo[ABS_Y].minimum ||
	      input_dev->असलinfo[ABS_Y].maximum)))
		input_set_असल_params(input_dev, ABS_Y, 0, 1, 0, 0);

	/* kept क्रम making udev and libwacom accepting the pad */
	__set_bit(BTN_STYLUS, input_dev->keybit);

	wacom_setup_numbered_buttons(input_dev, features->numbered_buttons);

	चयन (features->type) अणु

	हाल CINTIQ_HYBRID:
	हाल CINTIQ_COMPANION_2:
	हाल DTK:
	हाल DTUS:
	हाल GRAPHIRE_BT:
		अवरोध;

	हाल WACOM_MO:
		__set_bit(BTN_BACK, input_dev->keybit);
		__set_bit(BTN_LEFT, input_dev->keybit);
		__set_bit(BTN_FORWARD, input_dev->keybit);
		__set_bit(BTN_RIGHT, input_dev->keybit);
		input_set_असल_params(input_dev, ABS_WHEEL, 0, 71, 0, 0);
		अवरोध;

	हाल WACOM_G4:
		__set_bit(BTN_BACK, input_dev->keybit);
		__set_bit(BTN_FORWARD, input_dev->keybit);
		input_set_capability(input_dev, EV_REL, REL_WHEEL);
		अवरोध;

	हाल WACOM_24HD:
		__set_bit(KEY_PROG1, input_dev->keybit);
		__set_bit(KEY_PROG2, input_dev->keybit);
		__set_bit(KEY_PROG3, input_dev->keybit);

		__set_bit(KEY_ONSCREEN_KEYBOARD, input_dev->keybit);
		__set_bit(KEY_INFO, input_dev->keybit);

		अगर (!features->oPid)
			__set_bit(KEY_BUTTONCONFIG, input_dev->keybit);

		input_set_असल_params(input_dev, ABS_WHEEL, 0, 71, 0, 0);
		input_set_असल_params(input_dev, ABS_THROTTLE, 0, 71, 0, 0);
		अवरोध;

	हाल WACOM_27QHD:
		__set_bit(KEY_PROG1, input_dev->keybit);
		__set_bit(KEY_PROG2, input_dev->keybit);
		__set_bit(KEY_PROG3, input_dev->keybit);

		__set_bit(KEY_ONSCREEN_KEYBOARD, input_dev->keybit);
		__set_bit(KEY_BUTTONCONFIG, input_dev->keybit);

		अगर (!features->oPid)
			__set_bit(KEY_CONTROLPANEL, input_dev->keybit);
		input_set_असल_params(input_dev, ABS_X, -2048, 2048, 0, 0);
		input_असल_set_res(input_dev, ABS_X, 1024); /* poपूर्णांकs/g */
		input_set_असल_params(input_dev, ABS_Y, -2048, 2048, 0, 0);
		input_असल_set_res(input_dev, ABS_Y, 1024);
		input_set_असल_params(input_dev, ABS_Z, -2048, 2048, 0, 0);
		input_असल_set_res(input_dev, ABS_Z, 1024);
		__set_bit(INPUT_PROP_ACCELEROMETER, input_dev->propbit);
		अवरोध;

	हाल WACOM_22HD:
		__set_bit(KEY_PROG1, input_dev->keybit);
		__set_bit(KEY_PROG2, input_dev->keybit);
		__set_bit(KEY_PROG3, input_dev->keybit);

		__set_bit(KEY_BUTTONCONFIG, input_dev->keybit);
		__set_bit(KEY_INFO, input_dev->keybit);
		fallthrough;

	हाल WACOM_21UX2:
	हाल WACOM_BEE:
	हाल CINTIQ:
		input_set_असल_params(input_dev, ABS_RX, 0, 4096, 0, 0);
		input_set_असल_params(input_dev, ABS_RY, 0, 4096, 0, 0);
		अवरोध;

	हाल WACOM_13HD:
		input_set_असल_params(input_dev, ABS_WHEEL, 0, 71, 0, 0);
		अवरोध;

	हाल INTUOS3:
	हाल INTUOS3L:
		input_set_असल_params(input_dev, ABS_RY, 0, 4096, 0, 0);
		fallthrough;

	हाल INTUOS3S:
		input_set_असल_params(input_dev, ABS_RX, 0, 4096, 0, 0);
		अवरोध;

	हाल INTUOS5:
	हाल INTUOS5L:
	हाल INTUOSPM:
	हाल INTUOSPL:
	हाल INTUOS5S:
	हाल INTUOSPS:
	हाल INTUOSP2_BT:
	हाल INTUOSP2S_BT:
		input_set_असल_params(input_dev, ABS_WHEEL, 0, 71, 0, 0);
		अवरोध;

	हाल INTUOS4WL:
		/*
		 * For Bluetooth devices, the udev rule करोes not work correctly
		 * क्रम pads unless we add a stylus capability, which क्रमces
		 * ID_INPUT_TABLET to be set.
		 */
		__set_bit(BTN_STYLUS, input_dev->keybit);
		fallthrough;

	हाल INTUOS4:
	हाल INTUOS4L:
	हाल INTUOS4S:
		input_set_असल_params(input_dev, ABS_WHEEL, 0, 71, 0, 0);
		अवरोध;

	हाल INTUOSHT:
	हाल BAMBOO_PT:
	हाल BAMBOO_TOUCH:
	हाल INTUOSHT2:
		__clear_bit(ABS_MISC, input_dev->असलbit);

		__set_bit(BTN_LEFT, input_dev->keybit);
		__set_bit(BTN_FORWARD, input_dev->keybit);
		__set_bit(BTN_BACK, input_dev->keybit);
		__set_bit(BTN_RIGHT, input_dev->keybit);

		अवरोध;

	हाल REMOTE:
		input_set_capability(input_dev, EV_MSC, MSC_SERIAL);
		input_set_असल_params(input_dev, ABS_WHEEL, 0, 71, 0, 0);
		अवरोध;

	हाल INTUOSHT3_BT:
	हाल HID_GENERIC:
		अवरोध;

	शेष:
		/* no pad supported */
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा wacom_features wacom_features_0x00 =
	अणु "Wacom Penpartner", 5040, 3780, 255, 0,
	  PENPARTNER, WACOM_PENPRTN_RES, WACOM_PENPRTN_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x10 =
	अणु "Wacom Graphire", 10206, 7422, 511, 63,
	  GRAPHIRE, WACOM_GRAPHIRE_RES, WACOM_GRAPHIRE_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x81 =
	अणु "Wacom Graphire BT", 16704, 12064, 511, 32,
	  GRAPHIRE_BT, WACOM_GRAPHIRE_RES, WACOM_GRAPHIRE_RES, 2 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x11 =
	अणु "Wacom Graphire2 4x5", 10206, 7422, 511, 63,
	  GRAPHIRE, WACOM_GRAPHIRE_RES, WACOM_GRAPHIRE_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x12 =
	अणु "Wacom Graphire2 5x7", 13918, 10206, 511, 63,
	  GRAPHIRE, WACOM_GRAPHIRE_RES, WACOM_GRAPHIRE_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x13 =
	अणु "Wacom Graphire3", 10208, 7424, 511, 63,
	  GRAPHIRE, WACOM_GRAPHIRE_RES, WACOM_GRAPHIRE_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x14 =
	अणु "Wacom Graphire3 6x8", 16704, 12064, 511, 63,
	  GRAPHIRE, WACOM_GRAPHIRE_RES, WACOM_GRAPHIRE_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x15 =
	अणु "Wacom Graphire4 4x5", 10208, 7424, 511, 63,
	  WACOM_G4, WACOM_GRAPHIRE_RES, WACOM_GRAPHIRE_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x16 =
	अणु "Wacom Graphire4 6x8", 16704, 12064, 511, 63,
	  WACOM_G4, WACOM_GRAPHIRE_RES, WACOM_GRAPHIRE_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x17 =
	अणु "Wacom BambooFun 4x5", 14760, 9225, 511, 63,
	  WACOM_MO, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x18 =
	अणु "Wacom BambooFun 6x8", 21648, 13530, 511, 63,
	  WACOM_MO, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x19 =
	अणु "Wacom Bamboo1 Medium", 16704, 12064, 511, 63,
	  GRAPHIRE, WACOM_GRAPHIRE_RES, WACOM_GRAPHIRE_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x60 =
	अणु "Wacom Volito", 5104, 3712, 511, 63,
	  GRAPHIRE, WACOM_VOLITO_RES, WACOM_VOLITO_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x61 =
	अणु "Wacom PenStation2", 3250, 2320, 255, 63,
	  GRAPHIRE, WACOM_VOLITO_RES, WACOM_VOLITO_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x62 =
	अणु "Wacom Volito2 4x5", 5104, 3712, 511, 63,
	  GRAPHIRE, WACOM_VOLITO_RES, WACOM_VOLITO_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x63 =
	अणु "Wacom Volito2 2x3", 3248, 2320, 511, 63,
	  GRAPHIRE, WACOM_VOLITO_RES, WACOM_VOLITO_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x64 =
	अणु "Wacom PenPartner2", 3250, 2320, 511, 63,
	  GRAPHIRE, WACOM_VOLITO_RES, WACOM_VOLITO_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x65 =
	अणु "Wacom Bamboo", 14760, 9225, 511, 63,
	  WACOM_MO, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x69 =
	अणु "Wacom Bamboo1", 5104, 3712, 511, 63,
	  GRAPHIRE, WACOM_PENPRTN_RES, WACOM_PENPRTN_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x6A =
	अणु "Wacom Bamboo1 4x6", 14760, 9225, 1023, 63,
	  GRAPHIRE, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x6B =
	अणु "Wacom Bamboo1 5x8", 21648, 13530, 1023, 63,
	  GRAPHIRE, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x20 =
	अणु "Wacom Intuos 4x5", 12700, 10600, 1023, 31,
	  INTUOS, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x21 =
	अणु "Wacom Intuos 6x8", 20320, 16240, 1023, 31,
	  INTUOS, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x22 =
	अणु "Wacom Intuos 9x12", 30480, 24060, 1023, 31,
	  INTUOS, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x23 =
	अणु "Wacom Intuos 12x12", 30480, 31680, 1023, 31,
	  INTUOS, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x24 =
	अणु "Wacom Intuos 12x18", 45720, 31680, 1023, 31,
	  INTUOS, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x30 =
	अणु "Wacom PL400", 5408, 4056, 255, 0,
	  PL, WACOM_PL_RES, WACOM_PL_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x31 =
	अणु "Wacom PL500", 6144, 4608, 255, 0,
	  PL, WACOM_PL_RES, WACOM_PL_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x32 =
	अणु "Wacom PL600", 6126, 4604, 255, 0,
	  PL, WACOM_PL_RES, WACOM_PL_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x33 =
	अणु "Wacom PL600SX", 6260, 5016, 255, 0,
	  PL, WACOM_PL_RES, WACOM_PL_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x34 =
	अणु "Wacom PL550", 6144, 4608, 511, 0,
	  PL, WACOM_PL_RES, WACOM_PL_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x35 =
	अणु "Wacom PL800", 7220, 5780, 511, 0,
	  PL, WACOM_PL_RES, WACOM_PL_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x37 =
	अणु "Wacom PL700", 6758, 5406, 511, 0,
	  PL, WACOM_PL_RES, WACOM_PL_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x38 =
	अणु "Wacom PL510", 6282, 4762, 511, 0,
	  PL, WACOM_PL_RES, WACOM_PL_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x39 =
	अणु "Wacom DTU710", 34080, 27660, 511, 0,
	  PL, WACOM_PL_RES, WACOM_PL_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xC4 =
	अणु "Wacom DTF521", 6282, 4762, 511, 0,
	  PL, WACOM_PL_RES, WACOM_PL_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xC0 =
	अणु "Wacom DTF720", 6858, 5506, 511, 0,
	  PL, WACOM_PL_RES, WACOM_PL_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xC2 =
	अणु "Wacom DTF720a", 6858, 5506, 511, 0,
	  PL, WACOM_PL_RES, WACOM_PL_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x03 =
	अणु "Wacom Cintiq Partner", 20480, 15360, 511, 0,
	  PTU, WACOM_PL_RES, WACOM_PL_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x41 =
	अणु "Wacom Intuos2 4x5", 12700, 10600, 1023, 31,
	  INTUOS, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x42 =
	अणु "Wacom Intuos2 6x8", 20320, 16240, 1023, 31,
	  INTUOS, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x43 =
	अणु "Wacom Intuos2 9x12", 30480, 24060, 1023, 31,
	  INTUOS, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x44 =
	अणु "Wacom Intuos2 12x12", 30480, 31680, 1023, 31,
	  INTUOS, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x45 =
	अणु "Wacom Intuos2 12x18", 45720, 31680, 1023, 31,
	  INTUOS, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xB0 =
	अणु "Wacom Intuos3 4x5", 25400, 20320, 1023, 63,
	  INTUOS3S, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 4 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xB1 =
	अणु "Wacom Intuos3 6x8", 40640, 30480, 1023, 63,
	  INTUOS3, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 8 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xB2 =
	अणु "Wacom Intuos3 9x12", 60960, 45720, 1023, 63,
	  INTUOS3, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 8 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xB3 =
	अणु "Wacom Intuos3 12x12", 60960, 60960, 1023, 63,
	  INTUOS3L, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 8 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xB4 =
	अणु "Wacom Intuos3 12x19", 97536, 60960, 1023, 63,
	  INTUOS3L, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 8 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xB5 =
	अणु "Wacom Intuos3 6x11", 54204, 31750, 1023, 63,
	  INTUOS3, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 8 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xB7 =
	अणु "Wacom Intuos3 4x6", 31496, 19685, 1023, 63,
	  INTUOS3S, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 4 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xB8 =
	अणु "Wacom Intuos4 4x6", 31496, 19685, 2047, 63,
	  INTUOS4S, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 7 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xB9 =
	अणु "Wacom Intuos4 6x9", 44704, 27940, 2047, 63,
	  INTUOS4, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xBA =
	अणु "Wacom Intuos4 8x13", 65024, 40640, 2047, 63,
	  INTUOS4L, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xBB =
	अणु "Wacom Intuos4 12x19", 97536, 60960, 2047, 63,
	  INTUOS4L, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xBC =
	अणु "Wacom Intuos4 WL", 40640, 25400, 2047, 63,
	  INTUOS4, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xBD =
	अणु "Wacom Intuos4 WL", 40640, 25400, 2047, 63,
	  INTUOS4WL, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x26 =
	अणु "Wacom Intuos5 touch S", 31496, 19685, 2047, 63,
	  INTUOS5S, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 7, .touch_max = 16 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x27 =
	अणु "Wacom Intuos5 touch M", 44704, 27940, 2047, 63,
	  INTUOS5, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9, .touch_max = 16 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x28 =
	अणु "Wacom Intuos5 touch L", 65024, 40640, 2047, 63,
	  INTUOS5L, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9, .touch_max = 16 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x29 =
	अणु "Wacom Intuos5 S", 31496, 19685, 2047, 63,
	  INTUOS5S, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 7 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x2A =
	अणु "Wacom Intuos5 M", 44704, 27940, 2047, 63,
	  INTUOS5, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x314 =
	अणु "Wacom Intuos Pro S", 31496, 19685, 2047, 63,
	  INTUOSPS, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 7, .touch_max = 16,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x315 =
	अणु "Wacom Intuos Pro M", 44704, 27940, 2047, 63,
	  INTUOSPM, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9, .touch_max = 16,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x317 =
	अणु "Wacom Intuos Pro L", 65024, 40640, 2047, 63,
	  INTUOSPL, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9, .touch_max = 16,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xF4 =
	अणु "Wacom Cintiq 24HD", 104480, 65600, 2047, 63,
	  WACOM_24HD, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 16,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xF8 =
	अणु "Wacom Cintiq 24HD touch", 104480, 65600, 2047, 63, /* Pen */
	  WACOM_24HD, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 16,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOR_ID_WACOM, .oPid = 0xf6 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xF6 =
	अणु "Wacom Cintiq 24HD touch", .type = WACOM_24HDT, /* Touch */
	  .oVid = USB_VENDOR_ID_WACOM, .oPid = 0xf8, .touch_max = 10,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x32A =
	अणु "Wacom Cintiq 27QHD", 120140, 67920, 2047, 63,
	  WACOM_27QHD, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 0,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x32B =
	अणु "Wacom Cintiq 27QHD touch", 120140, 67920, 2047, 63,
	  WACOM_27QHD, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 0,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOR_ID_WACOM, .oPid = 0x32C पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x32C =
	अणु "Wacom Cintiq 27QHD touch", .type = WACOM_27QHDT,
	  .oVid = USB_VENDOR_ID_WACOM, .oPid = 0x32B, .touch_max = 10 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x3F =
	अणु "Wacom Cintiq 21UX", 87200, 65600, 1023, 63,
	  CINTIQ, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 8 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xC5 =
	अणु "Wacom Cintiq 20WSX", 86680, 54180, 1023, 63,
	  WACOM_BEE, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 10 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xC6 =
	अणु "Wacom Cintiq 12WX", 53020, 33440, 1023, 63,
	  WACOM_BEE, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 10 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x304 =
	अणु "Wacom Cintiq 13HD", 59552, 33848, 1023, 63,
	  WACOM_13HD, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x333 =
	अणु "Wacom Cintiq 13HD touch", 59552, 33848, 2047, 63,
	  WACOM_13HD, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOR_ID_WACOM, .oPid = 0x335 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x335 =
	अणु "Wacom Cintiq 13HD touch", .type = WACOM_24HDT, /* Touch */
	  .oVid = USB_VENDOR_ID_WACOM, .oPid = 0x333, .touch_max = 10,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xC7 =
	अणु "Wacom DTU1931", 37832, 30305, 511, 0,
	  PL, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xCE =
	अणु "Wacom DTU2231", 47864, 27011, 511, 0,
	  DTU, WACOM_INTUOS_RES, WACOM_INTUOS_RES,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBMOUSE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xF0 =
	अणु "Wacom DTU1631", 34623, 19553, 511, 0,
	  DTU, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xFB =
	अणु "Wacom DTU1031", 22096, 13960, 511, 0,
	  DTUS, WACOM_INTUOS_RES, WACOM_INTUOS_RES, 4,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x32F =
	अणु "Wacom DTU1031X", 22672, 12928, 511, 0,
	  DTUSX, WACOM_INTUOS_RES, WACOM_INTUOS_RES, 0,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x336 =
	अणु "Wacom DTU1141", 23672, 13403, 1023, 0,
	  DTUS, WACOM_INTUOS_RES, WACOM_INTUOS_RES, 4,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x57 =
	अणु "Wacom DTK2241", 95840, 54260, 2047, 63,
	  DTK, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 6,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x59 = /* Pen */
	अणु "Wacom DTH2242", 95840, 54260, 2047, 63,
	  DTK, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 6,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOR_ID_WACOM, .oPid = 0x5D पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x5D = /* Touch */
	अणु "Wacom DTH2242",       .type = WACOM_24HDT,
	  .oVid = USB_VENDOR_ID_WACOM, .oPid = 0x59, .touch_max = 10,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xCC =
	अणु "Wacom Cintiq 21UX2", 87200, 65600, 2047, 63,
	  WACOM_21UX2, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 18,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xFA =
	अणु "Wacom Cintiq 22HD", 95840, 54260, 2047, 63,
	  WACOM_22HD, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 18,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x5B =
	अणु "Wacom Cintiq 22HDT", 95840, 54260, 2047, 63,
	  WACOM_22HD, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 18,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOR_ID_WACOM, .oPid = 0x5e पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x5E =
	अणु "Wacom Cintiq 22HDT", .type = WACOM_24HDT,
	  .oVid = USB_VENDOR_ID_WACOM, .oPid = 0x5b, .touch_max = 10,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x90 =
	अणु "Wacom ISDv4 90", 26202, 16325, 255, 0,
	  TABLETPC, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण; /* Pen-only */
अटल स्थिर काष्ठा wacom_features wacom_features_0x93 =
	अणु "Wacom ISDv4 93", 26202, 16325, 255, 0,
	  TABLETPC, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 1 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x97 =
	अणु "Wacom ISDv4 97", 26202, 16325, 511, 0,
	  TABLETPC, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण; /* Pen-only */
अटल स्थिर काष्ठा wacom_features wacom_features_0x9A =
	अणु "Wacom ISDv4 9A", 26202, 16325, 255, 0,
	  TABLETPC, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 1 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x9F =
	अणु "Wacom ISDv4 9F", 26202, 16325, 255, 0,
	  TABLETPC, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 1 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xE2 =
	अणु "Wacom ISDv4 E2", 26202, 16325, 255, 0,
	  TABLETPC2FG, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 2 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xE3 =
	अणु "Wacom ISDv4 E3", 26202, 16325, 255, 0,
	  TABLETPC2FG, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 2 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xE5 =
	अणु "Wacom ISDv4 E5", 26202, 16325, 255, 0,
	  MTSCREEN, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xE6 =
	अणु "Wacom ISDv4 E6", 27760, 15694, 255, 0,
	  TABLETPC2FG, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 2 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xEC =
	अणु "Wacom ISDv4 EC", 25710, 14500, 255, 0,
	  TABLETPC,    WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण; /* Pen-only */
अटल स्थिर काष्ठा wacom_features wacom_features_0xED =
	अणु "Wacom ISDv4 ED", 26202, 16325, 255, 0,
	  TABLETPCE, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 1 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xEF =
	अणु "Wacom ISDv4 EF", 26202, 16325, 255, 0,
	  TABLETPC, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण; /* Pen-only */
अटल स्थिर काष्ठा wacom_features wacom_features_0x100 =
	अणु "Wacom ISDv4 100", 26202, 16325, 255, 0,
	  MTTPC, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x101 =
	अणु "Wacom ISDv4 101", 26202, 16325, 255, 0,
	  MTTPC, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x10D =
	अणु "Wacom ISDv4 10D", 26202, 16325, 255, 0,
	  MTTPC, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x10E =
	अणु "Wacom ISDv4 10E", 27760, 15694, 255, 0,
	  MTTPC, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x10F =
	अणु "Wacom ISDv4 10F", 27760, 15694, 255, 0,
	  MTTPC, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x116 =
	अणु "Wacom ISDv4 116", 26202, 16325, 255, 0,
	  TABLETPCE, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 1 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x12C =
	अणु "Wacom ISDv4 12C", 27848, 15752, 2047, 0,
	  TABLETPC, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण; /* Pen-only */
अटल स्थिर काष्ठा wacom_features wacom_features_0x4001 =
	अणु "Wacom ISDv4 4001", 26202, 16325, 255, 0,
	  MTTPC, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x4004 =
	अणु "Wacom ISDv4 4004", 11060, 6220, 255, 0,
	  MTTPC_B, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x5000 =
	अणु "Wacom ISDv4 5000", 27848, 15752, 1023, 0,
	  MTTPC_B, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x5002 =
	अणु "Wacom ISDv4 5002", 29576, 16724, 1023, 0,
	  MTTPC_B, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x47 =
	अणु "Wacom Intuos2 6x8", 20320, 16240, 1023, 31,
	  INTUOS, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x84 =
	अणु "Wacom Wireless Receiver", .type = WIRELESS, .touch_max = 16 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xD0 =
	अणु "Wacom Bamboo 2FG", 14720, 9200, 1023, 31,
	  BAMBOO_TOUCH, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 2 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xD1 =
	अणु "Wacom Bamboo 2FG 4x5", 14720, 9200, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 2 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xD2 =
	अणु "Wacom Bamboo Craft", 14720, 9200, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 2 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xD3 =
	अणु "Wacom Bamboo 2FG 6x8", 21648, 13700, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 2 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xD4 =
	अणु "Wacom Bamboo Pen", 14720, 9200, 1023, 31,
	  BAMBOO_PEN, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xD5 =
	अणु "Wacom Bamboo Pen 6x8", 21648, 13700, 1023, 31,
	  BAMBOO_PEN, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xD6 =
	अणु "Wacom BambooPT 2FG 4x5", 14720, 9200, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 2 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xD7 =
	अणु "Wacom BambooPT 2FG Small", 14720, 9200, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 2 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xD8 =
	अणु "Wacom Bamboo Comic 2FG", 21648, 13700, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 2 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xDA =
	अणु "Wacom Bamboo 2FG 4x5 SE", 14720, 9200, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 2 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xDB =
	अणु "Wacom Bamboo 2FG 6x8 SE", 21648, 13700, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 2 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xDD =
        अणु "Wacom Bamboo Connect", 14720, 9200, 1023, 31,
          BAMBOO_PT, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xDE =
        अणु "Wacom Bamboo 16FG 4x5", 14720, 9200, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 16 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0xDF =
        अणु "Wacom Bamboo 16FG 6x8", 21648, 13700, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 16 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x300 =
	अणु "Wacom Bamboo One S", 14720, 9225, 1023, 31,
	  BAMBOO_PEN, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x301 =
	अणु "Wacom Bamboo One M", 21648, 13530, 1023, 31,
	  BAMBOO_PEN, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x302 =
	अणु "Wacom Intuos PT S", 15200, 9500, 1023, 31,
	  INTUOSHT, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 16,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x303 =
	अणु "Wacom Intuos PT M", 21600, 13500, 1023, 31,
	  INTUOSHT, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 16,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x30E =
	अणु "Wacom Intuos S", 15200, 9500, 1023, 31,
	  INTUOSHT, WACOM_INTUOS_RES, WACOM_INTUOS_RES,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x6004 =
	अणु "ISD-V4", 12800, 8000, 255, 0,
	  TABLETPC, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x307 =
	अणु "Wacom ISDv5 307", 59552, 33848, 2047, 63,
	  CINTIQ_HYBRID, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOR_ID_WACOM, .oPid = 0x309 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x309 =
	अणु "Wacom ISDv5 309", .type = WACOM_24HDT, /* Touch */
	  .oVid = USB_VENDOR_ID_WACOM, .oPid = 0x0307, .touch_max = 10,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x30A =
	अणु "Wacom ISDv5 30A", 59552, 33848, 2047, 63,
	  CINTIQ_HYBRID, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOR_ID_WACOM, .oPid = 0x30C पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x30C =
	अणु "Wacom ISDv5 30C", .type = WACOM_24HDT, /* Touch */
	  .oVid = USB_VENDOR_ID_WACOM, .oPid = 0x30A, .touch_max = 10,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x318 =
	अणु "Wacom USB Bamboo PAD", 4095, 4095, /* Touch */
	  .type = BAMBOO_PAD, 35, 48, .touch_max = 4 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x319 =
	अणु "Wacom Wireless Bamboo PAD", 4095, 4095, /* Touch */
	  .type = BAMBOO_PAD, 35, 48, .touch_max = 4 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x325 =
	अणु "Wacom ISDv5 325", 59552, 33848, 2047, 63,
	  CINTIQ_COMPANION_2, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 11,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOR_ID_WACOM, .oPid = 0x326 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x326 = /* Touch */
	अणु "Wacom ISDv5 326", .type = HID_GENERIC, .oVid = USB_VENDOR_ID_WACOM,
	  .oPid = 0x325 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x323 =
	अणु "Wacom Intuos P M", 21600, 13500, 1023, 31,
	  INTUOSHT, WACOM_INTUOS_RES, WACOM_INTUOS_RES,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x331 =
	अणु "Wacom Express Key Remote", .type = REMOTE,
	  .numbered_buttons = 18, .check_क्रम_hid_type = true,
	  .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x33B =
	अणु "Wacom Intuos S 2", 15200, 9500, 2047, 63,
	  INTUOSHT2, WACOM_INTUOS_RES, WACOM_INTUOS_RES,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x33C =
	अणु "Wacom Intuos PT S 2", 15200, 9500, 2047, 63,
	  INTUOSHT2, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 16,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x33D =
	अणु "Wacom Intuos P M 2", 21600, 13500, 2047, 63,
	  INTUOSHT2, WACOM_INTUOS_RES, WACOM_INTUOS_RES,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x33E =
	अणु "Wacom Intuos PT M 2", 21600, 13500, 2047, 63,
	  INTUOSHT2, WACOM_INTUOS_RES, WACOM_INTUOS_RES, .touch_max = 16,
	  .check_क्रम_hid_type = true, .hid_type = HID_TYPE_USBNONE पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x343 =
	अणु "Wacom DTK1651", 34816, 19759, 1023, 0,
	  DTUS, WACOM_INTUOS_RES, WACOM_INTUOS_RES, 4,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x360 =
	अणु "Wacom Intuos Pro M", 44800, 29600, 8191, 63,
	  INTUOSP2_BT, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9, .touch_max = 10 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x361 =
	अणु "Wacom Intuos Pro L", 62200, 43200, 8191, 63,
	  INTUOSP2_BT, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 9, .touch_max = 10 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x377 =
	अणु "Wacom Intuos BT S", 15200, 9500, 4095, 63,
	  INTUOSHT3_BT, WACOM_INTUOS_RES, WACOM_INTUOS_RES, 4 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x379 =
	अणु "Wacom Intuos BT M", 21600, 13500, 4095, 63,
	  INTUOSHT3_BT, WACOM_INTUOS_RES, WACOM_INTUOS_RES, 4 पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x37A =
	अणु "Wacom One by Wacom S", 15200, 9500, 2047, 63,
	  BAMBOO_PEN, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x37B =
	अणु "Wacom One by Wacom M", 21600, 13500, 2047, 63,
	  BAMBOO_PEN, WACOM_INTUOS_RES, WACOM_INTUOS_RES पूर्ण;
अटल स्थिर काष्ठा wacom_features wacom_features_0x393 =
	अणु "Wacom Intuos Pro S", 31920, 19950, 8191, 63,
	  INTUOSP2S_BT, WACOM_INTUOS3_RES, WACOM_INTUOS3_RES, 7,
	  .touch_max = 10 पूर्ण;

अटल स्थिर काष्ठा wacom_features wacom_features_HID_ANY_ID =
	अणु "Wacom HID", .type = HID_GENERIC, .oVid = HID_ANY_ID, .oPid = HID_ANY_ID पूर्ण;

#घोषणा USB_DEVICE_WACOM(prod)						\
	HID_DEVICE(BUS_USB, HID_GROUP_WACOM, USB_VENDOR_ID_WACOM, prod),\
	.driver_data = (kernel_uदीर्घ_t)&wacom_features_##prod

#घोषणा BT_DEVICE_WACOM(prod)						\
	HID_DEVICE(BUS_BLUETOOTH, HID_GROUP_WACOM, USB_VENDOR_ID_WACOM, prod),\
	.driver_data = (kernel_uदीर्घ_t)&wacom_features_##prod

#घोषणा I2C_DEVICE_WACOM(prod)						\
	HID_DEVICE(BUS_I2C, HID_GROUP_WACOM, USB_VENDOR_ID_WACOM, prod),\
	.driver_data = (kernel_uदीर्घ_t)&wacom_features_##prod

#घोषणा USB_DEVICE_LENOVO(prod)					\
	HID_USB_DEVICE(USB_VENDOR_ID_LENOVO, prod),			\
	.driver_data = (kernel_uदीर्घ_t)&wacom_features_##prod

स्थिर काष्ठा hid_device_id wacom_ids[] = अणु
	अणु USB_DEVICE_WACOM(0x00) पूर्ण,
	अणु USB_DEVICE_WACOM(0x03) पूर्ण,
	अणु USB_DEVICE_WACOM(0x10) पूर्ण,
	अणु USB_DEVICE_WACOM(0x11) पूर्ण,
	अणु USB_DEVICE_WACOM(0x12) पूर्ण,
	अणु USB_DEVICE_WACOM(0x13) पूर्ण,
	अणु USB_DEVICE_WACOM(0x14) पूर्ण,
	अणु USB_DEVICE_WACOM(0x15) पूर्ण,
	अणु USB_DEVICE_WACOM(0x16) पूर्ण,
	अणु USB_DEVICE_WACOM(0x17) पूर्ण,
	अणु USB_DEVICE_WACOM(0x18) पूर्ण,
	अणु USB_DEVICE_WACOM(0x19) पूर्ण,
	अणु USB_DEVICE_WACOM(0x20) पूर्ण,
	अणु USB_DEVICE_WACOM(0x21) पूर्ण,
	अणु USB_DEVICE_WACOM(0x22) पूर्ण,
	अणु USB_DEVICE_WACOM(0x23) पूर्ण,
	अणु USB_DEVICE_WACOM(0x24) पूर्ण,
	अणु USB_DEVICE_WACOM(0x26) पूर्ण,
	अणु USB_DEVICE_WACOM(0x27) पूर्ण,
	अणु USB_DEVICE_WACOM(0x28) पूर्ण,
	अणु USB_DEVICE_WACOM(0x29) पूर्ण,
	अणु USB_DEVICE_WACOM(0x2A) पूर्ण,
	अणु USB_DEVICE_WACOM(0x30) पूर्ण,
	अणु USB_DEVICE_WACOM(0x31) पूर्ण,
	अणु USB_DEVICE_WACOM(0x32) पूर्ण,
	अणु USB_DEVICE_WACOM(0x33) पूर्ण,
	अणु USB_DEVICE_WACOM(0x34) पूर्ण,
	अणु USB_DEVICE_WACOM(0x35) पूर्ण,
	अणु USB_DEVICE_WACOM(0x37) पूर्ण,
	अणु USB_DEVICE_WACOM(0x38) पूर्ण,
	अणु USB_DEVICE_WACOM(0x39) पूर्ण,
	अणु USB_DEVICE_WACOM(0x3F) पूर्ण,
	अणु USB_DEVICE_WACOM(0x41) पूर्ण,
	अणु USB_DEVICE_WACOM(0x42) पूर्ण,
	अणु USB_DEVICE_WACOM(0x43) पूर्ण,
	अणु USB_DEVICE_WACOM(0x44) पूर्ण,
	अणु USB_DEVICE_WACOM(0x45) पूर्ण,
	अणु USB_DEVICE_WACOM(0x47) पूर्ण,
	अणु USB_DEVICE_WACOM(0x57) पूर्ण,
	अणु USB_DEVICE_WACOM(0x59) पूर्ण,
	अणु USB_DEVICE_WACOM(0x5B) पूर्ण,
	अणु USB_DEVICE_WACOM(0x5D) पूर्ण,
	अणु USB_DEVICE_WACOM(0x5E) पूर्ण,
	अणु USB_DEVICE_WACOM(0x60) पूर्ण,
	अणु USB_DEVICE_WACOM(0x61) पूर्ण,
	अणु USB_DEVICE_WACOM(0x62) पूर्ण,
	अणु USB_DEVICE_WACOM(0x63) पूर्ण,
	अणु USB_DEVICE_WACOM(0x64) पूर्ण,
	अणु USB_DEVICE_WACOM(0x65) पूर्ण,
	अणु USB_DEVICE_WACOM(0x69) पूर्ण,
	अणु USB_DEVICE_WACOM(0x6A) पूर्ण,
	अणु USB_DEVICE_WACOM(0x6B) पूर्ण,
	अणु BT_DEVICE_WACOM(0x81) पूर्ण,
	अणु USB_DEVICE_WACOM(0x84) पूर्ण,
	अणु USB_DEVICE_WACOM(0x90) पूर्ण,
	अणु USB_DEVICE_WACOM(0x93) पूर्ण,
	अणु USB_DEVICE_WACOM(0x97) पूर्ण,
	अणु USB_DEVICE_WACOM(0x9A) पूर्ण,
	अणु USB_DEVICE_WACOM(0x9F) पूर्ण,
	अणु USB_DEVICE_WACOM(0xB0) पूर्ण,
	अणु USB_DEVICE_WACOM(0xB1) पूर्ण,
	अणु USB_DEVICE_WACOM(0xB2) पूर्ण,
	अणु USB_DEVICE_WACOM(0xB3) पूर्ण,
	अणु USB_DEVICE_WACOM(0xB4) पूर्ण,
	अणु USB_DEVICE_WACOM(0xB5) पूर्ण,
	अणु USB_DEVICE_WACOM(0xB7) पूर्ण,
	अणु USB_DEVICE_WACOM(0xB8) पूर्ण,
	अणु USB_DEVICE_WACOM(0xB9) पूर्ण,
	अणु USB_DEVICE_WACOM(0xBA) पूर्ण,
	अणु USB_DEVICE_WACOM(0xBB) पूर्ण,
	अणु USB_DEVICE_WACOM(0xBC) पूर्ण,
	अणु BT_DEVICE_WACOM(0xBD) पूर्ण,
	अणु USB_DEVICE_WACOM(0xC0) पूर्ण,
	अणु USB_DEVICE_WACOM(0xC2) पूर्ण,
	अणु USB_DEVICE_WACOM(0xC4) पूर्ण,
	अणु USB_DEVICE_WACOM(0xC5) पूर्ण,
	अणु USB_DEVICE_WACOM(0xC6) पूर्ण,
	अणु USB_DEVICE_WACOM(0xC7) पूर्ण,
	अणु USB_DEVICE_WACOM(0xCC) पूर्ण,
	अणु USB_DEVICE_WACOM(0xCE) पूर्ण,
	अणु USB_DEVICE_WACOM(0xD0) पूर्ण,
	अणु USB_DEVICE_WACOM(0xD1) पूर्ण,
	अणु USB_DEVICE_WACOM(0xD2) पूर्ण,
	अणु USB_DEVICE_WACOM(0xD3) पूर्ण,
	अणु USB_DEVICE_WACOM(0xD4) पूर्ण,
	अणु USB_DEVICE_WACOM(0xD5) पूर्ण,
	अणु USB_DEVICE_WACOM(0xD6) पूर्ण,
	अणु USB_DEVICE_WACOM(0xD7) पूर्ण,
	अणु USB_DEVICE_WACOM(0xD8) पूर्ण,
	अणु USB_DEVICE_WACOM(0xDA) पूर्ण,
	अणु USB_DEVICE_WACOM(0xDB) पूर्ण,
	अणु USB_DEVICE_WACOM(0xDD) पूर्ण,
	अणु USB_DEVICE_WACOM(0xDE) पूर्ण,
	अणु USB_DEVICE_WACOM(0xDF) पूर्ण,
	अणु USB_DEVICE_WACOM(0xE2) पूर्ण,
	अणु USB_DEVICE_WACOM(0xE3) पूर्ण,
	अणु USB_DEVICE_WACOM(0xE5) पूर्ण,
	अणु USB_DEVICE_WACOM(0xE6) पूर्ण,
	अणु USB_DEVICE_WACOM(0xEC) पूर्ण,
	अणु USB_DEVICE_WACOM(0xED) पूर्ण,
	अणु USB_DEVICE_WACOM(0xEF) पूर्ण,
	अणु USB_DEVICE_WACOM(0xF0) पूर्ण,
	अणु USB_DEVICE_WACOM(0xF4) पूर्ण,
	अणु USB_DEVICE_WACOM(0xF6) पूर्ण,
	अणु USB_DEVICE_WACOM(0xF8) पूर्ण,
	अणु USB_DEVICE_WACOM(0xFA) पूर्ण,
	अणु USB_DEVICE_WACOM(0xFB) पूर्ण,
	अणु USB_DEVICE_WACOM(0x100) पूर्ण,
	अणु USB_DEVICE_WACOM(0x101) पूर्ण,
	अणु USB_DEVICE_WACOM(0x10D) पूर्ण,
	अणु USB_DEVICE_WACOM(0x10E) पूर्ण,
	अणु USB_DEVICE_WACOM(0x10F) पूर्ण,
	अणु USB_DEVICE_WACOM(0x116) पूर्ण,
	अणु USB_DEVICE_WACOM(0x12C) पूर्ण,
	अणु USB_DEVICE_WACOM(0x300) पूर्ण,
	अणु USB_DEVICE_WACOM(0x301) पूर्ण,
	अणु USB_DEVICE_WACOM(0x302) पूर्ण,
	अणु USB_DEVICE_WACOM(0x303) पूर्ण,
	अणु USB_DEVICE_WACOM(0x304) पूर्ण,
	अणु USB_DEVICE_WACOM(0x307) पूर्ण,
	अणु USB_DEVICE_WACOM(0x309) पूर्ण,
	अणु USB_DEVICE_WACOM(0x30A) पूर्ण,
	अणु USB_DEVICE_WACOM(0x30C) पूर्ण,
	अणु USB_DEVICE_WACOM(0x30E) पूर्ण,
	अणु USB_DEVICE_WACOM(0x314) पूर्ण,
	अणु USB_DEVICE_WACOM(0x315) पूर्ण,
	अणु USB_DEVICE_WACOM(0x317) पूर्ण,
	अणु USB_DEVICE_WACOM(0x318) पूर्ण,
	अणु USB_DEVICE_WACOM(0x319) पूर्ण,
	अणु USB_DEVICE_WACOM(0x323) पूर्ण,
	अणु USB_DEVICE_WACOM(0x325) पूर्ण,
	अणु USB_DEVICE_WACOM(0x326) पूर्ण,
	अणु USB_DEVICE_WACOM(0x32A) पूर्ण,
	अणु USB_DEVICE_WACOM(0x32B) पूर्ण,
	अणु USB_DEVICE_WACOM(0x32C) पूर्ण,
	अणु USB_DEVICE_WACOM(0x32F) पूर्ण,
	अणु USB_DEVICE_WACOM(0x331) पूर्ण,
	अणु USB_DEVICE_WACOM(0x333) पूर्ण,
	अणु USB_DEVICE_WACOM(0x335) पूर्ण,
	अणु USB_DEVICE_WACOM(0x336) पूर्ण,
	अणु USB_DEVICE_WACOM(0x33B) पूर्ण,
	अणु USB_DEVICE_WACOM(0x33C) पूर्ण,
	अणु USB_DEVICE_WACOM(0x33D) पूर्ण,
	अणु USB_DEVICE_WACOM(0x33E) पूर्ण,
	अणु USB_DEVICE_WACOM(0x343) पूर्ण,
	अणु BT_DEVICE_WACOM(0x360) पूर्ण,
	अणु BT_DEVICE_WACOM(0x361) पूर्ण,
	अणु BT_DEVICE_WACOM(0x377) पूर्ण,
	अणु BT_DEVICE_WACOM(0x379) पूर्ण,
	अणु USB_DEVICE_WACOM(0x37A) पूर्ण,
	अणु USB_DEVICE_WACOM(0x37B) पूर्ण,
	अणु BT_DEVICE_WACOM(0x393) पूर्ण,
	अणु USB_DEVICE_WACOM(0x4001) पूर्ण,
	अणु USB_DEVICE_WACOM(0x4004) पूर्ण,
	अणु USB_DEVICE_WACOM(0x5000) पूर्ण,
	अणु USB_DEVICE_WACOM(0x5002) पूर्ण,
	अणु USB_DEVICE_LENOVO(0x6004) पूर्ण,

	अणु USB_DEVICE_WACOM(HID_ANY_ID) पूर्ण,
	अणु I2C_DEVICE_WACOM(HID_ANY_ID) पूर्ण,
	अणु BT_DEVICE_WACOM(HID_ANY_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, wacom_ids);
