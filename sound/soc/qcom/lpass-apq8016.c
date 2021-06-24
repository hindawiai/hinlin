<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010-2011,2013-2015 The Linux Foundation. All rights reserved.
 *
 * lpass-apq8016.c -- ALSA SoC CPU DAI driver क्रम APQ8016 LPASS
 */


#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश <dt-bindings/sound/apq8016-lpass.h>
#समावेश "lpass-lpaif-reg.h"
#समावेश "lpass.h"

अटल काष्ठा snd_soc_dai_driver apq8016_lpass_cpu_dai_driver[] = अणु
	[MI2S_PRIMARY] =  अणु
		.id = MI2S_PRIMARY,
		.name = "Primary MI2S",
		.playback = अणु
			.stream_name	= "Primary Playback",
			.क्रमmats	= SNDRV_PCM_FMTBIT_S16 |
						SNDRV_PCM_FMTBIT_S24 |
						SNDRV_PCM_FMTBIT_S32,
			.rates		= SNDRV_PCM_RATE_8000 |
						SNDRV_PCM_RATE_16000 |
						SNDRV_PCM_RATE_32000 |
						SNDRV_PCM_RATE_48000 |
						SNDRV_PCM_RATE_96000,
			.rate_min	= 8000,
			.rate_max	= 96000,
			.channels_min	= 1,
			.channels_max	= 8,
		पूर्ण,
		.probe	= &asoc_qcom_lpass_cpu_dai_probe,
		.ops    = &asoc_qcom_lpass_cpu_dai_ops,
	पूर्ण,
	[MI2S_SECONDARY] =  अणु
		.id = MI2S_SECONDARY,
		.name = "Secondary MI2S",
		.playback = अणु
			.stream_name	= "Secondary Playback",
			.क्रमmats	= SNDRV_PCM_FMTBIT_S16 |
						SNDRV_PCM_FMTBIT_S24 |
						SNDRV_PCM_FMTBIT_S32,
			.rates		= SNDRV_PCM_RATE_8000 |
						SNDRV_PCM_RATE_16000 |
						SNDRV_PCM_RATE_32000 |
						SNDRV_PCM_RATE_48000 |
						SNDRV_PCM_RATE_96000,
			.rate_min	= 8000,
			.rate_max	= 96000,
			.channels_min	= 1,
			.channels_max	= 8,
		पूर्ण,
		.probe	= &asoc_qcom_lpass_cpu_dai_probe,
		.ops    = &asoc_qcom_lpass_cpu_dai_ops,
	पूर्ण,
	[MI2S_TERTIARY] =  अणु
		.id = MI2S_TERTIARY,
		.name = "Tertiary MI2S",
		.capture = अणु
			.stream_name	= "Tertiary Capture",
			.क्रमmats	= SNDRV_PCM_FMTBIT_S16 |
						SNDRV_PCM_FMTBIT_S24 |
						SNDRV_PCM_FMTBIT_S32,
			.rates		= SNDRV_PCM_RATE_8000 |
						SNDRV_PCM_RATE_16000 |
						SNDRV_PCM_RATE_32000 |
						SNDRV_PCM_RATE_48000 |
						SNDRV_PCM_RATE_96000,
			.rate_min	= 8000,
			.rate_max	= 96000,
			.channels_min	= 1,
			.channels_max	= 8,
		पूर्ण,
		.probe	= &asoc_qcom_lpass_cpu_dai_probe,
		.ops    = &asoc_qcom_lpass_cpu_dai_ops,
	पूर्ण,
	[MI2S_QUATERNARY] =  अणु
		.id = MI2S_QUATERNARY,
		.name = "Quatenary MI2S",
		.playback = अणु
			.stream_name	= "Quatenary Playback",
			.क्रमmats	= SNDRV_PCM_FMTBIT_S16 |
						SNDRV_PCM_FMTBIT_S24 |
						SNDRV_PCM_FMTBIT_S32,
			.rates		= SNDRV_PCM_RATE_8000 |
						SNDRV_PCM_RATE_16000 |
						SNDRV_PCM_RATE_32000 |
						SNDRV_PCM_RATE_48000 |
						SNDRV_PCM_RATE_96000,
			.rate_min	= 8000,
			.rate_max	= 96000,
			.channels_min	= 1,
			.channels_max	= 8,
		पूर्ण,
		.capture = अणु
			.stream_name	= "Quatenary Capture",
			.क्रमmats	= SNDRV_PCM_FMTBIT_S16 |
						SNDRV_PCM_FMTBIT_S24 |
						SNDRV_PCM_FMTBIT_S32,
			.rates		= SNDRV_PCM_RATE_8000 |
						SNDRV_PCM_RATE_16000 |
						SNDRV_PCM_RATE_32000 |
						SNDRV_PCM_RATE_48000 |
						SNDRV_PCM_RATE_96000,
			.rate_min	= 8000,
			.rate_max	= 96000,
			.channels_min	= 1,
			.channels_max	= 8,
		पूर्ण,
		.probe	= &asoc_qcom_lpass_cpu_dai_probe,
		.ops    = &asoc_qcom_lpass_cpu_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक apq8016_lpass_alloc_dma_channel(काष्ठा lpass_data *drvdata,
					   पूर्णांक direction, अचिन्हित पूर्णांक dai_id)
अणु
	काष्ठा lpass_variant *v = drvdata->variant;
	पूर्णांक chan = 0;

	अगर (direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
		chan = find_first_zero_bit(&drvdata->dma_ch_bit_map,
					v->rdma_channels);

		अगर (chan >= v->rdma_channels)
			वापस -EBUSY;
	पूर्ण अन्यथा अणु
		chan = find_next_zero_bit(&drvdata->dma_ch_bit_map,
					v->wrdma_channel_start +
					v->wrdma_channels,
					v->wrdma_channel_start);

		अगर (chan >=  v->wrdma_channel_start + v->wrdma_channels)
			वापस -EBUSY;
	पूर्ण

	set_bit(chan, &drvdata->dma_ch_bit_map);

	वापस chan;
पूर्ण

अटल पूर्णांक apq8016_lpass_मुक्त_dma_channel(काष्ठा lpass_data *drvdata, पूर्णांक chan, अचिन्हित पूर्णांक dai_id)
अणु
	clear_bit(chan, &drvdata->dma_ch_bit_map);

	वापस 0;
पूर्ण

अटल पूर्णांक apq8016_lpass_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpass_data *drvdata = platक्रमm_get_drvdata(pdev);
	काष्ठा lpass_variant *variant = drvdata->variant;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret, i;


	drvdata->clks = devm_kसुस्मृति(dev, variant->num_clks,
				     माप(*drvdata->clks), GFP_KERNEL);
	अगर (!drvdata->clks)
		वापस -ENOMEM;
	drvdata->num_clks = variant->num_clks;

	क्रम (i = 0; i < drvdata->num_clks; i++)
		drvdata->clks[i].id = variant->clk_name[i];

	ret = devm_clk_bulk_get(dev, drvdata->num_clks, drvdata->clks);
	अगर (ret) अणु
		dev_err(dev, "Failed to get clocks %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_bulk_prepare_enable(drvdata->num_clks, drvdata->clks);
	अगर (ret) अणु
		dev_err(dev, "apq8016 clk_enable failed\n");
		वापस ret;
	पूर्ण

	drvdata->ahbix_clk = devm_clk_get(dev, "ahbix-clk");
	अगर (IS_ERR(drvdata->ahbix_clk)) अणु
		dev_err(dev, "error getting ahbix-clk: %ld\n",
				PTR_ERR(drvdata->ahbix_clk));
		ret = PTR_ERR(drvdata->ahbix_clk);
		जाओ err_ahbix_clk;
	पूर्ण

	ret = clk_set_rate(drvdata->ahbix_clk, LPASS_AHBIX_CLOCK_FREQUENCY);
	अगर (ret) अणु
		dev_err(dev, "error setting rate on ahbix_clk: %d\n", ret);
		जाओ err_ahbix_clk;
	पूर्ण
	dev_dbg(dev, "set ahbix_clk rate to %lu\n",
			clk_get_rate(drvdata->ahbix_clk));

	ret = clk_prepare_enable(drvdata->ahbix_clk);
	अगर (ret) अणु
		dev_err(dev, "error enabling ahbix_clk: %d\n", ret);
		जाओ err_ahbix_clk;
	पूर्ण

	वापस 0;

err_ahbix_clk:
	clk_bulk_disable_unprepare(drvdata->num_clks, drvdata->clks);
	वापस ret;
पूर्ण

अटल पूर्णांक apq8016_lpass_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpass_data *drvdata = platक्रमm_get_drvdata(pdev);

	clk_bulk_disable_unprepare(drvdata->num_clks, drvdata->clks);
	clk_disable_unprepare(drvdata->ahbix_clk);

	वापस 0;
पूर्ण


अटल काष्ठा lpass_variant apq8016_data = अणु
	.i2sctrl_reg_base	= 0x1000,
	.i2sctrl_reg_stride	= 0x1000,
	.i2s_ports		= 4,
	.irq_reg_base		= 0x6000,
	.irq_reg_stride		= 0x1000,
	.irq_ports		= 3,
	.rdma_reg_base		= 0x8400,
	.rdma_reg_stride	= 0x1000,
	.rdma_channels		= 2,
	.dmactl_audअगर_start	= 1,
	.wrdma_reg_base		= 0xB000,
	.wrdma_reg_stride	= 0x1000,
	.wrdma_channel_start	= 5,
	.wrdma_channels		= 2,
	.loopback		= REG_FIELD_ID(0x1000, 15, 15, 4, 0x1000),
	.spken			= REG_FIELD_ID(0x1000, 14, 14, 4, 0x1000),
	.spkmode		= REG_FIELD_ID(0x1000, 10, 13, 4, 0x1000),
	.spkmono		= REG_FIELD_ID(0x1000, 9, 9, 4, 0x1000),
	.micen			= REG_FIELD_ID(0x1000, 8, 8, 4, 0x1000),
	.micmode		= REG_FIELD_ID(0x1000, 4, 7, 4, 0x1000),
	.micmono		= REG_FIELD_ID(0x1000, 3, 3, 4, 0x1000),
	.wssrc			= REG_FIELD_ID(0x1000, 2, 2, 4, 0x1000),
	.bitwidth		= REG_FIELD_ID(0x1000, 0, 1, 4, 0x1000),

	.rdma_dyncclk		= REG_FIELD_ID(0x8400, 12, 12, 2, 0x1000),
	.rdma_bursten		= REG_FIELD_ID(0x8400, 11, 11, 2, 0x1000),
	.rdma_wpscnt		= REG_FIELD_ID(0x8400, 8, 10, 2, 0x1000),
	.rdma_पूर्णांकf		= REG_FIELD_ID(0x8400, 4, 7, 2, 0x1000),
	.rdma_fअगरowm		= REG_FIELD_ID(0x8400, 1, 3, 2, 0x1000),
	.rdma_enable		= REG_FIELD_ID(0x8400, 0, 0, 2, 0x1000),

	.wrdma_dyncclk		= REG_FIELD_ID(0xB000, 12, 12, 2, 0x1000),
	.wrdma_bursten		= REG_FIELD_ID(0xB000, 11, 11, 2, 0x1000),
	.wrdma_wpscnt		= REG_FIELD_ID(0xB000, 8, 10, 2, 0x1000),
	.wrdma_पूर्णांकf		= REG_FIELD_ID(0xB000, 4, 7, 2, 0x1000),
	.wrdma_fअगरowm		= REG_FIELD_ID(0xB000, 1, 3, 2, 0x1000),
	.wrdma_enable		= REG_FIELD_ID(0xB000, 0, 0, 2, 0x1000),

	.clk_name		= (स्थिर अक्षर*[]) अणु
				   "pcnoc-mport-clk",
				   "pcnoc-sway-clk",
				  पूर्ण,
	.num_clks		= 2,
	.dai_driver		= apq8016_lpass_cpu_dai_driver,
	.num_dai		= ARRAY_SIZE(apq8016_lpass_cpu_dai_driver),
	.dai_osr_clk_names	= (स्थिर अक्षर *[]) अणु
				"mi2s-osr-clk0",
				"mi2s-osr-clk1",
				"mi2s-osr-clk2",
				"mi2s-osr-clk3",
				पूर्ण,
	.dai_bit_clk_names	= (स्थिर अक्षर *[]) अणु
				"mi2s-bit-clk0",
				"mi2s-bit-clk1",
				"mi2s-bit-clk2",
				"mi2s-bit-clk3",
				पूर्ण,
	.init			= apq8016_lpass_init,
	.निकास			= apq8016_lpass_निकास,
	.alloc_dma_channel	= apq8016_lpass_alloc_dma_channel,
	.मुक्त_dma_channel	= apq8016_lpass_मुक्त_dma_channel,
पूर्ण;

अटल स्थिर काष्ठा of_device_id apq8016_lpass_cpu_device_id[] __maybe_unused = अणु
	अणु .compatible = "qcom,lpass-cpu-apq8016", .data = &apq8016_data पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, apq8016_lpass_cpu_device_id);

अटल काष्ठा platक्रमm_driver apq8016_lpass_cpu_platक्रमm_driver = अणु
	.driver	= अणु
		.name		= "apq8016-lpass-cpu",
		.of_match_table	= of_match_ptr(apq8016_lpass_cpu_device_id),
	पूर्ण,
	.probe	= asoc_qcom_lpass_cpu_platक्रमm_probe,
	.हटाओ	= asoc_qcom_lpass_cpu_platक्रमm_हटाओ,
पूर्ण;
module_platक्रमm_driver(apq8016_lpass_cpu_platक्रमm_driver);

MODULE_DESCRIPTION("APQ8016 LPASS CPU Driver");
MODULE_LICENSE("GPL v2");

