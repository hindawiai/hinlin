<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ir-rc6-decoder.c - A decoder क्रम the RC6 IR protocol
 *
 * Copyright (C) 2010 by David Hथअrdeman <david@hardeman.nu>
 */

#समावेश "rc-core-priv.h"
#समावेश <linux/module.h>

/*
 * This decoder currently supports:
 * RC6-0-16	(standard toggle bit in header)
 * RC6-6A-20	(no toggle bit)
 * RC6-6A-24	(no toggle bit)
 * RC6-6A-32	(MCE version with toggle bit in body)
 */

#घोषणा RC6_UNIT		444	/* microseconds */
#घोषणा RC6_HEADER_NBITS	4	/* not including toggle bit */
#घोषणा RC6_0_NBITS		16
#घोषणा RC6_6A_32_NBITS		32
#घोषणा RC6_6A_NBITS		128	/* Variable 8..128 */
#घोषणा RC6_PREFIX_PULSE	(6 * RC6_UNIT)
#घोषणा RC6_PREFIX_SPACE	(2 * RC6_UNIT)
#घोषणा RC6_BIT_START		(1 * RC6_UNIT)
#घोषणा RC6_BIT_END		(1 * RC6_UNIT)
#घोषणा RC6_TOGGLE_START	(2 * RC6_UNIT)
#घोषणा RC6_TOGGLE_END		(2 * RC6_UNIT)
#घोषणा RC6_SUFFIX_SPACE	(6 * RC6_UNIT)
#घोषणा RC6_MODE_MASK		0x07	/* क्रम the header bits */
#घोषणा RC6_STARTBIT_MASK	0x08	/* क्रम the header bits */
#घोषणा RC6_6A_MCE_TOGGLE_MASK	0x8000	/* क्रम the body bits */
#घोषणा RC6_6A_LCC_MASK		0xffff0000 /* RC6-6A-32 दीर्घ customer code mask */
#घोषणा RC6_6A_MCE_CC		0x800f0000 /* MCE customer code */
#घोषणा RC6_6A_ZOTAC_CC		0x80340000 /* Zotac customer code */
#घोषणा RC6_6A_KATHREIN_CC	0x80460000 /* Kathrein RCU-676 customer code */
#अगर_अघोषित अक्षर_बिट
#घोषणा अक्षर_बिट 8	/* Normally in <सीमा.स> */
#पूर्ण_अगर

क्रमागत rc6_mode अणु
	RC6_MODE_0,
	RC6_MODE_6A,
	RC6_MODE_UNKNOWN,
पूर्ण;

क्रमागत rc6_state अणु
	STATE_INACTIVE,
	STATE_PREFIX_SPACE,
	STATE_HEADER_BIT_START,
	STATE_HEADER_BIT_END,
	STATE_TOGGLE_START,
	STATE_TOGGLE_END,
	STATE_BODY_BIT_START,
	STATE_BODY_BIT_END,
	STATE_FINISHED,
पूर्ण;

अटल क्रमागत rc6_mode rc6_mode(काष्ठा rc6_dec *data)
अणु
	चयन (data->header & RC6_MODE_MASK) अणु
	हाल 0:
		वापस RC6_MODE_0;
	हाल 6:
		अगर (!data->toggle)
			वापस RC6_MODE_6A;
		fallthrough;
	शेष:
		वापस RC6_MODE_UNKNOWN;
	पूर्ण
पूर्ण

/**
 * ir_rc6_decode() - Decode one RC6 pulse or space
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @ev:		the काष्ठा ir_raw_event descriptor of the pulse/space
 *
 * This function वापसs -EINVAL अगर the pulse violates the state machine
 */
अटल पूर्णांक ir_rc6_decode(काष्ठा rc_dev *dev, काष्ठा ir_raw_event ev)
अणु
	काष्ठा rc6_dec *data = &dev->raw->rc6;
	u32 scancode;
	u8 toggle;
	क्रमागत rc_proto protocol;

	अगर (!is_timing_event(ev)) अणु
		अगर (ev.reset)
			data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

	अगर (!geq_margin(ev.duration, RC6_UNIT, RC6_UNIT / 2))
		जाओ out;

again:
	dev_dbg(&dev->dev, "RC6 decode started at state %i (%uus %s)\n",
		data->state, ev.duration, TO_STR(ev.pulse));

	अगर (!geq_margin(ev.duration, RC6_UNIT, RC6_UNIT / 2))
		वापस 0;

	चयन (data->state) अणु

	हाल STATE_INACTIVE:
		अगर (!ev.pulse)
			अवरोध;

		/* Note: larger margin on first pulse since each RC6_UNIT
		   is quite लघु and some hardware takes some समय to
		   adjust to the संकेत */
		अगर (!eq_margin(ev.duration, RC6_PREFIX_PULSE, RC6_UNIT))
			अवरोध;

		data->state = STATE_PREFIX_SPACE;
		data->count = 0;
		वापस 0;

	हाल STATE_PREFIX_SPACE:
		अगर (ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, RC6_PREFIX_SPACE, RC6_UNIT / 2))
			अवरोध;

		data->state = STATE_HEADER_BIT_START;
		data->header = 0;
		वापस 0;

	हाल STATE_HEADER_BIT_START:
		अगर (!eq_margin(ev.duration, RC6_BIT_START, RC6_UNIT / 2))
			अवरोध;

		data->header <<= 1;
		अगर (ev.pulse)
			data->header |= 1;
		data->count++;
		data->state = STATE_HEADER_BIT_END;
		वापस 0;

	हाल STATE_HEADER_BIT_END:
		अगर (data->count == RC6_HEADER_NBITS)
			data->state = STATE_TOGGLE_START;
		अन्यथा
			data->state = STATE_HEADER_BIT_START;

		decrease_duration(&ev, RC6_BIT_END);
		जाओ again;

	हाल STATE_TOGGLE_START:
		अगर (!eq_margin(ev.duration, RC6_TOGGLE_START, RC6_UNIT / 2))
			अवरोध;

		data->toggle = ev.pulse;
		data->state = STATE_TOGGLE_END;
		वापस 0;

	हाल STATE_TOGGLE_END:
		अगर (!(data->header & RC6_STARTBIT_MASK)) अणु
			dev_dbg(&dev->dev, "RC6 invalid start bit\n");
			अवरोध;
		पूर्ण

		data->state = STATE_BODY_BIT_START;
		decrease_duration(&ev, RC6_TOGGLE_END);
		data->count = 0;
		data->body = 0;

		चयन (rc6_mode(data)) अणु
		हाल RC6_MODE_0:
			data->wanted_bits = RC6_0_NBITS;
			अवरोध;
		हाल RC6_MODE_6A:
			data->wanted_bits = RC6_6A_NBITS;
			अवरोध;
		शेष:
			dev_dbg(&dev->dev, "RC6 unknown mode\n");
			जाओ out;
		पूर्ण
		जाओ again;

	हाल STATE_BODY_BIT_START:
		अगर (eq_margin(ev.duration, RC6_BIT_START, RC6_UNIT / 2)) अणु
			/* Discard LSB's that won't fit in data->body */
			अगर (data->count++ < अक्षर_बिट * माप data->body) अणु
				data->body <<= 1;
				अगर (ev.pulse)
					data->body |= 1;
			पूर्ण
			data->state = STATE_BODY_BIT_END;
			वापस 0;
		पूर्ण अन्यथा अगर (RC6_MODE_6A == rc6_mode(data) && !ev.pulse &&
				geq_margin(ev.duration, RC6_SUFFIX_SPACE, RC6_UNIT / 2)) अणु
			data->state = STATE_FINISHED;
			जाओ again;
		पूर्ण
		अवरोध;

	हाल STATE_BODY_BIT_END:
		अगर (data->count == data->wanted_bits)
			data->state = STATE_FINISHED;
		अन्यथा
			data->state = STATE_BODY_BIT_START;

		decrease_duration(&ev, RC6_BIT_END);
		जाओ again;

	हाल STATE_FINISHED:
		अगर (ev.pulse)
			अवरोध;

		चयन (rc6_mode(data)) अणु
		हाल RC6_MODE_0:
			scancode = data->body;
			toggle = data->toggle;
			protocol = RC_PROTO_RC6_0;
			dev_dbg(&dev->dev, "RC6(0) scancode 0x%04x (toggle: %u)\n",
				scancode, toggle);
			अवरोध;

		हाल RC6_MODE_6A:
			अगर (data->count > अक्षर_बिट * माप data->body) अणु
				dev_dbg(&dev->dev, "RC6 too many (%u) data bits\n",
					data->count);
				जाओ out;
			पूर्ण

			scancode = data->body;
			चयन (data->count) अणु
			हाल 20:
				protocol = RC_PROTO_RC6_6A_20;
				toggle = 0;
				अवरोध;
			हाल 24:
				protocol = RC_PROTO_RC6_6A_24;
				toggle = 0;
				अवरोध;
			हाल 32:
				चयन (scancode & RC6_6A_LCC_MASK) अणु
				हाल RC6_6A_MCE_CC:
				हाल RC6_6A_KATHREIN_CC:
				हाल RC6_6A_ZOTAC_CC:
					protocol = RC_PROTO_RC6_MCE;
					toggle = !!(scancode & RC6_6A_MCE_TOGGLE_MASK);
					scancode &= ~RC6_6A_MCE_TOGGLE_MASK;
					अवरोध;
				शेष:
					protocol = RC_PROTO_RC6_6A_32;
					toggle = 0;
					अवरोध;
				पूर्ण
				अवरोध;
			शेष:
				dev_dbg(&dev->dev, "RC6(6A) unsupported length\n");
				जाओ out;
			पूर्ण

			dev_dbg(&dev->dev, "RC6(6A) proto 0x%04x, scancode 0x%08x (toggle: %u)\n",
				protocol, scancode, toggle);
			अवरोध;
		शेष:
			dev_dbg(&dev->dev, "RC6 unknown mode\n");
			जाओ out;
		पूर्ण

		rc_keyकरोwn(dev, protocol, scancode, toggle);
		data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

out:
	dev_dbg(&dev->dev, "RC6 decode failed at state %i (%uus %s)\n",
		data->state, ev.duration, TO_STR(ev.pulse));
	data->state = STATE_INACTIVE;
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा ir_raw_timings_manchester ir_rc6_timings[4] = अणु
	अणु
		.leader_pulse		= RC6_PREFIX_PULSE,
		.leader_space		= RC6_PREFIX_SPACE,
		.घड़ी			= RC6_UNIT,
		.invert			= 1,
	पूर्ण,
	अणु
		.घड़ी			= RC6_UNIT * 2,
		.invert			= 1,
	पूर्ण,
	अणु
		.घड़ी			= RC6_UNIT,
		.invert			= 1,
		.trailer_space		= RC6_SUFFIX_SPACE,
	पूर्ण,
पूर्ण;

/**
 * ir_rc6_encode() - Encode a scancode as a stream of raw events
 *
 * @protocol:	protocol to encode
 * @scancode:	scancode to encode
 * @events:	array of raw ir events to ग_लिखो पूर्णांकo
 * @max:	maximum size of @events
 *
 * Returns:	The number of events written.
 *		-ENOBUFS अगर there isn't enough space in the array to fit the
 *		encoding. In this हाल all @max events will have been written.
 *		-EINVAL अगर the scancode is ambiguous or invalid.
 */
अटल पूर्णांक ir_rc6_encode(क्रमागत rc_proto protocol, u32 scancode,
			 काष्ठा ir_raw_event *events, अचिन्हित पूर्णांक max)
अणु
	पूर्णांक ret;
	काष्ठा ir_raw_event *e = events;

	अगर (protocol == RC_PROTO_RC6_0) अणु
		/* Modulate the header (Start Bit & Mode-0) */
		ret = ir_raw_gen_manchester(&e, max - (e - events),
					    &ir_rc6_timings[0],
					    RC6_HEADER_NBITS, (1 << 3));
		अगर (ret < 0)
			वापस ret;

		/* Modulate Trailer Bit */
		ret = ir_raw_gen_manchester(&e, max - (e - events),
					    &ir_rc6_timings[1], 1, 0);
		अगर (ret < 0)
			वापस ret;

		/* Modulate rest of the data */
		ret = ir_raw_gen_manchester(&e, max - (e - events),
					    &ir_rc6_timings[2], RC6_0_NBITS,
					    scancode);
		अगर (ret < 0)
			वापस ret;

	पूर्ण अन्यथा अणु
		पूर्णांक bits;

		चयन (protocol) अणु
		हाल RC_PROTO_RC6_MCE:
		हाल RC_PROTO_RC6_6A_32:
			bits = 32;
			अवरोध;
		हाल RC_PROTO_RC6_6A_24:
			bits = 24;
			अवरोध;
		हाल RC_PROTO_RC6_6A_20:
			bits = 20;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		/* Modulate the header (Start Bit & Header-version 6 */
		ret = ir_raw_gen_manchester(&e, max - (e - events),
					    &ir_rc6_timings[0],
					    RC6_HEADER_NBITS, (1 << 3 | 6));
		अगर (ret < 0)
			वापस ret;

		/* Modulate Trailer Bit */
		ret = ir_raw_gen_manchester(&e, max - (e - events),
					    &ir_rc6_timings[1], 1, 0);
		अगर (ret < 0)
			वापस ret;

		/* Modulate rest of the data */
		ret = ir_raw_gen_manchester(&e, max - (e - events),
					    &ir_rc6_timings[2],
					    bits,
					    scancode);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस e - events;
पूर्ण

अटल काष्ठा ir_raw_handler rc6_handler = अणु
	.protocols	= RC_PROTO_BIT_RC6_0 | RC_PROTO_BIT_RC6_6A_20 |
			  RC_PROTO_BIT_RC6_6A_24 | RC_PROTO_BIT_RC6_6A_32 |
			  RC_PROTO_BIT_RC6_MCE,
	.decode		= ir_rc6_decode,
	.encode		= ir_rc6_encode,
	.carrier	= 36000,
	.min_समयout	= RC6_SUFFIX_SPACE,
पूर्ण;

अटल पूर्णांक __init ir_rc6_decode_init(व्योम)
अणु
	ir_raw_handler_रेजिस्टर(&rc6_handler);

	prपूर्णांकk(KERN_INFO "IR RC6 protocol handler initialized\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास ir_rc6_decode_निकास(व्योम)
अणु
	ir_raw_handler_unरेजिस्टर(&rc6_handler);
पूर्ण

module_init(ir_rc6_decode_init);
module_निकास(ir_rc6_decode_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Hथअrdeman <david@hardeman.nu>");
MODULE_DESCRIPTION("RC6 IR protocol decoder");
