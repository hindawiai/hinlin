<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cs42l73.c  --  CS42L73 ALSA Soc Audio driver
 *
 * Copyright 2011 Cirrus Logic, Inc.
 *
 * Authors: Georgi Vlaev, Nucleus Systems Ltd, <joe@nucleusys.com>
 *	    Brian Austin, Cirrus Logic Inc, <brian.austin@cirrus.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/cs42l73.h>
#समावेश "cs42l73.h"

काष्ठा sp_config अणु
	u8 spc, mmcc, spfs;
	u32 srate;
पूर्ण;
काष्ठा  cs42l73_निजी अणु
	काष्ठा cs42l73_platक्रमm_data pdata;
	काष्ठा sp_config config[3];
	काष्ठा regmap *regmap;
	u32 sysclk;
	u8 mclksel;
	u32 mclk;
	पूर्णांक shutdwn_delay;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष cs42l73_reg_शेषs[] = अणु
	अणु 6, 0xF1 पूर्ण,	/* r06	- Power Ctl 1 */
	अणु 7, 0xDF पूर्ण,	/* r07	- Power Ctl 2 */
	अणु 8, 0x3F पूर्ण,	/* r08	- Power Ctl 3 */
	अणु 9, 0x50 पूर्ण,	/* r09	- Charge Pump Freq */
	अणु 10, 0x53 पूर्ण,	/* r0A	- Output Load MicBias Short Detect */
	अणु 11, 0x00 पूर्ण,	/* r0B	- DMIC Master Clock Ctl */
	अणु 12, 0x00 पूर्ण,	/* r0C	- Aux PCM Ctl */
	अणु 13, 0x15 पूर्ण,	/* r0D	- Aux PCM Master Clock Ctl */
	अणु 14, 0x00 पूर्ण,	/* r0E	- Audio PCM Ctl */
	अणु 15, 0x15 पूर्ण,	/* r0F	- Audio PCM Master Clock Ctl */
	अणु 16, 0x00 पूर्ण,	/* r10	- Voice PCM Ctl */
	अणु 17, 0x15 पूर्ण,	/* r11	- Voice PCM Master Clock Ctl */
	अणु 18, 0x00 पूर्ण,	/* r12	- Voice/Aux Sample Rate */
	अणु 19, 0x06 पूर्ण,	/* r13	- Misc I/O Path Ctl */
	अणु 20, 0x00 पूर्ण,	/* r14	- ADC Input Path Ctl */
	अणु 21, 0x00 पूर्ण,	/* r15	- MICA Preamp, PGA Volume */
	अणु 22, 0x00 पूर्ण,	/* r16	- MICB Preamp, PGA Volume */
	अणु 23, 0x00 पूर्ण,	/* r17	- Input Path A Digital Volume */
	अणु 24, 0x00 पूर्ण,	/* r18	- Input Path B Digital Volume */
	अणु 25, 0x00 पूर्ण,	/* r19	- Playback Digital Ctl */
	अणु 26, 0x00 पूर्ण,	/* r1A	- HP/LO Left Digital Volume */
	अणु 27, 0x00 पूर्ण,	/* r1B	- HP/LO Right Digital Volume */
	अणु 28, 0x00 पूर्ण,	/* r1C	- Speakerphone Digital Volume */
	अणु 29, 0x00 पूर्ण,	/* r1D	- Ear/SPKLO Digital Volume */
	अणु 30, 0x00 पूर्ण,	/* r1E	- HP Left Analog Volume */
	अणु 31, 0x00 पूर्ण,	/* r1F	- HP Right Analog Volume */
	अणु 32, 0x00 पूर्ण,	/* r20	- LO Left Analog Volume */
	अणु 33, 0x00 पूर्ण,	/* r21	- LO Right Analog Volume */
	अणु 34, 0x00 पूर्ण,	/* r22	- Stereo Input Path Advisory Volume */
	अणु 35, 0x00 पूर्ण,	/* r23	- Aux PCM Input Advisory Volume */
	अणु 36, 0x00 पूर्ण,	/* r24	- Audio PCM Input Advisory Volume */
	अणु 37, 0x00 पूर्ण,	/* r25	- Voice PCM Input Advisory Volume */
	अणु 38, 0x00 पूर्ण,	/* r26	- Limiter Attack Rate HP/LO */
	अणु 39, 0x7F पूर्ण,	/* r27	- Limter Ctl, Release Rate HP/LO */
	अणु 40, 0x00 पूर्ण,	/* r28	- Limter Threshold HP/LO */
	अणु 41, 0x00 पूर्ण,	/* r29	- Limiter Attack Rate Speakerphone */
	अणु 42, 0x3F पूर्ण,	/* r2A	- Limter Ctl, Release Rate Speakerphone */
	अणु 43, 0x00 पूर्ण,	/* r2B	- Limter Threshold Speakerphone */
	अणु 44, 0x00 पूर्ण,	/* r2C	- Limiter Attack Rate Ear/SPKLO */
	अणु 45, 0x3F पूर्ण,	/* r2D	- Limter Ctl, Release Rate Ear/SPKLO */
	अणु 46, 0x00 पूर्ण,	/* r2E	- Limter Threshold Ear/SPKLO */
	अणु 47, 0x00 पूर्ण,	/* r2F	- ALC Enable, Attack Rate Left/Right */
	अणु 48, 0x3F पूर्ण,	/* r30	- ALC Release Rate Left/Right */
	अणु 49, 0x00 पूर्ण,	/* r31	- ALC Threshold Left/Right */
	अणु 50, 0x00 पूर्ण,	/* r32	- Noise Gate Ctl Left/Right */
	अणु 51, 0x00 पूर्ण,	/* r33	- ALC/NG Misc Ctl */
	अणु 52, 0x18 पूर्ण,	/* r34	- Mixer Ctl */
	अणु 53, 0x3F पूर्ण,	/* r35	- HP/LO Left Mixer Input Path Volume */
	अणु 54, 0x3F पूर्ण,	/* r36	- HP/LO Right Mixer Input Path Volume */
	अणु 55, 0x3F पूर्ण,	/* r37	- HP/LO Left Mixer Aux PCM Volume */
	अणु 56, 0x3F पूर्ण,	/* r38	- HP/LO Right Mixer Aux PCM Volume */
	अणु 57, 0x3F पूर्ण,	/* r39	- HP/LO Left Mixer Audio PCM Volume */
	अणु 58, 0x3F पूर्ण,	/* r3A	- HP/LO Right Mixer Audio PCM Volume */
	अणु 59, 0x3F पूर्ण,	/* r3B	- HP/LO Left Mixer Voice PCM Mono Volume */
	अणु 60, 0x3F पूर्ण,	/* r3C	- HP/LO Right Mixer Voice PCM Mono Volume */
	अणु 61, 0x3F पूर्ण,	/* r3D	- Aux PCM Left Mixer Input Path Volume */
	अणु 62, 0x3F पूर्ण,	/* r3E	- Aux PCM Right Mixer Input Path Volume */
	अणु 63, 0x3F पूर्ण,	/* r3F	- Aux PCM Left Mixer Volume */
	अणु 64, 0x3F पूर्ण,	/* r40	- Aux PCM Left Mixer Volume */
	अणु 65, 0x3F पूर्ण,	/* r41	- Aux PCM Left Mixer Audio PCM L Volume */
	अणु 66, 0x3F पूर्ण,	/* r42	- Aux PCM Right Mixer Audio PCM R Volume */
	अणु 67, 0x3F पूर्ण,	/* r43	- Aux PCM Left Mixer Voice PCM Volume */
	अणु 68, 0x3F पूर्ण,	/* r44	- Aux PCM Right Mixer Voice PCM Volume */
	अणु 69, 0x3F पूर्ण,	/* r45	- Audio PCM Left Input Path Volume */
	अणु 70, 0x3F पूर्ण,	/* r46	- Audio PCM Right Input Path Volume */
	अणु 71, 0x3F पूर्ण,	/* r47	- Audio PCM Left Mixer Aux PCM L Volume */
	अणु 72, 0x3F पूर्ण,	/* r48	- Audio PCM Right Mixer Aux PCM R Volume */
	अणु 73, 0x3F पूर्ण,	/* r49	- Audio PCM Left Mixer Volume */
	अणु 74, 0x3F पूर्ण,	/* r4A	- Audio PCM Right Mixer Volume */
	अणु 75, 0x3F पूर्ण,	/* r4B	- Audio PCM Left Mixer Voice PCM Volume */
	अणु 76, 0x3F पूर्ण,	/* r4C	- Audio PCM Right Mixer Voice PCM Volume */
	अणु 77, 0x3F पूर्ण,	/* r4D	- Voice PCM Left Input Path Volume */
	अणु 78, 0x3F पूर्ण,	/* r4E	- Voice PCM Right Input Path Volume */
	अणु 79, 0x3F पूर्ण,	/* r4F	- Voice PCM Left Mixer Aux PCM L Volume */
	अणु 80, 0x3F पूर्ण,	/* r50	- Voice PCM Right Mixer Aux PCM R Volume */
	अणु 81, 0x3F पूर्ण,	/* r51	- Voice PCM Left Mixer Audio PCM L Volume */
	अणु 82, 0x3F पूर्ण,	/* r52	- Voice PCM Right Mixer Audio PCM R Volume */
	अणु 83, 0x3F पूर्ण,	/* r53	- Voice PCM Left Mixer Voice PCM Volume */
	अणु 84, 0x3F पूर्ण,	/* r54	- Voice PCM Right Mixer Voice PCM Volume */
	अणु 85, 0xAA पूर्ण,	/* r55	- Mono Mixer Ctl */
	अणु 86, 0x3F पूर्ण,	/* r56	- SPK Mono Mixer Input Path Volume */
	अणु 87, 0x3F पूर्ण,	/* r57	- SPK Mono Mixer Aux PCM Mono/L/R Volume */
	अणु 88, 0x3F पूर्ण,	/* r58	- SPK Mono Mixer Audio PCM Mono/L/R Volume */
	अणु 89, 0x3F पूर्ण,	/* r59	- SPK Mono Mixer Voice PCM Mono Volume */
	अणु 90, 0x3F पूर्ण,	/* r5A	- SPKLO Mono Mixer Input Path Mono Volume */
	अणु 91, 0x3F पूर्ण,	/* r5B	- SPKLO Mono Mixer Aux Mono/L/R Volume */
	अणु 92, 0x3F पूर्ण,	/* r5C	- SPKLO Mono Mixer Audio Mono/L/R Volume */
	अणु 93, 0x3F पूर्ण,	/* r5D	- SPKLO Mono Mixer Voice Mono Volume */
	अणु 94, 0x00 पूर्ण,	/* r5E	- Interrupt Mask 1 */
	अणु 95, 0x00 पूर्ण,	/* r5F	- Interrupt Mask 2 */
पूर्ण;

अटल bool cs42l73_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS42L73_IS1:
	हाल CS42L73_IS2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs42l73_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS42L73_DEVID_AB ... CS42L73_DEVID_E:
	हाल CS42L73_REVID ... CS42L73_IM2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_RANGE(hpaloa_tlv,
	0, 13, TLV_DB_SCALE_ITEM(-7600, 200, 0),
	14, 75, TLV_DB_SCALE_ITEM(-4900, 100, 0)
);

अटल DECLARE_TLV_DB_SCALE(adc_boost_tlv, 0, 2500, 0);

अटल DECLARE_TLV_DB_SCALE(hl_tlv, -10200, 50, 0);

अटल DECLARE_TLV_DB_SCALE(ipd_tlv, -9600, 100, 0);

अटल DECLARE_TLV_DB_SCALE(micpga_tlv, -600, 50, 0);

अटल स्थिर DECLARE_TLV_DB_RANGE(limiter_tlv,
	0, 2, TLV_DB_SCALE_ITEM(-3000, 600, 0),
	3, 7, TLV_DB_SCALE_ITEM(-1200, 300, 0)
);

अटल स्थिर DECLARE_TLV_DB_SCALE(attn_tlv, -6300, 100, 1);

अटल स्थिर अक्षर * स्थिर cs42l73_pgaa_text[] = अणु "Line A", "Mic 1" पूर्ण;
अटल स्थिर अक्षर * स्थिर cs42l73_pgab_text[] = अणु "Line B", "Mic 2" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(pgaa_क्रमागत,
			    CS42L73_ADCIPC, 3,
			    cs42l73_pgaa_text);

अटल SOC_ENUM_SINGLE_DECL(pgab_क्रमागत,
			    CS42L73_ADCIPC, 7,
			    cs42l73_pgab_text);

अटल स्थिर काष्ठा snd_kcontrol_new pgaa_mux =
	SOC_DAPM_ENUM("Left Analog Input Capture Mux", pgaa_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new pgab_mux =
	SOC_DAPM_ENUM("Right Analog Input Capture Mux", pgab_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new input_left_mixer[] = अणु
	SOC_DAPM_SINGLE("ADC Left Input", CS42L73_PWRCTL1,
			5, 1, 1),
	SOC_DAPM_SINGLE("DMIC Left Input", CS42L73_PWRCTL1,
			4, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new input_right_mixer[] = अणु
	SOC_DAPM_SINGLE("ADC Right Input", CS42L73_PWRCTL1,
			7, 1, 1),
	SOC_DAPM_SINGLE("DMIC Right Input", CS42L73_PWRCTL1,
			6, 1, 1),
पूर्ण;

अटल स्थिर अक्षर * स्थिर cs42l73_ng_delay_text[] = अणु
	"50ms", "100ms", "150ms", "200ms" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(ng_delay_क्रमागत,
			    CS42L73_NGCAB, 0,
			    cs42l73_ng_delay_text);

अटल स्थिर अक्षर * स्थिर cs42l73_mono_mix_texts[] = अणु
	"Left", "Right", "Mono Mix"पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक cs42l73_mono_mix_values[] = अणु 0, 1, 2 पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत spk_asp_क्रमागत =
	SOC_VALUE_ENUM_SINGLE(CS42L73_MMIXCTL, 6, 3,
			      ARRAY_SIZE(cs42l73_mono_mix_texts),
			      cs42l73_mono_mix_texts,
			      cs42l73_mono_mix_values);

अटल स्थिर काष्ठा snd_kcontrol_new spk_asp_mixer =
	SOC_DAPM_ENUM("Route", spk_asp_क्रमागत);

अटल स्थिर काष्ठा soc_क्रमागत spk_xsp_क्रमागत =
	SOC_VALUE_ENUM_SINGLE(CS42L73_MMIXCTL, 4, 3,
			      ARRAY_SIZE(cs42l73_mono_mix_texts),
			      cs42l73_mono_mix_texts,
			      cs42l73_mono_mix_values);

अटल स्थिर काष्ठा snd_kcontrol_new spk_xsp_mixer =
	SOC_DAPM_ENUM("Route", spk_xsp_क्रमागत);

अटल स्थिर काष्ठा soc_क्रमागत esl_asp_क्रमागत =
	SOC_VALUE_ENUM_SINGLE(CS42L73_MMIXCTL, 2, 3,
			      ARRAY_SIZE(cs42l73_mono_mix_texts),
			      cs42l73_mono_mix_texts,
			      cs42l73_mono_mix_values);

अटल स्थिर काष्ठा snd_kcontrol_new esl_asp_mixer =
	SOC_DAPM_ENUM("Route", esl_asp_क्रमागत);

अटल स्थिर काष्ठा soc_क्रमागत esl_xsp_क्रमागत =
	SOC_VALUE_ENUM_SINGLE(CS42L73_MMIXCTL, 0, 3,
			      ARRAY_SIZE(cs42l73_mono_mix_texts),
			      cs42l73_mono_mix_texts,
			      cs42l73_mono_mix_values);

अटल स्थिर काष्ठा snd_kcontrol_new esl_xsp_mixer =
	SOC_DAPM_ENUM("Route", esl_xsp_क्रमागत);

अटल स्थिर अक्षर * स्थिर cs42l73_ip_swap_text[] = अणु
	"Stereo", "Mono A", "Mono B", "Swap A-B"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(ip_swap_क्रमागत,
			    CS42L73_MIOPC, 6,
			    cs42l73_ip_swap_text);

अटल स्थिर अक्षर * स्थिर cs42l73_spo_mixer_text[] = अणु"Mono", "Stereo"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(vsp_output_mux_क्रमागत,
			    CS42L73_MIXERCTL, 5,
			    cs42l73_spo_mixer_text);

अटल SOC_ENUM_SINGLE_DECL(xsp_output_mux_क्रमागत,
			    CS42L73_MIXERCTL, 4,
			    cs42l73_spo_mixer_text);

अटल स्थिर काष्ठा snd_kcontrol_new hp_amp_ctl =
	SOC_DAPM_SINGLE("Switch", CS42L73_PWRCTL3, 0, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new lo_amp_ctl =
	SOC_DAPM_SINGLE("Switch", CS42L73_PWRCTL3, 1, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new spk_amp_ctl =
	SOC_DAPM_SINGLE("Switch", CS42L73_PWRCTL3, 2, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new spklo_amp_ctl =
	SOC_DAPM_SINGLE("Switch", CS42L73_PWRCTL3, 4, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new ear_amp_ctl =
	SOC_DAPM_SINGLE("Switch", CS42L73_PWRCTL3, 3, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new cs42l73_snd_controls[] = अणु
	SOC_DOUBLE_R_SX_TLV("Headphone Analog Playback Volume",
			CS42L73_HPAAVOL, CS42L73_HPBAVOL, 0,
			0x41, 0x4B, hpaloa_tlv),

	SOC_DOUBLE_R_SX_TLV("LineOut Analog Playback Volume", CS42L73_LOAAVOL,
			CS42L73_LOBAVOL, 0, 0x41, 0x4B, hpaloa_tlv),

	SOC_DOUBLE_R_SX_TLV("Input PGA Analog Volume", CS42L73_MICAPREPGAAVOL,
			CS42L73_MICBPREPGABVOL, 0, 0x34,
			0x24, micpga_tlv),

	SOC_DOUBLE_R("MIC Preamp Switch", CS42L73_MICAPREPGAAVOL,
			CS42L73_MICBPREPGABVOL, 6, 1, 1),

	SOC_DOUBLE_R_SX_TLV("Input Path Digital Volume", CS42L73_IPADVOL,
			CS42L73_IPBDVOL, 0, 0xA0, 0x6C, ipd_tlv),

	SOC_DOUBLE_R_SX_TLV("HL Digital Playback Volume",
			CS42L73_HLADVOL, CS42L73_HLBDVOL,
			0, 0x34, 0xE4, hl_tlv),

	SOC_SINGLE_TLV("ADC A Boost Volume",
			CS42L73_ADCIPC, 2, 0x01, 1, adc_boost_tlv),

	SOC_SINGLE_TLV("ADC B Boost Volume",
		       CS42L73_ADCIPC, 6, 0x01, 1, adc_boost_tlv),

	SOC_SINGLE_SX_TLV("Speakerphone Digital Volume",
			    CS42L73_SPKDVOL, 0, 0x34, 0xE4, hl_tlv),

	SOC_SINGLE_SX_TLV("Ear Speaker Digital Volume",
			    CS42L73_ESLDVOL, 0, 0x34, 0xE4, hl_tlv),

	SOC_DOUBLE_R("Headphone Analog Playback Switch", CS42L73_HPAAVOL,
			CS42L73_HPBAVOL, 7, 1, 1),

	SOC_DOUBLE_R("LineOut Analog Playback Switch", CS42L73_LOAAVOL,
			CS42L73_LOBAVOL, 7, 1, 1),
	SOC_DOUBLE("Input Path Digital Switch", CS42L73_ADCIPC, 0, 4, 1, 1),
	SOC_DOUBLE("HL Digital Playback Switch", CS42L73_PBDC, 0,
			1, 1, 1),
	SOC_SINGLE("Speakerphone Digital Playback Switch", CS42L73_PBDC, 2, 1,
			1),
	SOC_SINGLE("Ear Speaker Digital Playback Switch", CS42L73_PBDC, 3, 1,
			1),

	SOC_SINGLE("PGA Soft-Ramp Switch", CS42L73_MIOPC, 3, 1, 0),
	SOC_SINGLE("Analog Zero Cross Switch", CS42L73_MIOPC, 2, 1, 0),
	SOC_SINGLE("Digital Soft-Ramp Switch", CS42L73_MIOPC, 1, 1, 0),
	SOC_SINGLE("Analog Output Soft-Ramp Switch", CS42L73_MIOPC, 0, 1, 0),

	SOC_DOUBLE("ADC Signal Polarity Switch", CS42L73_ADCIPC, 1, 5, 1,
			0),

	SOC_SINGLE("HL Limiter Attack Rate", CS42L73_LIMARATEHL, 0, 0x3F,
			0),
	SOC_SINGLE("HL Limiter Release Rate", CS42L73_LIMRRATEHL, 0,
			0x3F, 0),


	SOC_SINGLE("HL Limiter Switch", CS42L73_LIMRRATEHL, 7, 1, 0),
	SOC_SINGLE("HL Limiter All Channels Switch", CS42L73_LIMRRATEHL, 6, 1,
			0),

	SOC_SINGLE_TLV("HL Limiter Max Threshold Volume", CS42L73_LMAXHL, 5, 7,
			1, limiter_tlv),

	SOC_SINGLE_TLV("HL Limiter Cushion Volume", CS42L73_LMAXHL, 2, 7, 1,
			limiter_tlv),

	SOC_SINGLE("SPK Limiter Attack Rate Volume", CS42L73_LIMARATESPK, 0,
			0x3F, 0),
	SOC_SINGLE("SPK Limiter Release Rate Volume", CS42L73_LIMRRATESPK, 0,
			0x3F, 0),
	SOC_SINGLE("SPK Limiter Switch", CS42L73_LIMRRATESPK, 7, 1, 0),
	SOC_SINGLE("SPK Limiter All Channels Switch", CS42L73_LIMRRATESPK,
			6, 1, 0),
	SOC_SINGLE_TLV("SPK Limiter Max Threshold Volume", CS42L73_LMAXSPK, 5,
			7, 1, limiter_tlv),

	SOC_SINGLE_TLV("SPK Limiter Cushion Volume", CS42L73_LMAXSPK, 2, 7, 1,
			limiter_tlv),

	SOC_SINGLE("ESL Limiter Attack Rate Volume", CS42L73_LIMARATEESL, 0,
			0x3F, 0),
	SOC_SINGLE("ESL Limiter Release Rate Volume", CS42L73_LIMRRATEESL, 0,
			0x3F, 0),
	SOC_SINGLE("ESL Limiter Switch", CS42L73_LIMRRATEESL, 7, 1, 0),
	SOC_SINGLE_TLV("ESL Limiter Max Threshold Volume", CS42L73_LMAXESL, 5,
			7, 1, limiter_tlv),

	SOC_SINGLE_TLV("ESL Limiter Cushion Volume", CS42L73_LMAXESL, 2, 7, 1,
			limiter_tlv),

	SOC_SINGLE("ALC Attack Rate Volume", CS42L73_ALCARATE, 0, 0x3F, 0),
	SOC_SINGLE("ALC Release Rate Volume", CS42L73_ALCRRATE, 0, 0x3F, 0),
	SOC_DOUBLE("ALC Switch", CS42L73_ALCARATE, 6, 7, 1, 0),
	SOC_SINGLE_TLV("ALC Max Threshold Volume", CS42L73_ALCMINMAX, 5, 7, 0,
			limiter_tlv),
	SOC_SINGLE_TLV("ALC Min Threshold Volume", CS42L73_ALCMINMAX, 2, 7, 0,
			limiter_tlv),

	SOC_DOUBLE("NG Enable Switch", CS42L73_NGCAB, 6, 7, 1, 0),
	SOC_SINGLE("NG Boost Switch", CS42L73_NGCAB, 5, 1, 0),
	/*
	    NG Threshold depends on NG_BOOTSAB, which selects
	    between two threshold scales in decibels.
	    Set linear values क्रम now ..
	*/
	SOC_SINGLE("NG Threshold", CS42L73_NGCAB, 2, 7, 0),
	SOC_ENUM("NG Delay", ng_delay_क्रमागत),

	SOC_DOUBLE_R_TLV("XSP-IP Volume",
			CS42L73_XSPAIPAA, CS42L73_XSPBIPBA, 0, 0x3F, 1,
			attn_tlv),
	SOC_DOUBLE_R_TLV("XSP-XSP Volume",
			CS42L73_XSPAXSPAA, CS42L73_XSPBXSPBA, 0, 0x3F, 1,
			attn_tlv),
	SOC_DOUBLE_R_TLV("XSP-ASP Volume",
			CS42L73_XSPAASPAA, CS42L73_XSPAASPBA, 0, 0x3F, 1,
			attn_tlv),
	SOC_DOUBLE_R_TLV("XSP-VSP Volume",
			CS42L73_XSPAVSPMA, CS42L73_XSPBVSPMA, 0, 0x3F, 1,
			attn_tlv),

	SOC_DOUBLE_R_TLV("ASP-IP Volume",
			CS42L73_ASPAIPAA, CS42L73_ASPBIPBA, 0, 0x3F, 1,
			attn_tlv),
	SOC_DOUBLE_R_TLV("ASP-XSP Volume",
			CS42L73_ASPAXSPAA, CS42L73_ASPBXSPBA, 0, 0x3F, 1,
			attn_tlv),
	SOC_DOUBLE_R_TLV("ASP-ASP Volume",
			CS42L73_ASPAASPAA, CS42L73_ASPBASPBA, 0, 0x3F, 1,
			attn_tlv),
	SOC_DOUBLE_R_TLV("ASP-VSP Volume",
			CS42L73_ASPAVSPMA, CS42L73_ASPBVSPMA, 0, 0x3F, 1,
			attn_tlv),

	SOC_DOUBLE_R_TLV("VSP-IP Volume",
			CS42L73_VSPAIPAA, CS42L73_VSPBIPBA, 0, 0x3F, 1,
			attn_tlv),
	SOC_DOUBLE_R_TLV("VSP-XSP Volume",
			CS42L73_VSPAXSPAA, CS42L73_VSPBXSPBA, 0, 0x3F, 1,
			attn_tlv),
	SOC_DOUBLE_R_TLV("VSP-ASP Volume",
			CS42L73_VSPAASPAA, CS42L73_VSPBASPBA, 0, 0x3F, 1,
			attn_tlv),
	SOC_DOUBLE_R_TLV("VSP-VSP Volume",
			CS42L73_VSPAVSPMA, CS42L73_VSPBVSPMA, 0, 0x3F, 1,
			attn_tlv),

	SOC_DOUBLE_R_TLV("HL-IP Volume",
			CS42L73_HLAIPAA, CS42L73_HLBIPBA, 0, 0x3F, 1,
			attn_tlv),
	SOC_DOUBLE_R_TLV("HL-XSP Volume",
			CS42L73_HLAXSPAA, CS42L73_HLBXSPBA, 0, 0x3F, 1,
			attn_tlv),
	SOC_DOUBLE_R_TLV("HL-ASP Volume",
			CS42L73_HLAASPAA, CS42L73_HLBASPBA, 0, 0x3F, 1,
			attn_tlv),
	SOC_DOUBLE_R_TLV("HL-VSP Volume",
			CS42L73_HLAVSPMA, CS42L73_HLBVSPMA, 0, 0x3F, 1,
			attn_tlv),

	SOC_SINGLE_TLV("SPK-IP Mono Volume",
			CS42L73_SPKMIPMA, 0, 0x3F, 1, attn_tlv),
	SOC_SINGLE_TLV("SPK-XSP Mono Volume",
			CS42L73_SPKMXSPA, 0, 0x3F, 1, attn_tlv),
	SOC_SINGLE_TLV("SPK-ASP Mono Volume",
			CS42L73_SPKMASPA, 0, 0x3F, 1, attn_tlv),
	SOC_SINGLE_TLV("SPK-VSP Mono Volume",
			CS42L73_SPKMVSPMA, 0, 0x3F, 1, attn_tlv),

	SOC_SINGLE_TLV("ESL-IP Mono Volume",
			CS42L73_ESLMIPMA, 0, 0x3F, 1, attn_tlv),
	SOC_SINGLE_TLV("ESL-XSP Mono Volume",
			CS42L73_ESLMXSPA, 0, 0x3F, 1, attn_tlv),
	SOC_SINGLE_TLV("ESL-ASP Mono Volume",
			CS42L73_ESLMASPA, 0, 0x3F, 1, attn_tlv),
	SOC_SINGLE_TLV("ESL-VSP Mono Volume",
			CS42L73_ESLMVSPMA, 0, 0x3F, 1, attn_tlv),

	SOC_ENUM("IP Digital Swap/Mono Select", ip_swap_क्रमागत),

	SOC_ENUM("VSPOUT Mono/Stereo Select", vsp_output_mux_क्रमागत),
	SOC_ENUM("XSPOUT Mono/Stereo Select", xsp_output_mux_क्रमागत),
पूर्ण;

अटल पूर्णांक cs42l73_spklo_spk_amp_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs42l73_निजी *priv = snd_soc_component_get_drvdata(component);
	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMD:
		/* 150 ms delay between setting PDN and MCLKDIS */
		priv->shutdwn_delay = 150;
		अवरोध;
	शेष:
		pr_err("Invalid event = 0x%x\n", event);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cs42l73_ear_amp_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs42l73_निजी *priv = snd_soc_component_get_drvdata(component);
	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMD:
		/* 50 ms delay between setting PDN and MCLKDIS */
		अगर (priv->shutdwn_delay < 50)
			priv->shutdwn_delay = 50;
		अवरोध;
	शेष:
		pr_err("Invalid event = 0x%x\n", event);
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक cs42l73_hp_amp_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs42l73_निजी *priv = snd_soc_component_get_drvdata(component);
	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMD:
		/* 30 ms delay between setting PDN and MCLKDIS */
		अगर (priv->shutdwn_delay < 30)
			priv->shutdwn_delay = 30;
		अवरोध;
	शेष:
		pr_err("Invalid event = 0x%x\n", event);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget cs42l73_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("DMICA"),
	SND_SOC_DAPM_INPUT("DMICB"),
	SND_SOC_DAPM_INPUT("LINEINA"),
	SND_SOC_DAPM_INPUT("LINEINB"),
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_SUPPLY("MIC1 Bias", CS42L73_PWRCTL2, 6, 1, शून्य, 0),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_SUPPLY("MIC2 Bias", CS42L73_PWRCTL2, 7, 1, शून्य, 0),

	SND_SOC_DAPM_AIF_OUT("XSPOUTL", शून्य,  0,
			CS42L73_PWRCTL2, 1, 1),
	SND_SOC_DAPM_AIF_OUT("XSPOUTR", शून्य,  0,
			CS42L73_PWRCTL2, 1, 1),
	SND_SOC_DAPM_AIF_OUT("ASPOUTL", शून्य,  0,
			CS42L73_PWRCTL2, 3, 1),
	SND_SOC_DAPM_AIF_OUT("ASPOUTR", शून्य,  0,
			CS42L73_PWRCTL2, 3, 1),
	SND_SOC_DAPM_AIF_OUT("VSPINOUT", शून्य,  0,
			CS42L73_PWRCTL2, 4, 1),

	SND_SOC_DAPM_PGA("PGA Left", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PGA Right", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("PGA Left Mux", SND_SOC_NOPM, 0, 0, &pgaa_mux),
	SND_SOC_DAPM_MUX("PGA Right Mux", SND_SOC_NOPM, 0, 0, &pgab_mux),

	SND_SOC_DAPM_ADC("ADC Left", शून्य, CS42L73_PWRCTL1, 7, 1),
	SND_SOC_DAPM_ADC("ADC Right", शून्य, CS42L73_PWRCTL1, 5, 1),
	SND_SOC_DAPM_ADC("DMIC Left", शून्य, CS42L73_PWRCTL1, 6, 1),
	SND_SOC_DAPM_ADC("DMIC Right", शून्य, CS42L73_PWRCTL1, 4, 1),

	SND_SOC_DAPM_MIXER_NAMED_CTL("Input Left Capture", SND_SOC_NOPM,
			 0, 0, input_left_mixer,
			 ARRAY_SIZE(input_left_mixer)),

	SND_SOC_DAPM_MIXER_NAMED_CTL("Input Right Capture", SND_SOC_NOPM,
			0, 0, input_right_mixer,
			ARRAY_SIZE(input_right_mixer)),

	SND_SOC_DAPM_MIXER("ASPL Output Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("ASPR Output Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("XSPL Output Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("XSPR Output Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("VSP Output Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_AIF_IN("XSPINL", शून्य, 0,
				CS42L73_PWRCTL2, 0, 1),
	SND_SOC_DAPM_AIF_IN("XSPINR", शून्य, 0,
				CS42L73_PWRCTL2, 0, 1),
	SND_SOC_DAPM_AIF_IN("XSPINM", शून्य, 0,
				CS42L73_PWRCTL2, 0, 1),

	SND_SOC_DAPM_AIF_IN("ASPINL", शून्य, 0,
				CS42L73_PWRCTL2, 2, 1),
	SND_SOC_DAPM_AIF_IN("ASPINR", शून्य, 0,
				CS42L73_PWRCTL2, 2, 1),
	SND_SOC_DAPM_AIF_IN("ASPINM", शून्य, 0,
				CS42L73_PWRCTL2, 2, 1),

	SND_SOC_DAPM_AIF_IN("VSPINOUT", शून्य, 0,
				CS42L73_PWRCTL2, 4, 1),

	SND_SOC_DAPM_MIXER("HL Left Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("HL Right Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SPK Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("ESL Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("ESL-XSP Mux", SND_SOC_NOPM,
			 0, 0, &esl_xsp_mixer),

	SND_SOC_DAPM_MUX("ESL-ASP Mux", SND_SOC_NOPM,
			 0, 0, &esl_asp_mixer),

	SND_SOC_DAPM_MUX("SPK-ASP Mux", SND_SOC_NOPM,
			 0, 0, &spk_asp_mixer),

	SND_SOC_DAPM_MUX("SPK-XSP Mux", SND_SOC_NOPM,
			 0, 0, &spk_xsp_mixer),

	SND_SOC_DAPM_PGA("HL Left DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HL Right DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SPK DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("ESL DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SWITCH_E("HP Amp",  CS42L73_PWRCTL3, 0, 1,
			    &hp_amp_ctl, cs42l73_hp_amp_event,
			SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SWITCH("LO Amp", CS42L73_PWRCTL3, 1, 1,
			    &lo_amp_ctl),
	SND_SOC_DAPM_SWITCH_E("SPK Amp", CS42L73_PWRCTL3, 2, 1,
			&spk_amp_ctl, cs42l73_spklo_spk_amp_event,
			SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SWITCH_E("EAR Amp", CS42L73_PWRCTL3, 3, 1,
			    &ear_amp_ctl, cs42l73_ear_amp_event,
			SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SWITCH_E("SPKLO Amp", CS42L73_PWRCTL3, 4, 1,
			    &spklo_amp_ctl, cs42l73_spklo_spk_amp_event,
			SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_OUTPUT("HPOUTA"),
	SND_SOC_DAPM_OUTPUT("HPOUTB"),
	SND_SOC_DAPM_OUTPUT("LINEOUTA"),
	SND_SOC_DAPM_OUTPUT("LINEOUTB"),
	SND_SOC_DAPM_OUTPUT("EAROUT"),
	SND_SOC_DAPM_OUTPUT("SPKOUT"),
	SND_SOC_DAPM_OUTPUT("SPKLINEOUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs42l73_audio_map[] = अणु

	/* SPKLO EARSPK Paths */
	अणु"EAROUT", शून्य, "EAR Amp"पूर्ण,
	अणु"SPKLINEOUT", शून्य, "SPKLO Amp"पूर्ण,

	अणु"EAR Amp", "Switch", "ESL DAC"पूर्ण,
	अणु"SPKLO Amp", "Switch", "ESL DAC"पूर्ण,

	अणु"ESL DAC", "ESL-ASP Mono Volume", "ESL Mixer"पूर्ण,
	अणु"ESL DAC", "ESL-XSP Mono Volume", "ESL Mixer"पूर्ण,
	अणु"ESL DAC", "ESL-VSP Mono Volume", "VSPINOUT"पूर्ण,
	/* Loopback */
	अणु"ESL DAC", "ESL-IP Mono Volume", "Input Left Capture"पूर्ण,
	अणु"ESL DAC", "ESL-IP Mono Volume", "Input Right Capture"पूर्ण,

	अणु"ESL Mixer", शून्य, "ESL-ASP Mux"पूर्ण,
	अणु"ESL Mixer", शून्य, "ESL-XSP Mux"पूर्ण,

	अणु"ESL-ASP Mux", "Left", "ASPINL"पूर्ण,
	अणु"ESL-ASP Mux", "Right", "ASPINR"पूर्ण,
	अणु"ESL-ASP Mux", "Mono Mix", "ASPINM"पूर्ण,

	अणु"ESL-XSP Mux", "Left", "XSPINL"पूर्ण,
	अणु"ESL-XSP Mux", "Right", "XSPINR"पूर्ण,
	अणु"ESL-XSP Mux", "Mono Mix", "XSPINM"पूर्ण,

	/* Speakerphone Paths */
	अणु"SPKOUT", शून्य, "SPK Amp"पूर्ण,
	अणु"SPK Amp", "Switch", "SPK DAC"पूर्ण,

	अणु"SPK DAC", "SPK-ASP Mono Volume", "SPK Mixer"पूर्ण,
	अणु"SPK DAC", "SPK-XSP Mono Volume", "SPK Mixer"पूर्ण,
	अणु"SPK DAC", "SPK-VSP Mono Volume", "VSPINOUT"पूर्ण,
	/* Loopback */
	अणु"SPK DAC", "SPK-IP Mono Volume", "Input Left Capture"पूर्ण,
	अणु"SPK DAC", "SPK-IP Mono Volume", "Input Right Capture"पूर्ण,

	अणु"SPK Mixer", शून्य, "SPK-ASP Mux"पूर्ण,
	अणु"SPK Mixer", शून्य, "SPK-XSP Mux"पूर्ण,

	अणु"SPK-ASP Mux", "Left", "ASPINL"पूर्ण,
	अणु"SPK-ASP Mux", "Mono Mix", "ASPINM"पूर्ण,
	अणु"SPK-ASP Mux", "Right", "ASPINR"पूर्ण,

	अणु"SPK-XSP Mux", "Left", "XSPINL"पूर्ण,
	अणु"SPK-XSP Mux", "Mono Mix", "XSPINM"पूर्ण,
	अणु"SPK-XSP Mux", "Right", "XSPINR"पूर्ण,

	/* HP LineOUT Paths */
	अणु"HPOUTA", शून्य, "HP Amp"पूर्ण,
	अणु"HPOUTB", शून्य, "HP Amp"पूर्ण,
	अणु"LINEOUTA", शून्य, "LO Amp"पूर्ण,
	अणु"LINEOUTB", शून्य, "LO Amp"पूर्ण,

	अणु"HP Amp", "Switch", "HL Left DAC"पूर्ण,
	अणु"HP Amp", "Switch", "HL Right DAC"पूर्ण,
	अणु"LO Amp", "Switch", "HL Left DAC"पूर्ण,
	अणु"LO Amp", "Switch", "HL Right DAC"पूर्ण,

	अणु"HL Left DAC", "HL-XSP Volume", "HL Left Mixer"पूर्ण,
	अणु"HL Right DAC", "HL-XSP Volume", "HL Right Mixer"पूर्ण,
	अणु"HL Left DAC", "HL-ASP Volume", "HL Left Mixer"पूर्ण,
	अणु"HL Right DAC", "HL-ASP Volume", "HL Right Mixer"पूर्ण,
	अणु"HL Left DAC", "HL-VSP Volume", "HL Left Mixer"पूर्ण,
	अणु"HL Right DAC", "HL-VSP Volume", "HL Right Mixer"पूर्ण,
	/* Loopback */
	अणु"HL Left DAC", "HL-IP Volume", "HL Left Mixer"पूर्ण,
	अणु"HL Right DAC", "HL-IP Volume", "HL Right Mixer"पूर्ण,
	अणु"HL Left Mixer", शून्य, "Input Left Capture"पूर्ण,
	अणु"HL Right Mixer", शून्य, "Input Right Capture"पूर्ण,

	अणु"HL Left Mixer", शून्य, "ASPINL"पूर्ण,
	अणु"HL Right Mixer", शून्य, "ASPINR"पूर्ण,
	अणु"HL Left Mixer", शून्य, "XSPINL"पूर्ण,
	अणु"HL Right Mixer", शून्य, "XSPINR"पूर्ण,
	अणु"HL Left Mixer", शून्य, "VSPINOUT"पूर्ण,
	अणु"HL Right Mixer", शून्य, "VSPINOUT"पूर्ण,

	अणु"ASPINL", शून्य, "ASP Playback"पूर्ण,
	अणु"ASPINM", शून्य, "ASP Playback"पूर्ण,
	अणु"ASPINR", शून्य, "ASP Playback"पूर्ण,
	अणु"XSPINL", शून्य, "XSP Playback"पूर्ण,
	अणु"XSPINM", शून्य, "XSP Playback"पूर्ण,
	अणु"XSPINR", शून्य, "XSP Playback"पूर्ण,
	अणु"VSPINOUT", शून्य, "VSP Playback"पूर्ण,

	/* Capture Paths */
	अणु"MIC1", शून्य, "MIC1 Bias"पूर्ण,
	अणु"PGA Left Mux", "Mic 1", "MIC1"पूर्ण,
	अणु"MIC2", शून्य, "MIC2 Bias"पूर्ण,
	अणु"PGA Right Mux", "Mic 2", "MIC2"पूर्ण,

	अणु"PGA Left Mux", "Line A", "LINEINA"पूर्ण,
	अणु"PGA Right Mux", "Line B", "LINEINB"पूर्ण,

	अणु"PGA Left", शून्य, "PGA Left Mux"पूर्ण,
	अणु"PGA Right", शून्य, "PGA Right Mux"पूर्ण,

	अणु"ADC Left", शून्य, "PGA Left"पूर्ण,
	अणु"ADC Right", शून्य, "PGA Right"पूर्ण,
	अणु"DMIC Left", शून्य, "DMICA"पूर्ण,
	अणु"DMIC Right", शून्य, "DMICB"पूर्ण,

	अणु"Input Left Capture", "ADC Left Input", "ADC Left"पूर्ण,
	अणु"Input Right Capture", "ADC Right Input", "ADC Right"पूर्ण,
	अणु"Input Left Capture", "DMIC Left Input", "DMIC Left"पूर्ण,
	अणु"Input Right Capture", "DMIC Right Input", "DMIC Right"पूर्ण,

	/* Audio Capture */
	अणु"ASPL Output Mixer", शून्य, "Input Left Capture"पूर्ण,
	अणु"ASPR Output Mixer", शून्य, "Input Right Capture"पूर्ण,

	अणु"ASPOUTL", "ASP-IP Volume", "ASPL Output Mixer"पूर्ण,
	अणु"ASPOUTR", "ASP-IP Volume", "ASPR Output Mixer"पूर्ण,

	/* Auxillary Capture */
	अणु"XSPL Output Mixer", शून्य, "Input Left Capture"पूर्ण,
	अणु"XSPR Output Mixer", शून्य, "Input Right Capture"पूर्ण,

	अणु"XSPOUTL", "XSP-IP Volume", "XSPL Output Mixer"पूर्ण,
	अणु"XSPOUTR", "XSP-IP Volume", "XSPR Output Mixer"पूर्ण,

	अणु"XSPOUTL", शून्य, "XSPL Output Mixer"पूर्ण,
	अणु"XSPOUTR", शून्य, "XSPR Output Mixer"पूर्ण,

	/* Voice Capture */
	अणु"VSP Output Mixer", शून्य, "Input Left Capture"पूर्ण,
	अणु"VSP Output Mixer", शून्य, "Input Right Capture"पूर्ण,

	अणु"VSPINOUT", "VSP-IP Volume", "VSP Output Mixer"पूर्ण,

	अणु"VSPINOUT", शून्य, "VSP Output Mixer"पूर्ण,

	अणु"ASP Capture", शून्य, "ASPOUTL"पूर्ण,
	अणु"ASP Capture", शून्य, "ASPOUTR"पूर्ण,
	अणु"XSP Capture", शून्य, "XSPOUTL"पूर्ण,
	अणु"XSP Capture", शून्य, "XSPOUTR"पूर्ण,
	अणु"VSP Capture", शून्य, "VSPINOUT"पूर्ण,
पूर्ण;

काष्ठा cs42l73_mclk_भाग अणु
	u32 mclk;
	u32 srate;
	u8 mmcc;
पूर्ण;

अटल स्थिर काष्ठा cs42l73_mclk_भाग cs42l73_mclk_coeffs[] = अणु
	/* MCLK, Sample Rate, xMMCC[5:0] */
	अणु5644800, 11025, 0x30पूर्ण,
	अणु5644800, 22050, 0x20पूर्ण,
	अणु5644800, 44100, 0x10पूर्ण,

	अणु6000000,  8000, 0x39पूर्ण,
	अणु6000000, 11025, 0x33पूर्ण,
	अणु6000000, 12000, 0x31पूर्ण,
	अणु6000000, 16000, 0x29पूर्ण,
	अणु6000000, 22050, 0x23पूर्ण,
	अणु6000000, 24000, 0x21पूर्ण,
	अणु6000000, 32000, 0x19पूर्ण,
	अणु6000000, 44100, 0x13पूर्ण,
	अणु6000000, 48000, 0x11पूर्ण,

	अणु6144000,  8000, 0x38पूर्ण,
	अणु6144000, 12000, 0x30पूर्ण,
	अणु6144000, 16000, 0x28पूर्ण,
	अणु6144000, 24000, 0x20पूर्ण,
	अणु6144000, 32000, 0x18पूर्ण,
	अणु6144000, 48000, 0x10पूर्ण,

	अणु6500000,  8000, 0x3Cपूर्ण,
	अणु6500000, 11025, 0x35पूर्ण,
	अणु6500000, 12000, 0x34पूर्ण,
	अणु6500000, 16000, 0x2Cपूर्ण,
	अणु6500000, 22050, 0x25पूर्ण,
	अणु6500000, 24000, 0x24पूर्ण,
	अणु6500000, 32000, 0x1Cपूर्ण,
	अणु6500000, 44100, 0x15पूर्ण,
	अणु6500000, 48000, 0x14पूर्ण,

	अणु6400000,  8000, 0x3Eपूर्ण,
	अणु6400000, 11025, 0x37पूर्ण,
	अणु6400000, 12000, 0x36पूर्ण,
	अणु6400000, 16000, 0x2Eपूर्ण,
	अणु6400000, 22050, 0x27पूर्ण,
	अणु6400000, 24000, 0x26पूर्ण,
	अणु6400000, 32000, 0x1Eपूर्ण,
	अणु6400000, 44100, 0x17पूर्ण,
	अणु6400000, 48000, 0x16पूर्ण,
पूर्ण;

काष्ठा cs42l73_mclkx_भाग अणु
	u32 mclkx;
	u8 ratio;
	u8 mclkभाग;
पूर्ण;

अटल स्थिर काष्ठा cs42l73_mclkx_भाग cs42l73_mclkx_coeffs[] = अणु
	अणु5644800,  1, 0पूर्ण,	/* 5644800 */
	अणु6000000,  1, 0पूर्ण,	/* 6000000 */
	अणु6144000,  1, 0पूर्ण,	/* 6144000 */
	अणु11289600, 2, 2पूर्ण,	/* 5644800 */
	अणु12288000, 2, 2पूर्ण,	/* 6144000 */
	अणु12000000, 2, 2पूर्ण,	/* 6000000 */
	अणु13000000, 2, 2पूर्ण,	/* 6500000 */
	अणु19200000, 3, 3पूर्ण,	/* 6400000 */
	अणु24000000, 4, 4पूर्ण,	/* 6000000 */
	अणु26000000, 4, 4पूर्ण,	/* 6500000 */
	अणु38400000, 6, 5पूर्ण	/* 6400000 */
पूर्ण;

अटल पूर्णांक cs42l73_get_mclkx_coeff(पूर्णांक mclkx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cs42l73_mclkx_coeffs); i++) अणु
		अगर (cs42l73_mclkx_coeffs[i].mclkx == mclkx)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cs42l73_get_mclk_coeff(पूर्णांक mclk, पूर्णांक srate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cs42l73_mclk_coeffs); i++) अणु
		अगर (cs42l73_mclk_coeffs[i].mclk == mclk &&
		    cs42l73_mclk_coeffs[i].srate == srate)
			वापस i;
	पूर्ण
	वापस -EINVAL;

पूर्ण

अटल पूर्णांक cs42l73_set_mclk(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs42l73_निजी *priv = snd_soc_component_get_drvdata(component);

	पूर्णांक mclkx_coeff;
	u32 mclk = 0;
	u8 dmmcc = 0;

	/* MCLKX -> MCLK */
	mclkx_coeff = cs42l73_get_mclkx_coeff(freq);
	अगर (mclkx_coeff < 0)
		वापस mclkx_coeff;

	mclk = cs42l73_mclkx_coeffs[mclkx_coeff].mclkx /
		cs42l73_mclkx_coeffs[mclkx_coeff].ratio;

	dev_dbg(component->dev, "MCLK%u %u  <-> internal MCLK %u\n",
		 priv->mclksel + 1, cs42l73_mclkx_coeffs[mclkx_coeff].mclkx,
		 mclk);

	dmmcc = (priv->mclksel << 4) |
		(cs42l73_mclkx_coeffs[mclkx_coeff].mclkभाग << 1);

	snd_soc_component_ग_लिखो(component, CS42L73_DMMCC, dmmcc);

	priv->sysclk = mclkx_coeff;
	priv->mclk = mclk;

	वापस 0;
पूर्ण

अटल पूर्णांक cs42l73_set_sysclk(काष्ठा snd_soc_dai *dai,
			      पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs42l73_निजी *priv = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल CS42L73_CLKID_MCLK1:
		अवरोध;
	हाल CS42L73_CLKID_MCLK2:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((cs42l73_set_mclk(dai, freq)) < 0) अणु
		dev_err(component->dev, "Unable to set MCLK for dai %s\n",
			dai->name);
		वापस -EINVAL;
	पूर्ण

	priv->mclksel = clk_id;

	वापस 0;
पूर्ण

अटल पूर्णांक cs42l73_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs42l73_निजी *priv = snd_soc_component_get_drvdata(component);
	u8 id = codec_dai->id;
	अचिन्हित पूर्णांक inv, क्रमmat;
	u8 spc, mmcc;

	spc = snd_soc_component_पढ़ो(component, CS42L73_SPC(id));
	mmcc = snd_soc_component_पढ़ो(component, CS42L73_MMCC(id));

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		mmcc |= CS42L73_MS_MASTER;
		अवरोध;

	हाल SND_SOC_DAIFMT_CBS_CFS:
		mmcc &= ~CS42L73_MS_MASTER;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रमmat = (fmt & SND_SOC_DAIFMT_FORMAT_MASK);
	inv = (fmt & SND_SOC_DAIFMT_INV_MASK);

	चयन (क्रमmat) अणु
	हाल SND_SOC_DAIFMT_I2S:
		spc &= ~CS42L73_SPDIF_PCM;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		अगर (mmcc & CS42L73_MS_MASTER) अणु
			dev_err(component->dev,
				"PCM format in slave mode only\n");
			वापस -EINVAL;
		पूर्ण
		अगर (id == CS42L73_ASP) अणु
			dev_err(component->dev,
				"PCM format is not supported on ASP port\n");
			वापस -EINVAL;
		पूर्ण
		spc |= CS42L73_SPDIF_PCM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (spc & CS42L73_SPDIF_PCM) अणु
		/* Clear PCM mode, clear PCM_BIT_ORDER bit क्रम MSB->LSB */
		spc &= ~(CS42L73_PCM_MODE_MASK | CS42L73_PCM_BIT_ORDER);
		चयन (क्रमmat) अणु
		हाल SND_SOC_DAIFMT_DSP_B:
			अगर (inv == SND_SOC_DAIFMT_IB_IF)
				spc |= CS42L73_PCM_MODE0;
			अगर (inv == SND_SOC_DAIFMT_IB_NF)
				spc |= CS42L73_PCM_MODE1;
		अवरोध;
		हाल SND_SOC_DAIFMT_DSP_A:
			अगर (inv == SND_SOC_DAIFMT_IB_IF)
				spc |= CS42L73_PCM_MODE1;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	priv->config[id].spc = spc;
	priv->config[id].mmcc = mmcc;

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक cs42l73_asrc_rates[] = अणु
	8000, 11025, 12000, 16000, 22050,
	24000, 32000, 44100, 48000
पूर्ण;

अटल अचिन्हित पूर्णांक cs42l73_get_xspfs_coeff(u32 rate)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(cs42l73_asrc_rates); i++) अणु
		अगर (cs42l73_asrc_rates[i] == rate)
			वापस i + 1;
	पूर्ण
	वापस 0;		/* 0 = Don't know */
पूर्ण

अटल व्योम cs42l73_update_asrc(काष्ठा snd_soc_component *component, पूर्णांक id, पूर्णांक srate)
अणु
	u8 spfs = 0;

	अगर (srate > 0)
		spfs = cs42l73_get_xspfs_coeff(srate);

	चयन (id) अणु
	हाल CS42L73_XSP:
		snd_soc_component_update_bits(component, CS42L73_VXSPFS, 0x0f, spfs);
	अवरोध;
	हाल CS42L73_ASP:
		snd_soc_component_update_bits(component, CS42L73_ASPC, 0x3c, spfs << 2);
	अवरोध;
	हाल CS42L73_VSP:
		snd_soc_component_update_bits(component, CS42L73_VXSPFS, 0xf0, spfs << 4);
	अवरोध;
	शेष:
	अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक cs42l73_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs42l73_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक id = dai->id;
	पूर्णांक mclk_coeff;
	पूर्णांक srate = params_rate(params);

	अगर (priv->config[id].mmcc & CS42L73_MS_MASTER) अणु
		/* CS42L73 Master */
		/* MCLK -> srate */
		mclk_coeff =
		    cs42l73_get_mclk_coeff(priv->mclk, srate);

		अगर (mclk_coeff < 0)
			वापस -EINVAL;

		dev_dbg(component->dev,
			 "DAI[%d]: MCLK %u, srate %u, MMCC[5:0] = %x\n",
			 id, priv->mclk, srate,
			 cs42l73_mclk_coeffs[mclk_coeff].mmcc);

		priv->config[id].mmcc &= 0xC0;
		priv->config[id].mmcc |= cs42l73_mclk_coeffs[mclk_coeff].mmcc;
		priv->config[id].spc &= 0xFC;
		/* Use SCLK=64*Fs अगर पूर्णांकernal MCLK >= 6.4MHz */
		अगर (priv->mclk >= 6400000)
			priv->config[id].spc |= CS42L73_MCK_SCLK_64FS;
		अन्यथा
			priv->config[id].spc |= CS42L73_MCK_SCLK_MCLK;
	पूर्ण अन्यथा अणु
		/* CS42L73 Slave */
		priv->config[id].spc &= 0xFC;
		priv->config[id].spc |= CS42L73_MCK_SCLK_64FS;
	पूर्ण
	/* Update ASRCs */
	priv->config[id].srate = srate;

	snd_soc_component_ग_लिखो(component, CS42L73_SPC(id), priv->config[id].spc);
	snd_soc_component_ग_लिखो(component, CS42L73_MMCC(id), priv->config[id].mmcc);

	cs42l73_update_asrc(component, id, srate);

	वापस 0;
पूर्ण

अटल पूर्णांक cs42l73_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा cs42l73_निजी *cs42l73 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		snd_soc_component_update_bits(component, CS42L73_DMMCC, CS42L73_MCLKDIS, 0);
		snd_soc_component_update_bits(component, CS42L73_PWRCTL1, CS42L73_PDN, 0);
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			regcache_cache_only(cs42l73->regmap, false);
			regcache_sync(cs42l73->regmap);
		पूर्ण
		snd_soc_component_update_bits(component, CS42L73_PWRCTL1, CS42L73_PDN, 1);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, CS42L73_PWRCTL1, CS42L73_PDN, 1);
		अगर (cs42l73->shutdwn_delay > 0) अणु
			mdelay(cs42l73->shutdwn_delay);
			cs42l73->shutdwn_delay = 0;
		पूर्ण अन्यथा अणु
			mdelay(15); /* Min amount of समय requred to घातer
				     * करोwn.
				     */
		पूर्ण
		snd_soc_component_update_bits(component, CS42L73_DMMCC, CS42L73_MCLKDIS, 1);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cs42l73_set_tristate(काष्ठा snd_soc_dai *dai, पूर्णांक tristate)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक id = dai->id;

	वापस snd_soc_component_update_bits(component, CS42L73_SPC(id), CS42L73_SP_3ST,
				   tristate << 7);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_12_24 = अणु
	.count  = ARRAY_SIZE(cs42l73_asrc_rates),
	.list   = cs42l73_asrc_rates,
पूर्ण;

अटल पूर्णांक cs42l73_pcm_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					SNDRV_PCM_HW_PARAM_RATE,
					&स्थिरraपूर्णांकs_12_24);
	वापस 0;
पूर्ण


#घोषणा CS42L73_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
	SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops cs42l73_ops = अणु
	.startup = cs42l73_pcm_startup,
	.hw_params = cs42l73_pcm_hw_params,
	.set_fmt = cs42l73_set_dai_fmt,
	.set_sysclk = cs42l73_set_sysclk,
	.set_tristate = cs42l73_set_tristate,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs42l73_dai[] = अणु
	अणु
		.name = "cs42l73-xsp",
		.id = CS42L73_XSP,
		.playback = अणु
			.stream_name = "XSP Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = CS42L73_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "XSP Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = CS42L73_FORMATS,
		पूर्ण,
		.ops = &cs42l73_ops,
		.symmetric_rate = 1,
	 पूर्ण,
	अणु
		.name = "cs42l73-asp",
		.id = CS42L73_ASP,
		.playback = अणु
			.stream_name = "ASP Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = CS42L73_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "ASP Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = CS42L73_FORMATS,
		पूर्ण,
		.ops = &cs42l73_ops,
		.symmetric_rate = 1,
	 पूर्ण,
	अणु
		.name = "cs42l73-vsp",
		.id = CS42L73_VSP,
		.playback = अणु
			.stream_name = "VSP Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = CS42L73_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "VSP Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = CS42L73_FORMATS,
		पूर्ण,
		.ops = &cs42l73_ops,
		.symmetric_rate = 1,
	 पूर्ण
पूर्ण;

अटल पूर्णांक cs42l73_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs42l73_निजी *cs42l73 = snd_soc_component_get_drvdata(component);

	/* Set Charge Pump Frequency */
	अगर (cs42l73->pdata.chgfreq)
		snd_soc_component_update_bits(component, CS42L73_CPFCHC,
				    CS42L73_CHARGEPUMP_MASK,
					cs42l73->pdata.chgfreq << 4);

	/* MCLK1 as master clk */
	cs42l73->mclksel = CS42L73_CLKID_MCLK1;
	cs42l73->mclk = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_cs42l73 = अणु
	.probe			= cs42l73_probe,
	.set_bias_level		= cs42l73_set_bias_level,
	.controls		= cs42l73_snd_controls,
	.num_controls		= ARRAY_SIZE(cs42l73_snd_controls),
	.dapm_widमाला_लो		= cs42l73_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs42l73_dapm_widमाला_लो),
	.dapm_routes		= cs42l73_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(cs42l73_audio_map),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cs42l73_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = CS42L73_MAX_REGISTER,
	.reg_शेषs = cs42l73_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(cs42l73_reg_शेषs),
	.अस्थिर_reg = cs42l73_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = cs42l73_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,

	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल पूर्णांक cs42l73_i2c_probe(काष्ठा i2c_client *i2c_client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs42l73_निजी *cs42l73;
	काष्ठा cs42l73_platक्रमm_data *pdata = dev_get_platdata(&i2c_client->dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक devid = 0;
	अचिन्हित पूर्णांक reg;
	u32 val32;

	cs42l73 = devm_kzalloc(&i2c_client->dev, माप(*cs42l73), GFP_KERNEL);
	अगर (!cs42l73)
		वापस -ENOMEM;

	cs42l73->regmap = devm_regmap_init_i2c(i2c_client, &cs42l73_regmap);
	अगर (IS_ERR(cs42l73->regmap)) अणु
		ret = PTR_ERR(cs42l73->regmap);
		dev_err(&i2c_client->dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (pdata) अणु
		cs42l73->pdata = *pdata;
	पूर्ण अन्यथा अणु
		pdata = devm_kzalloc(&i2c_client->dev, माप(*pdata),
				     GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;

		अगर (i2c_client->dev.of_node) अणु
			अगर (of_property_पढ़ो_u32(i2c_client->dev.of_node,
				"chgfreq", &val32) >= 0)
				pdata->chgfreq = val32;
		पूर्ण
		pdata->reset_gpio = of_get_named_gpio(i2c_client->dev.of_node,
						"reset-gpio", 0);
		cs42l73->pdata = *pdata;
	पूर्ण

	i2c_set_clientdata(i2c_client, cs42l73);

	अगर (cs42l73->pdata.reset_gpio) अणु
		ret = devm_gpio_request_one(&i2c_client->dev,
					    cs42l73->pdata.reset_gpio,
					    GPIOF_OUT_INIT_HIGH,
					    "CS42L73 /RST");
		अगर (ret < 0) अणु
			dev_err(&i2c_client->dev, "Failed to request /RST %d: %d\n",
				cs42l73->pdata.reset_gpio, ret);
			वापस ret;
		पूर्ण
		gpio_set_value_cansleep(cs42l73->pdata.reset_gpio, 0);
		gpio_set_value_cansleep(cs42l73->pdata.reset_gpio, 1);
	पूर्ण

	/* initialize codec */
	ret = regmap_पढ़ो(cs42l73->regmap, CS42L73_DEVID_AB, &reg);
	devid = (reg & 0xFF) << 12;

	ret = regmap_पढ़ो(cs42l73->regmap, CS42L73_DEVID_CD, &reg);
	devid |= (reg & 0xFF) << 4;

	ret = regmap_पढ़ो(cs42l73->regmap, CS42L73_DEVID_E, &reg);
	devid |= (reg & 0xF0) >> 4;

	अगर (devid != CS42L73_DEVID) अणु
		ret = -ENODEV;
		dev_err(&i2c_client->dev,
			"CS42L73 Device ID (%X). Expected %X\n",
			devid, CS42L73_DEVID);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(cs42l73->regmap, CS42L73_REVID, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c_client->dev, "Get Revision ID failed\n");
		वापस ret;
	पूर्ण

	dev_info(&i2c_client->dev,
		 "Cirrus Logic CS42L73, Revision: %02X\n", reg & 0xFF);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c_client->dev,
			&soc_component_dev_cs42l73, cs42l73_dai,
			ARRAY_SIZE(cs42l73_dai));
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cs42l73_of_match[] = अणु
	अणु .compatible = "cirrus,cs42l73", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cs42l73_of_match);

अटल स्थिर काष्ठा i2c_device_id cs42l73_id[] = अणु
	अणु"cs42l73", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, cs42l73_id);

अटल काष्ठा i2c_driver cs42l73_i2c_driver = अणु
	.driver = अणु
		   .name = "cs42l73",
		   .of_match_table = cs42l73_of_match,
		   पूर्ण,
	.id_table = cs42l73_id,
	.probe = cs42l73_i2c_probe,

पूर्ण;

module_i2c_driver(cs42l73_i2c_driver);

MODULE_DESCRIPTION("ASoC CS42L73 driver");
MODULE_AUTHOR("Georgi Vlaev, Nucleus Systems Ltd, <joe@nucleusys.com>");
MODULE_AUTHOR("Brian Austin, Cirrus Logic Inc, <brian.austin@cirrus.com>");
MODULE_LICENSE("GPL");
