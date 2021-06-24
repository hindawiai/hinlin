<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// ir-rc5-decoder.c - decoder क्रम RC5(x) and StreamZap protocols
//
// Copyright (C) 2010 by Mauro Carvalho Chehab
// Copyright (C) 2010 by Jarod Wilson <jarod@redhat.com>

/*
 * This decoder handles the 14 bit RC5 protocol, 15 bit "StreamZap" protocol
 * and 20 bit RC5x protocol.
 */

#समावेश "rc-core-priv.h"
#समावेश <linux/module.h>

#घोषणा RC5_NBITS		14
#घोषणा RC5_SZ_NBITS		15
#घोषणा RC5X_NBITS		20
#घोषणा CHECK_RC5X_NBITS	8
#घोषणा RC5_UNIT		889 /* us */
#घोषणा RC5_BIT_START		(1 * RC5_UNIT)
#घोषणा RC5_BIT_END		(1 * RC5_UNIT)
#घोषणा RC5X_SPACE		(4 * RC5_UNIT)
#घोषणा RC5_TRAILER		(6 * RC5_UNIT) /* In reality, approx 100 */

क्रमागत rc5_state अणु
	STATE_INACTIVE,
	STATE_BIT_START,
	STATE_BIT_END,
	STATE_CHECK_RC5X,
	STATE_FINISHED,
पूर्ण;

/**
 * ir_rc5_decode() - Decode one RC-5 pulse or space
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @ev:		the काष्ठा ir_raw_event descriptor of the pulse/space
 *
 * This function वापसs -EINVAL अगर the pulse violates the state machine
 */
अटल पूर्णांक ir_rc5_decode(काष्ठा rc_dev *dev, काष्ठा ir_raw_event ev)
अणु
	काष्ठा rc5_dec *data = &dev->raw->rc5;
	u8 toggle;
	u32 scancode;
	क्रमागत rc_proto protocol;

	अगर (!is_timing_event(ev)) अणु
		अगर (ev.reset)
			data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

	अगर (!geq_margin(ev.duration, RC5_UNIT, RC5_UNIT / 2))
		जाओ out;

again:
	dev_dbg(&dev->dev, "RC5(x/sz) decode started at state %i (%uus %s)\n",
		data->state, ev.duration, TO_STR(ev.pulse));

	अगर (!geq_margin(ev.duration, RC5_UNIT, RC5_UNIT / 2))
		वापस 0;

	चयन (data->state) अणु

	हाल STATE_INACTIVE:
		अगर (!ev.pulse)
			अवरोध;

		data->state = STATE_BIT_START;
		data->count = 1;
		decrease_duration(&ev, RC5_BIT_START);
		जाओ again;

	हाल STATE_BIT_START:
		अगर (!ev.pulse && geq_margin(ev.duration, RC5_TRAILER, RC5_UNIT / 2)) अणु
			data->state = STATE_FINISHED;
			जाओ again;
		पूर्ण

		अगर (!eq_margin(ev.duration, RC5_BIT_START, RC5_UNIT / 2))
			अवरोध;

		data->bits <<= 1;
		अगर (!ev.pulse)
			data->bits |= 1;
		data->count++;
		data->state = STATE_BIT_END;
		वापस 0;

	हाल STATE_BIT_END:
		अगर (data->count == CHECK_RC5X_NBITS)
			data->state = STATE_CHECK_RC5X;
		अन्यथा
			data->state = STATE_BIT_START;

		decrease_duration(&ev, RC5_BIT_END);
		जाओ again;

	हाल STATE_CHECK_RC5X:
		अगर (!ev.pulse && geq_margin(ev.duration, RC5X_SPACE, RC5_UNIT / 2)) अणु
			data->is_rc5x = true;
			decrease_duration(&ev, RC5X_SPACE);
		पूर्ण अन्यथा
			data->is_rc5x = false;
		data->state = STATE_BIT_START;
		जाओ again;

	हाल STATE_FINISHED:
		अगर (ev.pulse)
			अवरोध;

		अगर (data->is_rc5x && data->count == RC5X_NBITS) अणु
			/* RC5X */
			u8 xdata, command, प्रणाली;
			अगर (!(dev->enabled_protocols & RC_PROTO_BIT_RC5X_20)) अणु
				data->state = STATE_INACTIVE;
				वापस 0;
			पूर्ण
			xdata    = (data->bits & 0x0003F) >> 0;
			command  = (data->bits & 0x00FC0) >> 6;
			प्रणाली   = (data->bits & 0x1F000) >> 12;
			toggle   = (data->bits & 0x20000) ? 1 : 0;
			command += (data->bits & 0x40000) ? 0 : 0x40;
			scancode = प्रणाली << 16 | command << 8 | xdata;
			protocol = RC_PROTO_RC5X_20;

		पूर्ण अन्यथा अगर (!data->is_rc5x && data->count == RC5_NBITS) अणु
			/* RC5 */
			u8 command, प्रणाली;
			अगर (!(dev->enabled_protocols & RC_PROTO_BIT_RC5)) अणु
				data->state = STATE_INACTIVE;
				वापस 0;
			पूर्ण
			command  = (data->bits & 0x0003F) >> 0;
			प्रणाली   = (data->bits & 0x007C0) >> 6;
			toggle   = (data->bits & 0x00800) ? 1 : 0;
			command += (data->bits & 0x01000) ? 0 : 0x40;
			scancode = प्रणाली << 8 | command;
			protocol = RC_PROTO_RC5;

		पूर्ण अन्यथा अगर (!data->is_rc5x && data->count == RC5_SZ_NBITS) अणु
			/* RC5 StreamZap */
			u8 command, प्रणाली;
			अगर (!(dev->enabled_protocols & RC_PROTO_BIT_RC5_SZ)) अणु
				data->state = STATE_INACTIVE;
				वापस 0;
			पूर्ण
			command  = (data->bits & 0x0003F) >> 0;
			प्रणाली   = (data->bits & 0x02FC0) >> 6;
			toggle   = (data->bits & 0x01000) ? 1 : 0;
			scancode = प्रणाली << 6 | command;
			protocol = RC_PROTO_RC5_SZ;

		पूर्ण अन्यथा
			अवरोध;

		dev_dbg(&dev->dev, "RC5(x/sz) scancode 0x%06x (p: %u, t: %u)\n",
			scancode, protocol, toggle);

		rc_keyकरोwn(dev, protocol, scancode, toggle);
		data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

out:
	dev_dbg(&dev->dev, "RC5(x/sz) decode failed at state %i count %d (%uus %s)\n",
		data->state, data->count, ev.duration, TO_STR(ev.pulse));
	data->state = STATE_INACTIVE;
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा ir_raw_timings_manchester ir_rc5_timings = अणु
	.leader_pulse		= RC5_UNIT,
	.घड़ी			= RC5_UNIT,
	.trailer_space		= RC5_UNIT * 10,
पूर्ण;

अटल स्थिर काष्ठा ir_raw_timings_manchester ir_rc5x_timings[2] = अणु
	अणु
		.leader_pulse		= RC5_UNIT,
		.घड़ी			= RC5_UNIT,
		.trailer_space		= RC5X_SPACE,
	पूर्ण,
	अणु
		.घड़ी			= RC5_UNIT,
		.trailer_space		= RC5_UNIT * 10,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ir_raw_timings_manchester ir_rc5_sz_timings = अणु
	.leader_pulse			= RC5_UNIT,
	.घड़ी				= RC5_UNIT,
	.trailer_space			= RC5_UNIT * 10,
पूर्ण;

/**
 * ir_rc5_encode() - Encode a scancode as a stream of raw events
 *
 * @protocol:	protocol variant to encode
 * @scancode:	scancode to encode
 * @events:	array of raw ir events to ग_लिखो पूर्णांकo
 * @max:	maximum size of @events
 *
 * Returns:	The number of events written.
 *		-ENOBUFS अगर there isn't enough space in the array to fit the
 *		encoding. In this हाल all @max events will have been written.
 *		-EINVAL अगर the scancode is ambiguous or invalid.
 */
अटल पूर्णांक ir_rc5_encode(क्रमागत rc_proto protocol, u32 scancode,
			 काष्ठा ir_raw_event *events, अचिन्हित पूर्णांक max)
अणु
	पूर्णांक ret;
	काष्ठा ir_raw_event *e = events;
	अचिन्हित पूर्णांक data, xdata, command, commandx, प्रणाली, pre_space_data;

	/* Detect protocol and convert scancode to raw data */
	अगर (protocol == RC_PROTO_RC5) अणु
		/* decode scancode */
		command  = (scancode & 0x003f) >> 0;
		commandx = (scancode & 0x0040) >> 6;
		प्रणाली   = (scancode & 0x1f00) >> 8;
		/* encode data */
		data = !commandx << 12 | प्रणाली << 6 | command;

		/* First bit is encoded by leader_pulse */
		ret = ir_raw_gen_manchester(&e, max, &ir_rc5_timings,
					    RC5_NBITS - 1, data);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (protocol == RC_PROTO_RC5X_20) अणु
		/* decode scancode */
		xdata    = (scancode & 0x00003f) >> 0;
		command  = (scancode & 0x003f00) >> 8;
		commandx = !(scancode & 0x004000);
		प्रणाली   = (scancode & 0x1f0000) >> 16;

		/* encode data */
		data = commandx << 18 | प्रणाली << 12 | command << 6 | xdata;

		/* First bit is encoded by leader_pulse */
		pre_space_data = data >> (RC5X_NBITS - CHECK_RC5X_NBITS);
		ret = ir_raw_gen_manchester(&e, max, &ir_rc5x_timings[0],
					    CHECK_RC5X_NBITS - 1,
					    pre_space_data);
		अगर (ret < 0)
			वापस ret;
		ret = ir_raw_gen_manchester(&e, max - (e - events),
					    &ir_rc5x_timings[1],
					    RC5X_NBITS - CHECK_RC5X_NBITS,
					    data);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (protocol == RC_PROTO_RC5_SZ) अणु
		/* RC5-SZ scancode is raw enough क्रम Manchester as it is */
		/* First bit is encoded by leader_pulse */
		ret = ir_raw_gen_manchester(&e, max, &ir_rc5_sz_timings,
					    RC5_SZ_NBITS - 1,
					    scancode & 0x2fff);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस e - events;
पूर्ण

अटल काष्ठा ir_raw_handler rc5_handler = अणु
	.protocols	= RC_PROTO_BIT_RC5 | RC_PROTO_BIT_RC5X_20 |
							RC_PROTO_BIT_RC5_SZ,
	.decode		= ir_rc5_decode,
	.encode		= ir_rc5_encode,
	.carrier	= 36000,
	.min_समयout	= RC5_TRAILER,
पूर्ण;

अटल पूर्णांक __init ir_rc5_decode_init(व्योम)
अणु
	ir_raw_handler_रेजिस्टर(&rc5_handler);

	prपूर्णांकk(KERN_INFO "IR RC5(x/sz) protocol handler initialized\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास ir_rc5_decode_निकास(व्योम)
अणु
	ir_raw_handler_unरेजिस्टर(&rc5_handler);
पूर्ण

module_init(ir_rc5_decode_init);
module_निकास(ir_rc5_decode_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Mauro Carvalho Chehab and Jarod Wilson");
MODULE_AUTHOR("Red Hat Inc. (http://www.redhat.com)");
MODULE_DESCRIPTION("RC5(x/sz) IR protocol decoder");
