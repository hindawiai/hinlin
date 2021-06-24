<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// ak4642.c  --  AK4642/AK4643 ALSA Soc Audio driver
//
// Copyright (C) 2009 Renesas Solutions Corp.
// Kuninori Morimoto <morimoto.kuninori@renesas.com>
//
// Based on wm8731.c by Riअक्षरd Purdie
// Based on ak4535.c by Riअक्षरd Purdie
// Based on wm8753.c by Liam Girdwood

/* ** CAUTION **
 *
 * This is very simple driver.
 * It can use headphone output / stereo input only
 *
 * AK4642 is tested.
 * AK4643 is tested.
 * AK4648 is tested.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#घोषणा PW_MGMT1	0x00
#घोषणा PW_MGMT2	0x01
#घोषणा SG_SL1		0x02
#घोषणा SG_SL2		0x03
#घोषणा MD_CTL1		0x04
#घोषणा MD_CTL2		0x05
#घोषणा TIMER		0x06
#घोषणा ALC_CTL1	0x07
#घोषणा ALC_CTL2	0x08
#घोषणा L_IVC		0x09
#घोषणा L_DVC		0x0a
#घोषणा ALC_CTL3	0x0b
#घोषणा R_IVC		0x0c
#घोषणा R_DVC		0x0d
#घोषणा MD_CTL3		0x0e
#घोषणा MD_CTL4		0x0f
#घोषणा PW_MGMT3	0x10
#घोषणा DF_S		0x11
#घोषणा FIL3_0		0x12
#घोषणा FIL3_1		0x13
#घोषणा FIL3_2		0x14
#घोषणा FIL3_3		0x15
#घोषणा EQ_0		0x16
#घोषणा EQ_1		0x17
#घोषणा EQ_2		0x18
#घोषणा EQ_3		0x19
#घोषणा EQ_4		0x1a
#घोषणा EQ_5		0x1b
#घोषणा FIL1_0		0x1c
#घोषणा FIL1_1		0x1d
#घोषणा FIL1_2		0x1e
#घोषणा FIL1_3		0x1f	/* The maximum valid रेजिस्टर क्रम ak4642 */
#घोषणा PW_MGMT4	0x20
#घोषणा MD_CTL5		0x21
#घोषणा LO_MS		0x22
#घोषणा HP_MS		0x23
#घोषणा SPK_MS		0x24	/* The maximum valid रेजिस्टर क्रम ak4643 */
#घोषणा EQ_FBEQAB	0x25
#घोषणा EQ_FBEQCD	0x26
#घोषणा EQ_FBEQE	0x27	/* The maximum valid रेजिस्टर क्रम ak4648 */

/* PW_MGMT1*/
#घोषणा PMVCM		(1 << 6) /* VCOM Power Management */
#घोषणा PMMIN		(1 << 5) /* MIN Input Power Management */
#घोषणा PMDAC		(1 << 2) /* DAC Power Management */
#घोषणा PMADL		(1 << 0) /* MIC Amp Lch and ADC Lch Power Management */

/* PW_MGMT2 */
#घोषणा HPMTN		(1 << 6)
#घोषणा PMHPL		(1 << 5)
#घोषणा PMHPR		(1 << 4)
#घोषणा MS		(1 << 3) /* master/slave select */
#घोषणा MCKO		(1 << 1)
#घोषणा PMPLL		(1 << 0)

#घोषणा PMHP_MASK	(PMHPL | PMHPR)
#घोषणा PMHP		PMHP_MASK

/* PW_MGMT3 */
#घोषणा PMADR		(1 << 0) /* MIC L / ADC R Power Management */

/* SG_SL1 */
#घोषणा MINS		(1 << 6) /* Switch from MIN to Speaker */
#घोषणा DACL		(1 << 4) /* Switch from DAC to Stereo or Receiver */
#घोषणा PMMP		(1 << 2) /* MPWR pin Power Management */
#घोषणा MGAIN0		(1 << 0) /* MIC amp gain*/

/* SG_SL2 */
#घोषणा LOPS		(1 << 6) /* Stero Line-out Power Save Mode */

/* TIMER */
#घोषणा ZTM(param)	((param & 0x3) << 4) /* ALC Zero Crossing TimeOut */
#घोषणा WTM(param)	(((param & 0x4) << 4) | ((param & 0x3) << 2))

/* ALC_CTL1 */
#घोषणा ALC		(1 << 5) /* ALC Enable */
#घोषणा LMTH0		(1 << 0) /* ALC Limiter / Recovery Level */

/* MD_CTL1 */
#घोषणा PLL3		(1 << 7)
#घोषणा PLL2		(1 << 6)
#घोषणा PLL1		(1 << 5)
#घोषणा PLL0		(1 << 4)
#घोषणा PLL_MASK	(PLL3 | PLL2 | PLL1 | PLL0)

#घोषणा BCKO_MASK	(1 << 3)
#घोषणा BCKO_64		BCKO_MASK

#घोषणा DIF_MASK	(3 << 0)
#घोषणा DSP		(0 << 0)
#घोषणा RIGHT_J		(1 << 0)
#घोषणा LEFT_J		(2 << 0)
#घोषणा I2S		(3 << 0)

/* MD_CTL2 */
#घोषणा FSs(val)	(((val & 0x7) << 0) | ((val & 0x8) << 2))
#घोषणा PSs(val)	((val & 0x3) << 6)

/* MD_CTL3 */
#घोषणा BST1		(1 << 3)

/* MD_CTL4 */
#घोषणा DACH		(1 << 0)

काष्ठा ak4642_drvdata अणु
	स्थिर काष्ठा regmap_config *regmap_config;
	पूर्णांक extended_frequencies;
पूर्ण;

काष्ठा ak4642_priv अणु
	स्थिर काष्ठा ak4642_drvdata *drvdata;
	काष्ठा clk *mcko;
पूर्ण;

/*
 * Playback Volume (table 39)
 *
 * max : 0x00 : +12.0 dB
 *       ( 0.5 dB step )
 * min : 0xFE : -115.0 dB
 * mute: 0xFF
 */
अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, -11550, 50, 1);

अटल स्थिर काष्ठा snd_kcontrol_new ak4642_snd_controls[] = अणु

	SOC_DOUBLE_R_TLV("Digital Playback Volume", L_DVC, R_DVC,
			 0, 0xFF, 1, out_tlv),
	SOC_SINGLE("ALC Capture Switch", ALC_CTL1, 5, 1, 0),
	SOC_SINGLE("ALC Capture ZC Switch", ALC_CTL1, 4, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ak4642_headphone_control =
	SOC_DAPM_SINGLE("Switch", PW_MGMT2, 6, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new ak4642_lout_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("DACL", SG_SL1, 4, 1, 0),
पूर्ण;

/* event handlers */
अटल पूर्णांक ak4642_lout_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMD:
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Power save mode ON */
		snd_soc_component_update_bits(component, SG_SL2, LOPS, LOPS);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
	हाल SND_SOC_DAPM_POST_PMD:
		/* Power save mode OFF */
		msleep(300);
		snd_soc_component_update_bits(component, SG_SL2, LOPS, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget ak4642_dapm_widमाला_लो[] = अणु

	/* Outमाला_दो */
	SND_SOC_DAPM_OUTPUT("HPOUTL"),
	SND_SOC_DAPM_OUTPUT("HPOUTR"),
	SND_SOC_DAPM_OUTPUT("LINEOUT"),

	SND_SOC_DAPM_PGA("HPL Out", PW_MGMT2, 5, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HPR Out", PW_MGMT2, 4, 0, शून्य, 0),
	SND_SOC_DAPM_SWITCH("Headphone Enable", SND_SOC_NOPM, 0, 0,
			    &ak4642_headphone_control),

	SND_SOC_DAPM_PGA("DACH", MD_CTL4, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MIXER_E("LINEOUT Mixer", PW_MGMT1, 3, 0,
			   &ak4642_lout_mixer_controls[0],
			   ARRAY_SIZE(ak4642_lout_mixer_controls),
			   ak4642_lout_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	/* DAC */
	SND_SOC_DAPM_DAC("DAC", शून्य, PW_MGMT1, 2, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ak4642_पूर्णांकercon[] = अणु

	/* Outमाला_दो */
	अणु"HPOUTL", शून्य, "HPL Out"पूर्ण,
	अणु"HPOUTR", शून्य, "HPR Out"पूर्ण,
	अणु"LINEOUT", शून्य, "LINEOUT Mixer"पूर्ण,

	अणु"HPL Out", शून्य, "Headphone Enable"पूर्ण,
	अणु"HPR Out", शून्य, "Headphone Enable"पूर्ण,

	अणु"Headphone Enable", "Switch", "DACH"पूर्ण,

	अणु"DACH", शून्य, "DAC"पूर्ण,

	अणु"LINEOUT Mixer", "DACL", "DAC"पूर्ण,

	अणु "DAC", शून्य, "Playback" पूर्ण,
पूर्ण;

/*
 * ak4642 रेजिस्टर cache
 */
अटल स्थिर काष्ठा reg_शेष ak4643_reg[] = अणु
	अणु  0, 0x00 पूर्ण, अणु  1, 0x00 पूर्ण, अणु  2, 0x01 पूर्ण, अणु  3, 0x00 पूर्ण,
	अणु  4, 0x02 पूर्ण, अणु  5, 0x00 पूर्ण, अणु  6, 0x00 पूर्ण, अणु  7, 0x00 पूर्ण,
	अणु  8, 0xe1 पूर्ण, अणु  9, 0xe1 पूर्ण, अणु 10, 0x18 पूर्ण, अणु 11, 0x00 पूर्ण,
	अणु 12, 0xe1 पूर्ण, अणु 13, 0x18 पूर्ण, अणु 14, 0x11 पूर्ण, अणु 15, 0x08 पूर्ण,
	अणु 16, 0x00 पूर्ण, अणु 17, 0x00 पूर्ण, अणु 18, 0x00 पूर्ण, अणु 19, 0x00 पूर्ण,
	अणु 20, 0x00 पूर्ण, अणु 21, 0x00 पूर्ण, अणु 22, 0x00 पूर्ण, अणु 23, 0x00 पूर्ण,
	अणु 24, 0x00 पूर्ण, अणु 25, 0x00 पूर्ण, अणु 26, 0x00 पूर्ण, अणु 27, 0x00 पूर्ण,
	अणु 28, 0x00 पूर्ण, अणु 29, 0x00 पूर्ण, अणु 30, 0x00 पूर्ण, अणु 31, 0x00 पूर्ण,
	अणु 32, 0x00 पूर्ण, अणु 33, 0x00 पूर्ण, अणु 34, 0x00 पूर्ण, अणु 35, 0x00 पूर्ण,
	अणु 36, 0x00 पूर्ण,
पूर्ण;

/* The शेष settings क्रम 0x0 ~ 0x1f रेजिस्टरs are the same क्रम ak4642
   and ak4643. So we reuse the ak4643 reg_शेष क्रम ak4642.
   The valid रेजिस्टरs क्रम ak4642 are 0x0 ~ 0x1f which is a subset of ak4643,
   so define NUM_AK4642_REG_DEFAULTS क्रम ak4642.
*/
#घोषणा ak4642_reg ak4643_reg
#घोषणा NUM_AK4642_REG_DEFAULTS	(FIL1_3 + 1)

अटल स्थिर काष्ठा reg_शेष ak4648_reg[] = अणु
	अणु  0, 0x00 पूर्ण, अणु  1, 0x00 पूर्ण, अणु  2, 0x01 पूर्ण, अणु  3, 0x00 पूर्ण,
	अणु  4, 0x02 पूर्ण, अणु  5, 0x00 पूर्ण, अणु  6, 0x00 पूर्ण, अणु  7, 0x00 पूर्ण,
	अणु  8, 0xe1 पूर्ण, अणु  9, 0xe1 पूर्ण, अणु 10, 0x18 पूर्ण, अणु 11, 0x00 पूर्ण,
	अणु 12, 0xe1 पूर्ण, अणु 13, 0x18 पूर्ण, अणु 14, 0x11 पूर्ण, अणु 15, 0xb8 पूर्ण,
	अणु 16, 0x00 पूर्ण, अणु 17, 0x00 पूर्ण, अणु 18, 0x00 पूर्ण, अणु 19, 0x00 पूर्ण,
	अणु 20, 0x00 पूर्ण, अणु 21, 0x00 पूर्ण, अणु 22, 0x00 पूर्ण, अणु 23, 0x00 पूर्ण,
	अणु 24, 0x00 पूर्ण, अणु 25, 0x00 पूर्ण, अणु 26, 0x00 पूर्ण, अणु 27, 0x00 पूर्ण,
	अणु 28, 0x00 पूर्ण, अणु 29, 0x00 पूर्ण, अणु 30, 0x00 पूर्ण, अणु 31, 0x00 पूर्ण,
	अणु 32, 0x00 पूर्ण, अणु 33, 0x00 पूर्ण, अणु 34, 0x00 पूर्ण, अणु 35, 0x00 पूर्ण,
	अणु 36, 0x00 पूर्ण, अणु 37, 0x88 पूर्ण, अणु 38, 0x88 पूर्ण, अणु 39, 0x08 पूर्ण,
पूर्ण;

अटल पूर्णांक ak4642_dai_startup(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक is_play = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	काष्ठा snd_soc_component *component = dai->component;

	अगर (is_play) अणु
		/*
		 * start headphone output
		 *
		 * PLL, Master Mode
		 * Audio I/F Format :MSB justअगरied (ADC & DAC)
		 * Bass Boost Level : Middle
		 *
		 * This operation came from example code of
		 * "ASAHI KASEI AK4642" (japanese) manual p97.
		 */
		snd_soc_component_ग_लिखो(component, L_IVC, 0x91); /* volume */
		snd_soc_component_ग_लिखो(component, R_IVC, 0x91); /* volume */
	पूर्ण अन्यथा अणु
		/*
		 * start stereo input
		 *
		 * PLL Master Mode
		 * Audio I/F Format:MSB justअगरied (ADC & DAC)
		 * Pre MIC AMP:+20dB
		 * MIC Power On
		 * ALC setting:Refer to Table 35
		 * ALC bit=ै 1ै 
		 *
		 * This operation came from example code of
		 * "ASAHI KASEI AK4642" (japanese) manual p94.
		 */
		snd_soc_component_update_bits(component, SG_SL1, PMMP | MGAIN0, PMMP | MGAIN0);
		snd_soc_component_ग_लिखो(component, TIMER, ZTM(0x3) | WTM(0x3));
		snd_soc_component_ग_लिखो(component, ALC_CTL1, ALC | LMTH0);
		snd_soc_component_update_bits(component, PW_MGMT1, PMADL, PMADL);
		snd_soc_component_update_bits(component, PW_MGMT3, PMADR, PMADR);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ak4642_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक is_play = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	काष्ठा snd_soc_component *component = dai->component;

	अगर (is_play) अणु
	पूर्ण अन्यथा अणु
		/* stop stereo input */
		snd_soc_component_update_bits(component, PW_MGMT1, PMADL, 0);
		snd_soc_component_update_bits(component, PW_MGMT3, PMADR, 0);
		snd_soc_component_update_bits(component, ALC_CTL1, ALC, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक ak4642_dai_set_sysclk(काष्ठा snd_soc_dai *codec_dai,
	पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा ak4642_priv *priv = snd_soc_component_get_drvdata(component);
	u8 pll;
	पूर्णांक extended_freq = 0;

	चयन (freq) अणु
	हाल 11289600:
		pll = PLL2;
		अवरोध;
	हाल 12288000:
		pll = PLL2 | PLL0;
		अवरोध;
	हाल 12000000:
		pll = PLL2 | PLL1;
		अवरोध;
	हाल 24000000:
		pll = PLL2 | PLL1 | PLL0;
		अवरोध;
	हाल 13500000:
		pll = PLL3 | PLL2;
		अवरोध;
	हाल 27000000:
		pll = PLL3 | PLL2 | PLL0;
		अवरोध;
	हाल 19200000:
		pll = PLL3;
		extended_freq = 1;
		अवरोध;
	हाल 13000000:
		pll = PLL3 | PLL2 | PLL1;
		extended_freq = 1;
		अवरोध;
	हाल 26000000:
		pll = PLL3 | PLL2 | PLL1 | PLL0;
		extended_freq = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (extended_freq && !priv->drvdata->extended_frequencies)
		वापस -EINVAL;

	snd_soc_component_update_bits(component, MD_CTL1, PLL_MASK, pll);

	वापस 0;
पूर्ण

अटल पूर्णांक ak4642_dai_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 data;
	u8 bcko;

	data = MCKO | PMPLL; /* use MCKO */
	bcko = 0;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		data |= MS;
		bcko = BCKO_64;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, PW_MGMT2, MS | MCKO | PMPLL, data);
	snd_soc_component_update_bits(component, MD_CTL1, BCKO_MASK, bcko);

	/* क्रमmat type */
	data = 0;
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_LEFT_J:
		data = LEFT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		data = I2S;
		अवरोध;
	/* FIXME
	 * Please add RIGHT_J / DSP support here
	 */
	शेष:
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, MD_CTL1, DIF_MASK, data);

	वापस 0;
पूर्ण

अटल पूर्णांक ak4642_set_mcko(काष्ठा snd_soc_component *component,
			   u32 frequency)
अणु
	अटल स्थिर u32 fs_list[] = अणु
		[0] = 8000,
		[1] = 12000,
		[2] = 16000,
		[3] = 24000,
		[4] = 7350,
		[5] = 11025,
		[6] = 14700,
		[7] = 22050,
		[10] = 32000,
		[11] = 48000,
		[14] = 29400,
		[15] = 44100,
	पूर्ण;
	अटल स्थिर u32 ps_list[] = अणु
		[0] = 256,
		[1] = 128,
		[2] = 64,
		[3] = 32
	पूर्ण;
	पूर्णांक ps, fs;

	क्रम (ps = 0; ps < ARRAY_SIZE(ps_list); ps++) अणु
		क्रम (fs = 0; fs < ARRAY_SIZE(fs_list); fs++) अणु
			अगर (frequency == ps_list[ps] * fs_list[fs]) अणु
				snd_soc_component_ग_लिखो(component, MD_CTL2,
					      PSs(ps) | FSs(fs));
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ak4642_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak4642_priv *priv = snd_soc_component_get_drvdata(component);
	u32 rate = clk_get_rate(priv->mcko);

	अगर (!rate)
		rate = params_rate(params) * 256;

	वापस ak4642_set_mcko(component, rate);
पूर्ण

अटल पूर्णांक ak4642_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_ग_लिखो(component, PW_MGMT1, 0x00);
		अवरोध;
	शेष:
		snd_soc_component_update_bits(component, PW_MGMT1, PMVCM, PMVCM);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops ak4642_dai_ops = अणु
	.startup	= ak4642_dai_startup,
	.shutकरोwn	= ak4642_dai_shutकरोwn,
	.set_sysclk	= ak4642_dai_set_sysclk,
	.set_fmt	= ak4642_dai_set_fmt,
	.hw_params	= ak4642_dai_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ak4642_dai = अणु
	.name = "ak4642-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE पूर्ण,
	.ops = &ak4642_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक ak4642_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा regmap *regmap = dev_get_regmap(component->dev, शून्य);

	regcache_cache_only(regmap, true);
	regcache_mark_dirty(regmap);
	वापस 0;
पूर्ण

अटल पूर्णांक ak4642_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा regmap *regmap = dev_get_regmap(component->dev, शून्य);

	regcache_cache_only(regmap, false);
	regcache_sync(regmap);
	वापस 0;
पूर्ण
अटल पूर्णांक ak4642_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ak4642_priv *priv = snd_soc_component_get_drvdata(component);

	अगर (priv->mcko)
		ak4642_set_mcko(component, clk_get_rate(priv->mcko));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_ak4642 = अणु
	.probe			= ak4642_probe,
	.suspend		= ak4642_suspend,
	.resume			= ak4642_resume,
	.set_bias_level		= ak4642_set_bias_level,
	.controls		= ak4642_snd_controls,
	.num_controls		= ARRAY_SIZE(ak4642_snd_controls),
	.dapm_widमाला_लो		= ak4642_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ak4642_dapm_widमाला_लो),
	.dapm_routes		= ak4642_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(ak4642_पूर्णांकercon),
	.idle_bias_on		= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ak4642_regmap = अणु
	.reg_bits		= 8,
	.val_bits		= 8,
	.max_रेजिस्टर		= FIL1_3,
	.reg_शेषs		= ak4642_reg,
	.num_reg_शेषs	= NUM_AK4642_REG_DEFAULTS,
	.cache_type		= REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ak4643_regmap = अणु
	.reg_bits		= 8,
	.val_bits		= 8,
	.max_रेजिस्टर		= SPK_MS,
	.reg_शेषs		= ak4643_reg,
	.num_reg_शेषs	= ARRAY_SIZE(ak4643_reg),
	.cache_type		= REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ak4648_regmap = अणु
	.reg_bits		= 8,
	.val_bits		= 8,
	.max_रेजिस्टर		= EQ_FBEQE,
	.reg_शेषs		= ak4648_reg,
	.num_reg_शेषs	= ARRAY_SIZE(ak4648_reg),
	.cache_type		= REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा ak4642_drvdata ak4642_drvdata = अणु
	.regmap_config = &ak4642_regmap,
पूर्ण;

अटल स्थिर काष्ठा ak4642_drvdata ak4643_drvdata = अणु
	.regmap_config = &ak4643_regmap,
पूर्ण;

अटल स्थिर काष्ठा ak4642_drvdata ak4648_drvdata = अणु
	.regmap_config = &ak4648_regmap,
	.extended_frequencies = 1,
पूर्ण;

#अगर_घोषित CONFIG_COMMON_CLK
अटल काष्ठा clk *ak4642_of_parse_mcko(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा clk *clk;
	स्थिर अक्षर *clk_name = np->name;
	स्थिर अक्षर *parent_clk_name = शून्य;
	u32 rate;

	अगर (of_property_पढ़ो_u32(np, "clock-frequency", &rate))
		वापस शून्य;

	अगर (of_property_पढ़ो_bool(np, "clocks"))
		parent_clk_name = of_clk_get_parent_name(np, 0);

	of_property_पढ़ो_string(np, "clock-output-names", &clk_name);

	clk = clk_रेजिस्टर_fixed_rate(dev, clk_name, parent_clk_name, 0, rate);
	अगर (!IS_ERR(clk))
		of_clk_add_provider(np, of_clk_src_simple_get, clk);

	वापस clk;
पूर्ण
#अन्यथा
#घोषणा ak4642_of_parse_mcko(d) 0
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id ak4642_of_match[];
अटल पूर्णांक ak4642_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा ak4642_drvdata *drvdata = शून्य;
	काष्ठा regmap *regmap;
	काष्ठा ak4642_priv *priv;
	काष्ठा clk *mcko = शून्य;

	अगर (np) अणु
		स्थिर काष्ठा of_device_id *of_id;

		mcko = ak4642_of_parse_mcko(dev);
		अगर (IS_ERR(mcko))
			mcko = शून्य;

		of_id = of_match_device(ak4642_of_match, dev);
		अगर (of_id)
			drvdata = of_id->data;
	पूर्ण अन्यथा अणु
		drvdata = (स्थिर काष्ठा ak4642_drvdata *)id->driver_data;
	पूर्ण

	अगर (!drvdata) अणु
		dev_err(dev, "Unknown device type\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->drvdata = drvdata;
	priv->mcko = mcko;

	i2c_set_clientdata(i2c, priv);

	regmap = devm_regmap_init_i2c(i2c, drvdata->regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस devm_snd_soc_रेजिस्टर_component(dev,
				&soc_component_dev_ak4642, &ak4642_dai, 1);
पूर्ण

अटल स्थिर काष्ठा of_device_id ak4642_of_match[] = अणु
	अणु .compatible = "asahi-kasei,ak4642",	.data = &ak4642_drvdataपूर्ण,
	अणु .compatible = "asahi-kasei,ak4643",	.data = &ak4643_drvdataपूर्ण,
	अणु .compatible = "asahi-kasei,ak4648",	.data = &ak4648_drvdataपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ak4642_of_match);

अटल स्थिर काष्ठा i2c_device_id ak4642_i2c_id[] = अणु
	अणु "ak4642", (kernel_uदीर्घ_t)&ak4642_drvdata पूर्ण,
	अणु "ak4643", (kernel_uदीर्घ_t)&ak4643_drvdata पूर्ण,
	अणु "ak4648", (kernel_uदीर्घ_t)&ak4648_drvdata पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ak4642_i2c_id);

अटल काष्ठा i2c_driver ak4642_i2c_driver = अणु
	.driver = अणु
		.name = "ak4642-codec",
		.of_match_table = ak4642_of_match,
	पूर्ण,
	.probe		= ak4642_i2c_probe,
	.id_table	= ak4642_i2c_id,
पूर्ण;

module_i2c_driver(ak4642_i2c_driver);

MODULE_DESCRIPTION("Soc AK4642 driver");
MODULE_AUTHOR("Kuninori Morimoto <morimoto.kuninori@renesas.com>");
MODULE_LICENSE("GPL v2");
