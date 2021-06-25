<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// smdk_spdअगर.c - S/PDIF audio क्रम SMDK
//
// Copyright (C) 2010 Samsung Electronics Co., Ltd.

#समावेश <linux/clk.h>
#समावेश <linux/module.h>

#समावेश <sound/soc.h>

#समावेश "spdif.h"

/* Audio घड़ी settings are beदीर्घed to board specअगरic part. Every
 * board can set audio source घड़ी setting which is matched with H/W
 * like this function-'set_audio_clock_heirachy'.
 */
अटल पूर्णांक set_audio_घड़ी_heirachy(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk *fout_epll, *mout_epll, *sclk_audio0, *sclk_spdअगर;
	पूर्णांक ret = 0;

	fout_epll = clk_get(शून्य, "fout_epll");
	अगर (IS_ERR(fout_epll)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Cannot find fout_epll.\n",
				__func__);
		वापस -EINVAL;
	पूर्ण

	mout_epll = clk_get(शून्य, "mout_epll");
	अगर (IS_ERR(mout_epll)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Cannot find mout_epll.\n",
				__func__);
		ret = -EINVAL;
		जाओ out1;
	पूर्ण

	sclk_audio0 = clk_get(&pdev->dev, "sclk_audio");
	अगर (IS_ERR(sclk_audio0)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Cannot find sclk_audio.\n",
				__func__);
		ret = -EINVAL;
		जाओ out2;
	पूर्ण

	sclk_spdअगर = clk_get(शून्य, "sclk_spdif");
	अगर (IS_ERR(sclk_spdअगर)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Cannot find sclk_spdif.\n",
				__func__);
		ret = -EINVAL;
		जाओ out3;
	पूर्ण

	/* Set audio घड़ी hierarchy क्रम S/PDIF */
	clk_set_parent(mout_epll, fout_epll);
	clk_set_parent(sclk_audio0, mout_epll);
	clk_set_parent(sclk_spdअगर, sclk_audio0);

	clk_put(sclk_spdअगर);
out3:
	clk_put(sclk_audio0);
out2:
	clk_put(mout_epll);
out1:
	clk_put(fout_epll);

	वापस ret;
पूर्ण

/* We should haved to set घड़ी directly on this part because of घड़ी
 * scheme of Samsudng SoCs did not support to set rates from असलtrct
 * घड़ी of it's hierarchy.
 */
अटल पूर्णांक set_audio_घड़ी_rate(अचिन्हित दीर्घ epll_rate,
				अचिन्हित दीर्घ audio_rate)
अणु
	काष्ठा clk *fout_epll, *sclk_spdअगर;

	fout_epll = clk_get(शून्य, "fout_epll");
	अगर (IS_ERR(fout_epll)) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to get fout_epll\n", __func__);
		वापस -ENOENT;
	पूर्ण

	clk_set_rate(fout_epll, epll_rate);
	clk_put(fout_epll);

	sclk_spdअगर = clk_get(शून्य, "sclk_spdif");
	अगर (IS_ERR(sclk_spdअगर)) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to get sclk_spdif\n", __func__);
		वापस -ENOENT;
	पूर्ण

	clk_set_rate(sclk_spdअगर, audio_rate);
	clk_put(sclk_spdअगर);

	वापस 0;
पूर्ण

अटल पूर्णांक smdk_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	अचिन्हित दीर्घ pll_out, rclk_rate;
	पूर्णांक ret, ratio;

	चयन (params_rate(params)) अणु
	हाल 44100:
		pll_out = 45158400;
		अवरोध;
	हाल 32000:
	हाल 48000:
	हाल 96000:
		pll_out = 49152000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Setting ratio to 512fs helps to use S/PDIF with HDMI without
	 * modअगरy S/PDIF ASoC machine driver.
	 */
	ratio = 512;
	rclk_rate = params_rate(params) * ratio;

	/* Set audio source घड़ी rates */
	ret = set_audio_घड़ी_rate(pll_out, rclk_rate);
	अगर (ret < 0)
		वापस ret;

	/* Set S/PDIF uses पूर्णांकernal source घड़ी */
	ret = snd_soc_dai_set_sysclk(cpu_dai, SND_SOC_SPDIF_INT_MCLK,
					rclk_rate, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops smdk_spdअगर_ops = अणु
	.hw_params = smdk_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEFS(spdअगर,
	DAILINK_COMP_ARRAY(COMP_CPU("samsung-spdif")),
	DAILINK_COMP_ARRAY(COMP_CODEC("spdif-dit", "dit-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("samsung-spdif")));

अटल काष्ठा snd_soc_dai_link smdk_dai = अणु
	.name = "S/PDIF",
	.stream_name = "S/PDIF PCM Playback",
	.ops = &smdk_spdअगर_ops,
	SND_SOC_DAILINK_REG(spdअगर),
पूर्ण;

अटल काष्ठा snd_soc_card smdk = अणु
	.name = "SMDK-S/PDIF",
	.owner = THIS_MODULE,
	.dai_link = &smdk_dai,
	.num_links = 1,
पूर्ण;

अटल काष्ठा platक्रमm_device *smdk_snd_spdअगर_dit_device;
अटल काष्ठा platक्रमm_device *smdk_snd_spdअगर_device;

अटल पूर्णांक __init smdk_init(व्योम)
अणु
	पूर्णांक ret;

	smdk_snd_spdअगर_dit_device = platक्रमm_device_alloc("spdif-dit", -1);
	अगर (!smdk_snd_spdअगर_dit_device)
		वापस -ENOMEM;

	ret = platक्रमm_device_add(smdk_snd_spdअगर_dit_device);
	अगर (ret)
		जाओ err1;

	smdk_snd_spdअगर_device = platक्रमm_device_alloc("soc-audio", -1);
	अगर (!smdk_snd_spdअगर_device) अणु
		ret = -ENOMEM;
		जाओ err2;
	पूर्ण

	platक्रमm_set_drvdata(smdk_snd_spdअगर_device, &smdk);

	ret = platक्रमm_device_add(smdk_snd_spdअगर_device);
	अगर (ret)
		जाओ err3;

	/* Set audio घड़ी hierarchy manually */
	ret = set_audio_घड़ी_heirachy(smdk_snd_spdअगर_device);
	अगर (ret)
		जाओ err4;

	वापस 0;
err4:
	platक्रमm_device_del(smdk_snd_spdअगर_device);
err3:
	platक्रमm_device_put(smdk_snd_spdअगर_device);
err2:
	platक्रमm_device_del(smdk_snd_spdअगर_dit_device);
err1:
	platक्रमm_device_put(smdk_snd_spdअगर_dit_device);
	वापस ret;
पूर्ण

अटल व्योम __निकास smdk_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(smdk_snd_spdअगर_device);
	platक्रमm_device_unरेजिस्टर(smdk_snd_spdअगर_dit_device);
पूर्ण

module_init(smdk_init);
module_निकास(smdk_निकास);

MODULE_AUTHOR("Seungwhan Youn, <sw.youn@samsung.com>");
MODULE_DESCRIPTION("ALSA SoC SMDK+S/PDIF");
MODULE_LICENSE("GPL");
