<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_WM8776_H
#घोषणा __SOUND_WM8776_H

/*
 *   ALSA driver क्रम ICEnsemble VT17xx
 *
 *   Lowlevel functions क्रम WM8776 codec
 *
 *	Copyright (c) 2012 Ondrej Zary <linux@rainbow-software.org>
 */

#घोषणा WM8776_REG_HPLVOL	0x00
#घोषणा WM8776_REG_HPRVOL	0x01
#घोषणा WM8776_REG_HPMASTER	0x02
#घोषणा WM8776_HPVOL_MASK		0x17f		/* incl. update bit */
#घोषणा WM8776_VOL_HPZCEN		(1 << 7)	/* zero cross detect */
#घोषणा WM8776_VOL_UPDATE		(1 << 8)	/* update volume */
#घोषणा WM8776_REG_DACLVOL	0x03
#घोषणा WM8776_REG_DACRVOL	0x04
#घोषणा WM8776_REG_DACMASTER	0x05
#घोषणा WM8776_DACVOL_MASK		0x1ff		/* incl. update bit */
#घोषणा WM8776_REG_PHASESWAP	0x06
#घोषणा WM8776_PHASE_INVERTL		(1 << 0)
#घोषणा WM8776_PHASE_INVERTR		(1 << 1)
#घोषणा WM8776_REG_DACCTRL1	0x07
#घोषणा WM8776_DAC_DZCEN		(1 << 0)
#घोषणा WM8776_DAC_ATC			(1 << 1)
#घोषणा WM8776_DAC_IZD			(1 << 2)
#घोषणा WM8776_DAC_TOD			(1 << 3)
#घोषणा WM8776_DAC_PL_MASK		0xf0
#घोषणा WM8776_DAC_PL_LL		(1 << 4)	/* L chan: L संकेत */
#घोषणा WM8776_DAC_PL_LR		(2 << 4)	/* L chan: R संकेत */
#घोषणा WM8776_DAC_PL_LB		(3 << 4)	/* L chan: both */
#घोषणा WM8776_DAC_PL_RL		(1 << 6)	/* R chan: L संकेत */
#घोषणा WM8776_DAC_PL_RR		(2 << 6)	/* R chan: R संकेत */
#घोषणा WM8776_DAC_PL_RB		(3 << 6)	/* R chan: both */
#घोषणा WM8776_REG_DACMUTE	0x08
#घोषणा WM8776_DACMUTE			(1 << 0)
#घोषणा WM8776_REG_DACCTRL2	0x09
#घोषणा WM8776_DAC2_DEEMPH		(1 << 0)
#घोषणा WM8776_DAC2_ZFLAG_DISABLE	(0 << 1)
#घोषणा WM8776_DAC2_ZFLAG_OWN		(1 << 1)
#घोषणा WM8776_DAC2_ZFLAG_BOTH		(2 << 1)
#घोषणा WM8776_DAC2_ZFLAG_EITHER	(3 << 1)
#घोषणा WM8776_REG_DACIFCTRL	0x0a
#घोषणा WM8776_FMT_RIGHTJ		(0 << 0)
#घोषणा WM8776_FMT_LEFTJ		(1 << 0)
#घोषणा WM8776_FMT_I2S			(2 << 0)
#घोषणा WM8776_FMT_DSP			(3 << 0)
#घोषणा WM8776_FMT_DSP_LATE		(1 << 2)	/* in DSP mode */
#घोषणा WM8776_FMT_LRC_INVERTED		(1 << 2)	/* in other modes */
#घोषणा WM8776_FMT_BCLK_INVERTED	(1 << 3)
#घोषणा WM8776_FMT_16BIT		(0 << 4)
#घोषणा WM8776_FMT_20BIT		(1 << 4)
#घोषणा WM8776_FMT_24BIT		(2 << 4)
#घोषणा WM8776_FMT_32BIT		(3 << 4)
#घोषणा WM8776_REG_ADCIFCTRL	0x0b
#घोषणा WM8776_FMT_ADCMCLK_INVERTED	(1 << 6)
#घोषणा WM8776_FMT_ADCHPD		(1 << 8)
#घोषणा WM8776_REG_MSTRCTRL	0x0c
#घोषणा WM8776_IF_ADC256FS		(2 << 0)
#घोषणा WM8776_IF_ADC384FS		(3 << 0)
#घोषणा WM8776_IF_ADC512FS		(4 << 0)
#घोषणा WM8776_IF_ADC768FS		(5 << 0)
#घोषणा WM8776_IF_OVERSAMP64		(1 << 3)
#घोषणा WM8776_IF_DAC128FS		(0 << 4)
#घोषणा WM8776_IF_DAC192FS		(1 << 4)
#घोषणा WM8776_IF_DAC256FS		(2 << 4)
#घोषणा WM8776_IF_DAC384FS		(3 << 4)
#घोषणा WM8776_IF_DAC512FS		(4 << 4)
#घोषणा WM8776_IF_DAC768FS		(5 << 4)
#घोषणा WM8776_IF_DAC_MASTER		(1 << 7)
#घोषणा WM8776_IF_ADC_MASTER		(1 << 8)
#घोषणा WM8776_REG_PWRDOWN	0x0d
#घोषणा WM8776_PWR_PDWN			(1 << 0)
#घोषणा WM8776_PWR_ADCPD		(1 << 1)
#घोषणा WM8776_PWR_DACPD		(1 << 2)
#घोषणा WM8776_PWR_HPPD			(1 << 3)
#घोषणा WM8776_PWR_AINPD		(1 << 6)
#घोषणा WM8776_REG_ADCLVOL	0x0e
#घोषणा WM8776_REG_ADCRVOL	0x0f
#घोषणा WM8776_ADC_GAIN_MASK		0xff
#घोषणा WM8776_ADC_ZCEN			(1 << 8)
#घोषणा WM8776_REG_ALCCTRL1	0x10
#घोषणा WM8776_ALC1_LCT_MASK		0x0f	/* 0=-16dB, 1=-15dB..15=-1dB */
#घोषणा WM8776_ALC1_MAXGAIN_MASK	0x70	/* 0,1=0dB, 2=+4dB...7=+24dB */
#घोषणा WM8776_ALC1_LCSEL_MASK		0x180
#घोषणा WM8776_ALC1_LCSEL_LIMITER	(0 << 7)
#घोषणा WM8776_ALC1_LCSEL_ALCR		(1 << 7)
#घोषणा WM8776_ALC1_LCSEL_ALCL		(2 << 7)
#घोषणा WM8776_ALC1_LCSEL_ALCSTEREO	(3 << 7)
#घोषणा WM8776_REG_ALCCTRL2	0x11
#घोषणा WM8776_ALC2_HOLD_MASK		0x0f	/*0=0ms, 1=2.67ms, 2=5.33ms.. */
#घोषणा WM8776_ALC2_ZCEN		(1 << 7)
#घोषणा WM8776_ALC2_LCEN		(1 << 8)
#घोषणा WM8776_REG_ALCCTRL3	0x12
#घोषणा WM8776_ALC3_ATK_MASK		0x0f
#घोषणा WM8776_ALC3_DCY_MASK		0xf0
#घोषणा WM8776_ALC3_FDECAY		(1 << 8)
#घोषणा WM8776_REG_NOISEGATE	0x13
#घोषणा WM8776_NGAT_ENABLE		(1 << 0)
#घोषणा WM8776_NGAT_THR_MASK		0x1c	/*0=-78dB, 1=-72dB...7=-36dB */
#घोषणा WM8776_REG_LIMITER	0x14
#घोषणा WM8776_LIM_MAXATTEN_MASK	0x0f
#घोषणा WM8776_LIM_TRANWIN_MASK		0x70	/*0=0us, 1=62.5us, 2=125us.. */
#घोषणा WM8776_REG_ADCMUX	0x15
#घोषणा WM8776_ADC_MUX_AIN1		(1 << 0)
#घोषणा WM8776_ADC_MUX_AIN2		(1 << 1)
#घोषणा WM8776_ADC_MUX_AIN3		(1 << 2)
#घोषणा WM8776_ADC_MUX_AIN4		(1 << 3)
#घोषणा WM8776_ADC_MUX_AIN5		(1 << 4)
#घोषणा WM8776_ADC_MUTER		(1 << 6)
#घोषणा WM8776_ADC_MUTEL		(1 << 7)
#घोषणा WM8776_ADC_LRBOTH		(1 << 8)
#घोषणा WM8776_REG_OUTMUX	0x16
#घोषणा WM8776_OUTMUX_DAC		(1 << 0)
#घोषणा WM8776_OUTMUX_AUX		(1 << 1)
#घोषणा WM8776_OUTMUX_BYPASS		(1 << 2)
#घोषणा WM8776_REG_RESET	0x17

#घोषणा WM8776_REG_COUNT	0x17	/* करोn't cache the RESET रेजिस्टर */

काष्ठा snd_wm8776;

काष्ठा snd_wm8776_ops अणु
	व्योम (*ग_लिखो)(काष्ठा snd_wm8776 *wm, u8 addr, u8 data);
पूर्ण;

क्रमागत snd_wm8776_ctl_id अणु
	WM8776_CTL_DAC_VOL,
	WM8776_CTL_DAC_SW,
	WM8776_CTL_DAC_ZC_SW,
	WM8776_CTL_HP_VOL,
	WM8776_CTL_HP_SW,
	WM8776_CTL_HP_ZC_SW,
	WM8776_CTL_AUX_SW,
	WM8776_CTL_BYPASS_SW,
	WM8776_CTL_DAC_IZD_SW,
	WM8776_CTL_PHASE_SW,
	WM8776_CTL_DEEMPH_SW,
	WM8776_CTL_ADC_VOL,
	WM8776_CTL_ADC_SW,
	WM8776_CTL_INPUT1_SW,
	WM8776_CTL_INPUT2_SW,
	WM8776_CTL_INPUT3_SW,
	WM8776_CTL_INPUT4_SW,
	WM8776_CTL_INPUT5_SW,
	WM8776_CTL_AGC_SEL,
	WM8776_CTL_LIM_THR,
	WM8776_CTL_LIM_ATK,
	WM8776_CTL_LIM_DCY,
	WM8776_CTL_LIM_TRANWIN,
	WM8776_CTL_LIM_MAXATTN,
	WM8776_CTL_ALC_TGT,
	WM8776_CTL_ALC_ATK,
	WM8776_CTL_ALC_DCY,
	WM8776_CTL_ALC_MAXGAIN,
	WM8776_CTL_ALC_MAXATTN,
	WM8776_CTL_ALC_HLD,
	WM8776_CTL_NGT_SW,
	WM8776_CTL_NGT_THR,

	WM8776_CTL_COUNT,
पूर्ण;

#घोषणा WM8776_ENUM_MAX		16

#घोषणा WM8776_FLAG_STEREO	(1 << 0)
#घोषणा WM8776_FLAG_VOL_UPDATE	(1 << 1)
#घोषणा WM8776_FLAG_INVERT	(1 << 2)
#घोषणा WM8776_FLAG_LIM		(1 << 3)
#घोषणा WM8776_FLAG_ALC		(1 << 4)

काष्ठा snd_wm8776_ctl अणु
	स्थिर अक्षर *name;
	snd_ctl_elem_type_t type;
	स्थिर अक्षर *स्थिर क्रमागत_names[WM8776_ENUM_MAX];
	स्थिर अचिन्हित पूर्णांक *tlv;
	u16 reg1, reg2, mask1, mask2, min, max, flags;
	व्योम (*set)(काष्ठा snd_wm8776 *wm, u16 ch1, u16 ch2);
	व्योम (*get)(काष्ठा snd_wm8776 *wm, u16 *ch1, u16 *ch2);
पूर्ण;

क्रमागत snd_wm8776_agc_mode अणु
	WM8776_AGC_OFF,
	WM8776_AGC_LIM,
	WM8776_AGC_ALC_R,
	WM8776_AGC_ALC_L,
	WM8776_AGC_ALC_STEREO
पूर्ण;

काष्ठा snd_wm8776 अणु
	काष्ठा snd_card *card;
	काष्ठा snd_wm8776_ctl ctl[WM8776_CTL_COUNT];
	क्रमागत snd_wm8776_agc_mode agc_mode;
	काष्ठा snd_wm8776_ops ops;
	u16 regs[WM8776_REG_COUNT];	/* 9-bit रेजिस्टरs */
पूर्ण;



व्योम snd_wm8776_init(काष्ठा snd_wm8776 *wm);
व्योम snd_wm8776_resume(काष्ठा snd_wm8776 *wm);
व्योम snd_wm8776_set_घातer(काष्ठा snd_wm8776 *wm, u16 घातer);
व्योम snd_wm8776_volume_restore(काष्ठा snd_wm8776 *wm);
पूर्णांक snd_wm8776_build_controls(काष्ठा snd_wm8776 *wm);

#पूर्ण_अगर /* __SOUND_WM8776_H */
