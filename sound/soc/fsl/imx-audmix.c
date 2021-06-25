<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2017 NXP
 *
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * https://www.खोलोsource.org/licenses/gpl-license.hपंचांगl
 * https://www.gnu.org/copyleft/gpl.hपंचांगl
 */

#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/clk.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश "fsl_sai.h"
#समावेश "fsl_audmix.h"

काष्ठा imx_audmix अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा snd_soc_card card;
	काष्ठा platक्रमm_device *audmix_pdev;
	काष्ठा platक्रमm_device *out_pdev;
	काष्ठा clk *cpu_mclk;
	पूर्णांक num_dai;
	काष्ठा snd_soc_dai_link *dai;
	पूर्णांक num_dai_conf;
	काष्ठा snd_soc_codec_conf *dai_conf;
	पूर्णांक num_dapm_routes;
	काष्ठा snd_soc_dapm_route *dapm_routes;
पूर्ण;

अटल स्थिर u32 imx_audmix_rates[] = अणु
	8000, 12000, 16000, 24000, 32000, 48000, 64000, 96000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list imx_audmix_rate_स्थिरraपूर्णांकs = अणु
	.count = ARRAY_SIZE(imx_audmix_rates),
	.list = imx_audmix_rates,
पूर्ण;

अटल पूर्णांक imx_audmix_fe_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा imx_audmix *priv = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा device *dev = rtd->card->dev;
	अचिन्हित दीर्घ clk_rate = clk_get_rate(priv->cpu_mclk);
	पूर्णांक ret;

	अगर (clk_rate % 24576000 == 0) अणु
		ret = snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
						 SNDRV_PCM_HW_PARAM_RATE,
						 &imx_audmix_rate_स्थिरraपूर्णांकs);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		dev_warn(dev, "mclk may be not supported %lu\n", clk_rate);
	पूर्ण

	ret = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_CHANNELS,
					   1, 8);
	अगर (ret < 0)
		वापस ret;

	वापस snd_pcm_hw_स्थिरraपूर्णांक_mask64(runसमय, SNDRV_PCM_HW_PARAM_FORMAT,
					    FSL_AUDMIX_FORMATS);
पूर्ण

अटल पूर्णांक imx_audmix_fe_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा device *dev = rtd->card->dev;
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	अचिन्हित पूर्णांक fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_NB_NF;
	u32 channels = params_channels(params);
	पूर्णांक ret, dir;

	/* For playback the AUDMIX is slave, and क्रम record is master */
	fmt |= tx ? SND_SOC_DAIFMT_CBS_CFS : SND_SOC_DAIFMT_CBM_CFM;
	dir  = tx ? SND_SOC_CLOCK_OUT : SND_SOC_CLOCK_IN;

	/* set DAI configuration */
	ret = snd_soc_dai_set_fmt(asoc_rtd_to_cpu(rtd, 0), fmt);
	अगर (ret) अणु
		dev_err(dev, "failed to set cpu dai fmt: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(asoc_rtd_to_cpu(rtd, 0), FSL_SAI_CLK_MAST1, 0, dir);
	अगर (ret) अणु
		dev_err(dev, "failed to set cpu sysclk: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Per datasheet, AUDMIX expects 8 slots and 32 bits
	 * क्रम every slot in TDM mode.
	 */
	ret = snd_soc_dai_set_tdm_slot(asoc_rtd_to_cpu(rtd, 0), BIT(channels) - 1,
				       BIT(channels) - 1, 8, 32);
	अगर (ret)
		dev_err(dev, "failed to set cpu dai tdm slot: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक imx_audmix_be_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा device *dev = rtd->card->dev;
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	अचिन्हित पूर्णांक fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_NB_NF;
	पूर्णांक ret;

	अगर (!tx)
		वापस 0;

	/* For playback the AUDMIX is slave */
	fmt |= SND_SOC_DAIFMT_CBM_CFM;

	/* set AUDMIX DAI configuration */
	ret = snd_soc_dai_set_fmt(asoc_rtd_to_cpu(rtd, 0), fmt);
	अगर (ret)
		dev_err(dev, "failed to set AUDMIX DAI fmt: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_ops imx_audmix_fe_ops = अणु
	.startup = imx_audmix_fe_startup,
	.hw_params = imx_audmix_fe_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_ops imx_audmix_be_ops = अणु
	.hw_params = imx_audmix_be_hw_params,
पूर्ण;

अटल पूर्णांक imx_audmix_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *audmix_np = शून्य, *out_cpu_np = शून्य;
	काष्ठा platक्रमm_device *audmix_pdev = शून्य;
	काष्ठा platक्रमm_device *cpu_pdev;
	काष्ठा of_phandle_args args;
	काष्ठा imx_audmix *priv;
	पूर्णांक i, num_dai, ret;
	स्थिर अक्षर *fe_name_pref = "HiFi-AUDMIX-FE-";
	अक्षर *be_name, *be_pb, *be_cp, *dai_name, *capture_dai_name;

	अगर (pdev->dev.parent) अणु
		audmix_np = pdev->dev.parent->of_node;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Missing parent device.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!audmix_np) अणु
		dev_err(&pdev->dev, "Missing DT node for parent device.\n");
		वापस -EINVAL;
	पूर्ण

	audmix_pdev = of_find_device_by_node(audmix_np);
	अगर (!audmix_pdev) अणु
		dev_err(&pdev->dev, "Missing AUDMIX platform device for %s\n",
			np->full_name);
		वापस -EINVAL;
	पूर्ण
	put_device(&audmix_pdev->dev);

	num_dai = of_count_phandle_with_args(audmix_np, "dais", शून्य);
	अगर (num_dai != FSL_AUDMIX_MAX_DAIS) अणु
		dev_err(&pdev->dev, "Need 2 dais to be provided for %s\n",
			audmix_np->full_name);
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->num_dai = 2 * num_dai;
	priv->dai = devm_kसुस्मृति(&pdev->dev, priv->num_dai,
				 माप(काष्ठा snd_soc_dai_link), GFP_KERNEL);
	अगर (!priv->dai)
		वापस -ENOMEM;

	priv->num_dai_conf = num_dai;
	priv->dai_conf = devm_kसुस्मृति(&pdev->dev, priv->num_dai_conf,
				      माप(काष्ठा snd_soc_codec_conf),
				      GFP_KERNEL);
	अगर (!priv->dai_conf)
		वापस -ENOMEM;

	priv->num_dapm_routes = 3 * num_dai;
	priv->dapm_routes = devm_kसुस्मृति(&pdev->dev, priv->num_dapm_routes,
					 माप(काष्ठा snd_soc_dapm_route),
					 GFP_KERNEL);
	अगर (!priv->dapm_routes)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_dai; i++) अणु
		काष्ठा snd_soc_dai_link_component *dlc;

		/* क्रम CPU/Codec/Platक्रमm x 2 */
		dlc = devm_kसुस्मृति(&pdev->dev, 6, माप(*dlc), GFP_KERNEL);
		अगर (!dlc) अणु
			dev_err(&pdev->dev, "failed to allocate dai_link\n");
			वापस -ENOMEM;
		पूर्ण

		ret = of_parse_phandle_with_args(audmix_np, "dais", शून्य, i,
						 &args);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "of_parse_phandle_with_args failed\n");
			वापस ret;
		पूर्ण

		cpu_pdev = of_find_device_by_node(args.np);
		अगर (!cpu_pdev) अणु
			dev_err(&pdev->dev, "failed to find SAI platform device\n");
			वापस -EINVAL;
		पूर्ण
		put_device(&cpu_pdev->dev);

		dai_name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "%s%s",
					  fe_name_pref, args.np->full_name + 1);

		dev_info(pdev->dev.parent, "DAI FE name:%s\n", dai_name);

		अगर (i == 0) अणु
			out_cpu_np = args.np;
			capture_dai_name =
				devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "%s %s",
					       dai_name, "CPU-Capture");
		पूर्ण

		priv->dai[i].cpus = &dlc[0];
		priv->dai[i].codecs = &dlc[1];
		priv->dai[i].platक्रमms = &dlc[2];

		priv->dai[i].num_cpus = 1;
		priv->dai[i].num_codecs = 1;
		priv->dai[i].num_platक्रमms = 1;

		priv->dai[i].name = dai_name;
		priv->dai[i].stream_name = "HiFi-AUDMIX-FE";
		priv->dai[i].codecs->dai_name = "snd-soc-dummy-dai";
		priv->dai[i].codecs->name = "snd-soc-dummy";
		priv->dai[i].cpus->of_node = args.np;
		priv->dai[i].cpus->dai_name = dev_name(&cpu_pdev->dev);
		priv->dai[i].platक्रमms->of_node = args.np;
		priv->dai[i].dynamic = 1;
		priv->dai[i].dpcm_playback = 1;
		priv->dai[i].dpcm_capture = (i == 0 ? 1 : 0);
		priv->dai[i].ignore_pmकरोwn_समय = 1;
		priv->dai[i].ops = &imx_audmix_fe_ops;

		/* Add AUDMIX Backend */
		be_name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL,
					 "audmix-%d", i);
		be_pb = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL,
				       "AUDMIX-Playback-%d", i);
		be_cp = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL,
				       "AUDMIX-Capture-%d", i);

		priv->dai[num_dai + i].cpus = &dlc[3];
		priv->dai[num_dai + i].codecs = &dlc[4];
		priv->dai[num_dai + i].platक्रमms = &dlc[5];

		priv->dai[num_dai + i].num_cpus = 1;
		priv->dai[num_dai + i].num_codecs = 1;
		priv->dai[num_dai + i].num_platक्रमms = 1;

		priv->dai[num_dai + i].name = be_name;
		priv->dai[num_dai + i].codecs->dai_name = "snd-soc-dummy-dai";
		priv->dai[num_dai + i].codecs->name = "snd-soc-dummy";
		priv->dai[num_dai + i].cpus->of_node = audmix_np;
		priv->dai[num_dai + i].cpus->dai_name = be_name;
		priv->dai[num_dai + i].platक्रमms->name = "snd-soc-dummy";
		priv->dai[num_dai + i].no_pcm = 1;
		priv->dai[num_dai + i].dpcm_playback = 1;
		priv->dai[num_dai + i].dpcm_capture  = 1;
		priv->dai[num_dai + i].ignore_pmकरोwn_समय = 1;
		priv->dai[num_dai + i].ops = &imx_audmix_be_ops;

		priv->dai_conf[i].dlc.of_node = args.np;
		priv->dai_conf[i].name_prefix = dai_name;

		priv->dapm_routes[i].source =
			devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "%s %s",
				       dai_name, "CPU-Playback");
		priv->dapm_routes[i].sink = be_pb;
		priv->dapm_routes[num_dai + i].source   = be_pb;
		priv->dapm_routes[num_dai + i].sink     = be_cp;
		priv->dapm_routes[2 * num_dai + i].source = be_cp;
		priv->dapm_routes[2 * num_dai + i].sink   = capture_dai_name;
	पूर्ण

	cpu_pdev = of_find_device_by_node(out_cpu_np);
	अगर (!cpu_pdev) अणु
		dev_err(&pdev->dev, "failed to find SAI platform device\n");
		वापस -EINVAL;
	पूर्ण
	put_device(&cpu_pdev->dev);

	priv->cpu_mclk = devm_clk_get(&cpu_pdev->dev, "mclk1");
	अगर (IS_ERR(priv->cpu_mclk)) अणु
		ret = PTR_ERR(priv->cpu_mclk);
		dev_err(&cpu_pdev->dev, "failed to get DAI mclk1: %d\n", ret);
		वापस -EINVAL;
	पूर्ण

	priv->audmix_pdev = audmix_pdev;
	priv->out_pdev  = cpu_pdev;

	priv->card.dai_link = priv->dai;
	priv->card.num_links = priv->num_dai;
	priv->card.codec_conf = priv->dai_conf;
	priv->card.num_configs = priv->num_dai_conf;
	priv->card.dapm_routes = priv->dapm_routes;
	priv->card.num_dapm_routes = priv->num_dapm_routes;
	priv->card.dev = &pdev->dev;
	priv->card.owner = THIS_MODULE;
	priv->card.name = "imx-audmix";

	platक्रमm_set_drvdata(pdev, &priv->card);
	snd_soc_card_set_drvdata(&priv->card, priv);

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &priv->card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "snd_soc_register_card failed\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver imx_audmix_driver = अणु
	.probe = imx_audmix_probe,
	.driver = अणु
		.name = "imx-audmix",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx_audmix_driver);

MODULE_DESCRIPTION("NXP AUDMIX ASoC machine driver");
MODULE_AUTHOR("Viorel Suman <viorel.suman@nxp.com>");
MODULE_ALIAS("platform:imx-audmix");
MODULE_LICENSE("GPL v2");
