<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ----------------------------------------------------------------------------
 * touchkit_ps2.c  --  Driver क्रम eGalax TouchKit PS/2 Touchscreens
 *
 * Copyright (C) 2005 by Stefan Lucke
 * Copyright (C) 2004 by Daniel Ritz
 * Copyright (C) by Todd E. Johnson (mtouchusb.c)
 *
 * Based upon touchkitusb.c
 *
 * Venकरोr करोcumentation is available at:
 * http://home.eeti.com.tw/web20/drivers/Software%20Programming%20Guide_v2.0.pdf 
 */

#समावेश <linux/kernel.h>

#समावेश <linux/input.h>
#समावेश <linux/serपन.स>
#समावेश <linux/libps2.h>

#समावेश "psmouse.h"
#समावेश "touchkit_ps2.h"

#घोषणा TOUCHKIT_MAX_XC			0x07ff
#घोषणा TOUCHKIT_MAX_YC			0x07ff

#घोषणा TOUCHKIT_CMD			0x0a
#घोषणा TOUCHKIT_CMD_LENGTH		1

#घोषणा TOUCHKIT_CMD_ACTIVE		'A'
#घोषणा TOUCHKIT_CMD_FIRMWARE_VERSION	'D'
#घोषणा TOUCHKIT_CMD_CONTROLLER_TYPE	'E'

#घोषणा TOUCHKIT_SEND_PARMS(s, r, c)	((s) << 12 | (r) << 8 | (c))

#घोषणा TOUCHKIT_GET_TOUCHED(packet)	(((packet)[0]) & 0x01)
#घोषणा TOUCHKIT_GET_X(packet)		(((packet)[1] << 7) | (packet)[2])
#घोषणा TOUCHKIT_GET_Y(packet)		(((packet)[3] << 7) | (packet)[4])

अटल psmouse_ret_t touchkit_ps2_process_byte(काष्ठा psmouse *psmouse)
अणु
	अचिन्हित अक्षर *packet = psmouse->packet;
	काष्ठा input_dev *dev = psmouse->dev;

	अगर (psmouse->pktcnt != 5)
		वापस PSMOUSE_GOOD_DATA;

	input_report_असल(dev, ABS_X, TOUCHKIT_GET_X(packet));
	input_report_असल(dev, ABS_Y, TOUCHKIT_GET_Y(packet));
	input_report_key(dev, BTN_TOUCH, TOUCHKIT_GET_TOUCHED(packet));
	input_sync(dev);

	वापस PSMOUSE_FULL_PACKET;
पूर्ण

पूर्णांक touchkit_ps2_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	अचिन्हित अक्षर param[3];
	पूर्णांक command;

	param[0] = TOUCHKIT_CMD_LENGTH;
	param[1] = TOUCHKIT_CMD_ACTIVE;
	command = TOUCHKIT_SEND_PARMS(2, 3, TOUCHKIT_CMD);

	अगर (ps2_command(&psmouse->ps2dev, param, command))
		वापस -ENODEV;

	अगर (param[0] != TOUCHKIT_CMD || param[1] != 0x01 ||
	    param[2] != TOUCHKIT_CMD_ACTIVE)
		वापस -ENODEV;

	अगर (set_properties) अणु
		dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		dev->keybit[BIT_WORD(BTN_MOUSE)] = 0;
		dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
		input_set_असल_params(dev, ABS_X, 0, TOUCHKIT_MAX_XC, 0, 0);
		input_set_असल_params(dev, ABS_Y, 0, TOUCHKIT_MAX_YC, 0, 0);

		psmouse->venकरोr = "eGalax";
		psmouse->name = "Touchscreen";
		psmouse->protocol_handler = touchkit_ps2_process_byte;
		psmouse->pktsize = 5;
	पूर्ण

	वापस 0;
पूर्ण
