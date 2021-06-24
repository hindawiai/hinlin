<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम PowerMac AWACS onboard soundchips
 * Copyright (c) 2001 by Takashi Iwai <tiwai@suse.de>
 *   based on dmasound.c.
 */


#अगर_अघोषित __AWACS_H
#घोषणा __AWACS_H

/*******************************/
/* AWACs Audio Register Layout */
/*******************************/

काष्ठा awacs_regs अणु
    अचिन्हित	control;	/* Audio control रेजिस्टर */
    अचिन्हित	pad0[3];
    अचिन्हित	codec_ctrl;	/* Codec control रेजिस्टर */
    अचिन्हित	pad1[3];
    अचिन्हित	codec_stat;	/* Codec status रेजिस्टर */
    अचिन्हित	pad2[3];
    अचिन्हित	clip_count;	/* Clipping count रेजिस्टर */
    अचिन्हित	pad3[3];
    अचिन्हित	byteswap;	/* Data is little-endian अगर 1 */
पूर्ण;

/*******************/
/* Audio Bit Masks */
/*******************/

/* Audio Control Reg Bit Masks */
/* ----- ------- --- --- ----- */
#घोषणा MASK_ISFSEL	(0xf)		/* Input SubFrame Select */
#घोषणा MASK_OSFSEL	(0xf << 4)	/* Output SubFrame Select */
#घोषणा MASK_RATE	(0x7 << 8)	/* Sound Rate */
#घोषणा MASK_CNTLERR	(0x1 << 11)	/* Error */
#घोषणा MASK_PORTCHG	(0x1 << 12)	/* Port Change */
#घोषणा MASK_IEE	(0x1 << 13)	/* Enable Interrupt on Error */
#घोषणा MASK_IEPC	(0x1 << 14)	/* Enable Interrupt on Port Change */
#घोषणा MASK_SSFSEL	(0x3 << 15)	/* Status SubFrame Select */

/* Audio Codec Control Reg Bit Masks */
/* ----- ----- ------- --- --- ----- */
#घोषणा MASK_NEWECMD	(0x1 << 24)	/* Lock: करोn't ग_लिखो to reg when 1 */
#घोषणा MASK_EMODESEL	(0x3 << 22)	/* Send info out on which frame? */
#घोषणा MASK_EXMODEADDR	(0x3ff << 12)	/* Extended Mode Address -- 10 bits */
#घोषणा MASK_EXMODEDATA	(0xfff)		/* Extended Mode Data -- 12 bits */

/* Audio Codec Control Address Values / Masks */
/* ----- ----- ------- ------- ------ - ----- */
#घोषणा MASK_ADDR0	(0x0 << 12)	/* Expanded Data Mode Address 0 */
#घोषणा MASK_ADDR_MUX	MASK_ADDR0	/* Mux Control */
#घोषणा MASK_ADDR_GAIN	MASK_ADDR0

#घोषणा MASK_ADDR1	(0x1 << 12)	/* Expanded Data Mode Address 1 */
#घोषणा MASK_ADDR_MUTE	MASK_ADDR1
#घोषणा MASK_ADDR_RATE	MASK_ADDR1

#घोषणा MASK_ADDR2	(0x2 << 12)	/* Expanded Data Mode Address 2 */
#घोषणा MASK_ADDR_VOLA	MASK_ADDR2	/* Volume Control A -- Headphones */
#घोषणा MASK_ADDR_VOLHD MASK_ADDR2

#घोषणा MASK_ADDR4	(0x4 << 12)	/* Expanded Data Mode Address 4 */
#घोषणा MASK_ADDR_VOLC	MASK_ADDR4	/* Volume Control C -- Speaker */
#घोषणा MASK_ADDR_VOLSPK MASK_ADDR4

/* additional रेजिस्टरs of screamer */
#घोषणा MASK_ADDR5	(0x5 << 12)	/* Expanded Data Mode Address 5 */
#घोषणा MASK_ADDR6	(0x6 << 12)	/* Expanded Data Mode Address 6 */
#घोषणा MASK_ADDR7	(0x7 << 12)	/* Expanded Data Mode Address 7 */

/* Address 0 Bit Masks & Macros */
/* ------- - --- ----- - ------ */
#घोषणा MASK_GAINRIGHT	(0xf)		/* Gain Right Mask */
#घोषणा MASK_GAINLEFT	(0xf << 4)	/* Gain Left Mask */
#घोषणा MASK_GAINLINE	(0x1 << 8)	/* Disable Mic preamp */
#घोषणा MASK_GAINMIC	(0x0 << 8)	/* Enable Mic preamp */
#घोषणा MASK_MUX_CD	(0x1 << 9)	/* Select CD in MUX */
#घोषणा MASK_MUX_MIC	(0x1 << 10)	/* Select Mic in MUX */
#घोषणा MASK_MUX_AUDIN	(0x1 << 11)	/* Select Audio In in MUX */
#घोषणा MASK_MUX_LINE	MASK_MUX_AUDIN
#घोषणा SHIFT_GAINLINE	8
#घोषणा SHIFT_MUX_CD	9
#घोषणा SHIFT_MUX_MIC	10
#घोषणा SHIFT_MUX_LINE	11

#घोषणा GAINRIGHT(x)	((x) & MASK_GAINRIGHT)
#घोषणा GAINLEFT(x)	(((x) << 4) & MASK_GAINLEFT)

/* Address 1 Bit Masks */
/* ------- - --- ----- */
#घोषणा MASK_ADDR1RES1	(0x3)		/* Reserved */
#घोषणा MASK_RECALIBRATE (0x1 << 2)	/* Recalibrate */
#घोषणा MASK_SAMPLERATE	(0x7 << 3)	/* Sample Rate: */
#घोषणा MASK_LOOPTHRU	(0x1 << 6)	/* Loopthrough Enable */
#घोषणा SHIFT_LOOPTHRU	6
#घोषणा MASK_CMUTE	(0x1 << 7)	/* Output C (Speaker) Mute when 1 */
#घोषणा MASK_SPKMUTE	MASK_CMUTE
#घोषणा SHIFT_SPKMUTE	7
#घोषणा MASK_ADDR1RES2	(0x1 << 8)	/* Reserved */
#घोषणा MASK_AMUTE	(0x1 << 9)	/* Output A (Headphone) Mute when 1 */
#घोषणा MASK_HDMUTE	MASK_AMUTE
#घोषणा SHIFT_HDMUTE	9
#घोषणा MASK_PAROUT	(0x3 << 10)	/* Parallel Out (???) */
#घोषणा MASK_PAROUT0	(0x1 << 10)	/* Parallel Out (???) */
#घोषणा MASK_PAROUT1	(0x1 << 11)	/* Parallel Out (enable speaker) */
#घोषणा SHIFT_PAROUT	10
#घोषणा SHIFT_PAROUT0	10
#घोषणा SHIFT_PAROUT1	11

#घोषणा SAMPLERATE_48000	(0x0 << 3)	/* 48 or 44.1 kHz */
#घोषणा SAMPLERATE_32000	(0x1 << 3)	/* 32 or 29.4 kHz */
#घोषणा SAMPLERATE_24000	(0x2 << 3)	/* 24 or 22.05 kHz */
#घोषणा SAMPLERATE_19200	(0x3 << 3)	/* 19.2 or 17.64 kHz */
#घोषणा SAMPLERATE_16000	(0x4 << 3)	/* 16 or 14.7 kHz */
#घोषणा SAMPLERATE_12000	(0x5 << 3)	/* 12 or 11.025 kHz */
#घोषणा SAMPLERATE_9600		(0x6 << 3)	/* 9.6 or 8.82 kHz */
#घोषणा SAMPLERATE_8000		(0x7 << 3)	/* 8 or 7.35 kHz */

/* Address 2 & 4 Bit Masks & Macros */
/* ------- - - - --- ----- - ------ */
#घोषणा MASK_OUTVOLRIGHT (0xf)		/* Output Right Volume */
#घोषणा MASK_ADDR2RES1	(0x2 << 4)	/* Reserved */
#घोषणा MASK_ADDR4RES1	MASK_ADDR2RES1
#घोषणा MASK_OUTVOLLEFT	(0xf << 6)	/* Output Left Volume */
#घोषणा MASK_ADDR2RES2	(0x2 << 10)	/* Reserved */
#घोषणा MASK_ADDR4RES2	MASK_ADDR2RES2

#घोषणा VOLRIGHT(x)	(((~(x)) & MASK_OUTVOLRIGHT))
#घोषणा VOLLEFT(x)	(((~(x)) << 6) & MASK_OUTVOLLEFT)

/* address 6 */
#घोषणा MASK_MIC_BOOST  (0x4)		/* screamer mic boost */
#घोषणा SHIFT_MIC_BOOST	2

/* Audio Codec Status Reg Bit Masks */
/* ----- ----- ------ --- --- ----- */
#घोषणा MASK_EXTEND	(0x1 << 23)	/* Extend */
#घोषणा MASK_VALID	(0x1 << 22)	/* Valid Data? */
#घोषणा MASK_OFLEFT	(0x1 << 21)	/* Overflow Left */
#घोषणा MASK_OFRIGHT	(0x1 << 20)	/* Overflow Right */
#घोषणा MASK_ERRCODE	(0xf << 16)	/* Error Code */
#घोषणा MASK_REVISION	(0xf << 12)	/* Revision Number */
#घोषणा MASK_MFGID	(0xf << 8)	/* Mfg. ID */
#घोषणा MASK_CODSTATRES	(0xf << 4)	/* bits 4 - 7 reserved */
#घोषणा MASK_INSENSE	(0xf)		/* port sense bits: */
#घोषणा MASK_HDPCONN		8	/* headphone plugged in */
#घोषणा MASK_LOCONN		4	/* line-out plugged in */
#घोषणा MASK_LICONN		2	/* line-in plugged in */
#घोषणा MASK_MICCONN		1	/* microphone plugged in */
#घोषणा MASK_LICONN_IMAC	8	/* line-in plugged in */
#घोषणा MASK_HDPRCONN_IMAC	4	/* headphone right plugged in */
#घोषणा MASK_HDPLCONN_IMAC	2	/* headphone left plugged in */
#घोषणा MASK_LOCONN_IMAC	1	/* line-out plugged in */

/* Clipping Count Reg Bit Masks */
/* -------- ----- --- --- ----- */
#घोषणा MASK_CLIPLEFT	(0xff << 7)	/* Clipping Count, Left Channel */
#घोषणा MASK_CLIPRIGHT	(0xff)		/* Clipping Count, Right Channel */

/* DBDMA ChannelStatus Bit Masks */
/* ----- ------------- --- ----- */
#घोषणा MASK_CSERR	(0x1 << 7)	/* Error */
#घोषणा MASK_EOI	(0x1 << 6)	/* End of Input --
					   only क्रम Input Channel */
#घोषणा MASK_CSUNUSED	(0x1f << 1)	/* bits 1-5 not used */
#घोषणा MASK_WAIT	(0x1)		/* Wait */

/* Various Rates */
/* ------- ----- */
#घोषणा RATE_48000	(0x0 << 8)	/* 48 kHz */
#घोषणा RATE_44100	(0x0 << 8)	/* 44.1 kHz */
#घोषणा RATE_32000	(0x1 << 8)	/* 32 kHz */
#घोषणा RATE_29400	(0x1 << 8)	/* 29.4 kHz */
#घोषणा RATE_24000	(0x2 << 8)	/* 24 kHz */
#घोषणा RATE_22050	(0x2 << 8)	/* 22.05 kHz */
#घोषणा RATE_19200	(0x3 << 8)	/* 19.2 kHz */
#घोषणा RATE_17640	(0x3 << 8)	/* 17.64 kHz */
#घोषणा RATE_16000	(0x4 << 8)	/* 16 kHz */
#घोषणा RATE_14700	(0x4 << 8)	/* 14.7 kHz */
#घोषणा RATE_12000	(0x5 << 8)	/* 12 kHz */
#घोषणा RATE_11025	(0x5 << 8)	/* 11.025 kHz */
#घोषणा RATE_9600	(0x6 << 8)	/* 9.6 kHz */
#घोषणा RATE_8820	(0x6 << 8)	/* 8.82 kHz */
#घोषणा RATE_8000	(0x7 << 8)	/* 8 kHz */
#घोषणा RATE_7350	(0x7 << 8)	/* 7.35 kHz */

#घोषणा RATE_LOW	1	/* HIGH = 48kHz, etc;  LOW = 44.1kHz, etc. */


#पूर्ण_अगर /* __AWACS_H */
