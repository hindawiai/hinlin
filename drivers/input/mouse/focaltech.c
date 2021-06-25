<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Focaltech TouchPad PS/2 mouse driver
 *
 * Copyright (c) 2014 Red Hat Inc.
 * Copyright (c) 2014 Mathias Gottschlag <mgottschlag@gmail.com>
 *
 * Red Hat authors:
 *
 * Hans de Goede <hdegoede@redhat.com>
 */


#समावेश <linux/device.h>
#समावेश <linux/libps2.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/serपन.स>
#समावेश <linux/slab.h>
#समावेश "psmouse.h"
#समावेश "focaltech.h"

अटल स्थिर अक्षर * स्थिर focaltech_pnp_ids[] = अणु
	"FLT0101",
	"FLT0102",
	"FLT0103",
	शून्य
पूर्ण;

/*
 * Even अगर the kernel is built without support क्रम Focaltech PS/2 touchpads (or
 * when the real driver fails to recognize the device), we still have to detect
 * them in order to aव्योम further detection attempts confusing the touchpad.
 * This way it at least works in PS/2 mouse compatibility mode.
 */
पूर्णांक focaltech_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	अगर (!psmouse_matches_pnp_id(psmouse, focaltech_pnp_ids))
		वापस -ENODEV;

	अगर (set_properties) अणु
		psmouse->venकरोr = "FocalTech";
		psmouse->name = "Touchpad";
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MOUSE_PS2_FOCALTECH

/*
 * Packet types - the numbers are not consecutive, so we might be missing
 * something here.
 */
#घोषणा FOC_TOUCH 0x3 /* biपंचांगap of active fingers */
#घोषणा FOC_ABS 0x6 /* असलolute position of one finger */
#घोषणा FOC_REL 0x9 /* relative position of 1-2 fingers */

#घोषणा FOC_MAX_FINGERS 5

/*
 * Current state of a single finger on the touchpad.
 */
काष्ठा focaltech_finger_state अणु
	/* The touchpad has generated a touch event क्रम the finger */
	bool active;

	/*
	 * The touchpad has sent position data क्रम the finger. The
	 * flag is 0 when the finger is not active, and there is a
	 * समय between the first touch event क्रम the finger and the
	 * following असलolute position packet क्रम the finger where the
	 * touchpad has declared the finger to be valid, but we करो not
	 * have any valid position yet.
	 */
	bool valid;

	/*
	 * Absolute position (from the bottom left corner) of the
	 * finger.
	 */
	अचिन्हित पूर्णांक x;
	अचिन्हित पूर्णांक y;
पूर्ण;

/*
 * Description of the current state of the touchpad hardware.
 */
काष्ठा focaltech_hw_state अणु
	/*
	 * The touchpad tracks the positions of the fingers क्रम us,
	 * the array indices correspond to the finger indices वापसed
	 * in the report packages.
	 */
	काष्ठा focaltech_finger_state fingers[FOC_MAX_FINGERS];

	/*
	 * Finger width 0-7 and 15 क्रम a very big contact area.
	 * 15 value stays until the finger is released.
	 * Width is reported only in असलolute packets.
	 * Since hardware reports width only क्रम last touching finger,
	 * there is no need to store width क्रम every specअगरic finger,
	 * so we keep only last value reported.
	 */
	अचिन्हित पूर्णांक width;

	/* True अगर the clickpad has been pressed. */
	bool pressed;
पूर्ण;

काष्ठा focaltech_data अणु
	अचिन्हित पूर्णांक x_max, y_max;
	काष्ठा focaltech_hw_state state;
पूर्ण;

अटल व्योम focaltech_report_state(काष्ठा psmouse *psmouse)
अणु
	काष्ठा focaltech_data *priv = psmouse->निजी;
	काष्ठा focaltech_hw_state *state = &priv->state;
	काष्ठा input_dev *dev = psmouse->dev;
	पूर्णांक i;

	क्रम (i = 0; i < FOC_MAX_FINGERS; i++) अणु
		काष्ठा focaltech_finger_state *finger = &state->fingers[i];
		bool active = finger->active && finger->valid;

		input_mt_slot(dev, i);
		input_mt_report_slot_state(dev, MT_TOOL_FINGER, active);
		अगर (active) अणु
			अचिन्हित पूर्णांक clamped_x, clamped_y;
			/*
			 * The touchpad might report invalid data, so we clamp
			 * the resulting values so that we करो not confuse
			 * userspace.
			 */
			clamped_x = clamp(finger->x, 0U, priv->x_max);
			clamped_y = clamp(finger->y, 0U, priv->y_max);
			input_report_असल(dev, ABS_MT_POSITION_X, clamped_x);
			input_report_असल(dev, ABS_MT_POSITION_Y,
					 priv->y_max - clamped_y);
			input_report_असल(dev, ABS_TOOL_WIDTH, state->width);
		पूर्ण
	पूर्ण
	input_mt_report_poपूर्णांकer_emulation(dev, true);

	input_report_key(dev, BTN_LEFT, state->pressed);
	input_sync(dev);
पूर्ण

अटल व्योम focaltech_process_touch_packet(काष्ठा psmouse *psmouse,
					   अचिन्हित अक्षर *packet)
अणु
	काष्ठा focaltech_data *priv = psmouse->निजी;
	काष्ठा focaltech_hw_state *state = &priv->state;
	अचिन्हित अक्षर fingers = packet[1];
	पूर्णांक i;

	state->pressed = (packet[0] >> 4) & 1;

	/* the second byte contains a biपंचांगap of all fingers touching the pad */
	क्रम (i = 0; i < FOC_MAX_FINGERS; i++) अणु
		state->fingers[i].active = fingers & 0x1;
		अगर (!state->fingers[i].active) अणु
			/*
			 * Even when the finger becomes active again, we still
			 * will have to रुको क्रम the first valid position.
			 */
			state->fingers[i].valid = false;
		पूर्ण
		fingers >>= 1;
	पूर्ण
पूर्ण

अटल व्योम focaltech_process_असल_packet(काष्ठा psmouse *psmouse,
					 अचिन्हित अक्षर *packet)
अणु
	काष्ठा focaltech_data *priv = psmouse->निजी;
	काष्ठा focaltech_hw_state *state = &priv->state;
	अचिन्हित पूर्णांक finger;

	finger = (packet[1] >> 4) - 1;
	अगर (finger >= FOC_MAX_FINGERS) अणु
		psmouse_err(psmouse, "Invalid finger in abs packet: %d\n",
			    finger);
		वापस;
	पूर्ण

	state->pressed = (packet[0] >> 4) & 1;

	state->fingers[finger].x = ((packet[1] & 0xf) << 8) | packet[2];
	state->fingers[finger].y = (packet[3] << 8) | packet[4];
	state->width = packet[5] >> 4;
	state->fingers[finger].valid = true;
पूर्ण

अटल व्योम focaltech_process_rel_packet(काष्ठा psmouse *psmouse,
					 अचिन्हित अक्षर *packet)
अणु
	काष्ठा focaltech_data *priv = psmouse->निजी;
	काष्ठा focaltech_hw_state *state = &priv->state;
	पूर्णांक finger1, finger2;

	state->pressed = packet[0] >> 7;
	finger1 = ((packet[0] >> 4) & 0x7) - 1;
	अगर (finger1 < FOC_MAX_FINGERS) अणु
		state->fingers[finger1].x += (अक्षर)packet[1];
		state->fingers[finger1].y += (अक्षर)packet[2];
	पूर्ण अन्यथा अणु
		psmouse_err(psmouse, "First finger in rel packet invalid: %d\n",
			    finger1);
	पूर्ण

	/*
	 * If there is an odd number of fingers, the last relative
	 * packet only contains one finger. In this हाल, the second
	 * finger index in the packet is 0 (we subtract 1 in the lines
	 * above to create array indices, so the finger will overflow
	 * and be above FOC_MAX_FINGERS).
	 */
	finger2 = ((packet[3] >> 4) & 0x7) - 1;
	अगर (finger2 < FOC_MAX_FINGERS) अणु
		state->fingers[finger2].x += (अक्षर)packet[4];
		state->fingers[finger2].y += (अक्षर)packet[5];
	पूर्ण
पूर्ण

अटल व्योम focaltech_process_packet(काष्ठा psmouse *psmouse)
अणु
	अचिन्हित अक्षर *packet = psmouse->packet;

	चयन (packet[0] & 0xf) अणु
	हाल FOC_TOUCH:
		focaltech_process_touch_packet(psmouse, packet);
		अवरोध;

	हाल FOC_ABS:
		focaltech_process_असल_packet(psmouse, packet);
		अवरोध;

	हाल FOC_REL:
		focaltech_process_rel_packet(psmouse, packet);
		अवरोध;

	शेष:
		psmouse_err(psmouse, "Unknown packet type: %02x\n", packet[0]);
		अवरोध;
	पूर्ण

	focaltech_report_state(psmouse);
पूर्ण

अटल psmouse_ret_t focaltech_process_byte(काष्ठा psmouse *psmouse)
अणु
	अगर (psmouse->pktcnt >= 6) अणु /* Full packet received */
		focaltech_process_packet(psmouse);
		वापस PSMOUSE_FULL_PACKET;
	पूर्ण

	/*
	 * We might want to करो some validation of the data here, but
	 * we करो not know the protocol well enough
	 */
	वापस PSMOUSE_GOOD_DATA;
पूर्ण

अटल पूर्णांक focaltech_चयन_protocol(काष्ठा psmouse *psmouse)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	अचिन्हित अक्षर param[3];

	param[0] = 0;
	अगर (ps2_command(ps2dev, param, 0x10f8))
		वापस -EIO;

	अगर (ps2_command(ps2dev, param, 0x10f8))
		वापस -EIO;

	अगर (ps2_command(ps2dev, param, 0x10f8))
		वापस -EIO;

	param[0] = 1;
	अगर (ps2_command(ps2dev, param, 0x10f8))
		वापस -EIO;

	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_SETSCALE11))
		वापस -EIO;

	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_ENABLE))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम focaltech_reset(काष्ठा psmouse *psmouse)
अणु
	ps2_command(&psmouse->ps2dev, शून्य, PSMOUSE_CMD_RESET_DIS);
	psmouse_reset(psmouse);
पूर्ण

अटल व्योम focaltech_disconnect(काष्ठा psmouse *psmouse)
अणु
	focaltech_reset(psmouse);
	kमुक्त(psmouse->निजी);
	psmouse->निजी = शून्य;
पूर्ण

अटल पूर्णांक focaltech_reconnect(काष्ठा psmouse *psmouse)
अणु
	पूर्णांक error;

	focaltech_reset(psmouse);

	error = focaltech_चयन_protocol(psmouse);
	अगर (error) अणु
		psmouse_err(psmouse, "Unable to initialize the device\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम focaltech_set_input_params(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा focaltech_data *priv = psmouse->निजी;

	/*
	 * Unकरो part of setup करोne क्रम us by psmouse core since touchpad
	 * is not a relative device.
	 */
	__clear_bit(EV_REL, dev->evbit);
	__clear_bit(REL_X, dev->relbit);
	__clear_bit(REL_Y, dev->relbit);
	__clear_bit(BTN_RIGHT, dev->keybit);
	__clear_bit(BTN_MIDDLE, dev->keybit);

	/*
	 * Now set up our capabilities.
	 */
	__set_bit(EV_ABS, dev->evbit);
	input_set_असल_params(dev, ABS_MT_POSITION_X, 0, priv->x_max, 0, 0);
	input_set_असल_params(dev, ABS_MT_POSITION_Y, 0, priv->y_max, 0, 0);
	input_set_असल_params(dev, ABS_TOOL_WIDTH, 0, 15, 0, 0);
	input_mt_init_slots(dev, 5, INPUT_MT_POINTER);
	__set_bit(INPUT_PROP_BUTTONPAD, dev->propbit);
पूर्ण

अटल पूर्णांक focaltech_पढ़ो_रेजिस्टर(काष्ठा ps2dev *ps2dev, पूर्णांक reg,
				   अचिन्हित अक्षर *param)
अणु
	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_SETSCALE11))
		वापस -EIO;

	param[0] = 0;
	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES))
		वापस -EIO;

	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES))
		वापस -EIO;

	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES))
		वापस -EIO;

	param[0] = reg;
	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES))
		वापस -EIO;

	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक focaltech_पढ़ो_size(काष्ठा psmouse *psmouse)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	काष्ठा focaltech_data *priv = psmouse->निजी;
	अक्षर param[3];

	अगर (focaltech_पढ़ो_रेजिस्टर(ps2dev, 2, param))
		वापस -EIO;

	/* not sure whether this is 100% correct */
	priv->x_max = (अचिन्हित अक्षर)param[1] * 128;
	priv->y_max = (अचिन्हित अक्षर)param[2] * 128;

	वापस 0;
पूर्ण

अटल व्योम focaltech_set_resolution(काष्ठा psmouse *psmouse,
				     अचिन्हित पूर्णांक resolution)
अणु
	/* not supported yet */
पूर्ण

अटल व्योम focaltech_set_rate(काष्ठा psmouse *psmouse, अचिन्हित पूर्णांक rate)
अणु
	/* not supported yet */
पूर्ण

अटल व्योम focaltech_set_scale(काष्ठा psmouse *psmouse,
				क्रमागत psmouse_scale scale)
अणु
	/* not supported yet */
पूर्ण

पूर्णांक focaltech_init(काष्ठा psmouse *psmouse)
अणु
	काष्ठा focaltech_data *priv;
	पूर्णांक error;

	psmouse->निजी = priv = kzalloc(माप(काष्ठा focaltech_data),
					  GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	focaltech_reset(psmouse);

	error = focaltech_पढ़ो_size(psmouse);
	अगर (error) अणु
		psmouse_err(psmouse,
			    "Unable to read the size of the touchpad\n");
		जाओ fail;
	पूर्ण

	error = focaltech_चयन_protocol(psmouse);
	अगर (error) अणु
		psmouse_err(psmouse, "Unable to initialize the device\n");
		जाओ fail;
	पूर्ण

	focaltech_set_input_params(psmouse);

	psmouse->protocol_handler = focaltech_process_byte;
	psmouse->pktsize = 6;
	psmouse->disconnect = focaltech_disconnect;
	psmouse->reconnect = focaltech_reconnect;
	psmouse->cleanup = focaltech_reset;
	/* resync is not supported yet */
	psmouse->resync_समय = 0;
	/*
	 * rate/resolution/scale changes are not supported yet, and
	 * the generic implementations of these functions seem to
	 * confuse some touchpads
	 */
	psmouse->set_resolution = focaltech_set_resolution;
	psmouse->set_rate = focaltech_set_rate;
	psmouse->set_scale = focaltech_set_scale;

	वापस 0;

fail:
	focaltech_reset(psmouse);
	kमुक्त(priv);
	वापस error;
पूर्ण
#पूर्ण_अगर /* CONFIG_MOUSE_PS2_FOCALTECH */
