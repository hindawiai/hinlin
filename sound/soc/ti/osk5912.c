<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * osk5912.c  --  SoC audio क्रम OSK 5912
 *
 * Copyright (C) 2008 Mistral Solutions
 *
 * Contact: Arun KS  <arunks@mistralsolutions.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/asoc-ti-mcbsp.h>

#समावेश "omap-mcbsp.h"
#समावेश "../codecs/tlv320aic23.h"

#घोषणा CODEC_CLOCK 	12000000

अटल काष्ठा clk *tlv320aic23_mclk;

अटल पूर्णांक osk_startup(काष्ठा snd_pcm_substream *substream)
अणु
	वापस clk_enable(tlv320aic23_mclk);
पूर्ण

अटल व्योम osk_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	clk_disable(tlv320aic23_mclk);
पूर्ण

अटल पूर्णांक osk_hw_params(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक err;

	/* Set the codec प्रणाली घड़ी क्रम DAC and ADC */
	err =
	    snd_soc_dai_set_sysclk(codec_dai, 0, CODEC_CLOCK, SND_SOC_CLOCK_IN);

	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "can't set codec system clock\n");
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops osk_ops = अणु
	.startup = osk_startup,
	.hw_params = osk_hw_params,
	.shutकरोwn = osk_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tlv320aic23_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_LINE("Line In", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	अणु"Headphone Jack", शून्य, "LHPOUT"पूर्ण,
	अणु"Headphone Jack", शून्य, "RHPOUT"पूर्ण,

	अणु"LLINEIN", शून्य, "Line In"पूर्ण,
	अणु"RLINEIN", शून्य, "Line In"पूर्ण,

	अणु"MICIN", शून्य, "Mic Jack"पूर्ण,
पूर्ण;

/* Digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(aic23,
	DAILINK_COMP_ARRAY(COMP_CPU("omap-mcbsp.1")),
	DAILINK_COMP_ARRAY(COMP_CODEC("tlv320aic23-codec",
				      "tlv320aic23-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("omap-mcbsp.1")));

अटल काष्ठा snd_soc_dai_link osk_dai = अणु
	.name = "TLV320AIC23",
	.stream_name = "AIC23",
	.dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBM_CFM,
	.ops = &osk_ops,
	SND_SOC_DAILINK_REG(aic23),
पूर्ण;

/* Audio machine driver */
अटल काष्ठा snd_soc_card snd_soc_card_osk = अणु
	.name = "OSK5912",
	.owner = THIS_MODULE,
	.dai_link = &osk_dai,
	.num_links = 1,

	.dapm_widमाला_लो = tlv320aic23_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(tlv320aic23_dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
पूर्ण;

अटल काष्ठा platक्रमm_device *osk_snd_device;

अटल पूर्णांक __init osk_soc_init(व्योम)
अणु
	पूर्णांक err;
	u32 curRate;
	काष्ठा device *dev;

	अगर (!(machine_is_omap_osk()))
		वापस -ENODEV;

	osk_snd_device = platक्रमm_device_alloc("soc-audio", -1);
	अगर (!osk_snd_device)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(osk_snd_device, &snd_soc_card_osk);
	err = platक्रमm_device_add(osk_snd_device);
	अगर (err)
		जाओ err1;

	dev = &osk_snd_device->dev;

	tlv320aic23_mclk = clk_get(dev, "mclk");
	अगर (IS_ERR(tlv320aic23_mclk)) अणु
		prपूर्णांकk(KERN_ERR "Could not get mclk clock\n");
		err = PTR_ERR(tlv320aic23_mclk);
		जाओ err2;
	पूर्ण

	/*
	 * Configure 12 MHz output on MCLK.
	 */
	curRate = (uपूर्णांक) clk_get_rate(tlv320aic23_mclk);
	अगर (curRate != CODEC_CLOCK) अणु
		अगर (clk_set_rate(tlv320aic23_mclk, CODEC_CLOCK)) अणु
			prपूर्णांकk(KERN_ERR "Cannot set MCLK for AIC23 CODEC\n");
			err = -ECANCELED;
			जाओ err3;
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_INFO "MCLK = %d [%d]\n",
	       (uपूर्णांक) clk_get_rate(tlv320aic23_mclk), CODEC_CLOCK);

	वापस 0;

err3:
	clk_put(tlv320aic23_mclk);
err2:
	platक्रमm_device_del(osk_snd_device);
err1:
	platक्रमm_device_put(osk_snd_device);

	वापस err;

पूर्ण

अटल व्योम __निकास osk_soc_निकास(व्योम)
अणु
	clk_put(tlv320aic23_mclk);
	platक्रमm_device_unरेजिस्टर(osk_snd_device);
पूर्ण

module_init(osk_soc_init);
module_निकास(osk_soc_निकास);

MODULE_AUTHOR("Arun KS <arunks@mistralsolutions.com>");
MODULE_DESCRIPTION("ALSA SoC OSK 5912");
MODULE_LICENSE("GPL");
