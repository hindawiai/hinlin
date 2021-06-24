<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ir-sony-decoder.c - handle Sony IR Pulse/Space protocol
 *
 * Copyright (C) 2010 by David Hथअrdeman <david@hardeman.nu>
 */

#समावेश <linux/bitrev.h>
#समावेश <linux/module.h>
#समावेश "rc-core-priv.h"

#घोषणा SONY_UNIT		600 /* us */
#घोषणा SONY_HEADER_PULSE	(4 * SONY_UNIT)
#घोषणा	SONY_HEADER_SPACE	(1 * SONY_UNIT)
#घोषणा SONY_BIT_0_PULSE	(1 * SONY_UNIT)
#घोषणा SONY_BIT_1_PULSE	(2 * SONY_UNIT)
#घोषणा SONY_BIT_SPACE		(1 * SONY_UNIT)
#घोषणा SONY_TRAILER_SPACE	(10 * SONY_UNIT) /* minimum */

क्रमागत sony_state अणु
	STATE_INACTIVE,
	STATE_HEADER_SPACE,
	STATE_BIT_PULSE,
	STATE_BIT_SPACE,
	STATE_FINISHED,
पूर्ण;

/**
 * ir_sony_decode() - Decode one Sony pulse or space
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @ev:         the काष्ठा ir_raw_event descriptor of the pulse/space
 *
 * This function वापसs -EINVAL अगर the pulse violates the state machine
 */
अटल पूर्णांक ir_sony_decode(काष्ठा rc_dev *dev, काष्ठा ir_raw_event ev)
अणु
	काष्ठा sony_dec *data = &dev->raw->sony;
	क्रमागत rc_proto protocol;
	u32 scancode;
	u8 device, subdevice, function;

	अगर (!is_timing_event(ev)) अणु
		अगर (ev.reset)
			data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

	अगर (!geq_margin(ev.duration, SONY_UNIT, SONY_UNIT / 2))
		जाओ out;

	dev_dbg(&dev->dev, "Sony decode started at state %d (%uus %s)\n",
		data->state, ev.duration, TO_STR(ev.pulse));

	चयन (data->state) अणु

	हाल STATE_INACTIVE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, SONY_HEADER_PULSE, SONY_UNIT / 2))
			अवरोध;

		data->count = 0;
		data->state = STATE_HEADER_SPACE;
		वापस 0;

	हाल STATE_HEADER_SPACE:
		अगर (ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, SONY_HEADER_SPACE, SONY_UNIT / 2))
			अवरोध;

		data->state = STATE_BIT_PULSE;
		वापस 0;

	हाल STATE_BIT_PULSE:
		अगर (!ev.pulse)
			अवरोध;

		data->bits <<= 1;
		अगर (eq_margin(ev.duration, SONY_BIT_1_PULSE, SONY_UNIT / 2))
			data->bits |= 1;
		अन्यथा अगर (!eq_margin(ev.duration, SONY_BIT_0_PULSE, SONY_UNIT / 2))
			अवरोध;

		data->count++;
		data->state = STATE_BIT_SPACE;
		वापस 0;

	हाल STATE_BIT_SPACE:
		अगर (ev.pulse)
			अवरोध;

		अगर (!geq_margin(ev.duration, SONY_BIT_SPACE, SONY_UNIT / 2))
			अवरोध;

		decrease_duration(&ev, SONY_BIT_SPACE);

		अगर (!geq_margin(ev.duration, SONY_UNIT, SONY_UNIT / 2)) अणु
			data->state = STATE_BIT_PULSE;
			वापस 0;
		पूर्ण

		data->state = STATE_FINISHED;
		fallthrough;

	हाल STATE_FINISHED:
		अगर (ev.pulse)
			अवरोध;

		अगर (!geq_margin(ev.duration, SONY_TRAILER_SPACE, SONY_UNIT / 2))
			अवरोध;

		चयन (data->count) अणु
		हाल 12:
			अगर (!(dev->enabled_protocols & RC_PROTO_BIT_SONY12))
				जाओ finish_state_machine;

			device    = bitrev8((data->bits <<  3) & 0xF8);
			subdevice = 0;
			function  = bitrev8((data->bits >>  4) & 0xFE);
			protocol = RC_PROTO_SONY12;
			अवरोध;
		हाल 15:
			अगर (!(dev->enabled_protocols & RC_PROTO_BIT_SONY15))
				जाओ finish_state_machine;

			device    = bitrev8((data->bits >>  0) & 0xFF);
			subdevice = 0;
			function  = bitrev8((data->bits >>  7) & 0xFE);
			protocol = RC_PROTO_SONY15;
			अवरोध;
		हाल 20:
			अगर (!(dev->enabled_protocols & RC_PROTO_BIT_SONY20))
				जाओ finish_state_machine;

			device    = bitrev8((data->bits >>  5) & 0xF8);
			subdevice = bitrev8((data->bits >>  0) & 0xFF);
			function  = bitrev8((data->bits >> 12) & 0xFE);
			protocol = RC_PROTO_SONY20;
			अवरोध;
		शेष:
			dev_dbg(&dev->dev, "Sony invalid bitcount %u\n",
				data->count);
			जाओ out;
		पूर्ण

		scancode = device << 16 | subdevice << 8 | function;
		dev_dbg(&dev->dev, "Sony(%u) scancode 0x%05x\n", data->count,
			scancode);
		rc_keyकरोwn(dev, protocol, scancode, 0);
		जाओ finish_state_machine;
	पूर्ण

out:
	dev_dbg(&dev->dev, "Sony decode failed at state %d (%uus %s)\n",
		data->state, ev.duration, TO_STR(ev.pulse));
	data->state = STATE_INACTIVE;
	वापस -EINVAL;

finish_state_machine:
	data->state = STATE_INACTIVE;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ir_raw_timings_pl ir_sony_timings = अणु
	.header_pulse  = SONY_HEADER_PULSE,
	.bit_space     = SONY_BIT_SPACE,
	.bit_pulse[0]  = SONY_BIT_0_PULSE,
	.bit_pulse[1]  = SONY_BIT_1_PULSE,
	.trailer_space = SONY_TRAILER_SPACE + SONY_BIT_SPACE,
	.msb_first     = 0,
पूर्ण;

/**
 * ir_sony_encode() - Encode a scancode as a stream of raw events
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
अटल पूर्णांक ir_sony_encode(क्रमागत rc_proto protocol, u32 scancode,
			  काष्ठा ir_raw_event *events, अचिन्हित पूर्णांक max)
अणु
	काष्ठा ir_raw_event *e = events;
	u32 raw, len;
	पूर्णांक ret;

	अगर (protocol == RC_PROTO_SONY12) अणु
		raw = (scancode & 0x7f) | ((scancode & 0x1f0000) >> 9);
		len = 12;
	पूर्ण अन्यथा अगर (protocol == RC_PROTO_SONY15) अणु
		raw = (scancode & 0x7f) | ((scancode & 0xff0000) >> 9);
		len = 15;
	पूर्ण अन्यथा अणु
		raw = (scancode & 0x7f) | ((scancode & 0x1f0000) >> 9) |
		       ((scancode & 0xff00) << 4);
		len = 20;
	पूर्ण

	ret = ir_raw_gen_pl(&e, max, &ir_sony_timings, len, raw);
	अगर (ret < 0)
		वापस ret;

	वापस e - events;
पूर्ण

अटल काष्ठा ir_raw_handler sony_handler = अणु
	.protocols	= RC_PROTO_BIT_SONY12 | RC_PROTO_BIT_SONY15 |
							RC_PROTO_BIT_SONY20,
	.decode		= ir_sony_decode,
	.encode		= ir_sony_encode,
	.carrier	= 40000,
	.min_समयout	= SONY_TRAILER_SPACE,
पूर्ण;

अटल पूर्णांक __init ir_sony_decode_init(व्योम)
अणु
	ir_raw_handler_रेजिस्टर(&sony_handler);

	prपूर्णांकk(KERN_INFO "IR Sony protocol handler initialized\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास ir_sony_decode_निकास(व्योम)
अणु
	ir_raw_handler_unरेजिस्टर(&sony_handler);
पूर्ण

module_init(ir_sony_decode_init);
module_निकास(ir_sony_decode_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Hथअrdeman <david@hardeman.nu>");
MODULE_DESCRIPTION("Sony IR protocol decoder");
