<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 *
 *  Based on the work of:
 *	Andree Borrmann		Mats Sjथघvall
 */

/*
 * Atari, Amstrad, Commoकरोre, Amiga, Sega, etc. joystick driver क्रम Linux
 */

/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/parport.h>
#समावेश <linux/input.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Atari, Amstrad, Commodore, Amiga, Sega, etc. joystick driver");
MODULE_LICENSE("GPL");

काष्ठा db9_config अणु
	पूर्णांक args[2];
	अचिन्हित पूर्णांक nargs;
पूर्ण;

#घोषणा DB9_MAX_PORTS		3
अटल काष्ठा db9_config db9_cfg[DB9_MAX_PORTS];

module_param_array_named(dev, db9_cfg[0].args, पूर्णांक, &db9_cfg[0].nargs, 0);
MODULE_PARM_DESC(dev, "Describes first attached device (<parport#>,<type>)");
module_param_array_named(dev2, db9_cfg[1].args, पूर्णांक, &db9_cfg[1].nargs, 0);
MODULE_PARM_DESC(dev2, "Describes second attached device (<parport#>,<type>)");
module_param_array_named(dev3, db9_cfg[2].args, पूर्णांक, &db9_cfg[2].nargs, 0);
MODULE_PARM_DESC(dev3, "Describes third attached device (<parport#>,<type>)");

#घोषणा DB9_ARG_PARPORT		0
#घोषणा DB9_ARG_MODE		1

#घोषणा DB9_MULTI_STICK		0x01
#घोषणा DB9_MULTI2_STICK	0x02
#घोषणा DB9_GENESIS_PAD		0x03
#घोषणा DB9_GENESIS5_PAD	0x05
#घोषणा DB9_GENESIS6_PAD	0x06
#घोषणा DB9_SATURN_PAD		0x07
#घोषणा DB9_MULTI_0802		0x08
#घोषणा DB9_MULTI_0802_2	0x09
#घोषणा DB9_CD32_PAD		0x0A
#घोषणा DB9_SATURN_DPP		0x0B
#घोषणा DB9_SATURN_DPP_2	0x0C
#घोषणा DB9_MAX_PAD		0x0D

#घोषणा DB9_UP			0x01
#घोषणा DB9_DOWN		0x02
#घोषणा DB9_LEFT		0x04
#घोषणा DB9_RIGHT		0x08
#घोषणा DB9_FIRE1		0x10
#घोषणा DB9_FIRE2		0x20
#घोषणा DB9_FIRE3		0x40
#घोषणा DB9_FIRE4		0x80

#घोषणा DB9_NORMAL		0x0a
#घोषणा DB9_NOSELECT		0x08

#घोषणा DB9_GENESIS6_DELAY	14
#घोषणा DB9_REFRESH_TIME	HZ/100

#घोषणा DB9_MAX_DEVICES		2

काष्ठा db9_mode_data अणु
	स्थिर अक्षर *name;
	स्थिर लघु *buttons;
	पूर्णांक n_buttons;
	पूर्णांक n_pads;
	पूर्णांक n_axis;
	पूर्णांक bidirectional;
	पूर्णांक reverse;
पूर्ण;

काष्ठा db9 अणु
	काष्ठा input_dev *dev[DB9_MAX_DEVICES];
	काष्ठा समयr_list समयr;
	काष्ठा pardevice *pd;
	पूर्णांक mode;
	पूर्णांक used;
	पूर्णांक parportno;
	काष्ठा mutex mutex;
	अक्षर phys[DB9_MAX_DEVICES][32];
पूर्ण;

अटल काष्ठा db9 *db9_base[3];

अटल स्थिर लघु db9_multi_btn[] = अणु BTN_TRIGGER, BTN_THUMB पूर्ण;
अटल स्थिर लघु db9_genesis_btn[] = अणु BTN_START, BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_MODE पूर्ण;
अटल स्थिर लघु db9_cd32_btn[] = अणु BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_TL, BTN_TR, BTN_START पूर्ण;
अटल स्थिर लघु db9_असल[] = अणु ABS_X, ABS_Y, ABS_RX, ABS_RY, ABS_RZ, ABS_Z, ABS_HAT0X, ABS_HAT0Y, ABS_HAT1X, ABS_HAT1Y पूर्ण;

अटल स्थिर काष्ठा db9_mode_data db9_modes[] = अणु
	अणु शून्य,					 शून्य,		  0,  0,  0,  0,  0 पूर्ण,
	अणु "Multisystem joystick",		 db9_multi_btn,	  1,  1,  2,  1,  1 पूर्ण,
	अणु "Multisystem joystick (2 fire)",	 db9_multi_btn,	  2,  1,  2,  1,  1 पूर्ण,
	अणु "Genesis pad",			 db9_genesis_btn, 4,  1,  2,  1,  1 पूर्ण,
	अणु शून्य,					 शून्य,		  0,  0,  0,  0,  0 पूर्ण,
	अणु "Genesis 5 pad",			 db9_genesis_btn, 6,  1,  2,  1,  1 पूर्ण,
	अणु "Genesis 6 pad",			 db9_genesis_btn, 8,  1,  2,  1,  1 पूर्ण,
	अणु "Saturn pad",				 db9_cd32_btn,	  9,  6,  7,  0,  1 पूर्ण,
	अणु "Multisystem (0.8.0.2) joystick",	 db9_multi_btn,	  1,  1,  2,  1,  1 पूर्ण,
	अणु "Multisystem (0.8.0.2-dual) joystick", db9_multi_btn,	  1,  2,  2,  1,  1 पूर्ण,
	अणु "Amiga CD-32 pad",			 db9_cd32_btn,	  7,  1,  2,  1,  1 पूर्ण,
	अणु "Saturn dpp",				 db9_cd32_btn,	  9,  6,  7,  0,  0 पूर्ण,
	अणु "Saturn dpp dual",			 db9_cd32_btn,	  9,  12, 7,  0,  0 पूर्ण,
पूर्ण;

/*
 * Saturn controllers
 */
#घोषणा DB9_SATURN_DELAY 300
अटल स्थिर पूर्णांक db9_saturn_byte[] = अणु 1, 1, 1, 2, 2, 2, 2, 2, 1 पूर्ण;
अटल स्थिर अचिन्हित अक्षर db9_saturn_mask[] = अणु 0x04, 0x01, 0x02, 0x40, 0x20, 0x10, 0x08, 0x80, 0x08 पूर्ण;

/*
 * db9_saturn_ग_लिखो_sub() ग_लिखोs 2 bit data.
 */
अटल व्योम db9_saturn_ग_लिखो_sub(काष्ठा parport *port, पूर्णांक type, अचिन्हित अक्षर data, पूर्णांक घातered, पूर्णांक pwr_sub)
अणु
	अचिन्हित अक्षर c;

	चयन (type) अणु
	हाल 1: /* DPP1 */
		c = 0x80 | 0x30 | (घातered ? 0x08 : 0) | (pwr_sub ? 0x04 : 0) | data;
		parport_ग_लिखो_data(port, c);
		अवरोध;
	हाल 2: /* DPP2 */
		c = 0x40 | data << 4 | (घातered ? 0x08 : 0) | (pwr_sub ? 0x04 : 0) | 0x03;
		parport_ग_लिखो_data(port, c);
		अवरोध;
	हाल 0:	/* DB9 */
		c = ((((data & 2) ? 2 : 0) | ((data & 1) ? 4 : 0)) ^ 0x02) | !घातered;
		parport_ग_लिखो_control(port, c);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * gc_saturn_पढ़ो_sub() पढ़ोs 4 bit data.
 */
अटल अचिन्हित अक्षर db9_saturn_पढ़ो_sub(काष्ठा parport *port, पूर्णांक type)
अणु
	अचिन्हित अक्षर data;

	अगर (type) अणु
		/* DPP */
		data = parport_पढ़ो_status(port) ^ 0x80;
		वापस (data & 0x80 ? 1 : 0) | (data & 0x40 ? 2 : 0)
		     | (data & 0x20 ? 4 : 0) | (data & 0x10 ? 8 : 0);
	पूर्ण अन्यथा अणु
		/* DB9 */
		data = parport_पढ़ो_data(port) & 0x0f;
		वापस (data & 0x8 ? 1 : 0) | (data & 0x4 ? 2 : 0)
		     | (data & 0x2 ? 4 : 0) | (data & 0x1 ? 8 : 0);
	पूर्ण
पूर्ण

/*
 * db9_saturn_पढ़ो_analog() sends घड़ी and पढ़ोs 8 bit data.
 */
अटल अचिन्हित अक्षर db9_saturn_पढ़ो_analog(काष्ठा parport *port, पूर्णांक type, पूर्णांक घातered)
अणु
	अचिन्हित अक्षर data;

	db9_saturn_ग_लिखो_sub(port, type, 0, घातered, 0);
	udelay(DB9_SATURN_DELAY);
	data = db9_saturn_पढ़ो_sub(port, type) << 4;
	db9_saturn_ग_लिखो_sub(port, type, 2, घातered, 0);
	udelay(DB9_SATURN_DELAY);
	data |= db9_saturn_पढ़ो_sub(port, type);
	वापस data;
पूर्ण

/*
 * db9_saturn_पढ़ो_packet() पढ़ोs whole saturn packet at connector
 * and वापसs device identअगरier code.
 */
अटल अचिन्हित अक्षर db9_saturn_पढ़ो_packet(काष्ठा parport *port, अचिन्हित अक्षर *data, पूर्णांक type, पूर्णांक घातered)
अणु
	पूर्णांक i, j;
	अचिन्हित अक्षर पंचांगp;

	db9_saturn_ग_लिखो_sub(port, type, 3, घातered, 0);
	data[0] = db9_saturn_पढ़ो_sub(port, type);
	चयन (data[0] & 0x0f) अणु
	हाल 0xf:
		/* 1111  no pad */
		वापस data[0] = 0xff;
	हाल 0x4: हाल 0x4 | 0x8:
		/* ?100 : digital controller */
		db9_saturn_ग_लिखो_sub(port, type, 0, घातered, 1);
		data[2] = db9_saturn_पढ़ो_sub(port, type) << 4;
		db9_saturn_ग_लिखो_sub(port, type, 2, घातered, 1);
		data[1] = db9_saturn_पढ़ो_sub(port, type) << 4;
		db9_saturn_ग_लिखो_sub(port, type, 1, घातered, 1);
		data[1] |= db9_saturn_पढ़ो_sub(port, type);
		db9_saturn_ग_लिखो_sub(port, type, 3, घातered, 1);
		/* data[2] |= db9_saturn_पढ़ो_sub(port, type); */
		data[2] |= data[0];
		वापस data[0] = 0x02;
	हाल 0x1:
		/* 0001 : analog controller or multitap */
		db9_saturn_ग_लिखो_sub(port, type, 2, घातered, 0);
		udelay(DB9_SATURN_DELAY);
		data[0] = db9_saturn_पढ़ो_analog(port, type, घातered);
		अगर (data[0] != 0x41) अणु
			/* पढ़ो analog controller */
			क्रम (i = 0; i < (data[0] & 0x0f); i++)
				data[i + 1] = db9_saturn_पढ़ो_analog(port, type, घातered);
			db9_saturn_ग_लिखो_sub(port, type, 3, घातered, 0);
			वापस data[0];
		पूर्ण अन्यथा अणु
			/* पढ़ो multitap */
			अगर (db9_saturn_पढ़ो_analog(port, type, घातered) != 0x60)
				वापस data[0] = 0xff;
			क्रम (i = 0; i < 60; i += 10) अणु
				data[i] = db9_saturn_पढ़ो_analog(port, type, घातered);
				अगर (data[i] != 0xff)
					/* पढ़ो each pad */
					क्रम (j = 0; j < (data[i] & 0x0f); j++)
						data[i + j + 1] = db9_saturn_पढ़ो_analog(port, type, घातered);
			पूर्ण
			db9_saturn_ग_लिखो_sub(port, type, 3, घातered, 0);
			वापस 0x41;
		पूर्ण
	हाल 0x0:
		/* 0000 : mouse */
		db9_saturn_ग_लिखो_sub(port, type, 2, घातered, 0);
		udelay(DB9_SATURN_DELAY);
		पंचांगp = db9_saturn_पढ़ो_analog(port, type, घातered);
		अगर (पंचांगp == 0xff) अणु
			क्रम (i = 0; i < 3; i++)
				data[i + 1] = db9_saturn_पढ़ो_analog(port, type, घातered);
			db9_saturn_ग_लिखो_sub(port, type, 3, घातered, 0);
			वापस data[0] = 0xe3;
		पूर्ण
		fallthrough;
	शेष:
		वापस data[0];
	पूर्ण
पूर्ण

/*
 * db9_saturn_report() analyzes packet and reports.
 */
अटल पूर्णांक db9_saturn_report(अचिन्हित अक्षर id, अचिन्हित अक्षर data[60], काष्ठा input_dev *devs[], पूर्णांक n, पूर्णांक max_pads)
अणु
	काष्ठा input_dev *dev;
	पूर्णांक पंचांगp, i, j;

	पंचांगp = (id == 0x41) ? 60 : 10;
	क्रम (j = 0; j < पंचांगp && n < max_pads; j += 10, n++) अणु
		dev = devs[n];
		चयन (data[j]) अणु
		हाल 0x16: /* multi controller (analog 4 axis) */
			input_report_असल(dev, db9_असल[5], data[j + 6]);
			fallthrough;
		हाल 0x15: /* mission stick (analog 3 axis) */
			input_report_असल(dev, db9_असल[3], data[j + 4]);
			input_report_असल(dev, db9_असल[4], data[j + 5]);
			fallthrough;
		हाल 0x13: /* racing controller (analog 1 axis) */
			input_report_असल(dev, db9_असल[2], data[j + 3]);
			fallthrough;
		हाल 0x34: /* saturn keyboard (udlr ZXC ASD QE Esc) */
		हाल 0x02: /* digital pad (digital 2 axis + buttons) */
			input_report_असल(dev, db9_असल[0], !(data[j + 1] & 128) - !(data[j + 1] & 64));
			input_report_असल(dev, db9_असल[1], !(data[j + 1] & 32) - !(data[j + 1] & 16));
			क्रम (i = 0; i < 9; i++)
				input_report_key(dev, db9_cd32_btn[i], ~data[j + db9_saturn_byte[i]] & db9_saturn_mask[i]);
			अवरोध;
		हाल 0x19: /* mission stick x2 (analog 6 axis + buttons) */
			input_report_असल(dev, db9_असल[0], !(data[j + 1] & 128) - !(data[j + 1] & 64));
			input_report_असल(dev, db9_असल[1], !(data[j + 1] & 32) - !(data[j + 1] & 16));
			क्रम (i = 0; i < 9; i++)
				input_report_key(dev, db9_cd32_btn[i], ~data[j + db9_saturn_byte[i]] & db9_saturn_mask[i]);
			input_report_असल(dev, db9_असल[2], data[j + 3]);
			input_report_असल(dev, db9_असल[3], data[j + 4]);
			input_report_असल(dev, db9_असल[4], data[j + 5]);
			/*
			input_report_असल(dev, db9_असल[8], (data[j + 6] & 128 ? 0 : 1) - (data[j + 6] & 64 ? 0 : 1));
			input_report_असल(dev, db9_असल[9], (data[j + 6] & 32 ? 0 : 1) - (data[j + 6] & 16 ? 0 : 1));
			*/
			input_report_असल(dev, db9_असल[6], data[j + 7]);
			input_report_असल(dev, db9_असल[7], data[j + 8]);
			input_report_असल(dev, db9_असल[5], data[j + 9]);
			अवरोध;
		हाल 0xd3: /* sankyo ff (analog 1 axis + stop btn) */
			input_report_key(dev, BTN_A, data[j + 3] & 0x80);
			input_report_असल(dev, db9_असल[2], data[j + 3] & 0x7f);
			अवरोध;
		हाल 0xe3: /* shuttle mouse (analog 2 axis + buttons. चिन्हित value) */
			input_report_key(dev, BTN_START, data[j + 1] & 0x08);
			input_report_key(dev, BTN_A, data[j + 1] & 0x04);
			input_report_key(dev, BTN_C, data[j + 1] & 0x02);
			input_report_key(dev, BTN_B, data[j + 1] & 0x01);
			input_report_असल(dev, db9_असल[2], data[j + 2] ^ 0x80);
			input_report_असल(dev, db9_असल[3], (0xff-(data[j + 3] ^ 0x80))+1); /* */
			अवरोध;
		हाल 0xff:
		शेष: /* no pad */
			input_report_असल(dev, db9_असल[0], 0);
			input_report_असल(dev, db9_असल[1], 0);
			क्रम (i = 0; i < 9; i++)
				input_report_key(dev, db9_cd32_btn[i], 0);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस n;
पूर्ण

अटल पूर्णांक db9_saturn(पूर्णांक mode, काष्ठा parport *port, काष्ठा input_dev *devs[])
अणु
	अचिन्हित अक्षर id, data[60];
	पूर्णांक type, n, max_pads;
	पूर्णांक पंचांगp, i;

	चयन (mode) अणु
	हाल DB9_SATURN_PAD:
		type = 0;
		n = 1;
		अवरोध;
	हाल DB9_SATURN_DPP:
		type = 1;
		n = 1;
		अवरोध;
	हाल DB9_SATURN_DPP_2:
		type = 1;
		n = 2;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण
	max_pads = min(db9_modes[mode].n_pads, DB9_MAX_DEVICES);
	क्रम (पंचांगp = 0, i = 0; i < n; i++) अणु
		id = db9_saturn_पढ़ो_packet(port, data, type + i, 1);
		पंचांगp = db9_saturn_report(id, data, devs, पंचांगp, max_pads);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम db9_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा db9 *db9 = from_समयr(db9, t, समयr);
	काष्ठा parport *port = db9->pd->port;
	काष्ठा input_dev *dev = db9->dev[0];
	काष्ठा input_dev *dev2 = db9->dev[1];
	पूर्णांक data, i;

	चयन (db9->mode) अणु
		हाल DB9_MULTI_0802_2:

			data = parport_पढ़ो_data(port) >> 3;

			input_report_असल(dev2, ABS_X, (data & DB9_RIGHT ? 0 : 1) - (data & DB9_LEFT ? 0 : 1));
			input_report_असल(dev2, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));
			input_report_key(dev2, BTN_TRIGGER, ~data & DB9_FIRE1);
			fallthrough;

		हाल DB9_MULTI_0802:

			data = parport_पढ़ो_status(port) >> 3;

			input_report_असल(dev, ABS_X, (data & DB9_RIGHT ? 0 : 1) - (data & DB9_LEFT ? 0 : 1));
			input_report_असल(dev, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));
			input_report_key(dev, BTN_TRIGGER, data & DB9_FIRE1);
			अवरोध;

		हाल DB9_MULTI_STICK:

			data = parport_पढ़ो_data(port);

			input_report_असल(dev, ABS_X, (data & DB9_RIGHT ? 0 : 1) - (data & DB9_LEFT ? 0 : 1));
			input_report_असल(dev, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));
			input_report_key(dev, BTN_TRIGGER, ~data & DB9_FIRE1);
			अवरोध;

		हाल DB9_MULTI2_STICK:

			data = parport_पढ़ो_data(port);

			input_report_असल(dev, ABS_X, (data & DB9_RIGHT ? 0 : 1) - (data & DB9_LEFT ? 0 : 1));
			input_report_असल(dev, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));
			input_report_key(dev, BTN_TRIGGER, ~data & DB9_FIRE1);
			input_report_key(dev, BTN_THUMB,   ~data & DB9_FIRE2);
			अवरोध;

		हाल DB9_GENESIS_PAD:

			parport_ग_लिखो_control(port, DB9_NOSELECT);
			data = parport_पढ़ो_data(port);

			input_report_असल(dev, ABS_X, (data & DB9_RIGHT ? 0 : 1) - (data & DB9_LEFT ? 0 : 1));
			input_report_असल(dev, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));
			input_report_key(dev, BTN_B, ~data & DB9_FIRE1);
			input_report_key(dev, BTN_C, ~data & DB9_FIRE2);

			parport_ग_लिखो_control(port, DB9_NORMAL);
			data = parport_पढ़ो_data(port);

			input_report_key(dev, BTN_A,     ~data & DB9_FIRE1);
			input_report_key(dev, BTN_START, ~data & DB9_FIRE2);
			अवरोध;

		हाल DB9_GENESIS5_PAD:

			parport_ग_लिखो_control(port, DB9_NOSELECT);
			data = parport_पढ़ो_data(port);

			input_report_असल(dev, ABS_X, (data & DB9_RIGHT ? 0 : 1) - (data & DB9_LEFT ? 0 : 1));
			input_report_असल(dev, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));
			input_report_key(dev, BTN_B, ~data & DB9_FIRE1);
			input_report_key(dev, BTN_C, ~data & DB9_FIRE2);

			parport_ग_लिखो_control(port, DB9_NORMAL);
			data = parport_पढ़ो_data(port);

			input_report_key(dev, BTN_A,     ~data & DB9_FIRE1);
			input_report_key(dev, BTN_X,     ~data & DB9_FIRE2);
			input_report_key(dev, BTN_Y,     ~data & DB9_LEFT);
			input_report_key(dev, BTN_START, ~data & DB9_RIGHT);
			अवरोध;

		हाल DB9_GENESIS6_PAD:

			parport_ग_लिखो_control(port, DB9_NOSELECT); /* 1 */
			udelay(DB9_GENESIS6_DELAY);
			data = parport_पढ़ो_data(port);

			input_report_असल(dev, ABS_X, (data & DB9_RIGHT ? 0 : 1) - (data & DB9_LEFT ? 0 : 1));
			input_report_असल(dev, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));
			input_report_key(dev, BTN_B, ~data & DB9_FIRE1);
			input_report_key(dev, BTN_C, ~data & DB9_FIRE2);

			parport_ग_लिखो_control(port, DB9_NORMAL);
			udelay(DB9_GENESIS6_DELAY);
			data = parport_पढ़ो_data(port);

			input_report_key(dev, BTN_A, ~data & DB9_FIRE1);
			input_report_key(dev, BTN_START, ~data & DB9_FIRE2);

			parport_ग_लिखो_control(port, DB9_NOSELECT); /* 2 */
			udelay(DB9_GENESIS6_DELAY);
			parport_ग_लिखो_control(port, DB9_NORMAL);
			udelay(DB9_GENESIS6_DELAY);
			parport_ग_लिखो_control(port, DB9_NOSELECT); /* 3 */
			udelay(DB9_GENESIS6_DELAY);
			data=parport_पढ़ो_data(port);

			input_report_key(dev, BTN_X,    ~data & DB9_LEFT);
			input_report_key(dev, BTN_Y,    ~data & DB9_DOWN);
			input_report_key(dev, BTN_Z,    ~data & DB9_UP);
			input_report_key(dev, BTN_MODE, ~data & DB9_RIGHT);

			parport_ग_लिखो_control(port, DB9_NORMAL);
			udelay(DB9_GENESIS6_DELAY);
			parport_ग_लिखो_control(port, DB9_NOSELECT); /* 4 */
			udelay(DB9_GENESIS6_DELAY);
			parport_ग_लिखो_control(port, DB9_NORMAL);
			अवरोध;

		हाल DB9_SATURN_PAD:
		हाल DB9_SATURN_DPP:
		हाल DB9_SATURN_DPP_2:

			db9_saturn(db9->mode, port, db9->dev);
			अवरोध;

		हाल DB9_CD32_PAD:

			data = parport_पढ़ो_data(port);

			input_report_असल(dev, ABS_X, (data & DB9_RIGHT ? 0 : 1) - (data & DB9_LEFT ? 0 : 1));
			input_report_असल(dev, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));

			parport_ग_लिखो_control(port, 0x0a);

			क्रम (i = 0; i < 7; i++) अणु
				data = parport_पढ़ो_data(port);
				parport_ग_लिखो_control(port, 0x02);
				parport_ग_लिखो_control(port, 0x0a);
				input_report_key(dev, db9_cd32_btn[i], ~data & DB9_FIRE2);
			पूर्ण

			parport_ग_लिखो_control(port, 0x00);
			अवरोध;
		पूर्ण

	input_sync(dev);

	mod_समयr(&db9->समयr, jअगरfies + DB9_REFRESH_TIME);
पूर्ण

अटल पूर्णांक db9_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा db9 *db9 = input_get_drvdata(dev);
	काष्ठा parport *port = db9->pd->port;
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&db9->mutex);
	अगर (err)
		वापस err;

	अगर (!db9->used++) अणु
		parport_claim(db9->pd);
		parport_ग_लिखो_data(port, 0xff);
		अगर (db9_modes[db9->mode].reverse) अणु
			parport_data_reverse(port);
			parport_ग_लिखो_control(port, DB9_NORMAL);
		पूर्ण
		mod_समयr(&db9->समयr, jअगरfies + DB9_REFRESH_TIME);
	पूर्ण

	mutex_unlock(&db9->mutex);
	वापस 0;
पूर्ण

अटल व्योम db9_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा db9 *db9 = input_get_drvdata(dev);
	काष्ठा parport *port = db9->pd->port;

	mutex_lock(&db9->mutex);
	अगर (!--db9->used) अणु
		del_समयr_sync(&db9->समयr);
		parport_ग_लिखो_control(port, 0x00);
		parport_data_क्रमward(port);
		parport_release(db9->pd);
	पूर्ण
	mutex_unlock(&db9->mutex);
पूर्ण

अटल व्योम db9_attach(काष्ठा parport *pp)
अणु
	काष्ठा db9 *db9;
	स्थिर काष्ठा db9_mode_data *db9_mode;
	काष्ठा pardevice *pd;
	काष्ठा input_dev *input_dev;
	पूर्णांक i, j, port_idx;
	पूर्णांक mode;
	काष्ठा pardev_cb db9_parport_cb;

	क्रम (port_idx = 0; port_idx < DB9_MAX_PORTS; port_idx++) अणु
		अगर (db9_cfg[port_idx].nargs == 0 ||
		    db9_cfg[port_idx].args[DB9_ARG_PARPORT] < 0)
			जारी;

		अगर (db9_cfg[port_idx].args[DB9_ARG_PARPORT] == pp->number)
			अवरोध;
	पूर्ण

	अगर (port_idx == DB9_MAX_PORTS) अणु
		pr_debug("Not using parport%d.\n", pp->number);
		वापस;
	पूर्ण

	mode = db9_cfg[port_idx].args[DB9_ARG_MODE];

	अगर (mode < 1 || mode >= DB9_MAX_PAD || !db9_modes[mode].n_buttons) अणु
		prपूर्णांकk(KERN_ERR "db9.c: Bad device type %d\n", mode);
		वापस;
	पूर्ण

	db9_mode = &db9_modes[mode];

	अगर (db9_mode->bidirectional && !(pp->modes & PARPORT_MODE_TRISTATE)) अणु
		prपूर्णांकk(KERN_ERR "db9.c: specified parport is not bidirectional\n");
		वापस;
	पूर्ण

	स_रखो(&db9_parport_cb, 0, माप(db9_parport_cb));
	db9_parport_cb.flags = PARPORT_FLAG_EXCL;

	pd = parport_रेजिस्टर_dev_model(pp, "db9", &db9_parport_cb, port_idx);
	अगर (!pd) अणु
		prपूर्णांकk(KERN_ERR "db9.c: parport busy already - lp.o loaded?\n");
		वापस;
	पूर्ण

	db9 = kzalloc(माप(काष्ठा db9), GFP_KERNEL);
	अगर (!db9)
		जाओ err_unreg_pardev;

	mutex_init(&db9->mutex);
	db9->pd = pd;
	db9->mode = mode;
	db9->parportno = pp->number;
	समयr_setup(&db9->समयr, db9_समयr, 0);

	क्रम (i = 0; i < (min(db9_mode->n_pads, DB9_MAX_DEVICES)); i++) अणु

		db9->dev[i] = input_dev = input_allocate_device();
		अगर (!input_dev) अणु
			prपूर्णांकk(KERN_ERR "db9.c: Not enough memory for input device\n");
			जाओ err_unreg_devs;
		पूर्ण

		snम_लिखो(db9->phys[i], माप(db9->phys[i]),
			 "%s/input%d", db9->pd->port->name, i);

		input_dev->name = db9_mode->name;
		input_dev->phys = db9->phys[i];
		input_dev->id.bustype = BUS_PARPORT;
		input_dev->id.venकरोr = 0x0002;
		input_dev->id.product = mode;
		input_dev->id.version = 0x0100;

		input_set_drvdata(input_dev, db9);

		input_dev->खोलो = db9_खोलो;
		input_dev->बंद = db9_बंद;

		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		क्रम (j = 0; j < db9_mode->n_buttons; j++)
			set_bit(db9_mode->buttons[j], input_dev->keybit);
		क्रम (j = 0; j < db9_mode->n_axis; j++) अणु
			अगर (j < 2)
				input_set_असल_params(input_dev, db9_असल[j], -1, 1, 0, 0);
			अन्यथा
				input_set_असल_params(input_dev, db9_असल[j], 1, 255, 0, 0);
		पूर्ण

		अगर (input_रेजिस्टर_device(input_dev))
			जाओ err_मुक्त_dev;
	पूर्ण

	db9_base[port_idx] = db9;
	वापस;

 err_मुक्त_dev:
	input_मुक्त_device(db9->dev[i]);
 err_unreg_devs:
	जबतक (--i >= 0)
		input_unरेजिस्टर_device(db9->dev[i]);
	kमुक्त(db9);
 err_unreg_pardev:
	parport_unरेजिस्टर_device(pd);
पूर्ण

अटल व्योम db9_detach(काष्ठा parport *port)
अणु
	पूर्णांक i;
	काष्ठा db9 *db9;

	क्रम (i = 0; i < DB9_MAX_PORTS; i++) अणु
		अगर (db9_base[i] && db9_base[i]->parportno == port->number)
			अवरोध;
	पूर्ण

	अगर (i == DB9_MAX_PORTS)
		वापस;

	db9 = db9_base[i];
	db9_base[i] = शून्य;

	क्रम (i = 0; i < min(db9_modes[db9->mode].n_pads, DB9_MAX_DEVICES); i++)
		input_unरेजिस्टर_device(db9->dev[i]);
	parport_unरेजिस्टर_device(db9->pd);
	kमुक्त(db9);
पूर्ण

अटल काष्ठा parport_driver db9_parport_driver = अणु
	.name = "db9",
	.match_port = db9_attach,
	.detach = db9_detach,
	.devmodel = true,
पूर्ण;

अटल पूर्णांक __init db9_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक have_dev = 0;

	क्रम (i = 0; i < DB9_MAX_PORTS; i++) अणु
		अगर (db9_cfg[i].nargs == 0 || db9_cfg[i].args[DB9_ARG_PARPORT] < 0)
			जारी;

		अगर (db9_cfg[i].nargs < 2) अणु
			prपूर्णांकk(KERN_ERR "db9.c: Device type must be specified.\n");
			वापस -EINVAL;
		पूर्ण

		have_dev = 1;
	पूर्ण

	अगर (!have_dev)
		वापस -ENODEV;

	वापस parport_रेजिस्टर_driver(&db9_parport_driver);
पूर्ण

अटल व्योम __निकास db9_निकास(व्योम)
अणु
	parport_unरेजिस्टर_driver(&db9_parport_driver);
पूर्ण

module_init(db9_init);
module_निकास(db9_निकास);
