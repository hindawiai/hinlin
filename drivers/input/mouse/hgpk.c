<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OLPC HGPK (XO-1) touchpad PS/2 mouse driver
 *
 * Copyright (c) 2006-2008 One Laptop Per Child
 * Authors:
 *   Zephaniah E. Hull
 *   Andres Salomon <dilinger@debian.org>
 *
 * This driver is partly based on the ALPS driver, which is:
 *
 * Copyright (c) 2003 Neil Brown <neilb@cse.unsw.edu.au>
 * Copyright (c) 2003-2005 Peter Osterlund <petero2@telia.com>
 * Copyright (c) 2004 Dmitry Torokhov <dtor@mail.ru>
 * Copyright (c) 2005 Vojtech Pavlik <vojtech@suse.cz>
 */

/*
 * The spec from ALPS is available from
 * <http://wiki.laptop.org/go/Touch_Pad/Tablet>.  It refers to this
 * device as HGPK (Hybrid GS, PT, and Keymatrix).
 *
 * The earliest versions of the device had simultaneous reporting; that
 * was हटाओd.  After that, the device used the Advanced Mode GS/PT streaming
 * stuff.  That turned out to be too buggy to support, so we've finally
 * चयनed to Mouse Mode (which utilizes only the center 1/3 of the touchpad).
 */

#घोषणा DEBUG
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/serपन.स>
#समावेश <linux/libps2.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/olpc.h>

#समावेश "psmouse.h"
#समावेश "hgpk.h"

#घोषणा ILLEGAL_XY 999999

अटल bool tpdebug;
module_param(tpdebug, bool, 0644);
MODULE_PARM_DESC(tpdebug, "enable debugging, dumping packets to KERN_DEBUG.");

अटल पूर्णांक recalib_delta = 100;
module_param(recalib_delta, पूर्णांक, 0644);
MODULE_PARM_DESC(recalib_delta,
	"packets containing a delta this large will be discarded, and a "
	"recalibration may be scheduled.");

अटल पूर्णांक jumpy_delay = 20;
module_param(jumpy_delay, पूर्णांक, 0644);
MODULE_PARM_DESC(jumpy_delay,
	"delay (ms) before recal after jumpiness detected");

अटल पूर्णांक spew_delay = 1;
module_param(spew_delay, पूर्णांक, 0644);
MODULE_PARM_DESC(spew_delay,
	"delay (ms) before recal after packet spew detected");

अटल पूर्णांक recal_guard_समय;
module_param(recal_guard_समय, पूर्णांक, 0644);
MODULE_PARM_DESC(recal_guard_समय,
	"interval (ms) during which recal will be restarted if packet received");

अटल पूर्णांक post_पूर्णांकerrupt_delay = 40;
module_param(post_पूर्णांकerrupt_delay, पूर्णांक, 0644);
MODULE_PARM_DESC(post_पूर्णांकerrupt_delay,
	"delay (ms) before recal after recal interrupt detected");

अटल bool स्वतःrecal = true;
module_param(स्वतःrecal, bool, 0644);
MODULE_PARM_DESC(स्वतःrecal, "enable recalibration in the driver");

अटल अक्षर hgpk_mode_name[16];
module_param_string(hgpk_mode, hgpk_mode_name, माप(hgpk_mode_name), 0644);
MODULE_PARM_DESC(hgpk_mode,
	"default hgpk mode: mouse, glidesensor or pentablet");

अटल पूर्णांक hgpk_शेष_mode = HGPK_MODE_MOUSE;

अटल स्थिर अक्षर * स्थिर hgpk_mode_names[] = अणु
	[HGPK_MODE_MOUSE] = "Mouse",
	[HGPK_MODE_GLIDESENSOR] = "GlideSensor",
	[HGPK_MODE_PENTABLET] = "PenTablet",
पूर्ण;

अटल पूर्णांक hgpk_mode_from_name(स्थिर अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hgpk_mode_names); i++) अणु
		स्थिर अक्षर *name = hgpk_mode_names[i];
		अगर (म_माप(name) == len && !strnहालcmp(name, buf, len))
			वापस i;
	पूर्ण

	वापस HGPK_MODE_INVALID;
पूर्ण

/*
 * see अगर new value is within 20% of half of old value
 */
अटल पूर्णांक approx_half(पूर्णांक curr, पूर्णांक prev)
अणु
	पूर्णांक belowhalf, abovehalf;

	अगर (curr < 5 || prev < 5)
		वापस 0;

	belowhalf = (prev * 8) / 20;
	abovehalf = (prev * 12) / 20;

	वापस belowhalf < curr && curr <= abovehalf;
पूर्ण

/*
 * Throw out oddly large delta packets, and any that immediately follow whose
 * values are each approximately half of the previous.  It seems that the ALPS
 * firmware emits errant packets, and they get averaged out slowly.
 */
अटल पूर्णांक hgpk_discard_decay_hack(काष्ठा psmouse *psmouse, पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा hgpk_data *priv = psmouse->निजी;
	पूर्णांक avx, avy;
	bool करो_recal = false;

	avx = असल(x);
	avy = असल(y);

	/* discard अगर too big, or half that but > 4 बार the prev delta */
	अगर (avx > recalib_delta ||
		(avx > recalib_delta / 2 && ((avx / 4) > priv->xlast))) अणु
		psmouse_warn(psmouse, "detected %dpx jump in x\n", x);
		priv->xbigj = avx;
	पूर्ण अन्यथा अगर (approx_half(avx, priv->xbigj)) अणु
		psmouse_warn(psmouse, "detected secondary %dpx jump in x\n", x);
		priv->xbigj = avx;
		priv->xsaw_secondary++;
	पूर्ण अन्यथा अणु
		अगर (priv->xbigj && priv->xsaw_secondary > 1)
			करो_recal = true;
		priv->xbigj = 0;
		priv->xsaw_secondary = 0;
	पूर्ण

	अगर (avy > recalib_delta ||
		(avy > recalib_delta / 2 && ((avy / 4) > priv->ylast))) अणु
		psmouse_warn(psmouse, "detected %dpx jump in y\n", y);
		priv->ybigj = avy;
	पूर्ण अन्यथा अगर (approx_half(avy, priv->ybigj)) अणु
		psmouse_warn(psmouse, "detected secondary %dpx jump in y\n", y);
		priv->ybigj = avy;
		priv->ysaw_secondary++;
	पूर्ण अन्यथा अणु
		अगर (priv->ybigj && priv->ysaw_secondary > 1)
			करो_recal = true;
		priv->ybigj = 0;
		priv->ysaw_secondary = 0;
	पूर्ण

	priv->xlast = avx;
	priv->ylast = avy;

	अगर (करो_recal && jumpy_delay) अणु
		psmouse_warn(psmouse, "scheduling recalibration\n");
		psmouse_queue_work(psmouse, &priv->recalib_wq,
				msecs_to_jअगरfies(jumpy_delay));
	पूर्ण

	वापस priv->xbigj || priv->ybigj;
पूर्ण

अटल व्योम hgpk_reset_spew_detection(काष्ठा hgpk_data *priv)
अणु
	priv->spew_count = 0;
	priv->dupe_count = 0;
	priv->x_tally = 0;
	priv->y_tally = 0;
	priv->spew_flag = NO_SPEW;
पूर्ण

अटल व्योम hgpk_reset_hack_state(काष्ठा psmouse *psmouse)
अणु
	काष्ठा hgpk_data *priv = psmouse->निजी;

	priv->असल_x = priv->असल_y = -1;
	priv->xlast = priv->ylast = ILLEGAL_XY;
	priv->xbigj = priv->ybigj = 0;
	priv->xsaw_secondary = priv->ysaw_secondary = 0;
	hgpk_reset_spew_detection(priv);
पूर्ण

/*
 * We have no idea why this particular hardware bug occurs.  The touchpad
 * will अक्रमomly start spewing packets without anything touching the
 * pad.  This wouldn't necessarily be bad, but it's indicative of a
 * severely miscalibrated pad; attempting to use the touchpad जबतक it's
 * spewing means the cursor will jump all over the place, and act "drunk".
 *
 * The packets that are spewed tend to all have deltas between -2 and 2, and
 * the cursor will move around without really going very far.  It will
 * tend to end up in the same location; अगर we tally up the changes over
 * 100 packets, we end up w/ a final delta of बंद to 0.  This happens
 * pretty regularly when the touchpad is spewing, and is pretty hard to
 * manually trigger (at least क्रम *my* fingers).  So, it makes a perfect
 * scheme क्रम detecting spews.
 */
अटल व्योम hgpk_spewing_hack(काष्ठा psmouse *psmouse,
			      पूर्णांक l, पूर्णांक r, पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा hgpk_data *priv = psmouse->निजी;

	/* ignore button press packets; many in a row could trigger
	 * a false-positive! */
	अगर (l || r)
		वापस;

	/* करोn't track spew अगर the workaround feature has been turned off */
	अगर (!spew_delay)
		वापस;

	अगर (असल(x) > 3 || असल(y) > 3) अणु
		/* no spew, or spew ended */
		hgpk_reset_spew_detection(priv);
		वापस;
	पूर्ण

	/* Keep a tally of the overall delta to the cursor position caused by
	 * the spew */
	priv->x_tally += x;
	priv->y_tally += y;

	चयन (priv->spew_flag) अणु
	हाल NO_SPEW:
		/* we're not spewing, but this packet might be the start */
		priv->spew_flag = MAYBE_SPEWING;

		fallthrough;

	हाल MAYBE_SPEWING:
		priv->spew_count++;

		अगर (priv->spew_count < SPEW_WATCH_COUNT)
			अवरोध;

		/* excessive spew detected, request recalibration */
		priv->spew_flag = SPEW_DETECTED;

		fallthrough;

	हाल SPEW_DETECTED:
		/* only recalibrate when the overall delta to the cursor
		 * is really small. अगर the spew is causing signअगरicant cursor
		 * movement, it is probably a हाल of the user moving the
		 * cursor very slowly across the screen. */
		अगर (असल(priv->x_tally) < 3 && असल(priv->y_tally) < 3) अणु
			psmouse_warn(psmouse, "packet spew detected (%d,%d)\n",
				     priv->x_tally, priv->y_tally);
			priv->spew_flag = RECALIBRATING;
			psmouse_queue_work(psmouse, &priv->recalib_wq,
					   msecs_to_jअगरfies(spew_delay));
		पूर्ण

		अवरोध;
	हाल RECALIBRATING:
		/* we alपढ़ोy detected a spew and requested a recalibration,
		 * just रुको क्रम the queue to kick पूर्णांकo action. */
		अवरोध;
	पूर्ण
पूर्ण

/*
 * HGPK Mouse Mode क्रमmat (standard mouse क्रमmat, sans middle button)
 *
 * byte 0:	y-over	x-over	y-neg	x-neg	1	0	swr	swl
 * byte 1:	x7	x6	x5	x4	x3	x2	x1	x0
 * byte 2:	y7	y6	y5	y4	y3	y2	y1	y0
 *
 * swr/swl are the left/right buttons.
 * x-neg/y-neg are the x and y delta negative bits
 * x-over/y-over are the x and y overflow bits
 *
 * ---
 *
 * HGPK Advanced Mode - single-mode क्रमmat
 *
 * byte 0(PT):  1    1    0    0    1    1     1     1
 * byte 0(GS):  1    1    1    1    1    1     1     1
 * byte 1:      0   x6   x5   x4   x3   x2    x1    x0
 * byte 2(PT):  0    0   x9   x8   x7    ? pt-dsw    0
 * byte 2(GS):  0  x10   x9   x8   x7    ? gs-dsw pt-dsw
 * byte 3:      0   y9   y8   y7    1    0   swr   swl
 * byte 4:      0   y6   y5   y4   y3   y2    y1    y0
 * byte 5:      0   z6   z5   z4   z3   z2    z1    z0
 *
 * ?'s are not defined in the protocol spec, may vary between models.
 *
 * swr/swl are the left/right buttons.
 *
 * pt-dsw/gs-dsw indicate that the pt/gs sensor is detecting a
 * pen/finger
 */
अटल bool hgpk_is_byte_valid(काष्ठा psmouse *psmouse, अचिन्हित अक्षर *packet)
अणु
	काष्ठा hgpk_data *priv = psmouse->निजी;
	पूर्णांक pktcnt = psmouse->pktcnt;
	bool valid;

	चयन (priv->mode) अणु
	हाल HGPK_MODE_MOUSE:
		valid = (packet[0] & 0x0C) == 0x08;
		अवरोध;

	हाल HGPK_MODE_GLIDESENSOR:
		valid = pktcnt == 1 ?
			packet[0] == HGPK_GS : !(packet[pktcnt - 1] & 0x80);
		अवरोध;

	हाल HGPK_MODE_PENTABLET:
		valid = pktcnt == 1 ?
			packet[0] == HGPK_PT : !(packet[pktcnt - 1] & 0x80);
		अवरोध;

	शेष:
		valid = false;
		अवरोध;
	पूर्ण

	अगर (!valid)
		psmouse_dbg(psmouse,
			    "bad data, mode %d (%d) %*ph\n",
			    priv->mode, pktcnt, 6, psmouse->packet);

	वापस valid;
पूर्ण

अटल व्योम hgpk_process_advanced_packet(काष्ठा psmouse *psmouse)
अणु
	काष्ठा hgpk_data *priv = psmouse->निजी;
	काष्ठा input_dev *idev = psmouse->dev;
	अचिन्हित अक्षर *packet = psmouse->packet;
	पूर्णांक करोwn = !!(packet[2] & 2);
	पूर्णांक left = !!(packet[3] & 1);
	पूर्णांक right = !!(packet[3] & 2);
	पूर्णांक x = packet[1] | ((packet[2] & 0x78) << 4);
	पूर्णांक y = packet[4] | ((packet[3] & 0x70) << 3);

	अगर (priv->mode == HGPK_MODE_GLIDESENSOR) अणु
		पूर्णांक pt_करोwn = !!(packet[2] & 1);
		पूर्णांक finger_करोwn = !!(packet[2] & 2);
		पूर्णांक z = packet[5];

		input_report_असल(idev, ABS_PRESSURE, z);
		अगर (tpdebug)
			psmouse_dbg(psmouse, "pd=%d fd=%d z=%d",
				    pt_करोwn, finger_करोwn, z);
	पूर्ण अन्यथा अणु
		/*
		 * PenTablet mode करोes not report pressure, so we करोn't
		 * report it here
		 */
		अगर (tpdebug)
			psmouse_dbg(psmouse, "pd=%d ", करोwn);
	पूर्ण

	अगर (tpdebug)
		psmouse_dbg(psmouse, "l=%d r=%d x=%d y=%d\n",
			    left, right, x, y);

	input_report_key(idev, BTN_TOUCH, करोwn);
	input_report_key(idev, BTN_LEFT, left);
	input_report_key(idev, BTN_RIGHT, right);

	/*
	 * If this packet says that the finger was हटाओd, reset our position
	 * tracking so that we करोn't erroneously detect a jump on next press.
	 */
	अगर (!करोwn) अणु
		hgpk_reset_hack_state(psmouse);
		जाओ करोne;
	पूर्ण

	/*
	 * Weed out duplicate packets (we get quite a few, and they mess up
	 * our jump detection)
	 */
	अगर (x == priv->असल_x && y == priv->असल_y) अणु
		अगर (++priv->dupe_count > SPEW_WATCH_COUNT) अणु
			अगर (tpdebug)
				psmouse_dbg(psmouse, "hard spew detected\n");
			priv->spew_flag = RECALIBRATING;
			psmouse_queue_work(psmouse, &priv->recalib_wq,
					   msecs_to_jअगरfies(spew_delay));
		पूर्ण
		जाओ करोne;
	पूर्ण

	/* not a duplicate, जारी with position reporting */
	priv->dupe_count = 0;

	/* Don't apply hacks in PT mode, it seems reliable */
	अगर (priv->mode != HGPK_MODE_PENTABLET && priv->असल_x != -1) अणु
		पूर्णांक x_dअगरf = priv->असल_x - x;
		पूर्णांक y_dअगरf = priv->असल_y - y;
		अगर (hgpk_discard_decay_hack(psmouse, x_dअगरf, y_dअगरf)) अणु
			अगर (tpdebug)
				psmouse_dbg(psmouse, "discarding\n");
			जाओ करोne;
		पूर्ण
		hgpk_spewing_hack(psmouse, left, right, x_dअगरf, y_dअगरf);
	पूर्ण

	input_report_असल(idev, ABS_X, x);
	input_report_असल(idev, ABS_Y, y);
	priv->असल_x = x;
	priv->असल_y = y;

करोne:
	input_sync(idev);
पूर्ण

अटल व्योम hgpk_process_simple_packet(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	अचिन्हित अक्षर *packet = psmouse->packet;
	पूर्णांक left = packet[0] & 1;
	पूर्णांक right = (packet[0] >> 1) & 1;
	पूर्णांक x = packet[1] - ((packet[0] << 4) & 0x100);
	पूर्णांक y = ((packet[0] << 3) & 0x100) - packet[2];

	अगर (packet[0] & 0xc0)
		psmouse_dbg(psmouse,
			    "overflow -- 0x%02x 0x%02x 0x%02x\n",
			    packet[0], packet[1], packet[2]);

	अगर (hgpk_discard_decay_hack(psmouse, x, y)) अणु
		अगर (tpdebug)
			psmouse_dbg(psmouse, "discarding\n");
		वापस;
	पूर्ण

	hgpk_spewing_hack(psmouse, left, right, x, y);

	अगर (tpdebug)
		psmouse_dbg(psmouse, "l=%d r=%d x=%d y=%d\n",
			    left, right, x, y);

	input_report_key(dev, BTN_LEFT, left);
	input_report_key(dev, BTN_RIGHT, right);

	input_report_rel(dev, REL_X, x);
	input_report_rel(dev, REL_Y, y);

	input_sync(dev);
पूर्ण

अटल psmouse_ret_t hgpk_process_byte(काष्ठा psmouse *psmouse)
अणु
	काष्ठा hgpk_data *priv = psmouse->निजी;

	अगर (!hgpk_is_byte_valid(psmouse, psmouse->packet))
		वापस PSMOUSE_BAD_DATA;

	अगर (psmouse->pktcnt >= psmouse->pktsize) अणु
		अगर (priv->mode == HGPK_MODE_MOUSE)
			hgpk_process_simple_packet(psmouse);
		अन्यथा
			hgpk_process_advanced_packet(psmouse);
		वापस PSMOUSE_FULL_PACKET;
	पूर्ण

	अगर (priv->recalib_winकरोw) अणु
		अगर (समय_beक्रमe(jअगरfies, priv->recalib_winकरोw)) अणु
			/*
			 * ugh, got a packet inside our recalibration
			 * winकरोw, schedule another recalibration.
			 */
			psmouse_dbg(psmouse,
				    "packet inside calibration window, queueing another recalibration\n");
			psmouse_queue_work(psmouse, &priv->recalib_wq,
					msecs_to_jअगरfies(post_पूर्णांकerrupt_delay));
		पूर्ण
		priv->recalib_winकरोw = 0;
	पूर्ण

	वापस PSMOUSE_GOOD_DATA;
पूर्ण

अटल पूर्णांक hgpk_select_mode(काष्ठा psmouse *psmouse)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	काष्ठा hgpk_data *priv = psmouse->निजी;
	पूर्णांक i;
	पूर्णांक cmd;

	/*
	 * 4 disables to enable advanced mode
	 * then 3 0xf2 bytes as the preamble क्रम GS/PT selection
	 */
	स्थिर पूर्णांक advanced_init[] = अणु
		PSMOUSE_CMD_DISABLE, PSMOUSE_CMD_DISABLE,
		PSMOUSE_CMD_DISABLE, PSMOUSE_CMD_DISABLE,
		0xf2, 0xf2, 0xf2,
	पूर्ण;

	चयन (priv->mode) अणु
	हाल HGPK_MODE_MOUSE:
		psmouse->pktsize = 3;
		अवरोध;

	हाल HGPK_MODE_GLIDESENSOR:
	हाल HGPK_MODE_PENTABLET:
		psmouse->pktsize = 6;

		/* Switch to 'Advanced mode.', four disables in a row. */
		क्रम (i = 0; i < ARRAY_SIZE(advanced_init); i++)
			अगर (ps2_command(ps2dev, शून्य, advanced_init[i]))
				वापस -EIO;

		/* select between GlideSensor (mouse) or PenTablet */
		cmd = priv->mode == HGPK_MODE_GLIDESENSOR ?
			PSMOUSE_CMD_SETSCALE11 : PSMOUSE_CMD_SETSCALE21;

		अगर (ps2_command(ps2dev, शून्य, cmd))
			वापस -EIO;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hgpk_setup_input_device(काष्ठा input_dev *input,
				    काष्ठा input_dev *old_input,
				    क्रमागत hgpk_mode mode)
अणु
	अगर (old_input) अणु
		input->name = old_input->name;
		input->phys = old_input->phys;
		input->id = old_input->id;
		input->dev.parent = old_input->dev.parent;
	पूर्ण

	स_रखो(input->evbit, 0, माप(input->evbit));
	स_रखो(input->relbit, 0, माप(input->relbit));
	स_रखो(input->keybit, 0, माप(input->keybit));

	/* All modes report left and right buttons */
	__set_bit(EV_KEY, input->evbit);
	__set_bit(BTN_LEFT, input->keybit);
	__set_bit(BTN_RIGHT, input->keybit);

	चयन (mode) अणु
	हाल HGPK_MODE_MOUSE:
		__set_bit(EV_REL, input->evbit);
		__set_bit(REL_X, input->relbit);
		__set_bit(REL_Y, input->relbit);
		अवरोध;

	हाल HGPK_MODE_GLIDESENSOR:
		__set_bit(BTN_TOUCH, input->keybit);
		__set_bit(BTN_TOOL_FINGER, input->keybit);

		__set_bit(EV_ABS, input->evbit);

		/* GlideSensor has pressure sensor, PenTablet करोes not */
		input_set_असल_params(input, ABS_PRESSURE, 0, 15, 0, 0);

		/* From device specs */
		input_set_असल_params(input, ABS_X, 0, 399, 0, 0);
		input_set_असल_params(input, ABS_Y, 0, 290, 0, 0);

		/* Calculated by hand based on usable size (52mm x 38mm) */
		input_असल_set_res(input, ABS_X, 8);
		input_असल_set_res(input, ABS_Y, 8);
		अवरोध;

	हाल HGPK_MODE_PENTABLET:
		__set_bit(BTN_TOUCH, input->keybit);
		__set_bit(BTN_TOOL_FINGER, input->keybit);

		__set_bit(EV_ABS, input->evbit);

		/* From device specs */
		input_set_असल_params(input, ABS_X, 0, 999, 0, 0);
		input_set_असल_params(input, ABS_Y, 5, 239, 0, 0);

		/* Calculated by hand based on usable size (156mm x 38mm) */
		input_असल_set_res(input, ABS_X, 6);
		input_असल_set_res(input, ABS_Y, 8);
		अवरोध;

	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक hgpk_reset_device(काष्ठा psmouse *psmouse, bool recalibrate)
अणु
	पूर्णांक err;

	psmouse_reset(psmouse);

	अगर (recalibrate) अणु
		काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;

		/* send the recalibrate request */
		अगर (ps2_command(ps2dev, शून्य, 0xf5) ||
		    ps2_command(ps2dev, शून्य, 0xf5) ||
		    ps2_command(ps2dev, शून्य, 0xe6) ||
		    ps2_command(ps2dev, शून्य, 0xf5)) अणु
			वापस -1;
		पूर्ण

		/* according to ALPS, 150mS is required क्रम recalibration */
		msleep(150);
	पूर्ण

	err = hgpk_select_mode(psmouse);
	अगर (err) अणु
		psmouse_err(psmouse, "failed to select mode\n");
		वापस err;
	पूर्ण

	hgpk_reset_hack_state(psmouse);

	वापस 0;
पूर्ण

अटल पूर्णांक hgpk_क्रमce_recalibrate(काष्ठा psmouse *psmouse)
अणु
	काष्ठा hgpk_data *priv = psmouse->निजी;
	पूर्णांक err;

	/* C-series touchpads added the recalibrate command */
	अगर (psmouse->model < HGPK_MODEL_C)
		वापस 0;

	अगर (!स्वतःrecal) अणु
		psmouse_dbg(psmouse, "recalibration disabled, ignoring\n");
		वापस 0;
	पूर्ण

	psmouse_dbg(psmouse, "recalibrating touchpad..\n");

	/* we करोn't want to race with the irq handler, nor with resyncs */
	psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);

	/* start by resetting the device */
	err = hgpk_reset_device(psmouse, true);
	अगर (err)
		वापस err;

	/*
	 * XXX: If a finger is करोwn during this delay, recalibration will
	 * detect capacitance incorrectly.  This is a hardware bug, and
	 * we करोn't have a good way to deal with it.  The 2s winकरोw stuff
	 * (below) is our best option क्रम now.
	 */
	अगर (psmouse_activate(psmouse))
		वापस -1;

	अगर (tpdebug)
		psmouse_dbg(psmouse, "touchpad reactivated\n");

	/*
	 * If we get packets right away after recalibrating, it's likely
	 * that a finger was on the touchpad.  If so, it's probably
	 * miscalibrated, so we optionally schedule another.
	 */
	अगर (recal_guard_समय)
		priv->recalib_winकरोw = jअगरfies +
			msecs_to_jअगरfies(recal_guard_समय);

	वापस 0;
पूर्ण

/*
 * This माला_दो the touchpad in a घातer saving mode; according to ALPS, current
 * consumption goes करोwn to 50uA after running this.  To turn घातer back on,
 * we drive MS-DAT low.  Measuring with a 1mA resolution ammeter says that
 * the current on the SUS_3.3V rail drops from 3mA or 4mA to 0 when we करो this.
 *
 * We have no क्रमmal spec that details this operation -- the low-घातer
 * sequence came from a दीर्घ-lost email trail.
 */
अटल पूर्णांक hgpk_toggle_घातersave(काष्ठा psmouse *psmouse, पूर्णांक enable)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	पूर्णांक समयo;
	पूर्णांक err;

	/* Added on D-series touchpads */
	अगर (psmouse->model < HGPK_MODEL_D)
		वापस 0;

	अगर (enable) अणु
		psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);

		/*
		 * Sending a byte will drive MS-DAT low; this will wake up
		 * the controller.  Once we get an ACK back from it, it
		 * means we can जारी with the touchpad re-init.  ALPS
		 * tells us that 1s should be दीर्घ enough, so set that as
		 * the upper bound. (in practice, it takes about 3 loops.)
		 */
		क्रम (समयo = 20; समयo > 0; समयo--) अणु
			अगर (!ps2_sendbyte(ps2dev, PSMOUSE_CMD_DISABLE, 20))
				अवरोध;
			msleep(25);
		पूर्ण

		err = hgpk_reset_device(psmouse, false);
		अगर (err) अणु
			psmouse_err(psmouse, "Failed to reset device!\n");
			वापस err;
		पूर्ण

		/* should be all set, enable the touchpad */
		psmouse_activate(psmouse);
		psmouse_dbg(psmouse, "Touchpad powered up.\n");
	पूर्ण अन्यथा अणु
		psmouse_dbg(psmouse, "Powering off touchpad.\n");

		अगर (ps2_command(ps2dev, शून्य, 0xec) ||
		    ps2_command(ps2dev, शून्य, 0xec) ||
		    ps2_command(ps2dev, शून्य, 0xea)) अणु
			वापस -1;
		पूर्ण

		psmouse_set_state(psmouse, PSMOUSE_IGNORE);

		/* probably won't see an ACK, the touchpad will be off */
		ps2_sendbyte(ps2dev, 0xec, 20);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hgpk_poll(काष्ठा psmouse *psmouse)
अणु
	/* We can't poll, so always वापस failure. */
	वापस -1;
पूर्ण

अटल पूर्णांक hgpk_reconnect(काष्ठा psmouse *psmouse)
अणु
	काष्ठा hgpk_data *priv = psmouse->निजी;

	/*
	 * During suspend/resume the ps2 rails reमुख्य घातered.  We करोn't want
	 * to करो a reset because it's flush data out of buffers; however,
	 * earlier prototypes (B1) had some brokenness that required a reset.
	 */
	अगर (olpc_board_at_least(olpc_board(0xb2)))
		अगर (psmouse->ps2dev.serio->dev.घातer.घातer_state.event !=
				PM_EVENT_ON)
			वापस 0;

	priv->घातered = 1;
	वापस hgpk_reset_device(psmouse, false);
पूर्ण

अटल sमाप_प्रकार hgpk_show_घातered(काष्ठा psmouse *psmouse, व्योम *data, अक्षर *buf)
अणु
	काष्ठा hgpk_data *priv = psmouse->निजी;

	वापस प्र_लिखो(buf, "%d\n", priv->घातered);
पूर्ण

अटल sमाप_प्रकार hgpk_set_घातered(काष्ठा psmouse *psmouse, व्योम *data,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hgpk_data *priv = psmouse->निजी;
	अचिन्हित पूर्णांक value;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	अगर (value > 1)
		वापस -EINVAL;

	अगर (value != priv->घातered) अणु
		/*
		 * hgpk_toggle_घातer will deal w/ state so
		 * we're not racing w/ irq
		 */
		err = hgpk_toggle_घातersave(psmouse, value);
		अगर (!err)
			priv->घातered = value;
	पूर्ण

	वापस err ? err : count;
पूर्ण

__PSMOUSE_DEFINE_ATTR(घातered, S_IWUSR | S_IRUGO, शून्य,
		      hgpk_show_घातered, hgpk_set_घातered, false);

अटल sमाप_प्रकार attr_show_mode(काष्ठा psmouse *psmouse, व्योम *data, अक्षर *buf)
अणु
	काष्ठा hgpk_data *priv = psmouse->निजी;

	वापस प्र_लिखो(buf, "%s\n", hgpk_mode_names[priv->mode]);
पूर्ण

अटल sमाप_प्रकार attr_set_mode(काष्ठा psmouse *psmouse, व्योम *data,
			     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा hgpk_data *priv = psmouse->निजी;
	क्रमागत hgpk_mode old_mode = priv->mode;
	क्रमागत hgpk_mode new_mode = hgpk_mode_from_name(buf, len);
	काष्ठा input_dev *old_dev = psmouse->dev;
	काष्ठा input_dev *new_dev;
	पूर्णांक err;

	अगर (new_mode == HGPK_MODE_INVALID)
		वापस -EINVAL;

	अगर (old_mode == new_mode)
		वापस len;

	new_dev = input_allocate_device();
	अगर (!new_dev)
		वापस -ENOMEM;

	psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);

	/* Switch device पूर्णांकo the new mode */
	priv->mode = new_mode;
	err = hgpk_reset_device(psmouse, false);
	अगर (err)
		जाओ err_try_restore;

	hgpk_setup_input_device(new_dev, old_dev, new_mode);

	psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);

	err = input_रेजिस्टर_device(new_dev);
	अगर (err)
		जाओ err_try_restore;

	psmouse->dev = new_dev;
	input_unरेजिस्टर_device(old_dev);

	वापस len;

err_try_restore:
	input_मुक्त_device(new_dev);
	priv->mode = old_mode;
	hgpk_reset_device(psmouse, false);

	वापस err;
पूर्ण

PSMOUSE_DEFINE_ATTR(hgpk_mode, S_IWUSR | S_IRUGO, शून्य,
		    attr_show_mode, attr_set_mode);

अटल sमाप_प्रकार hgpk_trigger_recal_show(काष्ठा psmouse *psmouse,
		व्योम *data, अक्षर *buf)
अणु
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार hgpk_trigger_recal(काष्ठा psmouse *psmouse, व्योम *data,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hgpk_data *priv = psmouse->निजी;
	अचिन्हित पूर्णांक value;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	अगर (value != 1)
		वापस -EINVAL;

	/*
	 * We queue work instead of करोing recalibration right here
	 * to aव्योम adding locking to to hgpk_क्रमce_recalibrate()
	 * since workqueue provides serialization.
	 */
	psmouse_queue_work(psmouse, &priv->recalib_wq, 0);
	वापस count;
पूर्ण

__PSMOUSE_DEFINE_ATTR(recalibrate, S_IWUSR | S_IRUGO, शून्य,
		      hgpk_trigger_recal_show, hgpk_trigger_recal, false);

अटल व्योम hgpk_disconnect(काष्ठा psmouse *psmouse)
अणु
	काष्ठा hgpk_data *priv = psmouse->निजी;

	device_हटाओ_file(&psmouse->ps2dev.serio->dev,
			   &psmouse_attr_घातered.dattr);
	device_हटाओ_file(&psmouse->ps2dev.serio->dev,
			   &psmouse_attr_hgpk_mode.dattr);

	अगर (psmouse->model >= HGPK_MODEL_C)
		device_हटाओ_file(&psmouse->ps2dev.serio->dev,
				   &psmouse_attr_recalibrate.dattr);

	psmouse_reset(psmouse);
	kमुक्त(priv);
पूर्ण

अटल व्योम hgpk_recalib_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *w = to_delayed_work(work);
	काष्ठा hgpk_data *priv = container_of(w, काष्ठा hgpk_data, recalib_wq);
	काष्ठा psmouse *psmouse = priv->psmouse;

	अगर (hgpk_क्रमce_recalibrate(psmouse))
		psmouse_err(psmouse, "recalibration failed!\n");
पूर्ण

अटल पूर्णांक hgpk_रेजिस्टर(काष्ठा psmouse *psmouse)
अणु
	काष्ठा hgpk_data *priv = psmouse->निजी;
	पूर्णांक err;

	/* रेजिस्टर handlers */
	psmouse->protocol_handler = hgpk_process_byte;
	psmouse->poll = hgpk_poll;
	psmouse->disconnect = hgpk_disconnect;
	psmouse->reconnect = hgpk_reconnect;

	/* Disable the idle resync. */
	psmouse->resync_समय = 0;
	/* Reset after a lot of bad bytes. */
	psmouse->resetafter = 1024;

	hgpk_setup_input_device(psmouse->dev, शून्य, priv->mode);

	err = device_create_file(&psmouse->ps2dev.serio->dev,
				 &psmouse_attr_घातered.dattr);
	अगर (err) अणु
		psmouse_err(psmouse, "Failed creating 'powered' sysfs node\n");
		वापस err;
	पूर्ण

	err = device_create_file(&psmouse->ps2dev.serio->dev,
				 &psmouse_attr_hgpk_mode.dattr);
	अगर (err) अणु
		psmouse_err(psmouse,
			    "Failed creating 'hgpk_mode' sysfs node\n");
		जाओ err_हटाओ_घातered;
	पूर्ण

	/* C-series touchpads added the recalibrate command */
	अगर (psmouse->model >= HGPK_MODEL_C) अणु
		err = device_create_file(&psmouse->ps2dev.serio->dev,
					 &psmouse_attr_recalibrate.dattr);
		अगर (err) अणु
			psmouse_err(psmouse,
				    "Failed creating 'recalibrate' sysfs node\n");
			जाओ err_हटाओ_mode;
		पूर्ण
	पूर्ण

	वापस 0;

err_हटाओ_mode:
	device_हटाओ_file(&psmouse->ps2dev.serio->dev,
			   &psmouse_attr_hgpk_mode.dattr);
err_हटाओ_घातered:
	device_हटाओ_file(&psmouse->ps2dev.serio->dev,
			   &psmouse_attr_घातered.dattr);
	वापस err;
पूर्ण

पूर्णांक hgpk_init(काष्ठा psmouse *psmouse)
अणु
	काष्ठा hgpk_data *priv;
	पूर्णांक err;

	priv = kzalloc(माप(काष्ठा hgpk_data), GFP_KERNEL);
	अगर (!priv) अणु
		err = -ENOMEM;
		जाओ alloc_fail;
	पूर्ण

	psmouse->निजी = priv;

	priv->psmouse = psmouse;
	priv->घातered = true;
	priv->mode = hgpk_शेष_mode;
	INIT_DELAYED_WORK(&priv->recalib_wq, hgpk_recalib_work);

	err = hgpk_reset_device(psmouse, false);
	अगर (err)
		जाओ init_fail;

	err = hgpk_रेजिस्टर(psmouse);
	अगर (err)
		जाओ init_fail;

	वापस 0;

init_fail:
	kमुक्त(priv);
alloc_fail:
	वापस err;
पूर्ण

अटल क्रमागत hgpk_model_t hgpk_get_model(काष्ठा psmouse *psmouse)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	अचिन्हित अक्षर param[3];

	/* E7, E7, E7, E9 माला_लो us a 3 byte identअगरier */
	अगर (ps2_command(ps2dev,  शून्य, PSMOUSE_CMD_SETSCALE21) ||
	    ps2_command(ps2dev,  शून्य, PSMOUSE_CMD_SETSCALE21) ||
	    ps2_command(ps2dev,  शून्य, PSMOUSE_CMD_SETSCALE21) ||
	    ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO)) अणु
		वापस -EIO;
	पूर्ण

	psmouse_dbg(psmouse, "ID: %*ph\n", 3, param);

	/* HGPK signature: 0x67, 0x00, 0x<model> */
	अगर (param[0] != 0x67 || param[1] != 0x00)
		वापस -ENODEV;

	psmouse_info(psmouse, "OLPC touchpad revision 0x%x\n", param[2]);

	वापस param[2];
पूर्ण

पूर्णांक hgpk_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	पूर्णांक version;

	version = hgpk_get_model(psmouse);
	अगर (version < 0)
		वापस version;

	अगर (set_properties) अणु
		psmouse->venकरोr = "ALPS";
		psmouse->name = "HGPK";
		psmouse->model = version;
	पूर्ण

	वापस 0;
पूर्ण

व्योम hgpk_module_init(व्योम)
अणु
	hgpk_शेष_mode = hgpk_mode_from_name(hgpk_mode_name,
						म_माप(hgpk_mode_name));
	अगर (hgpk_शेष_mode == HGPK_MODE_INVALID) अणु
		hgpk_शेष_mode = HGPK_MODE_MOUSE;
		strlcpy(hgpk_mode_name, hgpk_mode_names[HGPK_MODE_MOUSE],
			माप(hgpk_mode_name));
	पूर्ण
पूर्ण
