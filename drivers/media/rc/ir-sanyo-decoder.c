<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// ir-sanyo-decoder.c - handle SANYO IR Pulse/Space protocol
//
// Copyright (C) 2011 by Mauro Carvalho Chehab
//
// This protocol uses the NEC protocol timings. However, data is क्रमmatted as:
//	13 bits Custom Code
//	13 bits NOT(Custom Code)
//	8 bits Key data
//	8 bits NOT(Key data)
//
// According with LIRC, this protocol is used on Sanyo, Aiwa and Chinon
// Inक्रमmation क्रम this protocol is available at the Sanyo LC7461 datasheet.

#समावेश <linux/module.h>
#समावेश <linux/bitrev.h>
#समावेश "rc-core-priv.h"

#घोषणा SANYO_NBITS		(13+13+8+8)
#घोषणा SANYO_UNIT		563  /* us */
#घोषणा SANYO_HEADER_PULSE	(16  * SANYO_UNIT)
#घोषणा SANYO_HEADER_SPACE	(8   * SANYO_UNIT)
#घोषणा SANYO_BIT_PULSE		(1   * SANYO_UNIT)
#घोषणा SANYO_BIT_0_SPACE	(1   * SANYO_UNIT)
#घोषणा SANYO_BIT_1_SPACE	(3   * SANYO_UNIT)
#घोषणा SANYO_REPEAT_SPACE	(150 * SANYO_UNIT)
#घोषणा	SANYO_TRAILER_PULSE	(1   * SANYO_UNIT)
#घोषणा	SANYO_TRAILER_SPACE	(10  * SANYO_UNIT)	/* in fact, 42 */

क्रमागत sanyo_state अणु
	STATE_INACTIVE,
	STATE_HEADER_SPACE,
	STATE_BIT_PULSE,
	STATE_BIT_SPACE,
	STATE_TRAILER_PULSE,
	STATE_TRAILER_SPACE,
पूर्ण;

/**
 * ir_sanyo_decode() - Decode one SANYO pulse or space
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @ev:		the काष्ठा ir_raw_event descriptor of the pulse/space
 *
 * This function वापसs -EINVAL अगर the pulse violates the state machine
 */
अटल पूर्णांक ir_sanyo_decode(काष्ठा rc_dev *dev, काष्ठा ir_raw_event ev)
अणु
	काष्ठा sanyo_dec *data = &dev->raw->sanyo;
	u32 scancode;
	u16 address;
	u8 command, not_command;

	अगर (!is_timing_event(ev)) अणु
		अगर (ev.reset) अणु
			dev_dbg(&dev->dev, "SANYO event reset received. reset to state 0\n");
			data->state = STATE_INACTIVE;
		पूर्ण
		वापस 0;
	पूर्ण

	dev_dbg(&dev->dev, "SANYO decode started at state %d (%uus %s)\n",
		data->state, ev.duration, TO_STR(ev.pulse));

	चयन (data->state) अणु

	हाल STATE_INACTIVE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (eq_margin(ev.duration, SANYO_HEADER_PULSE, SANYO_UNIT / 2)) अणु
			data->count = 0;
			data->state = STATE_HEADER_SPACE;
			वापस 0;
		पूर्ण
		अवरोध;


	हाल STATE_HEADER_SPACE:
		अगर (ev.pulse)
			अवरोध;

		अगर (eq_margin(ev.duration, SANYO_HEADER_SPACE, SANYO_UNIT / 2)) अणु
			data->state = STATE_BIT_PULSE;
			वापस 0;
		पूर्ण

		अवरोध;

	हाल STATE_BIT_PULSE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, SANYO_BIT_PULSE, SANYO_UNIT / 2))
			अवरोध;

		data->state = STATE_BIT_SPACE;
		वापस 0;

	हाल STATE_BIT_SPACE:
		अगर (ev.pulse)
			अवरोध;

		अगर (!data->count && geq_margin(ev.duration, SANYO_REPEAT_SPACE, SANYO_UNIT / 2)) अणु
			rc_repeat(dev);
			dev_dbg(&dev->dev, "SANYO repeat last key\n");
			data->state = STATE_INACTIVE;
			वापस 0;
		पूर्ण

		data->bits <<= 1;
		अगर (eq_margin(ev.duration, SANYO_BIT_1_SPACE, SANYO_UNIT / 2))
			data->bits |= 1;
		अन्यथा अगर (!eq_margin(ev.duration, SANYO_BIT_0_SPACE, SANYO_UNIT / 2))
			अवरोध;
		data->count++;

		अगर (data->count == SANYO_NBITS)
			data->state = STATE_TRAILER_PULSE;
		अन्यथा
			data->state = STATE_BIT_PULSE;

		वापस 0;

	हाल STATE_TRAILER_PULSE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, SANYO_TRAILER_PULSE, SANYO_UNIT / 2))
			अवरोध;

		data->state = STATE_TRAILER_SPACE;
		वापस 0;

	हाल STATE_TRAILER_SPACE:
		अगर (ev.pulse)
			अवरोध;

		अगर (!geq_margin(ev.duration, SANYO_TRAILER_SPACE, SANYO_UNIT / 2))
			अवरोध;

		address     = bitrev16((data->bits >> 29) & 0x1fff) >> 3;
		/* not_address = bitrev16((data->bits >> 16) & 0x1fff) >> 3; */
		command	    = bitrev8((data->bits >>  8) & 0xff);
		not_command = bitrev8((data->bits >>  0) & 0xff);

		अगर ((command ^ not_command) != 0xff) अणु
			dev_dbg(&dev->dev, "SANYO checksum error: received 0x%08llx\n",
				data->bits);
			data->state = STATE_INACTIVE;
			वापस 0;
		पूर्ण

		scancode = address << 8 | command;
		dev_dbg(&dev->dev, "SANYO scancode: 0x%06x\n", scancode);
		rc_keyकरोwn(dev, RC_PROTO_SANYO, scancode, 0);
		data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

	dev_dbg(&dev->dev, "SANYO decode failed at count %d state %d (%uus %s)\n",
		data->count, data->state, ev.duration, TO_STR(ev.pulse));
	data->state = STATE_INACTIVE;
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा ir_raw_timings_pd ir_sanyo_timings = अणु
	.header_pulse  = SANYO_HEADER_PULSE,
	.header_space  = SANYO_HEADER_SPACE,
	.bit_pulse     = SANYO_BIT_PULSE,
	.bit_space[0]  = SANYO_BIT_0_SPACE,
	.bit_space[1]  = SANYO_BIT_1_SPACE,
	.trailer_pulse = SANYO_TRAILER_PULSE,
	.trailer_space = SANYO_TRAILER_SPACE,
	.msb_first     = 1,
पूर्ण;

/**
 * ir_sanyo_encode() - Encode a scancode as a stream of raw events
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
अटल पूर्णांक ir_sanyo_encode(क्रमागत rc_proto protocol, u32 scancode,
			   काष्ठा ir_raw_event *events, अचिन्हित पूर्णांक max)
अणु
	काष्ठा ir_raw_event *e = events;
	पूर्णांक ret;
	u64 raw;

	raw = ((u64)(bitrev16(scancode >> 8) & 0xfff8) << (8 + 8 + 13 - 3)) |
	      ((u64)(bitrev16(~scancode >> 8) & 0xfff8) << (8 + 8 +  0 - 3)) |
	      ((bitrev8(scancode) & 0xff) << 8) |
	      (bitrev8(~scancode) & 0xff);

	ret = ir_raw_gen_pd(&e, max, &ir_sanyo_timings, SANYO_NBITS, raw);
	अगर (ret < 0)
		वापस ret;

	वापस e - events;
पूर्ण

अटल काष्ठा ir_raw_handler sanyo_handler = अणु
	.protocols	= RC_PROTO_BIT_SANYO,
	.decode		= ir_sanyo_decode,
	.encode		= ir_sanyo_encode,
	.carrier	= 38000,
	.min_समयout	= SANYO_TRAILER_SPACE,
पूर्ण;

अटल पूर्णांक __init ir_sanyo_decode_init(व्योम)
अणु
	ir_raw_handler_रेजिस्टर(&sanyo_handler);

	prपूर्णांकk(KERN_INFO "IR SANYO protocol handler initialized\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास ir_sanyo_decode_निकास(व्योम)
अणु
	ir_raw_handler_unरेजिस्टर(&sanyo_handler);
पूर्ण

module_init(ir_sanyo_decode_init);
module_निकास(ir_sanyo_decode_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_AUTHOR("Red Hat Inc. (http://www.redhat.com)");
MODULE_DESCRIPTION("SANYO IR protocol decoder");
