<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALPS touchpad PS/2 mouse driver
 *
 * Copyright (c) 2003 Neil Brown <neilb@cse.unsw.edu.au>
 * Copyright (c) 2003-2005 Peter Osterlund <petero2@telia.com>
 * Copyright (c) 2004 Dmitry Torokhov <dtor@mail.ru>
 * Copyright (c) 2005 Vojtech Pavlik <vojtech@suse.cz>
 * Copyright (c) 2009 Sebastian Kapfer <sebastian_kapfer@gmx.net>
 *
 * ALPS detection, tap चयनing and status querying info is taken from
 * tpconfig utility (by C. Scott Ananian and Bruce Kall).
 */

#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/serपन.स>
#समावेश <linux/libps2.h>
#समावेश <linux/dmi.h>

#समावेश "psmouse.h"
#समावेश "alps.h"
#समावेश "trackpoint.h"

/*
 * Definitions क्रम ALPS version 3 and 4 command mode protocol
 */
#घोषणा ALPS_CMD_NIBBLE_10	0x01f2

#घोषणा ALPS_REG_BASE_RUSHMORE	0xc2c0
#घोषणा ALPS_REG_BASE_V7	0xc2c0
#घोषणा ALPS_REG_BASE_PINNACLE	0x0000

अटल स्थिर काष्ठा alps_nibble_commands alps_v3_nibble_commands[] = अणु
	अणु PSMOUSE_CMD_SETPOLL,		0x00 पूर्ण, /* 0 */
	अणु PSMOUSE_CMD_RESET_DIS,	0x00 पूर्ण, /* 1 */
	अणु PSMOUSE_CMD_SETSCALE21,	0x00 पूर्ण, /* 2 */
	अणु PSMOUSE_CMD_SETRATE,		0x0a पूर्ण, /* 3 */
	अणु PSMOUSE_CMD_SETRATE,		0x14 पूर्ण, /* 4 */
	अणु PSMOUSE_CMD_SETRATE,		0x28 पूर्ण, /* 5 */
	अणु PSMOUSE_CMD_SETRATE,		0x3c पूर्ण, /* 6 */
	अणु PSMOUSE_CMD_SETRATE,		0x50 पूर्ण, /* 7 */
	अणु PSMOUSE_CMD_SETRATE,		0x64 पूर्ण, /* 8 */
	अणु PSMOUSE_CMD_SETRATE,		0xc8 पूर्ण, /* 9 */
	अणु ALPS_CMD_NIBBLE_10,		0x00 पूर्ण, /* a */
	अणु PSMOUSE_CMD_SETRES,		0x00 पूर्ण, /* b */
	अणु PSMOUSE_CMD_SETRES,		0x01 पूर्ण, /* c */
	अणु PSMOUSE_CMD_SETRES,		0x02 पूर्ण, /* d */
	अणु PSMOUSE_CMD_SETRES,		0x03 पूर्ण, /* e */
	अणु PSMOUSE_CMD_SETSCALE11,	0x00 पूर्ण, /* f */
पूर्ण;

अटल स्थिर काष्ठा alps_nibble_commands alps_v4_nibble_commands[] = अणु
	अणु PSMOUSE_CMD_ENABLE,		0x00 पूर्ण, /* 0 */
	अणु PSMOUSE_CMD_RESET_DIS,	0x00 पूर्ण, /* 1 */
	अणु PSMOUSE_CMD_SETSCALE21,	0x00 पूर्ण, /* 2 */
	अणु PSMOUSE_CMD_SETRATE,		0x0a पूर्ण, /* 3 */
	अणु PSMOUSE_CMD_SETRATE,		0x14 पूर्ण, /* 4 */
	अणु PSMOUSE_CMD_SETRATE,		0x28 पूर्ण, /* 5 */
	अणु PSMOUSE_CMD_SETRATE,		0x3c पूर्ण, /* 6 */
	अणु PSMOUSE_CMD_SETRATE,		0x50 पूर्ण, /* 7 */
	अणु PSMOUSE_CMD_SETRATE,		0x64 पूर्ण, /* 8 */
	अणु PSMOUSE_CMD_SETRATE,		0xc8 पूर्ण, /* 9 */
	अणु ALPS_CMD_NIBBLE_10,		0x00 पूर्ण, /* a */
	अणु PSMOUSE_CMD_SETRES,		0x00 पूर्ण, /* b */
	अणु PSMOUSE_CMD_SETRES,		0x01 पूर्ण, /* c */
	अणु PSMOUSE_CMD_SETRES,		0x02 पूर्ण, /* d */
	अणु PSMOUSE_CMD_SETRES,		0x03 पूर्ण, /* e */
	अणु PSMOUSE_CMD_SETSCALE11,	0x00 पूर्ण, /* f */
पूर्ण;

अटल स्थिर काष्ठा alps_nibble_commands alps_v6_nibble_commands[] = अणु
	अणु PSMOUSE_CMD_ENABLE,		0x00 पूर्ण, /* 0 */
	अणु PSMOUSE_CMD_SETRATE,		0x0a पूर्ण, /* 1 */
	अणु PSMOUSE_CMD_SETRATE,		0x14 पूर्ण, /* 2 */
	अणु PSMOUSE_CMD_SETRATE,		0x28 पूर्ण, /* 3 */
	अणु PSMOUSE_CMD_SETRATE,		0x3c पूर्ण, /* 4 */
	अणु PSMOUSE_CMD_SETRATE,		0x50 पूर्ण, /* 5 */
	अणु PSMOUSE_CMD_SETRATE,		0x64 पूर्ण, /* 6 */
	अणु PSMOUSE_CMD_SETRATE,		0xc8 पूर्ण, /* 7 */
	अणु PSMOUSE_CMD_GETID,		0x00 पूर्ण, /* 8 */
	अणु PSMOUSE_CMD_GETINFO,		0x00 पूर्ण, /* 9 */
	अणु PSMOUSE_CMD_SETRES,		0x00 पूर्ण, /* a */
	अणु PSMOUSE_CMD_SETRES,		0x01 पूर्ण, /* b */
	अणु PSMOUSE_CMD_SETRES,		0x02 पूर्ण, /* c */
	अणु PSMOUSE_CMD_SETRES,		0x03 पूर्ण, /* d */
	अणु PSMOUSE_CMD_SETSCALE21,	0x00 पूर्ण, /* e */
	अणु PSMOUSE_CMD_SETSCALE11,	0x00 पूर्ण, /* f */
पूर्ण;


#घोषणा ALPS_DUALPOINT		0x02	/* touchpad has trackstick */
#घोषणा ALPS_PASS		0x04	/* device has a pass-through port */

#घोषणा ALPS_WHEEL		0x08	/* hardware wheel present */
#घोषणा ALPS_FW_BK_1		0x10	/* front & back buttons present */
#घोषणा ALPS_FW_BK_2		0x20	/* front & back buttons present */
#घोषणा ALPS_FOUR_BUTTONS	0x40	/* 4 direction button present */
#घोषणा ALPS_PS2_INTERLEAVED	0x80	/* 3-byte PS/2 packet पूर्णांकerleaved with
					   6-byte ALPS packet */
#घोषणा ALPS_STICK_BITS		0x100	/* separate stick button bits */
#घोषणा ALPS_BUTTONPAD		0x200	/* device is a clickpad */
#घोषणा ALPS_DUALPOINT_WITH_PRESSURE	0x400	/* device can report trackpoपूर्णांक pressure */

अटल स्थिर काष्ठा alps_model_info alps_model_data[] = अणु
	/*
	 * XXX This entry is suspicious. First byte has zero lower nibble,
	 * which is what a normal mouse would report. Also, the value 0x0e
	 * isn't valid per PS/2 spec.
	 */
	अणु अणु 0x20, 0x02, 0x0e पूर्ण, अणु ALPS_PROTO_V2, 0xf8, 0xf8, ALPS_PASS | ALPS_DUALPOINT पूर्ण पूर्ण,

	अणु अणु 0x22, 0x02, 0x0a पूर्ण, अणु ALPS_PROTO_V2, 0xf8, 0xf8, ALPS_PASS | ALPS_DUALPOINT पूर्ण पूर्ण,
	अणु अणु 0x22, 0x02, 0x14 पूर्ण, अणु ALPS_PROTO_V2, 0xff, 0xff, ALPS_PASS | ALPS_DUALPOINT पूर्ण पूर्ण,	/* Dell Latitude D600 */
	अणु अणु 0x32, 0x02, 0x14 पूर्ण, अणु ALPS_PROTO_V2, 0xf8, 0xf8, ALPS_PASS | ALPS_DUALPOINT पूर्ण पूर्ण,	/* Toshiba Salellite Pro M10 */
	अणु अणु 0x33, 0x02, 0x0a पूर्ण, अणु ALPS_PROTO_V1, 0x88, 0xf8, 0 पूर्ण पूर्ण,				/* UMAX-530T */
	अणु अणु 0x52, 0x01, 0x14 पूर्ण, अणु ALPS_PROTO_V2, 0xff, 0xff,
		ALPS_PASS | ALPS_DUALPOINT | ALPS_PS2_INTERLEAVED पूर्ण पूर्ण,				/* Toshiba Tecra A11-11L */
	अणु अणु 0x53, 0x02, 0x0a पूर्ण, अणु ALPS_PROTO_V2, 0xf8, 0xf8, 0 पूर्ण पूर्ण,
	अणु अणु 0x53, 0x02, 0x14 पूर्ण, अणु ALPS_PROTO_V2, 0xf8, 0xf8, 0 पूर्ण पूर्ण,
	अणु अणु 0x60, 0x03, 0xc8 पूर्ण, अणु ALPS_PROTO_V2, 0xf8, 0xf8, 0 पूर्ण पूर्ण,				/* HP ze1115 */
	अणु अणु 0x62, 0x02, 0x14 पूर्ण, अणु ALPS_PROTO_V2, 0xcf, 0xcf,
		ALPS_PASS | ALPS_DUALPOINT | ALPS_PS2_INTERLEAVED पूर्ण पूर्ण,				/* Dell Latitude E5500, E6400, E6500, Precision M4400 */
	अणु अणु 0x63, 0x02, 0x0a पूर्ण, अणु ALPS_PROTO_V2, 0xf8, 0xf8, 0 पूर्ण पूर्ण,
	अणु अणु 0x63, 0x02, 0x14 पूर्ण, अणु ALPS_PROTO_V2, 0xf8, 0xf8, 0 पूर्ण पूर्ण,
	अणु अणु 0x63, 0x02, 0x28 पूर्ण, अणु ALPS_PROTO_V2, 0xf8, 0xf8, ALPS_FW_BK_2 पूर्ण पूर्ण,			/* Fujitsu Siemens S6010 */
	अणु अणु 0x63, 0x02, 0x3c पूर्ण, अणु ALPS_PROTO_V2, 0x8f, 0x8f, ALPS_WHEEL पूर्ण पूर्ण,			/* Toshiba Satellite S2400-103 */
	अणु अणु 0x63, 0x02, 0x50 पूर्ण, अणु ALPS_PROTO_V2, 0xef, 0xef, ALPS_FW_BK_1 पूर्ण पूर्ण,			/* NEC Versa L320 */
	अणु अणु 0x63, 0x02, 0x64 पूर्ण, अणु ALPS_PROTO_V2, 0xf8, 0xf8, 0 पूर्ण पूर्ण,
	अणु अणु 0x63, 0x03, 0xc8 पूर्ण, अणु ALPS_PROTO_V2, 0xf8, 0xf8, ALPS_PASS | ALPS_DUALPOINT पूर्ण पूर्ण,	/* Dell Latitude D800 */
	अणु अणु 0x73, 0x00, 0x0a पूर्ण, अणु ALPS_PROTO_V2, 0xf8, 0xf8, ALPS_DUALPOINT पूर्ण पूर्ण,		/* ThinkPad R61 8918-5QG */
	अणु अणु 0x73, 0x00, 0x14 पूर्ण, अणु ALPS_PROTO_V6, 0xff, 0xff, ALPS_DUALPOINT पूर्ण पूर्ण,		/* Dell XT2 */
	अणु अणु 0x73, 0x02, 0x0a पूर्ण, अणु ALPS_PROTO_V2, 0xf8, 0xf8, 0 पूर्ण पूर्ण,
	अणु अणु 0x73, 0x02, 0x14 पूर्ण, अणु ALPS_PROTO_V2, 0xf8, 0xf8, ALPS_FW_BK_2 पूर्ण पूर्ण,			/* Ahtec Laptop */
	अणु अणु 0x73, 0x02, 0x50 पूर्ण, अणु ALPS_PROTO_V2, 0xcf, 0xcf, ALPS_FOUR_BUTTONS पूर्ण पूर्ण,		/* Dell Vostro 1400 */
पूर्ण;

अटल स्थिर काष्ठा alps_protocol_info alps_v3_protocol_data = अणु
	ALPS_PROTO_V3, 0x8f, 0x8f, ALPS_DUALPOINT | ALPS_DUALPOINT_WITH_PRESSURE
पूर्ण;

अटल स्थिर काष्ठा alps_protocol_info alps_v3_rushmore_data = अणु
	ALPS_PROTO_V3_RUSHMORE, 0x8f, 0x8f, ALPS_DUALPOINT | ALPS_DUALPOINT_WITH_PRESSURE
पूर्ण;

अटल स्थिर काष्ठा alps_protocol_info alps_v4_protocol_data = अणु
	ALPS_PROTO_V4, 0x8f, 0x8f, 0
पूर्ण;

अटल स्थिर काष्ठा alps_protocol_info alps_v5_protocol_data = अणु
	ALPS_PROTO_V5, 0xc8, 0xd8, 0
पूर्ण;

अटल स्थिर काष्ठा alps_protocol_info alps_v7_protocol_data = अणु
	ALPS_PROTO_V7, 0x48, 0x48, ALPS_DUALPOINT | ALPS_DUALPOINT_WITH_PRESSURE
पूर्ण;

अटल स्थिर काष्ठा alps_protocol_info alps_v8_protocol_data = अणु
	ALPS_PROTO_V8, 0x18, 0x18, 0
पूर्ण;

अटल स्थिर काष्ठा alps_protocol_info alps_v9_protocol_data = अणु
	ALPS_PROTO_V9, 0xc8, 0xc8, 0
पूर्ण;

/*
 * Some v2 models report the stick buttons in separate bits
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id alps_dmi_has_separate_stick_buttons[] = अणु
#अगर defined(CONFIG_DMI) && defined(CONFIG_X86)
	अणु
		/* Extrapolated from other entries */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude D420"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Reported-by: Hans de Bruin <jmdebruin@xmsnet.nl> */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude D430"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Reported-by: Hans de Goede <hdegoede@redhat.com> */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude D620"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Extrapolated from other entries */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude D630"),
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल व्योम alps_set_असल_params_st(काष्ठा alps_data *priv,
				   काष्ठा input_dev *dev1);
अटल व्योम alps_set_असल_params_semi_mt(काष्ठा alps_data *priv,
					काष्ठा input_dev *dev1);
अटल व्योम alps_set_असल_params_v7(काष्ठा alps_data *priv,
				   काष्ठा input_dev *dev1);
अटल व्योम alps_set_असल_params_ss4_v2(काष्ठा alps_data *priv,
				       काष्ठा input_dev *dev1);

/* Packet क्रमmats are described in Documentation/input/devices/alps.rst */

अटल bool alps_is_valid_first_byte(काष्ठा alps_data *priv,
				     अचिन्हित अक्षर data)
अणु
	वापस (data & priv->mask0) == priv->byte0;
पूर्ण

अटल व्योम alps_report_buttons(काष्ठा input_dev *dev1, काष्ठा input_dev *dev2,
				पूर्णांक left, पूर्णांक right, पूर्णांक middle)
अणु
	काष्ठा input_dev *dev;

	/*
	 * If shared button has alपढ़ोy been reported on the
	 * other device (dev2) then this event should be also
	 * sent through that device.
	 */
	dev = (dev2 && test_bit(BTN_LEFT, dev2->key)) ? dev2 : dev1;
	input_report_key(dev, BTN_LEFT, left);

	dev = (dev2 && test_bit(BTN_RIGHT, dev2->key)) ? dev2 : dev1;
	input_report_key(dev, BTN_RIGHT, right);

	dev = (dev2 && test_bit(BTN_MIDDLE, dev2->key)) ? dev2 : dev1;
	input_report_key(dev, BTN_MIDDLE, middle);

	/*
	 * Sync the _other_ device now, we'll करो the first
	 * device later once we report the rest of the events.
	 */
	अगर (dev2)
		input_sync(dev2);
पूर्ण

अटल व्योम alps_process_packet_v1_v2(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा input_dev *dev2 = priv->dev2;
	पूर्णांक x, y, z, ges, fin, left, right, middle;
	पूर्णांक back = 0, क्रमward = 0;

	अगर (priv->proto_version == ALPS_PROTO_V1) अणु
		left = packet[2] & 0x10;
		right = packet[2] & 0x08;
		middle = 0;
		x = packet[1] | ((packet[0] & 0x07) << 7);
		y = packet[4] | ((packet[3] & 0x07) << 7);
		z = packet[5];
	पूर्ण अन्यथा अणु
		left = packet[3] & 1;
		right = packet[3] & 2;
		middle = packet[3] & 4;
		x = packet[1] | ((packet[2] & 0x78) << (7 - 3));
		y = packet[4] | ((packet[3] & 0x70) << (7 - 4));
		z = packet[5];
	पूर्ण

	अगर (priv->flags & ALPS_FW_BK_1) अणु
		back = packet[0] & 0x10;
		क्रमward = packet[2] & 4;
	पूर्ण

	अगर (priv->flags & ALPS_FW_BK_2) अणु
		back = packet[3] & 4;
		क्रमward = packet[2] & 4;
		अगर ((middle = क्रमward && back))
			क्रमward = back = 0;
	पूर्ण

	ges = packet[2] & 1;
	fin = packet[2] & 2;

	अगर ((priv->flags & ALPS_DUALPOINT) && z == 127) अणु
		input_report_rel(dev2, REL_X,  (x > 383 ? (x - 768) : x));
		input_report_rel(dev2, REL_Y, -(y > 255 ? (y - 512) : y));

		alps_report_buttons(dev2, dev, left, right, middle);

		input_sync(dev2);
		वापस;
	पूर्ण

	/* Some models have separate stick button bits */
	अगर (priv->flags & ALPS_STICK_BITS) अणु
		left |= packet[0] & 1;
		right |= packet[0] & 2;
		middle |= packet[0] & 4;
	पूर्ण

	alps_report_buttons(dev, dev2, left, right, middle);

	/* Convert hardware tap to a reasonable Z value */
	अगर (ges && !fin)
		z = 40;

	/*
	 * A "tap and drag" operation is reported by the hardware as a transition
	 * from (!fin && ges) to (fin && ges). This should be translated to the
	 * sequence Z>0, Z==0, Z>0, so the Z==0 event has to be generated manually.
	 */
	अगर (ges && fin && !priv->prev_fin) अणु
		input_report_असल(dev, ABS_X, x);
		input_report_असल(dev, ABS_Y, y);
		input_report_असल(dev, ABS_PRESSURE, 0);
		input_report_key(dev, BTN_TOOL_FINGER, 0);
		input_sync(dev);
	पूर्ण
	priv->prev_fin = fin;

	अगर (z > 30)
		input_report_key(dev, BTN_TOUCH, 1);
	अगर (z < 25)
		input_report_key(dev, BTN_TOUCH, 0);

	अगर (z > 0) अणु
		input_report_असल(dev, ABS_X, x);
		input_report_असल(dev, ABS_Y, y);
	पूर्ण

	input_report_असल(dev, ABS_PRESSURE, z);
	input_report_key(dev, BTN_TOOL_FINGER, z > 0);

	अगर (priv->flags & ALPS_WHEEL)
		input_report_rel(dev, REL_WHEEL, ((packet[2] << 1) & 0x08) - ((packet[0] >> 4) & 0x07));

	अगर (priv->flags & (ALPS_FW_BK_1 | ALPS_FW_BK_2)) अणु
		input_report_key(dev, BTN_FORWARD, क्रमward);
		input_report_key(dev, BTN_BACK, back);
	पूर्ण

	अगर (priv->flags & ALPS_FOUR_BUTTONS) अणु
		input_report_key(dev, BTN_0, packet[2] & 4);
		input_report_key(dev, BTN_1, packet[0] & 0x10);
		input_report_key(dev, BTN_2, packet[3] & 4);
		input_report_key(dev, BTN_3, packet[0] & 0x20);
	पूर्ण

	input_sync(dev);
पूर्ण

अटल व्योम alps_get_biपंचांगap_poपूर्णांकs(अचिन्हित पूर्णांक map,
				   काष्ठा alps_biपंचांगap_poपूर्णांक *low,
				   काष्ठा alps_biपंचांगap_poपूर्णांक *high,
				   पूर्णांक *fingers)
अणु
	काष्ठा alps_biपंचांगap_poपूर्णांक *poपूर्णांक;
	पूर्णांक i, bit, prev_bit = 0;

	poपूर्णांक = low;
	क्रम (i = 0; map != 0; i++, map >>= 1) अणु
		bit = map & 1;
		अगर (bit) अणु
			अगर (!prev_bit) अणु
				poपूर्णांक->start_bit = i;
				poपूर्णांक->num_bits = 0;
				(*fingers)++;
			पूर्ण
			poपूर्णांक->num_bits++;
		पूर्ण अन्यथा अणु
			अगर (prev_bit)
				poपूर्णांक = high;
		पूर्ण
		prev_bit = bit;
	पूर्ण
पूर्ण

/*
 * Process biपंचांगap data from semi-mt protocols. Returns the number of
 * fingers detected. A वापस value of 0 means at least one of the
 * biपंचांगaps was empty.
 *
 * The biपंचांगaps करोn't have enough data to track fingers, so this function
 * only generates poपूर्णांकs representing a bounding box of all contacts.
 * These poपूर्णांकs are वापसed in fields->mt when the वापस value
 * is greater than 0.
 */
अटल पूर्णांक alps_process_biपंचांगap(काष्ठा alps_data *priv,
			       काष्ठा alps_fields *fields)
अणु
	पूर्णांक i, fingers_x = 0, fingers_y = 0, fingers, बंदst;
	काष्ठा alps_biपंचांगap_poपूर्णांक x_low = अणु0,पूर्ण, x_high = अणु0,पूर्ण;
	काष्ठा alps_biपंचांगap_poपूर्णांक y_low = अणु0,पूर्ण, y_high = अणु0,पूर्ण;
	काष्ठा input_mt_pos corner[4];

	अगर (!fields->x_map || !fields->y_map)
		वापस 0;

	alps_get_biपंचांगap_poपूर्णांकs(fields->x_map, &x_low, &x_high, &fingers_x);
	alps_get_biपंचांगap_poपूर्णांकs(fields->y_map, &y_low, &y_high, &fingers_y);

	/*
	 * Fingers can overlap, so we use the maximum count of fingers
	 * on either axis as the finger count.
	 */
	fingers = max(fingers_x, fingers_y);

	/*
	 * If an axis reports only a single contact, we have overlapping or
	 * adjacent fingers. Divide the single contact between the two poपूर्णांकs.
	 */
	अगर (fingers_x == 1) अणु
		i = (x_low.num_bits - 1) / 2;
		x_low.num_bits = x_low.num_bits - i;
		x_high.start_bit = x_low.start_bit + i;
		x_high.num_bits = max(i, 1);
	पूर्ण
	अगर (fingers_y == 1) अणु
		i = (y_low.num_bits - 1) / 2;
		y_low.num_bits = y_low.num_bits - i;
		y_high.start_bit = y_low.start_bit + i;
		y_high.num_bits = max(i, 1);
	पूर्ण

	/* top-left corner */
	corner[0].x =
		(priv->x_max * (2 * x_low.start_bit + x_low.num_bits - 1)) /
		(2 * (priv->x_bits - 1));
	corner[0].y =
		(priv->y_max * (2 * y_low.start_bit + y_low.num_bits - 1)) /
		(2 * (priv->y_bits - 1));

	/* top-right corner */
	corner[1].x =
		(priv->x_max * (2 * x_high.start_bit + x_high.num_bits - 1)) /
		(2 * (priv->x_bits - 1));
	corner[1].y =
		(priv->y_max * (2 * y_low.start_bit + y_low.num_bits - 1)) /
		(2 * (priv->y_bits - 1));

	/* bottom-right corner */
	corner[2].x =
		(priv->x_max * (2 * x_high.start_bit + x_high.num_bits - 1)) /
		(2 * (priv->x_bits - 1));
	corner[2].y =
		(priv->y_max * (2 * y_high.start_bit + y_high.num_bits - 1)) /
		(2 * (priv->y_bits - 1));

	/* bottom-left corner */
	corner[3].x =
		(priv->x_max * (2 * x_low.start_bit + x_low.num_bits - 1)) /
		(2 * (priv->x_bits - 1));
	corner[3].y =
		(priv->y_max * (2 * y_high.start_bit + y_high.num_bits - 1)) /
		(2 * (priv->y_bits - 1));

	/* x-biपंचांगap order is reversed on v5 touchpads  */
	अगर (priv->proto_version == ALPS_PROTO_V5) अणु
		क्रम (i = 0; i < 4; i++)
			corner[i].x = priv->x_max - corner[i].x;
	पूर्ण

	/* y-biपंचांगap order is reversed on v3 and v4 touchpads  */
	अगर (priv->proto_version == ALPS_PROTO_V3 ||
	    priv->proto_version == ALPS_PROTO_V4) अणु
		क्रम (i = 0; i < 4; i++)
			corner[i].y = priv->y_max - corner[i].y;
	पूर्ण

	/*
	 * We only select a corner क्रम the second touch once per 2 finger
	 * touch sequence to aव्योम the chosen corner (and thus the coordinates)
	 * jumping around when the first touch is in the middle.
	 */
	अगर (priv->second_touch == -1) अणु
		/* Find corner बंदst to our st coordinates */
		बंदst = 0x7fffffff;
		क्रम (i = 0; i < 4; i++) अणु
			पूर्णांक dx = fields->st.x - corner[i].x;
			पूर्णांक dy = fields->st.y - corner[i].y;
			पूर्णांक distance = dx * dx + dy * dy;

			अगर (distance < बंदst) अणु
				priv->second_touch = i;
				बंदst = distance;
			पूर्ण
		पूर्ण
		/* And select the opposite corner to use क्रम the 2nd touch */
		priv->second_touch = (priv->second_touch + 2) % 4;
	पूर्ण

	fields->mt[0] = fields->st;
	fields->mt[1] = corner[priv->second_touch];

	वापस fingers;
पूर्ण

अटल व्योम alps_set_slot(काष्ठा input_dev *dev, पूर्णांक slot, पूर्णांक x, पूर्णांक y)
अणु
	input_mt_slot(dev, slot);
	input_mt_report_slot_state(dev, MT_TOOL_FINGER, true);
	input_report_असल(dev, ABS_MT_POSITION_X, x);
	input_report_असल(dev, ABS_MT_POSITION_Y, y);
पूर्ण

अटल व्योम alps_report_mt_data(काष्ठा psmouse *psmouse, पूर्णांक n)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा alps_fields *f = &priv->f;
	पूर्णांक i, slot[MAX_TOUCHES];

	input_mt_assign_slots(dev, slot, f->mt, n, 0);
	क्रम (i = 0; i < n; i++)
		alps_set_slot(dev, slot[i], f->mt[i].x, f->mt[i].y);

	input_mt_sync_frame(dev);
पूर्ण

अटल व्योम alps_report_semi_mt_data(काष्ठा psmouse *psmouse, पूर्णांक fingers)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा alps_fields *f = &priv->f;

	/* Use st data when we करोn't have mt data */
	अगर (fingers < 2) अणु
		f->mt[0].x = f->st.x;
		f->mt[0].y = f->st.y;
		fingers = f->pressure > 0 ? 1 : 0;
		priv->second_touch = -1;
	पूर्ण

	अगर (fingers >= 1)
		alps_set_slot(dev, 0, f->mt[0].x, f->mt[0].y);
	अगर (fingers >= 2)
		alps_set_slot(dev, 1, f->mt[1].x, f->mt[1].y);
	input_mt_sync_frame(dev);

	input_mt_report_finger_count(dev, fingers);

	input_report_key(dev, BTN_LEFT, f->left);
	input_report_key(dev, BTN_RIGHT, f->right);
	input_report_key(dev, BTN_MIDDLE, f->middle);

	input_report_असल(dev, ABS_PRESSURE, f->pressure);

	input_sync(dev);
पूर्ण

अटल व्योम alps_process_trackstick_packet_v3(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;
	काष्ठा input_dev *dev = priv->dev2;
	पूर्णांक x, y, z, left, right, middle;

	/* It should be a DualPoपूर्णांक when received trackstick packet */
	अगर (!(priv->flags & ALPS_DUALPOINT)) अणु
		psmouse_warn(psmouse,
			     "Rejected trackstick packet from non DualPoint device");
		वापस;
	पूर्ण

	/* Sanity check packet */
	अगर (!(packet[0] & 0x40)) अणु
		psmouse_dbg(psmouse, "Bad trackstick packet, discarding\n");
		वापस;
	पूर्ण

	/*
	 * There's a special packet that seems to indicate the end
	 * of a stream of trackstick data. Filter these out.
	 */
	अगर (packet[1] == 0x7f && packet[2] == 0x7f && packet[4] == 0x7f)
		वापस;

	x = (s8)(((packet[0] & 0x20) << 2) | (packet[1] & 0x7f));
	y = (s8)(((packet[0] & 0x10) << 3) | (packet[2] & 0x7f));
	z = packet[4] & 0x7f;

	/*
	 * The x and y values tend to be quite large, and when used
	 * alone the trackstick is dअगरficult to use. Scale them करोwn
	 * to compensate.
	 */
	x /= 8;
	y /= 8;

	input_report_rel(dev, REL_X, x);
	input_report_rel(dev, REL_Y, -y);
	input_report_असल(dev, ABS_PRESSURE, z);

	/*
	 * Most ALPS models report the trackstick buttons in the touchpad
	 * packets, but a few report them here. No reliable way has been
	 * found to dअगरferentiate between the models upfront, so we enable
	 * the quirk in response to seeing a button press in the trackstick
	 * packet.
	 */
	left = packet[3] & 0x01;
	right = packet[3] & 0x02;
	middle = packet[3] & 0x04;

	अगर (!(priv->quirks & ALPS_QUIRK_TRACKSTICK_BUTTONS) &&
	    (left || right || middle))
		priv->quirks |= ALPS_QUIRK_TRACKSTICK_BUTTONS;

	अगर (priv->quirks & ALPS_QUIRK_TRACKSTICK_BUTTONS) अणु
		input_report_key(dev, BTN_LEFT, left);
		input_report_key(dev, BTN_RIGHT, right);
		input_report_key(dev, BTN_MIDDLE, middle);
	पूर्ण

	input_sync(dev);
	वापस;
पूर्ण

अटल व्योम alps_decode_buttons_v3(काष्ठा alps_fields *f, अचिन्हित अक्षर *p)
अणु
	f->left = !!(p[3] & 0x01);
	f->right = !!(p[3] & 0x02);
	f->middle = !!(p[3] & 0x04);

	f->ts_left = !!(p[3] & 0x10);
	f->ts_right = !!(p[3] & 0x20);
	f->ts_middle = !!(p[3] & 0x40);
पूर्ण

अटल पूर्णांक alps_decode_pinnacle(काष्ठा alps_fields *f, अचिन्हित अक्षर *p,
				 काष्ठा psmouse *psmouse)
अणु
	f->first_mp = !!(p[4] & 0x40);
	f->is_mp = !!(p[0] & 0x40);

	अगर (f->is_mp) अणु
		f->fingers = (p[5] & 0x3) + 1;
		f->x_map = ((p[4] & 0x7e) << 8) |
			   ((p[1] & 0x7f) << 2) |
			   ((p[0] & 0x30) >> 4);
		f->y_map = ((p[3] & 0x70) << 4) |
			   ((p[2] & 0x7f) << 1) |
			   (p[4] & 0x01);
	पूर्ण अन्यथा अणु
		f->st.x = ((p[1] & 0x7f) << 4) | ((p[4] & 0x30) >> 2) |
		       ((p[0] & 0x30) >> 4);
		f->st.y = ((p[2] & 0x7f) << 4) | (p[4] & 0x0f);
		f->pressure = p[5] & 0x7f;

		alps_decode_buttons_v3(f, p);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक alps_decode_rushmore(काष्ठा alps_fields *f, अचिन्हित अक्षर *p,
				 काष्ठा psmouse *psmouse)
अणु
	f->first_mp = !!(p[4] & 0x40);
	f->is_mp = !!(p[5] & 0x40);

	अगर (f->is_mp) अणु
		f->fingers = max((p[5] & 0x3), ((p[5] >> 2) & 0x3)) + 1;
		f->x_map = ((p[5] & 0x10) << 11) |
			   ((p[4] & 0x7e) << 8) |
			   ((p[1] & 0x7f) << 2) |
			   ((p[0] & 0x30) >> 4);
		f->y_map = ((p[5] & 0x20) << 6) |
			   ((p[3] & 0x70) << 4) |
			   ((p[2] & 0x7f) << 1) |
			   (p[4] & 0x01);
	पूर्ण अन्यथा अणु
		f->st.x = ((p[1] & 0x7f) << 4) | ((p[4] & 0x30) >> 2) |
		       ((p[0] & 0x30) >> 4);
		f->st.y = ((p[2] & 0x7f) << 4) | (p[4] & 0x0f);
		f->pressure = p[5] & 0x7f;

		alps_decode_buttons_v3(f, p);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक alps_decode_करोlphin(काष्ठा alps_fields *f, अचिन्हित अक्षर *p,
				काष्ठा psmouse *psmouse)
अणु
	u64 palm_data = 0;
	काष्ठा alps_data *priv = psmouse->निजी;

	f->first_mp = !!(p[0] & 0x02);
	f->is_mp = !!(p[0] & 0x20);

	अगर (!f->is_mp) अणु
		f->st.x = ((p[1] & 0x7f) | ((p[4] & 0x0f) << 7));
		f->st.y = ((p[2] & 0x7f) | ((p[4] & 0xf0) << 3));
		f->pressure = (p[0] & 4) ? 0 : p[5] & 0x7f;
		alps_decode_buttons_v3(f, p);
	पूर्ण अन्यथा अणु
		f->fingers = ((p[0] & 0x6) >> 1 |
		     (p[0] & 0x10) >> 2);

		palm_data = (p[1] & 0x7f) |
			    ((p[2] & 0x7f) << 7) |
			    ((p[4] & 0x7f) << 14) |
			    ((p[5] & 0x7f) << 21) |
			    ((p[3] & 0x07) << 28) |
			    (((u64)p[3] & 0x70) << 27) |
			    (((u64)p[0] & 0x01) << 34);

		/* Y-profile is stored in P(0) to p(n-1), n = y_bits; */
		f->y_map = palm_data & (BIT(priv->y_bits) - 1);

		/* X-profile is stored in p(n) to p(n+m-1), m = x_bits; */
		f->x_map = (palm_data >> priv->y_bits) &
			   (BIT(priv->x_bits) - 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम alps_process_touchpad_packet_v3_v5(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;
	काष्ठा input_dev *dev2 = priv->dev2;
	काष्ठा alps_fields *f = &priv->f;
	पूर्णांक fingers = 0;

	स_रखो(f, 0, माप(*f));

	priv->decode_fields(f, packet, psmouse);

	/*
	 * There's no single feature of touchpad position and biपंचांगap packets
	 * that can be used to distinguish between them. We rely on the fact
	 * that a biपंचांगap packet should always follow a position packet with
	 * bit 6 of packet[4] set.
	 */
	अगर (priv->multi_packet) अणु
		/*
		 * Someबार a position packet will indicate a multi-packet
		 * sequence, but then what follows is another position
		 * packet. Check क्रम this, and when it happens process the
		 * position packet as usual.
		 */
		अगर (f->is_mp) अणु
			fingers = f->fingers;
			/*
			 * Biपंचांगap processing uses position packet's coordinate
			 * data, so we need to करो decode it first.
			 */
			priv->decode_fields(f, priv->multi_data, psmouse);
			अगर (alps_process_biपंचांगap(priv, f) == 0)
				fingers = 0; /* Use st data */
		पूर्ण अन्यथा अणु
			priv->multi_packet = 0;
		पूर्ण
	पूर्ण

	/*
	 * Bit 6 of byte 0 is not usually set in position packets. The only
	 * बार it seems to be set is in situations where the data is
	 * suspect anyway, e.g. a palm resting flat on the touchpad. Given
	 * this combined with the fact that this bit is useful क्रम filtering
	 * out misidentअगरied biपंचांगap packets, we reject anything with this
	 * bit set.
	 */
	अगर (f->is_mp)
		वापस;

	अगर (!priv->multi_packet && f->first_mp) अणु
		priv->multi_packet = 1;
		स_नकल(priv->multi_data, packet, माप(priv->multi_data));
		वापस;
	पूर्ण

	priv->multi_packet = 0;

	/*
	 * Someबार the hardware sends a single packet with z = 0
	 * in the middle of a stream. Real releases generate packets
	 * with x, y, and z all zero, so these seem to be flukes.
	 * Ignore them.
	 */
	अगर (f->st.x && f->st.y && !f->pressure)
		वापस;

	alps_report_semi_mt_data(psmouse, fingers);

	अगर ((priv->flags & ALPS_DUALPOINT) &&
	    !(priv->quirks & ALPS_QUIRK_TRACKSTICK_BUTTONS)) अणु
		input_report_key(dev2, BTN_LEFT, f->ts_left);
		input_report_key(dev2, BTN_RIGHT, f->ts_right);
		input_report_key(dev2, BTN_MIDDLE, f->ts_middle);
		input_sync(dev2);
	पूर्ण
पूर्ण

अटल व्योम alps_process_packet_v3(काष्ठा psmouse *psmouse)
अणु
	अचिन्हित अक्षर *packet = psmouse->packet;

	/*
	 * v3 protocol packets come in three types, two representing
	 * touchpad data and one representing trackstick data.
	 * Trackstick packets seem to be distinguished by always
	 * having 0x3f in the last byte. This value has never been
	 * observed in the last byte of either of the other types
	 * of packets.
	 */
	अगर (packet[5] == 0x3f) अणु
		alps_process_trackstick_packet_v3(psmouse);
		वापस;
	पूर्ण

	alps_process_touchpad_packet_v3_v5(psmouse);
पूर्ण

अटल व्योम alps_process_packet_v6(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा input_dev *dev2 = priv->dev2;
	पूर्णांक x, y, z;

	/*
	 * We can use Byte5 to distinguish अगर the packet is from Touchpad
	 * or Trackpoपूर्णांक.
	 * Touchpad:	0 - 0x7E
	 * Trackpoपूर्णांक:	0x7F
	 */
	अगर (packet[5] == 0x7F) अणु
		/* It should be a DualPoपूर्णांक when received Trackpoपूर्णांक packet */
		अगर (!(priv->flags & ALPS_DUALPOINT)) अणु
			psmouse_warn(psmouse,
				     "Rejected trackstick packet from non DualPoint device");
			वापस;
		पूर्ण

		/* Trackpoपूर्णांक packet */
		x = packet[1] | ((packet[3] & 0x20) << 2);
		y = packet[2] | ((packet[3] & 0x40) << 1);
		z = packet[4];

		/* To prevent the cursor jump when finger lअगरted */
		अगर (x == 0x7F && y == 0x7F && z == 0x7F)
			x = y = z = 0;

		/* Divide 4 since trackpoपूर्णांक's speed is too fast */
		input_report_rel(dev2, REL_X, (अक्षर)x / 4);
		input_report_rel(dev2, REL_Y, -((अक्षर)y / 4));

		psmouse_report_standard_buttons(dev2, packet[3]);

		input_sync(dev2);
		वापस;
	पूर्ण

	/* Touchpad packet */
	x = packet[1] | ((packet[3] & 0x78) << 4);
	y = packet[2] | ((packet[4] & 0x78) << 4);
	z = packet[5];

	अगर (z > 30)
		input_report_key(dev, BTN_TOUCH, 1);
	अगर (z < 25)
		input_report_key(dev, BTN_TOUCH, 0);

	अगर (z > 0) अणु
		input_report_असल(dev, ABS_X, x);
		input_report_असल(dev, ABS_Y, y);
	पूर्ण

	input_report_असल(dev, ABS_PRESSURE, z);
	input_report_key(dev, BTN_TOOL_FINGER, z > 0);

	/* v6 touchpad करोes not have middle button */
	packet[3] &= ~BIT(2);
	psmouse_report_standard_buttons(dev2, packet[3]);

	input_sync(dev);
पूर्ण

अटल व्योम alps_process_packet_v4(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;
	काष्ठा alps_fields *f = &priv->f;
	पूर्णांक offset;

	/*
	 * v4 has a 6-byte encoding क्रम biपंचांगap data, but this data is
	 * broken up between 3 normal packets. Use priv->multi_packet to
	 * track our position in the biपंचांगap packet.
	 */
	अगर (packet[6] & 0x40) अणु
		/* sync, reset position */
		priv->multi_packet = 0;
	पूर्ण

	अगर (WARN_ON_ONCE(priv->multi_packet > 2))
		वापस;

	offset = 2 * priv->multi_packet;
	priv->multi_data[offset] = packet[6];
	priv->multi_data[offset + 1] = packet[7];

	f->left = !!(packet[4] & 0x01);
	f->right = !!(packet[4] & 0x02);

	f->st.x = ((packet[1] & 0x7f) << 4) | ((packet[3] & 0x30) >> 2) |
		  ((packet[0] & 0x30) >> 4);
	f->st.y = ((packet[2] & 0x7f) << 4) | (packet[3] & 0x0f);
	f->pressure = packet[5] & 0x7f;

	अगर (++priv->multi_packet > 2) अणु
		priv->multi_packet = 0;

		f->x_map = ((priv->multi_data[2] & 0x1f) << 10) |
			   ((priv->multi_data[3] & 0x60) << 3) |
			   ((priv->multi_data[0] & 0x3f) << 2) |
			   ((priv->multi_data[1] & 0x60) >> 5);
		f->y_map = ((priv->multi_data[5] & 0x01) << 10) |
			   ((priv->multi_data[3] & 0x1f) << 5) |
			    (priv->multi_data[1] & 0x1f);

		f->fingers = alps_process_biपंचांगap(priv, f);
	पूर्ण

	alps_report_semi_mt_data(psmouse, f->fingers);
पूर्ण

अटल bool alps_is_valid_package_v7(काष्ठा psmouse *psmouse)
अणु
	चयन (psmouse->pktcnt) अणु
	हाल 3:
		वापस (psmouse->packet[2] & 0x40) == 0x40;
	हाल 4:
		वापस (psmouse->packet[3] & 0x48) == 0x48;
	हाल 6:
		वापस (psmouse->packet[5] & 0x40) == 0x00;
	पूर्ण
	वापस true;
पूर्ण

अटल अचिन्हित अक्षर alps_get_packet_id_v7(अक्षर *byte)
अणु
	अचिन्हित अक्षर packet_id;

	अगर (byte[4] & 0x40)
		packet_id = V7_PACKET_ID_TWO;
	अन्यथा अगर (byte[4] & 0x01)
		packet_id = V7_PACKET_ID_MULTI;
	अन्यथा अगर ((byte[0] & 0x10) && !(byte[4] & 0x43))
		packet_id = V7_PACKET_ID_NEW;
	अन्यथा अगर (byte[1] == 0x00 && byte[4] == 0x00)
		packet_id = V7_PACKET_ID_IDLE;
	अन्यथा
		packet_id = V7_PACKET_ID_UNKNOWN;

	वापस packet_id;
पूर्ण

अटल व्योम alps_get_finger_coordinate_v7(काष्ठा input_mt_pos *mt,
					  अचिन्हित अक्षर *pkt,
					  अचिन्हित अक्षर pkt_id)
अणु
	mt[0].x = ((pkt[2] & 0x80) << 4);
	mt[0].x |= ((pkt[2] & 0x3F) << 5);
	mt[0].x |= ((pkt[3] & 0x30) >> 1);
	mt[0].x |= (pkt[3] & 0x07);
	mt[0].y = (pkt[1] << 3) | (pkt[0] & 0x07);

	mt[1].x = ((pkt[3] & 0x80) << 4);
	mt[1].x |= ((pkt[4] & 0x80) << 3);
	mt[1].x |= ((pkt[4] & 0x3F) << 4);
	mt[1].y = ((pkt[5] & 0x80) << 3);
	mt[1].y |= ((pkt[5] & 0x3F) << 4);

	चयन (pkt_id) अणु
	हाल V7_PACKET_ID_TWO:
		mt[1].x &= ~0x000F;
		mt[1].y |= 0x000F;
		/* Detect false-positive touches where x & y report max value */
		अगर (mt[1].y == 0x7ff && mt[1].x == 0xff0) अणु
			mt[1].x = 0;
			/* y माला_लो set to 0 at the end of this function */
		पूर्ण
		अवरोध;

	हाल V7_PACKET_ID_MULTI:
		mt[1].x &= ~0x003F;
		mt[1].y &= ~0x0020;
		mt[1].y |= ((pkt[4] & 0x02) << 4);
		mt[1].y |= 0x001F;
		अवरोध;

	हाल V7_PACKET_ID_NEW:
		mt[1].x &= ~0x003F;
		mt[1].x |= (pkt[0] & 0x20);
		mt[1].y |= 0x000F;
		अवरोध;
	पूर्ण

	mt[0].y = 0x7FF - mt[0].y;
	mt[1].y = 0x7FF - mt[1].y;
पूर्ण

अटल पूर्णांक alps_get_mt_count(काष्ठा input_mt_pos *mt)
अणु
	पूर्णांक i, fingers = 0;

	क्रम (i = 0; i < MAX_TOUCHES; i++) अणु
		अगर (mt[i].x != 0 || mt[i].y != 0)
			fingers++;
	पूर्ण

	वापस fingers;
पूर्ण

अटल पूर्णांक alps_decode_packet_v7(काष्ठा alps_fields *f,
				  अचिन्हित अक्षर *p,
				  काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	अचिन्हित अक्षर pkt_id;

	pkt_id = alps_get_packet_id_v7(p);
	अगर (pkt_id == V7_PACKET_ID_IDLE)
		वापस 0;
	अगर (pkt_id == V7_PACKET_ID_UNKNOWN)
		वापस -1;
	/*
	 * NEW packets are send to indicate a discontinuity in the finger
	 * coordinate reporting. Specअगरically a finger may have moved from
	 * slot 0 to 1 or vice versa. INPUT_MT_TRACK takes care of this क्रम
	 * us.
	 *
	 * NEW packets have 3 problems:
	 * 1) They करो not contain middle / right button info (on non clickpads)
	 *    this can be worked around by preserving the old button state
	 * 2) They करो not contain an accurate fingercount, and they are
	 *    typically send when the number of fingers changes. We cannot use
	 *    the old finger count as that may mismatch with the amount of
	 *    touch coordinates we've available in the NEW packet
	 * 3) Their x data क्रम the second touch is inaccurate leading to
	 *    a possible jump of the x coordinate by 16 units when the first
	 *    non NEW packet comes in
	 * Since problems 2 & 3 cannot be worked around, just ignore them.
	 */
	अगर (pkt_id == V7_PACKET_ID_NEW)
		वापस 1;

	alps_get_finger_coordinate_v7(f->mt, p, pkt_id);

	अगर (pkt_id == V7_PACKET_ID_TWO)
		f->fingers = alps_get_mt_count(f->mt);
	अन्यथा /* pkt_id == V7_PACKET_ID_MULTI */
		f->fingers = 3 + (p[5] & 0x03);

	f->left = (p[0] & 0x80) >> 7;
	अगर (priv->flags & ALPS_BUTTONPAD) अणु
		अगर (p[0] & 0x20)
			f->fingers++;
		अगर (p[0] & 0x10)
			f->fingers++;
	पूर्ण अन्यथा अणु
		f->right = (p[0] & 0x20) >> 5;
		f->middle = (p[0] & 0x10) >> 4;
	पूर्ण

	/* Someबार a single touch is reported in mt[1] rather then mt[0] */
	अगर (f->fingers == 1 && f->mt[0].x == 0 && f->mt[0].y == 0) अणु
		f->mt[0].x = f->mt[1].x;
		f->mt[0].y = f->mt[1].y;
		f->mt[1].x = 0;
		f->mt[1].y = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम alps_process_trackstick_packet_v7(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;
	काष्ठा input_dev *dev2 = priv->dev2;
	पूर्णांक x, y, z;

	/* It should be a DualPoपूर्णांक when received trackstick packet */
	अगर (!(priv->flags & ALPS_DUALPOINT)) अणु
		psmouse_warn(psmouse,
			     "Rejected trackstick packet from non DualPoint device");
		वापस;
	पूर्ण

	x = ((packet[2] & 0xbf)) | ((packet[3] & 0x10) << 2);
	y = (packet[3] & 0x07) | (packet[4] & 0xb8) |
	    ((packet[3] & 0x20) << 1);
	z = (packet[5] & 0x3f) | ((packet[3] & 0x80) >> 1);

	input_report_rel(dev2, REL_X, (अक्षर)x);
	input_report_rel(dev2, REL_Y, -((अक्षर)y));
	input_report_असल(dev2, ABS_PRESSURE, z);

	psmouse_report_standard_buttons(dev2, packet[1]);

	input_sync(dev2);
पूर्ण

अटल व्योम alps_process_touchpad_packet_v7(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा alps_fields *f = &priv->f;

	स_रखो(f, 0, माप(*f));

	अगर (priv->decode_fields(f, psmouse->packet, psmouse))
		वापस;

	alps_report_mt_data(psmouse, alps_get_mt_count(f->mt));

	input_mt_report_finger_count(dev, f->fingers);

	input_report_key(dev, BTN_LEFT, f->left);
	input_report_key(dev, BTN_RIGHT, f->right);
	input_report_key(dev, BTN_MIDDLE, f->middle);

	input_sync(dev);
पूर्ण

अटल व्योम alps_process_packet_v7(काष्ठा psmouse *psmouse)
अणु
	अचिन्हित अक्षर *packet = psmouse->packet;

	अगर (packet[0] == 0x48 && (packet[4] & 0x47) == 0x06)
		alps_process_trackstick_packet_v7(psmouse);
	अन्यथा
		alps_process_touchpad_packet_v7(psmouse);
पूर्ण

अटल क्रमागत SS4_PACKET_ID alps_get_pkt_id_ss4_v2(अचिन्हित अक्षर *byte)
अणु
	क्रमागत SS4_PACKET_ID pkt_id = SS4_PACKET_ID_IDLE;

	चयन (byte[3] & 0x30) अणु
	हाल 0x00:
		अगर (SS4_IS_IDLE_V2(byte)) अणु
			pkt_id = SS4_PACKET_ID_IDLE;
		पूर्ण अन्यथा अणु
			pkt_id = SS4_PACKET_ID_ONE;
		पूर्ण
		अवरोध;
	हाल 0x10:
		/* two-finger finger positions */
		pkt_id = SS4_PACKET_ID_TWO;
		अवरोध;
	हाल 0x20:
		/* stick poपूर्णांकer */
		pkt_id = SS4_PACKET_ID_STICK;
		अवरोध;
	हाल 0x30:
		/* third and fourth finger positions */
		pkt_id = SS4_PACKET_ID_MULTI;
		अवरोध;
	पूर्ण

	वापस pkt_id;
पूर्ण

अटल पूर्णांक alps_decode_ss4_v2(काष्ठा alps_fields *f,
			      अचिन्हित अक्षर *p, काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	क्रमागत SS4_PACKET_ID pkt_id;
	अचिन्हित पूर्णांक no_data_x, no_data_y;

	pkt_id = alps_get_pkt_id_ss4_v2(p);

	/* Current packet is 1Finger coordinate packet */
	चयन (pkt_id) अणु
	हाल SS4_PACKET_ID_ONE:
		f->mt[0].x = SS4_1F_X_V2(p);
		f->mt[0].y = SS4_1F_Y_V2(p);
		f->pressure = ((SS4_1F_Z_V2(p)) * 2) & 0x7f;
		/*
		 * When a button is held the device will give us events
		 * with x, y, and pressure of 0. This causes annoying jumps
		 * अगर a touch is released जबतक the button is held.
		 * Handle this by claiming zero contacts.
		 */
		f->fingers = f->pressure > 0 ? 1 : 0;
		f->first_mp = 0;
		f->is_mp = 0;
		अवरोध;

	हाल SS4_PACKET_ID_TWO:
		अगर (priv->flags & ALPS_BUTTONPAD) अणु
			अगर (IS_SS4PLUS_DEV(priv->dev_id)) अणु
				f->mt[0].x = SS4_PLUS_BTL_MF_X_V2(p, 0);
				f->mt[1].x = SS4_PLUS_BTL_MF_X_V2(p, 1);
			पूर्ण अन्यथा अणु
				f->mt[0].x = SS4_BTL_MF_X_V2(p, 0);
				f->mt[1].x = SS4_BTL_MF_X_V2(p, 1);
			पूर्ण
			f->mt[0].y = SS4_BTL_MF_Y_V2(p, 0);
			f->mt[1].y = SS4_BTL_MF_Y_V2(p, 1);
		पूर्ण अन्यथा अणु
			अगर (IS_SS4PLUS_DEV(priv->dev_id)) अणु
				f->mt[0].x = SS4_PLUS_STD_MF_X_V2(p, 0);
				f->mt[1].x = SS4_PLUS_STD_MF_X_V2(p, 1);
			पूर्ण अन्यथा अणु
				f->mt[0].x = SS4_STD_MF_X_V2(p, 0);
				f->mt[1].x = SS4_STD_MF_X_V2(p, 1);
			पूर्ण
			f->mt[0].y = SS4_STD_MF_Y_V2(p, 0);
			f->mt[1].y = SS4_STD_MF_Y_V2(p, 1);
		पूर्ण
		f->pressure = SS4_MF_Z_V2(p, 0) ? 0x30 : 0;

		अगर (SS4_IS_MF_CONTINUE(p)) अणु
			f->first_mp = 1;
		पूर्ण अन्यथा अणु
			f->fingers = 2;
			f->first_mp = 0;
		पूर्ण
		f->is_mp = 0;

		अवरोध;

	हाल SS4_PACKET_ID_MULTI:
		अगर (priv->flags & ALPS_BUTTONPAD) अणु
			अगर (IS_SS4PLUS_DEV(priv->dev_id)) अणु
				f->mt[2].x = SS4_PLUS_BTL_MF_X_V2(p, 0);
				f->mt[3].x = SS4_PLUS_BTL_MF_X_V2(p, 1);
				no_data_x = SS4_PLUS_MFPACKET_NO_AX_BL;
			पूर्ण अन्यथा अणु
				f->mt[2].x = SS4_BTL_MF_X_V2(p, 0);
				f->mt[3].x = SS4_BTL_MF_X_V2(p, 1);
				no_data_x = SS4_MFPACKET_NO_AX_BL;
			पूर्ण
			no_data_y = SS4_MFPACKET_NO_AY_BL;

			f->mt[2].y = SS4_BTL_MF_Y_V2(p, 0);
			f->mt[3].y = SS4_BTL_MF_Y_V2(p, 1);
		पूर्ण अन्यथा अणु
			अगर (IS_SS4PLUS_DEV(priv->dev_id)) अणु
				f->mt[2].x = SS4_PLUS_STD_MF_X_V2(p, 0);
				f->mt[3].x = SS4_PLUS_STD_MF_X_V2(p, 1);
				no_data_x = SS4_PLUS_MFPACKET_NO_AX;
			पूर्ण अन्यथा अणु
				f->mt[2].x = SS4_STD_MF_X_V2(p, 0);
				f->mt[3].x = SS4_STD_MF_X_V2(p, 1);
				no_data_x = SS4_MFPACKET_NO_AX;
			पूर्ण
			no_data_y = SS4_MFPACKET_NO_AY;

			f->mt[2].y = SS4_STD_MF_Y_V2(p, 0);
			f->mt[3].y = SS4_STD_MF_Y_V2(p, 1);
		पूर्ण

		f->first_mp = 0;
		f->is_mp = 1;

		अगर (SS4_IS_5F_DETECTED(p)) अणु
			f->fingers = 5;
		पूर्ण अन्यथा अगर (f->mt[3].x == no_data_x &&
			     f->mt[3].y == no_data_y) अणु
			f->mt[3].x = 0;
			f->mt[3].y = 0;
			f->fingers = 3;
		पूर्ण अन्यथा अणु
			f->fingers = 4;
		पूर्ण
		अवरोध;

	हाल SS4_PACKET_ID_STICK:
		/*
		 * x, y, and pressure are decoded in
		 * alps_process_packet_ss4_v2()
		 */
		f->first_mp = 0;
		f->is_mp = 0;
		अवरोध;

	हाल SS4_PACKET_ID_IDLE:
	शेष:
		स_रखो(f, 0, माप(काष्ठा alps_fields));
		अवरोध;
	पूर्ण

	/* handle buttons */
	अगर (pkt_id == SS4_PACKET_ID_STICK) अणु
		f->ts_left = !!(SS4_BTN_V2(p) & 0x01);
		f->ts_right = !!(SS4_BTN_V2(p) & 0x02);
		f->ts_middle = !!(SS4_BTN_V2(p) & 0x04);
	पूर्ण अन्यथा अणु
		f->left = !!(SS4_BTN_V2(p) & 0x01);
		अगर (!(priv->flags & ALPS_BUTTONPAD)) अणु
			f->right = !!(SS4_BTN_V2(p) & 0x02);
			f->middle = !!(SS4_BTN_V2(p) & 0x04);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम alps_process_packet_ss4_v2(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा input_dev *dev2 = priv->dev2;
	काष्ठा alps_fields *f = &priv->f;

	स_रखो(f, 0, माप(काष्ठा alps_fields));
	priv->decode_fields(f, packet, psmouse);
	अगर (priv->multi_packet) अणु
		/*
		 * Someबार the first packet will indicate a multi-packet
		 * sequence, but someबार the next multi-packet would not
		 * come. Check क्रम this, and when it happens process the
		 * position packet as usual.
		 */
		अगर (f->is_mp) अणु
			/* Now process the 1st packet */
			priv->decode_fields(f, priv->multi_data, psmouse);
		पूर्ण अन्यथा अणु
			priv->multi_packet = 0;
		पूर्ण
	पूर्ण

	/*
	 * "f.is_mp" would always be '0' after merging the 1st and 2nd packet.
	 * When it is set, it means 2nd packet comes without 1st packet come.
	 */
	अगर (f->is_mp)
		वापस;

	/* Save the first packet */
	अगर (!priv->multi_packet && f->first_mp) अणु
		priv->multi_packet = 1;
		स_नकल(priv->multi_data, packet, माप(priv->multi_data));
		वापस;
	पूर्ण

	priv->multi_packet = 0;

	/* Report trackstick */
	अगर (alps_get_pkt_id_ss4_v2(packet) == SS4_PACKET_ID_STICK) अणु
		अगर (!(priv->flags & ALPS_DUALPOINT)) अणु
			psmouse_warn(psmouse,
				     "Rejected trackstick packet from non DualPoint device");
			वापस;
		पूर्ण

		input_report_rel(dev2, REL_X, SS4_TS_X_V2(packet));
		input_report_rel(dev2, REL_Y, SS4_TS_Y_V2(packet));
		input_report_असल(dev2, ABS_PRESSURE, SS4_TS_Z_V2(packet));

		input_report_key(dev2, BTN_LEFT, f->ts_left);
		input_report_key(dev2, BTN_RIGHT, f->ts_right);
		input_report_key(dev2, BTN_MIDDLE, f->ts_middle);

		input_sync(dev2);
		वापस;
	पूर्ण

	/* Report touchpad */
	alps_report_mt_data(psmouse, (f->fingers <= 4) ? f->fingers : 4);

	input_mt_report_finger_count(dev, f->fingers);

	input_report_key(dev, BTN_LEFT, f->left);
	input_report_key(dev, BTN_RIGHT, f->right);
	input_report_key(dev, BTN_MIDDLE, f->middle);

	input_report_असल(dev, ABS_PRESSURE, f->pressure);
	input_sync(dev);
पूर्ण

अटल bool alps_is_valid_package_ss4_v2(काष्ठा psmouse *psmouse)
अणु
	अगर (psmouse->pktcnt == 4 && ((psmouse->packet[3] & 0x08) != 0x08))
		वापस false;
	अगर (psmouse->pktcnt == 6 && ((psmouse->packet[5] & 0x10) != 0x0))
		वापस false;
	वापस true;
पूर्ण

अटल DEFINE_MUTEX(alps_mutex);

अटल व्योम alps_रेजिस्टर_bare_ps2_mouse(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा alps_data *priv =
		container_of(work, काष्ठा alps_data, dev3_रेजिस्टर_work.work);
	काष्ठा psmouse *psmouse = priv->psmouse;
	काष्ठा input_dev *dev3;
	पूर्णांक error = 0;

	mutex_lock(&alps_mutex);

	अगर (priv->dev3)
		जाओ out;

	dev3 = input_allocate_device();
	अगर (!dev3) अणु
		psmouse_err(psmouse, "failed to allocate secondary device\n");
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	snम_लिखो(priv->phys3, माप(priv->phys3), "%s/%s",
		 psmouse->ps2dev.serio->phys,
		 (priv->dev2 ? "input2" : "input1"));
	dev3->phys = priv->phys3;

	/*
	 * क्रमmat of input device name is: "protocol vendor name"
	 * see function psmouse_चयन_protocol() in psmouse-base.c
	 */
	dev3->name = "PS/2 ALPS Mouse";

	dev3->id.bustype = BUS_I8042;
	dev3->id.venकरोr  = 0x0002;
	dev3->id.product = PSMOUSE_PS2;
	dev3->id.version = 0x0000;
	dev3->dev.parent = &psmouse->ps2dev.serio->dev;

	input_set_capability(dev3, EV_REL, REL_X);
	input_set_capability(dev3, EV_REL, REL_Y);
	input_set_capability(dev3, EV_KEY, BTN_LEFT);
	input_set_capability(dev3, EV_KEY, BTN_RIGHT);
	input_set_capability(dev3, EV_KEY, BTN_MIDDLE);

	__set_bit(INPUT_PROP_POINTER, dev3->propbit);

	error = input_रेजिस्टर_device(dev3);
	अगर (error) अणु
		psmouse_err(psmouse,
			    "failed to register secondary device: %d\n",
			    error);
		input_मुक्त_device(dev3);
		जाओ out;
	पूर्ण

	priv->dev3 = dev3;

out:
	/*
	 * Save the error code so that we can detect that we
	 * alपढ़ोy tried to create the device.
	 */
	अगर (error)
		priv->dev3 = ERR_PTR(error);

	mutex_unlock(&alps_mutex);
पूर्ण

अटल व्योम alps_report_bare_ps2_packet(काष्ठा psmouse *psmouse,
					अचिन्हित अक्षर packet[],
					bool report_buttons)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	काष्ठा input_dev *dev, *dev2 = शून्य;

	/* Figure out which device to use to report the bare packet */
	अगर (priv->proto_version == ALPS_PROTO_V2 &&
	    (priv->flags & ALPS_DUALPOINT)) अणु
		/* On V2 devices the DualPoपूर्णांक Stick reports bare packets */
		dev = priv->dev2;
		dev2 = psmouse->dev;
	पूर्ण अन्यथा अगर (unlikely(IS_ERR_OR_शून्य(priv->dev3))) अणु
		/* Register dev3 mouse अगर we received PS/2 packet first समय */
		अगर (!IS_ERR(priv->dev3))
			psmouse_queue_work(psmouse, &priv->dev3_रेजिस्टर_work,
					   0);
		वापस;
	पूर्ण अन्यथा अणु
		dev = priv->dev3;
	पूर्ण

	अगर (report_buttons)
		alps_report_buttons(dev, dev2,
				packet[0] & 1, packet[0] & 2, packet[0] & 4);

	psmouse_report_standard_motion(dev, packet);

	input_sync(dev);
पूर्ण

अटल psmouse_ret_t alps_handle_पूर्णांकerleaved_ps2(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;

	अगर (psmouse->pktcnt < 6)
		वापस PSMOUSE_GOOD_DATA;

	अगर (psmouse->pktcnt == 6) अणु
		/*
		 * Start a समयr to flush the packet अगर it ends up last
		 * 6-byte packet in the stream. Timer needs to fire
		 * psmouse core बार out itself. 20 ms should be enough
		 * to decide अगर we are getting more data or not.
		 */
		mod_समयr(&priv->समयr, jअगरfies + msecs_to_jअगरfies(20));
		वापस PSMOUSE_GOOD_DATA;
	पूर्ण

	del_समयr(&priv->समयr);

	अगर (psmouse->packet[6] & 0x80) अणु

		/*
		 * Highest bit is set - that means we either had
		 * complete ALPS packet and this is start of the
		 * next packet or we got garbage.
		 */

		अगर (((psmouse->packet[3] |
		      psmouse->packet[4] |
		      psmouse->packet[5]) & 0x80) ||
		    (!alps_is_valid_first_byte(priv, psmouse->packet[6]))) अणु
			psmouse_dbg(psmouse,
				    "refusing packet %4ph (suspected interleaved ps/2)\n",
				    psmouse->packet + 3);
			वापस PSMOUSE_BAD_DATA;
		पूर्ण

		priv->process_packet(psmouse);

		/* Continue with the next packet */
		psmouse->packet[0] = psmouse->packet[6];
		psmouse->pktcnt = 1;

	पूर्ण अन्यथा अणु

		/*
		 * High bit is 0 - that means that we indeed got a PS/2
		 * packet in the middle of ALPS packet.
		 *
		 * There is also possibility that we got 6-byte ALPS
		 * packet followed  by 3-byte packet from trackpoपूर्णांक. We
		 * can not distinguish between these 2 scenarios but
		 * because the latter is unlikely to happen in course of
		 * normal operation (user would need to press all
		 * buttons on the pad and start moving trackpoपूर्णांक
		 * without touching the pad surface) we assume क्रमmer.
		 * Even अगर we are wrong the wost thing that would happen
		 * the cursor would jump but we should not get protocol
		 * de-synchronization.
		 */

		alps_report_bare_ps2_packet(psmouse, &psmouse->packet[3],
					    false);

		/*
		 * Continue with the standard ALPS protocol handling,
		 * but make sure we won't process it as an पूर्णांकerleaved
		 * packet again, which may happen अगर all buttons are
		 * pressed. To aव्योम this let's reset the 4th bit which
		 * is normally 1.
		 */
		psmouse->packet[3] = psmouse->packet[6] & 0xf7;
		psmouse->pktcnt = 4;
	पूर्ण

	वापस PSMOUSE_GOOD_DATA;
पूर्ण

अटल व्योम alps_flush_packet(काष्ठा समयr_list *t)
अणु
	काष्ठा alps_data *priv = from_समयr(priv, t, समयr);
	काष्ठा psmouse *psmouse = priv->psmouse;

	serio_छोड़ो_rx(psmouse->ps2dev.serio);

	अगर (psmouse->pktcnt == psmouse->pktsize) अणु

		/*
		 * We did not any more data in reasonable amount of समय.
		 * Validate the last 3 bytes and process as a standard
		 * ALPS packet.
		 */
		अगर ((psmouse->packet[3] |
		     psmouse->packet[4] |
		     psmouse->packet[5]) & 0x80) अणु
			psmouse_dbg(psmouse,
				    "refusing packet %3ph (suspected interleaved ps/2)\n",
				    psmouse->packet + 3);
		पूर्ण अन्यथा अणु
			priv->process_packet(psmouse);
		पूर्ण
		psmouse->pktcnt = 0;
	पूर्ण

	serio_जारी_rx(psmouse->ps2dev.serio);
पूर्ण

अटल psmouse_ret_t alps_process_byte(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;

	/*
	 * Check अगर we are dealing with a bare PS/2 packet, presumably from
	 * a device connected to the बाह्यal PS/2 port. Because bare PS/2
	 * protocol करोes not have enough स्थिरant bits to self-synchronize
	 * properly we only करो this अगर the device is fully synchronized.
	 * Can not distinguish V8's first byte from PS/2 packet's
	 */
	अगर (priv->proto_version != ALPS_PROTO_V8 &&
	    !psmouse->out_of_sync_cnt &&
	    (psmouse->packet[0] & 0xc8) == 0x08) अणु

		अगर (psmouse->pktcnt == 3) अणु
			alps_report_bare_ps2_packet(psmouse, psmouse->packet,
						    true);
			वापस PSMOUSE_FULL_PACKET;
		पूर्ण
		वापस PSMOUSE_GOOD_DATA;
	पूर्ण

	/* Check क्रम PS/2 packet stuffed in the middle of ALPS packet. */

	अगर ((priv->flags & ALPS_PS2_INTERLEAVED) &&
	    psmouse->pktcnt >= 4 && (psmouse->packet[3] & 0x0f) == 0x0f) अणु
		वापस alps_handle_पूर्णांकerleaved_ps2(psmouse);
	पूर्ण

	अगर (!alps_is_valid_first_byte(priv, psmouse->packet[0])) अणु
		psmouse_dbg(psmouse,
			    "refusing packet[0] = %x (mask0 = %x, byte0 = %x)\n",
			    psmouse->packet[0], priv->mask0, priv->byte0);
		वापस PSMOUSE_BAD_DATA;
	पूर्ण

	/* Bytes 2 - pktsize should have 0 in the highest bit */
	अगर (priv->proto_version < ALPS_PROTO_V5 &&
	    psmouse->pktcnt >= 2 && psmouse->pktcnt <= psmouse->pktsize &&
	    (psmouse->packet[psmouse->pktcnt - 1] & 0x80)) अणु
		psmouse_dbg(psmouse, "refusing packet[%i] = %x\n",
			    psmouse->pktcnt - 1,
			    psmouse->packet[psmouse->pktcnt - 1]);

		अगर (priv->proto_version == ALPS_PROTO_V3_RUSHMORE &&
		    psmouse->pktcnt == psmouse->pktsize) अणु
			/*
			 * Some Dell boxes, such as Latitude E6440 or E7440
			 * with बंदd lid, quite often smash last byte of
			 * otherwise valid packet with 0xff. Given that the
			 * next packet is very likely to be valid let's
			 * report PSMOUSE_FULL_PACKET but not process data,
			 * rather than reporting PSMOUSE_BAD_DATA and
			 * filling the logs.
			 */
			वापस PSMOUSE_FULL_PACKET;
		पूर्ण

		वापस PSMOUSE_BAD_DATA;
	पूर्ण

	अगर ((priv->proto_version == ALPS_PROTO_V7 &&
			!alps_is_valid_package_v7(psmouse)) ||
	    (priv->proto_version == ALPS_PROTO_V8 &&
			!alps_is_valid_package_ss4_v2(psmouse))) अणु
		psmouse_dbg(psmouse, "refusing packet[%i] = %x\n",
			    psmouse->pktcnt - 1,
			    psmouse->packet[psmouse->pktcnt - 1]);
		वापस PSMOUSE_BAD_DATA;
	पूर्ण

	अगर (psmouse->pktcnt == psmouse->pktsize) अणु
		priv->process_packet(psmouse);
		वापस PSMOUSE_FULL_PACKET;
	पूर्ण

	वापस PSMOUSE_GOOD_DATA;
पूर्ण

अटल पूर्णांक alps_command_mode_send_nibble(काष्ठा psmouse *psmouse, पूर्णांक nibble)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	काष्ठा alps_data *priv = psmouse->निजी;
	पूर्णांक command;
	अचिन्हित अक्षर *param;
	अचिन्हित अक्षर dummy[4];

	BUG_ON(nibble > 0xf);

	command = priv->nibble_commands[nibble].command;
	param = (command & 0x0f00) ?
		dummy : (अचिन्हित अक्षर *)&priv->nibble_commands[nibble].data;

	अगर (ps2_command(ps2dev, param, command))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक alps_command_mode_set_addr(काष्ठा psmouse *psmouse, पूर्णांक addr)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	काष्ठा alps_data *priv = psmouse->निजी;
	पूर्णांक i, nibble;

	अगर (ps2_command(ps2dev, शून्य, priv->addr_command))
		वापस -1;

	क्रम (i = 12; i >= 0; i -= 4) अणु
		nibble = (addr >> i) & 0xf;
		अगर (alps_command_mode_send_nibble(psmouse, nibble))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __alps_command_mode_पढ़ो_reg(काष्ठा psmouse *psmouse, पूर्णांक addr)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	अचिन्हित अक्षर param[4];

	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO))
		वापस -1;

	/*
	 * The address being पढ़ो is वापसed in the first two bytes
	 * of the result. Check that this address matches the expected
	 * address.
	 */
	अगर (addr != ((param[0] << 8) | param[1]))
		वापस -1;

	वापस param[2];
पूर्ण

अटल पूर्णांक alps_command_mode_पढ़ो_reg(काष्ठा psmouse *psmouse, पूर्णांक addr)
अणु
	अगर (alps_command_mode_set_addr(psmouse, addr))
		वापस -1;
	वापस __alps_command_mode_पढ़ो_reg(psmouse, addr);
पूर्ण

अटल पूर्णांक __alps_command_mode_ग_लिखो_reg(काष्ठा psmouse *psmouse, u8 value)
अणु
	अगर (alps_command_mode_send_nibble(psmouse, (value >> 4) & 0xf))
		वापस -1;
	अगर (alps_command_mode_send_nibble(psmouse, value & 0xf))
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक alps_command_mode_ग_लिखो_reg(काष्ठा psmouse *psmouse, पूर्णांक addr,
				       u8 value)
अणु
	अगर (alps_command_mode_set_addr(psmouse, addr))
		वापस -1;
	वापस __alps_command_mode_ग_लिखो_reg(psmouse, value);
पूर्ण

अटल पूर्णांक alps_rpt_cmd(काष्ठा psmouse *psmouse, पूर्णांक init_command,
			पूर्णांक repeated_command, अचिन्हित अक्षर *param)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;

	param[0] = 0;
	अगर (init_command && ps2_command(ps2dev, param, init_command))
		वापस -EIO;

	अगर (ps2_command(ps2dev,  शून्य, repeated_command) ||
	    ps2_command(ps2dev,  शून्य, repeated_command) ||
	    ps2_command(ps2dev,  शून्य, repeated_command))
		वापस -EIO;

	param[0] = param[1] = param[2] = 0xff;
	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO))
		वापस -EIO;

	psmouse_dbg(psmouse, "%2.2X report: %3ph\n",
		    repeated_command, param);
	वापस 0;
पूर्ण

अटल bool alps_check_valid_firmware_id(अचिन्हित अक्षर id[])
अणु
	अगर (id[0] == 0x73)
		वापस true;

	अगर (id[0] == 0x88 &&
	    (id[1] == 0x07 ||
	     id[1] == 0x08 ||
	     (id[1] & 0xf0) == 0xb0 ||
	     (id[1] & 0xf0) == 0xc0)) अणु
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक alps_enter_command_mode(काष्ठा psmouse *psmouse)
अणु
	अचिन्हित अक्षर param[4];

	अगर (alps_rpt_cmd(psmouse, 0, PSMOUSE_CMD_RESET_WRAP, param)) अणु
		psmouse_err(psmouse, "failed to enter command mode\n");
		वापस -1;
	पूर्ण

	अगर (!alps_check_valid_firmware_id(param)) अणु
		psmouse_dbg(psmouse,
			    "unknown response while entering command mode\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक alps_निकास_command_mode(काष्ठा psmouse *psmouse)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	अगर (ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETSTREAM))
		वापस -1;
	वापस 0;
पूर्ण

/*
 * For DualPoपूर्णांक devices select the device that should respond to
 * subsequent commands. It looks like glidepad is behind stickpoपूर्णांकer,
 * I'd thought it would be other way around...
 */
अटल पूर्णांक alps_passthrough_mode_v2(काष्ठा psmouse *psmouse, bool enable)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	पूर्णांक cmd = enable ? PSMOUSE_CMD_SETSCALE21 : PSMOUSE_CMD_SETSCALE11;

	अगर (ps2_command(ps2dev, शून्य, cmd) ||
	    ps2_command(ps2dev, शून्य, cmd) ||
	    ps2_command(ps2dev, शून्य, cmd) ||
	    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_DISABLE))
		वापस -1;

	/* we may get 3 more bytes, just ignore them */
	ps2_drain(ps2dev, 3, 100);

	वापस 0;
पूर्ण

अटल पूर्णांक alps_असलolute_mode_v1_v2(काष्ठा psmouse *psmouse)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;

	/* Try ALPS magic knock - 4 disable beक्रमe enable */
	अगर (ps2_command(ps2dev, शून्य, PSMOUSE_CMD_DISABLE) ||
	    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_DISABLE) ||
	    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_DISABLE) ||
	    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_DISABLE) ||
	    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_ENABLE))
		वापस -1;

	/*
	 * Switch mouse to poll (remote) mode so motion data will not
	 * get in our way
	 */
	वापस ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETPOLL);
पूर्ण

अटल पूर्णांक alps_monitor_mode_send_word(काष्ठा psmouse *psmouse, u16 word)
अणु
	पूर्णांक i, nibble;

	/*
	 * b0-b11 are valid bits, send sequence is inverse.
	 * e.g. when word = 0x0123, nibble send sequence is 3, 2, 1
	 */
	क्रम (i = 0; i <= 8; i += 4) अणु
		nibble = (word >> i) & 0xf;
		अगर (alps_command_mode_send_nibble(psmouse, nibble))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक alps_monitor_mode_ग_लिखो_reg(काष्ठा psmouse *psmouse,
				       u16 addr, u16 value)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;

	/* 0x0A0 is the command to ग_लिखो the word */
	अगर (ps2_command(ps2dev, शून्य, PSMOUSE_CMD_ENABLE) ||
	    alps_monitor_mode_send_word(psmouse, 0x0A0) ||
	    alps_monitor_mode_send_word(psmouse, addr) ||
	    alps_monitor_mode_send_word(psmouse, value) ||
	    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_DISABLE))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक alps_monitor_mode(काष्ठा psmouse *psmouse, bool enable)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;

	अगर (enable) अणु
		/* EC E9 F5 F5 E7 E6 E7 E9 to enter monitor mode */
		अगर (ps2_command(ps2dev, शून्य, PSMOUSE_CMD_RESET_WRAP) ||
		    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_GETINFO) ||
		    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_DISABLE) ||
		    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_DISABLE) ||
		    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETSCALE21) ||
		    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETSCALE11) ||
		    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETSCALE21) ||
		    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_GETINFO))
			वापस -1;
	पूर्ण अन्यथा अणु
		/* EC to निकास monitor mode */
		अगर (ps2_command(ps2dev, शून्य, PSMOUSE_CMD_RESET_WRAP))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक alps_असलolute_mode_v6(काष्ठा psmouse *psmouse)
अणु
	u16 reg_val = 0x181;
	पूर्णांक ret;

	/* enter monitor mode, to ग_लिखो the रेजिस्टर */
	अगर (alps_monitor_mode(psmouse, true))
		वापस -1;

	ret = alps_monitor_mode_ग_लिखो_reg(psmouse, 0x000, reg_val);

	अगर (alps_monitor_mode(psmouse, false))
		ret = -1;

	वापस ret;
पूर्ण

अटल पूर्णांक alps_get_status(काष्ठा psmouse *psmouse, अक्षर *param)
अणु
	/* Get status: 0xF5 0xF5 0xF5 0xE9 */
	अगर (alps_rpt_cmd(psmouse, 0, PSMOUSE_CMD_DISABLE, param))
		वापस -1;

	वापस 0;
पूर्ण

/*
 * Turn touchpad tapping on or off. The sequences are:
 * 0xE9 0xF5 0xF5 0xF3 0x0A to enable,
 * 0xE9 0xF5 0xF5 0xE8 0x00 to disable.
 * My guess that 0xE9 (GetInfo) is here as a sync poपूर्णांक.
 * For models that also have stickpoपूर्णांकer (DualPoपूर्णांकs) its tapping
 * is controlled separately (0xE6 0xE6 0xE6 0xF3 0x14|0x0A) but
 * we करोn't fiddle with it.
 */
अटल पूर्णांक alps_tap_mode(काष्ठा psmouse *psmouse, पूर्णांक enable)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	पूर्णांक cmd = enable ? PSMOUSE_CMD_SETRATE : PSMOUSE_CMD_SETRES;
	अचिन्हित अक्षर tap_arg = enable ? 0x0A : 0x00;
	अचिन्हित अक्षर param[4];

	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO) ||
	    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_DISABLE) ||
	    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_DISABLE) ||
	    ps2_command(ps2dev, &tap_arg, cmd))
		वापस -1;

	अगर (alps_get_status(psmouse, param))
		वापस -1;

	वापस 0;
पूर्ण

/*
 * alps_poll() - poll the touchpad क्रम current motion packet.
 * Used in resync.
 */
अटल पूर्णांक alps_poll(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	अचिन्हित अक्षर buf[माप(psmouse->packet)];
	bool poll_failed;

	अगर (priv->flags & ALPS_PASS)
		alps_passthrough_mode_v2(psmouse, true);

	poll_failed = ps2_command(&psmouse->ps2dev, buf,
				  PSMOUSE_CMD_POLL | (psmouse->pktsize << 8)) < 0;

	अगर (priv->flags & ALPS_PASS)
		alps_passthrough_mode_v2(psmouse, false);

	अगर (poll_failed || (buf[0] & priv->mask0) != priv->byte0)
		वापस -1;

	अगर ((psmouse->badbyte & 0xc8) == 0x08) अणु
/*
 * Poll the track stick ...
 */
		अगर (ps2_command(&psmouse->ps2dev, buf, PSMOUSE_CMD_POLL | (3 << 8)))
			वापस -1;
	पूर्ण

	स_नकल(psmouse->packet, buf, माप(buf));
	वापस 0;
पूर्ण

अटल पूर्णांक alps_hw_init_v1_v2(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;

	अगर ((priv->flags & ALPS_PASS) &&
	    alps_passthrough_mode_v2(psmouse, true)) अणु
		वापस -1;
	पूर्ण

	अगर (alps_tap_mode(psmouse, true)) अणु
		psmouse_warn(psmouse, "Failed to enable hardware tapping\n");
		वापस -1;
	पूर्ण

	अगर (alps_असलolute_mode_v1_v2(psmouse)) अणु
		psmouse_err(psmouse, "Failed to enable absolute mode\n");
		वापस -1;
	पूर्ण

	अगर ((priv->flags & ALPS_PASS) &&
	    alps_passthrough_mode_v2(psmouse, false)) अणु
		वापस -1;
	पूर्ण

	/* ALPS needs stream mode, otherwise it won't report any data */
	अगर (ps2_command(&psmouse->ps2dev, शून्य, PSMOUSE_CMD_SETSTREAM)) अणु
		psmouse_err(psmouse, "Failed to enable stream mode\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/* Must be in passthrough mode when calling this function */
अटल पूर्णांक alps_trackstick_enter_extended_mode_v3_v6(काष्ठा psmouse *psmouse)
अणु
	अचिन्हित अक्षर param[2] = अणु0xC8, 0x14पूर्ण;

	अगर (ps2_command(&psmouse->ps2dev, शून्य, PSMOUSE_CMD_SETSCALE11) ||
	    ps2_command(&psmouse->ps2dev, शून्य, PSMOUSE_CMD_SETSCALE11) ||
	    ps2_command(&psmouse->ps2dev, शून्य, PSMOUSE_CMD_SETSCALE11) ||
	    ps2_command(&psmouse->ps2dev, &param[0], PSMOUSE_CMD_SETRATE) ||
	    ps2_command(&psmouse->ps2dev, &param[1], PSMOUSE_CMD_SETRATE))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक alps_hw_init_v6(काष्ठा psmouse *psmouse)
अणु
	पूर्णांक ret;

	/* Enter passthrough mode to let trackpoपूर्णांक enter 6byte raw mode */
	अगर (alps_passthrough_mode_v2(psmouse, true))
		वापस -1;

	ret = alps_trackstick_enter_extended_mode_v3_v6(psmouse);

	अगर (alps_passthrough_mode_v2(psmouse, false))
		वापस -1;

	अगर (ret)
		वापस ret;

	अगर (alps_असलolute_mode_v6(psmouse)) अणु
		psmouse_err(psmouse, "Failed to enable absolute mode\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Enable or disable passthrough mode to the trackstick.
 */
अटल पूर्णांक alps_passthrough_mode_v3(काष्ठा psmouse *psmouse,
				    पूर्णांक reg_base, bool enable)
अणु
	पूर्णांक reg_val, ret = -1;

	अगर (alps_enter_command_mode(psmouse))
		वापस -1;

	reg_val = alps_command_mode_पढ़ो_reg(psmouse, reg_base + 0x0008);
	अगर (reg_val == -1)
		जाओ error;

	अगर (enable)
		reg_val |= 0x01;
	अन्यथा
		reg_val &= ~0x01;

	ret = __alps_command_mode_ग_लिखो_reg(psmouse, reg_val);

error:
	अगर (alps_निकास_command_mode(psmouse))
		ret = -1;
	वापस ret;
पूर्ण

/* Must be in command mode when calling this function */
अटल पूर्णांक alps_असलolute_mode_v3(काष्ठा psmouse *psmouse)
अणु
	पूर्णांक reg_val;

	reg_val = alps_command_mode_पढ़ो_reg(psmouse, 0x0004);
	अगर (reg_val == -1)
		वापस -1;

	reg_val |= 0x06;
	अगर (__alps_command_mode_ग_लिखो_reg(psmouse, reg_val))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक alps_probe_trackstick_v3_v7(काष्ठा psmouse *psmouse, पूर्णांक reg_base)
अणु
	पूर्णांक ret = -EIO, reg_val;

	अगर (alps_enter_command_mode(psmouse))
		जाओ error;

	reg_val = alps_command_mode_पढ़ो_reg(psmouse, reg_base + 0x08);
	अगर (reg_val == -1)
		जाओ error;

	/* bit 7: trackstick is present */
	ret = reg_val & 0x80 ? 0 : -ENODEV;

error:
	alps_निकास_command_mode(psmouse);
	वापस ret;
पूर्ण

अटल पूर्णांक alps_setup_trackstick_v3(काष्ठा psmouse *psmouse, पूर्णांक reg_base)
अणु
	पूर्णांक ret = 0;
	पूर्णांक reg_val;
	अचिन्हित अक्षर param[4];

	/*
	 * We need to configure trackstick to report data क्रम touchpad in
	 * extended क्रमmat. And also we need to tell touchpad to expect data
	 * from trackstick in extended क्रमmat. Without this configuration
	 * trackstick packets sent from touchpad are in basic क्रमmat which is
	 * dअगरferent from what we expect.
	 */

	अगर (alps_passthrough_mode_v3(psmouse, reg_base, true))
		वापस -EIO;

	/*
	 * E7 report क्रम the trackstick
	 *
	 * There have been reports of failures to seem to trace back
	 * to the above trackstick check failing. When these occur
	 * this E7 report fails, so when that happens we जारी
	 * with the assumption that there isn't a trackstick after
	 * all.
	 */
	अगर (alps_rpt_cmd(psmouse, 0, PSMOUSE_CMD_SETSCALE21, param)) अणु
		psmouse_warn(psmouse, "Failed to initialize trackstick (E7 report failed)\n");
		ret = -ENODEV;
	पूर्ण अन्यथा अणु
		psmouse_dbg(psmouse, "trackstick E7 report: %3ph\n", param);
		अगर (alps_trackstick_enter_extended_mode_v3_v6(psmouse)) अणु
			psmouse_err(psmouse, "Failed to enter into trackstick extended mode\n");
			ret = -EIO;
		पूर्ण
	पूर्ण

	अगर (alps_passthrough_mode_v3(psmouse, reg_base, false))
		वापस -EIO;

	अगर (ret)
		वापस ret;

	अगर (alps_enter_command_mode(psmouse))
		वापस -EIO;

	reg_val = alps_command_mode_पढ़ो_reg(psmouse, reg_base + 0x08);
	अगर (reg_val == -1) अणु
		ret = -EIO;
	पूर्ण अन्यथा अणु
		/*
		 * Tell touchpad that trackstick is now in extended mode.
		 * If bit 1 isn't set the packet क्रमmat is dअगरferent.
		 */
		reg_val |= BIT(1);
		अगर (__alps_command_mode_ग_लिखो_reg(psmouse, reg_val))
			ret = -EIO;
	पूर्ण

	अगर (alps_निकास_command_mode(psmouse))
		वापस -EIO;

	वापस ret;
पूर्ण

अटल पूर्णांक alps_hw_init_v3(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	पूर्णांक reg_val;
	अचिन्हित अक्षर param[4];

	अगर ((priv->flags & ALPS_DUALPOINT) &&
	    alps_setup_trackstick_v3(psmouse, ALPS_REG_BASE_PINNACLE) == -EIO)
		जाओ error;

	अगर (alps_enter_command_mode(psmouse) ||
	    alps_असलolute_mode_v3(psmouse)) अणु
		psmouse_err(psmouse, "Failed to enter absolute mode\n");
		जाओ error;
	पूर्ण

	reg_val = alps_command_mode_पढ़ो_reg(psmouse, 0x0006);
	अगर (reg_val == -1)
		जाओ error;
	अगर (__alps_command_mode_ग_लिखो_reg(psmouse, reg_val | 0x01))
		जाओ error;

	reg_val = alps_command_mode_पढ़ो_reg(psmouse, 0x0007);
	अगर (reg_val == -1)
		जाओ error;
	अगर (__alps_command_mode_ग_लिखो_reg(psmouse, reg_val | 0x01))
		जाओ error;

	अगर (alps_command_mode_पढ़ो_reg(psmouse, 0x0144) == -1)
		जाओ error;
	अगर (__alps_command_mode_ग_लिखो_reg(psmouse, 0x04))
		जाओ error;

	अगर (alps_command_mode_पढ़ो_reg(psmouse, 0x0159) == -1)
		जाओ error;
	अगर (__alps_command_mode_ग_लिखो_reg(psmouse, 0x03))
		जाओ error;

	अगर (alps_command_mode_पढ़ो_reg(psmouse, 0x0163) == -1)
		जाओ error;
	अगर (alps_command_mode_ग_लिखो_reg(psmouse, 0x0163, 0x03))
		जाओ error;

	अगर (alps_command_mode_पढ़ो_reg(psmouse, 0x0162) == -1)
		जाओ error;
	अगर (alps_command_mode_ग_लिखो_reg(psmouse, 0x0162, 0x04))
		जाओ error;

	alps_निकास_command_mode(psmouse);

	/* Set rate and enable data reporting */
	param[0] = 0x64;
	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE) ||
	    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_ENABLE)) अणु
		psmouse_err(psmouse, "Failed to enable data reporting\n");
		वापस -1;
	पूर्ण

	वापस 0;

error:
	/*
	 * Leaving the touchpad in command mode will essentially render
	 * it unusable until the machine reboots, so निकास it here just
	 * to be safe
	 */
	alps_निकास_command_mode(psmouse);
	वापस -1;
पूर्ण

अटल पूर्णांक alps_get_v3_v7_resolution(काष्ठा psmouse *psmouse, पूर्णांक reg_pitch)
अणु
	पूर्णांक reg, x_pitch, y_pitch, x_electrode, y_electrode, x_phys, y_phys;
	काष्ठा alps_data *priv = psmouse->निजी;

	reg = alps_command_mode_पढ़ो_reg(psmouse, reg_pitch);
	अगर (reg < 0)
		वापस reg;

	x_pitch = (अक्षर)(reg << 4) >> 4; /* sign extend lower 4 bits */
	x_pitch = 50 + 2 * x_pitch; /* In 0.1 mm units */

	y_pitch = (अक्षर)reg >> 4; /* sign extend upper 4 bits */
	y_pitch = 36 + 2 * y_pitch; /* In 0.1 mm units */

	reg = alps_command_mode_पढ़ो_reg(psmouse, reg_pitch + 1);
	अगर (reg < 0)
		वापस reg;

	x_electrode = (अक्षर)(reg << 4) >> 4; /* sign extend lower 4 bits */
	x_electrode = 17 + x_electrode;

	y_electrode = (अक्षर)reg >> 4; /* sign extend upper 4 bits */
	y_electrode = 13 + y_electrode;

	x_phys = x_pitch * (x_electrode - 1); /* In 0.1 mm units */
	y_phys = y_pitch * (y_electrode - 1); /* In 0.1 mm units */

	priv->x_res = priv->x_max * 10 / x_phys; /* units / mm */
	priv->y_res = priv->y_max * 10 / y_phys; /* units / mm */

	psmouse_dbg(psmouse,
		    "pitch %dx%d num-electrodes %dx%d physical size %dx%d mm res %dx%d\n",
		    x_pitch, y_pitch, x_electrode, y_electrode,
		    x_phys / 10, y_phys / 10, priv->x_res, priv->y_res);

	वापस 0;
पूर्ण

अटल पूर्णांक alps_hw_init_rushmore_v3(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	पूर्णांक reg_val, ret = -1;

	अगर (priv->flags & ALPS_DUALPOINT) अणु
		reg_val = alps_setup_trackstick_v3(psmouse,
						   ALPS_REG_BASE_RUSHMORE);
		अगर (reg_val == -EIO)
			जाओ error;
	पूर्ण

	अगर (alps_enter_command_mode(psmouse) ||
	    alps_command_mode_पढ़ो_reg(psmouse, 0xc2d9) == -1 ||
	    alps_command_mode_ग_लिखो_reg(psmouse, 0xc2cb, 0x00))
		जाओ error;

	अगर (alps_get_v3_v7_resolution(psmouse, 0xc2da))
		जाओ error;

	reg_val = alps_command_mode_पढ़ो_reg(psmouse, 0xc2c6);
	अगर (reg_val == -1)
		जाओ error;
	अगर (__alps_command_mode_ग_लिखो_reg(psmouse, reg_val & 0xfd))
		जाओ error;

	अगर (alps_command_mode_ग_लिखो_reg(psmouse, 0xc2c9, 0x64))
		जाओ error;

	/* enter असलolute mode */
	reg_val = alps_command_mode_पढ़ो_reg(psmouse, 0xc2c4);
	अगर (reg_val == -1)
		जाओ error;
	अगर (__alps_command_mode_ग_लिखो_reg(psmouse, reg_val | 0x02))
		जाओ error;

	alps_निकास_command_mode(psmouse);
	वापस ps2_command(ps2dev, शून्य, PSMOUSE_CMD_ENABLE);

error:
	alps_निकास_command_mode(psmouse);
	वापस ret;
पूर्ण

/* Must be in command mode when calling this function */
अटल पूर्णांक alps_असलolute_mode_v4(काष्ठा psmouse *psmouse)
अणु
	पूर्णांक reg_val;

	reg_val = alps_command_mode_पढ़ो_reg(psmouse, 0x0004);
	अगर (reg_val == -1)
		वापस -1;

	reg_val |= 0x02;
	अगर (__alps_command_mode_ग_लिखो_reg(psmouse, reg_val))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक alps_hw_init_v4(काष्ठा psmouse *psmouse)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	अचिन्हित अक्षर param[4];

	अगर (alps_enter_command_mode(psmouse))
		जाओ error;

	अगर (alps_असलolute_mode_v4(psmouse)) अणु
		psmouse_err(psmouse, "Failed to enter absolute mode\n");
		जाओ error;
	पूर्ण

	अगर (alps_command_mode_ग_लिखो_reg(psmouse, 0x0007, 0x8c))
		जाओ error;

	अगर (alps_command_mode_ग_लिखो_reg(psmouse, 0x0149, 0x03))
		जाओ error;

	अगर (alps_command_mode_ग_लिखो_reg(psmouse, 0x0160, 0x03))
		जाओ error;

	अगर (alps_command_mode_ग_लिखो_reg(psmouse, 0x017f, 0x15))
		जाओ error;

	अगर (alps_command_mode_ग_लिखो_reg(psmouse, 0x0151, 0x01))
		जाओ error;

	अगर (alps_command_mode_ग_लिखो_reg(psmouse, 0x0168, 0x03))
		जाओ error;

	अगर (alps_command_mode_ग_लिखो_reg(psmouse, 0x014a, 0x03))
		जाओ error;

	अगर (alps_command_mode_ग_लिखो_reg(psmouse, 0x0161, 0x03))
		जाओ error;

	alps_निकास_command_mode(psmouse);

	/*
	 * This sequence changes the output from a 9-byte to an
	 * 8-byte क्रमmat. All the same data seems to be present,
	 * just in a more compact क्रमmat.
	 */
	param[0] = 0xc8;
	param[1] = 0x64;
	param[2] = 0x50;
	अगर (ps2_command(ps2dev, &param[0], PSMOUSE_CMD_SETRATE) ||
	    ps2_command(ps2dev, &param[1], PSMOUSE_CMD_SETRATE) ||
	    ps2_command(ps2dev, &param[2], PSMOUSE_CMD_SETRATE) ||
	    ps2_command(ps2dev, param, PSMOUSE_CMD_GETID))
		वापस -1;

	/* Set rate and enable data reporting */
	param[0] = 0x64;
	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE) ||
	    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_ENABLE)) अणु
		psmouse_err(psmouse, "Failed to enable data reporting\n");
		वापस -1;
	पूर्ण

	वापस 0;

error:
	/*
	 * Leaving the touchpad in command mode will essentially render
	 * it unusable until the machine reboots, so निकास it here just
	 * to be safe
	 */
	alps_निकास_command_mode(psmouse);
	वापस -1;
पूर्ण

अटल पूर्णांक alps_get_otp_values_ss4_v2(काष्ठा psmouse *psmouse,
				      अचिन्हित अक्षर index, अचिन्हित अक्षर otp[])
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;

	चयन (index) अणु
	हाल 0:
		अगर (ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETSTREAM)  ||
		    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETSTREAM)  ||
		    ps2_command(ps2dev, otp, PSMOUSE_CMD_GETINFO))
			वापस -1;

		अवरोध;

	हाल 1:
		अगर (ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETPOLL)  ||
		    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETPOLL)  ||
		    ps2_command(ps2dev, otp, PSMOUSE_CMD_GETINFO))
			वापस -1;

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक alps_update_device_area_ss4_v2(अचिन्हित अक्षर otp[][4],
					  काष्ठा alps_data *priv)
अणु
	पूर्णांक num_x_electrode;
	पूर्णांक num_y_electrode;
	पूर्णांक x_pitch, y_pitch, x_phys, y_phys;

	अगर (IS_SS4PLUS_DEV(priv->dev_id)) अणु
		num_x_electrode =
			SS4PLUS_NUMSENSOR_XOFFSET + (otp[0][2] & 0x0F);
		num_y_electrode =
			SS4PLUS_NUMSENSOR_YOFFSET + ((otp[0][2] >> 4) & 0x0F);

		priv->x_max =
			(num_x_electrode - 1) * SS4PLUS_COUNT_PER_ELECTRODE;
		priv->y_max =
			(num_y_electrode - 1) * SS4PLUS_COUNT_PER_ELECTRODE;

		x_pitch = (otp[0][1] & 0x0F) + SS4PLUS_MIN_PITCH_MM;
		y_pitch = ((otp[0][1] >> 4) & 0x0F) + SS4PLUS_MIN_PITCH_MM;

	पूर्ण अन्यथा अणु
		num_x_electrode =
			SS4_NUMSENSOR_XOFFSET + (otp[1][0] & 0x0F);
		num_y_electrode =
			SS4_NUMSENSOR_YOFFSET + ((otp[1][0] >> 4) & 0x0F);

		priv->x_max =
			(num_x_electrode - 1) * SS4_COUNT_PER_ELECTRODE;
		priv->y_max =
			(num_y_electrode - 1) * SS4_COUNT_PER_ELECTRODE;

		x_pitch = ((otp[1][2] >> 2) & 0x07) + SS4_MIN_PITCH_MM;
		y_pitch = ((otp[1][2] >> 5) & 0x07) + SS4_MIN_PITCH_MM;
	पूर्ण

	x_phys = x_pitch * (num_x_electrode - 1); /* In 0.1 mm units */
	y_phys = y_pitch * (num_y_electrode - 1); /* In 0.1 mm units */

	priv->x_res = priv->x_max * 10 / x_phys; /* units / mm */
	priv->y_res = priv->y_max * 10 / y_phys; /* units / mm */

	वापस 0;
पूर्ण

अटल पूर्णांक alps_update_btn_info_ss4_v2(अचिन्हित अक्षर otp[][4],
				       काष्ठा alps_data *priv)
अणु
	अचिन्हित अक्षर is_btnless;

	अगर (IS_SS4PLUS_DEV(priv->dev_id))
		is_btnless = (otp[1][0] >> 1) & 0x01;
	अन्यथा
		is_btnless = (otp[1][1] >> 3) & 0x01;

	अगर (is_btnless)
		priv->flags |= ALPS_BUTTONPAD;

	वापस 0;
पूर्ण

अटल पूर्णांक alps_update_dual_info_ss4_v2(अचिन्हित अक्षर otp[][4],
					काष्ठा alps_data *priv,
					काष्ठा psmouse *psmouse)
अणु
	bool is_dual = false;
	पूर्णांक reg_val = 0;
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;

	अगर (IS_SS4PLUS_DEV(priv->dev_id)) अणु
		is_dual = (otp[0][0] >> 4) & 0x01;

		अगर (!is_dual) अणु
			/* For support TrackStick of Thinkpad L/E series */
			अगर (alps_निकास_command_mode(psmouse) == 0 &&
				alps_enter_command_mode(psmouse) == 0) अणु
				reg_val = alps_command_mode_पढ़ो_reg(psmouse,
									0xD7);
			पूर्ण
			alps_निकास_command_mode(psmouse);
			ps2_command(ps2dev, शून्य, PSMOUSE_CMD_ENABLE);

			अगर (reg_val == 0x0C || reg_val == 0x1D)
				is_dual = true;
		पूर्ण
	पूर्ण

	अगर (is_dual)
		priv->flags |= ALPS_DUALPOINT |
					ALPS_DUALPOINT_WITH_PRESSURE;

	वापस 0;
पूर्ण

अटल पूर्णांक alps_set_शेषs_ss4_v2(काष्ठा psmouse *psmouse,
				    काष्ठा alps_data *priv)
अणु
	अचिन्हित अक्षर otp[2][4];

	स_रखो(otp, 0, माप(otp));

	अगर (alps_get_otp_values_ss4_v2(psmouse, 1, &otp[1][0]) ||
	    alps_get_otp_values_ss4_v2(psmouse, 0, &otp[0][0]))
		वापस -1;

	alps_update_device_area_ss4_v2(otp, priv);

	alps_update_btn_info_ss4_v2(otp, priv);

	alps_update_dual_info_ss4_v2(otp, priv, psmouse);

	वापस 0;
पूर्ण

अटल पूर्णांक alps_करोlphin_get_device_area(काष्ठा psmouse *psmouse,
					काष्ठा alps_data *priv)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	अचिन्हित अक्षर param[4] = अणु0पूर्ण;
	पूर्णांक num_x_electrode, num_y_electrode;

	अगर (alps_enter_command_mode(psmouse))
		वापस -1;

	param[0] = 0x0a;
	अगर (ps2_command(ps2dev, शून्य, PSMOUSE_CMD_RESET_WRAP) ||
	    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETPOLL) ||
	    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETPOLL) ||
	    ps2_command(ps2dev, &param[0], PSMOUSE_CMD_SETRATE) ||
	    ps2_command(ps2dev, &param[0], PSMOUSE_CMD_SETRATE))
		वापस -1;

	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO))
		वापस -1;

	/*
	 * Dolphin's sensor line number is not fixed. It can be calculated
	 * by adding the device's रेजिस्टर value with DOLPHIN_PROखाता_X/YOFFSET.
	 * Further more, we can get device's x_max and y_max by multiplying
	 * sensor line number with DOLPHIN_COUNT_PER_ELECTRODE.
	 *
	 * e.g. When we get रेजिस्टर's sensor_x = 11 & sensor_y = 8,
	 *	real sensor line number X = 11 + 8 = 19, and
	 *	real sensor line number Y = 8 + 1 = 9.
	 *	So, x_max = (19 - 1) * 64 = 1152, and
	 *	    y_max = (9 - 1) * 64 = 512.
	 */
	num_x_electrode = DOLPHIN_PROखाता_XOFFSET + (param[2] & 0x0F);
	num_y_electrode = DOLPHIN_PROखाता_YOFFSET + ((param[2] >> 4) & 0x0F);
	priv->x_bits = num_x_electrode;
	priv->y_bits = num_y_electrode;
	priv->x_max = (num_x_electrode - 1) * DOLPHIN_COUNT_PER_ELECTRODE;
	priv->y_max = (num_y_electrode - 1) * DOLPHIN_COUNT_PER_ELECTRODE;

	अगर (alps_निकास_command_mode(psmouse))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक alps_hw_init_करोlphin_v1(काष्ठा psmouse *psmouse)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	अचिन्हित अक्षर param[2];

	/* This is करोlphin "v1" as empirically defined by florin9करोi */
	param[0] = 0x64;
	param[1] = 0x28;

	अगर (ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETSTREAM) ||
	    ps2_command(ps2dev, &param[0], PSMOUSE_CMD_SETRATE) ||
	    ps2_command(ps2dev, &param[1], PSMOUSE_CMD_SETRATE))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक alps_hw_init_v7(काष्ठा psmouse *psmouse)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	पूर्णांक reg_val, ret = -1;

	अगर (alps_enter_command_mode(psmouse) ||
	    alps_command_mode_पढ़ो_reg(psmouse, 0xc2d9) == -1)
		जाओ error;

	अगर (alps_get_v3_v7_resolution(psmouse, 0xc397))
		जाओ error;

	अगर (alps_command_mode_ग_लिखो_reg(psmouse, 0xc2c9, 0x64))
		जाओ error;

	reg_val = alps_command_mode_पढ़ो_reg(psmouse, 0xc2c4);
	अगर (reg_val == -1)
		जाओ error;
	अगर (__alps_command_mode_ग_लिखो_reg(psmouse, reg_val | 0x02))
		जाओ error;

	alps_निकास_command_mode(psmouse);
	वापस ps2_command(ps2dev, शून्य, PSMOUSE_CMD_ENABLE);

error:
	alps_निकास_command_mode(psmouse);
	वापस ret;
पूर्ण

अटल पूर्णांक alps_hw_init_ss4_v2(काष्ठा psmouse *psmouse)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	अक्षर param[2] = अणु0x64, 0x28पूर्ण;
	पूर्णांक ret = -1;

	/* enter असलolute mode */
	अगर (ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETSTREAM) ||
	    ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETSTREAM) ||
	    ps2_command(ps2dev, &param[0], PSMOUSE_CMD_SETRATE) ||
	    ps2_command(ps2dev, &param[1], PSMOUSE_CMD_SETRATE)) अणु
		जाओ error;
	पूर्ण

	/* T.B.D. Decपढ़ो noise packet number, delete in the future */
	अगर (alps_निकास_command_mode(psmouse) ||
	    alps_enter_command_mode(psmouse) ||
	    alps_command_mode_ग_लिखो_reg(psmouse, 0x001D, 0x20)) अणु
		जाओ error;
	पूर्ण
	alps_निकास_command_mode(psmouse);

	वापस ps2_command(ps2dev, शून्य, PSMOUSE_CMD_ENABLE);

error:
	alps_निकास_command_mode(psmouse);
	वापस ret;
पूर्ण

अटल पूर्णांक alps_set_protocol(काष्ठा psmouse *psmouse,
			     काष्ठा alps_data *priv,
			     स्थिर काष्ठा alps_protocol_info *protocol)
अणु
	psmouse->निजी = priv;

	समयr_setup(&priv->समयr, alps_flush_packet, 0);

	priv->proto_version = protocol->version;
	priv->byte0 = protocol->byte0;
	priv->mask0 = protocol->mask0;
	priv->flags = protocol->flags;

	priv->x_max = 2000;
	priv->y_max = 1400;
	priv->x_bits = 15;
	priv->y_bits = 11;

	चयन (priv->proto_version) अणु
	हाल ALPS_PROTO_V1:
	हाल ALPS_PROTO_V2:
		priv->hw_init = alps_hw_init_v1_v2;
		priv->process_packet = alps_process_packet_v1_v2;
		priv->set_असल_params = alps_set_असल_params_st;
		priv->x_max = 1023;
		priv->y_max = 767;
		अगर (dmi_check_प्रणाली(alps_dmi_has_separate_stick_buttons))
			priv->flags |= ALPS_STICK_BITS;
		अवरोध;

	हाल ALPS_PROTO_V3:
		priv->hw_init = alps_hw_init_v3;
		priv->process_packet = alps_process_packet_v3;
		priv->set_असल_params = alps_set_असल_params_semi_mt;
		priv->decode_fields = alps_decode_pinnacle;
		priv->nibble_commands = alps_v3_nibble_commands;
		priv->addr_command = PSMOUSE_CMD_RESET_WRAP;

		अगर (alps_probe_trackstick_v3_v7(psmouse,
						ALPS_REG_BASE_PINNACLE) < 0)
			priv->flags &= ~ALPS_DUALPOINT;

		अवरोध;

	हाल ALPS_PROTO_V3_RUSHMORE:
		priv->hw_init = alps_hw_init_rushmore_v3;
		priv->process_packet = alps_process_packet_v3;
		priv->set_असल_params = alps_set_असल_params_semi_mt;
		priv->decode_fields = alps_decode_rushmore;
		priv->nibble_commands = alps_v3_nibble_commands;
		priv->addr_command = PSMOUSE_CMD_RESET_WRAP;
		priv->x_bits = 16;
		priv->y_bits = 12;

		अगर (alps_probe_trackstick_v3_v7(psmouse,
						ALPS_REG_BASE_RUSHMORE) < 0)
			priv->flags &= ~ALPS_DUALPOINT;

		अवरोध;

	हाल ALPS_PROTO_V4:
		priv->hw_init = alps_hw_init_v4;
		priv->process_packet = alps_process_packet_v4;
		priv->set_असल_params = alps_set_असल_params_semi_mt;
		priv->nibble_commands = alps_v4_nibble_commands;
		priv->addr_command = PSMOUSE_CMD_DISABLE;
		अवरोध;

	हाल ALPS_PROTO_V5:
		priv->hw_init = alps_hw_init_करोlphin_v1;
		priv->process_packet = alps_process_touchpad_packet_v3_v5;
		priv->decode_fields = alps_decode_करोlphin;
		priv->set_असल_params = alps_set_असल_params_semi_mt;
		priv->nibble_commands = alps_v3_nibble_commands;
		priv->addr_command = PSMOUSE_CMD_RESET_WRAP;
		priv->x_bits = 23;
		priv->y_bits = 12;

		अगर (alps_करोlphin_get_device_area(psmouse, priv))
			वापस -EIO;

		अवरोध;

	हाल ALPS_PROTO_V6:
		priv->hw_init = alps_hw_init_v6;
		priv->process_packet = alps_process_packet_v6;
		priv->set_असल_params = alps_set_असल_params_st;
		priv->nibble_commands = alps_v6_nibble_commands;
		priv->x_max = 2047;
		priv->y_max = 1535;
		अवरोध;

	हाल ALPS_PROTO_V7:
		priv->hw_init = alps_hw_init_v7;
		priv->process_packet = alps_process_packet_v7;
		priv->decode_fields = alps_decode_packet_v7;
		priv->set_असल_params = alps_set_असल_params_v7;
		priv->nibble_commands = alps_v3_nibble_commands;
		priv->addr_command = PSMOUSE_CMD_RESET_WRAP;
		priv->x_max = 0xfff;
		priv->y_max = 0x7ff;

		अगर (priv->fw_ver[1] != 0xba)
			priv->flags |= ALPS_BUTTONPAD;

		अगर (alps_probe_trackstick_v3_v7(psmouse, ALPS_REG_BASE_V7) < 0)
			priv->flags &= ~ALPS_DUALPOINT;

		अवरोध;

	हाल ALPS_PROTO_V8:
		priv->hw_init = alps_hw_init_ss4_v2;
		priv->process_packet = alps_process_packet_ss4_v2;
		priv->decode_fields = alps_decode_ss4_v2;
		priv->set_असल_params = alps_set_असल_params_ss4_v2;
		priv->nibble_commands = alps_v3_nibble_commands;
		priv->addr_command = PSMOUSE_CMD_RESET_WRAP;

		अगर (alps_set_शेषs_ss4_v2(psmouse, priv))
			वापस -EIO;

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा alps_protocol_info *alps_match_table(अचिन्हित अक्षर *e7,
							 अचिन्हित अक्षर *ec)
अणु
	स्थिर काष्ठा alps_model_info *model;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(alps_model_data); i++) अणु
		model = &alps_model_data[i];

		अगर (!स_भेद(e7, model->signature, माप(model->signature)))
			वापस &model->protocol_info;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool alps_is_cs19_trackpoपूर्णांक(काष्ठा psmouse *psmouse)
अणु
	u8 param[2] = अणु 0 पूर्ण;

	अगर (ps2_command(&psmouse->ps2dev,
			param, MAKE_PS2_CMD(0, 2, TP_READ_ID)))
		वापस false;

	/*
	 * param[0] contains the trackpoपूर्णांक device variant_id जबतक
	 * param[1] contains the firmware_id. So far all alps
	 * trackpoपूर्णांक-only devices have their variant_ids equal
	 * TP_VARIANT_ALPS and their firmware_ids are in 0x20~0x2f range.
	 */
	वापस param[0] == TP_VARIANT_ALPS && ((param[1] & 0xf0) == 0x20);
पूर्ण

अटल पूर्णांक alps_identअगरy(काष्ठा psmouse *psmouse, काष्ठा alps_data *priv)
अणु
	स्थिर काष्ठा alps_protocol_info *protocol;
	अचिन्हित अक्षर e6[4], e7[4], ec[4];
	पूर्णांक error;

	/*
	 * First try "E6 report".
	 * ALPS should वापस 0,0,10 or 0,0,100 अगर no buttons are pressed.
	 * The bits 0-2 of the first byte will be 1s अगर some buttons are
	 * pressed.
	 */
	अगर (alps_rpt_cmd(psmouse, PSMOUSE_CMD_SETRES,
			 PSMOUSE_CMD_SETSCALE11, e6))
		वापस -EIO;

	अगर ((e6[0] & 0xf8) != 0 || e6[1] != 0 || (e6[2] != 10 && e6[2] != 100))
		वापस -EINVAL;

	/*
	 * Now get the "E7" and "EC" reports.  These will uniquely identअगरy
	 * most ALPS touchpads.
	 */
	अगर (alps_rpt_cmd(psmouse, PSMOUSE_CMD_SETRES,
			 PSMOUSE_CMD_SETSCALE21, e7) ||
	    alps_rpt_cmd(psmouse, PSMOUSE_CMD_SETRES,
			 PSMOUSE_CMD_RESET_WRAP, ec) ||
	    alps_निकास_command_mode(psmouse))
		वापस -EIO;

	protocol = alps_match_table(e7, ec);
	अगर (!protocol) अणु
		अगर (e7[0] == 0x73 && e7[1] == 0x02 && e7[2] == 0x64 &&
			   ec[2] == 0x8a) अणु
			protocol = &alps_v4_protocol_data;
		पूर्ण अन्यथा अगर (e7[0] == 0x73 && e7[1] == 0x03 && e7[2] == 0x50 &&
			   ec[0] == 0x73 && (ec[1] == 0x01 || ec[1] == 0x02)) अणु
			protocol = &alps_v5_protocol_data;
		पूर्ण अन्यथा अगर (ec[0] == 0x88 &&
			   ((ec[1] & 0xf0) == 0xb0 || (ec[1] & 0xf0) == 0xc0)) अणु
			protocol = &alps_v7_protocol_data;
		पूर्ण अन्यथा अगर (ec[0] == 0x88 && ec[1] == 0x08) अणु
			protocol = &alps_v3_rushmore_data;
		पूर्ण अन्यथा अगर (ec[0] == 0x88 && ec[1] == 0x07 &&
			   ec[2] >= 0x90 && ec[2] <= 0x9d) अणु
			protocol = &alps_v3_protocol_data;
		पूर्ण अन्यथा अगर (e7[0] == 0x73 && e7[1] == 0x03 &&
			   (e7[2] == 0x14 || e7[2] == 0x28)) अणु
			protocol = &alps_v8_protocol_data;
		पूर्ण अन्यथा अगर (e7[0] == 0x73 && e7[1] == 0x03 && e7[2] == 0xc8) अणु
			protocol = &alps_v9_protocol_data;
			psmouse_warn(psmouse,
				     "Unsupported ALPS V9 touchpad: E7=%3ph, EC=%3ph\n",
				     e7, ec);
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			psmouse_dbg(psmouse,
				    "Likely not an ALPS touchpad: E7=%3ph, EC=%3ph\n", e7, ec);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (priv) अणु
		/* Save Device ID and Firmware version */
		स_नकल(priv->dev_id, e7, 3);
		स_नकल(priv->fw_ver, ec, 3);
		error = alps_set_protocol(psmouse, priv, protocol);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक alps_reconnect(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;

	psmouse_reset(psmouse);

	अगर (alps_identअगरy(psmouse, priv) < 0)
		वापस -1;

	वापस priv->hw_init(psmouse);
पूर्ण

अटल व्योम alps_disconnect(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;

	psmouse_reset(psmouse);
	del_समयr_sync(&priv->समयr);
	अगर (priv->dev2)
		input_unरेजिस्टर_device(priv->dev2);
	अगर (!IS_ERR_OR_शून्य(priv->dev3))
		input_unरेजिस्टर_device(priv->dev3);
	kमुक्त(priv);
पूर्ण

अटल व्योम alps_set_असल_params_st(काष्ठा alps_data *priv,
				   काष्ठा input_dev *dev1)
अणु
	input_set_असल_params(dev1, ABS_X, 0, priv->x_max, 0, 0);
	input_set_असल_params(dev1, ABS_Y, 0, priv->y_max, 0, 0);
	input_set_असल_params(dev1, ABS_PRESSURE, 0, 127, 0, 0);
पूर्ण

अटल व्योम alps_set_असल_params_mt_common(काष्ठा alps_data *priv,
					  काष्ठा input_dev *dev1)
अणु
	input_set_असल_params(dev1, ABS_MT_POSITION_X, 0, priv->x_max, 0, 0);
	input_set_असल_params(dev1, ABS_MT_POSITION_Y, 0, priv->y_max, 0, 0);

	input_असल_set_res(dev1, ABS_MT_POSITION_X, priv->x_res);
	input_असल_set_res(dev1, ABS_MT_POSITION_Y, priv->y_res);

	set_bit(BTN_TOOL_TRIPLETAP, dev1->keybit);
	set_bit(BTN_TOOL_QUADTAP, dev1->keybit);
पूर्ण

अटल व्योम alps_set_असल_params_semi_mt(काष्ठा alps_data *priv,
					काष्ठा input_dev *dev1)
अणु
	alps_set_असल_params_mt_common(priv, dev1);
	input_set_असल_params(dev1, ABS_PRESSURE, 0, 127, 0, 0);

	input_mt_init_slots(dev1, MAX_TOUCHES,
			    INPUT_MT_POINTER | INPUT_MT_DROP_UNUSED |
				INPUT_MT_SEMI_MT);
पूर्ण

अटल व्योम alps_set_असल_params_v7(काष्ठा alps_data *priv,
				   काष्ठा input_dev *dev1)
अणु
	alps_set_असल_params_mt_common(priv, dev1);
	set_bit(BTN_TOOL_QUINTTAP, dev1->keybit);

	input_mt_init_slots(dev1, MAX_TOUCHES,
			    INPUT_MT_POINTER | INPUT_MT_DROP_UNUSED |
				INPUT_MT_TRACK);

	set_bit(BTN_TOOL_QUINTTAP, dev1->keybit);
पूर्ण

अटल व्योम alps_set_असल_params_ss4_v2(काष्ठा alps_data *priv,
				       काष्ठा input_dev *dev1)
अणु
	alps_set_असल_params_mt_common(priv, dev1);
	input_set_असल_params(dev1, ABS_PRESSURE, 0, 127, 0, 0);
	set_bit(BTN_TOOL_QUINTTAP, dev1->keybit);

	input_mt_init_slots(dev1, MAX_TOUCHES,
			    INPUT_MT_POINTER | INPUT_MT_DROP_UNUSED |
				INPUT_MT_TRACK);
पूर्ण

पूर्णांक alps_init(काष्ठा psmouse *psmouse)
अणु
	काष्ठा alps_data *priv = psmouse->निजी;
	काष्ठा input_dev *dev1 = psmouse->dev;
	पूर्णांक error;

	error = priv->hw_init(psmouse);
	अगर (error)
		जाओ init_fail;

	/*
	 * Unकरो part of setup करोne क्रम us by psmouse core since touchpad
	 * is not a relative device.
	 */
	__clear_bit(EV_REL, dev1->evbit);
	__clear_bit(REL_X, dev1->relbit);
	__clear_bit(REL_Y, dev1->relbit);

	/*
	 * Now set up our capabilities.
	 */
	dev1->evbit[BIT_WORD(EV_KEY)] |= BIT_MASK(EV_KEY);
	dev1->keybit[BIT_WORD(BTN_TOUCH)] |= BIT_MASK(BTN_TOUCH);
	dev1->keybit[BIT_WORD(BTN_TOOL_FINGER)] |= BIT_MASK(BTN_TOOL_FINGER);
	dev1->keybit[BIT_WORD(BTN_LEFT)] |=
		BIT_MASK(BTN_LEFT) | BIT_MASK(BTN_RIGHT);

	dev1->evbit[BIT_WORD(EV_ABS)] |= BIT_MASK(EV_ABS);

	priv->set_असल_params(priv, dev1);

	अगर (priv->flags & ALPS_WHEEL) अणु
		dev1->evbit[BIT_WORD(EV_REL)] |= BIT_MASK(EV_REL);
		dev1->relbit[BIT_WORD(REL_WHEEL)] |= BIT_MASK(REL_WHEEL);
	पूर्ण

	अगर (priv->flags & (ALPS_FW_BK_1 | ALPS_FW_BK_2)) अणु
		dev1->keybit[BIT_WORD(BTN_FORWARD)] |= BIT_MASK(BTN_FORWARD);
		dev1->keybit[BIT_WORD(BTN_BACK)] |= BIT_MASK(BTN_BACK);
	पूर्ण

	अगर (priv->flags & ALPS_FOUR_BUTTONS) अणु
		dev1->keybit[BIT_WORD(BTN_0)] |= BIT_MASK(BTN_0);
		dev1->keybit[BIT_WORD(BTN_1)] |= BIT_MASK(BTN_1);
		dev1->keybit[BIT_WORD(BTN_2)] |= BIT_MASK(BTN_2);
		dev1->keybit[BIT_WORD(BTN_3)] |= BIT_MASK(BTN_3);
	पूर्ण अन्यथा अगर (priv->flags & ALPS_BUTTONPAD) अणु
		set_bit(INPUT_PROP_BUTTONPAD, dev1->propbit);
		clear_bit(BTN_RIGHT, dev1->keybit);
	पूर्ण अन्यथा अणु
		dev1->keybit[BIT_WORD(BTN_MIDDLE)] |= BIT_MASK(BTN_MIDDLE);
	पूर्ण

	अगर (priv->flags & ALPS_DUALPOINT) अणु
		काष्ठा input_dev *dev2;

		dev2 = input_allocate_device();
		अगर (!dev2) अणु
			psmouse_err(psmouse,
				    "failed to allocate trackstick device\n");
			error = -ENOMEM;
			जाओ init_fail;
		पूर्ण

		snम_लिखो(priv->phys2, माप(priv->phys2), "%s/input1",
			 psmouse->ps2dev.serio->phys);
		dev2->phys = priv->phys2;

		/*
		 * क्रमmat of input device name is: "protocol vendor name"
		 * see function psmouse_चयन_protocol() in psmouse-base.c
		 */
		dev2->name = "AlpsPS/2 ALPS DualPoint Stick";

		dev2->id.bustype = BUS_I8042;
		dev2->id.venकरोr  = 0x0002;
		dev2->id.product = PSMOUSE_ALPS;
		dev2->id.version = priv->proto_version;
		dev2->dev.parent = &psmouse->ps2dev.serio->dev;

		input_set_capability(dev2, EV_REL, REL_X);
		input_set_capability(dev2, EV_REL, REL_Y);
		अगर (priv->flags & ALPS_DUALPOINT_WITH_PRESSURE) अणु
			input_set_capability(dev2, EV_ABS, ABS_PRESSURE);
			input_set_असल_params(dev2, ABS_PRESSURE, 0, 127, 0, 0);
		पूर्ण
		input_set_capability(dev2, EV_KEY, BTN_LEFT);
		input_set_capability(dev2, EV_KEY, BTN_RIGHT);
		input_set_capability(dev2, EV_KEY, BTN_MIDDLE);

		__set_bit(INPUT_PROP_POINTER, dev2->propbit);
		__set_bit(INPUT_PROP_POINTING_STICK, dev2->propbit);

		error = input_रेजिस्टर_device(dev2);
		अगर (error) अणु
			psmouse_err(psmouse,
				    "failed to register trackstick device: %d\n",
				    error);
			input_मुक्त_device(dev2);
			जाओ init_fail;
		पूर्ण

		priv->dev2 = dev2;
	पूर्ण

	priv->psmouse = psmouse;

	INIT_DELAYED_WORK(&priv->dev3_रेजिस्टर_work,
			  alps_रेजिस्टर_bare_ps2_mouse);

	psmouse->protocol_handler = alps_process_byte;
	psmouse->poll = alps_poll;
	psmouse->disconnect = alps_disconnect;
	psmouse->reconnect = alps_reconnect;
	psmouse->pktsize = priv->proto_version == ALPS_PROTO_V4 ? 8 : 6;

	/* We are having trouble resyncing ALPS touchpads so disable it क्रम now */
	psmouse->resync_समय = 0;

	/* Allow 2 invalid packets without resetting device */
	psmouse->resetafter = psmouse->pktsize * 2;

	वापस 0;

init_fail:
	psmouse_reset(psmouse);
	/*
	 * Even though we did not allocate psmouse->निजी we करो मुक्त
	 * it here.
	 */
	kमुक्त(psmouse->निजी);
	psmouse->निजी = शून्य;
	वापस error;
पूर्ण

पूर्णांक alps_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	काष्ठा alps_data *priv;
	पूर्णांक error;

	error = alps_identअगरy(psmouse, शून्य);
	अगर (error)
		वापस error;

	/*
	 * ALPS cs19 is a trackpoपूर्णांक-only device, and uses dअगरferent
	 * protocol than DualPoपूर्णांक ones, so we वापस -EINVAL here and let
	 * trackpoपूर्णांक.c drive this device. If the trackpoपूर्णांक driver is not
	 * enabled, the device will fall back to a bare PS/2 mouse.
	 * If ps2_command() fails here, we depend on the immediately
	 * followed psmouse_reset() to reset the device to normal state.
	 */
	अगर (alps_is_cs19_trackpoपूर्णांक(psmouse)) अणु
		psmouse_dbg(psmouse,
			    "ALPS CS19 trackpoint-only device detected, ignoring\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Reset the device to make sure it is fully operational:
	 * on some laptops, like certain Dell Latitudes, we may
	 * fail to properly detect presence of trackstick अगर device
	 * has not been reset.
	 */
	psmouse_reset(psmouse);

	priv = kzalloc(माप(काष्ठा alps_data), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	error = alps_identअगरy(psmouse, priv);
	अगर (error) अणु
		kमुक्त(priv);
		वापस error;
	पूर्ण

	अगर (set_properties) अणु
		psmouse->venकरोr = "ALPS";
		psmouse->name = priv->flags & ALPS_DUALPOINT ?
				"DualPoint TouchPad" : "GlidePoint";
		psmouse->model = priv->proto_version;
	पूर्ण अन्यथा अणु
		/*
		 * Destroy alps_data काष्ठाure we allocated earlier since
		 * this was just a "trial run". Otherwise we'll keep it
		 * to be used by alps_init() which has to be called अगर
		 * we succeed and set_properties is true.
		 */
		kमुक्त(priv);
		psmouse->निजी = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

