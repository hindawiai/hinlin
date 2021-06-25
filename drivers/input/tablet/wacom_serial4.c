<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Wacom protocol 4 serial tablet driver
 *
 * Copyright 2014      Hans de Goede <hdegoede@redhat.com>
 * Copyright 2011-2012 Julian Squires <julian@cipht.net>
 *
 * Many thanks to Bill Seremetis, without whom PenPartner support
 * would not have been possible. Thanks to Patrick Mahoney.
 *
 * This driver was developed with reference to much code written by others,
 * particularly:
 *  - elo, gunze drivers by Vojtech Pavlik <vojtech@ucw.cz>;
 *  - wacom_w8001 driver by Jaya Kumar <jayakumar.lkml@gmail.com>;
 *  - the USB wacom input driver, credited to many people
 *    (see drivers/input/tablet/wacom.h);
 *  - new and old versions of linuxwacom / xf86-input-wacom credited to
 *    Frederic Lepied, France. <Lepied@XFree86.org> and
 *    Ping Cheng, Wacom. <pingc@wacom.com>;
 *  - and xf86wacom.c (a presumably ancient version of the linuxwacom code),
 *    by Frederic Lepied and Raph Levien <raph@gtk.org>.
 *
 * To करो:
 *  - support pad buttons; (requires access to a model with pad buttons)
 *  - support (protocol 4-style) tilt (requires access to a > 1.4 rom model)
 */

/*
 * Wacom serial protocol 4 करोcumentation taken from linuxwacom-0.9.9 code,
 * protocol 4 uses 7 or 9 byte of data in the following क्रमmat:
 *
 *	Byte 1
 *	bit 7  Sync bit always 1
 *	bit 6  Poपूर्णांकing device detected
 *	bit 5  Cursor = 0 / Stylus = 1
 *	bit 4  Reserved
 *	bit 3  1 अगर a button on the poपूर्णांकing device has been pressed
 *	bit 2  P0 (optional)
 *	bit 1  X15
 *	bit 0  X14
 *
 *	Byte 2
 *	bit 7  Always 0
 *	bits 6-0 = X13 - X7
 *
 *	Byte 3
 *	bit 7  Always 0
 *	bits 6-0 = X6 - X0
 *
 *	Byte 4
 *	bit 7  Always 0
 *	bit 6  B3
 *	bit 5  B2
 *	bit 4  B1
 *	bit 3  B0
 *	bit 2  P1 (optional)
 *	bit 1  Y15
 *	bit 0  Y14
 *
 *	Byte 5
 *	bit 7  Always 0
 *	bits 6-0 = Y13 - Y7
 *
 *	Byte 6
 *	bit 7  Always 0
 *	bits 6-0 = Y6 - Y0
 *
 *	Byte 7
 *	bit 7 Always 0
 *	bit 6  Sign of pressure data; or wheel-rel क्रम cursor tool
 *	bit 5  P7; or REL1 क्रम cursor tool
 *	bit 4  P6; or REL0 क्रम cursor tool
 *	bit 3  P5
 *	bit 2  P4
 *	bit 1  P3
 *	bit 0  P2
 *
 *	byte 8 and 9 are optional and present only
 *	in tilt mode.
 *
 *	Byte 8
 *	bit 7 Always 0
 *	bit 6 Sign of tilt X
 *	bit 5  Xt6
 *	bit 4  Xt5
 *	bit 3  Xt4
 *	bit 2  Xt3
 *	bit 1  Xt2
 *	bit 0  Xt1
 *
 *	Byte 9
 *	bit 7 Always 0
 *	bit 6 Sign of tilt Y
 *	bit 5  Yt6
 *	bit 4  Yt5
 *	bit 3  Yt4
 *	bit 2  Yt3
 *	bit 1  Yt2
 *	bit 0  Yt1
 */

#समावेश <linux/completion.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/serपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

MODULE_AUTHOR("Julian Squires <julian@cipht.net>, Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Wacom protocol 4 serial tablet driver");
MODULE_LICENSE("GPL");

#घोषणा REQUEST_MODEL_AND_ROM_VERSION	"~#"
#घोषणा REQUEST_MAX_COORDINATES		"~C\r"
#घोषणा REQUEST_CONFIGURATION_STRING	"~R\r"
#घोषणा REQUEST_RESET_TO_PROTOCOL_IV	"\r#"
/*
 * Note: sending "\r$\r" causes at least the Digitizer II to send
 * packets in ASCII instead of binary.  "\r#" seems to unकरो that.
 */

#घोषणा COMMAND_START_SENDING_PACKETS		"ST\r"
#घोषणा COMMAND_STOP_SENDING_PACKETS		"SP\r"
#घोषणा COMMAND_MULTI_MODE_INPUT		"MU1\r"
#घोषणा COMMAND_ORIGIN_IN_UPPER_LEFT		"OC1\r"
#घोषणा COMMAND_ENABLE_ALL_MACRO_BUTTONS	"~M0\r"
#घोषणा COMMAND_DISABLE_GROUP_1_MACRO_BUTTONS	"~M1\r"
#घोषणा COMMAND_TRANSMIT_AT_MAX_RATE		"IT0\r"
#घोषणा COMMAND_DISABLE_INCREMENTAL_MODE	"IN0\r"
#घोषणा COMMAND_ENABLE_CONTINUOUS_MODE		"SR\r"
#घोषणा COMMAND_ENABLE_PRESSURE_MODE		"PH1\r"
#घोषणा COMMAND_Z_FILTER			"ZF1\r"

/* Note that this is a protocol 4 packet without tilt inक्रमmation. */
#घोषणा PACKET_LENGTH		7
#घोषणा DATA_SIZE		32

/* flags */
#घोषणा F_COVERS_SCREEN		0x01
#घोषणा F_HAS_STYLUS2		0x02
#घोषणा F_HAS_SCROLLWHEEL	0x04

/* device IDs */
#घोषणा STYLUS_DEVICE_ID	0x02
#घोषणा CURSOR_DEVICE_ID	0x06
#घोषणा ERASER_DEVICE_ID	0x0A

क्रमागत अणु STYLUS = 1, ERASER, CURSOR पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक device_id;
	पूर्णांक input_id;
पूर्ण tools[] = अणु
	अणु 0, 0 पूर्ण,
	अणु STYLUS_DEVICE_ID, BTN_TOOL_PEN पूर्ण,
	अणु ERASER_DEVICE_ID, BTN_TOOL_RUBBER पूर्ण,
	अणु CURSOR_DEVICE_ID, BTN_TOOL_MOUSE पूर्ण,
पूर्ण;

काष्ठा wacom अणु
	काष्ठा input_dev *dev;
	काष्ठा completion cmd_करोne;
	पूर्णांक result;
	u8 expect;
	u8 eraser_mask;
	अचिन्हित पूर्णांक extra_z_bits;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक res_x, res_y;
	अचिन्हित पूर्णांक max_x, max_y;
	अचिन्हित पूर्णांक tool;
	अचिन्हित पूर्णांक idx;
	u8 data[DATA_SIZE];
	अक्षर phys[32];
पूर्ण;

क्रमागत अणु
	MODEL_CINTIQ		= 0x504C, /* PL */
	MODEL_CINTIQ2		= 0x4454, /* DT */
	MODEL_DIGITIZER_II	= 0x5544, /* UD */
	MODEL_GRAPHIRE		= 0x4554, /* ET */
	MODEL_PENPARTNER	= 0x4354, /* CT */
	MODEL_ARTPAD_II		= 0x4B54, /* KT */
पूर्ण;

अटल व्योम wacom_handle_model_response(काष्ठा wacom *wacom)
अणु
	पूर्णांक major_v, minor_v, r = 0;
	अक्षर *p;

	p = म_खोजप(wacom->data, 'V');
	अगर (p)
		r = माला_पूछो(p + 1, "%u.%u", &major_v, &minor_v);
	अगर (r != 2)
		major_v = minor_v = 0;

	चयन (wacom->data[2] << 8 | wacom->data[3]) अणु
	हाल MODEL_CINTIQ:	/* UNTESTED */
	हाल MODEL_CINTIQ2:
		अगर ((wacom->data[2] << 8 | wacom->data[3]) == MODEL_CINTIQ) अणु
			wacom->dev->name = "Wacom Cintiq";
			wacom->dev->id.version = MODEL_CINTIQ;
		पूर्ण अन्यथा अणु
			wacom->dev->name = "Wacom Cintiq II";
			wacom->dev->id.version = MODEL_CINTIQ2;
		पूर्ण
		wacom->res_x = 508;
		wacom->res_y = 508;

		चयन (wacom->data[5] << 8 | wacom->data[6]) अणु
		हाल 0x3731: /* PL-710 */
			wacom->res_x = 2540;
			wacom->res_y = 2540;
			fallthrough;
		हाल 0x3535: /* PL-550 */
		हाल 0x3830: /* PL-800 */
			wacom->extra_z_bits = 2;
		पूर्ण

		wacom->flags = F_COVERS_SCREEN;
		अवरोध;

	हाल MODEL_PENPARTNER:
		wacom->dev->name = "Wacom Penpartner";
		wacom->dev->id.version = MODEL_PENPARTNER;
		wacom->res_x = 1000;
		wacom->res_y = 1000;
		अवरोध;

	हाल MODEL_GRAPHIRE:
		wacom->dev->name = "Wacom Graphire";
		wacom->dev->id.version = MODEL_GRAPHIRE;
		wacom->res_x = 1016;
		wacom->res_y = 1016;
		wacom->max_x = 5103;
		wacom->max_y = 3711;
		wacom->extra_z_bits = 2;
		wacom->eraser_mask = 0x08;
		wacom->flags = F_HAS_STYLUS2 | F_HAS_SCROLLWHEEL;
		अवरोध;

	हाल MODEL_ARTPAD_II:
	हाल MODEL_DIGITIZER_II:
		wacom->dev->name = "Wacom Digitizer II";
		wacom->dev->id.version = MODEL_DIGITIZER_II;
		अगर (major_v == 1 && minor_v <= 2)
			wacom->extra_z_bits = 0; /* UNTESTED */
		अवरोध;

	शेष:
		dev_err(&wacom->dev->dev, "Unsupported Wacom model %s\n",
			wacom->data);
		wacom->result = -ENODEV;
		वापस;
	पूर्ण

	dev_info(&wacom->dev->dev, "%s tablet, version %u.%u\n",
		 wacom->dev->name, major_v, minor_v);
पूर्ण

अटल व्योम wacom_handle_configuration_response(काष्ठा wacom *wacom)
अणु
	पूर्णांक r, skip;

	dev_dbg(&wacom->dev->dev, "Configuration string: %s\n", wacom->data);
	r = माला_पूछो(wacom->data, "~R%x,%u,%u,%u,%u", &skip, &skip, &skip,
		   &wacom->res_x, &wacom->res_y);
	अगर (r != 5)
		dev_warn(&wacom->dev->dev, "could not get resolution\n");
पूर्ण

अटल व्योम wacom_handle_coordinates_response(काष्ठा wacom *wacom)
अणु
	पूर्णांक r;

	dev_dbg(&wacom->dev->dev, "Coordinates string: %s\n", wacom->data);
	r = माला_पूछो(wacom->data, "~C%u,%u", &wacom->max_x, &wacom->max_y);
	अगर (r != 2)
		dev_warn(&wacom->dev->dev, "could not get max coordinates\n");
पूर्ण

अटल व्योम wacom_handle_response(काष्ठा wacom *wacom)
अणु
	अगर (wacom->data[0] != '~' || wacom->data[1] != wacom->expect) अणु
		dev_err(&wacom->dev->dev,
			"Wacom got an unexpected response: %s\n", wacom->data);
		wacom->result = -EIO;
	पूर्ण अन्यथा अणु
		wacom->result = 0;

		चयन (wacom->data[1]) अणु
		हाल '#':
			wacom_handle_model_response(wacom);
			अवरोध;
		हाल 'R':
			wacom_handle_configuration_response(wacom);
			अवरोध;
		हाल 'C':
			wacom_handle_coordinates_response(wacom);
			अवरोध;
		पूर्ण
	पूर्ण

	complete(&wacom->cmd_करोne);
पूर्ण

अटल व्योम wacom_handle_packet(काष्ठा wacom *wacom)
अणु
	u8 in_proximity_p, stylus_p, button;
	अचिन्हित पूर्णांक tool;
	पूर्णांक x, y, z;

	in_proximity_p = wacom->data[0] & 0x40;
	stylus_p = wacom->data[0] & 0x20;
	button = (wacom->data[3] & 0x78) >> 3;
	x = (wacom->data[0] & 3) << 14 | wacom->data[1]<<7 | wacom->data[2];
	y = (wacom->data[3] & 3) << 14 | wacom->data[4]<<7 | wacom->data[5];

	अगर (in_proximity_p && stylus_p) अणु
		z = wacom->data[6] & 0x7f;
		अगर (wacom->extra_z_bits >= 1)
			z = z << 1 | (wacom->data[3] & 0x4) >> 2;
		अगर (wacom->extra_z_bits > 1)
			z = z << 1 | (wacom->data[0] & 0x4) >> 2;
		z = z ^ (0x40 << wacom->extra_z_bits);
	पूर्ण अन्यथा अणु
		z = -1;
	पूर्ण

	अगर (stylus_p)
		tool = (button & wacom->eraser_mask) ? ERASER : STYLUS;
	अन्यथा
		tool = CURSOR;

	अगर (tool != wacom->tool && wacom->tool != 0) अणु
		input_report_key(wacom->dev, tools[wacom->tool].input_id, 0);
		input_sync(wacom->dev);
	पूर्ण
	wacom->tool = tool;

	input_report_key(wacom->dev, tools[tool].input_id, in_proximity_p);
	input_report_असल(wacom->dev, ABS_MISC,
			 in_proximity_p ? tools[tool].device_id : 0);
	input_report_असल(wacom->dev, ABS_X, x);
	input_report_असल(wacom->dev, ABS_Y, y);
	input_report_असल(wacom->dev, ABS_PRESSURE, z);
	अगर (stylus_p) अणु
		input_report_key(wacom->dev, BTN_TOUCH, button & 1);
		input_report_key(wacom->dev, BTN_STYLUS, button & 2);
		input_report_key(wacom->dev, BTN_STYLUS2, button & 4);
	पूर्ण अन्यथा अणु
		input_report_key(wacom->dev, BTN_LEFT, button & 1);
		input_report_key(wacom->dev, BTN_RIGHT, button & 2);
		input_report_key(wacom->dev, BTN_MIDDLE, button & 4);
		/* handle relative wheel क्रम non-stylus device */
		z = (wacom->data[6] & 0x30) >> 4;
		अगर (wacom->data[6] & 0x40)
			z = -z;
		input_report_rel(wacom->dev, REL_WHEEL, z);
	पूर्ण
	input_sync(wacom->dev);
पूर्ण

अटल व्योम wacom_clear_data_buf(काष्ठा wacom *wacom)
अणु
	स_रखो(wacom->data, 0, DATA_SIZE);
	wacom->idx = 0;
पूर्ण

अटल irqवापस_t wacom_पूर्णांकerrupt(काष्ठा serio *serio, अचिन्हित अक्षर data,
				   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा wacom *wacom = serio_get_drvdata(serio);

	अगर (data & 0x80)
		wacom->idx = 0;

	/*
	 * We're either expecting a carriage वापस-terminated ASCII
	 * response string, or a seven-byte packet with the MSB set on
	 * the first byte.
	 *
	 * Note however that some tablets (the PenPartner, क्रम
	 * example) करोn't send a carriage वापस at the end of a
	 * command.  We handle these by रुकोing क्रम समयout.
	 */
	अगर (data == '\r' && !(wacom->data[0] & 0x80)) अणु
		wacom_handle_response(wacom);
		wacom_clear_data_buf(wacom);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Leave place क्रम 0 termination */
	अगर (wacom->idx > (DATA_SIZE - 2)) अणु
		dev_dbg(&wacom->dev->dev,
			"throwing away %d bytes of garbage\n", wacom->idx);
		wacom_clear_data_buf(wacom);
	पूर्ण
	wacom->data[wacom->idx++] = data;

	अगर (wacom->idx == PACKET_LENGTH && (wacom->data[0] & 0x80)) अणु
		wacom_handle_packet(wacom);
		wacom_clear_data_buf(wacom);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम wacom_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा wacom *wacom = serio_get_drvdata(serio);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_unरेजिस्टर_device(wacom->dev);
	kमुक्त(wacom);
पूर्ण

अटल पूर्णांक wacom_send(काष्ठा serio *serio, स्थिर u8 *command)
अणु
	पूर्णांक err = 0;

	क्रम (; !err && *command; command++)
		err = serio_ग_लिखो(serio, *command);

	वापस err;
पूर्ण

अटल पूर्णांक wacom_send_setup_string(काष्ठा wacom *wacom, काष्ठा serio *serio)
अणु
	स्थिर u8 *cmd;

	चयन (wacom->dev->id.version) अणु
	हाल MODEL_CINTIQ:	/* UNTESTED */
		cmd = COMMAND_ORIGIN_IN_UPPER_LEFT
			COMMAND_TRANSMIT_AT_MAX_RATE
			COMMAND_ENABLE_CONTINUOUS_MODE
			COMMAND_START_SENDING_PACKETS;
		अवरोध;

	हाल MODEL_PENPARTNER:
		cmd = COMMAND_ENABLE_PRESSURE_MODE
			COMMAND_START_SENDING_PACKETS;
		अवरोध;

	शेष:
		cmd = COMMAND_MULTI_MODE_INPUT
			COMMAND_ORIGIN_IN_UPPER_LEFT
			COMMAND_ENABLE_ALL_MACRO_BUTTONS
			COMMAND_DISABLE_GROUP_1_MACRO_BUTTONS
			COMMAND_TRANSMIT_AT_MAX_RATE
			COMMAND_DISABLE_INCREMENTAL_MODE
			COMMAND_ENABLE_CONTINUOUS_MODE
			COMMAND_Z_FILTER
			COMMAND_START_SENDING_PACKETS;
		अवरोध;
	पूर्ण

	वापस wacom_send(serio, cmd);
पूर्ण

अटल पूर्णांक wacom_send_and_रुको(काष्ठा wacom *wacom, काष्ठा serio *serio,
			       स्थिर u8 *cmd, स्थिर अक्षर *desc)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ u;

	wacom->expect = cmd[1];
	init_completion(&wacom->cmd_करोne);

	err = wacom_send(serio, cmd);
	अगर (err)
		वापस err;

	u = रुको_क्रम_completion_समयout(&wacom->cmd_करोne, HZ);
	अगर (u == 0) अणु
		/* Timeout, process what we've received. */
		wacom_handle_response(wacom);
	पूर्ण

	wacom->expect = 0;
	वापस wacom->result;
पूर्ण

अटल पूर्णांक wacom_setup(काष्ठा wacom *wacom, काष्ठा serio *serio)
अणु
	पूर्णांक err;

	/* Note that setting the link speed is the job of inputattach.
	 * We assume that reset negotiation has alपढ़ोy happened,
	 * here. */
	err = wacom_send_and_रुको(wacom, serio, REQUEST_MODEL_AND_ROM_VERSION,
				  "model and version");
	अगर (err)
		वापस err;

	अगर (!(wacom->res_x && wacom->res_y)) अणु
		err = wacom_send_and_रुको(wacom, serio,
					  REQUEST_CONFIGURATION_STRING,
					  "configuration string");
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!(wacom->max_x && wacom->max_y)) अणु
		err = wacom_send_and_रुको(wacom, serio,
					  REQUEST_MAX_COORDINATES,
					  "coordinates string");
		अगर (err)
			वापस err;
	पूर्ण

	वापस wacom_send_setup_string(wacom, serio);
पूर्ण

अटल पूर्णांक wacom_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा wacom *wacom;
	काष्ठा input_dev *input_dev;
	पूर्णांक err = -ENOMEM;

	wacom = kzalloc(माप(काष्ठा wacom), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!wacom || !input_dev)
		जाओ मुक्त_device;

	wacom->dev = input_dev;
	wacom->extra_z_bits = 1;
	wacom->eraser_mask = 0x04;
	wacom->tool = wacom->idx = 0;
	snम_लिखो(wacom->phys, माप(wacom->phys), "%s/input0", serio->phys);
	input_dev->phys = wacom->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr  = SERIO_WACOM_IV;
	input_dev->id.product = serio->id.extra;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] =
		BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS) | BIT_MASK(EV_REL);
	set_bit(ABS_MISC, input_dev->असलbit);
	set_bit(BTN_TOOL_PEN, input_dev->keybit);
	set_bit(BTN_TOOL_RUBBER, input_dev->keybit);
	set_bit(BTN_TOOL_MOUSE, input_dev->keybit);
	set_bit(BTN_TOUCH, input_dev->keybit);
	set_bit(BTN_STYLUS, input_dev->keybit);
	set_bit(BTN_LEFT, input_dev->keybit);
	set_bit(BTN_RIGHT, input_dev->keybit);
	set_bit(BTN_MIDDLE, input_dev->keybit);

	serio_set_drvdata(serio, wacom);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ मुक्त_device;

	err = wacom_setup(wacom, serio);
	अगर (err)
		जाओ बंद_serio;

	set_bit(INPUT_PROP_सूचीECT, input_dev->propbit);
	अगर (!(wacom->flags & F_COVERS_SCREEN))
		__set_bit(INPUT_PROP_POINTER, input_dev->propbit);

	अगर (wacom->flags & F_HAS_STYLUS2)
		__set_bit(BTN_STYLUS2, input_dev->keybit);

	अगर (wacom->flags & F_HAS_SCROLLWHEEL)
		__set_bit(REL_WHEEL, input_dev->relbit);

	input_असल_set_res(wacom->dev, ABS_X, wacom->res_x);
	input_असल_set_res(wacom->dev, ABS_Y, wacom->res_y);
	input_set_असल_params(wacom->dev, ABS_X, 0, wacom->max_x, 0, 0);
	input_set_असल_params(wacom->dev, ABS_Y, 0, wacom->max_y, 0, 0);
	input_set_असल_params(wacom->dev, ABS_PRESSURE, -1,
			     (1 << (7 + wacom->extra_z_bits)) - 1, 0, 0);

	err = input_रेजिस्टर_device(wacom->dev);
	अगर (err)
		जाओ बंद_serio;

	वापस 0;

बंद_serio:
	serio_बंद(serio);
मुक्त_device:
	serio_set_drvdata(serio, शून्य);
	input_मुक्त_device(input_dev);
	kमुक्त(wacom);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा serio_device_id wacom_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_WACOM_IV,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, wacom_serio_ids);

अटल काष्ठा serio_driver wacom_drv = अणु
	.driver		= अणु
		.name	= "wacom_serial4",
	पूर्ण,
	.description	= "Wacom protocol 4 serial tablet driver",
	.id_table	= wacom_serio_ids,
	.पूर्णांकerrupt	= wacom_पूर्णांकerrupt,
	.connect	= wacom_connect,
	.disconnect	= wacom_disconnect,
पूर्ण;

module_serio_driver(wacom_drv);
