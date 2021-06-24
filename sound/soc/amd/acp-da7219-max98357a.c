<शैली गुरु>
// SPDX-License-Identअगरier: MIT
//
// Machine driver क्रम AMD ACP Audio engine using DA7219, RT5682 & MAX98357 codec
//
//Copyright 2017-2021 Advanced Micro Devices, Inc.

#समावेश <sound/core.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/jack.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/acpi.h>

#समावेश "acp.h"
#समावेश "../codecs/da7219.h"
#समावेश "../codecs/da7219-aad.h"
#समावेश "../codecs/rt5682.h"

#घोषणा CZ_PLAT_CLK 48000000
#घोषणा DUAL_CHANNEL		2
#घोषणा RT5682_PLL_FREQ (48000 * 512)

अटल काष्ठा snd_soc_jack cz_jack;
अटल काष्ठा clk *da7219_dai_wclk;
अटल काष्ठा clk *da7219_dai_bclk;
अटल काष्ठा clk *rt5682_dai_wclk;
अटल काष्ठा clk *rt5682_dai_bclk;
बाह्य bool bt_uart_enable;
व्योम *acp_soc_is_rltk_max(काष्ठा device *dev);

अटल पूर्णांक cz_da7219_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_component *component = codec_dai->component;

	dev_info(rtd->dev, "codec dai name = %s\n", codec_dai->name);

	ret = snd_soc_dai_set_sysclk(codec_dai, DA7219_CLKSRC_MCLK,
				     CZ_PLAT_CLK, SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec sysclk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_pll(codec_dai, 0, DA7219_SYSCLK_PLL,
				  CZ_PLAT_CLK, DA7219_PLL_FREQ_OUT_98304);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec pll: %d\n", ret);
		वापस ret;
	पूर्ण

	da7219_dai_wclk = devm_clk_get(component->dev, "da7219-dai-wclk");
	अगर (IS_ERR(da7219_dai_wclk))
		वापस PTR_ERR(da7219_dai_wclk);

	da7219_dai_bclk = devm_clk_get(component->dev, "da7219-dai-bclk");
	अगर (IS_ERR(da7219_dai_bclk))
		वापस PTR_ERR(da7219_dai_bclk);

	ret = snd_soc_card_jack_new(card, "Headset Jack",
				SND_JACK_HEADSET | SND_JACK_LINEOUT |
				SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				SND_JACK_BTN_2 | SND_JACK_BTN_3,
				&cz_jack, शून्य, 0);
	अगर (ret) अणु
		dev_err(card->dev, "HP jack creation failed %d\n", ret);
		वापस ret;
	पूर्ण

	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_1, KEY_VOLUMEUP);
	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_2, KEY_VOLUMEDOWN);
	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_3, KEY_VOICECOMMAND);

	da7219_aad_jack_det(component, &cz_jack);

	वापस 0;
पूर्ण

अटल पूर्णांक da7219_clk_enable(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	/*
	 * Set wclk to 48000 because the rate स्थिरraपूर्णांक of this driver is
	 * 48000. ADAU7002 spec: "The ADAU7002 requires a BCLK rate that is
	 * minimum of 64x the LRCLK sample rate." DA7219 is the only clk
	 * source so क्रम all codecs we have to limit bclk to 64X lrclk.
	 */
	clk_set_rate(da7219_dai_wclk, 48000);
	clk_set_rate(da7219_dai_bclk, 48000 * 64);
	ret = clk_prepare_enable(da7219_dai_bclk);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't enable master clock %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम da7219_clk_disable(व्योम)
अणु
	clk_disable_unprepare(da7219_dai_bclk);
पूर्ण

अटल पूर्णांक cz_rt5682_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_component *component = codec_dai->component;

	dev_info(codec_dai->dev, "codec dai name = %s\n", codec_dai->name);

	/* Set codec sysclk */
	ret = snd_soc_dai_set_sysclk(codec_dai, RT5682_SCLK_S_PLL2,
				     RT5682_PLL_FREQ, SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(codec_dai->dev,
			"Failed to set rt5682 SYSCLK: %d\n", ret);
		वापस ret;
	पूर्ण
	/* set codec PLL */
	ret = snd_soc_dai_set_pll(codec_dai, RT5682_PLL2, RT5682_PLL2_S_MCLK,
				  CZ_PLAT_CLK, RT5682_PLL_FREQ);
	अगर (ret < 0) अणु
		dev_err(codec_dai->dev, "can't set rt5682 PLL: %d\n", ret);
		वापस ret;
	पूर्ण

	rt5682_dai_wclk = devm_clk_get(component->dev, "rt5682-dai-wclk");
	अगर (IS_ERR(rt5682_dai_wclk))
		वापस PTR_ERR(rt5682_dai_wclk);

	rt5682_dai_bclk = devm_clk_get(component->dev, "rt5682-dai-bclk");
	अगर (IS_ERR(rt5682_dai_bclk))
		वापस PTR_ERR(rt5682_dai_bclk);

	ret = snd_soc_card_jack_new(card, "Headset Jack",
				    SND_JACK_HEADSET | SND_JACK_LINEOUT |
				    SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				    SND_JACK_BTN_2 | SND_JACK_BTN_3,
				    &cz_jack, शून्य, 0);
	अगर (ret) अणु
		dev_err(card->dev, "HP jack creation failed %d\n", ret);
		वापस ret;
	पूर्ण

	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_1, KEY_VOLUMEUP);
	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_2, KEY_VOLUMEDOWN);
	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_3, KEY_VOICECOMMAND);

	ret = snd_soc_component_set_jack(component, &cz_jack, शून्य);
	अगर (ret) अणु
		dev_err(rtd->dev, "Headset Jack call-back failed: %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt5682_clk_enable(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	/*
	 * Set wclk to 48000 because the rate स्थिरraपूर्णांक of this driver is
	 * 48000. ADAU7002 spec: "The ADAU7002 requires a BCLK rate that is
	 * minimum of 64x the LRCLK sample rate." RT5682 is the only clk
	 * source so क्रम all codecs we have to limit bclk to 64X lrclk.
	 */
	ret = clk_set_rate(rt5682_dai_wclk, 48000);
	अगर (ret) अणु
		dev_err(rtd->dev, "Error setting wclk rate: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = clk_set_rate(rt5682_dai_bclk, 48000 * 64);
	अगर (ret) अणु
		dev_err(rtd->dev, "Error setting bclk rate: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = clk_prepare_enable(rt5682_dai_wclk);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't enable wclk %d\n", ret);
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

अटल पूर्णांक cz_da7219_play_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा acp_platक्रमm_info *machine = snd_soc_card_get_drvdata(card);

	/*
	 * On this platक्रमm क्रम PCM device we support stereo
	 */

	runसमय->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				   &स्थिरraपूर्णांकs_channels);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &स्थिरraपूर्णांकs_rates);

	machine->play_i2s_instance = I2S_SP_INSTANCE;
	वापस da7219_clk_enable(substream);
पूर्ण

अटल पूर्णांक cz_da7219_cap_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा acp_platक्रमm_info *machine = snd_soc_card_get_drvdata(card);

	/*
	 * On this platक्रमm क्रम PCM device we support stereo
	 */

	runसमय->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				   &स्थिरraपूर्णांकs_channels);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &स्थिरraपूर्णांकs_rates);

	machine->cap_i2s_instance = I2S_SP_INSTANCE;
	machine->capture_channel = CAP_CHANNEL1;
	वापस da7219_clk_enable(substream);
पूर्ण

अटल पूर्णांक cz_max_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा acp_platक्रमm_info *machine = snd_soc_card_get_drvdata(card);

	/*
	 * On this platक्रमm क्रम PCM device we support stereo
	 */

	runसमय->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				   &स्थिरraपूर्णांकs_channels);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &स्थिरraपूर्णांकs_rates);

	machine->play_i2s_instance = I2S_BT_INSTANCE;
	वापस da7219_clk_enable(substream);
पूर्ण

अटल पूर्णांक cz_dmic0_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा acp_platक्रमm_info *machine = snd_soc_card_get_drvdata(card);

	/*
	 * On this platक्रमm क्रम PCM device we support stereo
	 */

	runसमय->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				   &स्थिरraपूर्णांकs_channels);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &स्थिरraपूर्णांकs_rates);

	machine->cap_i2s_instance = I2S_BT_INSTANCE;
	वापस da7219_clk_enable(substream);
पूर्ण

अटल पूर्णांक cz_dmic1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा acp_platक्रमm_info *machine = snd_soc_card_get_drvdata(card);

	/*
	 * On this platक्रमm क्रम PCM device we support stereo
	 */

	runसमय->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				   &स्थिरraपूर्णांकs_channels);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &स्थिरraपूर्णांकs_rates);

	machine->cap_i2s_instance = I2S_SP_INSTANCE;
	machine->capture_channel = CAP_CHANNEL0;
	वापस da7219_clk_enable(substream);
पूर्ण

अटल व्योम cz_da7219_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	da7219_clk_disable();
पूर्ण

अटल पूर्णांक cz_rt5682_play_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा acp_platक्रमm_info *machine = snd_soc_card_get_drvdata(card);

	/*
	 * On this platक्रमm क्रम PCM device we support stereo
	 */

	runसमय->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				   &स्थिरraपूर्णांकs_channels);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &स्थिरraपूर्णांकs_rates);

	machine->play_i2s_instance = I2S_SP_INSTANCE;
	वापस rt5682_clk_enable(substream);
पूर्ण

अटल पूर्णांक cz_rt5682_cap_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा acp_platक्रमm_info *machine = snd_soc_card_get_drvdata(card);

	/*
	 * On this platक्रमm क्रम PCM device we support stereo
	 */

	runसमय->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				   &स्थिरraपूर्णांकs_channels);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &स्थिरraपूर्णांकs_rates);

	machine->cap_i2s_instance = I2S_SP_INSTANCE;
	machine->capture_channel = CAP_CHANNEL1;
	वापस rt5682_clk_enable(substream);
पूर्ण

अटल पूर्णांक cz_rt5682_max_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा acp_platक्रमm_info *machine = snd_soc_card_get_drvdata(card);

	/*
	 * On this platक्रमm क्रम PCM device we support stereo
	 */

	runसमय->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				   &स्थिरraपूर्णांकs_channels);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &स्थिरraपूर्णांकs_rates);

	machine->play_i2s_instance = I2S_BT_INSTANCE;
	वापस rt5682_clk_enable(substream);
पूर्ण

अटल पूर्णांक cz_rt5682_dmic0_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा acp_platक्रमm_info *machine = snd_soc_card_get_drvdata(card);

	/*
	 * On this platक्रमm क्रम PCM device we support stereo
	 */

	runसमय->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				   &स्थिरraपूर्णांकs_channels);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &स्थिरraपूर्णांकs_rates);

	machine->cap_i2s_instance = I2S_BT_INSTANCE;
	वापस rt5682_clk_enable(substream);
पूर्ण

अटल पूर्णांक cz_rt5682_dmic1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा acp_platक्रमm_info *machine = snd_soc_card_get_drvdata(card);

	/*
	 * On this platक्रमm क्रम PCM device we support stereo
	 */

	runसमय->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				   &स्थिरraपूर्णांकs_channels);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &स्थिरraपूर्णांकs_rates);

	machine->cap_i2s_instance = I2S_SP_INSTANCE;
	machine->capture_channel = CAP_CHANNEL0;
	वापस rt5682_clk_enable(substream);
पूर्ण

अटल व्योम cz_rt5682_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	rt5682_clk_disable();
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops cz_da7219_play_ops = अणु
	.startup = cz_da7219_play_startup,
	.shutकरोwn = cz_da7219_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops cz_da7219_cap_ops = अणु
	.startup = cz_da7219_cap_startup,
	.shutकरोwn = cz_da7219_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops cz_max_play_ops = अणु
	.startup = cz_max_startup,
	.shutकरोwn = cz_da7219_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops cz_dmic0_cap_ops = अणु
	.startup = cz_dmic0_startup,
	.shutकरोwn = cz_da7219_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops cz_dmic1_cap_ops = अणु
	.startup = cz_dmic1_startup,
	.shutकरोwn = cz_da7219_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops cz_rt5682_play_ops = अणु
	.startup = cz_rt5682_play_startup,
	.shutकरोwn = cz_rt5682_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops cz_rt5682_cap_ops = अणु
	.startup = cz_rt5682_cap_startup,
	.shutकरोwn = cz_rt5682_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops cz_rt5682_max_play_ops = अणु
	.startup = cz_rt5682_max_startup,
	.shutकरोwn = cz_rt5682_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops cz_rt5682_dmic0_cap_ops = अणु
	.startup = cz_rt5682_dmic0_startup,
	.shutकरोwn = cz_rt5682_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops cz_rt5682_dmic1_cap_ops = अणु
	.startup = cz_rt5682_dmic1_startup,
	.shutकरोwn = cz_rt5682_shutकरोwn,
पूर्ण;

SND_SOC_DAILINK_DEF(designware1,
	DAILINK_COMP_ARRAY(COMP_CPU("designware-i2s.1.auto")));
SND_SOC_DAILINK_DEF(designware2,
	DAILINK_COMP_ARRAY(COMP_CPU("designware-i2s.2.auto")));
SND_SOC_DAILINK_DEF(designware3,
	DAILINK_COMP_ARRAY(COMP_CPU("designware-i2s.3.auto")));

SND_SOC_DAILINK_DEF(dlgs,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-DLGS7219:00", "da7219-hifi")));
SND_SOC_DAILINK_DEF(rt5682,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-10EC5682:00", "rt5682-aif1")));
SND_SOC_DAILINK_DEF(mx,
	DAILINK_COMP_ARRAY(COMP_CODEC("MX98357A:00", "HiFi")));
SND_SOC_DAILINK_DEF(adau,
	DAILINK_COMP_ARRAY(COMP_CODEC("ADAU7002:00", "adau7002-hifi")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("acp_audio_dma.0.auto")));

अटल काष्ठा snd_soc_dai_link cz_dai_7219_98357[] = अणु
	अणु
		.name = "amd-da7219-play",
		.stream_name = "Playback",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.init = cz_da7219_init,
		.dpcm_playback = 1,
		.ops = &cz_da7219_play_ops,
		SND_SOC_DAILINK_REG(designware1, dlgs, platक्रमm),
	पूर्ण,
	अणु
		.name = "amd-da7219-cap",
		.stream_name = "Capture",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.dpcm_capture = 1,
		.ops = &cz_da7219_cap_ops,
		SND_SOC_DAILINK_REG(designware2, dlgs, platक्रमm),
	पूर्ण,
	अणु
		.name = "amd-max98357-play",
		.stream_name = "HiFi Playback",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.dpcm_playback = 1,
		.ops = &cz_max_play_ops,
		SND_SOC_DAILINK_REG(designware3, mx, platक्रमm),
	पूर्ण,
	अणु
		/* C panel DMIC */
		.name = "dmic0",
		.stream_name = "DMIC0 Capture",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.dpcm_capture = 1,
		.ops = &cz_dmic0_cap_ops,
		SND_SOC_DAILINK_REG(designware3, adau, platक्रमm),
	पूर्ण,
	अणु
		/* A/B panel DMIC */
		.name = "dmic1",
		.stream_name = "DMIC1 Capture",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.dpcm_capture = 1,
		.ops = &cz_dmic1_cap_ops,
		SND_SOC_DAILINK_REG(designware2, adau, platक्रमm),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_link cz_dai_5682_98357[] = अणु
	अणु
		.name = "amd-rt5682-play",
		.stream_name = "Playback",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.init = cz_rt5682_init,
		.dpcm_playback = 1,
		.ops = &cz_rt5682_play_ops,
		SND_SOC_DAILINK_REG(designware1, rt5682, platक्रमm),
	पूर्ण,
	अणु
		.name = "amd-rt5682-cap",
		.stream_name = "Capture",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.dpcm_capture = 1,
		.ops = &cz_rt5682_cap_ops,
		SND_SOC_DAILINK_REG(designware2, rt5682, platक्रमm),
	पूर्ण,
	अणु
		.name = "amd-max98357-play",
		.stream_name = "HiFi Playback",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.dpcm_playback = 1,
		.ops = &cz_rt5682_max_play_ops,
		SND_SOC_DAILINK_REG(designware3, mx, platक्रमm),
	पूर्ण,
	अणु
		/* C panel DMIC */
		.name = "dmic0",
		.stream_name = "DMIC0 Capture",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.dpcm_capture = 1,
		.ops = &cz_rt5682_dmic0_cap_ops,
		SND_SOC_DAILINK_REG(designware3, adau, platक्रमm),
	पूर्ण,
	अणु
		/* A/B panel DMIC */
		.name = "dmic1",
		.stream_name = "DMIC1 Capture",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.dpcm_capture = 1,
		.ops = &cz_rt5682_dmic1_cap_ops,
		SND_SOC_DAILINK_REG(designware2, adau, platक्रमm),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cz_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphones", शून्य),
	SND_SOC_DAPM_SPK("Speakers", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Int Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cz_audio_route[] = अणु
	अणु"Headphones", शून्य, "HPL"पूर्ण,
	अणु"Headphones", शून्य, "HPR"पूर्ण,
	अणु"MIC", शून्य, "Headset Mic"पूर्ण,
	अणु"Speakers", शून्य, "Speaker"पूर्ण,
	अणु"PDM_DAT", शून्य, "Int Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cz_rt5682_audio_route[] = अणु
	अणु"Headphones", शून्य, "HPOL"पूर्ण,
	अणु"Headphones", शून्य, "HPOR"पूर्ण,
	अणु"IN1P", शून्य, "Headset Mic"पूर्ण,
	अणु"Speakers", शून्य, "Speaker"पूर्ण,
	अणु"PDM_DAT", शून्य, "Int Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cz_mc_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphones"),
	SOC_DAPM_PIN_SWITCH("Speakers"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
पूर्ण;

अटल काष्ठा snd_soc_card cz_card = अणु
	.name = "acpd7219m98357",
	.owner = THIS_MODULE,
	.dai_link = cz_dai_7219_98357,
	.num_links = ARRAY_SIZE(cz_dai_7219_98357),
	.dapm_widमाला_लो = cz_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(cz_widमाला_लो),
	.dapm_routes = cz_audio_route,
	.num_dapm_routes = ARRAY_SIZE(cz_audio_route),
	.controls = cz_mc_controls,
	.num_controls = ARRAY_SIZE(cz_mc_controls),
पूर्ण;

अटल काष्ठा snd_soc_card cz_rt5682_card = अणु
	.name = "acpr5682m98357",
	.owner = THIS_MODULE,
	.dai_link = cz_dai_5682_98357,
	.num_links = ARRAY_SIZE(cz_dai_5682_98357),
	.dapm_widमाला_लो = cz_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(cz_widमाला_लो),
	.dapm_routes = cz_rt5682_audio_route,
	.controls = cz_mc_controls,
	.num_controls = ARRAY_SIZE(cz_mc_controls),
पूर्ण;

व्योम *acp_soc_is_rltk_max(काष्ठा device *dev)
अणु
	स्थिर काष्ठा acpi_device_id *match;

	match = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!match)
		वापस शून्य;
	वापस (व्योम *)match->driver_data;
पूर्ण

अटल काष्ठा regulator_consumer_supply acp_da7219_supplies[] = अणु
	REGULATOR_SUPPLY("VDD", "i2c-DLGS7219:00"),
	REGULATOR_SUPPLY("VDDMIC", "i2c-DLGS7219:00"),
	REGULATOR_SUPPLY("VDDIO", "i2c-DLGS7219:00"),
	REGULATOR_SUPPLY("IOVDD", "ADAU7002:00"),
पूर्ण;

अटल काष्ठा regulator_init_data acp_da7219_data = अणु
	.स्थिरraपूर्णांकs = अणु
		.always_on = 1,
	पूर्ण,
	.num_consumer_supplies = ARRAY_SIZE(acp_da7219_supplies),
	.consumer_supplies = acp_da7219_supplies,
पूर्ण;

अटल काष्ठा regulator_config acp_da7219_cfg = अणु
	.init_data = &acp_da7219_data,
पूर्ण;

अटल काष्ठा regulator_ops acp_da7219_ops = अणु
पूर्ण;

अटल स्थिर काष्ठा regulator_desc acp_da7219_desc = अणु
	.name = "reg-fixed-1.8V",
	.type = REGULATOR_VOLTAGE,
	.owner = THIS_MODULE,
	.ops = &acp_da7219_ops,
	.fixed_uV = 1800000, /* 1.8V */
	.n_voltages = 1,
पूर्ण;

अटल पूर्णांक cz_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_card *card;
	काष्ठा acp_platक्रमm_info *machine;
	काष्ठा regulator_dev *rdev;
	काष्ठा device *dev = &pdev->dev;

	card = (काष्ठा snd_soc_card *)acp_soc_is_rltk_max(dev);
	अगर (!card)
		वापस -ENODEV;
	अगर (!म_भेद(card->name, "acpd7219m98357")) अणु
		acp_da7219_cfg.dev = &pdev->dev;
		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &acp_da7219_desc,
					       &acp_da7219_cfg);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "Failed to register regulator: %d\n",
				(पूर्णांक)PTR_ERR(rdev));
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	machine = devm_kzalloc(&pdev->dev, माप(काष्ठा acp_platक्रमm_info),
			       GFP_KERNEL);
	अगर (!machine)
		वापस -ENOMEM;
	card->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, card);
	snd_soc_card_set_drvdata(card, machine);
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
		वापस ret;
	पूर्ण
	bt_uart_enable = !device_property_पढ़ो_bool(&pdev->dev,
						    "bt-pad-enable");
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id cz_audio_acpi_match[] = अणु
	अणु "AMD7219", (अचिन्हित दीर्घ)&cz_card पूर्ण,
	अणु "AMDI5682", (अचिन्हित दीर्घ)&cz_rt5682_cardपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cz_audio_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver cz_pcm_driver = अणु
	.driver = अणु
		.name = "cz-da7219-max98357a",
		.acpi_match_table = ACPI_PTR(cz_audio_acpi_match),
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = cz_probe,
पूर्ण;

module_platक्रमm_driver(cz_pcm_driver);

MODULE_AUTHOR("akshu.agrawal@amd.com");
MODULE_AUTHOR("Vijendar.Mukunda@amd.com");
MODULE_DESCRIPTION("DA7219, RT5682 & MAX98357A audio support");
MODULE_LICENSE("GPL v2");
