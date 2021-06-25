<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// ir-nec-decoder.c - handle NEC IR Pulse/Space protocol
//
// Copyright (C) 2010 by Mauro Carvalho Chehab

#समावेश <linux/bitrev.h>
#समावेश <linux/module.h>
#समावेश "rc-core-priv.h"

#घोषणा NEC_NBITS		32
#घोषणा NEC_UNIT		563  /* us */
#घोषणा NEC_HEADER_PULSE	(16 * NEC_UNIT)
#घोषणा NECX_HEADER_PULSE	(8  * NEC_UNIT) /* Less common NEC variant */
#घोषणा NEC_HEADER_SPACE	(8  * NEC_UNIT)
#घोषणा NEC_REPEAT_SPACE	(4  * NEC_UNIT)
#घोषणा NEC_BIT_PULSE		(1  * NEC_UNIT)
#घोषणा NEC_BIT_0_SPACE		(1  * NEC_UNIT)
#घोषणा NEC_BIT_1_SPACE		(3  * NEC_UNIT)
#घोषणा	NEC_TRAILER_PULSE	(1  * NEC_UNIT)
#घोषणा	NEC_TRAILER_SPACE	(10 * NEC_UNIT) /* even दीर्घer in reality */
#घोषणा NECX_REPEAT_BITS	1

क्रमागत nec_state अणु
	STATE_INACTIVE,
	STATE_HEADER_SPACE,
	STATE_BIT_PULSE,
	STATE_BIT_SPACE,
	STATE_TRAILER_PULSE,
	STATE_TRAILER_SPACE,
पूर्ण;

/**
 * ir_nec_decode() - Decode one NEC pulse or space
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @ev:		the काष्ठा ir_raw_event descriptor of the pulse/space
 *
 * This function वापसs -EINVAL अगर the pulse violates the state machine
 */
अटल पूर्णांक ir_nec_decode(काष्ठा rc_dev *dev, काष्ठा ir_raw_event ev)
अणु
	काष्ठा nec_dec *data = &dev->raw->nec;
	u32 scancode;
	क्रमागत rc_proto rc_proto;
	u8 address, not_address, command, not_command;

	अगर (!is_timing_event(ev)) अणु
		अगर (ev.reset)
			data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

	dev_dbg(&dev->dev, "NEC decode started at state %d (%uus %s)\n",
		data->state, ev.duration, TO_STR(ev.pulse));

	चयन (data->state) अणु

	हाल STATE_INACTIVE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (eq_margin(ev.duration, NEC_HEADER_PULSE, NEC_UNIT * 2)) अणु
			data->is_nec_x = false;
			data->necx_repeat = false;
		पूर्ण अन्यथा अगर (eq_margin(ev.duration, NECX_HEADER_PULSE, NEC_UNIT / 2))
			data->is_nec_x = true;
		अन्यथा
			अवरोध;

		data->count = 0;
		data->state = STATE_HEADER_SPACE;
		वापस 0;

	हाल STATE_HEADER_SPACE:
		अगर (ev.pulse)
			अवरोध;

		अगर (eq_margin(ev.duration, NEC_HEADER_SPACE, NEC_UNIT)) अणु
			data->state = STATE_BIT_PULSE;
			वापस 0;
		पूर्ण अन्यथा अगर (eq_margin(ev.duration, NEC_REPEAT_SPACE, NEC_UNIT / 2)) अणु
			data->state = STATE_TRAILER_PULSE;
			वापस 0;
		पूर्ण

		अवरोध;

	हाल STATE_BIT_PULSE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, NEC_BIT_PULSE, NEC_UNIT / 2))
			अवरोध;

		data->state = STATE_BIT_SPACE;
		वापस 0;

	हाल STATE_BIT_SPACE:
		अगर (ev.pulse)
			अवरोध;

		अगर (data->necx_repeat && data->count == NECX_REPEAT_BITS &&
		    geq_margin(ev.duration, NEC_TRAILER_SPACE, NEC_UNIT / 2)) अणु
			dev_dbg(&dev->dev, "Repeat last key\n");
			rc_repeat(dev);
			data->state = STATE_INACTIVE;
			वापस 0;
		पूर्ण अन्यथा अगर (data->count > NECX_REPEAT_BITS)
			data->necx_repeat = false;

		data->bits <<= 1;
		अगर (eq_margin(ev.duration, NEC_BIT_1_SPACE, NEC_UNIT / 2))
			data->bits |= 1;
		अन्यथा अगर (!eq_margin(ev.duration, NEC_BIT_0_SPACE, NEC_UNIT / 2))
			अवरोध;
		data->count++;

		अगर (data->count == NEC_NBITS)
			data->state = STATE_TRAILER_PULSE;
		अन्यथा
			data->state = STATE_BIT_PULSE;

		वापस 0;

	हाल STATE_TRAILER_PULSE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, NEC_TRAILER_PULSE, NEC_UNIT / 2))
			अवरोध;

		data->state = STATE_TRAILER_SPACE;
		वापस 0;

	हाल STATE_TRAILER_SPACE:
		अगर (ev.pulse)
			अवरोध;

		अगर (!geq_margin(ev.duration, NEC_TRAILER_SPACE, NEC_UNIT / 2))
			अवरोध;

		अगर (data->count == NEC_NBITS) अणु
			address     = bitrev8((data->bits >> 24) & 0xff);
			not_address = bitrev8((data->bits >> 16) & 0xff);
			command	    = bitrev8((data->bits >>  8) & 0xff);
			not_command = bitrev8((data->bits >>  0) & 0xff);

			scancode = ir_nec_bytes_to_scancode(address,
							    not_address,
							    command,
							    not_command,
							    &rc_proto);

			अगर (data->is_nec_x)
				data->necx_repeat = true;

			rc_keyकरोwn(dev, rc_proto, scancode, 0);
		पूर्ण अन्यथा अणु
			rc_repeat(dev);
		पूर्ण

		data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

	dev_dbg(&dev->dev, "NEC decode failed at count %d state %d (%uus %s)\n",
		data->count, data->state, ev.duration, TO_STR(ev.pulse));
	data->state = STATE_INACTIVE;
	वापस -EINVAL;
पूर्ण

/**
 * ir_nec_scancode_to_raw() - encode an NEC scancode पढ़ोy क्रम modulation.
 * @protocol:	specअगरic protocol to use
 * @scancode:	a single NEC scancode.
 */
अटल u32 ir_nec_scancode_to_raw(क्रमागत rc_proto protocol, u32 scancode)
अणु
	अचिन्हित पूर्णांक addr, addr_inv, data, data_inv;

	data = scancode & 0xff;

	अगर (protocol == RC_PROTO_NEC32) अणु
		/* 32-bit NEC (used by Apple and TiVo remotes) */
		/* scan encoding: aaAAddDD */
		addr_inv   = (scancode >> 24) & 0xff;
		addr       = (scancode >> 16) & 0xff;
		data_inv   = (scancode >>  8) & 0xff;
	पूर्ण अन्यथा अगर (protocol == RC_PROTO_NECX) अणु
		/* Extended NEC */
		/* scan encoding AAaaDD */
		addr       = (scancode >> 16) & 0xff;
		addr_inv   = (scancode >>  8) & 0xff;
		data_inv   = data ^ 0xff;
	पूर्ण अन्यथा अणु
		/* Normal NEC */
		/* scan encoding: AADD */
		addr       = (scancode >>  8) & 0xff;
		addr_inv   = addr ^ 0xff;
		data_inv   = data ^ 0xff;
	पूर्ण

	/* raw encoding: ddDDaaAA */
	वापस data_inv << 24 |
	       data     << 16 |
	       addr_inv <<  8 |
	       addr;
पूर्ण

अटल स्थिर काष्ठा ir_raw_timings_pd ir_nec_timings = अणु
	.header_pulse	= NEC_HEADER_PULSE,
	.header_space	= NEC_HEADER_SPACE,
	.bit_pulse	= NEC_BIT_PULSE,
	.bit_space[0]	= NEC_BIT_0_SPACE,
	.bit_space[1]	= NEC_BIT_1_SPACE,
	.trailer_pulse	= NEC_TRAILER_PULSE,
	.trailer_space	= NEC_TRAILER_SPACE,
	.msb_first	= 0,
पूर्ण;

/**
 * ir_nec_encode() - Encode a scancode as a stream of raw events
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
अटल पूर्णांक ir_nec_encode(क्रमागत rc_proto protocol, u32 scancode,
			 काष्ठा ir_raw_event *events, अचिन्हित पूर्णांक max)
अणु
	काष्ठा ir_raw_event *e = events;
	पूर्णांक ret;
	u32 raw;

	/* Convert a NEC scancode to raw NEC data */
	raw = ir_nec_scancode_to_raw(protocol, scancode);

	/* Modulate the raw data using a pulse distance modulation */
	ret = ir_raw_gen_pd(&e, max, &ir_nec_timings, NEC_NBITS, raw);
	अगर (ret < 0)
		वापस ret;

	वापस e - events;
पूर्ण

अटल काष्ठा ir_raw_handler nec_handler = अणु
	.protocols	= RC_PROTO_BIT_NEC | RC_PROTO_BIT_NECX |
							RC_PROTO_BIT_NEC32,
	.decode		= ir_nec_decode,
	.encode		= ir_nec_encode,
	.carrier	= 38000,
	.min_समयout	= NEC_TRAILER_SPACE,
पूर्ण;

अटल पूर्णांक __init ir_nec_decode_init(व्योम)
अणु
	ir_raw_handler_रेजिस्टर(&nec_handler);

	prपूर्णांकk(KERN_INFO "IR NEC protocol handler initialized\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास ir_nec_decode_निकास(व्योम)
अणु
	ir_raw_handler_unरेजिस्टर(&nec_handler);
पूर्ण

module_init(ir_nec_decode_init);
module_निकास(ir_nec_decode_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_AUTHOR("Red Hat Inc. (http://www.redhat.com)");
MODULE_DESCRIPTION("NEC IR protocol decoder");
