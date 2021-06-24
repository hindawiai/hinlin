<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश "../codecs/wm8994.h"
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

 /*
  * Default CFG चयन settings to use this driver:
  *	SMDKV310: CFG5-1000, CFG7-111111
  */

 /*
  * Configure audio route as :-
  * $ amixer sset 'DAC1' on,on
  * $ amixer sset 'Right Headphone Mux' 'DAC'
  * $ amixer sset 'Left Headphone Mux' 'DAC'
  * $ amixer sset 'DAC1R Mixer AIF1.1' on
  * $ amixer sset 'DAC1L Mixer AIF1.1' on
  * $ amixer sset 'IN2L' on
  * $ amixer sset 'IN2L PGA IN2LN' on
  * $ amixer sset 'MIXINL IN2L' on
  * $ amixer sset 'AIF1ADC1L Mixer ADC/DMIC' on
  * $ amixer sset 'IN2R' on
  * $ amixer sset 'IN2R PGA IN2RN' on
  * $ amixer sset 'MIXINR IN2R' on
  * $ amixer sset 'AIF1ADC1R Mixer ADC/DMIC' on
  */

/* SMDK has a 16.934MHZ crystal attached to WM8994 */
#घोषणा SMDK_WM8994_FREQ 16934000

काष्ठा smdk_wm8994_data अणु
	पूर्णांक mclk1_rate;
पूर्ण;

/* Default SMDKs */
अटल काष्ठा smdk_wm8994_data smdk_board_data = अणु
	.mclk1_rate = SMDK_WM8994_FREQ,
पूर्ण;

अटल पूर्णांक smdk_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	अचिन्हित पूर्णांक pll_out;
	पूर्णांक ret;

	/* AIF1CLK should be >=3MHz क्रम optimal perक्रमmance */
	अगर (params_width(params) == 24)
		pll_out = params_rate(params) * 384;
	अन्यथा अगर (params_rate(params) == 8000 || params_rate(params) == 11025)
		pll_out = params_rate(params) * 512;
	अन्यथा
		pll_out = params_rate(params) * 256;

	ret = snd_soc_dai_set_pll(codec_dai, WM8994_FLL1, WM8994_FLL_SRC_MCLK1,
					SMDK_WM8994_FREQ, pll_out);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_sysclk(codec_dai, WM8994_SYSCLK_FLL1,
					pll_out, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * SMDK WM8994 DAI operations.
 */
अटल काष्ठा snd_soc_ops smdk_ops = अणु
	.hw_params = smdk_hw_params,
पूर्ण;

अटल पूर्णांक smdk_wm8994_init_paअगरtx(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dapm_context *dapm = &rtd->card->dapm;

	/* Other pins NC */
	snd_soc_dapm_nc_pin(dapm, "HPOUT2P");
	snd_soc_dapm_nc_pin(dapm, "HPOUT2N");
	snd_soc_dapm_nc_pin(dapm, "SPKOUTLN");
	snd_soc_dapm_nc_pin(dapm, "SPKOUTLP");
	snd_soc_dapm_nc_pin(dapm, "SPKOUTRP");
	snd_soc_dapm_nc_pin(dapm, "SPKOUTRN");
	snd_soc_dapm_nc_pin(dapm, "LINEOUT1N");
	snd_soc_dapm_nc_pin(dapm, "LINEOUT1P");
	snd_soc_dapm_nc_pin(dapm, "LINEOUT2N");
	snd_soc_dapm_nc_pin(dapm, "LINEOUT2P");
	snd_soc_dapm_nc_pin(dapm, "IN1LP");
	snd_soc_dapm_nc_pin(dapm, "IN2LP:VXRN");
	snd_soc_dapm_nc_pin(dapm, "IN1RP");
	snd_soc_dapm_nc_pin(dapm, "IN2RP:VXRP");

	वापस 0;
पूर्ण

SND_SOC_DAILINK_DEFS(aअगर1,
	DAILINK_COMP_ARRAY(COMP_CPU("samsung-i2s.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8994-codec", "wm8994-aif1")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("samsung-i2s.0")));

SND_SOC_DAILINK_DEFS(fअगरo_tx,
	DAILINK_COMP_ARRAY(COMP_CPU("samsung-i2s-sec")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8994-codec", "wm8994-aif1")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("samsung-i2s-sec")));

अटल काष्ठा snd_soc_dai_link smdk_dai[] = अणु
	अणु /* Primary DAI i/f */
		.name = "WM8994 AIF1",
		.stream_name = "Pri_Dai",
		.init = smdk_wm8994_init_paअगरtx,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBM_CFM,
		.ops = &smdk_ops,
		SND_SOC_DAILINK_REG(aअगर1),
	पूर्ण, अणु /* Sec_Fअगरo Playback i/f */
		.name = "Sec_FIFO TX",
		.stream_name = "Sec_Dai",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBM_CFM,
		.ops = &smdk_ops,
		SND_SOC_DAILINK_REG(fअगरo_tx),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card smdk = अणु
	.name = "SMDK-I2S",
	.owner = THIS_MODULE,
	.dai_link = smdk_dai,
	.num_links = ARRAY_SIZE(smdk_dai),
पूर्ण;

अटल स्थिर काष्ठा of_device_id samsung_wm8994_of_match[] __maybe_unused = अणु
	अणु .compatible = "samsung,smdk-wm8994", .data = &smdk_board_data पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, samsung_wm8994_of_match);

अटल पूर्णांक smdk_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा snd_soc_card *card = &smdk;
	काष्ठा smdk_wm8994_data *board;
	स्थिर काष्ठा of_device_id *id;

	card->dev = &pdev->dev;

	board = devm_kzalloc(&pdev->dev, माप(*board), GFP_KERNEL);
	अगर (!board)
		वापस -ENOMEM;

	अगर (np) अणु
		smdk_dai[0].cpus->dai_name = शून्य;
		smdk_dai[0].cpus->of_node = of_parse_phandle(np,
				"samsung,i2s-controller", 0);
		अगर (!smdk_dai[0].cpus->of_node) अणु
			dev_err(&pdev->dev,
			   "Property 'samsung,i2s-controller' missing or invalid\n");
			ret = -EINVAL;
			वापस ret;
		पूर्ण

		smdk_dai[0].platक्रमms->name = शून्य;
		smdk_dai[0].platक्रमms->of_node = smdk_dai[0].cpus->of_node;
	पूर्ण

	id = of_match_device(samsung_wm8994_of_match, &pdev->dev);
	अगर (id)
		*board = *((काष्ठा smdk_wm8994_data *)id->data);

	platक्रमm_set_drvdata(pdev, board);

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);

	अगर (ret && ret != -EPROBE_DEFER)
		dev_err(&pdev->dev, "snd_soc_register_card() failed:%d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver smdk_audio_driver = अणु
	.driver		= अणु
		.name	= "smdk-audio-wm8994",
		.of_match_table = of_match_ptr(samsung_wm8994_of_match),
		.pm	= &snd_soc_pm_ops,
	पूर्ण,
	.probe		= smdk_audio_probe,
पूर्ण;

module_platक्रमm_driver(smdk_audio_driver);

MODULE_DESCRIPTION("ALSA SoC SMDK WM8994");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:smdk-audio-wm8994");
