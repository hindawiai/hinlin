<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ir-xmp-decoder.c - handle XMP IR Pulse/Space protocol
 *
 * Copyright (C) 2014 by Marcel Mol
 *
 * - Based on info from http://www.hअगरi-remote.com
 * - Ignore Toggle=9 frames
 * - Ignore XMP-1 XMP-2 dअगरference, always store 16 bit OBC
 */

#समावेश <linux/bitrev.h>
#समावेश <linux/module.h>
#समावेश "rc-core-priv.h"

#घोषणा XMP_UNIT		  136 /* us */
#घोषणा XMP_LEADER		  210 /* us */
#घोषणा XMP_NIBBLE_PREFIX	  760 /* us */
#घोषणा	XMP_HALFFRAME_SPACE	13800 /* us */
/* should be 80ms but not all duration supliers can go that high */
#घोषणा	XMP_TRAILER_SPACE	20000

क्रमागत xmp_state अणु
	STATE_INACTIVE,
	STATE_LEADER_PULSE,
	STATE_NIBBLE_SPACE,
पूर्ण;

/**
 * ir_xmp_decode() - Decode one XMP pulse or space
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @ev:		the काष्ठा ir_raw_event descriptor of the pulse/space
 *
 * This function वापसs -EINVAL अगर the pulse violates the state machine
 */
अटल पूर्णांक ir_xmp_decode(काष्ठा rc_dev *dev, काष्ठा ir_raw_event ev)
अणु
	काष्ठा xmp_dec *data = &dev->raw->xmp;

	अगर (!is_timing_event(ev)) अणु
		अगर (ev.reset)
			data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

	dev_dbg(&dev->dev, "XMP decode started at state %d %d (%uus %s)\n",
		data->state, data->count, ev.duration, TO_STR(ev.pulse));

	चयन (data->state) अणु

	हाल STATE_INACTIVE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (eq_margin(ev.duration, XMP_LEADER, XMP_UNIT / 2)) अणु
			data->count = 0;
			data->state = STATE_NIBBLE_SPACE;
		पूर्ण

		वापस 0;

	हाल STATE_LEADER_PULSE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (eq_margin(ev.duration, XMP_LEADER, XMP_UNIT / 2))
			data->state = STATE_NIBBLE_SPACE;

		वापस 0;

	हाल STATE_NIBBLE_SPACE:
		अगर (ev.pulse)
			अवरोध;

		अगर (geq_margin(ev.duration, XMP_TRAILER_SPACE, XMP_NIBBLE_PREFIX)) अणु
			पूर्णांक भागider, i;
			u8 addr, subaddr, subaddr2, toggle, oem, obc1, obc2, sum1, sum2;
			u32 *n;
			u32 scancode;

			अगर (data->count != 16) अणु
				dev_dbg(&dev->dev, "received TRAILER period at index %d: %u\n",
					data->count, ev.duration);
				data->state = STATE_INACTIVE;
				वापस -EINVAL;
			पूर्ण

			n = data->durations;
			/*
			 * the 4th nibble should be 15 so base the भागider on this
			 * to transक्रमm durations पूर्णांकo nibbles. Subtract 2000 from
			 * the भागider to compensate क्रम fluctuations in the संकेत
			 */
			भागider = (n[3] - XMP_NIBBLE_PREFIX) / 15 - 2000;
			अगर (भागider < 50) अणु
				dev_dbg(&dev->dev, "divider to small %d.\n",
					भागider);
				data->state = STATE_INACTIVE;
				वापस -EINVAL;
			पूर्ण

			/* convert to nibbles and करो some sanity checks */
			क्रम (i = 0; i < 16; i++)
				n[i] = (n[i] - XMP_NIBBLE_PREFIX) / भागider;
			sum1 = (15 + n[0] + n[1] + n[2] + n[3] +
				n[4] + n[5] + n[6] + n[7]) % 16;
			sum2 = (15 + n[8] + n[9] + n[10] + n[11] +
				n[12] + n[13] + n[14] + n[15]) % 16;

			अगर (sum1 != 15 || sum2 != 15) अणु
				dev_dbg(&dev->dev, "checksum errors sum1=0x%X sum2=0x%X\n",
					sum1, sum2);
				data->state = STATE_INACTIVE;
				वापस -EINVAL;
			पूर्ण

			subaddr  = n[0] << 4 | n[2];
			subaddr2 = n[8] << 4 | n[11];
			oem      = n[4] << 4 | n[5];
			addr     = n[6] << 4 | n[7];
			toggle   = n[10];
			obc1 = n[12] << 4 | n[13];
			obc2 = n[14] << 4 | n[15];
			अगर (subaddr != subaddr2) अणु
				dev_dbg(&dev->dev, "subaddress nibbles mismatch 0x%02X != 0x%02X\n",
					subaddr, subaddr2);
				data->state = STATE_INACTIVE;
				वापस -EINVAL;
			पूर्ण
			अगर (oem != 0x44)
				dev_dbg(&dev->dev, "Warning: OEM nibbles 0x%02X. Expected 0x44\n",
					oem);

			scancode = addr << 24 | subaddr << 16 |
				   obc1 << 8 | obc2;
			dev_dbg(&dev->dev, "XMP scancode 0x%06x\n", scancode);

			अगर (toggle == 0) अणु
				rc_keyकरोwn(dev, RC_PROTO_XMP, scancode, 0);
			पूर्ण अन्यथा अणु
				rc_repeat(dev);
				dev_dbg(&dev->dev, "Repeat last key\n");
			पूर्ण
			data->state = STATE_INACTIVE;

			वापस 0;

		पूर्ण अन्यथा अगर (geq_margin(ev.duration, XMP_HALFFRAME_SPACE, XMP_NIBBLE_PREFIX)) अणु
			/* Expect 8 or 16 nibble pulses. 16 in हाल of 'final' frame */
			अगर (data->count == 16) अणु
				dev_dbg(&dev->dev, "received half frame pulse at index %d. Probably a final frame key-up event: %u\n",
					data->count, ev.duration);
				/*
				 * TODO: क्रम now go back to half frame position
				 *	 so trailer can be found and key press
				 *	 can be handled.
				 */
				data->count = 8;
			पूर्ण

			अन्यथा अगर (data->count != 8)
				dev_dbg(&dev->dev, "received half frame pulse at index %d: %u\n",
					data->count, ev.duration);
			data->state = STATE_LEADER_PULSE;

			वापस 0;

		पूर्ण अन्यथा अगर (geq_margin(ev.duration, XMP_NIBBLE_PREFIX, XMP_UNIT)) अणु
			/* store nibble raw data, decode after trailer */
			अगर (data->count == 16) अणु
				dev_dbg(&dev->dev, "too many pulses (%d) ignoring: %u\n",
					data->count, ev.duration);
				data->state = STATE_INACTIVE;
				वापस -EINVAL;
			पूर्ण
			data->durations[data->count] = ev.duration;
			data->count++;
			data->state = STATE_LEADER_PULSE;

			वापस 0;

		पूर्ण

		अवरोध;
	पूर्ण

	dev_dbg(&dev->dev, "XMP decode failed at count %d state %d (%uus %s)\n",
		data->count, data->state, ev.duration, TO_STR(ev.pulse));
	data->state = STATE_INACTIVE;
	वापस -EINVAL;
पूर्ण

अटल काष्ठा ir_raw_handler xmp_handler = अणु
	.protocols	= RC_PROTO_BIT_XMP,
	.decode		= ir_xmp_decode,
	.min_समयout	= XMP_TRAILER_SPACE,
पूर्ण;

अटल पूर्णांक __init ir_xmp_decode_init(व्योम)
अणु
	ir_raw_handler_रेजिस्टर(&xmp_handler);

	prपूर्णांकk(KERN_INFO "IR XMP protocol handler initialized\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास ir_xmp_decode_निकास(व्योम)
अणु
	ir_raw_handler_unरेजिस्टर(&xmp_handler);
पूर्ण

module_init(ir_xmp_decode_init);
module_निकास(ir_xmp_decode_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marcel Mol <marcel@mesa.nl>");
MODULE_AUTHOR("MESA Consulting (http://www.mesa.nl)");
MODULE_DESCRIPTION("XMP IR protocol decoder");
