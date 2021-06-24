<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _IR_I2C
#घोषणा _IR_I2C

#समावेश <media/rc-core.h>

#घोषणा DEFAULT_POLLING_INTERVAL	100	/* ms */

काष्ठा IR_i2c;

काष्ठा IR_i2c अणु
	अक्षर		       *ir_codes;
	काष्ठा i2c_client      *c;
	काष्ठा rc_dev          *rc;

	/* Used to aव्योम fast repeating */
	अचिन्हित अक्षर          old;

	u32                    polling_पूर्णांकerval; /* in ms */

	काष्ठा delayed_work    work;
	अक्षर                   phys[32];
	पूर्णांक                    (*get_key)(काष्ठा IR_i2c *ir,
					  क्रमागत rc_proto *protocol,
					  u32 *scancode, u8 *toggle);
	/* tx */
	काष्ठा i2c_client      *tx_c;
	काष्ठा mutex	       lock;	/* करो not poll Rx during Tx */
	अचिन्हित पूर्णांक	       carrier;
	अचिन्हित पूर्णांक	       duty_cycle;
पूर्ण;

क्रमागत ir_kbd_get_key_fn अणु
	IR_KBD_GET_KEY_CUSTOM = 0,
	IR_KBD_GET_KEY_PIXELVIEW,
	IR_KBD_GET_KEY_HAUP,
	IR_KBD_GET_KEY_KNC1,
	IR_KBD_GET_KEY_FUSIONHDTV,
	IR_KBD_GET_KEY_HAUP_XVR,
	IR_KBD_GET_KEY_AVERMEDIA_CARDBUS,
पूर्ण;

/* Can be passed when instantiating an ir_video i2c device */
काष्ठा IR_i2c_init_data अणु
	अक्षर			*ir_codes;
	स्थिर अक्षर		*name;
	u64			type; /* RC_PROTO_BIT_RC5, etc */
	u32			polling_पूर्णांकerval; /* 0 means DEFAULT_POLLING_INTERVAL */

	/*
	 * Specअगरy either a function poपूर्णांकer or a value indicating one of
	 * ir_kbd_i2c's पूर्णांकernal get_key functions
	 */
	पूर्णांक                    (*get_key)(काष्ठा IR_i2c *ir,
					  क्रमागत rc_proto *protocol,
					  u32 *scancode, u8 *toggle);
	क्रमागत ir_kbd_get_key_fn पूर्णांकernal_get_key_func;

	काष्ठा rc_dev		*rc_dev;
पूर्ण;
#पूर्ण_अगर
