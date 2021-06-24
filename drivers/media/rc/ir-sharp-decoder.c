<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ir-sharp-decoder.c - handle Sharp IR Pulse/Space protocol
 *
 * Copyright (C) 2013-2014 Imagination Technologies Ltd.
 *
 * Based on NEC decoder:
 * Copyright (C) 2010 by Mauro Carvalho Chehab
 */

#समावेश <linux/bitrev.h>
#समावेश <linux/module.h>
#समावेश "rc-core-priv.h"

#घोषणा SHARP_NBITS		15
#घोषणा SHARP_UNIT		40  /* us */
#घोषणा SHARP_BIT_PULSE		(8    * SHARP_UNIT) /* 320us */
#घोषणा SHARP_BIT_0_PERIOD	(25   * SHARP_UNIT) /* 1ms (680us space) */
#घोषणा SHARP_BIT_1_PERIOD	(50   * SHARP_UNIT) /* 2ms (1680ms space) */
#घोषणा SHARP_ECHO_SPACE	(1000 * SHARP_UNIT) /* 40 ms */
#घोषणा SHARP_TRAILER_SPACE	(125  * SHARP_UNIT) /* 5 ms (even दीर्घer) */

क्रमागत sharp_state अणु
	STATE_INACTIVE,
	STATE_BIT_PULSE,
	STATE_BIT_SPACE,
	STATE_TRAILER_PULSE,
	STATE_ECHO_SPACE,
	STATE_TRAILER_SPACE,
पूर्ण;

/**
 * ir_sharp_decode() - Decode one Sharp pulse or space
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @ev:		the काष्ठा ir_raw_event descriptor of the pulse/space
 *
 * This function वापसs -EINVAL अगर the pulse violates the state machine
 */
अटल पूर्णांक ir_sharp_decode(काष्ठा rc_dev *dev, काष्ठा ir_raw_event ev)
अणु
	काष्ठा sharp_dec *data = &dev->raw->sharp;
	u32 msg, echo, address, command, scancode;

	अगर (!is_timing_event(ev)) अणु
		अगर (ev.reset)
			data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

	dev_dbg(&dev->dev, "Sharp decode started at state %d (%uus %s)\n",
		data->state, ev.duration, TO_STR(ev.pulse));

	चयन (data->state) अणु

	हाल STATE_INACTIVE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, SHARP_BIT_PULSE,
			       SHARP_BIT_PULSE / 2))
			अवरोध;

		data->count = 0;
		data->pulse_len = ev.duration;
		data->state = STATE_BIT_SPACE;
		वापस 0;

	हाल STATE_BIT_PULSE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, SHARP_BIT_PULSE,
			       SHARP_BIT_PULSE / 2))
			अवरोध;

		data->pulse_len = ev.duration;
		data->state = STATE_BIT_SPACE;
		वापस 0;

	हाल STATE_BIT_SPACE:
		अगर (ev.pulse)
			अवरोध;

		data->bits <<= 1;
		अगर (eq_margin(data->pulse_len + ev.duration, SHARP_BIT_1_PERIOD,
			      SHARP_BIT_PULSE * 2))
			data->bits |= 1;
		अन्यथा अगर (!eq_margin(data->pulse_len + ev.duration,
				    SHARP_BIT_0_PERIOD, SHARP_BIT_PULSE * 2))
			अवरोध;
		data->count++;

		अगर (data->count == SHARP_NBITS ||
		    data->count == SHARP_NBITS * 2)
			data->state = STATE_TRAILER_PULSE;
		अन्यथा
			data->state = STATE_BIT_PULSE;

		वापस 0;

	हाल STATE_TRAILER_PULSE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, SHARP_BIT_PULSE,
			       SHARP_BIT_PULSE / 2))
			अवरोध;

		अगर (data->count == SHARP_NBITS) अणु
			/* exp,chk bits should be 1,0 */
			अगर ((data->bits & 0x3) != 0x2 &&
			/* DENON variant, both chk bits 0 */
			    (data->bits & 0x3) != 0x0)
				अवरोध;
			data->state = STATE_ECHO_SPACE;
		पूर्ण अन्यथा अणु
			data->state = STATE_TRAILER_SPACE;
		पूर्ण
		वापस 0;

	हाल STATE_ECHO_SPACE:
		अगर (ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, SHARP_ECHO_SPACE,
			       SHARP_ECHO_SPACE / 4))
			अवरोध;

		data->state = STATE_BIT_PULSE;

		वापस 0;

	हाल STATE_TRAILER_SPACE:
		अगर (ev.pulse)
			अवरोध;

		अगर (!geq_margin(ev.duration, SHARP_TRAILER_SPACE,
				SHARP_BIT_PULSE / 2))
			अवरोध;

		/* Validate - command, ext, chk should be inverted in 2nd */
		msg = (data->bits >> 15) & 0x7fff;
		echo = data->bits & 0x7fff;
		अगर ((msg ^ echo) != 0x3ff) अणु
			dev_dbg(&dev->dev,
				"Sharp checksum error: received 0x%04x, 0x%04x\n",
				msg, echo);
			अवरोध;
		पूर्ण

		address = bitrev8((msg >> 7) & 0xf8);
		command = bitrev8((msg >> 2) & 0xff);

		scancode = address << 8 | command;
		dev_dbg(&dev->dev, "Sharp scancode 0x%04x\n", scancode);

		rc_keyकरोwn(dev, RC_PROTO_SHARP, scancode, 0);
		data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

	dev_dbg(&dev->dev, "Sharp decode failed at count %d state %d (%uus %s)\n",
		data->count, data->state, ev.duration, TO_STR(ev.pulse));
	data->state = STATE_INACTIVE;
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा ir_raw_timings_pd ir_sharp_timings = अणु
	.header_pulse  = 0,
	.header_space  = 0,
	.bit_pulse     = SHARP_BIT_PULSE,
	.bit_space[0]  = SHARP_BIT_0_PERIOD,
	.bit_space[1]  = SHARP_BIT_1_PERIOD,
	.trailer_pulse = SHARP_BIT_PULSE,
	.trailer_space = SHARP_ECHO_SPACE,
	.msb_first     = 1,
पूर्ण;

/**
 * ir_sharp_encode() - Encode a scancode as a stream of raw events
 *
 * @protocol:	protocol to encode
 * @scancode:	scancode to encode
 * @events:	array of raw ir events to ग_लिखो पूर्णांकo
 * @max:	maximum size of @events
 *
 * Returns:	The number of events written.
 *		-ENOBUFS अगर there isn't enough space in the array to fit the
 *		encoding. In this हाल all @max events will have been written.
 */
अटल पूर्णांक ir_sharp_encode(क्रमागत rc_proto protocol, u32 scancode,
			   काष्ठा ir_raw_event *events, अचिन्हित पूर्णांक max)
अणु
	काष्ठा ir_raw_event *e = events;
	पूर्णांक ret;
	u32 raw;

	raw = (((bitrev8(scancode >> 8) >> 3) << 8) & 0x1f00) |
		bitrev8(scancode);
	ret = ir_raw_gen_pd(&e, max, &ir_sharp_timings, SHARP_NBITS,
			    (raw << 2) | 2);
	अगर (ret < 0)
		वापस ret;

	max -= ret;

	raw = (((bitrev8(scancode >> 8) >> 3) << 8) & 0x1f00) |
		bitrev8(~scancode);
	ret = ir_raw_gen_pd(&e, max, &ir_sharp_timings, SHARP_NBITS,
			    (raw << 2) | 1);
	अगर (ret < 0)
		वापस ret;

	वापस e - events;
पूर्ण

अटल काष्ठा ir_raw_handler sharp_handler = अणु
	.protocols	= RC_PROTO_BIT_SHARP,
	.decode		= ir_sharp_decode,
	.encode		= ir_sharp_encode,
	.carrier	= 38000,
	.min_समयout	= SHARP_ECHO_SPACE + SHARP_ECHO_SPACE / 4,
पूर्ण;

अटल पूर्णांक __init ir_sharp_decode_init(व्योम)
अणु
	ir_raw_handler_रेजिस्टर(&sharp_handler);

	pr_info("IR Sharp protocol handler initialized\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास ir_sharp_decode_निकास(व्योम)
अणु
	ir_raw_handler_unरेजिस्टर(&sharp_handler);
पूर्ण

module_init(ir_sharp_decode_init);
module_निकास(ir_sharp_decode_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("James Hogan <jhogan@kernel.org>");
MODULE_DESCRIPTION("Sharp IR protocol decoder");
