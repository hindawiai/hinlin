<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// ir-rcmm-decoder.c - A decoder क्रम the RCMM IR protocol
//
// Copyright (C) 2018 by Patrick Lerda <patrick9876@मुक्त.fr>

#समावेश "rc-core-priv.h"
#समावेश <linux/module.h>

#घोषणा RCMM_UNIT		166  /* microseconds */
#घोषणा RCMM_PREFIX_PULSE	417  /* 166.666666666666*2.5 */
#घोषणा RCMM_PULSE_0            278  /* 166.666666666666*(1+2/3) */
#घोषणा RCMM_PULSE_1            444  /* 166.666666666666*(2+2/3) */
#घोषणा RCMM_PULSE_2            611  /* 166.666666666666*(3+2/3) */
#घोषणा RCMM_PULSE_3            778  /* 166.666666666666*(4+2/3) */

क्रमागत rcmm_state अणु
	STATE_INACTIVE,
	STATE_LOW,
	STATE_BUMP,
	STATE_VALUE,
	STATE_FINISHED,
पूर्ण;

अटल bool rcmm_mode(स्थिर काष्ठा rcmm_dec *data)
अणु
	वापस !((0x000c0000 & data->bits) == 0x000c0000);
पूर्ण

अटल पूर्णांक rcmm_miscmode(काष्ठा rc_dev *dev, काष्ठा rcmm_dec *data)
अणु
	चयन (data->count) अणु
	हाल 24:
		अगर (dev->enabled_protocols & RC_PROTO_BIT_RCMM24) अणु
			rc_keyकरोwn(dev, RC_PROTO_RCMM24, data->bits, 0);
			data->state = STATE_INACTIVE;
			वापस 0;
		पूर्ण
		वापस -1;

	हाल 12:
		अगर (dev->enabled_protocols & RC_PROTO_BIT_RCMM12) अणु
			rc_keyकरोwn(dev, RC_PROTO_RCMM12, data->bits, 0);
			data->state = STATE_INACTIVE;
			वापस 0;
		पूर्ण
		वापस -1;
	पूर्ण

	वापस -1;
पूर्ण

/**
 * ir_rcmm_decode() - Decode one RCMM pulse or space
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @ev:		the काष्ठा ir_raw_event descriptor of the pulse/space
 *
 * This function वापसs -EINVAL अगर the pulse violates the state machine
 */
अटल पूर्णांक ir_rcmm_decode(काष्ठा rc_dev *dev, काष्ठा ir_raw_event ev)
अणु
	काष्ठा rcmm_dec *data = &dev->raw->rcmm;
	u32 scancode;
	u8 toggle;
	पूर्णांक value;

	अगर (!(dev->enabled_protocols & (RC_PROTO_BIT_RCMM32 |
					RC_PROTO_BIT_RCMM24 |
					RC_PROTO_BIT_RCMM12)))
		वापस 0;

	अगर (!is_timing_event(ev)) अणु
		अगर (ev.reset)
			data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

	चयन (data->state) अणु
	हाल STATE_INACTIVE:
		अगर (!ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, RCMM_PREFIX_PULSE, RCMM_UNIT))
			अवरोध;

		data->state = STATE_LOW;
		data->count = 0;
		data->bits  = 0;
		वापस 0;

	हाल STATE_LOW:
		अगर (ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, RCMM_PULSE_0, RCMM_UNIT))
			अवरोध;

		data->state = STATE_BUMP;
		वापस 0;

	हाल STATE_BUMP:
		अगर (!ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, RCMM_UNIT, RCMM_UNIT / 2))
			अवरोध;

		data->state = STATE_VALUE;
		वापस 0;

	हाल STATE_VALUE:
		अगर (ev.pulse)
			अवरोध;

		अगर (eq_margin(ev.duration, RCMM_PULSE_0, RCMM_UNIT / 2))
			value = 0;
		अन्यथा अगर (eq_margin(ev.duration, RCMM_PULSE_1, RCMM_UNIT / 2))
			value = 1;
		अन्यथा अगर (eq_margin(ev.duration, RCMM_PULSE_2, RCMM_UNIT / 2))
			value = 2;
		अन्यथा अगर (eq_margin(ev.duration, RCMM_PULSE_3, RCMM_UNIT / 2))
			value = 3;
		अन्यथा
			value = -1;

		अगर (value == -1) अणु
			अगर (!rcmm_miscmode(dev, data))
				वापस 0;
			अवरोध;
		पूर्ण

		data->bits <<= 2;
		data->bits |= value;

		data->count += 2;

		अगर (data->count < 32)
			data->state = STATE_BUMP;
		अन्यथा
			data->state = STATE_FINISHED;

		वापस 0;

	हाल STATE_FINISHED:
		अगर (!ev.pulse)
			अवरोध;

		अगर (!eq_margin(ev.duration, RCMM_UNIT, RCMM_UNIT / 2))
			अवरोध;

		अगर (rcmm_mode(data)) अणु
			toggle = !!(0x8000 & data->bits);
			scancode = data->bits & ~0x8000;
		पूर्ण अन्यथा अणु
			toggle = 0;
			scancode = data->bits;
		पूर्ण

		अगर (dev->enabled_protocols & RC_PROTO_BIT_RCMM32) अणु
			rc_keyकरोwn(dev, RC_PROTO_RCMM32, scancode, toggle);
			data->state = STATE_INACTIVE;
			वापस 0;
		पूर्ण

		अवरोध;
	पूर्ण

	dev_dbg(&dev->dev, "RC-MM decode failed at count %d state %d (%uus %s)\n",
		data->count, data->state, ev.duration, TO_STR(ev.pulse));
	data->state = STATE_INACTIVE;
	वापस -EINVAL;
पूर्ण

अटल स्थिर पूर्णांक rcmmspace[] = अणु
	RCMM_PULSE_0,
	RCMM_PULSE_1,
	RCMM_PULSE_2,
	RCMM_PULSE_3,
पूर्ण;

अटल पूर्णांक ir_rcmm_rawencoder(काष्ठा ir_raw_event **ev, अचिन्हित पूर्णांक max,
			      अचिन्हित पूर्णांक n, u32 data)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	ret = ir_raw_gen_pulse_space(ev, &max, RCMM_PREFIX_PULSE, RCMM_PULSE_0);
	अगर (ret)
		वापस ret;

	क्रम (i = n - 2; i >= 0; i -= 2) अणु
		स्थिर अचिन्हित पूर्णांक space = rcmmspace[(data >> i) & 3];

		ret = ir_raw_gen_pulse_space(ev, &max, RCMM_UNIT, space);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ir_raw_gen_pulse_space(ev, &max, RCMM_UNIT, RCMM_PULSE_3 * 2);
पूर्ण

अटल पूर्णांक ir_rcmm_encode(क्रमागत rc_proto protocol, u32 scancode,
			  काष्ठा ir_raw_event *events, अचिन्हित पूर्णांक max)
अणु
	काष्ठा ir_raw_event *e = events;
	पूर्णांक ret;

	चयन (protocol) अणु
	हाल RC_PROTO_RCMM32:
		ret = ir_rcmm_rawencoder(&e, max, 32, scancode);
		अवरोध;
	हाल RC_PROTO_RCMM24:
		ret = ir_rcmm_rawencoder(&e, max, 24, scancode);
		अवरोध;
	हाल RC_PROTO_RCMM12:
		ret = ir_rcmm_rawencoder(&e, max, 12, scancode);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	वापस e - events;
पूर्ण

अटल काष्ठा ir_raw_handler rcmm_handler = अणु
	.protocols	= RC_PROTO_BIT_RCMM32 |
			  RC_PROTO_BIT_RCMM24 |
			  RC_PROTO_BIT_RCMM12,
	.decode		= ir_rcmm_decode,
	.encode         = ir_rcmm_encode,
	.carrier        = 36000,
	.min_समयout	= RCMM_PULSE_3 + RCMM_UNIT,
पूर्ण;

अटल पूर्णांक __init ir_rcmm_decode_init(व्योम)
अणु
	ir_raw_handler_रेजिस्टर(&rcmm_handler);

	pr_info("IR RCMM protocol handler initialized\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास ir_rcmm_decode_निकास(व्योम)
अणु
	ir_raw_handler_unरेजिस्टर(&rcmm_handler);
पूर्ण

module_init(ir_rcmm_decode_init);
module_निकास(ir_rcmm_decode_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick Lerda");
MODULE_DESCRIPTION("RCMM IR protocol decoder");
