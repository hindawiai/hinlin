<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Logitech PS/2++ mouse driver
 *
 * Copyright (c) 1999-2003 Vojtech Pavlik <vojtech@suse.cz>
 * Copyright (c) 2003 Eric Wong <eric@yhbt.net>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>
#समावेश <linux/libps2.h>
#समावेश <linux/types.h>
#समावेश "psmouse.h"
#समावेश "logips2pp.h"

/* Logitech mouse types */
#घोषणा PS2PP_KIND_WHEEL	1
#घोषणा PS2PP_KIND_MX		2
#घोषणा PS2PP_KIND_TP3		3
#घोषणा PS2PP_KIND_TRACKMAN	4

/* Logitech mouse features */
#घोषणा PS2PP_WHEEL		BIT(0)
#घोषणा PS2PP_HWHEEL		BIT(1)
#घोषणा PS2PP_SIDE_BTN		BIT(2)
#घोषणा PS2PP_EXTRA_BTN		BIT(3)
#घोषणा PS2PP_TASK_BTN		BIT(4)
#घोषणा PS2PP_NAV_BTN		BIT(5)

काष्ठा ps2pp_info अणु
	u8 model;
	u8 kind;
	u16 features;
पूर्ण;

/*
 * Process a PS2++ or PS2T++ packet.
 */

अटल psmouse_ret_t ps2pp_process_byte(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	u8 *packet = psmouse->packet;

	अगर (psmouse->pktcnt < 3)
		वापस PSMOUSE_GOOD_DATA;

/*
 * Full packet accumulated, process it
 */

	अगर ((packet[0] & 0x48) == 0x48 && (packet[1] & 0x02) == 0x02) अणु

		/* Logitech extended packet */
		चयन ((packet[1] >> 4) | (packet[0] & 0x30)) अणु

		हाल 0x0d: /* Mouse extra info */

			input_report_rel(dev,
				packet[2] & 0x80 ? REL_HWHEEL : REL_WHEEL,
				-sign_extend32(packet[2], 3));
			input_report_key(dev, BTN_SIDE,  packet[2] & BIT(4));
			input_report_key(dev, BTN_EXTRA, packet[2] & BIT(5));

			अवरोध;

		हाल 0x0e: /* buttons 4, 5, 6, 7, 8, 9, 10 info */

			input_report_key(dev, BTN_SIDE,    packet[2] & BIT(0));
			input_report_key(dev, BTN_EXTRA,   packet[2] & BIT(1));
			input_report_key(dev, BTN_TASK,    packet[2] & BIT(2));
			input_report_key(dev, BTN_BACK,    packet[2] & BIT(3));
			input_report_key(dev, BTN_FORWARD, packet[2] & BIT(4));

			अवरोध;

		हाल 0x0f: /* TouchPad extra info */

			input_report_rel(dev,
				packet[2] & 0x08 ? REL_HWHEEL : REL_WHEEL,
				-sign_extend32(packet[2] >> 4, 3));
			packet[0] = packet[2] | BIT(3);
			अवरोध;

		शेष:
			psmouse_dbg(psmouse,
				    "Received PS2++ packet #%x, but don't know how to handle.\n",
				    (packet[1] >> 4) | (packet[0] & 0x30));
			अवरोध;
		पूर्ण

		psmouse_report_standard_buttons(dev, packet[0]);

	पूर्ण अन्यथा अणु
		/* Standard PS/2 motion data */
		psmouse_report_standard_packet(dev, packet);
	पूर्ण

	input_sync(dev);

	वापस PSMOUSE_FULL_PACKET;

पूर्ण

/*
 * ps2pp_cmd() sends a PS2++ command, sliced पूर्णांकo two bit
 * pieces through the SETRES command. This is needed to send extended
 * commands to mice on notebooks that try to understand the PS/2 protocol
 * Ugly.
 */

अटल पूर्णांक ps2pp_cmd(काष्ठा psmouse *psmouse, u8 *param, u8 command)
अणु
	पूर्णांक error;

	error = ps2_sliced_command(&psmouse->ps2dev, command);
	अगर (error)
		वापस error;

	error = ps2_command(&psmouse->ps2dev, param, PSMOUSE_CMD_POLL | 0x0300);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

/*
 * SmartScroll / CruiseControl क्रम some newer Logitech mice Defaults to
 * enabled अगर we करो nothing to it. Of course I put this in because I want it
 * disabled :P
 * 1 - enabled (अगर previously disabled, also शेष)
 * 0 - disabled
 */

अटल व्योम ps2pp_set_smartscroll(काष्ठा psmouse *psmouse, bool smartscroll)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	u8 param[4];

	ps2pp_cmd(psmouse, param, 0x32);

	param[0] = 0;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);

	param[0] = smartscroll;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
पूर्ण

अटल sमाप_प्रकार ps2pp_attr_show_smartscroll(काष्ठा psmouse *psmouse,
					   व्योम *data, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", psmouse->smartscroll);
पूर्ण

अटल sमाप_प्रकार ps2pp_attr_set_smartscroll(काष्ठा psmouse *psmouse, व्योम *data,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	अगर (value > 1)
		वापस -EINVAL;

	ps2pp_set_smartscroll(psmouse, value);
	psmouse->smartscroll = value;
	वापस count;
पूर्ण

PSMOUSE_DEFINE_ATTR(smartscroll, S_IWUSR | S_IRUGO, शून्य,
		    ps2pp_attr_show_smartscroll, ps2pp_attr_set_smartscroll);

/*
 * Support 800 dpi resolution _only_ अगर the user wants it (there are good
 * reasons to not use it even अगर the mouse supports it, and of course there are
 * also good reasons to use it, let the user decide).
 */

अटल व्योम ps2pp_set_resolution(काष्ठा psmouse *psmouse,
				 अचिन्हित पूर्णांक resolution)
अणु
	अगर (resolution > 400) अणु
		काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
		u8 param = 3;

		ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETSCALE11);
		ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETSCALE11);
		ps2_command(ps2dev, शून्य, PSMOUSE_CMD_SETSCALE11);
		ps2_command(ps2dev, &param, PSMOUSE_CMD_SETRES);
		psmouse->resolution = 800;
	पूर्ण अन्यथा
		psmouse_set_resolution(psmouse, resolution);
पूर्ण

अटल व्योम ps2pp_disconnect(काष्ठा psmouse *psmouse)
अणु
	device_हटाओ_file(&psmouse->ps2dev.serio->dev,
			   &psmouse_attr_smartscroll.dattr);
पूर्ण

अटल स्थिर काष्ठा ps2pp_info *get_model_info(अचिन्हित अक्षर model)
अणु
	अटल स्थिर काष्ठा ps2pp_info ps2pp_list[] = अणु
		अणु  1,	0,			0 पूर्ण,	/* Simple 2-button mouse */
		अणु 12,	0,			PS2PP_SIDE_BTNपूर्ण,
		अणु 13,	0,			0 पूर्ण,
		अणु 15,	PS2PP_KIND_MX,					/* MX1000 */
				PS2PP_WHEEL | PS2PP_SIDE_BTN | PS2PP_TASK_BTN |
				PS2PP_EXTRA_BTN | PS2PP_NAV_BTN | PS2PP_HWHEEL पूर्ण,
		अणु 40,	0,			PS2PP_SIDE_BTN पूर्ण,
		अणु 41,	0,			PS2PP_SIDE_BTN पूर्ण,
		अणु 42,	0,			PS2PP_SIDE_BTN पूर्ण,
		अणु 43,	0,			PS2PP_SIDE_BTN पूर्ण,
		अणु 50,	0,			0 पूर्ण,
		अणु 51,	0,			0 पूर्ण,
		अणु 52,	PS2PP_KIND_WHEEL,	PS2PP_SIDE_BTN | PS2PP_WHEEL पूर्ण,
		अणु 53,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL पूर्ण,
		अणु 56,	PS2PP_KIND_WHEEL,	PS2PP_SIDE_BTN | PS2PP_WHEEL पूर्ण, /* Cordless MouseMan Wheel */
		अणु 61,	PS2PP_KIND_MX,					/* MX700 */
				PS2PP_WHEEL | PS2PP_SIDE_BTN | PS2PP_TASK_BTN |
				PS2PP_EXTRA_BTN | PS2PP_NAV_BTN पूर्ण,
		अणु 66,	PS2PP_KIND_MX,					/* MX3100 receiver */
				PS2PP_WHEEL | PS2PP_SIDE_BTN | PS2PP_TASK_BTN |
				PS2PP_EXTRA_BTN | PS2PP_NAV_BTN | PS2PP_HWHEEL पूर्ण,
		अणु 72,	PS2PP_KIND_TRACKMAN,	0 पूर्ण,			/* T-CH11: TrackMan Marble */
		अणु 73,	PS2PP_KIND_TRACKMAN,	PS2PP_SIDE_BTN पूर्ण,	/* TrackMan FX */
		अणु 75,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL पूर्ण,
		अणु 76,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL पूर्ण,
		अणु 79,	PS2PP_KIND_TRACKMAN,	PS2PP_WHEEL पूर्ण,		/* TrackMan with wheel */
		अणु 80,	PS2PP_KIND_WHEEL,	PS2PP_SIDE_BTN | PS2PP_WHEEL पूर्ण,
		अणु 81,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL पूर्ण,
		अणु 83,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL पूर्ण,
		अणु 85,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL पूर्ण,
		अणु 86,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL पूर्ण,
		अणु 87,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL पूर्ण,
		अणु 88,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL पूर्ण,
		अणु 96,	0,			0 पूर्ण,
		अणु 97,	PS2PP_KIND_TP3,		PS2PP_WHEEL | PS2PP_HWHEEL पूर्ण,
		अणु 99,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL पूर्ण,
		अणु 100,	PS2PP_KIND_MX,					/* MX510 */
				PS2PP_WHEEL | PS2PP_SIDE_BTN | PS2PP_TASK_BTN |
				PS2PP_EXTRA_BTN | PS2PP_NAV_BTN पूर्ण,
		अणु 111,  PS2PP_KIND_MX,	PS2PP_WHEEL | PS2PP_SIDE_BTN पूर्ण,	/* MX300 reports task button as side */
		अणु 112,	PS2PP_KIND_MX,					/* MX500 */
				PS2PP_WHEEL | PS2PP_SIDE_BTN | PS2PP_TASK_BTN |
				PS2PP_EXTRA_BTN | PS2PP_NAV_BTN पूर्ण,
		अणु 114,	PS2PP_KIND_MX,					/* MX310 */
				PS2PP_WHEEL | PS2PP_SIDE_BTN |
				PS2PP_TASK_BTN | PS2PP_EXTRA_BTN पूर्ण
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ps2pp_list); i++)
		अगर (model == ps2pp_list[i].model)
			वापस &ps2pp_list[i];

	वापस शून्य;
पूर्ण

/*
 * Set up input device's properties based on the detected mouse model.
 */

अटल व्योम ps2pp_set_model_properties(काष्ठा psmouse *psmouse,
				       स्थिर काष्ठा ps2pp_info *model_info,
				       bool using_ps2pp)
अणु
	काष्ठा input_dev *input_dev = psmouse->dev;

	अगर (model_info->features & PS2PP_SIDE_BTN)
		input_set_capability(input_dev, EV_KEY, BTN_SIDE);

	अगर (model_info->features & PS2PP_EXTRA_BTN)
		input_set_capability(input_dev, EV_KEY, BTN_EXTRA);

	अगर (model_info->features & PS2PP_TASK_BTN)
		input_set_capability(input_dev, EV_KEY, BTN_TASK);

	अगर (model_info->features & PS2PP_NAV_BTN) अणु
		input_set_capability(input_dev, EV_KEY, BTN_FORWARD);
		input_set_capability(input_dev, EV_KEY, BTN_BACK);
	पूर्ण

	अगर (model_info->features & PS2PP_WHEEL)
		input_set_capability(input_dev, EV_REL, REL_WHEEL);

	अगर (model_info->features & PS2PP_HWHEEL)
		input_set_capability(input_dev, EV_REL, REL_HWHEEL);

	चयन (model_info->kind) अणु

	हाल PS2PP_KIND_WHEEL:
		psmouse->name = "Wheel Mouse";
		अवरोध;

	हाल PS2PP_KIND_MX:
		psmouse->name = "MX Mouse";
		अवरोध;

	हाल PS2PP_KIND_TP3:
		psmouse->name = "TouchPad 3";
		अवरोध;

	हाल PS2PP_KIND_TRACKMAN:
		psmouse->name = "TrackMan";
		अवरोध;

	शेष:
		/*
		 * Set name to "Mouse" only when using PS2++,
		 * otherwise let other protocols define suitable
		 * name
		 */
		अगर (using_ps2pp)
			psmouse->name = "Mouse";
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ps2pp_setup_protocol(काष्ठा psmouse *psmouse,
				स्थिर काष्ठा ps2pp_info *model_info)
अणु
	पूर्णांक error;

	psmouse->protocol_handler = ps2pp_process_byte;
	psmouse->pktsize = 3;

	अगर (model_info->kind != PS2PP_KIND_TP3) अणु
		psmouse->set_resolution = ps2pp_set_resolution;
		psmouse->disconnect = ps2pp_disconnect;

		error = device_create_file(&psmouse->ps2dev.serio->dev,
					   &psmouse_attr_smartscroll.dattr);
		अगर (error) अणु
			psmouse_err(psmouse,
				    "failed to create smartscroll sysfs attribute, error: %d\n",
				    error);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Logitech magic init. Detect whether the mouse is a Logitech one
 * and its exact model and try turning on extended protocol क्रम ones
 * that support it.
 */

पूर्णांक ps2pp_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	स्थिर काष्ठा ps2pp_info *model_info;
	u8 param[4];
	u8 model, buttons;
	bool use_ps2pp = false;
	पूर्णांक error;

	param[0] = 0;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	ps2_command(ps2dev,  शून्य, PSMOUSE_CMD_SETSCALE11);
	ps2_command(ps2dev,  शून्य, PSMOUSE_CMD_SETSCALE11);
	ps2_command(ps2dev,  शून्य, PSMOUSE_CMD_SETSCALE11);
	param[1] = 0;
	ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO);

	model = ((param[0] >> 4) & 0x07) | ((param[0] << 3) & 0x78);
	buttons = param[1];

	अगर (!model || !buttons)
		वापस -ENXIO;

	model_info = get_model_info(model);
	अगर (model_info) अणु

/*
 * Do Logitech PS2++ / PS2T++ magic init.
 */
		अगर (model_info->kind == PS2PP_KIND_TP3) अणु /* Touch Pad 3 */

			/* Unprotect RAM */
			param[0] = 0x11; param[1] = 0x04; param[2] = 0x68;
			ps2_command(ps2dev, param, 0x30d1);
			/* Enable features */
			param[0] = 0x11; param[1] = 0x05; param[2] = 0x0b;
			ps2_command(ps2dev, param, 0x30d1);
			/* Enable PS2++ */
			param[0] = 0x11; param[1] = 0x09; param[2] = 0xc3;
			ps2_command(ps2dev, param, 0x30d1);

			param[0] = 0;
			अगर (!ps2_command(ps2dev, param, 0x13d1) &&
			    param[0] == 0x06 && param[1] == 0x00 &&
			    param[2] == 0x14) अणु
				use_ps2pp = true;
			पूर्ण

		पूर्ण अन्यथा अणु

			param[0] = param[1] = param[2] = 0;
			ps2pp_cmd(psmouse, param, 0x39); /* Magic knock */
			ps2pp_cmd(psmouse, param, 0xDB);

			अगर ((param[0] & 0x78) == 0x48 &&
			    (param[1] & 0xf3) == 0xc2 &&
			    (param[2] & 0x03) == ((param[1] >> 2) & 3)) अणु
				ps2pp_set_smartscroll(psmouse, false);
				use_ps2pp = true;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		psmouse_warn(psmouse,
			     "Detected unknown Logitech mouse model %d\n",
			     model);
	पूर्ण

	अगर (set_properties) अणु
		psmouse->venकरोr = "Logitech";
		psmouse->model = model;

		अगर (use_ps2pp) अणु
			error = ps2pp_setup_protocol(psmouse, model_info);
			अगर (error)
				वापस error;
		पूर्ण

		अगर (buttons >= 3)
			input_set_capability(psmouse->dev, EV_KEY, BTN_MIDDLE);

		अगर (model_info)
			ps2pp_set_model_properties(psmouse, model_info, use_ps2pp);
	पूर्ण

	वापस use_ps2pp ? 0 : -ENXIO;
पूर्ण

