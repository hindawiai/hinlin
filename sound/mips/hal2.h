<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __HAL2_H
#घोषणा __HAL2_H

/*
 *  Driver क्रम HAL2 sound processors
 *  Copyright (c) 1999 Ulf Carlsson <ulfc@bun.falkenberg.se>
 *  Copyright (c) 2001, 2002, 2003 Ladislav Michl <ladis@linux-mips.org>
 */

#समावेश <linux/types.h>

/* Indirect status रेजिस्टर */

#घोषणा H2_ISR_TSTATUS		0x01	/* RO: transaction status 1=busy */
#घोषणा H2_ISR_USTATUS		0x02	/* RO: uसमय status bit 1=armed */
#घोषणा H2_ISR_QUAD_MODE	0x04	/* codec mode 0=indigo 1=quad */
#घोषणा H2_ISR_GLOBAL_RESET_N	0x08	/* chip global reset 0=reset */
#घोषणा H2_ISR_CODEC_RESET_N	0x10	/* codec/synth reset 0=reset  */

/* Revision रेजिस्टर */

#घोषणा H2_REV_AUDIO_PRESENT	0x8000	/* RO: audio present 0=present */
#घोषणा H2_REV_BOARD_M		0x7000	/* RO: bits 14:12, board revision */
#घोषणा H2_REV_MAJOR_CHIP_M	0x00F0	/* RO: bits 7:4, major chip revision */
#घोषणा H2_REV_MINOR_CHIP_M	0x000F	/* RO: bits 3:0, minor chip revision */

/* Indirect address रेजिस्टर */

/*
 * Address of indirect पूर्णांकernal रेजिस्टर to be accessed. A ग_लिखो to this
 * रेजिस्टर initiates पढ़ो or ग_लिखो access to the indirect रेजिस्टरs in the
 * HAL2. Note that there af four indirect data रेजिस्टरs क्रम ग_लिखो access to
 * रेजिस्टरs larger than 16 byte.
 */

#घोषणा H2_IAR_TYPE_M		0xF000	/* bits 15:12, type of functional */
					/* block the रेजिस्टर resides in */
					/* 1=DMA Port */
					/* 9=Global DMA Control */
					/* 2=Bresenham */
					/* 3=Unix Timer */
#घोषणा H2_IAR_NUM_M		0x0F00	/* bits 11:8 instance of the */
					/* blockin which the indirect */
					/* रेजिस्टर resides */
					/* If IAR_TYPE_M=DMA Port: */
					/* 1=Synth In */
					/* 2=AES In */
					/* 3=AES Out */
					/* 4=DAC Out */
					/* 5=ADC Out */
					/* 6=Synth Control */
					/* If IAR_TYPE_M=Global DMA Control: */
					/* 1=Control */
					/* If IAR_TYPE_M=Bresenham: */
					/* 1=Bresenham Clock Gen 1 */
					/* 2=Bresenham Clock Gen 2 */
					/* 3=Bresenham Clock Gen 3 */
					/* If IAR_TYPE_M=Unix Timer: */
					/* 1=Unix Timer */
#घोषणा H2_IAR_ACCESS_SELECT	0x0080	/* 1=पढ़ो 0=ग_लिखो */
#घोषणा H2_IAR_PARAM		0x000C	/* Parameter Select */
#घोषणा H2_IAR_RB_INDEX_M	0x0003	/* Read Back Index */
					/* 00:word0 */
					/* 01:word1 */
					/* 10:word2 */
					/* 11:word3 */
/*
 * HAL2 पूर्णांकernal addressing
 *
 * The HAL2 has "indirect registers" (idr) which are accessed by writing to the
 * Indirect Data रेजिस्टरs. Write the address to the Indirect Address रेजिस्टर
 * to transfer the data.
 *
 * We define the H2IR_* to the पढ़ो address and H2IW_* to the ग_लिखो address and
 * H2I_* to be fields in whatever रेजिस्टर is referred to.
 *
 * When we ग_लिखो to indirect रेजिस्टरs which are larger than one word (16 bit)
 * we have to fill more than one indirect रेजिस्टर beक्रमe writing. When we पढ़ो
 * back however we have to पढ़ो several बार, each समय with dअगरferent Read
 * Back Indexes (there are defs क्रम करोing this easily).
 */

/*
 * Relay Control
 */
#घोषणा H2I_RELAY_C		0x9100
#घोषणा H2I_RELAY_C_STATE	0x01		/* state of RELAY pin संकेत */

/* DMA port enable */

#घोषणा H2I_DMA_PORT_EN		0x9104
#घोषणा H2I_DMA_PORT_EN_SY_IN	0x01		/* Synth_in DMA port */
#घोषणा H2I_DMA_PORT_EN_AESRX	0x02		/* AES receiver DMA port */
#घोषणा H2I_DMA_PORT_EN_AESTX	0x04		/* AES transmitter DMA port */
#घोषणा H2I_DMA_PORT_EN_CODECTX	0x08		/* CODEC transmit DMA port */
#घोषणा H2I_DMA_PORT_EN_CODECR	0x10		/* CODEC receive DMA port */

#घोषणा H2I_DMA_END		0x9108 		/* global dma endian select */
#घोषणा H2I_DMA_END_SY_IN	0x01		/* Synth_in DMA port */
#घोषणा H2I_DMA_END_AESRX	0x02		/* AES receiver DMA port */
#घोषणा H2I_DMA_END_AESTX	0x04		/* AES transmitter DMA port */
#घोषणा H2I_DMA_END_CODECTX	0x08		/* CODEC transmit DMA port */
#घोषणा H2I_DMA_END_CODECR	0x10		/* CODEC receive DMA port */
						/* 0=b_end 1=l_end */

#घोषणा H2I_DMA_DRV		0x910C  	/* global PBUS DMA enable */

#घोषणा H2I_SYNTH_C		0x1104		/* Synth DMA control */

#घोषणा H2I_AESRX_C		0x1204	 	/* AES RX dma control */

#घोषणा H2I_C_TS_EN		0x20		/* Timestamp enable */
#घोषणा H2I_C_TS_FRMT		0x40		/* Timestamp क्रमmat */
#घोषणा H2I_C_NAUDIO		0x80		/* Sign extend */

/* AESRX CTL, 16 bit */

#घोषणा H2I_AESTX_C		0x1304		/* AES TX DMA control */
#घोषणा H2I_AESTX_C_CLKID_SHIFT	3		/* Bresenham Clock Gen 1-3 */
#घोषणा H2I_AESTX_C_CLKID_M	0x18
#घोषणा H2I_AESTX_C_DATAT_SHIFT	8		/* 1=mono 2=stereo (3=quad) */
#घोषणा H2I_AESTX_C_DATAT_M	0x300

/* CODEC रेजिस्टरs */

#घोषणा H2I_DAC_C1		0x1404 		/* DAC DMA control, 16 bit */
#घोषणा H2I_DAC_C2		0x1408		/* DAC DMA control, 32 bit */
#घोषणा H2I_ADC_C1		0x1504 		/* ADC DMA control, 16 bit */
#घोषणा H2I_ADC_C2		0x1508		/* ADC DMA control, 32 bit */

/* Bits in CTL1 रेजिस्टर */

#घोषणा H2I_C1_DMA_SHIFT	0		/* DMA channel */
#घोषणा H2I_C1_DMA_M		0x7
#घोषणा H2I_C1_CLKID_SHIFT	3		/* Bresenham Clock Gen 1-3 */
#घोषणा H2I_C1_CLKID_M		0x18
#घोषणा H2I_C1_DATAT_SHIFT	8		/* 1=mono 2=stereo (3=quad) */
#घोषणा H2I_C1_DATAT_M		0x300

/* Bits in CTL2 रेजिस्टर */

#घोषणा H2I_C2_R_GAIN_SHIFT	0		/* right a/d input gain */
#घोषणा H2I_C2_R_GAIN_M		0xf
#घोषणा H2I_C2_L_GAIN_SHIFT	4		/* left a/d input gain */
#घोषणा H2I_C2_L_GAIN_M		0xf0
#घोषणा H2I_C2_R_SEL		0x100		/* right input select */
#घोषणा H2I_C2_L_SEL		0x200		/* left input select */
#घोषणा H2I_C2_MUTE		0x400		/* mute */
#घोषणा H2I_C2_DO1		0x00010000	/* digital output port bit 0 */
#घोषणा H2I_C2_DO2		0x00020000	/* digital output port bit 1 */
#घोषणा H2I_C2_R_ATT_SHIFT	18		/* right d/a output - */
#घोषणा H2I_C2_R_ATT_M		0x007c0000	/* attenuation */
#घोषणा H2I_C2_L_ATT_SHIFT	23		/* left d/a output - */
#घोषणा H2I_C2_L_ATT_M		0x0f800000	/* attenuation */

#घोषणा H2I_SYNTH_MAP_C		0x1104		/* synth dma handshake ctrl */

/* Clock generator CTL 1, 16 bit */

#घोषणा H2I_BRES1_C1		0x2104
#घोषणा H2I_BRES2_C1		0x2204
#घोषणा H2I_BRES3_C1		0x2304

#घोषणा H2I_BRES_C1_SHIFT	0		/* 0=48.0 1=44.1 2=aes_rx */
#घोषणा H2I_BRES_C1_M		0x03

/* Clock generator CTL 2, 32 bit */

#घोषणा H2I_BRES1_C2		0x2108
#घोषणा H2I_BRES2_C2		0x2208
#घोषणा H2I_BRES3_C2		0x2308

#घोषणा H2I_BRES_C2_INC_SHIFT	0		/* increment value */
#घोषणा H2I_BRES_C2_INC_M	0xffff
#घोषणा H2I_BRES_C2_MOD_SHIFT	16		/* modcontrol value */
#घोषणा H2I_BRES_C2_MOD_M	0xffff0000	/* modctrl=0xffff&(modinc-1) */

/* Unix समयr, 64 bit */

#घोषणा H2I_UTIME		0x3104
#घोषणा H2I_UTIME_0_LD		0xffff		/* microseconds, LSB's */
#घोषणा H2I_UTIME_1_LD0		0x0f		/* microseconds, MSB's */
#घोषणा H2I_UTIME_1_LD1		0xf0		/* tenths of microseconds */
#घोषणा H2I_UTIME_2_LD		0xffff		/* seconds, LSB's */
#घोषणा H2I_UTIME_3_LD		0xffff		/* seconds, MSB's */

काष्ठा hal2_ctl_regs अणु
	u32 _unused0[4];
	u32 isr;		/* 0x10 Status Register */
	u32 _unused1[3];
	u32 rev;		/* 0x20 Revision Register */
	u32 _unused2[3];
	u32 iar;		/* 0x30 Indirect Address Register */
	u32 _unused3[3];
	u32 idr0;		/* 0x40 Indirect Data Register 0 */
	u32 _unused4[3];
	u32 idr1;		/* 0x50 Indirect Data Register 1 */
	u32 _unused5[3];
	u32 idr2;		/* 0x60 Indirect Data Register 2 */
	u32 _unused6[3];
	u32 idr3;		/* 0x70 Indirect Data Register 3 */
पूर्ण;

काष्ठा hal2_aes_regs अणु
	u32 rx_stat[2];	/* Status रेजिस्टरs */
	u32 rx_cr[2];		/* Control रेजिस्टरs */
	u32 rx_ud[4];		/* User data winकरोw */
	u32 rx_st[24];		/* Channel status data */

	u32 tx_stat[1];	/* Status रेजिस्टर */
	u32 tx_cr[3];		/* Control रेजिस्टरs */
	u32 tx_ud[4];		/* User data winकरोw */
	u32 tx_st[24];		/* Channel status data */
पूर्ण;

काष्ठा hal2_vol_regs अणु
	u32 right;		/* Right volume */
	u32 left;		/* Left volume */
पूर्ण;

काष्ठा hal2_syn_regs अणु
	u32 _unused0[2];
	u32 page;		/* DOC Page रेजिस्टर */
	u32 regsel;		/* DOC Register selection */
	u32 dlow;		/* DOC Data low */
	u32 dhigh;		/* DOC Data high */
	u32 irq;		/* IRQ Status */
	u32 dram;		/* DRAM Access */
पूर्ण;

#पूर्ण_अगर	/* __HAL2_H */
