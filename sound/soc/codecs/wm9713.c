<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm9713.c  --  ALSA Soc WM9713 codec support
 *
 * Copyright 2006-10 Wolfson Microelectronics PLC.
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 *
 *  Features:-
 *
 *   o Support क्रम AC97 Codec, Voice DAC and Aux DAC
 *   o Support क्रम DAPM
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/wm97xx.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/ac97/codec.h>
#समावेश <sound/ac97/compat.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश <sound/soc.h>

#समावेश "wm9713.h"

#घोषणा WM9713_VENDOR_ID 0x574d4c13
#घोषणा WM9713_VENDOR_ID_MASK 0xffffffff

काष्ठा wm9713_priv अणु
	काष्ठा snd_ac97 *ac97;
	u32 pll_in; /* PLL input frequency */
	अचिन्हित पूर्णांक hp_mixer[2];
	काष्ठा mutex lock;
	काष्ठा wm97xx_platक्रमm_data *mfd_pdata;
पूर्ण;

#घोषणा HPL_MIXER 0
#घोषणा HPR_MIXER 1

अटल स्थिर अक्षर *wm9713_mic_mixer[] = अणु"Stereo", "Mic 1", "Mic 2", "Mute"पूर्ण;
अटल स्थिर अक्षर *wm9713_rec_mux[] = अणु"Stereo", "Left", "Right", "Mute"पूर्ण;
अटल स्थिर अक्षर *wm9713_rec_src[] =
	अणु"Mic 1", "Mic 2", "Line", "Mono In", "Headphone", "Speaker",
	"Mono Out", "Zh"पूर्ण;
अटल स्थिर अक्षर *wm9713_rec_gain[] = अणु"+1.5dB Steps", "+0.75dB Steps"पूर्ण;
अटल स्थिर अक्षर *wm9713_alc_select[] = अणु"None", "Left", "Right", "Stereo"पूर्ण;
अटल स्थिर अक्षर *wm9713_mono_pga[] = अणु"Vmid", "Zh", "Mono", "Inv"पूर्ण;
अटल स्थिर अक्षर *wm9713_spk_pga[] =
	अणु"Vmid", "Zh", "Headphone", "Speaker", "Inv", "Headphone Vmid",
	"Speaker Vmid", "Inv Vmid"पूर्ण;
अटल स्थिर अक्षर *wm9713_hp_pga[] = अणु"Vmid", "Zh", "Headphone",
	"Headphone Vmid"पूर्ण;
अटल स्थिर अक्षर *wm9713_out3_pga[] = अणु"Vmid", "Zh", "Inv 1", "Inv 1 Vmid"पूर्ण;
अटल स्थिर अक्षर *wm9713_out4_pga[] = अणु"Vmid", "Zh", "Inv 2", "Inv 2 Vmid"पूर्ण;
अटल स्थिर अक्षर *wm9713_dac_inv[] =
	अणु"Off", "Mono", "Speaker", "Left Headphone", "Right Headphone",
	"Headphone Mono", "NC", "Vmid"पूर्ण;
अटल स्थिर अक्षर *wm9713_bass[] = अणु"Linear Control", "Adaptive Boost"पूर्ण;
अटल स्थिर अक्षर *wm9713_ng_type[] = अणु"Constant Gain", "Mute"पूर्ण;
अटल स्थिर अक्षर *wm9713_mic_select[] = अणु"Mic 1", "Mic 2 A", "Mic 2 B"पूर्ण;
अटल स्थिर अक्षर *wm9713_micb_select[] = अणु"MPB", "MPA"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत wm9713_क्रमागत[] = अणु
SOC_ENUM_SINGLE(AC97_LINE, 3, 4, wm9713_mic_mixer), /* record mic mixer 0 */
SOC_ENUM_SINGLE(AC97_VIDEO, 14, 4, wm9713_rec_mux), /* record mux hp 1 */
SOC_ENUM_SINGLE(AC97_VIDEO, 9, 4, wm9713_rec_mux),  /* record mux mono 2 */
SOC_ENUM_SINGLE(AC97_VIDEO, 3, 8, wm9713_rec_src),  /* record mux left 3 */
SOC_ENUM_SINGLE(AC97_VIDEO, 0, 8, wm9713_rec_src),  /* record mux right 4*/
SOC_ENUM_DOUBLE(AC97_CD, 14, 6, 2, wm9713_rec_gain), /* record step size 5 */
SOC_ENUM_SINGLE(AC97_PCI_SVID, 14, 4, wm9713_alc_select), /* alc source select 6*/
SOC_ENUM_SINGLE(AC97_REC_GAIN, 14, 4, wm9713_mono_pga), /* mono input select 7 */
SOC_ENUM_SINGLE(AC97_REC_GAIN, 11, 8, wm9713_spk_pga), /* speaker left input select 8 */
SOC_ENUM_SINGLE(AC97_REC_GAIN, 8, 8, wm9713_spk_pga), /* speaker right input select 9 */
SOC_ENUM_SINGLE(AC97_REC_GAIN, 6, 3, wm9713_hp_pga), /* headphone left input 10 */
SOC_ENUM_SINGLE(AC97_REC_GAIN, 4, 3, wm9713_hp_pga), /* headphone right input 11 */
SOC_ENUM_SINGLE(AC97_REC_GAIN, 2, 4, wm9713_out3_pga), /* out 3 source 12 */
SOC_ENUM_SINGLE(AC97_REC_GAIN, 0, 4, wm9713_out4_pga), /* out 4 source 13 */
SOC_ENUM_SINGLE(AC97_REC_GAIN_MIC, 13, 8, wm9713_dac_inv), /* dac invert 1 14 */
SOC_ENUM_SINGLE(AC97_REC_GAIN_MIC, 10, 8, wm9713_dac_inv), /* dac invert 2 15 */
SOC_ENUM_SINGLE(AC97_GENERAL_PURPOSE, 15, 2, wm9713_bass), /* bass control 16 */
SOC_ENUM_SINGLE(AC97_PCI_SVID, 5, 2, wm9713_ng_type), /* noise gate type 17 */
SOC_ENUM_SINGLE(AC97_3D_CONTROL, 12, 3, wm9713_mic_select), /* mic selection 18 */
SOC_ENUM_SINGLE_VIRT(2, wm9713_micb_select), /* mic selection 19 */
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, -4650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(मुख्य_tlv, -3450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(misc_tlv, -1500, 300, 0);
अटल स्थिर  DECLARE_TLV_DB_RANGE(mic_tlv,
	0, 2, TLV_DB_SCALE_ITEM(1200, 600, 0),
	3, 3, TLV_DB_SCALE_ITEM(3000, 0, 0)
);

अटल स्थिर काष्ठा snd_kcontrol_new wm9713_snd_ac97_controls[] = अणु
SOC_DOUBLE_TLV("Speaker Playback Volume", AC97_MASTER, 8, 0, 31, 1, out_tlv),
SOC_DOUBLE("Speaker Playback Switch", AC97_MASTER, 15, 7, 1, 1),
SOC_DOUBLE_TLV("Headphone Playback Volume", AC97_HEADPHONE, 8, 0, 31, 1,
	       out_tlv),
SOC_DOUBLE("Headphone Playback Switch", AC97_HEADPHONE, 15, 7, 1, 1),
SOC_DOUBLE_TLV("Line In Volume", AC97_PC_BEEP, 8, 0, 31, 1, मुख्य_tlv),
SOC_DOUBLE_TLV("PCM Playback Volume", AC97_PHONE, 8, 0, 31, 1, मुख्य_tlv),
SOC_SINGLE_TLV("Mic 1 Volume", AC97_MIC, 8, 31, 1, मुख्य_tlv),
SOC_SINGLE_TLV("Mic 2 Volume", AC97_MIC, 0, 31, 1, मुख्य_tlv),
SOC_SINGLE_TLV("Mic 1 Preamp Volume", AC97_3D_CONTROL, 10, 3, 0, mic_tlv),
SOC_SINGLE_TLV("Mic 2 Preamp Volume", AC97_3D_CONTROL, 12, 3, 0, mic_tlv),

SOC_SINGLE("Mic Boost (+20dB) Switch", AC97_LINE, 5, 1, 0),
SOC_SINGLE("Mic Headphone Mixer Volume", AC97_LINE, 0, 7, 1),

SOC_SINGLE("Capture Switch", AC97_CD, 15, 1, 1),
SOC_ENUM("Capture Volume Steps", wm9713_क्रमागत[5]),
SOC_DOUBLE("Capture Volume", AC97_CD, 8, 0, 31, 0),
SOC_SINGLE("Capture ZC Switch", AC97_CD, 7, 1, 0),

SOC_SINGLE_TLV("Capture to Headphone Volume", AC97_VIDEO, 11, 7, 1, misc_tlv),
SOC_SINGLE("Capture to Mono Boost (+20dB) Switch", AC97_VIDEO, 8, 1, 0),
SOC_SINGLE("Capture ADC Boost (+20dB) Switch", AC97_VIDEO, 6, 1, 0),

SOC_SINGLE("ALC Target Volume", AC97_CODEC_CLASS_REV, 12, 15, 0),
SOC_SINGLE("ALC Hold Time", AC97_CODEC_CLASS_REV, 8, 15, 0),
SOC_SINGLE("ALC Decay Time", AC97_CODEC_CLASS_REV, 4, 15, 0),
SOC_SINGLE("ALC Attack Time", AC97_CODEC_CLASS_REV, 0, 15, 0),
SOC_ENUM("ALC Function", wm9713_क्रमागत[6]),
SOC_SINGLE("ALC Max Volume", AC97_PCI_SVID, 11, 7, 0),
SOC_SINGLE("ALC ZC Timeout", AC97_PCI_SVID, 9, 3, 0),
SOC_SINGLE("ALC ZC Switch", AC97_PCI_SVID, 8, 1, 0),
SOC_SINGLE("ALC NG Switch", AC97_PCI_SVID, 7, 1, 0),
SOC_ENUM("ALC NG Type", wm9713_क्रमागत[17]),
SOC_SINGLE("ALC NG Threshold", AC97_PCI_SVID, 0, 31, 0),

SOC_DOUBLE("Speaker Playback ZC Switch", AC97_MASTER, 14, 6, 1, 0),
SOC_DOUBLE("Headphone Playback ZC Switch", AC97_HEADPHONE, 14, 6, 1, 0),

SOC_SINGLE("Out4 Playback Switch", AC97_MASTER_MONO, 15, 1, 1),
SOC_SINGLE("Out4 Playback ZC Switch", AC97_MASTER_MONO, 14, 1, 0),
SOC_SINGLE_TLV("Out4 Playback Volume", AC97_MASTER_MONO, 8, 31, 1, out_tlv),

SOC_SINGLE("Out3 Playback Switch", AC97_MASTER_MONO, 7, 1, 1),
SOC_SINGLE("Out3 Playback ZC Switch", AC97_MASTER_MONO, 6, 1, 0),
SOC_SINGLE_TLV("Out3 Playback Volume", AC97_MASTER_MONO, 0, 31, 1, out_tlv),

SOC_SINGLE_TLV("Mono Capture Volume", AC97_MASTER_TONE, 8, 31, 1, मुख्य_tlv),
SOC_SINGLE("Mono Playback Switch", AC97_MASTER_TONE, 7, 1, 1),
SOC_SINGLE("Mono Playback ZC Switch", AC97_MASTER_TONE, 6, 1, 0),
SOC_SINGLE_TLV("Mono Playback Volume", AC97_MASTER_TONE, 0, 31, 1, out_tlv),

SOC_SINGLE_TLV("Headphone Mixer Beep Playback Volume", AC97_AUX, 12, 7, 1,
	       misc_tlv),
SOC_SINGLE_TLV("Speaker Mixer Beep Playback Volume", AC97_AUX, 8, 7, 1,
	       misc_tlv),
SOC_SINGLE_TLV("Mono Mixer Beep Playback Volume", AC97_AUX, 4, 7, 1, misc_tlv),

SOC_SINGLE_TLV("Voice Playback Headphone Volume", AC97_PCM, 12, 7, 1,
	       misc_tlv),
SOC_SINGLE("Voice Playback Master Volume", AC97_PCM, 8, 7, 1),
SOC_SINGLE("Voice Playback Mono Volume", AC97_PCM, 4, 7, 1),

SOC_SINGLE_TLV("Headphone Mixer Aux Playback Volume", AC97_REC_SEL, 12, 7, 1,
	       misc_tlv),

SOC_SINGLE_TLV("Speaker Mixer Voice Playback Volume", AC97_PCM, 8, 7, 1,
	       misc_tlv),
SOC_SINGLE_TLV("Speaker Mixer Aux Playback Volume", AC97_REC_SEL, 8, 7, 1,
	       misc_tlv),

SOC_SINGLE_TLV("Mono Mixer Voice Playback Volume", AC97_PCM, 4, 7, 1,
	       misc_tlv),
SOC_SINGLE_TLV("Mono Mixer Aux Playback Volume", AC97_REC_SEL, 4, 7, 1,
	       misc_tlv),

SOC_SINGLE("Aux Playback Headphone Volume", AC97_REC_SEL, 12, 7, 1),
SOC_SINGLE("Aux Playback Master Volume", AC97_REC_SEL, 8, 7, 1),

SOC_ENUM("Bass Control", wm9713_क्रमागत[16]),
SOC_SINGLE("Bass Cut-off Switch", AC97_GENERAL_PURPOSE, 12, 1, 1),
SOC_SINGLE("Tone Cut-off Switch", AC97_GENERAL_PURPOSE, 4, 1, 1),
SOC_SINGLE("Playback Attenuate (-6dB) Switch", AC97_GENERAL_PURPOSE, 6, 1, 0),
SOC_SINGLE("Bass Volume", AC97_GENERAL_PURPOSE, 8, 15, 1),
SOC_SINGLE("Tone Volume", AC97_GENERAL_PURPOSE, 0, 15, 1),

SOC_SINGLE("3D Upper Cut-off Switch", AC97_REC_GAIN_MIC, 5, 1, 0),
SOC_SINGLE("3D Lower Cut-off Switch", AC97_REC_GAIN_MIC, 4, 1, 0),
SOC_SINGLE("3D Depth", AC97_REC_GAIN_MIC, 0, 15, 1),
पूर्ण;

अटल पूर्णांक wm9713_voice_shutकरोwn(काष्ठा snd_soc_dapm_widget *w,
				 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	अगर (WARN_ON(event != SND_SOC_DAPM_PRE_PMD))
		वापस -EINVAL;

	/* Gracefully shut करोwn the voice पूर्णांकerface. */
	snd_soc_component_update_bits(component, AC97_HANDSET_RATE, 0x0f00, 0x0200);
	schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(1));
	snd_soc_component_update_bits(component, AC97_HANDSET_RATE, 0x0f00, 0x0f00);
	snd_soc_component_update_bits(component, AC97_EXTENDED_MID, 0x1000, 0x1000);

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक wm9713_mixer_mute_regs[] = अणु
	AC97_PC_BEEP,
	AC97_MASTER_TONE,
	AC97_PHONE,
	AC97_REC_SEL,
	AC97_PCM,
	AC97_AUX,
पूर्ण;

/* We have to create a fake left and right HP mixers because
 * the codec only has a single control that is shared by both channels.
 * This makes it impossible to determine the audio path using the current
 * रेजिस्टर map, thus we add a new (भव) रेजिस्टर to help determine the
 * audio route within the device.
 */
अटल पूर्णांक wm9713_hp_mixer_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	काष्ठा wm9713_priv *wm9713 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val = ucontrol->value.पूर्णांकeger.value[0];
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक mixer, mask, shअगरt, old;
	काष्ठा snd_soc_dapm_update update = अणुपूर्ण;
	bool change;

	mixer = mc->shअगरt >> 8;
	shअगरt = mc->shअगरt & 0xff;
	mask = (1 << shअगरt);

	mutex_lock(&wm9713->lock);
	old = wm9713->hp_mixer[mixer];
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		wm9713->hp_mixer[mixer] |= mask;
	अन्यथा
		wm9713->hp_mixer[mixer] &= ~mask;

	change = old != wm9713->hp_mixer[mixer];
	अगर (change) अणु
		update.kcontrol = kcontrol;
		update.reg = wm9713_mixer_mute_regs[shअगरt];
		update.mask = 0x8000;
		अगर ((wm9713->hp_mixer[0] & mask) ||
		    (wm9713->hp_mixer[1] & mask))
			update.val = 0x0;
		अन्यथा
			update.val = 0x8000;

		snd_soc_dapm_mixer_update_घातer(dapm, kcontrol, val,
			&update);
	पूर्ण

	mutex_unlock(&wm9713->lock);

	वापस change;
पूर्ण

अटल पूर्णांक wm9713_hp_mixer_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	काष्ठा wm9713_priv *wm9713 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक mixer, shअगरt;

	mixer = mc->shअगरt >> 8;
	shअगरt = mc->shअगरt & 0xff;

	ucontrol->value.पूर्णांकeger.value[0] =
		(wm9713->hp_mixer[mixer] >> shअगरt) & 1;

	वापस 0;
पूर्ण

#घोषणा WM9713_HP_MIXER_CTRL(xname, xmixer, xshअगरt) अणु \
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_volsw, \
	.get = wm9713_hp_mixer_get, .put = wm9713_hp_mixer_put, \
	.निजी_value = SOC_DOUBLE_VALUE(SND_SOC_NOPM, \
		xshअगरt, xmixer, 1, 0, 0) \
पूर्ण

/* Left Headphone Mixers */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_hpl_mixer_controls[] = अणु
WM9713_HP_MIXER_CTRL("Beep Playback Switch", HPL_MIXER, 5),
WM9713_HP_MIXER_CTRL("Voice Playback Switch", HPL_MIXER, 4),
WM9713_HP_MIXER_CTRL("Aux Playback Switch", HPL_MIXER, 3),
WM9713_HP_MIXER_CTRL("PCM Playback Switch", HPL_MIXER, 2),
WM9713_HP_MIXER_CTRL("MonoIn Playback Switch", HPL_MIXER, 1),
WM9713_HP_MIXER_CTRL("Bypass Playback Switch", HPL_MIXER, 0),
पूर्ण;

/* Right Headphone Mixers */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_hpr_mixer_controls[] = अणु
WM9713_HP_MIXER_CTRL("Beep Playback Switch", HPR_MIXER, 5),
WM9713_HP_MIXER_CTRL("Voice Playback Switch", HPR_MIXER, 4),
WM9713_HP_MIXER_CTRL("Aux Playback Switch", HPR_MIXER, 3),
WM9713_HP_MIXER_CTRL("PCM Playback Switch", HPR_MIXER, 2),
WM9713_HP_MIXER_CTRL("MonoIn Playback Switch", HPR_MIXER, 1),
WM9713_HP_MIXER_CTRL("Bypass Playback Switch", HPR_MIXER, 0),
पूर्ण;

/* headphone capture mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_hp_rec_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[1]);

/* headphone mic mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_hp_mic_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[0]);

/* Speaker Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_speaker_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Beep Playback Switch", AC97_AUX, 11, 1, 1),
SOC_DAPM_SINGLE("Voice Playback Switch", AC97_PCM, 11, 1, 1),
SOC_DAPM_SINGLE("Aux Playback Switch", AC97_REC_SEL, 11, 1, 1),
SOC_DAPM_SINGLE("PCM Playback Switch", AC97_PHONE, 14, 1, 1),
SOC_DAPM_SINGLE("MonoIn Playback Switch", AC97_MASTER_TONE, 14, 1, 1),
SOC_DAPM_SINGLE("Bypass Playback Switch", AC97_PC_BEEP, 14, 1, 1),
पूर्ण;

/* Mono Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_mono_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Beep Playback Switch", AC97_AUX, 7, 1, 1),
SOC_DAPM_SINGLE("Voice Playback Switch", AC97_PCM, 7, 1, 1),
SOC_DAPM_SINGLE("Aux Playback Switch", AC97_REC_SEL, 7, 1, 1),
SOC_DAPM_SINGLE("PCM Playback Switch", AC97_PHONE, 13, 1, 1),
SOC_DAPM_SINGLE("MonoIn Playback Switch", AC97_MASTER_TONE, 13, 1, 1),
SOC_DAPM_SINGLE("Bypass Playback Switch", AC97_PC_BEEP, 13, 1, 1),
SOC_DAPM_SINGLE("Mic 1 Sidetone Switch", AC97_LINE, 7, 1, 1),
SOC_DAPM_SINGLE("Mic 2 Sidetone Switch", AC97_LINE, 6, 1, 1),
पूर्ण;

/* mono mic mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_mono_mic_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[2]);

/* mono output mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_mono_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[7]);

/* speaker left output mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_hp_spkl_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[8]);

/* speaker right output mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_hp_spkr_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[9]);

/* headphone left output mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_hpl_out_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[10]);

/* headphone right output mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_hpr_out_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[11]);

/* Out3 mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_out3_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[12]);

/* Out4 mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_out4_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[13]);

/* DAC inv mux 1 */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_dac_inv1_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[14]);

/* DAC inv mux 2 */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_dac_inv2_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[15]);

/* Capture source left */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_rec_srcl_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[3]);

/* Capture source right */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_rec_srcr_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[4]);

/* mic source */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_mic_sel_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[18]);

/* mic source B भव control */
अटल स्थिर काष्ठा snd_kcontrol_new wm9713_micb_sel_mux_controls =
SOC_DAPM_ENUM("Route", wm9713_क्रमागत[19]);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm9713_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_MUX("Capture Headphone Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_hp_rec_mux_controls),
SND_SOC_DAPM_MUX("Sidetone Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_hp_mic_mux_controls),
SND_SOC_DAPM_MUX("Capture Mono Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_mono_mic_mux_controls),
SND_SOC_DAPM_MUX("Mono Out Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_mono_mux_controls),
SND_SOC_DAPM_MUX("Left Speaker Out Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_hp_spkl_mux_controls),
SND_SOC_DAPM_MUX("Right Speaker Out Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_hp_spkr_mux_controls),
SND_SOC_DAPM_MUX("Left Headphone Out Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_hpl_out_mux_controls),
SND_SOC_DAPM_MUX("Right Headphone Out Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_hpr_out_mux_controls),
SND_SOC_DAPM_MUX("Out 3 Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_out3_mux_controls),
SND_SOC_DAPM_MUX("Out 4 Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_out4_mux_controls),
SND_SOC_DAPM_MUX("DAC Inv Mux 1", SND_SOC_NOPM, 0, 0,
	&wm9713_dac_inv1_mux_controls),
SND_SOC_DAPM_MUX("DAC Inv Mux 2", SND_SOC_NOPM, 0, 0,
	&wm9713_dac_inv2_mux_controls),
SND_SOC_DAPM_MUX("Left Capture Source", SND_SOC_NOPM, 0, 0,
	&wm9713_rec_srcl_mux_controls),
SND_SOC_DAPM_MUX("Right Capture Source", SND_SOC_NOPM, 0, 0,
	&wm9713_rec_srcr_mux_controls),
SND_SOC_DAPM_MUX("Mic A Source", SND_SOC_NOPM, 0, 0,
	&wm9713_mic_sel_mux_controls),
SND_SOC_DAPM_MUX("Mic B Source", SND_SOC_NOPM, 0, 0,
	&wm9713_micb_sel_mux_controls),
SND_SOC_DAPM_MIXER("Left HP Mixer", AC97_EXTENDED_MID, 3, 1,
	&wm9713_hpl_mixer_controls[0], ARRAY_SIZE(wm9713_hpl_mixer_controls)),
SND_SOC_DAPM_MIXER("Right HP Mixer", AC97_EXTENDED_MID, 2, 1,
	&wm9713_hpr_mixer_controls[0], ARRAY_SIZE(wm9713_hpr_mixer_controls)),
SND_SOC_DAPM_MIXER("Mono Mixer", AC97_EXTENDED_MID, 0, 1,
	&wm9713_mono_mixer_controls[0], ARRAY_SIZE(wm9713_mono_mixer_controls)),
SND_SOC_DAPM_MIXER("Speaker Mixer", AC97_EXTENDED_MID, 1, 1,
	&wm9713_speaker_mixer_controls[0],
	ARRAY_SIZE(wm9713_speaker_mixer_controls)),
SND_SOC_DAPM_DAC("Left DAC", "Left HiFi Playback", AC97_EXTENDED_MID, 7, 1),
SND_SOC_DAPM_DAC("Right DAC", "Right HiFi Playback", AC97_EXTENDED_MID, 6, 1),
SND_SOC_DAPM_MIXER("AC97 Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("HP Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("Line Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("Capture Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_DAC_E("Voice DAC", "Voice Playback", AC97_EXTENDED_MID, 12, 1,
		   wm9713_voice_shutकरोwn, SND_SOC_DAPM_PRE_PMD),
SND_SOC_DAPM_DAC("Aux DAC", "Aux Playback", AC97_EXTENDED_MID, 11, 1),
SND_SOC_DAPM_PGA("Left ADC", AC97_EXTENDED_MID, 5, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Right ADC", AC97_EXTENDED_MID, 4, 1, शून्य, 0),
SND_SOC_DAPM_ADC("Left HiFi ADC", "Left HiFi Capture", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_ADC("Right HiFi ADC", "Right HiFi Capture", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_ADC("Left Voice ADC", "Left Voice Capture", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_ADC("Right Voice ADC", "Right Voice Capture", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_PGA("Left Headphone", AC97_EXTENDED_MSTATUS, 10, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Right Headphone", AC97_EXTENDED_MSTATUS, 9, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Left Speaker", AC97_EXTENDED_MSTATUS, 8, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Right Speaker", AC97_EXTENDED_MSTATUS, 7, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Out 3", AC97_EXTENDED_MSTATUS, 11, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Out 4", AC97_EXTENDED_MSTATUS, 12, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Mono Out", AC97_EXTENDED_MSTATUS, 13, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Left Line In", AC97_EXTENDED_MSTATUS, 6, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Right Line In", AC97_EXTENDED_MSTATUS, 5, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Mono In", AC97_EXTENDED_MSTATUS, 4, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Mic A PGA", AC97_EXTENDED_MSTATUS, 3, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Mic B PGA", AC97_EXTENDED_MSTATUS, 2, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Mic A Pre Amp", AC97_EXTENDED_MSTATUS, 1, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Mic B Pre Amp", AC97_EXTENDED_MSTATUS, 0, 1, शून्य, 0),
SND_SOC_DAPM_MICBIAS("Mic Bias", AC97_EXTENDED_MSTATUS, 14, 1),
SND_SOC_DAPM_OUTPUT("MONO"),
SND_SOC_DAPM_OUTPUT("HPL"),
SND_SOC_DAPM_OUTPUT("HPR"),
SND_SOC_DAPM_OUTPUT("SPKL"),
SND_SOC_DAPM_OUTPUT("SPKR"),
SND_SOC_DAPM_OUTPUT("OUT3"),
SND_SOC_DAPM_OUTPUT("OUT4"),
SND_SOC_DAPM_INPUT("LINEL"),
SND_SOC_DAPM_INPUT("LINER"),
SND_SOC_DAPM_INPUT("MONOIN"),
SND_SOC_DAPM_INPUT("PCBEEP"),
SND_SOC_DAPM_INPUT("MIC1"),
SND_SOC_DAPM_INPUT("MIC2A"),
SND_SOC_DAPM_INPUT("MIC2B"),
SND_SOC_DAPM_VMID("VMID"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm9713_audio_map[] = अणु
	/* left HP mixer */
	अणु"Left HP Mixer", "Beep Playback Switch",    "PCBEEP"पूर्ण,
	अणु"Left HP Mixer", "Voice Playback Switch",   "Voice DAC"पूर्ण,
	अणु"Left HP Mixer", "Aux Playback Switch",     "Aux DAC"पूर्ण,
	अणु"Left HP Mixer", "Bypass Playback Switch",  "Left Line In"पूर्ण,
	अणु"Left HP Mixer", "PCM Playback Switch",     "Left DAC"पूर्ण,
	अणु"Left HP Mixer", "MonoIn Playback Switch",  "Mono In"पूर्ण,
	अणु"Left HP Mixer", शून्य,  "Capture Headphone Mux"पूर्ण,

	/* right HP mixer */
	अणु"Right HP Mixer", "Beep Playback Switch",    "PCBEEP"पूर्ण,
	अणु"Right HP Mixer", "Voice Playback Switch",   "Voice DAC"पूर्ण,
	अणु"Right HP Mixer", "Aux Playback Switch",     "Aux DAC"पूर्ण,
	अणु"Right HP Mixer", "Bypass Playback Switch",  "Right Line In"पूर्ण,
	अणु"Right HP Mixer", "PCM Playback Switch",     "Right DAC"पूर्ण,
	अणु"Right HP Mixer", "MonoIn Playback Switch",  "Mono In"पूर्ण,
	अणु"Right HP Mixer", शून्य,  "Capture Headphone Mux"पूर्ण,

	/* भव mixer - mixes left & right channels क्रम spk and mono */
	अणु"AC97 Mixer", शून्य, "Left DAC"पूर्ण,
	अणु"AC97 Mixer", शून्य, "Right DAC"पूर्ण,
	अणु"Line Mixer", शून्य, "Right Line In"पूर्ण,
	अणु"Line Mixer", शून्य, "Left Line In"पूर्ण,
	अणु"HP Mixer", शून्य, "Left HP Mixer"पूर्ण,
	अणु"HP Mixer", शून्य, "Right HP Mixer"पूर्ण,
	अणु"Capture Mixer", शून्य, "Left Capture Source"पूर्ण,
	अणु"Capture Mixer", शून्य, "Right Capture Source"पूर्ण,

	/* speaker mixer */
	अणु"Speaker Mixer", "Beep Playback Switch",    "PCBEEP"पूर्ण,
	अणु"Speaker Mixer", "Voice Playback Switch",   "Voice DAC"पूर्ण,
	अणु"Speaker Mixer", "Aux Playback Switch",     "Aux DAC"पूर्ण,
	अणु"Speaker Mixer", "Bypass Playback Switch",  "Line Mixer"पूर्ण,
	अणु"Speaker Mixer", "PCM Playback Switch",     "AC97 Mixer"पूर्ण,
	अणु"Speaker Mixer", "MonoIn Playback Switch",  "Mono In"पूर्ण,

	/* mono mixer */
	अणु"Mono Mixer", "Beep Playback Switch",    "PCBEEP"पूर्ण,
	अणु"Mono Mixer", "Voice Playback Switch",   "Voice DAC"पूर्ण,
	अणु"Mono Mixer", "Aux Playback Switch",     "Aux DAC"पूर्ण,
	अणु"Mono Mixer", "Bypass Playback Switch",  "Line Mixer"पूर्ण,
	अणु"Mono Mixer", "PCM Playback Switch",     "AC97 Mixer"पूर्ण,
	अणु"Mono Mixer", "Mic 1 Sidetone Switch", "Mic A PGA"पूर्ण,
	अणु"Mono Mixer", "Mic 2 Sidetone Switch", "Mic B PGA"पूर्ण,
	अणु"Mono Mixer", शून्य,  "Capture Mono Mux"पूर्ण,

	/* DAC inv mux 1 */
	अणु"DAC Inv Mux 1", "Mono", "Mono Mixer"पूर्ण,
	अणु"DAC Inv Mux 1", "Speaker", "Speaker Mixer"पूर्ण,
	अणु"DAC Inv Mux 1", "Left Headphone", "Left HP Mixer"पूर्ण,
	अणु"DAC Inv Mux 1", "Right Headphone", "Right HP Mixer"पूर्ण,
	अणु"DAC Inv Mux 1", "Headphone Mono", "HP Mixer"पूर्ण,

	/* DAC inv mux 2 */
	अणु"DAC Inv Mux 2", "Mono", "Mono Mixer"पूर्ण,
	अणु"DAC Inv Mux 2", "Speaker", "Speaker Mixer"पूर्ण,
	अणु"DAC Inv Mux 2", "Left Headphone", "Left HP Mixer"पूर्ण,
	अणु"DAC Inv Mux 2", "Right Headphone", "Right HP Mixer"पूर्ण,
	अणु"DAC Inv Mux 2", "Headphone Mono", "HP Mixer"पूर्ण,

	/* headphone left mux */
	अणु"Left Headphone Out Mux", "Headphone", "Left HP Mixer"पूर्ण,

	/* headphone right mux */
	अणु"Right Headphone Out Mux", "Headphone", "Right HP Mixer"पूर्ण,

	/* speaker left mux */
	अणु"Left Speaker Out Mux", "Headphone", "Left HP Mixer"पूर्ण,
	अणु"Left Speaker Out Mux", "Speaker", "Speaker Mixer"पूर्ण,
	अणु"Left Speaker Out Mux", "Inv", "DAC Inv Mux 1"पूर्ण,

	/* speaker right mux */
	अणु"Right Speaker Out Mux", "Headphone", "Right HP Mixer"पूर्ण,
	अणु"Right Speaker Out Mux", "Speaker", "Speaker Mixer"पूर्ण,
	अणु"Right Speaker Out Mux", "Inv", "DAC Inv Mux 2"पूर्ण,

	/* mono mux */
	अणु"Mono Out Mux", "Mono", "Mono Mixer"पूर्ण,
	अणु"Mono Out Mux", "Inv", "DAC Inv Mux 1"पूर्ण,

	/* out 3 mux */
	अणु"Out 3 Mux", "Inv 1", "DAC Inv Mux 1"पूर्ण,

	/* out 4 mux */
	अणु"Out 4 Mux", "Inv 2", "DAC Inv Mux 2"पूर्ण,

	/* output pga */
	अणु"HPL", शून्य, "Left Headphone"पूर्ण,
	अणु"Left Headphone", शून्य, "Left Headphone Out Mux"पूर्ण,
	अणु"HPR", शून्य, "Right Headphone"पूर्ण,
	अणु"Right Headphone", शून्य, "Right Headphone Out Mux"पूर्ण,
	अणु"OUT3", शून्य, "Out 3"पूर्ण,
	अणु"Out 3", शून्य, "Out 3 Mux"पूर्ण,
	अणु"OUT4", शून्य, "Out 4"पूर्ण,
	अणु"Out 4", शून्य, "Out 4 Mux"पूर्ण,
	अणु"SPKL", शून्य, "Left Speaker"पूर्ण,
	अणु"Left Speaker", शून्य, "Left Speaker Out Mux"पूर्ण,
	अणु"SPKR", शून्य, "Right Speaker"पूर्ण,
	अणु"Right Speaker", शून्य, "Right Speaker Out Mux"पूर्ण,
	अणु"MONO", शून्य, "Mono Out"पूर्ण,
	अणु"Mono Out", शून्य, "Mono Out Mux"पूर्ण,

	/* input pga */
	अणु"Left Line In", शून्य, "LINEL"पूर्ण,
	अणु"Right Line In", शून्य, "LINER"पूर्ण,
	अणु"Mono In", शून्य, "MONOIN"पूर्ण,
	अणु"Mic A PGA", शून्य, "Mic A Pre Amp"पूर्ण,
	अणु"Mic B PGA", शून्य, "Mic B Pre Amp"पूर्ण,

	/* left capture select */
	अणु"Left Capture Source", "Mic 1", "Mic A Pre Amp"पूर्ण,
	अणु"Left Capture Source", "Mic 2", "Mic B Pre Amp"पूर्ण,
	अणु"Left Capture Source", "Line", "LINEL"पूर्ण,
	अणु"Left Capture Source", "Mono In", "MONOIN"पूर्ण,
	अणु"Left Capture Source", "Headphone", "Left HP Mixer"पूर्ण,
	अणु"Left Capture Source", "Speaker", "Speaker Mixer"पूर्ण,
	अणु"Left Capture Source", "Mono Out", "Mono Mixer"पूर्ण,

	/* right capture select */
	अणु"Right Capture Source", "Mic 1", "Mic A Pre Amp"पूर्ण,
	अणु"Right Capture Source", "Mic 2", "Mic B Pre Amp"पूर्ण,
	अणु"Right Capture Source", "Line", "LINER"पूर्ण,
	अणु"Right Capture Source", "Mono In", "MONOIN"पूर्ण,
	अणु"Right Capture Source", "Headphone", "Right HP Mixer"पूर्ण,
	अणु"Right Capture Source", "Speaker", "Speaker Mixer"पूर्ण,
	अणु"Right Capture Source", "Mono Out", "Mono Mixer"पूर्ण,

	/* left ADC */
	अणु"Left ADC", शून्य, "Left Capture Source"पूर्ण,
	अणु"Left Voice ADC", शून्य, "Left ADC"पूर्ण,
	अणु"Left HiFi ADC", शून्य, "Left ADC"पूर्ण,

	/* right ADC */
	अणु"Right ADC", शून्य, "Right Capture Source"पूर्ण,
	अणु"Right Voice ADC", शून्य, "Right ADC"पूर्ण,
	अणु"Right HiFi ADC", शून्य, "Right ADC"पूर्ण,

	/* mic */
	अणु"Mic A Pre Amp", शून्य, "Mic A Source"पूर्ण,
	अणु"Mic A Source", "Mic 1", "MIC1"पूर्ण,
	अणु"Mic A Source", "Mic 2 A", "MIC2A"पूर्ण,
	अणु"Mic A Source", "Mic 2 B", "Mic B Source"पूर्ण,
	अणु"Mic B Pre Amp", "MPB", "Mic B Source"पूर्ण,
	अणु"Mic B Source", शून्य, "MIC2B"पूर्ण,

	/* headphone capture */
	अणु"Capture Headphone Mux", "Stereo", "Capture Mixer"पूर्ण,
	अणु"Capture Headphone Mux", "Left", "Left Capture Source"पूर्ण,
	अणु"Capture Headphone Mux", "Right", "Right Capture Source"पूर्ण,

	/* mono capture */
	अणु"Capture Mono Mux", "Stereo", "Capture Mixer"पूर्ण,
	अणु"Capture Mono Mux", "Left", "Left Capture Source"पूर्ण,
	अणु"Capture Mono Mux", "Right", "Right Capture Source"पूर्ण,
पूर्ण;

अटल bool wm9713_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AC97_RESET ... AC97_PCM_SURR_DAC_RATE:
	हाल AC97_PCM_LR_ADC_RATE:
	हाल AC97_CENTER_LFE_MASTER:
	हाल AC97_SPDIF ... AC97_LINE1_LEVEL:
	हाल AC97_GPIO_CFG ... 0x5c:
	हाल AC97_CODEC_CLASS_REV ... AC97_PCI_SID:
	हाल 0x74 ... AC97_VENDOR_ID2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm9713_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AC97_VENDOR_ID1:
	हाल AC97_VENDOR_ID2:
		वापस false;
	शेष:
		वापस wm9713_पढ़ोable_reg(dev, reg);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा reg_शेष wm9713_reg_शेषs[] = अणु
	अणु 0x02, 0x8080 पूर्ण,	/* Speaker Output Volume */
	अणु 0x04, 0x8080 पूर्ण,	/* Headphone Output Volume */
	अणु 0x06, 0x8080 पूर्ण,	/* Out3/OUT4 Volume */
	अणु 0x08, 0xc880 पूर्ण,	/* Mono Volume */
	अणु 0x0a, 0xe808 पूर्ण,	/* LINEIN Volume */
	अणु 0x0c, 0xe808 पूर्ण,	/* DAC PGA Volume */
	अणु 0x0e, 0x0808 पूर्ण,	/* MIC PGA Volume */
	अणु 0x10, 0x00da पूर्ण,	/* MIC Routing Control */
	अणु 0x12, 0x8000 पूर्ण,	/* Record PGA Volume */
	अणु 0x14, 0xd600 पूर्ण,	/* Record Routing */
	अणु 0x16, 0xaaa0 पूर्ण,	/* PCBEEP Volume */
	अणु 0x18, 0xaaa0 पूर्ण,	/* VxDAC Volume */
	अणु 0x1a, 0xaaa0 पूर्ण,	/* AUXDAC Volume */
	अणु 0x1c, 0x0000 पूर्ण,	/* Output PGA Mux */
	अणु 0x1e, 0x0000 पूर्ण,	/* DAC 3D control */
	अणु 0x20, 0x0f0f पूर्ण,	/* DAC Tone Control*/
	अणु 0x22, 0x0040 पूर्ण,	/* MIC Input Select & Bias */
	अणु 0x24, 0x0000 पूर्ण,	/* Output Volume Mapping & Jack */
	अणु 0x26, 0x7f00 पूर्ण,	/* Powerकरोwn Ctrl/Stat*/
	अणु 0x28, 0x0405 पूर्ण,	/* Extended Audio ID */
	अणु 0x2a, 0x0410 पूर्ण,	/* Extended Audio Start/Ctrl */
	अणु 0x2c, 0xbb80 पूर्ण,	/* Audio DACs Sample Rate */
	अणु 0x2e, 0xbb80 पूर्ण,	/* AUXDAC Sample Rate */
	अणु 0x32, 0xbb80 पूर्ण,	/* Audio ADCs Sample Rate */
	अणु 0x36, 0x4523 पूर्ण,	/* PCM codec control */
	अणु 0x3a, 0x2000 पूर्ण,	/* SPDIF control */
	अणु 0x3c, 0xfdff पूर्ण,	/* Powerकरोwn 1 */
	अणु 0x3e, 0xffff पूर्ण,	/* Powerकरोwn 2 */
	अणु 0x40, 0x0000 पूर्ण,	/* General Purpose */
	अणु 0x42, 0x0000 पूर्ण,	/* Fast Power-Up Control */
	अणु 0x44, 0x0080 पूर्ण,	/* MCLK/PLL Control */
	अणु 0x46, 0x0000 पूर्ण,	/* MCLK/PLL Control */
	अणु 0x4c, 0xfffe पूर्ण,	/* GPIO Pin Configuration */
	अणु 0x4e, 0xffff पूर्ण,	/* GPIO Pin Polarity / Type */
	अणु 0x50, 0x0000 पूर्ण,	/* GPIO Pin Sticky */
	अणु 0x52, 0x0000 पूर्ण,	/* GPIO Pin Wake-Up */
				/* GPIO Pin Status */
	अणु 0x56, 0xfffe पूर्ण,	/* GPIO Pin Sharing */
	अणु 0x58, 0x4000 पूर्ण,	/* GPIO PullUp/PullDown */
	अणु 0x5a, 0x0000 पूर्ण,	/* Additional Functions 1 */
	अणु 0x5c, 0x0000 पूर्ण,	/* Additional Functions 2 */
	अणु 0x60, 0xb032 पूर्ण,	/* ALC Control */
	अणु 0x62, 0x3e00 पूर्ण,	/* ALC / Noise Gate Control */
	अणु 0x64, 0x0000 पूर्ण,	/* AUXDAC input control */
	अणु 0x74, 0x0000 पूर्ण,	/* Digitiser Reg 1 */
	अणु 0x76, 0x0006 पूर्ण,	/* Digitiser Reg 2 */
	अणु 0x78, 0x0001 पूर्ण,	/* Digitiser Reg 3 */
	अणु 0x7a, 0x0000 पूर्ण,	/* Digitiser Read Back */
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm9713_regmap_config = अणु
	.reg_bits = 16,
	.reg_stride = 2,
	.val_bits = 16,
	.max_रेजिस्टर = 0x7e,
	.cache_type = REGCACHE_RBTREE,

	.reg_शेषs = wm9713_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm9713_reg_शेषs),
	.अस्थिर_reg = regmap_ac97_शेष_अस्थिर,
	.पढ़ोable_reg = wm9713_पढ़ोable_reg,
	.ग_लिखोable_reg = wm9713_ग_लिखोable_reg,
पूर्ण;

/* PLL भागisors */
काष्ठा _pll_भाग अणु
	u32 भागsel:1;
	u32 भागctl:1;
	u32 lf:1;
	u32 n:4;
	u32 k:24;
पूर्ण;

/* The size in bits of the PLL भागide multiplied by 10
 * to allow rounding later */
#घोषणा FIXED_PLL_SIZE ((1 << 22) * 10)

अटल व्योम pll_factors(काष्ठा snd_soc_component *component,
	काष्ठा _pll_भाग *pll_भाग, अचिन्हित पूर्णांक source)
अणु
	u64 Kpart;
	अचिन्हित पूर्णांक K, Nभाग, Nmod, target;

	/* The PLL output is always 98.304MHz. */
	target = 98304000;

	/* If the input frequency is over 14.4MHz then scale it करोwn. */
	अगर (source > 14400000) अणु
		source >>= 1;
		pll_भाग->भागsel = 1;

		अगर (source > 14400000) अणु
			source >>= 1;
			pll_भाग->भागctl = 1;
		पूर्ण अन्यथा
			pll_भाग->भागctl = 0;

	पूर्ण अन्यथा अणु
		pll_भाग->भागsel = 0;
		pll_भाग->भागctl = 0;
	पूर्ण

	/* Low frequency sources require an additional भागide in the
	 * loop.
	 */
	अगर (source < 8192000) अणु
		pll_भाग->lf = 1;
		target >>= 2;
	पूर्ण अन्यथा
		pll_भाग->lf = 0;

	Nभाग = target / source;
	अगर ((Nभाग < 5) || (Nभाग > 12))
		dev_warn(component->dev,
			"WM9713 PLL N value %u out of recommended range!\n",
			Nभाग);

	pll_भाग->n = Nभाग;
	Nmod = target % source;
	Kpart = FIXED_PLL_SIZE * (दीर्घ दीर्घ)Nmod;

	करो_भाग(Kpart, source);

	K = Kpart & 0xFFFFFFFF;

	/* Check अगर we need to round */
	अगर ((K % 10) >= 5)
		K += 5;

	/* Move करोwn to proper range now rounding is करोne */
	K /= 10;

	pll_भाग->k = K;
पूर्ण

/*
 * Please note that changing the PLL input frequency may require
 * resynchronisation with the AC97 controller.
 */
अटल पूर्णांक wm9713_set_pll(काष्ठा snd_soc_component *component,
	पूर्णांक pll_id, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा wm9713_priv *wm9713 = snd_soc_component_get_drvdata(component);
	u16 reg, reg2;
	काष्ठा _pll_भाग pll_भाग;

	/* turn PLL off ? */
	अगर (freq_in == 0) अणु
		/* disable PLL घातer and select ext source */
		snd_soc_component_update_bits(component, AC97_HANDSET_RATE, 0x0080, 0x0080);
		snd_soc_component_update_bits(component, AC97_EXTENDED_MID, 0x0200, 0x0200);
		wm9713->pll_in = 0;
		वापस 0;
	पूर्ण

	pll_factors(component, &pll_भाग, freq_in);

	अगर (pll_भाग.k == 0) अणु
		reg = (pll_भाग.n << 12) | (pll_भाग.lf << 11) |
			(pll_भाग.भागsel << 9) | (pll_भाग.भागctl << 8);
		snd_soc_component_ग_लिखो(component, AC97_LINE1_LEVEL, reg);
	पूर्ण अन्यथा अणु
		/* ग_लिखो the fractional k to the reg 0x46 pages */
		reg2 = (pll_भाग.n << 12) | (pll_भाग.lf << 11) | (1 << 10) |
			(pll_भाग.भागsel << 9) | (pll_भाग.भागctl << 8);

		/* K [21:20] */
		reg = reg2 | (0x5 << 4) | (pll_भाग.k >> 20);
		snd_soc_component_ग_लिखो(component, AC97_LINE1_LEVEL, reg);

		/* K [19:16] */
		reg = reg2 | (0x4 << 4) | ((pll_भाग.k >> 16) & 0xf);
		snd_soc_component_ग_लिखो(component, AC97_LINE1_LEVEL, reg);

		/* K [15:12] */
		reg = reg2 | (0x3 << 4) | ((pll_भाग.k >> 12) & 0xf);
		snd_soc_component_ग_लिखो(component, AC97_LINE1_LEVEL, reg);

		/* K [11:8] */
		reg = reg2 | (0x2 << 4) | ((pll_भाग.k >> 8) & 0xf);
		snd_soc_component_ग_लिखो(component, AC97_LINE1_LEVEL, reg);

		/* K [7:4] */
		reg = reg2 | (0x1 << 4) | ((pll_भाग.k >> 4) & 0xf);
		snd_soc_component_ग_लिखो(component, AC97_LINE1_LEVEL, reg);

		reg = reg2 | (0x0 << 4) | (pll_भाग.k & 0xf); /* K [3:0] */
		snd_soc_component_ग_लिखो(component, AC97_LINE1_LEVEL, reg);
	पूर्ण

	/* turn PLL on and select as source */
	snd_soc_component_update_bits(component, AC97_EXTENDED_MID, 0x0200, 0x0000);
	snd_soc_component_update_bits(component, AC97_HANDSET_RATE, 0x0080, 0x0000);
	wm9713->pll_in = freq_in;

	/* रुको 10ms AC97 link frames क्रम the link to stabilise */
	schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(10));
	वापस 0;
पूर्ण

अटल पूर्णांक wm9713_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
		पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	वापस wm9713_set_pll(component, pll_id, freq_in, freq_out);
पूर्ण

/*
 * Tristate the PCM DAI lines, tristate can be disabled by calling
 * wm9713_set_dai_fmt()
 */
अटल पूर्णांक wm9713_set_dai_tristate(काष्ठा snd_soc_dai *codec_dai,
	पूर्णांक tristate)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;

	अगर (tristate)
		snd_soc_component_update_bits(component, AC97_CENTER_LFE_MASTER,
				    0x6000, 0x0000);

	वापस 0;
पूर्ण

/*
 * Configure WM9713 घड़ी भागiders.
 * Voice DAC needs 256 FS
 */
अटल पूर्णांक wm9713_set_dai_clkभाग(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;

	चयन (भाग_id) अणु
	हाल WM9713_PCMCLK_DIV:
		snd_soc_component_update_bits(component, AC97_HANDSET_RATE, 0x0f00, भाग);
		अवरोध;
	हाल WM9713_CLKA_MULT:
		snd_soc_component_update_bits(component, AC97_HANDSET_RATE, 0x0002, भाग);
		अवरोध;
	हाल WM9713_CLKB_MULT:
		snd_soc_component_update_bits(component, AC97_HANDSET_RATE, 0x0004, भाग);
		अवरोध;
	हाल WM9713_HIFI_DIV:
		snd_soc_component_update_bits(component, AC97_HANDSET_RATE, 0x7000, भाग);
		अवरोध;
	हाल WM9713_PCMBCLK_DIV:
		snd_soc_component_update_bits(component, AC97_CENTER_LFE_MASTER, 0x0e00, भाग);
		अवरोध;
	हाल WM9713_PCMCLK_PLL_DIV:
		snd_soc_component_update_bits(component, AC97_LINE1_LEVEL,
				    0x007f, भाग | 0x60);
		अवरोध;
	हाल WM9713_HIFI_PLL_DIV:
		snd_soc_component_update_bits(component, AC97_LINE1_LEVEL,
				    0x007f, भाग | 0x70);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm9713_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 gpio = snd_soc_component_पढ़ो(component, AC97_GPIO_CFG) & 0xffc5;
	u16 reg = 0x8000;

	/* घड़ी masters */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		reg |= 0x4000;
		gpio |= 0x0010;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		reg |= 0x6000;
		gpio |= 0x0018;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg |= 0x2000;
		gpio |= 0x001a;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		gpio |= 0x0012;
		अवरोध;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_IB_IF:
		reg |= 0x00c0;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg |= 0x0080;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		reg |= 0x0040;
		अवरोध;
	पूर्ण

	/* DAI क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		reg |= 0x0002;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		reg |= 0x0001;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		reg |= 0x0003;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		reg |= 0x0043;
		अवरोध;
	पूर्ण

	snd_soc_component_ग_लिखो(component, AC97_GPIO_CFG, gpio);
	snd_soc_component_ग_लिखो(component, AC97_CENTER_LFE_MASTER, reg);
	वापस 0;
पूर्ण

अटल पूर्णांक wm9713_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	/* enable PCM पूर्णांकerface in master mode */
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		snd_soc_component_update_bits(component, AC97_CENTER_LFE_MASTER,
				    0x000c, 0x0004);
		अवरोध;
	हाल 24:
		snd_soc_component_update_bits(component, AC97_CENTER_LFE_MASTER,
				    0x000c, 0x0008);
		अवरोध;
	हाल 32:
		snd_soc_component_update_bits(component, AC97_CENTER_LFE_MASTER,
				    0x000c, 0x000c);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ac97_hअगरi_prepare(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक reg;

	snd_soc_component_update_bits(component, AC97_EXTENDED_STATUS, 0x0001, 0x0001);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		reg = AC97_PCM_FRONT_DAC_RATE;
	अन्यथा
		reg = AC97_PCM_LR_ADC_RATE;

	वापस snd_soc_component_ग_लिखो(component, reg, runसमय->rate);
पूर्ण

अटल पूर्णांक ac97_aux_prepare(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_soc_component_update_bits(component, AC97_EXTENDED_STATUS, 0x0001, 0x0001);
	snd_soc_component_update_bits(component, AC97_PCI_SID, 0x8000, 0x8000);

	अगर (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
		वापस -ENODEV;

	वापस snd_soc_component_ग_लिखो(component, AC97_PCM_SURR_DAC_RATE, runसमय->rate);
पूर्ण

#घोषणा WM9713_RATES (SNDRV_PCM_RATE_8000  |	\
		      SNDRV_PCM_RATE_11025 |	\
		      SNDRV_PCM_RATE_22050 |	\
		      SNDRV_PCM_RATE_44100 |	\
		      SNDRV_PCM_RATE_48000)

#घोषणा WM9713_PCM_RATES (SNDRV_PCM_RATE_8000  |	\
			  SNDRV_PCM_RATE_11025 |	\
			  SNDRV_PCM_RATE_16000 |	\
			  SNDRV_PCM_RATE_22050 |	\
			  SNDRV_PCM_RATE_44100 |	\
			  SNDRV_PCM_RATE_48000)

#घोषणा WM9713_PCM_FORMATS \
	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
	 SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm9713_dai_ops_hअगरi = अणु
	.prepare	= ac97_hअगरi_prepare,
	.set_clkभाग	= wm9713_set_dai_clkभाग,
	.set_pll	= wm9713_set_dai_pll,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops wm9713_dai_ops_aux = अणु
	.prepare	= ac97_aux_prepare,
	.set_clkभाग	= wm9713_set_dai_clkभाग,
	.set_pll	= wm9713_set_dai_pll,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops wm9713_dai_ops_voice = अणु
	.hw_params	= wm9713_pcm_hw_params,
	.set_clkभाग	= wm9713_set_dai_clkभाग,
	.set_pll	= wm9713_set_dai_pll,
	.set_fmt	= wm9713_set_dai_fmt,
	.set_tristate	= wm9713_set_dai_tristate,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm9713_dai[] = अणु
अणु
	.name = "wm9713-hifi",
	.playback = अणु
		.stream_name = "HiFi Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM9713_RATES,
		.क्रमmats = SND_SOC_STD_AC97_FMTS,पूर्ण,
	.capture = अणु
		.stream_name = "HiFi Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM9713_RATES,
		.क्रमmats = SND_SOC_STD_AC97_FMTS,पूर्ण,
	.ops = &wm9713_dai_ops_hअगरi,
	पूर्ण,
	अणु
	.name = "wm9713-aux",
	.playback = अणु
		.stream_name = "Aux Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = WM9713_RATES,
		.क्रमmats = SND_SOC_STD_AC97_FMTS,पूर्ण,
	.ops = &wm9713_dai_ops_aux,
	पूर्ण,
	अणु
	.name = "wm9713-voice",
	.playback = अणु
		.stream_name = "Voice Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = WM9713_PCM_RATES,
		.क्रमmats = WM9713_PCM_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "Voice Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM9713_PCM_RATES,
		.क्रमmats = WM9713_PCM_FORMATS,पूर्ण,
	.ops = &wm9713_dai_ops_voice,
	.symmetric_rate = 1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक wm9713_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		/* enable thermal shutकरोwn */
		snd_soc_component_update_bits(component, AC97_EXTENDED_MID, 0xe400, 0x0000);
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		/* enable master bias and vmid */
		snd_soc_component_update_bits(component, AC97_EXTENDED_MID, 0xc400, 0x0000);
		snd_soc_component_ग_लिखो(component, AC97_POWERDOWN, 0x0000);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* disable everything including AC link */
		snd_soc_component_ग_लिखो(component, AC97_EXTENDED_MID, 0xffff);
		snd_soc_component_ग_लिखो(component, AC97_EXTENDED_MSTATUS, 0xffff);
		snd_soc_component_ग_लिखो(component, AC97_POWERDOWN, 0xffff);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wm9713_soc_suspend(काष्ठा snd_soc_component *component)
अणु
	/* Disable everything except touchpanel - that will be handled
	 * by the touch driver and left disabled अगर touch is not in
	 * use. */
	snd_soc_component_update_bits(component, AC97_EXTENDED_MID, 0x7fff,
				 0x7fff);
	snd_soc_component_ग_लिखो(component, AC97_EXTENDED_MSTATUS, 0xffff);
	snd_soc_component_ग_लिखो(component, AC97_POWERDOWN, 0x6f00);
	snd_soc_component_ग_लिखो(component, AC97_POWERDOWN, 0xffff);

	वापस 0;
पूर्ण

अटल पूर्णांक wm9713_soc_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm9713_priv *wm9713 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = snd_ac97_reset(wm9713->ac97, true, WM9713_VENDOR_ID,
		WM9713_VENDOR_ID_MASK);
	अगर (ret < 0)
		वापस ret;

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);

	/* करो we need to re-start the PLL ? */
	अगर (wm9713->pll_in)
		wm9713_set_pll(component, 0, wm9713->pll_in, 0);

	/* only synchronise the codec अगर warm reset failed */
	अगर (ret == 0) अणु
		regcache_mark_dirty(component->regmap);
		snd_soc_component_cache_sync(component);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक wm9713_soc_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm9713_priv *wm9713 = snd_soc_component_get_drvdata(component);
	काष्ठा regmap *regmap = शून्य;

	अगर (wm9713->mfd_pdata) अणु
		wm9713->ac97 = wm9713->mfd_pdata->ac97;
		regmap = wm9713->mfd_pdata->regmap;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_SND_SOC_AC97_BUS)) अणु
		wm9713->ac97 = snd_soc_new_ac97_component(component, WM9713_VENDOR_ID,
						      WM9713_VENDOR_ID_MASK);
		अगर (IS_ERR(wm9713->ac97))
			वापस PTR_ERR(wm9713->ac97);
		regmap = regmap_init_ac97(wm9713->ac97, &wm9713_regmap_config);
		अगर (IS_ERR(regmap)) अणु
			snd_soc_मुक्त_ac97_component(wm9713->ac97);
			वापस PTR_ERR(regmap);
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -ENXIO;
	पूर्ण

	snd_soc_component_init_regmap(component, regmap);

	/* unmute the adc - move to kcontrol */
	snd_soc_component_update_bits(component, AC97_CD, 0x7fff, 0x0000);

	वापस 0;
पूर्ण

अटल व्योम wm9713_soc_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm9713_priv *wm9713 = snd_soc_component_get_drvdata(component);

	अगर (IS_ENABLED(CONFIG_SND_SOC_AC97_BUS) && !wm9713->mfd_pdata) अणु
		snd_soc_component_निकास_regmap(component);
		snd_soc_मुक्त_ac97_component(wm9713->ac97);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm9713 = अणु
	.probe			= wm9713_soc_probe,
	.हटाओ			= wm9713_soc_हटाओ,
	.suspend		= wm9713_soc_suspend,
	.resume			= wm9713_soc_resume,
	.set_bias_level		= wm9713_set_bias_level,
	.controls		= wm9713_snd_ac97_controls,
	.num_controls		= ARRAY_SIZE(wm9713_snd_ac97_controls),
	.dapm_widमाला_लो		= wm9713_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm9713_dapm_widमाला_लो),
	.dapm_routes		= wm9713_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(wm9713_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक wm9713_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm9713_priv *wm9713;

	wm9713 = devm_kzalloc(&pdev->dev, माप(*wm9713), GFP_KERNEL);
	अगर (wm9713 == शून्य)
		वापस -ENOMEM;

	mutex_init(&wm9713->lock);

	wm9713->mfd_pdata = dev_get_platdata(&pdev->dev);
	platक्रमm_set_drvdata(pdev, wm9713);

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_wm9713, wm9713_dai, ARRAY_SIZE(wm9713_dai));
पूर्ण

अटल काष्ठा platक्रमm_driver wm9713_codec_driver = अणु
	.driver = अणु
			.name = "wm9713-codec",
	पूर्ण,

	.probe = wm9713_probe,
पूर्ण;

module_platक्रमm_driver(wm9713_codec_driver);

MODULE_DESCRIPTION("ASoC WM9713/WM9714 driver");
MODULE_AUTHOR("Liam Girdwood");
MODULE_LICENSE("GPL");
