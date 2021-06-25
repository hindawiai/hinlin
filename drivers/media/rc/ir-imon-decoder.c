<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// ir-imon-decoder.c - handle iMon protocol
//
// Copyright (C) 2018 by Sean Young <sean@mess.org>

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश "rc-core-priv.h"

#घोषणा IMON_UNIT		416 /* us */
#घोषणा IMON_BITS		30
#घोषणा IMON_CHKBITS		(BIT(30) | BIT(25) | BIT(24) | BIT(22) | \
				 BIT(21) | BIT(20) | BIT(19) | BIT(18) | \
				 BIT(17) | BIT(16) | BIT(14) | BIT(13) | \
				 BIT(12) | BIT(11) | BIT(10) | BIT(9))

/*
 * This protocol has 30 bits. The क्रमmat is one IMON_UNIT header pulse,
 * followed by 30 bits. Each bit is one IMON_UNIT check field, and then
 * one IMON_UNIT field with the actual bit (1=space, 0=pulse).
 * The check field is always space क्रम some bits, क्रम others it is pulse अगर
 * both the preceding and current bit are zero, अन्यथा space. IMON_CHKBITS
 * defines which bits are of type check.
 *
 * There is no way to distinguish an incomplete message from one where
 * the lower bits are all set, iow. the last pulse is क्रम the lowest
 * bit which is 0.
 */
क्रमागत imon_state अणु
	STATE_INACTIVE,
	STATE_BIT_CHK,
	STATE_BIT_START,
	STATE_FINISHED,
	STATE_ERROR,
पूर्ण;

अटल व्योम ir_imon_decode_scancode(काष्ठा rc_dev *dev)
अणु
	काष्ठा imon_dec *imon = &dev->raw->imon;

	/* Keyboard/Mouse toggle */
	अगर (imon->bits == 0x299115b7)
		imon->stick_keyboard = !imon->stick_keyboard;

	अगर ((imon->bits & 0xfc0000ff) == 0x680000b7) अणु
		पूर्णांक rel_x, rel_y;
		u8 buf;

		buf = imon->bits >> 16;
		rel_x = (buf & 0x08) | (buf & 0x10) >> 2 |
			(buf & 0x20) >> 4 | (buf & 0x40) >> 6;
		अगर (imon->bits & 0x02000000)
			rel_x |= ~0x0f;
		buf = imon->bits >> 8;
		rel_y = (buf & 0x08) | (buf & 0x10) >> 2 |
			(buf & 0x20) >> 4 | (buf & 0x40) >> 6;
		अगर (imon->bits & 0x01000000)
			rel_y |= ~0x0f;

		अगर (rel_x && rel_y && imon->stick_keyboard) अणु
			अगर (असल(rel_y) > असल(rel_x))
				imon->bits = rel_y > 0 ?
					0x289515b7 : /* KEY_DOWN */
					0x2aa515b7;  /* KEY_UP */
			अन्यथा
				imon->bits = rel_x > 0 ?
					0x2ba515b7 : /* KEY_RIGHT */
					0x29a515b7;  /* KEY_LEFT */
		पूर्ण

		अगर (!imon->stick_keyboard) अणु
			input_report_rel(dev->input_dev, REL_X, rel_x);
			input_report_rel(dev->input_dev, REL_Y, rel_y);

			input_report_key(dev->input_dev, BTN_LEFT,
					 (imon->bits & 0x00010000) != 0);
			input_report_key(dev->input_dev, BTN_RIGHT,
					 (imon->bits & 0x00040000) != 0);
		पूर्ण
	पूर्ण

	rc_keyकरोwn(dev, RC_PROTO_IMON, imon->bits, 0);
पूर्ण

/**
 * ir_imon_decode() - Decode one iMON pulse or space
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @ev:		the काष्ठा ir_raw_event descriptor of the pulse/space
 *
 * This function वापसs -EINVAL अगर the pulse violates the state machine
 */
अटल पूर्णांक ir_imon_decode(काष्ठा rc_dev *dev, काष्ठा ir_raw_event ev)
अणु
	काष्ठा imon_dec *data = &dev->raw->imon;

	अगर (!is_timing_event(ev)) अणु
		अगर (ev.reset)
			data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

	dev_dbg(&dev->dev,
		"iMON decode started at state %d bitno %d (%uus %s)\n",
		data->state, data->count, ev.duration, TO_STR(ev.pulse));

	/*
	 * Since iMON protocol is a series of bits, अगर at any poपूर्णांक
	 * we encounter an error, make sure that any reमुख्यing bits
	 * aren't parsed as a scancode made up of less bits.
	 *
	 * Note that अगर the stick is held, then the remote repeats
	 * the scancode with about 12ms between them. So, make sure
	 * we have at least 10ms of space after an error. That way,
	 * we're at a new scancode.
	 */
	अगर (data->state == STATE_ERROR) अणु
		अगर (!ev.pulse && ev.duration > MS_TO_US(10))
			data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

	क्रम (;;) अणु
		अगर (!geq_margin(ev.duration, IMON_UNIT, IMON_UNIT / 2))
			वापस 0;

		decrease_duration(&ev, IMON_UNIT);

		चयन (data->state) अणु
		हाल STATE_INACTIVE:
			अगर (ev.pulse) अणु
				data->state = STATE_BIT_CHK;
				data->bits = 0;
				data->count = IMON_BITS;
			पूर्ण
			अवरोध;
		हाल STATE_BIT_CHK:
			अगर (IMON_CHKBITS & BIT(data->count))
				data->last_chk = ev.pulse;
			अन्यथा अगर (ev.pulse)
				जाओ err_out;
			data->state = STATE_BIT_START;
			अवरोध;
		हाल STATE_BIT_START:
			data->bits <<= 1;
			अगर (!ev.pulse)
				data->bits |= 1;

			अगर (IMON_CHKBITS & BIT(data->count)) अणु
				अगर (data->last_chk != !(data->bits & 3))
					जाओ err_out;
			पूर्ण

			अगर (!data->count--)
				data->state = STATE_FINISHED;
			अन्यथा
				data->state = STATE_BIT_CHK;
			अवरोध;
		हाल STATE_FINISHED:
			अगर (ev.pulse)
				जाओ err_out;
			ir_imon_decode_scancode(dev);
			data->state = STATE_INACTIVE;
			अवरोध;
		पूर्ण
	पूर्ण

err_out:
	dev_dbg(&dev->dev,
		"iMON decode failed at state %d bitno %d (%uus %s)\n",
		data->state, data->count, ev.duration, TO_STR(ev.pulse));

	data->state = STATE_ERROR;

	वापस -EINVAL;
पूर्ण

/**
 * ir_imon_encode() - Encode a scancode as a stream of raw events
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
अटल पूर्णांक ir_imon_encode(क्रमागत rc_proto protocol, u32 scancode,
			  काष्ठा ir_raw_event *events, अचिन्हित पूर्णांक max)
अणु
	काष्ठा ir_raw_event *e = events;
	पूर्णांक i, pulse;

	अगर (!max--)
		वापस -ENOBUFS;
	init_ir_raw_event_duration(e, 1, IMON_UNIT);

	क्रम (i = IMON_BITS; i >= 0; i--) अणु
		अगर (BIT(i) & IMON_CHKBITS)
			pulse = !(scancode & (BIT(i) | BIT(i + 1)));
		अन्यथा
			pulse = 0;

		अगर (pulse == e->pulse) अणु
			e->duration += IMON_UNIT;
		पूर्ण अन्यथा अणु
			अगर (!max--)
				वापस -ENOBUFS;
			init_ir_raw_event_duration(++e, pulse, IMON_UNIT);
		पूर्ण

		pulse = !(scancode & BIT(i));

		अगर (pulse == e->pulse) अणु
			e->duration += IMON_UNIT;
		पूर्ण अन्यथा अणु
			अगर (!max--)
				वापस -ENOBUFS;
			init_ir_raw_event_duration(++e, pulse, IMON_UNIT);
		पूर्ण
	पूर्ण

	अगर (e->pulse)
		e++;

	वापस e - events;
पूर्ण

अटल पूर्णांक ir_imon_रेजिस्टर(काष्ठा rc_dev *dev)
अणु
	काष्ठा imon_dec *imon = &dev->raw->imon;

	imon->stick_keyboard = false;

	वापस 0;
पूर्ण

अटल काष्ठा ir_raw_handler imon_handler = अणु
	.protocols	= RC_PROTO_BIT_IMON,
	.decode		= ir_imon_decode,
	.encode		= ir_imon_encode,
	.carrier	= 38000,
	.raw_रेजिस्टर	= ir_imon_रेजिस्टर,
	.min_समयout	= IMON_UNIT * IMON_BITS * 2,
पूर्ण;

अटल पूर्णांक __init ir_imon_decode_init(व्योम)
अणु
	ir_raw_handler_रेजिस्टर(&imon_handler);

	pr_info("IR iMON protocol handler initialized\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास ir_imon_decode_निकास(व्योम)
अणु
	ir_raw_handler_unरेजिस्टर(&imon_handler);
पूर्ण

module_init(ir_imon_decode_init);
module_निकास(ir_imon_decode_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sean Young <sean@mess.org>");
MODULE_DESCRIPTION("iMON IR protocol decoder");
