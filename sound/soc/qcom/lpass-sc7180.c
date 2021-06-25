<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 *
 * lpass-sc7180.c -- ALSA SoC platक्रमm-machine driver क्रम QTi LPASS
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <dt-bindings/sound/sc7180-lpass.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश "lpass-lpaif-reg.h"
#समावेश "lpass.h"

अटल काष्ठा snd_soc_dai_driver sc7180_lpass_cpu_dai_driver[] = अणु
	अणु
		.id = MI2S_PRIMARY,
		.name = "Primary MI2S",
		.playback = अणु
			.stream_name = "Primary Playback",
			.क्रमmats	= SNDRV_PCM_FMTBIT_S16,
			.rates = SNDRV_PCM_RATE_48000,
			.rate_min	= 48000,
			.rate_max	= 48000,
			.channels_min	= 2,
			.channels_max	= 2,
		पूर्ण,
		.capture = अणु
			.stream_name = "Primary Capture",
			.क्रमmats = SNDRV_PCM_FMTBIT_S16 |
				SNDRV_PCM_FMTBIT_S32,
			.rates = SNDRV_PCM_RATE_48000,
			.rate_min	= 48000,
			.rate_max	= 48000,
			.channels_min	= 2,
			.channels_max	= 2,
		पूर्ण,
		.probe	= &asoc_qcom_lpass_cpu_dai_probe,
		.ops    = &asoc_qcom_lpass_cpu_dai_ops,
	पूर्ण, अणु
		.id = MI2S_SECONDARY,
		.name = "Secondary MI2S",
		.playback = अणु
			.stream_name = "Secondary Playback",
			.क्रमmats	= SNDRV_PCM_FMTBIT_S16,
			.rates = SNDRV_PCM_RATE_48000,
			.rate_min	= 48000,
			.rate_max	= 48000,
			.channels_min	= 2,
			.channels_max	= 2,
		पूर्ण,
		.probe	= &asoc_qcom_lpass_cpu_dai_probe,
		.ops    = &asoc_qcom_lpass_cpu_dai_ops,
	पूर्ण, अणु
		.id = LPASS_DP_RX,
		.name = "Hdmi",
		.playback = अणु
			.stream_name = "Hdmi Playback",
			.क्रमmats	= SNDRV_PCM_FMTBIT_S24,
			.rates = SNDRV_PCM_RATE_48000,
			.rate_min	= 48000,
			.rate_max	= 48000,
			.channels_min	= 2,
			.channels_max	= 2,
		पूर्ण,
		.ops    = &asoc_qcom_lpass_hdmi_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sc7180_lpass_alloc_dma_channel(काष्ठा lpass_data *drvdata,
					   पूर्णांक direction, अचिन्हित पूर्णांक dai_id)
अणु
	काष्ठा lpass_variant *v = drvdata->variant;
	पूर्णांक chan = 0;

	अगर (dai_id == LPASS_DP_RX) अणु
		अगर (direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
			chan = find_first_zero_bit(&drvdata->hdmi_dma_ch_bit_map,
						v->hdmi_rdma_channels);

			अगर (chan >= v->hdmi_rdma_channels)
				वापस -EBUSY;
		पूर्ण
		set_bit(chan, &drvdata->hdmi_dma_ch_bit_map);
	पूर्ण अन्यथा अणु
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
	पूर्ण
	वापस chan;
पूर्ण

अटल पूर्णांक sc7180_lpass_मुक्त_dma_channel(काष्ठा lpass_data *drvdata, पूर्णांक chan, अचिन्हित पूर्णांक dai_id)
अणु
	अगर (dai_id == LPASS_DP_RX)
		clear_bit(chan, &drvdata->hdmi_dma_ch_bit_map);
	अन्यथा
		clear_bit(chan, &drvdata->dma_ch_bit_map);

	वापस 0;
पूर्ण

अटल पूर्णांक sc7180_lpass_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpass_data *drvdata = platक्रमm_get_drvdata(pdev);
	काष्ठा lpass_variant *variant = drvdata->variant;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret, i;

	drvdata->clks = devm_kसुस्मृति(dev, variant->num_clks,
				     माप(*drvdata->clks), GFP_KERNEL);
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
		dev_err(dev, "sc7180 clk_enable failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sc7180_lpass_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpass_data *drvdata = platक्रमm_get_drvdata(pdev);

	clk_bulk_disable_unprepare(drvdata->num_clks, drvdata->clks);

	वापस 0;
पूर्ण

अटल काष्ठा lpass_variant sc7180_data = अणु
	.i2sctrl_reg_base	= 0x1000,
	.i2sctrl_reg_stride	= 0x1000,
	.i2s_ports		= 3,
	.irq_reg_base		= 0x9000,
	.irq_reg_stride		= 0x1000,
	.irq_ports		= 3,
	.rdma_reg_base		= 0xC000,
	.rdma_reg_stride	= 0x1000,
	.rdma_channels		= 5,
	.hdmi_rdma_reg_base		= 0x64000,
	.hdmi_rdma_reg_stride	= 0x1000,
	.hdmi_rdma_channels		= 4,
	.dmactl_audअगर_start	= 1,
	.wrdma_reg_base		= 0x18000,
	.wrdma_reg_stride	= 0x1000,
	.wrdma_channel_start	= 5,
	.wrdma_channels		= 4,

	.loopback		= REG_FIELD_ID(0x1000, 17, 17, 3, 0x1000),
	.spken			= REG_FIELD_ID(0x1000, 16, 16, 3, 0x1000),
	.spkmode		= REG_FIELD_ID(0x1000, 11, 15, 3, 0x1000),
	.spkmono		= REG_FIELD_ID(0x1000, 10, 10, 3, 0x1000),
	.micen			= REG_FIELD_ID(0x1000, 9, 9, 3, 0x1000),
	.micmode		= REG_FIELD_ID(0x1000, 4, 8, 3, 0x1000),
	.micmono		= REG_FIELD_ID(0x1000, 3, 3, 3, 0x1000),
	.wssrc			= REG_FIELD_ID(0x1000, 2, 2, 3, 0x1000),
	.bitwidth		= REG_FIELD_ID(0x1000, 0, 1, 3, 0x1000),

	.rdma_dyncclk		= REG_FIELD_ID(0xC000, 21, 21, 5, 0x1000),
	.rdma_bursten		= REG_FIELD_ID(0xC000, 20, 20, 5, 0x1000),
	.rdma_wpscnt		= REG_FIELD_ID(0xC000, 16, 19, 5, 0x1000),
	.rdma_पूर्णांकf			= REG_FIELD_ID(0xC000, 12, 15, 5, 0x1000),
	.rdma_fअगरowm		= REG_FIELD_ID(0xC000, 1, 5, 5, 0x1000),
	.rdma_enable		= REG_FIELD_ID(0xC000, 0, 0, 5, 0x1000),

	.wrdma_dyncclk		= REG_FIELD_ID(0x18000, 22, 22, 4, 0x1000),
	.wrdma_bursten		= REG_FIELD_ID(0x18000, 21, 21, 4, 0x1000),
	.wrdma_wpscnt		= REG_FIELD_ID(0x18000, 17, 20, 4, 0x1000),
	.wrdma_पूर्णांकf		= REG_FIELD_ID(0x18000, 12, 16, 4, 0x1000),
	.wrdma_fअगरowm		= REG_FIELD_ID(0x18000, 1, 5, 4, 0x1000),
	.wrdma_enable		= REG_FIELD_ID(0x18000, 0, 0, 4, 0x1000),

	.hdmi_tx_ctl_addr	= 0x1000,
	.hdmi_legacy_addr	= 0x1008,
	.hdmi_vbit_addr		= 0x610c0,
	.hdmi_ch_lsb_addr	= 0x61048,
	.hdmi_ch_msb_addr	= 0x6104c,
	.ch_stride		= 0x8,
	.hdmi_parity_addr	= 0x61034,
	.hdmi_dmactl_addr	= 0x61038,
	.hdmi_dma_stride	= 0x4,
	.hdmi_DP_addr		= 0x610c8,
	.hdmi_sstream_addr	= 0x6101c,
	.hdmi_irq_reg_base		= 0x63000,
	.hdmi_irq_ports		= 1,

	.hdmi_rdma_dyncclk		= REG_FIELD_ID(0x64000, 14, 14, 4, 0x1000),
	.hdmi_rdma_bursten		= REG_FIELD_ID(0x64000, 13, 13, 4, 0x1000),
	.hdmi_rdma_burst8		= REG_FIELD_ID(0x64000, 15, 15, 4, 0x1000),
	.hdmi_rdma_burst16		= REG_FIELD_ID(0x64000, 16, 16, 4, 0x1000),
	.hdmi_rdma_dynburst		= REG_FIELD_ID(0x64000, 18, 18, 4, 0x1000),
	.hdmi_rdma_wpscnt		= REG_FIELD_ID(0x64000, 10, 12, 4, 0x1000),
	.hdmi_rdma_fअगरowm		= REG_FIELD_ID(0x64000, 1, 5, 4, 0x1000),
	.hdmi_rdma_enable		= REG_FIELD_ID(0x64000, 0, 0, 4, 0x1000),

	.sstream_en		= REG_FIELD(0x6101c, 0, 0),
	.dma_sel			= REG_FIELD(0x6101c, 1, 2),
	.स्वतः_bbit_en	= REG_FIELD(0x6101c, 3, 3),
	.layout			= REG_FIELD(0x6101c, 4, 4),
	.layout_sp		= REG_FIELD(0x6101c, 5, 8),
	.set_sp_on_en	= REG_FIELD(0x6101c, 10, 10),
	.dp_audio		= REG_FIELD(0x6101c, 11, 11),
	.dp_staffing_en	= REG_FIELD(0x6101c, 12, 12),
	.dp_sp_b_hw_en	= REG_FIELD(0x6101c, 13, 13),

	.mute			= REG_FIELD(0x610c8, 0, 0),
	.as_sdp_cc		= REG_FIELD(0x610c8, 1, 3),
	.as_sdp_ct		= REG_FIELD(0x610c8, 4, 7),
	.aअगर_db4			= REG_FIELD(0x610c8, 8, 15),
	.frequency		= REG_FIELD(0x610c8, 16, 21),
	.mst_index		= REG_FIELD(0x610c8, 28, 29),
	.dptx_index		= REG_FIELD(0x610c8, 30, 31),

	.soft_reset		= REG_FIELD(0x1000, 31, 31),
	.क्रमce_reset	= REG_FIELD(0x1000, 30, 30),

	.use_hw_chs		= REG_FIELD(0x61038, 0, 0),
	.use_hw_usr		= REG_FIELD(0x61038, 1, 1),
	.hw_chs_sel		= REG_FIELD(0x61038, 2, 4),
	.hw_usr_sel		= REG_FIELD(0x61038, 5, 6),

	.replace_vbit	= REG_FIELD(0x610c0, 0, 0),
	.vbit_stream	= REG_FIELD(0x610c0, 1, 1),

	.legacy_en		=  REG_FIELD(0x1008, 0, 0),
	.calc_en		=  REG_FIELD(0x61034, 0, 0),
	.lsb_bits		=  REG_FIELD(0x61048, 0, 31),
	.msb_bits		=  REG_FIELD(0x6104c, 0, 31),


	.clk_name		= (स्थिर अक्षर*[]) अणु
				   "pcnoc-sway-clk",
				   "audio-core",
				   "pcnoc-mport-clk",
				पूर्ण,
	.num_clks		= 3,
	.dai_driver		= sc7180_lpass_cpu_dai_driver,
	.num_dai		= ARRAY_SIZE(sc7180_lpass_cpu_dai_driver),
	.dai_osr_clk_names      = (स्थिर अक्षर *[]) अणु
				   "mclk0",
				   "null",
				पूर्ण,
	.dai_bit_clk_names      = (स्थिर अक्षर *[]) अणु
				   "mi2s-bit-clk0",
				   "mi2s-bit-clk1",
				पूर्ण,
	.init			= sc7180_lpass_init,
	.निकास			= sc7180_lpass_निकास,
	.alloc_dma_channel	= sc7180_lpass_alloc_dma_channel,
	.मुक्त_dma_channel	= sc7180_lpass_मुक्त_dma_channel,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sc7180_lpass_cpu_device_id[] __maybe_unused = अणु
	अणु.compatible = "qcom,sc7180-lpass-cpu", .data = &sc7180_dataपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sc7180_lpass_cpu_device_id);

अटल काष्ठा platक्रमm_driver sc7180_lpass_cpu_platक्रमm_driver = अणु
	.driver = अणु
		.name = "sc7180-lpass-cpu",
		.of_match_table = of_match_ptr(sc7180_lpass_cpu_device_id),
	पूर्ण,
	.probe = asoc_qcom_lpass_cpu_platक्रमm_probe,
	.हटाओ = asoc_qcom_lpass_cpu_platक्रमm_हटाओ,
	.shutकरोwn = asoc_qcom_lpass_cpu_platक्रमm_shutकरोwn,
पूर्ण;

module_platक्रमm_driver(sc7180_lpass_cpu_platक्रमm_driver);

MODULE_DESCRIPTION("SC7180 LPASS CPU DRIVER");
MODULE_LICENSE("GPL v2");
