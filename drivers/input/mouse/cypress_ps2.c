<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cypress Trackpad PS/2 mouse driver
 *
 * Copyright (c) 2012 Cypress Semiconductor Corporation.
 *
 * Author:
 *   Dudley Du <dudl@cypress.com>
 *
 * Additional contributors include:
 *   Kamal Mostafa <kamal@canonical.com>
 *   Kyle Fazzari <git@status.e4ward.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/serपन.स>
#समावेश <linux/libps2.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>

#समावेश "cypress_ps2.h"

#अघोषित CYTP_DEBUG_VERBOSE  /* define this and DEBUG क्रम more verbose dump */

अटल व्योम cypress_set_packet_size(काष्ठा psmouse *psmouse, अचिन्हित पूर्णांक n)
अणु
	काष्ठा cytp_data *cytp = psmouse->निजी;
	cytp->pkt_size = n;
पूर्ण

अटल स्थिर अचिन्हित अक्षर cytp_rate[] = अणु10, 20, 40, 60, 100, 200पूर्ण;
अटल स्थिर अचिन्हित अक्षर cytp_resolution[] = अणु0x00, 0x01, 0x02, 0x03पूर्ण;

अटल पूर्णांक cypress_ps2_sendbyte(काष्ठा psmouse *psmouse, पूर्णांक value)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;

	अगर (ps2_sendbyte(ps2dev, value & 0xff, CYTP_CMD_TIMEOUT) < 0) अणु
		psmouse_dbg(psmouse,
				"sending command 0x%02x failed, resp 0x%02x\n",
				value & 0xff, ps2dev->nak);
		अगर (ps2dev->nak == CYTP_PS2_RETRY)
			वापस CYTP_PS2_RETRY;
		अन्यथा
			वापस CYTP_PS2_ERROR;
	पूर्ण

#अगर_घोषित CYTP_DEBUG_VERBOSE
	psmouse_dbg(psmouse, "sending command 0x%02x succeeded, resp 0xfa\n",
			value & 0xff);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक cypress_ps2_ext_cmd(काष्ठा psmouse *psmouse, अचिन्हित लघु cmd,
			       अचिन्हित अक्षर data)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	पूर्णांक tries = CYTP_PS2_CMD_TRIES;
	पूर्णांक rc;

	ps2_begin_command(ps2dev);

	करो अणु
		/*
		 * Send extension command byte (0xE8 or 0xF3).
		 * If sending the command fails, send recovery command
		 * to make the device वापस to the पढ़ोy state.
		 */
		rc = cypress_ps2_sendbyte(psmouse, cmd & 0xff);
		अगर (rc == CYTP_PS2_RETRY) अणु
			rc = cypress_ps2_sendbyte(psmouse, 0x00);
			अगर (rc == CYTP_PS2_RETRY)
				rc = cypress_ps2_sendbyte(psmouse, 0x0a);
		पूर्ण
		अगर (rc == CYTP_PS2_ERROR)
			जारी;

		rc = cypress_ps2_sendbyte(psmouse, data);
		अगर (rc == CYTP_PS2_RETRY)
			rc = cypress_ps2_sendbyte(psmouse, data);
		अगर (rc == CYTP_PS2_ERROR)
			जारी;
		अन्यथा
			अवरोध;
	पूर्ण जबतक (--tries > 0);

	ps2_end_command(ps2dev);

	वापस rc;
पूर्ण

अटल पूर्णांक cypress_ps2_पढ़ो_cmd_status(काष्ठा psmouse *psmouse,
				       अचिन्हित अक्षर cmd,
				       अचिन्हित अक्षर *param)
अणु
	पूर्णांक rc;
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	क्रमागत psmouse_state old_state;
	पूर्णांक pktsize;

	ps2_begin_command(ps2dev);

	old_state = psmouse->state;
	psmouse->state = PSMOUSE_CMD_MODE;
	psmouse->pktcnt = 0;

	pktsize = (cmd == CYTP_CMD_READ_TP_METRICS) ? 8 : 3;
	स_रखो(param, 0, pktsize);

	rc = cypress_ps2_sendbyte(psmouse, 0xe9);
	अगर (rc < 0)
		जाओ out;

	रुको_event_समयout(ps2dev->रुको,
			(psmouse->pktcnt >= pktsize),
			msecs_to_jअगरfies(CYTP_CMD_TIMEOUT));

	स_नकल(param, psmouse->packet, pktsize);

	psmouse_dbg(psmouse, "Command 0x%02x response data (0x): %*ph\n",
			cmd, pktsize, param);

out:
	psmouse->state = old_state;
	psmouse->pktcnt = 0;

	ps2_end_command(ps2dev);

	वापस rc;
पूर्ण

अटल bool cypress_verअगरy_cmd_state(काष्ठा psmouse *psmouse,
				     अचिन्हित अक्षर cmd, अचिन्हित अक्षर *param)
अणु
	bool rate_match = false;
	bool resolution_match = false;
	पूर्णांक i;

	/* callers will करो further checking. */
	अगर (cmd == CYTP_CMD_READ_CYPRESS_ID ||
	    cmd == CYTP_CMD_STANDARD_MODE ||
	    cmd == CYTP_CMD_READ_TP_METRICS)
		वापस true;

	अगर ((~param[0] & DFLT_RESP_BITS_VALID) == DFLT_RESP_BITS_VALID &&
	    (param[0] & DFLT_RESP_BIT_MODE) == DFLT_RESP_STREAM_MODE) अणु
		क्रम (i = 0; i < माप(cytp_resolution); i++)
			अगर (cytp_resolution[i] == param[1])
				resolution_match = true;

		क्रम (i = 0; i < माप(cytp_rate); i++)
			अगर (cytp_rate[i] == param[2])
				rate_match = true;

		अगर (resolution_match && rate_match)
			वापस true;
	पूर्ण

	psmouse_dbg(psmouse, "verify cmd state failed.\n");
	वापस false;
पूर्ण

अटल पूर्णांक cypress_send_ext_cmd(काष्ठा psmouse *psmouse, अचिन्हित अक्षर cmd,
				अचिन्हित अक्षर *param)
अणु
	पूर्णांक tries = CYTP_PS2_CMD_TRIES;
	पूर्णांक rc;

	psmouse_dbg(psmouse, "send extension cmd 0x%02x, [%d %d %d %d]\n",
		 cmd, DECODE_CMD_AA(cmd), DECODE_CMD_BB(cmd),
		 DECODE_CMD_CC(cmd), DECODE_CMD_DD(cmd));

	करो अणु
		cypress_ps2_ext_cmd(psmouse,
				    PSMOUSE_CMD_SETRES, DECODE_CMD_DD(cmd));
		cypress_ps2_ext_cmd(psmouse,
				    PSMOUSE_CMD_SETRES, DECODE_CMD_CC(cmd));
		cypress_ps2_ext_cmd(psmouse,
				    PSMOUSE_CMD_SETRES, DECODE_CMD_BB(cmd));
		cypress_ps2_ext_cmd(psmouse,
				    PSMOUSE_CMD_SETRES, DECODE_CMD_AA(cmd));

		rc = cypress_ps2_पढ़ो_cmd_status(psmouse, cmd, param);
		अगर (rc)
			जारी;

		अगर (cypress_verअगरy_cmd_state(psmouse, cmd, param))
			वापस 0;

	पूर्ण जबतक (--tries > 0);

	वापस -EIO;
पूर्ण

पूर्णांक cypress_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	अचिन्हित अक्षर param[3];

	अगर (cypress_send_ext_cmd(psmouse, CYTP_CMD_READ_CYPRESS_ID, param))
		वापस -ENODEV;

	/* Check क्रम Cypress Trackpad signature bytes: 0x33 0xCC */
	अगर (param[0] != 0x33 || param[1] != 0xCC)
		वापस -ENODEV;

	अगर (set_properties) अणु
		psmouse->venकरोr = "Cypress";
		psmouse->name = "Trackpad";
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cypress_पढ़ो_fw_version(काष्ठा psmouse *psmouse)
अणु
	काष्ठा cytp_data *cytp = psmouse->निजी;
	अचिन्हित अक्षर param[3];

	अगर (cypress_send_ext_cmd(psmouse, CYTP_CMD_READ_CYPRESS_ID, param))
		वापस -ENODEV;

	/* Check क्रम Cypress Trackpad signature bytes: 0x33 0xCC */
	अगर (param[0] != 0x33 || param[1] != 0xCC)
		वापस -ENODEV;

	cytp->fw_version = param[2] & FW_VERSION_MASX;
	cytp->tp_metrics_supported = (param[2] & TP_METRICS_MASK) ? 1 : 0;

	/*
	 * Trackpad fw_version 11 (in Dell XPS12) yields a bogus response to
	 * CYTP_CMD_READ_TP_METRICS so करो not try to use it. LP: #1103594.
	 */
	अगर (cytp->fw_version >= 11)
		cytp->tp_metrics_supported = 0;

	psmouse_dbg(psmouse, "cytp->fw_version = %d\n", cytp->fw_version);
	psmouse_dbg(psmouse, "cytp->tp_metrics_supported = %d\n",
		 cytp->tp_metrics_supported);

	वापस 0;
पूर्ण

अटल पूर्णांक cypress_पढ़ो_tp_metrics(काष्ठा psmouse *psmouse)
अणु
	काष्ठा cytp_data *cytp = psmouse->निजी;
	अचिन्हित अक्षर param[8];

	/* set शेष values क्रम tp metrics. */
	cytp->tp_width = CYTP_DEFAULT_WIDTH;
	cytp->tp_high = CYTP_DEFAULT_HIGH;
	cytp->tp_max_असल_x = CYTP_ABS_MAX_X;
	cytp->tp_max_असल_y = CYTP_ABS_MAX_Y;
	cytp->tp_min_pressure = CYTP_MIN_PRESSURE;
	cytp->tp_max_pressure = CYTP_MAX_PRESSURE;
	cytp->tp_res_x = cytp->tp_max_असल_x / cytp->tp_width;
	cytp->tp_res_y = cytp->tp_max_असल_y / cytp->tp_high;

	अगर (!cytp->tp_metrics_supported)
		वापस 0;

	स_रखो(param, 0, माप(param));
	अगर (cypress_send_ext_cmd(psmouse, CYTP_CMD_READ_TP_METRICS, param) == 0) अणु
		/* Update trackpad parameters. */
		cytp->tp_max_असल_x = (param[1] << 8) | param[0];
		cytp->tp_max_असल_y = (param[3] << 8) | param[2];
		cytp->tp_min_pressure = param[4];
		cytp->tp_max_pressure = param[5];
	पूर्ण

	अगर (!cytp->tp_max_pressure ||
	    cytp->tp_max_pressure < cytp->tp_min_pressure ||
	    !cytp->tp_width || !cytp->tp_high ||
	    !cytp->tp_max_असल_x ||
	    cytp->tp_max_असल_x < cytp->tp_width ||
	    !cytp->tp_max_असल_y ||
	    cytp->tp_max_असल_y < cytp->tp_high)
		वापस -EINVAL;

	cytp->tp_res_x = cytp->tp_max_असल_x / cytp->tp_width;
	cytp->tp_res_y = cytp->tp_max_असल_y / cytp->tp_high;

#अगर_घोषित CYTP_DEBUG_VERBOSE
	psmouse_dbg(psmouse, "Dump trackpad hardware configuration as below:\n");
	psmouse_dbg(psmouse, "cytp->tp_width = %d\n", cytp->tp_width);
	psmouse_dbg(psmouse, "cytp->tp_high = %d\n", cytp->tp_high);
	psmouse_dbg(psmouse, "cytp->tp_max_abs_x = %d\n", cytp->tp_max_असल_x);
	psmouse_dbg(psmouse, "cytp->tp_max_abs_y = %d\n", cytp->tp_max_असल_y);
	psmouse_dbg(psmouse, "cytp->tp_min_pressure = %d\n", cytp->tp_min_pressure);
	psmouse_dbg(psmouse, "cytp->tp_max_pressure = %d\n", cytp->tp_max_pressure);
	psmouse_dbg(psmouse, "cytp->tp_res_x = %d\n", cytp->tp_res_x);
	psmouse_dbg(psmouse, "cytp->tp_res_y = %d\n", cytp->tp_res_y);

	psmouse_dbg(psmouse, "tp_type_APA = %d\n",
			(param[6] & TP_METRICS_BIT_APA) ? 1 : 0);
	psmouse_dbg(psmouse, "tp_type_MTG = %d\n",
			(param[6] & TP_METRICS_BIT_MTG) ? 1 : 0);
	psmouse_dbg(psmouse, "tp_palm = %d\n",
			(param[6] & TP_METRICS_BIT_PALM) ? 1 : 0);
	psmouse_dbg(psmouse, "tp_stubborn = %d\n",
			(param[6] & TP_METRICS_BIT_STUBBORN) ? 1 : 0);
	psmouse_dbg(psmouse, "tp_1f_jitter = %d\n",
			(param[6] & TP_METRICS_BIT_1F_JITTER) >> 2);
	psmouse_dbg(psmouse, "tp_2f_jitter = %d\n",
			(param[6] & TP_METRICS_BIT_2F_JITTER) >> 4);
	psmouse_dbg(psmouse, "tp_1f_spike = %d\n",
			param[7] & TP_METRICS_BIT_1F_SPIKE);
	psmouse_dbg(psmouse, "tp_2f_spike = %d\n",
			(param[7] & TP_METRICS_BIT_2F_SPIKE) >> 2);
	psmouse_dbg(psmouse, "tp_abs_packet_format_set = %d\n",
			(param[7] & TP_METRICS_BIT_ABS_PKT_FORMAT_SET) >> 4);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक cypress_query_hardware(काष्ठा psmouse *psmouse)
अणु
	पूर्णांक ret;

	ret = cypress_पढ़ो_fw_version(psmouse);
	अगर (ret)
		वापस ret;

	ret = cypress_पढ़ो_tp_metrics(psmouse);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक cypress_set_असलolute_mode(काष्ठा psmouse *psmouse)
अणु
	काष्ठा cytp_data *cytp = psmouse->निजी;
	अचिन्हित अक्षर param[3];

	अगर (cypress_send_ext_cmd(psmouse, CYTP_CMD_ABS_WITH_PRESSURE_MODE, param) < 0)
		वापस -1;

	cytp->mode = (cytp->mode & ~CYTP_BIT_ABS_REL_MASK)
			| CYTP_BIT_ABS_PRESSURE;
	cypress_set_packet_size(psmouse, 5);

	वापस 0;
पूर्ण

/*
 * Reset trackpad device.
 * This is also the शेष mode when trackpad घातered on.
 */
अटल व्योम cypress_reset(काष्ठा psmouse *psmouse)
अणु
	काष्ठा cytp_data *cytp = psmouse->निजी;

	cytp->mode = 0;

	psmouse_reset(psmouse);
पूर्ण

अटल पूर्णांक cypress_set_input_params(काष्ठा input_dev *input,
				    काष्ठा cytp_data *cytp)
अणु
	पूर्णांक ret;

	अगर (!cytp->tp_res_x || !cytp->tp_res_y)
		वापस -EINVAL;

	__set_bit(EV_ABS, input->evbit);
	input_set_असल_params(input, ABS_X, 0, cytp->tp_max_असल_x, 0, 0);
	input_set_असल_params(input, ABS_Y, 0, cytp->tp_max_असल_y, 0, 0);
	input_set_असल_params(input, ABS_PRESSURE,
			     cytp->tp_min_pressure, cytp->tp_max_pressure, 0, 0);
	input_set_असल_params(input, ABS_TOOL_WIDTH, 0, 255, 0, 0);

	/* finger position */
	input_set_असल_params(input, ABS_MT_POSITION_X, 0, cytp->tp_max_असल_x, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y, 0, cytp->tp_max_असल_y, 0, 0);
	input_set_असल_params(input, ABS_MT_PRESSURE, 0, 255, 0, 0);

	ret = input_mt_init_slots(input, CYTP_MAX_MT_SLOTS,
			INPUT_MT_DROP_UNUSED|INPUT_MT_TRACK);
	अगर (ret < 0)
		वापस ret;

	__set_bit(INPUT_PROP_SEMI_MT, input->propbit);

	input_असल_set_res(input, ABS_X, cytp->tp_res_x);
	input_असल_set_res(input, ABS_Y, cytp->tp_res_y);

	input_असल_set_res(input, ABS_MT_POSITION_X, cytp->tp_res_x);
	input_असल_set_res(input, ABS_MT_POSITION_Y, cytp->tp_res_y);

	__set_bit(BTN_TOUCH, input->keybit);
	__set_bit(BTN_TOOL_FINGER, input->keybit);
	__set_bit(BTN_TOOL_DOUBLETAP, input->keybit);
	__set_bit(BTN_TOOL_TRIPLETAP, input->keybit);
	__set_bit(BTN_TOOL_QUADTAP, input->keybit);
	__set_bit(BTN_TOOL_QUINTTAP, input->keybit);

	__clear_bit(EV_REL, input->evbit);
	__clear_bit(REL_X, input->relbit);
	__clear_bit(REL_Y, input->relbit);

	__set_bit(EV_KEY, input->evbit);
	__set_bit(BTN_LEFT, input->keybit);
	__set_bit(BTN_RIGHT, input->keybit);
	__set_bit(BTN_MIDDLE, input->keybit);

	वापस 0;
पूर्ण

अटल पूर्णांक cypress_get_finger_count(अचिन्हित अक्षर header_byte)
अणु
	अचिन्हित अक्षर bits6_7;
	पूर्णांक finger_count;

	bits6_7 = header_byte >> 6;
	finger_count = bits6_7 & 0x03;

	अगर (finger_count == 1)
		वापस 1;

	अगर (header_byte & ABS_HSCROLL_BIT) अणु
		/* HSCROLL माला_लो added on to 0 finger count. */
		चयन (finger_count) अणु
			हाल 0:	वापस 4;
			हाल 2: वापस 5;
			शेष:
				/* Invalid contact (e.g. palm). Ignore it. */
				वापस 0;
		पूर्ण
	पूर्ण

	वापस finger_count;
पूर्ण


अटल पूर्णांक cypress_parse_packet(काष्ठा psmouse *psmouse,
				काष्ठा cytp_data *cytp, काष्ठा cytp_report_data *report_data)
अणु
	अचिन्हित अक्षर *packet = psmouse->packet;
	अचिन्हित अक्षर header_byte = packet[0];

	स_रखो(report_data, 0, माप(काष्ठा cytp_report_data));

	report_data->contact_cnt = cypress_get_finger_count(header_byte);
	report_data->tap = (header_byte & ABS_MULTIFINGER_TAP) ? 1 : 0;

	अगर (report_data->contact_cnt == 1) अणु
		report_data->contacts[0].x =
			((packet[1] & 0x70) << 4) | packet[2];
		report_data->contacts[0].y =
			((packet[1] & 0x07) << 8) | packet[3];
		अगर (cytp->mode & CYTP_BIT_ABS_PRESSURE)
			report_data->contacts[0].z = packet[4];

	पूर्ण अन्यथा अगर (report_data->contact_cnt >= 2) अणु
		report_data->contacts[0].x =
			((packet[1] & 0x70) << 4) | packet[2];
		report_data->contacts[0].y =
			((packet[1] & 0x07) << 8) | packet[3];
		अगर (cytp->mode & CYTP_BIT_ABS_PRESSURE)
			report_data->contacts[0].z = packet[4];

		report_data->contacts[1].x =
			((packet[5] & 0xf0) << 4) | packet[6];
		report_data->contacts[1].y =
			((packet[5] & 0x0f) << 8) | packet[7];
		अगर (cytp->mode & CYTP_BIT_ABS_PRESSURE)
			report_data->contacts[1].z = report_data->contacts[0].z;
	पूर्ण

	report_data->left = (header_byte & BTN_LEFT_BIT) ? 1 : 0;
	report_data->right = (header_byte & BTN_RIGHT_BIT) ? 1 : 0;

	/*
	 * This is only true अगर one of the mouse buttons were tapped.  Make
	 * sure it करोesn't turn पूर्णांकo a click. The regular tap-to-click
	 * functionality will handle that on its own. If we करोn't करो this,
	 * disabling tap-to-click won't affect the mouse button zones.
	 */
	अगर (report_data->tap)
		report_data->left = 0;

#अगर_घोषित CYTP_DEBUG_VERBOSE
	अणु
		पूर्णांक i;
		पूर्णांक n = report_data->contact_cnt;
		psmouse_dbg(psmouse, "Dump parsed report data as below:\n");
		psmouse_dbg(psmouse, "contact_cnt = %d\n",
			report_data->contact_cnt);
		अगर (n > CYTP_MAX_MT_SLOTS)
		    n = CYTP_MAX_MT_SLOTS;
		क्रम (i = 0; i < n; i++)
			psmouse_dbg(psmouse, "contacts[%d] = {%d, %d, %d}\n", i,
					report_data->contacts[i].x,
					report_data->contacts[i].y,
					report_data->contacts[i].z);
		psmouse_dbg(psmouse, "left = %d\n", report_data->left);
		psmouse_dbg(psmouse, "right = %d\n", report_data->right);
		psmouse_dbg(psmouse, "middle = %d\n", report_data->middle);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम cypress_process_packet(काष्ठा psmouse *psmouse, bool zero_pkt)
अणु
	पूर्णांक i;
	काष्ठा input_dev *input = psmouse->dev;
	काष्ठा cytp_data *cytp = psmouse->निजी;
	काष्ठा cytp_report_data report_data;
	काष्ठा cytp_contact *contact;
	काष्ठा input_mt_pos pos[CYTP_MAX_MT_SLOTS];
	पूर्णांक slots[CYTP_MAX_MT_SLOTS];
	पूर्णांक n;

	cypress_parse_packet(psmouse, cytp, &report_data);

	n = report_data.contact_cnt;
	अगर (n > CYTP_MAX_MT_SLOTS)
		n = CYTP_MAX_MT_SLOTS;

	क्रम (i = 0; i < n; i++) अणु
		contact = &report_data.contacts[i];
		pos[i].x = contact->x;
		pos[i].y = contact->y;
	पूर्ण

	input_mt_assign_slots(input, slots, pos, n, 0);

	क्रम (i = 0; i < n; i++) अणु
		contact = &report_data.contacts[i];
		input_mt_slot(input, slots[i]);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, true);
		input_report_असल(input, ABS_MT_POSITION_X, contact->x);
		input_report_असल(input, ABS_MT_POSITION_Y, contact->y);
		input_report_असल(input, ABS_MT_PRESSURE, contact->z);
	पूर्ण

	input_mt_sync_frame(input);

	input_mt_report_finger_count(input, report_data.contact_cnt);

	input_report_key(input, BTN_LEFT, report_data.left);
	input_report_key(input, BTN_RIGHT, report_data.right);
	input_report_key(input, BTN_MIDDLE, report_data.middle);

	input_sync(input);
पूर्ण

अटल psmouse_ret_t cypress_validate_byte(काष्ठा psmouse *psmouse)
अणु
	पूर्णांक contact_cnt;
	पूर्णांक index = psmouse->pktcnt - 1;
	अचिन्हित अक्षर *packet = psmouse->packet;
	काष्ठा cytp_data *cytp = psmouse->निजी;

	अगर (index < 0 || index > cytp->pkt_size)
		वापस PSMOUSE_BAD_DATA;

	अगर (index == 0 && (packet[0] & 0xfc) == 0) अणु
		/* call packet process क्रम reporting finger leave. */
		cypress_process_packet(psmouse, 1);
		वापस PSMOUSE_FULL_PACKET;
	पूर्ण

	/*
	 * Perक्रमm validation (and adjust packet size) based only on the
	 * first byte; allow all further bytes through.
	 */
	अगर (index != 0)
		वापस PSMOUSE_GOOD_DATA;

	/*
	 * If असलolute/relative mode bit has not been set yet, just pass
	 * the byte through.
	 */
	अगर ((cytp->mode & CYTP_BIT_ABS_REL_MASK) == 0)
		वापस PSMOUSE_GOOD_DATA;

	अगर ((packet[0] & 0x08) == 0x08)
		वापस PSMOUSE_BAD_DATA;

	contact_cnt = cypress_get_finger_count(packet[0]);
	अगर (cytp->mode & CYTP_BIT_ABS_NO_PRESSURE)
		cypress_set_packet_size(psmouse, contact_cnt == 2 ? 7 : 4);
	अन्यथा
		cypress_set_packet_size(psmouse, contact_cnt == 2 ? 8 : 5);

	वापस PSMOUSE_GOOD_DATA;
पूर्ण

अटल psmouse_ret_t cypress_protocol_handler(काष्ठा psmouse *psmouse)
अणु
	काष्ठा cytp_data *cytp = psmouse->निजी;

	अगर (psmouse->pktcnt >= cytp->pkt_size) अणु
		cypress_process_packet(psmouse, 0);
		वापस PSMOUSE_FULL_PACKET;
	पूर्ण

	वापस cypress_validate_byte(psmouse);
पूर्ण

अटल व्योम cypress_set_rate(काष्ठा psmouse *psmouse, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा cytp_data *cytp = psmouse->निजी;

	अगर (rate >= 80) अणु
		psmouse->rate = 80;
		cytp->mode |= CYTP_BIT_HIGH_RATE;
	पूर्ण अन्यथा अणु
		psmouse->rate = 40;
		cytp->mode &= ~CYTP_BIT_HIGH_RATE;
	पूर्ण

	ps2_command(&psmouse->ps2dev, (अचिन्हित अक्षर *)&psmouse->rate,
		    PSMOUSE_CMD_SETRATE);
पूर्ण

अटल व्योम cypress_disconnect(काष्ठा psmouse *psmouse)
अणु
	cypress_reset(psmouse);
	kमुक्त(psmouse->निजी);
	psmouse->निजी = शून्य;
पूर्ण

अटल पूर्णांक cypress_reconnect(काष्ठा psmouse *psmouse)
अणु
	पूर्णांक tries = CYTP_PS2_CMD_TRIES;
	पूर्णांक rc;

	करो अणु
		cypress_reset(psmouse);
		rc = cypress_detect(psmouse, false);
	पूर्ण जबतक (rc && (--tries > 0));

	अगर (rc) अणु
		psmouse_err(psmouse, "Reconnect: unable to detect trackpad.\n");
		वापस -1;
	पूर्ण

	अगर (cypress_set_असलolute_mode(psmouse)) अणु
		psmouse_err(psmouse, "Reconnect: Unable to initialize Cypress absolute mode.\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cypress_init(काष्ठा psmouse *psmouse)
अणु
	काष्ठा cytp_data *cytp;

	cytp = kzalloc(माप(काष्ठा cytp_data), GFP_KERNEL);
	अगर (!cytp)
		वापस -ENOMEM;

	psmouse->निजी = cytp;
	psmouse->pktsize = 8;

	cypress_reset(psmouse);

	अगर (cypress_query_hardware(psmouse)) अणु
		psmouse_err(psmouse, "Unable to query Trackpad hardware.\n");
		जाओ err_निकास;
	पूर्ण

	अगर (cypress_set_असलolute_mode(psmouse)) अणु
		psmouse_err(psmouse, "init: Unable to initialize Cypress absolute mode.\n");
		जाओ err_निकास;
	पूर्ण

	अगर (cypress_set_input_params(psmouse->dev, cytp) < 0) अणु
		psmouse_err(psmouse, "init: Unable to set input params.\n");
		जाओ err_निकास;
	पूर्ण

	psmouse->model = 1;
	psmouse->protocol_handler = cypress_protocol_handler;
	psmouse->set_rate = cypress_set_rate;
	psmouse->disconnect = cypress_disconnect;
	psmouse->reconnect = cypress_reconnect;
	psmouse->cleanup = cypress_reset;
	psmouse->resync_समय = 0;

	वापस 0;

err_निकास:
	/*
	 * Reset Cypress Trackpad as a standard mouse. Then
	 * let psmouse driver commmunicating with it as शेष PS2 mouse.
	 */
	cypress_reset(psmouse);

	psmouse->निजी = शून्य;
	kमुक्त(cytp);

	वापस -1;
पूर्ण
