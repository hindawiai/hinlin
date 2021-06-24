<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2000-2002 Vojtech Pavlik <vojtech@ucw.cz>
 *  Copyright (c) 2001-2002, 2007 Johann Deneux <johann.deneux@gmail.com>
 *
 *  USB/RS232 I-Force joysticks and wheels.
 */

#समावेश <यंत्र/unaligned.h>
#समावेश "iforce.h"

अटल काष्ठा अणु
	__s32 x;
	__s32 y;
पूर्ण अगरorce_hat_to_axis[16] = अणुअणु 0,-1पूर्ण, अणु 1,-1पूर्ण, अणु 1, 0पूर्ण, अणु 1, 1पूर्ण, अणु 0, 1पूर्ण, अणु-1, 1पूर्ण, अणु-1, 0पूर्ण, अणु-1,-1पूर्णपूर्ण;


व्योम अगरorce_dump_packet(काष्ठा अगरorce *अगरorce, अक्षर *msg, u16 cmd, अचिन्हित अक्षर *data)
अणु
	dev_dbg(अगरorce->dev->dev.parent, "%s %s cmd = %04x, data = %*ph\n",
		__func__, msg, cmd, LO(cmd), data);
पूर्ण

/*
 * Send a packet of bytes to the device
 */
पूर्णांक अगरorce_send_packet(काष्ठा अगरorce *अगरorce, u16 cmd, अचिन्हित अक्षर* data)
अणु
	/* Copy data to buffer */
	पूर्णांक n = LO(cmd);
	पूर्णांक c;
	पूर्णांक empty;
	पूर्णांक head, tail;
	अचिन्हित दीर्घ flags;

/*
 * Update head and tail of xmit buffer
 */
	spin_lock_irqsave(&अगरorce->xmit_lock, flags);

	head = अगरorce->xmit.head;
	tail = अगरorce->xmit.tail;


	अगर (CIRC_SPACE(head, tail, XMIT_SIZE) < n+2) अणु
		dev_warn(&अगरorce->dev->dev,
			 "not enough space in xmit buffer to send new packet\n");
		spin_unlock_irqrestore(&अगरorce->xmit_lock, flags);
		वापस -1;
	पूर्ण

	empty = head == tail;
	XMIT_INC(अगरorce->xmit.head, n+2);

/*
 * Store packet in xmit buffer
 */
	अगरorce->xmit.buf[head] = HI(cmd);
	XMIT_INC(head, 1);
	अगरorce->xmit.buf[head] = LO(cmd);
	XMIT_INC(head, 1);

	c = CIRC_SPACE_TO_END(head, tail, XMIT_SIZE);
	अगर (n < c) c=n;

	स_नकल(&अगरorce->xmit.buf[head],
	       data,
	       c);
	अगर (n != c) अणु
		स_नकल(&अगरorce->xmit.buf[0],
		       data + c,
		       n - c);
	पूर्ण
	XMIT_INC(head, n);

	spin_unlock_irqrestore(&अगरorce->xmit_lock, flags);
/*
 * If necessary, start the transmission
 */
	अगर (empty)
		अगरorce->xport_ops->xmit(अगरorce);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(अगरorce_send_packet);

/* Start or stop an effect */
पूर्णांक अगरorce_control_playback(काष्ठा अगरorce* अगरorce, u16 id, अचिन्हित पूर्णांक value)
अणु
	अचिन्हित अक्षर data[3];

	data[0] = LO(id);
	data[1] = (value > 0) ? ((value > 1) ? 0x41 : 0x01) : 0;
	data[2] = LO(value);
	वापस अगरorce_send_packet(अगरorce, FF_CMD_PLAY, data);
पूर्ण

/* Mark an effect that was being updated as पढ़ोy. That means it can be updated
 * again */
अटल पूर्णांक mark_core_as_पढ़ोy(काष्ठा अगरorce *अगरorce, अचिन्हित लघु addr)
अणु
	पूर्णांक i;

	अगर (!अगरorce->dev->ff)
		वापस 0;

	क्रम (i = 0; i < अगरorce->dev->ff->max_effects; ++i) अणु
		अगर (test_bit(FF_CORE_IS_USED, अगरorce->core_effects[i].flags) &&
		    (अगरorce->core_effects[i].mod1_chunk.start == addr ||
		     अगरorce->core_effects[i].mod2_chunk.start == addr)) अणु
			clear_bit(FF_CORE_UPDATE, अगरorce->core_effects[i].flags);
			वापस 0;
		पूर्ण
	पूर्ण
	dev_warn(&अगरorce->dev->dev, "unused effect %04x updated !!!\n", addr);
	वापस -1;
पूर्ण

अटल व्योम अगरorce_report_hats_buttons(काष्ठा अगरorce *अगरorce, u8 *data)
अणु
	काष्ठा input_dev *dev = अगरorce->dev;
	पूर्णांक i;

	input_report_असल(dev, ABS_HAT0X, अगरorce_hat_to_axis[data[6] >> 4].x);
	input_report_असल(dev, ABS_HAT0Y, अगरorce_hat_to_axis[data[6] >> 4].y);

	क्रम (i = 0; अगरorce->type->btn[i] >= 0; i++)
		input_report_key(dev, अगरorce->type->btn[i],
				 data[(i >> 3) + 5] & (1 << (i & 7)));

	/* If there are untouched bits left, पूर्णांकerpret them as the second hat */
	अगर (i <= 8) अणु
		u8 btns = data[6];

		अगर (test_bit(ABS_HAT1X, dev->असलbit)) अणु
			अगर (btns & BIT(3))
				input_report_असल(dev, ABS_HAT1X, -1);
			अन्यथा अगर (btns & BIT(1))
				input_report_असल(dev, ABS_HAT1X, 1);
			अन्यथा
				input_report_असल(dev, ABS_HAT1X, 0);
		पूर्ण

		अगर (test_bit(ABS_HAT1Y, dev->असलbit)) अणु
			अगर (btns & BIT(0))
				input_report_असल(dev, ABS_HAT1Y, -1);
			अन्यथा अगर (btns & BIT(2))
				input_report_असल(dev, ABS_HAT1Y, 1);
			अन्यथा
				input_report_असल(dev, ABS_HAT1Y, 0);
		पूर्ण
	पूर्ण
पूर्ण

व्योम अगरorce_process_packet(काष्ठा अगरorce *अगरorce,
			   u8 packet_id, u8 *data, माप_प्रकार len)
अणु
	काष्ठा input_dev *dev = अगरorce->dev;
	पूर्णांक i, j;

	चयन (packet_id) अणु

	हाल 0x01:	/* joystick position data */
		input_report_असल(dev, ABS_X,
				 (__s16) get_unaligned_le16(data));
		input_report_असल(dev, ABS_Y,
				 (__s16) get_unaligned_le16(data + 2));
		input_report_असल(dev, ABS_THROTTLE, 255 - data[4]);

		अगर (len >= 8 && test_bit(ABS_RUDDER ,dev->असलbit))
			input_report_असल(dev, ABS_RUDDER, (__s8)data[7]);

		अगरorce_report_hats_buttons(अगरorce, data);

		input_sync(dev);
		अवरोध;

	हाल 0x03:	/* wheel position data */
		input_report_असल(dev, ABS_WHEEL,
				 (__s16) get_unaligned_le16(data));
		input_report_असल(dev, ABS_GAS,   255 - data[2]);
		input_report_असल(dev, ABS_BRAKE, 255 - data[3]);

		अगरorce_report_hats_buttons(अगरorce, data);

		input_sync(dev);
		अवरोध;

	हाल 0x02:	/* status report */
		input_report_key(dev, BTN_DEAD, data[0] & 0x02);
		input_sync(dev);

		/* Check अगर an effect was just started or stopped */
		i = data[1] & 0x7f;
		अगर (data[1] & 0x80) अणु
			अगर (!test_and_set_bit(FF_CORE_IS_PLAYED, अगरorce->core_effects[i].flags)) अणु
				/* Report play event */
				input_report_ff_status(dev, i, FF_STATUS_PLAYING);
			पूर्ण
		पूर्ण अन्यथा अगर (test_and_clear_bit(FF_CORE_IS_PLAYED, अगरorce->core_effects[i].flags)) अणु
			/* Report stop event */
			input_report_ff_status(dev, i, FF_STATUS_STOPPED);
		पूर्ण

		क्रम (j = 3; j < len; j += 2)
			mark_core_as_पढ़ोy(अगरorce, get_unaligned_le16(data + j));

		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(अगरorce_process_packet);
