<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap3panकरोra.c  --  SoC audio क्रम Panकरोra Handheld Console
 *
 * Author: Graधठvydas Ignotas <notasas@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/module.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <linux/platक्रमm_data/asoc-ti-mcbsp.h>

#समावेश "omap-mcbsp.h"

#घोषणा OMAP3_PANDORA_DAC_POWER_GPIO	118
#घोषणा OMAP3_PANDORA_AMP_POWER_GPIO	14

#घोषणा PREFIX "ASoC omap3pandora: "

अटल काष्ठा regulator *omap3panकरोra_dac_reg;

अटल पूर्णांक omap3panकरोra_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक ret;

	/* Set the codec प्रणाली घड़ी क्रम DAC and ADC */
	ret = snd_soc_dai_set_sysclk(codec_dai, 0, 26000000,
					    SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		pr_err(PREFIX "can't set codec system clock\n");
		वापस ret;
	पूर्ण

	/* Set McBSP घड़ी to बाह्यal */
	ret = snd_soc_dai_set_sysclk(cpu_dai, OMAP_MCBSP_SYSCLK_CLKS_EXT,
				     256 * params_rate(params),
				     SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		pr_err(PREFIX "can't set cpu system clock\n");
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_clkभाग(cpu_dai, OMAP_MCBSP_CLKGDV, 8);
	अगर (ret < 0) अणु
		pr_err(PREFIX "can't set SRG clock divider\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap3panकरोra_dac_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	पूर्णांक ret;

	/*
	 * The PCM1773 DAC datasheet requires 1ms delay between चयनing
	 * VCC घातer on/off and /PD pin high/low
	 */
	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		ret = regulator_enable(omap3panकरोra_dac_reg);
		अगर (ret) अणु
			dev_err(w->dapm->dev, "Failed to power DAC: %d\n", ret);
			वापस ret;
		पूर्ण
		mdelay(1);
		gpio_set_value(OMAP3_PANDORA_DAC_POWER_GPIO, 1);
	पूर्ण अन्यथा अणु
		gpio_set_value(OMAP3_PANDORA_DAC_POWER_GPIO, 0);
		mdelay(1);
		regulator_disable(omap3panकरोra_dac_reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap3panकरोra_hp_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	अगर (SND_SOC_DAPM_EVENT_ON(event))
		gpio_set_value(OMAP3_PANDORA_AMP_POWER_GPIO, 1);
	अन्यथा
		gpio_set_value(OMAP3_PANDORA_AMP_POWER_GPIO, 0);

	वापस 0;
पूर्ण

/*
 * Audio paths on Panकरोra board:
 *
 *  |O| ---> PCM DAC +-> AMP -> Headphone Jack
 *  |M|         A    +--------> Line Out
 *  |A| <~~clk~~+
 *  |P| <--- TWL4030 <--------- Line In and MICs
 */
अटल स्थिर काष्ठा snd_soc_dapm_widget omap3panकरोra_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC_E("PCM DAC", "HiFi Playback", SND_SOC_NOPM,
			   0, 0, omap3panकरोra_dac_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_PGA_E("Headphone Amplifier", SND_SOC_NOPM,
			   0, 0, शून्य, 0, omap3panकरोra_hp_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_LINE("Line Out", शून्य),

	SND_SOC_DAPM_MIC("Mic (internal)", शून्य),
	SND_SOC_DAPM_MIC("Mic (external)", शून्य),
	SND_SOC_DAPM_LINE("Line In", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route omap3panकरोra_map[] = अणु
	अणु"PCM DAC", शून्य, "APLL Enable"पूर्ण,
	अणु"Headphone Amplifier", शून्य, "PCM DAC"पूर्ण,
	अणु"Line Out", शून्य, "PCM DAC"पूर्ण,
	अणु"Headphone Jack", शून्य, "Headphone Amplifier"पूर्ण,

	अणु"AUXL", शून्य, "Line In"पूर्ण,
	अणु"AUXR", शून्य, "Line In"पूर्ण,

	अणु"MAINMIC", शून्य, "Mic (internal)"पूर्ण,
	अणु"Mic (internal)", शून्य, "Mic Bias 1"पूर्ण,

	अणु"SUBMIC", शून्य, "Mic (external)"पूर्ण,
	अणु"Mic (external)", शून्य, "Mic Bias 2"पूर्ण,
पूर्ण;

अटल पूर्णांक omap3panकरोra_out_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dapm_context *dapm = &rtd->card->dapm;

	/* All TWL4030 output pins are भग्नing */
	snd_soc_dapm_nc_pin(dapm, "EARPIECE");
	snd_soc_dapm_nc_pin(dapm, "PREDRIVEL");
	snd_soc_dapm_nc_pin(dapm, "PREDRIVER");
	snd_soc_dapm_nc_pin(dapm, "HSOL");
	snd_soc_dapm_nc_pin(dapm, "HSOR");
	snd_soc_dapm_nc_pin(dapm, "CARKITL");
	snd_soc_dapm_nc_pin(dapm, "CARKITR");
	snd_soc_dapm_nc_pin(dapm, "HFL");
	snd_soc_dapm_nc_pin(dapm, "HFR");
	snd_soc_dapm_nc_pin(dapm, "VIBRA");

	वापस 0;
पूर्ण

अटल पूर्णांक omap3panकरोra_in_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dapm_context *dapm = &rtd->card->dapm;

	/* Not comnnected */
	snd_soc_dapm_nc_pin(dapm, "HSMIC");
	snd_soc_dapm_nc_pin(dapm, "CARKITMIC");
	snd_soc_dapm_nc_pin(dapm, "DIGIMIC0");
	snd_soc_dapm_nc_pin(dapm, "DIGIMIC1");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops omap3panकरोra_ops = अणु
	.hw_params = omap3panकरोra_hw_params,
पूर्ण;

/* Digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(out,
	DAILINK_COMP_ARRAY(COMP_CPU("omap-mcbsp.2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("twl4030-codec", "twl4030-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("omap-mcbsp.2")));

SND_SOC_DAILINK_DEFS(in,
	DAILINK_COMP_ARRAY(COMP_CPU("omap-mcbsp.4")),
	DAILINK_COMP_ARRAY(COMP_CODEC("twl4030-codec", "twl4030-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("omap-mcbsp.4")));

अटल काष्ठा snd_soc_dai_link omap3panकरोra_dai[] = अणु
	अणु
		.name = "PCM1773",
		.stream_name = "HiFi Out",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			   SND_SOC_DAIFMT_CBS_CFS,
		.ops = &omap3panकरोra_ops,
		.init = omap3panकरोra_out_init,
		SND_SOC_DAILINK_REG(out),
	पूर्ण, अणु
		.name = "TWL4030",
		.stream_name = "Line/Mic In",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			   SND_SOC_DAIFMT_CBS_CFS,
		.ops = &omap3panकरोra_ops,
		.init = omap3panकरोra_in_init,
		SND_SOC_DAILINK_REG(in),
	पूर्ण
पूर्ण;

/* SoC card */
अटल काष्ठा snd_soc_card snd_soc_card_omap3panकरोra = अणु
	.name = "omap3pandora",
	.owner = THIS_MODULE,
	.dai_link = omap3panकरोra_dai,
	.num_links = ARRAY_SIZE(omap3panकरोra_dai),

	.dapm_widमाला_लो = omap3panकरोra_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(omap3panकरोra_dapm_widमाला_लो),
	.dapm_routes = omap3panकरोra_map,
	.num_dapm_routes = ARRAY_SIZE(omap3panकरोra_map),
पूर्ण;

अटल काष्ठा platक्रमm_device *omap3panकरोra_snd_device;

अटल पूर्णांक __init omap3panकरोra_soc_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_omap3_panकरोra())
		वापस -ENODEV;

	pr_info("OMAP3 Pandora SoC init\n");

	ret = gpio_request(OMAP3_PANDORA_DAC_POWER_GPIO, "dac_power");
	अगर (ret) अणु
		pr_err(PREFIX "Failed to get DAC power GPIO\n");
		वापस ret;
	पूर्ण

	ret = gpio_direction_output(OMAP3_PANDORA_DAC_POWER_GPIO, 0);
	अगर (ret) अणु
		pr_err(PREFIX "Failed to set DAC power GPIO direction\n");
		जाओ fail0;
	पूर्ण

	ret = gpio_request(OMAP3_PANDORA_AMP_POWER_GPIO, "amp_power");
	अगर (ret) अणु
		pr_err(PREFIX "Failed to get amp power GPIO\n");
		जाओ fail0;
	पूर्ण

	ret = gpio_direction_output(OMAP3_PANDORA_AMP_POWER_GPIO, 0);
	अगर (ret) अणु
		pr_err(PREFIX "Failed to set amp power GPIO direction\n");
		जाओ fail1;
	पूर्ण

	omap3panकरोra_snd_device = platक्रमm_device_alloc("soc-audio", -1);
	अगर (omap3panकरोra_snd_device == शून्य) अणु
		pr_err(PREFIX "Platform device allocation failed\n");
		ret = -ENOMEM;
		जाओ fail1;
	पूर्ण

	platक्रमm_set_drvdata(omap3panकरोra_snd_device, &snd_soc_card_omap3panकरोra);

	ret = platक्रमm_device_add(omap3panकरोra_snd_device);
	अगर (ret) अणु
		pr_err(PREFIX "Unable to add platform device\n");
		जाओ fail2;
	पूर्ण

	omap3panकरोra_dac_reg = regulator_get(&omap3panकरोra_snd_device->dev, "vcc");
	अगर (IS_ERR(omap3panकरोra_dac_reg)) अणु
		pr_err(PREFIX "Failed to get DAC regulator from %s: %ld\n",
			dev_name(&omap3panकरोra_snd_device->dev),
			PTR_ERR(omap3panकरोra_dac_reg));
		ret = PTR_ERR(omap3panकरोra_dac_reg);
		जाओ fail3;
	पूर्ण

	वापस 0;

fail3:
	platक्रमm_device_del(omap3panकरोra_snd_device);
fail2:
	platक्रमm_device_put(omap3panकरोra_snd_device);
fail1:
	gpio_मुक्त(OMAP3_PANDORA_AMP_POWER_GPIO);
fail0:
	gpio_मुक्त(OMAP3_PANDORA_DAC_POWER_GPIO);
	वापस ret;
पूर्ण
module_init(omap3panकरोra_soc_init);

अटल व्योम __निकास omap3panकरोra_soc_निकास(व्योम)
अणु
	regulator_put(omap3panकरोra_dac_reg);
	platक्रमm_device_unरेजिस्टर(omap3panकरोra_snd_device);
	gpio_मुक्त(OMAP3_PANDORA_AMP_POWER_GPIO);
	gpio_मुक्त(OMAP3_PANDORA_DAC_POWER_GPIO);
पूर्ण
module_निकास(omap3panकरोra_soc_निकास);

MODULE_AUTHOR("Grazvydas Ignotas <notasas@gmail.com>");
MODULE_DESCRIPTION("ALSA SoC OMAP3 Pandora");
MODULE_LICENSE("GPL");
