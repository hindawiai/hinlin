<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Synaptics TouchPad PS/2 mouse driver
 */

#अगर_अघोषित _SYNAPTICS_H
#घोषणा _SYNAPTICS_H

/* synaptics queries */
#घोषणा SYN_QUE_IDENTIFY		0x00
#घोषणा SYN_QUE_MODES			0x01
#घोषणा SYN_QUE_CAPABILITIES		0x02
#घोषणा SYN_QUE_MODEL			0x03
#घोषणा SYN_QUE_SERIAL_NUMBER_PREFIX	0x06
#घोषणा SYN_QUE_SERIAL_NUMBER_SUFFIX	0x07
#घोषणा SYN_QUE_RESOLUTION		0x08
#घोषणा SYN_QUE_EXT_CAPAB		0x09
#घोषणा SYN_QUE_FIRMWARE_ID		0x0a
#घोषणा SYN_QUE_EXT_CAPAB_0C		0x0c
#घोषणा SYN_QUE_EXT_MAX_COORDS		0x0d
#घोषणा SYN_QUE_EXT_MIN_COORDS		0x0f
#घोषणा SYN_QUE_MEXT_CAPAB_10		0x10

/* synatics modes */
#घोषणा SYN_BIT_ABSOLUTE_MODE		BIT(7)
#घोषणा SYN_BIT_HIGH_RATE		BIT(6)
#घोषणा SYN_BIT_SLEEP_MODE		BIT(3)
#घोषणा SYN_BIT_DISABLE_GESTURE		BIT(2)
#घोषणा SYN_BIT_FOUR_BYTE_CLIENT	BIT(1)
#घोषणा SYN_BIT_W_MODE			BIT(0)

/* synaptics model ID bits */
#घोषणा SYN_MODEL_ROT180(m)		((m) & BIT(23))
#घोषणा SYN_MODEL_PORTRAIT(m)		((m) & BIT(22))
#घोषणा SYN_MODEL_SENSOR(m)		(((m) & GENMASK(21, 16)) >> 16)
#घोषणा SYN_MODEL_HARDWARE(m)		(((m) & GENMASK(15, 9)) >> 9)
#घोषणा SYN_MODEL_NEWABS(m)		((m) & BIT(7))
#घोषणा SYN_MODEL_PEN(m)		((m) & BIT(6))
#घोषणा SYN_MODEL_SIMPLIC(m)		((m) & BIT(5))
#घोषणा SYN_MODEL_GEOMETRY(m)		((m) & GENMASK(3, 0))

/* synaptics capability bits */
#घोषणा SYN_CAP_EXTENDED(c)		((c) & BIT(23))
#घोषणा SYN_CAP_MIDDLE_BUTTON(c)	((c) & BIT(18))
#घोषणा SYN_CAP_PASS_THROUGH(c)		((c) & BIT(7))
#घोषणा SYN_CAP_SLEEP(c)		((c) & BIT(4))
#घोषणा SYN_CAP_FOUR_BUTTON(c)		((c) & BIT(3))
#घोषणा SYN_CAP_MULTIFINGER(c)		((c) & BIT(1))
#घोषणा SYN_CAP_PALMDETECT(c)		((c) & BIT(0))
#घोषणा SYN_CAP_SUBMODEL_ID(c)		(((c) & GENMASK(15, 8)) >> 8)
#घोषणा SYN_EXT_CAP_REQUESTS(c)		(((c) & GENMASK(22, 20)) >> 20)
#घोषणा SYN_CAP_MB_MASK			GENMASK(15, 12)
#घोषणा SYN_CAP_MULTI_BUTTON_NO(ec)	(((ec) & SYN_CAP_MB_MASK) >> 12)
#घोषणा SYN_CAP_PRODUCT_ID(ec)		(((ec) & GENMASK(23, 16)) >> 16)
#घोषणा SYN_MEXT_CAP_BIT(m)		((m) & BIT(1))

/*
 * The following describes response क्रम the 0x0c query.
 *
 * byte	mask	name			meaning
 * ----	----	-------			------------
 * 1	0x01	adjustable threshold	capacitive button sensitivity
 *					can be adjusted
 * 1	0x02	report max		query 0x0d gives max coord reported
 * 1	0x04	clearpad		sensor is ClearPad product
 * 1	0x08	advanced gesture	not particularly meaningful
 * 1	0x10	clickpad bit 0		1-button ClickPad
 * 1	0x60	multअगरinger mode	identअगरies firmware finger counting
 *					(not reporting!) algorithm.
 *					Not particularly meaningful
 * 1	0x80	covered pad		W clipped to 14, 15 == pad mostly covered
 * 2	0x01	clickpad bit 1		2-button ClickPad
 * 2	0x02	deluxe LED controls	touchpad support LED commands
 *					ala mulसमयdia control bar
 * 2	0x04	reduced filtering	firmware करोes less filtering on
 *					position data, driver should watch
 *					क्रम noise.
 * 2	0x08	image sensor		image sensor tracks 5 fingers, but only
 *					reports 2.
 * 2	0x01	unअगरorm clickpad	whole clickpad moves instead of being
 *					hinged at the top.
 * 2	0x20	report min		query 0x0f gives min coord reported
 */
#घोषणा SYN_CAP_CLICKPAD(ex0c)		((ex0c) & BIT(20)) /* 1-button ClickPad */
#घोषणा SYN_CAP_CLICKPAD2BTN(ex0c)	((ex0c) & BIT(8))  /* 2-button ClickPad */
#घोषणा SYN_CAP_MAX_DIMENSIONS(ex0c)	((ex0c) & BIT(17))
#घोषणा SYN_CAP_MIN_DIMENSIONS(ex0c)	((ex0c) & BIT(13))
#घोषणा SYN_CAP_ADV_GESTURE(ex0c)	((ex0c) & BIT(19))
#घोषणा SYN_CAP_REDUCED_FILTERING(ex0c)	((ex0c) & BIT(10))
#घोषणा SYN_CAP_IMAGE_SENSOR(ex0c)	((ex0c) & BIT(11))
#घोषणा SYN_CAP_INTERTOUCH(ex0c)	((ex0c) & BIT(14))

/*
 * The following descibes response क्रम the 0x10 query.
 *
 * byte	mask	name			meaning
 * ----	----	-------			------------
 * 1	0x01	ext buttons are stick	buttons exported in the extended
 *					capability are actually meant to be used
 *					by the tracktick (pass-through).
 * 1	0x02	SecurePad		the touchpad is a SecurePad, so it
 *					contains a built-in fingerprपूर्णांक पढ़ोer.
 * 1	0xe0	more ext count		how many more extented queries are
 *					available after this one.
 * 2	0xff	SecurePad width		the width of the SecurePad fingerprपूर्णांक
 *					पढ़ोer.
 * 3	0xff	SecurePad height	the height of the SecurePad fingerprपूर्णांक
 *					पढ़ोer.
 */
#घोषणा SYN_CAP_EXT_BUTTONS_STICK(ex10)	((ex10) & BIT(16))
#घोषणा SYN_CAP_SECUREPAD(ex10)		((ex10) & BIT(17))

#घोषणा SYN_EXT_BUTTON_STICK_L(eb)	(((eb) & BIT(0)) >> 0)
#घोषणा SYN_EXT_BUTTON_STICK_M(eb)	(((eb) & BIT(1)) >> 1)
#घोषणा SYN_EXT_BUTTON_STICK_R(eb)	(((eb) & BIT(2)) >> 2)

/* synaptics modes query bits */
#घोषणा SYN_MODE_ABSOLUTE(m)		((m) & BIT(7))
#घोषणा SYN_MODE_RATE(m)		((m) & BIT(6))
#घोषणा SYN_MODE_BAUD_SLEEP(m)		((m) & BIT(3))
#घोषणा SYN_MODE_DISABLE_GESTURE(m)	((m) & BIT(2))
#घोषणा SYN_MODE_PACKSIZE(m)		((m) & BIT(1))
#घोषणा SYN_MODE_WMODE(m)		((m) & BIT(0))

/* synaptics identअगरy query bits */
#घोषणा SYN_ID_MODEL(i)			(((i) & GENMASK(7, 4)) >> 4)
#घोषणा SYN_ID_MAJOR(i)			(((i) & GENMASK(3, 0)) >> 0)
#घोषणा SYN_ID_MINOR(i)			(((i) & GENMASK(23, 16)) >> 16)
#घोषणा SYN_ID_FULL(i)			((SYN_ID_MAJOR(i) << 8) | SYN_ID_MINOR(i))
#घोषणा SYN_ID_IS_SYNAPTICS(i)		(((i) & GENMASK(15, 8)) == 0x004700U)
#घोषणा SYN_ID_DISGEST_SUPPORTED(i)	(SYN_ID_MAJOR(i) >= 4)

/* synaptics special commands */
#घोषणा SYN_PS_SET_MODE2		0x14
#घोषणा SYN_PS_CLIENT_CMD		0x28

/* amount to fuzz position data when touchpad reports reduced filtering */
#घोषणा SYN_REDUCED_FILTER_FUZZ		8

/* synaptics packet types */
क्रमागत synaptics_pkt_type अणु
	SYN_NEWABS,
	SYN_NEWABS_STRICT,
	SYN_NEWABS_RELAXED,
	SYN_OLDABS,
पूर्ण;

/*
 * A काष्ठाure to describe the state of the touchpad hardware (buttons and pad)
 */
काष्ठा synaptics_hw_state अणु
	पूर्णांक x;
	पूर्णांक y;
	पूर्णांक z;
	पूर्णांक w;
	अचिन्हित पूर्णांक left:1;
	अचिन्हित पूर्णांक right:1;
	अचिन्हित पूर्णांक middle:1;
	अचिन्हित पूर्णांक up:1;
	अचिन्हित पूर्णांक करोwn:1;
	u8 ext_buttons;
	s8 scroll;
पूर्ण;

/* Data पढ़ो from the touchpad */
काष्ठा synaptics_device_info अणु
	u32 model_id;		/* Model-ID */
	u32 firmware_id;	/* Firmware-ID */
	u32 board_id;		/* Board-ID */
	u32 capabilities;	/* Capabilities */
	u32 ext_cap;		/* Extended Capabilities */
	u32 ext_cap_0c;		/* Ext Caps from 0x0c query */
	u32 ext_cap_10;		/* Ext Caps from 0x10 query */
	u32 identity;		/* Identअगरication */
	u32 x_res, y_res;	/* X/Y resolution in units/mm */
	u32 x_max, y_max;	/* Max coordinates (from FW) */
	u32 x_min, y_min;	/* Min coordinates (from FW) */
पूर्ण;

काष्ठा synaptics_data अणु
	काष्ठा synaptics_device_info info;

	क्रमागत synaptics_pkt_type pkt_type;	/* packet type - old, new, etc */
	u8 mode;				/* current mode byte */
	पूर्णांक scroll;

	bool असलolute_mode;			/* run in Absolute mode */
	bool disable_gesture;			/* disable gestures */

	काष्ठा serio *pt_port;			/* Pass-through serio port */

	/*
	 * Last received Advanced Gesture Mode (AGM) packet. An AGM packet
	 * contains position data क्रम a second contact, at half resolution.
	 */
	काष्ठा synaptics_hw_state agm;
	अचिन्हित पूर्णांक agm_count;			/* finger count reported by agm */

	/* ForcePad handling */
	अचिन्हित दीर्घ				press_start;
	bool					press;
	bool					report_press;
	bool					is_क्रमcepad;
पूर्ण;

व्योम synaptics_module_init(व्योम);
पूर्णांक synaptics_detect(काष्ठा psmouse *psmouse, bool set_properties);
पूर्णांक synaptics_init_असलolute(काष्ठा psmouse *psmouse);
पूर्णांक synaptics_init_relative(काष्ठा psmouse *psmouse);
पूर्णांक synaptics_init_smbus(काष्ठा psmouse *psmouse);
पूर्णांक synaptics_init(काष्ठा psmouse *psmouse);
व्योम synaptics_reset(काष्ठा psmouse *psmouse);

#पूर्ण_अगर /* _SYNAPTICS_H */
