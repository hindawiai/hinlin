<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Elantech Touchpad driver (v6)
 *
 * Copyright (C) 2007-2009 Arjan Opmeer <arjan@opmeer.net>
 *
 * Trademarks are the property of their respective owners.
 */

#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serपन.स>
#समावेश <linux/libps2.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "psmouse.h"
#समावेश "elantech.h"
#समावेश "elan_i2c.h"

#घोषणा elantech_debug(fmt, ...)					\
	करो अणु								\
		अगर (etd->info.debug)					\
			psmouse_prपूर्णांकk(KERN_DEBUG, psmouse,		\
					fmt, ##__VA_ARGS__);		\
	पूर्ण जबतक (0)

/*
 * Send a Synaptics style sliced query command
 */
अटल पूर्णांक synaptics_send_cmd(काष्ठा psmouse *psmouse, अचिन्हित अक्षर c,
				अचिन्हित अक्षर *param)
अणु
	अगर (ps2_sliced_command(&psmouse->ps2dev, c) ||
	    ps2_command(&psmouse->ps2dev, param, PSMOUSE_CMD_GETINFO)) अणु
		psmouse_err(psmouse, "%s query 0x%02x failed.\n", __func__, c);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * V3 and later support this fast command
 */
अटल पूर्णांक elantech_send_cmd(काष्ठा psmouse *psmouse, अचिन्हित अक्षर c,
				अचिन्हित अक्षर *param)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;

	अगर (ps2_command(ps2dev, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
	    ps2_command(ps2dev, शून्य, c) ||
	    ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO)) अणु
		psmouse_err(psmouse, "%s query 0x%02x failed.\n", __func__, c);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * A retrying version of ps2_command
 */
अटल पूर्णांक elantech_ps2_command(काष्ठा psmouse *psmouse,
				अचिन्हित अक्षर *param, पूर्णांक command)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	काष्ठा elantech_data *etd = psmouse->निजी;
	पूर्णांक rc;
	पूर्णांक tries = ETP_PS2_COMMAND_TRIES;

	करो अणु
		rc = ps2_command(ps2dev, param, command);
		अगर (rc == 0)
			अवरोध;
		tries--;
		elantech_debug("retrying ps2 command 0x%02x (%d).\n",
				command, tries);
		msleep(ETP_PS2_COMMAND_DELAY);
	पूर्ण जबतक (tries > 0);

	अगर (rc)
		psmouse_err(psmouse, "ps2 command 0x%02x failed.\n", command);

	वापस rc;
पूर्ण

/*
 * Send an Elantech style special command to पढ़ो 3 bytes from a रेजिस्टर
 */
अटल पूर्णांक elantech_पढ़ो_reg_params(काष्ठा psmouse *psmouse, u8 reg, u8 *param)
अणु
	अगर (elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
	    elantech_ps2_command(psmouse, शून्य, ETP_REGISTER_READWRITE) ||
	    elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
	    elantech_ps2_command(psmouse, शून्य, reg) ||
	    elantech_ps2_command(psmouse, param, PSMOUSE_CMD_GETINFO)) अणु
		psmouse_err(psmouse,
			    "failed to read register %#02x\n", reg);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Send an Elantech style special command to ग_लिखो a रेजिस्टर with a parameter
 */
अटल पूर्णांक elantech_ग_लिखो_reg_params(काष्ठा psmouse *psmouse, u8 reg, u8 *param)
अणु
	अगर (elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
	    elantech_ps2_command(psmouse, शून्य, ETP_REGISTER_READWRITE) ||
	    elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
	    elantech_ps2_command(psmouse, शून्य, reg) ||
	    elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
	    elantech_ps2_command(psmouse, शून्य, param[0]) ||
	    elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
	    elantech_ps2_command(psmouse, शून्य, param[1]) ||
	    elantech_ps2_command(psmouse, शून्य, PSMOUSE_CMD_SETSCALE11)) अणु
		psmouse_err(psmouse,
			    "failed to write register %#02x with value %#02x%#02x\n",
			    reg, param[0], param[1]);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Send an Elantech style special command to पढ़ो a value from a रेजिस्टर
 */
अटल पूर्णांक elantech_पढ़ो_reg(काष्ठा psmouse *psmouse, अचिन्हित अक्षर reg,
				अचिन्हित अक्षर *val)
अणु
	काष्ठा elantech_data *etd = psmouse->निजी;
	अचिन्हित अक्षर param[3];
	पूर्णांक rc = 0;

	अगर (reg < 0x07 || reg > 0x26)
		वापस -1;

	अगर (reg > 0x11 && reg < 0x20)
		वापस -1;

	चयन (etd->info.hw_version) अणु
	हाल 1:
		अगर (ps2_sliced_command(&psmouse->ps2dev, ETP_REGISTER_READ) ||
		    ps2_sliced_command(&psmouse->ps2dev, reg) ||
		    ps2_command(&psmouse->ps2dev, param, PSMOUSE_CMD_GETINFO)) अणु
			rc = -1;
		पूर्ण
		अवरोध;

	हाल 2:
		अगर (elantech_ps2_command(psmouse,  शून्य, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse,  शून्य, ETP_REGISTER_READ) ||
		    elantech_ps2_command(psmouse,  शून्य, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse,  शून्य, reg) ||
		    elantech_ps2_command(psmouse, param, PSMOUSE_CMD_GETINFO)) अणु
			rc = -1;
		पूर्ण
		अवरोध;

	हाल 3 ... 4:
		अगर (elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse, शून्य, ETP_REGISTER_READWRITE) ||
		    elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse, शून्य, reg) ||
		    elantech_ps2_command(psmouse, param, PSMOUSE_CMD_GETINFO)) अणु
			rc = -1;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (rc)
		psmouse_err(psmouse, "failed to read register 0x%02x.\n", reg);
	अन्यथा अगर (etd->info.hw_version != 4)
		*val = param[0];
	अन्यथा
		*val = param[1];

	वापस rc;
पूर्ण

/*
 * Send an Elantech style special command to ग_लिखो a रेजिस्टर with a value
 */
अटल पूर्णांक elantech_ग_लिखो_reg(काष्ठा psmouse *psmouse, अचिन्हित अक्षर reg,
				अचिन्हित अक्षर val)
अणु
	काष्ठा elantech_data *etd = psmouse->निजी;
	पूर्णांक rc = 0;

	अगर (reg < 0x07 || reg > 0x26)
		वापस -1;

	अगर (reg > 0x11 && reg < 0x20)
		वापस -1;

	चयन (etd->info.hw_version) अणु
	हाल 1:
		अगर (ps2_sliced_command(&psmouse->ps2dev, ETP_REGISTER_WRITE) ||
		    ps2_sliced_command(&psmouse->ps2dev, reg) ||
		    ps2_sliced_command(&psmouse->ps2dev, val) ||
		    ps2_command(&psmouse->ps2dev, शून्य, PSMOUSE_CMD_SETSCALE11)) अणु
			rc = -1;
		पूर्ण
		अवरोध;

	हाल 2:
		अगर (elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse, शून्य, ETP_REGISTER_WRITE) ||
		    elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse, शून्य, reg) ||
		    elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse, शून्य, val) ||
		    elantech_ps2_command(psmouse, शून्य, PSMOUSE_CMD_SETSCALE11)) अणु
			rc = -1;
		पूर्ण
		अवरोध;

	हाल 3:
		अगर (elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse, शून्य, ETP_REGISTER_READWRITE) ||
		    elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse, शून्य, reg) ||
		    elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse, शून्य, val) ||
		    elantech_ps2_command(psmouse, शून्य, PSMOUSE_CMD_SETSCALE11)) अणु
			rc = -1;
		पूर्ण
		अवरोध;

	हाल 4:
		अगर (elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse, शून्य, ETP_REGISTER_READWRITE) ||
		    elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse, शून्य, reg) ||
		    elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse, शून्य, ETP_REGISTER_READWRITE) ||
		    elantech_ps2_command(psmouse, शून्य, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse, शून्य, val) ||
		    elantech_ps2_command(psmouse, शून्य, PSMOUSE_CMD_SETSCALE11)) अणु
			rc = -1;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (rc)
		psmouse_err(psmouse,
			    "failed to write register 0x%02x with value 0x%02x.\n",
			    reg, val);

	वापस rc;
पूर्ण

/*
 * Dump a complete mouse movement packet to the syslog
 */
अटल व्योम elantech_packet_dump(काष्ठा psmouse *psmouse)
अणु
	psmouse_prपूर्णांकk(KERN_DEBUG, psmouse, "PS/2 packet [%*ph]\n",
		       psmouse->pktsize, psmouse->packet);
पूर्ण

/*
 * Advertise INPUT_PROP_BUTTONPAD क्रम clickpads. The testing of bit 12 in
 * fw_version क्रम this is based on the following fw_version & caps table:
 *
 * Laptop-model:           fw_version:     caps:           buttons:
 * Acer S3                 0x461f00        10, 13, 0e      clickpad
 * Acer S7-392             0x581f01        50, 17, 0d      clickpad
 * Acer V5-131             0x461f02        01, 16, 0c      clickpad
 * Acer V5-551             0x461f00        ?               clickpad
 * Asus K53SV              0x450f01        78, 15, 0c      2 hw buttons
 * Asus G46VW              0x460f02        00, 18, 0c      2 hw buttons
 * Asus G750JX             0x360f00        00, 16, 0c      2 hw buttons
 * Asus TP500LN            0x381f17        10, 14, 0e      clickpad
 * Asus X750JN             0x381f17        10, 14, 0e      clickpad
 * Asus UX31               0x361f00        20, 15, 0e      clickpad
 * Asus UX32VD             0x361f02        00, 15, 0e      clickpad
 * Avatar AVIU-145A2       0x361f00        ?               clickpad
 * Fujitsu CELSIUS H760    0x570f02        40, 14, 0c      3 hw buttons (**)
 * Fujitsu CELSIUS H780    0x5d0f02        41, 16, 0d      3 hw buttons (**)
 * Fujitsu LIFEBOOK E544   0x470f00        d0, 12, 09      2 hw buttons
 * Fujitsu LIFEBOOK E546   0x470f00        50, 12, 09      2 hw buttons
 * Fujitsu LIFEBOOK E547   0x470f00        50, 12, 09      2 hw buttons
 * Fujitsu LIFEBOOK E554   0x570f01        40, 14, 0c      2 hw buttons
 * Fujitsu LIFEBOOK E557   0x570f01        40, 14, 0c      2 hw buttons
 * Fujitsu T725            0x470f01        05, 12, 09      2 hw buttons
 * Fujitsu H730            0x570f00        c0, 14, 0c      3 hw buttons (**)
 * Gigabyte U2442          0x450f01        58, 17, 0c      2 hw buttons
 * Lenovo L430             0x350f02        b9, 15, 0c      2 hw buttons (*)
 * Lenovo L530             0x350f02        b9, 15, 0c      2 hw buttons (*)
 * Samsung NF210           0x150b00        78, 14, 0a      2 hw buttons
 * Samsung NP770Z5E        0x575f01        10, 15, 0f      clickpad
 * Samsung NP700Z5B        0x361f06        21, 15, 0f      clickpad
 * Samsung NP900X3E-A02    0x575f03        ?               clickpad
 * Samsung NP-QX410        0x851b00        19, 14, 0c      clickpad
 * Samsung RC512           0x450f00        08, 15, 0c      2 hw buttons
 * Samsung RF710           0x450f00        ?               2 hw buttons
 * System76 Pangolin       0x250f01        ?               2 hw buttons
 * (*) + 3 trackpoपूर्णांक buttons
 * (**) + 0 trackpoपूर्णांक buttons
 * Note: Lenovo L430 and Lenovo L530 have the same fw_version/caps
 */
अटल अंतरभूत पूर्णांक elantech_is_buttonpad(काष्ठा elantech_device_info *info)
अणु
	वापस info->fw_version & 0x001000;
पूर्ण

/*
 * Interpret complete data packets and report असलolute mode input events क्रम
 * hardware version 1. (4 byte packets)
 */
अटल व्योम elantech_report_असलolute_v1(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा elantech_data *etd = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;
	पूर्णांक fingers;

	अगर (etd->info.fw_version < 0x020000) अणु
		/*
		 * byte 0:  D   U  p1  p2   1  p3   R   L
		 * byte 1:  f   0  th  tw  x9  x8  y9  y8
		 */
		fingers = ((packet[1] & 0x80) >> 7) +
				((packet[1] & 0x30) >> 4);
	पूर्ण अन्यथा अणु
		/*
		 * byte 0: n1  n0  p2  p1   1  p3   R   L
		 * byte 1:  0   0   0   0  x9  x8  y9  y8
		 */
		fingers = (packet[0] & 0xc0) >> 6;
	पूर्ण

	अगर (etd->info.jumpy_cursor) अणु
		अगर (fingers != 1) अणु
			etd->single_finger_reports = 0;
		पूर्ण अन्यथा अगर (etd->single_finger_reports < 2) अणु
			/* Discard first 2 reports of one finger, bogus */
			etd->single_finger_reports++;
			elantech_debug("discarding packet\n");
			वापस;
		पूर्ण
	पूर्ण

	input_report_key(dev, BTN_TOUCH, fingers != 0);

	/*
	 * byte 2: x7  x6  x5  x4  x3  x2  x1  x0
	 * byte 3: y7  y6  y5  y4  y3  y2  y1  y0
	 */
	अगर (fingers) अणु
		input_report_असल(dev, ABS_X,
			((packet[1] & 0x0c) << 6) | packet[2]);
		input_report_असल(dev, ABS_Y,
			etd->y_max - (((packet[1] & 0x03) << 8) | packet[3]));
	पूर्ण

	input_report_key(dev, BTN_TOOL_FINGER, fingers == 1);
	input_report_key(dev, BTN_TOOL_DOUBLETAP, fingers == 2);
	input_report_key(dev, BTN_TOOL_TRIPLETAP, fingers == 3);

	psmouse_report_standard_buttons(dev, packet[0]);

	अगर (etd->info.fw_version < 0x020000 &&
	    (etd->info.capabilities[0] & ETP_CAP_HAS_ROCKER)) अणु
		/* rocker up */
		input_report_key(dev, BTN_FORWARD, packet[0] & 0x40);
		/* rocker करोwn */
		input_report_key(dev, BTN_BACK, packet[0] & 0x80);
	पूर्ण

	input_sync(dev);
पूर्ण

अटल व्योम elantech_set_slot(काष्ठा input_dev *dev, पूर्णांक slot, bool active,
			      अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y)
अणु
	input_mt_slot(dev, slot);
	input_mt_report_slot_state(dev, MT_TOOL_FINGER, active);
	अगर (active) अणु
		input_report_असल(dev, ABS_MT_POSITION_X, x);
		input_report_असल(dev, ABS_MT_POSITION_Y, y);
	पूर्ण
पूर्ण

/* x1 < x2 and y1 < y2 when two fingers, x = y = 0 when not pressed */
अटल व्योम elantech_report_semi_mt_data(काष्ठा input_dev *dev,
					 अचिन्हित पूर्णांक num_fingers,
					 अचिन्हित पूर्णांक x1, अचिन्हित पूर्णांक y1,
					 अचिन्हित पूर्णांक x2, अचिन्हित पूर्णांक y2)
अणु
	elantech_set_slot(dev, 0, num_fingers != 0, x1, y1);
	elantech_set_slot(dev, 1, num_fingers >= 2, x2, y2);
पूर्ण

/*
 * Interpret complete data packets and report असलolute mode input events क्रम
 * hardware version 2. (6 byte packets)
 */
अटल व्योम elantech_report_असलolute_v2(काष्ठा psmouse *psmouse)
अणु
	काष्ठा elantech_data *etd = psmouse->निजी;
	काष्ठा input_dev *dev = psmouse->dev;
	अचिन्हित अक्षर *packet = psmouse->packet;
	अचिन्हित पूर्णांक fingers, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	अचिन्हित पूर्णांक width = 0, pres = 0;

	/* byte 0: n1  n0   .   .   .   .   R   L */
	fingers = (packet[0] & 0xc0) >> 6;

	चयन (fingers) अणु
	हाल 3:
		/*
		 * Same as one finger, except report of more than 3 fingers:
		 * byte 3:  n4  .   w1  w0   .   .   .   .
		 */
		अगर (packet[3] & 0x80)
			fingers = 4;
		fallthrough;
	हाल 1:
		/*
		 * byte 1:  .   .   .   .  x11 x10 x9  x8
		 * byte 2: x7  x6  x5  x4  x4  x2  x1  x0
		 */
		x1 = ((packet[1] & 0x0f) << 8) | packet[2];
		/*
		 * byte 4:  .   .   .   .  y11 y10 y9  y8
		 * byte 5: y7  y6  y5  y4  y3  y2  y1  y0
		 */
		y1 = etd->y_max - (((packet[4] & 0x0f) << 8) | packet[5]);

		pres = (packet[1] & 0xf0) | ((packet[4] & 0xf0) >> 4);
		width = ((packet[0] & 0x30) >> 2) | ((packet[3] & 0x30) >> 4);
		अवरोध;

	हाल 2:
		/*
		 * The coordinate of each finger is reported separately
		 * with a lower resolution क्रम two finger touches:
		 * byte 0:  .   .  ay8 ax8  .   .   .   .
		 * byte 1: ax7 ax6 ax5 ax4 ax3 ax2 ax1 ax0
		 */
		x1 = (((packet[0] & 0x10) << 4) | packet[1]) << 2;
		/* byte 2: ay7 ay6 ay5 ay4 ay3 ay2 ay1 ay0 */
		y1 = etd->y_max -
			((((packet[0] & 0x20) << 3) | packet[2]) << 2);
		/*
		 * byte 3:  .   .  by8 bx8  .   .   .   .
		 * byte 4: bx7 bx6 bx5 bx4 bx3 bx2 bx1 bx0
		 */
		x2 = (((packet[3] & 0x10) << 4) | packet[4]) << 2;
		/* byte 5: by7 by8 by5 by4 by3 by2 by1 by0 */
		y2 = etd->y_max -
			((((packet[3] & 0x20) << 3) | packet[5]) << 2);

		/* Unknown so just report sensible values */
		pres = 127;
		width = 7;
		अवरोध;
	पूर्ण

	input_report_key(dev, BTN_TOUCH, fingers != 0);
	अगर (fingers != 0) अणु
		input_report_असल(dev, ABS_X, x1);
		input_report_असल(dev, ABS_Y, y1);
	पूर्ण
	elantech_report_semi_mt_data(dev, fingers, x1, y1, x2, y2);
	input_report_key(dev, BTN_TOOL_FINGER, fingers == 1);
	input_report_key(dev, BTN_TOOL_DOUBLETAP, fingers == 2);
	input_report_key(dev, BTN_TOOL_TRIPLETAP, fingers == 3);
	input_report_key(dev, BTN_TOOL_QUADTAP, fingers == 4);
	psmouse_report_standard_buttons(dev, packet[0]);
	अगर (etd->info.reports_pressure) अणु
		input_report_असल(dev, ABS_PRESSURE, pres);
		input_report_असल(dev, ABS_TOOL_WIDTH, width);
	पूर्ण

	input_sync(dev);
पूर्ण

अटल व्योम elantech_report_trackpoपूर्णांक(काष्ठा psmouse *psmouse,
				       पूर्णांक packet_type)
अणु
	/*
	 * byte 0:  0   0  sx  sy   0   M   R   L
	 * byte 1:~sx   0   0   0   0   0   0   0
	 * byte 2:~sy   0   0   0   0   0   0   0
	 * byte 3:  0   0 ~sy ~sx   0   1   1   0
	 * byte 4: x7  x6  x5  x4  x3  x2  x1  x0
	 * byte 5: y7  y6  y5  y4  y3  y2  y1  y0
	 *
	 * x and y are written in two's complement spपढ़ो
	 * over 9 bits with sx/sy the relative top bit and
	 * x7..x0 and y7..y0 the lower bits.
	 * The sign of y is opposite to what the input driver
	 * expects क्रम a relative movement
	 */

	काष्ठा elantech_data *etd = psmouse->निजी;
	काष्ठा input_dev *tp_dev = etd->tp_dev;
	अचिन्हित अक्षर *packet = psmouse->packet;
	पूर्णांक x, y;
	u32 t;

	t = get_unaligned_le32(&packet[0]);

	चयन (t & ~7U) अणु
	हाल 0x06000030U:
	हाल 0x16008020U:
	हाल 0x26800010U:
	हाल 0x36808000U:
		x = packet[4] - (पूर्णांक)((packet[1]^0x80) << 1);
		y = (पूर्णांक)((packet[2]^0x80) << 1) - packet[5];

		psmouse_report_standard_buttons(tp_dev, packet[0]);

		input_report_rel(tp_dev, REL_X, x);
		input_report_rel(tp_dev, REL_Y, y);

		input_sync(tp_dev);

		अवरोध;

	शेष:
		/* Dump unexpected packet sequences अगर debug=1 (शेष) */
		अगर (etd->info.debug == 1)
			elantech_packet_dump(psmouse);

		अवरोध;
	पूर्ण
पूर्ण

/*
 * Interpret complete data packets and report असलolute mode input events क्रम
 * hardware version 3. (12 byte packets क्रम two fingers)
 */
अटल व्योम elantech_report_असलolute_v3(काष्ठा psmouse *psmouse,
					पूर्णांक packet_type)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा elantech_data *etd = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;
	अचिन्हित पूर्णांक fingers = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	अचिन्हित पूर्णांक width = 0, pres = 0;

	/* byte 0: n1  n0   .   .   .   .   R   L */
	fingers = (packet[0] & 0xc0) >> 6;

	चयन (fingers) अणु
	हाल 3:
	हाल 1:
		/*
		 * byte 1:  .   .   .   .  x11 x10 x9  x8
		 * byte 2: x7  x6  x5  x4  x4  x2  x1  x0
		 */
		x1 = ((packet[1] & 0x0f) << 8) | packet[2];
		/*
		 * byte 4:  .   .   .   .  y11 y10 y9  y8
		 * byte 5: y7  y6  y5  y4  y3  y2  y1  y0
		 */
		y1 = etd->y_max - (((packet[4] & 0x0f) << 8) | packet[5]);
		अवरोध;

	हाल 2:
		अगर (packet_type == PACKET_V3_HEAD) अणु
			/*
			 * byte 1:   .    .    .    .  ax11 ax10 ax9  ax8
			 * byte 2: ax7  ax6  ax5  ax4  ax3  ax2  ax1  ax0
			 */
			etd->mt[0].x = ((packet[1] & 0x0f) << 8) | packet[2];
			/*
			 * byte 4:   .    .    .    .  ay11 ay10 ay9  ay8
			 * byte 5: ay7  ay6  ay5  ay4  ay3  ay2  ay1  ay0
			 */
			etd->mt[0].y = etd->y_max -
				(((packet[4] & 0x0f) << 8) | packet[5]);
			/*
			 * रुको क्रम next packet
			 */
			वापस;
		पूर्ण

		/* packet_type == PACKET_V3_TAIL */
		x1 = etd->mt[0].x;
		y1 = etd->mt[0].y;
		x2 = ((packet[1] & 0x0f) << 8) | packet[2];
		y2 = etd->y_max - (((packet[4] & 0x0f) << 8) | packet[5]);
		अवरोध;
	पूर्ण

	pres = (packet[1] & 0xf0) | ((packet[4] & 0xf0) >> 4);
	width = ((packet[0] & 0x30) >> 2) | ((packet[3] & 0x30) >> 4);

	input_report_key(dev, BTN_TOUCH, fingers != 0);
	अगर (fingers != 0) अणु
		input_report_असल(dev, ABS_X, x1);
		input_report_असल(dev, ABS_Y, y1);
	पूर्ण
	elantech_report_semi_mt_data(dev, fingers, x1, y1, x2, y2);
	input_report_key(dev, BTN_TOOL_FINGER, fingers == 1);
	input_report_key(dev, BTN_TOOL_DOUBLETAP, fingers == 2);
	input_report_key(dev, BTN_TOOL_TRIPLETAP, fingers == 3);

	/* For clickpads map both buttons to BTN_LEFT */
	अगर (elantech_is_buttonpad(&etd->info))
		input_report_key(dev, BTN_LEFT, packet[0] & 0x03);
	अन्यथा
		psmouse_report_standard_buttons(dev, packet[0]);

	input_report_असल(dev, ABS_PRESSURE, pres);
	input_report_असल(dev, ABS_TOOL_WIDTH, width);

	input_sync(dev);
पूर्ण

अटल व्योम elantech_input_sync_v4(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा elantech_data *etd = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;

	/* For clickpads map both buttons to BTN_LEFT */
	अगर (elantech_is_buttonpad(&etd->info))
		input_report_key(dev, BTN_LEFT, packet[0] & 0x03);
	अन्यथा
		psmouse_report_standard_buttons(dev, packet[0]);

	input_mt_report_poपूर्णांकer_emulation(dev, true);
	input_sync(dev);
पूर्ण

अटल व्योम process_packet_status_v4(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	अचिन्हित अक्षर *packet = psmouse->packet;
	अचिन्हित fingers;
	पूर्णांक i;

	/* notअगरy finger state change */
	fingers = packet[1] & 0x1f;
	क्रम (i = 0; i < ETP_MAX_FINGERS; i++) अणु
		अगर ((fingers & (1 << i)) == 0) अणु
			input_mt_slot(dev, i);
			input_mt_report_slot_state(dev, MT_TOOL_FINGER, false);
		पूर्ण
	पूर्ण

	elantech_input_sync_v4(psmouse);
पूर्ण

अटल व्योम process_packet_head_v4(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा elantech_data *etd = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;
	पूर्णांक id = ((packet[3] & 0xe0) >> 5) - 1;
	पूर्णांक pres, traces;

	अगर (id < 0)
		वापस;

	etd->mt[id].x = ((packet[1] & 0x0f) << 8) | packet[2];
	etd->mt[id].y = etd->y_max - (((packet[4] & 0x0f) << 8) | packet[5]);
	pres = (packet[1] & 0xf0) | ((packet[4] & 0xf0) >> 4);
	traces = (packet[0] & 0xf0) >> 4;

	input_mt_slot(dev, id);
	input_mt_report_slot_state(dev, MT_TOOL_FINGER, true);

	input_report_असल(dev, ABS_MT_POSITION_X, etd->mt[id].x);
	input_report_असल(dev, ABS_MT_POSITION_Y, etd->mt[id].y);
	input_report_असल(dev, ABS_MT_PRESSURE, pres);
	input_report_असल(dev, ABS_MT_TOUCH_MAJOR, traces * etd->width);
	/* report this क्रम backwards compatibility */
	input_report_असल(dev, ABS_TOOL_WIDTH, traces);

	elantech_input_sync_v4(psmouse);
पूर्ण

अटल व्योम process_packet_motion_v4(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा elantech_data *etd = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;
	पूर्णांक weight, delta_x1 = 0, delta_y1 = 0, delta_x2 = 0, delta_y2 = 0;
	पूर्णांक id, sid;

	id = ((packet[0] & 0xe0) >> 5) - 1;
	अगर (id < 0)
		वापस;

	sid = ((packet[3] & 0xe0) >> 5) - 1;
	weight = (packet[0] & 0x10) ? ETP_WEIGHT_VALUE : 1;
	/*
	 * Motion packets give us the delta of x, y values of specअगरic fingers,
	 * but in two's complement. Let the compiler करो the conversion क्रम us.
	 * Also _enlarge_ the numbers to पूर्णांक, in हाल of overflow.
	 */
	delta_x1 = (चिन्हित अक्षर)packet[1];
	delta_y1 = (चिन्हित अक्षर)packet[2];
	delta_x2 = (चिन्हित अक्षर)packet[4];
	delta_y2 = (चिन्हित अक्षर)packet[5];

	etd->mt[id].x += delta_x1 * weight;
	etd->mt[id].y -= delta_y1 * weight;
	input_mt_slot(dev, id);
	input_report_असल(dev, ABS_MT_POSITION_X, etd->mt[id].x);
	input_report_असल(dev, ABS_MT_POSITION_Y, etd->mt[id].y);

	अगर (sid >= 0) अणु
		etd->mt[sid].x += delta_x2 * weight;
		etd->mt[sid].y -= delta_y2 * weight;
		input_mt_slot(dev, sid);
		input_report_असल(dev, ABS_MT_POSITION_X, etd->mt[sid].x);
		input_report_असल(dev, ABS_MT_POSITION_Y, etd->mt[sid].y);
	पूर्ण

	elantech_input_sync_v4(psmouse);
पूर्ण

अटल व्योम elantech_report_असलolute_v4(काष्ठा psmouse *psmouse,
					पूर्णांक packet_type)
अणु
	चयन (packet_type) अणु
	हाल PACKET_V4_STATUS:
		process_packet_status_v4(psmouse);
		अवरोध;

	हाल PACKET_V4_HEAD:
		process_packet_head_v4(psmouse);
		अवरोध;

	हाल PACKET_V4_MOTION:
		process_packet_motion_v4(psmouse);
		अवरोध;

	हाल PACKET_UNKNOWN:
	शेष:
		/* impossible to get here */
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक elantech_packet_check_v1(काष्ठा psmouse *psmouse)
अणु
	काष्ठा elantech_data *etd = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;
	अचिन्हित अक्षर p1, p2, p3;

	/* Parity bits are placed dअगरferently */
	अगर (etd->info.fw_version < 0x020000) अणु
		/* byte 0:  D   U  p1  p2   1  p3   R   L */
		p1 = (packet[0] & 0x20) >> 5;
		p2 = (packet[0] & 0x10) >> 4;
	पूर्ण अन्यथा अणु
		/* byte 0: n1  n0  p2  p1   1  p3   R   L */
		p1 = (packet[0] & 0x10) >> 4;
		p2 = (packet[0] & 0x20) >> 5;
	पूर्ण

	p3 = (packet[0] & 0x04) >> 2;

	वापस etd->parity[packet[1]] == p1 &&
	       etd->parity[packet[2]] == p2 &&
	       etd->parity[packet[3]] == p3;
पूर्ण

अटल पूर्णांक elantech_debounce_check_v2(काष्ठा psmouse *psmouse)
अणु
        /*
         * When we encounter packet that matches this exactly, it means the
         * hardware is in debounce status. Just ignore the whole packet.
         */
	अटल स्थिर u8 debounce_packet[] = अणु
		0x84, 0xff, 0xff, 0x02, 0xff, 0xff
	पूर्ण;
        अचिन्हित अक्षर *packet = psmouse->packet;

        वापस !स_भेद(packet, debounce_packet, माप(debounce_packet));
पूर्ण

अटल पूर्णांक elantech_packet_check_v2(काष्ठा psmouse *psmouse)
अणु
	काष्ठा elantech_data *etd = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;

	/*
	 * V2 hardware has two flavors. Older ones that करो not report pressure,
	 * and newer ones that reports pressure and width. With newer ones, all
	 * packets (1, 2, 3 finger touch) have the same स्थिरant bits. With
	 * older ones, 1/3 finger touch packets and 2 finger touch packets
	 * have dअगरferent स्थिरant bits.
	 * With all three हालs, अगर the स्थिरant bits are not exactly what I
	 * expected, I consider them invalid.
	 */
	अगर (etd->info.reports_pressure)
		वापस (packet[0] & 0x0c) == 0x04 &&
		       (packet[3] & 0x0f) == 0x02;

	अगर ((packet[0] & 0xc0) == 0x80)
		वापस (packet[0] & 0x0c) == 0x0c &&
		       (packet[3] & 0x0e) == 0x08;

	वापस (packet[0] & 0x3c) == 0x3c &&
	       (packet[1] & 0xf0) == 0x00 &&
	       (packet[3] & 0x3e) == 0x38 &&
	       (packet[4] & 0xf0) == 0x00;
पूर्ण

/*
 * We check the स्थिरant bits to determine what packet type we get,
 * so packet checking is mandatory क्रम v3 and later hardware.
 */
अटल पूर्णांक elantech_packet_check_v3(काष्ठा psmouse *psmouse)
अणु
	काष्ठा elantech_data *etd = psmouse->निजी;
	अटल स्थिर u8 debounce_packet[] = अणु
		0xc4, 0xff, 0xff, 0x02, 0xff, 0xff
	पूर्ण;
	अचिन्हित अक्षर *packet = psmouse->packet;

	/*
	 * check debounce first, it has the same signature in byte 0
	 * and byte 3 as PACKET_V3_HEAD.
	 */
	अगर (!स_भेद(packet, debounce_packet, माप(debounce_packet)))
		वापस PACKET_DEBOUNCE;

	/*
	 * If the hardware flag 'crc_enabled' is set the packets have
	 * dअगरferent signatures.
	 */
	अगर (etd->info.crc_enabled) अणु
		अगर ((packet[3] & 0x09) == 0x08)
			वापस PACKET_V3_HEAD;

		अगर ((packet[3] & 0x09) == 0x09)
			वापस PACKET_V3_TAIL;
	पूर्ण अन्यथा अणु
		अगर ((packet[0] & 0x0c) == 0x04 && (packet[3] & 0xcf) == 0x02)
			वापस PACKET_V3_HEAD;

		अगर ((packet[0] & 0x0c) == 0x0c && (packet[3] & 0xce) == 0x0c)
			वापस PACKET_V3_TAIL;
		अगर ((packet[3] & 0x0f) == 0x06)
			वापस PACKET_TRACKPOINT;
	पूर्ण

	वापस PACKET_UNKNOWN;
पूर्ण

अटल पूर्णांक elantech_packet_check_v4(काष्ठा psmouse *psmouse)
अणु
	काष्ठा elantech_data *etd = psmouse->निजी;
	अचिन्हित अक्षर *packet = psmouse->packet;
	अचिन्हित अक्षर packet_type = packet[3] & 0x03;
	अचिन्हित पूर्णांक ic_version;
	bool sanity_check;

	अगर (etd->tp_dev && (packet[3] & 0x0f) == 0x06)
		वापस PACKET_TRACKPOINT;

	/* This represents the version of IC body. */
	ic_version = (etd->info.fw_version & 0x0f0000) >> 16;

	/*
	 * Sanity check based on the स्थिरant bits of a packet.
	 * The स्थिरant bits change depending on the value of
	 * the hardware flag 'crc_enabled' and the version of
	 * the IC body, but are the same क्रम every packet,
	 * regardless of the type.
	 */
	अगर (etd->info.crc_enabled)
		sanity_check = ((packet[3] & 0x08) == 0x00);
	अन्यथा अगर (ic_version == 7 && etd->info.samples[1] == 0x2A)
		sanity_check = ((packet[3] & 0x1c) == 0x10);
	अन्यथा
		sanity_check = ((packet[0] & 0x08) == 0x00 &&
				(packet[3] & 0x1c) == 0x10);

	अगर (!sanity_check)
		वापस PACKET_UNKNOWN;

	चयन (packet_type) अणु
	हाल 0:
		वापस PACKET_V4_STATUS;

	हाल 1:
		वापस PACKET_V4_HEAD;

	हाल 2:
		वापस PACKET_V4_MOTION;
	पूर्ण

	वापस PACKET_UNKNOWN;
पूर्ण

/*
 * Process byte stream from mouse and handle complete packets
 */
अटल psmouse_ret_t elantech_process_byte(काष्ठा psmouse *psmouse)
अणु
	काष्ठा elantech_data *etd = psmouse->निजी;
	पूर्णांक packet_type;

	अगर (psmouse->pktcnt < psmouse->pktsize)
		वापस PSMOUSE_GOOD_DATA;

	अगर (etd->info.debug > 1)
		elantech_packet_dump(psmouse);

	चयन (etd->info.hw_version) अणु
	हाल 1:
		अगर (etd->info.paritycheck && !elantech_packet_check_v1(psmouse))
			वापस PSMOUSE_BAD_DATA;

		elantech_report_असलolute_v1(psmouse);
		अवरोध;

	हाल 2:
		/* ignore debounce */
		अगर (elantech_debounce_check_v2(psmouse))
			वापस PSMOUSE_FULL_PACKET;

		अगर (etd->info.paritycheck && !elantech_packet_check_v2(psmouse))
			वापस PSMOUSE_BAD_DATA;

		elantech_report_असलolute_v2(psmouse);
		अवरोध;

	हाल 3:
		packet_type = elantech_packet_check_v3(psmouse);
		चयन (packet_type) अणु
		हाल PACKET_UNKNOWN:
			वापस PSMOUSE_BAD_DATA;

		हाल PACKET_DEBOUNCE:
			/* ignore debounce */
			अवरोध;

		हाल PACKET_TRACKPOINT:
			elantech_report_trackpoपूर्णांक(psmouse, packet_type);
			अवरोध;

		शेष:
			elantech_report_असलolute_v3(psmouse, packet_type);
			अवरोध;
		पूर्ण

		अवरोध;

	हाल 4:
		packet_type = elantech_packet_check_v4(psmouse);
		चयन (packet_type) अणु
		हाल PACKET_UNKNOWN:
			वापस PSMOUSE_BAD_DATA;

		हाल PACKET_TRACKPOINT:
			elantech_report_trackpoपूर्णांक(psmouse, packet_type);
			अवरोध;

		शेष:
			elantech_report_असलolute_v4(psmouse, packet_type);
			अवरोध;
		पूर्ण

		अवरोध;
	पूर्ण

	वापस PSMOUSE_FULL_PACKET;
पूर्ण

/*
 * This ग_लिखोs the reg_07 value again to the hardware at the end of every
 * set_rate call because the रेजिस्टर loses its value. reg_07 allows setting
 * असलolute mode on v4 hardware
 */
अटल व्योम elantech_set_rate_restore_reg_07(काष्ठा psmouse *psmouse,
		अचिन्हित पूर्णांक rate)
अणु
	काष्ठा elantech_data *etd = psmouse->निजी;

	etd->original_set_rate(psmouse, rate);
	अगर (elantech_ग_लिखो_reg(psmouse, 0x07, etd->reg_07))
		psmouse_err(psmouse, "restoring reg_07 failed\n");
पूर्ण

/*
 * Put the touchpad पूर्णांकo असलolute mode
 */
अटल पूर्णांक elantech_set_असलolute_mode(काष्ठा psmouse *psmouse)
अणु
	काष्ठा elantech_data *etd = psmouse->निजी;
	अचिन्हित अक्षर val;
	पूर्णांक tries = ETP_READ_BACK_TRIES;
	पूर्णांक rc = 0;

	चयन (etd->info.hw_version) अणु
	हाल 1:
		etd->reg_10 = 0x16;
		etd->reg_11 = 0x8f;
		अगर (elantech_ग_लिखो_reg(psmouse, 0x10, etd->reg_10) ||
		    elantech_ग_लिखो_reg(psmouse, 0x11, etd->reg_11)) अणु
			rc = -1;
		पूर्ण
		अवरोध;

	हाल 2:
					/* Winकरोws driver values */
		etd->reg_10 = 0x54;
		etd->reg_11 = 0x88;	/* 0x8a */
		etd->reg_21 = 0x60;	/* 0x00 */
		अगर (elantech_ग_लिखो_reg(psmouse, 0x10, etd->reg_10) ||
		    elantech_ग_लिखो_reg(psmouse, 0x11, etd->reg_11) ||
		    elantech_ग_लिखो_reg(psmouse, 0x21, etd->reg_21)) अणु
			rc = -1;
		पूर्ण
		अवरोध;

	हाल 3:
		अगर (etd->info.set_hw_resolution)
			etd->reg_10 = 0x0b;
		अन्यथा
			etd->reg_10 = 0x01;

		अगर (elantech_ग_लिखो_reg(psmouse, 0x10, etd->reg_10))
			rc = -1;

		अवरोध;

	हाल 4:
		etd->reg_07 = 0x01;
		अगर (elantech_ग_लिखो_reg(psmouse, 0x07, etd->reg_07))
			rc = -1;

		जाओ skip_पढ़ोback_reg_10; /* v4 has no reg 0x10 to पढ़ो */
	पूर्ण

	अगर (rc == 0) अणु
		/*
		 * Read back reg 0x10. For hardware version 1 we must make
		 * sure the असलolute mode bit is set. For hardware version 2
		 * the touchpad is probably initializing and not पढ़ोy until
		 * we पढ़ो back the value we just wrote.
		 */
		करो अणु
			rc = elantech_पढ़ो_reg(psmouse, 0x10, &val);
			अगर (rc == 0)
				अवरोध;
			tries--;
			elantech_debug("retrying read (%d).\n", tries);
			msleep(ETP_READ_BACK_DELAY);
		पूर्ण जबतक (tries > 0);

		अगर (rc) अणु
			psmouse_err(psmouse,
				    "failed to read back register 0x10.\n");
		पूर्ण अन्यथा अगर (etd->info.hw_version == 1 &&
			   !(val & ETP_R10_ABSOLUTE_MODE)) अणु
			psmouse_err(psmouse,
				    "touchpad refuses to switch to absolute mode.\n");
			rc = -1;
		पूर्ण
	पूर्ण

 skip_पढ़ोback_reg_10:
	अगर (rc)
		psmouse_err(psmouse, "failed to initialise registers.\n");

	वापस rc;
पूर्ण

/*
 * (value from firmware) * 10 + 790 = dpi
 * we also have to convert dpi to करोts/mm (*10/254 to aव्योम भग्नing poपूर्णांक)
 */
अटल अचिन्हित पूर्णांक elantech_convert_res(अचिन्हित पूर्णांक val)
अणु
	वापस (val * 10 + 790) * 10 / 254;
पूर्ण

अटल पूर्णांक elantech_get_resolution_v4(काष्ठा psmouse *psmouse,
				      अचिन्हित पूर्णांक *x_res,
				      अचिन्हित पूर्णांक *y_res,
				      अचिन्हित पूर्णांक *bus)
अणु
	अचिन्हित अक्षर param[3];

	अगर (elantech_send_cmd(psmouse, ETP_RESOLUTION_QUERY, param))
		वापस -1;

	*x_res = elantech_convert_res(param[1] & 0x0f);
	*y_res = elantech_convert_res((param[1] & 0xf0) >> 4);
	*bus = param[2];

	वापस 0;
पूर्ण

अटल व्योम elantech_set_buttonpad_prop(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा elantech_data *etd = psmouse->निजी;

	अगर (elantech_is_buttonpad(&etd->info)) अणु
		__set_bit(INPUT_PROP_BUTTONPAD, dev->propbit);
		__clear_bit(BTN_RIGHT, dev->keybit);
	पूर्ण
पूर्ण

/*
 * Some hw_version 4 models करो have a middle button
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id elantech_dmi_has_middle_button[] = अणु
#अगर defined(CONFIG_DMI) && defined(CONFIG_X86)
	अणु
		/* Fujitsu H730 has a middle button */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CELSIUS H730"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu H760 also has a middle button */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CELSIUS H760"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu H780 also has a middle button */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CELSIUS H780"),
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

/*
 * Set the appropriate event bits क्रम the input subप्रणाली
 */
अटल पूर्णांक elantech_set_input_params(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा elantech_data *etd = psmouse->निजी;
	काष्ठा elantech_device_info *info = &etd->info;
	अचिन्हित पूर्णांक x_min = info->x_min, y_min = info->y_min,
		     x_max = info->x_max, y_max = info->y_max,
		     width = info->width;

	__set_bit(INPUT_PROP_POINTER, dev->propbit);
	__set_bit(EV_KEY, dev->evbit);
	__set_bit(EV_ABS, dev->evbit);
	__clear_bit(EV_REL, dev->evbit);

	__set_bit(BTN_LEFT, dev->keybit);
	अगर (info->has_middle_button)
		__set_bit(BTN_MIDDLE, dev->keybit);
	__set_bit(BTN_RIGHT, dev->keybit);

	__set_bit(BTN_TOUCH, dev->keybit);
	__set_bit(BTN_TOOL_FINGER, dev->keybit);
	__set_bit(BTN_TOOL_DOUBLETAP, dev->keybit);
	__set_bit(BTN_TOOL_TRIPLETAP, dev->keybit);

	चयन (info->hw_version) अणु
	हाल 1:
		/* Rocker button */
		अगर (info->fw_version < 0x020000 &&
		    (info->capabilities[0] & ETP_CAP_HAS_ROCKER)) अणु
			__set_bit(BTN_FORWARD, dev->keybit);
			__set_bit(BTN_BACK, dev->keybit);
		पूर्ण
		input_set_असल_params(dev, ABS_X, x_min, x_max, 0, 0);
		input_set_असल_params(dev, ABS_Y, y_min, y_max, 0, 0);
		अवरोध;

	हाल 2:
		__set_bit(BTN_TOOL_QUADTAP, dev->keybit);
		__set_bit(INPUT_PROP_SEMI_MT, dev->propbit);
		fallthrough;
	हाल 3:
		अगर (info->hw_version == 3)
			elantech_set_buttonpad_prop(psmouse);
		input_set_असल_params(dev, ABS_X, x_min, x_max, 0, 0);
		input_set_असल_params(dev, ABS_Y, y_min, y_max, 0, 0);
		अगर (info->reports_pressure) अणु
			input_set_असल_params(dev, ABS_PRESSURE, ETP_PMIN_V2,
					     ETP_PMAX_V2, 0, 0);
			input_set_असल_params(dev, ABS_TOOL_WIDTH, ETP_WMIN_V2,
					     ETP_WMAX_V2, 0, 0);
		पूर्ण
		input_mt_init_slots(dev, 2, INPUT_MT_SEMI_MT);
		input_set_असल_params(dev, ABS_MT_POSITION_X, x_min, x_max, 0, 0);
		input_set_असल_params(dev, ABS_MT_POSITION_Y, y_min, y_max, 0, 0);
		अवरोध;

	हाल 4:
		elantech_set_buttonpad_prop(psmouse);
		__set_bit(BTN_TOOL_QUADTAP, dev->keybit);
		/* For X to recognize me as touchpad. */
		input_set_असल_params(dev, ABS_X, x_min, x_max, 0, 0);
		input_set_असल_params(dev, ABS_Y, y_min, y_max, 0, 0);
		/*
		 * range of pressure and width is the same as v2,
		 * report ABS_PRESSURE, ABS_TOOL_WIDTH क्रम compatibility.
		 */
		input_set_असल_params(dev, ABS_PRESSURE, ETP_PMIN_V2,
				     ETP_PMAX_V2, 0, 0);
		input_set_असल_params(dev, ABS_TOOL_WIDTH, ETP_WMIN_V2,
				     ETP_WMAX_V2, 0, 0);
		/* Multitouch capable pad, up to 5 fingers. */
		input_mt_init_slots(dev, ETP_MAX_FINGERS, 0);
		input_set_असल_params(dev, ABS_MT_POSITION_X, x_min, x_max, 0, 0);
		input_set_असल_params(dev, ABS_MT_POSITION_Y, y_min, y_max, 0, 0);
		input_set_असल_params(dev, ABS_MT_PRESSURE, ETP_PMIN_V2,
				     ETP_PMAX_V2, 0, 0);
		/*
		 * The firmware reports how many trace lines the finger spans,
		 * convert to surface unit as Protocol-B requires.
		 */
		input_set_असल_params(dev, ABS_MT_TOUCH_MAJOR, 0,
				     ETP_WMAX_V2 * width, 0, 0);
		अवरोध;
	पूर्ण

	input_असल_set_res(dev, ABS_X, info->x_res);
	input_असल_set_res(dev, ABS_Y, info->y_res);
	अगर (info->hw_version > 1) अणु
		input_असल_set_res(dev, ABS_MT_POSITION_X, info->x_res);
		input_असल_set_res(dev, ABS_MT_POSITION_Y, info->y_res);
	पूर्ण

	etd->y_max = y_max;
	etd->width = width;

	वापस 0;
पूर्ण

काष्ठा elantech_attr_data अणु
	माप_प्रकार		field_offset;
	अचिन्हित अक्षर	reg;
पूर्ण;

/*
 * Display a रेजिस्टर value by पढ़ोing a sysfs entry
 */
अटल sमाप_प्रकार elantech_show_पूर्णांक_attr(काष्ठा psmouse *psmouse, व्योम *data,
					अक्षर *buf)
अणु
	काष्ठा elantech_data *etd = psmouse->निजी;
	काष्ठा elantech_attr_data *attr = data;
	अचिन्हित अक्षर *reg = (अचिन्हित अक्षर *) etd + attr->field_offset;
	पूर्णांक rc = 0;

	अगर (attr->reg)
		rc = elantech_पढ़ो_reg(psmouse, attr->reg, reg);

	वापस प्र_लिखो(buf, "0x%02x\n", (attr->reg && rc) ? -1 : *reg);
पूर्ण

/*
 * Write a रेजिस्टर value by writing a sysfs entry
 */
अटल sमाप_प्रकार elantech_set_पूर्णांक_attr(काष्ठा psmouse *psmouse,
				     व्योम *data, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा elantech_data *etd = psmouse->निजी;
	काष्ठा elantech_attr_data *attr = data;
	अचिन्हित अक्षर *reg = (अचिन्हित अक्षर *) etd + attr->field_offset;
	अचिन्हित अक्षर value;
	पूर्णांक err;

	err = kstrtou8(buf, 16, &value);
	अगर (err)
		वापस err;

	/* Do we need to preserve some bits क्रम version 2 hardware too? */
	अगर (etd->info.hw_version == 1) अणु
		अगर (attr->reg == 0x10)
			/* Force असलolute mode always on */
			value |= ETP_R10_ABSOLUTE_MODE;
		अन्यथा अगर (attr->reg == 0x11)
			/* Force 4 byte mode always on */
			value |= ETP_R11_4_BYTE_MODE;
	पूर्ण

	अगर (!attr->reg || elantech_ग_लिखो_reg(psmouse, attr->reg, value) == 0)
		*reg = value;

	वापस count;
पूर्ण

#घोषणा ELANTECH_INT_ATTR(_name, _रेजिस्टर)				\
	अटल काष्ठा elantech_attr_data elantech_attr_##_name = अणु	\
		.field_offset = दुरत्व(काष्ठा elantech_data, _name),	\
		.reg = _रेजिस्टर,					\
	पूर्ण;								\
	PSMOUSE_DEFINE_ATTR(_name, 0644,				\
			    &elantech_attr_##_name,			\
			    elantech_show_पूर्णांक_attr,			\
			    elantech_set_पूर्णांक_attr)

#घोषणा ELANTECH_INFO_ATTR(_name)					       \
	अटल काष्ठा elantech_attr_data elantech_attr_##_name = अणु	       \
		.field_offset = दुरत्व(काष्ठा elantech_data, info) +	       \
				दुरत्व(काष्ठा elantech_device_info, _name),  \
		.reg = 0,						       \
	पूर्ण;								       \
	PSMOUSE_DEFINE_ATTR(_name, 0644,				       \
			    &elantech_attr_##_name,			       \
			    elantech_show_पूर्णांक_attr,			       \
			    elantech_set_पूर्णांक_attr)

ELANTECH_INT_ATTR(reg_07, 0x07);
ELANTECH_INT_ATTR(reg_10, 0x10);
ELANTECH_INT_ATTR(reg_11, 0x11);
ELANTECH_INT_ATTR(reg_20, 0x20);
ELANTECH_INT_ATTR(reg_21, 0x21);
ELANTECH_INT_ATTR(reg_22, 0x22);
ELANTECH_INT_ATTR(reg_23, 0x23);
ELANTECH_INT_ATTR(reg_24, 0x24);
ELANTECH_INT_ATTR(reg_25, 0x25);
ELANTECH_INT_ATTR(reg_26, 0x26);
ELANTECH_INFO_ATTR(debug);
ELANTECH_INFO_ATTR(paritycheck);
ELANTECH_INFO_ATTR(crc_enabled);

अटल काष्ठा attribute *elantech_attrs[] = अणु
	&psmouse_attr_reg_07.dattr.attr,
	&psmouse_attr_reg_10.dattr.attr,
	&psmouse_attr_reg_11.dattr.attr,
	&psmouse_attr_reg_20.dattr.attr,
	&psmouse_attr_reg_21.dattr.attr,
	&psmouse_attr_reg_22.dattr.attr,
	&psmouse_attr_reg_23.dattr.attr,
	&psmouse_attr_reg_24.dattr.attr,
	&psmouse_attr_reg_25.dattr.attr,
	&psmouse_attr_reg_26.dattr.attr,
	&psmouse_attr_debug.dattr.attr,
	&psmouse_attr_paritycheck.dattr.attr,
	&psmouse_attr_crc_enabled.dattr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group elantech_attr_group = अणु
	.attrs = elantech_attrs,
पूर्ण;

अटल bool elantech_is_signature_valid(स्थिर अचिन्हित अक्षर *param)
अणु
	अटल स्थिर अचिन्हित अक्षर rates[] = अणु 200, 100, 80, 60, 40, 20, 10 पूर्ण;
	पूर्णांक i;

	अगर (param[0] == 0)
		वापस false;

	अगर (param[1] == 0)
		वापस true;

	/*
	 * Some hw_version >= 4 models have a revision higher then 20. Meaning
	 * that param[2] may be 10 or 20, skip the rates check क्रम these.
	 */
	अगर ((param[0] & 0x0f) >= 0x06 && (param[1] & 0xaf) == 0x0f &&
	    param[2] < 40)
		वापस true;

	क्रम (i = 0; i < ARRAY_SIZE(rates); i++)
		अगर (param[2] == rates[i])
			वापस false;

	वापस true;
पूर्ण

/*
 * Use magic knock to detect Elantech touchpad
 */
पूर्णांक elantech_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	अचिन्हित अक्षर param[3];

	ps2_command(ps2dev, शून्य, PSMOUSE_CMD_RESET_DIS);

	अगर (ps2_command(ps2dev,  शून्य, PSMOUSE_CMD_DISABLE) ||
	    ps2_command(ps2dev,  शून्य, PSMOUSE_CMD_SETSCALE11) ||
	    ps2_command(ps2dev,  शून्य, PSMOUSE_CMD_SETSCALE11) ||
	    ps2_command(ps2dev,  शून्य, PSMOUSE_CMD_SETSCALE11) ||
	    ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO)) अणु
		psmouse_dbg(psmouse, "sending Elantech magic knock failed.\n");
		वापस -1;
	पूर्ण

	/*
	 * Report this in हाल there are Elantech models that use a dअगरferent
	 * set of magic numbers
	 */
	अगर (param[0] != 0x3c || param[1] != 0x03 ||
	    (param[2] != 0xc8 && param[2] != 0x00)) अणु
		psmouse_dbg(psmouse,
			    "unexpected magic knock result 0x%02x, 0x%02x, 0x%02x.\n",
			    param[0], param[1], param[2]);
		वापस -1;
	पूर्ण

	/*
	 * Query touchpad's firmware version and see अगर it reports known
	 * value to aव्योम mis-detection. Logitech mice are known to respond
	 * to Elantech magic knock and there might be more.
	 */
	अगर (synaptics_send_cmd(psmouse, ETP_FW_VERSION_QUERY, param)) अणु
		psmouse_dbg(psmouse, "failed to query firmware version.\n");
		वापस -1;
	पूर्ण

	psmouse_dbg(psmouse,
		    "Elantech version query result 0x%02x, 0x%02x, 0x%02x.\n",
		    param[0], param[1], param[2]);

	अगर (!elantech_is_signature_valid(param)) अणु
		psmouse_dbg(psmouse,
			    "Probably not a real Elantech touchpad. Aborting.\n");
		वापस -1;
	पूर्ण

	अगर (set_properties) अणु
		psmouse->venकरोr = "Elantech";
		psmouse->name = "Touchpad";
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Clean up sysfs entries when disconnecting
 */
अटल व्योम elantech_disconnect(काष्ठा psmouse *psmouse)
अणु
	काष्ठा elantech_data *etd = psmouse->निजी;

	/*
	 * We might have left a bपढ़ोcrumb when trying to
	 * set up SMbus companion.
	 */
	psmouse_smbus_cleanup(psmouse);

	अगर (etd->tp_dev)
		input_unरेजिस्टर_device(etd->tp_dev);
	sysfs_हटाओ_group(&psmouse->ps2dev.serio->dev.kobj,
			   &elantech_attr_group);
	kमुक्त(psmouse->निजी);
	psmouse->निजी = शून्य;
पूर्ण

/*
 * Put the touchpad back पूर्णांकo असलolute mode when reconnecting
 */
अटल पूर्णांक elantech_reconnect(काष्ठा psmouse *psmouse)
अणु
	psmouse_reset(psmouse);

	अगर (elantech_detect(psmouse, 0))
		वापस -1;

	अगर (elantech_set_असलolute_mode(psmouse)) अणु
		psmouse_err(psmouse,
			    "failed to put touchpad back into absolute mode.\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Some hw_version 4 models करो not work with crc_disabled
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id elantech_dmi_क्रमce_crc_enabled[] = अणु
#अगर defined(CONFIG_DMI) && defined(CONFIG_X86)
	अणु
		/* Fujitsu H730 करोes not work with crc_enabled == 0 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CELSIUS H730"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu H760 करोes not work with crc_enabled == 0 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CELSIUS H760"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu LIFEBOOK E544  करोes not work with crc_enabled == 0 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK E544"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu LIFEBOOK E546  करोes not work with crc_enabled == 0 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK E546"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu LIFEBOOK E547 करोes not work with crc_enabled == 0 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK E547"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu LIFEBOOK E554  करोes not work with crc_enabled == 0 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK E554"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu LIFEBOOK E556 करोes not work with crc_enabled == 0 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK E556"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu LIFEBOOK E557 करोes not work with crc_enabled == 0 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK E557"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu LIFEBOOK U745 करोes not work with crc_enabled == 0 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK U745"),
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

/*
 * Some hw_version 3 models go पूर्णांकo error state when we try to set
 * bit 3 and/or bit 1 of r10.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id no_hw_res_dmi_table[] = अणु
#अगर defined(CONFIG_DMI) && defined(CONFIG_X86)
	अणु
		/* Gigabyte U2442 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GIGABYTE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "U2442"),
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

/*
 * Change Report id 0x5E to 0x5F.
 */
अटल पूर्णांक elantech_change_report_id(काष्ठा psmouse *psmouse)
अणु
	अचिन्हित अक्षर param[2] = अणु 0x10, 0x03 पूर्ण;

	अगर (elantech_ग_लिखो_reg_params(psmouse, 0x7, param) ||
	    elantech_पढ़ो_reg_params(psmouse, 0x7, param) ||
	    param[0] != 0x10 || param[1] != 0x03) अणु
		psmouse_err(psmouse, "Unable to change report ID to 0x5f.\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
/*
 * determine hardware version and set some properties according to it.
 */
अटल पूर्णांक elantech_set_properties(काष्ठा elantech_device_info *info)
अणु
	/* This represents the version of IC body. */
	info->ic_version = (info->fw_version & 0x0f0000) >> 16;

	/* Early version of Elan touchpads करोesn't obey the rule. */
	अगर (info->fw_version < 0x020030 || info->fw_version == 0x020600)
		info->hw_version = 1;
	अन्यथा अणु
		चयन (info->ic_version) अणु
		हाल 2:
		हाल 4:
			info->hw_version = 2;
			अवरोध;
		हाल 5:
			info->hw_version = 3;
			अवरोध;
		हाल 6 ... 15:
			info->hw_version = 4;
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण
	पूर्ण

	/* Get inक्रमmation pattern क्रम hw_version 4 */
	info->pattern = 0x00;
	अगर (info->ic_version == 0x0f && (info->fw_version & 0xff) <= 0x02)
		info->pattern = info->fw_version & 0xff;

	/* decide which send_cmd we're gonna use early */
	info->send_cmd = info->hw_version >= 3 ? elantech_send_cmd :
						 synaptics_send_cmd;

	/* Turn on packet checking by शेष */
	info->paritycheck = 1;

	/*
	 * This firmware suffers from misreporting coordinates when
	 * a touch action starts causing the mouse cursor or scrolled page
	 * to jump. Enable a workaround.
	 */
	info->jumpy_cursor =
		(info->fw_version == 0x020022 || info->fw_version == 0x020600);

	अगर (info->hw_version > 1) अणु
		/* For now show extra debug inक्रमmation */
		info->debug = 1;

		अगर (info->fw_version >= 0x020800)
			info->reports_pressure = true;
	पूर्ण

	/*
	 * The signatures of v3 and v4 packets change depending on the
	 * value of this hardware flag.
	 */
	info->crc_enabled = (info->fw_version & 0x4000) == 0x4000 ||
			     dmi_check_प्रणाली(elantech_dmi_क्रमce_crc_enabled);

	/* Enable real hardware resolution on hw_version 3 ? */
	info->set_hw_resolution = !dmi_check_प्रणाली(no_hw_res_dmi_table);

	वापस 0;
पूर्ण

अटल पूर्णांक elantech_query_info(काष्ठा psmouse *psmouse,
			       काष्ठा elantech_device_info *info)
अणु
	अचिन्हित अक्षर param[3];
	अचिन्हित अक्षर traces;
	अचिन्हित अक्षर ic_body[3];

	स_रखो(info, 0, माप(*info));

	/*
	 * Do the version query again so we can store the result
	 */
	अगर (synaptics_send_cmd(psmouse, ETP_FW_VERSION_QUERY, param)) अणु
		psmouse_err(psmouse, "failed to query firmware version.\n");
		वापस -EINVAL;
	पूर्ण
	info->fw_version = (param[0] << 16) | (param[1] << 8) | param[2];

	अगर (elantech_set_properties(info)) अणु
		psmouse_err(psmouse, "unknown hardware version, aborting...\n");
		वापस -EINVAL;
	पूर्ण
	psmouse_info(psmouse,
		     "assuming hardware version %d (with firmware version 0x%02x%02x%02x)\n",
		     info->hw_version, param[0], param[1], param[2]);

	अगर (info->send_cmd(psmouse, ETP_CAPABILITIES_QUERY,
	    info->capabilities)) अणु
		psmouse_err(psmouse, "failed to query capabilities.\n");
		वापस -EINVAL;
	पूर्ण
	psmouse_info(psmouse,
		     "Synaptics capabilities query result 0x%02x, 0x%02x, 0x%02x.\n",
		     info->capabilities[0], info->capabilities[1],
		     info->capabilities[2]);

	अगर (info->hw_version != 1) अणु
		अगर (info->send_cmd(psmouse, ETP_SAMPLE_QUERY, info->samples)) अणु
			psmouse_err(psmouse, "failed to query sample data\n");
			वापस -EINVAL;
		पूर्ण
		psmouse_info(psmouse,
			     "Elan sample query result %02x, %02x, %02x\n",
			     info->samples[0],
			     info->samples[1],
			     info->samples[2]);
	पूर्ण

	अगर (info->pattern > 0x00 && info->ic_version == 0xf) अणु
		अगर (info->send_cmd(psmouse, ETP_ICBODY_QUERY, ic_body)) अणु
			psmouse_err(psmouse, "failed to query ic body\n");
			वापस -EINVAL;
		पूर्ण
		info->ic_version = be16_to_cpup((__be16 *)ic_body);
		psmouse_info(psmouse,
			     "Elan ic body: %#04x, current fw version: %#02x\n",
			     info->ic_version, ic_body[2]);
	पूर्ण

	info->product_id = be16_to_cpup((__be16 *)info->samples);
	अगर (info->pattern == 0x00)
		info->product_id &= 0xff;

	अगर (info->samples[1] == 0x74 && info->hw_version == 0x03) अणु
		/*
		 * This module has a bug which makes असलolute mode
		 * unusable, so let's abort so we'll be using standard
		 * PS/2 protocol.
		 */
		psmouse_info(psmouse,
			     "absolute mode broken, forcing standard PS/2 protocol\n");
		वापस -ENODEV;
	पूर्ण

	/* The MSB indicates the presence of the trackpoपूर्णांक */
	info->has_trackpoपूर्णांक = (info->capabilities[0] & 0x80) == 0x80;

	अगर (info->has_trackpoपूर्णांक && info->ic_version == 0x0011 &&
	    (info->product_id == 0x08 || info->product_id == 0x09 ||
	     info->product_id == 0x0d || info->product_id == 0x0e)) अणु
		/*
		 * This module has a bug which makes trackpoपूर्णांक in SMBus
		 * mode वापस invalid data unless trackpoपूर्णांक is चयनed
		 * from using 0x5e reports to 0x5f. If we are not able to
		 * make the चयन, let's abort initialization so we'll be
		 * using standard PS/2 protocol.
		 */
		अगर (elantech_change_report_id(psmouse)) अणु
			psmouse_info(psmouse,
				     "Trackpoint report is broken, forcing standard PS/2 protocol\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	info->x_res = 31;
	info->y_res = 31;
	अगर (info->hw_version == 4) अणु
		अगर (elantech_get_resolution_v4(psmouse,
					       &info->x_res,
					       &info->y_res,
					       &info->bus)) अणु
			psmouse_warn(psmouse,
				     "failed to query resolution data.\n");
		पूर्ण
	पूर्ण

	/* query range inक्रमmation */
	चयन (info->hw_version) अणु
	हाल 1:
		info->x_min = ETP_XMIN_V1;
		info->y_min = ETP_YMIN_V1;
		info->x_max = ETP_XMAX_V1;
		info->y_max = ETP_YMAX_V1;
		अवरोध;

	हाल 2:
		अगर (info->fw_version == 0x020800 ||
		    info->fw_version == 0x020b00 ||
		    info->fw_version == 0x020030) अणु
			info->x_min = ETP_XMIN_V2;
			info->y_min = ETP_YMIN_V2;
			info->x_max = ETP_XMAX_V2;
			info->y_max = ETP_YMAX_V2;
		पूर्ण अन्यथा अणु
			पूर्णांक i;
			पूर्णांक fixed_dpi;

			i = (info->fw_version > 0x020800 &&
			     info->fw_version < 0x020900) ? 1 : 2;

			अगर (info->send_cmd(psmouse, ETP_FW_ID_QUERY, param))
				वापस -EINVAL;

			fixed_dpi = param[1] & 0x10;

			अगर (((info->fw_version >> 16) == 0x14) && fixed_dpi) अणु
				अगर (info->send_cmd(psmouse, ETP_SAMPLE_QUERY, param))
					वापस -EINVAL;

				info->x_max = (info->capabilities[1] - i) * param[1] / 2;
				info->y_max = (info->capabilities[2] - i) * param[2] / 2;
			पूर्ण अन्यथा अगर (info->fw_version == 0x040216) अणु
				info->x_max = 819;
				info->y_max = 405;
			पूर्ण अन्यथा अगर (info->fw_version == 0x040219 || info->fw_version == 0x040215) अणु
				info->x_max = 900;
				info->y_max = 500;
			पूर्ण अन्यथा अणु
				info->x_max = (info->capabilities[1] - i) * 64;
				info->y_max = (info->capabilities[2] - i) * 64;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल 3:
		अगर (info->send_cmd(psmouse, ETP_FW_ID_QUERY, param))
			वापस -EINVAL;

		info->x_max = (0x0f & param[0]) << 8 | param[1];
		info->y_max = (0xf0 & param[0]) << 4 | param[2];
		अवरोध;

	हाल 4:
		अगर (info->send_cmd(psmouse, ETP_FW_ID_QUERY, param))
			वापस -EINVAL;

		info->x_max = (0x0f & param[0]) << 8 | param[1];
		info->y_max = (0xf0 & param[0]) << 4 | param[2];
		traces = info->capabilities[1];
		अगर ((traces < 2) || (traces > info->x_max))
			वापस -EINVAL;

		info->width = info->x_max / (traces - 1);

		/* column number of traces */
		info->x_traces = traces;

		/* row number of traces */
		traces = info->capabilities[2];
		अगर ((traces >= 2) && (traces <= info->y_max))
			info->y_traces = traces;

		अवरोध;
	पूर्ण

	/* check क्रम the middle button: DMI matching or new v4 firmwares */
	info->has_middle_button = dmi_check_प्रणाली(elantech_dmi_has_middle_button) ||
				  (ETP_NEW_IC_SMBUS_HOST_NOTIFY(info->fw_version) &&
				   !elantech_is_buttonpad(info));

	वापस 0;
पूर्ण

#अगर defined(CONFIG_MOUSE_PS2_ELANTECH_SMBUS)

/*
 * The newest Elantech device can use a secondary bus (over SMBus) which
 * provides a better bandwidth and allow a better control of the touchpads.
 * This is used to decide अगर we need to use this bus or not.
 */
क्रमागत अणु
	ELANTECH_SMBUS_NOT_SET = -1,
	ELANTECH_SMBUS_OFF,
	ELANTECH_SMBUS_ON,
पूर्ण;

अटल पूर्णांक elantech_smbus = IS_ENABLED(CONFIG_MOUSE_ELAN_I2C_SMBUS) ?
		ELANTECH_SMBUS_NOT_SET : ELANTECH_SMBUS_OFF;
module_param_named(elantech_smbus, elantech_smbus, पूर्णांक, 0644);
MODULE_PARM_DESC(elantech_smbus, "Use a secondary bus for the Elantech device.");

अटल स्थिर अक्षर * स्थिर i2c_blacklist_pnp_ids[] = अणु
	/*
	 * These are known to not be working properly as bits are missing
	 * in elan_i2c.
	 */
	शून्य
पूर्ण;

अटल पूर्णांक elantech_create_smbus(काष्ठा psmouse *psmouse,
				 काष्ठा elantech_device_info *info,
				 bool leave_bपढ़ोcrumbs)
अणु
	काष्ठा property_entry i2c_props[11] = अणुपूर्ण;
	काष्ठा i2c_board_info smbus_board = अणु
		I2C_BOARD_INFO("elan_i2c", 0x15),
		.flags = I2C_CLIENT_HOST_NOTIFY,
	पूर्ण;
	अचिन्हित पूर्णांक idx = 0;

	i2c_props[idx++] = PROPERTY_ENTRY_U32("touchscreen-size-x",
						   info->x_max + 1);
	i2c_props[idx++] = PROPERTY_ENTRY_U32("touchscreen-size-y",
						   info->y_max + 1);
	i2c_props[idx++] = PROPERTY_ENTRY_U32("touchscreen-min-x",
						   info->x_min);
	i2c_props[idx++] = PROPERTY_ENTRY_U32("touchscreen-min-y",
						   info->y_min);
	अगर (info->x_res)
		i2c_props[idx++] = PROPERTY_ENTRY_U32("touchscreen-x-mm",
						      (info->x_max + 1) / info->x_res);
	अगर (info->y_res)
		i2c_props[idx++] = PROPERTY_ENTRY_U32("touchscreen-y-mm",
						      (info->y_max + 1) / info->y_res);

	अगर (info->has_trackpoपूर्णांक)
		i2c_props[idx++] = PROPERTY_ENTRY_BOOL("elan,trackpoint");

	अगर (info->has_middle_button)
		i2c_props[idx++] = PROPERTY_ENTRY_BOOL("elan,middle-button");

	अगर (info->x_traces)
		i2c_props[idx++] = PROPERTY_ENTRY_U32("elan,x_traces",
						      info->x_traces);
	अगर (info->y_traces)
		i2c_props[idx++] = PROPERTY_ENTRY_U32("elan,y_traces",
						      info->y_traces);

	अगर (elantech_is_buttonpad(info))
		i2c_props[idx++] = PROPERTY_ENTRY_BOOL("elan,clickpad");

	smbus_board.fwnode = fwnode_create_software_node(i2c_props, शून्य);
	अगर (IS_ERR(smbus_board.fwnode))
		वापस PTR_ERR(smbus_board.fwnode);

	वापस psmouse_smbus_init(psmouse, &smbus_board, शून्य, 0, false,
				  leave_bपढ़ोcrumbs);
पूर्ण

/*
 * elantech_setup_smbus - called once the PS/2 devices are क्रमागतerated
 * and decides to instantiate a SMBus InterTouch device.
 */
अटल पूर्णांक elantech_setup_smbus(काष्ठा psmouse *psmouse,
				काष्ठा elantech_device_info *info,
				bool leave_bपढ़ोcrumbs)
अणु
	पूर्णांक error;

	अगर (elantech_smbus == ELANTECH_SMBUS_OFF)
		वापस -ENXIO;

	अगर (elantech_smbus == ELANTECH_SMBUS_NOT_SET) अणु
		/*
		 * New ICs are enabled by शेष, unless mentioned in
		 * i2c_blacklist_pnp_ids.
		 * Old ICs are up to the user to decide.
		 */
		अगर (!ETP_NEW_IC_SMBUS_HOST_NOTIFY(info->fw_version) ||
		    psmouse_matches_pnp_id(psmouse, i2c_blacklist_pnp_ids))
			वापस -ENXIO;
	पूर्ण

	psmouse_info(psmouse, "Trying to set up SMBus access\n");

	error = elantech_create_smbus(psmouse, info, leave_bपढ़ोcrumbs);
	अगर (error) अणु
		अगर (error == -EAGAIN)
			psmouse_info(psmouse, "SMbus companion is not ready yet\n");
		अन्यथा
			psmouse_err(psmouse, "unable to create intertouch device\n");

		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool elantech_use_host_notअगरy(काष्ठा psmouse *psmouse,
				     काष्ठा elantech_device_info *info)
अणु
	अगर (ETP_NEW_IC_SMBUS_HOST_NOTIFY(info->fw_version))
		वापस true;

	चयन (info->bus) अणु
	हाल ETP_BUS_PS2_ONLY:
		/* expected हाल */
		अवरोध;
	हाल ETP_BUS_SMB_ALERT_ONLY:
	हाल ETP_BUS_PS2_SMB_ALERT:
		psmouse_dbg(psmouse, "Ignoring SMBus provider through alert protocol.\n");
		अवरोध;
	हाल ETP_BUS_SMB_HST_NTFY_ONLY:
	हाल ETP_BUS_PS2_SMB_HST_NTFY:
		वापस true;
	शेष:
		psmouse_dbg(psmouse,
			    "Ignoring SMBus bus provider %d.\n",
			    info->bus);
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक elantech_init_smbus(काष्ठा psmouse *psmouse)
अणु
	काष्ठा elantech_device_info info;
	पूर्णांक error;

	psmouse_reset(psmouse);

	error = elantech_query_info(psmouse, &info);
	अगर (error)
		जाओ init_fail;

	अगर (info.hw_version < 4) अणु
		error = -ENXIO;
		जाओ init_fail;
	पूर्ण

	वापस elantech_create_smbus(psmouse, &info, false);
 init_fail:
	psmouse_reset(psmouse);
	वापस error;
पूर्ण
#पूर्ण_अगर /* CONFIG_MOUSE_PS2_ELANTECH_SMBUS */

/*
 * Initialize the touchpad and create sysfs entries
 */
अटल पूर्णांक elantech_setup_ps2(काष्ठा psmouse *psmouse,
			      काष्ठा elantech_device_info *info)
अणु
	काष्ठा elantech_data *etd;
	पूर्णांक i;
	पूर्णांक error = -EINVAL;
	काष्ठा input_dev *tp_dev;

	psmouse->निजी = etd = kzalloc(माप(*etd), GFP_KERNEL);
	अगर (!etd)
		वापस -ENOMEM;

	etd->info = *info;

	etd->parity[0] = 1;
	क्रम (i = 1; i < 256; i++)
		etd->parity[i] = etd->parity[i & (i - 1)] ^ 1;

	अगर (elantech_set_असलolute_mode(psmouse)) अणु
		psmouse_err(psmouse,
			    "failed to put touchpad into absolute mode.\n");
		जाओ init_fail;
	पूर्ण

	अगर (info->fw_version == 0x381f17) अणु
		etd->original_set_rate = psmouse->set_rate;
		psmouse->set_rate = elantech_set_rate_restore_reg_07;
	पूर्ण

	अगर (elantech_set_input_params(psmouse)) अणु
		psmouse_err(psmouse, "failed to query touchpad range.\n");
		जाओ init_fail;
	पूर्ण

	error = sysfs_create_group(&psmouse->ps2dev.serio->dev.kobj,
				   &elantech_attr_group);
	अगर (error) अणु
		psmouse_err(psmouse,
			    "failed to create sysfs attributes, error: %d.\n",
			    error);
		जाओ init_fail;
	पूर्ण

	अगर (info->has_trackpoपूर्णांक) अणु
		tp_dev = input_allocate_device();

		अगर (!tp_dev) अणु
			error = -ENOMEM;
			जाओ init_fail_tp_alloc;
		पूर्ण

		etd->tp_dev = tp_dev;
		snम_लिखो(etd->tp_phys, माप(etd->tp_phys), "%s/input1",
			psmouse->ps2dev.serio->phys);
		tp_dev->phys = etd->tp_phys;
		tp_dev->name = "ETPS/2 Elantech TrackPoint";
		tp_dev->id.bustype = BUS_I8042;
		tp_dev->id.venकरोr  = 0x0002;
		tp_dev->id.product = PSMOUSE_ELANTECH;
		tp_dev->id.version = 0x0000;
		tp_dev->dev.parent = &psmouse->ps2dev.serio->dev;
		tp_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
		tp_dev->relbit[BIT_WORD(REL_X)] =
			BIT_MASK(REL_X) | BIT_MASK(REL_Y);
		tp_dev->keybit[BIT_WORD(BTN_LEFT)] =
			BIT_MASK(BTN_LEFT) | BIT_MASK(BTN_MIDDLE) |
			BIT_MASK(BTN_RIGHT);

		__set_bit(INPUT_PROP_POINTER, tp_dev->propbit);
		__set_bit(INPUT_PROP_POINTING_STICK, tp_dev->propbit);

		error = input_रेजिस्टर_device(etd->tp_dev);
		अगर (error < 0)
			जाओ init_fail_tp_reg;
	पूर्ण

	psmouse->protocol_handler = elantech_process_byte;
	psmouse->disconnect = elantech_disconnect;
	psmouse->reconnect = elantech_reconnect;
	psmouse->pktsize = info->hw_version > 1 ? 6 : 4;

	वापस 0;
 init_fail_tp_reg:
	input_मुक्त_device(tp_dev);
 init_fail_tp_alloc:
	sysfs_हटाओ_group(&psmouse->ps2dev.serio->dev.kobj,
			   &elantech_attr_group);
 init_fail:
	kमुक्त(etd);
	वापस error;
पूर्ण

पूर्णांक elantech_init_ps2(काष्ठा psmouse *psmouse)
अणु
	काष्ठा elantech_device_info info;
	पूर्णांक error;

	psmouse_reset(psmouse);

	error = elantech_query_info(psmouse, &info);
	अगर (error)
		जाओ init_fail;

	error = elantech_setup_ps2(psmouse, &info);
	अगर (error)
		जाओ init_fail;

	वापस 0;
 init_fail:
	psmouse_reset(psmouse);
	वापस error;
पूर्ण

पूर्णांक elantech_init(काष्ठा psmouse *psmouse)
अणु
	काष्ठा elantech_device_info info;
	पूर्णांक error;

	psmouse_reset(psmouse);

	error = elantech_query_info(psmouse, &info);
	अगर (error)
		जाओ init_fail;

#अगर defined(CONFIG_MOUSE_PS2_ELANTECH_SMBUS)

	अगर (elantech_use_host_notअगरy(psmouse, &info)) अणु
		अगर (!IS_ENABLED(CONFIG_MOUSE_ELAN_I2C_SMBUS) ||
		    !IS_ENABLED(CONFIG_MOUSE_PS2_ELANTECH_SMBUS)) अणु
			psmouse_warn(psmouse,
				     "The touchpad can support a better bus than the too old PS/2 protocol. "
				     "Make sure MOUSE_PS2_ELANTECH_SMBUS and MOUSE_ELAN_I2C_SMBUS are enabled to get a better touchpad experience.\n");
		पूर्ण
		error = elantech_setup_smbus(psmouse, &info, true);
		अगर (!error)
			वापस PSMOUSE_ELANTECH_SMBUS;
	पूर्ण

#पूर्ण_अगर /* CONFIG_MOUSE_PS2_ELANTECH_SMBUS */

	error = elantech_setup_ps2(psmouse, &info);
	अगर (error < 0) अणु
		/*
		 * Not using any flavor of Elantech support, so clean up
		 * SMbus bपढ़ोcrumbs, अगर any.
		 */
		psmouse_smbus_cleanup(psmouse);
		जाओ init_fail;
	पूर्ण

	वापस PSMOUSE_ELANTECH;
 init_fail:
	psmouse_reset(psmouse);
	वापस error;
पूर्ण
