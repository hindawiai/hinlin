<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm9712.c  --  ALSA Soc WM9712 codec support
 *
 * Copyright 2006-12 Wolfson Microelectronics PLC.
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/wm97xx.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/ac97/codec.h>
#समावेश <sound/ac97/compat.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#घोषणा WM9712_VENDOR_ID 0x574d4c12
#घोषणा WM9712_VENDOR_ID_MASK 0xffffffff

काष्ठा wm9712_priv अणु
	काष्ठा snd_ac97 *ac97;
	अचिन्हित पूर्णांक hp_mixer[2];
	काष्ठा mutex lock;
	काष्ठा wm97xx_platक्रमm_data *mfd_pdata;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm9712_reg_शेषs[] = अणु
	अणु 0x02, 0x8000 पूर्ण,
	अणु 0x04, 0x8000 पूर्ण,
	अणु 0x06, 0x8000 पूर्ण,
	अणु 0x08, 0x0f0f पूर्ण,
	अणु 0x0a, 0xaaa0 पूर्ण,
	अणु 0x0c, 0xc008 पूर्ण,
	अणु 0x0e, 0x6808 पूर्ण,
	अणु 0x10, 0xe808 पूर्ण,
	अणु 0x12, 0xaaa0 पूर्ण,
	अणु 0x14, 0xad00 पूर्ण,
	अणु 0x16, 0x8000 पूर्ण,
	अणु 0x18, 0xe808 पूर्ण,
	अणु 0x1a, 0x3000 पूर्ण,
	अणु 0x1c, 0x8000 पूर्ण,
	अणु 0x20, 0x0000 पूर्ण,
	अणु 0x22, 0x0000 पूर्ण,
	अणु 0x26, 0x000f पूर्ण,
	अणु 0x28, 0x0605 पूर्ण,
	अणु 0x2a, 0x0410 पूर्ण,
	अणु 0x2c, 0xbb80 पूर्ण,
	अणु 0x2e, 0xbb80 पूर्ण,
	अणु 0x32, 0xbb80 पूर्ण,
	अणु 0x34, 0x2000 पूर्ण,
	अणु 0x4c, 0xf83e पूर्ण,
	अणु 0x4e, 0xffff पूर्ण,
	अणु 0x50, 0x0000 पूर्ण,
	अणु 0x52, 0x0000 पूर्ण,
	अणु 0x56, 0xf83e पूर्ण,
	अणु 0x58, 0x0008 पूर्ण,
	अणु 0x5c, 0x0000 पूर्ण,
	अणु 0x60, 0xb032 पूर्ण,
	अणु 0x62, 0x3e00 पूर्ण,
	अणु 0x64, 0x0000 पूर्ण,
	अणु 0x76, 0x0006 पूर्ण,
	अणु 0x78, 0x0001 पूर्ण,
	अणु 0x7a, 0x0000 पूर्ण,
पूर्ण;

अटल bool wm9712_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AC97_REC_GAIN:
		वापस true;
	शेष:
		वापस regmap_ac97_शेष_अस्थिर(dev, reg);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config wm9712_regmap_config = अणु
	.reg_bits = 16,
	.reg_stride = 2,
	.val_bits = 16,
	.max_रेजिस्टर = 0x7e,
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = wm9712_अस्थिर_reg,

	.reg_शेषs = wm9712_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm9712_reg_शेषs),
पूर्ण;

#घोषणा HPL_MIXER	0x0
#घोषणा HPR_MIXER	0x1

अटल स्थिर अक्षर *wm9712_alc_select[] = अणु"None", "Left", "Right", "Stereo"पूर्ण;
अटल स्थिर अक्षर *wm9712_alc_mux[] = अणु"Stereo", "Left", "Right", "None"पूर्ण;
अटल स्थिर अक्षर *wm9712_out3_src[] = अणु"Left", "VREF", "Left + Right",
	"Mono"पूर्ण;
अटल स्थिर अक्षर *wm9712_spk_src[] = अणु"Speaker Mix", "Headphone Mix"पूर्ण;
अटल स्थिर अक्षर *wm9712_rec_adc[] = अणु"Stereo", "Left", "Right", "Mute"पूर्ण;
अटल स्थिर अक्षर *wm9712_base[] = अणु"Linear Control", "Adaptive Boost"पूर्ण;
अटल स्थिर अक्षर *wm9712_rec_gain[] = अणु"+1.5dB Steps", "+0.75dB Steps"पूर्ण;
अटल स्थिर अक्षर *wm9712_mic[] = अणु"Mic 1", "Differential", "Mic 2",
	"Stereo"पूर्ण;
अटल स्थिर अक्षर *wm9712_rec_sel[] = अणु"Mic", "NC", "NC", "Speaker Mixer",
	"Line", "Headphone Mixer", "Phone Mixer", "Phone"पूर्ण;
अटल स्थिर अक्षर *wm9712_ng_type[] = अणु"Constant Gain", "Mute"पूर्ण;
अटल स्थिर अक्षर *wm9712_dअगरf_sel[] = अणु"Mic", "Line"पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(मुख्य_tlv, -3450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(boost_tlv, 0, 2000, 0);

अटल स्थिर काष्ठा soc_क्रमागत wm9712_क्रमागत[] = अणु
SOC_ENUM_SINGLE(AC97_PCI_SVID, 14, 4, wm9712_alc_select),
SOC_ENUM_SINGLE(AC97_VIDEO, 12, 4, wm9712_alc_mux),
SOC_ENUM_SINGLE(AC97_AUX, 9, 4, wm9712_out3_src),
SOC_ENUM_SINGLE(AC97_AUX, 8, 2, wm9712_spk_src),
SOC_ENUM_SINGLE(AC97_REC_SEL, 12, 4, wm9712_rec_adc),
SOC_ENUM_SINGLE(AC97_MASTER_TONE, 15, 2, wm9712_base),
SOC_ENUM_DOUBLE(AC97_REC_GAIN, 14, 6, 2, wm9712_rec_gain),
SOC_ENUM_SINGLE(AC97_MIC, 5, 4, wm9712_mic),
SOC_ENUM_SINGLE(AC97_REC_SEL, 8, 8, wm9712_rec_sel),
SOC_ENUM_SINGLE(AC97_REC_SEL, 0, 8, wm9712_rec_sel),
SOC_ENUM_SINGLE(AC97_PCI_SVID, 5, 2, wm9712_ng_type),
SOC_ENUM_SINGLE(0x5c, 8, 2, wm9712_dअगरf_sel),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm9712_snd_ac97_controls[] = अणु
SOC_DOUBLE("Speaker Playback Volume", AC97_MASTER, 8, 0, 31, 1),
SOC_SINGLE("Speaker Playback Switch", AC97_MASTER, 15, 1, 1),
SOC_DOUBLE("Headphone Playback Volume", AC97_HEADPHONE, 8, 0, 31, 1),
SOC_SINGLE("Headphone Playback Switch", AC97_HEADPHONE, 15, 1, 1),
SOC_DOUBLE("PCM Playback Volume", AC97_PCM, 8, 0, 31, 1),

SOC_SINGLE("Speaker Playback ZC Switch", AC97_MASTER, 7, 1, 0),
SOC_SINGLE("Speaker Playback Invert Switch", AC97_MASTER, 6, 1, 0),
SOC_SINGLE("Headphone Playback ZC Switch", AC97_HEADPHONE, 7, 1, 0),
SOC_SINGLE("Mono Playback ZC Switch", AC97_MASTER_MONO, 7, 1, 0),
SOC_SINGLE("Mono Playback Volume", AC97_MASTER_MONO, 0, 31, 1),
SOC_SINGLE("Mono Playback Switch", AC97_MASTER_MONO, 15, 1, 1),

SOC_SINGLE("ALC Target Volume", AC97_CODEC_CLASS_REV, 12, 15, 0),
SOC_SINGLE("ALC Hold Time", AC97_CODEC_CLASS_REV, 8, 15, 0),
SOC_SINGLE("ALC Decay Time", AC97_CODEC_CLASS_REV, 4, 15, 0),
SOC_SINGLE("ALC Attack Time", AC97_CODEC_CLASS_REV, 0, 15, 0),
SOC_ENUM("ALC Function", wm9712_क्रमागत[0]),
SOC_SINGLE("ALC Max Volume", AC97_PCI_SVID, 11, 7, 0),
SOC_SINGLE("ALC ZC Timeout", AC97_PCI_SVID, 9, 3, 1),
SOC_SINGLE("ALC ZC Switch", AC97_PCI_SVID, 8, 1, 0),
SOC_SINGLE("ALC NG Switch", AC97_PCI_SVID, 7, 1, 0),
SOC_ENUM("ALC NG Type", wm9712_क्रमागत[10]),
SOC_SINGLE("ALC NG Threshold", AC97_PCI_SVID, 0, 31, 1),

SOC_SINGLE("Mic Headphone  Volume", AC97_VIDEO, 12, 7, 1),
SOC_SINGLE("ALC Headphone Volume", AC97_VIDEO, 7, 7, 1),

SOC_SINGLE("Out3 Switch", AC97_AUX, 15, 1, 1),
SOC_SINGLE("Out3 ZC Switch", AC97_AUX, 7, 1, 1),
SOC_SINGLE("Out3 Volume", AC97_AUX, 0, 31, 1),

SOC_SINGLE("PCBeep Bypass Headphone Volume", AC97_PC_BEEP, 12, 7, 1),
SOC_SINGLE("PCBeep Bypass Speaker Volume", AC97_PC_BEEP, 8, 7, 1),
SOC_SINGLE("PCBeep Bypass Phone Volume", AC97_PC_BEEP, 4, 7, 1),

SOC_SINGLE("Aux Playback Headphone Volume", AC97_CD, 12, 7, 1),
SOC_SINGLE("Aux Playback Speaker Volume", AC97_CD, 8, 7, 1),
SOC_SINGLE("Aux Playback Phone Volume", AC97_CD, 4, 7, 1),

SOC_SINGLE("Phone Volume", AC97_PHONE, 0, 15, 1),
SOC_DOUBLE("Line Capture Volume", AC97_LINE, 8, 0, 31, 1),

SOC_SINGLE_TLV("Capture Boost Switch", AC97_REC_SEL, 14, 1, 0, boost_tlv),
SOC_SINGLE_TLV("Capture to Phone Boost Switch", AC97_REC_SEL, 11, 1, 1,
	       boost_tlv),

SOC_SINGLE("3D Upper Cut-off Switch", AC97_3D_CONTROL, 5, 1, 1),
SOC_SINGLE("3D Lower Cut-off Switch", AC97_3D_CONTROL, 4, 1, 1),
SOC_SINGLE("3D Playback Volume", AC97_3D_CONTROL, 0, 15, 0),

SOC_ENUM("Bass Control", wm9712_क्रमागत[5]),
SOC_SINGLE("Bass Cut-off Switch", AC97_MASTER_TONE, 12, 1, 1),
SOC_SINGLE("Tone Cut-off Switch", AC97_MASTER_TONE, 4, 1, 1),
SOC_SINGLE("Playback Attenuate (-6dB) Switch", AC97_MASTER_TONE, 6, 1, 0),
SOC_SINGLE("Bass Volume", AC97_MASTER_TONE, 8, 15, 1),
SOC_SINGLE("Treble Volume", AC97_MASTER_TONE, 0, 15, 1),

SOC_SINGLE("Capture Switch", AC97_REC_GAIN, 15, 1, 1),
SOC_ENUM("Capture Volume Steps", wm9712_क्रमागत[6]),
SOC_DOUBLE("Capture Volume", AC97_REC_GAIN, 8, 0, 63, 0),
SOC_SINGLE("Capture ZC Switch", AC97_REC_GAIN, 7, 1, 0),

SOC_SINGLE_TLV("Mic 1 Volume", AC97_MIC, 8, 31, 1, मुख्य_tlv),
SOC_SINGLE_TLV("Mic 2 Volume", AC97_MIC, 0, 31, 1, मुख्य_tlv),
SOC_SINGLE_TLV("Mic Boost Volume", AC97_MIC, 7, 1, 0, boost_tlv),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक wm9712_mixer_mute_regs[] = अणु
	AC97_VIDEO,
	AC97_PCM,
	AC97_LINE,
	AC97_PHONE,
	AC97_CD,
	AC97_PC_BEEP,
पूर्ण;

/* We have to create a fake left and right HP mixers because
 * the codec only has a single control that is shared by both channels.
 * This makes it impossible to determine the audio path.
 */
अटल पूर्णांक wm9712_hp_mixer_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	काष्ठा wm9712_priv *wm9712 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val = ucontrol->value.पूर्णांकeger.value[0];
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक mixer, mask, shअगरt, old;
	काष्ठा snd_soc_dapm_update update = अणुपूर्ण;
	bool change;

	mixer = mc->shअगरt >> 8;
	shअगरt = mc->shअगरt & 0xff;
	mask = 1 << shअगरt;

	mutex_lock(&wm9712->lock);
	old = wm9712->hp_mixer[mixer];
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		wm9712->hp_mixer[mixer] |= mask;
	अन्यथा
		wm9712->hp_mixer[mixer] &= ~mask;

	change = old != wm9712->hp_mixer[mixer];
	अगर (change) अणु
		update.kcontrol = kcontrol;
		update.reg = wm9712_mixer_mute_regs[shअगरt];
		update.mask = 0x8000;
		अगर ((wm9712->hp_mixer[0] & mask) ||
		    (wm9712->hp_mixer[1] & mask))
			update.val = 0x0;
		अन्यथा
			update.val = 0x8000;

		snd_soc_dapm_mixer_update_घातer(dapm, kcontrol, val,
			&update);
	पूर्ण

	mutex_unlock(&wm9712->lock);

	वापस change;
पूर्ण

अटल पूर्णांक wm9712_hp_mixer_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	काष्ठा wm9712_priv *wm9712 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक shअगरt, mixer;

	mixer = mc->shअगरt >> 8;
	shअगरt = mc->shअगरt & 0xff;

	ucontrol->value.पूर्णांकeger.value[0] =
		(wm9712->hp_mixer[mixer] >> shअगरt) & 1;

	वापस 0;
पूर्ण

#घोषणा WM9712_HP_MIXER_CTRL(xname, xmixer, xshअगरt) अणु \
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_volsw, \
	.get = wm9712_hp_mixer_get, .put = wm9712_hp_mixer_put, \
	.निजी_value = SOC_SINGLE_VALUE(SND_SOC_NOPM, \
		(xmixer << 8) | xshअगरt, 1, 0, 0) \
पूर्ण

/* Left Headphone Mixers */
अटल स्थिर काष्ठा snd_kcontrol_new wm9712_hpl_mixer_controls[] = अणु
	WM9712_HP_MIXER_CTRL("PCBeep Bypass Switch", HPL_MIXER, 5),
	WM9712_HP_MIXER_CTRL("Aux Playback Switch", HPL_MIXER, 4),
	WM9712_HP_MIXER_CTRL("Phone Bypass Switch", HPL_MIXER, 3),
	WM9712_HP_MIXER_CTRL("Line Bypass Switch", HPL_MIXER, 2),
	WM9712_HP_MIXER_CTRL("PCM Playback Switch", HPL_MIXER, 1),
	WM9712_HP_MIXER_CTRL("Mic Sidetone Switch", HPL_MIXER, 0),
पूर्ण;

/* Right Headphone Mixers */
अटल स्थिर काष्ठा snd_kcontrol_new wm9712_hpr_mixer_controls[] = अणु
	WM9712_HP_MIXER_CTRL("PCBeep Bypass Switch", HPR_MIXER, 5),
	WM9712_HP_MIXER_CTRL("Aux Playback Switch", HPR_MIXER, 4),
	WM9712_HP_MIXER_CTRL("Phone Bypass Switch", HPR_MIXER, 3),
	WM9712_HP_MIXER_CTRL("Line Bypass Switch", HPR_MIXER, 2),
	WM9712_HP_MIXER_CTRL("PCM Playback Switch", HPR_MIXER, 1),
	WM9712_HP_MIXER_CTRL("Mic Sidetone Switch", HPR_MIXER, 0),
पूर्ण;

/* Speaker Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm9712_speaker_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("PCBeep Bypass Switch", AC97_PC_BEEP, 11, 1, 1),
	SOC_DAPM_SINGLE("Aux Playback Switch", AC97_CD, 11, 1, 1),
	SOC_DAPM_SINGLE("Phone Bypass Switch", AC97_PHONE, 14, 1, 1),
	SOC_DAPM_SINGLE("Line Bypass Switch", AC97_LINE, 14, 1, 1),
	SOC_DAPM_SINGLE("PCM Playback Switch", AC97_PCM, 14, 1, 1),
पूर्ण;

/* Phone Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm9712_phone_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("PCBeep Bypass Switch", AC97_PC_BEEP, 7, 1, 1),
	SOC_DAPM_SINGLE("Aux Playback Switch", AC97_CD, 7, 1, 1),
	SOC_DAPM_SINGLE("Line Bypass Switch", AC97_LINE, 13, 1, 1),
	SOC_DAPM_SINGLE("PCM Playback Switch", AC97_PCM, 13, 1, 1),
	SOC_DAPM_SINGLE("Mic 1 Sidetone Switch", AC97_MIC, 14, 1, 1),
	SOC_DAPM_SINGLE("Mic 2 Sidetone Switch", AC97_MIC, 13, 1, 1),
पूर्ण;

/* ALC headphone mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm9712_alc_mux_controls =
SOC_DAPM_ENUM("Route", wm9712_क्रमागत[1]);

/* out 3 mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm9712_out3_mux_controls =
SOC_DAPM_ENUM("Route", wm9712_क्रमागत[2]);

/* spk mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm9712_spk_mux_controls =
SOC_DAPM_ENUM("Route", wm9712_क्रमागत[3]);

/* Capture to Phone mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm9712_capture_phone_mux_controls =
SOC_DAPM_ENUM("Route", wm9712_क्रमागत[4]);

/* Capture left select */
अटल स्थिर काष्ठा snd_kcontrol_new wm9712_capture_selectl_controls =
SOC_DAPM_ENUM("Route", wm9712_क्रमागत[8]);

/* Capture right select */
अटल स्थिर काष्ठा snd_kcontrol_new wm9712_capture_selectr_controls =
SOC_DAPM_ENUM("Route", wm9712_क्रमागत[9]);

/* Mic select */
अटल स्थिर काष्ठा snd_kcontrol_new wm9712_mic_src_controls =
SOC_DAPM_ENUM("Mic Source Select", wm9712_क्रमागत[7]);

/* dअगरf select */
अटल स्थिर काष्ठा snd_kcontrol_new wm9712_dअगरf_sel_controls =
SOC_DAPM_ENUM("Route", wm9712_क्रमागत[11]);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm9712_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_MUX("ALC Sidetone Mux", SND_SOC_NOPM, 0, 0,
	&wm9712_alc_mux_controls),
SND_SOC_DAPM_MUX("Out3 Mux", SND_SOC_NOPM, 0, 0,
	&wm9712_out3_mux_controls),
SND_SOC_DAPM_MUX("Speaker Mux", SND_SOC_NOPM, 0, 0,
	&wm9712_spk_mux_controls),
SND_SOC_DAPM_MUX("Capture Phone Mux", SND_SOC_NOPM, 0, 0,
	&wm9712_capture_phone_mux_controls),
SND_SOC_DAPM_MUX("Left Capture Select", SND_SOC_NOPM, 0, 0,
	&wm9712_capture_selectl_controls),
SND_SOC_DAPM_MUX("Right Capture Select", SND_SOC_NOPM, 0, 0,
	&wm9712_capture_selectr_controls),
SND_SOC_DAPM_MUX("Left Mic Select Source", SND_SOC_NOPM, 0, 0,
	&wm9712_mic_src_controls),
SND_SOC_DAPM_MUX("Right Mic Select Source", SND_SOC_NOPM, 0, 0,
	&wm9712_mic_src_controls),
SND_SOC_DAPM_MUX("Differential Source", SND_SOC_NOPM, 0, 0,
	&wm9712_dअगरf_sel_controls),
SND_SOC_DAPM_MIXER("AC97 Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("Left HP Mixer", AC97_INT_PAGING, 9, 1,
	&wm9712_hpl_mixer_controls[0], ARRAY_SIZE(wm9712_hpl_mixer_controls)),
SND_SOC_DAPM_MIXER("Right HP Mixer", AC97_INT_PAGING, 8, 1,
	&wm9712_hpr_mixer_controls[0], ARRAY_SIZE(wm9712_hpr_mixer_controls)),
SND_SOC_DAPM_MIXER("Phone Mixer", AC97_INT_PAGING, 6, 1,
	&wm9712_phone_mixer_controls[0], ARRAY_SIZE(wm9712_phone_mixer_controls)),
SND_SOC_DAPM_MIXER("Speaker Mixer", AC97_INT_PAGING, 7, 1,
	&wm9712_speaker_mixer_controls[0],
	ARRAY_SIZE(wm9712_speaker_mixer_controls)),
SND_SOC_DAPM_MIXER("Mono Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_DAC("Left DAC", "Left HiFi Playback", AC97_INT_PAGING, 14, 1),
SND_SOC_DAPM_DAC("Right DAC", "Right HiFi Playback", AC97_INT_PAGING, 13, 1),
SND_SOC_DAPM_DAC("Aux DAC", "Aux Playback", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_ADC("Left ADC", "Left HiFi Capture", AC97_INT_PAGING, 12, 1),
SND_SOC_DAPM_ADC("Right ADC", "Right HiFi Capture", AC97_INT_PAGING, 11, 1),
SND_SOC_DAPM_PGA("Headphone PGA", AC97_INT_PAGING, 4, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Speaker PGA", AC97_INT_PAGING, 3, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Out 3 PGA", AC97_INT_PAGING, 5, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Line PGA", AC97_INT_PAGING, 2, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Phone PGA", AC97_INT_PAGING, 1, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Mic PGA", AC97_INT_PAGING, 0, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Differential Mic", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_MICBIAS("Mic Bias", AC97_INT_PAGING, 10, 1),
SND_SOC_DAPM_OUTPUT("MONOOUT"),
SND_SOC_DAPM_OUTPUT("HPOUTL"),
SND_SOC_DAPM_OUTPUT("HPOUTR"),
SND_SOC_DAPM_OUTPUT("LOUT2"),
SND_SOC_DAPM_OUTPUT("ROUT2"),
SND_SOC_DAPM_OUTPUT("OUT3"),
SND_SOC_DAPM_INPUT("LINEINL"),
SND_SOC_DAPM_INPUT("LINEINR"),
SND_SOC_DAPM_INPUT("PHONE"),
SND_SOC_DAPM_INPUT("PCBEEP"),
SND_SOC_DAPM_INPUT("MIC1"),
SND_SOC_DAPM_INPUT("MIC2"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm9712_audio_map[] = अणु
	/* भव mixer - mixes left & right channels क्रम spk and mono */
	अणु"AC97 Mixer", शून्य, "Left DAC"पूर्ण,
	अणु"AC97 Mixer", शून्य, "Right DAC"पूर्ण,

	/* Left HP mixer */
	अणु"Left HP Mixer", "PCBeep Bypass Switch", "PCBEEP"पूर्ण,
	अणु"Left HP Mixer", "Aux Playback Switch",  "Aux DAC"पूर्ण,
	अणु"Left HP Mixer", "Phone Bypass Switch",  "Phone PGA"पूर्ण,
	अणु"Left HP Mixer", "Line Bypass Switch",   "Line PGA"पूर्ण,
	अणु"Left HP Mixer", "PCM Playback Switch",  "Left DAC"पूर्ण,
	अणु"Left HP Mixer", "Mic Sidetone Switch",  "Mic PGA"पूर्ण,
	अणु"Left HP Mixer", शून्य,  "ALC Sidetone Mux"पूर्ण,

	/* Right HP mixer */
	अणु"Right HP Mixer", "PCBeep Bypass Switch", "PCBEEP"पूर्ण,
	अणु"Right HP Mixer", "Aux Playback Switch",  "Aux DAC"पूर्ण,
	अणु"Right HP Mixer", "Phone Bypass Switch",  "Phone PGA"पूर्ण,
	अणु"Right HP Mixer", "Line Bypass Switch",   "Line PGA"पूर्ण,
	अणु"Right HP Mixer", "PCM Playback Switch",  "Right DAC"पूर्ण,
	अणु"Right HP Mixer", "Mic Sidetone Switch",  "Mic PGA"पूर्ण,
	अणु"Right HP Mixer", शून्य,  "ALC Sidetone Mux"पूर्ण,

	/* speaker mixer */
	अणु"Speaker Mixer", "PCBeep Bypass Switch", "PCBEEP"पूर्ण,
	अणु"Speaker Mixer", "Line Bypass Switch",   "Line PGA"पूर्ण,
	अणु"Speaker Mixer", "PCM Playback Switch",  "AC97 Mixer"पूर्ण,
	अणु"Speaker Mixer", "Phone Bypass Switch",  "Phone PGA"पूर्ण,
	अणु"Speaker Mixer", "Aux Playback Switch",  "Aux DAC"पूर्ण,

	/* Phone mixer */
	अणु"Phone Mixer", "PCBeep Bypass Switch",  "PCBEEP"पूर्ण,
	अणु"Phone Mixer", "Line Bypass Switch",    "Line PGA"पूर्ण,
	अणु"Phone Mixer", "Aux Playback Switch",   "Aux DAC"पूर्ण,
	अणु"Phone Mixer", "PCM Playback Switch",   "AC97 Mixer"पूर्ण,
	अणु"Phone Mixer", "Mic 1 Sidetone Switch", "Mic PGA"पूर्ण,
	अणु"Phone Mixer", "Mic 2 Sidetone Switch", "Mic PGA"पूर्ण,

	/* inमाला_दो */
	अणु"Line PGA", शून्य, "LINEINL"पूर्ण,
	अणु"Line PGA", शून्य, "LINEINR"पूर्ण,
	अणु"Phone PGA", शून्य, "PHONE"पूर्ण,
	अणु"Mic PGA", शून्य, "MIC1"पूर्ण,
	अणु"Mic PGA", शून्य, "MIC2"पूर्ण,

	/* microphones */
	अणु"Differential Mic", शून्य, "MIC1"पूर्ण,
	अणु"Differential Mic", शून्य, "MIC2"पूर्ण,
	अणु"Left Mic Select Source", "Mic 1", "MIC1"पूर्ण,
	अणु"Left Mic Select Source", "Mic 2", "MIC2"पूर्ण,
	अणु"Left Mic Select Source", "Stereo", "MIC1"पूर्ण,
	अणु"Left Mic Select Source", "Differential", "Differential Mic"पूर्ण,
	अणु"Right Mic Select Source", "Mic 1", "MIC1"पूर्ण,
	अणु"Right Mic Select Source", "Mic 2", "MIC2"पूर्ण,
	अणु"Right Mic Select Source", "Stereo", "MIC2"पूर्ण,
	अणु"Right Mic Select Source", "Differential", "Differential Mic"पूर्ण,

	/* left capture selector */
	अणु"Left Capture Select", "Mic", "MIC1"पूर्ण,
	अणु"Left Capture Select", "Speaker Mixer", "Speaker Mixer"पूर्ण,
	अणु"Left Capture Select", "Line", "LINEINL"पूर्ण,
	अणु"Left Capture Select", "Headphone Mixer", "Left HP Mixer"पूर्ण,
	अणु"Left Capture Select", "Phone Mixer", "Phone Mixer"पूर्ण,
	अणु"Left Capture Select", "Phone", "PHONE"पूर्ण,

	/* right capture selector */
	अणु"Right Capture Select", "Mic", "MIC2"पूर्ण,
	अणु"Right Capture Select", "Speaker Mixer", "Speaker Mixer"पूर्ण,
	अणु"Right Capture Select", "Line", "LINEINR"पूर्ण,
	अणु"Right Capture Select", "Headphone Mixer", "Right HP Mixer"पूर्ण,
	अणु"Right Capture Select", "Phone Mixer", "Phone Mixer"पूर्ण,
	अणु"Right Capture Select", "Phone", "PHONE"पूर्ण,

	/* ALC Sidetone */
	अणु"ALC Sidetone Mux", "Stereo", "Left Capture Select"पूर्ण,
	अणु"ALC Sidetone Mux", "Stereo", "Right Capture Select"पूर्ण,
	अणु"ALC Sidetone Mux", "Left", "Left Capture Select"पूर्ण,
	अणु"ALC Sidetone Mux", "Right", "Right Capture Select"पूर्ण,

	/* ADC's */
	अणु"Left ADC", शून्य, "Left Capture Select"पूर्ण,
	अणु"Right ADC", शून्य, "Right Capture Select"पूर्ण,

	/* outमाला_दो */
	अणु"MONOOUT", शून्य, "Phone Mixer"पूर्ण,
	अणु"HPOUTL", शून्य, "Headphone PGA"पूर्ण,
	अणु"Headphone PGA", शून्य, "Left HP Mixer"पूर्ण,
	अणु"HPOUTR", शून्य, "Headphone PGA"पूर्ण,
	अणु"Headphone PGA", शून्य, "Right HP Mixer"पूर्ण,

	/* mono mixer */
	अणु"Mono Mixer", शून्य, "Left HP Mixer"पूर्ण,
	अणु"Mono Mixer", शून्य, "Right HP Mixer"पूर्ण,

	/* Out3 Mux */
	अणु"Out3 Mux", "Left", "Left HP Mixer"पूर्ण,
	अणु"Out3 Mux", "Mono", "Phone Mixer"पूर्ण,
	अणु"Out3 Mux", "Left + Right", "Mono Mixer"पूर्ण,
	अणु"Out 3 PGA", शून्य, "Out3 Mux"पूर्ण,
	अणु"OUT3", शून्य, "Out 3 PGA"पूर्ण,

	/* speaker Mux */
	अणु"Speaker Mux", "Speaker Mix", "Speaker Mixer"पूर्ण,
	अणु"Speaker Mux", "Headphone Mix", "Mono Mixer"पूर्ण,
	अणु"Speaker PGA", शून्य, "Speaker Mux"पूर्ण,
	अणु"LOUT2", शून्य, "Speaker PGA"पूर्ण,
	अणु"ROUT2", शून्य, "Speaker PGA"पूर्ण,
पूर्ण;

अटल पूर्णांक ac97_prepare(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक reg;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_soc_component_update_bits(component, AC97_EXTENDED_STATUS, 0x1, 0x1);

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

	snd_soc_component_update_bits(component, AC97_EXTENDED_STATUS, 0x1, 0x1);
	snd_soc_component_update_bits(component, AC97_PCI_SID, 0x8000, 0x8000);

	अगर (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
		वापस -ENODEV;

	वापस snd_soc_component_ग_लिखो(component, AC97_PCM_SURR_DAC_RATE, runसमय->rate);
पूर्ण

#घोषणा WM9712_AC97_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
		SNDRV_PCM_RATE_22050 | SNDRV_PCM_RATE_44100 |\
		SNDRV_PCM_RATE_48000)

अटल स्थिर काष्ठा snd_soc_dai_ops wm9712_dai_ops_hअगरi = अणु
	.prepare	= ac97_prepare,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops wm9712_dai_ops_aux = अणु
	.prepare	= ac97_aux_prepare,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm9712_dai[] = अणु
अणु
	.name = "wm9712-hifi",
	.playback = अणु
		.stream_name = "HiFi Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM9712_AC97_RATES,
		.क्रमmats = SND_SOC_STD_AC97_FMTS,पूर्ण,
	.capture = अणु
		.stream_name = "HiFi Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM9712_AC97_RATES,
		.क्रमmats = SND_SOC_STD_AC97_FMTS,पूर्ण,
	.ops = &wm9712_dai_ops_hअगरi,
पूर्ण,
अणु
	.name = "wm9712-aux",
	.playback = अणु
		.stream_name = "Aux Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = WM9712_AC97_RATES,
		.क्रमmats = SND_SOC_STD_AC97_FMTS,पूर्ण,
	.ops = &wm9712_dai_ops_aux,
पूर्ण
पूर्ण;

अटल पूर्णांक wm9712_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		snd_soc_component_ग_लिखो(component, AC97_POWERDOWN, 0x0000);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* disable everything including AC link */
		snd_soc_component_ग_लिखो(component, AC97_EXTENDED_MSTATUS, 0xffff);
		snd_soc_component_ग_लिखो(component, AC97_POWERDOWN, 0xffff);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wm9712_soc_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm9712_priv *wm9712 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = snd_ac97_reset(wm9712->ac97, true, WM9712_VENDOR_ID,
		WM9712_VENDOR_ID_MASK);
	अगर (ret < 0)
		वापस ret;

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);

	अगर (ret == 0)
		snd_soc_component_cache_sync(component);

	वापस ret;
पूर्ण

अटल पूर्णांक wm9712_soc_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm9712_priv *wm9712 = snd_soc_component_get_drvdata(component);
	काष्ठा regmap *regmap;

	अगर (wm9712->mfd_pdata) अणु
		wm9712->ac97 = wm9712->mfd_pdata->ac97;
		regmap = wm9712->mfd_pdata->regmap;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_SND_SOC_AC97_BUS)) अणु
		पूर्णांक ret;

		wm9712->ac97 = snd_soc_new_ac97_component(component, WM9712_VENDOR_ID,
						      WM9712_VENDOR_ID_MASK);
		अगर (IS_ERR(wm9712->ac97)) अणु
			ret = PTR_ERR(wm9712->ac97);
			dev_err(component->dev,
				"Failed to register AC97 codec: %d\n", ret);
			वापस ret;
		पूर्ण

		regmap = regmap_init_ac97(wm9712->ac97, &wm9712_regmap_config);
		अगर (IS_ERR(regmap)) अणु
			snd_soc_मुक्त_ac97_component(wm9712->ac97);
			वापस PTR_ERR(regmap);
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -ENXIO;
	पूर्ण

	snd_soc_component_init_regmap(component, regmap);

	/* set alc mux to none */
	snd_soc_component_update_bits(component, AC97_VIDEO, 0x3000, 0x3000);

	वापस 0;
पूर्ण

अटल व्योम wm9712_soc_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm9712_priv *wm9712 = snd_soc_component_get_drvdata(component);

	अगर (IS_ENABLED(CONFIG_SND_SOC_AC97_BUS) && !wm9712->mfd_pdata) अणु
		snd_soc_component_निकास_regmap(component);
		snd_soc_मुक्त_ac97_component(wm9712->ac97);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm9712 = अणु
	.probe			= wm9712_soc_probe,
	.हटाओ			= wm9712_soc_हटाओ,
	.resume			= wm9712_soc_resume,
	.set_bias_level		= wm9712_set_bias_level,
	.controls		= wm9712_snd_ac97_controls,
	.num_controls		= ARRAY_SIZE(wm9712_snd_ac97_controls),
	.dapm_widमाला_लो		= wm9712_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm9712_dapm_widमाला_लो),
	.dapm_routes		= wm9712_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(wm9712_audio_map),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक wm9712_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm9712_priv *wm9712;

	wm9712 = devm_kzalloc(&pdev->dev, माप(*wm9712), GFP_KERNEL);
	अगर (wm9712 == शून्य)
		वापस -ENOMEM;

	mutex_init(&wm9712->lock);

	wm9712->mfd_pdata = dev_get_platdata(&pdev->dev);
	platक्रमm_set_drvdata(pdev, wm9712);

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_wm9712, wm9712_dai, ARRAY_SIZE(wm9712_dai));
पूर्ण

अटल काष्ठा platक्रमm_driver wm9712_component_driver = अणु
	.driver = अणु
		.name = "wm9712-codec",
	पूर्ण,

	.probe = wm9712_probe,
पूर्ण;

module_platक्रमm_driver(wm9712_component_driver);

MODULE_DESCRIPTION("ASoC WM9711/WM9712 driver");
MODULE_AUTHOR("Liam Girdwood");
MODULE_LICENSE("GPL");
