<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PS/2 mouse driver
 *
 * Copyright (c) 1999-2002 Vojtech Pavlik
 * Copyright (c) 2003-2004 Dmitry Torokhov
 */


#घोषणा pr_fmt(fmt)		KBUILD_MODNAME ": " fmt
#घोषणा psmouse_fmt(fmt)	fmt

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>
#समावेश <linux/init.h>
#समावेश <linux/libps2.h>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>

#समावेश "psmouse.h"
#समावेश "synaptics.h"
#समावेश "logips2pp.h"
#समावेश "alps.h"
#समावेश "hgpk.h"
#समावेश "lifebook.h"
#समावेश "trackpoint.h"
#समावेश "touchkit_ps2.h"
#समावेश "elantech.h"
#समावेश "sentelic.h"
#समावेश "cypress_ps2.h"
#समावेश "focaltech.h"
#समावेश "vmmouse.h"
#समावेश "byd.h"

#घोषणा DRIVER_DESC	"PS/2 mouse driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@suse.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक psmouse_max_proto = PSMOUSE_AUTO;
अटल पूर्णांक psmouse_set_maxproto(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *);
अटल पूर्णांक psmouse_get_maxproto(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
अटल स्थिर काष्ठा kernel_param_ops param_ops_proto_abbrev = अणु
	.set = psmouse_set_maxproto,
	.get = psmouse_get_maxproto,
पूर्ण;
#घोषणा param_check_proto_abbrev(name, p)	__param_check(name, p, अचिन्हित पूर्णांक)
module_param_named(proto, psmouse_max_proto, proto_abbrev, 0644);
MODULE_PARM_DESC(proto, "Highest protocol extension to probe (bare, imps, exps, any). Useful for KVM switches.");

अटल अचिन्हित पूर्णांक psmouse_resolution = 200;
module_param_named(resolution, psmouse_resolution, uपूर्णांक, 0644);
MODULE_PARM_DESC(resolution, "Resolution, in dpi.");

अटल अचिन्हित पूर्णांक psmouse_rate = 100;
module_param_named(rate, psmouse_rate, uपूर्णांक, 0644);
MODULE_PARM_DESC(rate, "Report rate, in reports per second.");

अटल bool psmouse_smartscroll = true;
module_param_named(smartscroll, psmouse_smartscroll, bool, 0644);
MODULE_PARM_DESC(smartscroll, "Logitech Smartscroll autorepeat, 1 = enabled (default), 0 = disabled.");

अटल bool psmouse_a4tech_2wheels;
module_param_named(a4tech_workaround, psmouse_a4tech_2wheels, bool, 0644);
MODULE_PARM_DESC(a4tech_workaround, "A4Tech second scroll wheel workaround, 1 = enabled, 0 = disabled (default).");

अटल अचिन्हित पूर्णांक psmouse_resetafter = 5;
module_param_named(resetafter, psmouse_resetafter, uपूर्णांक, 0644);
MODULE_PARM_DESC(resetafter, "Reset device after so many bad packets (0 = never).");

अटल अचिन्हित पूर्णांक psmouse_resync_समय;
module_param_named(resync_समय, psmouse_resync_समय, uपूर्णांक, 0644);
MODULE_PARM_DESC(resync_समय, "How long can mouse stay idle before forcing resync (in seconds, 0 = never).");

PSMOUSE_DEFINE_ATTR(protocol, S_IWUSR | S_IRUGO,
			शून्य,
			psmouse_attr_show_protocol, psmouse_attr_set_protocol);
PSMOUSE_DEFINE_ATTR(rate, S_IWUSR | S_IRUGO,
			(व्योम *) दुरत्व(काष्ठा psmouse, rate),
			psmouse_show_पूर्णांक_attr, psmouse_attr_set_rate);
PSMOUSE_DEFINE_ATTR(resolution, S_IWUSR | S_IRUGO,
			(व्योम *) दुरत्व(काष्ठा psmouse, resolution),
			psmouse_show_पूर्णांक_attr, psmouse_attr_set_resolution);
PSMOUSE_DEFINE_ATTR(resetafter, S_IWUSR | S_IRUGO,
			(व्योम *) दुरत्व(काष्ठा psmouse, resetafter),
			psmouse_show_पूर्णांक_attr, psmouse_set_पूर्णांक_attr);
PSMOUSE_DEFINE_ATTR(resync_समय, S_IWUSR | S_IRUGO,
			(व्योम *) दुरत्व(काष्ठा psmouse, resync_समय),
			psmouse_show_पूर्णांक_attr, psmouse_set_पूर्णांक_attr);

अटल काष्ठा attribute *psmouse_attributes[] = अणु
	&psmouse_attr_protocol.dattr.attr,
	&psmouse_attr_rate.dattr.attr,
	&psmouse_attr_resolution.dattr.attr,
	&psmouse_attr_resetafter.dattr.attr,
	&psmouse_attr_resync_समय.dattr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group psmouse_attribute_group = अणु
	.attrs	= psmouse_attributes,
पूर्ण;

/*
 * psmouse_mutex protects all operations changing state of mouse
 * (connecting, disconnecting, changing rate or resolution via
 * sysfs). We could use a per-device semaphore but since there
 * rarely more than one PS/2 mouse connected and since semaphore
 * is taken in "slow" paths it is not worth it.
 */
अटल DEFINE_MUTEX(psmouse_mutex);

अटल काष्ठा workqueue_काष्ठा *kpsmoused_wq;

व्योम psmouse_report_standard_buttons(काष्ठा input_dev *dev, u8 buttons)
अणु
	input_report_key(dev, BTN_LEFT,   buttons & BIT(0));
	input_report_key(dev, BTN_MIDDLE, buttons & BIT(2));
	input_report_key(dev, BTN_RIGHT,  buttons & BIT(1));
पूर्ण

व्योम psmouse_report_standard_motion(काष्ठा input_dev *dev, u8 *packet)
अणु
	पूर्णांक x, y;

	x = packet[1] ? packet[1] - ((packet[0] << 4) & 0x100) : 0;
	y = packet[2] ? packet[2] - ((packet[0] << 3) & 0x100) : 0;

	input_report_rel(dev, REL_X, x);
	input_report_rel(dev, REL_Y, -y);
पूर्ण

व्योम psmouse_report_standard_packet(काष्ठा input_dev *dev, u8 *packet)
अणु
	psmouse_report_standard_buttons(dev, packet[0]);
	psmouse_report_standard_motion(dev, packet);
पूर्ण

/*
 * psmouse_process_byte() analyzes the PS/2 data stream and reports
 * relevant events to the input module once full packet has arrived.
 */
psmouse_ret_t psmouse_process_byte(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	u8 *packet = psmouse->packet;
	पूर्णांक wheel;

	अगर (psmouse->pktcnt < psmouse->pktsize)
		वापस PSMOUSE_GOOD_DATA;

	/* Full packet accumulated, process it */

	चयन (psmouse->protocol->type) अणु
	हाल PSMOUSE_IMPS:
		/* IntelliMouse has scroll wheel */
		input_report_rel(dev, REL_WHEEL, -(s8) packet[3]);
		अवरोध;

	हाल PSMOUSE_IMEX:
		/* Scroll wheel and buttons on IntelliMouse Explorer */
		चयन (packet[3] & 0xC0) अणु
		हाल 0x80: /* vertical scroll on IntelliMouse Explorer 4.0 */
			input_report_rel(dev, REL_WHEEL,
					 -sign_extend32(packet[3], 5));
			अवरोध;
		हाल 0x40: /* horizontal scroll on IntelliMouse Explorer 4.0 */
			input_report_rel(dev, REL_HWHEEL,
					 -sign_extend32(packet[3], 5));
			अवरोध;
		हाल 0x00:
		हाल 0xC0:
			wheel = sign_extend32(packet[3], 3);

			/*
			 * Some A4Tech mice have two scroll wheels, with first
			 * one reporting +/-1 in the lower nibble, and second
			 * one reporting +/-2.
			 */
			अगर (psmouse_a4tech_2wheels && असल(wheel) > 1)
				input_report_rel(dev, REL_HWHEEL, wheel / 2);
			अन्यथा
				input_report_rel(dev, REL_WHEEL, -wheel);

			input_report_key(dev, BTN_SIDE,  packet[3] & BIT(4));
			input_report_key(dev, BTN_EXTRA, packet[3] & BIT(5));
			अवरोध;
		पूर्ण
		अवरोध;

	हाल PSMOUSE_GENPS:
		/* Report scroll buttons on NetMice */
		input_report_rel(dev, REL_WHEEL, -(s8) packet[3]);

		/* Extra buttons on Genius NewNet 3D */
		input_report_key(dev, BTN_SIDE,  packet[0] & BIT(6));
		input_report_key(dev, BTN_EXTRA, packet[0] & BIT(7));
		अवरोध;

	हाल PSMOUSE_THINKPS:
		/* Extra button on ThinkingMouse */
		input_report_key(dev, BTN_EXTRA, packet[0] & BIT(3));

		/*
		 * Without this bit of weirdness moving up gives wildly
		 * high Y changes.
		 */
		packet[1] |= (packet[0] & 0x40) << 1;
		अवरोध;

	हाल PSMOUSE_CORTRON:
		/*
		 * Cortron PS2 Trackball reports SIDE button in the
		 * 4th bit of the first byte.
		 */
		input_report_key(dev, BTN_SIDE, packet[0] & BIT(3));
		packet[0] |= BIT(3);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/* Generic PS/2 Mouse */
	packet[0] |= psmouse->extra_buttons;
	psmouse_report_standard_packet(dev, packet);

	input_sync(dev);

	वापस PSMOUSE_FULL_PACKET;
पूर्ण

व्योम psmouse_queue_work(काष्ठा psmouse *psmouse, काष्ठा delayed_work *work,
		अचिन्हित दीर्घ delay)
अणु
	queue_delayed_work(kpsmoused_wq, work, delay);
पूर्ण

/*
 * __psmouse_set_state() sets new psmouse state and resets all flags.
 */
अटल अंतरभूत व्योम __psmouse_set_state(काष्ठा psmouse *psmouse, क्रमागत psmouse_state new_state)
अणु
	psmouse->state = new_state;
	psmouse->pktcnt = psmouse->out_of_sync_cnt = 0;
	psmouse->ps2dev.flags = 0;
	psmouse->last = jअगरfies;
पूर्ण

/*
 * psmouse_set_state() sets new psmouse state and resets all flags and
 * counters जबतक holding serio lock so fighting with पूर्णांकerrupt handler
 * is not a concern.
 */
व्योम psmouse_set_state(काष्ठा psmouse *psmouse, क्रमागत psmouse_state new_state)
अणु
	serio_छोड़ो_rx(psmouse->ps2dev.serio);
	__psmouse_set_state(psmouse, new_state);
	serio_जारी_rx(psmouse->ps2dev.serio);
पूर्ण

/*
 * psmouse_handle_byte() processes one byte of the input data stream
 * by calling corresponding protocol handler.
 */
अटल पूर्णांक psmouse_handle_byte(काष्ठा psmouse *psmouse)
अणु
	psmouse_ret_t rc = psmouse->protocol_handler(psmouse);

	चयन (rc) अणु
	हाल PSMOUSE_BAD_DATA:
		अगर (psmouse->state == PSMOUSE_ACTIVATED) अणु
			psmouse_warn(psmouse,
				     "%s at %s lost sync at byte %d\n",
				     psmouse->name, psmouse->phys,
				     psmouse->pktcnt);
			अगर (++psmouse->out_of_sync_cnt == psmouse->resetafter) अणु
				__psmouse_set_state(psmouse, PSMOUSE_IGNORE);
				psmouse_notice(psmouse,
						"issuing reconnect request\n");
				serio_reconnect(psmouse->ps2dev.serio);
				वापस -EIO;
			पूर्ण
		पूर्ण
		psmouse->pktcnt = 0;
		अवरोध;

	हाल PSMOUSE_FULL_PACKET:
		psmouse->pktcnt = 0;
		अगर (psmouse->out_of_sync_cnt) अणु
			psmouse->out_of_sync_cnt = 0;
			psmouse_notice(psmouse,
					"%s at %s - driver resynced.\n",
					psmouse->name, psmouse->phys);
		पूर्ण
		अवरोध;

	हाल PSMOUSE_GOOD_DATA:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम psmouse_handle_oob_data(काष्ठा psmouse *psmouse, u8 data)
अणु
	चयन (psmouse->oob_data_type) अणु
	हाल PSMOUSE_OOB_NONE:
		psmouse->oob_data_type = data;
		अवरोध;

	हाल PSMOUSE_OOB_EXTRA_BTNS:
		psmouse_report_standard_buttons(psmouse->dev, data);
		input_sync(psmouse->dev);

		psmouse->extra_buttons = data;
		psmouse->oob_data_type = PSMOUSE_OOB_NONE;
		अवरोध;

	शेष:
		psmouse_warn(psmouse,
			     "unknown OOB_DATA type: 0x%02x\n",
			     psmouse->oob_data_type);
		psmouse->oob_data_type = PSMOUSE_OOB_NONE;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * psmouse_पूर्णांकerrupt() handles incoming अक्षरacters, either passing them
 * क्रम normal processing or gathering them as command response.
 */
अटल irqवापस_t psmouse_पूर्णांकerrupt(काष्ठा serio *serio,
				     u8 data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा psmouse *psmouse = serio_get_drvdata(serio);

	अगर (psmouse->state == PSMOUSE_IGNORE)
		जाओ out;

	अगर (unlikely((flags & SERIO_TIMEOUT) ||
		     ((flags & SERIO_PARITY) &&
		      !psmouse->protocol->ignore_parity))) अणु

		अगर (psmouse->state == PSMOUSE_ACTIVATED)
			psmouse_warn(psmouse,
				     "bad data from KBC -%s%s\n",
				     flags & SERIO_TIMEOUT ? " timeout" : "",
				     flags & SERIO_PARITY ? " bad parity" : "");
		ps2_cmd_पातed(&psmouse->ps2dev);
		जाओ out;
	पूर्ण

	अगर (flags & SERIO_OOB_DATA) अणु
		psmouse_handle_oob_data(psmouse, data);
		जाओ out;
	पूर्ण

	अगर (unlikely(psmouse->ps2dev.flags & PS2_FLAG_ACK))
		अगर  (ps2_handle_ack(&psmouse->ps2dev, data))
			जाओ out;

	अगर (unlikely(psmouse->ps2dev.flags & PS2_FLAG_CMD))
		अगर  (ps2_handle_response(&psmouse->ps2dev, data))
			जाओ out;

	pm_wakeup_event(&serio->dev, 0);

	अगर (psmouse->state <= PSMOUSE_RESYNCING)
		जाओ out;

	अगर (psmouse->state == PSMOUSE_ACTIVATED &&
	    psmouse->pktcnt && समय_after(jअगरfies, psmouse->last + HZ/2)) अणु
		psmouse_info(psmouse, "%s at %s lost synchronization, throwing %d bytes away.\n",
			     psmouse->name, psmouse->phys, psmouse->pktcnt);
		psmouse->badbyte = psmouse->packet[0];
		__psmouse_set_state(psmouse, PSMOUSE_RESYNCING);
		psmouse_queue_work(psmouse, &psmouse->resync_work, 0);
		जाओ out;
	पूर्ण

	psmouse->packet[psmouse->pktcnt++] = data;

	/* Check अगर this is a new device announcement (0xAA 0x00) */
	अगर (unlikely(psmouse->packet[0] == PSMOUSE_RET_BAT && psmouse->pktcnt <= 2)) अणु
		अगर (psmouse->pktcnt == 1) अणु
			psmouse->last = jअगरfies;
			जाओ out;
		पूर्ण

		अगर (psmouse->packet[1] == PSMOUSE_RET_ID ||
		    (psmouse->protocol->type == PSMOUSE_HGPK &&
		     psmouse->packet[1] == PSMOUSE_RET_BAT)) अणु
			__psmouse_set_state(psmouse, PSMOUSE_IGNORE);
			serio_reconnect(serio);
			जाओ out;
		पूर्ण

		/* Not a new device, try processing first byte normally */
		psmouse->pktcnt = 1;
		अगर (psmouse_handle_byte(psmouse))
			जाओ out;

		psmouse->packet[psmouse->pktcnt++] = data;
	पूर्ण

	/*
	 * See अगर we need to क्रमce resync because mouse was idle क्रम
	 * too दीर्घ.
	 */
	अगर (psmouse->state == PSMOUSE_ACTIVATED &&
	    psmouse->pktcnt == 1 && psmouse->resync_समय &&
	    समय_after(jअगरfies, psmouse->last + psmouse->resync_समय * HZ)) अणु
		psmouse->badbyte = psmouse->packet[0];
		__psmouse_set_state(psmouse, PSMOUSE_RESYNCING);
		psmouse_queue_work(psmouse, &psmouse->resync_work, 0);
		जाओ out;
	पूर्ण

	psmouse->last = jअगरfies;
	psmouse_handle_byte(psmouse);

 out:
	वापस IRQ_HANDLED;
पूर्ण

/*
 * psmouse_reset() resets the mouse पूर्णांकo घातer-on state.
 */
पूर्णांक psmouse_reset(काष्ठा psmouse *psmouse)
अणु
	u8 param[2];
	पूर्णांक error;

	error = ps2_command(&psmouse->ps2dev, param, PSMOUSE_CMD_RESET_BAT);
	अगर (error)
		वापस error;

	अगर (param[0] != PSMOUSE_RET_BAT && param[1] != PSMOUSE_RET_ID)
		वापस -EIO;

	वापस 0;
पूर्ण

/*
 * Here we set the mouse resolution.
 */
व्योम psmouse_set_resolution(काष्ठा psmouse *psmouse, अचिन्हित पूर्णांक resolution)
अणु
	अटल स्थिर u8 params[] = अणु 0, 1, 2, 2, 3 पूर्ण;
	u8 p;

	अगर (resolution == 0 || resolution > 200)
		resolution = 200;

	p = params[resolution / 50];
	ps2_command(&psmouse->ps2dev, &p, PSMOUSE_CMD_SETRES);
	psmouse->resolution = 25 << p;
पूर्ण

/*
 * Here we set the mouse report rate.
 */
अटल व्योम psmouse_set_rate(काष्ठा psmouse *psmouse, अचिन्हित पूर्णांक rate)
अणु
	अटल स्थिर u8 rates[] = अणु 200, 100, 80, 60, 40, 20, 10, 0 पूर्ण;
	u8 r;
	पूर्णांक i = 0;

	जबतक (rates[i] > rate)
		i++;
	r = rates[i];
	ps2_command(&psmouse->ps2dev, &r, PSMOUSE_CMD_SETRATE);
	psmouse->rate = r;
पूर्ण

/*
 * Here we set the mouse scaling.
 */
अटल व्योम psmouse_set_scale(काष्ठा psmouse *psmouse, क्रमागत psmouse_scale scale)
अणु
	ps2_command(&psmouse->ps2dev, शून्य,
		    scale == PSMOUSE_SCALE21 ? PSMOUSE_CMD_SETSCALE21 :
					       PSMOUSE_CMD_SETSCALE11);
पूर्ण

/*
 * psmouse_poll() - शेष poll handler. Everyone except क्रम ALPS uses it.
 */
अटल पूर्णांक psmouse_poll(काष्ठा psmouse *psmouse)
अणु
	वापस ps2_command(&psmouse->ps2dev, psmouse->packet,
			   PSMOUSE_CMD_POLL | (psmouse->pktsize << 8));
पूर्ण

अटल bool psmouse_check_pnp_id(स्थिर अक्षर *id, स्थिर अक्षर * स्थिर ids[])
अणु
	पूर्णांक i;

	क्रम (i = 0; ids[i]; i++)
		अगर (!strहालcmp(id, ids[i]))
			वापस true;

	वापस false;
पूर्ण

/*
 * psmouse_matches_pnp_id - check अगर psmouse matches one of the passed in ids.
 */
bool psmouse_matches_pnp_id(काष्ठा psmouse *psmouse, स्थिर अक्षर * स्थिर ids[])
अणु
	काष्ठा serio *serio = psmouse->ps2dev.serio;
	अक्षर *p, *fw_id_copy, *save_ptr;
	bool found = false;

	अगर (म_भेदन(serio->firmware_id, "PNP: ", 5))
		वापस false;

	fw_id_copy = kstrndup(&serio->firmware_id[5],
			      माप(serio->firmware_id) - 5,
			      GFP_KERNEL);
	अगर (!fw_id_copy)
		वापस false;

	save_ptr = fw_id_copy;
	जबतक ((p = strsep(&fw_id_copy, " ")) != शून्य) अणु
		अगर (psmouse_check_pnp_id(p, ids)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(save_ptr);
	वापस found;
पूर्ण

/*
 * Genius NetMouse magic init.
 */
अटल पूर्णांक genius_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	u8 param[4];

	param[0] = 3;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	ps2_command(ps2dev,  शून्य, PSMOUSE_CMD_SETSCALE11);
	ps2_command(ps2dev,  शून्य, PSMOUSE_CMD_SETSCALE11);
	ps2_command(ps2dev,  शून्य, PSMOUSE_CMD_SETSCALE11);
	ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO);

	अगर (param[0] != 0x00 || param[1] != 0x33 || param[2] != 0x55)
		वापस -ENODEV;

	अगर (set_properties) अणु
		__set_bit(BTN_MIDDLE, psmouse->dev->keybit);
		__set_bit(BTN_EXTRA, psmouse->dev->keybit);
		__set_bit(BTN_SIDE, psmouse->dev->keybit);
		__set_bit(REL_WHEEL, psmouse->dev->relbit);

		psmouse->venकरोr = "Genius";
		psmouse->name = "Mouse";
		psmouse->pktsize = 4;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * IntelliMouse magic init.
 */
अटल पूर्णांक पूर्णांकellimouse_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	u8 param[2];

	param[0] = 200;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);
	param[0] = 100;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);
	param[0] =  80;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);
	ps2_command(ps2dev, param, PSMOUSE_CMD_GETID);

	अगर (param[0] != 3)
		वापस -ENODEV;

	अगर (set_properties) अणु
		__set_bit(BTN_MIDDLE, psmouse->dev->keybit);
		__set_bit(REL_WHEEL, psmouse->dev->relbit);

		अगर (!psmouse->venकरोr)
			psmouse->venकरोr = "Generic";
		अगर (!psmouse->name)
			psmouse->name = "Wheel Mouse";
		psmouse->pktsize = 4;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Try IntelliMouse/Explorer magic init.
 */
अटल पूर्णांक im_explorer_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	u8 param[2];

	पूर्णांकellimouse_detect(psmouse, 0);

	param[0] = 200;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);
	param[0] = 200;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);
	param[0] =  80;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);
	ps2_command(ps2dev, param, PSMOUSE_CMD_GETID);

	अगर (param[0] != 4)
		वापस -ENODEV;

	/* Magic to enable horizontal scrolling on IntelliMouse 4.0 */
	param[0] = 200;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);
	param[0] =  80;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);
	param[0] =  40;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);

	अगर (set_properties) अणु
		__set_bit(BTN_MIDDLE, psmouse->dev->keybit);
		__set_bit(REL_WHEEL, psmouse->dev->relbit);
		__set_bit(REL_HWHEEL, psmouse->dev->relbit);
		__set_bit(BTN_SIDE, psmouse->dev->keybit);
		__set_bit(BTN_EXTRA, psmouse->dev->keybit);

		अगर (!psmouse->venकरोr)
			psmouse->venकरोr = "Generic";
		अगर (!psmouse->name)
			psmouse->name = "Explorer Mouse";
		psmouse->pktsize = 4;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Kensington ThinkingMouse / ExpertMouse magic init.
 */
अटल पूर्णांक thinking_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	u8 param[2];
	अटल स्थिर u8 seq[] = अणु 20, 60, 40, 20, 20, 60, 40, 20, 20 पूर्ण;
	पूर्णांक i;

	param[0] = 10;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);
	param[0] = 0;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	क्रम (i = 0; i < ARRAY_SIZE(seq); i++) अणु
		param[0] = seq[i];
		ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);
	पूर्ण
	ps2_command(ps2dev, param, PSMOUSE_CMD_GETID);

	अगर (param[0] != 2)
		वापस -ENODEV;

	अगर (set_properties) अणु
		__set_bit(BTN_MIDDLE, psmouse->dev->keybit);
		__set_bit(BTN_EXTRA, psmouse->dev->keybit);

		psmouse->venकरोr = "Kensington";
		psmouse->name = "ThinkingMouse";
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Bare PS/2 protocol "detection". Always succeeds.
 */
अटल पूर्णांक ps2bare_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	अगर (set_properties) अणु
		अगर (!psmouse->venकरोr)
			psmouse->venकरोr = "Generic";
		अगर (!psmouse->name)
			psmouse->name = "Mouse";

		/*
		 * We have no way of figuring true number of buttons so let's
		 * assume that the device has 3.
		 */
		input_set_capability(psmouse->dev, EV_KEY, BTN_MIDDLE);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Cortron PS/2 protocol detection. There's no special way to detect it, so it
 * must be क्रमced by sysfs protocol writing.
 */
अटल पूर्णांक cortron_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	अगर (set_properties) अणु
		psmouse->venकरोr = "Cortron";
		psmouse->name = "PS/2 Trackball";

		__set_bit(BTN_MIDDLE, psmouse->dev->keybit);
		__set_bit(BTN_SIDE, psmouse->dev->keybit);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा psmouse_protocol psmouse_protocols[] = अणु
	अणु
		.type		= PSMOUSE_PS2,
		.name		= "PS/2",
		.alias		= "bare",
		.maxproto	= true,
		.ignore_parity	= true,
		.detect		= ps2bare_detect,
		.try_passthru	= true,
	पूर्ण,
#अगर_घोषित CONFIG_MOUSE_PS2_LOGIPS2PP
	अणु
		.type		= PSMOUSE_PS2PP,
		.name		= "PS2++",
		.alias		= "logitech",
		.detect		= ps2pp_detect,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.type		= PSMOUSE_THINKPS,
		.name		= "ThinkPS/2",
		.alias		= "thinkps",
		.detect		= thinking_detect,
	पूर्ण,
#अगर_घोषित CONFIG_MOUSE_PS2_CYPRESS
	अणु
		.type		= PSMOUSE_CYPRESS,
		.name		= "CyPS/2",
		.alias		= "cypress",
		.detect		= cypress_detect,
		.init		= cypress_init,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.type		= PSMOUSE_GENPS,
		.name		= "GenPS/2",
		.alias		= "genius",
		.detect		= genius_detect,
	पूर्ण,
	अणु
		.type		= PSMOUSE_IMPS,
		.name		= "ImPS/2",
		.alias		= "imps",
		.maxproto	= true,
		.ignore_parity	= true,
		.detect		= पूर्णांकellimouse_detect,
		.try_passthru	= true,
	पूर्ण,
	अणु
		.type		= PSMOUSE_IMEX,
		.name		= "ImExPS/2",
		.alias		= "exps",
		.maxproto	= true,
		.ignore_parity	= true,
		.detect		= im_explorer_detect,
		.try_passthru	= true,
	पूर्ण,
#अगर_घोषित CONFIG_MOUSE_PS2_SYNAPTICS
	अणु
		.type		= PSMOUSE_SYNAPTICS,
		.name		= "SynPS/2",
		.alias		= "synaptics",
		.detect		= synaptics_detect,
		.init		= synaptics_init_असलolute,
	पूर्ण,
	अणु
		.type		= PSMOUSE_SYNAPTICS_RELATIVE,
		.name		= "SynRelPS/2",
		.alias		= "synaptics-relative",
		.detect		= synaptics_detect,
		.init		= synaptics_init_relative,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MOUSE_PS2_SYNAPTICS_SMBUS
	अणु
		.type		= PSMOUSE_SYNAPTICS_SMBUS,
		.name		= "SynSMBus",
		.alias		= "synaptics-smbus",
		.detect		= synaptics_detect,
		.init		= synaptics_init_smbus,
		.smbus_companion = true,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MOUSE_PS2_ALPS
	अणु
		.type		= PSMOUSE_ALPS,
		.name		= "AlpsPS/2",
		.alias		= "alps",
		.detect		= alps_detect,
		.init		= alps_init,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MOUSE_PS2_LIFEBOOK
	अणु
		.type		= PSMOUSE_LIFEBOOK,
		.name		= "LBPS/2",
		.alias		= "lifebook",
		.detect		= lअगरebook_detect,
		.init		= lअगरebook_init,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MOUSE_PS2_TRACKPOINT
	अणु
		.type		= PSMOUSE_TRACKPOINT,
		.name		= "TPPS/2",
		.alias		= "trackpoint",
		.detect		= trackpoपूर्णांक_detect,
		.try_passthru	= true,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MOUSE_PS2_TOUCHKIT
	अणु
		.type		= PSMOUSE_TOUCHKIT_PS2,
		.name		= "touchkitPS/2",
		.alias		= "touchkit",
		.detect		= touchkit_ps2_detect,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MOUSE_PS2_OLPC
	अणु
		.type		= PSMOUSE_HGPK,
		.name		= "OLPC HGPK",
		.alias		= "hgpk",
		.detect		= hgpk_detect,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MOUSE_PS2_ELANTECH
	अणु
		.type		= PSMOUSE_ELANTECH,
		.name		= "ETPS/2",
		.alias		= "elantech",
		.detect		= elantech_detect,
		.init		= elantech_init_ps2,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MOUSE_PS2_ELANTECH_SMBUS
	अणु
		.type		= PSMOUSE_ELANTECH_SMBUS,
		.name		= "ETSMBus",
		.alias		= "elantech-smbus",
		.detect		= elantech_detect,
		.init		= elantech_init_smbus,
		.smbus_companion = true,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MOUSE_PS2_SENTELIC
	अणु
		.type		= PSMOUSE_FSP,
		.name		= "FSPPS/2",
		.alias		= "fsp",
		.detect		= fsp_detect,
		.init		= fsp_init,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.type		= PSMOUSE_CORTRON,
		.name		= "CortronPS/2",
		.alias		= "cortps",
		.detect		= cortron_detect,
	पूर्ण,
#अगर_घोषित CONFIG_MOUSE_PS2_FOCALTECH
	अणु
		.type		= PSMOUSE_FOCALTECH,
		.name		= "FocalTechPS/2",
		.alias		= "focaltech",
		.detect		= focaltech_detect,
		.init		= focaltech_init,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MOUSE_PS2_VMMOUSE
	अणु
		.type		= PSMOUSE_VMMOUSE,
		.name		= VMMOUSE_PSNAME,
		.alias		= "vmmouse",
		.detect		= vmmouse_detect,
		.init		= vmmouse_init,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MOUSE_PS2_BYD
	अणु
		.type		= PSMOUSE_BYD,
		.name		= "BYDPS/2",
		.alias		= "byd",
		.detect		= byd_detect,
		.init		= byd_init,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.type		= PSMOUSE_AUTO,
		.name		= "auto",
		.alias		= "any",
		.maxproto	= true,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा psmouse_protocol *__psmouse_protocol_by_type(क्रमागत psmouse_type type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(psmouse_protocols); i++)
		अगर (psmouse_protocols[i].type == type)
			वापस &psmouse_protocols[i];

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा psmouse_protocol *psmouse_protocol_by_type(क्रमागत psmouse_type type)
अणु
	स्थिर काष्ठा psmouse_protocol *proto;

	proto = __psmouse_protocol_by_type(type);
	अगर (proto)
		वापस proto;

	WARN_ON(1);
	वापस &psmouse_protocols[0];
पूर्ण

अटल स्थिर काष्ठा psmouse_protocol *psmouse_protocol_by_name(स्थिर अक्षर *name, माप_प्रकार len)
अणु
	स्थिर काष्ठा psmouse_protocol *p;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(psmouse_protocols); i++) अणु
		p = &psmouse_protocols[i];

		अगर ((म_माप(p->name) == len && !म_भेदन(p->name, name, len)) ||
		    (म_माप(p->alias) == len && !म_भेदन(p->alias, name, len)))
			वापस &psmouse_protocols[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Apply शेष settings to the psmouse काष्ठाure. Most of them will
 * be overridden by inभागidual protocol initialization routines.
 */
अटल व्योम psmouse_apply_शेषs(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *input_dev = psmouse->dev;

	biपंचांगap_zero(input_dev->evbit, EV_CNT);
	biपंचांगap_zero(input_dev->keybit, KEY_CNT);
	biपंचांगap_zero(input_dev->relbit, REL_CNT);
	biपंचांगap_zero(input_dev->असलbit, ABS_CNT);
	biपंचांगap_zero(input_dev->mscbit, MSC_CNT);

	input_set_capability(input_dev, EV_KEY, BTN_LEFT);
	input_set_capability(input_dev, EV_KEY, BTN_RIGHT);

	input_set_capability(input_dev, EV_REL, REL_X);
	input_set_capability(input_dev, EV_REL, REL_Y);

	__set_bit(INPUT_PROP_POINTER, input_dev->propbit);

	psmouse->protocol = &psmouse_protocols[0];

	psmouse->set_rate = psmouse_set_rate;
	psmouse->set_resolution = psmouse_set_resolution;
	psmouse->set_scale = psmouse_set_scale;
	psmouse->poll = psmouse_poll;
	psmouse->protocol_handler = psmouse_process_byte;
	psmouse->pktsize = 3;
	psmouse->reconnect = शून्य;
	psmouse->fast_reconnect = शून्य;
	psmouse->disconnect = शून्य;
	psmouse->cleanup = शून्य;
	psmouse->pt_activate = शून्य;
	psmouse->pt_deactivate = शून्य;
पूर्ण

अटल bool psmouse_करो_detect(पूर्णांक (*detect)(काष्ठा psmouse *, bool),
			      काष्ठा psmouse *psmouse, bool allow_passthrough,
			      bool set_properties)
अणु
	अगर (psmouse->ps2dev.serio->id.type == SERIO_PS_PSTHRU &&
	    !allow_passthrough) अणु
		वापस false;
	पूर्ण

	अगर (set_properties)
		psmouse_apply_शेषs(psmouse);

	वापस detect(psmouse, set_properties) == 0;
पूर्ण

अटल bool psmouse_try_protocol(काष्ठा psmouse *psmouse,
				 क्रमागत psmouse_type type,
				 अचिन्हित पूर्णांक *max_proto,
				 bool set_properties, bool init_allowed)
अणु
	स्थिर काष्ठा psmouse_protocol *proto;

	proto = __psmouse_protocol_by_type(type);
	अगर (!proto)
		वापस false;

	अगर (!psmouse_करो_detect(proto->detect, psmouse, proto->try_passthru,
			       set_properties))
		वापस false;

	अगर (set_properties && proto->init && init_allowed) अणु
		अगर (proto->init(psmouse) != 0) अणु
			/*
			 * We detected device, but init failed. Adjust
			 * max_proto so we only try standard protocols.
			 */
			अगर (*max_proto > PSMOUSE_IMEX)
				*max_proto = PSMOUSE_IMEX;

			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/*
 * psmouse_extensions() probes क्रम any extensions to the basic PS/2 protocol
 * the mouse may have.
 */
अटल पूर्णांक psmouse_extensions(काष्ठा psmouse *psmouse,
			      अचिन्हित पूर्णांक max_proto, bool set_properties)
अणु
	bool synaptics_hardware = false;
	पूर्णांक ret;

	/*
	 * Always check क्रम focaltech, this is safe as it uses pnp-id
	 * matching.
	 */
	अगर (psmouse_करो_detect(focaltech_detect,
			      psmouse, false, set_properties)) अणु
		अगर (max_proto > PSMOUSE_IMEX &&
		    IS_ENABLED(CONFIG_MOUSE_PS2_FOCALTECH) &&
		    (!set_properties || focaltech_init(psmouse) == 0)) अणु
			वापस PSMOUSE_FOCALTECH;
		पूर्ण
		/*
		 * Restrict psmouse_max_proto so that psmouse_initialize()
		 * करोes not try to reset rate and resolution, because even
		 * that upsets the device.
		 * This also causes us to basically fall through to basic
		 * protocol detection, where we fully reset the mouse,
		 * and set it up as bare PS/2 protocol device.
		 */
		psmouse_max_proto = max_proto = PSMOUSE_PS2;
	पूर्ण

	/*
	 * We always check क्रम LअगरeBook because it करोes not disturb mouse
	 * (it only checks DMI inक्रमmation).
	 */
	अगर (psmouse_try_protocol(psmouse, PSMOUSE_LIFEBOOK, &max_proto,
				 set_properties, max_proto > PSMOUSE_IMEX))
		वापस PSMOUSE_LIFEBOOK;

	अगर (psmouse_try_protocol(psmouse, PSMOUSE_VMMOUSE, &max_proto,
				 set_properties, max_proto > PSMOUSE_IMEX))
		वापस PSMOUSE_VMMOUSE;

	/*
	 * Try Kensington ThinkingMouse (we try first, because Synaptics
	 * probe upsets the ThinkingMouse).
	 */
	अगर (max_proto > PSMOUSE_IMEX &&
	    psmouse_try_protocol(psmouse, PSMOUSE_THINKPS, &max_proto,
				 set_properties, true)) अणु
		वापस PSMOUSE_THINKPS;
	पूर्ण

	/*
	 * Try Synaptics TouchPad. Note that probing is करोne even अगर
	 * Synaptics protocol support is disabled in config - we need to
	 * know अगर it is Synaptics so we can reset it properly after
	 * probing क्रम IntelliMouse.
	 */
	अगर (max_proto > PSMOUSE_PS2 &&
	    psmouse_करो_detect(synaptics_detect,
			      psmouse, false, set_properties)) अणु
		synaptics_hardware = true;

		अगर (max_proto > PSMOUSE_IMEX) अणु
			/*
			 * Try activating protocol, but check अगर support is
			 * enabled first, since we try detecting Synaptics
			 * even when protocol is disabled.
			 */
			अगर (IS_ENABLED(CONFIG_MOUSE_PS2_SYNAPTICS) ||
			    IS_ENABLED(CONFIG_MOUSE_PS2_SYNAPTICS_SMBUS)) अणु
				अगर (!set_properties)
					वापस PSMOUSE_SYNAPTICS;

				ret = synaptics_init(psmouse);
				अगर (ret >= 0)
					वापस ret;
			पूर्ण

			/*
			 * Some Synaptics touchpads can emulate extended
			 * protocols (like IMPS/2).  Unक्रमtunately
			 * Logitech/Genius probes confuse some firmware
			 * versions so we'll have to skip them.
			 */
			max_proto = PSMOUSE_IMEX;
		पूर्ण

		/*
		 * Make sure that touchpad is in relative mode, gestures
		 * (taps) are enabled.
		 */
		synaptics_reset(psmouse);
	पूर्ण

	/*
	 * Try Cypress Trackpad. We must try it beक्रमe Finger Sensing Pad
	 * because Finger Sensing Pad probe upsets some modules of Cypress
	 * Trackpads.
	 */
	अगर (max_proto > PSMOUSE_IMEX &&
	    psmouse_try_protocol(psmouse, PSMOUSE_CYPRESS, &max_proto,
				 set_properties, true)) अणु
		वापस PSMOUSE_CYPRESS;
	पूर्ण

	/* Try ALPS TouchPad */
	अगर (max_proto > PSMOUSE_IMEX) अणु
		ps2_command(&psmouse->ps2dev, शून्य, PSMOUSE_CMD_RESET_DIS);
		अगर (psmouse_try_protocol(psmouse, PSMOUSE_ALPS,
					 &max_proto, set_properties, true))
			वापस PSMOUSE_ALPS;
	पूर्ण

	/* Try OLPC HGPK touchpad */
	अगर (max_proto > PSMOUSE_IMEX &&
	    psmouse_try_protocol(psmouse, PSMOUSE_HGPK, &max_proto,
				 set_properties, true)) अणु
		वापस PSMOUSE_HGPK;
	पूर्ण

	/* Try Elantech touchpad */
	अगर (max_proto > PSMOUSE_IMEX &&
	    psmouse_try_protocol(psmouse, PSMOUSE_ELANTECH,
				 &max_proto, set_properties, false)) अणु
		अगर (!set_properties)
			वापस PSMOUSE_ELANTECH;

		ret = elantech_init(psmouse);
		अगर (ret >= 0)
			वापस ret;
	पूर्ण

	अगर (max_proto > PSMOUSE_IMEX) अणु
		अगर (psmouse_try_protocol(psmouse, PSMOUSE_GENPS,
					 &max_proto, set_properties, true))
			वापस PSMOUSE_GENPS;

		अगर (psmouse_try_protocol(psmouse, PSMOUSE_PS2PP,
					 &max_proto, set_properties, true))
			वापस PSMOUSE_PS2PP;

		अगर (psmouse_try_protocol(psmouse, PSMOUSE_TRACKPOINT,
					 &max_proto, set_properties, true))
			वापस PSMOUSE_TRACKPOINT;

		अगर (psmouse_try_protocol(psmouse, PSMOUSE_TOUCHKIT_PS2,
					 &max_proto, set_properties, true))
			वापस PSMOUSE_TOUCHKIT_PS2;
	पूर्ण

	/*
	 * Try Finger Sensing Pad. We करो it here because its probe upsets
	 * Trackpoपूर्णांक devices (causing TP_READ_ID command to समय out).
	 */
	अगर (max_proto > PSMOUSE_IMEX &&
	    psmouse_try_protocol(psmouse, PSMOUSE_FSP,
				 &max_proto, set_properties, true)) अणु
		वापस PSMOUSE_FSP;
	पूर्ण

	/*
	 * Reset to शेषs in हाल the device got confused by extended
	 * protocol probes. Note that we follow up with full reset because
	 * some mice put themselves to sleep when they see PSMOUSE_RESET_DIS.
	 */
	ps2_command(&psmouse->ps2dev, शून्य, PSMOUSE_CMD_RESET_DIS);
	psmouse_reset(psmouse);

	अगर (max_proto >= PSMOUSE_IMEX &&
	    psmouse_try_protocol(psmouse, PSMOUSE_IMEX,
				 &max_proto, set_properties, true)) अणु
		वापस PSMOUSE_IMEX;
	पूर्ण

	अगर (max_proto >= PSMOUSE_IMPS &&
	    psmouse_try_protocol(psmouse, PSMOUSE_IMPS,
				 &max_proto, set_properties, true)) अणु
		वापस PSMOUSE_IMPS;
	पूर्ण

	/*
	 * Okay, all failed, we have a standard mouse here. The number of
	 * the buttons is still a question, though. We assume 3.
	 */
	psmouse_try_protocol(psmouse, PSMOUSE_PS2,
			     &max_proto, set_properties, true);

	अगर (synaptics_hardware) अणु
		/*
		 * We detected Synaptics hardware but it did not respond to
		 * IMPS/2 probes.  We need to reset the touchpad because अगर
		 * there is a track poपूर्णांक on the pass through port it could
		 * get disabled जबतक probing क्रम protocol extensions.
		 */
		psmouse_reset(psmouse);
	पूर्ण

	वापस PSMOUSE_PS2;
पूर्ण

/*
 * psmouse_probe() probes क्रम a PS/2 mouse.
 */
अटल पूर्णांक psmouse_probe(काष्ठा psmouse *psmouse)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	u8 param[2];
	पूर्णांक error;

	/*
	 * First, we check अगर it's a mouse. It should send 0x00 or 0x03 in
	 * हाल of an IntelliMouse in 4-byte mode or 0x04 क्रम IM Explorer.
	 * Sunrex K8561 IR Keyboard/Mouse reports 0xff on second and
	 * subsequent ID queries, probably due to a firmware bug.
	 */
	param[0] = 0xa5;
	error = ps2_command(ps2dev, param, PSMOUSE_CMD_GETID);
	अगर (error)
		वापस error;

	अगर (param[0] != 0x00 && param[0] != 0x03 &&
	    param[0] != 0x04 && param[0] != 0xff)
		वापस -ENODEV;

	/*
	 * Then we reset and disable the mouse so that it करोesn't generate
	 * events.
	 */
	error = ps2_command(ps2dev, शून्य, PSMOUSE_CMD_RESET_DIS);
	अगर (error)
		psmouse_warn(psmouse, "Failed to reset mouse on %s: %d\n",
			     ps2dev->serio->phys, error);

	वापस 0;
पूर्ण

/*
 * psmouse_initialize() initializes the mouse to a sane state.
 */
अटल व्योम psmouse_initialize(काष्ठा psmouse *psmouse)
अणु
	/*
	 * We set the mouse report rate, resolution and scaling.
	 */
	अगर (psmouse_max_proto != PSMOUSE_PS2) अणु
		psmouse->set_rate(psmouse, psmouse->rate);
		psmouse->set_resolution(psmouse, psmouse->resolution);
		psmouse->set_scale(psmouse, PSMOUSE_SCALE11);
	पूर्ण
पूर्ण

/*
 * psmouse_activate() enables the mouse so that we get motion reports from it.
 */
पूर्णांक psmouse_activate(काष्ठा psmouse *psmouse)
अणु
	अगर (ps2_command(&psmouse->ps2dev, शून्य, PSMOUSE_CMD_ENABLE)) अणु
		psmouse_warn(psmouse, "Failed to enable mouse on %s\n",
			     psmouse->ps2dev.serio->phys);
		वापस -1;
	पूर्ण

	psmouse_set_state(psmouse, PSMOUSE_ACTIVATED);
	वापस 0;
पूर्ण

/*
 * psmouse_deactivate() माला_दो the mouse पूर्णांकo poll mode so that we करोn't get
 * motion reports from it unless we explicitly request it.
 */
पूर्णांक psmouse_deactivate(काष्ठा psmouse *psmouse)
अणु
	पूर्णांक error;

	error = ps2_command(&psmouse->ps2dev, शून्य, PSMOUSE_CMD_DISABLE);
	अगर (error) अणु
		psmouse_warn(psmouse, "Failed to deactivate mouse on %s: %d\n",
			     psmouse->ps2dev.serio->phys, error);
		वापस error;
	पूर्ण

	psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);
	वापस 0;
पूर्ण

/*
 * psmouse_resync() attempts to re-validate current protocol.
 */
अटल व्योम psmouse_resync(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा psmouse *parent = शून्य, *psmouse =
		container_of(work, काष्ठा psmouse, resync_work.work);
	काष्ठा serio *serio = psmouse->ps2dev.serio;
	psmouse_ret_t rc = PSMOUSE_GOOD_DATA;
	bool failed = false, enabled = false;
	पूर्णांक i;

	mutex_lock(&psmouse_mutex);

	अगर (psmouse->state != PSMOUSE_RESYNCING)
		जाओ out;

	अगर (serio->parent && serio->id.type == SERIO_PS_PSTHRU) अणु
		parent = serio_get_drvdata(serio->parent);
		psmouse_deactivate(parent);
	पूर्ण

	/*
	 * Some mice करोn't ACK commands sent जबतक they are in the middle of
	 * transmitting motion packet. To aव्योम delay we use ps2_sendbyte()
	 * instead of ps2_command() which would रुको क्रम 200ms क्रम an ACK
	 * that may never come.
	 * As an additional quirk ALPS touchpads may not only क्रमget to ACK
	 * disable command but will stop reporting taps, so अगर we see that
	 * mouse at least once ACKs disable we will करो full reconnect अगर ACK
	 * is missing.
	 */
	psmouse->num_resyncs++;

	अगर (ps2_sendbyte(&psmouse->ps2dev, PSMOUSE_CMD_DISABLE, 20)) अणु
		अगर (psmouse->num_resyncs < 3 || psmouse->acks_disable_command)
			failed = true;
	पूर्ण अन्यथा
		psmouse->acks_disable_command = true;

	/*
	 * Poll the mouse. If it was reset the packet will be लघुer than
	 * psmouse->pktsize and ps2_command will fail. We करो not expect and
	 * करो not handle scenario when mouse "upgrades" its protocol जबतक
	 * disconnected since it would require additional delay. If we ever
	 * see a mouse that करोes it we'll adjust the code.
	 */
	अगर (!failed) अणु
		अगर (psmouse->poll(psmouse))
			failed = true;
		अन्यथा अणु
			psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);
			क्रम (i = 0; i < psmouse->pktsize; i++) अणु
				psmouse->pktcnt++;
				rc = psmouse->protocol_handler(psmouse);
				अगर (rc != PSMOUSE_GOOD_DATA)
					अवरोध;
			पूर्ण
			अगर (rc != PSMOUSE_FULL_PACKET)
				failed = true;
			psmouse_set_state(psmouse, PSMOUSE_RESYNCING);
		पूर्ण
	पूर्ण

	/*
	 * Now try to enable mouse. We try to करो that even अगर poll failed
	 * and also repeat our attempts 5 बार, otherwise we may be left
	 * out with disabled mouse.
	 */
	क्रम (i = 0; i < 5; i++) अणु
		अगर (!ps2_command(&psmouse->ps2dev, शून्य, PSMOUSE_CMD_ENABLE)) अणु
			enabled = true;
			अवरोध;
		पूर्ण
		msleep(200);
	पूर्ण

	अगर (!enabled) अणु
		psmouse_warn(psmouse, "failed to re-enable mouse on %s\n",
			     psmouse->ps2dev.serio->phys);
		failed = true;
	पूर्ण

	अगर (failed) अणु
		psmouse_set_state(psmouse, PSMOUSE_IGNORE);
		psmouse_info(psmouse,
			     "resync failed, issuing reconnect request\n");
		serio_reconnect(serio);
	पूर्ण अन्यथा
		psmouse_set_state(psmouse, PSMOUSE_ACTIVATED);

	अगर (parent)
		psmouse_activate(parent);
 out:
	mutex_unlock(&psmouse_mutex);
पूर्ण

/*
 * psmouse_cleanup() resets the mouse पूर्णांकo घातer-on state.
 */
अटल व्योम psmouse_cleanup(काष्ठा serio *serio)
अणु
	काष्ठा psmouse *psmouse = serio_get_drvdata(serio);
	काष्ठा psmouse *parent = शून्य;

	mutex_lock(&psmouse_mutex);

	अगर (serio->parent && serio->id.type == SERIO_PS_PSTHRU) अणु
		parent = serio_get_drvdata(serio->parent);
		psmouse_deactivate(parent);
	पूर्ण

	psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);

	/*
	 * Disable stream mode so cleanup routine can proceed undisturbed.
	 */
	अगर (ps2_command(&psmouse->ps2dev, शून्य, PSMOUSE_CMD_DISABLE))
		psmouse_warn(psmouse, "Failed to disable mouse on %s\n",
			     psmouse->ps2dev.serio->phys);

	अगर (psmouse->cleanup)
		psmouse->cleanup(psmouse);

	/*
	 * Reset the mouse to शेषs (bare PS/2 protocol).
	 */
	ps2_command(&psmouse->ps2dev, शून्य, PSMOUSE_CMD_RESET_DIS);

	/*
	 * Some boxes, such as HP nx7400, get terribly confused अगर mouse
	 * is not fully enabled beक्रमe suspending/shutting करोwn.
	 */
	ps2_command(&psmouse->ps2dev, शून्य, PSMOUSE_CMD_ENABLE);

	अगर (parent) अणु
		अगर (parent->pt_deactivate)
			parent->pt_deactivate(parent);

		psmouse_activate(parent);
	पूर्ण

	mutex_unlock(&psmouse_mutex);
पूर्ण

/*
 * psmouse_disconnect() बंदs and मुक्तs.
 */
अटल व्योम psmouse_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा psmouse *psmouse = serio_get_drvdata(serio);
	काष्ठा psmouse *parent = शून्य;

	sysfs_हटाओ_group(&serio->dev.kobj, &psmouse_attribute_group);

	mutex_lock(&psmouse_mutex);

	psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);

	/* make sure we करोn't have a resync in progress */
	mutex_unlock(&psmouse_mutex);
	flush_workqueue(kpsmoused_wq);
	mutex_lock(&psmouse_mutex);

	अगर (serio->parent && serio->id.type == SERIO_PS_PSTHRU) अणु
		parent = serio_get_drvdata(serio->parent);
		psmouse_deactivate(parent);
	पूर्ण

	अगर (psmouse->disconnect)
		psmouse->disconnect(psmouse);

	अगर (parent && parent->pt_deactivate)
		parent->pt_deactivate(parent);

	psmouse_set_state(psmouse, PSMOUSE_IGNORE);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);

	अगर (psmouse->dev)
		input_unरेजिस्टर_device(psmouse->dev);

	kमुक्त(psmouse);

	अगर (parent)
		psmouse_activate(parent);

	mutex_unlock(&psmouse_mutex);
पूर्ण

अटल पूर्णांक psmouse_चयन_protocol(काष्ठा psmouse *psmouse,
				   स्थिर काष्ठा psmouse_protocol *proto)
अणु
	स्थिर काष्ठा psmouse_protocol *selected_proto;
	काष्ठा input_dev *input_dev = psmouse->dev;
	क्रमागत psmouse_type type;

	input_dev->dev.parent = &psmouse->ps2dev.serio->dev;

	अगर (proto && (proto->detect || proto->init)) अणु
		psmouse_apply_शेषs(psmouse);

		अगर (proto->detect && proto->detect(psmouse, true) < 0)
			वापस -1;

		अगर (proto->init && proto->init(psmouse) < 0)
			वापस -1;

		selected_proto = proto;
	पूर्ण अन्यथा अणु
		type = psmouse_extensions(psmouse, psmouse_max_proto, true);
		selected_proto = psmouse_protocol_by_type(type);
	पूर्ण

	psmouse->protocol = selected_proto;

	/*
	 * If mouse's packet size is 3 there is no poपूर्णांक in polling the
	 * device in hopes to detect protocol reset - we won't get less
	 * than 3 bytes response anyhow.
	 */
	अगर (psmouse->pktsize == 3)
		psmouse->resync_समय = 0;

	/*
	 * Some smart KVMs fake response to POLL command वापसing just
	 * 3 bytes and messing up our resync logic, so अगर initial poll
	 * fails we won't try polling the device anymore. Hopefully
	 * such KVM will मुख्यtain initially selected protocol.
	 */
	अगर (psmouse->resync_समय && psmouse->poll(psmouse))
		psmouse->resync_समय = 0;

	snम_लिखो(psmouse->devname, माप(psmouse->devname), "%s %s %s",
		 selected_proto->name, psmouse->venकरोr, psmouse->name);

	input_dev->name = psmouse->devname;
	input_dev->phys = psmouse->phys;
	input_dev->id.bustype = BUS_I8042;
	input_dev->id.venकरोr = 0x0002;
	input_dev->id.product = psmouse->protocol->type;
	input_dev->id.version = psmouse->model;

	वापस 0;
पूर्ण

/*
 * psmouse_connect() is a callback from the serio module when
 * an unhandled serio port is found.
 */
अटल पूर्णांक psmouse_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा psmouse *psmouse, *parent = शून्य;
	काष्ठा input_dev *input_dev;
	पूर्णांक retval = 0, error = -ENOMEM;

	mutex_lock(&psmouse_mutex);

	/*
	 * If this is a pass-through port deactivate parent so the device
	 * connected to this port can be successfully identअगरied
	 */
	अगर (serio->parent && serio->id.type == SERIO_PS_PSTHRU) अणु
		parent = serio_get_drvdata(serio->parent);
		psmouse_deactivate(parent);
	पूर्ण

	psmouse = kzalloc(माप(काष्ठा psmouse), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!psmouse || !input_dev)
		जाओ err_मुक्त;

	ps2_init(&psmouse->ps2dev, serio);
	INIT_DELAYED_WORK(&psmouse->resync_work, psmouse_resync);
	psmouse->dev = input_dev;
	snम_लिखो(psmouse->phys, माप(psmouse->phys), "%s/input0", serio->phys);

	psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);

	serio_set_drvdata(serio, psmouse);

	error = serio_खोलो(serio, drv);
	अगर (error)
		जाओ err_clear_drvdata;

	/* give PT device some समय to settle करोwn beक्रमe probing */
	अगर (serio->id.type == SERIO_PS_PSTHRU)
		usleep_range(10000, 15000);

	अगर (psmouse_probe(psmouse) < 0) अणु
		error = -ENODEV;
		जाओ err_बंद_serio;
	पूर्ण

	psmouse->rate = psmouse_rate;
	psmouse->resolution = psmouse_resolution;
	psmouse->resetafter = psmouse_resetafter;
	psmouse->resync_समय = parent ? 0 : psmouse_resync_समय;
	psmouse->smartscroll = psmouse_smartscroll;

	psmouse_चयन_protocol(psmouse, शून्य);

	अगर (!psmouse->protocol->smbus_companion) अणु
		psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);
		psmouse_initialize(psmouse);

		error = input_रेजिस्टर_device(input_dev);
		अगर (error)
			जाओ err_protocol_disconnect;
	पूर्ण अन्यथा अणु
		/* Smbus companion will be reporting events, not us. */
		input_मुक्त_device(input_dev);
		psmouse->dev = input_dev = शून्य;
	पूर्ण

	अगर (parent && parent->pt_activate)
		parent->pt_activate(parent);

	error = sysfs_create_group(&serio->dev.kobj, &psmouse_attribute_group);
	अगर (error)
		जाओ err_pt_deactivate;

	/*
	 * PS/2 devices having SMBus companions should stay disabled
	 * on PS/2 side, in order to have SMBus part operable.
	 */
	अगर (!psmouse->protocol->smbus_companion)
		psmouse_activate(psmouse);

 out:
	/* If this is a pass-through port the parent needs to be re-activated */
	अगर (parent)
		psmouse_activate(parent);

	mutex_unlock(&psmouse_mutex);
	वापस retval;

 err_pt_deactivate:
	अगर (parent && parent->pt_deactivate)
		parent->pt_deactivate(parent);
	अगर (input_dev) अणु
		input_unरेजिस्टर_device(input_dev);
		input_dev = शून्य; /* so we करोn't try to मुक्त it below */
	पूर्ण
 err_protocol_disconnect:
	अगर (psmouse->disconnect)
		psmouse->disconnect(psmouse);
	psmouse_set_state(psmouse, PSMOUSE_IGNORE);
 err_बंद_serio:
	serio_बंद(serio);
 err_clear_drvdata:
	serio_set_drvdata(serio, शून्य);
 err_मुक्त:
	input_मुक्त_device(input_dev);
	kमुक्त(psmouse);

	retval = error;
	जाओ out;
पूर्ण

अटल पूर्णांक __psmouse_reconnect(काष्ठा serio *serio, bool fast_reconnect)
अणु
	काष्ठा psmouse *psmouse = serio_get_drvdata(serio);
	काष्ठा psmouse *parent = शून्य;
	पूर्णांक (*reconnect_handler)(काष्ठा psmouse *);
	क्रमागत psmouse_type type;
	पूर्णांक rc = -1;

	mutex_lock(&psmouse_mutex);

	अगर (fast_reconnect) अणु
		reconnect_handler = psmouse->fast_reconnect;
		अगर (!reconnect_handler) अणु
			rc = -ENOENT;
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		reconnect_handler = psmouse->reconnect;
	पूर्ण

	अगर (serio->parent && serio->id.type == SERIO_PS_PSTHRU) अणु
		parent = serio_get_drvdata(serio->parent);
		psmouse_deactivate(parent);
	पूर्ण

	psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);

	अगर (reconnect_handler) अणु
		अगर (reconnect_handler(psmouse))
			जाओ out;
	पूर्ण अन्यथा अणु
		psmouse_reset(psmouse);

		अगर (psmouse_probe(psmouse) < 0)
			जाओ out;

		type = psmouse_extensions(psmouse, psmouse_max_proto, false);
		अगर (psmouse->protocol->type != type)
			जाओ out;
	पूर्ण

	/*
	 * OK, the device type (and capabilities) match the old one,
	 * we can जारी using it, complete initialization
	 */
	अगर (!psmouse->protocol->smbus_companion) अणु
		psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);
		psmouse_initialize(psmouse);
	पूर्ण

	अगर (parent && parent->pt_activate)
		parent->pt_activate(parent);

	/*
	 * PS/2 devices having SMBus companions should stay disabled
	 * on PS/2 side, in order to have SMBus part operable.
	 */
	अगर (!psmouse->protocol->smbus_companion)
		psmouse_activate(psmouse);

	rc = 0;

out:
	/* If this is a pass-through port the parent रुकोs to be activated */
	अगर (parent)
		psmouse_activate(parent);

out_unlock:
	mutex_unlock(&psmouse_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक psmouse_reconnect(काष्ठा serio *serio)
अणु
	वापस __psmouse_reconnect(serio, false);
पूर्ण

अटल पूर्णांक psmouse_fast_reconnect(काष्ठा serio *serio)
अणु
	वापस __psmouse_reconnect(serio, true);
पूर्ण

अटल काष्ठा serio_device_id psmouse_serio_ids[] = अणु
	अणु
		.type	= SERIO_8042,
		.proto	= SERIO_ANY,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु
		.type	= SERIO_PS_PSTHRU,
		.proto	= SERIO_ANY,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, psmouse_serio_ids);

अटल काष्ठा serio_driver psmouse_drv = अणु
	.driver		= अणु
		.name	= "psmouse",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= psmouse_serio_ids,
	.पूर्णांकerrupt	= psmouse_पूर्णांकerrupt,
	.connect	= psmouse_connect,
	.reconnect	= psmouse_reconnect,
	.fast_reconnect	= psmouse_fast_reconnect,
	.disconnect	= psmouse_disconnect,
	.cleanup	= psmouse_cleanup,
पूर्ण;

sमाप_प्रकार psmouse_attr_show_helper(काष्ठा device *dev, काष्ठा device_attribute *devattr,
				 अक्षर *buf)
अणु
	काष्ठा serio *serio = to_serio_port(dev);
	काष्ठा psmouse_attribute *attr = to_psmouse_attr(devattr);
	काष्ठा psmouse *psmouse = serio_get_drvdata(serio);

	अगर (psmouse->protocol->smbus_companion &&
			devattr != &psmouse_attr_protocol.dattr)
		वापस -ENOENT;

	वापस attr->show(psmouse, attr->data, buf);
पूर्ण

sमाप_प्रकार psmouse_attr_set_helper(काष्ठा device *dev, काष्ठा device_attribute *devattr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा serio *serio = to_serio_port(dev);
	काष्ठा psmouse_attribute *attr = to_psmouse_attr(devattr);
	काष्ठा psmouse *psmouse, *parent = शून्य;
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&psmouse_mutex);
	अगर (retval)
		जाओ out;

	psmouse = serio_get_drvdata(serio);

	अगर (psmouse->protocol->smbus_companion &&
			devattr != &psmouse_attr_protocol.dattr) अणु
		retval = -ENOENT;
		जाओ out_unlock;
	पूर्ण

	अगर (attr->protect) अणु
		अगर (psmouse->state == PSMOUSE_IGNORE) अणु
			retval = -ENODEV;
			जाओ out_unlock;
		पूर्ण

		अगर (serio->parent && serio->id.type == SERIO_PS_PSTHRU) अणु
			parent = serio_get_drvdata(serio->parent);
			psmouse_deactivate(parent);
		पूर्ण

		अगर (!psmouse->protocol->smbus_companion)
			psmouse_deactivate(psmouse);
	पूर्ण

	retval = attr->set(psmouse, attr->data, buf, count);

	अगर (attr->protect) अणु
		अगर (retval != -ENODEV && !psmouse->protocol->smbus_companion)
			psmouse_activate(psmouse);

		अगर (parent)
			psmouse_activate(parent);
	पूर्ण

 out_unlock:
	mutex_unlock(&psmouse_mutex);
 out:
	वापस retval;
पूर्ण

अटल sमाप_प्रकार psmouse_show_पूर्णांक_attr(काष्ठा psmouse *psmouse, व्योम *offset, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक *field = (अचिन्हित पूर्णांक *)((अक्षर *)psmouse + (माप_प्रकार)offset);

	वापस प्र_लिखो(buf, "%u\n", *field);
पूर्ण

अटल sमाप_प्रकार psmouse_set_पूर्णांक_attr(काष्ठा psmouse *psmouse, व्योम *offset, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक *field = (अचिन्हित पूर्णांक *)((अक्षर *)psmouse + (माप_प्रकार)offset);
	अचिन्हित पूर्णांक value;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	*field = value;

	वापस count;
पूर्ण

अटल sमाप_प्रकार psmouse_attr_show_protocol(काष्ठा psmouse *psmouse, व्योम *data, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", psmouse->protocol->name);
पूर्ण

अटल sमाप_प्रकार psmouse_attr_set_protocol(काष्ठा psmouse *psmouse, व्योम *data, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा serio *serio = psmouse->ps2dev.serio;
	काष्ठा psmouse *parent = शून्य;
	काष्ठा input_dev *old_dev, *new_dev;
	स्थिर काष्ठा psmouse_protocol *proto, *old_proto;
	पूर्णांक error;
	पूर्णांक retry = 0;

	proto = psmouse_protocol_by_name(buf, count);
	अगर (!proto)
		वापस -EINVAL;

	अगर (psmouse->protocol == proto)
		वापस count;

	new_dev = input_allocate_device();
	अगर (!new_dev)
		वापस -ENOMEM;

	जबतक (!list_empty(&serio->children)) अणु
		अगर (++retry > 3) अणु
			psmouse_warn(psmouse,
				     "failed to destroy children ports, protocol change aborted.\n");
			input_मुक्त_device(new_dev);
			वापस -EIO;
		पूर्ण

		mutex_unlock(&psmouse_mutex);
		serio_unरेजिस्टर_child_port(serio);
		mutex_lock(&psmouse_mutex);

		अगर (serio->drv != &psmouse_drv) अणु
			input_मुक्त_device(new_dev);
			वापस -ENODEV;
		पूर्ण

		अगर (psmouse->protocol == proto) अणु
			input_मुक्त_device(new_dev);
			वापस count; /* चयनed by other thपढ़ो */
		पूर्ण
	पूर्ण

	अगर (serio->parent && serio->id.type == SERIO_PS_PSTHRU) अणु
		parent = serio_get_drvdata(serio->parent);
		अगर (parent->pt_deactivate)
			parent->pt_deactivate(parent);
	पूर्ण

	old_dev = psmouse->dev;
	old_proto = psmouse->protocol;

	अगर (psmouse->disconnect)
		psmouse->disconnect(psmouse);

	psmouse_set_state(psmouse, PSMOUSE_IGNORE);

	psmouse->dev = new_dev;
	psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);

	अगर (psmouse_चयन_protocol(psmouse, proto) < 0) अणु
		psmouse_reset(psmouse);
		/* शेष to PSMOUSE_PS2 */
		psmouse_चयन_protocol(psmouse, &psmouse_protocols[0]);
	पूर्ण

	psmouse_initialize(psmouse);
	psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);

	अगर (psmouse->protocol->smbus_companion) अणु
		input_मुक्त_device(psmouse->dev);
		psmouse->dev = शून्य;
	पूर्ण अन्यथा अणु
		error = input_रेजिस्टर_device(psmouse->dev);
		अगर (error) अणु
			अगर (psmouse->disconnect)
				psmouse->disconnect(psmouse);

			psmouse_set_state(psmouse, PSMOUSE_IGNORE);
			input_मुक्त_device(new_dev);
			psmouse->dev = old_dev;
			psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);
			psmouse_चयन_protocol(psmouse, old_proto);
			psmouse_initialize(psmouse);
			psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);

			वापस error;
		पूर्ण
	पूर्ण

	अगर (old_dev)
		input_unरेजिस्टर_device(old_dev);

	अगर (parent && parent->pt_activate)
		parent->pt_activate(parent);

	वापस count;
पूर्ण

अटल sमाप_प्रकार psmouse_attr_set_rate(काष्ठा psmouse *psmouse, व्योम *data, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	psmouse->set_rate(psmouse, value);
	वापस count;
पूर्ण

अटल sमाप_प्रकार psmouse_attr_set_resolution(काष्ठा psmouse *psmouse, व्योम *data, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	psmouse->set_resolution(psmouse, value);
	वापस count;
पूर्ण


अटल पूर्णांक psmouse_set_maxproto(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	स्थिर काष्ठा psmouse_protocol *proto;

	अगर (!val)
		वापस -EINVAL;

	proto = psmouse_protocol_by_name(val, म_माप(val));

	अगर (!proto || !proto->maxproto)
		वापस -EINVAL;

	*((अचिन्हित पूर्णांक *)kp->arg) = proto->type;

	वापस 0;
पूर्ण

अटल पूर्णांक psmouse_get_maxproto(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक type = *((अचिन्हित पूर्णांक *)kp->arg);

	वापस प्र_लिखो(buffer, "%s\n", psmouse_protocol_by_type(type)->name);
पूर्ण

अटल पूर्णांक __init psmouse_init(व्योम)
अणु
	पूर्णांक err;

	lअगरebook_module_init();
	synaptics_module_init();
	hgpk_module_init();

	err = psmouse_smbus_module_init();
	अगर (err)
		वापस err;

	kpsmoused_wq = alloc_ordered_workqueue("kpsmoused", 0);
	अगर (!kpsmoused_wq) अणु
		pr_err("failed to create kpsmoused workqueue\n");
		err = -ENOMEM;
		जाओ err_smbus_निकास;
	पूर्ण

	err = serio_रेजिस्टर_driver(&psmouse_drv);
	अगर (err)
		जाओ err_destroy_wq;

	वापस 0;

err_destroy_wq:
	destroy_workqueue(kpsmoused_wq);
err_smbus_निकास:
	psmouse_smbus_module_निकास();
	वापस err;
पूर्ण

अटल व्योम __निकास psmouse_निकास(व्योम)
अणु
	serio_unरेजिस्टर_driver(&psmouse_drv);
	destroy_workqueue(kpsmoused_wq);
	psmouse_smbus_module_निकास();
पूर्ण

module_init(psmouse_init);
module_निकास(psmouse_निकास);
