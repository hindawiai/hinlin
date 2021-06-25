<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>,
 *		     Creative Lअसल, Inc.
 *  Definitions क्रम EMU10K1 (SB Live!) chips
 *
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */
#अगर_अघोषित _UAPI__SOUND_EMU10K1_H
#घोषणा _UAPI__SOUND_EMU10K1_H

#अगर_घोषित __linux__
#समावेश <linux/types.h>
#पूर्ण_अगर

/*
 * ---- FX8010 ----
 */

#घोषणा EMU10K1_CARD_CREATIVE			0x00000000
#घोषणा EMU10K1_CARD_EMUAPS			0x00000001

#घोषणा EMU10K1_FX8010_PCM_COUNT		8

/*
 * Following definition is copied from linux/types.h to support compiling
 * this header file in userspace since they are not generally available क्रम
 * uapi headers.
 */
#घोषणा __EMU10K1_DECLARE_BITMAP(name,bits) \
	अचिन्हित दीर्घ name[(bits) / (माप(अचिन्हित दीर्घ) * 8)]

/* inकाष्ठाion set */
#घोषणा iMAC0	 0x00	/* R = A + (X * Y >> 31)   ; saturation */
#घोषणा iMAC1	 0x01	/* R = A + (-X * Y >> 31)  ; saturation */
#घोषणा iMAC2	 0x02	/* R = A + (X * Y >> 31)   ; wraparound */
#घोषणा iMAC3	 0x03	/* R = A + (-X * Y >> 31)  ; wraparound */
#घोषणा iMACINT0 0x04	/* R = A + X * Y	   ; saturation */
#घोषणा iMACINT1 0x05	/* R = A + X * Y	   ; wraparound (31-bit) */
#घोषणा iACC3	 0x06	/* R = A + X + Y	   ; saturation */
#घोषणा iMACMV   0x07	/* R = A, acc += X * Y >> 31 */
#घोषणा iANDXOR  0x08	/* R = (A & X) ^ Y */
#घोषणा iTSTNEG  0x09	/* R = (A >= Y) ? X : ~X */
#घोषणा iLIMITGE 0x0a	/* R = (A >= Y) ? X : Y */
#घोषणा iLIMITLT 0x0b	/* R = (A < Y) ? X : Y */
#घोषणा iLOG	 0x0c	/* R = linear_data, A (log_data), X (max_exp), Y (क्रमmat_word) */
#घोषणा iEXP	 0x0d	/* R = log_data, A (linear_data), X (max_exp), Y (क्रमmat_word) */
#घोषणा iINTERP  0x0e	/* R = A + (X * (Y - A) >> 31)  ; saturation */
#घोषणा iSKIP    0x0f	/* R = A (cc_reg), X (count), Y (cc_test) */

/* GPRs */
#घोषणा FXBUS(x)	(0x00 + (x))	/* x = 0x00 - 0x0f */
#घोषणा EXTIN(x)	(0x10 + (x))	/* x = 0x00 - 0x0f */
#घोषणा EXTOUT(x)	(0x20 + (x))	/* x = 0x00 - 0x0f physical outs -> FXWC low 16 bits */
#घोषणा FXBUS2(x)	(0x30 + (x))	/* x = 0x00 - 0x0f copies of fx buses क्रम capture -> FXWC high 16 bits */
					/* NB: 0x31 and 0x32 are shared with Center/LFE on SB live 5.1 */

#घोषणा C_00000000	0x40
#घोषणा C_00000001	0x41
#घोषणा C_00000002	0x42
#घोषणा C_00000003	0x43
#घोषणा C_00000004	0x44
#घोषणा C_00000008	0x45
#घोषणा C_00000010	0x46
#घोषणा C_00000020	0x47
#घोषणा C_00000100	0x48
#घोषणा C_00010000	0x49
#घोषणा C_00080000	0x4a
#घोषणा C_10000000	0x4b
#घोषणा C_20000000	0x4c
#घोषणा C_40000000	0x4d
#घोषणा C_80000000	0x4e
#घोषणा C_7fffffff	0x4f
#घोषणा C_ffffffff	0x50
#घोषणा C_fffffffe	0x51
#घोषणा C_c0000000	0x52
#घोषणा C_4f1bbcdc	0x53
#घोषणा C_5a7ef9db	0x54
#घोषणा C_00100000	0x55		/* ?? */
#घोषणा GPR_ACCU	0x56		/* ACCUM, accumulator */
#घोषणा GPR_COND	0x57		/* CCR, condition रेजिस्टर */
#घोषणा GPR_NOISE0	0x58		/* noise source */
#घोषणा GPR_NOISE1	0x59		/* noise source */
#घोषणा GPR_IRQ		0x5a		/* IRQ रेजिस्टर */
#घोषणा GPR_DBAC	0x5b		/* TRAM Delay Base Address Counter */
#घोषणा GPR(x)		(FXGPREGBASE + (x)) /* मुक्त GPRs: x = 0x00 - 0xff */
#घोषणा ITRAM_DATA(x)	(TANKMEMDATAREGBASE + 0x00 + (x)) /* x = 0x00 - 0x7f */
#घोषणा ETRAM_DATA(x)	(TANKMEMDATAREGBASE + 0x80 + (x)) /* x = 0x00 - 0x1f */
#घोषणा ITRAM_ADDR(x)	(TANKMEMADDRREGBASE + 0x00 + (x)) /* x = 0x00 - 0x7f */
#घोषणा ETRAM_ADDR(x)	(TANKMEMADDRREGBASE + 0x80 + (x)) /* x = 0x00 - 0x1f */

#घोषणा A_ITRAM_DATA(x)	(TANKMEMDATAREGBASE + 0x00 + (x)) /* x = 0x00 - 0xbf */
#घोषणा A_ETRAM_DATA(x)	(TANKMEMDATAREGBASE + 0xc0 + (x)) /* x = 0x00 - 0x3f */
#घोषणा A_ITRAM_ADDR(x)	(TANKMEMADDRREGBASE + 0x00 + (x)) /* x = 0x00 - 0xbf */
#घोषणा A_ETRAM_ADDR(x)	(TANKMEMADDRREGBASE + 0xc0 + (x)) /* x = 0x00 - 0x3f */
#घोषणा A_ITRAM_CTL(x)	(A_TANKMEMCTLREGBASE + 0x00 + (x)) /* x = 0x00 - 0xbf */
#घोषणा A_ETRAM_CTL(x)	(A_TANKMEMCTLREGBASE + 0xc0 + (x)) /* x = 0x00 - 0x3f */

#घोषणा A_FXBUS(x)	(0x00 + (x))	/* x = 0x00 - 0x3f FX buses */
#घोषणा A_EXTIN(x)	(0x40 + (x))	/* x = 0x00 - 0x0f physical ins */
#घोषणा A_P16VIN(x)	(0x50 + (x))	/* x = 0x00 - 0x0f p16v ins (A2 only) "EMU32 inputs" */
#घोषणा A_EXTOUT(x)	(0x60 + (x))	/* x = 0x00 - 0x1f physical outs -> A_FXWC1 0x79-7f unknown   */
#घोषणा A_FXBUS2(x)	(0x80 + (x))	/* x = 0x00 - 0x1f extra outs used क्रम EFX capture -> A_FXWC2 */
#घोषणा A_EMU32OUTH(x)	(0xa0 + (x))	/* x = 0x00 - 0x0f "EMU32_OUT_10 - _1F" - ??? */
#घोषणा A_EMU32OUTL(x)	(0xb0 + (x))	/* x = 0x00 - 0x0f "EMU32_OUT_1 - _F" - ??? */
#घोषणा A3_EMU32IN(x)	(0x160 + (x))	/* x = 0x00 - 0x3f "EMU32_IN_00 - _3F" - Only when .device = 0x0008 */
#घोषणा A3_EMU32OUT(x)	(0x1E0 + (x))	/* x = 0x00 - 0x0f "EMU32_OUT_00 - _3F" - Only when .device = 0x0008 */
#घोषणा A_GPR(x)	(A_FXGPREGBASE + (x))

/* cc_reg स्थिरants */
#घोषणा CC_REG_NORMALIZED C_00000001
#घोषणा CC_REG_BORROW	C_00000002
#घोषणा CC_REG_MINUS	C_00000004
#घोषणा CC_REG_ZERO	C_00000008
#घोषणा CC_REG_SATURATE	C_00000010
#घोषणा CC_REG_NONZERO	C_00000100

/* FX buses */
#घोषणा FXBUS_PCM_LEFT		0x00
#घोषणा FXBUS_PCM_RIGHT		0x01
#घोषणा FXBUS_PCM_LEFT_REAR	0x02
#घोषणा FXBUS_PCM_RIGHT_REAR	0x03
#घोषणा FXBUS_MIDI_LEFT		0x04
#घोषणा FXBUS_MIDI_RIGHT	0x05
#घोषणा FXBUS_PCM_CENTER	0x06
#घोषणा FXBUS_PCM_LFE		0x07
#घोषणा FXBUS_PCM_LEFT_FRONT	0x08
#घोषणा FXBUS_PCM_RIGHT_FRONT	0x09
#घोषणा FXBUS_MIDI_REVERB	0x0c
#घोषणा FXBUS_MIDI_CHORUS	0x0d
#घोषणा FXBUS_PCM_LEFT_SIDE	0x0e
#घोषणा FXBUS_PCM_RIGHT_SIDE	0x0f
#घोषणा FXBUS_PT_LEFT		0x14
#घोषणा FXBUS_PT_RIGHT		0x15

/* Inमाला_दो */
#घोषणा EXTIN_AC97_L	   0x00	/* AC'97 capture channel - left */
#घोषणा EXTIN_AC97_R	   0x01	/* AC'97 capture channel - right */
#घोषणा EXTIN_SPDIF_CD_L   0x02	/* पूर्णांकernal S/PDIF CD - onboard - left */
#घोषणा EXTIN_SPDIF_CD_R   0x03	/* पूर्णांकernal S/PDIF CD - onboard - right */
#घोषणा EXTIN_ZOOM_L	   0x04	/* Zoom Video I2S - left */
#घोषणा EXTIN_ZOOM_R	   0x05	/* Zoom Video I2S - right */
#घोषणा EXTIN_TOSLINK_L	   0x06	/* LiveDrive - TOSLink Optical - left */
#घोषणा EXTIN_TOSLINK_R    0x07	/* LiveDrive - TOSLink Optical - right */
#घोषणा EXTIN_LINE1_L	   0x08	/* LiveDrive - Line/Mic 1 - left */
#घोषणा EXTIN_LINE1_R	   0x09	/* LiveDrive - Line/Mic 1 - right */
#घोषणा EXTIN_COAX_SPDIF_L 0x0a	/* LiveDrive - Coaxial S/PDIF - left */
#घोषणा EXTIN_COAX_SPDIF_R 0x0b /* LiveDrive - Coaxial S/PDIF - right */
#घोषणा EXTIN_LINE2_L	   0x0c	/* LiveDrive - Line/Mic 2 - left */
#घोषणा EXTIN_LINE2_R	   0x0d	/* LiveDrive - Line/Mic 2 - right */

/* Outमाला_दो */
#घोषणा EXTOUT_AC97_L	   0x00	/* AC'97 playback channel - left */
#घोषणा EXTOUT_AC97_R	   0x01	/* AC'97 playback channel - right */
#घोषणा EXTOUT_TOSLINK_L   0x02	/* LiveDrive - TOSLink Optical - left */
#घोषणा EXTOUT_TOSLINK_R   0x03	/* LiveDrive - TOSLink Optical - right */
#घोषणा EXTOUT_AC97_CENTER 0x04	/* SB Live 5.1 - center */
#घोषणा EXTOUT_AC97_LFE	   0x05 /* SB Live 5.1 - LFE */
#घोषणा EXTOUT_HEADPHONE_L 0x06	/* LiveDrive - Headphone - left */
#घोषणा EXTOUT_HEADPHONE_R 0x07	/* LiveDrive - Headphone - right */
#घोषणा EXTOUT_REAR_L	   0x08	/* Rear channel - left */
#घोषणा EXTOUT_REAR_R	   0x09	/* Rear channel - right */
#घोषणा EXTOUT_ADC_CAP_L   0x0a	/* ADC Capture buffer - left */
#घोषणा EXTOUT_ADC_CAP_R   0x0b	/* ADC Capture buffer - right */
#घोषणा EXTOUT_MIC_CAP	   0x0c	/* MIC Capture buffer */
#घोषणा EXTOUT_AC97_REAR_L 0x0d	/* SB Live 5.1 (c) 2003 - Rear Left */
#घोषणा EXTOUT_AC97_REAR_R 0x0e	/* SB Live 5.1 (c) 2003 - Rear Right */
#घोषणा EXTOUT_ACENTER	   0x11 /* Analog Center */
#घोषणा EXTOUT_ALFE	   0x12 /* Analog LFE */

/* Audigy Inमाला_दो */
#घोषणा A_EXTIN_AC97_L		0x00	/* AC'97 capture channel - left */
#घोषणा A_EXTIN_AC97_R		0x01	/* AC'97 capture channel - right */
#घोषणा A_EXTIN_SPDIF_CD_L	0x02	/* digital CD left */
#घोषणा A_EXTIN_SPDIF_CD_R	0x03	/* digital CD left */
#घोषणा A_EXTIN_OPT_SPDIF_L     0x04    /* audigy drive Optical SPDIF - left */
#घोषणा A_EXTIN_OPT_SPDIF_R     0x05    /*                              right */ 
#घोषणा A_EXTIN_LINE2_L		0x08	/* audigy drive line2/mic2 - left */
#घोषणा A_EXTIN_LINE2_R		0x09	/*                           right */
#घोषणा A_EXTIN_ADC_L		0x0a    /* Philips ADC - left */
#घोषणा A_EXTIN_ADC_R		0x0b    /*               right */
#घोषणा A_EXTIN_AUX2_L		0x0c	/* audigy drive aux2 - left */
#घोषणा A_EXTIN_AUX2_R		0x0d	/*                   - right */

/* Audigiy Outमाला_दो */
#घोषणा A_EXTOUT_FRONT_L	0x00	/* digital front left */
#घोषणा A_EXTOUT_FRONT_R	0x01	/*               right */
#घोषणा A_EXTOUT_CENTER		0x02	/* digital front center */
#घोषणा A_EXTOUT_LFE		0x03	/* digital front lfe */
#घोषणा A_EXTOUT_HEADPHONE_L	0x04	/* headphone audigy drive left */
#घोषणा A_EXTOUT_HEADPHONE_R	0x05	/*                        right */
#घोषणा A_EXTOUT_REAR_L		0x06	/* digital rear left */
#घोषणा A_EXTOUT_REAR_R		0x07	/*              right */
#घोषणा A_EXTOUT_AFRONT_L	0x08	/* analog front left */
#घोषणा A_EXTOUT_AFRONT_R	0x09	/*              right */
#घोषणा A_EXTOUT_ACENTER	0x0a	/* analog center */
#घोषणा A_EXTOUT_ALFE		0x0b	/* analog LFE */
#घोषणा A_EXTOUT_ASIDE_L	0x0c	/* analog side left  - Audigy 2 ZS */
#घोषणा A_EXTOUT_ASIDE_R	0x0d	/*             right - Audigy 2 ZS */
#घोषणा A_EXTOUT_AREAR_L	0x0e	/* analog rear left */
#घोषणा A_EXTOUT_AREAR_R	0x0f	/*             right */
#घोषणा A_EXTOUT_AC97_L		0x10	/* AC97 left (front) */
#घोषणा A_EXTOUT_AC97_R		0x11	/*      right */
#घोषणा A_EXTOUT_ADC_CAP_L	0x16	/* ADC capture buffer left */
#घोषणा A_EXTOUT_ADC_CAP_R	0x17	/*                    right */
#घोषणा A_EXTOUT_MIC_CAP	0x18	/* Mic capture buffer */

/* Audigy स्थिरants */
#घोषणा A_C_00000000	0xc0
#घोषणा A_C_00000001	0xc1
#घोषणा A_C_00000002	0xc2
#घोषणा A_C_00000003	0xc3
#घोषणा A_C_00000004	0xc4
#घोषणा A_C_00000008	0xc5
#घोषणा A_C_00000010	0xc6
#घोषणा A_C_00000020	0xc7
#घोषणा A_C_00000100	0xc8
#घोषणा A_C_00010000	0xc9
#घोषणा A_C_00000800	0xca
#घोषणा A_C_10000000	0xcb
#घोषणा A_C_20000000	0xcc
#घोषणा A_C_40000000	0xcd
#घोषणा A_C_80000000	0xce
#घोषणा A_C_7fffffff	0xcf
#घोषणा A_C_ffffffff	0xd0
#घोषणा A_C_fffffffe	0xd1
#घोषणा A_C_c0000000	0xd2
#घोषणा A_C_4f1bbcdc	0xd3
#घोषणा A_C_5a7ef9db	0xd4
#घोषणा A_C_00100000	0xd5
#घोषणा A_GPR_ACCU	0xd6		/* ACCUM, accumulator */
#घोषणा A_GPR_COND	0xd7		/* CCR, condition रेजिस्टर */
#घोषणा A_GPR_NOISE0	0xd8		/* noise source */
#घोषणा A_GPR_NOISE1	0xd9		/* noise source */
#घोषणा A_GPR_IRQ	0xda		/* IRQ रेजिस्टर */
#घोषणा A_GPR_DBAC	0xdb		/* TRAM Delay Base Address Counter - पूर्णांकernal */
#घोषणा A_GPR_DBACE	0xde		/* TRAM Delay Base Address Counter - बाह्यal */

/* definitions क्रम debug रेजिस्टर */
#घोषणा EMU10K1_DBG_ZC			0x80000000	/* zero tram counter */
#घोषणा EMU10K1_DBG_SATURATION_OCCURED	0x02000000	/* saturation control */
#घोषणा EMU10K1_DBG_SATURATION_ADDR	0x01ff0000	/* saturation address */
#घोषणा EMU10K1_DBG_SINGLE_STEP		0x00008000	/* single step mode */
#घोषणा EMU10K1_DBG_STEP		0x00004000	/* start single step */
#घोषणा EMU10K1_DBG_CONDITION_CODE	0x00003e00	/* condition code */
#घोषणा EMU10K1_DBG_SINGLE_STEP_ADDR	0x000001ff	/* single step address */

/* tank memory address line */
#अगर_अघोषित __KERNEL__
#घोषणा TANKMEMADDRREG_ADDR_MASK 0x000fffff	/* 20 bit tank address field			*/
#घोषणा TANKMEMADDRREG_CLEAR	 0x00800000	/* Clear tank memory				*/
#घोषणा TANKMEMADDRREG_ALIGN	 0x00400000	/* Align पढ़ो or ग_लिखो relative to tank access	*/
#घोषणा TANKMEMADDRREG_WRITE	 0x00200000	/* Write to tank memory				*/
#घोषणा TANKMEMADDRREG_READ	 0x00100000	/* Read from tank memory			*/
#पूर्ण_अगर

काष्ठा snd_emu10k1_fx8010_info अणु
	अचिन्हित पूर्णांक पूर्णांकernal_tram_size;	/* in samples */
	अचिन्हित पूर्णांक बाह्यal_tram_size;	/* in samples */
	अक्षर fxbus_names[16][32];		/* names of FXBUSes */
	अक्षर extin_names[16][32];		/* names of बाह्यal inमाला_दो */
	अक्षर extout_names[32][32];		/* names of बाह्यal outमाला_दो */
	अचिन्हित पूर्णांक gpr_controls;		/* count of GPR controls */
पूर्ण;

#घोषणा EMU10K1_GPR_TRANSLATION_NONE		0
#घोषणा EMU10K1_GPR_TRANSLATION_TABLE100	1
#घोषणा EMU10K1_GPR_TRANSLATION_BASS		2
#घोषणा EMU10K1_GPR_TRANSLATION_TREBLE		3
#घोषणा EMU10K1_GPR_TRANSLATION_ONOFF		4

क्रमागत emu10k1_ctl_elem_अगरace अणु
	EMU10K1_CTL_ELEM_IFACE_MIXER = 2,	/* भव mixer device */
	EMU10K1_CTL_ELEM_IFACE_PCM = 3,		/* PCM device */
पूर्ण;

काष्ठा emu10k1_ctl_elem_id अणु
	अचिन्हित पूर्णांक pad;		/* करोn't use */
	पूर्णांक अगरace;			/* पूर्णांकerface identअगरier */
	अचिन्हित पूर्णांक device;		/* device/client number */
	अचिन्हित पूर्णांक subdevice;		/* subdevice (substream) number */
	अचिन्हित अक्षर name[44];		/* ASCII name of item */
	अचिन्हित पूर्णांक index;		/* index of item */
पूर्ण;

काष्ठा snd_emu10k1_fx8010_control_gpr अणु
	काष्ठा emu10k1_ctl_elem_id id;	/* full control ID definition */
	अचिन्हित पूर्णांक vcount;		/* visible count */
	अचिन्हित पूर्णांक count;		/* count of GPR (1..16) */
	अचिन्हित लघु gpr[32];		/* GPR number(s) */
	अचिन्हित पूर्णांक value[32];		/* initial values */
	अचिन्हित पूर्णांक min;		/* minimum range */
	अचिन्हित पूर्णांक max;		/* maximum range */
	अचिन्हित पूर्णांक translation;	/* translation type (EMU10K1_GPR_TRANSLATION*) */
	स्थिर अचिन्हित पूर्णांक *tlv;
पूर्ण;

/* old ABI without TLV support */
काष्ठा snd_emu10k1_fx8010_control_old_gpr अणु
	काष्ठा emu10k1_ctl_elem_id id;
	अचिन्हित पूर्णांक vcount;
	अचिन्हित पूर्णांक count;
	अचिन्हित लघु gpr[32];
	अचिन्हित पूर्णांक value[32];
	अचिन्हित पूर्णांक min;
	अचिन्हित पूर्णांक max;
	अचिन्हित पूर्णांक translation;
पूर्ण;

काष्ठा snd_emu10k1_fx8010_code अणु
	अक्षर name[128];

	__EMU10K1_DECLARE_BITMAP(gpr_valid, 0x200); /* biपंचांगask of valid initializers */
	__u32 *gpr_map;			/* initializers */

	अचिन्हित पूर्णांक gpr_add_control_count; /* count of GPR controls to add/replace */
	काष्ठा snd_emu10k1_fx8010_control_gpr *gpr_add_controls; /* GPR controls to add/replace */

	अचिन्हित पूर्णांक gpr_del_control_count; /* count of GPR controls to हटाओ */
	काष्ठा emu10k1_ctl_elem_id *gpr_del_controls; /* IDs of GPR controls to हटाओ */

	अचिन्हित पूर्णांक gpr_list_control_count; /* count of GPR controls to list */
	अचिन्हित पूर्णांक gpr_list_control_total; /* total count of GPR controls */
	काष्ठा snd_emu10k1_fx8010_control_gpr *gpr_list_controls; /* listed GPR controls */

	__EMU10K1_DECLARE_BITMAP(tram_valid, 0x100); /* biपंचांगask of valid initializers */
	__u32 *tram_data_map;		  /* data initializers */
	__u32 *tram_addr_map;		  /* map initializers */

	__EMU10K1_DECLARE_BITMAP(code_valid, 1024); /* biपंचांगask of valid inकाष्ठाions */
	__u32 *code;			  /* one inकाष्ठाion - 64 bits */
पूर्ण;

काष्ठा snd_emu10k1_fx8010_tram अणु
	अचिन्हित पूर्णांक address;		/* 31.bit == 1 -> बाह्यal TRAM */
	अचिन्हित पूर्णांक size;		/* size in samples (4 bytes) */
	अचिन्हित पूर्णांक *samples;		/* poपूर्णांकer to samples (20-bit) */
					/* शून्य->clear memory */
पूर्ण;

काष्ठा snd_emu10k1_fx8010_pcm_rec अणु
	अचिन्हित पूर्णांक substream;		/* substream number */
	अचिन्हित पूर्णांक res1;		/* reserved */
	अचिन्हित पूर्णांक channels;		/* 16-bit channels count, zero = हटाओ this substream */
	अचिन्हित पूर्णांक tram_start;	/* ring buffer position in TRAM (in samples) */
	अचिन्हित पूर्णांक buffer_size;	/* count of buffered samples */
	अचिन्हित लघु gpr_size;		/* GPR containing size of ringbuffer in samples (host) */
	अचिन्हित लघु gpr_ptr;		/* GPR containing current poपूर्णांकer in the ring buffer (host = reset, FX8010) */
	अचिन्हित लघु gpr_count;	/* GPR containing count of samples between two पूर्णांकerrupts (host) */
	अचिन्हित लघु gpr_पंचांगpcount;	/* GPR containing current count of samples to पूर्णांकerrupt (host = set, FX8010) */
	अचिन्हित लघु gpr_trigger;	/* GPR containing trigger (activate) inक्रमmation (host) */
	अचिन्हित लघु gpr_running;	/* GPR containing info अगर PCM is running (FX8010) */
	अचिन्हित अक्षर pad;		/* reserved */
	अचिन्हित अक्षर etram[32];	/* बाह्यal TRAM address & data (one per channel) */
	अचिन्हित पूर्णांक res2;		/* reserved */
पूर्ण;

#घोषणा SNDRV_EMU10K1_VERSION		SNDRV_PROTOCOL_VERSION(1, 0, 1)

#घोषणा SNDRV_EMU10K1_IOCTL_INFO	_IOR ('H', 0x10, काष्ठा snd_emu10k1_fx8010_info)
#घोषणा SNDRV_EMU10K1_IOCTL_CODE_POKE	_IOW ('H', 0x11, काष्ठा snd_emu10k1_fx8010_code)
#घोषणा SNDRV_EMU10K1_IOCTL_CODE_PEEK	_IOWR('H', 0x12, काष्ठा snd_emu10k1_fx8010_code)
#घोषणा SNDRV_EMU10K1_IOCTL_TRAM_SETUP	_IOW ('H', 0x20, पूर्णांक)
#घोषणा SNDRV_EMU10K1_IOCTL_TRAM_POKE	_IOW ('H', 0x21, काष्ठा snd_emu10k1_fx8010_tram)
#घोषणा SNDRV_EMU10K1_IOCTL_TRAM_PEEK	_IOWR('H', 0x22, काष्ठा snd_emu10k1_fx8010_tram)
#घोषणा SNDRV_EMU10K1_IOCTL_PCM_POKE	_IOW ('H', 0x30, काष्ठा snd_emu10k1_fx8010_pcm_rec)
#घोषणा SNDRV_EMU10K1_IOCTL_PCM_PEEK	_IOWR('H', 0x31, काष्ठा snd_emu10k1_fx8010_pcm_rec)
#घोषणा SNDRV_EMU10K1_IOCTL_PVERSION	_IOR ('H', 0x40, पूर्णांक)
#घोषणा SNDRV_EMU10K1_IOCTL_STOP	_IO  ('H', 0x80)
#घोषणा SNDRV_EMU10K1_IOCTL_CONTINUE	_IO  ('H', 0x81)
#घोषणा SNDRV_EMU10K1_IOCTL_ZERO_TRAM_COUNTER _IO ('H', 0x82)
#घोषणा SNDRV_EMU10K1_IOCTL_SINGLE_STEP	_IOW ('H', 0x83, पूर्णांक)
#घोषणा SNDRV_EMU10K1_IOCTL_DBG_READ	_IOR ('H', 0x84, पूर्णांक)

#पूर्ण_अगर /* _UAPI__SOUND_EMU10K1_H */
