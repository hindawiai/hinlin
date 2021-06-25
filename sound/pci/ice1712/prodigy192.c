<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble VT1724 (Envy24HT)
 *
 *   Lowlevel functions क्रम AudioTrak Prodigy 192 cards
 *   Supported IEC958 input from optional MI/ODI/O add-on card.
 *
 *   Specअगरics (SW, HW):
 *   -------------------
 *   	* 49.5MHz crystal
 *   	* SPDIF-OUT on the card:
 *  	  - coax (through isolation transक्रमmer)/toslink supplied by
 *          74HC04 gates - 3 in parallel
 *   	  - output चयनed between on-board CD drive dig-out connector
 *          and ice1724 SPDTX pin, using 74HC02 NOR gates, controlled
 *          by GPIO20 (0 = CD dig-out, 1 = SPDTX)
 *   	* SPDTX goes straight to MI/ODI/O card's SPDIF-OUT coax
 *
 *   	* MI/ODI/O card: AK4114 based, used क्रम iec958 input only
 *   		- toslink input -> RX0
 *   		- coax input -> RX1
 *   		- 4wire protocol:
 *   			AK4114		ICE1724
 *   			------------------------------
 * 			CDTO (pin 32) -- GPIO11 pin 86
 * 			CDTI (pin 33) -- GPIO10 pin 77
 * 			CCLK (pin 34) -- GPIO9 pin 76
 * 			CSN  (pin 35) -- GPIO8 pin 75
 *   		- output data Mode 7 (24bit, I2S, slave)
 *		- both MCKO1 and MCKO2 of ak4114 are fed to FPGA, which
 *		  outमाला_दो master घड़ी to SPMCLKIN of ice1724.
 *		  Experimentally I found out that only a combination of
 *		  OCKS0=1, OCKS1=1 (128fs, 64fs output) and ice1724 -
 *		  VT1724_MT_I2S_MCLK_128X=0 (256fs input) yields correct
 *		  sampling rate. That means that the FPGA द्विगुनs the
 *		  MCK01 rate.
 *
 *	Copyright (c) 2003 Takashi Iwai <tiwai@suse.de>
 *      Copyright (c) 2003 Dimitromanolakis Apostolos <apostol@cs.utoronto.ca>
 *      Copyright (c) 2004 Kouichi ONO <co2b@ceres.dti.ne.jp>
 */      

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>

#समावेश "ice1712.h"
#समावेश "envy24ht.h"
#समावेश "prodigy192.h"
#समावेश "stac946x.h"
#समावेश <sound/tlv.h>

काष्ठा prodigy192_spec अणु
	काष्ठा ak4114 *ak4114;
	/* rate change needs atomic mute/unmute of all dacs*/
	काष्ठा mutex mute_mutex;
पूर्ण;

अटल अंतरभूत व्योम stac9460_put(काष्ठा snd_ice1712 *ice, पूर्णांक reg, अचिन्हित अक्षर val)
अणु
	snd_vt1724_ग_लिखो_i2c(ice, PRODIGY192_STAC9460_ADDR, reg, val);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर stac9460_get(काष्ठा snd_ice1712 *ice, पूर्णांक reg)
अणु
	वापस snd_vt1724_पढ़ो_i2c(ice, PRODIGY192_STAC9460_ADDR, reg);
पूर्ण

/*
 * DAC mute control
 */

/*
 * idx = STAC9460 volume रेजिस्टर number, mute: 0 = mute, 1 = unmute
 */
अटल पूर्णांक stac9460_dac_mute(काष्ठा snd_ice1712 *ice, पूर्णांक idx,
		अचिन्हित अक्षर mute)
अणु
	अचिन्हित अक्षर new, old;
	पूर्णांक change;
	old = stac9460_get(ice, idx);
	new = (~mute << 7 & 0x80) | (old & ~0x80);
	change = (new != old);
	अगर (change)
		/* dev_dbg(ice->card->dev, "Volume register 0x%02x: 0x%02x\n", idx, new);*/
		stac9460_put(ice, idx, new);
	वापस change;
पूर्ण

#घोषणा stac9460_dac_mute_info		snd_ctl_boolean_mono_info

अटल पूर्णांक stac9460_dac_mute_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val;
	पूर्णांक idx;

	अगर (kcontrol->निजी_value)
		idx = STAC946X_MASTER_VOLUME;
	अन्यथा
		idx  = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id) + STAC946X_LF_VOLUME;
	val = stac9460_get(ice, idx);
	ucontrol->value.पूर्णांकeger.value[0] = (~val >> 7) & 0x1;
	वापस 0;
पूर्ण

अटल पूर्णांक stac9460_dac_mute_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा prodigy192_spec *spec = ice->spec;
	पूर्णांक idx, change;

	अगर (kcontrol->निजी_value)
		idx = STAC946X_MASTER_VOLUME;
	अन्यथा
		idx  = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id) + STAC946X_LF_VOLUME;
	/* due to possible conflicts with stac9460_set_rate_val, mutexing */
	mutex_lock(&spec->mute_mutex);
	/*
	dev_dbg(ice->card->dev, "Mute put: reg 0x%02x, ctrl value: 0x%02x\n", idx,
	       ucontrol->value.पूर्णांकeger.value[0]);
	*/
	change = stac9460_dac_mute(ice, idx, ucontrol->value.पूर्णांकeger.value[0]);
	mutex_unlock(&spec->mute_mutex);
	वापस change;
पूर्ण

/*
 * DAC volume attenuation mixer control
 */
अटल पूर्णांक stac9460_dac_vol_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;			/* mute */
	uinfo->value.पूर्णांकeger.max = 0x7f;		/* 0dB */
	वापस 0;
पूर्ण

अटल पूर्णांक stac9460_dac_vol_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx;
	अचिन्हित अक्षर vol;

	अगर (kcontrol->निजी_value)
		idx = STAC946X_MASTER_VOLUME;
	अन्यथा
		idx  = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id) + STAC946X_LF_VOLUME;
	vol = stac9460_get(ice, idx) & 0x7f;
	ucontrol->value.पूर्णांकeger.value[0] = 0x7f - vol;

	वापस 0;
पूर्ण

अटल पूर्णांक stac9460_dac_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx;
	अचिन्हित अक्षर पंचांगp, ovol, nvol;
	पूर्णांक change;

	अगर (kcontrol->निजी_value)
		idx = STAC946X_MASTER_VOLUME;
	अन्यथा
		idx  = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id) + STAC946X_LF_VOLUME;
	nvol = ucontrol->value.पूर्णांकeger.value[0];
	पंचांगp = stac9460_get(ice, idx);
	ovol = 0x7f - (पंचांगp & 0x7f);
	change = (ovol != nvol);
	अगर (change) अणु
		ovol =  (0x7f - nvol) | (पंचांगp & 0x80);
		/*
		dev_dbg(ice->card->dev, "DAC Volume: reg 0x%02x: 0x%02x\n",
		       idx, ovol);
		*/
		stac9460_put(ice, idx, (0x7f - nvol) | (पंचांगp & 0x80));
	पूर्ण
	वापस change;
पूर्ण

/*
 * ADC mute control
 */
#घोषणा stac9460_adc_mute_info		snd_ctl_boolean_stereo_info

अटल पूर्णांक stac9460_adc_mute_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val;
	पूर्णांक i;

	क्रम (i = 0; i < 2; ++i) अणु
		val = stac9460_get(ice, STAC946X_MIC_L_VOLUME + i);
		ucontrol->value.पूर्णांकeger.value[i] = ~val>>7 & 0x1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stac9460_adc_mute_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर new, old;
	पूर्णांक i, reg;
	पूर्णांक change;

	क्रम (i = 0; i < 2; ++i) अणु
		reg = STAC946X_MIC_L_VOLUME + i;
		old = stac9460_get(ice, reg);
		new = (~ucontrol->value.पूर्णांकeger.value[i]<<7&0x80) | (old&~0x80);
		change = (new != old);
		अगर (change)
			stac9460_put(ice, reg, new);
	पूर्ण

	वापस change;
पूर्ण

/*
 * ADC gain mixer control
 */
अटल पूर्णांक stac9460_adc_vol_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;		/* 0dB */
	uinfo->value.पूर्णांकeger.max = 0x0f;	/* 22.5dB */
	वापस 0;
पूर्ण

अटल पूर्णांक stac9460_adc_vol_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक i, reg;
	अचिन्हित अक्षर vol;

	क्रम (i = 0; i < 2; ++i) अणु
		reg = STAC946X_MIC_L_VOLUME + i;
		vol = stac9460_get(ice, reg) & 0x0f;
		ucontrol->value.पूर्णांकeger.value[i] = 0x0f - vol;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stac9460_adc_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक i, reg;
	अचिन्हित अक्षर ovol, nvol;
	पूर्णांक change;

	क्रम (i = 0; i < 2; ++i) अणु
		reg = STAC946X_MIC_L_VOLUME + i;
		nvol = ucontrol->value.पूर्णांकeger.value[i] & 0x0f;
		ovol = 0x0f - stac9460_get(ice, reg);
		change = ((ovol & 0x0f)  != nvol);
		अगर (change)
			stac9460_put(ice, reg, (0x0f - nvol) | (ovol & ~0x0f));
	पूर्ण

	वापस change;
पूर्ण

अटल पूर्णांक stac9460_mic_sw_info(काष्ठा snd_kcontrol *kcontrol,
	       			काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु "Line In", "Mic" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण


अटल पूर्णांक stac9460_mic_sw_get(काष्ठा snd_kcontrol *kcontrol,
	       		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val;
		
	val = stac9460_get(ice, STAC946X_GENERAL_PURPOSE);
	ucontrol->value.क्रमागतerated.item[0] = (val >> 7) & 0x1;
	वापस 0;
पूर्ण

अटल पूर्णांक stac9460_mic_sw_put(काष्ठा snd_kcontrol *kcontrol,
	       		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर new, old;
	पूर्णांक change;
	old = stac9460_get(ice, STAC946X_GENERAL_PURPOSE);
	new = (ucontrol->value.क्रमागतerated.item[0] << 7 & 0x80) | (old & ~0x80);
	change = (new != old);
	अगर (change)
		stac9460_put(ice, STAC946X_GENERAL_PURPOSE, new);
	वापस change;
पूर्ण
/*
 * Handler क्रम setting correct codec rate - called when rate change is detected
 */
अटल व्योम stac9460_set_rate_val(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित अक्षर old, new;
	पूर्णांक idx;
	अचिन्हित अक्षर changed[7];
	काष्ठा prodigy192_spec *spec = ice->spec;

	अगर (rate == 0)  /* no hपूर्णांक - S/PDIF input is master, simply वापस */
		वापस;
	अन्यथा अगर (rate <= 48000)
		new = 0x08;	/* 256x, base rate mode */
	अन्यथा अगर (rate <= 96000)
		new = 0x11;	/* 256x, mid rate mode */
	अन्यथा
		new = 0x12;	/* 128x, high rate mode */
	old = stac9460_get(ice, STAC946X_MASTER_CLOCKING);
	अगर (old == new)
		वापस;
	/* change detected, setting master घड़ी, muting first */
	/* due to possible conflicts with mute controls - mutexing */
	mutex_lock(&spec->mute_mutex);
	/* we have to remember current mute status क्रम each DAC */
	क्रम (idx = 0; idx < 7 ; ++idx)
		changed[idx] = stac9460_dac_mute(ice,
				STAC946X_MASTER_VOLUME + idx, 0);
	/*dev_dbg(ice->card->dev, "Rate change: %d, new MC: 0x%02x\n", rate, new);*/
	stac9460_put(ice, STAC946X_MASTER_CLOCKING, new);
	udelay(10);
	/* unmuting - only originally unmuted dacs -
	 * i.e. those changed when muting */
	क्रम (idx = 0; idx < 7 ; ++idx) अणु
		अगर (changed[idx])
			stac9460_dac_mute(ice, STAC946X_MASTER_VOLUME + idx, 1);
	पूर्ण
	mutex_unlock(&spec->mute_mutex);
पूर्ण


अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_dac, -19125, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_adc, 0, 150, 0);

/*
 * mixers
 */

अटल स्थिर काष्ठा snd_kcontrol_new stac_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Master Playback Switch",
		.info = stac9460_dac_mute_info,
		.get = stac9460_dac_mute_get,
		.put = stac9460_dac_mute_put,
		.निजी_value = 1,
		.tlv = अणु .p = db_scale_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Master Playback Volume",
		.info = stac9460_dac_vol_info,
		.get = stac9460_dac_vol_get,
		.put = stac9460_dac_vol_put,
		.निजी_value = 1,
		.tlv = अणु .p = db_scale_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "DAC Switch",
		.count = 6,
		.info = stac9460_dac_mute_info,
		.get = stac9460_dac_mute_get,
		.put = stac9460_dac_mute_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "DAC Volume",
		.count = 6,
		.info = stac9460_dac_vol_info,
		.get = stac9460_dac_vol_get,
		.put = stac9460_dac_vol_put,
		.tlv = अणु .p = db_scale_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "ADC Capture Switch",
		.count = 1,
		.info = stac9460_adc_mute_info,
		.get = stac9460_adc_mute_get,
		.put = stac9460_adc_mute_put,

	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "ADC Capture Volume",
		.count = 1,
		.info = stac9460_adc_vol_info,
		.get = stac9460_adc_vol_get,
		.put = stac9460_adc_vol_put,
		.tlv = अणु .p = db_scale_adc पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Analog Capture Input",
		.info = stac9460_mic_sw_info,
		.get = stac9460_mic_sw_get,
		.put = stac9460_mic_sw_put,

	पूर्ण,
पूर्ण;

/* AK4114 - ICE1724 connections on Prodigy192 + MI/ODI/O */
/* CDTO (pin 32) -- GPIO11 pin 86
 * CDTI (pin 33) -- GPIO10 pin 77
 * CCLK (pin 34) -- GPIO9 pin 76
 * CSN  (pin 35) -- GPIO8 pin 75
 */
#घोषणा AK4114_ADDR	0x00 /* C1-C0: Chip Address
			      * (According to datasheet fixed to ै 00ै )
			      */

/*
 * 4wire ak4114 protocol - writing data
 */
अटल व्योम ग_लिखो_data(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक gpio,
		       अचिन्हित पूर्णांक data, पूर्णांक idx)
अणु
	क्रम (; idx >= 0; idx--) अणु
		/* drop घड़ी */
		gpio &= ~VT1724_PRODIGY192_CCLK;
		snd_ice1712_gpio_ग_लिखो(ice, gpio);
		udelay(1);
		/* set data */
		अगर (data & (1 << idx))
			gpio |= VT1724_PRODIGY192_CDOUT;
		अन्यथा
			gpio &= ~VT1724_PRODIGY192_CDOUT;
		snd_ice1712_gpio_ग_लिखो(ice, gpio);
		udelay(1);
		/* उठाओ घड़ी */
		gpio |= VT1724_PRODIGY192_CCLK;
		snd_ice1712_gpio_ग_लिखो(ice, gpio);
		udelay(1);
	पूर्ण
पूर्ण

/*
 * 4wire ak4114 protocol - पढ़ोing data
 */
अटल अचिन्हित अक्षर पढ़ो_data(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक gpio,
			       पूर्णांक idx)
अणु
	अचिन्हित अक्षर data = 0;

	क्रम (; idx >= 0; idx--) अणु
		/* drop घड़ी */
		gpio &= ~VT1724_PRODIGY192_CCLK;
		snd_ice1712_gpio_ग_लिखो(ice, gpio);
		udelay(1);
		/* पढ़ो data */
		अगर (snd_ice1712_gpio_पढ़ो(ice) & VT1724_PRODIGY192_CDIN)
			data |= (1 << idx);
		udelay(1);
		/* उठाओ घड़ी */
		gpio |= VT1724_PRODIGY192_CCLK;
		snd_ice1712_gpio_ग_लिखो(ice, gpio);
		udelay(1);
	पूर्ण
	वापस data;
पूर्ण
/*
 * 4wire ak4114 protocol - starting sequence
 */
अटल अचिन्हित पूर्णांक prodigy192_4wire_start(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	snd_ice1712_save_gpio_status(ice);
	पंचांगp = snd_ice1712_gpio_पढ़ो(ice);

	पंचांगp |= VT1724_PRODIGY192_CCLK; /* high at init */
	पंचांगp &= ~VT1724_PRODIGY192_CS; /* drop chip select */
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);
	वापस पंचांगp;
पूर्ण

/*
 * 4wire ak4114 protocol - final sequence
 */
अटल व्योम prodigy192_4wire_finish(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक पंचांगp)
अणु
	पंचांगp |= VT1724_PRODIGY192_CS; /* उठाओ chip select */
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);
	snd_ice1712_restore_gpio_status(ice);
पूर्ण

/*
 * Write data to addr रेजिस्टर of ak4114
 */
अटल व्योम prodigy192_ak4114_ग_लिखो(व्योम *निजी_data, अचिन्हित अक्षर addr,
			       अचिन्हित अक्षर data)
अणु
	काष्ठा snd_ice1712 *ice = निजी_data;
	अचिन्हित पूर्णांक पंचांगp, addrdata;
	पंचांगp = prodigy192_4wire_start(ice);
	addrdata = (AK4114_ADDR << 6) | 0x20 | (addr & 0x1f);
	addrdata = (addrdata << 8) | data;
	ग_लिखो_data(ice, पंचांगp, addrdata, 15);
	prodigy192_4wire_finish(ice, पंचांगp);
पूर्ण

/*
 * Read data from addr रेजिस्टर of ak4114
 */
अटल अचिन्हित अक्षर prodigy192_ak4114_पढ़ो(व्योम *निजी_data,
					    अचिन्हित अक्षर addr)
अणु
	काष्ठा snd_ice1712 *ice = निजी_data;
	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित अक्षर data;

	पंचांगp = prodigy192_4wire_start(ice);
	ग_लिखो_data(ice, पंचांगp, (AK4114_ADDR << 6) | (addr & 0x1f), 7);
	data = पढ़ो_data(ice, पंचांगp, 7);
	prodigy192_4wire_finish(ice, पंचांगp);
	वापस data;
पूर्ण


अटल पूर्णांक ak4114_input_sw_info(काष्ठा snd_kcontrol *kcontrol,
	       			काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु "Toslink", "Coax" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण


अटल पूर्णांक ak4114_input_sw_get(काष्ठा snd_kcontrol *kcontrol,
	       		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val;
		
	val = prodigy192_ak4114_पढ़ो(ice, AK4114_REG_IO1);
	/* AK4114_IPS0 bit = 0 -> RX0 = Toslink
	 * AK4114_IPS0 bit = 1 -> RX1 = Coax
	 */
	ucontrol->value.क्रमागतerated.item[0] = (val & AK4114_IPS0) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ak4114_input_sw_put(काष्ठा snd_kcontrol *kcontrol,
	       		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर new, old, itemvalue;
	पूर्णांक change;

	old = prodigy192_ak4114_पढ़ो(ice, AK4114_REG_IO1);
	/* AK4114_IPS0 could be any bit */
	itemvalue = (ucontrol->value.क्रमागतerated.item[0]) ? 0xff : 0x00;

	new = (itemvalue & AK4114_IPS0) | (old & ~AK4114_IPS0);
	change = (new != old);
	अगर (change)
		prodigy192_ak4114_ग_लिखो(ice, AK4114_REG_IO1, new);
	वापस change;
पूर्ण


अटल स्थिर काष्ठा snd_kcontrol_new ak4114_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "MIODIO IEC958 Capture Input",
		.info = ak4114_input_sw_info,
		.get = ak4114_input_sw_get,
		.put = ak4114_input_sw_put,

	पूर्ण
पूर्ण;


अटल पूर्णांक prodigy192_ak4114_init(काष्ठा snd_ice1712 *ice)
अणु
	अटल स्थिर अचिन्हित अक्षर ak4114_init_vals[] = अणु
		AK4114_RST | AK4114_PWN | AK4114_OCKS0 | AK4114_OCKS1,
		/* ice1724 expects I2S and provides घड़ी,
		 * DEM0 disables the deemphasis filter
		 */
		AK4114_DIF_I24I2S | AK4114_DEM0 ,
		AK4114_TX1E,
		AK4114_EFH_1024 | AK4114_DIT, /* शेष input RX0 */
		0,
		0
	पूर्ण;
	अटल स्थिर अचिन्हित अक्षर ak4114_init_txcsb[] = अणु
		0x41, 0x02, 0x2c, 0x00, 0x00
	पूर्ण;
	काष्ठा prodigy192_spec *spec = ice->spec;
	पूर्णांक err;

	err = snd_ak4114_create(ice->card,
				 prodigy192_ak4114_पढ़ो,
				 prodigy192_ak4114_ग_लिखो,
				 ak4114_init_vals, ak4114_init_txcsb,
				 ice, &spec->ak4114);
	अगर (err < 0)
		वापस err;
	/* AK4114 in Prodigy192 cannot detect बाह्यal rate correctly.
	 * No reason to stop capture stream due to incorrect checks */
	spec->ak4114->check_flags = AK4114_CHECK_NO_RATE;
	वापस 0;
पूर्ण

अटल व्योम stac9460_proc_regs_पढ़ो(काष्ठा snd_info_entry *entry,
		काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ice1712 *ice = entry->निजी_data;
	पूर्णांक reg, val;
	/* रेजिस्टरs 0x0 - 0x14 */
	क्रम (reg = 0; reg <= 0x15; reg++) अणु
		val = stac9460_get(ice, reg);
		snd_iम_लिखो(buffer, "0x%02x = 0x%02x\n", reg, val);
	पूर्ण
पूर्ण


अटल व्योम stac9460_proc_init(काष्ठा snd_ice1712 *ice)
अणु
	snd_card_ro_proc_new(ice->card, "stac9460_codec", ice,
			     stac9460_proc_regs_पढ़ो);
पूर्ण


अटल पूर्णांक prodigy192_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा prodigy192_spec *spec = ice->spec;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(stac_controls); i++) अणु
		err = snd_ctl_add(ice->card,
				  snd_ctl_new1(&stac_controls[i], ice));
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (spec->ak4114) अणु
		/* ak4114 is connected */
		क्रम (i = 0; i < ARRAY_SIZE(ak4114_controls); i++) अणु
			err = snd_ctl_add(ice->card,
					  snd_ctl_new1(&ak4114_controls[i],
						       ice));
			अगर (err < 0)
				वापस err;
		पूर्ण
		err = snd_ak4114_build(spec->ak4114,
				शून्य, /* ak4114 in MIO/DI/O handles no IEC958 output */
				ice->pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream);
		अगर (err < 0)
			वापस err;
	पूर्ण
	stac9460_proc_init(ice);
	वापस 0;
पूर्ण

/*
 * check क्रम presence of MI/ODI/O add-on card with digital inमाला_दो
 */
अटल पूर्णांक prodigy192_miodio_exists(काष्ठा snd_ice1712 *ice)
अणु

	अचिन्हित अक्षर orig_value;
	स्थिर अचिन्हित अक्षर test_data = 0xd1;	/* अक्रमom value */
	अचिन्हित अक्षर addr = AK4114_REG_INT0_MASK; /* अक्रमom SAFE address */
	पूर्णांक exists = 0;

	orig_value = prodigy192_ak4114_पढ़ो(ice, addr);
	prodigy192_ak4114_ग_लिखो(ice, addr, test_data);
	अगर (prodigy192_ak4114_पढ़ो(ice, addr) == test_data) अणु
		/* ak4114 seems to communicate, apparently exists */
		/* writing back original value */
		prodigy192_ak4114_ग_लिखो(ice, addr, orig_value);
		exists = 1;
	पूर्ण
	वापस exists;
पूर्ण

/*
 * initialize the chip
 */
अटल पूर्णांक prodigy192_init(काष्ठा snd_ice1712 *ice)
अणु
	अटल स्थिर अचिन्हित लघु stac_inits_prodigy[] = अणु
		STAC946X_RESET, 0,
		STAC946X_MASTER_CLOCKING, 0x11,
/*		STAC946X_MASTER_VOLUME, 0,
		STAC946X_LF_VOLUME, 0,
		STAC946X_RF_VOLUME, 0,
		STAC946X_LR_VOLUME, 0,
		STAC946X_RR_VOLUME, 0,
		STAC946X_CENTER_VOLUME, 0,
		STAC946X_LFE_VOLUME, 0,*/
		(अचिन्हित लघु)-1
	पूर्ण;
	स्थिर अचिन्हित लघु *p;
	पूर्णांक err = 0;
	काष्ठा prodigy192_spec *spec;

	/* prodigy 192 */
	ice->num_total_dacs = 6;
	ice->num_total_adcs = 2;
	ice->vt1720 = 0;  /* ice1724, e.g. 23 GPIOs */
	
	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	ice->spec = spec;
	mutex_init(&spec->mute_mutex);

	/* initialize codec */
	p = stac_inits_prodigy;
	क्रम (; *p != (अचिन्हित लघु)-1; p += 2)
		stac9460_put(ice, p[0], p[1]);
	ice->gpio.set_pro_rate = stac9460_set_rate_val;

	/* MI/ODI/O add on card with AK4114 */
	अगर (prodigy192_miodio_exists(ice)) अणु
		err = prodigy192_ak4114_init(ice);
		/* from this moment अगर err = 0 then
		 * spec->ak4114 should not be null
		 */
		dev_dbg(ice->card->dev,
			"AK4114 initialized with status %d\n", err);
	पूर्ण अन्यथा
		dev_dbg(ice->card->dev, "AK4114 not found\n");

	वापस err;
पूर्ण


/*
 * Aureon boards करोn't provide the EEPROM data except क्रम the venकरोr IDs.
 * hence the driver needs to sets up it properly.
 */

अटल स्थिर अचिन्हित अक्षर prodigy71_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]     = 0x6a,	/* 49MHz crystal, mpu401,
					 * spdअगर-in+ 1 stereo ADC,
					 * 3 stereo DACs
					 */
	[ICE_EEP2_ACLINK]      = 0x80,	/* I2S */
	[ICE_EEP2_I2S]         = 0xf8,	/* vol, 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]       = 0xc3,	/* out-en, out-पूर्णांक, spdअगर-in */
	[ICE_EEP2_GPIO_सूची]    = 0xff,
	[ICE_EEP2_GPIO_सूची1]   = ~(VT1724_PRODIGY192_CDIN >> 8) ,
	[ICE_EEP2_GPIO_सूची2]   = 0xbf,
	[ICE_EEP2_GPIO_MASK]   = 0x00,
	[ICE_EEP2_GPIO_MASK1]  = 0x00,
	[ICE_EEP2_GPIO_MASK2]  = 0x00,
	[ICE_EEP2_GPIO_STATE]  = 0x00,
	[ICE_EEP2_GPIO_STATE1] = 0x00,
	[ICE_EEP2_GPIO_STATE2] = 0x10,  /* GPIO20: 0 = CD drive dig. input
					 * passthrough,
					 * 1 = SPDIF-OUT from ice1724
					 */
पूर्ण;


/* entry poपूर्णांक */
काष्ठा snd_ice1712_card_info snd_vt1724_prodigy192_cards[] = अणु
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_PRODIGY192VE,
		.name = "Audiotrak Prodigy 192",
		.model = "prodigy192",
		.chip_init = prodigy192_init,
		.build_controls = prodigy192_add_controls,
		.eeprom_size = माप(prodigy71_eeprom),
		.eeprom_data = prodigy71_eeprom,
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;
