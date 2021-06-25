<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_CS4231_REGS_H
#घोषणा __SOUND_CS4231_REGS_H

/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Definitions क्रम CS4231 & InterWave chips & compatible chips रेजिस्टरs
 */

/* IO ports */

#घोषणा CS4231P(x)		(c_d_c_CS4231##x)

#घोषणा c_d_c_CS4231REGSEL	0
#घोषणा c_d_c_CS4231REG		1
#घोषणा c_d_c_CS4231STATUS	2
#घोषणा c_d_c_CS4231PIO		3

/* codec रेजिस्टरs */

#घोषणा CS4231_LEFT_INPUT	0x00	/* left input control */
#घोषणा CS4231_RIGHT_INPUT	0x01	/* right input control */
#घोषणा CS4231_AUX1_LEFT_INPUT	0x02	/* left AUX1 input control */
#घोषणा CS4231_AUX1_RIGHT_INPUT	0x03	/* right AUX1 input control */
#घोषणा CS4231_AUX2_LEFT_INPUT	0x04	/* left AUX2 input control */
#घोषणा CS4231_AUX2_RIGHT_INPUT	0x05	/* right AUX2 input control */
#घोषणा CS4231_LEFT_OUTPUT	0x06	/* left output control रेजिस्टर */
#घोषणा CS4231_RIGHT_OUTPUT	0x07	/* right output control रेजिस्टर */
#घोषणा CS4231_PLAYBK_FORMAT	0x08	/* घड़ी and data क्रमmat - playback - bits 7-0 MCE */
#घोषणा CS4231_IFACE_CTRL	0x09	/* पूर्णांकerface control - bits 7-2 MCE */
#घोषणा CS4231_PIN_CTRL		0x0a	/* pin control */
#घोषणा CS4231_TEST_INIT	0x0b	/* test and initialization */
#घोषणा CS4231_MISC_INFO	0x0c	/* miscellaneous inक्रमmation */
#घोषणा CS4231_LOOPBACK		0x0d	/* loopback control */
#घोषणा CS4231_PLY_UPR_CNT	0x0e	/* playback upper base count */
#घोषणा CS4231_PLY_LWR_CNT	0x0f	/* playback lower base count */
#घोषणा CS4231_ALT_FEATURE_1	0x10	/* alternate #1 feature enable */
#घोषणा AD1845_AF1_MIC_LEFT	0x10	/* alternate #1 feature + MIC left */
#घोषणा CS4231_ALT_FEATURE_2	0x11	/* alternate #2 feature enable */
#घोषणा AD1845_AF2_MIC_RIGHT	0x11	/* alternate #2 feature + MIC right */
#घोषणा CS4231_LEFT_LINE_IN	0x12	/* left line input control */
#घोषणा CS4231_RIGHT_LINE_IN	0x13	/* right line input control */
#घोषणा CS4231_TIMER_LOW	0x14	/* समयr low byte */
#घोषणा CS4231_TIMER_HIGH	0x15	/* समयr high byte */
#घोषणा CS4231_LEFT_MIC_INPUT	0x16	/* left MIC input control रेजिस्टर (InterWave only) */
#घोषणा AD1845_UPR_FREQ_SEL	0x16	/* upper byte of frequency select */
#घोषणा CS4231_RIGHT_MIC_INPUT	0x17	/* right MIC input control रेजिस्टर (InterWave only) */
#घोषणा AD1845_LWR_FREQ_SEL	0x17	/* lower byte of frequency select */
#घोषणा CS4236_EXT_REG		0x17	/* extended रेजिस्टर access */
#घोषणा CS4231_IRQ_STATUS	0x18	/* irq status रेजिस्टर */
#घोषणा CS4231_LINE_LEFT_OUTPUT	0x19	/* left line output control रेजिस्टर (InterWave only) */
#घोषणा CS4231_VERSION		0x19	/* CS4231(A) - version values */
#घोषणा CS4231_MONO_CTRL	0x1a	/* mono input/output control */
#घोषणा CS4231_LINE_RIGHT_OUTPUT 0x1b	/* right line output control रेजिस्टर (InterWave only) */
#घोषणा AD1845_PWR_DOWN		0x1b	/* घातer करोwn control */
#घोषणा CS4235_LEFT_MASTER	0x1b	/* left master output control */
#घोषणा CS4231_REC_FORMAT	0x1c	/* घड़ी and data क्रमmat - record - bits 7-0 MCE */
#घोषणा AD1845_CLOCK		0x1d	/* crystal घड़ी select and total घातer करोwn */
#घोषणा CS4235_RIGHT_MASTER	0x1d	/* right master output control */
#घोषणा CS4231_REC_UPR_CNT	0x1e	/* record upper count */
#घोषणा CS4231_REC_LWR_CNT	0x1f	/* record lower count */

/* definitions क्रम codec रेजिस्टर select port - CODECP( REGSEL ) */

#घोषणा CS4231_INIT		0x80	/* CODEC is initializing */
#घोषणा CS4231_MCE		0x40	/* mode change enable */
#घोषणा CS4231_TRD		0x20	/* transfer request disable */

/* definitions क्रम codec status रेजिस्टर - CODECP( STATUS ) */

#घोषणा CS4231_GLOBALIRQ	0x01	/* IRQ is active */

/* definitions क्रम codec irq status */

#घोषणा CS4231_PLAYBACK_IRQ	0x10
#घोषणा CS4231_RECORD_IRQ	0x20
#घोषणा CS4231_TIMER_IRQ	0x40
#घोषणा CS4231_ALL_IRQS		0x70
#घोषणा CS4231_REC_UNDERRUN	0x08
#घोषणा CS4231_REC_OVERRUN	0x04
#घोषणा CS4231_PLY_OVERRUN	0x02
#घोषणा CS4231_PLY_UNDERRUN	0x01

/* definitions क्रम CS4231_LEFT_INPUT and CS4231_RIGHT_INPUT रेजिस्टरs */

#घोषणा CS4231_ENABLE_MIC_GAIN	0x20

#घोषणा CS4231_MIXS_LINE	0x00
#घोषणा CS4231_MIXS_AUX1	0x40
#घोषणा CS4231_MIXS_MIC		0x80
#घोषणा CS4231_MIXS_ALL		0xc0

/* definitions क्रम घड़ी and data क्रमmat रेजिस्टर - CS4231_PLAYBK_FORMAT */

#घोषणा CS4231_LINEAR_8		0x00	/* 8-bit अचिन्हित data */
#घोषणा CS4231_ALAW_8		0x60	/* 8-bit A-law companded */
#घोषणा CS4231_ULAW_8		0x20	/* 8-bit U-law companded */
#घोषणा CS4231_LINEAR_16	0x40	/* 16-bit twos complement data - little endian */
#घोषणा CS4231_LINEAR_16_BIG	0xc0	/* 16-bit twos complement data - big endian */
#घोषणा CS4231_ADPCM_16		0xa0	/* 16-bit ADPCM */
#घोषणा CS4231_STEREO		0x10	/* stereo mode */
/* bits 3-1 define frequency भागisor */
#घोषणा CS4231_XTAL1		0x00	/* 24.576 crystal */
#घोषणा CS4231_XTAL2		0x01	/* 16.9344 crystal */

/* definitions क्रम पूर्णांकerface control रेजिस्टर - CS4231_IFACE_CTRL */

#घोषणा CS4231_RECORD_PIO	0x80	/* record PIO enable */
#घोषणा CS4231_PLAYBACK_PIO	0x40	/* playback PIO enable */
#घोषणा CS4231_CALIB_MODE	0x18	/* calibration mode bits */
#घोषणा CS4231_AUTOCALIB	0x08	/* स्वतः calibrate */
#घोषणा CS4231_SINGLE_DMA	0x04	/* use single DMA channel */
#घोषणा CS4231_RECORD_ENABLE	0x02	/* record enable */
#घोषणा CS4231_PLAYBACK_ENABLE	0x01	/* playback enable */

/* definitions क्रम pin control रेजिस्टर - CS4231_PIN_CTRL */

#घोषणा CS4231_IRQ_ENABLE	0x02	/* enable IRQ */
#घोषणा CS4231_XCTL1		0x40	/* बाह्यal control #1 */
#घोषणा CS4231_XCTL0		0x80	/* बाह्यal control #0 */

/* definitions क्रम test and init रेजिस्टर - CS4231_TEST_INIT */

#घोषणा CS4231_CALIB_IN_PROGRESS 0x20	/* स्वतः calibrate in progress */
#घोषणा CS4231_DMA_REQUEST	0x10	/* DMA request in progress */

/* definitions क्रम misc control रेजिस्टर - CS4231_MISC_INFO */

#घोषणा CS4231_MODE2		0x40	/* MODE 2 */
#घोषणा CS4231_IW_MODE3		0x6c	/* MODE 3 - InterWave enhanced mode */
#घोषणा CS4231_4236_MODE3	0xe0	/* MODE 3 - CS4236+ enhanced mode */

/* definitions क्रम alternate feature 1 रेजिस्टर - CS4231_ALT_FEATURE_1 */

#घोषणा	CS4231_DACZ		0x01	/* zero DAC when underrun */
#घोषणा CS4231_TIMER_ENABLE	0x40	/* codec समयr enable */
#घोषणा CS4231_OLB		0x80	/* output level bit */

/* definitions क्रम Extended Registers - CS4236+ */

#घोषणा CS4236_REG(i23val)	(((i23val << 2) & 0x10) | ((i23val >> 4) & 0x0f))
#घोषणा CS4236_I23VAL(reg)	((((reg)&0xf) << 4) | (((reg)&0x10) >> 2) | 0x8)

#घोषणा CS4236_LEFT_LINE	0x08	/* left LINE alternate volume */
#घोषणा CS4236_RIGHT_LINE	0x18	/* right LINE alternate volume */
#घोषणा CS4236_LEFT_MIC		0x28	/* left MIC volume */
#घोषणा CS4236_RIGHT_MIC	0x38	/* right MIC volume */
#घोषणा CS4236_LEFT_MIX_CTRL	0x48	/* synthesis and left input mixer control */
#घोषणा CS4236_RIGHT_MIX_CTRL	0x58	/* right input mixer control */
#घोषणा CS4236_LEFT_FM		0x68	/* left FM volume */
#घोषणा CS4236_RIGHT_FM		0x78	/* right FM volume */
#घोषणा CS4236_LEFT_DSP		0x88	/* left DSP serial port volume */
#घोषणा CS4236_RIGHT_DSP	0x98	/* right DSP serial port volume */
#घोषणा CS4236_RIGHT_LOOPBACK	0xa8	/* right loopback monitor volume */
#घोषणा CS4236_DAC_MUTE		0xb8	/* DAC mute and IFSE enable */
#घोषणा CS4236_ADC_RATE		0xc8	/* indenpendent ADC sample frequency */
#घोषणा CS4236_DAC_RATE		0xd8	/* indenpendent DAC sample frequency */
#घोषणा CS4236_LEFT_MASTER	0xe8	/* left master digital audio volume */
#घोषणा CS4236_RIGHT_MASTER	0xf8	/* right master digital audio volume */
#घोषणा CS4236_LEFT_WAVE	0x0c	/* left wavetable serial port volume */
#घोषणा CS4236_RIGHT_WAVE	0x1c	/* right wavetable serial port volume */
#घोषणा CS4236_VERSION		0x9c	/* chip version and ID */

/* definitions क्रम extended रेजिस्टरs - OPTI93X */
#घोषणा OPTi931_AUX_LEFT_INPUT	0x10
#घोषणा OPTi931_AUX_RIGHT_INPUT	0x11
#घोषणा OPTi93X_MIC_LEFT_INPUT	0x14
#घोषणा OPTi93X_MIC_RIGHT_INPUT	0x15
#घोषणा OPTi93X_OUT_LEFT	0x16
#घोषणा OPTi93X_OUT_RIGHT	0x17

#पूर्ण_अगर /* __SOUND_CS4231_REGS_H */
