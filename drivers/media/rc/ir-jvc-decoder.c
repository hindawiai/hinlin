<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ir-jvc-decoder.c - handle JVC IR Pulse/Space protocol
 *
 * Copyright (C) 2010 by David Hथअrdeman <david@hardeman.nu>
 */

#समावेश <linux/bitrev.h>
#समावेश <linux/module.h>
#समावेश "rc-core-priv.h"

#घोषणा JVC_NBITS		16		/* dev(8) + func(8) */
#घोषणा JVC_UNIT		525		/* us */
#घोषणा JVC_HEADER_PULSE	(16 * JVC_UNIT) /* lack of header -> repeat */
#घोषणा JVC_HEADER_SPACE	(8  * JVC_UNIT)
#घोषणा JVC_BIT_PULSE		(1  * JVC_UNIT)
#घोषणा JVC_BIT_0_SPACE		(1  * JVC_UNIT)
#घोषणा JVC_BIT_1_SPACE		(3  * JVC_UNIT)
#घोषणा JVC_TRAILER_PULSE	(1  * JVC_UNIT)
#घोषणा	JVC_TRAILER_SPACE	(35 * JVC_UNIT)

क्रमागत jvc_state अणु
	STATE_INACTIVE,
	STATE_HEADER_SPACE,
	STATE_BIT_PULSE,
	STATE_BIT_SPACE,
	STATE_TRAILER_PULSE,
	STATE_TRAILER_SPACE,
	STATE_CHECK_REPEAT,
पूर्ण;

/**
 * ir_jvc_decode() - Decode one JVC pulse or space
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @ev:   the काष्ठा ir_raw_event descriptor of the pulse/space
 *
 * This function वापसs -EINVAL अगर the pulse violates the state machine
 */
अटल पूर्णांक ir_jvc_decode(काष्ठा rc_dev *dev, काष्ठा ir_raw_event ev)
अणु
	काष्ठा jvc_dec *data = &dev->raw->jvc;

	अगर (!is_timing_event(ev)) अणु
		अगर (ev.reset)
			data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

	अगर (!geq_margin(ev.duration, JVC_UNIT, JVC_UNIT / 2))
		जाओ out;

	dev_dbg(&dev->dev, "JVC decode started at state %d (%uus %s)\n",
		data->state, ev.duration, TO_STR(ev.pulse));

again:
	चयन (data->state) अणु

	हाल STATE_INACTIVE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, JVC_HEADER_PULSE, JVC_UNIT / 2))
			अवरोध;

		data->count = 0;
		data->first = true;
		data->toggle = !data->toggle;
		data->state = STATE_HEADER_SPACE;
		वापस 0;

	हाल STATE_HEADER_SPACE:
		अगर (ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, JVC_HEADER_SPACE, JVC_UNIT / 2))
			अवरोध;

		data->state = STATE_BIT_PULSE;
		वापस 0;

	हाल STATE_BIT_PULSE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, JVC_BIT_PULSE, JVC_UNIT / 2))
			अवरोध;

		data->state = STATE_BIT_SPACE;
		वापस 0;

	हाल STATE_BIT_SPACE:
		अगर (ev.pulse)
			अवरोध;

		data->bits <<= 1;
		अगर (eq_margin(ev.duration, JVC_BIT_1_SPACE, JVC_UNIT / 2)) अणु
			data->bits |= 1;
			decrease_duration(&ev, JVC_BIT_1_SPACE);
		पूर्ण अन्यथा अगर (eq_margin(ev.duration, JVC_BIT_0_SPACE, JVC_UNIT / 2))
			decrease_duration(&ev, JVC_BIT_0_SPACE);
		अन्यथा
			अवरोध;
		data->count++;

		अगर (data->count == JVC_NBITS)
			data->state = STATE_TRAILER_PULSE;
		अन्यथा
			data->state = STATE_BIT_PULSE;
		वापस 0;

	हाल STATE_TRAILER_PULSE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, JVC_TRAILER_PULSE, JVC_UNIT / 2))
			अवरोध;

		data->state = STATE_TRAILER_SPACE;
		वापस 0;

	हाल STATE_TRAILER_SPACE:
		अगर (ev.pulse)
			अवरोध;

		अगर (!geq_margin(ev.duration, JVC_TRAILER_SPACE, JVC_UNIT / 2))
			अवरोध;

		अगर (data->first) अणु
			u32 scancode;
			scancode = (bitrev8((data->bits >> 8) & 0xff) << 8) |
				   (bitrev8((data->bits >> 0) & 0xff) << 0);
			dev_dbg(&dev->dev, "JVC scancode 0x%04x\n", scancode);
			rc_keyकरोwn(dev, RC_PROTO_JVC, scancode, data->toggle);
			data->first = false;
			data->old_bits = data->bits;
		पूर्ण अन्यथा अगर (data->bits == data->old_bits) अणु
			dev_dbg(&dev->dev, "JVC repeat\n");
			rc_repeat(dev);
		पूर्ण अन्यथा अणु
			dev_dbg(&dev->dev, "JVC invalid repeat msg\n");
			अवरोध;
		पूर्ण

		data->count = 0;
		data->state = STATE_CHECK_REPEAT;
		वापस 0;

	हाल STATE_CHECK_REPEAT:
		अगर (!ev.pulse)
			अवरोध;

		अगर (eq_margin(ev.duration, JVC_HEADER_PULSE, JVC_UNIT / 2))
			data->state = STATE_INACTIVE;
  अन्यथा
			data->state = STATE_BIT_PULSE;
		जाओ again;
	पूर्ण

out:
	dev_dbg(&dev->dev, "JVC decode failed at state %d (%uus %s)\n",
		data->state, ev.duration, TO_STR(ev.pulse));
	data->state = STATE_INACTIVE;
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा ir_raw_timings_pd ir_jvc_timings = अणु
	.header_pulse  = JVC_HEADER_PULSE,
	.header_space  = JVC_HEADER_SPACE,
	.bit_pulse     = JVC_BIT_PULSE,
	.bit_space[0]  = JVC_BIT_0_SPACE,
	.bit_space[1]  = JVC_BIT_1_SPACE,
	.trailer_pulse = JVC_TRAILER_PULSE,
	.trailer_space = JVC_TRAILER_SPACE,
	.msb_first     = 1,
पूर्ण;

/**
 * ir_jvc_encode() - Encode a scancode as a stream of raw events
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
अटल पूर्णांक ir_jvc_encode(क्रमागत rc_proto protocol, u32 scancode,
			 काष्ठा ir_raw_event *events, अचिन्हित पूर्णांक max)
अणु
	काष्ठा ir_raw_event *e = events;
	पूर्णांक ret;
	u32 raw = (bitrev8((scancode >> 8) & 0xff) << 8) |
		  (bitrev8((scancode >> 0) & 0xff) << 0);

	ret = ir_raw_gen_pd(&e, max, &ir_jvc_timings, JVC_NBITS, raw);
	अगर (ret < 0)
		वापस ret;

	वापस e - events;
पूर्ण

अटल काष्ठा ir_raw_handler jvc_handler = अणु
	.protocols	= RC_PROTO_BIT_JVC,
	.decode		= ir_jvc_decode,
	.encode		= ir_jvc_encode,
	.carrier	= 38000,
	.min_समयout	= JVC_TRAILER_SPACE,
पूर्ण;

अटल पूर्णांक __init ir_jvc_decode_init(व्योम)
अणु
	ir_raw_handler_रेजिस्टर(&jvc_handler);

	prपूर्णांकk(KERN_INFO "IR JVC protocol handler initialized\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास ir_jvc_decode_निकास(व्योम)
अणु
	ir_raw_handler_unरेजिस्टर(&jvc_handler);
पूर्ण

module_init(ir_jvc_decode_init);
module_निकास(ir_jvc_decode_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Hथअrdeman <david@hardeman.nu>");
MODULE_DESCRIPTION("JVC IR protocol decoder");
