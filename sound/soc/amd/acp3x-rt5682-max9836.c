<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Machine driver क्रम AMD ACP Audio engine using DA7219 & MAX98357 codec.
//
//Copyright 2016 Advanced Micro Devices, Inc.

#समावेश <sound/core.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/jack.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पन.स>
#समावेश <linux/acpi.h>

#समावेश "raven/acp3x.h"
#समावेश "../codecs/rt5682.h"
#समावेश "../codecs/rt1015.h"

#घोषणा PCO_PLAT_CLK 48000000
#घोषणा RT5682_PLL_FREQ (48000 * 512)
#घोषणा DUAL_CHANNEL		2

अटल काष्ठा snd_soc_jack pco_jack;
अटल काष्ठा clk *rt5682_dai_wclk;
अटल काष्ठा clk *rt5682_dai_bclk;
अटल काष्ठा gpio_desc *dmic_sel;
व्योम *soc_is_rltk_max(काष्ठा device *dev);

क्रमागत अणु
	RT5682 = 0,
	MAX,
	EC,
पूर्ण;

अटल पूर्णांक acp3x_5682_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_component *component = codec_dai->component;

	dev_info(rtd->dev, "codec dai name = %s\n", codec_dai->name);

	/* set rt5682 dai fmt */
	ret =  snd_soc_dai_set_fmt(codec_dai, SND_SOC_DAIFMT_I2S
			| SND_SOC_DAIFMT_NB_NF
			| SND_SOC_DAIFMT_CBM_CFM);
	अगर (ret < 0) अणु
		dev_err(rtd->card->dev,
				"Failed to set rt5682 dai fmt: %d\n", ret);
		वापस ret;
	पूर्ण

	/* set codec PLL */
	ret = snd_soc_dai_set_pll(codec_dai, RT5682_PLL2, RT5682_PLL2_S_MCLK,
				  PCO_PLAT_CLK, RT5682_PLL_FREQ);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set rt5682 PLL: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Set codec sysclk */
	ret = snd_soc_dai_set_sysclk(codec_dai, RT5682_SCLK_S_PLL2,
			RT5682_PLL_FREQ, SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(rtd->dev,
			"Failed to set rt5682 SYSCLK: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Set tdm/i2s1 master bclk ratio */
	ret = snd_soc_dai_set_bclk_ratio(codec_dai, 64);
	अगर (ret < 0) अणु
		dev_err(rtd->dev,
			"Failed to set rt5682 tdm bclk ratio: %d\n", ret);
		वापस ret;
	पूर्ण

	rt5682_dai_wclk = clk_get(component->dev, "rt5682-dai-wclk");
	rt5682_dai_bclk = clk_get(component->dev, "rt5682-dai-bclk");

	ret = snd_soc_card_jack_new(card, "Headset Jack",
				SND_JACK_HEADSET | SND_JACK_LINEOUT |
				SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				SND_JACK_BTN_2 | SND_JACK_BTN_3,
				&pco_jack, शून्य, 0);
	अगर (ret) अणु
		dev_err(card->dev, "HP jack creation failed %d\n", ret);
		वापस ret;
	पूर्ण

	snd_jack_set_key(pco_jack.jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(pco_jack.jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(pco_jack.jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
	snd_jack_set_key(pco_jack.jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);

	ret = snd_soc_component_set_jack(component, &pco_jack, शून्य);
	अगर (ret) अणु
		dev_err(rtd->dev, "Headset Jack call-back failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rt5682_clk_enable(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	/* RT5682 will support only 48K output with 48M mclk */
	clk_set_rate(rt5682_dai_wclk, 48000);
	clk_set_rate(rt5682_dai_bclk, 48000 * 64);
	ret = clk_prepare_enable(rt5682_dai_wclk);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't enable wclk %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक acp3x_1015_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक srate, i, ret;

	ret = 0;
	srate = params_rate(params);

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		अगर (म_भेद(codec_dai->name, "rt1015-aif"))
			जारी;

		ret = snd_soc_dai_set_pll(codec_dai, 0, RT1015_PLL_S_BCLK,
						64 * srate, 256 * srate);
		अगर (ret < 0)
			वापस ret;
		ret = snd_soc_dai_set_sysclk(codec_dai, RT1015_SCLK_S_PLL,
					256 * srate, SND_SOC_CLOCK_IN);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम rt5682_clk_disable(व्योम)
अणु
	clk_disable_unprepare(rt5682_dai_wclk);
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक channels[] = अणु
	DUAL_CHANNEL,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
	48000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_rates = अणु
	.count = ARRAY_SIZE(rates),
	.list  = rates,
	.mask = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels = अणु
	.count = ARRAY_SIZE(channels),
	.list = channels,
	.mask = 0,
पूर्ण;

अटल पूर्णांक acp3x_5682_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा acp3x_platक्रमm_info *machine = snd_soc_card_get_drvdata(card);

	machine->play_i2s_instance = I2S_SP_INSTANCE;
	machine->cap_i2s_instance = I2S_SP_INSTANCE;

	runसमय->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				   &स्थिरraपूर्णांकs_channels);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &स्थिरraपूर्णांकs_rates);
	वापस rt5682_clk_enable(substream);
पूर्ण

अटल पूर्णांक acp3x_max_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा acp3x_platक्रमm_info *machine = snd_soc_card_get_drvdata(card);

	machine->play_i2s_instance = I2S_BT_INSTANCE;

	runसमय->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				   &स्थिरraपूर्णांकs_channels);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &स्थिरraपूर्णांकs_rates);
	वापस rt5682_clk_enable(substream);
पूर्ण

अटल पूर्णांक acp3x_ec_dmic0_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा acp3x_platक्रमm_info *machine = snd_soc_card_get_drvdata(card);

	machine->cap_i2s_instance = I2S_BT_INSTANCE;
	snd_soc_dai_set_bclk_ratio(codec_dai, 64);

	वापस rt5682_clk_enable(substream);
पूर्ण

अटल पूर्णांक dmic_चयन;

अटल पूर्णांक dmic_get(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = dmic_चयन;
	वापस 0;
पूर्ण

अटल पूर्णांक dmic_set(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अगर (dmic_sel) अणु
		dmic_चयन = ucontrol->value.पूर्णांकeger.value[0];
		gpiod_set_value(dmic_sel, dmic_चयन);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम rt5682_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	rt5682_clk_disable();
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops acp3x_5682_ops = अणु
	.startup = acp3x_5682_startup,
	.shutकरोwn = rt5682_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops acp3x_max_play_ops = अणु
	.startup = acp3x_max_startup,
	.shutकरोwn = rt5682_shutकरोwn,
	.hw_params = acp3x_1015_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops acp3x_ec_cap0_ops = अणु
	.startup = acp3x_ec_dmic0_startup,
	.shutकरोwn = rt5682_shutकरोwn,
पूर्ण;

SND_SOC_DAILINK_DEF(acp3x_i2s,
	DAILINK_COMP_ARRAY(COMP_CPU("acp3x_i2s_playcap.0")));
SND_SOC_DAILINK_DEF(acp3x_bt,
	DAILINK_COMP_ARRAY(COMP_CPU("acp3x_i2s_playcap.2")));

SND_SOC_DAILINK_DEF(rt5682,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-10EC5682:00", "rt5682-aif1")));
SND_SOC_DAILINK_DEF(max,
	DAILINK_COMP_ARRAY(COMP_CODEC("MX98357A:00", "HiFi")));
SND_SOC_DAILINK_DEF(rt1015p,
	DAILINK_COMP_ARRAY(COMP_CODEC("RTL1015:00", "HiFi")));
SND_SOC_DAILINK_DEF(rt1015,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-10EC1015:00", "rt1015-aif"),
			COMP_CODEC("i2c-10EC1015:01", "rt1015-aif")));
SND_SOC_DAILINK_DEF(cros_ec,
	DAILINK_COMP_ARRAY(COMP_CODEC("GOOG0013:00", "EC Codec I2S RX")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("acp3x_rv_i2s_dma.0")));

अटल काष्ठा snd_soc_codec_conf rt1015_conf[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF("i2c-10EC1015:00"),
		.name_prefix = "Left",
	पूर्ण,
	अणु
		.dlc = COMP_CODEC_CONF("i2c-10EC1015:01"),
		.name_prefix = "Right",
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_link acp3x_dai[] = अणु
	[RT5682] = अणु
		.name = "acp3x-5682-play",
		.stream_name = "Playback",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.init = acp3x_5682_init,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &acp3x_5682_ops,
		SND_SOC_DAILINK_REG(acp3x_i2s, rt5682, platक्रमm),
	पूर्ण,
	[MAX] = अणु
		.name = "acp3x-max98357-play",
		.stream_name = "HiFi Playback",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBS_CFS,
		.dpcm_playback = 1,
		.ops = &acp3x_max_play_ops,
		.cpus = acp3x_bt,
		.num_cpus = ARRAY_SIZE(acp3x_bt),
		.platक्रमms = platक्रमm,
		.num_platक्रमms = ARRAY_SIZE(platक्रमm),
	पूर्ण,
	[EC] = अणु
		.name = "acp3x-ec-dmic0-capture",
		.stream_name = "Capture DMIC0",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBS_CFS,
		.dpcm_capture = 1,
		.ops = &acp3x_ec_cap0_ops,
		SND_SOC_DAILINK_REG(acp3x_bt, cros_ec, platक्रमm),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dmic_mux_text[] = अणु
	"Front Mic",
	"Rear Mic",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
		acp3x_dmic_क्रमागत, SND_SOC_NOPM, 0, dmic_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new acp3x_dmic_mux_control =
	SOC_DAPM_ENUM_EXT("DMIC Select Mux", acp3x_dmic_क्रमागत,
			  dmic_get, dmic_set);

अटल स्थिर काष्ठा snd_soc_dapm_widget acp3x_5682_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_SPK("Spk", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MUX("Dmic Mux", SND_SOC_NOPM, 0, 0,
			 &acp3x_dmic_mux_control),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route acp3x_5682_audio_route[] = अणु
	अणु"Headphone Jack", शून्य, "HPOL"पूर्ण,
	अणु"Headphone Jack", शून्य, "HPOR"पूर्ण,
	अणु"IN1P", शून्य, "Headset Mic"पूर्ण,
	अणु"Spk", शून्य, "Speaker"पूर्ण,
	अणु"Dmic Mux", "Front Mic", "DMIC"पूर्ण,
	अणु"Dmic Mux", "Rear Mic", "DMIC"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new acp3x_5682_mc_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Spk"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
पूर्ण;

अटल काष्ठा snd_soc_card acp3x_5682 = अणु
	.name = "acp3xalc5682m98357",
	.owner = THIS_MODULE,
	.dai_link = acp3x_dai,
	.num_links = ARRAY_SIZE(acp3x_dai),
	.dapm_widमाला_लो = acp3x_5682_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(acp3x_5682_widमाला_लो),
	.dapm_routes = acp3x_5682_audio_route,
	.num_dapm_routes = ARRAY_SIZE(acp3x_5682_audio_route),
	.controls = acp3x_5682_mc_controls,
	.num_controls = ARRAY_SIZE(acp3x_5682_mc_controls),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget acp3x_1015_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MUX("Dmic Mux", SND_SOC_NOPM, 0, 0,
			 &acp3x_dmic_mux_control),
	SND_SOC_DAPM_SPK("Left Spk", शून्य),
	SND_SOC_DAPM_SPK("Right Spk", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route acp3x_1015_route[] = अणु
	अणु"Headphone Jack", शून्य, "HPOL"पूर्ण,
	अणु"Headphone Jack", शून्य, "HPOR"पूर्ण,
	अणु"IN1P", शून्य, "Headset Mic"पूर्ण,
	अणु"Dmic Mux", "Front Mic", "DMIC"पूर्ण,
	अणु"Dmic Mux", "Rear Mic", "DMIC"पूर्ण,
	अणु"Left Spk", शून्य, "Left SPO"पूर्ण,
	अणु"Right Spk", शून्य, "Right SPO"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new acp3x_mc_1015_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Left Spk"),
	SOC_DAPM_PIN_SWITCH("Right Spk"),
पूर्ण;

अटल काष्ठा snd_soc_card acp3x_1015 = अणु
	.name = "acp3xalc56821015",
	.owner = THIS_MODULE,
	.dai_link = acp3x_dai,
	.num_links = ARRAY_SIZE(acp3x_dai),
	.dapm_widमाला_लो = acp3x_1015_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(acp3x_1015_widमाला_लो),
	.dapm_routes = acp3x_1015_route,
	.num_dapm_routes = ARRAY_SIZE(acp3x_1015_route),
	.codec_conf = rt1015_conf,
	.num_configs = ARRAY_SIZE(rt1015_conf),
	.controls = acp3x_mc_1015_controls,
	.num_controls = ARRAY_SIZE(acp3x_mc_1015_controls),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget acp3x_1015p_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MUX("Dmic Mux", SND_SOC_NOPM, 0, 0,
			 &acp3x_dmic_mux_control),
	SND_SOC_DAPM_SPK("Speakers", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route acp3x_1015p_route[] = अणु
	अणु"Headphone Jack", शून्य, "HPOL"पूर्ण,
	अणु"Headphone Jack", शून्य, "HPOR"पूर्ण,
	अणु"IN1P", शून्य, "Headset Mic"पूर्ण,
	अणु"Dmic Mux", "Front Mic", "DMIC"पूर्ण,
	अणु"Dmic Mux", "Rear Mic", "DMIC"पूर्ण,
	/* speaker */
	अणु "Speakers", शून्य, "Speaker" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new acp3x_mc_1015p_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speakers"),
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
पूर्ण;

अटल काष्ठा snd_soc_card acp3x_1015p = अणु
	.name = "acp3xalc56821015p",
	.owner = THIS_MODULE,
	.dai_link = acp3x_dai,
	.num_links = ARRAY_SIZE(acp3x_dai),
	.dapm_widमाला_लो = acp3x_1015p_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(acp3x_1015p_widमाला_लो),
	.dapm_routes = acp3x_1015p_route,
	.num_dapm_routes = ARRAY_SIZE(acp3x_1015p_route),
	.controls = acp3x_mc_1015p_controls,
	.num_controls = ARRAY_SIZE(acp3x_mc_1015p_controls),
पूर्ण;

व्योम *soc_is_rltk_max(काष्ठा device *dev)
अणु
	स्थिर काष्ठा acpi_device_id *match;

	match = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!match)
		वापस शून्य;
	वापस (व्योम *)match->driver_data;
पूर्ण

अटल व्योम card_spk_dai_link_present(काष्ठा snd_soc_dai_link *links,
						स्थिर अक्षर *card_name)
अणु
	अगर (!म_भेद(card_name, "acp3xalc56821015")) अणु
		links[1].codecs = rt1015;
		links[1].num_codecs = ARRAY_SIZE(rt1015);
	पूर्ण अन्यथा अगर (!म_भेद(card_name, "acp3xalc56821015p")) अणु
		links[1].codecs = rt1015p;
		links[1].num_codecs = ARRAY_SIZE(rt1015p);
	पूर्ण अन्यथा अणु
		links[1].codecs = max;
		links[1].num_codecs = ARRAY_SIZE(max);
	पूर्ण
पूर्ण

अटल पूर्णांक acp3x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_card *card;
	काष्ठा acp3x_platक्रमm_info *machine;
	काष्ठा device *dev = &pdev->dev;

	card = (काष्ठा snd_soc_card *)soc_is_rltk_max(dev);
	अगर (!card)
		वापस -ENODEV;

	machine = devm_kzalloc(&pdev->dev, माप(*machine), GFP_KERNEL);
	अगर (!machine)
		वापस -ENOMEM;

	card_spk_dai_link_present(card->dai_link, card->name);
	card->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, card);
	snd_soc_card_set_drvdata(card, machine);

	dmic_sel = devm_gpiod_get(&pdev->dev, "dmic", GPIOD_OUT_LOW);
	अगर (IS_ERR(dmic_sel)) अणु
		dev_err(&pdev->dev, "DMIC gpio failed err=%ld\n",
			PTR_ERR(dmic_sel));
		वापस PTR_ERR(dmic_sel);
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"devm_snd_soc_register_card(%s) failed: %d\n",
				card->name, ret);
		अन्यथा
			dev_dbg(&pdev->dev,
				"devm_snd_soc_register_card(%s) probe deferred: %d\n",
				card->name, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id acp3x_audio_acpi_match[] = अणु
	अणु "AMDI5682", (अचिन्हित दीर्घ)&acp3x_5682पूर्ण,
	अणु "AMDI1015", (अचिन्हित दीर्घ)&acp3x_1015पूर्ण,
	अणु "10021015", (अचिन्हित दीर्घ)&acp3x_1015pपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, acp3x_audio_acpi_match);

अटल काष्ठा platक्रमm_driver acp3x_audio = अणु
	.driver = अणु
		.name = "acp3x-alc5682-max98357",
		.acpi_match_table = ACPI_PTR(acp3x_audio_acpi_match),
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = acp3x_probe,
पूर्ण;

module_platक्रमm_driver(acp3x_audio);

MODULE_AUTHOR("akshu.agrawal@amd.com");
MODULE_AUTHOR("Vishnuvardhanrao.Ravulapati@amd.com");
MODULE_AUTHOR("Vijendar.Mukunda@amd.com");
MODULE_DESCRIPTION("ALC5682 ALC1015, ALC1015P & MAX98357 audio support");
MODULE_LICENSE("GPL v2");
