<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010-2011,2013-2015 The Linux Foundation. All rights reserved.
 *
 * lpass-ipq806x.c -- ALSA SoC CPU DAI driver क्रम QTi LPASS
 * Splited out the IPQ8064 soc specअगरic from lpass-cpu.c
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "lpass-lpaif-reg.h"
#समावेश "lpass.h"

क्रमागत lpaअगर_i2s_ports अणु
	IPQ806X_LPAIF_I2S_PORT_CODEC_SPK,
	IPQ806X_LPAIF_I2S_PORT_CODEC_MIC,
	IPQ806X_LPAIF_I2S_PORT_SEC_SPK,
	IPQ806X_LPAIF_I2S_PORT_SEC_MIC,
	IPQ806X_LPAIF_I2S_PORT_MI2S,
पूर्ण;

क्रमागत lpaअगर_dma_channels अणु
	IPQ806X_LPAIF_RDMA_CHAN_MI2S,
	IPQ806X_LPAIF_RDMA_CHAN_PCM0,
	IPQ806X_LPAIF_RDMA_CHAN_PCM1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ipq806x_lpass_cpu_dai_driver = अणु
	.id	= IPQ806X_LPAIF_I2S_PORT_MI2S,
	.playback = अणु
		.stream_name	= "lpass-cpu-playback",
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
पूर्ण;

अटल पूर्णांक ipq806x_lpass_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpass_data *drvdata = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

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

err_ahbix_clk:
	वापस ret;
पूर्ण

अटल पूर्णांक ipq806x_lpass_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpass_data *drvdata = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(drvdata->ahbix_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक ipq806x_lpass_alloc_dma_channel(काष्ठा lpass_data *drvdata, पूर्णांक dir, अचिन्हित पूर्णांक dai_id)
अणु
	अगर (dir == SNDRV_PCM_STREAM_PLAYBACK)
		वापस IPQ806X_LPAIF_RDMA_CHAN_MI2S;
	अन्यथा	/* Capture currently not implemented */
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक ipq806x_lpass_मुक्त_dma_channel(काष्ठा lpass_data *drvdata, पूर्णांक chan, अचिन्हित पूर्णांक dai_id)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा lpass_variant ipq806x_data = अणु
	.i2sctrl_reg_base	= 0x0010,
	.i2sctrl_reg_stride	= 0x04,
	.i2s_ports		= 5,
	.irq_reg_base		= 0x3000,
	.irq_reg_stride		= 0x1000,
	.irq_ports		= 3,
	.rdma_reg_base		= 0x6000,
	.rdma_reg_stride	= 0x1000,
	.rdma_channels		= 4,
	.wrdma_reg_base		= 0xB000,
	.wrdma_reg_stride	= 0x1000,
	.wrdma_channel_start	= 5,
	.wrdma_channels		= 4,
	.loopback		= REG_FIELD_ID(0x0010, 15, 15, 5, 0x4),
	.spken			= REG_FIELD_ID(0x0010, 14, 14, 5, 0x4),
	.spkmode		= REG_FIELD_ID(0x0010, 10, 13, 5, 0x4),
	.spkmono		= REG_FIELD_ID(0x0010, 9, 9, 5, 0x4),
	.micen			= REG_FIELD_ID(0x0010, 8, 8, 5, 0x4),
	.micmode		= REG_FIELD_ID(0x0010, 4, 7, 5, 0x4),
	.micmono		= REG_FIELD_ID(0x0010, 3, 3, 5, 0x4),
	.wssrc			= REG_FIELD_ID(0x0010, 2, 2, 5, 0x4),
	.bitwidth		= REG_FIELD_ID(0x0010, 0, 1, 5, 0x4),

	.rdma_dyncclk		= REG_FIELD_ID(0x6000, 12, 12, 4, 0x1000),
	.rdma_bursten		= REG_FIELD_ID(0x6000, 11, 11, 4, 0x1000),
	.rdma_wpscnt		= REG_FIELD_ID(0x6000, 8, 10, 4, 0x1000),
	.rdma_पूर्णांकf		= REG_FIELD_ID(0x6000, 4, 7, 4, 0x1000),
	.rdma_fअगरowm		= REG_FIELD_ID(0x6000, 1, 3, 4, 0x1000),
	.rdma_enable		= REG_FIELD_ID(0x6000, 0, 0, 4, 0x1000),

	.wrdma_dyncclk		= REG_FIELD_ID(0xB000, 12, 12, 4, 0x1000),
	.wrdma_bursten		= REG_FIELD_ID(0xB000, 11, 11, 4, 0x1000),
	.wrdma_wpscnt		= REG_FIELD_ID(0xB000, 8, 10, 4, 0x1000),
	.wrdma_पूर्णांकf		= REG_FIELD_ID(0xB000, 4, 7, 4, 0x1000),
	.wrdma_fअगरowm		= REG_FIELD_ID(0xB000, 1, 3, 4, 0x1000),
	.wrdma_enable		= REG_FIELD_ID(0xB000, 0, 0, 4, 0x1000),

	.dai_driver		= &ipq806x_lpass_cpu_dai_driver,
	.num_dai		= 1,
	.dai_osr_clk_names	= (स्थिर अक्षर *[]) अणु
				"mi2s-osr-clk",
				पूर्ण,
	.dai_bit_clk_names	= (स्थिर अक्षर *[]) अणु
				"mi2s-bit-clk",
				पूर्ण,
	.init			= ipq806x_lpass_init,
	.निकास			= ipq806x_lpass_निकास,
	.alloc_dma_channel	= ipq806x_lpass_alloc_dma_channel,
	.मुक्त_dma_channel	= ipq806x_lpass_मुक्त_dma_channel,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ipq806x_lpass_cpu_device_id[] __maybe_unused = अणु
	अणु .compatible = "qcom,lpass-cpu", .data = &ipq806x_data पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ipq806x_lpass_cpu_device_id);

अटल काष्ठा platक्रमm_driver ipq806x_lpass_cpu_platक्रमm_driver = अणु
	.driver	= अणु
		.name		= "lpass-cpu",
		.of_match_table	= of_match_ptr(ipq806x_lpass_cpu_device_id),
	पूर्ण,
	.probe	= asoc_qcom_lpass_cpu_platक्रमm_probe,
	.हटाओ	= asoc_qcom_lpass_cpu_platक्रमm_हटाओ,
पूर्ण;
module_platक्रमm_driver(ipq806x_lpass_cpu_platक्रमm_driver);

MODULE_DESCRIPTION("QTi LPASS CPU Driver");
MODULE_LICENSE("GPL v2");
