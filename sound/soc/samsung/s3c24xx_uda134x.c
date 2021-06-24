<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Modअगरications by Christian Pellegrin <chripell@evolware.org>
//
// s3c24xx_uda134x.c - S3C24XX_UDA134X ALSA SoC Audio board driver
//
// Copyright 2007 Dension Audio Systems Ltd.
// Author: Zoltan Devai

#समावेश <linux/clk.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>

#समावेश <sound/soc.h>
#समावेश <sound/s3c24xx_uda134x.h>

#समावेश "regs-iis.h"
#समावेश "s3c24xx-i2s.h"

काष्ठा s3c24xx_uda134x अणु
	काष्ठा clk *xtal;
	काष्ठा clk *pclk;
	काष्ठा mutex clk_lock;
	पूर्णांक clk_users;
पूर्ण;

/* #घोषणा ENFORCE_RATES 1 */
/*
  Unक्रमtunately the S3C24XX in master mode has a limited capacity of
  generating the घड़ी क्रम the codec. If you define this only rates
  that are really available will be enक्रमced. But be careful, most
  user level application just want the usual sampling frequencies (8,
  11.025, 22.050, 44.1 kHz) and anyway resampling is a costly
  operation क्रम embedded प्रणालीs. So अगर you aren't very lucky or your
  hardware engineer wasn't very forward-looking it's better to leave
  this undefined. If you करो so an approximate value क्रम the requested
  sampling rate in the range -/+ 5% will be chosen. If this in not
  possible an error will be वापसed.
*/

अटल अचिन्हित पूर्णांक rates[33 * 2];
#अगर_घोषित ENFORCE_RATES
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_rates = अणु
	.count	= ARRAY_SIZE(rates),
	.list	= rates,
	.mask	= 0,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक s3c24xx_uda134x_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा s3c24xx_uda134x *priv = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक ret = 0;

	mutex_lock(&priv->clk_lock);

	अगर (priv->clk_users == 0) अणु
		priv->xtal = clk_get(rtd->dev, "xtal");
		अगर (IS_ERR(priv->xtal)) अणु
			dev_err(rtd->dev, "%s cannot get xtal\n", __func__);
			ret = PTR_ERR(priv->xtal);
		पूर्ण अन्यथा अणु
			priv->pclk = clk_get(cpu_dai->dev, "iis");
			अगर (IS_ERR(priv->pclk)) अणु
				dev_err(rtd->dev, "%s cannot get pclk\n",
					__func__);
				clk_put(priv->xtal);
				ret = PTR_ERR(priv->pclk);
			पूर्ण
		पूर्ण
		अगर (!ret) अणु
			पूर्णांक i, j;

			क्रम (i = 0; i < 2; i++) अणु
				पूर्णांक fs = i ? 256 : 384;

				rates[i*33] = clk_get_rate(priv->xtal) / fs;
				क्रम (j = 1; j < 33; j++)
					rates[i*33 + j] = clk_get_rate(priv->pclk) /
						(j * fs);
			पूर्ण
		पूर्ण
	पूर्ण
	priv->clk_users += 1;
	mutex_unlock(&priv->clk_lock);

	अगर (!ret) अणु
#अगर_घोषित ENFORCE_RATES
		ret = snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
						 SNDRV_PCM_HW_PARAM_RATE,
						 &hw_स्थिरraपूर्णांकs_rates);
		अगर (ret < 0)
			dev_err(rtd->dev, "%s cannot set constraints\n",
				__func__);
#पूर्ण_अगर
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम s3c24xx_uda134x_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा s3c24xx_uda134x *priv = snd_soc_card_get_drvdata(rtd->card);

	mutex_lock(&priv->clk_lock);
	priv->clk_users -= 1;
	अगर (priv->clk_users == 0) अणु
		clk_put(priv->xtal);
		priv->xtal = शून्य;
		clk_put(priv->pclk);
		priv->pclk = शून्य;
	पूर्ण
	mutex_unlock(&priv->clk_lock);
पूर्ण

अटल पूर्णांक s3c24xx_uda134x_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	अचिन्हित पूर्णांक clk = 0;
	पूर्णांक ret = 0;
	पूर्णांक clk_source, fs_mode;
	अचिन्हित दीर्घ rate = params_rate(params);
	दीर्घ err, cerr;
	अचिन्हित पूर्णांक भाग;
	पूर्णांक i, bi;

	err = 999999;
	bi = 0;
	क्रम (i = 0; i < 2*33; i++) अणु
		cerr = rates[i] - rate;
		अगर (cerr < 0)
			cerr = -cerr;
		अगर (cerr < err) अणु
			err = cerr;
			bi = i;
		पूर्ण
	पूर्ण
	अगर (bi / 33 == 1)
		fs_mode = S3C2410_IISMOD_256FS;
	अन्यथा
		fs_mode = S3C2410_IISMOD_384FS;
	अगर (bi % 33 == 0) अणु
		clk_source = S3C24XX_CLKSRC_MPLL;
		भाग = 1;
	पूर्ण अन्यथा अणु
		clk_source = S3C24XX_CLKSRC_PCLK;
		भाग = bi % 33;
	पूर्ण

	dev_dbg(rtd->dev, "%s desired rate %lu, %d\n", __func__, rate, bi);

	clk = (fs_mode == S3C2410_IISMOD_384FS ? 384 : 256) * rate;

	dev_dbg(rtd->dev, "%s will use: %s %s %d sysclk %d err %ld\n", __func__,
		fs_mode == S3C2410_IISMOD_384FS ? "384FS" : "256FS",
		clk_source == S3C24XX_CLKSRC_MPLL ? "MPLLin" : "PCLK",
		भाग, clk, err);

	अगर ((err * 100 / rate) > 5) अणु
		dev_err(rtd->dev, "effective frequency too different "
				  "from desired (%ld%%)\n", err * 100 / rate);
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(cpu_dai, clk_source , clk,
			SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_clkभाग(cpu_dai, S3C24XX_DIV_MCLK, fs_mode);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_clkभाग(cpu_dai, S3C24XX_DIV_BCLK,
			S3C2410_IISMOD_32FS);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_clkभाग(cpu_dai, S3C24XX_DIV_PRESCALER,
			S3C24XX_PRESCALE(भाग, भाग));
	अगर (ret < 0)
		वापस ret;

	/* set the codec प्रणाली घड़ी क्रम DAC and ADC */
	ret = snd_soc_dai_set_sysclk(codec_dai, 0, clk,
			SND_SOC_CLOCK_OUT);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops s3c24xx_uda134x_ops = अणु
	.startup = s3c24xx_uda134x_startup,
	.shutकरोwn = s3c24xx_uda134x_shutकरोwn,
	.hw_params = s3c24xx_uda134x_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEFS(uda134x,
	DAILINK_COMP_ARRAY(COMP_CPU("s3c24xx-iis")),
	DAILINK_COMP_ARRAY(COMP_CODEC("uda134x-codec", "uda134x-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("s3c24xx-iis")));

अटल काष्ठा snd_soc_dai_link s3c24xx_uda134x_dai_link = अणु
	.name = "UDA134X",
	.stream_name = "UDA134X",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	.ops = &s3c24xx_uda134x_ops,
	SND_SOC_DAILINK_REG(uda134x),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_s3c24xx_uda134x = अणु
	.name = "S3C24XX_UDA134X",
	.owner = THIS_MODULE,
	.dai_link = &s3c24xx_uda134x_dai_link,
	.num_links = 1,
पूर्ण;

अटल पूर्णांक s3c24xx_uda134x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &snd_soc_s3c24xx_uda134x;
	काष्ठा s3c24xx_uda134x *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_init(&priv->clk_lock);

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, priv);

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		dev_err(&pdev->dev, "failed to register card: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver s3c24xx_uda134x_driver = अणु
	.probe  = s3c24xx_uda134x_probe,
	.driver = अणु
		.name = "s3c24xx_uda134x",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(s3c24xx_uda134x_driver);

MODULE_AUTHOR("Zoltan Devai, Christian Pellegrin <chripell@evolware.org>");
MODULE_DESCRIPTION("S3C24XX_UDA134X ALSA SoC audio driver");
MODULE_LICENSE("GPL");
