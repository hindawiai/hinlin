<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MacBook (Pro) SPI keyboard and touchpad driver
 *
 * Copyright (c) 2015-2018 Federico Lorenzi
 * Copyright (c) 2017-2018 Ronald Tschalथअr
 */

/*
 * The keyboard and touchpad controller on the MacBookAir6, MacBookPro12,
 * MacBook8 and newer can be driven either by USB or SPI. However the USB
 * pins are only connected on the MacBookAir6 and 7 and the MacBookPro12.
 * All others need this driver. The पूर्णांकerface is selected using ACPI methods:
 *
 * * UIEN ("USB Interface Enable"): If invoked with argument 1, disables SPI
 *   and enables USB. If invoked with argument 0, disables USB.
 * * UIST ("USB Interface Status"): Returns 1 अगर USB is enabled, 0 otherwise.
 * * SIEN ("SPI Interface Enable"): If invoked with argument 1, disables USB
 *   and enables SPI. If invoked with argument 0, disables SPI.
 * * SIST ("SPI Interface Status"): Returns 1 अगर SPI is enabled, 0 otherwise.
 * * ISOL: Resets the four GPIO pins used क्रम SPI. Intended to be invoked with
 *   argument 1, then once more with argument 0.
 *
 * UIEN and UIST are only provided on models where the USB pins are connected.
 *
 * SPI-based Protocol
 * ------------------
 *
 * The device and driver exchange messages (काष्ठा message); each message is
 * encapsulated in one or more packets (काष्ठा spi_packet). There are two types
 * of exchanges: पढ़ोs, and ग_लिखोs. A पढ़ो is संकेतed by a GPE, upon which one
 * message can be पढ़ो from the device. A ग_लिखो exchange consists of writing a
 * command message, immediately पढ़ोing a लघु status packet, and then, upon
 * receiving a GPE, पढ़ोing the response message. Write exchanges cannot be
 * पूर्णांकerleaved, i.e. a new ग_लिखो exchange must not be started till the previous
 * ग_लिखो exchange is complete. Whether a received message is part of a पढ़ो or
 * ग_लिखो exchange is indicated in the encapsulating packet's flags field.
 *
 * A single message may be too large to fit in a single packet (which has a
 * fixed, 256-byte size). In that हाल it will be split over multiple,
 * consecutive packets.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/crc16.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/efi.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश "applespi.h"
#समावेश "applespi_trace.h"

#घोषणा APPLESPI_PACKET_SIZE	256
#घोषणा APPLESPI_STATUS_SIZE	4

#घोषणा PACKET_TYPE_READ	0x20
#घोषणा PACKET_TYPE_WRITE	0x40
#घोषणा PACKET_DEV_KEYB		0x01
#घोषणा PACKET_DEV_TPAD		0x02
#घोषणा PACKET_DEV_INFO		0xd0

#घोषणा MAX_ROLLOVER		6

#घोषणा MAX_FINGERS		11
#घोषणा MAX_FINGER_ORIENTATION	16384
#घोषणा MAX_PKTS_PER_MSG	2

#घोषणा KBD_BL_LEVEL_MIN	32U
#घोषणा KBD_BL_LEVEL_MAX	255U
#घोषणा KBD_BL_LEVEL_SCALE	1000000U
#घोषणा KBD_BL_LEVEL_ADJ	\
	((KBD_BL_LEVEL_MAX - KBD_BL_LEVEL_MIN) * KBD_BL_LEVEL_SCALE / 255U)

#घोषणा EFI_BL_LEVEL_NAME	L"KeyboardBacklightLevel"
#घोषणा EFI_BL_LEVEL_GUID	EFI_GUID(0xa076d2af, 0x9678, 0x4386, 0x8b, 0x58, 0x1f, 0xc8, 0xef, 0x04, 0x16, 0x19)

#घोषणा APPLE_FLAG_FKEY		0x01

#घोषणा SPI_RW_CHG_DELAY_US	100	/* from experimentation, in तगs */

#घोषणा SYNAPTICS_VENDOR_ID	0x06cb

अटल अचिन्हित पूर्णांक fnmode = 1;
module_param(fnmode, uपूर्णांक, 0644);
MODULE_PARM_DESC(fnmode, "Mode of Fn key on Apple keyboards (0 = disabled, [1] = fkeyslast, 2 = fkeysfirst)");

अटल अचिन्हित पूर्णांक fnremap;
module_param(fnremap, uपूर्णांक, 0644);
MODULE_PARM_DESC(fnremap, "Remap Fn key ([0] = no-remap; 1 = left-ctrl, 2 = left-shift, 3 = left-alt, 4 = left-meta, 6 = right-shift, 7 = right-alt, 8 = right-meta)");

अटल bool iso_layout;
module_param(iso_layout, bool, 0644);
MODULE_PARM_DESC(iso_layout, "Enable/Disable hardcoded ISO-layout of the keyboard. ([0] = disabled, 1 = enabled)");

अटल अक्षर touchpad_dimensions[40];
module_param_string(touchpad_dimensions, touchpad_dimensions,
		    माप(touchpad_dimensions), 0444);
MODULE_PARM_DESC(touchpad_dimensions, "The pixel dimensions of the touchpad, as XxY+W+H .");

/**
 * काष्ठा keyboard_protocol - keyboard message.
 * message.type = 0x0110, message.length = 0x000a
 *
 * @unknown1:		unknown
 * @modअगरiers:		bit-set of modअगरier/control keys pressed
 * @unknown2:		unknown
 * @keys_pressed:	the (non-modअगरier) keys currently pressed
 * @fn_pressed:		whether the fn key is currently pressed
 * @crc16:		crc over the whole message काष्ठा (message header +
 *			this काष्ठा) minus this @crc16 field
 */
काष्ठा keyboard_protocol अणु
	u8			unknown1;
	u8			modअगरiers;
	u8			unknown2;
	u8			keys_pressed[MAX_ROLLOVER];
	u8			fn_pressed;
	__le16			crc16;
पूर्ण;

/**
 * काष्ठा tp_finger - single trackpad finger काष्ठाure, le16-aligned
 *
 * @origin:		zero when चयनing track finger
 * @असल_x:		असलolute x coordinate
 * @असल_y:		असलolute y coordinate
 * @rel_x:		relative x coordinate
 * @rel_y:		relative y coordinate
 * @tool_major:		tool area, major axis
 * @tool_minor:		tool area, minor axis
 * @orientation:	16384 when poपूर्णांक, अन्यथा 15 bit angle
 * @touch_major:	touch area, major axis
 * @touch_minor:	touch area, minor axis
 * @unused:		zeros
 * @pressure:		pressure on क्रमcetouch touchpad
 * @multi:		one finger: varies, more fingers: स्थिरant
 * @crc16:		on last finger: crc over the whole message काष्ठा
 *			(i.e. message header + this काष्ठा) minus the last
 *			@crc16 field; unknown on all other fingers.
 */
काष्ठा tp_finger अणु
	__le16 origin;
	__le16 असल_x;
	__le16 असल_y;
	__le16 rel_x;
	__le16 rel_y;
	__le16 tool_major;
	__le16 tool_minor;
	__le16 orientation;
	__le16 touch_major;
	__le16 touch_minor;
	__le16 unused[2];
	__le16 pressure;
	__le16 multi;
	__le16 crc16;
पूर्ण;

/**
 * काष्ठा touchpad_protocol - touchpad message.
 * message.type = 0x0210
 *
 * @unknown1:		unknown
 * @clicked:		1 अगर a button-click was detected, 0 otherwise
 * @unknown2:		unknown
 * @number_of_fingers:	the number of fingers being reported in @fingers
 * @clicked2:		same as @clicked
 * @unknown3:		unknown
 * @fingers:		the data क्रम each finger
 */
काष्ठा touchpad_protocol अणु
	u8			unknown1[1];
	u8			clicked;
	u8			unknown2[28];
	u8			number_of_fingers;
	u8			clicked2;
	u8			unknown3[16];
	काष्ठा tp_finger	fingers[];
पूर्ण;

/**
 * काष्ठा command_protocol_tp_info - get touchpad info.
 * message.type = 0x1020, message.length = 0x0000
 *
 * @crc16:		crc over the whole message काष्ठा (message header +
 *			this काष्ठा) minus this @crc16 field
 */
काष्ठा command_protocol_tp_info अणु
	__le16			crc16;
पूर्ण;

/**
 * काष्ठा touchpad_info - touchpad info response.
 * message.type = 0x1020, message.length = 0x006e
 *
 * @unknown1:		unknown
 * @model_flags:	flags (vary by model number, but signअगरicance otherwise
 *			unknown)
 * @model_no:		the touchpad model number
 * @unknown2:		unknown
 * @crc16:		crc over the whole message काष्ठा (message header +
 *			this काष्ठा) minus this @crc16 field
 */
काष्ठा touchpad_info_protocol अणु
	u8			unknown1[105];
	u8			model_flags;
	u8			model_no;
	u8			unknown2[3];
	__le16			crc16;
पूर्ण;

/**
 * काष्ठा command_protocol_mt_init - initialize multitouch.
 * message.type = 0x0252, message.length = 0x0002
 *
 * @cmd:		value: 0x0102
 * @crc16:		crc over the whole message काष्ठा (message header +
 *			this काष्ठा) minus this @crc16 field
 */
काष्ठा command_protocol_mt_init अणु
	__le16			cmd;
	__le16			crc16;
पूर्ण;

/**
 * काष्ठा command_protocol_capsl - toggle caps-lock led
 * message.type = 0x0151, message.length = 0x0002
 *
 * @unknown:		value: 0x01 (length?)
 * @led:		0 off, 2 on
 * @crc16:		crc over the whole message काष्ठा (message header +
 *			this काष्ठा) minus this @crc16 field
 */
काष्ठा command_protocol_capsl अणु
	u8			unknown;
	u8			led;
	__le16			crc16;
पूर्ण;

/**
 * काष्ठा command_protocol_bl - set keyboard backlight brightness
 * message.type = 0xB051, message.length = 0x0006
 *
 * @स्थिर1:		value: 0x01B0
 * @level:		the brightness level to set
 * @स्थिर2:		value: 0x0001 (backlight off), 0x01F4 (backlight on)
 * @crc16:		crc over the whole message काष्ठा (message header +
 *			this काष्ठा) minus this @crc16 field
 */
काष्ठा command_protocol_bl अणु
	__le16			स्थिर1;
	__le16			level;
	__le16			स्थिर2;
	__le16			crc16;
पूर्ण;

/**
 * काष्ठा message - a complete spi message.
 *
 * Each message begins with fixed header, followed by a message-type specअगरic
 * payload, and ends with a 16-bit crc. Because of the varying lengths of the
 * payload, the crc is defined at the end of each payload काष्ठा, rather than
 * in this काष्ठा.
 *
 * @type:	the message type
 * @zero:	always 0
 * @counter:	incremented on each message, rolls over after 255; there is a
 *		separate counter क्रम each message type.
 * @rsp_buf_len:response buffer length (the exact nature of this field is quite
 *		speculative). On a request/ग_लिखो this is often the same as
 *		@length, though in some हालs it has been seen to be much larger
 *		(e.g. 0x400); on a response/पढ़ो this the same as on the
 *		request; क्रम पढ़ोs that are not responses it is 0.
 * @length:	length of the reमुख्यder of the data in the whole message
 *		काष्ठाure (after re-assembly in हाल of being split over
 *		multiple spi-packets), minus the trailing crc. The total size
 *		of the message काष्ठा is thereक्रमe @length + 10.
 *
 * @keyboard:		Keyboard message
 * @touchpad:		Touchpad message
 * @tp_info:		Touchpad info (response)
 * @tp_info_command:	Touchpad info (CRC)
 * @init_mt_command:	Initialise Multitouch
 * @capsl_command:	Toggle caps-lock LED
 * @bl_command:		Keyboard brightness
 * @data:		Buffer data
 */
काष्ठा message अणु
	__le16		type;
	u8		zero;
	u8		counter;
	__le16		rsp_buf_len;
	__le16		length;
	जोड़ अणु
		काष्ठा keyboard_protocol	keyboard;
		काष्ठा touchpad_protocol	touchpad;
		काष्ठा touchpad_info_protocol	tp_info;
		काष्ठा command_protocol_tp_info	tp_info_command;
		काष्ठा command_protocol_mt_init	init_mt_command;
		काष्ठा command_protocol_capsl	capsl_command;
		काष्ठा command_protocol_bl	bl_command;
		u8				data[0];
	पूर्ण;
पूर्ण;

/* type + zero + counter + rsp_buf_len + length */
#घोषणा MSG_HEADER_SIZE		8

/**
 * काष्ठा spi_packet - a complete spi packet; always 256 bytes. This carries
 * the (parts of the) message in the data. But note that this करोes not
 * necessarily contain a complete message, as in some हालs (e.g. many
 * fingers pressed) the message is split over multiple packets (see the
 * @offset, @reमुख्यing, and @length fields). In general the data parts in
 * spi_packet's are concatenated until @reमुख्यing is 0, and the result is an
 * message.
 *
 * @flags:	0x40 = ग_लिखो (to device), 0x20 = पढ़ो (from device); note that
 *		the response to a ग_लिखो still has 0x40.
 * @device:	1 = keyboard, 2 = touchpad
 * @offset:	specअगरies the offset of this packet's data in the complete
 *		message; i.e. > 0 indicates this is a continuation packet (in
 *		the second packet क्रम a message split over multiple packets
 *		this would then be the same as the @length in the first packet)
 * @reमुख्यing:	number of message bytes reमुख्यing in subsequents packets (in
 *		the first packet of a message split over two packets this would
 *		then be the same as the @length in the second packet)
 * @length:	length of the valid data in the @data in this packet
 * @data:	all or part of a message
 * @crc16:	crc over this whole काष्ठाure minus this @crc16 field. This
 *		covers just this packet, even on multi-packet messages (in
 *		contrast to the crc in the message).
 */
काष्ठा spi_packet अणु
	u8			flags;
	u8			device;
	__le16			offset;
	__le16			reमुख्यing;
	__le16			length;
	u8			data[246];
	__le16			crc16;
पूर्ण;

काष्ठा spi_settings अणु
	u64	spi_cs_delay;		/* cs-to-clk delay in us */
	u64	reset_a2r_usec;		/* active-to-receive delay? */
	u64	reset_rec_usec;		/* ? (cur val: 10) */
पूर्ण;

/* this mimics काष्ठा drm_rect */
काष्ठा applespi_tp_info अणु
	पूर्णांक	x_min;
	पूर्णांक	y_min;
	पूर्णांक	x_max;
	पूर्णांक	y_max;
पूर्ण;

काष्ठा applespi_data अणु
	काष्ठा spi_device		*spi;
	काष्ठा spi_settings		spi_settings;
	काष्ठा input_dev		*keyboard_input_dev;
	काष्ठा input_dev		*touchpad_input_dev;

	u8				*tx_buffer;
	u8				*tx_status;
	u8				*rx_buffer;

	u8				*msg_buf;
	अचिन्हित पूर्णांक			saved_msg_len;

	काष्ठा applespi_tp_info		tp_info;

	u8				last_keys_pressed[MAX_ROLLOVER];
	u8				last_keys_fn_pressed[MAX_ROLLOVER];
	u8				last_fn_pressed;
	काष्ठा input_mt_pos		pos[MAX_FINGERS];
	पूर्णांक				slots[MAX_FINGERS];
	पूर्णांक				gpe;
	acpi_handle			sien;
	acpi_handle			sist;

	काष्ठा spi_transfer		dl_t;
	काष्ठा spi_transfer		rd_t;
	काष्ठा spi_message		rd_m;

	काष्ठा spi_transfer		ww_t;
	काष्ठा spi_transfer		wd_t;
	काष्ठा spi_transfer		wr_t;
	काष्ठा spi_transfer		st_t;
	काष्ठा spi_message		wr_m;

	bool				want_tp_info_cmd;
	bool				want_mt_init_cmd;
	bool				want_cl_led_on;
	bool				have_cl_led_on;
	अचिन्हित पूर्णांक			want_bl_level;
	अचिन्हित पूर्णांक			have_bl_level;
	अचिन्हित पूर्णांक			cmd_msg_cntr;
	/* lock to protect the above parameters and flags below */
	spinlock_t			cmd_msg_lock;
	kसमय_प्रकार				cmd_msg_queued;
	क्रमागत applespi_evt_type		cmd_evt_type;

	काष्ठा led_classdev		backlight_info;

	bool				suspended;
	bool				drain;
	रुको_queue_head_t		drain_complete;
	bool				पढ़ो_active;
	bool				ग_लिखो_active;

	काष्ठा work_काष्ठा		work;
	काष्ठा touchpad_info_protocol	rcvd_tp_info;

	काष्ठा dentry			*debugfs_root;
	bool				debug_tp_dim;
	अक्षर				tp_dim_val[40];
	पूर्णांक				tp_dim_min_x;
	पूर्णांक				tp_dim_max_x;
	पूर्णांक				tp_dim_min_y;
	पूर्णांक				tp_dim_max_y;
पूर्ण;

अटल स्थिर अचिन्हित अक्षर applespi_scancodes[] = अणु
	0, 0, 0, 0,
	KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
	KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
	KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,
	KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
	KEY_ENTER, KEY_ESC, KEY_BACKSPACE, KEY_TAB, KEY_SPACE, KEY_MINUS,
	KEY_EQUAL, KEY_LEFTBRACE, KEY_RIGHTBRACE, KEY_BACKSLASH, 0,
	KEY_SEMICOLON, KEY_APOSTROPHE, KEY_GRAVE, KEY_COMMA, KEY_DOT, KEY_SLASH,
	KEY_CAPSLOCK,
	KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9,
	KEY_F10, KEY_F11, KEY_F12, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, KEY_102ND,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, KEY_RO, 0, KEY_YEN, 0, 0, 0, 0, 0,
	0, KEY_KATAKANAHIRAGANA, KEY_MUHENKAN
पूर्ण;

/*
 * This must have exactly as many entries as there are bits in
 * काष्ठा keyboard_protocol.modअगरiers .
 */
अटल स्थिर अचिन्हित अक्षर applespi_controlcodes[] = अणु
	KEY_LEFTCTRL,
	KEY_LEFTSHIFT,
	KEY_LEFTALT,
	KEY_LEFTMETA,
	0,
	KEY_RIGHTSHIFT,
	KEY_RIGHTALT,
	KEY_RIGHTMETA
पूर्ण;

काष्ठा applespi_key_translation अणु
	u16 from;
	u16 to;
	u8 flags;
पूर्ण;

अटल स्थिर काष्ठा applespi_key_translation applespi_fn_codes[] = अणु
	अणु KEY_BACKSPACE, KEY_DELETE पूर्ण,
	अणु KEY_ENTER,	KEY_INSERT पूर्ण,
	अणु KEY_F1,	KEY_BRIGHTNESSDOWN,	APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F2,	KEY_BRIGHTNESSUP,	APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F3,	KEY_SCALE,		APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F4,	KEY_DASHBOARD,		APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F5,	KEY_KBDILLUMDOWN,	APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F6,	KEY_KBDILLUMUP,		APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F7,	KEY_PREVIOUSSONG,	APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F8,	KEY_PLAYPAUSE,		APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F9,	KEY_NEXTSONG,		APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F10,	KEY_MUTE,		APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F11,	KEY_VOLUMEDOWN,		APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F12,	KEY_VOLUMEUP,		APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_RIGHT,	KEY_END पूर्ण,
	अणु KEY_LEFT,	KEY_HOME पूर्ण,
	अणु KEY_DOWN,	KEY_PAGEDOWN पूर्ण,
	अणु KEY_UP,	KEY_PAGEUP पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा applespi_key_translation apple_iso_keyboard[] = अणु
	अणु KEY_GRAVE,	KEY_102ND पूर्ण,
	अणु KEY_102ND,	KEY_GRAVE पूर्ण,
	अणु पूर्ण
पूर्ण;

काष्ठा applespi_tp_model_info अणु
	u16			model;
	काष्ठा applespi_tp_info	tp_info;
पूर्ण;

अटल स्थिर काष्ठा applespi_tp_model_info applespi_tp_models[] = अणु
	अणु
		.model = 0x04,	/* MB8 MB9 MB10 */
		.tp_info = अणु -5087, -182, 5579, 6089 पूर्ण,
	पूर्ण,
	अणु
		.model = 0x05,	/* MBP13,1 MBP13,2 MBP14,1 MBP14,2 */
		.tp_info = अणु -6243, -170, 6749, 7685 पूर्ण,
	पूर्ण,
	अणु
		.model = 0x06,	/* MBP13,3 MBP14,3 */
		.tp_info = अणु -7456, -163, 7976, 9283 पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

प्रकार व्योम (*applespi_trace_fun)(क्रमागत applespi_evt_type,
				   क्रमागत applespi_pkt_type, u8 *, माप_प्रकार);

अटल applespi_trace_fun applespi_get_trace_fun(क्रमागत applespi_evt_type type)
अणु
	चयन (type) अणु
	हाल ET_CMD_TP_INI:
		वापस trace_applespi_tp_ini_cmd;
	हाल ET_CMD_BL:
		वापस trace_applespi_backlight_cmd;
	हाल ET_CMD_CL:
		वापस trace_applespi_caps_lock_cmd;
	हाल ET_RD_KEYB:
		वापस trace_applespi_keyboard_data;
	हाल ET_RD_TPAD:
		वापस trace_applespi_touchpad_data;
	हाल ET_RD_UNKN:
		वापस trace_applespi_unknown_data;
	शेष:
		WARN_ONCE(1, "Unknown msg type %d", type);
		वापस trace_applespi_unknown_data;
	पूर्ण
पूर्ण

अटल व्योम applespi_setup_पढ़ो_txfrs(काष्ठा applespi_data *applespi)
अणु
	काष्ठा spi_message *msg = &applespi->rd_m;
	काष्ठा spi_transfer *dl_t = &applespi->dl_t;
	काष्ठा spi_transfer *rd_t = &applespi->rd_t;

	स_रखो(dl_t, 0, माप(*dl_t));
	स_रखो(rd_t, 0, माप(*rd_t));

	dl_t->delay.value = applespi->spi_settings.spi_cs_delay;
	dl_t->delay.unit = SPI_DELAY_UNIT_USECS;

	rd_t->rx_buf = applespi->rx_buffer;
	rd_t->len = APPLESPI_PACKET_SIZE;

	spi_message_init(msg);
	spi_message_add_tail(dl_t, msg);
	spi_message_add_tail(rd_t, msg);
पूर्ण

अटल व्योम applespi_setup_ग_लिखो_txfrs(काष्ठा applespi_data *applespi)
अणु
	काष्ठा spi_message *msg = &applespi->wr_m;
	काष्ठा spi_transfer *wt_t = &applespi->ww_t;
	काष्ठा spi_transfer *dl_t = &applespi->wd_t;
	काष्ठा spi_transfer *wr_t = &applespi->wr_t;
	काष्ठा spi_transfer *st_t = &applespi->st_t;

	स_रखो(wt_t, 0, माप(*wt_t));
	स_रखो(dl_t, 0, माप(*dl_t));
	स_रखो(wr_t, 0, माप(*wr_t));
	स_रखो(st_t, 0, माप(*st_t));

	/*
	 * All we need here is a delay at the beginning of the message beक्रमe
	 * निश्चितing cs. But the current spi API करोesn't support this, so we
	 * end up with an extra unnecessary (but harmless) cs निश्चितion and
	 * deनिश्चितion.
	 */
	wt_t->delay.value = SPI_RW_CHG_DELAY_US;
	wt_t->delay.unit = SPI_DELAY_UNIT_USECS;
	wt_t->cs_change = 1;

	dl_t->delay.value = applespi->spi_settings.spi_cs_delay;
	dl_t->delay.unit = SPI_DELAY_UNIT_USECS;

	wr_t->tx_buf = applespi->tx_buffer;
	wr_t->len = APPLESPI_PACKET_SIZE;
	wr_t->delay.value = SPI_RW_CHG_DELAY_US;
	wr_t->delay.unit = SPI_DELAY_UNIT_USECS;

	st_t->rx_buf = applespi->tx_status;
	st_t->len = APPLESPI_STATUS_SIZE;

	spi_message_init(msg);
	spi_message_add_tail(wt_t, msg);
	spi_message_add_tail(dl_t, msg);
	spi_message_add_tail(wr_t, msg);
	spi_message_add_tail(st_t, msg);
पूर्ण

अटल पूर्णांक applespi_async(काष्ठा applespi_data *applespi,
			  काष्ठा spi_message *message, व्योम (*complete)(व्योम *))
अणु
	message->complete = complete;
	message->context = applespi;

	वापस spi_async(applespi->spi, message);
पूर्ण

अटल अंतरभूत bool applespi_check_ग_लिखो_status(काष्ठा applespi_data *applespi,
					       पूर्णांक sts)
अणु
	अटल u8 status_ok[] = अणु 0xac, 0x27, 0x68, 0xd5 पूर्ण;

	अगर (sts < 0) अणु
		dev_warn(&applespi->spi->dev, "Error writing to device: %d\n",
			 sts);
		वापस false;
	पूर्ण

	अगर (स_भेद(applespi->tx_status, status_ok, APPLESPI_STATUS_SIZE)) अणु
		dev_warn(&applespi->spi->dev, "Error writing to device: %*ph\n",
			 APPLESPI_STATUS_SIZE, applespi->tx_status);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक applespi_get_spi_settings(काष्ठा applespi_data *applespi)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&applespi->spi->dev);
	स्थिर जोड़ acpi_object *o;
	काष्ठा spi_settings *settings = &applespi->spi_settings;

	अगर (!acpi_dev_get_property(adev, "spiCSDelay", ACPI_TYPE_BUFFER, &o))
		settings->spi_cs_delay = *(u64 *)o->buffer.poपूर्णांकer;
	अन्यथा
		dev_warn(&applespi->spi->dev,
			 "Property spiCSDelay not found\n");

	अगर (!acpi_dev_get_property(adev, "resetA2RUsec", ACPI_TYPE_BUFFER, &o))
		settings->reset_a2r_usec = *(u64 *)o->buffer.poपूर्णांकer;
	अन्यथा
		dev_warn(&applespi->spi->dev,
			 "Property resetA2RUsec not found\n");

	अगर (!acpi_dev_get_property(adev, "resetRecUsec", ACPI_TYPE_BUFFER, &o))
		settings->reset_rec_usec = *(u64 *)o->buffer.poपूर्णांकer;
	अन्यथा
		dev_warn(&applespi->spi->dev,
			 "Property resetRecUsec not found\n");

	dev_dbg(&applespi->spi->dev,
		"SPI settings: spi_cs_delay=%llu reset_a2r_usec=%llu reset_rec_usec=%llu\n",
		settings->spi_cs_delay, settings->reset_a2r_usec,
		settings->reset_rec_usec);

	वापस 0;
पूर्ण

अटल पूर्णांक applespi_setup_spi(काष्ठा applespi_data *applespi)
अणु
	पूर्णांक sts;

	sts = applespi_get_spi_settings(applespi);
	अगर (sts)
		वापस sts;

	spin_lock_init(&applespi->cmd_msg_lock);
	init_रुकोqueue_head(&applespi->drain_complete);

	वापस 0;
पूर्ण

अटल पूर्णांक applespi_enable_spi(काष्ठा applespi_data *applespi)
अणु
	acpi_status acpi_sts;
	अचिन्हित दीर्घ दीर्घ spi_status;

	/* check अगर SPI is alपढ़ोy enabled, so we can skip the delay below */
	acpi_sts = acpi_evaluate_पूर्णांकeger(applespi->sist, शून्य, शून्य,
					 &spi_status);
	अगर (ACPI_SUCCESS(acpi_sts) && spi_status)
		वापस 0;

	/* SIEN(1) will enable SPI communication */
	acpi_sts = acpi_execute_simple_method(applespi->sien, शून्य, 1);
	अगर (ACPI_FAILURE(acpi_sts)) अणु
		dev_err(&applespi->spi->dev, "SIEN failed: %s\n",
			acpi_क्रमmat_exception(acpi_sts));
		वापस -ENODEV;
	पूर्ण

	/*
	 * Allow the SPI पूर्णांकerface to come up beक्रमe वापसing. Without this
	 * delay, the SPI commands to enable multitouch mode may not reach
	 * the trackpad controller, causing poपूर्णांकer movement to अवरोध upon
	 * resume from sleep.
	 */
	msleep(50);

	वापस 0;
पूर्ण

अटल पूर्णांक applespi_send_cmd_msg(काष्ठा applespi_data *applespi);

अटल व्योम applespi_msg_complete(काष्ठा applespi_data *applespi,
				  bool is_ग_लिखो_msg, bool is_पढ़ो_compl)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&applespi->cmd_msg_lock, flags);

	अगर (is_पढ़ो_compl)
		applespi->पढ़ो_active = false;
	अगर (is_ग_लिखो_msg)
		applespi->ग_लिखो_active = false;

	अगर (applespi->drain && !applespi->ग_लिखो_active)
		wake_up_all(&applespi->drain_complete);

	अगर (is_ग_लिखो_msg) अणु
		applespi->cmd_msg_queued = 0;
		applespi_send_cmd_msg(applespi);
	पूर्ण

	spin_unlock_irqrestore(&applespi->cmd_msg_lock, flags);
पूर्ण

अटल व्योम applespi_async_ग_लिखो_complete(व्योम *context)
अणु
	काष्ठा applespi_data *applespi = context;
	क्रमागत applespi_evt_type evt_type = applespi->cmd_evt_type;

	applespi_get_trace_fun(evt_type)(evt_type, PT_WRITE,
					 applespi->tx_buffer,
					 APPLESPI_PACKET_SIZE);
	applespi_get_trace_fun(evt_type)(evt_type, PT_STATUS,
					 applespi->tx_status,
					 APPLESPI_STATUS_SIZE);

	udelay(SPI_RW_CHG_DELAY_US);

	अगर (!applespi_check_ग_लिखो_status(applespi, applespi->wr_m.status)) अणु
		/*
		 * If we got an error, we presumably won't get the expected
		 * response message either.
		 */
		applespi_msg_complete(applespi, true, false);
	पूर्ण
पूर्ण

अटल पूर्णांक applespi_send_cmd_msg(काष्ठा applespi_data *applespi)
अणु
	u16 crc;
	पूर्णांक sts;
	काष्ठा spi_packet *packet = (काष्ठा spi_packet *)applespi->tx_buffer;
	काष्ठा message *message = (काष्ठा message *)packet->data;
	u16 msg_len;
	u8 device;

	/* check अगर draining */
	अगर (applespi->drain)
		वापस 0;

	/* check whether send is in progress */
	अगर (applespi->cmd_msg_queued) अणु
		अगर (kसमय_ms_delta(kसमय_get(), applespi->cmd_msg_queued) < 1000)
			वापस 0;

		dev_warn(&applespi->spi->dev, "Command %d timed out\n",
			 applespi->cmd_evt_type);

		applespi->cmd_msg_queued = 0;
		applespi->ग_लिखो_active = false;
	पूर्ण

	/* set up packet */
	स_रखो(packet, 0, APPLESPI_PACKET_SIZE);

	/* are we processing init commands? */
	अगर (applespi->want_tp_info_cmd) अणु
		applespi->want_tp_info_cmd = false;
		applespi->want_mt_init_cmd = true;
		applespi->cmd_evt_type = ET_CMD_TP_INI;

		/* build init command */
		device = PACKET_DEV_INFO;

		message->type = cpu_to_le16(0x1020);
		msg_len = माप(message->tp_info_command);

		message->zero = 0x02;
		message->rsp_buf_len = cpu_to_le16(0x0200);

	पूर्ण अन्यथा अगर (applespi->want_mt_init_cmd) अणु
		applespi->want_mt_init_cmd = false;
		applespi->cmd_evt_type = ET_CMD_TP_INI;

		/* build init command */
		device = PACKET_DEV_TPAD;

		message->type = cpu_to_le16(0x0252);
		msg_len = माप(message->init_mt_command);

		message->init_mt_command.cmd = cpu_to_le16(0x0102);

	/* करो we need caps-lock command? */
	पूर्ण अन्यथा अगर (applespi->want_cl_led_on != applespi->have_cl_led_on) अणु
		applespi->have_cl_led_on = applespi->want_cl_led_on;
		applespi->cmd_evt_type = ET_CMD_CL;

		/* build led command */
		device = PACKET_DEV_KEYB;

		message->type = cpu_to_le16(0x0151);
		msg_len = माप(message->capsl_command);

		message->capsl_command.unknown = 0x01;
		message->capsl_command.led = applespi->have_cl_led_on ? 2 : 0;

	/* करो we need backlight command? */
	पूर्ण अन्यथा अगर (applespi->want_bl_level != applespi->have_bl_level) अणु
		applespi->have_bl_level = applespi->want_bl_level;
		applespi->cmd_evt_type = ET_CMD_BL;

		/* build command buffer */
		device = PACKET_DEV_KEYB;

		message->type = cpu_to_le16(0xB051);
		msg_len = माप(message->bl_command);

		message->bl_command.स्थिर1 = cpu_to_le16(0x01B0);
		message->bl_command.level =
				cpu_to_le16(applespi->have_bl_level);

		अगर (applespi->have_bl_level > 0)
			message->bl_command.स्थिर2 = cpu_to_le16(0x01F4);
		अन्यथा
			message->bl_command.स्थिर2 = cpu_to_le16(0x0001);

	/* everything's up-to-date */
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	/* finalize packet */
	packet->flags = PACKET_TYPE_WRITE;
	packet->device = device;
	packet->length = cpu_to_le16(MSG_HEADER_SIZE + msg_len);

	message->counter = applespi->cmd_msg_cntr++ % (U8_MAX + 1);

	message->length = cpu_to_le16(msg_len - 2);
	अगर (!message->rsp_buf_len)
		message->rsp_buf_len = message->length;

	crc = crc16(0, (u8 *)message, le16_to_cpu(packet->length) - 2);
	put_unaligned_le16(crc, &message->data[msg_len - 2]);

	crc = crc16(0, (u8 *)packet, माप(*packet) - 2);
	packet->crc16 = cpu_to_le16(crc);

	/* send command */
	sts = applespi_async(applespi, &applespi->wr_m,
			     applespi_async_ग_लिखो_complete);
	अगर (sts) अणु
		dev_warn(&applespi->spi->dev,
			 "Error queueing async write to device: %d\n", sts);
		वापस sts;
	पूर्ण

	applespi->cmd_msg_queued = kसमय_get_coarse();
	applespi->ग_लिखो_active = true;

	वापस 0;
पूर्ण

अटल व्योम applespi_init(काष्ठा applespi_data *applespi, bool is_resume)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&applespi->cmd_msg_lock, flags);

	अगर (is_resume)
		applespi->want_mt_init_cmd = true;
	अन्यथा
		applespi->want_tp_info_cmd = true;
	applespi_send_cmd_msg(applespi);

	spin_unlock_irqrestore(&applespi->cmd_msg_lock, flags);
पूर्ण

अटल पूर्णांक applespi_set_capsl_led(काष्ठा applespi_data *applespi,
				  bool capslock_on)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक sts;

	spin_lock_irqsave(&applespi->cmd_msg_lock, flags);

	applespi->want_cl_led_on = capslock_on;
	sts = applespi_send_cmd_msg(applespi);

	spin_unlock_irqrestore(&applespi->cmd_msg_lock, flags);

	वापस sts;
पूर्ण

अटल व्योम applespi_set_bl_level(काष्ठा led_classdev *led_cdev,
				  क्रमागत led_brightness value)
अणु
	काष्ठा applespi_data *applespi =
		container_of(led_cdev, काष्ठा applespi_data, backlight_info);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&applespi->cmd_msg_lock, flags);

	अगर (value == 0) अणु
		applespi->want_bl_level = value;
	पूर्ण अन्यथा अणु
		/*
		 * The backlight करोes not turn on till level 32, so we scale
		 * the range here so that from a user's perspective it turns
		 * on at 1.
		 */
		applespi->want_bl_level =
			((value * KBD_BL_LEVEL_ADJ) / KBD_BL_LEVEL_SCALE +
			 KBD_BL_LEVEL_MIN);
	पूर्ण

	applespi_send_cmd_msg(applespi);

	spin_unlock_irqrestore(&applespi->cmd_msg_lock, flags);
पूर्ण

अटल पूर्णांक applespi_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
			  अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा applespi_data *applespi = input_get_drvdata(dev);

	चयन (type) अणु
	हाल EV_LED:
		applespi_set_capsl_led(applespi, !!test_bit(LED_CAPSL, dev->led));
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* lअगरted from the BCM5974 driver and नामd from raw2पूर्णांक */
/* convert 16-bit little endian to चिन्हित पूर्णांकeger */
अटल अंतरभूत पूर्णांक le16_to_पूर्णांक(__le16 x)
अणु
	वापस (चिन्हित लघु)le16_to_cpu(x);
पूर्ण

अटल व्योम applespi_debug_update_dimensions(काष्ठा applespi_data *applespi,
					     स्थिर काष्ठा tp_finger *f)
अणु
	applespi->tp_dim_min_x = min(applespi->tp_dim_min_x,
				     le16_to_पूर्णांक(f->असल_x));
	applespi->tp_dim_max_x = max(applespi->tp_dim_max_x,
				     le16_to_पूर्णांक(f->असल_x));
	applespi->tp_dim_min_y = min(applespi->tp_dim_min_y,
				     le16_to_पूर्णांक(f->असल_y));
	applespi->tp_dim_max_y = max(applespi->tp_dim_max_y,
				     le16_to_पूर्णांक(f->असल_y));
पूर्ण

अटल पूर्णांक applespi_tp_dim_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा applespi_data *applespi = inode->i_निजी;

	file->निजी_data = applespi;

	snम_लिखो(applespi->tp_dim_val, माप(applespi->tp_dim_val),
		 "0x%.4x %dx%d+%u+%u\n",
		 applespi->touchpad_input_dev->id.product,
		 applespi->tp_dim_min_x, applespi->tp_dim_min_y,
		 applespi->tp_dim_max_x - applespi->tp_dim_min_x,
		 applespi->tp_dim_max_y - applespi->tp_dim_min_y);

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल sमाप_प्रकार applespi_tp_dim_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				    माप_प्रकार len, loff_t *off)
अणु
	काष्ठा applespi_data *applespi = file->निजी_data;

	वापस simple_पढ़ो_from_buffer(buf, len, off, applespi->tp_dim_val,
				       म_माप(applespi->tp_dim_val));
पूर्ण

अटल स्थिर काष्ठा file_operations applespi_tp_dim_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = applespi_tp_dim_खोलो,
	.पढ़ो = applespi_tp_dim_पढ़ो,
	.llseek = no_llseek,
पूर्ण;

अटल व्योम report_finger_data(काष्ठा input_dev *input, पूर्णांक slot,
			       स्थिर काष्ठा input_mt_pos *pos,
			       स्थिर काष्ठा tp_finger *f)
अणु
	input_mt_slot(input, slot);
	input_mt_report_slot_state(input, MT_TOOL_FINGER, true);

	input_report_असल(input, ABS_MT_TOUCH_MAJOR,
			 le16_to_पूर्णांक(f->touch_major) << 1);
	input_report_असल(input, ABS_MT_TOUCH_MINOR,
			 le16_to_पूर्णांक(f->touch_minor) << 1);
	input_report_असल(input, ABS_MT_WIDTH_MAJOR,
			 le16_to_पूर्णांक(f->tool_major) << 1);
	input_report_असल(input, ABS_MT_WIDTH_MINOR,
			 le16_to_पूर्णांक(f->tool_minor) << 1);
	input_report_असल(input, ABS_MT_ORIENTATION,
			 MAX_FINGER_ORIENTATION - le16_to_पूर्णांक(f->orientation));
	input_report_असल(input, ABS_MT_POSITION_X, pos->x);
	input_report_असल(input, ABS_MT_POSITION_Y, pos->y);
पूर्ण

अटल व्योम report_tp_state(काष्ठा applespi_data *applespi,
			    काष्ठा touchpad_protocol *t)
अणु
	स्थिर काष्ठा tp_finger *f;
	काष्ठा input_dev *input;
	स्थिर काष्ठा applespi_tp_info *tp_info = &applespi->tp_info;
	पूर्णांक i, n;

	/* touchpad_input_dev is set async in worker */
	input = smp_load_acquire(&applespi->touchpad_input_dev);
	अगर (!input)
		वापस;	/* touchpad isn't initialized yet */

	n = 0;

	क्रम (i = 0; i < t->number_of_fingers; i++) अणु
		f = &t->fingers[i];
		अगर (le16_to_पूर्णांक(f->touch_major) == 0)
			जारी;
		applespi->pos[n].x = le16_to_पूर्णांक(f->असल_x);
		applespi->pos[n].y = tp_info->y_min + tp_info->y_max -
				     le16_to_पूर्णांक(f->असल_y);
		n++;

		अगर (applespi->debug_tp_dim)
			applespi_debug_update_dimensions(applespi, f);
	पूर्ण

	input_mt_assign_slots(input, applespi->slots, applespi->pos, n, 0);

	क्रम (i = 0; i < n; i++)
		report_finger_data(input, applespi->slots[i],
				   &applespi->pos[i], &t->fingers[i]);

	input_mt_sync_frame(input);
	input_report_key(input, BTN_LEFT, t->clicked);

	input_sync(input);
पूर्ण

अटल स्थिर काष्ठा applespi_key_translation *
applespi_find_translation(स्थिर काष्ठा applespi_key_translation *table, u16 key)
अणु
	स्थिर काष्ठा applespi_key_translation *trans;

	क्रम (trans = table; trans->from; trans++)
		अगर (trans->from == key)
			वापस trans;

	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक applespi_translate_fn_key(अचिन्हित पूर्णांक key, पूर्णांक fn_pressed)
अणु
	स्थिर काष्ठा applespi_key_translation *trans;
	पूर्णांक करो_translate;

	trans = applespi_find_translation(applespi_fn_codes, key);
	अगर (trans) अणु
		अगर (trans->flags & APPLE_FLAG_FKEY)
			करो_translate = (fnmode == 2 && fn_pressed) ||
				       (fnmode == 1 && !fn_pressed);
		अन्यथा
			करो_translate = fn_pressed;

		अगर (करो_translate)
			key = trans->to;
	पूर्ण

	वापस key;
पूर्ण

अटल अचिन्हित पूर्णांक applespi_translate_iso_layout(अचिन्हित पूर्णांक key)
अणु
	स्थिर काष्ठा applespi_key_translation *trans;

	trans = applespi_find_translation(apple_iso_keyboard, key);
	अगर (trans)
		key = trans->to;

	वापस key;
पूर्ण

अटल अचिन्हित पूर्णांक applespi_code_to_key(u8 code, पूर्णांक fn_pressed)
अणु
	अचिन्हित पूर्णांक key = applespi_scancodes[code];

	अगर (fnmode)
		key = applespi_translate_fn_key(key, fn_pressed);
	अगर (iso_layout)
		key = applespi_translate_iso_layout(key);
	वापस key;
पूर्ण

अटल व्योम
applespi_remap_fn_key(काष्ठा keyboard_protocol *keyboard_protocol)
अणु
	अचिन्हित अक्षर पंचांगp;
	u8 bit = BIT((fnremap - 1) & 0x07);

	अगर (!fnremap || fnremap > ARRAY_SIZE(applespi_controlcodes) ||
	    !applespi_controlcodes[fnremap - 1])
		वापस;

	पंचांगp = keyboard_protocol->fn_pressed;
	keyboard_protocol->fn_pressed = !!(keyboard_protocol->modअगरiers & bit);
	अगर (पंचांगp)
		keyboard_protocol->modअगरiers |= bit;
	अन्यथा
		keyboard_protocol->modअगरiers &= ~bit;
पूर्ण

अटल व्योम
applespi_handle_keyboard_event(काष्ठा applespi_data *applespi,
			       काष्ठा keyboard_protocol *keyboard_protocol)
अणु
	अचिन्हित पूर्णांक key;
	पूर्णांक i;

	compileसमय_निश्चित(ARRAY_SIZE(applespi_controlcodes) ==
			   माप_field(काष्ठा keyboard_protocol, modअगरiers) * 8,
			   "applespi_controlcodes has wrong number of entries");

	/* check क्रम rollover overflow, which is संकेतled by all keys == 1 */
	अगर (!स_प्रथम_inv(keyboard_protocol->keys_pressed, 1, MAX_ROLLOVER))
		वापस;

	/* remap fn key अगर desired */
	applespi_remap_fn_key(keyboard_protocol);

	/* check released keys */
	क्रम (i = 0; i < MAX_ROLLOVER; i++) अणु
		अगर (स_प्रथम(keyboard_protocol->keys_pressed,
			   applespi->last_keys_pressed[i], MAX_ROLLOVER))
			जारी;	/* key is still pressed */

		key = applespi_code_to_key(applespi->last_keys_pressed[i],
					   applespi->last_keys_fn_pressed[i]);
		input_report_key(applespi->keyboard_input_dev, key, 0);
		applespi->last_keys_fn_pressed[i] = 0;
	पूर्ण

	/* check pressed keys */
	क्रम (i = 0; i < MAX_ROLLOVER; i++) अणु
		अगर (keyboard_protocol->keys_pressed[i] <
				ARRAY_SIZE(applespi_scancodes) &&
		    keyboard_protocol->keys_pressed[i] > 0) अणु
			key = applespi_code_to_key(
					keyboard_protocol->keys_pressed[i],
					keyboard_protocol->fn_pressed);
			input_report_key(applespi->keyboard_input_dev, key, 1);
			applespi->last_keys_fn_pressed[i] =
					keyboard_protocol->fn_pressed;
		पूर्ण
	पूर्ण

	/* check control keys */
	क्रम (i = 0; i < ARRAY_SIZE(applespi_controlcodes); i++) अणु
		अगर (keyboard_protocol->modअगरiers & BIT(i))
			input_report_key(applespi->keyboard_input_dev,
					 applespi_controlcodes[i], 1);
		अन्यथा
			input_report_key(applespi->keyboard_input_dev,
					 applespi_controlcodes[i], 0);
	पूर्ण

	/* check function key */
	अगर (keyboard_protocol->fn_pressed && !applespi->last_fn_pressed)
		input_report_key(applespi->keyboard_input_dev, KEY_FN, 1);
	अन्यथा अगर (!keyboard_protocol->fn_pressed && applespi->last_fn_pressed)
		input_report_key(applespi->keyboard_input_dev, KEY_FN, 0);
	applespi->last_fn_pressed = keyboard_protocol->fn_pressed;

	/* करोne */
	input_sync(applespi->keyboard_input_dev);
	स_नकल(&applespi->last_keys_pressed, keyboard_protocol->keys_pressed,
	       माप(applespi->last_keys_pressed));
पूर्ण

अटल स्थिर काष्ठा applespi_tp_info *applespi_find_touchpad_info(u8 model)
अणु
	स्थिर काष्ठा applespi_tp_model_info *info;

	क्रम (info = applespi_tp_models; info->model; info++) अणु
		अगर (info->model == model)
			वापस &info->tp_info;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक
applespi_रेजिस्टर_touchpad_device(काष्ठा applespi_data *applespi,
				  काष्ठा touchpad_info_protocol *rcvd_tp_info)
अणु
	स्थिर काष्ठा applespi_tp_info *tp_info;
	काष्ठा input_dev *touchpad_input_dev;
	पूर्णांक sts;

	/* set up touchpad dimensions */
	tp_info = applespi_find_touchpad_info(rcvd_tp_info->model_no);
	अगर (!tp_info) अणु
		dev_warn(&applespi->spi->dev,
			 "Unknown touchpad model %x - falling back to MB8 touchpad\n",
			 rcvd_tp_info->model_no);
		tp_info = &applespi_tp_models[0].tp_info;
	पूर्ण

	applespi->tp_info = *tp_info;

	अगर (touchpad_dimensions[0]) अणु
		पूर्णांक x, y, w, h;

		sts = माला_पूछो(touchpad_dimensions, "%dx%d+%u+%u", &x, &y, &w, &h);
		अगर (sts == 4) अणु
			dev_info(&applespi->spi->dev,
				 "Overriding touchpad dimensions from module param\n");
			applespi->tp_info.x_min = x;
			applespi->tp_info.y_min = y;
			applespi->tp_info.x_max = x + w;
			applespi->tp_info.y_max = y + h;
		पूर्ण अन्यथा अणु
			dev_warn(&applespi->spi->dev,
				 "Invalid touchpad dimensions '%s': must be in the form XxY+W+H\n",
				 touchpad_dimensions);
			touchpad_dimensions[0] = '\0';
		पूर्ण
	पूर्ण
	अगर (!touchpad_dimensions[0]) अणु
		snम_लिखो(touchpad_dimensions, माप(touchpad_dimensions),
			 "%dx%d+%u+%u",
			 applespi->tp_info.x_min,
			 applespi->tp_info.y_min,
			 applespi->tp_info.x_max - applespi->tp_info.x_min,
			 applespi->tp_info.y_max - applespi->tp_info.y_min);
	पूर्ण

	/* create touchpad input device */
	touchpad_input_dev = devm_input_allocate_device(&applespi->spi->dev);
	अगर (!touchpad_input_dev) अणु
		dev_err(&applespi->spi->dev,
			"Failed to allocate touchpad input device\n");
		वापस -ENOMEM;
	पूर्ण

	touchpad_input_dev->name = "Apple SPI Touchpad";
	touchpad_input_dev->phys = "applespi/input1";
	touchpad_input_dev->dev.parent = &applespi->spi->dev;
	touchpad_input_dev->id.bustype = BUS_SPI;
	touchpad_input_dev->id.venकरोr = SYNAPTICS_VENDOR_ID;
	touchpad_input_dev->id.product =
			rcvd_tp_info->model_no << 8 | rcvd_tp_info->model_flags;

	/* basic properties */
	input_set_capability(touchpad_input_dev, EV_REL, REL_X);
	input_set_capability(touchpad_input_dev, EV_REL, REL_Y);

	__set_bit(INPUT_PROP_POINTER, touchpad_input_dev->propbit);
	__set_bit(INPUT_PROP_BUTTONPAD, touchpad_input_dev->propbit);

	/* finger touch area */
	input_set_असल_params(touchpad_input_dev, ABS_MT_TOUCH_MAJOR,
			     0, 5000, 0, 0);
	input_set_असल_params(touchpad_input_dev, ABS_MT_TOUCH_MINOR,
			     0, 5000, 0, 0);

	/* finger approach area */
	input_set_असल_params(touchpad_input_dev, ABS_MT_WIDTH_MAJOR,
			     0, 5000, 0, 0);
	input_set_असल_params(touchpad_input_dev, ABS_MT_WIDTH_MINOR,
			     0, 5000, 0, 0);

	/* finger orientation */
	input_set_असल_params(touchpad_input_dev, ABS_MT_ORIENTATION,
			     -MAX_FINGER_ORIENTATION, MAX_FINGER_ORIENTATION,
			     0, 0);

	/* finger position */
	input_set_असल_params(touchpad_input_dev, ABS_MT_POSITION_X,
			     applespi->tp_info.x_min, applespi->tp_info.x_max,
			     0, 0);
	input_set_असल_params(touchpad_input_dev, ABS_MT_POSITION_Y,
			     applespi->tp_info.y_min, applespi->tp_info.y_max,
			     0, 0);

	/* touchpad button */
	input_set_capability(touchpad_input_dev, EV_KEY, BTN_LEFT);

	/* multitouch */
	sts = input_mt_init_slots(touchpad_input_dev, MAX_FINGERS,
				  INPUT_MT_POINTER | INPUT_MT_DROP_UNUSED |
					INPUT_MT_TRACK);
	अगर (sts) अणु
		dev_err(&applespi->spi->dev,
			"failed to initialize slots: %d", sts);
		वापस sts;
	पूर्ण

	/* रेजिस्टर input device */
	sts = input_रेजिस्टर_device(touchpad_input_dev);
	अगर (sts) अणु
		dev_err(&applespi->spi->dev,
			"Unable to register touchpad input device (%d)\n", sts);
		वापस sts;
	पूर्ण

	/* touchpad_input_dev is पढ़ो async in spi callback */
	smp_store_release(&applespi->touchpad_input_dev, touchpad_input_dev);

	वापस 0;
पूर्ण

अटल व्योम applespi_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा applespi_data *applespi =
		container_of(work, काष्ठा applespi_data, work);

	applespi_रेजिस्टर_touchpad_device(applespi, &applespi->rcvd_tp_info);
पूर्ण

अटल व्योम applespi_handle_cmd_response(काष्ठा applespi_data *applespi,
					 काष्ठा spi_packet *packet,
					 काष्ठा message *message)
अणु
	अगर (packet->device == PACKET_DEV_INFO &&
	    le16_to_cpu(message->type) == 0x1020) अणु
		/*
		 * We're not allowed to sleep here, but रेजिस्टरing an input
		 * device can sleep.
		 */
		applespi->rcvd_tp_info = message->tp_info;
		schedule_work(&applespi->work);
		वापस;
	पूर्ण

	अगर (le16_to_cpu(message->length) != 0x0000) अणु
		dev_warn_ratelimited(&applespi->spi->dev,
				     "Received unexpected write response: length=%x\n",
				     le16_to_cpu(message->length));
		वापस;
	पूर्ण

	अगर (packet->device == PACKET_DEV_TPAD &&
	    le16_to_cpu(message->type) == 0x0252 &&
	    le16_to_cpu(message->rsp_buf_len) == 0x0002)
		dev_info(&applespi->spi->dev, "modeswitch done.\n");
पूर्ण

अटल bool applespi_verअगरy_crc(काष्ठा applespi_data *applespi, u8 *buffer,
				माप_प्रकार buflen)
अणु
	u16 crc;

	crc = crc16(0, buffer, buflen);
	अगर (crc) अणु
		dev_warn_ratelimited(&applespi->spi->dev,
				     "Received corrupted packet (crc mismatch)\n");
		trace_applespi_bad_crc(ET_RD_CRC, READ, buffer, buflen);

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम applespi_debug_prपूर्णांक_पढ़ो_packet(काष्ठा applespi_data *applespi,
					     काष्ठा spi_packet *packet)
अणु
	अचिन्हित पूर्णांक evt_type;

	अगर (packet->flags == PACKET_TYPE_READ &&
	    packet->device == PACKET_DEV_KEYB)
		evt_type = ET_RD_KEYB;
	अन्यथा अगर (packet->flags == PACKET_TYPE_READ &&
		 packet->device == PACKET_DEV_TPAD)
		evt_type = ET_RD_TPAD;
	अन्यथा अगर (packet->flags == PACKET_TYPE_WRITE)
		evt_type = applespi->cmd_evt_type;
	अन्यथा
		evt_type = ET_RD_UNKN;

	applespi_get_trace_fun(evt_type)(evt_type, PT_READ, applespi->rx_buffer,
					 APPLESPI_PACKET_SIZE);
पूर्ण

अटल व्योम applespi_got_data(काष्ठा applespi_data *applespi)
अणु
	काष्ठा spi_packet *packet;
	काष्ठा message *message;
	अचिन्हित पूर्णांक msg_len;
	अचिन्हित पूर्णांक off;
	अचिन्हित पूर्णांक rem;
	अचिन्हित पूर्णांक len;

	/* process packet header */
	अगर (!applespi_verअगरy_crc(applespi, applespi->rx_buffer,
				 APPLESPI_PACKET_SIZE)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&applespi->cmd_msg_lock, flags);

		अगर (applespi->drain) अणु
			applespi->पढ़ो_active = false;
			applespi->ग_लिखो_active = false;

			wake_up_all(&applespi->drain_complete);
		पूर्ण

		spin_unlock_irqrestore(&applespi->cmd_msg_lock, flags);

		वापस;
	पूर्ण

	packet = (काष्ठा spi_packet *)applespi->rx_buffer;

	applespi_debug_prपूर्णांक_पढ़ो_packet(applespi, packet);

	off = le16_to_cpu(packet->offset);
	rem = le16_to_cpu(packet->reमुख्यing);
	len = le16_to_cpu(packet->length);

	अगर (len > माप(packet->data)) अणु
		dev_warn_ratelimited(&applespi->spi->dev,
				     "Received corrupted packet (invalid packet length %u)\n",
				     len);
		जाओ msg_complete;
	पूर्ण

	/* handle multi-packet messages */
	अगर (rem > 0 || off > 0) अणु
		अगर (off != applespi->saved_msg_len) अणु
			dev_warn_ratelimited(&applespi->spi->dev,
					     "Received unexpected offset (got %u, expected %u)\n",
					     off, applespi->saved_msg_len);
			जाओ msg_complete;
		पूर्ण

		अगर (off + rem > MAX_PKTS_PER_MSG * APPLESPI_PACKET_SIZE) अणु
			dev_warn_ratelimited(&applespi->spi->dev,
					     "Received message too large (size %u)\n",
					     off + rem);
			जाओ msg_complete;
		पूर्ण

		अगर (off + len > MAX_PKTS_PER_MSG * APPLESPI_PACKET_SIZE) अणु
			dev_warn_ratelimited(&applespi->spi->dev,
					     "Received message too large (size %u)\n",
					     off + len);
			जाओ msg_complete;
		पूर्ण

		स_नकल(applespi->msg_buf + off, &packet->data, len);
		applespi->saved_msg_len += len;

		अगर (rem > 0)
			वापस;

		message = (काष्ठा message *)applespi->msg_buf;
		msg_len = applespi->saved_msg_len;
	पूर्ण अन्यथा अणु
		message = (काष्ठा message *)&packet->data;
		msg_len = len;
	पूर्ण

	/* got complete message - verअगरy */
	अगर (!applespi_verअगरy_crc(applespi, (u8 *)message, msg_len))
		जाओ msg_complete;

	अगर (le16_to_cpu(message->length) != msg_len - MSG_HEADER_SIZE - 2) अणु
		dev_warn_ratelimited(&applespi->spi->dev,
				     "Received corrupted packet (invalid message length %u - expected %u)\n",
				     le16_to_cpu(message->length),
				     msg_len - MSG_HEADER_SIZE - 2);
		जाओ msg_complete;
	पूर्ण

	/* handle message */
	अगर (packet->flags == PACKET_TYPE_READ &&
	    packet->device == PACKET_DEV_KEYB) अणु
		applespi_handle_keyboard_event(applespi, &message->keyboard);

	पूर्ण अन्यथा अगर (packet->flags == PACKET_TYPE_READ &&
		   packet->device == PACKET_DEV_TPAD) अणु
		काष्ठा touchpad_protocol *tp;
		माप_प्रकार tp_len;

		tp = &message->touchpad;
		tp_len = काष्ठा_size(tp, fingers, tp->number_of_fingers);

		अगर (le16_to_cpu(message->length) + 2 != tp_len) अणु
			dev_warn_ratelimited(&applespi->spi->dev,
					     "Received corrupted packet (invalid message length %u - num-fingers %u, tp-len %zu)\n",
					     le16_to_cpu(message->length),
					     tp->number_of_fingers, tp_len);
			जाओ msg_complete;
		पूर्ण

		अगर (tp->number_of_fingers > MAX_FINGERS) अणु
			dev_warn_ratelimited(&applespi->spi->dev,
					     "Number of reported fingers (%u) exceeds max (%u))\n",
					     tp->number_of_fingers,
					     MAX_FINGERS);
			tp->number_of_fingers = MAX_FINGERS;
		पूर्ण

		report_tp_state(applespi, tp);

	पूर्ण अन्यथा अगर (packet->flags == PACKET_TYPE_WRITE) अणु
		applespi_handle_cmd_response(applespi, packet, message);
	पूर्ण

msg_complete:
	applespi->saved_msg_len = 0;

	applespi_msg_complete(applespi, packet->flags == PACKET_TYPE_WRITE,
			      true);
पूर्ण

अटल व्योम applespi_async_पढ़ो_complete(व्योम *context)
अणु
	काष्ठा applespi_data *applespi = context;

	अगर (applespi->rd_m.status < 0) अणु
		dev_warn(&applespi->spi->dev, "Error reading from device: %d\n",
			 applespi->rd_m.status);
		/*
		 * We करोn't actually know अगर this was a pure पढ़ो, or a response
		 * to a ग_लिखो. But this is a rare error condition that should
		 * never occur, so clearing both flags to aव्योम deadlock.
		 */
		applespi_msg_complete(applespi, true, true);
	पूर्ण अन्यथा अणु
		applespi_got_data(applespi);
	पूर्ण

	acpi_finish_gpe(शून्य, applespi->gpe);
पूर्ण

अटल u32 applespi_notअगरy(acpi_handle gpe_device, u32 gpe, व्योम *context)
अणु
	काष्ठा applespi_data *applespi = context;
	पूर्णांक sts;
	अचिन्हित दीर्घ flags;

	trace_applespi_irq_received(ET_RD_IRQ, PT_READ);

	spin_lock_irqsave(&applespi->cmd_msg_lock, flags);

	अगर (!applespi->suspended) अणु
		sts = applespi_async(applespi, &applespi->rd_m,
				     applespi_async_पढ़ो_complete);
		अगर (sts)
			dev_warn(&applespi->spi->dev,
				 "Error queueing async read to device: %d\n",
				 sts);
		अन्यथा
			applespi->पढ़ो_active = true;
	पूर्ण

	spin_unlock_irqrestore(&applespi->cmd_msg_lock, flags);

	वापस ACPI_INTERRUPT_HANDLED;
पूर्ण

अटल पूर्णांक applespi_get_saved_bl_level(काष्ठा applespi_data *applespi)
अणु
	काष्ठा efivar_entry *efivar_entry;
	u16 efi_data = 0;
	अचिन्हित दीर्घ efi_data_len;
	पूर्णांक sts;

	efivar_entry = kदो_स्मृति(माप(*efivar_entry), GFP_KERNEL);
	अगर (!efivar_entry)
		वापस -ENOMEM;

	स_नकल(efivar_entry->var.VariableName, EFI_BL_LEVEL_NAME,
	       माप(EFI_BL_LEVEL_NAME));
	efivar_entry->var.VenकरोrGuid = EFI_BL_LEVEL_GUID;
	efi_data_len = माप(efi_data);

	sts = efivar_entry_get(efivar_entry, शून्य, &efi_data_len, &efi_data);
	अगर (sts && sts != -ENOENT)
		dev_warn(&applespi->spi->dev,
			 "Error getting backlight level from EFI vars: %d\n",
			 sts);

	kमुक्त(efivar_entry);

	वापस sts ? sts : efi_data;
पूर्ण

अटल व्योम applespi_save_bl_level(काष्ठा applespi_data *applespi,
				   अचिन्हित पूर्णांक level)
अणु
	efi_guid_t efi_guid;
	u32 efi_attr;
	अचिन्हित दीर्घ efi_data_len;
	u16 efi_data;
	पूर्णांक sts;

	/* Save keyboard backlight level */
	efi_guid = EFI_BL_LEVEL_GUID;
	efi_data = (u16)level;
	efi_data_len = माप(efi_data);
	efi_attr = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS |
		   EFI_VARIABLE_RUNTIME_ACCESS;

	sts = efivar_entry_set_safe((efi_अक्षर16_t *)EFI_BL_LEVEL_NAME, efi_guid,
				    efi_attr, true, efi_data_len, &efi_data);
	अगर (sts)
		dev_warn(&applespi->spi->dev,
			 "Error saving backlight level to EFI vars: %d\n", sts);
पूर्ण

अटल पूर्णांक applespi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा applespi_data *applespi;
	acpi_handle spi_handle = ACPI_HANDLE(&spi->dev);
	acpi_status acpi_sts;
	पूर्णांक sts, i;
	अचिन्हित दीर्घ दीर्घ gpe, usb_status;

	/* check अगर the USB पूर्णांकerface is present and enabled alपढ़ोy */
	acpi_sts = acpi_evaluate_पूर्णांकeger(spi_handle, "UIST", शून्य, &usb_status);
	अगर (ACPI_SUCCESS(acpi_sts) && usb_status) अणु
		/* let the USB driver take over instead */
		dev_info(&spi->dev, "USB interface already enabled\n");
		वापस -ENODEV;
	पूर्ण

	/* allocate driver data */
	applespi = devm_kzalloc(&spi->dev, माप(*applespi), GFP_KERNEL);
	अगर (!applespi)
		वापस -ENOMEM;

	applespi->spi = spi;

	INIT_WORK(&applespi->work, applespi_worker);

	/* store the driver data */
	spi_set_drvdata(spi, applespi);

	/* create our buffers */
	applespi->tx_buffer = devm_kदो_स्मृति(&spi->dev, APPLESPI_PACKET_SIZE,
					   GFP_KERNEL);
	applespi->tx_status = devm_kदो_स्मृति(&spi->dev, APPLESPI_STATUS_SIZE,
					   GFP_KERNEL);
	applespi->rx_buffer = devm_kदो_स्मृति(&spi->dev, APPLESPI_PACKET_SIZE,
					   GFP_KERNEL);
	applespi->msg_buf = devm_kदो_स्मृति_array(&spi->dev, MAX_PKTS_PER_MSG,
					       APPLESPI_PACKET_SIZE,
					       GFP_KERNEL);

	अगर (!applespi->tx_buffer || !applespi->tx_status ||
	    !applespi->rx_buffer || !applespi->msg_buf)
		वापस -ENOMEM;

	/* set up our spi messages */
	applespi_setup_पढ़ो_txfrs(applespi);
	applespi_setup_ग_लिखो_txfrs(applespi);

	/* cache ACPI method handles */
	acpi_sts = acpi_get_handle(spi_handle, "SIEN", &applespi->sien);
	अगर (ACPI_FAILURE(acpi_sts)) अणु
		dev_err(&applespi->spi->dev,
			"Failed to get SIEN ACPI method handle: %s\n",
			acpi_क्रमmat_exception(acpi_sts));
		वापस -ENODEV;
	पूर्ण

	acpi_sts = acpi_get_handle(spi_handle, "SIST", &applespi->sist);
	अगर (ACPI_FAILURE(acpi_sts)) अणु
		dev_err(&applespi->spi->dev,
			"Failed to get SIST ACPI method handle: %s\n",
			acpi_क्रमmat_exception(acpi_sts));
		वापस -ENODEV;
	पूर्ण

	/* चयन on the SPI पूर्णांकerface */
	sts = applespi_setup_spi(applespi);
	अगर (sts)
		वापस sts;

	sts = applespi_enable_spi(applespi);
	अगर (sts)
		वापस sts;

	/* setup the keyboard input dev */
	applespi->keyboard_input_dev = devm_input_allocate_device(&spi->dev);

	अगर (!applespi->keyboard_input_dev)
		वापस -ENOMEM;

	applespi->keyboard_input_dev->name = "Apple SPI Keyboard";
	applespi->keyboard_input_dev->phys = "applespi/input0";
	applespi->keyboard_input_dev->dev.parent = &spi->dev;
	applespi->keyboard_input_dev->id.bustype = BUS_SPI;

	applespi->keyboard_input_dev->evbit[0] =
			BIT_MASK(EV_KEY) | BIT_MASK(EV_LED) | BIT_MASK(EV_REP);
	applespi->keyboard_input_dev->ledbit[0] = BIT_MASK(LED_CAPSL);

	input_set_drvdata(applespi->keyboard_input_dev, applespi);
	applespi->keyboard_input_dev->event = applespi_event;

	क्रम (i = 0; i < ARRAY_SIZE(applespi_scancodes); i++)
		अगर (applespi_scancodes[i])
			input_set_capability(applespi->keyboard_input_dev,
					     EV_KEY, applespi_scancodes[i]);

	क्रम (i = 0; i < ARRAY_SIZE(applespi_controlcodes); i++)
		अगर (applespi_controlcodes[i])
			input_set_capability(applespi->keyboard_input_dev,
					     EV_KEY, applespi_controlcodes[i]);

	क्रम (i = 0; i < ARRAY_SIZE(applespi_fn_codes); i++)
		अगर (applespi_fn_codes[i].to)
			input_set_capability(applespi->keyboard_input_dev,
					     EV_KEY, applespi_fn_codes[i].to);

	input_set_capability(applespi->keyboard_input_dev, EV_KEY, KEY_FN);

	sts = input_रेजिस्टर_device(applespi->keyboard_input_dev);
	अगर (sts) अणु
		dev_err(&applespi->spi->dev,
			"Unable to register keyboard input device (%d)\n", sts);
		वापस -ENODEV;
	पूर्ण

	/*
	 * The applespi device करोesn't send पूर्णांकerrupts normally (as is described
	 * in its DSDT), but rather seems to use ACPI GPEs.
	 */
	acpi_sts = acpi_evaluate_पूर्णांकeger(spi_handle, "_GPE", शून्य, &gpe);
	अगर (ACPI_FAILURE(acpi_sts)) अणु
		dev_err(&applespi->spi->dev,
			"Failed to obtain GPE for SPI slave device: %s\n",
			acpi_क्रमmat_exception(acpi_sts));
		वापस -ENODEV;
	पूर्ण
	applespi->gpe = (पूर्णांक)gpe;

	acpi_sts = acpi_install_gpe_handler(शून्य, applespi->gpe,
					    ACPI_GPE_LEVEL_TRIGGERED,
					    applespi_notअगरy, applespi);
	अगर (ACPI_FAILURE(acpi_sts)) अणु
		dev_err(&applespi->spi->dev,
			"Failed to install GPE handler for GPE %d: %s\n",
			applespi->gpe, acpi_क्रमmat_exception(acpi_sts));
		वापस -ENODEV;
	पूर्ण

	applespi->suspended = false;

	acpi_sts = acpi_enable_gpe(शून्य, applespi->gpe);
	अगर (ACPI_FAILURE(acpi_sts)) अणु
		dev_err(&applespi->spi->dev,
			"Failed to enable GPE handler for GPE %d: %s\n",
			applespi->gpe, acpi_क्रमmat_exception(acpi_sts));
		acpi_हटाओ_gpe_handler(शून्य, applespi->gpe, applespi_notअगरy);
		वापस -ENODEV;
	पूर्ण

	/* trigger touchpad setup */
	applespi_init(applespi, false);

	/*
	 * By शेष this device is not enabled क्रम wakeup; but USB keyboards
	 * generally are, so the expectation is that by शेष the keyboard
	 * will wake the प्रणाली.
	 */
	device_wakeup_enable(&spi->dev);

	/* set up keyboard-backlight */
	sts = applespi_get_saved_bl_level(applespi);
	अगर (sts >= 0)
		applespi_set_bl_level(&applespi->backlight_info, sts);

	applespi->backlight_info.name            = "spi::kbd_backlight";
	applespi->backlight_info.शेष_trigger = "kbd-backlight";
	applespi->backlight_info.brightness_set  = applespi_set_bl_level;

	sts = devm_led_classdev_रेजिस्टर(&spi->dev, &applespi->backlight_info);
	अगर (sts)
		dev_warn(&applespi->spi->dev,
			 "Unable to register keyboard backlight class dev (%d)\n",
			 sts);

	/* set up debugfs entries क्रम touchpad dimensions logging */
	applespi->debugfs_root = debugfs_create_dir("applespi", शून्य);

	debugfs_create_bool("enable_tp_dim", 0600, applespi->debugfs_root,
			    &applespi->debug_tp_dim);

	debugfs_create_file("tp_dim", 0400, applespi->debugfs_root, applespi,
			    &applespi_tp_dim_fops);

	वापस 0;
पूर्ण

अटल व्योम applespi_drain_ग_लिखोs(काष्ठा applespi_data *applespi)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&applespi->cmd_msg_lock, flags);

	applespi->drain = true;
	रुको_event_lock_irq(applespi->drain_complete, !applespi->ग_लिखो_active,
			    applespi->cmd_msg_lock);

	spin_unlock_irqrestore(&applespi->cmd_msg_lock, flags);
पूर्ण

अटल व्योम applespi_drain_पढ़ोs(काष्ठा applespi_data *applespi)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&applespi->cmd_msg_lock, flags);

	रुको_event_lock_irq(applespi->drain_complete, !applespi->पढ़ो_active,
			    applespi->cmd_msg_lock);

	applespi->suspended = true;

	spin_unlock_irqrestore(&applespi->cmd_msg_lock, flags);
पूर्ण

अटल पूर्णांक applespi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा applespi_data *applespi = spi_get_drvdata(spi);

	applespi_drain_ग_लिखोs(applespi);

	acpi_disable_gpe(शून्य, applespi->gpe);
	acpi_हटाओ_gpe_handler(शून्य, applespi->gpe, applespi_notअगरy);
	device_wakeup_disable(&spi->dev);

	applespi_drain_पढ़ोs(applespi);

	debugfs_हटाओ_recursive(applespi->debugfs_root);

	वापस 0;
पूर्ण

अटल व्योम applespi_shutकरोwn(काष्ठा spi_device *spi)
अणु
	काष्ठा applespi_data *applespi = spi_get_drvdata(spi);

	applespi_save_bl_level(applespi, applespi->have_bl_level);
पूर्ण

अटल पूर्णांक applespi_घातeroff_late(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा applespi_data *applespi = spi_get_drvdata(spi);

	applespi_save_bl_level(applespi, applespi->have_bl_level);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused applespi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा applespi_data *applespi = spi_get_drvdata(spi);
	acpi_status acpi_sts;
	पूर्णांक sts;

	/* turn off caps-lock - it'll stay on otherwise */
	sts = applespi_set_capsl_led(applespi, false);
	अगर (sts)
		dev_warn(&applespi->spi->dev,
			 "Failed to turn off caps-lock led (%d)\n", sts);

	applespi_drain_ग_लिखोs(applespi);

	/* disable the पूर्णांकerrupt */
	acpi_sts = acpi_disable_gpe(शून्य, applespi->gpe);
	अगर (ACPI_FAILURE(acpi_sts))
		dev_err(&applespi->spi->dev,
			"Failed to disable GPE handler for GPE %d: %s\n",
			applespi->gpe, acpi_क्रमmat_exception(acpi_sts));

	applespi_drain_पढ़ोs(applespi);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused applespi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा applespi_data *applespi = spi_get_drvdata(spi);
	acpi_status acpi_sts;
	अचिन्हित दीर्घ flags;

	/* ensure our flags and state reflect a newly resumed device */
	spin_lock_irqsave(&applespi->cmd_msg_lock, flags);

	applespi->drain = false;
	applespi->have_cl_led_on = false;
	applespi->have_bl_level = 0;
	applespi->cmd_msg_queued = 0;
	applespi->पढ़ो_active = false;
	applespi->ग_लिखो_active = false;

	applespi->suspended = false;

	spin_unlock_irqrestore(&applespi->cmd_msg_lock, flags);

	/* चयन on the SPI पूर्णांकerface */
	applespi_enable_spi(applespi);

	/* re-enable the पूर्णांकerrupt */
	acpi_sts = acpi_enable_gpe(शून्य, applespi->gpe);
	अगर (ACPI_FAILURE(acpi_sts))
		dev_err(&applespi->spi->dev,
			"Failed to re-enable GPE handler for GPE %d: %s\n",
			applespi->gpe, acpi_क्रमmat_exception(acpi_sts));

	/* चयन the touchpad पूर्णांकo multitouch mode */
	applespi_init(applespi, true);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id applespi_acpi_match[] = अणु
	अणु "APP000D", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, applespi_acpi_match);

अटल स्थिर काष्ठा dev_pm_ops applespi_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(applespi_suspend, applespi_resume)
	.घातeroff_late	= applespi_घातeroff_late,
पूर्ण;

अटल काष्ठा spi_driver applespi_driver = अणु
	.driver		= अणु
		.name			= "applespi",
		.acpi_match_table	= applespi_acpi_match,
		.pm			= &applespi_pm_ops,
	पूर्ण,
	.probe		= applespi_probe,
	.हटाओ		= applespi_हटाओ,
	.shutकरोwn	= applespi_shutकरोwn,
पूर्ण;

module_spi_driver(applespi_driver)

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MacBook(Pro) SPI Keyboard/Touchpad driver");
MODULE_AUTHOR("Federico Lorenzi");
MODULE_AUTHOR("Ronald Tschalथअr");
