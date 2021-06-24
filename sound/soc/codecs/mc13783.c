<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2008 Juergen Beisert, kernel@pengutronix.de
 * Copyright 2009 Sascha Hauer, s.hauer@pengutronix.de
 * Copyright 2012 Philippe Retornaz, philippe.retornaz@epfl.ch
 *
 * Initial development of this code was funded by
 * Phytec Messtechnik GmbH, https://www.phytec.de
 */
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/mc13xxx.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc-dapm.h>
#समावेश <linux/regmap.h>

#समावेश "mc13783.h"

#घोषणा AUDIO_RX0_ALSPEN		(1 << 5)
#घोषणा AUDIO_RX0_ALSPSEL		(1 << 7)
#घोषणा AUDIO_RX0_ADDCDC		(1 << 21)
#घोषणा AUDIO_RX0_ADDSTDC		(1 << 22)
#घोषणा AUDIO_RX0_ADDRXIN		(1 << 23)

#घोषणा AUDIO_RX1_PGARXEN		(1 << 0);
#घोषणा AUDIO_RX1_PGASTEN		(1 << 5)
#घोषणा AUDIO_RX1_ARXINEN		(1 << 10)

#घोषणा AUDIO_TX_AMC1REN		(1 << 5)
#घोषणा AUDIO_TX_AMC1LEN		(1 << 7)
#घोषणा AUDIO_TX_AMC2EN			(1 << 9)
#घोषणा AUDIO_TX_ATXINEN		(1 << 11)
#घोषणा AUDIO_TX_RXINREC		(1 << 13)

#घोषणा SSI_NETWORK_CDCTXRXSLOT(x)	(((x) & 0x3) << 2)
#घोषणा SSI_NETWORK_CDCTXSECSLOT(x)	(((x) & 0x3) << 4)
#घोषणा SSI_NETWORK_CDCRXSECSLOT(x)	(((x) & 0x3) << 6)
#घोषणा SSI_NETWORK_CDCRXSECGAIN(x)	(((x) & 0x3) << 8)
#घोषणा SSI_NETWORK_CDCSUMGAIN(x)	(1 << 10)
#घोषणा SSI_NETWORK_CDCFSDLY(x)		(1 << 11)
#घोषणा SSI_NETWORK_DAC_SLOTS_8		(1 << 12)
#घोषणा SSI_NETWORK_DAC_SLOTS_4		(2 << 12)
#घोषणा SSI_NETWORK_DAC_SLOTS_2		(3 << 12)
#घोषणा SSI_NETWORK_DAC_SLOT_MASK	(3 << 12)
#घोषणा SSI_NETWORK_DAC_RXSLOT_0_1	(0 << 14)
#घोषणा SSI_NETWORK_DAC_RXSLOT_2_3	(1 << 14)
#घोषणा SSI_NETWORK_DAC_RXSLOT_4_5	(2 << 14)
#घोषणा SSI_NETWORK_DAC_RXSLOT_6_7	(3 << 14)
#घोषणा SSI_NETWORK_DAC_RXSLOT_MASK	(3 << 14)
#घोषणा SSI_NETWORK_STDCRXSECSLOT(x)	(((x) & 0x3) << 16)
#घोषणा SSI_NETWORK_STDCRXSECGAIN(x)	(((x) & 0x3) << 18)
#घोषणा SSI_NETWORK_STDCSUMGAIN		(1 << 20)

/*
 * MC13783_AUDIO_CODEC and MC13783_AUDIO_DAC mostly share the same
 * रेजिस्टर layout
 */
#घोषणा AUDIO_SSI_SEL			(1 << 0)
#घोषणा AUDIO_CLK_SEL			(1 << 1)
#घोषणा AUDIO_CSM			(1 << 2)
#घोषणा AUDIO_BCL_INV			(1 << 3)
#घोषणा AUDIO_CFS_INV			(1 << 4)
#घोषणा AUDIO_CFS(x)			(((x) & 0x3) << 5)
#घोषणा AUDIO_CLK(x)			(((x) & 0x7) << 7)
#घोषणा AUDIO_C_EN			(1 << 11)
#घोषणा AUDIO_C_CLK_EN			(1 << 12)
#घोषणा AUDIO_C_RESET			(1 << 15)

#घोषणा AUDIO_CODEC_CDCFS8K16K		(1 << 10)
#घोषणा AUDIO_DAC_CFS_DLY_B		(1 << 10)

काष्ठा mc13783_priv अणु
	काष्ठा mc13xxx *mc13xxx;
	काष्ठा regmap *regmap;

	क्रमागत mc13783_ssi_port adc_ssi_port;
	क्रमागत mc13783_ssi_port dac_ssi_port;
पूर्ण;

/* Mapping between sample rates and रेजिस्टर value */
अटल अचिन्हित पूर्णांक mc13783_rates[] = अणु
	8000, 11025, 12000, 16000,
	22050, 24000, 32000, 44100,
	48000, 64000, 96000
पूर्ण;

अटल पूर्णांक mc13783_pcm_hw_params_dac(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक rate = params_rate(params);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mc13783_rates); i++) अणु
		अगर (rate == mc13783_rates[i]) अणु
			snd_soc_component_update_bits(component, MC13783_AUDIO_DAC,
					0xf << 17, i << 17);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mc13783_pcm_hw_params_codec(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक val;

	चयन (rate) अणु
	हाल 8000:
		val = 0;
		अवरोध;
	हाल 16000:
		val = AUDIO_CODEC_CDCFS8K16K;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, MC13783_AUDIO_CODEC, AUDIO_CODEC_CDCFS8K16K,
			val);

	वापस 0;
पूर्ण

अटल पूर्णांक mc13783_pcm_hw_params_sync(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस mc13783_pcm_hw_params_dac(substream, params, dai);
	अन्यथा
		वापस mc13783_pcm_hw_params_codec(substream, params, dai);
पूर्ण

अटल पूर्णांक mc13783_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt,
			अचिन्हित पूर्णांक reg)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक val = 0;
	अचिन्हित पूर्णांक mask = AUDIO_CFS(3) | AUDIO_BCL_INV | AUDIO_CFS_INV |
				AUDIO_CSM | AUDIO_C_CLK_EN | AUDIO_C_RESET;


	/* DAI mode */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		val |= AUDIO_CFS(2);
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		val |= AUDIO_CFS(1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* DAI घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		val |= AUDIO_BCL_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		val |= AUDIO_BCL_INV | AUDIO_CFS_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		val |= AUDIO_CFS_INV;
		अवरोध;
	पूर्ण

	/* DAI घड़ी master masks */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		val |= AUDIO_C_CLK_EN;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		val |= AUDIO_CSM;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
	हाल SND_SOC_DAIFMT_CBS_CFM:
		वापस -EINVAL;
	पूर्ण

	val |= AUDIO_C_RESET;

	snd_soc_component_update_bits(component, reg, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक mc13783_set_fmt_async(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	अगर (dai->id == MC13783_ID_STEREO_DAC)
		वापस mc13783_set_fmt(dai, fmt, MC13783_AUDIO_DAC);
	अन्यथा
		वापस mc13783_set_fmt(dai, fmt, MC13783_AUDIO_CODEC);
पूर्ण

अटल पूर्णांक mc13783_set_fmt_sync(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	पूर्णांक ret;

	ret = mc13783_set_fmt(dai, fmt, MC13783_AUDIO_DAC);
	अगर (ret)
		वापस ret;

	/*
	 * In synchronous mode क्रमce the voice codec पूर्णांकo slave mode
	 * so that the घड़ी / framesync from the stereo DAC is used
	 */
	fmt &= ~SND_SOC_DAIFMT_MASTER_MASK;
	fmt |= SND_SOC_DAIFMT_CBS_CFS;
	ret = mc13783_set_fmt(dai, fmt, MC13783_AUDIO_CODEC);

	वापस ret;
पूर्ण

अटल पूर्णांक mc13783_sysclk[] = अणु
	13000000,
	15360000,
	16800000,
	-1,
	26000000,
	-1, /* 12000000, invalid क्रम voice codec */
	-1, /* 3686400, invalid क्रम voice codec */
	33600000,
पूर्ण;

अटल पूर्णांक mc13783_set_sysclk(काष्ठा snd_soc_dai *dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir,
				  अचिन्हित पूर्णांक reg)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक clk;
	अचिन्हित पूर्णांक val = 0;
	अचिन्हित पूर्णांक mask = AUDIO_CLK(0x7) | AUDIO_CLK_SEL;

	क्रम (clk = 0; clk < ARRAY_SIZE(mc13783_sysclk); clk++) अणु
		अगर (mc13783_sysclk[clk] < 0)
			जारी;
		अगर (mc13783_sysclk[clk] == freq)
			अवरोध;
	पूर्ण

	अगर (clk == ARRAY_SIZE(mc13783_sysclk))
		वापस -EINVAL;

	अगर (clk_id == MC13783_CLK_CLIB)
		val |= AUDIO_CLK_SEL;

	val |= AUDIO_CLK(clk);

	snd_soc_component_update_bits(component, reg, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक mc13783_set_sysclk_dac(काष्ठा snd_soc_dai *dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	वापस mc13783_set_sysclk(dai, clk_id, freq, dir, MC13783_AUDIO_DAC);
पूर्ण

अटल पूर्णांक mc13783_set_sysclk_codec(काष्ठा snd_soc_dai *dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	वापस mc13783_set_sysclk(dai, clk_id, freq, dir, MC13783_AUDIO_CODEC);
पूर्ण

अटल पूर्णांक mc13783_set_sysclk_sync(काष्ठा snd_soc_dai *dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	पूर्णांक ret;

	ret = mc13783_set_sysclk(dai, clk_id, freq, dir, MC13783_AUDIO_DAC);
	अगर (ret)
		वापस ret;

	वापस mc13783_set_sysclk(dai, clk_id, freq, dir, MC13783_AUDIO_CODEC);
पूर्ण

अटल पूर्णांक mc13783_set_tdm_slot_dac(काष्ठा snd_soc_dai *dai,
	अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask, पूर्णांक slots,
	पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक val = 0;
	अचिन्हित पूर्णांक mask = SSI_NETWORK_DAC_SLOT_MASK |
				SSI_NETWORK_DAC_RXSLOT_MASK;

	चयन (slots) अणु
	हाल 2:
		val |= SSI_NETWORK_DAC_SLOTS_2;
		अवरोध;
	हाल 4:
		val |= SSI_NETWORK_DAC_SLOTS_4;
		अवरोध;
	हाल 8:
		val |= SSI_NETWORK_DAC_SLOTS_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (rx_mask) अणु
	हाल 0x03:
		val |= SSI_NETWORK_DAC_RXSLOT_0_1;
		अवरोध;
	हाल 0x0c:
		val |= SSI_NETWORK_DAC_RXSLOT_2_3;
		अवरोध;
	हाल 0x30:
		val |= SSI_NETWORK_DAC_RXSLOT_4_5;
		अवरोध;
	हाल 0xc0:
		val |= SSI_NETWORK_DAC_RXSLOT_6_7;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, MC13783_SSI_NETWORK, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक mc13783_set_tdm_slot_codec(काष्ठा snd_soc_dai *dai,
	अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask, पूर्णांक slots,
	पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक val = 0;
	अचिन्हित पूर्णांक mask = 0x3f;

	अगर (slots != 4)
		वापस -EINVAL;

	अगर (tx_mask != 0x3)
		वापस -EINVAL;

	val |= (0x00 << 2);	/* primary बारlot RX/TX(?) is 0 */
	val |= (0x01 << 4);	/* secondary बारlot TX is 1 */

	snd_soc_component_update_bits(component, MC13783_SSI_NETWORK, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक mc13783_set_tdm_slot_sync(काष्ठा snd_soc_dai *dai,
	अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask, पूर्णांक slots,
	पूर्णांक slot_width)
अणु
	पूर्णांक ret;

	ret = mc13783_set_tdm_slot_dac(dai, tx_mask, rx_mask, slots,
			slot_width);
	अगर (ret)
		वापस ret;

	ret = mc13783_set_tdm_slot_codec(dai, tx_mask, rx_mask, slots,
			slot_width);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mc1l_amp_ctl =
	SOC_DAPM_SINGLE("Switch", MC13783_AUDIO_TX, 7, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new mc1r_amp_ctl =
	SOC_DAPM_SINGLE("Switch", MC13783_AUDIO_TX, 5, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new mc2_amp_ctl =
	SOC_DAPM_SINGLE("Switch", MC13783_AUDIO_TX, 9, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new atx_amp_ctl =
	SOC_DAPM_SINGLE("Switch", MC13783_AUDIO_TX, 11, 1, 0);


/* Virtual mux. The chip करोes the input selection स्वतःmatically
 * as soon as we enable one input. */
अटल स्थिर अक्षर * स्थिर adcl_क्रमागत_text[] = अणु
	"MC1L", "RXINL",
पूर्ण;

अटल SOC_ENUM_SINGLE_VIRT_DECL(adcl_क्रमागत, adcl_क्रमागत_text);

अटल स्थिर काष्ठा snd_kcontrol_new left_input_mux =
	SOC_DAPM_ENUM("Route", adcl_क्रमागत);

अटल स्थिर अक्षर * स्थिर adcr_क्रमागत_text[] = अणु
	"MC1R", "MC2", "RXINR", "TXIN",
पूर्ण;

अटल SOC_ENUM_SINGLE_VIRT_DECL(adcr_क्रमागत, adcr_क्रमागत_text);

अटल स्थिर काष्ठा snd_kcontrol_new right_input_mux =
	SOC_DAPM_ENUM("Route", adcr_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new samp_ctl =
	SOC_DAPM_SINGLE("Switch", MC13783_AUDIO_RX0, 3, 1, 0);

अटल स्थिर अक्षर * स्थिर speaker_amp_source_text[] = अणु
	"CODEC", "Right"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(speaker_amp_source, MC13783_AUDIO_RX0, 4,
			    speaker_amp_source_text);
अटल स्थिर काष्ठा snd_kcontrol_new speaker_amp_source_mux =
	SOC_DAPM_ENUM("Speaker Amp Source MUX", speaker_amp_source);

अटल स्थिर अक्षर * स्थिर headset_amp_source_text[] = अणु
	"CODEC", "Mixer"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(headset_amp_source, MC13783_AUDIO_RX0, 11,
			    headset_amp_source_text);
अटल स्थिर काष्ठा snd_kcontrol_new headset_amp_source_mux =
	SOC_DAPM_ENUM("Headset Amp Source MUX", headset_amp_source);

अटल स्थिर काष्ठा snd_kcontrol_new cdcout_ctl =
	SOC_DAPM_SINGLE("Switch", MC13783_AUDIO_RX0, 18, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new adc_bypass_ctl =
	SOC_DAPM_SINGLE("Switch", MC13783_AUDIO_CODEC, 16, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new lamp_ctl =
	SOC_DAPM_SINGLE("Switch", MC13783_AUDIO_RX0, 5, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new hlamp_ctl =
	SOC_DAPM_SINGLE("Switch", MC13783_AUDIO_RX0, 10, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new hramp_ctl =
	SOC_DAPM_SINGLE("Switch", MC13783_AUDIO_RX0, 9, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new llamp_ctl =
	SOC_DAPM_SINGLE("Switch", MC13783_AUDIO_RX0, 16, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new lramp_ctl =
	SOC_DAPM_SINGLE("Switch", MC13783_AUDIO_RX0, 15, 1, 0);

अटल स्थिर काष्ठा snd_soc_dapm_widget mc13783_dapm_widमाला_लो[] = अणु
/* Input */
	SND_SOC_DAPM_INPUT("MC1LIN"),
	SND_SOC_DAPM_INPUT("MC1RIN"),
	SND_SOC_DAPM_INPUT("MC2IN"),
	SND_SOC_DAPM_INPUT("RXINR"),
	SND_SOC_DAPM_INPUT("RXINL"),
	SND_SOC_DAPM_INPUT("TXIN"),

	SND_SOC_DAPM_SUPPLY("MC1 Bias", MC13783_AUDIO_TX, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MC2 Bias", MC13783_AUDIO_TX, 1, 0, शून्य, 0),

	SND_SOC_DAPM_SWITCH("MC1L Amp", MC13783_AUDIO_TX, 7, 0, &mc1l_amp_ctl),
	SND_SOC_DAPM_SWITCH("MC1R Amp", MC13783_AUDIO_TX, 5, 0, &mc1r_amp_ctl),
	SND_SOC_DAPM_SWITCH("MC2 Amp", MC13783_AUDIO_TX, 9, 0, &mc2_amp_ctl),
	SND_SOC_DAPM_SWITCH("TXIN Amp", MC13783_AUDIO_TX, 11, 0, &atx_amp_ctl),

	SND_SOC_DAPM_MUX("PGA Left Input Mux", SND_SOC_NOPM, 0, 0,
			      &left_input_mux),
	SND_SOC_DAPM_MUX("PGA Right Input Mux", SND_SOC_NOPM, 0, 0,
			      &right_input_mux),

	SND_SOC_DAPM_MUX("Speaker Amp Source MUX", SND_SOC_NOPM, 0, 0,
			 &speaker_amp_source_mux),

	SND_SOC_DAPM_MUX("Headset Amp Source MUX", SND_SOC_NOPM, 0, 0,
			 &headset_amp_source_mux),

	SND_SOC_DAPM_PGA("PGA Left Input", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PGA Right Input", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_ADC("ADC", "Capture", MC13783_AUDIO_CODEC, 11, 0),
	SND_SOC_DAPM_SUPPLY("ADC_Reset", MC13783_AUDIO_CODEC, 15, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("Voice CODEC PGA", MC13783_AUDIO_RX1, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SWITCH("Voice CODEC Bypass", MC13783_AUDIO_CODEC, 16, 0,
			&adc_bypass_ctl),

/* Output */
	SND_SOC_DAPM_SUPPLY("DAC_E", MC13783_AUDIO_DAC, 11, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC_Reset", MC13783_AUDIO_DAC, 15, 0, शून्य, 0),
	SND_SOC_DAPM_OUTPUT("RXOUTL"),
	SND_SOC_DAPM_OUTPUT("RXOUTR"),
	SND_SOC_DAPM_OUTPUT("HSL"),
	SND_SOC_DAPM_OUTPUT("HSR"),
	SND_SOC_DAPM_OUTPUT("LSPL"),
	SND_SOC_DAPM_OUTPUT("LSP"),
	SND_SOC_DAPM_OUTPUT("SP"),
	SND_SOC_DAPM_OUTPUT("CDCOUT"),

	SND_SOC_DAPM_SWITCH("CDCOUT Switch", MC13783_AUDIO_RX0, 18, 0,
			&cdcout_ctl),
	SND_SOC_DAPM_SWITCH("Speaker Amp Switch", MC13783_AUDIO_RX0, 3, 0,
			&samp_ctl),
	SND_SOC_DAPM_SWITCH("Loudspeaker Amp", SND_SOC_NOPM, 0, 0, &lamp_ctl),
	SND_SOC_DAPM_SWITCH("Headset Amp Left", MC13783_AUDIO_RX0, 10, 0,
			&hlamp_ctl),
	SND_SOC_DAPM_SWITCH("Headset Amp Right", MC13783_AUDIO_RX0, 9, 0,
			&hramp_ctl),
	SND_SOC_DAPM_SWITCH("Line out Amp Left", MC13783_AUDIO_RX0, 16, 0,
			&llamp_ctl),
	SND_SOC_DAPM_SWITCH("Line out Amp Right", MC13783_AUDIO_RX0, 15, 0,
			&lramp_ctl),
	SND_SOC_DAPM_DAC("DAC", "Playback", MC13783_AUDIO_RX0, 22, 0),
	SND_SOC_DAPM_PGA("DAC PGA", MC13783_AUDIO_RX1, 5, 0, शून्य, 0),
पूर्ण;

अटल काष्ठा snd_soc_dapm_route mc13783_routes[] = अणु
/* Input */
	अणु "MC1L Amp", शून्य, "MC1LIN"पूर्ण,
	अणु "MC1R Amp", शून्य, "MC1RIN" पूर्ण,
	अणु "MC2 Amp", शून्य, "MC2IN" पूर्ण,
	अणु "TXIN Amp", शून्य, "TXIN"पूर्ण,

	अणु "PGA Left Input Mux", "MC1L", "MC1L Amp" पूर्ण,
	अणु "PGA Left Input Mux", "RXINL", "RXINL"पूर्ण,
	अणु "PGA Right Input Mux", "MC1R", "MC1R Amp" पूर्ण,
	अणु "PGA Right Input Mux", "MC2",  "MC2 Amp"पूर्ण,
	अणु "PGA Right Input Mux", "TXIN", "TXIN Amp"पूर्ण,
	अणु "PGA Right Input Mux", "RXINR", "RXINR"पूर्ण,

	अणु "PGA Left Input", शून्य, "PGA Left Input Mux"पूर्ण,
	अणु "PGA Right Input", शून्य, "PGA Right Input Mux"पूर्ण,

	अणु "ADC", शून्य, "PGA Left Input"पूर्ण,
	अणु "ADC", शून्य, "PGA Right Input"पूर्ण,
	अणु "ADC", शून्य, "ADC_Reset"पूर्ण,

	अणु "Voice CODEC PGA", "Voice CODEC Bypass", "ADC" पूर्ण,

	अणु "Speaker Amp Source MUX", "CODEC", "Voice CODEC PGA"पूर्ण,
	अणु "Speaker Amp Source MUX", "Right", "DAC PGA"पूर्ण,

	अणु "Headset Amp Source MUX", "CODEC", "Voice CODEC PGA"पूर्ण,
	अणु "Headset Amp Source MUX", "Mixer", "DAC PGA"पूर्ण,

/* Output */
	अणु "HSL", शून्य, "Headset Amp Left" पूर्ण,
	अणु "HSR", शून्य, "Headset Amp Right"पूर्ण,
	अणु "RXOUTL", शून्य, "Line out Amp Left"पूर्ण,
	अणु "RXOUTR", शून्य, "Line out Amp Right"पूर्ण,
	अणु "SP", "Speaker Amp Switch", "Speaker Amp Source MUX"पूर्ण,
	अणु "LSP", "Loudspeaker Amp", "Speaker Amp Source MUX"पूर्ण,
	अणु "HSL", "Headset Amp Left", "Headset Amp Source MUX"पूर्ण,
	अणु "HSR", "Headset Amp Right", "Headset Amp Source MUX"पूर्ण,
	अणु "Line out Amp Left", शून्य, "DAC PGA"पूर्ण,
	अणु "Line out Amp Right", शून्य, "DAC PGA"पूर्ण,
	अणु "DAC PGA", शून्य, "DAC"पूर्ण,
	अणु "DAC", शून्य, "DAC_E"पूर्ण,
	अणु "CDCOUT", "CDCOUT Switch", "Voice CODEC PGA"पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mc13783_3d_mixer[] = अणु"Stereo", "Phase Mix",
						"Mono", "Mono Mix"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(mc13783_क्रमागत_3d_mixer,
			    MC13783_AUDIO_RX1, 16,
			    mc13783_3d_mixer);

अटल काष्ठा snd_kcontrol_new mc13783_control_list[] = अणु
	SOC_SINGLE("Loudspeaker enable", MC13783_AUDIO_RX0, 5, 1, 0),
	SOC_SINGLE("PCM Playback Volume", MC13783_AUDIO_RX1, 6, 15, 0),
	SOC_SINGLE("PCM Playback Switch", MC13783_AUDIO_RX1, 5, 1, 0),
	SOC_DOUBLE("PCM Capture Volume", MC13783_AUDIO_TX, 19, 14, 31, 0),
	SOC_ENUM("3D Control", mc13783_क्रमागत_3d_mixer),

	SOC_SINGLE("CDCOUT Switch", MC13783_AUDIO_RX0, 18, 1, 0),
	SOC_SINGLE("Earpiece Amp Switch", MC13783_AUDIO_RX0, 3, 1, 0),
	SOC_DOUBLE("Headset Amp Switch", MC13783_AUDIO_RX0, 10, 9, 1, 0),
	SOC_DOUBLE("Line out Amp Switch", MC13783_AUDIO_RX0, 16, 15, 1, 0),

	SOC_SINGLE("PCM Capture Mixin Switch", MC13783_AUDIO_RX0, 22, 1, 0),
	SOC_SINGLE("Line in Capture Mixin Switch", MC13783_AUDIO_RX0, 23, 1, 0),

	SOC_SINGLE("CODEC Capture Volume", MC13783_AUDIO_RX1, 1, 15, 0),
	SOC_SINGLE("CODEC Capture Mixin Switch", MC13783_AUDIO_RX0, 21, 1, 0),

	SOC_SINGLE("Line in Capture Volume", MC13783_AUDIO_RX1, 12, 15, 0),
	SOC_SINGLE("Line in Capture Switch", MC13783_AUDIO_RX1, 10, 1, 0),

	SOC_SINGLE("MC1 Capture Bias Switch", MC13783_AUDIO_TX, 0, 1, 0),
	SOC_SINGLE("MC2 Capture Bias Switch", MC13783_AUDIO_TX, 1, 1, 0),
पूर्ण;

अटल पूर्णांक mc13783_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा mc13783_priv *priv = snd_soc_component_get_drvdata(component);

	snd_soc_component_init_regmap(component,
				  dev_get_regmap(component->dev->parent, शून्य));

	/* these are the reset values */
	mc13xxx_reg_ग_लिखो(priv->mc13xxx, MC13783_AUDIO_RX0, 0x25893);
	mc13xxx_reg_ग_लिखो(priv->mc13xxx, MC13783_AUDIO_RX1, 0x00d35A);
	mc13xxx_reg_ग_लिखो(priv->mc13xxx, MC13783_AUDIO_TX, 0x420000);
	mc13xxx_reg_ग_लिखो(priv->mc13xxx, MC13783_SSI_NETWORK, 0x013060);
	mc13xxx_reg_ग_लिखो(priv->mc13xxx, MC13783_AUDIO_CODEC, 0x180027);
	mc13xxx_reg_ग_लिखो(priv->mc13xxx, MC13783_AUDIO_DAC, 0x0e0004);

	अगर (priv->adc_ssi_port == MC13783_SSI1_PORT)
		mc13xxx_reg_rmw(priv->mc13xxx, MC13783_AUDIO_CODEC,
				AUDIO_SSI_SEL, 0);
	अन्यथा
		mc13xxx_reg_rmw(priv->mc13xxx, MC13783_AUDIO_CODEC,
				AUDIO_SSI_SEL, AUDIO_SSI_SEL);

	अगर (priv->dac_ssi_port == MC13783_SSI1_PORT)
		mc13xxx_reg_rmw(priv->mc13xxx, MC13783_AUDIO_DAC,
				AUDIO_SSI_SEL, 0);
	अन्यथा
		mc13xxx_reg_rmw(priv->mc13xxx, MC13783_AUDIO_DAC,
				AUDIO_SSI_SEL, AUDIO_SSI_SEL);

	वापस 0;
पूर्ण

अटल व्योम mc13783_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा mc13783_priv *priv = snd_soc_component_get_drvdata(component);

	/* Make sure VAUDIOON is off */
	mc13xxx_reg_rmw(priv->mc13xxx, MC13783_AUDIO_RX0, 0x3, 0);
पूर्ण

#घोषणा MC13783_RATES_RECORD (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000)

#घोषणा MC13783_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
	SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops mc13783_ops_dac = अणु
	.hw_params	= mc13783_pcm_hw_params_dac,
	.set_fmt	= mc13783_set_fmt_async,
	.set_sysclk	= mc13783_set_sysclk_dac,
	.set_tdm_slot	= mc13783_set_tdm_slot_dac,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops mc13783_ops_codec = अणु
	.hw_params	= mc13783_pcm_hw_params_codec,
	.set_fmt	= mc13783_set_fmt_async,
	.set_sysclk	= mc13783_set_sysclk_codec,
	.set_tdm_slot	= mc13783_set_tdm_slot_codec,
पूर्ण;

/*
 * The mc13783 has two SSI ports, both of them can be routed either
 * to the voice codec or the stereo DAC. When two dअगरferent SSI ports
 * are used क्रम the voice codec and the stereo DAC we can करो dअगरferent
 * क्रमmats and sysघड़ी settings क्रम playback and capture
 * (mc13783-hअगरi-playback and mc13783-hअगरi-capture). Using the same port
 * क्रमces us to use symmetric rates (mc13783-hअगरi).
 */
अटल काष्ठा snd_soc_dai_driver mc13783_dai_async[] = अणु
	अणु
		.name = "mc13783-hifi-playback",
		.id = MC13783_ID_STEREO_DAC,
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_96000,
			.क्रमmats = MC13783_FORMATS,
		पूर्ण,
		.ops = &mc13783_ops_dac,
	पूर्ण, अणु
		.name = "mc13783-hifi-capture",
		.id = MC13783_ID_STEREO_CODEC,
		.capture = अणु
			.stream_name = "Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = MC13783_RATES_RECORD,
			.क्रमmats = MC13783_FORMATS,
		पूर्ण,
		.ops = &mc13783_ops_codec,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops mc13783_ops_sync = अणु
	.hw_params	= mc13783_pcm_hw_params_sync,
	.set_fmt	= mc13783_set_fmt_sync,
	.set_sysclk	= mc13783_set_sysclk_sync,
	.set_tdm_slot	= mc13783_set_tdm_slot_sync,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver mc13783_dai_sync[] = अणु
	अणु
		.name = "mc13783-hifi",
		.id = MC13783_ID_SYNC,
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_96000,
			.क्रमmats = MC13783_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = MC13783_RATES_RECORD,
			.क्रमmats = MC13783_FORMATS,
		पूर्ण,
		.ops = &mc13783_ops_sync,
		.symmetric_rate = 1,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_mc13783 = अणु
	.probe			= mc13783_probe,
	.हटाओ			= mc13783_हटाओ,
	.controls		= mc13783_control_list,
	.num_controls		= ARRAY_SIZE(mc13783_control_list),
	.dapm_widमाला_लो		= mc13783_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(mc13783_dapm_widमाला_लो),
	.dapm_routes		= mc13783_routes,
	.num_dapm_routes	= ARRAY_SIZE(mc13783_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक __init mc13783_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mc13783_priv *priv;
	काष्ठा mc13xxx_codec_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा device_node *np;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (pdata) अणु
		priv->adc_ssi_port = pdata->adc_ssi_port;
		priv->dac_ssi_port = pdata->dac_ssi_port;
	पूर्ण अन्यथा अणु
		np = of_get_child_by_name(pdev->dev.parent->of_node, "codec");
		अगर (!np)
			वापस -ENOSYS;

		ret = of_property_पढ़ो_u32(np, "adc-port", &priv->adc_ssi_port);
		अगर (ret) अणु
			of_node_put(np);
			वापस ret;
		पूर्ण

		ret = of_property_पढ़ो_u32(np, "dac-port", &priv->dac_ssi_port);
		अगर (ret) अणु
			of_node_put(np);
			वापस ret;
		पूर्ण

		of_node_put(np);
	पूर्ण

	dev_set_drvdata(&pdev->dev, priv);
	priv->mc13xxx = dev_get_drvdata(pdev->dev.parent);

	अगर (priv->adc_ssi_port == priv->dac_ssi_port)
		ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &soc_component_dev_mc13783,
			mc13783_dai_sync, ARRAY_SIZE(mc13783_dai_sync));
	अन्यथा
		ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &soc_component_dev_mc13783,
			mc13783_dai_async, ARRAY_SIZE(mc13783_dai_async));

	वापस ret;
पूर्ण

अटल पूर्णांक mc13783_codec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mc13783_codec_driver = अणु
	.driver = अणु
		.name	= "mc13783-codec",
	पूर्ण,
	.हटाओ = mc13783_codec_हटाओ,
पूर्ण;
module_platक्रमm_driver_probe(mc13783_codec_driver, mc13783_codec_probe);

MODULE_DESCRIPTION("ASoC MC13783 driver");
MODULE_AUTHOR("Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>");
MODULE_AUTHOR("Philippe Retornaz <philippe.retornaz@epfl.ch>");
MODULE_LICENSE("GPL");
