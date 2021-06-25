<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// ak4613.c  --  Asahi Kasei ALSA Soc Audio driver
//
// Copyright (C) 2015 Renesas Electronics Corporation
// Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
//
// Based on ak4642.c by Kuninori Morimoto
// Based on wm8731.c by Riअक्षरd Purdie
// Based on ak4535.c by Riअक्षरd Purdie
// Based on wm8753.c by Liam Girdwood

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>

#घोषणा PW_MGMT1	0x00 /* Power Management 1 */
#घोषणा PW_MGMT2	0x01 /* Power Management 2 */
#घोषणा PW_MGMT3	0x02 /* Power Management 3 */
#घोषणा CTRL1		0x03 /* Control 1 */
#घोषणा CTRL2		0x04 /* Control 2 */
#घोषणा DEMP1		0x05 /* De-emphasis1 */
#घोषणा DEMP2		0x06 /* De-emphasis2 */
#घोषणा OFD		0x07 /* Overflow Detect */
#घोषणा ZRD		0x08 /* Zero Detect */
#घोषणा ICTRL		0x09 /* Input Control */
#घोषणा OCTRL		0x0a /* Output Control */
#घोषणा LOUT1		0x0b /* LOUT1 Volume Control */
#घोषणा ROUT1		0x0c /* ROUT1 Volume Control */
#घोषणा LOUT2		0x0d /* LOUT2 Volume Control */
#घोषणा ROUT2		0x0e /* ROUT2 Volume Control */
#घोषणा LOUT3		0x0f /* LOUT3 Volume Control */
#घोषणा ROUT3		0x10 /* ROUT3 Volume Control */
#घोषणा LOUT4		0x11 /* LOUT4 Volume Control */
#घोषणा ROUT4		0x12 /* ROUT4 Volume Control */
#घोषणा LOUT5		0x13 /* LOUT5 Volume Control */
#घोषणा ROUT5		0x14 /* ROUT5 Volume Control */
#घोषणा LOUT6		0x15 /* LOUT6 Volume Control */
#घोषणा ROUT6		0x16 /* ROUT6 Volume Control */

/* PW_MGMT1 */
#घोषणा RSTN		BIT(0)
#घोषणा PMDAC		BIT(1)
#घोषणा PMADC		BIT(2)
#घोषणा PMVR		BIT(3)

/* PW_MGMT2 */
#घोषणा PMAD_ALL	0x7

/* PW_MGMT3 */
#घोषणा PMDA_ALL	0x3f

/* CTRL1 */
#घोषणा DIF0		BIT(3)
#घोषणा DIF1		BIT(4)
#घोषणा DIF2		BIT(5)
#घोषणा TDM0		BIT(6)
#घोषणा TDM1		BIT(7)
#घोषणा NO_FMT		(0xff)
#घोषणा FMT_MASK	(0xf8)

/* CTRL2 */
#घोषणा DFS_MASK		(3 << 2)
#घोषणा DFS_NORMAL_SPEED	(0 << 2)
#घोषणा DFS_DOUBLE_SPEED	(1 << 2)
#घोषणा DFS_QUAD_SPEED		(2 << 2)

/* ICTRL */
#घोषणा ICTRL_MASK	(0x3)

/* OCTRL */
#घोषणा OCTRL_MASK	(0x3F)

काष्ठा ak4613_क्रमmats अणु
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक fmt;
पूर्ण;

काष्ठा ak4613_पूर्णांकerface अणु
	काष्ठा ak4613_क्रमmats capture;
	काष्ठा ak4613_क्रमmats playback;
पूर्ण;

काष्ठा ak4613_priv अणु
	काष्ठा mutex lock;
	स्थिर काष्ठा ak4613_पूर्णांकerface *अगरace;
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांक;
	काष्ठा work_काष्ठा dummy_ग_लिखो_work;
	काष्ठा snd_soc_component *component;
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक sysclk;

	अचिन्हित पूर्णांक fmt;
	u8 oc;
	u8 ic;
	पूर्णांक cnt;
पूर्ण;

/*
 * Playback Volume
 *
 * max : 0x00 : 0 dB
 *       ( 0.5 dB step )
 * min : 0xFE : -127.0 dB
 * mute: 0xFF
 */
अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, -12750, 50, 1);

अटल स्थिर काष्ठा snd_kcontrol_new ak4613_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("Digital Playback Volume1", LOUT1, ROUT1,
			 0, 0xFF, 1, out_tlv),
	SOC_DOUBLE_R_TLV("Digital Playback Volume2", LOUT2, ROUT2,
			 0, 0xFF, 1, out_tlv),
	SOC_DOUBLE_R_TLV("Digital Playback Volume3", LOUT3, ROUT3,
			 0, 0xFF, 1, out_tlv),
	SOC_DOUBLE_R_TLV("Digital Playback Volume4", LOUT4, ROUT4,
			 0, 0xFF, 1, out_tlv),
	SOC_DOUBLE_R_TLV("Digital Playback Volume5", LOUT5, ROUT5,
			 0, 0xFF, 1, out_tlv),
	SOC_DOUBLE_R_TLV("Digital Playback Volume6", LOUT6, ROUT6,
			 0, 0xFF, 1, out_tlv),
पूर्ण;

अटल स्थिर काष्ठा reg_शेष ak4613_reg[] = अणु
	अणु 0x0,  0x0f पूर्ण, अणु 0x1,  0x07 पूर्ण, अणु 0x2,  0x3f पूर्ण, अणु 0x3,  0x20 पूर्ण,
	अणु 0x4,  0x20 पूर्ण, अणु 0x5,  0x55 पूर्ण, अणु 0x6,  0x05 पूर्ण, अणु 0x7,  0x07 पूर्ण,
	अणु 0x8,  0x0f पूर्ण, अणु 0x9,  0x07 पूर्ण, अणु 0xa,  0x3f पूर्ण, अणु 0xb,  0x00 पूर्ण,
	अणु 0xc,  0x00 पूर्ण, अणु 0xd,  0x00 पूर्ण, अणु 0xe,  0x00 पूर्ण, अणु 0xf,  0x00 पूर्ण,
	अणु 0x10, 0x00 पूर्ण, अणु 0x11, 0x00 पूर्ण, अणु 0x12, 0x00 पूर्ण, अणु 0x13, 0x00 पूर्ण,
	अणु 0x14, 0x00 पूर्ण, अणु 0x15, 0x00 पूर्ण, अणु 0x16, 0x00 पूर्ण,
पूर्ण;

#घोषणा AUDIO_IFACE_TO_VAL(fmts) ((fmts - ak4613_अगरace) << 3)
#घोषणा AUDIO_IFACE(b, fmt) अणु b, SND_SOC_DAIFMT_##fmt पूर्ण
अटल स्थिर काष्ठा ak4613_पूर्णांकerface ak4613_अगरace[] = अणु
	/* capture */				/* playback */
	/* [0] - [2] are not supported */
	[3] = अणु	AUDIO_IFACE(24, LEFT_J),	AUDIO_IFACE(24, LEFT_J) पूर्ण,
	[4] = अणु	AUDIO_IFACE(24, I2S),		AUDIO_IFACE(24, I2S) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ak4613_regmap_cfg = अणु
	.reg_bits		= 8,
	.val_bits		= 8,
	.max_रेजिस्टर		= 0x16,
	.reg_शेषs		= ak4613_reg,
	.num_reg_शेषs	= ARRAY_SIZE(ak4613_reg),
	.cache_type		= REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ak4613_of_match[] = अणु
	अणु .compatible = "asahi-kasei,ak4613",	.data = &ak4613_regmap_cfg पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ak4613_of_match);

अटल स्थिर काष्ठा i2c_device_id ak4613_i2c_id[] = अणु
	अणु "ak4613", (kernel_uदीर्घ_t)&ak4613_regmap_cfg पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ak4613_i2c_id);

अटल स्थिर काष्ठा snd_soc_dapm_widget ak4613_dapm_widमाला_लो[] = अणु

	/* Outमाला_दो */
	SND_SOC_DAPM_OUTPUT("LOUT1"),
	SND_SOC_DAPM_OUTPUT("LOUT2"),
	SND_SOC_DAPM_OUTPUT("LOUT3"),
	SND_SOC_DAPM_OUTPUT("LOUT4"),
	SND_SOC_DAPM_OUTPUT("LOUT5"),
	SND_SOC_DAPM_OUTPUT("LOUT6"),

	SND_SOC_DAPM_OUTPUT("ROUT1"),
	SND_SOC_DAPM_OUTPUT("ROUT2"),
	SND_SOC_DAPM_OUTPUT("ROUT3"),
	SND_SOC_DAPM_OUTPUT("ROUT4"),
	SND_SOC_DAPM_OUTPUT("ROUT5"),
	SND_SOC_DAPM_OUTPUT("ROUT6"),

	/* Inमाला_दो */
	SND_SOC_DAPM_INPUT("LIN1"),
	SND_SOC_DAPM_INPUT("LIN2"),

	SND_SOC_DAPM_INPUT("RIN1"),
	SND_SOC_DAPM_INPUT("RIN2"),

	/* DAC */
	SND_SOC_DAPM_DAC("DAC1", शून्य, PW_MGMT3, 0, 0),
	SND_SOC_DAPM_DAC("DAC2", शून्य, PW_MGMT3, 1, 0),
	SND_SOC_DAPM_DAC("DAC3", शून्य, PW_MGMT3, 2, 0),
	SND_SOC_DAPM_DAC("DAC4", शून्य, PW_MGMT3, 3, 0),
	SND_SOC_DAPM_DAC("DAC5", शून्य, PW_MGMT3, 4, 0),
	SND_SOC_DAPM_DAC("DAC6", शून्य, PW_MGMT3, 5, 0),

	/* ADC */
	SND_SOC_DAPM_ADC("ADC1", शून्य, PW_MGMT2, 0, 0),
	SND_SOC_DAPM_ADC("ADC2", शून्य, PW_MGMT2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ak4613_पूर्णांकercon[] = अणु
	अणु"LOUT1", शून्य, "DAC1"पूर्ण,
	अणु"LOUT2", शून्य, "DAC2"पूर्ण,
	अणु"LOUT3", शून्य, "DAC3"पूर्ण,
	अणु"LOUT4", शून्य, "DAC4"पूर्ण,
	अणु"LOUT5", शून्य, "DAC5"पूर्ण,
	अणु"LOUT6", शून्य, "DAC6"पूर्ण,

	अणु"ROUT1", शून्य, "DAC1"पूर्ण,
	अणु"ROUT2", शून्य, "DAC2"पूर्ण,
	अणु"ROUT3", शून्य, "DAC3"पूर्ण,
	अणु"ROUT4", शून्य, "DAC4"पूर्ण,
	अणु"ROUT5", शून्य, "DAC5"पूर्ण,
	अणु"ROUT6", शून्य, "DAC6"पूर्ण,

	अणु"DAC1", शून्य, "Playback"पूर्ण,
	अणु"DAC2", शून्य, "Playback"पूर्ण,
	अणु"DAC3", शून्य, "Playback"पूर्ण,
	अणु"DAC4", शून्य, "Playback"पूर्ण,
	अणु"DAC5", शून्य, "Playback"पूर्ण,
	अणु"DAC6", शून्य, "Playback"पूर्ण,

	अणु"Capture", शून्य, "ADC1"पूर्ण,
	अणु"Capture", शून्य, "ADC2"पूर्ण,

	अणु"ADC1", शून्य, "LIN1"पूर्ण,
	अणु"ADC2", शून्य, "LIN2"पूर्ण,

	अणु"ADC1", शून्य, "RIN1"पूर्ण,
	अणु"ADC2", शून्य, "RIN2"पूर्ण,
पूर्ण;

अटल व्योम ak4613_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak4613_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा device *dev = component->dev;

	mutex_lock(&priv->lock);
	priv->cnt--;
	अगर (priv->cnt < 0) अणु
		dev_err(dev, "unexpected counter error\n");
		priv->cnt = 0;
	पूर्ण
	अगर (!priv->cnt)
		priv->अगरace = शून्य;
	mutex_unlock(&priv->lock);
पूर्ण

अटल व्योम ak4613_hw_स्थिरraपूर्णांकs(काष्ठा ak4613_priv *priv,
				  काष्ठा snd_pcm_runसमय *runसमय)
अणु
	अटल स्थिर अचिन्हित पूर्णांक ak4613_rates[] = अणु
		 32000,
		 44100,
		 48000,
		 64000,
		 88200,
		 96000,
		176400,
		192000,
	पूर्ण;
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *स्थिरraपूर्णांक = &priv->स्थिरraपूर्णांक;
	अचिन्हित पूर्णांक fs;
	पूर्णांक i;

	स्थिरraपूर्णांक->list	= ak4613_rates;
	स्थिरraपूर्णांक->mask	= 0;
	स्थिरraपूर्णांक->count	= 0;

	/*
	 * Slave Mode
	 *	Normal: [32kHz, 48kHz] : 256fs,384fs or 512fs
	 *	Double: [64kHz, 96kHz] : 256fs
	 *	Quad  : [128kHz,192kHz]: 128fs
	 *
	 * Master mode
	 *	Normal: [32kHz, 48kHz] : 256fs or 512fs
	 *	Double: [64kHz, 96kHz] : 256fs
	 *	Quad  : [128kHz,192kHz]: 128fs
	*/
	क्रम (i = 0; i < ARRAY_SIZE(ak4613_rates); i++) अणु
		/* minimum fs on each range */
		fs = (ak4613_rates[i] <= 96000) ? 256 : 128;

		अगर (priv->sysclk >= ak4613_rates[i] * fs)
			स्थिरraपूर्णांक->count = i + 1;
	पूर्ण

	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE, स्थिरraपूर्णांक);
पूर्ण

अटल पूर्णांक ak4613_dai_startup(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak4613_priv *priv = snd_soc_component_get_drvdata(component);

	priv->cnt++;

	ak4613_hw_स्थिरraपूर्णांकs(priv, substream->runसमय);

	वापस 0;
पूर्ण

अटल पूर्णांक ak4613_dai_set_sysclk(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा ak4613_priv *priv = snd_soc_component_get_drvdata(component);

	priv->sysclk = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक ak4613_dai_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak4613_priv *priv = snd_soc_component_get_drvdata(component);

	fmt &= SND_SOC_DAIFMT_FORMAT_MASK;

	चयन (fmt) अणु
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_I2S:
		priv->fmt = fmt;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool ak4613_dai_fmt_matching(स्थिर काष्ठा ak4613_पूर्णांकerface *अगरace,
				    पूर्णांक is_play,
				    अचिन्हित पूर्णांक fmt, अचिन्हित पूर्णांक width)
अणु
	स्थिर काष्ठा ak4613_क्रमmats *fmts;

	fmts = (is_play) ? &अगरace->playback : &अगरace->capture;

	अगर (fmts->fmt != fmt)
		वापस false;

	अगर (fmts->width != width)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक ak4613_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak4613_priv *priv = snd_soc_component_get_drvdata(component);
	स्थिर काष्ठा ak4613_पूर्णांकerface *अगरace;
	काष्ठा device *dev = component->dev;
	अचिन्हित पूर्णांक width = params_width(params);
	अचिन्हित पूर्णांक fmt = priv->fmt;
	अचिन्हित पूर्णांक rate;
	पूर्णांक is_play = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	पूर्णांक i, ret;
	u8 fmt_ctrl, ctrl2;

	rate = params_rate(params);
	चयन (rate) अणु
	हाल 32000:
	हाल 44100:
	हाल 48000:
		ctrl2 = DFS_NORMAL_SPEED;
		अवरोध;
	हाल 64000:
	हाल 88200:
	हाल 96000:
		ctrl2 = DFS_DOUBLE_SPEED;
		अवरोध;
	हाल 176400:
	हाल 192000:
		ctrl2 = DFS_QUAD_SPEED;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	priv->rate = rate;

	/*
	 * FIXME
	 *
	 * It करोesn't support TDM at this poपूर्णांक
	 */
	fmt_ctrl = NO_FMT;
	ret = -EINVAL;
	अगरace = शून्य;

	mutex_lock(&priv->lock);
	अगर (priv->अगरace) अणु
		अगर (ak4613_dai_fmt_matching(priv->अगरace, is_play, fmt, width))
			अगरace = priv->अगरace;
	पूर्ण अन्यथा अणु
		क्रम (i = ARRAY_SIZE(ak4613_अगरace) - 1; i >= 0; i--) अणु
			अगर (!ak4613_dai_fmt_matching(ak4613_अगरace + i,
						     is_play,
						     fmt, width))
				जारी;
			अगरace = ak4613_अगरace + i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((priv->अगरace == शून्य) ||
	    (priv->अगरace == अगरace)) अणु
		priv->अगरace = अगरace;
		ret = 0;
	पूर्ण
	mutex_unlock(&priv->lock);

	अगर (ret < 0)
		जाओ hw_params_end;

	fmt_ctrl = AUDIO_IFACE_TO_VAL(अगरace);

	snd_soc_component_update_bits(component, CTRL1, FMT_MASK, fmt_ctrl);
	snd_soc_component_update_bits(component, CTRL2, DFS_MASK, ctrl2);

	snd_soc_component_update_bits(component, ICTRL, ICTRL_MASK, priv->ic);
	snd_soc_component_update_bits(component, OCTRL, OCTRL_MASK, priv->oc);

hw_params_end:
	अगर (ret < 0)
		dev_warn(dev, "unsupported data width/format combination\n");

	वापस ret;
पूर्ण

अटल पूर्णांक ak4613_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	u8 mgmt1 = 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		mgmt1 |= RSTN;
		fallthrough;
	हाल SND_SOC_BIAS_PREPARE:
		mgmt1 |= PMADC | PMDAC;
		fallthrough;
	हाल SND_SOC_BIAS_STANDBY:
		mgmt1 |= PMVR;
		fallthrough;
	हाल SND_SOC_BIAS_OFF:
	शेष:
		अवरोध;
	पूर्ण

	snd_soc_component_ग_लिखो(component, PW_MGMT1, mgmt1);

	वापस 0;
पूर्ण

अटल व्योम ak4613_dummy_ग_लिखो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ak4613_priv *priv = container_of(work,
						काष्ठा ak4613_priv,
						dummy_ग_लिखो_work);
	काष्ठा snd_soc_component *component = priv->component;
	अचिन्हित पूर्णांक mgmt1;
	अचिन्हित पूर्णांक mgmt3;

	/*
	 * PW_MGMT1 / PW_MGMT3 needs dummy ग_लिखो at least after 5 LR घड़ीs
	 *
	 * Note
	 *
	 * To aव्योम extra delay, we want to aव्योम preemption here,
	 * but we can't. Because it uses I2C access which is using IRQ
	 * and sleep. Thus, delay might be more than 5 LR घड़ीs
	 * see also
	 *	ak4613_dai_trigger()
	 */
	udelay(5000000 / priv->rate);

	mgmt1 = snd_soc_component_पढ़ो(component, PW_MGMT1);
	mgmt3 = snd_soc_component_पढ़ो(component, PW_MGMT3);

	snd_soc_component_ग_लिखो(component, PW_MGMT1, mgmt1);
	snd_soc_component_ग_लिखो(component, PW_MGMT3, mgmt3);
पूर्ण

अटल पूर्णांक ak4613_dai_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak4613_priv *priv = snd_soc_component_get_drvdata(component);

	/*
	 * FIXME
	 *
	 * PW_MGMT1 / PW_MGMT3 needs dummy ग_लिखो at least after 5 LR घड़ीs
	 * from Power Down Release. Otherwise, Playback volume will be 0dB.
	 * To aव्योम complex multiple delay/dummy_ग_लिखो method from
	 * ak4613_set_bias_level() / SND_SOC_DAPM_DAC_E("DACx", ...),
	 * call it once here.
	 *
	 * But, unक्रमtunately, we can't "write" here because here is atomic
	 * context (It uses I2C access क्रम writing).
	 * Thus, use schedule_work() to चयनing to normal context
	 * immediately.
	 *
	 * Note
	 *
	 * Calling ak4613_dummy_ग_लिखो() function might be delayed.
	 * In such हाल, ak4613 volume might be temporarily 0dB when
	 * beggining of playback.
	 * see also
	 *	ak4613_dummy_ग_लिखो()
	 */

	अगर ((cmd != SNDRV_PCM_TRIGGER_START) &&
	    (cmd != SNDRV_PCM_TRIGGER_RESUME))
		वापस 0;

	अगर (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
		वापस  0;

	priv->component = component;
	schedule_work(&priv->dummy_ग_लिखो_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops ak4613_dai_ops = अणु
	.startup	= ak4613_dai_startup,
	.shutकरोwn	= ak4613_dai_shutकरोwn,
	.set_sysclk	= ak4613_dai_set_sysclk,
	.set_fmt	= ak4613_dai_set_fmt,
	.trigger	= ak4613_dai_trigger,
	.hw_params	= ak4613_dai_hw_params,
पूर्ण;

#घोषणा AK4613_PCM_RATE		(SNDRV_PCM_RATE_32000  |\
				 SNDRV_PCM_RATE_44100  |\
				 SNDRV_PCM_RATE_48000  |\
				 SNDRV_PCM_RATE_64000  |\
				 SNDRV_PCM_RATE_88200  |\
				 SNDRV_PCM_RATE_96000  |\
				 SNDRV_PCM_RATE_176400 |\
				 SNDRV_PCM_RATE_192000)
#घोषणा AK4613_PCM_FMTBIT	(SNDRV_PCM_FMTBIT_S24_LE)

अटल काष्ठा snd_soc_dai_driver ak4613_dai = अणु
	.name = "ak4613-hifi",
	.playback = अणु
		.stream_name	= "Playback",
		.channels_min	= 2,
		.channels_max	= 2,
		.rates		= AK4613_PCM_RATE,
		.क्रमmats	= AK4613_PCM_FMTBIT,
	पूर्ण,
	.capture = अणु
		.stream_name	= "Capture",
		.channels_min	= 2,
		.channels_max	= 2,
		.rates		= AK4613_PCM_RATE,
		.क्रमmats	= AK4613_PCM_FMTBIT,
	पूर्ण,
	.ops = &ak4613_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक ak4613_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा regmap *regmap = dev_get_regmap(component->dev, शून्य);

	regcache_cache_only(regmap, true);
	regcache_mark_dirty(regmap);
	वापस 0;
पूर्ण

अटल पूर्णांक ak4613_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा regmap *regmap = dev_get_regmap(component->dev, शून्य);

	regcache_cache_only(regmap, false);
	वापस regcache_sync(regmap);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_ak4613 = अणु
	.suspend		= ak4613_suspend,
	.resume			= ak4613_resume,
	.set_bias_level		= ak4613_set_bias_level,
	.controls		= ak4613_snd_controls,
	.num_controls		= ARRAY_SIZE(ak4613_snd_controls),
	.dapm_widमाला_लो		= ak4613_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ak4613_dapm_widमाला_लो),
	.dapm_routes		= ak4613_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(ak4613_पूर्णांकercon),
	.idle_bias_on		= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल व्योम ak4613_parse_of(काष्ठा ak4613_priv *priv,
			    काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	अक्षर prop[32];
	पूर्णांक i;

	/* Input 1 - 2 */
	क्रम (i = 0; i < 2; i++) अणु
		snम_लिखो(prop, माप(prop), "asahi-kasei,in%d-single-end", i + 1);
		अगर (!of_get_property(np, prop, शून्य))
			priv->ic |= 1 << i;
	पूर्ण

	/* Output 1 - 6 */
	क्रम (i = 0; i < 6; i++) अणु
		snम_लिखो(prop, माप(prop), "asahi-kasei,out%d-single-end", i + 1);
		अगर (!of_get_property(np, prop, शून्य))
			priv->oc |= 1 << i;
	पूर्ण
पूर्ण

अटल पूर्णांक ak4613_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा regmap_config *regmap_cfg;
	काष्ठा regmap *regmap;
	काष्ठा ak4613_priv *priv;

	regmap_cfg = शून्य;
	अगर (np) अणु
		स्थिर काष्ठा of_device_id *of_id;

		of_id = of_match_device(ak4613_of_match, dev);
		अगर (of_id)
			regmap_cfg = of_id->data;
	पूर्ण अन्यथा अणु
		regmap_cfg = (स्थिर काष्ठा regmap_config *)id->driver_data;
	पूर्ण

	अगर (!regmap_cfg)
		वापस -EINVAL;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ak4613_parse_of(priv, dev);

	priv->अगरace		= शून्य;
	priv->cnt		= 0;
	priv->sysclk		= 0;
	INIT_WORK(&priv->dummy_ग_लिखो_work, ak4613_dummy_ग_लिखो);

	mutex_init(&priv->lock);

	i2c_set_clientdata(i2c, priv);

	regmap = devm_regmap_init_i2c(i2c, regmap_cfg);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस devm_snd_soc_रेजिस्टर_component(dev, &soc_component_dev_ak4613,
				      &ak4613_dai, 1);
पूर्ण

अटल पूर्णांक ak4613_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver ak4613_i2c_driver = अणु
	.driver = अणु
		.name = "ak4613-codec",
		.of_match_table = ak4613_of_match,
	पूर्ण,
	.probe		= ak4613_i2c_probe,
	.हटाओ		= ak4613_i2c_हटाओ,
	.id_table	= ak4613_i2c_id,
पूर्ण;

module_i2c_driver(ak4613_i2c_driver);

MODULE_DESCRIPTION("Soc AK4613 driver");
MODULE_AUTHOR("Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>");
MODULE_LICENSE("GPL v2");
