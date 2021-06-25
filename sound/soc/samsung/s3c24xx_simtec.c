<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2009 Simtec Electronics

#समावेश <linux/gpपन.स>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>

#समावेश <sound/soc.h>

#समावेश <linux/platक्रमm_data/asoc-s3c24xx_simtec.h>

#समावेश "s3c24xx-i2s.h"
#समावेश "s3c24xx_simtec.h"

अटल काष्ठा s3c24xx_audio_simtec_pdata *pdata;
अटल काष्ठा clk *xtal_clk;

अटल पूर्णांक spk_gain;
अटल पूर्णांक spk_unmute;

/**
 * speaker_gain_get - पढ़ो the speaker gain setting.
 * @kcontrol: The control क्रम the speaker gain.
 * @ucontrol: The value that needs to be updated.
 *
 * Read the value क्रम the AMP gain control.
 */
अटल पूर्णांक speaker_gain_get(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = spk_gain;
	वापस 0;
पूर्ण

/**
 * speaker_gain_set - set the value of the speaker amp gain
 * @value: The value to ग_लिखो.
 */
अटल व्योम speaker_gain_set(पूर्णांक value)
अणु
	gpio_set_value_cansleep(pdata->amp_gain[0], value & 1);
	gpio_set_value_cansleep(pdata->amp_gain[1], value >> 1);
पूर्ण

/**
 * speaker_gain_put - set the speaker gain setting.
 * @kcontrol: The control क्रम the speaker gain.
 * @ucontrol: The value that needs to be set.
 *
 * Set the value of the speaker gain from the specअगरied
 * @ucontrol setting.
 *
 * Note, अगर the speaker amp is muted, then we करो not set a gain value
 * as at-least one of the ICs that is fitted will try and घातer up even
 * अगर the मुख्य control is set to off.
 */
अटल पूर्णांक speaker_gain_put(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक value = ucontrol->value.पूर्णांकeger.value[0];

	spk_gain = value;

	अगर (!spk_unmute)
		speaker_gain_set(value);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new amp_gain_controls[] = अणु
	SOC_SINGLE_EXT("Speaker Gain", 0, 0, 3, 0,
		       speaker_gain_get, speaker_gain_put),
पूर्ण;

/**
 * spk_unmute_state - set the unmute state of the speaker
 * @to: zero to unmute, non-zero to ununmute.
 */
अटल व्योम spk_unmute_state(पूर्णांक to)
अणु
	pr_debug("%s: to=%d\n", __func__, to);

	spk_unmute = to;
	gpio_set_value(pdata->amp_gpio, to);

	/* अगर we're umuting, also re-set the gain */
	अगर (to && pdata->amp_gain[0] > 0)
		speaker_gain_set(spk_gain);
पूर्ण

/**
 * speaker_unmute_get - पढ़ो the speaker unmute setting.
 * @kcontrol: The control क्रम the speaker gain.
 * @ucontrol: The value that needs to be updated.
 *
 * Read the value क्रम the AMP gain control.
 */
अटल पूर्णांक speaker_unmute_get(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = spk_unmute;
	वापस 0;
पूर्ण

/**
 * speaker_unmute_put - set the speaker unmute setting.
 * @kcontrol: The control क्रम the speaker gain.
 * @ucontrol: The value that needs to be set.
 *
 * Set the value of the speaker gain from the specअगरied
 * @ucontrol setting.
 */
अटल पूर्णांक speaker_unmute_put(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	spk_unmute_state(ucontrol->value.पूर्णांकeger.value[0]);
	वापस 0;
पूर्ण

/* This is added as a manual control as the speaker amps create clicks
 * when their घातer state is changed, which are far more noticeable than
 * anything produced by the CODEC itself.
 */
अटल स्थिर काष्ठा snd_kcontrol_new amp_unmute_controls[] = अणु
	SOC_SINGLE_EXT("Speaker Switch", 0, 0, 1, 0,
		       speaker_unmute_get, speaker_unmute_put),
पूर्ण;

व्योम simtec_audio_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;

	अगर (pdata->amp_gpio > 0) अणु
		pr_debug("%s: adding amp routes\n", __func__);

		snd_soc_add_card_controls(card, amp_unmute_controls,
				     ARRAY_SIZE(amp_unmute_controls));
	पूर्ण

	अगर (pdata->amp_gain[0] > 0) अणु
		pr_debug("%s: adding amp controls\n", __func__);
		snd_soc_add_card_controls(card, amp_gain_controls,
				     ARRAY_SIZE(amp_gain_controls));
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(simtec_audio_init);

#घोषणा CODEC_CLOCK 12000000

/**
 * simtec_hw_params - update hardware parameters
 * @substream: The audio substream instance.
 * @params: The parameters requested.
 *
 * Update the codec data routing and configuration  settings
 * from the supplied data.
 */
अटल पूर्णांक simtec_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(codec_dai, 0,
				     CODEC_CLOCK, SND_SOC_CLOCK_IN);
	अगर (ret) अणु
		pr_err( "%s: failed setting codec sysclk\n", __func__);
		वापस ret;
	पूर्ण

	अगर (pdata->use_mpllin) अणु
		ret = snd_soc_dai_set_sysclk(cpu_dai, S3C24XX_CLKSRC_MPLL,
					     0, SND_SOC_CLOCK_OUT);

		अगर (ret) अणु
			pr_err("%s: failed to set MPLLin as clksrc\n",
			       __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (pdata->output_cdclk) अणु
		पूर्णांक cdclk_scale;

		cdclk_scale = clk_get_rate(xtal_clk) / CODEC_CLOCK;
		cdclk_scale--;

		ret = snd_soc_dai_set_clkभाग(cpu_dai, S3C24XX_DIV_PRESCALER,
					     cdclk_scale);
		अगर (ret) अणु
			pr_err("%s: failed to set clock div\n",
			       __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक simtec_call_startup(काष्ठा s3c24xx_audio_simtec_pdata *pd)
अणु
	/* call any board supplied startup code, this currently only
	 * covers the bast/vr1000 which have a CPLD in the way of the
	 * LRCLK */
	अगर (pd->startup)
		pd->startup();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops simtec_snd_ops = अणु
	.hw_params	= simtec_hw_params,
पूर्ण;

/**
 * attach_gpio_amp - get and configure the necessary gpios
 * @dev: The device we're probing.
 * @pd: The platक्रमm data supplied by the board.
 *
 * If there is a GPIO based amplअगरier attached to the board, claim
 * the necessary GPIO lines क्रम it, and set शेष values.
 */
अटल पूर्णांक attach_gpio_amp(काष्ठा device *dev,
			   काष्ठा s3c24xx_audio_simtec_pdata *pd)
अणु
	पूर्णांक ret;

	/* attach gpio amp gain (अगर any) */
	अगर (pdata->amp_gain[0] > 0) अणु
		ret = gpio_request(pd->amp_gain[0], "gpio-amp-gain0");
		अगर (ret) अणु
			dev_err(dev, "cannot get amp gpio gain0\n");
			वापस ret;
		पूर्ण

		ret = gpio_request(pd->amp_gain[1], "gpio-amp-gain1");
		अगर (ret) अणु
			dev_err(dev, "cannot get amp gpio gain1\n");
			gpio_मुक्त(pdata->amp_gain[0]);
			वापस ret;
		पूर्ण

		gpio_direction_output(pd->amp_gain[0], 0);
		gpio_direction_output(pd->amp_gain[1], 0);
	पूर्ण

	/* note, currently we assume GPA0 isn't valid amp */
	अगर (pdata->amp_gpio > 0) अणु
		ret = gpio_request(pd->amp_gpio, "gpio-amp");
		अगर (ret) अणु
			dev_err(dev, "cannot get amp gpio %d (%d)\n",
				pd->amp_gpio, ret);
			जाओ err_amp;
		पूर्ण

		/* set the amp off at startup */
		spk_unmute_state(0);
	पूर्ण

	वापस 0;

err_amp:
	अगर (pd->amp_gain[0] > 0) अणु
		gpio_मुक्त(pd->amp_gain[0]);
		gpio_मुक्त(pd->amp_gain[1]);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम detach_gpio_amp(काष्ठा s3c24xx_audio_simtec_pdata *pd)
अणु
	अगर (pd->amp_gain[0] > 0) अणु
		gpio_मुक्त(pd->amp_gain[0]);
		gpio_मुक्त(pd->amp_gain[1]);
	पूर्ण

	अगर (pd->amp_gpio > 0)
		gpio_मुक्त(pd->amp_gpio);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक simtec_audio_resume(काष्ठा device *dev)
अणु
	simtec_call_startup(pdata);
	वापस 0;
पूर्ण

स्थिर काष्ठा dev_pm_ops simtec_audio_pmops = अणु
	.resume	= simtec_audio_resume,
पूर्ण;
EXPORT_SYMBOL_GPL(simtec_audio_pmops);
#पूर्ण_अगर

पूर्णांक simtec_audio_core_probe(काष्ठा platक्रमm_device *pdev,
			    काष्ठा snd_soc_card *card)
अणु
	काष्ठा platक्रमm_device *snd_dev;
	पूर्णांक ret;

	card->dai_link->ops = &simtec_snd_ops;
	card->dai_link->dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				  SND_SOC_DAIFMT_CBM_CFM;

	pdata = pdev->dev.platक्रमm_data;
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "no platform data supplied\n");
		वापस -EINVAL;
	पूर्ण

	simtec_call_startup(pdata);

	xtal_clk = clk_get(&pdev->dev, "xtal");
	अगर (IS_ERR(xtal_clk)) अणु
		dev_err(&pdev->dev, "could not get clkout0\n");
		वापस -EINVAL;
	पूर्ण

	dev_info(&pdev->dev, "xtal rate is %ld\n", clk_get_rate(xtal_clk));

	ret = attach_gpio_amp(&pdev->dev, pdata);
	अगर (ret)
		जाओ err_clk;

	snd_dev = platक्रमm_device_alloc("soc-audio", -1);
	अगर (!snd_dev) अणु
		dev_err(&pdev->dev, "failed to alloc soc-audio devicec\n");
		ret = -ENOMEM;
		जाओ err_gpio;
	पूर्ण

	platक्रमm_set_drvdata(snd_dev, card);

	ret = platक्रमm_device_add(snd_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add soc-audio dev\n");
		जाओ err_pdev;
	पूर्ण

	platक्रमm_set_drvdata(pdev, snd_dev);
	वापस 0;

err_pdev:
	platक्रमm_device_put(snd_dev);

err_gpio:
	detach_gpio_amp(pdata);

err_clk:
	clk_put(xtal_clk);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(simtec_audio_core_probe);

पूर्णांक simtec_audio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_device *snd_dev = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(snd_dev);

	detach_gpio_amp(pdata);
	clk_put(xtal_clk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(simtec_audio_हटाओ);

MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_DESCRIPTION("ALSA SoC Simtec Audio common support");
MODULE_LICENSE("GPL");
