<शैली गुरु>
#अगर_अघोषित _HIL_H_
#घोषणा _HIL_H_

/*
 * Hewlett Packard Human Interface Loop (HP-HIL) Protocol -- header.
 *
 * Copyright (c) 2001 Brian S. Julin
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *
 * References:
 * HP-HIL Technical Reference Manual.  Hewlett Packard Product No. 45918A
 *
 * A note of thanks to HP क्रम providing and shipping reference materials
 * मुक्त of अक्षरge to help in the development of HIL support क्रम Linux.
 *
 */

#समावेश <यंत्र/types.h>

/* Physical स्थिरants relevant to raw loop/device timing. 
 */ 

#घोषणा HIL_CLOCK		8MHZ
#घोषणा HIL_EK1_CLOCK		30HZ
#घोषणा HIL_EK2_CLOCK		60HZ

#घोषणा HIL_TIMEOUT_DEV         5	/* ms */
#घोषणा HIL_TIMEOUT_DEVS	10	/* ms */
#घोषणा HIL_TIMEOUT_NORESP	10	/* ms */
#घोषणा HIL_TIMEOUT_DEVS_DATA	16	/* ms */
#घोषणा HIL_TIMEOUT_SELFTEST	200	/* ms */


/* Actual wire line coding.  These will only be useful अगर someone is 
 * implementing a software MLC to run HIL devices on a non-parisc machine.
 */

#घोषणा HIL_WIRE_PACKET_LEN	15
क्रमागत hil_wire_bitpos अणु
	HIL_WIRE_START		= 0,
	HIL_WIRE_ADDR2,
	HIL_WIRE_ADDR1,
	HIL_WIRE_ADDR0,
	HIL_WIRE_COMMAND,
	HIL_WIRE_DATA7,
	HIL_WIRE_DATA6,
	HIL_WIRE_DATA5,
	HIL_WIRE_DATA4,
	HIL_WIRE_DATA3,
	HIL_WIRE_DATA2,
	HIL_WIRE_DATA1,
	HIL_WIRE_DATA0,
	HIL_WIRE_PARITY,
	HIL_WIRE_STOP
पूर्ण;

/* HP करोcumentation uses these bit positions to refer to commands;
 * we will call these "packets".
 */
क्रमागत hil_pkt_bitpos अणु
	HIL_PKT_CMD		= 0x00000800,
	HIL_PKT_ADDR2		= 0x00000400,
	HIL_PKT_ADDR1		= 0x00000200,
	HIL_PKT_ADDR0		= 0x00000100,
	HIL_PKT_ADDR_MASK	= 0x00000700,
	HIL_PKT_ADDR_SHIFT	= 8,
	HIL_PKT_DATA7		= 0x00000080,
	HIL_PKT_DATA6		= 0x00000040,
	HIL_PKT_DATA5		= 0x00000020,
	HIL_PKT_DATA4		= 0x00000010,
	HIL_PKT_DATA3		= 0x00000008,
	HIL_PKT_DATA2		= 0x00000004,
	HIL_PKT_DATA1		= 0x00000002,
	HIL_PKT_DATA0		= 0x00000001,
	HIL_PKT_DATA_MASK	= 0x000000FF,
	HIL_PKT_DATA_SHIFT	= 0
पूर्ण;

/* The HIL MLC also has several error/status/control bits.  We extend the 
 * "packet" to include these when direct access to the MLC is available,
 * or emulate them in हालs where they are not available. 
 *
 * This way the device driver knows that the underlying MLC driver
 * has had to deal with loop errors.
 */
क्रमागत hil_error_bitpos अणु
	HIL_ERR_OB	= 0x00000800, /* MLC is busy sending an स्वतः-poll, 
					 or we have filled up the output 
					 buffer and must रुको. */
	HIL_ERR_INT	= 0x00010000, /* A normal पूर्णांकerrupt has occurred. */
	HIL_ERR_NMI	= 0x00020000, /* An NMI has occurred. */
	HIL_ERR_LERR	= 0x00040000, /* A poll didn't come back. */
	HIL_ERR_PERR	= 0x01000000, /* There was a Parity Error. */
	HIL_ERR_FERR	= 0x02000000, /* There was a Framing Error. */
	HIL_ERR_FOF	= 0x04000000  /* Input FIFO Overflowed. */
पूर्ण;

क्रमागत hil_control_bitpos अणु
	HIL_CTRL_TEST	= 0x00010000,
	HIL_CTRL_IPF	= 0x00040000,
	HIL_CTRL_APE	= 0x02000000
पूर्ण;

/* Bits 30,31 are unused, we use them to control ग_लिखो behavior. */
#घोषणा HIL_DO_ALTER_CTRL  0x40000000 /* Write MSW of packet to control 
                                          beक्रमe writing LSW to loop */
#घोषणा HIL_CTRL_ONLY      0xc0000000 /* *Only* alter the control रेजिस्टरs */

/* This gives us a 32-bit "packet" 
 */
प्रकार u32 hil_packet;


/* HIL Loop commands 
 */
क्रमागत hil_command अणु
	HIL_CMD_IFC	= 0x00,	/* Interface Clear */
	HIL_CMD_EPT	= 0x01,	/* Enter Pass-Thru Mode */
	HIL_CMD_ELB	= 0x02,	/* Enter Loop-Back Mode */
	HIL_CMD_IDD	= 0x03,	/* Identअगरy and Describe */
	HIL_CMD_DSR	= 0x04,	/* Device Soft Reset */
	HIL_CMD_PST	= 0x05,	/* Perक्रमm Self Test */
	HIL_CMD_RRG	= 0x06,	/* Read Register */
	HIL_CMD_WRG	= 0x07,	/* Write Register */
	HIL_CMD_ACF	= 0x08,	/* Auto Configure */
	HIL_CMDID_ACF	= 0x07,	/* Auto Configure bits with incremented ID */
	HIL_CMD_POL	= 0x10,	/* Poll */
	HIL_CMDCT_POL	= 0x0f,	/* Poll command bits with item count  */
	HIL_CMD_RPL	= 0x20,	/* RePoll */
	HIL_CMDCT_RPL	= 0x0f,	/* RePoll command bits with item count */
	HIL_CMD_RNM	= 0x30,	/* Report Name */
	HIL_CMD_RST	= 0x31,	/* Report Status */
	HIL_CMD_EXD	= 0x32,	/* Extended Describe */
	HIL_CMD_RSC	= 0x33,	/* Report Security Code */

	/* 0x34 to 0x3c reserved क्रम future use  */

	HIL_CMD_DKA	= 0x3d,	/* Disable Keyचयन Autorepeat */
	HIL_CMD_EK1	= 0x3e,	/* Enable Keyचयन Autorepeat 1 */
	HIL_CMD_EK2	= 0x3f,	/* Enable Keyचयन Autorepeat 2 */
	HIL_CMD_PR1	= 0x40,	/* Prompt1 */  
	HIL_CMD_PR2	= 0x41,	/* Prompt2 */
	HIL_CMD_PR3	= 0x42,	/* Prompt3 */
	HIL_CMD_PR4	= 0x43,	/* Prompt4 */
	HIL_CMD_PR5	= 0x44,	/* Prompt5 */
	HIL_CMD_PR6	= 0x45,	/* Prompt6 */
	HIL_CMD_PR7	= 0x46,	/* Prompt7 */
	HIL_CMD_PRM	= 0x47,	/* Prompt (General Purpose) */
	HIL_CMD_AK1	= 0x48,	/* Acknowledge1 */  
	HIL_CMD_AK2	= 0x49,	/* Acknowledge2 */
	HIL_CMD_AK3	= 0x4a,	/* Acknowledge3 */
	HIL_CMD_AK4	= 0x4b,	/* Acknowledge4 */
	HIL_CMD_AK5	= 0x4c,	/* Acknowledge5 */
	HIL_CMD_AK6	= 0x4d,	/* Acknowledge6 */
	HIL_CMD_AK7	= 0x4e,	/* Acknowledge7 */
	HIL_CMD_ACK	= 0x4f,	/* Acknowledge (General Purpose) */

	/* 0x50 to 0x78 reserved क्रम future use  */
	/* 0x80 to 0xEF device-specअगरic commands */
	/* 0xf0 to 0xf9 reserved क्रम future use  */

	HIL_CMD_RIO	= 0xfa,	/* Register I/O Error */
	HIL_CMD_SHR	= 0xfb,	/* System Hard Reset */
	HIL_CMD_TER	= 0xfc,	/* Transmission Error */
	HIL_CMD_CAE	= 0xfd,	/* Configuration Address Error */
	HIL_CMD_DHR	= 0xfe,	/* Device Hard Reset */

	/* 0xff is prohibited from use. */
पूर्ण;


/* 
 * Response "records" to HIL commands
 */

/* Device ID byte 
 */
#घोषणा HIL_IDD_DID_TYPE_MASK		0xe0	/* Primary type bits */
#घोषणा HIL_IDD_DID_TYPE_KB_INTEGRAL	0xa0	/* Integral keyboard */
#घोषणा HIL_IDD_DID_TYPE_KB_ITF		0xc0	/* ITD keyboard */
#घोषणा HIL_IDD_DID_TYPE_KB_RSVD	0xe0	/* Reserved keyboard type */
#घोषणा HIL_IDD_DID_TYPE_KB_LANG_MASK	0x1f	/* Keyboard locale bits */
#घोषणा HIL_IDD_DID_KBLANG_USE_ESD	0x00	/* Use ESD Locale instead */
#घोषणा HIL_IDD_DID_TYPE_ABS		0x80    /* Absolute Positioners */
#घोषणा HIL_IDD_DID_ABS_RSVD1_MASK	0xf8	/* Reserved */
#घोषणा HIL_IDD_DID_ABS_RSVD1		0x98
#घोषणा HIL_IDD_DID_ABS_TABLET_MASK	0xf8	/* Tablets and digitizers */
#घोषणा HIL_IDD_DID_ABS_TABLET		0x90
#घोषणा HIL_IDD_DID_ABS_TSCREEN_MASK	0xfc	/* Touch screens */
#घोषणा HIL_IDD_DID_ABS_TSCREEN		0x8c
#घोषणा HIL_IDD_DID_ABS_RSVD2_MASK	0xfc	/* Reserved */
#घोषणा HIL_IDD_DID_ABS_RSVD2		0x88
#घोषणा HIL_IDD_DID_ABS_RSVD3_MASK	0xfc	/* Reserved */
#घोषणा HIL_IDD_DID_ABS_RSVD3		0x80
#घोषणा HIL_IDD_DID_TYPE_REL		0x60    /* Relative Positioners */
#घोषणा HIL_IDD_DID_REL_RSVD1_MASK	0xf0	/* Reserved */
#घोषणा HIL_IDD_DID_REL_RSVD1		0x70
#घोषणा HIL_IDD_DID_REL_RSVD2_MASK	0xfc	/* Reserved */
#घोषणा HIL_IDD_DID_REL_RSVD2		0x6c
#घोषणा HIL_IDD_DID_REL_MOUSE_MASK	0xfc	/* Mouse */
#घोषणा HIL_IDD_DID_REL_MOUSE		0x68
#घोषणा HIL_IDD_DID_REL_QUAD_MASK	0xf8	/* Other Quadrature Devices */
#घोषणा HIL_IDD_DID_REL_QUAD		0x60
#घोषणा HIL_IDD_DID_TYPE_CHAR		0x40    /* Character Entry */
#घोषणा HIL_IDD_DID_CHAR_BARCODE_MASK	0xfc	/* Barcode Reader */
#घोषणा HIL_IDD_DID_CHAR_BARCODE	0x5c
#घोषणा HIL_IDD_DID_CHAR_RSVD1_MASK	0xfc	/* Reserved */
#घोषणा HIL_IDD_DID_CHAR_RSVD1		0x58
#घोषणा HIL_IDD_DID_CHAR_RSVD2_MASK	0xf8	/* Reserved */
#घोषणा HIL_IDD_DID_CHAR_RSVD2		0x50
#घोषणा HIL_IDD_DID_CHAR_RSVD3_MASK	0xf0	/* Reserved */
#घोषणा HIL_IDD_DID_CHAR_RSVD3		0x40
#घोषणा HIL_IDD_DID_TYPE_OTHER		0x20    /* Miscellaneous */
#घोषणा HIL_IDD_DID_OTHER_RSVD1_MASK	0xf0	/* Reserved */
#घोषणा HIL_IDD_DID_OTHER_RSVD1		0x30
#घोषणा HIL_IDD_DID_OTHER_BARCODE_MASK	0xfc	/* Tone Generator */
#घोषणा HIL_IDD_DID_OTHER_BARCODE	0x2c
#घोषणा HIL_IDD_DID_OTHER_RSVD2_MASK	0xfc	/* Reserved */
#घोषणा HIL_IDD_DID_OTHER_RSVD2		0x28
#घोषणा HIL_IDD_DID_OTHER_RSVD3_MASK	0xf8	/* Reserved */
#घोषणा HIL_IDD_DID_OTHER_RSVD3		0x20
#घोषणा HIL_IDD_DID_TYPE_KEYPAD		0x00	/* Vectra Keyboard */

/* IDD record header 
 */
#घोषणा HIL_IDD_HEADER_AXSET_MASK	0x03    /* Number of axis in a set */
#घोषणा HIL_IDD_HEADER_RSC		0x04	/* Supports RSC command */
#घोषणा HIL_IDD_HEADER_EXD		0x08	/* Supports EXD command */
#घोषणा HIL_IDD_HEADER_IOD		0x10	/* IOD byte to follow */
#घोषणा HIL_IDD_HEADER_16BIT		0x20	/* 16 (vs. 8) bit resolution */
#घोषणा HIL_IDD_HEADER_ABS		0x40	/* Reports Absolute Position */
#घोषणा HIL_IDD_HEADER_2X_AXIS		0x80	/* Two sets of 1-3 axis */

/* I/O Descriptor
 */
#घोषणा HIL_IDD_IOD_NBUTTON_MASK	0x07	/* Number of buttons */
#घोषणा HIL_IDD_IOD_PROXIMITY		0x08	/* Proximity in/out events */
#घोषणा HIL_IDD_IOD_PROMPT_MASK		0x70	/* Number of prompts/acks */
#घोषणा HIL_IDD_IOD_PROMPT_SHIFT	4
#घोषणा HIL_IDD_IOD_PROMPT		0x80	/* Generic prompt/ack */

#घोषणा HIL_IDD_NUM_AXES_PER_SET(header_packet) \
((header_packet) & HIL_IDD_HEADER_AXSET_MASK)

#घोषणा HIL_IDD_NUM_AXSETS(header_packet) \
(2 - !((header_packet) & HIL_IDD_HEADER_2X_AXIS))

#घोषणा HIL_IDD_LEN(header_packet) \
((4 - !(header_packet & HIL_IDD_HEADER_IOD) -			\
  2 * !(HIL_IDD_NUM_AXES_PER_SET(header_packet))) +		\
  2 * HIL_IDD_NUM_AXES_PER_SET(header_packet) *			\
 !!((header_packet) & HIL_IDD_HEADER_ABS))

/* The following HIL_IDD_* macros assume you have an array of 
 * packets and/or unpacked 8-bit data in the order that they 
 * were received.
 */

#घोषणा HIL_IDD_AXIS_COUNTS_PER_M(header_ptr) \
(!(HIL_IDD_NUM_AXSETS(*(header_ptr))) ? -1 :			\
(((*(header_ptr + 1) & HIL_PKT_DATA_MASK) +			\
  ((*(header_ptr + 2) & HIL_PKT_DATA_MASK)) << 8)		\
* ((*(header_ptr) & HIL_IDD_HEADER_16BIT) ? 100 : 1)))

#घोषणा HIL_IDD_AXIS_MAX(header_ptr, __axnum) \
((!(*(header_ptr) & HIL_IDD_HEADER_ABS) ||			\
  (HIL_IDD_NUM_AXES_PER_SET(*(header_ptr)) <= __axnum)) ? 0 :	\
 ((HIL_PKT_DATA_MASK & *((header_ptr) + 3 + 2 * __axnum)) +	\
  ((HIL_PKT_DATA_MASK & *((header_ptr) + 4 + 2 * __axnum)) << 8)))

#घोषणा HIL_IDD_IOD(header_ptr) \
(*(header_ptr + HIL_IDD_LEN((*header_ptr)) - 1))

#घोषणा HIL_IDD_HAS_GEN_PROMPT(header_ptr) \
((*header_ptr & HIL_IDD_HEADER_IOD) &&				\
 (HIL_IDD_IOD(header_ptr) & HIL_IDD_IOD_PROMPT))

#घोषणा HIL_IDD_HAS_GEN_PROXIMITY(header_ptr) \
((*header_ptr & HIL_IDD_HEADER_IOD) &&				\
 (HIL_IDD_IOD(header_ptr) & HIL_IDD_IOD_PROXIMITY))

#घोषणा HIL_IDD_NUM_BUTTONS(header_ptr) \
((*header_ptr & HIL_IDD_HEADER_IOD) ?				\
 (HIL_IDD_IOD(header_ptr) & HIL_IDD_IOD_NBUTTON_MASK) : 0)

#घोषणा HIL_IDD_NUM_PROMPTS(header_ptr) \
((*header_ptr & HIL_IDD_HEADER_IOD) ?				\
 ((HIL_IDD_IOD(header_ptr) & HIL_IDD_IOD_NPROMPT_MASK)		\
  >> HIL_IDD_IOD_PROMPT_SHIFT) : 0)

/* The response to HIL EXD commands -- the "extended describe record" */
#घोषणा	HIL_EXD_HEADER_WRG		0x03	/* Supports type2 WRG */
#घोषणा HIL_EXD_HEADER_WRG_TYPE1	0x01	/* Supports type1 WRG */
#घोषणा	HIL_EXD_HEADER_WRG_TYPE2	0x02	/* Supports type2 WRG */
#घोषणा	HIL_EXD_HEADER_RRG		0x04	/* Supports RRG command */
#घोषणा	HIL_EXD_HEADER_RNM		0x10	/* Supports RNM command */
#घोषणा HIL_EXD_HEADER_RST		0x20	/* Supports RST command */
#घोषणा HIL_EXD_HEADER_LOCALE		0x40	/* Contains locale code */

#घोषणा HIL_EXD_NUM_RRG(header_ptr) \
((*header_ptr & HIL_EXD_HEADER_RRG) ? \
 (*(header_ptr + 1) & HIL_PKT_DATA_MASK) : 0)

#घोषणा HIL_EXD_NUM_WWG(header_ptr) \
((*header_ptr & HIL_EXD_HEADER_WRG) ?				\
 (*(header_ptr + 2 - !(*header_ptr & HIL_EXD_HEADER_RRG)) &	\
    HIL_PKT_DATA_MASK) : 0)

#घोषणा HIL_EXD_LEN(header_ptr) \
(!!(*header_ptr & HIL_EXD_HEADER_RRG) +				\
 !!(*header_ptr & HIL_EXD_HEADER_WRG) +				\
 !!(*header_ptr & HIL_EXD_HEADER_LOCALE) +			\
 2 * !!(*header_ptr & HIL_EXD_HEADER_WRG_TYPE2) + 1)

#घोषणा HIL_EXD_LOCALE(header_ptr) \
(!(*header_ptr & HIL_EXD_HEADER_LOCALE) ? -1 :			\
 (*(header_ptr + HIL_EXD_LEN(header_ptr) - 1) & HIL_PKT_DATA_MASK))

#घोषणा HIL_EXD_WRG_TYPE2_LEN(header_ptr) \
(!(*header_ptr & HIL_EXD_HEADER_WRG_TYPE2) ? -1	:			\
 (*(header_ptr + HIL_EXD_LEN(header_ptr) - 2 -                  	\
    !!(*header_ptr & HIL_EXD_HEADER_LOCALE)) & HIL_PKT_DATA_MASK) +	\
 ((*(header_ptr + HIL_EXD_LEN(header_ptr) - 1 -				\
     !!(*header_ptr & HIL_EXD_HEADER_LOCALE)) & HIL_PKT_DATA_MASK) << 8))

/* Device locale codes. */ 

/* Last defined locale code.  Everything above this is "Reserved",
   and note that this same table applies to the Device ID Byte where 
   keyboards may have a nationality code which is only 5 bits. */
#घोषणा HIL_LOCALE_MAX 0x1f

/* Map to hopefully useful strings.  I was trying to make these look
   like locale.aliases strings करो; maybe that isn't the right table to
   emulate.  In either हाल, I didn't have much to work on. */
#घोषणा HIL_LOCALE_MAP \
"",			/* 0x00 Reserved */		\
"",			/* 0x01 Reserved */		\
"",			/* 0x02 Reserved */		\
"swiss.french",		/* 0x03 Swiss/French */		\
"portuguese",		/* 0x04 Portuguese */		\
"arabic",		/* 0x05 Arabic */		\
"hebrew",		/* 0x06 Hebrew */		\
"english.canadian",	/* 0x07 Canadian English */	\
"turkish",		/* 0x08 Turkish */		\
"greek",		/* 0x09 Greek */		\
"thai",			/* 0x0a Thai (Thailand) */	\
"italian",		/* 0x0b Italian */		\
"korean",		/* 0x0c Hangul (Korea) */	\
"dutch",		/* 0x0d Dutch */		\
"swedish",		/* 0x0e Swedish */		\
"german",		/* 0x0f German */		\
"chinese",		/* 0x10 Chinese-PRC */		\
"chinese",		/* 0x11 Chinese-ROC */		\
"swiss.french",		/* 0x12 Swiss/French II */	\
"spanish",		/* 0x13 Spanish */		\
"swiss.german",		/* 0x14 Swiss/German II */	\
"flemish",		/* 0x15 Belgian (Flemish) */	\
"finnish",		/* 0x16 Finnish	*/		\
"english.uk",		/* 0x17 United Kingकरोm */	\
"french.canadian",	/* 0x18 French/Canadian */	\
"swiss.german",		/* 0x19 Swiss/German */		\
"norwegian",		/* 0x1a Norwegian */		\
"french",		/* 0x1b French */		\
"danish",		/* 0x1c Danish */		\
"japanese",		/* 0x1d Katakana */		\
"spanish",		/* 0x1e Latin American/Spanish*/\
"english.us"		/* 0x1f United States */	\


/* HIL keycodes */
#घोषणा HIL_KEYCODES_SET1_TBLSIZE 128
#घोषणा HIL_KEYCODES_SET1 	\
   KEY_5,		KEY_RESERVED,	KEY_RIGHTALT,	KEY_LEFTALT,	\
   KEY_RIGHTSHIFT,	KEY_LEFTSHIFT,	KEY_LEFTCTRL,	KEY_SYSRQ,	\
   KEY_KP4,		KEY_KP8,	KEY_KP5,	KEY_KP9,	\
   KEY_KP6,		KEY_KP7,	KEY_KPCOMMA,	KEY_KPENTER,	\
   KEY_KP1,		KEY_KPSLASH,	KEY_KP2,	KEY_KPPLUS,	\
   KEY_KP3,		KEY_KPASTERISK,	KEY_KP0,	KEY_KPMINUS,	\
   KEY_B,		KEY_V,		KEY_C,		KEY_X,		\
   KEY_Z,		KEY_RESERVED,	KEY_RESERVED,   KEY_ESC,	\
   KEY_6,		KEY_F10,	KEY_3,		KEY_F11,	\
   KEY_KPDOT,		KEY_F9,		KEY_TAB /*KP*/,	KEY_F12,	\
   KEY_H,		KEY_G,		KEY_F,		KEY_D,		\
   KEY_S,		KEY_A,		KEY_RESERVED,	KEY_CAPSLOCK,	\
   KEY_U,		KEY_Y,		KEY_T,		KEY_R,		\
   KEY_E,		KEY_W,		KEY_Q,		KEY_TAB,	\
   KEY_7,		KEY_6,		KEY_5,		KEY_4,		\
   KEY_3,		KEY_2,		KEY_1,		KEY_GRAVE,	\
   KEY_F13,		KEY_F14,	KEY_F15,	KEY_F16,	\
   KEY_F17,		KEY_F18,	KEY_F19,	KEY_F20,	\
   KEY_MENU,		KEY_F4,		KEY_F3,		KEY_F2,		\
   KEY_F1,		KEY_VOLUMEUP,	KEY_STOP,	KEY_SENDखाता,	\
   KEY_SYSRQ,		KEY_F5,		KEY_F6,		KEY_F7,		\
   KEY_F8,		KEY_VOLUMEDOWN,	KEY_DEL_EOL,	KEY_DEL_EOS,	\
   KEY_8,		KEY_9,		KEY_0,		KEY_MINUS,	\
   KEY_EQUAL,		KEY_BACKSPACE,	KEY_INS_LINE,	KEY_DEL_LINE,	\
   KEY_I,		KEY_O,		KEY_P,		KEY_LEFTBRACE,	\
   KEY_RIGHTBRACE,	KEY_BACKSLASH,	KEY_INSERT,	KEY_DELETE,	\
   KEY_J,		KEY_K,		KEY_L,		KEY_SEMICOLON,	\
   KEY_APOSTROPHE,	KEY_ENTER,	KEY_HOME,	KEY_PAGEUP,	\
   KEY_M,		KEY_COMMA,	KEY_DOT,	KEY_SLASH,	\
   KEY_BACKSLASH,	KEY_SELECT,	KEY_102ND,	KEY_PAGEDOWN,	\
   KEY_N,		KEY_SPACE,	KEY_NEXT,	KEY_RESERVED,	\
   KEY_LEFT,		KEY_DOWN,	KEY_UP,		KEY_RIGHT


#घोषणा HIL_KEYCODES_SET3_TBLSIZE 128
#घोषणा HIL_KEYCODES_SET3 	\
  KEY_RESERVED,	KEY_ESC,	KEY_1,		KEY_2,			\
  KEY_3,	KEY_4,		KEY_5,		KEY_6,			\
  KEY_7,	KEY_8,		KEY_9,		KEY_0,			\
  KEY_MINUS,	KEY_EQUAL,	KEY_BACKSPACE,	KEY_TAB,		\
  KEY_Q,	KEY_W,		KEY_E,		KEY_R,			\
  KEY_T,	KEY_Y,		KEY_U,		KEY_I,			\
  KEY_O,	KEY_P,		KEY_LEFTBRACE,	KEY_RIGHTBRACE,		\
  KEY_ENTER,	KEY_LEFTCTRL,	KEY_A,		KEY_S,			\
  KEY_D,	KEY_F,		KEY_G,		KEY_H,			\
  KEY_J,	KEY_K,		KEY_L,		KEY_SEMICOLON,		\
  KEY_APOSTROPHE,KEY_GRAVE,	KEY_LEFTSHIFT,	KEY_BACKSLASH,		\
  KEY_Z,	KEY_X,		KEY_C,		KEY_V,			\
  KEY_B,	KEY_N,		KEY_M,		KEY_COMMA,		\
  KEY_DOT,	KEY_SLASH,	KEY_RIGHTSHIFT,	KEY_KPASTERISK,		\
  KEY_LEFTALT,	KEY_SPACE,	KEY_CAPSLOCK,	KEY_F1,			\
  KEY_F2,	KEY_F3,		KEY_F4,		KEY_F5,			\
  KEY_F6,	KEY_F7,		KEY_F8,		KEY_F9,			\
  KEY_F10,	KEY_NUMLOCK,	KEY_SCROLLLOCK,	KEY_KP7,		\
  KEY_KP8,	KEY_KP9,	KEY_KPMINUS,	KEY_KP4,		\
  KEY_KP5,	KEY_KP6,	KEY_KPPLUS,	KEY_KP1,		\
  KEY_KP2,	KEY_KP3,	KEY_KP0,	KEY_KPDOT,		\
  KEY_SYSRQ,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,		\
  KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,		\
  KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,		\
  KEY_UP,	KEY_LEFT,	KEY_DOWN,	KEY_RIGHT,		\
  KEY_HOME,	KEY_PAGEUP,	KEY_END,	KEY_PAGEDOWN,		\
  KEY_INSERT,	KEY_DELETE,	KEY_102ND,	KEY_RESERVED,		\
  KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,		\
  KEY_F1,	KEY_F2,		KEY_F3,		KEY_F4,			\
  KEY_F5,	KEY_F6,		KEY_F7,		KEY_F8,			\
  KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,		\
  KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED


/* Response to POL command, the "poll record header" */

#घोषणा HIL_POL_NUM_AXES_MASK	0x03	/* Number of axis reported */
#घोषणा HIL_POL_CTS		0x04	/* Device पढ़ोy to receive data */
#घोषणा HIL_POL_STATUS_PENDING	0x08	/* Device has status to report */
#घोषणा HIL_POL_CHARTYPE_MASK	0x70	/* Type of अक्षरacter data to follow */
#घोषणा HIL_POL_CHARTYPE_NONE	0x00	/* No अक्षरacter data to follow */
#घोषणा HIL_POL_CHARTYPE_RSVD1	0x10	/* Reserved Set 1 */
#घोषणा HIL_POL_CHARTYPE_ASCII	0x20	/* U.S. ASCII */
#घोषणा HIL_POL_CHARTYPE_BINARY	0x30	/* Binary data */
#घोषणा HIL_POL_CHARTYPE_SET1	0x40	/* Keycode Set 1 */
#घोषणा HIL_POL_CHARTYPE_RSVD2	0x50	/* Reserved Set 2 */
#घोषणा HIL_POL_CHARTYPE_SET2	0x60	/* Keycode Set 2 */
#घोषणा HIL_POL_CHARTYPE_SET3	0x70	/* Keycode Set 3 */
#घोषणा HIL_POL_AXIS_ALT	0x80	/* Data is from axis set 2 */


#पूर्ण_अगर /* _HIL_H_ */
