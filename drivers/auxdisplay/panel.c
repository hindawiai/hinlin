<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Front panel driver क्रम Linux
 * Copyright (C) 2000-2008, Willy Tarreau <w@1wt.eu>
 * Copyright (C) 2016-2017 Glider bvba
 *
 * This code drives an LCD module (/dev/lcd), and a keypad (/dev/keypad)
 * connected to a parallel prपूर्णांकer port.
 *
 * The LCD module may either be an HD44780-like 8-bit parallel LCD, or a 1-bit
 * serial module compatible with Samsung's KS0074. The pins may be connected in
 * any combination, everything is programmable.
 *
 * The keypad consists in a matrix of push buttons connecting input pins to
 * data output pins or to the ground. The combinations have to be hard-coded
 * in the driver, though several profiles exist and adding new ones is easy.
 *
 * Several profiles are provided क्रम commonly found LCD+keypad modules on the
 * market, such as those found in Nexcom's appliances.
 *
 * FIXME:
 *      - the initialization/deinitialization process is very dirty and should
 *        be rewritten. It may even be buggy.
 *
 * TODO:
 *	- करोcument 24 keys keyboard (3 rows of 8 cols, 32 diodes + 2 inमाला_दो)
 *      - make the LCD a part of a भव screen of Vx*Vy
 *	- make the inमाला_दो list smp-safe
 *      - change the keyboard to a द्विगुन mapping : संकेतs -> key_id -> values
 *        so that applications can change values without knowing संकेतs
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/parport.h>
#समावेश <linux/list.h>

#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>

#समावेश "charlcd.h"
#समावेश "hd44780_common.h"

#घोषणा LCD_MAXBYTES		256	/* max burst ग_लिखो */

#घोषणा KEYPAD_BUFFER		64

/* poll the keyboard this every second */
#घोषणा INPUT_POLL_TIME		(HZ / 50)
/* a key starts to repeat after this बार INPUT_POLL_TIME */
#घोषणा KEYPAD_REP_START	(10)
/* a key repeats this बार INPUT_POLL_TIME */
#घोषणा KEYPAD_REP_DELAY	(2)

/* converts an r_str() input to an active high, bits string : 000BAOSE */
#घोषणा PNL_PINPUT(a)		((((अचिन्हित अक्षर)(a)) ^ 0x7F) >> 3)

#घोषणा PNL_PBUSY		0x80	/* inverted input, active low */
#घोषणा PNL_PACK		0x40	/* direct input, active low */
#घोषणा PNL_POUTPA		0x20	/* direct input, active high */
#घोषणा PNL_PSELECD		0x10	/* direct input, active high */
#घोषणा PNL_PERRORP		0x08	/* direct input, active low */

#घोषणा PNL_PBIसूची		0x20	/* bi-directional ports */
/* high to पढ़ो data in or-ed with data out */
#घोषणा PNL_PINTEN		0x10
#घोषणा PNL_PSELECP		0x08	/* inverted output, active low */
#घोषणा PNL_PINITP		0x04	/* direct output, active low */
#घोषणा PNL_PAUTOLF		0x02	/* inverted output, active low */
#घोषणा PNL_PSTROBE		0x01	/* inverted output */

#घोषणा PNL_PD0			0x01
#घोषणा PNL_PD1			0x02
#घोषणा PNL_PD2			0x04
#घोषणा PNL_PD3			0x08
#घोषणा PNL_PD4			0x10
#घोषणा PNL_PD5			0x20
#घोषणा PNL_PD6			0x40
#घोषणा PNL_PD7			0x80

#घोषणा PIN_NONE		0
#घोषणा PIN_STROBE		1
#घोषणा PIN_D0			2
#घोषणा PIN_D1			3
#घोषणा PIN_D2			4
#घोषणा PIN_D3			5
#घोषणा PIN_D4			6
#घोषणा PIN_D5			7
#घोषणा PIN_D6			8
#घोषणा PIN_D7			9
#घोषणा PIN_AUTOLF		14
#घोषणा PIN_INITP		16
#घोषणा PIN_SELECP		17
#घोषणा PIN_NOT_SET		127

#घोषणा NOT_SET			-1

/* macros to simplअगरy use of the parallel port */
#घोषणा r_ctr(x)        (parport_पढ़ो_control((x)->port))
#घोषणा r_dtr(x)        (parport_पढ़ो_data((x)->port))
#घोषणा r_str(x)        (parport_पढ़ो_status((x)->port))
#घोषणा w_ctr(x, y)     (parport_ग_लिखो_control((x)->port, (y)))
#घोषणा w_dtr(x, y)     (parport_ग_लिखो_data((x)->port, (y)))

/* this defines which bits are to be used and which ones to be ignored */
/* logical or of the output bits involved in the scan matrix */
अटल __u8 scan_mask_o;
/* logical or of the input bits involved in the scan matrix */
अटल __u8 scan_mask_i;

क्रमागत input_type अणु
	INPUT_TYPE_STD,
	INPUT_TYPE_KBD,
पूर्ण;

क्रमागत input_state अणु
	INPUT_ST_LOW,
	INPUT_ST_RISING,
	INPUT_ST_HIGH,
	INPUT_ST_FALLING,
पूर्ण;

काष्ठा logical_input अणु
	काष्ठा list_head list;
	__u64 mask;
	__u64 value;
	क्रमागत input_type type;
	क्रमागत input_state state;
	__u8 rise_समय, fall_समय;
	__u8 rise_समयr, fall_समयr, high_समयr;

	जोड़ अणु
		काष्ठा अणु	/* valid when type == INPUT_TYPE_STD */
			व्योम (*press_fct)(पूर्णांक);
			व्योम (*release_fct)(पूर्णांक);
			पूर्णांक press_data;
			पूर्णांक release_data;
		पूर्ण std;
		काष्ठा अणु	/* valid when type == INPUT_TYPE_KBD */
			अक्षर press_str[माप(व्योम *) + माप(पूर्णांक)] __nonstring;
			अक्षर repeat_str[माप(व्योम *) + माप(पूर्णांक)] __nonstring;
			अक्षर release_str[माप(व्योम *) + माप(पूर्णांक)] __nonstring;
		पूर्ण kbd;
	पूर्ण u;
पूर्ण;

अटल LIST_HEAD(logical_inमाला_दो);	/* list of all defined logical inमाला_दो */

/* physical contacts history
 * Physical contacts are a 45 bits string of 9 groups of 5 bits each.
 * The 8 lower groups correspond to output bits 0 to 7, and the 9th group
 * corresponds to the ground.
 * Within each group, bits are stored in the same order as पढ़ो on the port :
 * BAPSE (busy=4, ack=3, paper empty=2, select=1, error=0).
 * So, each __u64 is represented like this :
 * 0000000000000000000BAPSEBAPSEBAPSEBAPSEBAPSEBAPSEBAPSEBAPSEBAPSE
 * <-----unused------><gnd><d07><d06><d05><d04><d03><d02><d01><d00>
 */

/* what has just been पढ़ो from the I/O ports */
अटल __u64 phys_पढ़ो;
/* previous phys_पढ़ो */
अटल __u64 phys_पढ़ो_prev;
/* stabilized phys_पढ़ो (phys_पढ़ो|phys_पढ़ो_prev) */
अटल __u64 phys_curr;
/* previous phys_curr */
अटल __u64 phys_prev;
/* 0 means that at least one logical संकेत needs be computed */
अटल अक्षर inमाला_दो_stable;

/* these variables are specअगरic to the keypad */
अटल काष्ठा अणु
	bool enabled;
पूर्ण keypad;

अटल अक्षर keypad_buffer[KEYPAD_BUFFER];
अटल पूर्णांक keypad_buflen;
अटल पूर्णांक keypad_start;
अटल अक्षर keypressed;
अटल रुको_queue_head_t keypad_पढ़ो_रुको;

/* lcd-specअगरic variables */
अटल काष्ठा अणु
	bool enabled;
	bool initialized;

	पूर्णांक अक्षरset;
	पूर्णांक proto;

	/* TODO: use जोड़ here? */
	काष्ठा अणु
		पूर्णांक e;
		पूर्णांक rs;
		पूर्णांक rw;
		पूर्णांक cl;
		पूर्णांक da;
		पूर्णांक bl;
	पूर्ण pins;

	काष्ठा अक्षरlcd *अक्षरlcd;
पूर्ण lcd;

/* Needed only क्रम init */
अटल पूर्णांक selected_lcd_type = NOT_SET;

/*
 * Bit masks to convert LCD संकेतs to parallel port outमाला_दो.
 * _d_ are values क्रम data port, _c_ are क्रम control port.
 * [0] = संकेत OFF, [1] = संकेत ON, [2] = mask
 */
#घोषणा BIT_CLR		0
#घोषणा BIT_SET		1
#घोषणा BIT_MSK		2
#घोषणा BIT_STATES	3
/*
 * one entry क्रम each bit on the LCD
 */
#घोषणा LCD_BIT_E	0
#घोषणा LCD_BIT_RS	1
#घोषणा LCD_BIT_RW	2
#घोषणा LCD_BIT_BL	3
#घोषणा LCD_BIT_CL	4
#घोषणा LCD_BIT_DA	5
#घोषणा LCD_BITS	6

/*
 * each bit can be either connected to a DATA or CTRL port
 */
#घोषणा LCD_PORT_C	0
#घोषणा LCD_PORT_D	1
#घोषणा LCD_PORTS	2

अटल अचिन्हित अक्षर lcd_bits[LCD_PORTS][LCD_BITS][BIT_STATES];

/*
 * LCD protocols
 */
#घोषणा LCD_PROTO_PARALLEL      0
#घोषणा LCD_PROTO_SERIAL        1
#घोषणा LCD_PROTO_TI_DA8XX_LCD	2

/*
 * LCD अक्षरacter sets
 */
#घोषणा LCD_CHARSET_NORMAL      0
#घोषणा LCD_CHARSET_KS0074      1

/*
 * LCD types
 */
#घोषणा LCD_TYPE_NONE		0
#घोषणा LCD_TYPE_CUSTOM		1
#घोषणा LCD_TYPE_OLD		2
#घोषणा LCD_TYPE_KS0074		3
#घोषणा LCD_TYPE_HANTRONIX	4
#घोषणा LCD_TYPE_NEXCOM		5

/*
 * keypad types
 */
#घोषणा KEYPAD_TYPE_NONE	0
#घोषणा KEYPAD_TYPE_OLD		1
#घोषणा KEYPAD_TYPE_NEW		2
#घोषणा KEYPAD_TYPE_NEXCOM	3

/*
 * panel profiles
 */
#घोषणा PANEL_PROखाता_CUSTOM	0
#घोषणा PANEL_PROखाता_OLD	1
#घोषणा PANEL_PROखाता_NEW	2
#घोषणा PANEL_PROखाता_HANTRONIX	3
#घोषणा PANEL_PROखाता_NEXCOM	4
#घोषणा PANEL_PROखाता_LARGE	5

/*
 * Conकाष्ठा custom config from the kernel's configuration
 */
#घोषणा DEFAULT_PARPORT         0
#घोषणा DEFAULT_PROखाता         PANEL_PROखाता_LARGE
#घोषणा DEFAULT_KEYPAD_TYPE     KEYPAD_TYPE_OLD
#घोषणा DEFAULT_LCD_TYPE        LCD_TYPE_OLD
#घोषणा DEFAULT_LCD_HEIGHT      2
#घोषणा DEFAULT_LCD_WIDTH       40
#घोषणा DEFAULT_LCD_CHARSET     LCD_CHARSET_NORMAL
#घोषणा DEFAULT_LCD_PROTO       LCD_PROTO_PARALLEL

#घोषणा DEFAULT_LCD_PIN_E       PIN_AUTOLF
#घोषणा DEFAULT_LCD_PIN_RS      PIN_SELECP
#घोषणा DEFAULT_LCD_PIN_RW      PIN_INITP
#घोषणा DEFAULT_LCD_PIN_SCL     PIN_STROBE
#घोषणा DEFAULT_LCD_PIN_SDA     PIN_D0
#घोषणा DEFAULT_LCD_PIN_BL      PIN_NOT_SET

#अगर_घोषित CONFIG_PANEL_PARPORT
#अघोषित DEFAULT_PARPORT
#घोषणा DEFAULT_PARPORT CONFIG_PANEL_PARPORT
#पूर्ण_अगर

#अगर_घोषित CONFIG_PANEL_PROखाता
#अघोषित DEFAULT_PROखाता
#घोषणा DEFAULT_PROखाता CONFIG_PANEL_PROखाता
#पूर्ण_अगर

#अगर DEFAULT_PROखाता == 0	/* custom */
#अगर_घोषित CONFIG_PANEL_KEYPAD
#अघोषित DEFAULT_KEYPAD_TYPE
#घोषणा DEFAULT_KEYPAD_TYPE CONFIG_PANEL_KEYPAD
#पूर्ण_अगर

#अगर_घोषित CONFIG_PANEL_LCD
#अघोषित DEFAULT_LCD_TYPE
#घोषणा DEFAULT_LCD_TYPE CONFIG_PANEL_LCD
#पूर्ण_अगर

#अगर_घोषित CONFIG_PANEL_LCD_HEIGHT
#अघोषित DEFAULT_LCD_HEIGHT
#घोषणा DEFAULT_LCD_HEIGHT CONFIG_PANEL_LCD_HEIGHT
#पूर्ण_अगर

#अगर_घोषित CONFIG_PANEL_LCD_WIDTH
#अघोषित DEFAULT_LCD_WIDTH
#घोषणा DEFAULT_LCD_WIDTH CONFIG_PANEL_LCD_WIDTH
#पूर्ण_अगर

#अगर_घोषित CONFIG_PANEL_LCD_BWIDTH
#अघोषित DEFAULT_LCD_BWIDTH
#घोषणा DEFAULT_LCD_BWIDTH CONFIG_PANEL_LCD_BWIDTH
#पूर्ण_अगर

#अगर_घोषित CONFIG_PANEL_LCD_HWIDTH
#अघोषित DEFAULT_LCD_HWIDTH
#घोषणा DEFAULT_LCD_HWIDTH CONFIG_PANEL_LCD_HWIDTH
#पूर्ण_अगर

#अगर_घोषित CONFIG_PANEL_LCD_CHARSET
#अघोषित DEFAULT_LCD_CHARSET
#घोषणा DEFAULT_LCD_CHARSET CONFIG_PANEL_LCD_CHARSET
#पूर्ण_अगर

#अगर_घोषित CONFIG_PANEL_LCD_PROTO
#अघोषित DEFAULT_LCD_PROTO
#घोषणा DEFAULT_LCD_PROTO CONFIG_PANEL_LCD_PROTO
#पूर्ण_अगर

#अगर_घोषित CONFIG_PANEL_LCD_PIN_E
#अघोषित DEFAULT_LCD_PIN_E
#घोषणा DEFAULT_LCD_PIN_E CONFIG_PANEL_LCD_PIN_E
#पूर्ण_अगर

#अगर_घोषित CONFIG_PANEL_LCD_PIN_RS
#अघोषित DEFAULT_LCD_PIN_RS
#घोषणा DEFAULT_LCD_PIN_RS CONFIG_PANEL_LCD_PIN_RS
#पूर्ण_अगर

#अगर_घोषित CONFIG_PANEL_LCD_PIN_RW
#अघोषित DEFAULT_LCD_PIN_RW
#घोषणा DEFAULT_LCD_PIN_RW CONFIG_PANEL_LCD_PIN_RW
#पूर्ण_अगर

#अगर_घोषित CONFIG_PANEL_LCD_PIN_SCL
#अघोषित DEFAULT_LCD_PIN_SCL
#घोषणा DEFAULT_LCD_PIN_SCL CONFIG_PANEL_LCD_PIN_SCL
#पूर्ण_अगर

#अगर_घोषित CONFIG_PANEL_LCD_PIN_SDA
#अघोषित DEFAULT_LCD_PIN_SDA
#घोषणा DEFAULT_LCD_PIN_SDA CONFIG_PANEL_LCD_PIN_SDA
#पूर्ण_अगर

#अगर_घोषित CONFIG_PANEL_LCD_PIN_BL
#अघोषित DEFAULT_LCD_PIN_BL
#घोषणा DEFAULT_LCD_PIN_BL CONFIG_PANEL_LCD_PIN_BL
#पूर्ण_अगर

#पूर्ण_अगर /* DEFAULT_PROखाता == 0 */

/* global variables */

/* Device single-खोलो policy control */
अटल atomic_t keypad_available = ATOMIC_INIT(1);

अटल काष्ठा pardevice *pprt;

अटल पूर्णांक keypad_initialized;

अटल DEFINE_SPINLOCK(pprt_lock);
अटल काष्ठा समयr_list scan_समयr;

MODULE_DESCRIPTION("Generic parallel port LCD/Keypad driver");

अटल पूर्णांक parport = DEFAULT_PARPORT;
module_param(parport, पूर्णांक, 0000);
MODULE_PARM_DESC(parport, "Parallel port index (0=lpt1, 1=lpt2, ...)");

अटल पूर्णांक profile = DEFAULT_PROखाता;
module_param(profile, पूर्णांक, 0000);
MODULE_PARM_DESC(profile,
		 "1=16x2 old kp; 2=serial 16x2, new kp; 3=16x2 hantronix; "
		 "4=16x2 nexcom; default=40x2, old kp");

अटल पूर्णांक keypad_type = NOT_SET;
module_param(keypad_type, पूर्णांक, 0000);
MODULE_PARM_DESC(keypad_type,
		 "Keypad type: 0=none, 1=old 6 keys, 2=new 6+1 keys, 3=nexcom 4 keys");

अटल पूर्णांक lcd_type = NOT_SET;
module_param(lcd_type, पूर्णांक, 0000);
MODULE_PARM_DESC(lcd_type,
		 "LCD type: 0=none, 1=compiled-in, 2=old, 3=serial ks0074, 4=hantronix, 5=nexcom");

अटल पूर्णांक lcd_height = NOT_SET;
module_param(lcd_height, पूर्णांक, 0000);
MODULE_PARM_DESC(lcd_height, "Number of lines on the LCD");

अटल पूर्णांक lcd_width = NOT_SET;
module_param(lcd_width, पूर्णांक, 0000);
MODULE_PARM_DESC(lcd_width, "Number of columns on the LCD");

अटल पूर्णांक lcd_bwidth = NOT_SET;	/* पूर्णांकernal buffer width (usually 40) */
module_param(lcd_bwidth, पूर्णांक, 0000);
MODULE_PARM_DESC(lcd_bwidth, "Internal LCD line width (40)");

अटल पूर्णांक lcd_hwidth = NOT_SET;	/* hardware buffer width (usually 64) */
module_param(lcd_hwidth, पूर्णांक, 0000);
MODULE_PARM_DESC(lcd_hwidth, "LCD line hardware address (64)");

अटल पूर्णांक lcd_अक्षरset = NOT_SET;
module_param(lcd_अक्षरset, पूर्णांक, 0000);
MODULE_PARM_DESC(lcd_अक्षरset, "LCD character set: 0=standard, 1=KS0074");

अटल पूर्णांक lcd_proto = NOT_SET;
module_param(lcd_proto, पूर्णांक, 0000);
MODULE_PARM_DESC(lcd_proto,
		 "LCD communication: 0=parallel (//), 1=serial, 2=TI LCD Interface");

/*
 * These are the parallel port pins the LCD control संकेतs are connected to.
 * Set this to 0 अगर the संकेत is not used. Set it to its opposite value
 * (negative) अगर the संकेत is negated. -MAXINT is used to indicate that the
 * pin has not been explicitly specअगरied.
 *
 * WARNING! no check will be perक्रमmed about collisions with keypad !
 */

अटल पूर्णांक lcd_e_pin  = PIN_NOT_SET;
module_param(lcd_e_pin, पूर्णांक, 0000);
MODULE_PARM_DESC(lcd_e_pin,
		 "# of the // port pin connected to LCD 'E' signal, with polarity (-17..17)");

अटल पूर्णांक lcd_rs_pin = PIN_NOT_SET;
module_param(lcd_rs_pin, पूर्णांक, 0000);
MODULE_PARM_DESC(lcd_rs_pin,
		 "# of the // port pin connected to LCD 'RS' signal, with polarity (-17..17)");

अटल पूर्णांक lcd_rw_pin = PIN_NOT_SET;
module_param(lcd_rw_pin, पूर्णांक, 0000);
MODULE_PARM_DESC(lcd_rw_pin,
		 "# of the // port pin connected to LCD 'RW' signal, with polarity (-17..17)");

अटल पूर्णांक lcd_cl_pin = PIN_NOT_SET;
module_param(lcd_cl_pin, पूर्णांक, 0000);
MODULE_PARM_DESC(lcd_cl_pin,
		 "# of the // port pin connected to serial LCD 'SCL' signal, with polarity (-17..17)");

अटल पूर्णांक lcd_da_pin = PIN_NOT_SET;
module_param(lcd_da_pin, पूर्णांक, 0000);
MODULE_PARM_DESC(lcd_da_pin,
		 "# of the // port pin connected to serial LCD 'SDA' signal, with polarity (-17..17)");

अटल पूर्णांक lcd_bl_pin = PIN_NOT_SET;
module_param(lcd_bl_pin, पूर्णांक, 0000);
MODULE_PARM_DESC(lcd_bl_pin,
		 "# of the // port pin connected to LCD backlight, with polarity (-17..17)");

/* Deprecated module parameters - consider not using them anymore */

अटल पूर्णांक lcd_enabled = NOT_SET;
module_param(lcd_enabled, पूर्णांक, 0000);
MODULE_PARM_DESC(lcd_enabled, "Deprecated option, use lcd_type instead");

अटल पूर्णांक keypad_enabled = NOT_SET;
module_param(keypad_enabled, पूर्णांक, 0000);
MODULE_PARM_DESC(keypad_enabled, "Deprecated option, use keypad_type instead");

/* क्रम some LCD drivers (ks0074) we need a अक्षरset conversion table. */
अटल स्थिर अचिन्हित अक्षर lcd_अक्षर_conv_ks0074[256] = अणु
	/*          0|8   1|9   2|A   3|B   4|C   5|D   6|E   7|F */
	/* 0x00 */ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	/* 0x08 */ 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	/* 0x10 */ 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
	/* 0x18 */ 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
	/* 0x20 */ 0x20, 0x21, 0x22, 0x23, 0xa2, 0x25, 0x26, 0x27,
	/* 0x28 */ 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
	/* 0x30 */ 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
	/* 0x38 */ 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
	/* 0x40 */ 0xa0, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	/* 0x48 */ 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
	/* 0x50 */ 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
	/* 0x58 */ 0x58, 0x59, 0x5a, 0xfa, 0xfb, 0xfc, 0x1d, 0xc4,
	/* 0x60 */ 0x96, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	/* 0x68 */ 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
	/* 0x70 */ 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
	/* 0x78 */ 0x78, 0x79, 0x7a, 0xfd, 0xfe, 0xff, 0xce, 0x20,
	/* 0x80 */ 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	/* 0x88 */ 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
	/* 0x90 */ 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
	/* 0x98 */ 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
	/* 0xA0 */ 0x20, 0x40, 0xb1, 0xa1, 0x24, 0xa3, 0xfe, 0x5f,
	/* 0xA8 */ 0x22, 0xc8, 0x61, 0x14, 0x97, 0x2d, 0xad, 0x96,
	/* 0xB0 */ 0x80, 0x8c, 0x82, 0x83, 0x27, 0x8f, 0x86, 0xdd,
	/* 0xB8 */ 0x2c, 0x81, 0x6f, 0x15, 0x8b, 0x8a, 0x84, 0x60,
	/* 0xC0 */ 0xe2, 0xe2, 0xe2, 0x5b, 0x5b, 0xae, 0xbc, 0xa9,
	/* 0xC8 */ 0xc5, 0xbf, 0xc6, 0xf1, 0xe3, 0xe3, 0xe3, 0xe3,
	/* 0xD0 */ 0x44, 0x5d, 0xa8, 0xe4, 0xec, 0xec, 0x5c, 0x78,
	/* 0xD8 */ 0xab, 0xa6, 0xe5, 0x5e, 0x5e, 0xe6, 0xaa, 0xbe,
	/* 0xE0 */ 0x7f, 0xe7, 0xaf, 0x7b, 0x7b, 0xaf, 0xbd, 0xc8,
	/* 0xE8 */ 0xa4, 0xa5, 0xc7, 0xf6, 0xa7, 0xe8, 0x69, 0x69,
	/* 0xF0 */ 0xed, 0x7d, 0xa8, 0xe4, 0xec, 0x5c, 0x5c, 0x25,
	/* 0xF8 */ 0xac, 0xa6, 0xea, 0xef, 0x7e, 0xeb, 0xb2, 0x79,
पूर्ण;

अटल स्थिर अक्षर old_keypad_profile[][4][9] = अणु
	अणु"S0", "Left\n", "Left\n", ""पूर्ण,
	अणु"S1", "Down\n", "Down\n", ""पूर्ण,
	अणु"S2", "Up\n", "Up\n", ""पूर्ण,
	अणु"S3", "Right\n", "Right\n", ""पूर्ण,
	अणु"S4", "Esc\n", "Esc\n", ""पूर्ण,
	अणु"S5", "Ret\n", "Ret\n", ""पूर्ण,
	अणु"", "", "", ""पूर्ण
पूर्ण;

/* संकेतs, press, repeat, release */
अटल स्थिर अक्षर new_keypad_profile[][4][9] = अणु
	अणु"S0", "Left\n", "Left\n", ""पूर्ण,
	अणु"S1", "Down\n", "Down\n", ""पूर्ण,
	अणु"S2", "Up\n", "Up\n", ""पूर्ण,
	अणु"S3", "Right\n", "Right\n", ""पूर्ण,
	अणु"S4s5", "", "Esc\n", "Esc\n"पूर्ण,
	अणु"s4S5", "", "Ret\n", "Ret\n"पूर्ण,
	अणु"S4S5", "Help\n", "", ""पूर्ण,
	/* add new संकेतs above this line */
	अणु"", "", "", ""पूर्ण
पूर्ण;

/* संकेतs, press, repeat, release */
अटल स्थिर अक्षर nexcom_keypad_profile[][4][9] = अणु
	अणु"a-p-e-", "Down\n", "Down\n", ""पूर्ण,
	अणु"a-p-E-", "Ret\n", "Ret\n", ""पूर्ण,
	अणु"a-P-E-", "Esc\n", "Esc\n", ""पूर्ण,
	अणु"a-P-e-", "Up\n", "Up\n", ""पूर्ण,
	/* add new संकेतs above this line */
	अणु"", "", "", ""पूर्ण
पूर्ण;

अटल स्थिर अक्षर (*keypad_profile)[4][9] = old_keypad_profile;

अटल DECLARE_BITMAP(bits, LCD_BITS);

अटल व्योम lcd_get_bits(अचिन्हित पूर्णांक port, पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक bit, state;

	क्रम (bit = 0; bit < LCD_BITS; bit++) अणु
		state = test_bit(bit, bits) ? BIT_SET : BIT_CLR;
		*val &= lcd_bits[port][bit][BIT_MSK];
		*val |= lcd_bits[port][bit][state];
	पूर्ण
पूर्ण

/* sets data port bits according to current संकेतs values */
अटल पूर्णांक set_data_bits(व्योम)
अणु
	पूर्णांक val;

	val = r_dtr(pprt);
	lcd_get_bits(LCD_PORT_D, &val);
	w_dtr(pprt, val);
	वापस val;
पूर्ण

/* sets ctrl port bits according to current संकेतs values */
अटल पूर्णांक set_ctrl_bits(व्योम)
अणु
	पूर्णांक val;

	val = r_ctr(pprt);
	lcd_get_bits(LCD_PORT_C, &val);
	w_ctr(pprt, val);
	वापस val;
पूर्ण

/* sets ctrl & data port bits according to current संकेतs values */
अटल व्योम panel_set_bits(व्योम)
अणु
	set_data_bits();
	set_ctrl_bits();
पूर्ण

/*
 * Converts a parallel port pin (from -25 to 25) to data and control ports
 * masks, and data and control port bits. The संकेत will be considered
 * unconnected अगर it's on pin 0 or an invalid pin (<-25 or >25).
 *
 * Result will be used this way :
 *   out(dport, in(dport) & d_val[2] | d_val[संकेत_state])
 *   out(cport, in(cport) & c_val[2] | c_val[संकेत_state])
 */
अटल व्योम pin_to_bits(पूर्णांक pin, अचिन्हित अक्षर *d_val, अचिन्हित अक्षर *c_val)
अणु
	पूर्णांक d_bit, c_bit, inv;

	d_val[0] = 0;
	c_val[0] = 0;
	d_val[1] = 0;
	c_val[1] = 0;
	d_val[2] = 0xFF;
	c_val[2] = 0xFF;

	अगर (pin == 0)
		वापस;

	inv = (pin < 0);
	अगर (inv)
		pin = -pin;

	d_bit = 0;
	c_bit = 0;

	चयन (pin) अणु
	हाल PIN_STROBE:	/* strobe, inverted */
		c_bit = PNL_PSTROBE;
		inv = !inv;
		अवरोध;
	हाल PIN_D0...PIN_D7:	/* D0 - D7 = 2 - 9 */
		d_bit = 1 << (pin - 2);
		अवरोध;
	हाल PIN_AUTOLF:	/* स्वतःfeed, inverted */
		c_bit = PNL_PAUTOLF;
		inv = !inv;
		अवरोध;
	हाल PIN_INITP:		/* init, direct */
		c_bit = PNL_PINITP;
		अवरोध;
	हाल PIN_SELECP:	/* select_in, inverted */
		c_bit = PNL_PSELECP;
		inv = !inv;
		अवरोध;
	शेष:		/* unknown pin, ignore */
		अवरोध;
	पूर्ण

	अगर (c_bit) अणु
		c_val[2] &= ~c_bit;
		c_val[!inv] = c_bit;
	पूर्ण अन्यथा अगर (d_bit) अणु
		d_val[2] &= ~d_bit;
		d_val[!inv] = d_bit;
	पूर्ण
पूर्ण

/*
 * send a serial byte to the LCD panel. The caller is responsible क्रम locking
 * अगर needed.
 */
अटल व्योम lcd_send_serial(पूर्णांक byte)
अणु
	पूर्णांक bit;

	/*
	 * the data bit is set on D0, and the घड़ी on STROBE.
	 * LCD पढ़ोs D0 on STROBE's rising edge.
	 */
	क्रम (bit = 0; bit < 8; bit++) अणु
		clear_bit(LCD_BIT_CL, bits);	/* CLK low */
		panel_set_bits();
		अगर (byte & 1) अणु
			set_bit(LCD_BIT_DA, bits);
		पूर्ण अन्यथा अणु
			clear_bit(LCD_BIT_DA, bits);
		पूर्ण

		panel_set_bits();
		udelay(2);  /* मुख्यtain the data during 2 us beक्रमe CLK up */
		set_bit(LCD_BIT_CL, bits);	/* CLK high */
		panel_set_bits();
		udelay(1);  /* मुख्यtain the strobe during 1 us */
		byte >>= 1;
	पूर्ण
पूर्ण

/* turn the backlight on or off */
अटल व्योम lcd_backlight(काष्ठा अक्षरlcd *अक्षरlcd, क्रमागत अक्षरlcd_onoff on)
अणु
	अगर (lcd.pins.bl == PIN_NONE)
		वापस;

	/* The backlight is activated by setting the AUTOFEED line to +5V  */
	spin_lock_irq(&pprt_lock);
	अगर (on)
		set_bit(LCD_BIT_BL, bits);
	अन्यथा
		clear_bit(LCD_BIT_BL, bits);
	panel_set_bits();
	spin_unlock_irq(&pprt_lock);
पूर्ण

/* send a command to the LCD panel in serial mode */
अटल व्योम lcd_ग_लिखो_cmd_s(काष्ठा hd44780_common *hdc, पूर्णांक cmd)
अणु
	spin_lock_irq(&pprt_lock);
	lcd_send_serial(0x1F);	/* R/W=W, RS=0 */
	lcd_send_serial(cmd & 0x0F);
	lcd_send_serial((cmd >> 4) & 0x0F);
	udelay(40);		/* the लघुest command takes at least 40 us */
	spin_unlock_irq(&pprt_lock);
पूर्ण

/* send data to the LCD panel in serial mode */
अटल व्योम lcd_ग_लिखो_data_s(काष्ठा hd44780_common *hdc, पूर्णांक data)
अणु
	spin_lock_irq(&pprt_lock);
	lcd_send_serial(0x5F);	/* R/W=W, RS=1 */
	lcd_send_serial(data & 0x0F);
	lcd_send_serial((data >> 4) & 0x0F);
	udelay(40);		/* the लघुest data takes at least 40 us */
	spin_unlock_irq(&pprt_lock);
पूर्ण

/* send a command to the LCD panel in 8 bits parallel mode */
अटल व्योम lcd_ग_लिखो_cmd_p8(काष्ठा hd44780_common *hdc, पूर्णांक cmd)
अणु
	spin_lock_irq(&pprt_lock);
	/* present the data to the data port */
	w_dtr(pprt, cmd);
	udelay(20);	/* मुख्यtain the data during 20 us beक्रमe the strobe */

	set_bit(LCD_BIT_E, bits);
	clear_bit(LCD_BIT_RS, bits);
	clear_bit(LCD_BIT_RW, bits);
	set_ctrl_bits();

	udelay(40);	/* मुख्यtain the strobe during 40 us */

	clear_bit(LCD_BIT_E, bits);
	set_ctrl_bits();

	udelay(120);	/* the लघुest command takes at least 120 us */
	spin_unlock_irq(&pprt_lock);
पूर्ण

/* send data to the LCD panel in 8 bits parallel mode */
अटल व्योम lcd_ग_लिखो_data_p8(काष्ठा hd44780_common *hdc, पूर्णांक data)
अणु
	spin_lock_irq(&pprt_lock);
	/* present the data to the data port */
	w_dtr(pprt, data);
	udelay(20);	/* मुख्यtain the data during 20 us beक्रमe the strobe */

	set_bit(LCD_BIT_E, bits);
	set_bit(LCD_BIT_RS, bits);
	clear_bit(LCD_BIT_RW, bits);
	set_ctrl_bits();

	udelay(40);	/* मुख्यtain the strobe during 40 us */

	clear_bit(LCD_BIT_E, bits);
	set_ctrl_bits();

	udelay(45);	/* the लघुest data takes at least 45 us */
	spin_unlock_irq(&pprt_lock);
पूर्ण

/* send a command to the TI LCD panel */
अटल व्योम lcd_ग_लिखो_cmd_tilcd(काष्ठा hd44780_common *hdc, पूर्णांक cmd)
अणु
	spin_lock_irq(&pprt_lock);
	/* present the data to the control port */
	w_ctr(pprt, cmd);
	udelay(60);
	spin_unlock_irq(&pprt_lock);
पूर्ण

/* send data to the TI LCD panel */
अटल व्योम lcd_ग_लिखो_data_tilcd(काष्ठा hd44780_common *hdc, पूर्णांक data)
अणु
	spin_lock_irq(&pprt_lock);
	/* present the data to the data port */
	w_dtr(pprt, data);
	udelay(60);
	spin_unlock_irq(&pprt_lock);
पूर्ण

अटल स्थिर काष्ठा अक्षरlcd_ops अक्षरlcd_ops = अणु
	.backlight	= lcd_backlight,
	.prपूर्णांक		= hd44780_common_prपूर्णांक,
	.जाओxy		= hd44780_common_जाओxy,
	.home		= hd44780_common_home,
	.clear_display	= hd44780_common_clear_display,
	.init_display	= hd44780_common_init_display,
	.shअगरt_cursor	= hd44780_common_shअगरt_cursor,
	.shअगरt_display	= hd44780_common_shअगरt_display,
	.display	= hd44780_common_display,
	.cursor		= hd44780_common_cursor,
	.blink		= hd44780_common_blink,
	.fontsize	= hd44780_common_fontsize,
	.lines		= hd44780_common_lines,
	.redefine_अक्षर	= hd44780_common_redefine_अक्षर,
पूर्ण;

/* initialize the LCD driver */
अटल व्योम lcd_init(व्योम)
अणु
	काष्ठा अक्षरlcd *अक्षरlcd;
	काष्ठा hd44780_common *hdc;

	hdc = hd44780_common_alloc();
	अगर (!hdc)
		वापस;

	अक्षरlcd = अक्षरlcd_alloc();
	अगर (!अक्षरlcd) अणु
		kमुक्त(hdc);
		वापस;
	पूर्ण

	hdc->hd44780 = &lcd;
	अक्षरlcd->drvdata = hdc;

	/*
	 * Init lcd काष्ठा with load-समय values to preserve exact
	 * current functionality (at least क्रम now).
	 */
	अक्षरlcd->height = lcd_height;
	अक्षरlcd->width = lcd_width;
	hdc->bwidth = lcd_bwidth;
	hdc->hwidth = lcd_hwidth;

	चयन (selected_lcd_type) अणु
	हाल LCD_TYPE_OLD:
		/* parallel mode, 8 bits */
		lcd.proto = LCD_PROTO_PARALLEL;
		lcd.अक्षरset = LCD_CHARSET_NORMAL;
		lcd.pins.e = PIN_STROBE;
		lcd.pins.rs = PIN_AUTOLF;

		अक्षरlcd->width = 40;
		hdc->bwidth = 40;
		hdc->hwidth = 64;
		अक्षरlcd->height = 2;
		अवरोध;
	हाल LCD_TYPE_KS0074:
		/* serial mode, ks0074 */
		lcd.proto = LCD_PROTO_SERIAL;
		lcd.अक्षरset = LCD_CHARSET_KS0074;
		lcd.pins.bl = PIN_AUTOLF;
		lcd.pins.cl = PIN_STROBE;
		lcd.pins.da = PIN_D0;

		अक्षरlcd->width = 16;
		hdc->bwidth = 40;
		hdc->hwidth = 16;
		अक्षरlcd->height = 2;
		अवरोध;
	हाल LCD_TYPE_NEXCOM:
		/* parallel mode, 8 bits, generic */
		lcd.proto = LCD_PROTO_PARALLEL;
		lcd.अक्षरset = LCD_CHARSET_NORMAL;
		lcd.pins.e = PIN_AUTOLF;
		lcd.pins.rs = PIN_SELECP;
		lcd.pins.rw = PIN_INITP;

		अक्षरlcd->width = 16;
		hdc->bwidth = 40;
		hdc->hwidth = 64;
		अक्षरlcd->height = 2;
		अवरोध;
	हाल LCD_TYPE_CUSTOM:
		/* customer-defined */
		lcd.proto = DEFAULT_LCD_PROTO;
		lcd.अक्षरset = DEFAULT_LCD_CHARSET;
		/* शेष geometry will be set later */
		अवरोध;
	हाल LCD_TYPE_HANTRONIX:
		/* parallel mode, 8 bits, hantronix-like */
	शेष:
		lcd.proto = LCD_PROTO_PARALLEL;
		lcd.अक्षरset = LCD_CHARSET_NORMAL;
		lcd.pins.e = PIN_STROBE;
		lcd.pins.rs = PIN_SELECP;

		अक्षरlcd->width = 16;
		hdc->bwidth = 40;
		hdc->hwidth = 64;
		अक्षरlcd->height = 2;
		अवरोध;
	पूर्ण

	/* Overग_लिखो with module params set on loading */
	अगर (lcd_height != NOT_SET)
		अक्षरlcd->height = lcd_height;
	अगर (lcd_width != NOT_SET)
		अक्षरlcd->width = lcd_width;
	अगर (lcd_bwidth != NOT_SET)
		hdc->bwidth = lcd_bwidth;
	अगर (lcd_hwidth != NOT_SET)
		hdc->hwidth = lcd_hwidth;
	अगर (lcd_अक्षरset != NOT_SET)
		lcd.अक्षरset = lcd_अक्षरset;
	अगर (lcd_proto != NOT_SET)
		lcd.proto = lcd_proto;
	अगर (lcd_e_pin != PIN_NOT_SET)
		lcd.pins.e = lcd_e_pin;
	अगर (lcd_rs_pin != PIN_NOT_SET)
		lcd.pins.rs = lcd_rs_pin;
	अगर (lcd_rw_pin != PIN_NOT_SET)
		lcd.pins.rw = lcd_rw_pin;
	अगर (lcd_cl_pin != PIN_NOT_SET)
		lcd.pins.cl = lcd_cl_pin;
	अगर (lcd_da_pin != PIN_NOT_SET)
		lcd.pins.da = lcd_da_pin;
	अगर (lcd_bl_pin != PIN_NOT_SET)
		lcd.pins.bl = lcd_bl_pin;

	/* this is used to catch wrong and शेष values */
	अगर (अक्षरlcd->width <= 0)
		अक्षरlcd->width = DEFAULT_LCD_WIDTH;
	अगर (hdc->bwidth <= 0)
		hdc->bwidth = DEFAULT_LCD_BWIDTH;
	अगर (hdc->hwidth <= 0)
		hdc->hwidth = DEFAULT_LCD_HWIDTH;
	अगर (अक्षरlcd->height <= 0)
		अक्षरlcd->height = DEFAULT_LCD_HEIGHT;

	अगर (lcd.proto == LCD_PROTO_SERIAL) अणु	/* SERIAL */
		अक्षरlcd->ops = &अक्षरlcd_ops;
		hdc->ग_लिखो_data = lcd_ग_लिखो_data_s;
		hdc->ग_लिखो_cmd = lcd_ग_लिखो_cmd_s;

		अगर (lcd.pins.cl == PIN_NOT_SET)
			lcd.pins.cl = DEFAULT_LCD_PIN_SCL;
		अगर (lcd.pins.da == PIN_NOT_SET)
			lcd.pins.da = DEFAULT_LCD_PIN_SDA;

	पूर्ण अन्यथा अगर (lcd.proto == LCD_PROTO_PARALLEL) अणु	/* PARALLEL */
		अक्षरlcd->ops = &अक्षरlcd_ops;
		hdc->ग_लिखो_data = lcd_ग_लिखो_data_p8;
		hdc->ग_लिखो_cmd = lcd_ग_लिखो_cmd_p8;

		अगर (lcd.pins.e == PIN_NOT_SET)
			lcd.pins.e = DEFAULT_LCD_PIN_E;
		अगर (lcd.pins.rs == PIN_NOT_SET)
			lcd.pins.rs = DEFAULT_LCD_PIN_RS;
		अगर (lcd.pins.rw == PIN_NOT_SET)
			lcd.pins.rw = DEFAULT_LCD_PIN_RW;
	पूर्ण अन्यथा अणु
		अक्षरlcd->ops = &अक्षरlcd_ops;
		hdc->ग_लिखो_data = lcd_ग_लिखो_data_tilcd;
		hdc->ग_लिखो_cmd = lcd_ग_लिखो_cmd_tilcd;
	पूर्ण

	अगर (lcd.pins.bl == PIN_NOT_SET)
		lcd.pins.bl = DEFAULT_LCD_PIN_BL;

	अगर (lcd.pins.e == PIN_NOT_SET)
		lcd.pins.e = PIN_NONE;
	अगर (lcd.pins.rs == PIN_NOT_SET)
		lcd.pins.rs = PIN_NONE;
	अगर (lcd.pins.rw == PIN_NOT_SET)
		lcd.pins.rw = PIN_NONE;
	अगर (lcd.pins.bl == PIN_NOT_SET)
		lcd.pins.bl = PIN_NONE;
	अगर (lcd.pins.cl == PIN_NOT_SET)
		lcd.pins.cl = PIN_NONE;
	अगर (lcd.pins.da == PIN_NOT_SET)
		lcd.pins.da = PIN_NONE;

	अगर (lcd.अक्षरset == NOT_SET)
		lcd.अक्षरset = DEFAULT_LCD_CHARSET;

	अगर (lcd.अक्षरset == LCD_CHARSET_KS0074)
		अक्षरlcd->अक्षर_conv = lcd_अक्षर_conv_ks0074;
	अन्यथा
		अक्षरlcd->अक्षर_conv = शून्य;

	pin_to_bits(lcd.pins.e, lcd_bits[LCD_PORT_D][LCD_BIT_E],
		    lcd_bits[LCD_PORT_C][LCD_BIT_E]);
	pin_to_bits(lcd.pins.rs, lcd_bits[LCD_PORT_D][LCD_BIT_RS],
		    lcd_bits[LCD_PORT_C][LCD_BIT_RS]);
	pin_to_bits(lcd.pins.rw, lcd_bits[LCD_PORT_D][LCD_BIT_RW],
		    lcd_bits[LCD_PORT_C][LCD_BIT_RW]);
	pin_to_bits(lcd.pins.bl, lcd_bits[LCD_PORT_D][LCD_BIT_BL],
		    lcd_bits[LCD_PORT_C][LCD_BIT_BL]);
	pin_to_bits(lcd.pins.cl, lcd_bits[LCD_PORT_D][LCD_BIT_CL],
		    lcd_bits[LCD_PORT_C][LCD_BIT_CL]);
	pin_to_bits(lcd.pins.da, lcd_bits[LCD_PORT_D][LCD_BIT_DA],
		    lcd_bits[LCD_PORT_C][LCD_BIT_DA]);

	lcd.अक्षरlcd = अक्षरlcd;
	lcd.initialized = true;
पूर्ण

/*
 * These are the file operation function क्रम user access to /dev/keypad
 */

अटल sमाप_प्रकार keypad_पढ़ो(काष्ठा file *file,
			   अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित i = *ppos;
	अक्षर __user *पंचांगp = buf;

	अगर (keypad_buflen == 0) अणु
		अगर (file->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		अगर (रुको_event_पूर्णांकerruptible(keypad_पढ़ो_रुको,
					     keypad_buflen != 0))
			वापस -EINTR;
	पूर्ण

	क्रम (; count-- > 0 && (keypad_buflen > 0);
	     ++i, ++पंचांगp, --keypad_buflen) अणु
		put_user(keypad_buffer[keypad_start], पंचांगp);
		keypad_start = (keypad_start + 1) % KEYPAD_BUFFER;
	पूर्ण
	*ppos = i;

	वापस पंचांगp - buf;
पूर्ण

अटल पूर्णांक keypad_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;

	ret = -EBUSY;
	अगर (!atomic_dec_and_test(&keypad_available))
		जाओ fail;	/* खोलो only once at a समय */

	ret = -EPERM;
	अगर (file->f_mode & FMODE_WRITE)	/* device is पढ़ो-only */
		जाओ fail;

	keypad_buflen = 0;	/* flush the buffer on खोलोing */
	वापस 0;
 fail:
	atomic_inc(&keypad_available);
	वापस ret;
पूर्ण

अटल पूर्णांक keypad_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	atomic_inc(&keypad_available);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations keypad_fops = अणु
	.पढ़ो    = keypad_पढ़ो,		/* पढ़ो */
	.खोलो    = keypad_खोलो,		/* खोलो */
	.release = keypad_release,	/* बंद */
	.llseek  = शेष_llseek,
पूर्ण;

अटल काष्ठा miscdevice keypad_dev = अणु
	.minor	= KEYPAD_MINOR,
	.name	= "keypad",
	.fops	= &keypad_fops,
पूर्ण;

अटल व्योम keypad_send_key(स्थिर अक्षर *string, पूर्णांक max_len)
अणु
	/* send the key to the device only अगर a process is attached to it. */
	अगर (!atomic_पढ़ो(&keypad_available)) अणु
		जबतक (max_len-- && keypad_buflen < KEYPAD_BUFFER && *string) अणु
			keypad_buffer[(keypad_start + keypad_buflen++) %
				      KEYPAD_BUFFER] = *string++;
		पूर्ण
		wake_up_पूर्णांकerruptible(&keypad_पढ़ो_रुको);
	पूर्ण
पूर्ण

/* this function scans all the bits involving at least one logical संकेत,
 * and माला_दो the results in the bitfield "phys_read" (one bit per established
 * contact), and sets "phys_read_prev" to "phys_read".
 *
 * Note: to debounce input संकेतs, we will only consider as चयनed a संकेत
 * which is stable across 2 measures. Signals which are dअगरferent between two
 * पढ़ोs will be kept as they previously were in their logical क्रमm (phys_prev).
 * A संकेत which has just चयनed will have a 1 in
 * (phys_पढ़ो ^ phys_पढ़ो_prev).
 */
अटल व्योम phys_scan_contacts(व्योम)
अणु
	पूर्णांक bit, bitval;
	अक्षर oldval;
	अक्षर biपंचांगask;
	अक्षर gndmask;

	phys_prev = phys_curr;
	phys_पढ़ो_prev = phys_पढ़ो;
	phys_पढ़ो = 0;		/* flush all संकेतs */

	/* keep track of old value, with all outमाला_दो disabled */
	oldval = r_dtr(pprt) | scan_mask_o;
	/* activate all keyboard outमाला_दो (active low) */
	w_dtr(pprt, oldval & ~scan_mask_o);

	/* will have a 1 क्रम each bit set to gnd */
	biपंचांगask = PNL_PINPUT(r_str(pprt)) & scan_mask_i;
	/* disable all matrix संकेतs */
	w_dtr(pprt, oldval);

	/* now that all outमाला_दो are cleared, the only active input bits are
	 * directly connected to the ground
	 */

	/* 1 क्रम each grounded input */
	gndmask = PNL_PINPUT(r_str(pprt)) & scan_mask_i;

	/* grounded inमाला_दो are संकेतs 40-44 */
	phys_पढ़ो |= (__u64)gndmask << 40;

	अगर (biपंचांगask != gndmask) अणु
		/*
		 * since clearing the outमाला_दो changed some inमाला_दो, we know
		 * that some input संकेतs are currently tied to some outमाला_दो.
		 * So we'll scan them.
		 */
		क्रम (bit = 0; bit < 8; bit++) अणु
			bitval = BIT(bit);

			अगर (!(scan_mask_o & bitval))	/* skip unused bits */
				जारी;

			w_dtr(pprt, oldval & ~bitval);	/* enable this output */
			biपंचांगask = PNL_PINPUT(r_str(pprt)) & ~gndmask;
			phys_पढ़ो |= (__u64)biपंचांगask << (5 * bit);
		पूर्ण
		w_dtr(pprt, oldval);	/* disable all outमाला_दो */
	पूर्ण
	/*
	 * this is easy: use old bits when they are flapping,
	 * use new ones when stable
	 */
	phys_curr = (phys_prev & (phys_पढ़ो ^ phys_पढ़ो_prev)) |
		    (phys_पढ़ो & ~(phys_पढ़ो ^ phys_पढ़ो_prev));
पूर्ण

अटल अंतरभूत पूर्णांक input_state_high(काष्ठा logical_input *input)
अणु
#अगर 0
	/* FIXME:
	 * this is an invalid test. It tries to catch
	 * transitions from single-key to multiple-key, but
	 * करोesn't take पूर्णांकo account the contacts polarity.
	 * The only solution to the problem is to parse keys
	 * from the most complex to the simplest combinations,
	 * and mark them as 'caught' once a combination
	 * matches, then unmatch it क्रम all other ones.
	 */

	/* try to catch dangerous transitions हालs :
	 * someone adds a bit, so this संकेत was a false
	 * positive resulting from a transition. We should
	 * invalidate the संकेत immediately and not call the
	 * release function.
	 * eg: 0 -(press A)-> A -(press B)-> AB : करोn't match A's release.
	 */
	अगर (((phys_prev & input->mask) == input->value) &&
	    ((phys_curr & input->mask) >  input->value)) अणु
		input->state = INPUT_ST_LOW; /* invalidate */
		वापस 1;
	पूर्ण
#पूर्ण_अगर

	अगर ((phys_curr & input->mask) == input->value) अणु
		अगर ((input->type == INPUT_TYPE_STD) &&
		    (input->high_समयr == 0)) अणु
			input->high_समयr++;
			अगर (input->u.std.press_fct)
				input->u.std.press_fct(input->u.std.press_data);
		पूर्ण अन्यथा अगर (input->type == INPUT_TYPE_KBD) अणु
			/* will turn on the light */
			keypressed = 1;

			अगर (input->high_समयr == 0) अणु
				अक्षर *press_str = input->u.kbd.press_str;

				अगर (press_str[0]) अणु
					पूर्णांक s = माप(input->u.kbd.press_str);

					keypad_send_key(press_str, s);
				पूर्ण
			पूर्ण

			अगर (input->u.kbd.repeat_str[0]) अणु
				अक्षर *repeat_str = input->u.kbd.repeat_str;

				अगर (input->high_समयr >= KEYPAD_REP_START) अणु
					पूर्णांक s = माप(input->u.kbd.repeat_str);

					input->high_समयr -= KEYPAD_REP_DELAY;
					keypad_send_key(repeat_str, s);
				पूर्ण
				/* we will need to come back here soon */
				inमाला_दो_stable = 0;
			पूर्ण

			अगर (input->high_समयr < 255)
				input->high_समयr++;
		पूर्ण
		वापस 1;
	पूर्ण

	/* अन्यथा संकेत falling करोwn. Let's fall through. */
	input->state = INPUT_ST_FALLING;
	input->fall_समयr = 0;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम input_state_falling(काष्ठा logical_input *input)
अणु
#अगर 0
	/* FIXME !!! same comment as in input_state_high */
	अगर (((phys_prev & input->mask) == input->value) &&
	    ((phys_curr & input->mask) >  input->value)) अणु
		input->state = INPUT_ST_LOW;	/* invalidate */
		वापस;
	पूर्ण
#पूर्ण_अगर

	अगर ((phys_curr & input->mask) == input->value) अणु
		अगर (input->type == INPUT_TYPE_KBD) अणु
			/* will turn on the light */
			keypressed = 1;

			अगर (input->u.kbd.repeat_str[0]) अणु
				अक्षर *repeat_str = input->u.kbd.repeat_str;

				अगर (input->high_समयr >= KEYPAD_REP_START) अणु
					पूर्णांक s = माप(input->u.kbd.repeat_str);

					input->high_समयr -= KEYPAD_REP_DELAY;
					keypad_send_key(repeat_str, s);
				पूर्ण
				/* we will need to come back here soon */
				inमाला_दो_stable = 0;
			पूर्ण

			अगर (input->high_समयr < 255)
				input->high_समयr++;
		पूर्ण
		input->state = INPUT_ST_HIGH;
	पूर्ण अन्यथा अगर (input->fall_समयr >= input->fall_समय) अणु
		/* call release event */
		अगर (input->type == INPUT_TYPE_STD) अणु
			व्योम (*release_fct)(पूर्णांक) = input->u.std.release_fct;

			अगर (release_fct)
				release_fct(input->u.std.release_data);
		पूर्ण अन्यथा अगर (input->type == INPUT_TYPE_KBD) अणु
			अक्षर *release_str = input->u.kbd.release_str;

			अगर (release_str[0]) अणु
				पूर्णांक s = माप(input->u.kbd.release_str);

				keypad_send_key(release_str, s);
			पूर्ण
		पूर्ण

		input->state = INPUT_ST_LOW;
	पूर्ण अन्यथा अणु
		input->fall_समयr++;
		inमाला_दो_stable = 0;
	पूर्ण
पूर्ण

अटल व्योम panel_process_inमाला_दो(व्योम)
अणु
	काष्ठा logical_input *input;

	keypressed = 0;
	inमाला_दो_stable = 1;
	list_क्रम_each_entry(input, &logical_inमाला_दो, list) अणु
		चयन (input->state) अणु
		हाल INPUT_ST_LOW:
			अगर ((phys_curr & input->mask) != input->value)
				अवरोध;
			/* अगर all needed ones were alपढ़ोy set previously,
			 * this means that this logical संकेत has been
			 * activated by the releasing of another combined
			 * संकेत, so we करोn't want to match.
			 * eg: AB -(release B)-> A -(release A)-> 0 :
			 *     करोn't match A.
			 */
			अगर ((phys_prev & input->mask) == input->value)
				अवरोध;
			input->rise_समयr = 0;
			input->state = INPUT_ST_RISING;
			fallthrough;
		हाल INPUT_ST_RISING:
			अगर ((phys_curr & input->mask) != input->value) अणु
				input->state = INPUT_ST_LOW;
				अवरोध;
			पूर्ण
			अगर (input->rise_समयr < input->rise_समय) अणु
				inमाला_दो_stable = 0;
				input->rise_समयr++;
				अवरोध;
			पूर्ण
			input->high_समयr = 0;
			input->state = INPUT_ST_HIGH;
			fallthrough;
		हाल INPUT_ST_HIGH:
			अगर (input_state_high(input))
				अवरोध;
			fallthrough;
		हाल INPUT_ST_FALLING:
			input_state_falling(input);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम panel_scan_समयr(काष्ठा समयr_list *unused)
अणु
	अगर (keypad.enabled && keypad_initialized) अणु
		अगर (spin_trylock_irq(&pprt_lock)) अणु
			phys_scan_contacts();

			/* no need क्रम the parport anymore */
			spin_unlock_irq(&pprt_lock);
		पूर्ण

		अगर (!inमाला_दो_stable || phys_curr != phys_prev)
			panel_process_inमाला_दो();
	पूर्ण

	अगर (keypressed && lcd.enabled && lcd.initialized)
		अक्षरlcd_poke(lcd.अक्षरlcd);

	mod_समयr(&scan_समयr, jअगरfies + INPUT_POLL_TIME);
पूर्ण

अटल व्योम init_scan_समयr(व्योम)
अणु
	अगर (scan_समयr.function)
		वापस;		/* alपढ़ोy started */

	समयr_setup(&scan_समयr, panel_scan_समयr, 0);
	scan_समयr.expires = jअगरfies + INPUT_POLL_TIME;
	add_समयr(&scan_समयr);
पूर्ण

/* converts a name of the क्रमm "({BbAaPpSsEe}{01234567-})*" to a series of bits.
 * अगर <omask> or <imask> are non-null, they will be or'ed with the bits
 * corresponding to out and in bits respectively.
 * वापसs 1 अगर ok, 0 अगर error (in which हाल, nothing is written).
 */
अटल u8 input_name2mask(स्थिर अक्षर *name, __u64 *mask, __u64 *value,
			  u8 *imask, u8 *omask)
अणु
	स्थिर अक्षर sigtab[] = "EeSsPpAaBb";
	u8 im, om;
	__u64 m, v;

	om = 0;
	im = 0;
	m = 0ULL;
	v = 0ULL;
	जबतक (*name) अणु
		पूर्णांक in, out, bit, neg;
		स्थिर अक्षर *idx;

		idx = म_अक्षर(sigtab, *name);
		अगर (!idx)
			वापस 0;	/* input name not found */

		in = idx - sigtab;
		neg = (in & 1);	/* odd (lower) names are negated */
		in >>= 1;
		im |= BIT(in);

		name++;
		अगर (*name >= '0' && *name <= '7') अणु
			out = *name - '0';
			om |= BIT(out);
		पूर्ण अन्यथा अगर (*name == '-') अणु
			out = 8;
		पूर्ण अन्यथा अणु
			वापस 0;	/* unknown bit name */
		पूर्ण

		bit = (out * 5) + in;

		m |= 1ULL << bit;
		अगर (!neg)
			v |= 1ULL << bit;
		name++;
	पूर्ण
	*mask = m;
	*value = v;
	अगर (imask)
		*imask |= im;
	अगर (omask)
		*omask |= om;
	वापस 1;
पूर्ण

/* tries to bind a key to the संकेत name <name>. The key will send the
 * strings <press>, <repeat>, <release> क्रम these respective events.
 * Returns the poपूर्णांकer to the new key अगर ok, शून्य अगर the key could not be bound.
 */
अटल काष्ठा logical_input *panel_bind_key(स्थिर अक्षर *name, स्थिर अक्षर *press,
					    स्थिर अक्षर *repeat,
					    स्थिर अक्षर *release)
अणु
	काष्ठा logical_input *key;

	key = kzalloc(माप(*key), GFP_KERNEL);
	अगर (!key)
		वापस शून्य;

	अगर (!input_name2mask(name, &key->mask, &key->value, &scan_mask_i,
			     &scan_mask_o)) अणु
		kमुक्त(key);
		वापस शून्य;
	पूर्ण

	key->type = INPUT_TYPE_KBD;
	key->state = INPUT_ST_LOW;
	key->rise_समय = 1;
	key->fall_समय = 1;

	म_नकलन(key->u.kbd.press_str, press, माप(key->u.kbd.press_str));
	म_नकलन(key->u.kbd.repeat_str, repeat, माप(key->u.kbd.repeat_str));
	म_नकलन(key->u.kbd.release_str, release,
		माप(key->u.kbd.release_str));
	list_add(&key->list, &logical_inमाला_दो);
	वापस key;
पूर्ण

#अगर 0
/* tries to bind a callback function to the संकेत name <name>. The function
 * <press_fct> will be called with the <press_data> arg when the संकेत is
 * activated, and so on क्रम <release_fct>/<release_data>
 * Returns the poपूर्णांकer to the new संकेत अगर ok, शून्य अगर the संकेत could not
 * be bound.
 */
अटल काष्ठा logical_input *panel_bind_callback(अक्षर *name,
						 व्योम (*press_fct)(पूर्णांक),
						 पूर्णांक press_data,
						 व्योम (*release_fct)(पूर्णांक),
						 पूर्णांक release_data)
अणु
	काष्ठा logical_input *callback;

	callback = kदो_स्मृति(माप(*callback), GFP_KERNEL);
	अगर (!callback)
		वापस शून्य;

	स_रखो(callback, 0, माप(काष्ठा logical_input));
	अगर (!input_name2mask(name, &callback->mask, &callback->value,
			     &scan_mask_i, &scan_mask_o))
		वापस शून्य;

	callback->type = INPUT_TYPE_STD;
	callback->state = INPUT_ST_LOW;
	callback->rise_समय = 1;
	callback->fall_समय = 1;
	callback->u.std.press_fct = press_fct;
	callback->u.std.press_data = press_data;
	callback->u.std.release_fct = release_fct;
	callback->u.std.release_data = release_data;
	list_add(&callback->list, &logical_inमाला_दो);
	वापस callback;
पूर्ण
#पूर्ण_अगर

अटल व्योम keypad_init(व्योम)
अणु
	पूर्णांक keynum;

	init_रुकोqueue_head(&keypad_पढ़ो_रुको);
	keypad_buflen = 0;	/* flushes any eventual noisy keystroke */

	/* Let's create all known keys */

	क्रम (keynum = 0; keypad_profile[keynum][0][0]; keynum++) अणु
		panel_bind_key(keypad_profile[keynum][0],
			       keypad_profile[keynum][1],
			       keypad_profile[keynum][2],
			       keypad_profile[keynum][3]);
	पूर्ण

	init_scan_समयr();
	keypad_initialized = 1;
पूर्ण

/**************************************************/
/* device initialization                          */
/**************************************************/

अटल व्योम panel_attach(काष्ठा parport *port)
अणु
	काष्ठा pardev_cb panel_cb;

	अगर (port->number != parport)
		वापस;

	अगर (pprt) अणु
		pr_err("%s: port->number=%d parport=%d, already registered!\n",
		       __func__, port->number, parport);
		वापस;
	पूर्ण

	स_रखो(&panel_cb, 0, माप(panel_cb));
	panel_cb.निजी = &pprt;
	/* panel_cb.flags = 0 should be PARPORT_DEV_EXCL? */

	pprt = parport_रेजिस्टर_dev_model(port, "panel", &panel_cb, 0);
	अगर (!pprt) अणु
		pr_err("%s: port->number=%d parport=%d, parport_register_device() failed\n",
		       __func__, port->number, parport);
		वापस;
	पूर्ण

	अगर (parport_claim(pprt)) अणु
		pr_err("could not claim access to parport%d. Aborting.\n",
		       parport);
		जाओ err_unreg_device;
	पूर्ण

	/* must init LCD first, just in हाल an IRQ from the keypad is
	 * generated at keypad init
	 */
	अगर (lcd.enabled) अणु
		lcd_init();
		अगर (!lcd.अक्षरlcd || अक्षरlcd_रेजिस्टर(lcd.अक्षरlcd))
			जाओ err_unreg_device;
	पूर्ण

	अगर (keypad.enabled) अणु
		keypad_init();
		अगर (misc_रेजिस्टर(&keypad_dev))
			जाओ err_lcd_unreg;
	पूर्ण
	वापस;

err_lcd_unreg:
	अगर (scan_समयr.function)
		del_समयr_sync(&scan_समयr);
	अगर (lcd.enabled)
		अक्षरlcd_unरेजिस्टर(lcd.अक्षरlcd);
err_unreg_device:
	kमुक्त(lcd.अक्षरlcd);
	lcd.अक्षरlcd = शून्य;
	parport_unरेजिस्टर_device(pprt);
	pprt = शून्य;
पूर्ण

अटल व्योम panel_detach(काष्ठा parport *port)
अणु
	अगर (port->number != parport)
		वापस;

	अगर (!pprt) अणु
		pr_err("%s: port->number=%d parport=%d, nothing to unregister.\n",
		       __func__, port->number, parport);
		वापस;
	पूर्ण
	अगर (scan_समयr.function)
		del_समयr_sync(&scan_समयr);

	अगर (keypad.enabled) अणु
		misc_deरेजिस्टर(&keypad_dev);
		keypad_initialized = 0;
	पूर्ण

	अगर (lcd.enabled) अणु
		अक्षरlcd_unरेजिस्टर(lcd.अक्षरlcd);
		lcd.initialized = false;
		kमुक्त(lcd.अक्षरlcd->drvdata);
		kमुक्त(lcd.अक्षरlcd);
		lcd.अक्षरlcd = शून्य;
	पूर्ण

	/* TODO: मुक्त all input संकेतs */
	parport_release(pprt);
	parport_unरेजिस्टर_device(pprt);
	pprt = शून्य;
पूर्ण

अटल काष्ठा parport_driver panel_driver = अणु
	.name = "panel",
	.match_port = panel_attach,
	.detach = panel_detach,
	.devmodel = true,
पूर्ण;

/* init function */
अटल पूर्णांक __init panel_init_module(व्योम)
अणु
	पूर्णांक selected_keypad_type = NOT_SET, err;

	/* take care of an eventual profile */
	चयन (profile) अणु
	हाल PANEL_PROखाता_CUSTOM:
		/* custom profile */
		selected_keypad_type = DEFAULT_KEYPAD_TYPE;
		selected_lcd_type = DEFAULT_LCD_TYPE;
		अवरोध;
	हाल PANEL_PROखाता_OLD:
		/* 8 bits, 2*16, old keypad */
		selected_keypad_type = KEYPAD_TYPE_OLD;
		selected_lcd_type = LCD_TYPE_OLD;

		/* TODO: This two are a little hacky, sort it out later */
		अगर (lcd_width == NOT_SET)
			lcd_width = 16;
		अगर (lcd_hwidth == NOT_SET)
			lcd_hwidth = 16;
		अवरोध;
	हाल PANEL_PROखाता_NEW:
		/* serial, 2*16, new keypad */
		selected_keypad_type = KEYPAD_TYPE_NEW;
		selected_lcd_type = LCD_TYPE_KS0074;
		अवरोध;
	हाल PANEL_PROखाता_HANTRONIX:
		/* 8 bits, 2*16 hantronix-like, no keypad */
		selected_keypad_type = KEYPAD_TYPE_NONE;
		selected_lcd_type = LCD_TYPE_HANTRONIX;
		अवरोध;
	हाल PANEL_PROखाता_NEXCOM:
		/* generic 8 bits, 2*16, nexcom keypad, eg. Nexcom. */
		selected_keypad_type = KEYPAD_TYPE_NEXCOM;
		selected_lcd_type = LCD_TYPE_NEXCOM;
		अवरोध;
	हाल PANEL_PROखाता_LARGE:
		/* 8 bits, 2*40, old keypad */
		selected_keypad_type = KEYPAD_TYPE_OLD;
		selected_lcd_type = LCD_TYPE_OLD;
		अवरोध;
	पूर्ण

	/*
	 * Overग_लिखो selection with module param values (both keypad and lcd),
	 * where the deprecated params have lower prio.
	 */
	अगर (keypad_enabled != NOT_SET)
		selected_keypad_type = keypad_enabled;
	अगर (keypad_type != NOT_SET)
		selected_keypad_type = keypad_type;

	keypad.enabled = (selected_keypad_type > 0);

	अगर (lcd_enabled != NOT_SET)
		selected_lcd_type = lcd_enabled;
	अगर (lcd_type != NOT_SET)
		selected_lcd_type = lcd_type;

	lcd.enabled = (selected_lcd_type > 0);

	अगर (lcd.enabled) अणु
		/*
		 * Init lcd काष्ठा with load-समय values to preserve exact
		 * current functionality (at least क्रम now).
		 */
		lcd.अक्षरset = lcd_अक्षरset;
		lcd.proto = lcd_proto;
		lcd.pins.e = lcd_e_pin;
		lcd.pins.rs = lcd_rs_pin;
		lcd.pins.rw = lcd_rw_pin;
		lcd.pins.cl = lcd_cl_pin;
		lcd.pins.da = lcd_da_pin;
		lcd.pins.bl = lcd_bl_pin;
	पूर्ण

	चयन (selected_keypad_type) अणु
	हाल KEYPAD_TYPE_OLD:
		keypad_profile = old_keypad_profile;
		अवरोध;
	हाल KEYPAD_TYPE_NEW:
		keypad_profile = new_keypad_profile;
		अवरोध;
	हाल KEYPAD_TYPE_NEXCOM:
		keypad_profile = nexcom_keypad_profile;
		अवरोध;
	शेष:
		keypad_profile = शून्य;
		अवरोध;
	पूर्ण

	अगर (!lcd.enabled && !keypad.enabled) अणु
		/* no device enabled, let's निकास */
		pr_err("panel driver disabled.\n");
		वापस -ENODEV;
	पूर्ण

	err = parport_रेजिस्टर_driver(&panel_driver);
	अगर (err) अणु
		pr_err("could not register with parport. Aborting.\n");
		वापस err;
	पूर्ण

	अगर (pprt)
		pr_info("panel driver registered on parport%d (io=0x%lx).\n",
			parport, pprt->port->base);
	अन्यथा
		pr_info("panel driver not yet registered\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास panel_cleanup_module(व्योम)
अणु
	parport_unरेजिस्टर_driver(&panel_driver);
पूर्ण

module_init(panel_init_module);
module_निकास(panel_cleanup_module);
MODULE_AUTHOR("Willy Tarreau");
MODULE_LICENSE("GPL");
