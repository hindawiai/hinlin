<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble VT17xx
 *
 *   Lowlevel functions क्रम WM8776 codec
 *
 *	Copyright (c) 2012 Ondrej Zary <linux@rainbow-software.org>
 */

#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश "wm8776.h"

/* low-level access */

अटल व्योम snd_wm8776_ग_लिखो(काष्ठा snd_wm8776 *wm, u16 addr, u16 data)
अणु
	u8 bus_addr = addr << 1 | data >> 8;	/* addr + 9th data bit */
	u8 bus_data = data & 0xff;		/* reमुख्यing 8 data bits */

	अगर (addr < WM8776_REG_RESET)
		wm->regs[addr] = data;
	wm->ops.ग_लिखो(wm, bus_addr, bus_data);
पूर्ण

/* रेजिस्टर-level functions */

अटल व्योम snd_wm8776_activate_ctl(काष्ठा snd_wm8776 *wm,
				    स्थिर अक्षर *ctl_name,
				    bool active)
अणु
	काष्ठा snd_card *card = wm->card;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_kcontrol_अस्थिर *vd;
	काष्ठा snd_ctl_elem_id elem_id;
	अचिन्हित पूर्णांक index_offset;

	स_रखो(&elem_id, 0, माप(elem_id));
	strscpy(elem_id.name, ctl_name, माप(elem_id.name));
	elem_id.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	kctl = snd_ctl_find_id(card, &elem_id);
	अगर (!kctl)
		वापस;
	index_offset = snd_ctl_get_ioff(kctl, &kctl->id);
	vd = &kctl->vd[index_offset];
	अगर (active)
		vd->access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	अन्यथा
		vd->access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_INFO, &kctl->id);
पूर्ण

अटल व्योम snd_wm8776_update_agc_ctl(काष्ठा snd_wm8776 *wm)
अणु
	पूर्णांक i, flags_on = 0, flags_off = 0;

	चयन (wm->agc_mode) अणु
	हाल WM8776_AGC_OFF:
		flags_off = WM8776_FLAG_LIM | WM8776_FLAG_ALC;
		अवरोध;
	हाल WM8776_AGC_LIM:
		flags_off = WM8776_FLAG_ALC;
		flags_on = WM8776_FLAG_LIM;
		अवरोध;
	हाल WM8776_AGC_ALC_R:
	हाल WM8776_AGC_ALC_L:
	हाल WM8776_AGC_ALC_STEREO:
		flags_off = WM8776_FLAG_LIM;
		flags_on = WM8776_FLAG_ALC;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < WM8776_CTL_COUNT; i++)
		अगर (wm->ctl[i].flags & flags_off)
			snd_wm8776_activate_ctl(wm, wm->ctl[i].name, false);
		अन्यथा अगर (wm->ctl[i].flags & flags_on)
			snd_wm8776_activate_ctl(wm, wm->ctl[i].name, true);
पूर्ण

अटल व्योम snd_wm8776_set_agc(काष्ठा snd_wm8776 *wm, u16 agc, u16 nothing)
अणु
	u16 alc1 = wm->regs[WM8776_REG_ALCCTRL1] & ~WM8776_ALC1_LCT_MASK;
	u16 alc2 = wm->regs[WM8776_REG_ALCCTRL2] & ~WM8776_ALC2_LCEN;

	चयन (agc) अणु
	हाल 0:	/* Off */
		wm->agc_mode = WM8776_AGC_OFF;
		अवरोध;
	हाल 1: /* Limiter */
		alc2 |= WM8776_ALC2_LCEN;
		wm->agc_mode = WM8776_AGC_LIM;
		अवरोध;
	हाल 2: /* ALC Right */
		alc1 |= WM8776_ALC1_LCSEL_ALCR;
		alc2 |= WM8776_ALC2_LCEN;
		wm->agc_mode = WM8776_AGC_ALC_R;
		अवरोध;
	हाल 3: /* ALC Left */
		alc1 |= WM8776_ALC1_LCSEL_ALCL;
		alc2 |= WM8776_ALC2_LCEN;
		wm->agc_mode = WM8776_AGC_ALC_L;
		अवरोध;
	हाल 4: /* ALC Stereo */
		alc1 |= WM8776_ALC1_LCSEL_ALCSTEREO;
		alc2 |= WM8776_ALC2_LCEN;
		wm->agc_mode = WM8776_AGC_ALC_STEREO;
		अवरोध;
	पूर्ण
	snd_wm8776_ग_लिखो(wm, WM8776_REG_ALCCTRL1, alc1);
	snd_wm8776_ग_लिखो(wm, WM8776_REG_ALCCTRL2, alc2);
	snd_wm8776_update_agc_ctl(wm);
पूर्ण

अटल व्योम snd_wm8776_get_agc(काष्ठा snd_wm8776 *wm, u16 *mode, u16 *nothing)
अणु
	*mode = wm->agc_mode;
पूर्ण

/* mixer controls */

अटल स्थिर DECLARE_TLV_DB_SCALE(wm8776_hp_tlv, -7400, 100, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(wm8776_dac_tlv, -12750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(wm8776_adc_tlv, -10350, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(wm8776_lct_tlv, -1600, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(wm8776_maxgain_tlv, 0, 400, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(wm8776_ngth_tlv, -7800, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(wm8776_maxatten_lim_tlv, -1200, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(wm8776_maxatten_alc_tlv, -2100, 400, 0);

अटल स्थिर काष्ठा snd_wm8776_ctl snd_wm8776_शेष_ctl[WM8776_CTL_COUNT] = अणु
	[WM8776_CTL_DAC_VOL] = अणु
		.name = "Master Playback Volume",
		.type = SNDRV_CTL_ELEM_TYPE_INTEGER,
		.tlv = wm8776_dac_tlv,
		.reg1 = WM8776_REG_DACLVOL,
		.reg2 = WM8776_REG_DACRVOL,
		.mask1 = WM8776_DACVOL_MASK,
		.mask2 = WM8776_DACVOL_MASK,
		.max = 0xff,
		.flags = WM8776_FLAG_STEREO | WM8776_FLAG_VOL_UPDATE,
	पूर्ण,
	[WM8776_CTL_DAC_SW] = अणु
		.name = "Master Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_DACCTRL1,
		.reg2 = WM8776_REG_DACCTRL1,
		.mask1 = WM8776_DAC_PL_LL,
		.mask2 = WM8776_DAC_PL_RR,
		.flags = WM8776_FLAG_STEREO,
	पूर्ण,
	[WM8776_CTL_DAC_ZC_SW] = अणु
		.name = "Master Zero Cross Detect Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_DACCTRL1,
		.mask1 = WM8776_DAC_DZCEN,
	पूर्ण,
	[WM8776_CTL_HP_VOL] = अणु
		.name = "Headphone Playback Volume",
		.type = SNDRV_CTL_ELEM_TYPE_INTEGER,
		.tlv = wm8776_hp_tlv,
		.reg1 = WM8776_REG_HPLVOL,
		.reg2 = WM8776_REG_HPRVOL,
		.mask1 = WM8776_HPVOL_MASK,
		.mask2 = WM8776_HPVOL_MASK,
		.min = 0x2f,
		.max = 0x7f,
		.flags = WM8776_FLAG_STEREO | WM8776_FLAG_VOL_UPDATE,
	पूर्ण,
	[WM8776_CTL_HP_SW] = अणु
		.name = "Headphone Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_PWRDOWN,
		.mask1 = WM8776_PWR_HPPD,
		.flags = WM8776_FLAG_INVERT,
	पूर्ण,
	[WM8776_CTL_HP_ZC_SW] = अणु
		.name = "Headphone Zero Cross Detect Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_HPLVOL,
		.reg2 = WM8776_REG_HPRVOL,
		.mask1 = WM8776_VOL_HPZCEN,
		.mask2 = WM8776_VOL_HPZCEN,
		.flags = WM8776_FLAG_STEREO,
	पूर्ण,
	[WM8776_CTL_AUX_SW] = अणु
		.name = "AUX Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_OUTMUX,
		.mask1 = WM8776_OUTMUX_AUX,
	पूर्ण,
	[WM8776_CTL_BYPASS_SW] = अणु
		.name = "Bypass Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_OUTMUX,
		.mask1 = WM8776_OUTMUX_BYPASS,
	पूर्ण,
	[WM8776_CTL_DAC_IZD_SW] = अणु
		.name = "Infinite Zero Detect Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_DACCTRL1,
		.mask1 = WM8776_DAC_IZD,
	पूर्ण,
	[WM8776_CTL_PHASE_SW] = अणु
		.name = "Phase Invert Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_PHASESWAP,
		.reg2 = WM8776_REG_PHASESWAP,
		.mask1 = WM8776_PHASE_INVERTL,
		.mask2 = WM8776_PHASE_INVERTR,
		.flags = WM8776_FLAG_STEREO,
	पूर्ण,
	[WM8776_CTL_DEEMPH_SW] = अणु
		.name = "Deemphasis Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_DACCTRL2,
		.mask1 = WM8776_DAC2_DEEMPH,
	पूर्ण,
	[WM8776_CTL_ADC_VOL] = अणु
		.name = "Input Capture Volume",
		.type = SNDRV_CTL_ELEM_TYPE_INTEGER,
		.tlv = wm8776_adc_tlv,
		.reg1 = WM8776_REG_ADCLVOL,
		.reg2 = WM8776_REG_ADCRVOL,
		.mask1 = WM8776_ADC_GAIN_MASK,
		.mask2 = WM8776_ADC_GAIN_MASK,
		.max = 0xff,
		.flags = WM8776_FLAG_STEREO | WM8776_FLAG_VOL_UPDATE,
	पूर्ण,
	[WM8776_CTL_ADC_SW] = अणु
		.name = "Input Capture Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_ADCMUX,
		.reg2 = WM8776_REG_ADCMUX,
		.mask1 = WM8776_ADC_MUTEL,
		.mask2 = WM8776_ADC_MUTER,
		.flags = WM8776_FLAG_STEREO | WM8776_FLAG_INVERT,
	पूर्ण,
	[WM8776_CTL_INPUT1_SW] = अणु
		.name = "AIN1 Capture Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_ADCMUX,
		.mask1 = WM8776_ADC_MUX_AIN1,
	पूर्ण,
	[WM8776_CTL_INPUT2_SW] = अणु
		.name = "AIN2 Capture Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_ADCMUX,
		.mask1 = WM8776_ADC_MUX_AIN2,
	पूर्ण,
	[WM8776_CTL_INPUT3_SW] = अणु
		.name = "AIN3 Capture Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_ADCMUX,
		.mask1 = WM8776_ADC_MUX_AIN3,
	पूर्ण,
	[WM8776_CTL_INPUT4_SW] = अणु
		.name = "AIN4 Capture Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_ADCMUX,
		.mask1 = WM8776_ADC_MUX_AIN4,
	पूर्ण,
	[WM8776_CTL_INPUT5_SW] = अणु
		.name = "AIN5 Capture Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_ADCMUX,
		.mask1 = WM8776_ADC_MUX_AIN5,
	पूर्ण,
	[WM8776_CTL_AGC_SEL] = अणु
		.name = "AGC Select Capture Enum",
		.type = SNDRV_CTL_ELEM_TYPE_ENUMERATED,
		.क्रमागत_names = अणु "Off", "Limiter", "ALC Right", "ALC Left",
				"ALC Stereo" पूर्ण,
		.max = 5,	/* .क्रमागत_names item count */
		.set = snd_wm8776_set_agc,
		.get = snd_wm8776_get_agc,
	पूर्ण,
	[WM8776_CTL_LIM_THR] = अणु
		.name = "Limiter Threshold Capture Volume",
		.type = SNDRV_CTL_ELEM_TYPE_INTEGER,
		.tlv = wm8776_lct_tlv,
		.reg1 = WM8776_REG_ALCCTRL1,
		.mask1 = WM8776_ALC1_LCT_MASK,
		.max = 15,
		.flags = WM8776_FLAG_LIM,
	पूर्ण,
	[WM8776_CTL_LIM_ATK] = अणु
		.name = "Limiter Attack Time Capture Enum",
		.type = SNDRV_CTL_ELEM_TYPE_ENUMERATED,
		.क्रमागत_names = अणु "0.25 ms", "0.5 ms", "1 ms", "2 ms", "4 ms",
			"8 ms", "16 ms", "32 ms", "64 ms", "128 ms", "256 ms" पूर्ण,
		.max = 11,	/* .क्रमागत_names item count */
		.reg1 = WM8776_REG_ALCCTRL3,
		.mask1 = WM8776_ALC3_ATK_MASK,
		.flags = WM8776_FLAG_LIM,
	पूर्ण,
	[WM8776_CTL_LIM_DCY] = अणु
		.name = "Limiter Decay Time Capture Enum",
		.type = SNDRV_CTL_ELEM_TYPE_ENUMERATED,
		.क्रमागत_names = अणु	"1.2 ms", "2.4 ms", "4.8 ms", "9.6 ms",
			"19.2 ms", "38.4 ms", "76.8 ms", "154 ms", "307 ms",
			"614 ms", "1.23 s" पूर्ण,
		.max = 11,	/* .क्रमागत_names item count */
		.reg1 = WM8776_REG_ALCCTRL3,
		.mask1 = WM8776_ALC3_DCY_MASK,
		.flags = WM8776_FLAG_LIM,
	पूर्ण,
	[WM8776_CTL_LIM_TRANWIN] = अणु
		.name = "Limiter Transient Window Capture Enum",
		.type = SNDRV_CTL_ELEM_TYPE_ENUMERATED,
		.क्रमागत_names = अणु	"0 us", "62.5 us", "125 us", "250 us", "500 us",
			"1 ms", "2 ms", "4 ms" पूर्ण,
		.max = 8,	/* .क्रमागत_names item count */
		.reg1 = WM8776_REG_LIMITER,
		.mask1 = WM8776_LIM_TRANWIN_MASK,
		.flags = WM8776_FLAG_LIM,
	पूर्ण,
	[WM8776_CTL_LIM_MAXATTN] = अणु
		.name = "Limiter Maximum Attenuation Capture Volume",
		.type = SNDRV_CTL_ELEM_TYPE_INTEGER,
		.tlv = wm8776_maxatten_lim_tlv,
		.reg1 = WM8776_REG_LIMITER,
		.mask1 = WM8776_LIM_MAXATTEN_MASK,
		.min = 3,
		.max = 12,
		.flags = WM8776_FLAG_LIM | WM8776_FLAG_INVERT,
	पूर्ण,
	[WM8776_CTL_ALC_TGT] = अणु
		.name = "ALC Target Level Capture Volume",
		.type = SNDRV_CTL_ELEM_TYPE_INTEGER,
		.tlv = wm8776_lct_tlv,
		.reg1 = WM8776_REG_ALCCTRL1,
		.mask1 = WM8776_ALC1_LCT_MASK,
		.max = 15,
		.flags = WM8776_FLAG_ALC,
	पूर्ण,
	[WM8776_CTL_ALC_ATK] = अणु
		.name = "ALC Attack Time Capture Enum",
		.type = SNDRV_CTL_ELEM_TYPE_ENUMERATED,
		.क्रमागत_names = अणु "8.40 ms", "16.8 ms", "33.6 ms", "67.2 ms",
			"134 ms", "269 ms", "538 ms", "1.08 s",	"2.15 s",
			"4.3 s", "8.6 s" पूर्ण,
		.max = 11,	/* .क्रमागत_names item count */
		.reg1 = WM8776_REG_ALCCTRL3,
		.mask1 = WM8776_ALC3_ATK_MASK,
		.flags = WM8776_FLAG_ALC,
	पूर्ण,
	[WM8776_CTL_ALC_DCY] = अणु
		.name = "ALC Decay Time Capture Enum",
		.type = SNDRV_CTL_ELEM_TYPE_ENUMERATED,
		.क्रमागत_names = अणु	"33.5 ms", "67.0 ms", "134 ms", "268 ms",
			"536 ms", "1.07 s", "2.14 s", "4.29 s",	"8.58 s",
			"17.2 s", "34.3 s" पूर्ण,
		.max = 11,	/* .क्रमागत_names item count */
		.reg1 = WM8776_REG_ALCCTRL3,
		.mask1 = WM8776_ALC3_DCY_MASK,
		.flags = WM8776_FLAG_ALC,
	पूर्ण,
	[WM8776_CTL_ALC_MAXGAIN] = अणु
		.name = "ALC Maximum Gain Capture Volume",
		.type = SNDRV_CTL_ELEM_TYPE_INTEGER,
		.tlv = wm8776_maxgain_tlv,
		.reg1 = WM8776_REG_ALCCTRL1,
		.mask1 = WM8776_ALC1_MAXGAIN_MASK,
		.min = 1,
		.max = 7,
		.flags = WM8776_FLAG_ALC,
	पूर्ण,
	[WM8776_CTL_ALC_MAXATTN] = अणु
		.name = "ALC Maximum Attenuation Capture Volume",
		.type = SNDRV_CTL_ELEM_TYPE_INTEGER,
		.tlv = wm8776_maxatten_alc_tlv,
		.reg1 = WM8776_REG_LIMITER,
		.mask1 = WM8776_LIM_MAXATTEN_MASK,
		.min = 10,
		.max = 15,
		.flags = WM8776_FLAG_ALC | WM8776_FLAG_INVERT,
	पूर्ण,
	[WM8776_CTL_ALC_HLD] = अणु
		.name = "ALC Hold Time Capture Enum",
		.type = SNDRV_CTL_ELEM_TYPE_ENUMERATED,
		.क्रमागत_names = अणु	"0 ms", "2.67 ms", "5.33 ms", "10.6 ms",
			"21.3 ms", "42.7 ms", "85.3 ms", "171 ms", "341 ms",
			"683 ms", "1.37 s", "2.73 s", "5.46 s", "10.9 s",
			"21.8 s", "43.7 s" पूर्ण,
		.max = 16,	/* .क्रमागत_names item count */
		.reg1 = WM8776_REG_ALCCTRL2,
		.mask1 = WM8776_ALC2_HOLD_MASK,
		.flags = WM8776_FLAG_ALC,
	पूर्ण,
	[WM8776_CTL_NGT_SW] = अणु
		.name = "Noise Gate Capture Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8776_REG_NOISEGATE,
		.mask1 = WM8776_NGAT_ENABLE,
		.flags = WM8776_FLAG_ALC,
	पूर्ण,
	[WM8776_CTL_NGT_THR] = अणु
		.name = "Noise Gate Threshold Capture Volume",
		.type = SNDRV_CTL_ELEM_TYPE_INTEGER,
		.tlv = wm8776_ngth_tlv,
		.reg1 = WM8776_REG_NOISEGATE,
		.mask1 = WM8776_NGAT_THR_MASK,
		.max = 7,
		.flags = WM8776_FLAG_ALC,
	पूर्ण,
पूर्ण;

/* exported functions */

व्योम snd_wm8776_init(काष्ठा snd_wm8776 *wm)
अणु
	पूर्णांक i;
	अटल स्थिर u16 शेष_values[] = अणु
		0x000, 0x100, 0x000,
		0x000, 0x100, 0x000,
		0x000, 0x090, 0x000, 0x000,
		0x022, 0x022, 0x022,
		0x008, 0x0cf, 0x0cf, 0x07b, 0x000,
		0x032, 0x000, 0x0a6, 0x001, 0x001
	पूर्ण;

	स_नकल(wm->ctl, snd_wm8776_शेष_ctl, माप(wm->ctl));

	snd_wm8776_ग_लिखो(wm, WM8776_REG_RESET, 0x00); /* reset */
	udelay(10);
	/* load शेषs */
	क्रम (i = 0; i < ARRAY_SIZE(शेष_values); i++)
		snd_wm8776_ग_लिखो(wm, i, शेष_values[i]);
पूर्ण

व्योम snd_wm8776_resume(काष्ठा snd_wm8776 *wm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < WM8776_REG_COUNT; i++)
		snd_wm8776_ग_लिखो(wm, i, wm->regs[i]);
पूर्ण

व्योम snd_wm8776_set_घातer(काष्ठा snd_wm8776 *wm, u16 घातer)
अणु
	snd_wm8776_ग_लिखो(wm, WM8776_REG_PWRDOWN, घातer);
पूर्ण

व्योम snd_wm8776_volume_restore(काष्ठा snd_wm8776 *wm)
अणु
	u16 val = wm->regs[WM8776_REG_DACRVOL];
	/* restore volume after MCLK stopped */
	snd_wm8776_ग_लिखो(wm, WM8776_REG_DACRVOL, val | WM8776_VOL_UPDATE);
पूर्ण

/* mixer callbacks */

अटल पूर्णांक snd_wm8776_volume_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_wm8776 *wm = snd_kcontrol_chip(kcontrol);
	पूर्णांक n = kcontrol->निजी_value;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = (wm->ctl[n].flags & WM8776_FLAG_STEREO) ? 2 : 1;
	uinfo->value.पूर्णांकeger.min = wm->ctl[n].min;
	uinfo->value.पूर्णांकeger.max = wm->ctl[n].max;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_wm8776_क्रमागत_info(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_wm8776 *wm = snd_kcontrol_chip(kcontrol);
	पूर्णांक n = kcontrol->निजी_value;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, wm->ctl[n].max,
						wm->ctl[n].क्रमागत_names);
पूर्ण

अटल पूर्णांक snd_wm8776_ctl_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wm8776 *wm = snd_kcontrol_chip(kcontrol);
	पूर्णांक n = kcontrol->निजी_value;
	u16 val1, val2;

	अगर (wm->ctl[n].get)
		wm->ctl[n].get(wm, &val1, &val2);
	अन्यथा अणु
		val1 = wm->regs[wm->ctl[n].reg1] & wm->ctl[n].mask1;
		val1 >>= __ffs(wm->ctl[n].mask1);
		अगर (wm->ctl[n].flags & WM8776_FLAG_STEREO) अणु
			val2 = wm->regs[wm->ctl[n].reg2] & wm->ctl[n].mask2;
			val2 >>= __ffs(wm->ctl[n].mask2);
			अगर (wm->ctl[n].flags & WM8776_FLAG_VOL_UPDATE)
				val2 &= ~WM8776_VOL_UPDATE;
		पूर्ण
	पूर्ण
	अगर (wm->ctl[n].flags & WM8776_FLAG_INVERT) अणु
		val1 = wm->ctl[n].max - (val1 - wm->ctl[n].min);
		अगर (wm->ctl[n].flags & WM8776_FLAG_STEREO)
			val2 = wm->ctl[n].max - (val2 - wm->ctl[n].min);
	पूर्ण
	ucontrol->value.पूर्णांकeger.value[0] = val1;
	अगर (wm->ctl[n].flags & WM8776_FLAG_STEREO)
		ucontrol->value.पूर्णांकeger.value[1] = val2;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_wm8776_ctl_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wm8776 *wm = snd_kcontrol_chip(kcontrol);
	पूर्णांक n = kcontrol->निजी_value;
	u16 val, regval1, regval2;

	/* this also works क्रम क्रमागत because value is a जोड़ */
	regval1 = ucontrol->value.पूर्णांकeger.value[0];
	regval2 = ucontrol->value.पूर्णांकeger.value[1];
	अगर (wm->ctl[n].flags & WM8776_FLAG_INVERT) अणु
		regval1 = wm->ctl[n].max - (regval1 - wm->ctl[n].min);
		regval2 = wm->ctl[n].max - (regval2 - wm->ctl[n].min);
	पूर्ण
	अगर (wm->ctl[n].set)
		wm->ctl[n].set(wm, regval1, regval2);
	अन्यथा अणु
		val = wm->regs[wm->ctl[n].reg1] & ~wm->ctl[n].mask1;
		val |= regval1 << __ffs(wm->ctl[n].mask1);
		/* both stereo controls in one रेजिस्टर */
		अगर (wm->ctl[n].flags & WM8776_FLAG_STEREO &&
				wm->ctl[n].reg1 == wm->ctl[n].reg2) अणु
			val &= ~wm->ctl[n].mask2;
			val |= regval2 << __ffs(wm->ctl[n].mask2);
		पूर्ण
		snd_wm8776_ग_लिखो(wm, wm->ctl[n].reg1, val);
		/* stereo controls in dअगरferent रेजिस्टरs */
		अगर (wm->ctl[n].flags & WM8776_FLAG_STEREO &&
				wm->ctl[n].reg1 != wm->ctl[n].reg2) अणु
			val = wm->regs[wm->ctl[n].reg2] & ~wm->ctl[n].mask2;
			val |= regval2 << __ffs(wm->ctl[n].mask2);
			अगर (wm->ctl[n].flags & WM8776_FLAG_VOL_UPDATE)
				val |= WM8776_VOL_UPDATE;
			snd_wm8776_ग_लिखो(wm, wm->ctl[n].reg2, val);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_wm8776_add_control(काष्ठा snd_wm8776 *wm, पूर्णांक num)
अणु
	काष्ठा snd_kcontrol_new cont;
	काष्ठा snd_kcontrol *ctl;

	स_रखो(&cont, 0, माप(cont));
	cont.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	cont.निजी_value = num;
	cont.name = wm->ctl[num].name;
	cont.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	अगर (wm->ctl[num].flags & WM8776_FLAG_LIM ||
	    wm->ctl[num].flags & WM8776_FLAG_ALC)
		cont.access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	cont.tlv.p = शून्य;
	cont.get = snd_wm8776_ctl_get;
	cont.put = snd_wm8776_ctl_put;

	चयन (wm->ctl[num].type) अणु
	हाल SNDRV_CTL_ELEM_TYPE_INTEGER:
		cont.info = snd_wm8776_volume_info;
		cont.access |= SNDRV_CTL_ELEM_ACCESS_TLV_READ;
		cont.tlv.p = wm->ctl[num].tlv;
		अवरोध;
	हाल SNDRV_CTL_ELEM_TYPE_BOOLEAN:
		wm->ctl[num].max = 1;
		अगर (wm->ctl[num].flags & WM8776_FLAG_STEREO)
			cont.info = snd_ctl_boolean_stereo_info;
		अन्यथा
			cont.info = snd_ctl_boolean_mono_info;
		अवरोध;
	हाल SNDRV_CTL_ELEM_TYPE_ENUMERATED:
		cont.info = snd_wm8776_क्रमागत_info;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ctl = snd_ctl_new1(&cont, wm);
	अगर (!ctl)
		वापस -ENOMEM;

	वापस snd_ctl_add(wm->card, ctl);
पूर्ण

पूर्णांक snd_wm8776_build_controls(काष्ठा snd_wm8776 *wm)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < WM8776_CTL_COUNT; i++)
		अगर (wm->ctl[i].name) अणु
			err = snd_wm8776_add_control(wm, i);
			अगर (err < 0)
				वापस err;
		पूर्ण

	वापस 0;
पूर्ण
